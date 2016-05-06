#include <of.h>
#include "securec.h"
#include "osl_types.h"
#include "osl_sem.h"
#include "osl_thread.h"
#include "bsp_dump.h"
#include "bsp_hardtimer.h"
#include "mdrv_dual_modem.h"
#include "dual_modem.h"

extern int uart_core_send(UART_CONSUMER_ID uPortNo, unsigned char * pDataBuffer, unsigned int uslength);
extern int uart_core_recv_handler_register(UART_CONSUMER_ID uPortNo, pUARTRecv pCallback);

void dual_modem_test_001(u32 lenth)
{
    u32 i = 0;
    unsigned char dual_modem_buf[1024];
	
	for(i = 0; i < lenth; i++)
    {
        dual_modem_buf[i]=i;
    }

    uart_core_send(CBP_UART_PORT_ID,dual_modem_buf,lenth);  /* [false alarm]:Îó±¨ */
}

int dual_modem_test_002(UART_CONSUMER_ID uPortNo,unsigned char *pData, unsigned int ulLength)
{
	uart_core_send(CBP_UART_PORT_ID,pData,ulLength);
	return 0;
}

void dual_modem_test_003(void)
{
 	
	(int)uart_core_recv_handler_register(CBP_UART_PORT_ID,dual_modem_test_002);
}

void dual_modem_test_004(void)
{
	u8 hi_via[14] ={0x7e,0x00,0x00,0x06,0x00,0x00,0x00,0xee,0x00,0x00,0x00,0x01,0x64,0x7e};
	uart_core_send(CBP_UART_PORT_ID,hi_via,14);
}

void dual_modem_test_005(void)
{
	u32 ret = ERROR;
	u8 hi_char[11] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x32,0xdf,0x7e};
	
	ret = uart_core_send(CBP_UART_PORT_ID,hi_char,11);
	if(ret == OK)
		dm_print_err("SEND SUCCESS!\n");
}

void dual_modem_test_006(void)
{
	u8 hi_via[64] ={0x7e,0x00,0x00,0x43,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x03,
					0x00,0x01,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00};
		u32 ret = ERROR;
		
		ret = uart_core_send(CBP_UART_PORT_ID,hi_via,64);
	if(ret == OK)
		dm_print_err("SEND SUCCESS!\n");
}

void dual_modem_test_007(void)
{
   system_error(0, 0, 0, NULL, 0);
}

