/*
 *	soundtrigger_dma_drv is a kernel driver which is used to manager dma
 *	Copyright (C) 2015	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _AUDIO_AUTO_SOUNDTRIGGER_DMA_DRV_H
#define _AUDIO_AUTO_SOUNDTRIGGER_DMA_DRV_H

/*slimbus register addr*/
#define HI3xxx_SLIMBUS_BASE_REG 							(0xE8050000)
#define HI3xxx_SLIMBUS_REG_SIZE 							(100)
#define HI3xxx_SLIMBUS_PORT0_REG_0							(0x100)
#define HI3xxx_SLIMBUS_PORT0_REG_1							(0x104)
#define HI3xxx_SLIMBUS_PORT1_REG_0							(0x108)
#define HI3xxx_SLIMBUS_PORT1_REG_1							(0x10C)
#define HI3xxx_SLIMBUS_PORT2_REG_0							(0x110)
#define HI3xxx_SLIMBUS_PORT2_REG_1							(0x114)
#define HI3xxx_SLIMBUS_PORT3_REG_0							(0x118)
#define HI3xxx_SLIMBUS_PORT3_REG_1							(0x11C)
#define HI3xxx_SLIMBUS_PORT4_REG_0							(0x120)
#define HI3xxx_SLIMBUS_PORT4_REG_1							(0x124)
#define HI3xxx_SLIMBUS_PORT5_REG_0							(0x128)
#define HI3xxx_SLIMBUS_PORT5_REG_1							(0x12C)
#define HI3xxx_SLIMBUS_PORT6_REG_0							(0x130)
#define HI3xxx_SLIMBUS_PORT6_REG_1							(0x134)
#define HI3xxx_SLIMBUS_PORT7_REG_0							(0x138)
#define HI3xxx_SLIMBUS_PORT7_REG_1							(0x13C)
#define HI3xxx_SLIMBUS_PORT8_REG_0							(0x140)
#define HI3xxx_SLIMBUS_PORT8_REG_1							(0x144)
#define HI3xxx_SLIMBUS_PORT9_REG_0							(0x148)
#define HI3xxx_SLIMBUS_PORT9_REG_1							(0x14C)
#define HI3xxx_SLIMBUS_PORT10_REG_0 						(0x150)
#define HI3xxx_SLIMBUS_PORT10_REG_1 						(0x154)
#define HI3xxx_SLIMBUS_PORT11_REG_0 						(0x158)
#define HI3xxx_SLIMBUS_PORT11_REG_1 						(0x15C)


#define HI3xxx_DMAC_INT_STAT_0_REG					 (0x0)
#define HI3xxx_DMAC_INT_STAT_1_REG					 (0x40)
#define HI3xxx_DMAC_INT_TC1_0_REG					 (0x4)
#define HI3xxx_DMAC_INT_TC1_1_REG					 (0x44)
#define HI3xxx_DMAC_INT_TC2_0_REG					 (0x8)
#define HI3xxx_DMAC_INT_TC2_1_REG					 (0x48)
#define HI3xxx_DMAC_INT_ERR1_0_REG					 (0xC)
#define HI3xxx_DMAC_INT_ERR1_1_REG					 (0x4C)
#define HI3xxx_DMAC_INT_ERR2_0_REG					 (0x10)
#define HI3xxx_DMAC_INT_ERR2_1_REG					 (0x50)
#define HI3xxx_DMAC_INT_ERR3_0_REG					 (0x14)
#define HI3xxx_DMAC_INT_ERR3_1_REG					 (0x54)
#define HI3xxx_DMAC_INT_TC1_MASK_0_REG				 (0x18)
#define HI3xxx_DMAC_INT_TC1_MASK_1_REG				 (0x58)
#define HI3xxx_DMAC_INT_TC2_MASK_0_REG				 (0x1C)
#define HI3xxx_DMAC_INT_TC2_MASK_1_REG				 (0x5C)
#define HI3xxx_DMAC_INT_ERR1_MASK_0_REG 			 (0x20)
#define HI3xxx_DMAC_INT_ERR1_MASK_1_REG 			 (0x60)
#define HI3xxx_DMAC_INT_ERR2_MASK_0_REG 			 (0x24)
#define HI3xxx_DMAC_INT_ERR2_MASK_1_REG 			 (0x64)
#define HI3xxx_DMAC_INT_ERR3_MASK_0_REG 			 (0x28)
#define HI3xxx_DMAC_INT_ERR3_MASK_1_REG 			 (0x68)
#define HI3xxx_DMAC_INT_TC1_RAW_REG 				 (0x600)
#define HI3xxx_DMAC_INT_TC2_RAW_REG 				 (0x608)
#define HI3xxx_DMAC_INT_ERR1_RAW_REG				 (0x610)
#define HI3xxx_DMAC_INT_ERR2_RAW_REG				 (0x618)
#define HI3xxx_DMAC_INT_ERR3_RAW_REG				 (0x620)
#define HI3xxx_DMAC_SREQ_REG						 (0x660)
#define HI3xxx_DMAC_LSREQ_REG						 (0x664)
#define HI3xxx_DMAC_BREQ_REG						 (0x668)
#define HI3xxx_DMAC_LBREQ_REG						 (0x66C)
#define HI3xxx_DMAC_FREQ_REG						 (0x670)
#define HI3xxx_DMAC_LFREQ_REG						 (0x674)
#define HI3xxx_DMAC_CH_PRI_REG						 (0x688)
#define HI3xxx_DMAC_CH_STAT_REG 					 (0x690)
#define HI3xxx_DMAC_SEC_CTRL_REG					 (0x694)
#define HI3xxx_DMAC_DMA_CTRL_REG					 (0x698)
#define HI3xxx_DMAC_CX_CURR_CNT1_0_REG				 (0x700)
#define HI3xxx_DMAC_CX_CURR_CNT1_1_REG				 (0x710)
#define HI3xxx_DMAC_CX_CURR_CNT1_2_REG				 (0x720)
#define HI3xxx_DMAC_CX_CURR_CNT1_3_REG				 (0x730)
#define HI3xxx_DMAC_CX_CURR_CNT1_4_REG				 (0x740)
#define HI3xxx_DMAC_CX_CURR_CNT1_5_REG				 (0x750)
#define HI3xxx_DMAC_CX_CURR_CNT1_6_REG				 (0x760)
#define HI3xxx_DMAC_CX_CURR_CNT1_7_REG				 (0x770)
#define HI3xxx_DMAC_CX_CURR_CNT1_8_REG				 (0x780)
#define HI3xxx_DMAC_CX_CURR_CNT1_9_REG				 (0x790)
#define HI3xxx_DMAC_CX_CURR_CNT1_10_REG 			 (0x7A0)
#define HI3xxx_DMAC_CX_CURR_CNT1_11_REG 			 (0x7B0)
#define HI3xxx_DMAC_CX_CURR_CNT0_0_REG				 (0x704)
#define HI3xxx_DMAC_CX_CURR_CNT0_1_REG				 (0x714)
#define HI3xxx_DMAC_CX_CURR_CNT0_2_REG				 (0x724)
#define HI3xxx_DMAC_CX_CURR_CNT0_3_REG				 (0x734)
#define HI3xxx_DMAC_CX_CURR_CNT0_4_REG				 (0x744)
#define HI3xxx_DMAC_CX_CURR_CNT0_5_REG				 (0x754)
#define HI3xxx_DMAC_CX_CURR_CNT0_6_REG				 (0x764)
#define HI3xxx_DMAC_CX_CURR_CNT0_7_REG				 (0x774)
#define HI3xxx_DMAC_CX_CURR_CNT0_8_REG				 (0x784)
#define HI3xxx_DMAC_CX_CURR_CNT0_9_REG				 (0x794)
#define HI3xxx_DMAC_CX_CURR_CNT0_10_REG 			 (0x7A4)
#define HI3xxx_DMAC_CX_CURR_CNT0_11_REG 			 (0x7B4)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_0_REG			 (0x708)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_1_REG			 (0x718)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_2_REG			 (0x728)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_3_REG			 (0x738)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_4_REG			 (0x748)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_5_REG			 (0x758)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_6_REG			 (0x768)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_7_REG			 (0x778)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_8_REG			 (0x788)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_9_REG			 (0x798)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_10_REG 		 (0x7A8)
#define HI3xxx_DMAC_CX_CURR_SRC_ADDR_11_REG 		 (0x7B8)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_0_REG			 (0x70C)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_1_REG			 (0x71C)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_2_REG			 (0x72C)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_3_REG			 (0x73C)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_4_REG			 (0x74C)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_5_REG			 (0x75C)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_6_REG			 (0x76C)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_7_REG			 (0x77C)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_8_REG			 (0x78C)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_9_REG			 (0x79C)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_10_REG 		 (0x7AC)
#define HI3xxx_DMAC_CX_CURR_DES_ADDR_11_REG 		 (0x7BC)
#define HI3xxx_DMAC_CX_LLI_0_REG					 (0x800)
#define HI3xxx_DMAC_CX_LLI_1_REG					 (0x840)
#define HI3xxx_DMAC_CX_LLI_2_REG					 (0x880)
#define HI3xxx_DMAC_CX_LLI_3_REG					 (0x8C0)
#define HI3xxx_DMAC_CX_LLI_4_REG					 (0x900)
#define HI3xxx_DMAC_CX_LLI_5_REG					 (0x940)
#define HI3xxx_DMAC_CX_LLI_6_REG					 (0x980)
#define HI3xxx_DMAC_CX_LLI_7_REG					 (0x9C0)
#define HI3xxx_DMAC_CX_LLI_8_REG					 (0xA00)
#define HI3xxx_DMAC_CX_LLI_9_REG					 (0xA40)
#define HI3xxx_DMAC_CX_LLI_10_REG					 (0xA80)
#define HI3xxx_DMAC_CX_LLI_11_REG					 (0xAC0)
#define HI3xxx_DMAC_CX_BINDX_0_REG					 (0x804)
#define HI3xxx_DMAC_CX_BINDX_1_REG					 (0x844)
#define HI3xxx_DMAC_CX_BINDX_2_REG					 (0x884)
#define HI3xxx_DMAC_CX_BINDX_3_REG					 (0x8C4)
#define HI3xxx_DMAC_CX_BINDX_4_REG					 (0x904)
#define HI3xxx_DMAC_CX_BINDX_5_REG					 (0x944)
#define HI3xxx_DMAC_CX_BINDX_6_REG					 (0x984)
#define HI3xxx_DMAC_CX_BINDX_7_REG					 (0x9C4)
#define HI3xxx_DMAC_CX_BINDX_8_REG					 (0xA04)
#define HI3xxx_DMAC_CX_BINDX_9_REG					 (0xA44)
#define HI3xxx_DMAC_CX_BINDX_10_REG 				 (0xA84)
#define HI3xxx_DMAC_CX_BINDX_11_REG 				 (0xAC4)
#define HI3xxx_DMAC_CX_CINDX_0_REG					 (0x808)
#define HI3xxx_DMAC_CX_CINDX_1_REG					 (0x848)
#define HI3xxx_DMAC_CX_CINDX_2_REG					 (0x888)
#define HI3xxx_DMAC_CX_CINDX_3_REG					 (0x8C8)
#define HI3xxx_DMAC_CX_CINDX_4_REG					 (0x908)
#define HI3xxx_DMAC_CX_CINDX_5_REG					 (0x948)
#define HI3xxx_DMAC_CX_CINDX_6_REG					 (0x988)
#define HI3xxx_DMAC_CX_CINDX_7_REG					 (0x9C8)
#define HI3xxx_DMAC_CX_CINDX_8_REG					 (0xA08)
#define HI3xxx_DMAC_CX_CINDX_9_REG					 (0xA48)
#define HI3xxx_DMAC_CX_CINDX_10_REG 				 (0xA88)
#define HI3xxx_DMAC_CX_CINDX_11_REG 				 (0xAC8)
#define HI3xxx_DMAC_CX_CNT1_0_REG					 (0x80C)
#define HI3xxx_DMAC_CX_CNT1_1_REG					 (0x84C)
#define HI3xxx_DMAC_CX_CNT1_2_REG					 (0x88C)
#define HI3xxx_DMAC_CX_CNT1_3_REG					 (0x8CC)
#define HI3xxx_DMAC_CX_CNT1_4_REG					 (0x90C)
#define HI3xxx_DMAC_CX_CNT1_5_REG					 (0x94C)
#define HI3xxx_DMAC_CX_CNT1_6_REG					 (0x98C)
#define HI3xxx_DMAC_CX_CNT1_7_REG					 (0x9CC)
#define HI3xxx_DMAC_CX_CNT1_8_REG					 (0xA0C)
#define HI3xxx_DMAC_CX_CNT1_9_REG					 (0xA4C)
#define HI3xxx_DMAC_CX_CNT1_10_REG					 (0xA8C)
#define HI3xxx_DMAC_CX_CNT1_11_REG					 (0xACC)
#define HI3xxx_DMAC_CX_CNT0_0_REG					 (0x810)
#define HI3xxx_DMAC_CX_CNT0_1_REG					 (0x850)
#define HI3xxx_DMAC_CX_CNT0_2_REG					 (0x890)
#define HI3xxx_DMAC_CX_CNT0_3_REG					 (0x8D0)
#define HI3xxx_DMAC_CX_CNT0_4_REG					 (0x910)
#define HI3xxx_DMAC_CX_CNT0_5_REG					 (0x950)
#define HI3xxx_DMAC_CX_CNT0_6_REG					 (0x990)
#define HI3xxx_DMAC_CX_CNT0_7_REG					 (0x9D0)
#define HI3xxx_DMAC_CX_CNT0_8_REG					 (0xA10)
#define HI3xxx_DMAC_CX_CNT0_9_REG					 (0xA50)
#define HI3xxx_DMAC_CX_CNT0_10_REG					 (0xA90)
#define HI3xxx_DMAC_CX_CNT0_11_REG					 (0xAD0)
#define HI3xxx_DMAC_CX_SRC_ADDR_0_REG				 (0x814)
#define HI3xxx_DMAC_CX_SRC_ADDR_1_REG				 (0x854)
#define HI3xxx_DMAC_CX_SRC_ADDR_2_REG				 (0x894)
#define HI3xxx_DMAC_CX_SRC_ADDR_3_REG				 (0x8D4)
#define HI3xxx_DMAC_CX_SRC_ADDR_4_REG				 (0x914)
#define HI3xxx_DMAC_CX_SRC_ADDR_5_REG				 (0x954)
#define HI3xxx_DMAC_CX_SRC_ADDR_6_REG				 (0x994)
#define HI3xxx_DMAC_CX_SRC_ADDR_7_REG				 (0x9D4)
#define HI3xxx_DMAC_CX_SRC_ADDR_8_REG				 (0xA14)
#define HI3xxx_DMAC_CX_SRC_ADDR_9_REG				 (0xA54)
#define HI3xxx_DMAC_CX_SRC_ADDR_10_REG				 (0xA94)
#define HI3xxx_DMAC_CX_SRC_ADDR_11_REG				 (0xAD4)
#define HI3xxx_DMAC_CX_DES_ADDR_0_REG				 (0x818)
#define HI3xxx_DMAC_CX_DES_ADDR_1_REG				 (0x858)
#define HI3xxx_DMAC_CX_DES_ADDR_2_REG				 (0x898)
#define HI3xxx_DMAC_CX_DES_ADDR_3_REG				 (0x8D8)
#define HI3xxx_DMAC_CX_DES_ADDR_4_REG				 (0x918)
#define HI3xxx_DMAC_CX_DES_ADDR_5_REG				 (0x958)
#define HI3xxx_DMAC_CX_DES_ADDR_6_REG				 (0x998)
#define HI3xxx_DMAC_CX_DES_ADDR_7_REG				 (0x9D8)
#define HI3xxx_DMAC_CX_DES_ADDR_8_REG				 (0xA18)
#define HI3xxx_DMAC_CX_DES_ADDR_9_REG				 (0xA58)
#define HI3xxx_DMAC_CX_DES_ADDR_10_REG				 (0xA98)
#define HI3xxx_DMAC_CX_DES_ADDR_11_REG				 (0xAD8)
#define HI3xxx_DMAC_CX_CONFIG_0_REG 				 (0x81C)
#define HI3xxx_DMAC_CX_CONFIG_1_REG 				 (0x85C)
#define HI3xxx_DMAC_CX_CONFIG_2_REG 				 (0x89C)
#define HI3xxx_DMAC_CX_CONFIG_3_REG 				 (0x8DC)
#define HI3xxx_DMAC_CX_CONFIG_4_REG 				 (0x91C)
#define HI3xxx_DMAC_CX_CONFIG_5_REG 				 (0x95C)
#define HI3xxx_DMAC_CX_CONFIG_6_REG 				 (0x99C)
#define HI3xxx_DMAC_CX_CONFIG_7_REG 				 (0x9DC)
#define HI3xxx_DMAC_CX_CONFIG_8_REG 				 (0xA1C)
#define HI3xxx_DMAC_CX_CONFIG_9_REG 				 (0xA5C)
#define HI3xxx_DMAC_CX_CONFIG_10_REG				 (0xA9C)
#define HI3xxx_DMAC_CX_CONFIG_11_REG				 (0xADC)
#define HI3xxx_DMAC_CX_AXI_CONF_0_REG				 (0x820)
#define HI3xxx_DMAC_CX_AXI_CONF_1_REG				 (0x860)
#define HI3xxx_DMAC_CX_AXI_CONF_2_REG				 (0x8A0)
#define HI3xxx_DMAC_CX_AXI_CONF_3_REG				 (0x8E0)
#define HI3xxx_DMAC_CX_AXI_CONF_4_REG				 (0x920)
#define HI3xxx_DMAC_CX_AXI_CONF_5_REG				 (0x960)
#define HI3xxx_DMAC_CX_AXI_CONF_6_REG				 (0x9A0)
#define HI3xxx_DMAC_CX_AXI_CONF_7_REG				 (0x9E0)
#define HI3xxx_DMAC_CX_AXI_CONF_8_REG				 (0xA20)
#define HI3xxx_DMAC_CX_AXI_CONF_9_REG				 (0xA60)
#define HI3xxx_DMAC_CX_AXI_CONF_10_REG				 (0xAA0)
#define HI3xxx_DMAC_CX_AXI_CONF_11_REG				 (0xAE0)

#define DRV_DMA_LLI_LINK(uwAddr)		(((uwAddr) & 0xffffffe0UL) | (0x2UL))

#define CH_0_UNMASK_BIT 			0x0
#define DMA_CH_UNMASK				0x198
#define DMA_FAST_LEFT_CH_UNMASK 	0x80
#define DMA_FAST_RIGHT_CH_UNMASK	0x100
#define DMA_NORMAL_LEFT_CH_UNMASK	0x8
#define DMA_NORMAL_RIGHT_CH_UNMASK	0x10

#define DMA_CH_INT_CLR 0x1
#define DMA_ENABLE_BIT 0

#define PCM_SWAP_BUFFER_NUM 	(6)
#define DMA_LLI_NUM 			(PCM_SWAP_BUFFER_NUM)

#define FAST_CHANNEL_TIMEOUT_READ_COUNT 	200
#define NORMAL_CHANNEL_TIMEOUT_READ_COUNT	200
#define NORMAL_CHANNEL_TIMEOUT_TRAN_COUNT	1000



typedef int ST_ERROR_NUM_INT32;
typedef int ST_IRQ_STATE_INT32;

enum fast_tran_state {
	FAST_TRAN_NOT_COMPLETE = 0,
	FAST_TRAN_COMPLETE,
};

enum read_state {
	READ_NOT_COMPLETE = 0,
	READ_COMPLETE,
};

enum find_state {
	FRAME_NOT_FIND = 0,
	FRAME_FIND,
};

enum dma_drv_state {
	DMA_DRV_NO_INIT = 0,
	DMA_DRV_INIT,
};

enum soundtrigger_irq_state {
	IRQ_ERR = 0,
	IRQ_FINISH,
	IRQ_FAST_LEFT_CHAN,
	IRQ_FAST_RIGHT_CHAN,
	IRQ_NORMAL_LEFT_CHAN,
	IRQ_NORMAL_RIGHT_CHAN,
};

enum {
	SOUNDTRIGGER_CMD_DMA_OPEN = 1,
	SOUNDTRIGGER_CMD_DMA_CLOSE,
	SOUNDTRIGGER_CMD_DMA_READY,
};

enum {
	SOUNDTRIGGER_PCM_FAST = 0,
	SOUNDTRIGGER_PCM_NORMAL,
	SOUNDTRIGGER_PCM_CHAN_NUM,
};

struct soundtrigger_io_sync_param {
	unsigned int para_in_l;
	unsigned int para_in_h;
	unsigned int para_size_in;

	unsigned int para_out_l;
	unsigned int para_out_h;
	unsigned int para_size_out;
};

struct krn_param_io_buf {
	unsigned char *buf_in;
	unsigned int buf_size_in;
	/*XXX: variables below is for sync cmd only*/
	unsigned char *buf_out;
	unsigned int buf_size_out;
};

struct st_fast_status{
	int fm_status;
	int fast_status;
};

#define INT_TO_ADDR(low,high) (void*) (unsigned long)((unsigned long long)(low) | ((unsigned long long)(high)<<32))

#define HWLOCK_WAIT_TIME	50

#endif /* end of _AUDIO_AUTO_TEST_ASP_CFG_H */

