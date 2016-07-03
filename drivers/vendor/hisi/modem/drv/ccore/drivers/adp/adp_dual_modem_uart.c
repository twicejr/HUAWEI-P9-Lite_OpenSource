

#include "mdrv_dual_modem.h"
#include "osl_types.h"

#ifndef CONFIG_BALONG_MDM_UART   /* ´ò×® */

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

