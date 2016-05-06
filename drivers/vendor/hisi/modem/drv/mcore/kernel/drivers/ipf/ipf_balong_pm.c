/*************************************************************************
*   版权所有(C) 1987-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  ipf_balong_pm.c
*
*   作    者 :  chendongyue
*
*   描    述 :  IPF的低功耗接口，运行于m3
*
*   修改记录 :  2013年4月23日v1.00 chendongyue 创建
*
*************************************************************************/

/*lint -save -e18 -e156 -e438 -e740 -e830*/

#include "bsp_ipf.h"
#include "bsp_psam.h"
#include "ipf_balong.h"
#include <libfdt.h>

#define IPF_ADDR_LIMIT_REGS_CNT		10

void *g_ipf_reg_base = NULL;
static unsigned int ipf_addr_limit = 0;
static char* compatible = "hisilicon,ipf_balong_m3";
/**************************************************************************
ipf 寄存器恢复顺序:
1.控制，配置
2.描述符队列读写指针(三种描述符队列之间没有顺序)
	AD:先写入rptr(需回退)后写入wptr(不需回退)
	BD、RD:不必备份、恢复写入，可直接归0
3.通道使能
***************************************************************************/
#ifndef CONFIG_IPF_PROPERTY_MBB
__ao_data unsigned int g_u32_ipf_setting_bak_space[20];
__ao_data unsigned int g_u32_ipf_adq_rptr_bak_space[8];
__ao_data unsigned int g_u32_ipf_adq_wptr_chctrl_bak_space[9];
__ao_data unsigned int g_u32_ipf_addr_limit_bak_space[IPF_ADDR_LIMIT_REGS_CNT];

__ao_data unsigned int* g_u32_ipf_setting_bak_addr = g_u32_ipf_setting_bak_space;
__ao_data unsigned int* g_u32_ipf_adq_rptr_bak_addr = g_u32_ipf_adq_rptr_bak_space;
__ao_data unsigned int* g_u32_ipf_adq_wptr_chctrl_bak_addr = g_u32_ipf_adq_wptr_chctrl_bak_space;
__ao_data unsigned int* g_u32_ipf_addr_limit_bak_addr = g_u32_ipf_addr_limit_bak_space;

#else

__ao_data unsigned int* g_u32_ipf_setting_bak_addr = (unsigned int*)IPF_PWRCTL_INFO_ADDR;
__ao_data unsigned int* g_u32_ipf_adq_rptr_bak_addr = (unsigned int*)IPF_PWRCTL_ADQ_WPTR_INFO_ADDR;
__ao_data unsigned int* g_u32_ipf_adq_wptr_chctrl_bak_addr = (unsigned int*)IPF_PWRCTL_ADQ_RPTR_CHCTRL_ADDR;
__ao_data unsigned int* g_u32_ipf_addr_limit_bak_addr = (unsigned int*)IPF_PWRCTL_ADDR_LIMIT_ADDR;

#endif

#ifdef CONFIG_BALONG_MODEM_RESET
__ao_data unsigned int g_u32_ipf_ccore_reset_flag = IPF_FORRESET_CONTROL_ALLOW;
#endif

__ao_data unsigned int g_ipf_setting_table[] =
{
    HI_IPF_CTRL_OFFSET,
    HI_IPF_GATE_OFFSET,
    HI_IPF_DMA_CTRL1_OFFSET,
    HI_IPF_EF_BADDR_OFFSET,

    HI_IPF_CH0_CTRL_OFFSET,
    HI_IPF_CH1_CTRL_OFFSET,		
		
    HI_IPF_CH0_BDQ_SIZE_OFFSET,
    HI_IPF_CH1_BDQ_SIZE_OFFSET,
    
    HI_IPF_CH0_RDQ_SIZE_OFFSET,
    HI_IPF_CH1_RDQ_SIZE_OFFSET,
    
    HI_IPF_CH0_BDQ_BADDR_OFFSET,
    HI_IPF_CH1_BDQ_BADDR_OFFSET,
    
    HI_IPF_CH0_RDQ_BADDR_OFFSET,
    HI_IPF_CH1_RDQ_BADDR_OFFSET,
    
    HI_IPF_CH0_ADQ0_BASE_OFFSET, 
    HI_IPF_CH0_ADQ1_BASE_OFFSET, 
    
    HI_IPF_CH1_ADQ0_BASE_OFFSET,  
    HI_IPF_CH1_ADQ1_BASE_OFFSET, 
    
    HI_IPF_TIME_OUT_OFFSET,
    HI_IPF_PKT_LEN_OFFSET
};

__ao_data unsigned int g_ipf_adq_rptr_table[] =
{
    HI_IPF_CH0_ADQ0_RPTR_OFFSET, 
    HI_IPF_CH0_ADQ1_RPTR_OFFSET, 
    HI_IPF_CH1_ADQ0_RPTR_OFFSET, 
    HI_IPF_CH1_ADQ1_RPTR_OFFSET, 
    
    HI_IPF_CH0_ADQ0_STAT_OFFSET, 
    HI_IPF_CH0_ADQ1_STAT_OFFSET, 
    HI_IPF_CH1_ADQ0_STAT_OFFSET, 
    HI_IPF_CH1_ADQ1_STAT_OFFSET
};

__ao_data unsigned int g_ipf_adq_wptr_chctrl_table[] =
{
    HI_IPF_CH0_ADQ0_WPTR_OFFSET, 
    HI_IPF_CH0_ADQ1_WPTR_OFFSET, 
    HI_IPF_CH1_ADQ0_WPTR_OFFSET, 
    HI_IPF_CH1_ADQ1_WPTR_OFFSET, 

    HI_IPF_CH0_ADQ_CTRL_OFFSET,
    HI_IPF_CH1_ADQ_CTRL_OFFSET,
    HI_IPF_INT_MASK0_OFFSET,
    HI_IPF_INT_MASK1_OFFSET,		
    HI_IPF_CH_EN_OFFSET
};

__ao_data unsigned int g_ipf_addr_limit_table[] =
{
	//addr limit
    HI_IPF_MST_REGION0_START_OFFSET,
	HI_IPF_MST_REGION0_END_OFFSET,
	HI_IPF_MST_REGION1_START_OFFSET,
	HI_IPF_MST_REGION1_END_OFFSET,
	HI_IPF_MST_REGION2_START_OFFSET,
	HI_IPF_MST_REGION2_END_OFFSET,
	HI_IPF_MST_REGION3_START_OFFSET,
	HI_IPF_MST_REGION3_END_OFFSET,
	HI_IPF_MST_DEFAULT_OFFSET,
	HI_IPF_MST_SECCTRL_OFFSET
};

#ifdef CONFIG_BALONG_MODEM_RESET
/*****************************************************************************
* 函 数 名  : bsp_ipf_reset_ccore_lpm3_cb
*
* 功能描述  : 在ccore单独复位流程中，设置ipf reset标记
*
* 输入参数  : 
*             
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2012年11月29日   z00212992  创建
*****************************************************************************/
int bsp_ipf_reset_ccore_lpm3_cb(DRV_RESET_CB_MOMENT_E eparam, int userdata)
{
	if(MDRV_RESET_CB_BEFORE == eparam)
	{
		g_u32_ipf_ccore_reset_flag = IPF_FORRESET_CONTROL_FORBID;
	}
	else if(MDRV_RESET_CB_AFTER == eparam)
	{
		g_u32_ipf_ccore_reset_flag = IPF_FORRESET_CONTROL_ALLOW;
	}
	return IPF_SUCCESS;
}
#endif
/*****************************************************************************
* 函 数 名  : bsp_ipf_init
*
* 功能描述  : m core init function.
*
* 输入参数  : void
*             
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2014-8-30  l00265142  created
*****************************************************************************/
int	bsp_ipf_init(void)
{
    struct device_node *node;
	node = of_find_compatible_node(NULL, NULL, compatible);
	if (!node)
	{
		return ERROR;
	}

	g_ipf_reg_base = of_iomap(node, 0);
	if (NULL == g_ipf_reg_base)
	{
		return ERROR;
	}

	(void)of_property_read_u32_array(node, "addr_limit", &ipf_addr_limit, 1);

	return 0;
}

/*****************************************************************************
* 函 数 名  : ipf_drx_restore_adq_rptr
*
* 功能描述  : 根据adq状态寄存器回退adq读指针
*
* 输入参数  : u32Index ADQ序列
*             
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2012年11月29日   z00212992  创建
*****************************************************************************/
static void ipf_drx_restore_adq_rptr(void)
{
    unsigned int u32Index = 0;
    unsigned int u32RptrValue = 0;
    unsigned int u32RptrOffsetValue = 0; 
    unsigned int u32AdqRptrMaxNum[4]  = {IPF_ULAD0_DESC_SIZE,
                                                  IPF_ULAD1_DESC_SIZE,
                                                  IPF_DLAD0_DESC_SIZE,
                                                  IPF_DLAD1_DESC_SIZE};
    unsigned int u32ADCtrl[IPF_CHANNEL_MAX] = {IPF_ADQ_OFF,IPF_ADQ_OFF};

    /*写入ADQ长度但不使能ADQ通道，用于防止产生ADQ中断*/
    ipf_writel(u32ADCtrl[IPF_CHANNEL_UP], (unsigned int)g_ipf_reg_base + HI_IPF_CH0_ADQ_CTRL_OFFSET);
    ipf_writel(u32ADCtrl[IPF_CHANNEL_DOWN], (unsigned int)g_ipf_reg_base + HI_IPF_CH1_ADQ_CTRL_OFFSET);

    for(u32Index = 0; u32Index < 4; u32Index++)
    {

        u32RptrValue = g_u32_ipf_adq_rptr_bak_addr[u32Index];

        if(u32RptrValue >= u32RptrOffsetValue)
        {
            u32RptrValue = u32RptrValue - u32RptrOffsetValue;
        }
        else
        {
            u32RptrValue = u32AdqRptrMaxNum[u32Index] + u32RptrValue - u32RptrOffsetValue;
        }
        /* 更新ADQ状态寄存器/读指针寄存器 */
        ipf_writel(u32RptrValue, (unsigned int)g_ipf_reg_base + g_ipf_adq_rptr_table[u32Index]); 
    }
}

/*****************************************************************************
* 函 数 名       : ipf_drx_bak_reg
*
* 功能描述  : 提供的低功耗接口，保存IPF相关信息
*
* 输入参数  : 无
*             
* 输出参数  : 无
* 返 回 值     : IPF_SUCCESS     IPF可以下电，相关信息已经保存
*                           IPF_ERROR        IPF不可以下电
* 注意:该函数需要在锁中断的情况下调用
* 修改记录  : 2013年4月23日v1.00 chendongyue 创建
*****************************************************************************/
int ipf_drx_bak_reg(void)
{
    unsigned int* u32_addr = NULL;
    unsigned int i = 0;
    unsigned int u32_total = 0;
    unsigned int u32_ul_state = 0;
    unsigned int u32_dl_state = 0;
    unsigned int u32ADCtrl[IPF_CHANNEL_MAX] = {0,0};

#ifdef CONFIG_BALONG_MODEM_RESET
    if(IPF_FORRESET_CONTROL_ALLOW != g_u32_ipf_ccore_reset_flag)
    {
        return IPF_SUCCESS;
    }
#endif
	
    /* 判断上行IPF是否空闲 */    
    u32_ul_state = ipf_readl((unsigned int)g_ipf_reg_base + HI_IPF_CH0_STATE_OFFSET);

    if(u32_ul_state != IPF_CHANNEL_STATE_IDLE)
    {
        return IPF_ERROR;
    }

    /* 判断下行IPF是否空闲 */  	    
    u32_dl_state = ipf_readl((unsigned int)g_ipf_reg_base + HI_IPF_CH1_STATE_OFFSET);

    if(u32_dl_state != IPF_CHANNEL_STATE_IDLE)
    {
        return IPF_ERROR;
    }

#ifdef CONFIG_PSAM
	if(psam_bakup_reg() != 0){
		return IPF_ERROR;
	}
#endif
	
    u32ADCtrl[IPF_CHANNEL_UP] = ipf_readl((unsigned int)g_ipf_reg_base + HI_IPF_CH0_ADQ_CTRL_OFFSET);
	u32ADCtrl[IPF_CHANNEL_UP] &= IPF_ADQ_EN_MASK;
	u32ADCtrl[IPF_CHANNEL_UP] |= (IPF_NONE_ADQ_EN);

#ifndef CONFIG_PSAM
    u32ADCtrl[IPF_CHANNEL_DOWN] = ipf_readl((unsigned int)g_ipf_reg_base + HI_IPF_CH1_ADQ_CTRL_OFFSET);
    u32ADCtrl[IPF_CHANNEL_DOWN] &= IPF_ADQ_EN_MASK;
    u32ADCtrl[IPF_CHANNEL_DOWN] |= (IPF_NONE_ADQ_EN);
#endif

    /*关闭ADQ通道，用于防止产生ADQ预取*/
    ipf_writel(u32ADCtrl[IPF_CHANNEL_UP], (unsigned int)g_ipf_reg_base + HI_IPF_CH0_ADQ_CTRL_OFFSET);

#ifndef CONFIG_PSAM
    ipf_writel(u32ADCtrl[IPF_CHANNEL_DOWN], (unsigned int)g_ipf_reg_base + HI_IPF_CH1_ADQ_CTRL_OFFSET);
#endif

    /* 保存必要的寄存器 */
    u32_total = sizeof(g_ipf_setting_table)/sizeof(unsigned int);
    u32_addr = g_u32_ipf_setting_bak_addr;
    
    for(i=0; i<u32_total; i++)
    {
        *u32_addr = ipf_readl(g_ipf_setting_table[i] + (unsigned int)g_ipf_reg_base);
        u32_addr ++;
    }

	/* save addr limit regs */
	if(ipf_addr_limit){
		u32_total = sizeof(g_ipf_addr_limit_table)/sizeof(unsigned int);
	    u32_addr = g_u32_ipf_addr_limit_bak_addr;

	    for(i=0; i<u32_total; i++)
	    {
	        *u32_addr = ipf_readl(g_ipf_addr_limit_table[i] + (unsigned int)g_ipf_reg_base);
	        u32_addr ++;
	    }
	}
	
    u32_total = sizeof(g_ipf_adq_wptr_chctrl_table)/sizeof(unsigned int);
    u32_addr = g_u32_ipf_adq_wptr_chctrl_bak_addr;
	
    /* 单独保存ADQ_Wptr寄存器和状态寄存器，该组寄存器需要特殊处理 */
    for(i=0; i<u32_total; i++)
    {
        *u32_addr = ipf_readl(g_ipf_adq_wptr_chctrl_table[i] + (unsigned int)g_ipf_reg_base);
        u32_addr ++;
    }
	
    /*由于上电配置顺序问题，备份剩余的寄存器*/
    u32_total = sizeof(g_ipf_adq_rptr_table)/sizeof(unsigned int);
    u32_addr = g_u32_ipf_adq_rptr_bak_addr;


    /* 单独保存ADQ_Rptr寄存器和状态寄存器，该寄存器需要特殊处理 */
    for(i=0; i<u32_total; i++)
    {
        *u32_addr = ipf_readl(g_ipf_adq_rptr_table[i] + (unsigned int)g_ipf_reg_base);
        u32_addr ++;
    }

    return IPF_SUCCESS;
}

#ifdef CONFIG_IPF_PROPERTY_MBB
/*****************************************************************************
* 函 数 名       : ipf_drx_restore_filter
*
* 功能描述  : 提供的低功耗接口，用于IPF上电恢复
*
* 输入参数  : 无
*             
* 输出参数  : 无
* 返 回 值     : 无
*
* 注意:该函数需要在锁中断的情况下调用
* 修改记录  : 2013年4月23日v1.00 chendongyue 创建
*****************************************************************************/
int ipf_drx_restore_filter(void)
{
    unsigned int i,j,k,filter_serial;
    IPF_MATCH_INFO_S* pstMatchInfo;
    unsigned int match_info;
    unsigned int* match_info_addr = (unsigned int *)(IPF_PWRCTL_BASIC_FILTER_ADDR);

    for(i=0 ; i < IPF_MODEM_MAX; i++)
    {
        match_info_addr = (unsigned int *)(IPF_PWRCTL_BASIC_FILTER_ADDR + i*sizeof(IPF_MATCH_INFO_S));
        pstMatchInfo = (IPF_MATCH_INFO_S*)match_info_addr;
        filter_serial = i;
        k = 0;
        do
        {
            if(filter_serial < IPF_BF_NUM)
            {
                ipf_writel(filter_serial, (unsigned int)g_ipf_reg_base + HI_BFLT_INDEX_OFFSET); 
                for(j=0; j<(sizeof(IPF_MATCH_INFO_S)/4); j++)
                {
                        match_info = *(match_info_addr+j);
                        ipf_writel((match_info), ((unsigned int)g_ipf_reg_base+HI_FLT_LOCAL_ADDR0_OFFSET+j*4)); 
                }
                k++;
            }
            filter_serial = pstMatchInfo->unFltChain.Bits.u16NextIndex;
            pstMatchInfo = (IPF_MATCH_INFO_S*)(IPF_PWRCTL_BASIC_FILTER_ADDR + filter_serial*sizeof(IPF_MATCH_INFO_S));
            match_info_addr = (unsigned int *)pstMatchInfo;
            if(k >= IPF_BF_NUM)
            {
                break;
            }
        }while(filter_serial != IPF_TAIL_INDEX);
    }
    return IPF_SUCCESS;
}
#endif

/*****************************************************************************
* 函 数 名       : ipf_drx_restore_reg
*
* 功能描述  : 提供的低功耗接口，用于IPF上电恢复
*
* 输入参数  : 无
*             
* 输出参数  : 无
* 返 回 值     : 无
*
* 注意:该函数需要在锁中断的情况下调用
* 修改记录  : 2013年4月23日v1.00 chendongyue 创建
*****************************************************************************/
void ipf_drx_restore_reg(void)
{
    unsigned int* u32_addr;
    unsigned int i = 0;
    unsigned int u32_total = 0;
    u32_addr = (unsigned int*)IPF_PWRCTL_INFO_ADDR;

#ifdef CONFIG_BALONG_MODEM_RESET
    if(IPF_FORRESET_CONTROL_ALLOW != g_u32_ipf_ccore_reset_flag)
    {
        return;
    }
#endif

     /* 复位IPF */
    ipf_writel(1, (unsigned int)g_ipf_reg_base + HI_IPF_SRST_OFFSET); 

    /* 解除复位 */
    ipf_writel(0, (unsigned int)g_ipf_reg_base + HI_IPF_SRST_OFFSET); 

    u32_total = sizeof(g_ipf_setting_table)/sizeof(unsigned int);
    u32_addr = g_u32_ipf_setting_bak_addr;

    for(i=0; i<u32_total; i++)
    {
        ipf_writel(*u32_addr, (g_ipf_setting_table[i]+(unsigned int)g_ipf_reg_base));        
        u32_addr ++;
    }

	//resetore addr limit regs
	if(ipf_addr_limit){
		u32_total = sizeof(g_ipf_addr_limit_table)/sizeof(unsigned int);
	    u32_addr = g_u32_ipf_addr_limit_bak_addr;

	    for(i=0; i<u32_total; i++)
	    {
	        ipf_writel(*u32_addr, (g_ipf_addr_limit_table[i]+(unsigned int)g_ipf_reg_base));        
	        u32_addr ++;
	    }
	}
	
#ifdef CONFIG_IPF_PROPERTY_MBB
    ipf_drx_restore_filter();
#endif
    ipf_drx_restore_adq_rptr();

    u32_total = sizeof(g_ipf_adq_wptr_chctrl_table)/sizeof(unsigned int);
    u32_addr = g_u32_ipf_adq_wptr_chctrl_bak_addr;

    for(i=0; i<4; i++)
    {
        ipf_writel(*u32_addr, (g_ipf_adq_wptr_chctrl_table[i] + (unsigned int)g_ipf_reg_base));        
        u32_addr ++;
    }

    ipf_writel(((*u32_addr)|=IPF_BOTH_ADQ_EN), (HI_IPF_CH0_ADQ_CTRL_OFFSET + (unsigned int)g_ipf_reg_base));        
    u32_addr ++;
#ifdef CONFIG_PSAM 
	ipf_writel(*u32_addr, (HI_IPF_CH1_ADQ_CTRL_OFFSET + (unsigned int)g_ipf_reg_base)); 
#else
    ipf_writel(((*u32_addr)|=IPF_BOTH_ADQ_EN), (HI_IPF_CH1_ADQ_CTRL_OFFSET + (unsigned int)g_ipf_reg_base));        
#endif
	u32_addr ++;
    for(i=6; i<9; i++)
    {
        ipf_writel(*u32_addr, (g_ipf_adq_wptr_chctrl_table[i] + (unsigned int)g_ipf_reg_base));        
        u32_addr ++;
    }
#ifdef CONFIG_PSAM
	psam_restore_reg();
#endif
}

/*lint -restore*/
