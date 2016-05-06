/*************************************************************************
*   版权所有(C) 1987-2011, 深圳华为技术有限公司.
*
*   文 件 名 :  om_balong.c
*
*   作    者 :  y00171698
*
*   描    述 :  M3 上OM
*
*   修改记录 :  2013年6月11日
*************************************************************************/
/*lint -save -e506 -e958 -e718 -e732 -e746*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <stdarg.h>
#include <osl_common.h>
#include "bsp_hardtimer.h"
#include "bsp_dump.h"
#ifndef K3V3_LPM3_HAS_MODEM_FEATURE
#include "m3_dump.h"
#else
#include "rdr.h"
#endif
#include "socp_balong.h"
#include "om_balong.h"

#ifdef ENABLE_BUILD_OM
/*global varibale for om module */
static bsp_om_global_s g_om_global_info ={0};

#ifndef K3V3_LPM3_HAS_MODEM_FEATURE
extern dump_global_info_t  *g_dump_global_info;
#endif

/*****************************************************************************
* 函 数 名  : om_header_packet
*
* 功能描述  : 打印数据包头信息填充
*
* 输入参数  :  mod_id: 输出模块
*                           print_level: 打印级别
*                           print_buf :整个buf指针
*                           buf_size: 整个输出的buf长度
* 输出参数  : 无
*
* 返 回 值  :
*****************************************************************************/
static void om_header_packet(u8 *print_buf, u32 buf_size, u32 str_id)
{
    bsp_om_gbl_s   *p_om_str;


    /* packet the buffer */
	p_om_str = (bsp_om_gbl_s *)(print_buf);
	p_om_str->hisi_head_str.hisiHead = BSP_HISI_HEAD;
	p_om_str->hisi_head_str.length   = buf_size - sizeof(bsp_hisi_head_s);
	p_om_str->socp_head_str.service_id = BSP_SOCP_SID_DIAG_SERVER;
	p_om_str->socp_head_str.s_service_id = (BSP_SOCP_HIGH4BIT_SSID_M3 << 4);
	p_om_str->socp_head_str.service_session_id = BSP_SOCP_SERVER_SESSION_ID;
	p_om_str->socp_head_str.msg_type = BSP_SOCP_MSG_TYPE_IND;
	p_om_str->socp_head_str.msg_trans_id = 0;
    memset((void *)p_om_str->socp_head_str.time_stamp, 0, sizeof(u32)*BSP_OM_TIMESTAMP_LEN);

    /* get 32 time slice */
    *(p_om_str->socp_head_str.time_stamp) = bsp_get_slice_value();

	p_om_str->om_head_str.om_id = (BSP_STRU_ID_28_31_GROUP_BSP << 28) | (BSP_STRU_ID_16_23_BSP_PRINT << 16 | str_id);  /*lint !e648*/ 
	p_om_str->om_head_str.data_size = buf_size - sizeof(bsp_hisi_head_s)-sizeof(bsp_socp_head_s)-sizeof(bsp_om_head_s);

}


/*****************************************************************************
* 函 数 名  : bsp_om_global_init
*
* 功能描述  : 全局初始化
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void om_log_init(void)
{
    
	g_om_global_info.om_cfg.nv_cfg.log_switch = BSP_LOG_SEND_TO_SHELL;
	g_om_global_info.print_sn = 0;
    g_om_global_info.trace_cnt = 0;

#ifdef K3V3_LPM3_HAS_MODEM_FEATURE

    register_modem_hook_func(om_m3_dump_save);
    
#endif
    return;
}

/*****************************************************************************
* 函 数 名  : om_switch_set
*
* 功能描述  : 全局初始化
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void om_switch_set(u32 ulSwitch)
{
	g_om_global_info.om_cfg.nv_cfg.log_switch = ulSwitch;

}

/*****************************************************************************
* 函 数 名  : bsp_log_bin_ind
*
* 功能描述  : 底软打印输出处理接口
*
* 输入参数  :  str_id: ssid
*                           ind_data: data to ind
*                           ind_data_size : size of data to ind
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void bsp_log_bin_ind(s32 str_id, void* ind_data, u32 ind_data_size)
{

#ifndef K3V3_LPM3_HAS_MODEM_FEATURE
    u32 u32Pktlen = 0;
    SOCP_BUFFER_RW_STRU  pTempBuff = {0};
    bsp_om_head_s   *om_head_str;

	if((NULL == ind_data) ||(0 == ind_data_size) || (ind_data_size > BSP_IND_DATA_MAX_LEN))
    {
       // printk("bsp_log_bin_ind: para is invalid, ind_data_size is %d\n",ind_data_size);
        return ;
    }

    if(TRUE == om_get_hso_connect_flag())
    {
    	bsp_socp_enable(SOCP_ENCSRC_LPM3_BASE);

        /* get input buffer */
        bsp_socp_get_write_buff(SOCP_ENCSRC_LPM3_BASE, &pTempBuff);

        if(NULL == pTempBuff.pBuffer)
        {
            //printk("bsp_log_bin_ind: pBuffer is null!\n");

            return;
        }
        
        u32Pktlen = sizeof(bsp_hisi_head_s)+sizeof(bsp_socp_head_s)+sizeof(bsp_om_head_s)+ ind_data_size;
        if(u32Pktlen > BSP_PRINT_BUF_LEN)
        {
            return ;
        }
        if(pTempBuff.u32Size >= BSP_PRINT_BUF_LEN)
        {
            om_header_packet((u8*)pTempBuff.pBuffer, u32Pktlen, (u32)str_id);

            om_head_str =(bsp_om_head_s *)(pTempBuff.pBuffer + sizeof(bsp_hisi_head_s)+sizeof(bsp_socp_head_s)+sizeof(bsp_om_head_s));

            memcpy((void *)om_head_str->data, ind_data, ind_data_size);

            /* 更新SOCP 通道的写指针*/
			bsp_socp_write_done(SOCP_ENCSRC_LPM3_BASE, BSP_PRINT_BUF_LEN);

        }
        else
		{
			//printk("bsp_log_bin_ind: u32Size and u32RbSize is not enough!\n");
            return;
		}

    }
#endif
    
}


u32 om_get_hso_connect_flag(void)
{
#ifndef K3V3_LPM3_HAS_MODEM_FEATURE
    if(BSP_NULL != g_dump_global_info)
    {
        return g_dump_global_info->internal_info.hso_connect_flag;
    }
#endif
    return FALSE ;
}

#ifdef K3V3_LPM3_HAS_MODEM_FEATURE
u32 *p_rdr_modem_sysctrl_file = BSP_NULL;
u32 *p_rdr_m3_sysctrl_file  = BSP_NULL;
u32 *p_rdr_app_sysctrl_file = BSP_NULL;
u32 *p_rdr_app_peri_crg_file = BSP_NULL;
__ao_data u32 *p_rdr_app_pmc_crg_file = BSP_NULL;
/* K3 dump */
void om_m3_dump_save()
{
    u32 ulCfgStatValue = 0;

    /* modem sysctrl regs */
    if(BSP_NULL == p_rdr_modem_sysctrl_file)
    {
        p_rdr_modem_sysctrl_file = (u32 *)rdr_balong_alloc_field(M3_MDM_SYSCTRL, HI_SYSCTRL_REG_SIZE);
    }

    /* m3 regs */
    if(BSP_NULL == p_rdr_m3_sysctrl_file)
    {
        p_rdr_m3_sysctrl_file = (u32 *)rdr_balong_alloc_field(M3_SYSCTRL, M3_SYSCTRL_TOTAL_LENGTH);
    }

    /* app sysctrl regs */
    if(BSP_NULL == p_rdr_app_sysctrl_file)
    {
        p_rdr_app_sysctrl_file = (u32 *)rdr_balong_alloc_field(M3_APP_SYSCTRL, HI_AP_SYSCTRL_REG_SIZE);
    }
    
    /* app sysctrl regs */
    if(BSP_NULL == p_rdr_app_peri_crg_file)
    {
        p_rdr_app_peri_crg_file = (u32 *)rdr_balong_alloc_field(M3_APP_PERICRG, HI_LP_PERI_CRG_REG_SIZE);
    }
    
     /* app PMC regs */
    if(BSP_NULL == p_rdr_app_pmc_crg_file)
    {
        p_rdr_app_pmc_crg_file = (u32 *)rdr_balong_alloc_field(M3_APP_PMCTRL, HI_PMC_REG_SIZE);
    }

    if(BSP_NULL != p_rdr_app_pmc_crg_file)
    {
        socp_memcpy(p_rdr_app_pmc_crg_file,(const u32 *)(HI_PMC_REGBASE_ADDR),(HI_PMC_REG_SIZE/sizeof(u32)));
    }
    /* save regs for dump */
    if(BSP_NULL != p_rdr_modem_sysctrl_file)
    {
        ulCfgStatValue = readl(CRG_SRSTSTAT1_AP_BASE_ADDR);
        if(!(ulCfgStatValue & CRG_STAT_MODEM_RST_MASK))
        {
           socp_memcpy(p_rdr_modem_sysctrl_file,(const u32 *)(HI_SYSCTRL_BASE_ADDR_VIRT),(HI_SYSCTRL_REG_SIZE/sizeof(u32))); 
        } 
    }

    if(BSP_NULL != p_rdr_m3_sysctrl_file)
    {
        socp_memcpy(p_rdr_m3_sysctrl_file,(const u32 *)(SCS_BASE),(M3_SYSCTRL_TOTAL_LENGTH/sizeof(u32)));
    }

    if(BSP_NULL != p_rdr_app_sysctrl_file)
    {
        socp_memcpy(p_rdr_app_sysctrl_file,(const u32 *)(HI_AP_SYSCTRL_BASE_ADDR_VIRT),(HI_AP_SYSCTRL_REG_SIZE/sizeof(u32)));
    }

    if(BSP_NULL != p_rdr_app_peri_crg_file)
    {
        socp_memcpy(p_rdr_app_peri_crg_file,(const u32 *)(HI_LP_PERI_CRG_REG_ADDR),(HI_LP_PERI_CRG_REG_SIZE/sizeof(u32)));
    }
    

    return ;

}

#endif
#endif /* ENABLE_BUILD_OM */

extern int console_xput(char ch, void *cookie);
extern void console_flush();

extern void xprintf(const char *fmt, va_list ap,
               void (*xputc)(unsigned n, void *cookie),
               void *cookie);
/*****************************************************************************
* 函 数 名  : bsp_trace
*
* 功能描述  : 底软打印输出处理接口
*
* 输入参数  :  mod_id: 输出模块
*                           print_level: 打印级别
*                           fmt :打印输入参数
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void bsp_trace(bsp_log_level_e log_level, bsp_module_e mod_id, char *fmt,...)
{
#ifdef K3V3_LPM3_HAS_MODEM_FEATURE
	u32     flag;  
	va_list arglist;

    /*whatever hso is connected, print to shell first */
    va_start(arglist, fmt);  /*lint !e530*/
	local_irq_save(flag);
	(void)log_print(mod_id, log_level, fmt, arglist);
	local_irq_restore(flag);
    va_end(arglist);
#else
	u32     flag; 
	va_list arglist;
	
	/*打印模块ID 过滤*/
    if(mod_id >= BSP_MODU_MAX )
    {
    	//printk("bsp_trace: mode is is invalid!\n");
        return ;
    }

    if(log_level < BSP_LOG_LEVEL_ERROR )
    {
        return ;
    }

    /*whatever hso is connected, print to shell first */
    va_start(arglist, fmt);  /*lint !e530*/
	local_irq_save(flag);
	xprintf(fmt, arglist, (void*)console_xput, 0);
	local_irq_restore(flag);
    va_end(arglist);

	console_flush();
#endif
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


/*lint -restore*/

