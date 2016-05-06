/*
 * Copyright (C) 2010 Trusted Logic S.A.
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#define MAX_BUFFER_SIZE	512
#define PN547_MAGIC 0xE9
#define PN547_SET_PWR	_IOW(PN547_MAGIC, 0x01, unsigned int)
#define VEN_VDD_VOLTAGE 3150000
#define DEFAULT_NFC_CLK_RATE	(192 * 100000L)
//#ifdef CONFIG_V8R2_NFC
//#define NFC_CLK_PIN     "CK19M2_NFC"
//#else
#define NFC_CLK_PIN     "clk_out0"
//#endif
#define NFC_TRY_NUM 3
#define UICC_SUPPORT_CARD_EMULATION (1<<0)
#define eSE_SUPPORT_CARD_EMULATION (1<<1)
#define CARD_UNKNOWN	0
#define CARD1_SELECT	 1
#define CARD2_SELECT  2
#define MAX_ATTRIBUTE_BUFFER_SIZE 128