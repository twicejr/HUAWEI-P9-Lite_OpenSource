/*************************************************************************
*   版权所有(C) 1987-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  dual_modem_wakeup.c
*
*   作    者 :  张良栋 z00265007
*
*   描    述 :  该文件实现AP侧唤醒v3 modem和 v7r2 modem功能
*
*   修改记录 :  2014年05月22日  v1.00  z00265007  创建
*************************************************************************/

#include "bsp_icc.h"
#include "osl_common.h"
#include "uart.h"
#include "gpio.h"
#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "bsp_nvim.h"

#define VIA_WAKEUP_BALONG_PIN	GPIO_26_3
#define LPm3_UART5_IQR_ENABLE	(0xaa)
#define UART_INIT_ENABLE   		(0x02)
#define VIA_WAKEUP_BALONG		(0x01)
#define dm_print_info(fmt, ...)    (printk(""fmt"\n", ##__VA_ARGS__))
#define UART_SWITCH_ENABLE	(1)
#define DUAL_MODEM_CCORE_RESET_TRUE		(1)

struct dual_modem_icc_msg_str
{
    unsigned int dual_modem_init_flag;
	unsigned int icc_msgs_flag;
};

__ao_data u32 uart_init_flag = 0;
__ao_data DRV_DUAL_MODEM_STR dual_modem_lpm3_nv;

void bsp_dual_modem_disable_cb(void)
{
	uart_init_flag = 0;
}
/*****************************************************************************
 函 数 名  : via_wakeup_balong_handler
 功能描述  : gpio中断处理函数，发送icc给modem
 输入参数  : 
 输出参数  : 
 返 回 值  : void
*****************************************************************************/
void via_wakeup_balong_handler(u32 gpio_no)
{
	u8 flag = VIA_WAKEUP_BALONG;

	if(uart_init_flag == LPm3_UART5_IQR_ENABLE)
	{
		bsp_icc_send((u32)ICC_CPU_MODEM,(ICC_CHN_MCORE_CCORE << 16)|MCORE_CCORE_FUNC_UART,&flag,sizeof(flag));
	}
}

/*****************************************************************************
 函 数 名  : recv_modem_rsg_by_icc
 功能描述  : modem发送icc，ap侧控制gpio唤醒对方modem
 输入参数  : 
 输出参数  : 无
 返 回 值  : void
*****************************************************************************/
int recv_modem_rsg_by_icc(u32 chan_id, u32 len, void* context)
{	
	s32 read_size = 0;
	u8 flag = 0;
	struct dual_modem_icc_msg_str dm_msg= {0};
	context = context;		//防止编译告警	
	
 	read_size = bsp_icc_read((ICC_CHN_MCORE_CCORE << 16)|MCORE_CCORE_FUNC_UART, (u8 *)&dm_msg, len); 
	if ((read_size > (s32)len) && (read_size <= 0))
    {
		return -1;
    }
	if(dm_msg.dual_modem_init_flag == UART_INIT_ENABLE)
	{
		if(dm_msg.icc_msgs_flag == LPm3_UART5_IQR_ENABLE)
		{
#ifdef UART5_IRQ_NOTIFY_MODEM
		uart5_init();
#endif
		}
		uart_init_flag = LPm3_UART5_IQR_ENABLE;
		flag = UART_INIT_ENABLE;
		bsp_icc_send((u32)ICC_CPU_MODEM,(ICC_CHN_MCORE_CCORE << 16)|MCORE_CCORE_FUNC_UART,&flag,sizeof(flag));
	}
	return 0;
}

/*****************************************************************************
 函 数 名  : wakeup_modem_init
 功能描述  : ap侧gpio初始化
 输入参数  : 
 输出参数  : 
 返 回 值  : 0:成功，-1:失败
*****************************************************************************/
int wakeup_modem_init(void)
{	
	unsigned int  retVal = 0;
	int ret = 0;
	
	/* first init should read nv */
	if(get_modem_init_flag() != MODEM_ALREADY_INIT_MAGIC)
	{
		memset((void*)&dual_modem_lpm3_nv,0,sizeof(DRV_DUAL_MODEM_STR));

		retVal =bsp_nvm_read(NV_ID_DRV_DUAL_MODEM,(u8 *)&dual_modem_lpm3_nv,sizeof(DRV_DUAL_MODEM_STR));
		if(retVal != OK)
		{
			dm_print_info("dm ERR:%d\n",NV_ID_DRV_DUAL_MODEM);
			return -1;
		}	
	}
	if(UART_SWITCH_ENABLE == dual_modem_lpm3_nv.enUartEnableCfg)
	{
		if(0 !=bsp_icc_event_register((ICC_CHN_MCORE_CCORE << 16)|MCORE_CCORE_FUNC_UART,recv_modem_rsg_by_icc , NULL, NULL, NULL))
	    {
	        printk("reg icc cb err\n");
			return -1;
	    }

		gpio_set_direction(VIA_WAKEUP_BALONG_PIN,0);
		ret = gpio_irq_request(VIA_WAKEUP_BALONG_PIN,via_wakeup_balong_handler,IRQ_TYPE_EDGE_FALLING|IRQF_AWAKE);
		if(ret < 0)
		{
			printk("g-irq err\n");
			return -1;
		}
	}
	return 0;
}

