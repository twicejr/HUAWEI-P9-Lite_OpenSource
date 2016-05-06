/*
 * Header file for device driver BOOST5V CONTROL DRIVER
 *
 * Copyright (c) 2013 Linaro Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef	__HISI_BOOST5V_CONTROL_H
#define	__HISI_BOOST5V_CONTROL_H

#define HI6421_BOOST5V_CONTROL_ADDR		0xB0
#define HI6421_BOOST5V_STATE_ENABLE		0x01
#define HI6421_BOOST5V_STATE_DISABLE		0x00
#define HI6421_BOOST_CTRL2					0xB1
#define HI6421_BOOST_CTRL2_VALUE1			0x1E
#define HI6421_BOOST_CTRL2_VALUE2			0x9E
#define HI6421_BOOST_CTRL3					0xB2
#define HI6421_BOOST_CTRL3_VALUE1			0x78
#define HI6421_BOOST_CTRL3_VALUE2			0x78
#define HI6421_BOOST_CTRL4					0xB3
#define HI6421_BOOST_CTRL4_VALUE1			0x9E
#define HI6421_BOOST_CTRL4_VALUE2			0x9E
#define HI6421_BOOST_CTRL5					0xB4
#define HI6421_BOOST_CTRL5_VALUE1			0x4C
#define HI6421_BOOST_CTRL5_VALUE2			0x4C
#define HI6421_BOOST_CTRL6					0xB5
#define HI6421_BOOST_CTRL6_VALUE1			0x7F
#define HI6421_BOOST_CTRL6_VALUE2			0x7F
#define HI6421_BOOST_CTRL7					0xB6
#define HI6421_BOOST_CTRL7_VALUE1			0x10
#define HI6421_BOOST_CTRL7_VALUE2			0x10
#define HI6421_BOOST_CTRL8					0xB7
#define HI6421_BOOST_CTRL8_VALUE1			0xDE
#define HI6421_BOOST_CTRL8_VALUE2			0xDE
#define HI6421_BOOST5V_VOLTAGE_ADDR		0xB8
#define BOOST5V_VALUE_5_V					0x15
#define BOOST5V_VALUE_5_3_V				0x05
#define HI6421_BOOST_CTRL10				0xB9
#define HI6421_BOOST_CTRL10_VALUE1		0x92
#define HI6421_BOOST_CTRL10_VALUE2		0x92
#define HI6421_BOOST_CTRL11				0xBA
#define HI6421_BOOST_CTRL11_VALUE1		0x03
#define HI6421_BOOST_CTRL11_VALUE2		0x03
#define HI6421_BOOST_CTRL14				0xBD
#define HI6421_BOOST_CTRL14_VALUE1		0x40
#define HI6421_BOOST_CTRL14_VALUE2		0x40

extern void boost5v_flash_led_enable(bool enable);
extern void boost5v_headphone_enable(bool enable);
extern void boost5v_classd_enable(bool enable);
extern void boost5v_hdmi_enable(bool enable);
extern void boost5v_denoise_headphone_enable(bool enable);

#endif		/* __HISI_BOOST5V_CONTROL_H */
