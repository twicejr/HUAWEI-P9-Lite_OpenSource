/*
 *  Hisilicon K3 soc camera ISP driver header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __TPS61310_H__
#define __TPS61310_H__


#define FLASH_REGISTER0			0x00
#define FLASH_REGISTER1			0x01
#define FLASH_REGISTER2			0x02
#define FLASH_REGISTER3			0x03
#define FLASH_REGISTER4			0x04
#define FLASH_REGISTER5			0x05
#define FLASH_REGISTER6			0x06
#define FLASH_REGISTER7			0x07

/* FLASH_REGISTER0 */
#define FLASH_RESET_BIT			(0x1<<7)
#define FLASH_RESET			0x80

#define FLASH_DCLC13_0			0x00
#define FLASH_DCLC13_25			0x08
#define FLASH_DCLC13_50			0x10
#define FLASH_DCLC13_75			0x18
#define FLASH_DCLC13_100		0x20
#define FLASH_DCLC13_125		0x28
#define FLASH_DCLC13_150		0x30
#define FLASH_DCLC13_175		0x38

#define FLASH_DCLC2_0			0x00
#define FLASH_DCLC2_25			0x01
#define FLASH_DCLC2_50			0x10
#define FLASH_DCLC2_75			0x11
#define FLASH_DCLC2_100			0x100
#define FLASH_DCLC2_125			0x101
#define FLASH_DCLC2_150			0x110
#define FLASH_DCLC2_175			0x111

/* FLASH_REGISTER1 */
#define MODE_CTRL_BIT			(0x3<<6)

#define FLASH_MODE_SHUTDOWN		0x00
#define FLASH_MODE_VIDEO_LIGHT		0x01
#define FLASH_MODE_FLASH		0x10
#define FLASH_MODE_CONSTANT		0x11

/* FLASH_REGISTER2 */
#define FLASH_ENVM			0x20

/* FLASH REGISTER3 */
#define FLASH_STT_BIT			(0x1<<2)
#define FLASH_SFT_BIT			(0x1<<1)

#define	K3_FLASH_I2C_ADDR		0x33

#define K3_FLASH_NAME			"k3_flash_client"

enum {
	LED1 = 0,
	LED2,
	LED3,
};

enum {
	DISABLE = 0,
	ENABLE,
};

enum {
	TRIG_MODE_LEVEL = 0,
	TRIG_MODE_EDGE,
	TRIG_MODE_CMD,
};

struct tps61310_platform_data {
	u32	reset_pin;
	u32	strobe0;
	u32	strobe1;
};



#endif /*__TP61310_H__ */

/********************************* END ***********************************************/

