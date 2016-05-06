/*
  stub of modem_sdio.h
 */
#ifndef MODEM_SDIO_H
#define MODEM_SDIO_H

#include <linux/skbuff.h>

typedef unsigned long (*RCV_C_DL_DATA_FUNC)(unsigned char ucPDNId, struct sk_buff *pstData);

#endif
