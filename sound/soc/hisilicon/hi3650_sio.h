/*
 * hi6401.h -- HI6401 ALSA SoC HI6401 codec driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _HI3630_SIO_H
#define _HI3630_SIO_H

#include <linux/pinctrl/consumer.h>
#include <linux/regulator/consumer.h>

/* 3635 */
/*
#define SIO_AUDIO_ADDR		0xE804E800
#define SIO_VOICE_ADDR		0xE804EC00
#define SIO_BT_ADDR			0xE804F000
#define SIO_MODEM_ADDR		0xE804F400
*/

#define SIO_AUDIO_ADDR		0xE804F000
#define SIO_VOICE_ADDR		0xE804F400
#define SIO_BT_ADDR			0xE804F800
#define SIO_MODEM_ADDR		0xE804FC00

#define SIO_AUDIO_ID		0
#define SIO_VOICE_ID		1
#define SIO_BT_ID			2
#define SIO_MODEM_ID		3

#define SIO_CFG			0x40

#define SIO_CFG_PCM_MODE		1
#define SIO_CFG_SIO_MODE		0

#define SIO_INT_CLR		0x48

#define SIO_CTL_SET		0x5C
#define SIO_CTL_CLR		0x60

#define SIO_RX_ENABLE			(1 << 13)
#define SIO_TX_ENABLE			(1 << 12)
#define SIO_RX_FIFO_DISABLE		(1 << 11)
#define SIO_TX_FIFO_DISABLE		(1 << 10)
#define SIO_RX_DATA_MERGE		(1 << 9)
#define SIO_TX_DATA_MERGE		(1 << 8)
#define SIO_RX_FIFO_THRESHOLD		(0x5 << 4)/* burst 4 */
#define SIO_TX_FIFO_THRESHOLD		(0xB << 0)/* burst 4 */
#define SIO_RX_FIFO_THRESHOLD_CLR	(0xF << 4)
#define SIO_TX_FIFO_THRESHOLD_CLR	(0xF << 0)

#define SIO_RX_FIFO_DEPTH	0x68
#define SIO_TX_FIFO_DEPTH	0x6C

#define SIO_DATA_WIDTH		0x78

#define SIO_DATA_WIDTH_RX		3
#define SIO_DATA_WIDTH_TX		0

#define SIO_I2S_START_POS	0x7C

#define SIO_I2S_POS_MERGE	0x88

#define SIO_INT_MASK		0x8C

#define SIO_I2S_RX_CHN		0xA0
#define SIO_I2S_TX_CHN		0xC0


struct hi3630_sio_platform_data {
	struct device	*dev;
	void		__iomem *reg_base_addr;
	struct resource	*res;
	struct pinctrl	*pctrl;
	struct regulator *regu_asp; 
	struct mutex	mutex;
	unsigned int	id;
	bool		is_master;
	unsigned int	pb_active;
	unsigned int	active_count;
};

#endif
