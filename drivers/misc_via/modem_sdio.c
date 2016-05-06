/*
  stub of modem_sdio.c
 */

#include "modem_sdio.h"


unsigned long SDIO_DL_RegDataCallback(unsigned char ucPDNId, RCV_C_DL_DATA_FUNC pFunc)
{
    printk("SDIO_DL_RegDataCallback stub\n");
	
	return 1;
}


unsigned long SDIO_UL_SendPacket(struct sk_buff *pstData, unsigned char ucPDNId)
{
	printk("SDIO_UL_SendPacket stub\n");
	
	return 1;
}

