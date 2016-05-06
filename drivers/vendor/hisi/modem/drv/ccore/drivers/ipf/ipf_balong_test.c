#ifdef __cplusplus
extern "C" {
#endif

#include <ipf_balong_test.h>

#define	LONG_DATA		(1500)
#define	SHORT_DATA		(300)
#define AD_WPTR_MASK	0xff

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
unsigned int ip_packet_flag = 0;

static int ipf_ul_confirm = 0;
unsigned int g_u32UlError=0;
unsigned int g_u32UlFltError=0;
unsigned int g_u32UlTotalDataNum = 0;
unsigned int g_u32UlTotalBDNum = 0;
unsigned int g_ipf_ul_init = 0;
unsigned int g_ipf_dl_init = 0;
unsigned int ccore_reset_ipf = 0;

struct tagIPF_AD_DESC_S ADulshort[IPF_ULAD0_DESC_SIZE];
struct tagIPF_AD_DESC_S ADullong[IPF_ULAD1_DESC_SIZE];

int g_u32IpfStAllInit = 0;
int g_u32IpfStUlInit = 0;

int g_u32IpfStDlInit = 0;

extern unsigned int ipf_base_addr_ccore;
extern struct ipf_ctx g_ipf_ctx;

int IPF_ST_DL_FlushAD(IPF_ADQ_EMPTY_E eAdqEmptyDl);
int IPF_ST_UL_FlushAD(IPF_ADQ_EMPTY_E eAdqEmptyUl);

void ipf_test_debug_switch(unsigned int num)
{
	debug_test = num;
}

void ipf_set_ccore_reset_flag(unsigned int flag)
{
	ccore_reset_ipf = flag;
}

int ipf_set_ccore_ipf_reset_flag_pos(void)
{
	ccore_reset_ipf = 1;
	return OK;
}

static void ipf_print_hex_4width(unsigned int *data, unsigned int len)
{
	unsigned int i;
	for(i=0; i< len / 4; i++ ) {
		IPF_TEST_PRINT("0x%08x\t", *(data + i));
		if((i+1)%4 == 0)
			IPF_TEST_PRINT("\n");
	}
	IPF_TEST_PRINT("\n");
}

static void delay(unsigned int count)
{
	int i,j;
	for(i=count; i>=0; i--)
	{
		for(j=1000;j>=0;j--);
	}
}

void ipf_ad_config_flag(IPF_ADQ_CONFIG_E flag)
{
	ipf_config_ad_flag = flag;
	if(STOP_CONFIG_AD == ipf_config_ad_flag)
	{
		IPF_TEST_ERR("Stop adq config at this core. \n");
	}
	else
	{
		IPF_TEST_ERR("Restore adq config at this core. \n");
		IPF_ST_UL_FlushAD(IPF_AD_0);
		IPF_ST_UL_FlushAD(IPF_AD_1);
	}
}

unsigned int g_IpfUlTaskId = 0;
unsigned char* g_pu8STUlData = NULL;
unsigned char* g_short_data = NULL;

int CmpDMAData(unsigned int* p1, unsigned int* p2, unsigned int u32Len)
{
    unsigned int i = 0;
    for(i=0; i<u32Len/4; i++)
    {
        if(*(unsigned int*)(p1+i) != *(unsigned int*)(p2+i))
        {
            return ERROR;
        }
    }
    return 0;
}

unsigned int get_ip_packet(void)
{
	unsigned int long_len;
	unsigned int short_len;
	StreamIPv4Header stIPHeader;
	StreamUDP stUDP;

	long_len = LONG_DATA;
	short_len = SHORT_DATA;
	
	g_short_data = (unsigned char*)osl_cachedma_malloc(short_len);
    if(g_short_data == NULL)
    {
        IPF_TEST_ERR("malloc failed :%d\n",__LINE__);
        return ERROR;
    }

	g_pu8STUlData = (unsigned char*)osl_cachedma_malloc(long_len);
    if(g_pu8STUlData == NULL)
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
	
	memset_s(g_short_data, short_len, T_UL_VALUE, short_len);
    memcpy_s(g_short_data, sizeof(StreamIPv4Header), &stIPHeader, sizeof(StreamIPv4Header));
    memcpy_s(g_short_data + sizeof(StreamIPv4Header), sizeof(StreamUDP), &stUDP, sizeof(StreamUDP));	

	stIPHeader.TOL = long_len;
	stUDP.Length = stIPHeader.TOL - sizeof(StreamIPv4Header);
	stIPHeader.Checksum = 0x3EDC;
	memset_s(g_pu8STUlData, long_len, T_UL_VALUE, long_len);
    memcpy_s(g_pu8STUlData, sizeof(StreamIPv4Header), &stIPHeader, sizeof(StreamIPv4Header));
    memcpy_s(g_pu8STUlData + sizeof(StreamIPv4Header), sizeof(StreamUDP), &stUDP, sizeof(StreamUDP));

	return IPF_SUCCESS;
}

int free_ul_ip_pkt(void)
{
	if(g_short_data != NULL)
	{
		osl_cachedma_free(g_short_data);
		g_short_data = NULL;
	}

	if(g_pu8STUlData != NULL)
	{
		osl_cachedma_free(g_pu8STUlData);
		g_pu8STUlData = NULL;
	}

	ip_packet_flag = 0;

	return IPF_SUCCESS;
}


/*CH0为上行通道，故编到Ccore*/
void print_CH0_BUFFED_AD_Num()
{
	HI_IPF_CH0_ADQ0_STAT_T ad0_stat;
	HI_IPF_CH0_ADQ1_STAT_T ad1_stat;
	ad0_stat.u32 = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_STAT_OFFSET);
	ad1_stat.u32 = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_STAT_OFFSET);
	if((ad0_stat.bits.ul_adq0_buf_epty == 1)&&(ad0_stat.bits.ul_adq0_buf_full == 1))
	{
		IPF_TEST_PRINT("\r CH0_AD0_BUF_FLAG_ERROR.\n");
	}
	else if(ad0_stat.bits.ul_adq0_buf_full == 1)
	{
		IPF_TEST_PRINT("\r CH0_AD0_BUF_NUM 2,2 unused AD in AD_Buff.\n");
	}
	else if(ad0_stat.bits.ul_adq0_buf_epty == 1)
	{
		IPF_TEST_PRINT("\r CH0_AD0_BUF_NUM 0,0 unused AD in AD_Buff.\n");
	}
	else
	{
		IPF_TEST_PRINT("\r CH0_AD0_BUF_NUM 1,1 unused AD in AD_Buff.\n");
	}
	
	if((ad1_stat.bits.ul_adq1_buf_epty == 1)&&(ad1_stat.bits.ul_adq1_buf_full == 1))
	{
		IPF_TEST_PRINT("\r CH0_AD1_BUF_FLAG_ERROR.\n");
	}
	else if(ad1_stat.bits.ul_adq1_buf_full == 1)
	{
		IPF_TEST_PRINT("\r CH0_AD1_BUF_NUM 2,2 unused AD in AD_Buff.\n");
	}
	else if(ad1_stat.bits.ul_adq1_buf_epty == 1)
	{
		IPF_TEST_PRINT("\r CH0_AD1_BUF_NUM 0,0 unused AD in AD_Buff.\n");
	}
	else
	{
		IPF_TEST_PRINT("\r CH0_AD1_BUF_NUM 1,1 unused AD in AD_Buff.\n");
	}
	return;
}



int IpfUlIntSTCb(void)
{
    print_CH0_BUFFED_AD_Num();
    return OK;
}

int IpfUlIntCb101()
{    
	unsigned int j;
	unsigned int u32AD0Num;
	unsigned int u32AD1Num;
	unsigned int u32Num = IPF_ULRD_DESC_SIZE;
	int s32Ret = 0;
	unsigned char *origin_data =  NULL;
	
	IPF_RD_DESC_S stRd[IPF_ULRD_DESC_SIZE];
	IPF_TEST_PRINT("Enter IpfUlIntCb101  \n");
	mdrv_ipf_get_ulrd(&u32Num, stRd);
	IPF_TEST_PRINT("Data transfer Num:%d \n",u32Num);
	for(j = 0; j < u32Num; j++)
	{	
		if(stRd[j].u16PktLen == 1500) {
			s32Ret = CmpDMAData((unsigned int *)g_pu8STUlData, (unsigned int *)stRd[j].u32OutPtr, stRd[j].u16PktLen);
			origin_data = g_pu8STUlData;
		} else if(stRd[j].u16PktLen == 300) {
			s32Ret = CmpDMAData((unsigned int *)g_short_data, (unsigned int *)stRd[j].u32OutPtr, stRd[j].u16PktLen);
			origin_data = g_short_data;
		} else
		    IPF_TEST_PRINT("IPF:origin data is null!\n");
		/*数据比对*/
		if(0 != s32Ret)
		{
			IPF_TEST_ERR("Comp error \n");
			
		    IPF_TEST_PRINT("Origin data\n");
		    IPF_TEST_PRINT("===================================\n");
			IPF_TEST_PRINT("Origin data:%p\n", origin_data);
			ipf_print_hex_4width((unsigned int *)origin_data, stRd[j].u16PktLen);
			IPF_TEST_PRINT("===================================\n");
			
		    IPF_TEST_PRINT("stRd[%d].u32OutPtr\n",j);
			IPF_TEST_PRINT("===================================\n");
			IPF_TEST_PRINT("stRd[%d].u32OutPtr =%x\n",j,stRd[j].u32OutPtr);
			ipf_print_hex_4width((unsigned int *)stRd[j].u32OutPtr, stRd[j].u16PktLen);
			IPF_TEST_PRINT("===================================\n");
			
			g_u32UlError++;
			ipf_ul_confirm = ERROR;
		}			
	}

	print_CH0_BUFFED_AD_Num();
	mdrv_ipf_get_ulad_num(&u32AD0Num, &u32AD1Num);
	IPF_TEST_PRINT("\r cb101 AD0Num:%d AD1Num:%d \n",u32AD0Num,u32AD1Num);
	IPF_TEST_ERR("transfer success! \n");

    return OK;    
}
int IpfUlIntCb111(void)
{
	unsigned int j;
	unsigned int u32AD0Num;
	unsigned int u32AD1Num;
	unsigned int u32Num = IPF_DLRD_DESC_SIZE;
	IPF_RD_DESC_S stRd[IPF_DLRD_DESC_SIZE];
	
	mdrv_ipf_get_ulrd(&u32Num, stRd);

	IPF_TEST_PRINT("Data transfer Num:%d \n",u32Num);
	
	for(j = 0; j < u32Num; j++)
	{			
		/*过滤结果*/
		if(stRd[j].u16Result == 0x3f)
		{
			IPF_TEST_PRINT("stRd[%d].u16Result ERROR !value is 0x%x \n",j,stRd[j].u16Result);
			g_u32UlError++;
			ipf_ul_confirm = ERROR;
		}			
	}
	g_u32UlTotalBDNum += u32Num;

	mdrv_ipf_get_ulad_num(&u32AD0Num, &u32AD1Num);
	
	IPF_TEST_PRINT("Data transfer success! Num: %d \n AD0Num:%d AD1Num:%d \n",j,u32AD0Num,u32AD1Num);
	IPF_TEST_PRINT("Data transfer ERROR Num:%d \n",g_u32UlError);
	IPF_TEST_ERR("transfer success! \n");
    return OK;
}

int IPF_ST_UL_FlushAD(IPF_ADQ_EMPTY_E eAdqEmptyUl)
{
	int s32Ret;  
	if(CONFIG_AD != ipf_config_ad_flag)
	{
		return OK;
	}
	if(IPF_EMPTY_ADQ0 == eAdqEmptyUl)
	{
		s32Ret = mdrv_ipf_config_ulad(IPF_AD_0,IPF_ULAD0_DESC_SIZE - IPF_ADQ_RESERVE_NUM,&ADulshort[0]);
		if(s32Ret != IPF_SUCCESS)
		{
			IPF_TEST_ERR("TEST ERROR BSP_IPF_ConfigDlAd :%d s32ret = %x\n",__LINE__, s32Ret);
			return s32Ret;
		}
	}
	else if(IPF_EMPTY_ADQ1 == eAdqEmptyUl)
	{
		s32Ret = mdrv_ipf_config_ulad(IPF_AD_1,IPF_ULAD1_DESC_SIZE - IPF_ADQ_RESERVE_NUM,&ADullong[0]);

		if(s32Ret != IPF_SUCCESS)
		{
			IPF_TEST_ERR("TEST ERROR mdrv_ipf_config_ulad:%d s32ret = %x\n",__LINE__, s32Ret);
			return s32Ret;
		}
	}
	else
	{
		return ERROR;
	}
	return OK;
}

int IPF_ST_UL_FlushOneAD(unsigned int AD0Num, unsigned int AD1Num)
{
    int s32Ret;  
    if(CONFIG_AD !=  ipf_config_ad_flag)
    {
        return OK;
    }

    s32Ret = mdrv_ipf_config_ulad(IPF_AD_0,AD0Num,&ADulshort[0]);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("TEST ERROR BSP_IPF_ConfigDlAd :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_config_ulad(IPF_AD_1,AD1Num,&ADullong[0]);

	if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("TEST ERROR mdrv_ipf_config_ulad:%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }
	return OK;
}

int disable_ipf_limit_func(void)
{
	unsigned int reg_bak = 0;

	reg_bak = ipf_readl(ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
	ipf_writel(reg_bak | SECCTRL_BYPASS, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
	return 0;
}

int IPF_ST_INIT(void)
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
        IPF_TEST_ERR("mdrv_ipf_init failed :%d   s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }
    g_u32IpfStAllInit = 1;
    
    return OK;
}

int IPF_ST_UL_INIT(void)
{	
    IPF_CHL_CTRL_S stCtrl;
    static IPF_FILTER_CONFIG_S stUlFilterInfo[50];
    int s32Ret = 0;
    unsigned int i = 0;

	if (g_ipf_ul_init)
		return IPF_SUCCESS;

	if(!ccore_reset_ipf){
		s32Ret = bsp_ipf_srest();
		if(s32Ret != IPF_SUCCESS){
			IPF_TEST_ERR("bsp_ipf_srest failed :%d s32Ret = %x\n", __LINE__, s32Ret);
			return IPF_ERROR;
		}
		else{
			ccore_reset_ipf = 1;
		}
	}
	
	for(i=0; i < IPF_ULAD0_DESC_SIZE - IPF_ADQ_RESERVE_NUM; i++)
	{
		ADulshort[i].u32OutPtr0 = (unsigned int)osl_cachedma_malloc(404);
		ADulshort[i].u32OutPtr1 = ADulshort[i].u32OutPtr0;
		if((unsigned int)NULL == ADulshort[i].u32OutPtr0)
		{
			IPF_TEST_ERR("osl_cachedma_malloc failed :%d\n",__LINE__);
			return ERROR;
		}
	}
	for(i=0; i < IPF_ULAD1_DESC_SIZE - IPF_ADQ_RESERVE_NUM; i++)
	{
		ADullong[i].u32OutPtr0 = (unsigned int)osl_cachedma_malloc(1500);
		ADullong[i].u32OutPtr1 = ADullong[i].u32OutPtr0;
		if((unsigned int)NULL == ADullong[i].u32OutPtr0)
		{
			IPF_TEST_ERR("osl_cachedma_malloc failed :%d\n",__LINE__);
			goto error1;
		}
	}
	
    s32Ret = mdrv_ipf_config_ulad(IPF_AD_0,IPF_ULAD0_DESC_SIZE - IPF_ADQ_RESERVE_NUM,&ADulshort[0]);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("mdrv_ipf_config_ulad failed :%d s32Ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }    

    s32Ret = mdrv_ipf_config_ulad(IPF_AD_1,IPF_ULAD1_DESC_SIZE - IPF_ADQ_RESERVE_NUM,&ADullong[0]);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("mdrv_ipf_config_ulad failed :%d s32Ret = %x\n",__LINE__, s32Ret);
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

    if(g_u32IpfStAllInit != 1)
    {
        s32Ret = IPF_ST_INIT();
        if(s32Ret != OK)
        {
            IPF_TEST_PRINT("IPF_ST_INIT failed :%d\n",__LINE__);
            return s32Ret;
        }
    }

    stCtrl.bDataChain = 0;
    stCtrl.bEndian = 1; /* 小端 */
    stCtrl.eIpfMode = IPF_MODE_FILTERANDTRANS;
    stCtrl.u32WrrValue = 0;
    s32Ret = mdrv_ipf_config_ulchan(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("mdrv_ipf_config_ulchan failed :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, stUlFilterInfo, 25);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR("mdrv_ipf_set_filter failed :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }
	
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM1_ULFC, stUlFilterInfo, 25);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR("mdrv_ipf_set_filter failed :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_enable_chan(IPF_CHANNEL_UP, 1);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("mdrv_ipf_enable_chan failed :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }
	
	g_ipf_ul_init = 1;
	
    return OK;
	
error1:
	IPF_TEST_ERR("IPF_ST_UL_INIT ERROR1");
	do
	{
		i--;
		osl_cachedma_free((void *)ADulshort[i].u32OutPtr0);
	}while(i);
	
	return s32Ret;
}

int IPF_ST_DL_INIT(void)
{
    IPF_CHL_CTRL_S stCtrl;
    static IPF_FILTER_CONFIG_S stDlFilterInfo[50];
    int s32Ret = 0;
    unsigned int i = 0;

	if (g_ipf_dl_init)
		return OK;
	
    ipf_ipv4_head.Vers = 4;
    ipf_ipv4_head.HeaderLen = 5;
    ipf_ipv4_head.TOS = 3;
    ipf_ipv4_head.TOL = 1200;
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

    if(g_u32IpfStAllInit != 1)
    {
        s32Ret = IPF_ST_INIT();
        if(s32Ret != OK)
        {
            IPF_TEST_ERR("IPF_ST_INIT return failed :%d\n",__LINE__);
            return s32Ret;
        }
    }

    stCtrl.bDataChain = 1;
    stCtrl.bEndian = 1; /* 小端 */
    stCtrl.eIpfMode = IPF_MODE_FILTERONLY;
    stCtrl.u32WrrValue = 0;
    s32Ret = mdrv_ipf_config_dlchan(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("mdrv_ipf_config_dlchan return failed  :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_DLFC, stDlFilterInfo, 50);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR("mdrv_ipf_set_filter return failed :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_enable_chan(IPF_CHANNEL_DOWN, 1);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("mdrv_ipf_enable_chan return failed  :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }
	g_ipf_dl_init = 1;
	
    return OK;
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

int BSP_IPF_ST_000(void)
{
	return IPF_SUCCESS;
}
/* test mdrv_ipf_config_timeout */

int BSP_IPF_ST_config_timeout(void)
{
    unsigned int u32Timeout = 0;
    unsigned int u32OldTime = 0;
    int s32ret = 0;

    u32OldTime = ipf_readl(ipf_base_addr_ccore + HI_IPF_TIME_OUT_OFFSET);

    s32ret = mdrv_ipf_config_timeout(u32Timeout);
    if(s32ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_timeout return failed :%d\n",__LINE__);
        goto error;
    }

    u32Timeout = 1;
    s32ret = mdrv_ipf_config_timeout(u32Timeout);
    if(s32ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_timeout return failed :%d\n",__LINE__);
        goto error;
    }

    if(*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_TIME_OUT_OFFSET) != 0x10001)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_timeout return failed :%d\n",__LINE__);
        goto error;
    }

    u32Timeout = 0xffff;
    s32ret = mdrv_ipf_config_timeout(u32Timeout);
    if(s32ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_timeout return failed :%d\n",__LINE__);
        goto error;
    }
	
    if(*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_TIME_OUT_OFFSET) != 0x1ffff)
    {
        IPF_TEST_PRINT("ipf time out register value error :%d\n",__LINE__);
        goto error;
    }

    u32Timeout = 0x10000;
    s32ret = mdrv_ipf_config_timeout(u32Timeout);
    if(s32ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_timeout return failed:%d\n",__LINE__);
        goto error;
    }

    ipf_writel(u32OldTime, ipf_base_addr_ccore + HI_IPF_TIME_OUT_OFFSET);
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);
    return OK;
	
error:
    ipf_writel(u32OldTime, ipf_base_addr_ccore + HI_IPF_TIME_OUT_OFFSET);
    return ERROR;
}

int BSP_IPF_ST_set_pkt_len(void)
{
    int s32Ret;
    unsigned int u32MaxLen = 0;
    unsigned int u32MinLen = 0;

    s32Ret = mdrv_ipf_set_pktlen(u32MaxLen,u32MinLen);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_set_pktlen return failed:%d\n",__LINE__);
        return s32Ret;
    }

    u32MaxLen = 0x5;
    u32MinLen = 0x6;
    s32Ret = mdrv_ipf_set_pktlen(u32MaxLen,u32MinLen);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_PRINT("mdrv_ipf_set_pktlen return failed:%d\n",__LINE__);
        return s32Ret;
    }

    u32MaxLen = 0x345;
    u32MinLen = 0x123;
    s32Ret = mdrv_ipf_set_pktlen(u32MaxLen,u32MinLen);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_set_pktlen return failed:%d\n",__LINE__);
        return s32Ret;
    }
	
    if(*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_PKT_LEN_OFFSET) != 0x3450123)
    {
        IPF_TEST_PRINT("mdrv_ipf_set_pktlen return failed:%d\n",__LINE__);
        return ERROR;
    }

    u32MaxLen = 1500;
    u32MinLen = 40;
    s32Ret = mdrv_ipf_set_pktlen(u32MaxLen,u32MinLen);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_set_pktlen return failed :%d\n",__LINE__);
        return s32Ret;
    }
    
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);
    return OK;
}


int BSP_IPF_ST_AD_config_test(void)
{
#if 0
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
#endif
	return IPF_SUCCESS;
}


int BSP_IPF_ST_005(void)
{
    int s32Ret;
    unsigned int i;
	unsigned int ad_wptr = 0;
	IPF_AD_DESC_S *TempAD;
	for(i=0; i < IPF_ULAD0_DESC_SIZE; i++)
	{
    	ADulshort[i].u32OutPtr0 = (unsigned int)NULL;
		ADulshort[i].u32OutPtr0 = (unsigned int)osl_cachedma_malloc(404);
		ADulshort[i].u32OutPtr1 = ADulshort[i].u32OutPtr0;
		if((unsigned int)NULL == ADulshort[i].u32OutPtr0){
			IPF_TEST_ERR("IPF_ST_UL_INIT AD MEM malloc fail:%d\n",__LINE__);
			goto error1;
		}
	}
	
	for(i=0; i < IPF_ULAD1_DESC_SIZE; i++)
	{
    	ADullong[i].u32OutPtr0 = (unsigned int)NULL;
		ADullong[i].u32OutPtr0 = (unsigned int)osl_cachedma_malloc(1500);
		ADullong[i].u32OutPtr1 = ADulshort[i].u32OutPtr0;
		if((unsigned int)NULL == ADullong[i].u32OutPtr0){
			IPF_TEST_ERR("IPF_ST_UL_INIT AD MEM malloc fail:%d\n",__LINE__);
			goto error2;
		}
	}
	
	ad_wptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_WPTR_OFFSET);
	ad_wptr &= AD_WPTR_MASK;
    s32Ret = mdrv_ipf_config_ulad(IPF_AD_0,IPF_ULAD0_DESC_SIZE-IPF_ADQ_RESERVE_NUM,&ADulshort[0]);
    if(s32Ret != IPF_SUCCESS){
        IPF_TEST_ERR("mdrv_ipf_config_ulad return failed:%d\n",__LINE__);
        return s32Ret;
    }
	
	TempAD = (IPF_AD_DESC_S*)(IPF_ULAD0_MEM_ADDR);
	for(i=0; i <IPF_ULAD0_DESC_SIZE-IPF_ADQ_RESERVE_NUM;i++)
	{

		if( ADulshort[i].u32OutPtr0 != TempAD[ad_wptr].u32OutPtr0){
			IPF_TEST_ERR("Long AD compare err!\t");
			IPF_TEST_ERR("AD num:%#X MEM:%#X\t",i,ADulshort[i].u32OutPtr0);
			IPF_TEST_ERR("AD %#X\n", TempAD[ad_wptr].u32OutPtr0);
		}
		ad_wptr = ((ad_wptr + 1) < IPF_DLAD0_DESC_SIZE)? (ad_wptr + 1) : 0;
	}
	
	ad_wptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_WPTR_OFFSET);
	ad_wptr &= AD_WPTR_MASK;
    s32Ret = mdrv_ipf_config_ulad(IPF_AD_1,IPF_ULAD1_DESC_SIZE-IPF_ADQ_RESERVE_NUM,&ADullong[0]);
    if(s32Ret != IPF_SUCCESS) {
        IPF_TEST_ERR("mdrv_ipf_config_ulad return failed:%d\n",__LINE__);
        return s32Ret;
    }
	
	TempAD = (IPF_AD_DESC_S*)(IPF_ULAD1_MEM_ADDR);
	for(i=0; i < IPF_ULAD1_DESC_SIZE-IPF_ADQ_RESERVE_NUM;i++)
	{		
		if(ADullong[i].u32OutPtr0 != TempAD[ad_wptr].u32OutPtr0){
			IPF_TEST_ERR("Long AD compare err!\t");
			IPF_TEST_ERR("AD num:%#X MEM:%#X\t",i,ADullong[i].u32OutPtr0);
			IPF_TEST_ERR("AD %#X\n", TempAD[ad_wptr].u32OutPtr0);
		}
		ad_wptr = ((ad_wptr + 1) < IPF_DLAD1_DESC_SIZE)? (ad_wptr + 1) : 0;
	}

    s32Ret = mdrv_ipf_config_ulad(IPF_AD_0,IPF_ULAD0_DESC_SIZE, &ADulshort[0]);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_ERR("mdrv_ipf_config_ulad return failed:%d\n",__LINE__);
        return s32Ret;
    }
	
    s32Ret = mdrv_ipf_config_ulad(IPF_AD_1,IPF_ULAD1_DESC_SIZE, &ADullong[0]);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA){
        IPF_TEST_ERR("mdrv_ipf_config_ulad return failed:%d\n",__LINE__);
        return s32Ret;
    }
	
    s32Ret = mdrv_ipf_config_ulad(IPF_AD_0,1,NULL);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_ERR("mdrv_ipf_config_ulad return failed:%d\n",__LINE__);
        return s32Ret;
    }
	
    s32Ret = mdrv_ipf_config_ulad(IPF_AD_1,1,NULL);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA){
        IPF_TEST_ERR("mdrv_ipf_config_ulad return failed:%d\n",__LINE__);
        return s32Ret;
    }
		
    s32Ret = mdrv_ipf_config_ulad(IPF_AD_0,0,&ADulshort[0]);
    if(s32Ret != IPF_SUCCESS){
        IPF_TEST_ERR("mdrv_ipf_config_ulad return failed:%d\n",__LINE__);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_config_ulad(IPF_AD_1,0,&ADullong[0]);
    if(s32Ret != IPF_SUCCESS){
        IPF_TEST_ERR("mdrv_ipf_config_ulad return failed:%d\n",__LINE__);
        return s32Ret;
    }
	
	for(i=0; i < IPF_ULAD0_DESC_SIZE; i++)
		osl_cachedma_free((unsigned int *)ADulshort[i].u32OutPtr0);

	for(i=0; i < IPF_ULAD1_DESC_SIZE; i++)
		osl_cachedma_free((unsigned int *)ADullong[i].u32OutPtr0);

    IPF_TEST_PRINT("BSP_IPF_ST_005 SUCCESS");
    return OK;

error1:
	do
	{
		i--;
		osl_cachedma_free((unsigned int *)ADulshort[i].u32OutPtr0);
	}while(i);
	return ERROR;
error2:
	do
	{
		i--;
		osl_cachedma_free((unsigned int *)ADullong[i].u32OutPtr0);
	}while(i);
	
	for(i=0; i < IPF_ULAD0_DESC_SIZE - IPF_ADQ_RESERVE_NUM; i++){
		osl_cachedma_free((unsigned int *)ADulshort[i].u32OutPtr0);
	}
	return ERROR;

    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);
}

int BSP_IPF_ST_ULAD(void)
{    
	unsigned int* u32AD0Num = NULL;
	unsigned int* u32AD1Num = NULL;
	int s32Ret = 0;
	s32Ret = mdrv_ipf_get_ulad_num(u32AD0Num, u32AD1Num);
	if(IPF_SUCCESS != s32Ret)
	{
  		  IPF_TEST_ERR("mdrv_ipf_get_ulad_num faild \n");
	}
    IPF_TEST_PRINT("mdrv_ipf_get_ulad_num AD0 = %d,AD1 = %d \n",u32AD0Num, u32AD1Num);
	return s32Ret;
}

/****************************
***1xx UL init test*****
*****************************/
/*接收准备*/
int BSP_IPF_ST_100_INIT(void)
{
    unsigned int u32Timeout = 100;
    int s32Ret = 0;
    unsigned int u32AD0Num = 0;
    unsigned int u32AD1Num = 0;

	if(!ip_packet_flag){
		s32Ret = get_ip_packet();

		if(s32Ret != OK){
			IPF_TEST_ERR("ipf get packet failed!\n");
	        return s32Ret;						
		}
		ip_packet_flag = 1;
	}

    s32Ret = IPF_ST_UL_INIT();

    if(s32Ret != OK)
    {
    	IPF_TEST_ERR(" init error :%d\n",__LINE__);
        return s32Ret;
    }
	
 	mdrv_ipf_get_ulad_num(&u32AD0Num, &u32AD1Num);
	if(IPF_SUCCESS != s32Ret)
	{
  		  IPF_TEST_ERR("mdrv_ipf_get_ulad_num faild :%d \n", __LINE__);
	}
	
  	IPF_TEST_PRINT("mdrv_ipf_get_ulad_num AD0 = %d,AD1 = %d \n",u32AD0Num, u32AD1Num);
    s32Ret = mdrv_ipf_config_timeout(u32Timeout);
    if(s32Ret != OK)
    {
        IPF_TEST_ERR("mdrv_ipf_config_timeout return failed:%d\n",__LINE__);
        return s32Ret;
    }
    s32Ret = ipf_register_wakeup_ulcb(IpfUlIntCb101);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("ipf_register_wakeup_ulcb return failed:%d\n",__LINE__);
        return s32Ret;
    }
	
    s32Ret = ipf_register_adq_empty_ulcb(IPF_ST_UL_FlushAD);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("ipf_register_adq_empty_ulcb return failed:%d\n",__LINE__);
        return s32Ret;
    }
	
    IPF_TEST_ERR("dl acore init ok!\n");

    return OK;
}

int BSP_IPF_ST_101_INIT(void)
{
    return BSP_IPF_ST_100_INIT();
}

int BSP_IPF_ST_102_INIT(void)
{
    return BSP_IPF_ST_100_INIT();
}

int BSP_IPF_ST_103_INIT(void)
{
    int s32Ret = 0;

    if(!ip_packet_flag){
		s32Ret = get_ip_packet();

		if(s32Ret != OK){
			IPF_TEST_ERR("ipf get packet failed!\n");
	        return s32Ret;						
		}
		ip_packet_flag = 1;
	}
	
    s32Ret = IPF_ST_UL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR("IPF_ST_UL_INIT return failed:%d\n",__LINE__);
        return s32Ret;
    }

    s32Ret = ipf_register_wakeup_ulcb(IpfUlIntCb101);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("ipf_register_wakeup_ulcb return failed:%d\n",__LINE__);
        return s32Ret;
    }
        s32Ret = ipf_register_adq_empty_ulcb(IPF_ST_UL_FlushAD);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("ipf_register_adq_empty_ulcb return failed:%d\n",__LINE__);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_config_timeout(0xFFFF);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("mdrv_ipf_config_timeout return failed:%d\n",__LINE__);
        return s32Ret;
    }

    IPF_TEST_PRINT(" Acore cloud start ul cases\n");


    s32Ret = mdrv_ipf_config_timeout(500);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("mdrv_ipf_config_timeout return failed:%d\n",__LINE__);
        return s32Ret;
    }
    IPF_TEST_ERR("dl acore init ok!\n");
	
    return OK;
}

int BSP_IPF_ST_111_INIT(void)
{
    int s32Ret = 0;
   
    s32Ret = IPF_ST_UL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR("IPF_ST_UL_INIT return failed:%d\n",__LINE__);
        return s32Ret;
    }

    s32Ret = ipf_register_wakeup_ulcb(IpfUlIntCb111);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("ipf_register_wakeup_ulcb return failed:%d\n",__LINE__);
        return s32Ret;
    }    
    s32Ret = ipf_register_adq_empty_ulcb(IPF_ST_UL_FlushAD);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("ipf_register_adq_empty_ulcb return failed:%d\n",__LINE__);
        return s32Ret;
    }

    IPF_TEST_ERR("dl acore init ok!\n");
    return OK;
}

int BSP_IPF_ST_112_INIT(void)
{
    int s32Ret = 0;
	
    s32Ret = IPF_ST_UL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR("IPF_ST_UL_INIT return failed:%d\n",__LINE__);
        return s32Ret;
    }

    s32Ret = ipf_register_wakeup_ulcb(IpfUlIntCb111);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("ipf_register_wakeup_ulcb return failed:%d\n",__LINE__);
        return s32Ret;
    }    
    s32Ret = ipf_register_adq_empty_ulcb(IPF_ST_UL_FlushAD);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("ipf_register_adq_empty_ulcb return failed:%d\n",__LINE__);
        return s32Ret;
    }

    IPF_TEST_ERR("dl acore init ok!\n");
    return OK;
}

int BSP_IPF_ST_113_INIT(void)
{
    int s32Ret = 0;
   
    s32Ret = IPF_ST_UL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR("IPF_ST_UL_INIT return failed:%d\n",__LINE__);
        return s32Ret;
    }

    s32Ret = ipf_register_wakeup_ulcb(IpfUlIntCb111);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("ipf_register_wakeup_ulcb return failed:%d\n",__LINE__);
        return s32Ret;
    }    
    s32Ret = ipf_register_adq_empty_ulcb(IPF_ST_UL_FlushAD);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("ipf_register_adq_empty_ulcb return failed:%d\n",__LINE__);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_config_timeout(0xFFFF);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("mdrv_ipf_config_timeout return failed:%d\n",__LINE__);
        return s32Ret;
    }
    IPF_TEST_ERR("dl acore init ok!\n");
    return OK;
}

int bsp_ipf_ul_confirm(void)
{	
	int tmp = 0;
	tmp = ipf_ul_confirm;
	ipf_ul_confirm = 0;
	
	return tmp;
}

int IpfUltestIntCb(void)
{
    unsigned int u32Num = IPF_ULRD_DESC_SIZE;
    IPF_RD_DESC_S stRd[IPF_ULRD_DESC_SIZE];
    unsigned int u32RecivedData = 0;
    unsigned int u32AD0Num = 0;
    unsigned int u32AD1Num = 0;
    unsigned int i = 0;
    int s32Ret = 0;

    /*处理RD*/
    mdrv_ipf_get_ulrd(&u32Num, stRd);
    for(i = 0; i < u32Num; i++)
    {
        s32Ret = CmpDMAData((unsigned int *)g_pu8STUlData, (unsigned int *)stRd[i].u32OutPtr, stRd[i].u16PktLen);
        /*数据比对*/
        if(!s32Ret)
        {
            g_u32UlError++;
        }
        if(stRd[i].u16Result == 0x3f)
        {
            g_u32UlFltError++;
        }
		u32RecivedData += stRd[i].u16PktLen;
    }

    /*统计结果*/
    g_u32UlTotalDataNum += u32RecivedData/1024;
    g_u32UlTotalBDNum += u32Num;
    s32Ret = mdrv_ipf_get_ulad_num(&u32AD0Num,&u32AD1Num);
    if(IPF_SUCCESS != s32Ret)
    {
        IPF_TEST_ERR("mdrv_ipf_get_ulad_num return failed :%d\n",__LINE__);
        return s32Ret;
    }
    if(u32AD0Num > 10)
    {
        s32Ret = mdrv_ipf_config_ulad(IPF_AD_0,u32AD0Num,&ADulshort[0]);
        if(IPF_SUCCESS != s32Ret)
        {
            IPF_TEST_ERR("mdrv_ipf_config_ulad0 return failed:%d\n",__LINE__);
        }
        for(i=0;i < u32AD0Num;i++)
        {
            memset_s((void *)ADulshort[i].u32OutPtr1, 404, 0, 404);
        }
    }
    if(u32AD1Num > 10)
    {
        s32Ret = mdrv_ipf_config_ulad(IPF_AD_1,u32AD1Num,&ADullong[0]);
        if(IPF_SUCCESS != s32Ret)
        {
            IPF_TEST_ERR("mdrv_ipf_config_ulad return failed:%d\n",__LINE__);
        }
        for(i=0;i < u32AD1Num;i++)
        {
            memset_s((void *)ADullong[i].u32OutPtr1, 1500, 0, 1500);
        }

    }
    return OK;
}

int IpfUltestIntCb122(void)
{
    unsigned int u32Num = IPF_ULRD_DESC_SIZE;
    IPF_RD_DESC_S stRd[IPF_ULRD_DESC_SIZE];
    unsigned int u32RecivedData = 0;
    unsigned int i = 0;
    int s32Ret = 0;

    /*处理RD*/
    mdrv_ipf_get_ulrd(&u32Num, stRd);
    for(i = 0; i < u32Num; i++)
    {
        s32Ret = CmpDMAData((unsigned int *)g_pu8STUlData, (unsigned int *)stRd[i].u32OutPtr, stRd[i].u16PktLen);
        /*数据比对*/
        if(!s32Ret)
        {
            g_u32UlError++;
        }
        if(stRd[i].u16Result == 0x3f)
        {
            g_u32UlFltError++;
        }
	u32RecivedData += stRd[i].u16PktLen;
    }

    /*统计结果*/
    g_u32UlTotalDataNum += u32RecivedData/1024;
    g_u32UlTotalBDNum += u32Num;
    return OK;
}


void BSP_IPF_ST_121_Result(void)
{
		IPF_TEST_PRINT(" g_u32UlError(BDs) :%d\n",g_u32UlError);
		IPF_TEST_PRINT(" g_u32UlFltError(BDs) :%d\n",g_u32UlFltError);
		IPF_TEST_PRINT(" g_u32UlTotalDataNum(KB) :%d\n",g_u32UlTotalDataNum);
		IPF_TEST_PRINT(" g_u32UlTotalBDNum(BDs) :%d\n",g_u32UlTotalBDNum);
}

void BSP_IPF_ST_122_Result(void)
{
	BSP_IPF_ST_121_Result();
}

/*上行压力测试C核准备函数*/
int BSP_IPF_ST_121_INIT(void)
{
    int s32Ret = 0;
    unsigned short u16Len = 1500;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
	
    g_pu8STUlData = (unsigned char*)osl_cachedma_malloc(u16Len);
    if(g_pu8STUlData == NULL)
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
    memset_s(g_pu8STUlData, u16Len, T_UL_VALUE, u16Len);
    memcpy_s(g_pu8STUlData, sizeof(StreamIPv4Header), &stIPHeader, sizeof(StreamIPv4Header));
    memcpy_s(g_pu8STUlData+sizeof(StreamIPv4Header), sizeof(StreamUDP), &stUDP, sizeof(StreamUDP));

	ipf_set_ccore_reset_flag(1);
    s32Ret = IPF_ST_UL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_UL_INIT :%d\n",__LINE__);
        return s32Ret;
    }

    s32Ret = ipf_register_wakeup_ulcb(IpfUltestIntCb);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    ipf_register_wakeup_ulcb :%d\n",__LINE__);
        return s32Ret;
    }    
    s32Ret = ipf_register_adq_empty_ulcb(IPF_ST_UL_FlushAD);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    ipf_register_adq_empty_ulcb :%d\n",__LINE__);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_config_timeout(0x65);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_timeout :%d\n",__LINE__);
        return s32Ret;
    }
    IPF_TEST_ERR("dl acore init ok!\n");
    return OK;
}

/*上行压力测试C核准备函数*/
int BSP_IPF_ST_122_INIT(void)
{

    int s32Ret = 0;
	
    s32Ret = ipf_register_wakeup_ulcb(IpfUltestIntCb122);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    ipf_register_wakeup_ulcb :%d\n",__LINE__);
        return s32Ret;
    }
    s32Ret = BSP_IPF_ST_121_INIT();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    BSP_IPF_ST_121_INIT :%d\n",__LINE__);
        return s32Ret;
    }    

    return IPF_SUCCESS;
}

int CmpFilterInfo(IPF_FILTER_CONFIG_S* p1, IPF_FILTER_CONFIG_S* p2)
{
    unsigned int i = 0;
    IPF_MATCH_INFO_S * p1t = (IPF_MATCH_INFO_S *)(&(p1->stMatchInfo));
    IPF_MATCH_INFO_S * p2t = (IPF_MATCH_INFO_S *)(&(p2->stMatchInfo));
    unsigned int *u32p1 = (unsigned int *)p1t;
    unsigned int *u32p2 = (unsigned int *)p2t;
    unsigned int u32Len = 0; 
    u32Len = sizeof(IPF_MATCH_INFO_S);
    u32Len = u32Len/4;

    /*过滤器配置信息里不包括下一个过滤器域，
    该域由底软动态分配，故比较时屏蔽该域*/
    (p2t->unFltChain).Bits.u16NextIndex = (p1t->unFltChain).Bits.u16NextIndex;
	
    for(i=0; i<u32Len; i++)
    {
        if(*(u32p1 + i) != *(u32p2 + i))
        {
            return ERROR;
        }
    }
    return 0;
}
int CmpMatchInfo(IPF_MATCH_INFO_S * p1t,IPF_MATCH_INFO_S * p2t)
{
    unsigned int i = 0;
    unsigned int *u32p1 = (unsigned int *)p1t;
    unsigned int *u32p2 = (unsigned int *)p2t;
    unsigned int u32Len = 0; 
    u32Len = sizeof(IPF_MATCH_INFO_S);
    u32Len = u32Len/4;
	
    for(i=0; i<u32Len; i++)
    {
        if(*(u32p1 + i) != *(u32p2 + i))
        {
            return ERROR;
        }
    }
    return 0;
}

void PrintFilterInfo(IPF_FILTER_CONFIG_S* pu32FilterInfo)
{
    unsigned int i = 0;
    unsigned int* p;
	
    unsigned int u32Len = sizeof(IPF_MATCH_INFO_S);
    p = (unsigned int *)(&(pu32FilterInfo->stMatchInfo));
    u32Len = u32Len/4;
	
    IPF_TEST_PRINT("0x%08x\n",pu32FilterInfo->u32FilterID);
    for(i=0; i < u32Len; i++)
    {
        IPF_TEST_PRINT("0x%08x    ", *(p+i));
        if((i%4) == 0)
        {
            IPF_TEST_PRINT("\n");
        }
    }
    IPF_TEST_PRINT("\n");
}

void PrintMatchInfo(IPF_MATCH_INFO_S * pu32MatchInfo)
{
    unsigned int i = 0;
    unsigned int* p;
	
    unsigned int u32Len = sizeof(IPF_MATCH_INFO_S);
    p = (unsigned int *)(pu32MatchInfo);
    u32Len = u32Len/4;
	
    for(i=0; i < u32Len; i++)
    {
        IPF_TEST_PRINT("0x%08x    ", *(p+i));
        if((i%4) == 0)
        {
            IPF_TEST_PRINT("\n");
        }
    }
    IPF_TEST_PRINT("\n");
}
int check_filter_backup_status(void)
{
    int ret;
    unsigned int i,j,k,filter_serial;
    IPF_MATCH_INFO_S* hard_filter_info;
    unsigned int *hard_filter_info_addr;
    IPF_MATCH_INFO_S* backup_filter_info;
    unsigned int* backup_info_addr = NULL;
    hard_filter_info = (IPF_MATCH_INFO_S*)osl_cachedma_malloc(sizeof(IPF_MATCH_INFO_S));
    if(NULL == hard_filter_info)
    {
        IPF_TEST_ERR( "\r pstMatchInfo malloc ERROR! \n");
        return IPF_ERROR;
    }
    hard_filter_info_addr = (unsigned int*)hard_filter_info;

    for(i=0 ; i < IPF_MODEM_MAX; i++)
    {
        backup_info_addr = (unsigned int *)(IPF_PWRCTL_BASIC_FILTER_ADDR + i*sizeof(IPF_MATCH_INFO_S));
        backup_filter_info = (IPF_MATCH_INFO_S*)backup_info_addr;
        filter_serial = i;
        k = 0;
        do
        {
            if(filter_serial < IPF_BF_NUM)
            {
                ipf_writel(filter_serial, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET); 
                for(j=0; j<(sizeof(IPF_MATCH_INFO_S)/4); j++)
                {
                    *hard_filter_info_addr = ipf_readl((ipf_base_addr_ccore+HI_FLT_LOCAL_ADDR0_OFFSET+j*4)); 
                    hard_filter_info_addr++;
                }
                k++;
                ret = CmpMatchInfo(backup_filter_info, hard_filter_info);
                if(ret != 0)
                {
                    IPF_TEST_PRINT("chainNum = %d \n",i);
                    IPF_TEST_PRINT("filterNum = %d \n",filter_serial);
                    IPF_TEST_PRINT("========BACKUPED_FILTER_INFO=======\n");
                    PrintMatchInfo(backup_filter_info);
                    IPF_TEST_PRINT("========FILTER_ACTUAL_INFO=======\n");
                    PrintMatchInfo(hard_filter_info);
                }
            	hard_filter_info_addr = (unsigned int*)hard_filter_info;
            }
            filter_serial = backup_filter_info->unFltChain.Bits.u16NextIndex;
            backup_filter_info = (IPF_MATCH_INFO_S*)(IPF_PWRCTL_BASIC_FILTER_ADDR + filter_serial*sizeof(IPF_MATCH_INFO_S));
            backup_info_addr = (unsigned int *)backup_filter_info;
            if(k >= IPF_BF_NUM)
            {
                IPF_TEST_ERR("Filter end error!\n");
                return IPF_ERROR;
            }
        }while(filter_serial != IPF_TAIL_INDEX);
    }

	osl_cachedma_free(hard_filter_info);
	return IPF_SUCCESS;
}

int check_filter_zero_status(IPF_FILTER_CHAIN_TYPE_E filter_serial)
{
    ipf_writel(filter_serial, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET); 

    if((IPF_TAIL_INDEX == ipf_readl( ipf_base_addr_ccore + HI_FLT_CHAIN_OFFSET))
		&(0 == ipf_readl(ipf_base_addr_ccore + HI_FLT_RULE_CTRL_OFFSET)))
    {
		IPF_TEST_PRINT(" empty list next index error\n");
		return IPF_ERROR;
    }
    return IPF_SUCCESS;
}

/* test mdrv_ipf_init */
int BSP_IPF_ST_201(void)
{
    int s32Ret;
    unsigned int u32OldPara = 0;
    IPF_COMMON_PARA_S stCommPara;

    u32OldPara = ipf_readl(ipf_base_addr_ccore + HI_IPF_CTRL_OFFSET); 
    s32Ret = mdrv_ipf_init(NULL);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_PRINT("mdrv_ipf_init return failed :%d\n",__LINE__);
        goto error;
    }

    stCommPara.bAdReport = 1; /*上报数据指针*/
    stCommPara.bMultiFilterChainEn = 0;/*多寄存器链模式*/
    stCommPara.bMultiModeEn = 0;/*动态业务模式*/
    stCommPara.bEspSpiDisable = 1;
    stCommPara.bAhSpiDisable = 1;
    stCommPara.bEspAhSel = 1;
    stCommPara.bIpv6NextHdSel = 1;
    stCommPara.eMaxBurst = IPF_BURST_8;
    stCommPara.bSpWrrModeSel = 1;
    stCommPara.bSpPriSel = 1;
    stCommPara.bFltAddrReverse = 1;
    stCommPara.bFilterSeq = 1;       

    s32Ret = mdrv_ipf_init(&stCommPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT(" TESTERROR    mdrv_ipf_init2 :%d\n",__LINE__);
        goto error;
    }

    if(*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CTRL_OFFSET)!=(g_ipf_ctx.ipf_version >= IPF_VERSION_120a? 0x73df:0x33DF))
    {
        IPF_TEST_PRINT(" TESTERROR    mdrv_ipf_init3 :%d  %x\n",__LINE__,*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CTRL_OFFSET));
        goto error;
    }

    stCommPara.bEspSpiDisable = 0;
    stCommPara.bAhSpiDisable = 0;
    stCommPara.bEspAhSel = 0;
    stCommPara.bIpv6NextHdSel = 0;
    stCommPara.eMaxBurst = IPF_BURST_4;
    stCommPara.bSpWrrModeSel = 0;
    stCommPara.bSpPriSel = 0;
    stCommPara.bFltAddrReverse = 0;
    stCommPara.bFilterSeq = 0;       
    stCommPara.bAdReport = 0; /*上报数据指针*/
    stCommPara.bMultiFilterChainEn = 1;/*多寄存器链模式*/
    stCommPara.bMultiModeEn = 1;/*动态业务模式*/

    s32Ret = mdrv_ipf_init(&stCommPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_init return failed :%d\n",__LINE__);
        goto error;
    }	
    if(*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CTRL_OFFSET)!=(g_ipf_ctx.ipf_version >= IPF_VERSION_120a? 0x6c20:0x2c20))
    {
        IPF_TEST_PRINT("mdrv_ipf_init return failed :%d %x\n",__LINE__,*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CTRL_OFFSET));
       	goto error;
    }

    ipf_writel(u32OldPara, ipf_base_addr_ccore + HI_IPF_CTRL_OFFSET); 
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);    
    return OK;
error:
    ipf_writel(u32OldPara, ipf_base_addr_ccore + HI_IPF_CTRL_OFFSET); 
    return ERROR;
}

int BSP_IPF_ST_202(void)
{
    int s32Ret;
    unsigned int u32OldPara = 0;
    IPF_CHL_CTRL_S stCtrl;

    u32OldPara = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET); 
    
    s32Ret = mdrv_ipf_config_ulchan(NULL);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_ulchan return failed:%d\n",__LINE__);
        goto error;
    }

    stCtrl.bDataChain = 1;
    stCtrl.bEndian = 1;
    stCtrl.eIpfMode = IPF_MODE_FILTERONLY;
    stCtrl.u32WrrValue = 1000;
    s32Ret = mdrv_ipf_config_ulchan(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_ulchan return failed:%d\n",__LINE__);
        goto error;
    }
	
    if(*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CH0_CTRL_OFFSET) != 0x3E8000D)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_ulchan return failed:%d\n",__LINE__);
        goto error;
    }

    stCtrl.bDataChain = 0;
    stCtrl.bEndian = 0;
    stCtrl.eIpfMode = IPF_MODE_FILTERANDTRANS;
    stCtrl.u32WrrValue = 100;
    s32Ret = mdrv_ipf_config_ulchan(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_ulchan return failed:%d\n",__LINE__);
        goto error;
    }

	
    if(*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CH0_CTRL_OFFSET) != 0x640000)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_ulchan return failed:%d\n",__LINE__);
        goto error;
    }

    ipf_writel(u32OldPara, ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET); 
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);    
    return OK;
error:
    ipf_writel(u32OldPara, ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET); 
    return ERROR;
}

/* test mdrv_ipf_config_dlchan */
int BSP_IPF_ST_203(void)
{
    int s32Ret;
    unsigned int u32OldPara = 0;
    IPF_CHL_CTRL_S stCtrl;

    u32OldPara = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET); 
    
    s32Ret = mdrv_ipf_config_dlchan(NULL);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_dlchan reutrn failed:%d\n",__LINE__);
        goto error;
    }

    stCtrl.bDataChain = 1;
    stCtrl.bEndian = 1;
    stCtrl.eIpfMode = IPF_MODE_FILTERONLY;
    stCtrl.u32WrrValue = 1000;
    s32Ret = mdrv_ipf_config_dlchan(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_dlchan  reutrn failed:%d\n",__LINE__);
        goto error;
    }

    if(*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CH1_CTRL_OFFSET) != 0x3E8000D)
    {
        IPF_TEST_PRINT("ch1 ctrl offset addr error :%d\n",__LINE__);
        goto error;
    }

    stCtrl.bDataChain = 0;
    stCtrl.bEndian = 0;
    stCtrl.eIpfMode = IPF_MODE_FILTERANDTRANS;
    stCtrl.u32WrrValue = 100;
    s32Ret = mdrv_ipf_config_dlchan(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_config_dlchan return failed :%d\n",__LINE__);
        goto error;
    }
	
	
    if(*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CH1_CTRL_OFFSET) != 0x640000)
    {
        IPF_TEST_PRINT("ch1 ctrl offset addr error :%d\n",__LINE__);
        goto error;
    }

    ipf_writel(u32OldPara, ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET); 
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);    
    return OK;
	
error:
    ipf_writel(u32OldPara, ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET); 
    return ERROR;
}

/* test mdrv_ipf_enable_chan */
int BSP_IPF_ST_204(void)
{
    IPF_CHANNEL_TYPE_E eChanType = IPF_CHANNEL_MAX;
    int bFlag = 0;
    unsigned int u32OldPara = 0;
    int s32Ret;
	unsigned int old_gate_v = 0;

    u32OldPara = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH_EN_OFFSET); 

	//To be sure disable DL channel
	old_gate_v = ipf_readl(ipf_base_addr_ccore + HI_IPF_GATE_OFFSET);
	ipf_writel(0, ipf_base_addr_ccore + HI_IPF_GATE_OFFSET);
	
    s32Ret = mdrv_ipf_enable_chan(eChanType, bFlag);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_PRINT("mdrv_ipf_enable_chan :%d\n",__LINE__);
        goto error;
    }

    /* test  IPF_CHANNEL_UP */
    eChanType = IPF_CHANNEL_UP;
    bFlag = 1;
    s32Ret = mdrv_ipf_enable_chan(eChanType, bFlag);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_enable_chan :%d\n",__LINE__);
        goto error;
    }
    if((*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CH_EN_OFFSET) & 0x1) != 0x1)
    {
        IPF_TEST_PRINT("mdrv_ipf_enable_chan :%d\n",__LINE__);
        goto error;
    }
    bFlag = 0;
    s32Ret = mdrv_ipf_enable_chan(eChanType, bFlag);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_enable_chan :%d\n",__LINE__);
        goto error;
    }
    if((*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CH_EN_OFFSET) & 0x1) != 0x0)
    {
        IPF_TEST_PRINT("mdrv_ipf_enable_chan :%d\n",__LINE__);
        goto error;
    }

    /* test  IPF_CHANNEL_DOWN */
    eChanType = IPF_CHANNEL_DOWN;
    bFlag = 1;
    s32Ret = mdrv_ipf_enable_chan(eChanType, bFlag);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_enable_chan :%d\n",__LINE__);
        goto error;
    }
    if((*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CH_EN_OFFSET) & 0x2) != 0x2)
    {
        IPF_TEST_PRINT("mdrv_ipf_enable_chan :%d\n",__LINE__);
        goto error;
    }
    bFlag = 0;
    s32Ret = mdrv_ipf_enable_chan(eChanType, bFlag);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT("mdrv_ipf_enable_chan :%d\n",__LINE__);
        goto error;
    }
    if((*(unsigned int*)(ipf_base_addr_ccore +HI_IPF_CH_EN_OFFSET) & 0x2) != 0x0)
    {
        IPF_TEST_PRINT("mdrv_ipf_enable_chan :%d\n",__LINE__);
        goto error;
    }
	
	ipf_writel(old_gate_v, ipf_base_addr_ccore + HI_IPF_GATE_OFFSET);
    ipf_writel(u32OldPara, ipf_base_addr_ccore + HI_IPF_CH_EN_OFFSET); 
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);    
    return OK;
	
 error:  
	ipf_writel(old_gate_v, ipf_base_addr_ccore + HI_IPF_GATE_OFFSET);
    ipf_writel(u32OldPara, ipf_base_addr_ccore + HI_IPF_CH_EN_OFFSET); 
    return ERROR;    
}


/* test  测试一个上行过滤器设置和查询 */
int BSP_IPF_ST_205(void)
{
    IPF_FILTER_CONFIG_S stUlFilterInfo = {0};
    IPF_FILTER_CONFIG_S stUlFilterInfo1 = {0};
    int s32Ret= 0;
    
    if(g_u32IpfStAllInit != 1)
    {
        s32Ret = IPF_ST_INIT();
        if(s32Ret != OK)
        {
            IPF_TEST_ERR(" TESTERROR    IPF_ST_INIT :%d\n",__LINE__);
            return s32Ret;
        }
    }

    memset_s(&stUlFilterInfo, sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));
    stUlFilterInfo.u32FilterID = 50;/*Basic filter,psid*/  
    stUlFilterInfo.stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0x13361;
    *(unsigned int*)(stUlFilterInfo.stMatchInfo.u8SrcAddr) = 0x020113C6;/*00xC6130102;*/  
    *(unsigned int*)(stUlFilterInfo.stMatchInfo.u8DstAddr) = 0x010113C6;/*00xC6130101;*/  
    *(unsigned int*)(stUlFilterInfo.stMatchInfo.u8DstMsk) = 0xFFFFFFFF;    
    stUlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortLo = 10;
    stUlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortHi = 30;
    stUlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortLo = 10;
    stUlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortHi = 30;
    stUlFilterInfo.stMatchInfo.unTrafficClass.Bits.u8TrafficClass = 3;
    stUlFilterInfo.stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask = 0xFF;
    stUlFilterInfo.stMatchInfo.u32LocalAddressMsk = 0;
    stUlFilterInfo.stMatchInfo.unNextHeader.u32Protocol = 1;
    stUlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Type = 2;
    stUlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Code = 3;
    stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16FltPri = 100;
    stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16NextIndex = 200;
    stUlFilterInfo.stMatchInfo.u32FltSpi = 4;

    /* 第一次配置上行，PS ID是50 */
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, &stUlFilterInfo, 1);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_PRINT(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    }       
    if(mdrv_ipf_get_filter(IPF_MODEM0_ULFC, 50, &stUlFilterInfo1) != IPF_SUCCESS)
    {
        IPF_TEST_PRINT(" TESTERROR    mdrv_ipf_get_filter :%d\n",__LINE__);
    }
    stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16NextIndex = 511;
    
    s32Ret = CmpFilterInfo((IPF_FILTER_CONFIG_S *)(&stUlFilterInfo), (IPF_FILTER_CONFIG_S *)(&stUlFilterInfo1));
    if(s32Ret != 0)
    {
        IPF_TEST_ERR(" TESTERROR    CmpFilterInfo :%d\n",__LINE__);

        IPF_TEST_ERR("========in=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S*)(&stUlFilterInfo));
        IPF_TEST_ERR("========out=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S*)(&stUlFilterInfo1));
        return s32Ret;   
    }

    /* 第二次配置上行，PS ID是30 */
    stUlFilterInfo.u32FilterID = 30;
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, &stUlFilterInfo, 1);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_PRINT(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    }       
    if(mdrv_ipf_get_filter(IPF_MODEM0_ULFC, 30, &stUlFilterInfo1) != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_get_filter :%d\n",__LINE__);

        IPF_TEST_ERR("========in=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S *)(&stUlFilterInfo));
        IPF_TEST_ERR("========out=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S *)(&stUlFilterInfo1));

        return s32Ret;   
    }
    stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16NextIndex = 511;
    
    s32Ret = CmpFilterInfo((IPF_FILTER_CONFIG_S *)(&stUlFilterInfo), (IPF_FILTER_CONFIG_S *)(&stUlFilterInfo1));
    if(s32Ret != 0)
    {
        IPF_TEST_ERR(" TESTERROR    CmpFilterInfo :%d\n",__LINE__);

        IPF_TEST_ERR("========in=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S*)&stUlFilterInfo);
        IPF_TEST_ERR("========out=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S*)&stUlFilterInfo1);
        return s32Ret;   
    }

    /* 查询没有配置的Filter返回错误 */
    if(mdrv_ipf_get_filter(IPF_MODEM0_ULFC, 90, (IPF_FILTER_CONFIG_S *)(&stUlFilterInfo1)) != IPF_ERROR)
    {
        IPF_TEST_PRINT(" TESTERROR    mdrv_ipf_get_filter :%d\n",__LINE__);
        return ERROR;
    }
    check_filter_backup_status();
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);    
    if(mdrv_ipf_set_filter(IPF_MODEM0_ULFC, (IPF_FILTER_CONFIG_S *)(&stUlFilterInfo), 0) != IPF_SUCCESS)
    {
        IPF_TEST_PRINT(" TESTERROR    mdrv_ipf_get_filter :%d\n",__LINE__);
        return ERROR;   
    }
    check_filter_backup_status();
    check_filter_zero_status(IPF_MODEM0_ULFC);
    return OK; 
}

/* test  测试2个过滤器设置和查询(Ps ID 一致 ) */
int BSP_IPF_ST_206(void)
{
    IPF_FILTER_CONFIG_S stUlFilterInfo[2];
    IPF_FILTER_CONFIG_S stUlFilterInfoCheck= {0};
    IPF_FILTER_CONFIG_S stDlFilterInfo[2];
    IPF_FILTER_CONFIG_S stDlFilterInfoCheck= {0};
    int s32Ret = 0;
    unsigned int i;

    if(g_u32IpfStAllInit != 1)
    {
        s32Ret = IPF_ST_INIT();
        if(s32Ret != OK)
        {
            IPF_TEST_PRINT(" TESTERROR    IPF_ST_INIT :%d\n",__LINE__);
            return s32Ret;
        }
    }
    for(i=0;i<2;i++)
		{
		    memset_s(&stUlFilterInfo[i], sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));
		    stUlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0x13361;
		    *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8SrcAddr) = 0x020113C6;/*00xC6130102;*/  
		    *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstAddr) = 0x010113C6;/*00xC6130101;*/  
		    *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
		    stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = 10;
		    stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = 30;
		    stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortLo = 10;
		    stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortHi = 30;
		    stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClass = 3;
		    stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask = 0xFF;
		    stUlFilterInfo[i].stMatchInfo.u32LocalAddressMsk = 0;
		    stUlFilterInfo[i].stMatchInfo.unNextHeader.u32Protocol = 1;
		    stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Type = 2;
		    stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Code = 3;
		    stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16FltPri = 100;
		    stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16NextIndex = 200;
		    stUlFilterInfo[i].stMatchInfo.u32FltSpi = 10;
		    memset_s(&stUlFilterInfo[i], sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));
		    stUlFilterInfo[i].u32FilterID = 50+i;
		    

		    memcpy_s(&stDlFilterInfo, 2*sizeof(IPF_FILTER_CONFIG_S), &stUlFilterInfo, 2*sizeof(IPF_FILTER_CONFIG_S));
		    stDlFilterInfo[i].stMatchInfo.u32FltSpi = 20;
    	}
	    stDlFilterInfo[1].stMatchInfo.unFltChain.Bits.u16NextIndex = 511;

    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_DLFC, (IPF_FILTER_CONFIG_S *)(&stDlFilterInfo), 2);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    }  
        check_filter_backup_status();

    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, (IPF_FILTER_CONFIG_S *)(&stUlFilterInfo), 2);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    }
        check_filter_backup_status();

    if(mdrv_ipf_get_filter(IPF_MODEM0_DLFC, 50, (IPF_FILTER_CONFIG_S *)(&stDlFilterInfoCheck)) != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_get_filter :%d\n",__LINE__);
        return ERROR; 
    }
       
    s32Ret = CmpFilterInfo((IPF_FILTER_CONFIG_S *)(&stDlFilterInfo), (IPF_FILTER_CONFIG_S *)(&stDlFilterInfoCheck));
    if(s32Ret != 0)
    {
        IPF_TEST_ERR(" TESTERROR    CmpFilterInfo :%d\n",__LINE__);
        IPF_TEST_ERR("filterNum = %d \n",i);
        IPF_TEST_ERR("========in=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S*)&stUlFilterInfo[i]);
        IPF_TEST_ERR("========out=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S*)&stUlFilterInfoCheck);

        return s32Ret; 
    }

    if(mdrv_ipf_get_filter(IPF_MODEM0_ULFC, 50, (IPF_FILTER_CONFIG_S *)(&stUlFilterInfoCheck)) != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_get_filter :%d\n",__LINE__);
        return ERROR; 
    }
    stUlFilterInfo[1].stMatchInfo.unFltChain.Bits.u16NextIndex = 511;
    
    s32Ret = CmpFilterInfo((IPF_FILTER_CONFIG_S *)(&stUlFilterInfo), (IPF_FILTER_CONFIG_S *)(&stUlFilterInfoCheck));
    if(s32Ret != 0)
    {
        IPF_TEST_ERR(" TESTERROR    CmpFilterInfo :%d\n",__LINE__);
        IPF_TEST_ERR("filterNum = %d \n",i);
        IPF_TEST_ERR("========in=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S *)(&stUlFilterInfo[i]));
        IPF_TEST_ERR("========out=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S *)(&stUlFilterInfoCheck));

        return s32Ret; 
    }
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, (IPF_FILTER_CONFIG_S *)(&stUlFilterInfo), 0);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    } 
    check_filter_backup_status();

    check_filter_zero_status(IPF_MODEM0_ULFC);
	
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_DLFC, (IPF_FILTER_CONFIG_S *)(&stUlFilterInfo), 0);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    } 
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);        
    check_filter_backup_status();

    check_filter_zero_status(IPF_MODEM0_DLFC);

    return OK; 
}


/* test  测试配置150个上行过滤器并查询比较 150个，调用过滤器类型标志，
用到了扩展过滤器 */
int BSP_IPF_ST_207(void)
{
    static IPF_FILTER_CONFIG_S stUlFilterInfo[150];
    IPF_FILTER_CONFIG_S stUlFilterInfoCheck;
    unsigned int u32BasicFilterNum = 50;
    unsigned int u32FilterNum = 150;
    int s32Ret = 0;
    unsigned int i = 0;

    if(g_u32IpfStAllInit != 1)
    {
        s32Ret = IPF_ST_INIT();
        if(s32Ret != OK)
        {
            IPF_TEST_ERR(" TESTERROR    IPF_ST_INIT :%d\n",__LINE__);
            return s32Ret;
        }
    }

    for(i = 0; i < u32BasicFilterNum; i++)
    {
        memset_s(&stUlFilterInfo[i], sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));
        stUlFilterInfo[i].u32FilterID = i+2;
        stUlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = (i+1000)&0xFFFFFFF3;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8SrcAddr) = i+2000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstAddr) = i+4000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClass = i+3;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask = 0xFF;
        stUlFilterInfo[i].stMatchInfo.u32LocalAddressMsk = 0;
        stUlFilterInfo[i].stMatchInfo.unNextHeader.u32Protocol = i+1;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Type = i+2;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Code = i+3;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16FltPri = i+100;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16NextIndex = i;
        stUlFilterInfo[i].stMatchInfo.u32FltSpi = i+4;
    }
	
    for(i = u32BasicFilterNum; i < u32FilterNum; i++)
    {
        memset_s(&stUlFilterInfo[i], sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));
        stUlFilterInfo[i].u32FilterID = i+2+0x10000;
        stUlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = (i+1000)&0xFFFFFFF3;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8SrcAddr) = i+2000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstAddr) = i+4000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClass = i+3;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask = 0xFF;
        stUlFilterInfo[i].stMatchInfo.u32LocalAddressMsk = 0;
        stUlFilterInfo[i].stMatchInfo.unNextHeader.u32Protocol = i+1;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Type = i+2;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Code = i+3;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16FltPri = i+100;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16NextIndex = i;
        stUlFilterInfo[i].stMatchInfo.u32FltSpi = i+4;
    }
	
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, stUlFilterInfo, u32FilterNum);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    }
    check_filter_backup_status();

    for(i = u32BasicFilterNum; i < u32FilterNum; i++)
    {
        memset_s(&stUlFilterInfo[i], sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));
        stUlFilterInfo[i].u32FilterID = i+2;
        stUlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = (i+1000)&0xFFFFFFF3;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8SrcAddr) = i+2000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstAddr) = i+4000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClass = i+3;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask = 0xFF;
        stUlFilterInfo[i].stMatchInfo.u32LocalAddressMsk = 0;
        stUlFilterInfo[i].stMatchInfo.unNextHeader.u32Protocol = i+1;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Type = i+2;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Code = i+3;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16FltPri = i+100;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16NextIndex = i;
        stUlFilterInfo[i].stMatchInfo.u32FltSpi = i+4;
    }
    for(i = 0; i < u32FilterNum; i++)
    {
        if(mdrv_ipf_get_filter(IPF_MODEM0_ULFC, i+2, &stUlFilterInfoCheck) != IPF_SUCCESS)
        {
            IPF_TEST_ERR(" TESTERROR    mdrv_ipf_get_filter :%d\n",__LINE__);
            return ERROR; 
        }
        if(i<u32FilterNum-1)
        {
            stUlFilterInfoCheck.stMatchInfo.unFltChain.Bits.u16NextIndex = i+1;
        }
        else
        {
            stUlFilterInfoCheck.stMatchInfo.unFltChain.Bits.u16NextIndex = 511;
        }
        
        s32Ret = CmpFilterInfo((IPF_FILTER_CONFIG_S *)(&stUlFilterInfoCheck), (IPF_FILTER_CONFIG_S *)(&stUlFilterInfo[i]));
        if(s32Ret != 0)
        {
            IPF_TEST_ERR("filterNum = %d \n",i);
            IPF_TEST_ERR("========in=======\n");
            PrintFilterInfo((IPF_FILTER_CONFIG_S*)&stUlFilterInfo[i]);
            IPF_TEST_ERR("========out=======\n");
            PrintFilterInfo((IPF_FILTER_CONFIG_S*)&stUlFilterInfoCheck);
        }
    }
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, stUlFilterInfo, 0);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    } 
    check_filter_backup_status();

    check_filter_zero_status(IPF_MODEM0_ULFC);
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);       
    return OK; 
}

/* test  测试配置150个下行过滤器全部设置为基本测试基本转扩展是否有效，并查询比较 */
int BSP_IPF_ST_208(void)
{
    static IPF_FILTER_CONFIG_S stDlFilterInfo[150];
    IPF_FILTER_CONFIG_S stDlFilterInfoCheck;
    unsigned int u32FilterNum = 150;
    int s32Ret = 0;
    unsigned int i = 0;
    
    if(g_u32IpfStAllInit != 1)
    {
        s32Ret = IPF_ST_INIT();
        if(s32Ret != OK)
        {
            IPF_TEST_ERR(" TESTERROR    IPF_ST_INIT :%d\n",__LINE__);
            return s32Ret;
        }
    }

    for(i = 0; i < u32FilterNum; i++)
    {
        memset_s(&stDlFilterInfo[i], sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));
        stDlFilterInfo[i].u32FilterID = i+2;
        stDlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = (i+1000)&0xFFFFFFF3;
        *(unsigned int*)(stDlFilterInfo[i].stMatchInfo.u8SrcAddr) = i+2000;
        *(unsigned int*)(stDlFilterInfo[i].stMatchInfo.u8DstAddr) = i+4000;
        *(unsigned int*)(stDlFilterInfo[i].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
        stDlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = i+10;
        stDlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = i+30;
        stDlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortLo = i+10;
        stDlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortHi = i+30;
		
        stDlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClass = i+3;
        stDlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask = 0xFF;
        stDlFilterInfo[i].stMatchInfo.u32LocalAddressMsk = 0;

		
        stDlFilterInfo[i].stMatchInfo.unNextHeader.u32Protocol = i+1;
        stDlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Type = i+2;
        stDlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Code = i+3;
        stDlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16FltPri = i+100;
        stDlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16NextIndex = i+200;
        stDlFilterInfo[i].stMatchInfo.u32FltSpi = i+4;
    }

		  
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_DLFC, stDlFilterInfo, u32FilterNum);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    }
    check_filter_backup_status();

    for(i = 0; i < u32FilterNum; i++)
    {
        if(mdrv_ipf_get_filter(IPF_MODEM0_DLFC, i+2, &stDlFilterInfoCheck) != IPF_SUCCESS)
        {
            IPF_TEST_ERR(" TESTERROR    mdrv_ipf_get_filter :%d\n",__LINE__);
            return ERROR; 
        }
        if(i<u32FilterNum-1)
        {
            stDlFilterInfoCheck.stMatchInfo.unFltChain.Bits.u16NextIndex = i+1;
        }
        else
        {
            stDlFilterInfoCheck.stMatchInfo.unFltChain.Bits.u16NextIndex = 511;
        }

        s32Ret = CmpFilterInfo((IPF_FILTER_CONFIG_S *)(&stDlFilterInfoCheck), (IPF_FILTER_CONFIG_S *)(&stDlFilterInfo[i]));
        if(s32Ret != 0)
        {
            IPF_TEST_ERR("filterNum = %d \n",i);
            IPF_TEST_ERR("========in=======\n");
            PrintFilterInfo((IPF_FILTER_CONFIG_S*)&stDlFilterInfo[i]);
            IPF_TEST_ERR("========out=======\n");
            PrintFilterInfo((IPF_FILTER_CONFIG_S*)&stDlFilterInfoCheck);
            return s32Ret; 
        }
    }

    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_DLFC, stDlFilterInfo, 0);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    } 
    check_filter_backup_status();

    check_filter_zero_status(IPF_MODEM0_DLFC);
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);           
    return OK; 
}

/* test  测试过滤器设置和查询  */
int BSP_IPF_ST_209(void)
{
    IPF_FILTER_CONFIG_S stUlFilterInfo = {0};
    IPF_FILTER_CONFIG_S stUlFilterInfoCheck= {0};
    int s32Ret = 0;
    unsigned int i = 0;

    if(g_u32IpfStAllInit != 1)
    {
        s32Ret = IPF_ST_INIT();
        if(s32Ret != OK)
        {
            IPF_TEST_ERR(" TESTERROR    IPF_ST_INIT :%d\n",__LINE__);
            return s32Ret;
        }
    }

    memset_s(&stUlFilterInfo, sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));
    stUlFilterInfo.u32FilterID = 3;
    stUlFilterInfo.stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0x13361;
    *(unsigned int*)(stUlFilterInfo.stMatchInfo.u8SrcAddr) = 0x020113C6;/*00xC6130102;*/
    *(unsigned int*)(stUlFilterInfo.stMatchInfo.u8DstAddr) = 0x010113C6;/*00xC6130101;*/
    *(unsigned int*)(stUlFilterInfo.stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
    stUlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortLo = 10;
    stUlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortHi = 30;
    stUlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortLo = 10;
    stUlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortHi = 30;
	
    stUlFilterInfo.stMatchInfo.unTrafficClass.Bits.u8TrafficClass = i+3;
    stUlFilterInfo.stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask = 0xFF;
    stUlFilterInfo.stMatchInfo.u32LocalAddressMsk = 0;
	
    stUlFilterInfo.stMatchInfo.unNextHeader.u32Protocol = 1;
    stUlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Type = 2;
    stUlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Code = 3;
    stUlFilterInfo.stMatchInfo.u32FltSpi = 4;

    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, &stUlFilterInfo, 1);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);    
        return s32Ret;   
    }
    check_filter_backup_status();
    if(mdrv_ipf_get_filter(IPF_MODEM0_ULFC, 3, &stUlFilterInfoCheck) != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_get_filter :%d\n",__LINE__);
        return ERROR; 
    }
    stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16NextIndex = 511;    
   
    s32Ret = CmpFilterInfo((IPF_FILTER_CONFIG_S *)(&stUlFilterInfo), (IPF_FILTER_CONFIG_S *)(&stUlFilterInfoCheck));
    if(s32Ret != 0)
    {
        IPF_TEST_ERR("========in=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S*)&stUlFilterInfo);
        IPF_TEST_ERR("========out=======\n");
        PrintFilterInfo((IPF_FILTER_CONFIG_S*)&stUlFilterInfoCheck);
        return s32Ret; 
    }    
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, &stUlFilterInfo, 0);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    } 
    check_filter_backup_status();
    if(mdrv_ipf_get_filter(IPF_MODEM0_ULFC, 3, &stUlFilterInfoCheck) != IPF_ERROR)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_get_filter :%d\n",__LINE__);
        return ERROR; 
    }
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, &stUlFilterInfo, 0);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    } 
    check_filter_backup_status();

    check_filter_zero_status(IPF_MODEM0_ULFC);
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);          
    return OK; 

}

/*配置基本扩展过滤器交替的场景*/
int BSP_IPF_ST_210(void)
{
    static IPF_FILTER_CONFIG_S stUlFilterInfo[150];
    int s32Ret = 0;
    unsigned int i = 0;

    if(g_u32IpfStAllInit != 1)
    {
        s32Ret = IPF_ST_INIT();
        if(s32Ret != OK)
        {
            IPF_TEST_ERR(" TESTERROR    IPF_ST_INIT :%d\n",__LINE__);
            return s32Ret;
        }
    }

    for(i = 0; i < 150; i++)
    {
        memset_s(&stUlFilterInfo[i], sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));
        if(0 == i)
        {
            stUlFilterInfo[i].u32FilterID = i+2;
        }
        else if(0 == i%2)
        {
            stUlFilterInfo[i].u32FilterID = i+2;
        }
        else
        {
            stUlFilterInfo[i].u32FilterID = i+2+0x10000;
        }
        stUlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = (i+1000)&0xFFFFFFF3;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8SrcAddr) = i+2000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstAddr) = i+4000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClass = i+3;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask = 0xFF;
        stUlFilterInfo[i].stMatchInfo.u32LocalAddressMsk = 0;
        stUlFilterInfo[i].stMatchInfo.unNextHeader.u32Protocol = i+1;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Type = i+2;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Code = i+3;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16FltPri = i+100;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16NextIndex = i;
        stUlFilterInfo[i].stMatchInfo.u32FltSpi = i+4;
    }
	
	
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, stUlFilterInfo, 150);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    }
    check_filter_backup_status();
    
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);       
    return OK; 
}


/*配置满全基本过滤器场景*/
int BSP_IPF_ST_211(void)
{
    static IPF_FILTER_CONFIG_S stUlFilterInfo[57];
    int s32Ret = 0;
    unsigned int i = 0;

    if(g_u32IpfStAllInit != 1)
    {
        s32Ret = IPF_ST_INIT();
        if(s32Ret != OK)
        {
            IPF_TEST_ERR(" TESTERROR    IPF_ST_INIT :%d\n",__LINE__);
            return s32Ret;
        }
    }

    for(i = 0; i < 57; i++)
    {
        memset_s(&stUlFilterInfo[i], sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));
        stUlFilterInfo[i].u32FilterID = i+2;
        stUlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = (i+1000)&0xFFFFFFF3;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8SrcAddr) = i+2000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstAddr) = i+4000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClass = i+3;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask = 0xFF;
        stUlFilterInfo[i].stMatchInfo.u32LocalAddressMsk = 0;
        stUlFilterInfo[i].stMatchInfo.unNextHeader.u32Protocol = i+1;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Type = i+2;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Code = i+3;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16FltPri = i+100;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16NextIndex = i;
        stUlFilterInfo[i].stMatchInfo.u32FltSpi = i+4;
    }
	
	
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, stUlFilterInfo, 57);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    }
    check_filter_backup_status();
    
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);       
    return OK; 
}



/*配置基本加扩展场景*/
int BSP_IPF_ST_212(unsigned int basic_num, unsigned int ext_num, unsigned int chain_head)
{
	//动态分配这么大的内存，很大可能会任务栈溢出，改为静态
    static IPF_FILTER_CONFIG_S stUlFilterInfo[511];
    int s32Ret = 0;
    unsigned int i = 0;

	for(i = 0; i < 511; i++)
    {
        memset_s(&stUlFilterInfo[i], sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));
	}

    if(g_u32IpfStAllInit != 1)
    {
        s32Ret = IPF_ST_INIT();
        if(s32Ret != OK)
        {
            IPF_TEST_ERR("IPF_ST_INIT :%d\n",__LINE__);
            return s32Ret;
        }
    }

    for(i = 0; i < (basic_num+ext_num); i++)
    {
        if(i < basic_num)
        {
            stUlFilterInfo[i].u32FilterID = i+2;
        }
		else
		{
            stUlFilterInfo[i].u32FilterID = i+2+0x10000;
		}
        stUlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = (i+1000)&0xFFFFFFF3;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8SrcAddr) = i+2000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstAddr) = i+4000;
        *(unsigned int*)(stUlFilterInfo[i].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortLo = i+10;
        stUlFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortHi = i+30;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClass = i+3;
        stUlFilterInfo[i].stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask = 0xFF;
        stUlFilterInfo[i].stMatchInfo.u32LocalAddressMsk = 0;
        stUlFilterInfo[i].stMatchInfo.unNextHeader.u32Protocol = i+1;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Type = i+2;
        stUlFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Code = i+3;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16FltPri = i+100;
        stUlFilterInfo[i].stMatchInfo.unFltChain.Bits.u16NextIndex = i;
        stUlFilterInfo[i].stMatchInfo.u32FltSpi = i+4;
    }
	
    s32Ret = mdrv_ipf_set_filter(chain_head, stUlFilterInfo, (basic_num+ext_num));
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR("mdrv_ipf_set_filter :%d\n",__LINE__);
        return s32Ret;   
    }
    check_filter_backup_status();
    
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);       
    return OK; 
}

int BSP_IPF_ST_RESTORE_DL_FILTER(void)
{
	static IPF_FILTER_CONFIG_S stDlFilterInfo[50];
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

	s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_DLFC, stDlFilterInfo, 50);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR("mdrv_ipf_set_filter return failed :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }

	return OK;
}

TTF_MEM_ST* GetDLSrcBufCb(unsigned int u32Len)
{
    TTF_MEM_ST* pstTTF;
    pstTTF = (TTF_MEM_ST*)osl_cachedma_malloc(sizeof(TTF_MEM_ST) + u32Len);
    if(pstTTF == NULL)
    	IPF_TEST_ERR("%s:GetPsBufCb malloc pstTTF error\n",__FUNCTION__);
    
    pstTTF->pData = (unsigned char*)pstTTF + sizeof(TTF_MEM_ST);
    pstTTF->usUsed = u32Len;
    if(pstTTF->pData == NULL)
    	IPF_TEST_ERR("%s:GetPsBufCb malloc pstTTF->pData error\n",__FUNCTION__);

	osl_cachedma_free(pstTTF);
    return pstTTF;
}

void ipf_set_sche_mode(unsigned int sche_mode)
{
    unsigned int control_info = 0;
    control_info = ipf_readl(ipf_base_addr_ccore + HI_IPF_CTRL_OFFSET);
    control_info &= 0xFFFFDFFF;//set sche ctrl to BD only

    if(0 == sche_mode)
    {
        IPF_TEST_PRINT( "\r ipf_set_sche_mode to BD only \n");
    }
    else
    {
        control_info |= 0x00002000;
        IPF_TEST_PRINT( "\r ipf_set_sche_mode to BD AD RD \n");
    }

    /* 配置上下行通道的AD阀值*/
    ipf_writel(control_info, ipf_base_addr_ccore + HI_IPF_CTRL_OFFSET);
    return;
}

/*****************************
***2xx DL start test*****
*****************************/
/* 2个TTF结点，配2个BD 一长一短，用于验证AD回退的有效性*/
int BSP_IPF_ST_300(void)
{
    IPF_CONFIG_DLPARAM_S stDlPara[2];
    TTF_MEM_ST stSrcTtf;
    TTF_MEM_ST stSrcTtfShort;
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    unsigned int u32Num = 2;
    int s32Ret = 0;
   
    s32Ret = IPF_ST_DL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return s32Ret;
    }
    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    {
        if(u32BDNum != IPF_DLBD_DESC_SIZE)
        {
            IPF_TEST_ERR(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
            ,__LINE__, u32BDNum, u32CDNum);
        } 
    }
	
    stSrcTtf.usUsed = 1000;
    stSrcTtf.pData = osl_cachedma_malloc(stSrcTtf.usUsed);
    stSrcTtf.pNext = NULL;
    if(stSrcTtf.pData == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }
    stSrcTtfShort.usUsed = 200;
    stSrcTtfShort.pData = osl_cachedma_malloc(stSrcTtfShort.usUsed);
    stSrcTtfShort.pNext = NULL;
    if(stSrcTtfShort.pData == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    ipf_ipv4_head.TOL = stSrcTtf.usUsed;
    ipf_udp.Length = ipf_ipv4_head.TOL;
    memset_s(stSrcTtf.pData, stSrcTtf.usUsed, T_DL_VALUE, stSrcTtf.usUsed);
    memcpy_s(stSrcTtf.pData, sizeof(StreamIPv4Header), &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy_s(stSrcTtf.pData+sizeof(StreamIPv4Header), sizeof(StreamUDP), &ipf_udp, sizeof(StreamUDP));
    
    stDlPara[0].u32Data = (unsigned int)&stSrcTtf;
    stDlPara[0].u16UsrField1= 1200;
    stDlPara[0].u16Len= 1000;

    /*设中断，仅搬移*/
    stDlPara[0].u16Attribute= 0x29; 

    osl_cache_flush(OSL_DATA_CACHE,stSrcTtf.pData,1000);
	
    ipf_ipv4_head.TOL = stSrcTtfShort.usUsed;
    memset_s(stSrcTtfShort.pData, stSrcTtfShort.usUsed, T_DL_VALUE, stSrcTtfShort.usUsed);
    memcpy_s(stSrcTtfShort.pData, sizeof(StreamIPv4Header), &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy_s(stSrcTtfShort.pData+sizeof(StreamIPv4Header), sizeof(StreamUDP), &ipf_udp, sizeof(StreamUDP));
    stDlPara[1].u32Data = (unsigned int)(&stSrcTtfShort);
    stDlPara[1].u16UsrField1= 200;
    stDlPara[1].u16Len= 200;

    /*设中断，仅搬移*/
    stDlPara[1].u16Attribute= 0x29; 

    osl_cache_flush(OSL_DATA_CACHE,stSrcTtfShort.pData,200);

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(u32Num, (IPF_CONFIG_DLPARAM_S*)&stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR("mdrv_ipf_config_dlbd :%d\n",__LINE__);
		goto error;
    } 
	
error:
	osl_cachedma_free((unsigned int *)stSrcTtf.pData);
	osl_cachedma_free((unsigned int *)stSrcTtfShort.pData);

    return s32Ret;
}


/* 1个TTF结点，配1个BD */
int BSP_IPF_ST_301(void)
{
    IPF_CONFIG_DLPARAM_S stDlPara;
    TTF_MEM_ST stSrcTtf;
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    unsigned int u32Num = 1;
    int s32Ret = 0;
   
    s32Ret = IPF_ST_DL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
		return s32Ret;
    }
	
    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    {
        if(u32BDNum != IPF_DLBD_DESC_SIZE)
        {
            IPF_TEST_ERR(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
            ,__LINE__, u32BDNum, u32CDNum);
        } 
    }
	
    stSrcTtf.usUsed = 1000;
    stSrcTtf.pData = osl_cachedma_malloc(stSrcTtf.usUsed);
    stSrcTtf.pNext = NULL;
    if(stSrcTtf.pData == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    ipf_ipv4_head.TOL = stSrcTtf.usUsed;
    ipf_udp.Length = ipf_ipv4_head.TOL;
    memset_s(stSrcTtf.pData, stSrcTtf.usUsed, T_DL_VALUE, stSrcTtf.usUsed);
    memcpy_s(stSrcTtf.pData, sizeof(StreamIPv4Header), &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy_s(stSrcTtf.pData+sizeof(StreamIPv4Header), sizeof(StreamUDP), &ipf_udp, sizeof(StreamUDP));
    
    stDlPara.u32Data = (unsigned int)(&stSrcTtf);
    stDlPara.u16UsrField1= 200;
    stDlPara.u16Len= 1000;

    /*设中断，仅搬移*/
    stDlPara.u16Attribute= 0x29; 

    osl_cache_flush(OSL_DATA_CACHE,stSrcTtf.pData,1000);

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(u32Num, &stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR("mdrv_ipf_config_dlbd :%d\n",__LINE__);
		goto error;
    } 

error:
    osl_cachedma_free((void *)(stSrcTtf.pData));
	
    return s32Ret;
}

/* 5个TTF结点，配1个BD */
int BSP_IPF_ST_302(void)
{
    unsigned char* pu8IPData;
    unsigned char* pu8IPData1;
    unsigned char* pu8IPData2;
    unsigned char* pu8IPData3;
    unsigned char* pu8IPData4;
    IPF_CONFIG_DLPARAM_S stDlPara;
    TTF_MEM_ST stSrcTtf[5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    int s32Ret = 0;
    unsigned int u32Num = 1;
	
    s32Ret = IPF_ST_DL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR("IPF_ST_DL_INIT :%d\n",__LINE__);
        return s32Ret;
    }

    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    {
        if(u32BDNum != IPF_DLBD_DESC_SIZE)
        {
            IPF_TEST_ERR(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
            ,__LINE__, u32BDNum, u32CDNum);
        } 
    }

    pu8IPData = (unsigned char*)osl_cachedma_malloc(200);
    if(pu8IPData == NULL)
    {
        IPF_TEST_ERR("cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pu8IPData1 = (unsigned char*)osl_cachedma_malloc(200);
    if(pu8IPData1 == NULL)
    {
        IPF_TEST_ERR("cacheDmaMalloc :%d\n",__LINE__);
        goto error4;
    }
    pu8IPData2 = (unsigned char*)osl_cachedma_malloc(100);
    if(pu8IPData1 == NULL)
    {
        IPF_TEST_ERR("cacheDmaMalloc :%d\n",__LINE__);
        goto error3;
    }
    pu8IPData3 = (unsigned char*)osl_cachedma_malloc(200);
    if(pu8IPData1 == NULL)
    {
        IPF_TEST_ERR("cacheDmaMalloc :%d\n",__LINE__);
        goto error2;
    }
    pu8IPData4 = (unsigned char*)osl_cachedma_malloc(300);
    if(pu8IPData1 == NULL)
    {
        IPF_TEST_ERR("cacheDmaMalloc :%d\n",__LINE__);
        goto error1;
    }

    ipf_ipv4_head.TOL = 1000;
    ipf_udp.Length = ipf_ipv4_head.TOL;
    memset_s(pu8IPData, 200, T_DL_VALUE, 200);
    memcpy_s(pu8IPData, sizeof(StreamIPv4Header), &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy_s(pu8IPData+sizeof(StreamIPv4Header), sizeof(StreamUDP), &ipf_udp, sizeof(StreamUDP));
    memset_s(pu8IPData1, 200, T_DL_VALUE, 200);
    memset_s(pu8IPData2, 100, T_DL_VALUE, 100);
    memset_s(pu8IPData3, 200, T_DL_VALUE, 200);
    memset_s(pu8IPData4, 300, T_DL_VALUE, 300);
	
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

    stSrcTtf[4].usUsed = 300;
    stSrcTtf[4].pData = pu8IPData4;
    stSrcTtf[4].pNext = NULL;
	
    stDlPara.u32Data = (unsigned int)stSrcTtf;
    stDlPara.u16UsrField1= 200;
    stDlPara.u16Len= 1000;
    /*设中断，仅搬移*/
    stDlPara.u16Attribute= 0x29; 

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(u32Num, &stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_dlbd :%d\n",__LINE__);
        goto error;
    } 
    delay(2);

error:
    osl_cachedma_free(pu8IPData4);
error1:
    osl_cachedma_free(pu8IPData3);
error2:
    osl_cachedma_free(pu8IPData2);
error3:
    osl_cachedma_free(pu8IPData1);
error4:
    osl_cachedma_free(pu8IPData);

    return s32Ret;

}
/*
*step1. call this fuction
*step2. run any ul case
*step3. check pmlog
*/
int ipf_test_pm_om_ul(void)
{
	int ret = -1;
	
	if (!g_ipf_ctx.status) {
		ret = -1;
		goto out;
	}
	g_ipf_ctx.status->resume_with_intr++;

out:
	IPF_TEST_ERR("%s %s\n", __FUNCTION__, ret ? "failed" : "success");
	return ret;
}

/* 5个TTF结点，配60个BD 仅搬移*/
int BSP_IPF_ST_3031(void)
{
    unsigned int BDNUM = 60;
    unsigned char* pu8IPData;
    unsigned char* pu8IPData1;
    unsigned char* pu8IPData2;
    unsigned char* pu8IPData3;
    unsigned char* pu8IPData4;
    static IPF_CONFIG_DLPARAM_S stDlPara[60];
    TTF_MEM_ST stSrcTtf[5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    int s32Ret = 0;
    unsigned int i = 0;
	
    s32Ret = IPF_ST_DL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return s32Ret;
    }

    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    {
        if(u32BDNum != IPF_DLBD_DESC_SIZE)
        {
            IPF_TEST_ERR(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n",__LINE__, u32BDNum, u32CDNum);
			return ERROR;
		} 
    }
	
    pu8IPData = (unsigned char*)osl_cachedma_malloc(200);
    if(pu8IPData == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pu8IPData1 = (unsigned char*)osl_cachedma_malloc(200);
    if(pu8IPData1 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error4;
    }
    pu8IPData2 = (unsigned char*)osl_cachedma_malloc(100);
    if(pu8IPData2 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error3;
    }
    pu8IPData3 = (unsigned char*)osl_cachedma_malloc(200);
    if(pu8IPData3 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error2;
    }
    pu8IPData4 = (unsigned char*)osl_cachedma_malloc(300);
    if(pu8IPData4 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error1;
    }
    
    ipf_ipv4_head.TOL = 1000;
    ipf_udp.Length = ipf_ipv4_head.TOL;

    memset_s(pu8IPData, 200, T_DL_VALUE, 200);
    memcpy_s(pu8IPData, sizeof(StreamIPv4Header), &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy_s(pu8IPData+sizeof(StreamIPv4Header), sizeof(StreamUDP), &ipf_udp, sizeof(StreamUDP));
    memset_s(pu8IPData1, 200, T_DL_VALUE, 200);
    memset_s(pu8IPData2, 100, T_DL_VALUE, 100);
    memset_s(pu8IPData3, 200, T_DL_VALUE, 200);
    memset_s(pu8IPData4, 300, T_DL_VALUE, 300);
	
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

    stSrcTtf[4].usUsed = 300;
    stSrcTtf[4].pData = pu8IPData4;
    stSrcTtf[4].pNext = NULL;
	
	for(i=0; i<BDNUM; i++){	
	    stDlPara[i].u32Data = (unsigned int)stSrcTtf;
	    stDlPara[i].u16UsrField1= 200+i;
	    stDlPara[i].u16Len= 1000;
	    /*设中断，仅搬移*/
	    stDlPara[i].u16Attribute= 0x28; 
	}	
	stDlPara[BDNUM - 1].u16Attribute= 0x29; 

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(BDNUM, stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_dlbd :%d\n",__LINE__);
        goto error;
    } 
    delay(2);

error:
    osl_cachedma_free(pu8IPData4);
error1:
    osl_cachedma_free(pu8IPData3);
error2:
    osl_cachedma_free(pu8IPData2);
error3:
    osl_cachedma_free(pu8IPData1);
error4:
    osl_cachedma_free(pu8IPData);

    return s32Ret;

}

/* 5个TTF结点，配31个BD 过滤搬移*/
int BSP_IPF_ST_3032(void)
{
    unsigned int BDNUM =  31;
    unsigned char* pu8IPData;
    unsigned char* pu8IPData1;
    unsigned char* pu8IPData2;
    unsigned char* pu8IPData3;
    unsigned char* pu8IPData4;
    IPF_CONFIG_DLPARAM_S stDlPara[BDNUM];
    TTF_MEM_ST stSrcTtf[5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    int s32Ret = 0;
    unsigned int i = 0;
	
    s32Ret = IPF_ST_DL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return s32Ret;
    }

    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    {
        if(u32BDNum != IPF_DLBD_DESC_SIZE)
        {
            IPF_TEST_ERR(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
            ,__LINE__, u32BDNum, u32CDNum);
        } 
    }

    pu8IPData = (unsigned char*)osl_cachedma_malloc(200);
    if(pu8IPData == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pu8IPData1 = (unsigned char*)osl_cachedma_malloc(200);
    if(pu8IPData1 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error4;
    }
    pu8IPData2 = (unsigned char*)osl_cachedma_malloc(100);
    if(pu8IPData2 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error3;
    }
    pu8IPData3 = (unsigned char*)osl_cachedma_malloc(200);
    if(pu8IPData3 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error2;
    }
    pu8IPData4 = (unsigned char*)osl_cachedma_malloc(300);
    if(pu8IPData4 == NULL)
    {
        IPF_TEST_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error1;
    }
   
    ipf_ipv4_head.TOL = 1000;
    ipf_udp.Length = ipf_ipv4_head.TOL;
	
    memset_s(pu8IPData, 200, T_DL_VALUE, 200);
    memcpy_s(pu8IPData, sizeof(StreamIPv4Header), &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy_s(pu8IPData+sizeof(StreamIPv4Header), sizeof(StreamUDP), &ipf_udp, sizeof(StreamUDP));
    memset_s(pu8IPData1, 200, T_DL_VALUE, 200);
    memset_s(pu8IPData2, 100, T_DL_VALUE, 100);
    memset_s(pu8IPData3, 200, T_DL_VALUE, 200);
    memset_s(pu8IPData4, 300, T_DL_VALUE, 300);
	
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

    stSrcTtf[4].usUsed = 300;
    stSrcTtf[4].pData = pu8IPData4;
    stSrcTtf[4].pNext = NULL;
	
	for(i=0; i<BDNUM; i++)
	{
	    stDlPara[i].u32Data = (unsigned int)stSrcTtf;
	    stDlPara[i].u16UsrField1= 200+i;
	    stDlPara[i].u16Len= 1000;
	    /*设中断，仅搬移*/
	    stDlPara[i].u16Attribute= 0x28; 
	}	
	stDlPara[BDNUM - 1].u16Attribute= 0x29; 

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(BDNUM, stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_dlbd :%d\n",__LINE__);
        goto error;
    } 
    delay(2);

error:
    osl_cachedma_free(pu8IPData4);
error1:
    osl_cachedma_free(pu8IPData3);
error2:
    osl_cachedma_free(pu8IPData2);
error3:
    osl_cachedma_free(pu8IPData1);
error4:
    osl_cachedma_free(pu8IPData);

    return s32Ret;
}


/* 5个TTF结点，配60个BD */
int BSP_IPF_ST_304(void)
{
    unsigned int BDNUM = 60;
    unsigned char* pu8IPData[BDNUM];
    unsigned int u32Len = 1000;
    static IPF_CONFIG_DLPARAM_S stDlPara[60];
    static TTF_MEM_ST stSrcTtf[60][5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    int s32Ret = 0;
    unsigned int i = 0;

    ipf_ipv4_head.TOL = u32Len;
    ipf_udp.Length = ipf_ipv4_head.TOL;

    s32Ret = IPF_ST_DL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return s32Ret;
    }

    
    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    {
        if(u32BDNum != IPF_DLBD_DESC_SIZE)
        {
            IPF_TEST_ERR(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
            ,__LINE__, u32BDNum, u32CDNum);
        } 
    }

    for(i = 0; i < BDNUM; i++)
    {
        pu8IPData[i] = (unsigned char*)osl_cachedma_malloc(u32Len);
        if(pu8IPData[i] == NULL)
        {
            IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        }

        
        memset_s(pu8IPData[i], u32Len, T_DL_VALUE, u32Len);
        memcpy_s(pu8IPData[i], sizeof(StreamIPv4Header), &ipf_ipv4_head, sizeof(StreamIPv4Header));
        memcpy_s(pu8IPData[i]+sizeof(StreamIPv4Header), sizeof(StreamUDP), &ipf_udp, sizeof(StreamUDP));

        stSrcTtf[i][0].usUsed = 200;
        stSrcTtf[i][0].pData = pu8IPData[i];
        stSrcTtf[i][0].pNext = &stSrcTtf[i][1];

        stSrcTtf[i][1].usUsed = 200;
        stSrcTtf[i][1].pData = pu8IPData[i] + stSrcTtf[i][0].usUsed;
        stSrcTtf[i][1].pNext = &stSrcTtf[i][2];

        stSrcTtf[i][2].usUsed = 100;
        stSrcTtf[i][2].pData = pu8IPData[i] + stSrcTtf[i][1].usUsed;
        stSrcTtf[i][2].pNext = &stSrcTtf[i][3];

        stSrcTtf[i][3].usUsed = 200;
        stSrcTtf[i][3].pData = pu8IPData[i] + stSrcTtf[i][2].usUsed;
        stSrcTtf[i][3].pNext = &stSrcTtf[i][4];

        stSrcTtf[i][4].usUsed = 300;
        stSrcTtf[i][4].pData = pu8IPData[i] + stSrcTtf[i][3].usUsed;
        stSrcTtf[i][4].pNext = NULL;
    
        stDlPara[i].u32Data= (unsigned int)stSrcTtf[i];
        stDlPara[i].u16Attribute= 0x3b;
        stDlPara[i].u16UsrField1 = 200; 
        stDlPara[i].u16Len= 1000; 
    }

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(BDNUM, stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_dlbd :%d\n",__LINE__);
        goto error1;
    } 
    delay(2);
	
error1:
    for(i = 0; i < BDNUM; i++)
    {
        if(pu8IPData[i] != NULL)
        {
            osl_cachedma_free(pu8IPData[i]);
        }
    }
    return s32Ret;
}


int BSP_IPF_DlSend_n2(unsigned int SendTimes,unsigned int SendNum)
{
    static IPF_CONFIG_DLPARAM_S stDlPara[IPF_DLBD_DESC_SIZE];
    int s32Ret = 0;
    unsigned int i = 0;
    unsigned int j = SendTimes;
    unsigned char* pu8IPData;
    unsigned char* pu8IPData1;
    unsigned char* pu8IPData2;
    unsigned char* pu8IPData3;
    unsigned char* pu8IPData4;
    unsigned int u32Len = 200;
    TTF_MEM_ST stSrcTtf[5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    unsigned int DlSendBDNum = 0;
	
    pu8IPData = (unsigned char*)osl_cachedma_malloc(u32Len);
    if(pu8IPData == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pu8IPData1 = (unsigned char*)osl_cachedma_malloc(u32Len);
    if(pu8IPData1 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error4;
    }
    pu8IPData2 = (unsigned char*)osl_cachedma_malloc(u32Len);
    if(pu8IPData2 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error3;
    }
    pu8IPData3 = (unsigned char*)osl_cachedma_malloc(u32Len);
    if(pu8IPData3 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error2;
    }
    pu8IPData4 = (unsigned char*)osl_cachedma_malloc(u32Len);
    if(pu8IPData4 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error1;
    }

    ipf_ipv4_head.TOL = u32Len*5;
    ipf_udp.Length = ipf_ipv4_head.TOL;
    memset_s(pu8IPData, u32Len, T_DL_VALUE, u32Len);
    memcpy_s(pu8IPData, sizeof(StreamIPv4Header), &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy_s(pu8IPData+sizeof(StreamIPv4Header), sizeof(StreamUDP), &ipf_udp, sizeof(StreamUDP));
    memset_s(pu8IPData1, u32Len, T_DL_VALUE, u32Len);
    memset_s(pu8IPData2, u32Len, T_DL_VALUE, u32Len);
    memset_s(pu8IPData3, u32Len, T_DL_VALUE, u32Len);
    memset_s(pu8IPData4, u32Len, T_DL_VALUE, u32Len);
    stSrcTtf[0].usUsed = u32Len;
    stSrcTtf[0].pData = pu8IPData;
    stSrcTtf[0].pNext = &stSrcTtf[1];

    stSrcTtf[1].usUsed = u32Len;
    stSrcTtf[1].pData = pu8IPData1;
    stSrcTtf[1].pNext = &stSrcTtf[2];

    stSrcTtf[2].usUsed = u32Len;
    stSrcTtf[2].pData = pu8IPData2;
    stSrcTtf[2].pNext = &stSrcTtf[3];

    stSrcTtf[3].usUsed = u32Len;
    stSrcTtf[3].pData = pu8IPData3;
    stSrcTtf[3].pNext = &stSrcTtf[4];

    stSrcTtf[4].usUsed = u32Len;
    stSrcTtf[4].pData = pu8IPData4;
    stSrcTtf[4].pNext = NULL;

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));

    while(j > 0)
    {
		u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
		
		if(u32BDNum > SendNum)
		{
			for(i=0;i < IPF_DLBD_DESC_SIZE;i++)
			{
			    stDlPara[i].u32Data = (unsigned int)stSrcTtf;
			    stDlPara[i].u16UsrField1= 200;
			    stDlPara[i].u16Len= u32Len*5;
			    /*设中断，仅搬移*/
			    stDlPara[i].u16Attribute= 0x28; 
			}	
			stDlPara[SendNum-1].u16Attribute= 0x29; 
			s32Ret = mdrv_ipf_config_dlbd(SendNum, stDlPara);
			if(s32Ret != IPF_SUCCESS)    
			{
				IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_dlbd :%d\n",__LINE__);
				goto error0;
			} 
			j--;
			DlSendBDNum += (u32BDNum-1);
		}
		osl_task_delay(100);
    }
	IPF_TEST_ERR("DlSendBDNum(BDs) =%u",DlSendBDNum);
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

int BSP_IPF_DlSend(void)
{
	return BSP_IPF_DlSend_n2(10000,60);
}
int BSP_IPF_ST_321(void)
{
    unsigned int s32Ret;
	unsigned int  para = 0;
	int tast_id = 0;
	
    s32Ret = IPF_ST_DL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return s32Ret;
    }
	/*起一个进程，不停地发东西*/

	tast_id = osl_task_init("IpfDlTask1", 32, 0x2000, (OSL_TASK_FUNC) BSP_IPF_DlSend, (void *)&para, &g_IpfUlTaskId);
	IPF_TEST_PRINT("task_id = %d\n", tast_id);
return OK;
}
int BSP_IPF_ST_321_n2(unsigned int sendtimes,unsigned int sendnum)
{
    unsigned int s32Ret;
    s32Ret = IPF_ST_DL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return s32Ret;
    }
	/*起一个进程，不停地发东西*/

	osl_task_init("IpfDlTask1", 32, 20000, (OSL_TASK_FUNC) BSP_IPF_DlSend_n2, 0, &g_IpfUlTaskId);
return OK;
}

/* 1个TTF结点，配1个BD 用于验证ADQ的rptr移动是否成功修正 */
int BSP_IPF_ST_331(void)
{
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    static IPF_CONFIG_DLPARAM_S stDlPara[IPF_ULBD_DESC_SIZE];
    TTF_MEM_ST stSrcTtf[IPF_ULBD_DESC_SIZE];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
    unsigned int u32Num = 2;
    int s32Ret = 0;
    unsigned int i;
	
    s32Ret = IPF_ST_DL_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return s32Ret;
    }
    u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
    {
        if(u32BDNum != IPF_DLBD_DESC_SIZE)
        {
            IPF_TEST_ERR(" %d :  dl queue not null u32BDNum = %d,  u32CDNum = %d\n"
            ,__LINE__, u32BDNum, u32CDNum);
        } 
    }
	
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return s32Ret;
    }

    memcpy_s(&stIPHeader, sizeof(StreamIPv4Header), &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy_s(&stUDP, sizeof(StreamUDP), &ipf_udp, sizeof(StreamUDP));
	
    stSrcTtf[0].usUsed = 200;
    stSrcTtf[1].usUsed = 1200;

    for(i=0; i<2; i++)    
    {
	    stSrcTtf[i].pData = osl_cachedma_malloc(stSrcTtf[i].usUsed);
	    stSrcTtf[i].pNext = NULL;
	    if(stSrcTtf[i].pData == NULL)
	    {
	        IPF_TEST_PRINT(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
	        return ERROR;
	    }
		
	    memset_s(stSrcTtf[i].pData, stSrcTtf[i].usUsed, 0x0, stSrcTtf[i].usUsed);
	    memcpy_s(stSrcTtf[i].pData, sizeof(StreamIPv4Header), &stIPHeader, sizeof(StreamIPv4Header));
	    memcpy_s(stSrcTtf[i].pData+sizeof(StreamIPv4Header), sizeof(StreamUDP), &stUDP, sizeof(StreamUDP));
	    
	    stDlPara[i].u32Data = (unsigned int)(&stSrcTtf[i]);
	    stDlPara[i].u16UsrField1= 200;
	    stDlPara[i].u16Len= stSrcTtf[i].usUsed;

	    /*设中断，仅搬移*/
	    stDlPara[i].u16Attribute= 0x29; 
	    osl_cache_flush(OSL_DATA_CACHE,stSrcTtf[i].pData,stSrcTtf[i].usUsed);
    }

	mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
						   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
	
    s32Ret = mdrv_ipf_config_dlbd(u32Num, stDlPara);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_dlbd :%d\n",__LINE__);
        goto error1;
    } 
    delay(20);
	
    return OK;
    
error1:
    for(i=0; i<2; i++)    
    {
        osl_cachedma_free((void *)(stSrcTtf[i].pData));
    }
    return ERROR;
}

int BSP_IPF_ST_331_n(unsigned int n)
{	
	unsigned int ad0_rptr_last,ad0_rptr_current,ad1_rptr_last,ad1_rptr_current;
	ad0_rptr_last = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ0_RPTR_OFFSET);
	ad1_rptr_last = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ1_RPTR_OFFSET);
	while(n>0)
	{
		BSP_IPF_ST_331();
		delay(2);

		ad0_rptr_current = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ0_RPTR_OFFSET);
		ad1_rptr_current = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ1_RPTR_OFFSET);
		if((IPF_DLAD0_DESC_SIZE-1) == ad0_rptr_last)
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
		ad0_rptr_last = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ0_RPTR_OFFSET);
		
		if((IPF_DLAD1_DESC_SIZE-1) == ad1_rptr_last)
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
		ad1_rptr_last = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ1_RPTR_OFFSET);
		n--;
	}
	return IPF_SUCCESS;
}


int ipf_ccore_init_for_test(void)
{
    unsigned int u32BDSize[IPF_CHANNEL_MAX] = {IPF_ULBD_DESC_SIZE, IPF_DLBD_DESC_SIZE};
    unsigned int u32RDSize[IPF_CHANNEL_MAX] = {IPF_ULRD_DESC_SIZE, IPF_DLRD_DESC_SIZE};
    unsigned int u32ADCtrl[IPF_CHANNEL_MAX] = {IPF_ADQ_DEFAULT_SEETING,IPF_ADQ_DEFAULT_SEETING};

    unsigned int u32IntMask0 = 0;
    unsigned int u32IntMask1 = 0;
    unsigned int u32ChanCtrl[IPF_CHANNEL_MAX] = {0,0};
    unsigned int u32IntStatus = 0;
    unsigned int u32Timeout = 0;
   // unsigned int u32IntGate = 0;
    unsigned int u32DMAOutstanding = 3;	

	IPF_UL_S g_stIpfUl = {0};
	IPF_DL_S g_stIpfDl = {0};

    /* 初始化全局结构体 */
    memset_s((void*)IPF_ULBD_MEM_ADDR, SHM_SIZE_IPF - IPF_DLDESC_SIZE, 0x0, SHM_SIZE_IPF - IPF_DLDESC_SIZE);/* [false alarm]:fortify disable */

    g_stIpfUl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_ULBD_MEM_ADDR;
    g_stIpfUl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_ULRD_MEM_ADDR;
    g_stIpfUl.pstIpfADQ0 = (IPF_AD_DESC_S*)IPF_ULAD0_MEM_ADDR;
    g_stIpfUl.pstIpfADQ1 = (IPF_AD_DESC_S*)IPF_ULAD1_MEM_ADDR;
    g_stIpfUl.pu32IdleBd = (unsigned int*)IPF_ULBD_IDLENUM_ADDR;
    *(unsigned int*)IPF_ULBD_IDLENUM_ADDR = IPF_ULBD_DESC_SIZE;
    
    g_stIpfDl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_DLBD_MEM_ADDR;
    g_stIpfDl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_DLRD_MEM_ADDR;
    g_stIpfDl.pstIpfADQ0 = (IPF_AD_DESC_S*)IPF_DLAD0_MEM_ADDR;
    g_stIpfDl.pstIpfADQ1 = (IPF_AD_DESC_S*)IPF_DLAD1_MEM_ADDR;
    g_stIpfDl.pstIpfCDQ = (IPF_CD_DESC_S*)IPF_DLCD_MEM_ADDR;
    g_stIpfDl.u32IpfCdRptr = (unsigned int*) IPF_DLCDRPTR_MEM_ADDR;
    *(g_stIpfDl.u32IpfCdRptr) = 0;

    g_stIpfDl.u32IdleBd = IPF_DLBD_DESC_SIZE;
	
    
    /* 配置扩展过滤器的起始地址 */	
    ipf_writel((unsigned int)IPF_EXT_FILTER_ADDR, ipf_base_addr_ccore + HI_IPF_EF_BADDR_OFFSET);
    
    /* 配置超时配置寄存器，使能超时中断，设置超时时间 */
    u32Timeout = TIME_OUT_CFG | (TIME_OUT_ENABLE);
    ipf_writel(u32Timeout, ipf_base_addr_ccore + HI_IPF_TIME_OUT_OFFSET);

    /* 配置时钟门控配置寄存器，设置为自动门控*/
    //u32IntGate = GATE_CFG;
#if (defined(BSP_CONFIG_PHONE_TYPE))
 	//ipf_writel(u32IntGate, HI_IPF_REGBASE_ADDR_VIRT + HI_IPF_GATE_OFFSET);/* [false alarm]:fortify disable */
#endif
    /* 清除上下行队列 */
    u32ChanCtrl[IPF_CHANNEL_UP] = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET);
    u32ChanCtrl[IPF_CHANNEL_UP] |= 0x30;
    ipf_writel(u32ChanCtrl[IPF_CHANNEL_UP], ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET);

    u32ChanCtrl[IPF_CHANNEL_DOWN] = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET);
    u32ChanCtrl[IPF_CHANNEL_DOWN] |= 0x30;
    ipf_writel(u32ChanCtrl[IPF_CHANNEL_DOWN], ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET);

    /* 配置上行通道的AD、BD和RD深度 */
    ipf_writel(u32BDSize[IPF_CHANNEL_UP]-1, ipf_base_addr_ccore + HI_IPF_CH0_BDQ_SIZE_OFFSET);
    ipf_writel(u32RDSize[IPF_CHANNEL_UP]-1, ipf_base_addr_ccore + HI_IPF_CH0_RDQ_SIZE_OFFSET);
    ipf_writel(u32ADCtrl[IPF_CHANNEL_UP], ipf_base_addr_ccore + HI_IPF_CH0_ADQ_CTRL_OFFSET);

    /* 上行通道的BD和RD起始地址*/    
    ipf_writel((unsigned int)g_stIpfUl.pstIpfBDQ, ipf_base_addr_ccore + HI_IPF_CH0_BDQ_BADDR_OFFSET);
    ipf_writel((unsigned int)g_stIpfUl.pstIpfRDQ, ipf_base_addr_ccore + HI_IPF_CH0_RDQ_BADDR_OFFSET);
    ipf_writel((unsigned int)g_stIpfUl.pstIpfADQ0, ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_BASE_OFFSET);
    ipf_writel((unsigned int)g_stIpfUl.pstIpfADQ1, ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_BASE_OFFSET);
	
    /* 配置中断屏蔽,只开5个中断，结果上报，结果超时，RD下溢，AD0、AD1空 */
    u32IntMask0 = IPF_INT_OPEN0;  /* 0号为Modem CPU */
    u32IntMask1 = IPF_INT_OPEN1;
    ipf_writel(u32IntMask0, ipf_base_addr_ccore + HI_IPF_INT_MASK0_OFFSET);
    ipf_writel(u32IntMask1, ipf_base_addr_ccore + HI_IPF_INT_MASK1_OFFSET);

    /* 清中断 */
    u32IntStatus = ipf_readl(ipf_base_addr_ccore + HI_IPF_INT_STATE_OFFSET);
    ipf_writel(u32IntStatus, ipf_base_addr_ccore + HI_IPF_INT_STATE_OFFSET);
    /*开DMA通道的Outstanding读写*/
    ipf_writel(u32DMAOutstanding, ipf_base_addr_ccore + HI_IPF_DMA_CTRL1_OFFSET);


    IPF_TEST_PRINT("[IPF] ipf init success\n");
	
    return IPF_SUCCESS;
    
}

//5xx ccore rest
/*ipf数传复位回调测试，
主要用于测试数传停止是否成功
进行数传，预期返回失败*/
void BSP_IPF_ST_501_CCORE(void)
{
    static IPF_CONFIG_DLPARAM_S stDlPara[IPF_ULBD_DESC_SIZE];	
    int s32Ret;
    /*调用ConfigUpFilter*/
    s32Ret = mdrv_ipf_config_dlbd(5, stDlPara);

    if(s32Ret != BSP_ERR_IPF_CCORE_RESETTING)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_dlbd :%d s32Ret = %x\n",__LINE__, s32Ret);
    }    
}


#ifdef __cplusplus
}
#endif
