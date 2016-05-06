/*************************************************************************
*   版权所有(C) 1987-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  ipf_balong.c
*
*   作    者 :  luting chendongyue
*
*   描    述 :  本文主要完成IP过滤接口函数，实现上行和下行的IP过滤功能
*
*   修改记录 :  2011年1月11日  v1.00  luting  创建
*                            2012年11月23日v2.00 chendongyue 修改
*                            2013年3月29日v2.10 chendongyue 修改
*                             2014年9月25日  v3.00 longyi修改，a/c核拆分
*************************************************************************/
/*lint -save -e429 -e529 -e534 -e550 -e650 -e661 -e715 -e537  -e737 -e539 -e574 -e239 -e438 -e701 -e740 -e958 -e451
-e64 -e732 -e740 -e801 -e830 -e530 -e775 -e414 -e525
*/

#ifdef __cplusplus
extern "C" {
#endif


#include <string.h>
#include <of.h>
#include <bsp_clk.h>
#include <bsp_hardtimer.h>
#include <osl_malloc.h>
#include <osl_irq.h>
#include <osl_thread.h>
#include "bsp_dpm.h"
#include "securec.h"
#include "bsp_pm_om.h"
#ifndef CONFIG_IPF_PROPERTY_MBB
#include <bsp_ipc.h>
#endif
#include <bsp_ipf.h>
#include <bsp_psam.h>
#include <ipf_balong.h>
#include <bsp_dump.h>

#include <bsp_sysctrl.h>
#include <bsp_reset.h>

/*C核启动(数传允许)标示*/
IPF_FORRESET_CONTROL_E* modem_reset_flag = NULL;
unsigned int reset_peri_crg[4] = {0,};

IPF_UL_S g_stIpfUl = {0};
IPF_DL_S g_stIpfDl = {0};

#ifdef CONFIG_PSAM
ipf_reg_s psam_para = {0};
#endif

/* 调试信息结构体 */
struct ipf_ctx g_ipf_ctx;

#ifndef CONFIG_IPF_PROPERTY_MBB
/*k3低功耗恢复标记*/
unsigned int* ipf_acore_init_status = NULL;
unsigned int* ipf_ccore_init_status = NULL;
#endif

IPF_MATCH_INFO_S* g_pstExFilterAddr;
IPF_ID_S* g_stIPFExtFreeList = NULL;
IPF_ID_S* g_stIPFBasicFreeList = NULL;
IPF_ID_S* g_stIPFFreeList = NULL;
IPF_ID_S* g_stIPFHeadList = NULL;
IPF_FILTER_INFO_S g_stIPFFilterInfo[IPF_FILTER_CHAIN_MAX_NUM];
IPF_PWRCTL_FILTER_INFO_S g_stIPFPwrCtlFilterInfo[IPF_FILTER_CHAIN_MAX_NUM];
unsigned int g_u32IPFPwrCtlStart = 0;
unsigned int g_u32IpfSwitchInt = 0;
spinlock_t ipf_filter_spinlock;
spinlock_t ipf_dlbd_spinlock;
unsigned int g_filter_delay_time = 10;
static struct ipf_memblk_offset memblk_offset;

unsigned int ipf_base_addr_ccore;
static unsigned int irqnum_ccore;
static struct dts_param_c ipf_ccore_dts;

IPF_TIMESTAMP_INFO_S g_ipf_ul_timestamp_info;
unsigned int g_ipf_dl_start_enable;
#define IPF_GET_TIMESTAMP_INFO() (&g_ipf_ul_timestamp_info)
#define IPF_START_STAMP_ENABLE (g_ipf_dl_start_enable)

#ifdef CONFIG_CCORE_PM

/*****************************************************************************
* 函 数 名     : ipf_ul_dpm_prepare
*
* 功能描述  : dpm进入准备函数
*
* 输入参数  : 设备指针
*   
* 输出参数  : 无
*
* 返 回 值     : IPF_ERROR 失败
                            IPF_SUCCESS 成功
*
* 修改记录  :2013年6月16日   陈东岳  创建
*****************************************************************************/
static int ipf_ul_dpm_prepare(struct dpm_device *dev)
{
    unsigned int u32_ul_state;

    /* 判断上行IPF是否空闲 */
    u32_ul_state = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_STATE_OFFSET);

    if(u32_ul_state != IPF_CHANNEL_STATE_IDLE)
    {
        /*bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r IPF CHANNEL NOT IDLE! \n");*/
        return IPF_ERROR;
    }

    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名     : ipf_ul_suspend
*
* 功能描述  : dpm桩函数
*
* 输入参数  : 设备指针
*   
* 输出参数  : 无
*
* 返 回 值     : 成功
*
* 修改记录  :2013年6月16日   陈东岳  创建
			2014年1月23日v1.01 陈东岳 修改 由于K3V3总线设计问题，
			无法在m3上进行低功耗恢复，移动到A9上进行。
*****************************************************************************/
static int ipf_ul_suspend(struct dpm_device *dev)
{
#ifndef CONFIG_IPF_PROPERTY_MBB

    unsigned long ipf_flags = 0;
	
    spin_lock_irqsave(&ipf_filter_spinlock, ipf_flags);
    bsp_ipc_spin_lock(IPC_SEM_IPF_PWCTRL);
    *ipf_ccore_init_status = IPF_PWC_DOWN;
    cache_sync();		
    bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
    spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);

#endif
    g_ipf_ctx.status->suspend++;
	return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名     : ipf_ul_resume
*
* 功能描述  : dpm桩函数
*
* 输入参数  : 设备指针
*   
* 输出参数  : 无
*
* 返 回 值     : 成功
*
* 修改记录  :2013年6月16日   陈东岳  创建
*****************************************************************************/
static int ipf_ul_resume(struct dpm_device *dev)
{
	unsigned int status;
	status = ipf_readl(ipf_base_addr_ccore + HI_IPF_INT0_OFFSET); 
	if (status & (IPF_UL_RPT_INT0 \
					| IPF_UL_TIMEOUT_INT0 \
					| IPF_UL_ADQ0_EPTY_INT0 \
					| IPF_UL_ADQ1_EPTY_INT0)) {
		g_ipf_ctx.status->resume_with_intr++;
	}
    g_ipf_ctx.status->resume++;
	return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名     : ipf_ul_dpm_complete
*
* 功能描述  : dpm桩函数
*
* 输入参数  : 设备指针
*   
* 输出参数  : 无
*
* 返 回 值     : 成功
*
* 修改记录  :2013年6月16日   陈东岳  创建
*****************************************************************************/
static int ipf_ul_dpm_complete(struct dpm_device *dev)
{
	return IPF_SUCCESS;
}

struct dpm_device ipf_dpm_device={
	.device_name = "ipf_dpm",
	.prepare = ipf_ul_dpm_prepare,
	.suspend_late = NULL,
	.suspend = ipf_ul_suspend,
	.resume = ipf_ul_resume,
	.resume_early = NULL,
	.complete = ipf_ul_dpm_complete,
};

#endif


int bsp_ipf_srest(void)
{
	int tmp_cnt = 10000;
	/*reset*/
	ipf_writel(1, ipf_base_addr_ccore + HI_IPF_SRST_OFFSET);

	while(!ipf_readl(ipf_base_addr_ccore + HI_IPF_SRST_STATE_OFFSET)){
		tmp_cnt--;
		if(!tmp_cnt){
			return -1;
		}
	}	
	/*start*/
	ipf_writel(0, ipf_base_addr_ccore + HI_IPF_SRST_OFFSET);

    ipf_writel(IPF_INT_OPEN0, ipf_base_addr_ccore + HI_IPF_INT_MASK0_OFFSET);
    ipf_writel(IPF_INT_OPEN1, ipf_base_addr_ccore + HI_IPF_INT_MASK1_OFFSET);
	return 0;
}
void bsp_ipf_dl_rpt1_switch(int value)
{
	unsigned int tmp = 0;
	tmp = ipf_readl(ipf_base_addr_ccore + HI_IPF_INT_MASK1_OFFSET);
	tmp = value?(tmp | 0x30000):(tmp & 0xfffcffff);
	ipf_writel(tmp, ipf_base_addr_ccore + HI_IPF_INT_MASK1_OFFSET);
}

/*
 * On ARMv5 and above those functions can be implemented around
 * the clz instruction.
 * refer to kernel/arch/arm/include/asm/bitops.h
 * put the code here for both vxWorks and linux version.
 */
static inline unsigned int ipf_fls(unsigned int x)
{
    unsigned int ret;

    asm("clz\t%0, %1" : "=r" (ret) : "r" (x));
    ret = 32 - ret;
    return ret;
}

static int get_ipf_ccore_dts(void)
{
	struct device_node *dev = NULL;
	const char *name = "hisilicon,ipf_balong_mdm";

 	dev = of_find_compatible_node(NULL, NULL, name);
	if(NULL == dev)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"device node not found\n");
		return IPF_ERROR;
	}
	
    ipf_ccore_dts.addr = (unsigned int)of_iomap(dev, 0);
	if(!ipf_ccore_dts.addr)
		return IPF_ERROR;

    ipf_ccore_dts.irqnum0 = irq_of_parse_and_map(dev, 0);
	if(!ipf_ccore_dts.irqnum0)
		return IPF_ERROR;
	
    irqnum_ccore = ipf_ccore_dts.irqnum0;
    ipf_base_addr_ccore  = ipf_ccore_dts.addr;
	


	/*only dallas platform need to reset ipf by peri_crg before going to start.*/
	(void)of_property_read_u32_array(dev, "rst_crg", reset_peri_crg, 4);
	bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_IPF,"reset_peri_crg %x, %x\n", reset_peri_crg[0],reset_peri_crg[1]);

	(void)of_property_read_u32_array(dev, "addr_limit", &(g_ipf_ctx.addr_limit), 1);
	(void)of_property_read_u32_array(dev, "addr_limit_off", &(g_ipf_ctx.addr_limit_off), 1);
	
	return 0;
}

static inline void ipf_record_start_time_stamp(unsigned int en, unsigned int* rec_point)
{
    if (!en) {
        return;
    }
    *rec_point = bsp_get_slice_value_hrt();
    return;
}

static inline void ipf_record_end_time_stamp(unsigned int en, unsigned int beg_time)
{
    unsigned int diff_time;
    IPF_TIMESTAMP_INFO_S* stamp_info = IPF_GET_TIMESTAMP_INFO();
    unsigned int idx;

    if (!en) {
        return;
    }

    diff_time = bsp_get_slice_value_hrt() - beg_time;

    /* avoid to record the overflowed value */
    if (diff_time > IPF_MAX_TIME_LIMIT) {
        stamp_info->overflow++;
    }
    else {
        if (diff_time > stamp_info->diff_max)
            stamp_info->diff_max = diff_time;

        stamp_info->diff_sum += diff_time;
        stamp_info->cnt_sum++;

        /* find the first bit not zero */
        idx = ((ipf_fls(diff_time)-1) & IPF_FLS_MASK);
        stamp_info->diff_order_cnt[idx]++;
    }
}

static inline unsigned int ipf_calc_percent(unsigned int value, unsigned int sum)
{
    if (0 == sum) {
        return 0;
    }
    return (value * 100 / sum);
}

static void ipf_get_version(void)
{
	unsigned int ver = 0;
	ver = ipf_readl(ipf_base_addr_ccore + HI_IPF_VERSION_OFFSET);
	
	switch(ver){
	case IPF_VER_120A:
		g_ipf_ctx.ipf_version = IPF_VERSION_120a;
		break;
	case IPF_VER_130A:
		g_ipf_ctx.ipf_version = IPF_VERSION_130a;
		break;
	case IPF_VER_130B:
		g_ipf_ctx.ipf_version = IPF_VERSION_130b;
		break;
	case IPF_VER_140A:
		g_ipf_ctx.ipf_version = IPF_VERSION_140a;
		break;
	default:
		g_ipf_ctx.ipf_version = IPF_VERSION_0000;
		break;
	}
}

void ipf_enable_rd_rate(int en)
{
    g_ipf_ctx.status->rate_en = en;
    return;
}

void ipf_enable_ul_time_stamp(int en)
{
    g_ipf_ctx.status->timestamp_en = en;
    return;
}

void ipf_clear_time_stamp(void)
{
    IPF_TIMESTAMP_INFO_S* stamp_info = IPF_GET_TIMESTAMP_INFO();

    memset_s(stamp_info, sizeof(IPF_TIMESTAMP_INFO_S), 0, sizeof(IPF_TIMESTAMP_INFO_S));/*[false alarm]:fortify*/
    return;
}

void ipf_dump_time_stamp(void)
{
    IPF_TIMESTAMP_INFO_S* stamp_info = IPF_GET_TIMESTAMP_INFO();
    unsigned int tmp = 0;
    int i;

    IPF_PRINT(" max diff:%u(%uus)\n",
              stamp_info->diff_max, stamp_info->diff_max*10/192);
    IPF_PRINT(" sum diff:%u(%uus)\n",
              stamp_info->diff_sum, stamp_info->diff_max/19);

    if (stamp_info->cnt_sum) {
        tmp = stamp_info->diff_sum / stamp_info->cnt_sum;
    }

    IPF_PRINT(" avg diff:%u(%uus)\n", tmp, tmp*10/192);

    for (i = 0; i < IPF_MAX_STAMP_ORDER; i++) {
        tmp = ipf_calc_percent(stamp_info->diff_order_cnt[i], stamp_info->cnt_sum);
        IPF_PRINT(" diff time (%u~%u) (%uus~%uus) count:%u (%u %%)\n",
            (0x80000000 >> (31-i)),
            (0xFFFFFFFF >> (31-i)),
            (0x80000000 >> (31-i))/19,
            (0xFFFFFFFF >> (31-i))/19,
            stamp_info->diff_order_cnt[i], tmp);
    }
    return;
}
/* IPF transfer time recorder end */

int mdrv_ipf_set_limited_addr(unsigned int start, unsigned int end)
{
	static unsigned int cnt = 0;
	unsigned int bak_reg = 0;

	if(cnt){
		return 0;
	}
	if(g_ipf_ctx.addr_limit_off){
		return 0;
	}
	
	if(g_ipf_ctx.addr_limit){
		if(start == end){
			g_ipf_ctx.ttf_addr_er++;
			return IPF_ERROR;
		}
		
		ipf_writel(start, ipf_base_addr_ccore + HI_IPF_MST_REGION0_START_OFFSET);
		ipf_writel(end, ipf_base_addr_ccore + HI_IPF_MST_REGION0_END_OFFSET);
		bak_reg = ipf_readl(ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
		ipf_writel(bak_reg|SECCTRL_VALID0, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);

		g_ipf_ctx.limit_reg_cnt |= SECCTRL_VALID0;
		if(g_ipf_ctx.limit_reg_cnt == SECCTRL_OPEN3 || g_ipf_ctx.limit_reg_cnt == SECCTRL_OPEN4){
			bak_reg = ipf_readl(ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
			ipf_writel(bak_reg & ~SECCTRL_BYPASS, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
		}
	}
	cnt = 1;
	
	return 0;
}

static void ipf_start_addr_limit(void)
{
	unsigned int reg_bak = 0;
	static int limit_set = 5;

	/*only set one times*/
	if(!limit_set){
		return;
	}

	if(g_ipf_ctx.addr_limit == 0){
		return;
	}
	if(g_ipf_ctx.addr_limit_off){
		return;
	}

	/*acore do not get limit addr*/
	if(g_ipf_ctx.sh_limit_addr->block_err){
		g_ipf_ctx.block_err++;
		return;
	}
	
	if(g_ipf_ctx.sh_limit_addr->block_sum){
		
		if(g_ipf_ctx.sh_limit_addr->block_sum > 2)
			return;
		
		g_ipf_ctx.limit_addr_set++;
		ipf_writel(g_ipf_ctx.sh_limit_addr->block1_start, ipf_base_addr_ccore + HI_IPF_MST_REGION2_START_OFFSET);
		ipf_writel(g_ipf_ctx.sh_limit_addr->block1_end, ipf_base_addr_ccore + HI_IPF_MST_REGION2_END_OFFSET);
		reg_bak = ipf_readl(ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
		
		if(g_ipf_ctx.sh_limit_addr->block_sum == 1){
			/*acore sep one block and enable limit func*/
			ipf_writel(reg_bak | SECCTRL_VALID2, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
			limit_set = 0;
			g_ipf_ctx.limit_reg_cnt |= SECCTRL_VALID2;
		}
		else{
			/*acore sep two blocks and enable limit func*/
			ipf_writel(g_ipf_ctx.sh_limit_addr->block2_start, ipf_base_addr_ccore + HI_IPF_MST_REGION3_START_OFFSET);
			ipf_writel(g_ipf_ctx.sh_limit_addr->block2_end, ipf_base_addr_ccore + HI_IPF_MST_REGION3_END_OFFSET);
			ipf_writel(reg_bak | SECCTRL_VALID2_3, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
			limit_set = 0;
			g_ipf_ctx.limit_reg_cnt |= SECCTRL_VALID2_3;
		}

		if(g_ipf_ctx.limit_reg_cnt == SECCTRL_OPEN3 || g_ipf_ctx.limit_reg_cnt == SECCTRL_OPEN4){
			reg_bak = ipf_readl(ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
			ipf_writel(reg_bak & ~SECCTRL_BYPASS, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
		}
		
		return;
	}
	limit_set--;
	return;
}

void ipf_write_basic_filter(unsigned int filter_hw_id, IPF_MATCH_INFO_S* match_infos)
{
    unsigned int j;
    unsigned int match_info;
    unsigned int* match_info_addr = (unsigned int*)match_infos;
    ipf_writel(filter_hw_id, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET);
    for(j=0; j<(sizeof(IPF_MATCH_INFO_S)/4); j++)
    {
        match_info = *(match_info_addr+j);
        ipf_writel((match_info), (ipf_base_addr_ccore+HI_FLT_LOCAL_ADDR0_OFFSET+j*4)); 
    }
}

static void ipf_dump_callback(void)
{
	int i;
	char* ptr;
	
	if (g_ipf_ctx.dump_reg) {
		writel(0, ipf_base_addr_ccore + HI_IPF_GATE_OFFSET);
		ptr = (char*)g_ipf_ctx.dump_reg;
		for(i = 0; i < IPF_REGS_SIZE; i += 4) {
			*(unsigned int*)(ptr + i) 
				= readl(ipf_base_addr_ccore + i);
		}
	}
}

void ipf_om_dump_init(void)
{

	g_ipf_ctx.dump_reg = (char*)bsp_dump_register_field(DUMP_CP_IPF, "IPF", 0, 0, 0x400, 0);
	
	if (!g_ipf_ctx.dump_reg) {
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "ipf backup mem for dump alloc failed\n");
		goto err;
	} else {
		g_ipf_ctx.status->dump_mem_alloc_ok = 1;
	}

    /* reg the dump callback to om */
	if (-1 == bsp_dump_register_hook("IPF", ipf_dump_callback)) {
	    goto err;
	}

    g_ipf_ctx.dump_size = 0x400;

    return;

err:
    g_ipf_ctx.dump_reg = NULL;
    g_ipf_ctx.dump_size = 0;
    return;
}

void ipf_reset_platform(void)
{
	unsigned int bak_reg=0;
	unsigned int res_status = 0;
	unsigned int pericrg_base_addr_virt = 0;
	
	/*get ipf syscrg base virtual addr*/
	pericrg_base_addr_virt = (unsigned int)bsp_sysctrl_addr_byindex(sysctrl_ap_pericrg);

	if(reset_peri_crg[0]){
		res_status = ipf_readl(pericrg_base_addr_virt + reset_peri_crg[2]);
		res_status &= reset_peri_crg[3];
		if(res_status){
			bak_reg = ipf_readl(pericrg_base_addr_virt + reset_peri_crg[1]);
			bak_reg |= reset_peri_crg[3];

			ipf_writel(bak_reg, pericrg_base_addr_virt + reset_peri_crg[1]);
		}
	}
}

static void reset_ipf_psam_from_sys(void)
{
#ifndef CONFIG_IPF_PROPERTY_MBB
	unsigned int regvalue = 0;
	unsigned int cnt = 1000;
	unsigned int hi_syscrg_base_addr_virt = 0;
	if(g_ipf_ctx.ipf_version >= IPF_VERSION_130b){
		hi_syscrg_base_addr_virt = (unsigned int)bsp_sysctrl_addr_byindex(sysctrl_ap_pericrg);
		regvalue = readl(hi_syscrg_base_addr_virt + reset_peri_crg[0]);
		regvalue |= reset_peri_crg[3];
		writel(regvalue, hi_syscrg_base_addr_virt + reset_peri_crg[0]);
		regvalue = readl(hi_syscrg_base_addr_virt + reset_peri_crg[1]);
		regvalue |= reset_peri_crg[3];
		writel(regvalue, hi_syscrg_base_addr_virt + reset_peri_crg[1]);
		do{
			regvalue = readl(hi_syscrg_base_addr_virt + reset_peri_crg[2]);
			regvalue &= reset_peri_crg[3];
			cnt--;
		}while((0x0 != regvalue) && cnt);
		if(!cnt){
			g_ipf_ctx.reset_time_out++;
		}
	}
#endif
}

static void ipf_fama_attr_set(void)
{
#ifndef CONFIG_IPF_PROPERTY_MBB
	if(g_ipf_ctx.ipf_version >= IPF_VERSION_140a){
		/*ul write : MODEM*/
		ipf_writel(IPF_FAMA_MODEM_ATTR ,ipf_base_addr_ccore + HI_IPF_CH0_WDATA_FAMA_ATTR_OFFSET);
		/*ul read : AP*/
		ipf_writel(IPF_FAMA_AP_ATTR ,ipf_base_addr_ccore + HI_IPF_CH0_RDATA_FAMA_ATTR_OFFSET);
		/*ul rd desc : SHARE DDR = MODEM*/
		ipf_writel(IPF_FAMA_MODEM_ATTR ,ipf_base_addr_ccore + HI_IPF_CH0_RD_FAMA_ATTR_OFFSET);
		/*ul bd desc : SHARE DDR = MODEM*/
		ipf_writel(IPF_FAMA_MODEM_ATTR ,ipf_base_addr_ccore + HI_IPF_CH0_BD_FAMA_ATTR_OFFSET);
		/*ul ad desc : SHARE DDR = MODEM*/
		ipf_writel(IPF_FAMA_MODEM_ATTR ,ipf_base_addr_ccore + HI_IPF_CH0_AD_FAMA_ATTR_OFFSET);
		/*ul cd desc : SHARE DDR = MODEM*/
		ipf_writel(IPF_FAMA_MODEM_ATTR ,ipf_base_addr_ccore + HI_IPF_CH0_CD_FAMA_ATTR_OFFSET);
		/*dl write : AP*/
		ipf_writel(IPF_FAMA_AP_ATTR ,ipf_base_addr_ccore + HI_IPF_CH1_WDATA_FAMA_ATTR_OFFSET);
		/*dl redirect read : MODEM*/
		ipf_writel(IPF_FAMA_MODEM_ATTR ,ipf_base_addr_ccore + HI_IPF_CH1_RDATA_FAMA_ATTR_OFFSET);
		/*dl rd desc : SHARE DDR = MODEM*/
		ipf_writel(IPF_FAMA_MODEM_ATTR ,ipf_base_addr_ccore + HI_IPF_CH1_RD_FAMA_ATTR_OFFSET);
		/*dl bd desc : SHARE DDR = MODEM*/
		ipf_writel(IPF_FAMA_MODEM_ATTR ,ipf_base_addr_ccore + HI_IPF_CH1_BD_FAMA_ATTR_OFFSET);
		/*dl ad desc : SHARE DDR = MODEM*/
		ipf_writel(IPF_FAMA_MODEM_ATTR ,ipf_base_addr_ccore + HI_IPF_CH1_AD_FAMA_ATTR_OFFSET);
		/*dl cd desc : SHARE DDR = MODEM*/
		ipf_writel(IPF_FAMA_MODEM_ATTR ,ipf_base_addr_ccore + HI_IPF_CH1_CD_FAMA_ATTR_OFFSET);
		/*extenerl filters : SHARE DDR = MODEM*/
		ipf_writel(IPF_FAMA_MODEM_ATTR ,ipf_base_addr_ccore + HI_IPF_EF_FAMA_ATTR_OFFSET);
		/*dl direct read : AP*/
		ipf_writel(IPF_FAMA_AP_ATTR ,ipf_base_addr_ccore + HI_IPF_CH1_DIRECT_RDATA_FAMA_ATTR_OFFSET);
	}
#endif
}

/*****************************************************************************
* 函 数 名      : ipf_init
*
* 功能描述  : IPF初始化     内部使用，不作为接口函数
*
* 输入参数  : void
* 输出参数  : 无
* 返 回 值     : IPF_SUCCESS    初始化成功
*                           IPF_ERROR      初始化失败
*
* 修改记录  :2011年1月21日   鲁婷  创建
				 2013年4月30日    陈东岳修改，将寄存器配置分配到两核 
*****************************************************************************/
int ipf_init(void)
{
    unsigned int u32BDSize[IPF_CHANNEL_MAX] = {IPF_ULBD_DESC_SIZE, IPF_DLBD_DESC_SIZE};
    unsigned int u32RDSize[IPF_CHANNEL_MAX] = {IPF_ULRD_DESC_SIZE, IPF_DLRD_DESC_SIZE};
    unsigned int u32ADCtrl[IPF_CHANNEL_MAX] = {IPF_ADQ_DEFAULT_SEETING,IPF_ADQ_DEFAULT_SEETING};
    unsigned int u32IntMask0 = 0;
    unsigned int u32IntMask1 = 0;
    unsigned int u32ChanCtrl[IPF_CHANNEL_MAX] = {0,0};
    unsigned int u32IntStatus = 0;
    unsigned int u32Timeout = 0;
    unsigned int u32IntGate = 0;
    unsigned int u32DMAOutstanding = 3;	
	unsigned int bak_reg=0;
#ifdef CONFIG_CCORE_PM
    unsigned int u32Result = 0;
#endif
		
	struct clk *c_ipfclk = NULL; 
	/*ipf enable clock*/
	c_ipfclk = clk_get(NULL, "ipf_clk");
	if(IS_ERR(c_ipfclk))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"ccore ipf clk get failed.\n");
		return -1;
	}

	if(0 !=clk_enable(c_ipfclk))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"ccore ipf clk open failed.\n");
		return -1;
	}

	if(IPF_ERROR == get_ipf_ccore_dts())
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r ccore ipf do not get dts data\n",0,0,0,0,0,0);
		return IPF_ERROR;
	}

#ifndef CONFIG_IPF_PROPERTY_MBB
    unsigned long ipf_flags = 0;
    ipf_flags = ipf_flags;
#endif

	ipf_get_version();
	g_ipf_ctx.sh_limit_addr = (IPF_LIMIT_ADDR_S *)IPF_TRANS_LIMIT_ADDR;

	ipf_reset_platform();
	modem_reset_flag = (IPF_FORRESET_CONTROL_E*)(IPF_INIT_ADDR+8);
	bsp_register_master_idle(IPF_IDLE, ccpu_reset_ipf_and_wait_idle);
	if(IPF_FORRESET_CONTROL_FORBID == bsp_ipf_get_control_flag_for_ccore_reset())
    {
        reset_ipf_psam_from_sys();
    }

	/*disable addr area limit func*/
	if(g_ipf_ctx.addr_limit){
		bak_reg = ipf_readl(ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
		ipf_writel(bak_reg | SECCTRL_BYPASS, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
		
		ipf_writel(IPF_OUT_ADDR_LIMIT_DEF, ipf_base_addr_ccore + HI_IPF_MST_DEFAULT_OFFSET);
		
		/*set share ddr regions to ipf reg1*/
		ipf_writel((unsigned long)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_IPF), ipf_base_addr_ccore + HI_IPF_MST_REGION1_START_OFFSET);
		ipf_writel(IPF_SHM_USED_END_ADDR, ipf_base_addr_ccore + HI_IPF_MST_REGION1_END_OFFSET);
		bak_reg = ipf_readl(ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
		ipf_writel(bak_reg | SECCTRL_VALID1, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
		
		g_ipf_ctx.limit_reg_cnt |= SECCTRL_VALID1;
		if(g_ipf_ctx.limit_reg_cnt == SECCTRL_OPEN3 || g_ipf_ctx.limit_reg_cnt == SECCTRL_OPEN4){
			bak_reg = ipf_readl(ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
			ipf_writel(bak_reg & ~SECCTRL_BYPASS, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
		}
	}
	/*init fama attr*/
	ipf_fama_attr_set();

    /* 初始化全局结构体 */
    memset_s((void*)IPF_ULBD_MEM_ADDR, IPF_DEBUG_INFO_ADDR - IPF_ULBD_MEM_ADDR, 0x0, IPF_DEBUG_INFO_ADDR - IPF_ULBD_MEM_ADDR);/* [false alarm]:fortify disable */
    
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
	
    /*s00219058 共享内存 下行CD读指针 初始化为0*/
    /* 申请扩展过滤器的内存, 配置扩展过滤器的基址 */
    g_pstExFilterAddr = (IPF_MATCH_INFO_S*)IPF_EXT_FILTER_ADDR;
    memset_s((void*)g_pstExFilterAddr, EXFLITER_NUM*sizeof(IPF_MATCH_INFO_S), 0x0, EXFLITER_NUM*sizeof(IPF_MATCH_INFO_S));
    
    /* 配置扩展过滤器的起始地址 */	
    ipf_writel((unsigned int)g_pstExFilterAddr, ipf_base_addr_ccore + HI_IPF_EF_BADDR_OFFSET);

    /* 初始化过滤器链表 */
    if(IPF_FilterList_Init() != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf_init malloc list ERROR! \n");
        goto FREE_ERROR;
    }
    
    /* 配置超时配置寄存器，使能超时中断，设置超时时间 */
    u32Timeout = TIME_OUT_CFG | (TIME_OUT_ENABLE);
    ipf_writel(u32Timeout, ipf_base_addr_ccore + HI_IPF_TIME_OUT_OFFSET);

    /* 配置时钟门控配置寄存器，设置为自动门控*/
    u32IntGate = GATE_CFG;
    ipf_writel(u32IntGate, ipf_base_addr_ccore + HI_IPF_GATE_OFFSET);/* [false alarm]:fortify disable */

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

    /*初始化ipf过滤器配置自旋锁*/
    spin_lock_init(&ipf_filter_spinlock);
	spin_lock_init(&ipf_dlbd_spinlock);
	
    ipf_int_connect();
	
#ifdef CONFIG_CCORE_PM

    u32Result = bsp_device_pm_add(&ipf_dpm_device);
    if(OK!= u32Result)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r ipf_dpm_device add error\n");
        return IPF_ERROR;
    }
#ifndef CONFIG_IPF_PROPERTY_MBB
    ipf_acore_init_status = (unsigned int*)IPF_INIT_ADDR;
    ipf_ccore_init_status = (unsigned int*)(IPF_INIT_ADDR+4);
	
    spin_lock_irqsave(&ipf_filter_spinlock, ipf_flags);
    bsp_ipc_spin_lock(IPC_SEM_IPF_PWCTRL);
    *ipf_ccore_init_status = IPF_CCORE_INIT_SUCCESS;
    bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
    spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);
#endif
#endif

	/*acore use first block,ccore use scnd block*/
	g_ipf_ctx.status = (struct ipf_debug*)(IPF_DEBUG_INFO_ADDR + sizeof(struct ipf_debug));
	memset_s(g_ipf_ctx.status, sizeof(struct ipf_debug), 0, sizeof(struct ipf_debug));

	ipf_om_dump_init();
	
	g_ipf_ctx.status->init_ok = IPF_CCORE_INIT_SUCCESS;
#ifdef CONFIG_PSAM
	psam_para.dlcdq		 = g_stIpfDl.pstIpfCDQ;
	psam_para.dlcdq_rptr = g_stIpfDl.u32IpfCdRptr;
	psam_para.dlcdq_wptr = &(g_stIpfDl.u32IpfCdWptr);
	psam_para.dlbdq_rptr_addr = ipf_base_addr_ccore + HI_IPF_CH1_BDQ_RPTR_OFFSET;
	psam_para.dlbdq_wptr_addr = ipf_base_addr_ccore + HI_IPF_CH1_BDQ_WPTR_OFFSET;
	bsp_psam_set_ipf_para(&psam_para);
#endif
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"[IPF] ipf init success\n");
	
    return IPF_SUCCESS;

FREE_ERROR:
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r ipf_init malloc ERROR! \n");
    return IPF_ERROR;
}



static irqreturn_t  ipf_interuppt(void * arg)
{
    unsigned int status = 0;

    status = ipf_readl(ipf_base_addr_ccore + HI_IPF_INT0_OFFSET); 
	
	ipf_writel(status, ipf_base_addr_ccore + HI_IPF_INT_STATE_OFFSET);

    if(status & (IPF_UL_RPT_INT0 | IPF_UL_TIMEOUT_INT0)) {
		if (status & IPF_UL_RPT_INT0) {
			g_ipf_ctx.status->rd_comp_intr++;
		}
		
		if (status & IPF_UL_TIMEOUT_INT0) {
			g_ipf_ctx.status->time_out_intr++;
		}

        if(g_stIpfUl.pFnUlIntCb) {
            g_stIpfUl.pFnUlIntCb();  
			g_ipf_ctx.status->rd_cb++;
        } else {
        	g_ipf_ctx.status->rd_cb_null++;
        }
    }

	
    if(status & (IPF_UL_ADQ0_EPTY_INT0 | IPF_UL_ADQ1_EPTY_INT0)) {
		if (g_stIpfUl.pAdqEmptyUlCb) {
        	if ((status & (IPF_UL_ADQ0_EPTY_INT0 | IPF_UL_ADQ1_EPTY_INT0))
				== (IPF_UL_ADQ0_EPTY_INT0 | IPF_UL_ADQ1_EPTY_INT0)) {
				g_ipf_ctx.status->ad_epty_intr[IPF_AD_0]++;
				g_ipf_ctx.status->ad_epty_intr[IPF_AD_1]++;
				g_stIpfUl.pAdqEmptyUlCb(IPF_EMPTY_ADQ);  
			} else {
				if ((status & IPF_UL_ADQ1_EPTY_INT0) == IPF_UL_ADQ1_EPTY_INT0) {
					g_ipf_ctx.status->ad_epty_intr[IPF_AD_1]++;
					g_stIpfUl.pAdqEmptyUlCb(IPF_EMPTY_ADQ1);  
				} else {
					g_ipf_ctx.status->ad_epty_intr[IPF_AD_0]++;
					g_stIpfUl.pAdqEmptyUlCb(IPF_EMPTY_ADQ0);  
				}
			}
			g_ipf_ctx.status->ad_epty_cb++;
		} else {
        	g_ipf_ctx.status->ad_epty_cb_null++;
        }
    }
	
	
	
    if(status & IPF_UL_RDQ_FULL) {
		g_ipf_ctx.status->rd_full++;
    }

    return IRQ_HANDLED;
}/*lint !e550*/

/*****************************************************************************
* 函 数 名     : ipf_int_connect
*
* 功能描述  : 挂IPF中断处理函数(两核都提供)
*
* 输入参数  : void
* 输出参数  : 无
* 返 回 值      : 无
*
* 修改记录  :2011年12月2日   鲁婷  创建
*****************************************************************************/
void ipf_int_connect(void)
{
	int s32Result;

	s32Result = request_irq(irqnum_ccore, (irq_handler_t)ipf_interuppt, IRQF_NO_SUSPEND, "balong_ipf_v700r200", NULL);
	if(0 != s32Result)
	{
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r ipf_int_connect Failed! \n",0,0,0,0,0,0);
	}
}


#ifndef CONFIG_IPF_PROPERTY_MBB
/*由于K3V3总线设计问题，ipf无法在M3上恢复ipf寄存器，故移动到acore和ccore*/

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
			2014年1月23日v1.01 chendongyue 移植到A9core
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
                ipf_writel(filter_serial, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET); 
                for(j=0; j<(sizeof(IPF_MATCH_INFO_S)/4); j++)
                {
                        match_info = *(match_info_addr+j);
                        ipf_writel((match_info), (ipf_base_addr_ccore+HI_FLT_LOCAL_ADDR0_OFFSET+j*4)); 
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

/*****************************************************************************
* 函 数 名       : ipf_check_filter_restore
*
* 功能描述  : 提供的低功耗接口，用于IPF上电恢复
*
* 输入参数  : 无
*             
* 输出参数  : 无
* 返 回 值     : 无
*
* 
* 修改记录  : 2014年1月23日v1.00 chendongyue创建
*****************************************************************************/
void ipf_check_filter_restore(void)
{
#ifdef CONFIG_CCORE_PM
	unsigned long ipf_flags = 0;
	unsigned int ipf_init_status = 0;
	spin_lock_irqsave(&ipf_filter_spinlock, ipf_flags);
	bsp_ipc_spin_lock(IPC_SEM_IPF_PWCTRL);

	ipf_init_status = (*ipf_acore_init_status)|(*ipf_ccore_init_status);
	*ipf_ccore_init_status = IPF_CCORE_INIT_SUCCESS;

	cache_sync();

	if(IPF_PWC_DOWN != ipf_init_status)
	{
		bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
		spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);
		return;
	}
	else
	{
		ipf_drx_restore_filter();
		bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
		spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);
		return;
	}
#endif
}

#endif

int mdrv_ipf_config_timeout(unsigned int u32Timeout)
{
    if((u32Timeout == 0) || (u32Timeout > 0xFFFF))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_timeout u32Timeout ERROR! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    u32Timeout |= TIME_OUT_ENABLE;
    ipf_writel(u32Timeout, ipf_base_addr_ccore + HI_IPF_TIME_OUT_OFFSET);
    
    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名      : mdrv_ipf_set_pktlen
*
* 功能描述  : 该接口用来配置过滤器的最大和最小包长
*
* 输入参数  : unsigned int MaxLen   最大包长
*                           unsigned int MinLen   最小包长
*
* 输出参数   : 无
* 返 回 值      : IPF_SUCCESS                成功
*                           BSP_ERR_IPF_INVALID_PARA   参数错误(最大包长比最小包长小)
*
* 修改记录  :2011年2月17日   鲁婷  创建
*****************************************************************************/
int mdrv_ipf_set_pktlen(unsigned int u32MaxLen, unsigned int u32MinLen)
{
    unsigned int u32PktLen = 0;

    /* 参数检查 */
    if(u32MaxLen < u32MinLen)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r mdrv_ipf_set_pktlen input error! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    
    u32PktLen = ((u32MaxLen&0x3FFF)<<16) | (u32MinLen&0x3FFF);
    
    ipf_writel(u32PktLen, ipf_base_addr_ccore + HI_IPF_PKT_LEN_OFFSET);
    return IPF_SUCCESS;
}/*lint !e550*/

/**********************************可维可测接口函数************************************/
void bsp_ipf_help(void)
{
    IPF_PRINT("===============================================\n");
    IPF_PRINT("bsp_ipf_info 参数1:通道类型  0为上行，1为下行\n");
    IPF_PRINT("bsp_ipf_bdinfo  参数1:通道类型  参数2:BD指针\n");
    IPF_PRINT("bsp_ipf_rdinfo  参数1:通道类型  参数2:RD指针\n"); 
    IPF_PRINT("bsp_ipf_adinfo 参数1:通道类型  参数2:AD指针参数3:AD 队列类型0为短,1为长\n"); 
    IPF_PRINT("===============================================\n");
    IPF_PRINT("bsp_ipf_dump_bdinfo  参数1:通道类型\n");
    IPF_PRINT("bsp_ipf_dump_rdinfo  参数1:通道类型\n"); 
    IPF_PRINT("bsp_ipf_dump_adinfo参数1:通道类型\n"); 
    IPF_PRINT("===============================================\n");
    IPF_PRINT("ipf_enable_ul_time_stamp  参数1:0-disable, 1-enable\n");
    IPF_PRINT("ipf_enable_dl_time_stamp  参数1:0-disable, 1-enable\n");
    IPF_PRINT("ipf_clear_time_stamp  清除实际戳记录\n");
    IPF_PRINT("ipf_dump_time_stamp  Linux:下行时间差, vxWorks:上行时间差\n");
    IPF_PRINT("===============================================\n");
    IPF_PRINT("bsp_ipf_usefilterinfo 	参数1:通道类型\n"); 
    IPF_PRINT("BSP_IPF_FreeFilterInfo\n"); 
    IPF_PRINT("bsp_ipf_filterinfohwid	参数1:硬件Filter ID\n");
    IPF_PRINT("bsp_ipf_filterinfopsid	参数1 :PS Filter ID\n");
}
void bsp_ipf_show_status(void)
{
	int i;
	struct ipf_debug* ptr = (struct ipf_debug*)(IPF_DEBUG_INFO_ADDR);

	g_ipf_ctx.status->flt_chain_loop = (int)readl(ipf_base_addr_ccore + HI_FLT_CHAIN_LOOP_OFFSET);

	for (i = 0; i < IPF_CHANNEL_MAX; i++) {
		IPF_PRINT("====ipf %score status====\n", i == 0 ? "a" : "c");
		IPF_PRINT("flt_chain_loop		%d\n", ptr->flt_chain_loop);
		IPF_PRINT("time_out_intr		%d\n", ptr->time_out_intr);
		IPF_PRINT("rd_comp_intr			%d\n", ptr->rd_comp_intr);
		IPF_PRINT("rd_full			%d\n", ptr->rd_full);
		IPF_PRINT("rd_cb			%d\n", ptr->rd_cb);
		IPF_PRINT("rd_cb_null		%d\n", ptr->rd_cb_null);
		IPF_PRINT("get_rd_num_times	%d\n", ptr->get_rd_num_times);
		IPF_PRINT("get_rd_times		%d\n", ptr->get_rd_times);
		IPF_PRINT("get_rd_short_cnt		%d\n", ptr->get_rd_cnt[IPF_AD_0]);
		IPF_PRINT("get_rd_long_cnt		%d\n", ptr->get_rd_cnt[IPF_AD_1]);
		IPF_PRINT("get_ad_num_times	%d\n", ptr->get_ad_num_times);
		IPF_PRINT("get_ad_thred	%d\n", 	   ptr->ad_thred);
		IPF_PRINT("short_adq_empty_intr	%d\n", ptr->ad_epty_intr[IPF_AD_0]);
		IPF_PRINT("short_adq_cfg_count	%d\n", ptr->cfg_ad_cnt[IPF_AD_0]);
		IPF_PRINT("short_adq_out_ptr_null	%d\n", ptr->ad_out_ptr_null[IPF_AD_0]);
		IPF_PRINT("long_adq_cfg_count	%d\n", ptr->cfg_ad_cnt[IPF_AD_1]);
		IPF_PRINT("long_adq_empty_intr	%d\n", ptr->ad_epty_intr[IPF_AD_1]);
		IPF_PRINT("long_adq_out_ptr_null	%d\n", ptr->ad_out_ptr_null[IPF_AD_1]);
		IPF_PRINT("ad_epty_cb		%d\n", ptr->ad_epty_cb);
		IPF_PRINT("ad_epty_cb_null		%d\n", ptr->ad_epty_cb_null);
		IPF_PRINT("bd_epty_intr		%d\n", ptr->bd_epty_intr);
		IPF_PRINT("bd_epty_cb		%d\n", ptr->bd_epty_cb);
		IPF_PRINT("bd_epty_cb_null		%d\n", ptr->bd_epty_cb_null);
		IPF_PRINT("get_bd_num_times	%d\n", ptr->get_bd_num_times);
		IPF_PRINT("bd_cfg_times		%d\n", ptr->cfg_bd_times);
		IPF_PRINT("cfg_bd_cnt		%d\n", ptr->cfg_bd_cnt);
		IPF_PRINT("bd_full			%d\n", ptr->bd_full);
		IPF_PRINT("bd_len_zero_err		%d\n", ptr->bd_len_zero_err);
		IPF_PRINT("busy_cnt		%d\n", ptr->busy_cnt);
		IPF_PRINT("resume			%d\n", ptr->resume);
		IPF_PRINT("suspend			%d\n", ptr->suspend);
		IPF_PRINT("time_stamp_en		%d\n", ptr->timestamp_en);
		IPF_PRINT("rate_en			%d\n", ptr->rate_en);
		IPF_PRINT("init_ok			0x%x\n", ptr->init_ok);
		IPF_PRINT("mdrv_called_not_init	%d\n", ptr->mdrv_called_not_init);
		IPF_PRINT("invalid_para		%d\n", ptr->invalid_para);
		IPF_PRINT("debug			%d\n", ptr->debug);
		IPF_PRINT("scr wr			%d\n", ptr->reg_scur_wr_err);
		IPF_PRINT("scr rd			%d\n", ptr->reg_scur_rd_err);
		IPF_PRINT("ccore rst idle err		%d\n", ptr->ccore_rst_err);
		ptr++;
	}
	IPF_PRINT("\n===count ccore only====================\n");
	IPF_PRINT("addr_limit			%d\n", g_ipf_ctx.addr_limit);
	IPF_PRINT("block_err			%d\n", g_ipf_ctx.block_err);
	IPF_PRINT("ttf_addr_err			%d\n", g_ipf_ctx.ttf_addr_er);
	IPF_PRINT("limit addr set		%d\n", g_ipf_ctx.limit_addr_set);
	IPF_PRINT("limit reg cnt		%x\n", g_ipf_ctx.limit_reg_cnt);
	IPF_PRINT("modem ipf reset err:	%x\n", g_ipf_ctx.reset_time_out);
}

int bsp_ipf_bdinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32BdqPtr)
{      
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            if(u32BdqPtr >= IPF_ULBD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("==========BD Info=========\n");
            IPF_PRINT("BD位置:         %d\n",u32BdqPtr);
            IPF_PRINT("u16Attribute:   %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:      %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:       0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:      0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32OutPtr);
            IPF_PRINT("u16Resv:        %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:   %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:   0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:   0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32UsrField3);
			IPF_PRINT("BD Desc Virt Addr:	0x%x\n",(g_stIpfUl.pstIpfBDQ + u32BdqPtr));
			IPF_PRINT("BD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfUl.pstIpfBDQ + u32BdqPtr)));
            break;
       case IPF_CHANNEL_DOWN:
            if(u32BdqPtr >= IPF_DLBD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("==========BD Info=========\n");
            IPF_PRINT("BD位置:         %d\n",u32BdqPtr);
            IPF_PRINT("u16Attribute:   %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:      %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:       0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:      0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32OutPtr);
            IPF_PRINT("u16Resv:        %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:   %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:   0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:   0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32UsrField3);
			IPF_PRINT("BD Desc Virt Addr:	0x%x\n",(g_stIpfDl.pstIpfBDQ + u32BdqPtr));
			IPF_PRINT("BD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfDl.pstIpfBDQ + u32BdqPtr)));
            break; 
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}

int bsp_ipf_dump_bdinfo(IPF_CHANNEL_TYPE_E eChnType)
{
    unsigned int i;
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
			
            for(i = 0;i < IPF_ULBD_DESC_SIZE;i++)
            {
                bsp_ipf_bdinfo(IPF_CHANNEL_UP,i);
            }
        break;
		
        case IPF_CHANNEL_DOWN:

            for(i = 0;i < IPF_DLBD_DESC_SIZE;i++)
            {
                bsp_ipf_bdinfo(IPF_CHANNEL_DOWN,i);
            }
        break;
				
        default:
        IPF_PRINT("Input param invalid ! \n");
        break;

    }
    return 0;
}

int bsp_ipf_rdinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32RdqPtr)
{     
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            if(u32RdqPtr >= IPF_ULRD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("===========RD Info==========\n");
            IPF_PRINT("RD位置:             %d\n",u32RdqPtr);
            IPF_PRINT("u16Attribute:       %d\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:          %d\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:           0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:          0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32OutPtr);
            IPF_PRINT("u16Result:          0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32UsrField3);
			IPF_PRINT("RD Desc Virt Addr:	0x%x\n",(g_stIpfUl.pstIpfRDQ + u32RdqPtr));
			IPF_PRINT("RD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfUl.pstIpfRDQ + u32RdqPtr)));
            break;
       case IPF_CHANNEL_DOWN:
            if(u32RdqPtr >= IPF_DLRD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("============RD Info===========\n");
            IPF_PRINT("RD位置:             %d\n",u32RdqPtr);
            IPF_PRINT("u16Attribute:       %d\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:          %d\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:           0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:          0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32OutPtr);
            IPF_PRINT("u16Result:          0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32UsrField3);
			IPF_PRINT("RD Desc Virt Addr:	0x%x\n",(g_stIpfUl.pstIpfRDQ + u32RdqPtr));
			IPF_PRINT("RD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfUl.pstIpfRDQ + u32RdqPtr)));
            break; 
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}


int bsp_ipf_dump_rdinfo(IPF_CHANNEL_TYPE_E eChnType)
{
    int i;

    switch(eChnType)
    {
        case IPF_CHANNEL_UP:

            for(i = 0;i < IPF_ULBD_DESC_SIZE;i++)
            {
                bsp_ipf_rdinfo(IPF_CHANNEL_UP,i);
            }
        break;
		
        case IPF_CHANNEL_DOWN:

            for(i = 0;i < IPF_DLBD_DESC_SIZE;i++)
            {
                bsp_ipf_rdinfo(IPF_CHANNEL_DOWN,i);
            }
        break;
        default:
        IPF_PRINT("Input param invalid ! \n");
        break;
    }
    return 0;
}
int bsp_ipf_adinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32AdqPtr, unsigned int u32AdType)
{

    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            if(u32AdqPtr >= IPF_ULAD0_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            if(0 == u32AdType)
            {
                 IPF_PRINT("===========UL AD0 Info==========\n");
                 IPF_PRINT("AD位置:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfUl.pstIpfADQ0[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfUl.pstIpfADQ0[u32AdqPtr].u32OutPtr1);
            }
            else
            {
                 IPF_PRINT("===========UL AD1 Info==========\n");
                 IPF_PRINT("AD位置:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfUl.pstIpfADQ1[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfUl.pstIpfADQ1[u32AdqPtr].u32OutPtr1);
            }
            break;
       case IPF_CHANNEL_DOWN:
            if(u32AdqPtr >= IPF_ULAD1_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            if(0 == u32AdType)
	      	{
                 IPF_PRINT("===========DL AD0 Info==========\n");
                 IPF_PRINT("AD位置:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfDl.pstIpfADQ0[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfDl.pstIpfADQ0[u32AdqPtr].u32OutPtr1);
            }
            else
            {
                 IPF_PRINT("===========DL AD1 Info==========\n");
                 IPF_PRINT("AD位置:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfDl.pstIpfADQ1[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfDl.pstIpfADQ1[u32AdqPtr].u32OutPtr1);
            }
            break;
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}


int bsp_ipf_dump_adinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32AdType)
{
    int i;

    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            for(i = 0;i < IPF_ULAD0_DESC_SIZE;i++)
            {
                bsp_ipf_adinfo(IPF_CHANNEL_UP, i, u32AdType);
            }
        break;
		
        case IPF_CHANNEL_DOWN:

            for(i = 0;i < IPF_DLAD1_DESC_SIZE;i++)
            {
                bsp_ipf_adinfo(IPF_CHANNEL_DOWN, i, u32AdType);
            }
        break;
		
        default:
        IPF_PRINT("Input param invalid ! \n");
        break;
    }
    return 0;
}

int bsp_ipf_info(IPF_CHANNEL_TYPE_E eChnType)
{
    unsigned int u32BdqDepth = 0;
    unsigned int u32BdqWptr = 0;
    unsigned int u32BdqRptr = 0;
    unsigned int u32BdqWaddr = 0;
    unsigned int u32BdqRaddr = 0;
    unsigned int u32RdqDepth = 0;
    unsigned int u32RdqRptr = 0;
    unsigned int u32RdqWptr = 0;
    unsigned int u32RdqWaddr = 0;
    unsigned int u32RdqRaddr = 0;
    unsigned int u32Depth = 0;
    unsigned int u32status = 0;
	
    unsigned int u32Adq0Rptr = 0;
    unsigned int u32Adq0Wptr = 0;

    unsigned int u32Adq1Rptr = 0;
    unsigned int u32Adq1Wptr = 0;

    if(IPF_CHANNEL_UP == eChnType)
    {
        u32Depth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_DQ_DEPTH_OFFSET);
        u32RdqDepth = (u32Depth>>16)&IPF_DQ_DEPTH_MASK;
        u32BdqDepth = u32Depth&IPF_DQ_DEPTH_MASK;

        u32status = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_STATE_OFFSET);

        u32BdqWptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_BDQ_WPTR_OFFSET);
        u32BdqRptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_BDQ_RPTR_OFFSET); 
        u32BdqWaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_BDQ_WADDR_OFFSET); 
        u32BdqRaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_BDQ_RADDR_OFFSET); 
    
        u32RdqWptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_RDQ_WPTR_OFFSET);
        u32RdqRptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_RDQ_RPTR_OFFSET);
        u32RdqWaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_RDQ_WADDR_OFFSET); 
        u32RdqRaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_RDQ_RADDR_OFFSET); 
		
        u32Adq0Rptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_RPTR_OFFSET);
        u32Adq0Wptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_WPTR_OFFSET);

        u32Adq1Rptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_RPTR_OFFSET);
        u32Adq1Wptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_WPTR_OFFSET);

    }
    else if(IPF_CHANNEL_DOWN == eChnType)
    {
        u32Depth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_DQ_DEPTH_OFFSET);
        u32RdqDepth = (u32Depth>>16)&IPF_DQ_DEPTH_MASK;
        u32BdqDepth = u32Depth&IPF_DQ_DEPTH_MASK;

        u32status = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_STATE_OFFSET);
		
        u32BdqWptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_BDQ_WPTR_OFFSET);
        u32BdqRptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_BDQ_RPTR_OFFSET); 
        u32BdqWaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_BDQ_WADDR_OFFSET); 
        u32BdqRaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_BDQ_RADDR_OFFSET); 
    
        u32RdqWptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_RDQ_WPTR_OFFSET);
        u32RdqRptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_RDQ_RPTR_OFFSET);
        u32RdqWaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_RDQ_WADDR_OFFSET); 
        u32RdqRaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_RDQ_RADDR_OFFSET); 

        u32Adq0Rptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ0_RPTR_OFFSET);
        u32Adq0Wptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ0_WPTR_OFFSET);

        u32Adq1Rptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ1_RPTR_OFFSET);
        u32Adq1Wptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ1_WPTR_OFFSET);

    }
    else
    {
        return 1;
    }
    IPF_PRINT("============================\n");
    IPF_PRINT("通道 状态:            0x%x\n", u32status);
    IPF_PRINT("BD 深度:            %d\n", u32BdqDepth);
    IPF_PRINT("BD 写指针:          %d\n", u32BdqWptr);
    IPF_PRINT("BD 读指针:          %d\n", u32BdqRptr);
    IPF_PRINT("BD 写地址:          0x%x\n", u32BdqWaddr);
    IPF_PRINT("BD 读地址:          0x%x\n", u32BdqRaddr);
    IPF_PRINT("RD 深度:            %d\n", u32RdqDepth);
    IPF_PRINT("RD 读指针:          %d\n", u32RdqRptr);
    IPF_PRINT("RD 写指针:          %d\n", u32RdqWptr);
    IPF_PRINT("RD 读地址:          0x%x\n", u32RdqRaddr);
    IPF_PRINT("RD 写地址:          0x%x\n", u32RdqWaddr);

    IPF_PRINT("AD0 读指针:          %d\n", u32Adq0Rptr);
    IPF_PRINT("AD0 写指针:          %d\n", u32Adq0Wptr);
	
    IPF_PRINT("AD1 读指针:          %d\n", u32Adq1Rptr);
    IPF_PRINT("AD1 写指针:          %d\n", u32Adq1Wptr);
    IPF_PRINT("============================\n");   
    return 0;
}

void bsp_ipf_mem(void)
{
	ipf_ddr_t *ddr_info = &g_ipf_ctx.status->share_ddr_info;
	unsigned int dl_start = IPF_DLBD_MEM_ADDR;
	
	IPF_PRINT("IPF Shared DDR information:\n");
	IPF_PRINT("start				 0x%x \n", ddr_info->start);
	IPF_PRINT("ul_start 			 0x%x \n", ddr_info->ul_start);
	IPF_PRINT("dl_start 			 0x%x \n", dl_start);
	IPF_PRINT("filter_pwc_start 	 0x%x \n", ddr_info->filter_pwc_start);
	IPF_PRINT("pwc_info_start		 0x%x \n", ddr_info->pwc_info_start);
	IPF_PRINT("dlcdrptr 			 0x%x \n", ddr_info->dlcdrptr);
	IPF_PRINT("debug_dlcd_start 	 0x%x \n", ddr_info->debug_dlcd_start);
	IPF_PRINT("debug_dlcd_size		 0x%x \n", ddr_info->debug_dlcd_size);
	IPF_PRINT("end					 0x%x \n", ddr_info->end);
	IPF_PRINT("len(The max:0x10000)  0x%x \n", ddr_info->len);

	IPF_PRINT("=======================================\n");
	IPF_PRINT("   bsp_ipf_mem		   ADDR 		   SIZE\n");
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_ULBD_MEM_ADDR	  ", IPF_ULBD_MEM_ADDR, (unsigned long)IPF_ULBD_MEM_SIZE);
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_ULRD_MEM_ADDR	  ", IPF_ULRD_MEM_ADDR, (unsigned long)IPF_ULRD_MEM_SIZE);
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DLBD_MEM_ADDR	  ", IPF_DLBD_MEM_ADDR, (unsigned long)IPF_DLBD_MEM_SIZE);
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DLRD_MEM_ADDR	  ", IPF_DLRD_MEM_ADDR, (unsigned long)IPF_DLRD_MEM_SIZE);
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DLCD_MEM_ADDR	  ", IPF_DLCD_MEM_ADDR, (unsigned long)IPF_DLCD_MEM_SIZE);
	IPF_PRINT("%s%lx\t\t%d\n", "IPF_INIT_ADDR		 ", IPF_INIT_ADDR, IPF_INIT_SIZE);
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DEBUG_INFO_ADDR  ", IPF_DEBUG_INFO_ADDR, (unsigned long)IPF_DEBUG_INFO_SIZE);
}

/*****************************************************************************
* 函 数 名     : bsp_ipf_get_control_flag_for_ccore_reset
*
* 功能描述  : modem单独复位ipf适配函数，用于在复位时阻止下行数传
*
* 输入参数  : 无
*   
* 输出参数  : 无
*
* 返 回 值     : 成功
*
* 修改记录  :2014年2月14日   陈东岳  创建
*****************************************************************************/
IPF_FORRESET_CONTROL_E bsp_ipf_get_control_flag_for_ccore_reset(void)
{
    return *modem_reset_flag;
}

/*****************************************************************************
 函 数 名  : ccpu_reset_ipf_and_wait_idle
 功能描述  : c核复位后关闭并等待ipf进入空闲态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : ccpu_reset_ipf_and_wait_idle
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    修改内容   : 新生成函数

*****************************************************************************/
int ccpu_reset_ipf_and_wait_idle(void)
{

	/*get ipf syscrg base virtual addr*/
	
    /*查询ipf clk的状态*/
    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_IPF_SOFT_RESET);

    /*查询IPF是否空闲*/

	/*reset ipf and psam*/
		/*enable rst ipf and psam*/
		/*leave rst*/

		/*judge reset ipf and psam ok or not*/
	    /*复位IPF*/

	    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_IPF_ENTER_IDLE);

	    /*判断复位是否成功*/

    /*查询IPF是否空闲*/
    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名  : IPF_FilterList_Init
*
* 功能描述  : IPF过滤器链表初始化     内部使用，不作为接口函数
*
* 输入参数  : void
* 输出参数  : 无
* 返 回 值  : IPF_SUCCESS    过滤器链表初始化成功
*                       IPF_ERROR      过滤器链表初始化失败
*
* 修改记录  :2011年11月17日   鲁婷  创建
*****************************************************************************/
int IPF_FilterList_Init(void)
{
    unsigned int i = 0;
    IPF_ID_S* current = NULL;
    IPF_ID_S* prev = NULL;
    IPF_ID_S* tmp = NULL;
	
    /* 初始化可作头节的的过滤器和uselist，从0-7*/	
    for(i =  0; i < IPF_FILTER_CHAIN_MAX_NUM; i++)
    {
        g_stIPFFilterInfo[i].u32FilterNum = 0;
        g_stIPFFilterInfo[i].pstUseList = NULL;
        ipf_delete_all(i);
    }

    /* 初始化basiclist  从8号开始，0-7是链表头，单列*/
    for(i =  IPF_FILTER_CHAIN_MAX_NUM; i < IPF_BF_NUM; i++)
    {
        /* coverity[alloc_fn] */
        current = (IPF_ID_S*)osl_malloc(sizeof(IPF_ID_S));
        if(NULL == current)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF_FilterList_Init malloc ERROR! \n");
            goto FREE_ALL;
        }
        if(g_stIPFBasicFreeList != NULL)
        {
            if(NULL != prev)
            {
                prev->pstNext = current;/*lint !e613*/
            }
            else
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF_FilterList_Init prev == null! \n");
                goto FREE_ALL;
            }
        }
        else /* basicfreelist头结点 */
        {
            g_stIPFBasicFreeList = current;
        }
        current->u32FilterID = i;
        current->u32PsID = 0;
        current->pstNext = NULL;

        prev = current;
    }
	
    prev = NULL;
    /* 初始化extfreelist  从64号开始*/
    for(i =  IPF_BF_NUM; i < IPF_TOTAL_FILTER_NUM; i++)
    {
        current = (IPF_ID_S*)osl_malloc(sizeof(IPF_ID_S));
        if(NULL == current)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF_FilterList_Init malloc ERROR! \n");
            goto FREE_ALL;
        }
        if(g_stIPFExtFreeList != NULL)
        {
            if(NULL != prev)
            {
                prev->pstNext = current;/*lint !e613*/
            }
            else
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF_FilterList_Init prev == null! \n");
                goto FREE_ALL;
            }
        }
        else /* freelist头结点 */
        {
            g_stIPFExtFreeList = current;
        }
        current->u32FilterID = i;
        current->u32PsID = 0;
        current->pstNext = NULL;
        prev = current;
    }
    	
    return IPF_SUCCESS;
    
FREE_ALL:
    i=0;
	
    /* coverity[overrun-local] */
    while((i <IPF_FILTER_CHAIN_MAX_NUM)&&(g_stIPFFilterInfo[i].pstUseList != NULL))/* [false alarm]:fortify disable */
    {
        osl_free(g_stIPFFilterInfo[i].pstUseList );
        /* coverity[incr] */
        i++;
    }

    while(g_stIPFBasicFreeList!= NULL)
    {
    	tmp = g_stIPFBasicFreeList->pstNext;
        osl_free(g_stIPFBasicFreeList);
        g_stIPFBasicFreeList = tmp;
    }

    while(g_stIPFExtFreeList!= NULL)
    {
    	tmp = g_stIPFExtFreeList->pstNext;
        osl_free(g_stIPFExtFreeList);
        g_stIPFExtFreeList = tmp;
    }

    return IPF_ERROR;
}

/*****************************************************************************
* 函 数 名  : IPF_AddToFreeList
*
* 功能描述  : 将结点加到freelist的合适位置
*
* 输入参数  : IPF_ID_S* stNode             待插入的结点指针
*             
* 输出参数  : 无

* 返 回 值  : 无
*
* 修改记录  : 2011年3月30日   鲁婷  创建
*****************************************************************************/
void IPF_AddToBasicFreeList(IPF_ID_S* stNode)
{
    IPF_ID_S* current = NULL;    
    IPF_ID_S* prev = NULL;

    current = g_stIPFBasicFreeList;

    /* 如果freelist为空 */
    if(NULL == current)
    {
        g_stIPFBasicFreeList = stNode;
        g_stIPFBasicFreeList->pstNext = NULL;
        return;
    }

    /* 如果比第一个结点的ID还小 */
    if(stNode->u32FilterID < current->u32FilterID)
    {
        stNode->pstNext = current;
        g_stIPFBasicFreeList = stNode;       
        return;
    }

    prev = g_stIPFBasicFreeList;
    current = g_stIPFBasicFreeList->pstNext;

    while(current != NULL)
    {
        if(stNode->u32FilterID < current->u32FilterID)
        {
            prev->pstNext = stNode;
            stNode->pstNext = current;
            return;
        }
        prev = current;
        current = current->pstNext;
    }
    /* 放在最后 */
    prev->pstNext = stNode;
    stNode->pstNext = NULL;

}

void IPF_AddToExtFreeList(IPF_ID_S* stNode)
{
    IPF_ID_S* current = NULL;    
    IPF_ID_S* prev = NULL;

    current = g_stIPFExtFreeList;

    /* 如果freelist为空 */
    if(NULL == current)
    {
        g_stIPFExtFreeList = stNode;
        g_stIPFExtFreeList->pstNext = NULL;
        return;
    }

    /* 如果比第一个结点的ID还小 */
    if(stNode->u32FilterID < current->u32FilterID)
    {
        stNode->pstNext = current;
        g_stIPFExtFreeList = stNode;       
        return;
    }

    prev = g_stIPFExtFreeList;
    current = g_stIPFExtFreeList->pstNext;

    while(current != NULL)
    {
        if(stNode->u32FilterID < current->u32FilterID)
        {
            prev->pstNext = stNode;
            stNode->pstNext = current;
            return;
        }
        prev = current;
        current = current->pstNext;
    }
    /* 放在最后 */
    prev->pstNext = stNode;
    stNode->pstNext = NULL;

}

/*****************************************************************************
* 函 数 名  : ipf_delete_all
*
* 功能描述  : 删除链表中的所有结点
*
* 输入参数  : IPF_FILTER_CHAIN_TYPE_E eFilterChainhead过滤器链首地址           
*             
* 输出参数  : 无

* 返 回 值  : 无
*
* 修改记录  :2011年3月30日   鲁婷  创建
*****************************************************************************/
void ipf_delete_all(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead)
{
    IPF_ID_S* pstMove = NULL;
    /* coverity[var_decl] */
    while(IPF_FILTERHEAD < g_stIPFFilterInfo[eFilterChainhead].u32FilterNum)
    {
        pstMove = g_stIPFFilterInfo[eFilterChainhead].pstUseList;
        /* 将结点从uselist删除 */
        g_stIPFFilterInfo[eFilterChainhead].pstUseList = pstMove->pstNext;
	
        /* 将删除的结点添加到freelist中 */ 
        if(IPF_BF_NUM > (pstMove->u32FilterID))
        {
            IPF_AddToBasicFreeList(pstMove); 
        }
        else
        {	
            IPF_AddToExtFreeList(pstMove); 
        }
        g_stIPFFilterInfo[eFilterChainhead].u32FilterNum--;
    }

    /* 将首过滤器索引设置为511，使能配置为0 */
    ipf_writel(eFilterChainhead, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET);
    ipf_writel(IPF_TAIL_INDEX, ipf_base_addr_ccore+HI_FLT_CHAIN_OFFSET); 
    ipf_writel(IPF_DISABLE_FILTER, ipf_base_addr_ccore+HI_FLT_RULE_CTRL_OFFSET); 
    BSP_IPF_BackupFilter(eFilterChainhead);
}

/*****************************************************************************
* 函 数 名  : IPF_MallocOneBasicFilter
*
* 功能描述  : 从freelist中分配一个结点(取出第一个结点)
*
* 输入参数  : 无       
*             
* 输出参数  : 无

* 返 回 值  : 结点指针
*
* 修改记录  : 2011年3月30日   鲁婷  创建
*
* 说明      : 由调用函数来保证一定能分配到结点
*****************************************************************************/
IPF_ID_S* IPF_MallocOneBasicFilter(void)
{
    IPF_ID_S* current = NULL;
    	current = g_stIPFBasicFreeList ;

    if(NULL == current)
    {
        bsp_trace(BSP_LOG_LEVEL_WARNING, BSP_MODU_IPF, "IPF_MallocOneBasicFilter Basic run out\n");
        return NULL;
    }
    g_stIPFBasicFreeList  = g_stIPFBasicFreeList ->pstNext;  

    return current;
}
/*****************************************************************************
* 函 数 名  : IPF_MallocOneExtFilter
*
* 功能描述  : 从freelist中分配一个结点(取出第一个结点)
*
* 输入参数  : 无       
*             
* 输出参数  : 无

* 返 回 值  : 结点指针
*
* 修改记录  : 2011年3月30日   鲁婷  创建
*
* 说明      : 由调用函数来保证一定能分配到结点
*****************************************************************************/
IPF_ID_S* IPF_MallocOneExtFilter(void)
{
    IPF_ID_S* current = NULL;
    	current = g_stIPFExtFreeList ;

    if(NULL == current)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "IPF_MallocOneExtFilter Ext run out\n");
        return NULL;
    }
    g_stIPFExtFreeList  = g_stIPFExtFreeList ->pstNext;  

    return current;
}

/*****************************************************************************
* 函 数 名  : IPF_AddTailUsedFilter
*
* 功能描述  : 将结点加到uselist的结尾
*
* 输入参数  : unsigned char eFilterChainhead 通道类型   
*             IPF_ID_S* stNode             待插入的结点指针
*             
* 输出参数  : 无

* 返 回 值  : 无
*
* 修改记录  : 2011年3月30日   鲁婷  创建
                             2012年11月25日陈东岳修改
*****************************************************************************/
void IPF_AddTailUsedFilter(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead,IPF_ID_S* stNode)
{
    IPF_ID_S* current = NULL;

    current = g_stIPFFilterInfo[eFilterChainhead].pstUseList;
    if(NULL == current)
    {
        g_stIPFFilterInfo[eFilterChainhead].pstUseList = stNode;
        g_stIPFFilterInfo[eFilterChainhead].pstUseList->pstNext = NULL;
        g_stIPFFilterInfo[eFilterChainhead].u32FilterNum = 1;
        return;
    }
	
    /* 将结点加到链表结尾 */
    while(current->pstNext != NULL)
    {
        current = current->pstNext;
    }
    current->pstNext = stNode;
    stNode->pstNext = NULL;
    
    g_stIPFFilterInfo[eFilterChainhead].u32FilterNum++;

}

/*****************************************************************************
* 函 数 名  : IPF_AddTailFilterChain
*
* 功能描述  :将过滤器配置到硬件中
*
* 输入参数  : unsigned int u32LastFilterID, unsigned int u32FilterID, IPF_MATCH_INFO_S* pstMatchInfo
*             
* 输出参数  : 无

* 返 回 值  : 无
*
* 修改记录  : 2011年3月30日   鲁婷  创建
*****************************************************************************/
void IPF_AddTailFilterChain(unsigned int u32LastFilterID, 
	unsigned int u32FilterID, IPF_MATCH_INFO_S* pstMatchInfo)
{
    unsigned int u32Value = 0;
    IPF_MATCH_INFO_S* pstLastMatchInfo = NULL;
    
    /* 基本过滤器--将新的过滤器规则配置到过滤器 */
    if(u32FilterID < IPF_BF_NUM)
    {
        ipf_write_basic_filter(u32FilterID, pstMatchInfo);
		
        /*对基本过滤器进行备份*/
        BSP_IPF_BackupFilter(u32FilterID);
    }
    /* 扩展过滤器 */
    else
    {
        memcpy_s((void*)(g_pstExFilterAddr + u32FilterID - IPF_BF_NUM), sizeof(IPF_MATCH_INFO_S), pstMatchInfo, sizeof(IPF_MATCH_INFO_S));
    }

    /* 不是最后一个filter才需要配置上一个filter的nextindex域 */
    if(u32LastFilterID != IPF_TAIL_INDEX)
    {
        /* 将上次配置最后一个过滤器的nextIndex域重新配置 */
        if(u32LastFilterID < IPF_BF_NUM)
        {
            ipf_writel(u32LastFilterID, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET); 
            u32Value = ipf_readl(ipf_base_addr_ccore + HI_FLT_CHAIN_OFFSET);
            u32Value = (u32Value&0x1FF0000) + u32FilterID;
            ipf_writel(u32Value, ipf_base_addr_ccore + HI_FLT_CHAIN_OFFSET);
			
            /*对修改next index的基本过滤器进行重新备份*/
            BSP_IPF_BackupFilter(u32LastFilterID);
        }
        else
        {
            pstLastMatchInfo = g_pstExFilterAddr + u32LastFilterID - IPF_BF_NUM;
            pstLastMatchInfo->unFltChain.Bits.u16NextIndex = u32FilterID;        
        }
    }    
}

/*****************************************************************************
* 函 数 名     : IPF_FindFilterID
*
* 功能描述  : 在上下行链表中寻找与PS ID 匹配的Filter ID
*
* 输入参数  : IPF_FILTER_CHAIN_TYPE_E eFilterChainhead    通道类型
*                           unsigned int u32PsID                PS ID            
*             
* 输出参数  : unsigned int* u32FilterID   查询到的Filter ID

* 返 回 值     : IPF_SUCCESS                查询成功
*                          IPF_ERROR                  查询失败
*
* 修改记录  :2011年1月11日   鲁婷  创建
*****************************************************************************/
int IPF_FindFilterID(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, unsigned int u32PsID, unsigned int* u32FilterID)
{
    IPF_ID_S* current = NULL;

    current = g_stIPFFilterInfo[eFilterChainhead].pstUseList;
    while(current != NULL)
    {
        if(current->u32PsID != u32PsID)
        {
            current = current->pstNext;
        }
        else
        {
            *u32FilterID = current->u32FilterID;
            return IPF_SUCCESS;
        }
    }
    return IPF_ERROR;        
}

int mdrv_ipf_init(IPF_COMMON_PARA_S *pstCommPara)
{
    HI_IPF_CTRL_T ipf_ctrl;
    int chn_schedule_strategy = SCH_ALL_DESC;

    if(NULL == pstCommPara)
    {
    	g_ipf_ctx.status->invalid_para++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_Init pstCommPara NULL! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF NOT Init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }

    /* 配置IPF全局控制配置寄存器 */
    ipf_ctrl.bits.filter_seq = pstCommPara->bFilterSeq;
    ipf_ctrl.bits.flt_addr_reverse = pstCommPara->bFltAddrReverse;
    ipf_ctrl.bits.sp_cfg = pstCommPara->bSpPriSel;
    ipf_ctrl.bits.sp_wrr_sel = pstCommPara->bSpWrrModeSel;
    ipf_ctrl.bits.max_burst_len = pstCommPara->eMaxBurst;
    ipf_ctrl.bits.ipv6_nh_sel = pstCommPara->bIpv6NextHdSel;
    ipf_ctrl.bits.ah_esp_sel = pstCommPara->bEspAhSel;
    ipf_ctrl.bits.ah_disable = pstCommPara->bAhSpiDisable;
    ipf_ctrl.bits.esp_disable = pstCommPara->bEspSpiDisable;
    ipf_ctrl.bits.mfc_en = pstCommPara->bMultiFilterChainEn;
    ipf_ctrl.bits.mm_en = pstCommPara->bMultiModeEn;
    ipf_ctrl.bits.add_rep = pstCommPara->bAdReport;
    ipf_ctrl.bits.schedule_strategy = chn_schedule_strategy;
	if(g_ipf_ctx.ipf_version >= IPF_VERSION_120a){
    	ipf_ctrl.u32 |= IPF_CD_EN_BIT;
	}
	
    bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_IPF, "\r u32IPFCtrl = 0x%x \n", ipf_ctrl.u32);
    ipf_writel(ipf_ctrl.u32, ipf_base_addr_ccore + HI_IPF_CTRL_OFFSET); 

    return  IPF_SUCCESS; 
}


int mdrv_ipf_config_ulchan(IPF_CHL_CTRL_S *pstCtrl)
{
    unsigned int u32ChanCtrl = 0; 
	


    if(NULL == pstCtrl)
    {
 		g_ipf_ctx.status->invalid_para++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_ulchan pstCtrl NULL! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF NOT Init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }


    /*配置上行通道控制寄存器 */
    u32ChanCtrl = pstCtrl->eIpfMode | (pstCtrl->bEndian<<2) | 
                            (pstCtrl->bDataChain<<3) | (pstCtrl->u32WrrValue<<16);
    bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_IPF,"\r u32ChanCtrl = 0x%x \n", u32ChanCtrl);
    ipf_writel(u32ChanCtrl, ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET);  

    return IPF_SUCCESS;
}

int mdrv_ipf_config_dlchan(IPF_CHL_CTRL_S *pstCtrl)
{
    unsigned int u32ChanCtrl = 0; 

    if(NULL == pstCtrl)
    {
 		g_ipf_ctx.status->invalid_para++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_dlchan pstCtrl NULL! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }
    
    /*配置上行通道控制寄存器 */
    u32ChanCtrl = pstCtrl->eIpfMode | (pstCtrl->bEndian<<2) | 
                            (pstCtrl->bDataChain<<3) | (pstCtrl->u32WrrValue<<16);
    bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_IPF,"\r u32ChanCtrl = 0x%x \n", u32ChanCtrl);
    ipf_writel(u32ChanCtrl, ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET);

    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名      : BSP_IPF_ConfigADThr
*
* 功能描述  : 配置上下行通道ADq长短包阀值
*
* 输入参数  : unsigned int u32UlADThr,unsigned int u32DlADThr
* 输出参数  : 无
* 返 回 值      : 无
*
* 说明             : 配置上下行通道ADq长短包阀值
*
* 修改记录  : 2011年12月13日   陈东岳创建
			 2014年1月23日v1.01 陈东岳 修改 由于K3V3总线设计问题，
			 无法在m3上进行低功耗恢复，移动到A9上进行。
*****************************************************************************/
int mdrv_ipf_config_adthred (unsigned int u32UlADThr, unsigned int u32DlADThr)
{
    unsigned int u32ADCtrl[IPF_CHANNEL_MAX] = {0,0};
	struct ipf_debug* a_status = (struct ipf_debug*)(IPF_DEBUG_INFO_ADDR);

    if((u32UlADThr == 0)  || (u32UlADThr > 0xFFFF) 
		|| (u32DlADThr == 0)  || (u32DlADThr > 0xFFFF))
    {
 		g_ipf_ctx.status->invalid_para++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_adthred invlaid para! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }

    u32ADCtrl[IPF_CHANNEL_UP] = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ_CTRL_OFFSET);
    u32ADCtrl[IPF_CHANNEL_UP] &= IPF_ADQ_THR_MASK;
    u32ADCtrl[IPF_CHANNEL_UP] |= (u32UlADThr<<16);
	a_status->ad_thred = u32UlADThr;
    /* 配置上行通道的AD阀值*/
    ipf_writel(u32ADCtrl[IPF_CHANNEL_UP], ipf_base_addr_ccore + HI_IPF_CH0_ADQ_CTRL_OFFSET);

#ifdef CONFIG_PSAM
	bsp_psam_config_adthred(u32DlADThr);
#else
	u32ADCtrl[IPF_CHANNEL_DOWN] = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ_CTRL_OFFSET);
	u32ADCtrl[IPF_CHANNEL_DOWN] &= IPF_ADQ_THR_MASK;
	u32ADCtrl[IPF_CHANNEL_DOWN] |= (u32DlADThr<<16);
	/* coverity[var_deref_op] */
	g_ipf_ctx.status->ad_thred = u32DlADThr;
	/* 配置下行通道的AD阀值*/
    ipf_writel(u32ADCtrl[IPF_CHANNEL_DOWN], ipf_base_addr_ccore + HI_IPF_CH1_ADQ_CTRL_OFFSET);
#endif
	
    return IPF_SUCCESS;
}



/*****************************************************************************
* 函 数 名     : BSP_IPF_SetFilter
*
* 功能描述  : 用来配置所有的Filter
*
* 输入参数  : unsigned char eFilterChainhead 过滤器链首/过滤器链号
*                           IPF_FILTER_CONFIG_S *pFilterInfo  Filter配置结构体指针
*                           unsigned int u32FilterNum   Filter个数
*
* 输出参数  : 无
* 返 回 值      : IPF_SUCCESS                      配置成功
*                            BSP_ERR_IPF_NOT_INIT             模块未初始化
*                            BSP_ERR_IPF_FILTER_NOT_ENOUGH    Filter个数不够
*                            BSP_ERR_IPF_INVALID_PARA         参数错误
*
* 修改记录  :2011年1月11日   鲁婷  创建
                            2011年3月30日   鲁婷  修改
                            2011年11月30日   鲁婷  修改
                            2012年11月24日陈东岳c00228781修改
							2014年1月23日v1.01 陈东岳 修改 由于K3V3总线设计问题，
							无法在m3上进行低功耗恢复，移动到A9上进行。
*****************************************************************************/
int mdrv_ipf_set_filter(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, 
	IPF_FILTER_CONFIG_S *pstFilterInfo, unsigned int u32FilterNum)
{
	unsigned int i = 0;
	IPF_ID_S* current = NULL;
	unsigned int u32LastFilterID = IPF_TAIL_INDEX;
	unsigned int u32FirstFilterID = IPF_TAIL_INDEX;
	unsigned long flags = 0;



	if((eFilterChainhead >= IPF_FILTER_CHAIN_MAX_NUM) || (NULL == pstFilterInfo))
	{
 		g_ipf_ctx.status->invalid_para++;
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_set_filter invalid para\n");
		return BSP_ERR_IPF_INVALID_PARA;
	}

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init\n");
        return BSP_ERR_IPF_NOT_INIT;
    }

#ifndef CONFIG_IPF_PROPERTY_MBB
    /*由于K3V3总线设计问题，使用ipf 前需要检测是否需要恢复过滤器*/
    ipf_check_filter_restore();
#endif

	spin_lock_irqsave(&ipf_filter_spinlock, flags);
#ifndef CONFIG_IPF_PROPERTY_MBB
	bsp_ipc_spin_lock(IPC_SEM_IPF_PWCTRL);
#endif
	/* 清除该寄存器链首地址以外的所有结点 */
	ipf_delete_all(eFilterChainhead);
	udelay(g_filter_delay_time);
		
	/*分配滤器*/
	for(i = 0; i < u32FilterNum; i++)
	{
        /* 从freelist中取出未配置的过滤器 */
		if(!(IPF_SET_EXT_FILTER & (pstFilterInfo->u32FilterID)))
		{    
			current = IPF_MallocOneBasicFilter();
			if(NULL == current)
			{		
				current = IPF_MallocOneExtFilter();
				if(NULL == current)
				{		
				#ifndef CONFIG_IPF_PROPERTY_MBB
					bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
				#endif
					spin_unlock_irqrestore(&ipf_filter_spinlock, flags);
					bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r IPF_MallocOneFilter error! \n");
					return BSP_ERR_IPF_FILTER_NOT_ENOUGH;
				}
			}		
		}
		else
		{
			current = IPF_MallocOneExtFilter();
			if(NULL == current)
			{
			#ifndef CONFIG_IPF_PROPERTY_MBB
				bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
			#endif
				spin_unlock_irqrestore(&ipf_filter_spinlock, flags);
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r IPF_MallocOneFilter error! \n");
				return BSP_ERR_IPF_FILTER_NOT_ENOUGH;
			}
		}
		if(0 == i)
		{
			u32FirstFilterID = current->u32FilterID;
		}
		current->u32PsID = (pstFilterInfo->u32FilterID)&IPF_FILTERTYPE_MASK;
		/* 先将NextIndex配置为511 */
		pstFilterInfo->stMatchInfo.unFltChain.Bits.u16NextIndex = IPF_TAIL_INDEX;
		IPF_AddTailFilterChain(u32LastFilterID, current->u32FilterID, &pstFilterInfo->stMatchInfo);
		IPF_AddTailUsedFilter(eFilterChainhead, current);
		u32LastFilterID = current->u32FilterID;
		pstFilterInfo++; 
	}
	
	/*将配置好的过滤器链挂到链首上*/
	ipf_writel(eFilterChainhead, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET);
	ipf_writel(u32FirstFilterID, ipf_base_addr_ccore+HI_FLT_CHAIN_OFFSET); 
	
	/*备份更改后的首过滤器*/
	BSP_IPF_BackupFilter(eFilterChainhead);
	cache_sync();


	#ifndef CONFIG_IPF_PROPERTY_MBB
		bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
	#endif
	spin_unlock_irqrestore(&ipf_filter_spinlock, flags);

	return IPF_SUCCESS;
}
/*****************************************************************************
* 函 数 名      : BSP_IPF_GetFilter
*
* 功能描述  : 提供给PS查询某个Filter配置信息
*
* 输入参数  : unsigned int u32FilterID   Filter ID号注意这个是psid
*             
* 输出参数  : IPF_FILTER_CONFIG_S * pFilterInfo  查询到的Filter信息

* 返 回 值     : IPF_SUCCESS                查询成功
*                           IPF_ERROR                  查询失败
*                           BSP_ERR_IPF_NOT_INIT       模块未初始化
*                           BSP_ERR_IPF_INVALID_PARA   参数错误
*
* 修改记录  : 2011年1月11日   鲁婷  创建
                             2011年3月30日   鲁婷  修改
                             2011    11月30日   鲁婷  修改
                             2012    11月26日   陈东岳修改
				 			 2014年1月23日v1.01 陈东岳 修改 由于K3V3总线设计问题，
							 无法在m3上进行低功耗恢复，移动到A9上进行。
*****************************************************************************/
int mdrv_ipf_get_filter(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, unsigned int u32FilterID, IPF_FILTER_CONFIG_S *pstFilterInfo)
{
    unsigned int u32FindID = 0;
    


    /* 参数检查 */
    if(NULL == pstFilterInfo)
    {
 		g_ipf_ctx.status->invalid_para++;
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_get_filter invalid para\n");
		return BSP_ERR_IPF_INVALID_PARA;
	}

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init\n");
        return BSP_ERR_IPF_NOT_INIT;
    }

	
#ifndef CONFIG_IPF_PROPERTY_MBB
    /*由于K3V3总线设计问题，使用ipf 前需要检测是否需要恢复过滤器*/
    ipf_check_filter_restore();
#endif
    /* 查找PS ID 对应的FilterID*/
    if(IPF_FindFilterID(eFilterChainhead, u32FilterID, &u32FindID) != IPF_SUCCESS)
    {
        return IPF_ERROR;
    }
    pstFilterInfo->u32FilterID = u32FilterID;    
    
    /* 如果是基本过滤器 */
    if(u32FindID < IPF_BF_NUM)
    {
        /* 写过滤表操作地址 */    
        ipf_writel(u32FindID, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET); 
         
        /* 读出过滤器的配置 */
        memcpy_s(&pstFilterInfo->stMatchInfo, sizeof(IPF_MATCH_INFO_S), (void*)(ipf_base_addr_ccore+HI_FLT_LOCAL_ADDR0_OFFSET), sizeof(IPF_MATCH_INFO_S));/* [false alarm]:fortify disable */
    }
    /* 扩展过滤器 */
    else
    {
        /* 读出过滤器的配置 */
        memcpy_s(&pstFilterInfo->stMatchInfo, sizeof(IPF_MATCH_INFO_S), (void*)(g_pstExFilterAddr + u32FindID - IPF_BF_NUM), sizeof(IPF_MATCH_INFO_S));
    }
    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名      : IPF_ConfigCD
*
* 功能描述  : 配置CD
*
* 输入参数  : IPF_TTF_MEM_ST *pstTtf, unsigned short* pu16TotalDataLen, unsigned int* pu32BdInPtr
* 输出参数  : 无
* 返 回 值      :  无
*
* 修改记录  :2011年1月24日   鲁婷  创建
*****************************************************************************/
int IPF_ConfigCD(void *pstTtf, unsigned short* pu16TotalDataLen, unsigned int* pu32BdInPtr)
{
    unsigned int u32DlCDWptr = 0;
    unsigned int u32DlCDRptr = 0;
    unsigned short u16TotalDataLen = 0;
	unsigned int* header = (unsigned int*)pstTtf;

    /* 为防止BD 满或者后续申请目的地址不成功，设置临时cd的位置 */
    u32DlCDWptr = g_stIpfDl.u32IpfCdWptr;
    u32DlCDRptr = *(g_stIpfDl.u32IpfCdRptr);
    *pu32BdInPtr = (unsigned int)(g_stIpfDl.pstIpfCDQ + (u32DlCDWptr));

    /* 配置CD */
    do
    {
        /* 判断是否有空闲CD */
        if(u32DlCDRptr != (u32DlCDWptr+1)%IPF_DLCD_DESC_SIZE)
        {
            g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u32Ptr = (unsigned int)IPF_GET_MEMBLK_BUF(header);
			g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u16PktLen = IPF_GET_MEMBLK_LEN(header);
            u16TotalDataLen += IPF_GET_MEMBLK_LEN(header);
            
            /* 标识是否结束 */
            if(IPF_GET_NEXT_MEMBLK(header) != NULL)
            {
                g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u16Attribute = 0;
                if(u32DlCDWptr+1 < IPF_DLCD_DESC_SIZE)
                {
                    u32DlCDWptr += 1;
                    header = IPF_GET_NEXT_MEMBLK(header);
                }
                /* 未结束时，CD不能翻转，这是记录CD的尾部，同时将从0开始配置CD */
                else
                {
                    u32DlCDWptr = 0;
                    u16TotalDataLen = 0;
                    header = (unsigned int*)pstTtf;
                    *pu32BdInPtr = (unsigned int)g_stIpfDl.pstIpfCDQ;
                }
            }
            else
            {
                g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u16Attribute = 1;
                
                /* 结束时CD可以翻转 */
                u32DlCDWptr = (u32DlCDWptr+1 < IPF_DLCD_DESC_SIZE)?(u32DlCDWptr+1):0;
                break;
            }
        }
        else
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,
                    "\r DownFilter CD FULL ! u32DlCDRptr=%d u32DlCDWptr=%d\n",u32DlCDRptr,u32DlCDWptr);
            return BSP_ERR_IPF_CDQ_NOT_ENOUGH;
        }        
    }while(header != NULL);
    
    g_stIpfDl.u32IpfCdWptr = u32DlCDWptr;
    *pu16TotalDataLen = u16TotalDataLen;    
    return IPF_SUCCESS;
}

int ipf_config_dlbd(unsigned int u32Num, IPF_CONFIG_DLPARAM_S* pstDlPara)
{
    unsigned int u32BdqWptr = 0;
    unsigned int i;
    unsigned int u32BdInPtr = 0;
    unsigned int u32BD = 0;
    unsigned short u16TotalDataLen = 0;
    unsigned int u32TimeStampEn;
    ipf_desc_attr_t bd_attr;
	IPF_DL_S* dl_bd = &g_stIpfDl;
	unsigned long flags = 0;

    /*入参检查*/
    if((NULL == pstDlPara)||(0 == u32Num))
    {
    	g_ipf_ctx.status->invalid_para++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"ipf_config_dlbd invalid para\n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

	/* coverity[FORWARD_NULL] */
    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init\n");
        return BSP_ERR_IPF_NOT_INIT;
    }

    /* 检查Ccore是否上电*/
    if(IPF_FORRESET_CONTROL_FORBID <= bsp_ipf_get_control_flag_for_ccore_reset())
    {
    	/* coverity[var_deref_op] */
        g_ipf_ctx.status->mdrv_called_not_init++;
        return BSP_ERR_IPF_CCORE_RESETTING;
    }

#ifndef CONFIG_IPF_PROPERTY_MBB
    /*由于K3V3总线设计问题，使用ipf 前需要检测是否需要恢复过滤器*/
    ipf_check_filter_restore();
#endif
	
    /*
    chendongyue c00228781: DTS2013061501582
    检测每个BD中数据的有效性，本来这里应该由上层保证，
    但是出了BUG令BD长度为0，故在这里进行规避
    */
    for(i = 0; i < u32Num; i++)
    {
        if(0 == pstDlPara[i].u16Len)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r INPUT BD_Len =0 !Drop pkt \n");
			/* coverity[var_deref_op] */
            g_ipf_ctx.status->bd_len_zero_err++;
            return BSP_ERR_IPF_INVALID_PARA;
        }
    }

    /* 读出BD写指针 */
    u32BdqWptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_BDQ_WPTR_OFFSET);
    u32BD = u32BdqWptr&IPF_DQ_PTR_MASK;
	/* coverity[var_deref_op] */
    u32TimeStampEn = g_ipf_ctx.status->timestamp_en;/*[false alarm]:fortify*/

    for(i = 0; i < u32Num; i++)
    {
        /* 配置CD */
        if(IPF_ConfigCD((void*)pstDlPara[i].u32Data, &u16TotalDataLen, &u32BdInPtr) != IPF_SUCCESS)
        {
            g_ipf_ctx.status->cd_not_enough++;
            return BSP_ERR_IPF_CDQ_NOT_ENOUGH;
        }
        bd_attr.u16 = pstDlPara[i].u16Attribute;
        bd_attr.bits.cd_en = ipf_enable;
        dl_bd->pstIpfBDQ[u32BD].u16Attribute = bd_attr.u16; 
        dl_bd->pstIpfBDQ[u32BD].u32InPtr =  u32BdInPtr;
        dl_bd->pstIpfBDQ[u32BD].u16PktLen = u16TotalDataLen;
        dl_bd->pstIpfBDQ[u32BD].u16UsrField1 = pstDlPara[i].u16UsrField1;
        dl_bd->pstIpfBDQ[u32BD].u32UsrField2 = pstDlPara[i].u32UsrField2;
        dl_bd->pstIpfBDQ[u32BD].u32UsrField3 = pstDlPara[i].u32UsrField3;
        ipf_record_start_time_stamp(u32TimeStampEn, &dl_bd->pstIpfBDQ[u32BD].u32UsrField2);
        u32BD = ((u32BD + 1) < IPF_DLBD_DESC_SIZE)? (u32BD + 1) : 0;
		
    }

	spin_lock_irqsave(&ipf_dlbd_spinlock, flags);
    /* 检查Ccore是否上电*/
    if(IPF_FORRESET_CONTROL_FORBID <= bsp_ipf_get_control_flag_for_ccore_reset())
    {
        g_ipf_ctx.status->mdrv_called_not_init++;
		spin_unlock_irqrestore(&ipf_dlbd_spinlock, flags);
        return BSP_ERR_IPF_CCORE_RESETTING;
    }

    g_ipf_ctx.status->cfg_bd_cnt += u32Num;

    /* 更新BD写指针 */
    ipf_writel(u32BD, ipf_base_addr_ccore + HI_IPF_CH1_BDQ_WPTR_OFFSET);  
	spin_unlock_irqrestore(&ipf_dlbd_spinlock, flags);
    return IPF_SUCCESS;
}

int mdrv_ipf_config_dlbd(unsigned int u32Num, IPF_CONFIG_DLPARAM_S* pstDlPara)
{	
	ipf_start_addr_limit();
	
	g_ipf_ctx.status->cfg_bd_times++;
	
#ifdef CONFIG_PSAM
	return bsp_psam_config_dlbd(u32Num, pstDlPara);
#else
	return ipf_config_dlbd(u32Num, pstDlPara);
#endif
}


/*****************************************************************************
* 函 数 名     : mdrv_ipf_config_ulad
*
* 功能描述  : 该接口仅在C核提供，用于移动ADQ写指针，
				给空闲的AD分配新的内存缓冲区，一次可以处理多个AD。
				数传前要调用这个函数分配缓冲区。
*                           
* 输入参数  : unsigned int u32Num0; 
				 unsigned int u32Num1; 
				 void* psk0; 
				 void* psk1
*
* 输出参数  : 无
* 返 回 值      : 无
* 修改记录  :2012年11月24日   陈东岳  创建
			2014年1月23日v1.01 陈东岳 修改 由于K3V3总线设计问题，
			无法在m3上进行低功耗恢复，移动到A9上进行。
*****************************************************************************/
int mdrv_ipf_config_ulad(IPF_AD_TYPE_E u32AdType, unsigned int  u32AdNum, IPF_AD_DESC_S * pstAdDesc)
{
	unsigned int u32ADQwptr = 0;
	struct tagIPF_AD_DESC_S * pstADDesc = pstAdDesc;
	unsigned int i;

	ipf_start_addr_limit();

	g_ipf_ctx.status->cfg_ad_times++;
	if(NULL == pstAdDesc || u32AdType >= IPF_AD_MAX)
	{
 		g_ipf_ctx.status->invalid_para++;
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_ulad invalid para\n");
		return BSP_ERR_IPF_INVALID_PARA;
	}

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init\n");
        return BSP_ERR_IPF_NOT_INIT;
    }

	
	if(IPF_AD_0 == u32AdType)
	{
		if(u32AdNum >= IPF_ULAD0_DESC_SIZE)
		{
	 		g_ipf_ctx.status->invalid_para++;
			bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_ulad input para ERROR! u32AdNum >=IPF_ULAD0_DESC_SIZE\n");
			return BSP_ERR_IPF_INVALID_PARA;
		}
		
		/*读出写指针*/
		u32ADQwptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_WPTR_OFFSET);
		for(i=0; i < u32AdNum; i++)
		{
			if(NULL == (void*)(pstADDesc->u32OutPtr1))
			{
				g_ipf_ctx.status->ad_out_ptr_null[IPF_AD_0]++;
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_ConfigDlAd input u32OutPtr1 NULL! \n");
				return BSP_ERR_IPF_INVALID_PARA;
			}
			g_stIpfUl.pstIpfADQ0[u32ADQwptr].u32OutPtr1 = pstADDesc->u32OutPtr1;
			g_stIpfUl.pstIpfADQ0[u32ADQwptr].u32OutPtr0 = pstADDesc->u32OutPtr0;
			u32ADQwptr = ((u32ADQwptr + 1) < IPF_ULAD0_DESC_SIZE)? (u32ADQwptr + 1) : 0;	
			pstADDesc++;
		}
		g_ipf_ctx.status->cfg_ad_cnt[IPF_AD_0] += u32AdNum;

		/* 更新AD0写指针*/
		ipf_writel(u32ADQwptr, ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_WPTR_OFFSET);  
	}
	
	else if(IPF_AD_1 == u32AdType)
	{
		if(u32AdNum >= IPF_ULAD1_DESC_SIZE)
		{
	 		g_ipf_ctx.status->invalid_para++;
			bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_ulad input para ERROR! u32AdNum >=IPF_ULAD1_DESC_SIZE\n");
			return BSP_ERR_IPF_INVALID_PARA;
		}
		
		/*读出写指针*/
		u32ADQwptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_WPTR_OFFSET);
		for(i=0; i < u32AdNum; i++)
		{
			if(NULL == (void*)(pstADDesc->u32OutPtr1))
			{
				g_ipf_ctx.status->ad_out_ptr_null[IPF_AD_1]++;
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_ConfigDlAd input u32OutPtr1 NULL! \n");
				return BSP_ERR_IPF_INVALID_PARA;
			}
			g_stIpfUl.pstIpfADQ1[u32ADQwptr].u32OutPtr1 = pstADDesc->u32OutPtr1;
			g_stIpfUl.pstIpfADQ1[u32ADQwptr].u32OutPtr0 = pstADDesc->u32OutPtr0;
			u32ADQwptr = ((u32ADQwptr + 1) < IPF_ULAD1_DESC_SIZE)? (u32ADQwptr + 1) : 0;		
			pstADDesc++;
		}
		g_ipf_ctx.status->cfg_ad_cnt[IPF_AD_1] += u32AdNum;

		/* 更新AD0写指针*/
		ipf_writel(u32ADQwptr, ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_WPTR_OFFSET);  

	}
	return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_ChannelEnable
*
* 功能描述  : 该接口用于使能或复位IP过滤器上下行通道
*
* 输入参数  : IPF_CHANNEL_TYPE_E eChanType      上下行通道标识
*                           int bFlag   使能复位标识 
*
* 输出参数  : 无
* 返 回 值      : IPF_SUCCESS                使能复位成功
*                            IPF_ERROR                  使能复位失败
*                            BSP_ERR_IPF_INVALID_PARA   参数错误
*
* 修改记录  :2011年1月11日   鲁婷  创建
			2014年1月23日v1.01 陈东岳 修改 由于K3V3总线设计问题，
			无法在m3上进行低功耗恢复，移动到A9上进行。
*****************************************************************************/
int mdrv_ipf_enable_chan(IPF_CHANNEL_TYPE_E eChanType, int bFlag)
{
    unsigned int u32ChanEnable = 0;
    unsigned int u32ChanState = 0;
    unsigned int u32Times = 0;
    unsigned int u32ChCtrl = 0;


    /* 参数检查 */
    if(eChanType >= IPF_CHANNEL_MAX)
    {
 		g_ipf_ctx.status->invalid_para++;
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_enable_chan invalid para\n");
		return BSP_ERR_IPF_INVALID_PARA;
	}

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init\n");
        return BSP_ERR_IPF_NOT_INIT;
    }


    /* 通道使能 */
    if(bFlag)
    {
        u32ChanEnable = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH_EN_OFFSET);
        u32ChanEnable |= 0x1<<eChanType;
        ipf_writel(u32ChanEnable, ipf_base_addr_ccore + HI_IPF_CH_EN_OFFSET);                        
    }
    /* 通道去使能 */
    else
    {
        u32ChanEnable = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH_EN_OFFSET);
        u32ChanEnable &= 0xFFFFFFFF ^ (0x1<<eChanType);
        ipf_writel(u32ChanEnable, ipf_base_addr_ccore + HI_IPF_CH_EN_OFFSET); 
        
        /* 遍历直到通道状态为0 */      
        do
        {
            (void)osl_task_delay(1);
            u32ChanState = ipf_readl(ipf_base_addr_ccore + HI_IPF_EN_STATE_OFFSET);
            u32ChanState &= 0x1<<eChanType;
            u32Times++;
        }while((u32ChanState) && (u32Times < 100)); 
        
        if(100 == u32Times)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,
                       "\r mdrv_ipf_enable_chan disable error u32Times = %d ! \n",u32Times,0,0,0,0,0);
            return IPF_ERROR;
        }
		
        /* 复位输入队列和输出队列的读写指针 */
        if(IPF_CHANNEL_UP == eChanType)
        {
            u32ChCtrl = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET);
            u32ChCtrl |= 0x30; /* 将4，5bit设置为1 */
            ipf_writel(u32ChCtrl, ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET); 
        }
        else if(IPF_CHANNEL_DOWN == eChanType)
        {
            u32ChCtrl = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET);
            u32ChCtrl |= 0x30; /* 将4，5bit设置为1 */
            ipf_writel(u32ChCtrl, ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET); 
        }
        else
        {
            return BSP_ERR_IPF_INVALID_PARA;
        }
    }
    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名     : mdrv_ipf_get_dlbd_num
*
* 功能描述  : 该接口用于获取下行空闲BD和CD 数目
*                           BD 范围: 0~63      CD范围: 0~1023
* 输入参数  : 无
*
* 输出参数  : 空闲CD数目
* 返 回 值      : 空闲BD数目
*  
* 修改记录  :2011年11月30日   鲁婷  创建
			2014年1月23日v1.01 陈东岳 修改 由于K3V3总线设计问题，
			无法在m3上进行低功耗恢复，移动到A9上进行。

*****************************************************************************/
unsigned int ipf_get_dlbd_num (unsigned int* pu32CDNum)
{
    unsigned int u32BdqDepth = 0;
    unsigned int u32IdleBd = 0;
    unsigned int u32IdleCd = 0;
    unsigned int u32IdleCdDown = 0;
    unsigned int u32IdleCdUp = 0;
	

    /* 计算空闲BD数量 */
    u32BdqDepth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_DQ_DEPTH_OFFSET);
    u32BdqDepth = u32BdqDepth & IPF_DQ_DEPTH_MASK;
    u32IdleBd = IPF_DLBD_DESC_SIZE - u32BdqDepth;
    /* 计算空闲CD 数量 */
    if(*(g_stIpfDl.u32IpfCdRptr) > g_stIpfDl.u32IpfCdWptr)
    {
        u32IdleCd = *(g_stIpfDl.u32IpfCdRptr) - g_stIpfDl.u32IpfCdWptr - 1;
    }
    else
    {
        u32IdleCdUp = (*(g_stIpfDl.u32IpfCdRptr) > 1)?(*(g_stIpfDl.u32IpfCdRptr) - 1):0;
        u32IdleCdDown = IPF_DLCD_DESC_SIZE -  g_stIpfDl.u32IpfCdWptr - 1;
        u32IdleCd = (u32IdleCdUp > u32IdleCdDown)? u32IdleCdUp:u32IdleCdDown;
    }
    g_stIpfDl.u32IdleBd = u32IdleBd;
    *pu32CDNum = u32IdleCd;

    if(0 == u32IdleBd)
	{
		g_ipf_ctx.status->bd_full++;
	}
    return u32IdleBd;
}

unsigned int mdrv_ipf_get_dlbd_max_num(void)
{
#ifdef CONFIG_PSAM
	return (PSAM_DLBD_DESC_SIZE - PSAM_DLBD_RES_NUM);
#else
	return IPF_DLBD_DESC_SIZE;
#endif
}

unsigned int mdrv_ipf_get_dlbd_num (unsigned int* pu32CDNum)
{
	g_ipf_ctx.status->get_bd_num_times++;
#ifdef CONFIG_PSAM
	return bsp_psam_get_dlbd_num(pu32CDNum);
#else
	return ipf_get_dlbd_num(pu32CDNum);
#endif
}

/*****************************************************************************
* 函 数 名     : mdrv_ipf_get_dlrd_num
*
* 功能描述  : 该接口用于读取下行RD数目
*
* 输入参数  : 无
*   
* 输出参数  : 无
*
* 返 回 值     : 下行RD数目
*
* 修改记录  :2013年8月1日   chendongyue  创建
*****************************************************************************/
unsigned int mdrv_ipf_get_dlrd_num(void)
{
    unsigned int u32RdqDepth = 0;

    /* 读取RD深度 */
    u32RdqDepth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_DQ_DEPTH_OFFSET);
    u32RdqDepth = (u32RdqDepth>>16)&IPF_DQ_DEPTH_MASK;
    return u32RdqDepth;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_RegisterWakeupUlCb
*
* 功能描述  : 该接口用于注册上行PS任务回调函数
*                           
* 输入参数  : BSP_IPF_WakeupUlCb *pFnWakeupUl
*
* 输出参数  : 无
* 返 回 值      : 无
*  
* 修改记录  :2011年11月30日   鲁婷  创建
*****************************************************************************/
int ipf_register_wakeup_ulcb(BSP_IPF_WakeupUlCb pFnWakeupUl)
{
    /* 参数检查 */
    if(NULL == pFnWakeupUl)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_RegisterWakeupUlCb inputPara ERROR! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    g_stIpfUl.pFnUlIntCb = pFnWakeupUl;
    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_RegisterAdqEmptyUlCb
*
* 功能描述  : 此接口只在C核提供，用于注册唤醒上行PS的
                             ADQ队列空回调函数
*                           
* 输入参数  : BSP_IPF_AdqEmptyCb pFnWakeupUl
*
* 输出参数  : 无
* 返 回 值      : IPF_SUCCESS 注册成功
*                            IPF_ERROR	注册失败
* 修改记录  :2012年11月24日   陈东岳  创建
*****************************************************************************/
int ipf_register_adq_empty_ulcb(BSP_IPF_AdqEmptyUlCb pAdqEmptyUl)
{
    /* 参数检查 */
    if(NULL == pAdqEmptyUl)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_RegisterAdqEmptyUlCb inputPara ERROR! \n");
        return IPF_ERROR;
    }
    g_stIpfUl.pAdqEmptyUlCb = pAdqEmptyUl;
    return IPF_SUCCESS;
}

int ipf_rd_rate(unsigned int enable, IPF_CHANNEL_TYPE_E eChnType)
{	
	unsigned int rate = 0;
	unsigned int rd_len = 0;
	unsigned int rd_ts =  0;
	unsigned int ratio = IPF_LEN_RATIO / (IPF_TIMER_RATIO * 8);
	
	if(!enable) {
		return IPF_ERROR;
	}

	if(eChnType > IPF_CHANNEL_DOWN){
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"eChnType err!\n");/* [false alarm]:fortify disable */
		return IPF_ERROR;
	}
	
	switch(eChnType)
    {
        case IPF_CHANNEL_UP:			
			rd_ts =  bsp_get_slice_value() - g_ipf_ctx.status->rd_ts;
			if(rd_ts < IPF_RD_TMOUT) {
				return IPF_ERROR;
			}
			
			rd_len = g_ipf_ctx.status->rd_len_update - g_ipf_ctx.status->rd_len;
			g_ipf_ctx.status->rd_ts = bsp_get_slice_value();
			g_ipf_ctx.status->rd_len = g_ipf_ctx.status->rd_len_update;
			break;
		default:
            break;
	}
	
	if(rd_len <= 0 || rd_ts <= 0) {
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"ipf rd len or ts err!\n");
		return IPF_ERROR;
	} else {
		rate = rd_len / (rd_ts * ratio);
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"ipf rd rate:%uMbps\n", rate);
	}
	
	return IPF_SUCCESS;
}
int mdrv_ipf_register_ops(struct mdrv_ipf_ops *ops)
{
	if(ops)
	{
		if(ipf_register_wakeup_ulcb(ops->rx_complete_cb)!= IPF_SUCCESS)
			return IPF_ERROR;
		if(ipf_register_adq_empty_ulcb(ops->adq_empty_cb)!= IPF_SUCCESS)
			return IPF_ERROR;
	}
	return IPF_SUCCESS;
}

static inline void ipf_pm_print_packet(void *buf, unsigned int len)
{
	if (g_ipf_ctx.status->resume_with_intr){

		if (len > MAX_PM_OM_SAVE_SIZE) {
			len = MAX_PM_OM_SAVE_SIZE;
		}
		
		bsp_pm_log(PM_OM_CIPF, len, buf);
		
		g_ipf_ctx.status->resume_with_intr = 0;
	}
	return;
}

/*****************************************************************************
* 函 数 名     : mdrv_ipf_get_ulrd
*
* 功能描述  : 该接口用于读取上行BD, 支持一次读取多个BD
*
* 输入参数  : unsigned int* pu32Num    
*                           IPF_RD_DESC_S *pstRd
*   
* 输出参数  : unsigned int* pu32Num    实际读取的RD数目
*
* 返 回 值     : IPF_SUCCESS               操作成功
*                           IPF_ERROR                   操作失败
*
* 修改记录  :2011年11月30日   鲁婷  创建
*****************************************************************************/
void mdrv_ipf_get_ulrd(unsigned int* pu32Num, IPF_RD_DESC_S *pstRd)
{
    unsigned int u32RdqRptr = 0;
    unsigned int u32RdqDepth = 0;
    unsigned int u32Num = 0;
    unsigned int i = 0;
    unsigned int u32TimeStampEn;
	unsigned int rd_rate_en;
	
	ipf_start_addr_limit();
	
    /* 读取RD深度 */
    u32RdqDepth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_DQ_DEPTH_OFFSET);
    u32RdqDepth = (u32RdqDepth>>16)&IPF_DQ_DEPTH_MASK;
    u32Num = (u32RdqDepth < *pu32Num)?u32RdqDepth:*pu32Num;

	g_ipf_ctx.status->get_rd_times++;
    if(0 == u32Num)
    {
        *pu32Num = 0;
        return;
    }

    u32TimeStampEn = g_ipf_ctx.status->timestamp_en;
	rd_rate_en = g_ipf_ctx.status->rate_en;

    /* 读取RD读指针 */
    u32RdqRptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_RDQ_RPTR_OFFSET);
    for(i = 0; i < u32Num; i++)
    {        
        /* 获取RD */
        pstRd[i].u16Attribute = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16Attribute;
        pstRd[i].u16PktLen = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16PktLen;
        pstRd[i].u16Result = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16Result;
        pstRd[i].u32InPtr = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32InPtr;
        pstRd[i].u32OutPtr = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32OutPtr;
        pstRd[i].u16UsrField1 = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16UsrField1;
        pstRd[i].u32UsrField2 = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32UsrField2;
        pstRd[i].u32UsrField3 = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32UsrField3;
        ipf_record_end_time_stamp(u32TimeStampEn, g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32UsrField2);

		ipf_pm_print_packet((void*)pstRd[i].u32OutPtr, pstRd[i].u16PktLen);
        /* 更新RD读指针 */
        u32RdqRptr = ((u32RdqRptr+1) < IPF_ULRD_DESC_SIZE)?(u32RdqRptr+1):0;
		
		g_ipf_ctx.status->rd_len_update += pstRd[i].u16PktLen;

		pstRd[i].u16PktLen > (g_ipf_ctx.status->ad_thred)? g_ipf_ctx.status->get_rd_cnt[IPF_AD_1]++:\
							   		  g_ipf_ctx.status->get_rd_cnt[IPF_AD_0]++;
    }

	ipf_rd_rate(rd_rate_en, IPF_CHANNEL_UP);
    ipf_writel(u32RdqRptr, ipf_base_addr_ccore + HI_IPF_CH0_RDQ_RPTR_OFFSET);

    *pu32Num = u32Num;
}


/*****************************************************************************
* 函 数 名       : mdrv_ipf_get_ulad_num
*
* 功能描述  : 该接口只在C核提供，获取上行（C核）空闲AD数目
*
* 输入参数  :BSP_OK：正常返回
                            BSP_ERROR：出错
*             
* 输出参数  : 无
* 返 回 值     : 无
* 修改记录  : 2011年11月24日   陈东岳  创建
			2014年1月23日v1.01 陈东岳 修改 由于K3V3总线设计问题，
			无法在m3上进行低功耗恢复，移动到A9上进行。
*****************************************************************************/
int mdrv_ipf_get_ulad_num(unsigned int* pu32AD0Num,unsigned int* pu32AD1Num)
{
	unsigned int u32UlAdDepth = 0;
	unsigned int u32UlAdwptr = 0;
	unsigned int u32UlAdrptr = 0;



	g_ipf_ctx.status->get_ad_num_times++;
	/*入参检测*/
	if((NULL == pu32AD0Num)||(NULL == pu32AD1Num))
	{
		g_ipf_ctx.status->invalid_para++;
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_get_ulad_num pstCtrl NULL! \n");
		return BSP_ERR_IPF_INVALID_PARA;
	}
	/* 计算空闲AD数量 */
	u32UlAdwptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_WPTR_OFFSET);
	u32UlAdrptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_RPTR_OFFSET);
	if (u32UlAdwptr >= u32UlAdrptr)/*写指针在前，正常顺序*/
	{
		u32UlAdDepth = IPF_ULAD0_DESC_SIZE - (u32UlAdwptr - u32UlAdrptr);
	}
	else
	{
		u32UlAdDepth =  u32UlAdrptr -u32UlAdwptr;
	}
	*pu32AD0Num = u32UlAdDepth;

	/*扣除reserve ad，用于防止硬件将ad队列满识别成空和低功耗引发内存泄露*/	
	if(u32UlAdDepth > IPF_ADQ_RESERVE_NUM)
	{
		*pu32AD0Num = u32UlAdDepth - IPF_ADQ_RESERVE_NUM;
	}
	else
	{
		*pu32AD0Num = 0;
	}

	u32UlAdwptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_WPTR_OFFSET);
	u32UlAdrptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_RPTR_OFFSET);
	if (u32UlAdwptr >= u32UlAdrptr)/*写指针在前，正常顺序*/
	{
		u32UlAdDepth = IPF_ULAD1_DESC_SIZE - (u32UlAdwptr - u32UlAdrptr);
	}
	else
	{
		u32UlAdDepth =  u32UlAdrptr - u32UlAdwptr;
	}
	
	/*扣除reserve ad，用于防止硬件将ad队列满识别成空和低功耗引发内存泄露*/
	if(u32UlAdDepth > IPF_ADQ_RESERVE_NUM)
	{
		*pu32AD1Num = u32UlAdDepth - IPF_ADQ_RESERVE_NUM;
	}
	else
	{
		*pu32AD1Num = 0;
	}

	return IPF_SUCCESS;
}


/*****************************************************************************
* 函 数 名     : mdrv_ipf_get_ulrd_num
*
* 功能描述  : 该接口用于读取上行RD数目
*
* 输入参数  : 无
*   
* 输出参数  : 无
*
* 返 回 值     : 上行RD数目
*
* 修改记录  :2012年2月16日   鲁婷  创建
*****************************************************************************/
unsigned int mdrv_ipf_get_ulrd_num(void)
{
    unsigned int u32RdqDepth = 0;
	g_ipf_ctx.status->get_rd_num_times++;  
    /* 读取RD深度 */
    u32RdqDepth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_DQ_DEPTH_OFFSET);
    u32RdqDepth = (u32RdqDepth>>16)&IPF_DQ_DEPTH_MASK;
    return u32RdqDepth;
}

int mdrv_ipf_set_dbuf_para(unsigned int bufoffset, 
							unsigned int lenoffset, unsigned int nextoffset)
{
	memblk_offset.bufoffset = bufoffset;
	memblk_offset.lenoffset = lenoffset;
	memblk_offset.nextoffset = nextoffset;
	
	return 0;
}
/*****************************************************************************
* 函 数 名       : BSP_IPF_SwitchInt
*
* 功能描述  : 提供的低功耗接口， 将上报给A核的中断同时上报给C 核
*
* 输入参数  : 1   上报给C核
*                           0  不上报给C核
*             
* 输出参数  : 无
* 返 回 值     : 无
* 修改记录  : 2011年2月14日   鲁婷  创建
*****************************************************************************/
void BSP_IPF_SwitchInt(int bFlag)
{
	unsigned int u32IntMask0 = 0;

	if(bFlag == 1)
	{
    	u32IntMask0 = IPF_INT_OPEN0 | IPF_INT_OPEN1;
		g_u32IpfSwitchInt = 1;
	}
	else
	{
		u32IntMask0 = IPF_INT_OPEN0;
		g_u32IpfSwitchInt = 0;
	}
    ipf_writel(u32IntMask0, ipf_base_addr_ccore + HI_IPF_INT_MASK0_OFFSET);
}

/*****************************************************************************
* 函 数 名  : bsp_ipf_usefilterinfo
*
* 功能描述  : 提供的debug接口，获取已经使用的filter号
*
* 输入参数  : IPF_CHANNEL_TYPE_E eChnType  通道类型
*             
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2011年1月11日   鲁婷  创建
                             2011年3月30日   鲁婷  修改
*****************************************************************************/
void bsp_ipf_usefilterinfo(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead)
{
    IPF_ID_S* current = NULL;
    unsigned int u32FilterNum = 0;
/*    int s32GetChar = 0;*/
    
    u32FilterNum = g_stIPFFilterInfo[eFilterChainhead].u32FilterNum;
    current = g_stIPFFilterInfo[eFilterChainhead].pstUseList;
	
    IPF_PRINT("Total Filter Num = %u\n",u32FilterNum);            
    IPF_PRINT("=============================\n");

    while(u32FilterNum)
    { 
        while(u32FilterNum)
        {
            if(1 == u32FilterNum)
            {
                IPF_PRINT("Filter ID = %d,    PS ID = %d\n    ,Next HWID = %d\n",current->u32FilterID, current->u32PsID, current->pstNext->u32FilterID);            
                u32FilterNum--;
            }
            else
            {
                IPF_PRINT("Filter ID = %d,    PS ID = %d\n    ,Next HWID = %d\n",current->u32FilterID, current->u32PsID, current->pstNext->u32FilterID);            
                current = current->pstNext;
                u32FilterNum--;
            }
        }
    }
    IPF_PRINT("*****************************\n");

}

/*****************************************************************************
* 函 数 名  : BSP_IPF_FreeFilterInfo
*
* 功能描述  : 提供的debug接口，获取未使用的filter号
*
* 输入参数  : IPF_CHANNEL_TYPE_E eChnType  通道类型
*             
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2011年1月11日   鲁婷  创建
*
*****************************************************************************/
void bsp_ipf_basicfreefilterinfo(void)
{
    IPF_ID_S* current = NULL;
/*    int s32GetChar = 0;*/

    current = g_stIPFBasicFreeList;

    IPF_PRINT("============================\n");

    while(current != NULL)
    {
        while(current != NULL)
        {
            IPF_PRINT("Filter ID:      %d\n",current->u32FilterID);
            current = current->pstNext; 
        }
    }
    IPF_PRINT("*****************************\n");    
}
void bsp_ipf_extfreefilterinfo(void)
{
    IPF_ID_S* current = NULL;
/*    int s32GetChar = 0;*/

    current = g_stIPFExtFreeList;

    IPF_PRINT("============================\n");

    while(current != NULL)
    {
        while(current != NULL)
        {
            IPF_PRINT("Filter ID:      %d\n",current->u32FilterID);
            current = current->pstNext; 
        }
    }
    IPF_PRINT("*****************************\n");    
}

void bsp_ipf_filterinfohwid(unsigned int u32Num)
{
    IPF_MATCH_INFO_S stMatchInfo; 
    
    if(u32Num < IPF_BF_NUM)
    {
         /* 写过滤表操作地址 */    
        ipf_writel(u32Num, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET); 
         
        /* 读出过滤器的配置 */
        memcpy_s(&stMatchInfo, sizeof(IPF_MATCH_INFO_S), (void*)(ipf_base_addr_ccore+HI_FLT_LOCAL_ADDR0_OFFSET), sizeof(IPF_MATCH_INFO_S));/* [false alarm]:fortify disable */
    }
    else
    {
        memcpy_s(&stMatchInfo, sizeof(IPF_MATCH_INFO_S), (void*)(g_pstExFilterAddr + u32Num - IPF_BF_NUM), sizeof(IPF_MATCH_INFO_S));
    }

    IPF_PRINT("============================\n");
    IPF_PRINT("src ADDR0 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[0], stMatchInfo.u8SrcAddr[1], stMatchInfo.u8SrcAddr[2], stMatchInfo.u8SrcAddr[3]);
    IPF_PRINT("src ADDR1 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[4], stMatchInfo.u8SrcAddr[5], stMatchInfo.u8SrcAddr[6], stMatchInfo.u8SrcAddr[7]);
    IPF_PRINT("src ADDR2 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[8], stMatchInfo.u8SrcAddr[9], stMatchInfo.u8SrcAddr[10], stMatchInfo.u8SrcAddr[11]);
    IPF_PRINT("src ADDR3 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[12], stMatchInfo.u8SrcAddr[13], stMatchInfo.u8SrcAddr[14], stMatchInfo.u8SrcAddr[15]);
    IPF_PRINT("dst ADDR0 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[0], stMatchInfo.u8DstAddr[1], stMatchInfo.u8DstAddr[2], stMatchInfo.u8DstAddr[3]);
    IPF_PRINT("dst ADDR1 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[4], stMatchInfo.u8DstAddr[5], stMatchInfo.u8DstAddr[6], stMatchInfo.u8DstAddr[7]);
    IPF_PRINT("dst ADDR2 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[8], stMatchInfo.u8DstAddr[9], stMatchInfo.u8DstAddr[10], stMatchInfo.u8DstAddr[11]);
    IPF_PRINT("dst ADDR3 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[12], stMatchInfo.u8DstAddr[13], stMatchInfo.u8DstAddr[14], stMatchInfo.u8DstAddr[15]);
    IPF_PRINT("SrcPortLo : %d  SrcPortHi: %d\n", stMatchInfo.unSrcPort.Bits.u16SrcPortLo, stMatchInfo.unSrcPort.Bits.u16SrcPortHi);
    IPF_PRINT("DstPortLo : %d  DstPortHi: %d\n", stMatchInfo.unDstPort.Bits.u16DstPortLo, stMatchInfo.unDstPort.Bits.u16DstPortHi);
    IPF_PRINT("TrafficClass :      %d\n", stMatchInfo.unTrafficClass.u32TrafficClass);
    IPF_PRINT("TrafficClassMsk :  %d\n", stMatchInfo.u32LocalAddressMsk);
    IPF_PRINT("Protocol :          %d\n", stMatchInfo.unNextHeader.u32Protocol);
    IPF_PRINT("FlowLable :         %d\n", stMatchInfo.u32FlowLable);
    IPF_PRINT("Type :        %d  Code: %d\n", stMatchInfo.unFltCodeType.Bits.u16Type, stMatchInfo.unFltCodeType.Bits.u16Code);
    IPF_PRINT("NextIndex : %d  FltPri: %d\n", stMatchInfo.unFltChain.Bits.u16NextIndex, stMatchInfo.unFltChain.Bits.u16FltPri);
    IPF_PRINT("FltSpi :             %d\n", stMatchInfo.u32FltSpi);
    IPF_PRINT("FltRuleCtrl :        %x\n", stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl);    
    IPF_PRINT("============================\n");
}

void bsp_ipf_filterinfopsid(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, unsigned int u32Num)
{
    unsigned int u32FindID = 0;
    
    /* 查找PS ID 对应的FilterID*/
    if(IPF_FindFilterID(eFilterChainhead, u32Num, &u32FindID) != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r cannot find filter ID! \n");
        return ;
    }
    IPF_PRINT("HWID is %d",u32FindID);
    bsp_ipf_filterinfohwid(u32FindID);
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_BackupFilter
*
* 功能描述  : 备份基本过滤器到DDR
*
* 输入参数  : 过滤器ID
*   
* 输出参数  : 无
*
* 返 回 值     : 无
*
* 修改记录  :2013年5月16日   陈东岳  创建
*****************************************************************************/
void BSP_IPF_BackupFilter(unsigned int u32FilterID)
{
    unsigned int j;	
    unsigned int* match_info_addr = (unsigned int *)(IPF_PWRCTL_BASIC_FILTER_ADDR + u32FilterID*sizeof(IPF_MATCH_INFO_S));

    for(j=0; j<(sizeof(IPF_MATCH_INFO_S)/4); j++)
    {
        *match_info_addr = ipf_readl((ipf_base_addr_ccore+HI_FLT_LOCAL_ADDR0_OFFSET+j*4)); 
        match_info_addr++;

    }
}

#ifdef __cplusplus
}
#endif

/*lint -restore*/

