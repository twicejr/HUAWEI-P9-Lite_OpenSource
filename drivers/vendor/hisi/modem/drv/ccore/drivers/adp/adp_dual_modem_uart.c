/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  adp_uart.c
*
*   作    者 :  z00265007
*
*   描    述 :  v7r2为保持与v7r1接口的一致的适配文件
*
*   修改记录 :  2013年2月1日  v1.00  y00184236  创建
*************************************************************************/

#include "mdrv_dual_modem.h"
#include "osl_types.h"

#ifndef CONFIG_BALONG_MDM_UART   /* 打桩 */

int uart_core_recv_handler_register(UART_CONSUMER_ID uPortNo, pUARTRecv pCallback)
{
	return 0;

}
int uart_core_send(UART_CONSUMER_ID uPortNo, unsigned char * pDataBuffer, unsigned int uslength)
{
	return 0;

}
int bsp_dual_modem_init(void)
{
	return 0;
}
int bsp_dual_modem_drv_init(void)
{
	return 0;
}

#endif

