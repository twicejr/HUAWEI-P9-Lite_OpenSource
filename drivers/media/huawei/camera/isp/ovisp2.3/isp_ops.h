/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _ISP_OPS_H_
#define _ISP_OPS_H_

#include <linux/platform_device.h>
#include <linux/wait.h>
#include <linux/spinlock.h>
#include <linux/ion.h>
#include <linux/hisi/hisi_ion.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/workqueue.h>
#include "hwisp_intf.h"

/*************************** isp register macro definition *****************************/
#define REG_ISP_TOP4				(0x65004) /* ISP work mode; Combine Mode (HDR) */
#define REG_ISP_SOFT_STANDBY			(0x60100)
#define REG_ISP_SOFT_RST			(0x60103)
#define DO_SOFT_RST   				(0x1)
#define DO_SOFTWARE_STAND_BY            	(0x1)
#define RELEASE_SOFT_RST   			(0x0)

#define REG_ISP_GPIO_SEL			(0x6302f)
#define REG_ISP_GPIO_CTL_H			(0x63030)
#define REG_ISP_GPIO_CTL_L			(0x63031)
#define REG_GPIO_R_REQ_CTRL_72          	(0x63d72)
#define REG_GPIO_R_REQ_CTRL_74          	(0x63d74)


#define REG_ISP_CLK_USED_BY_MCU             	(0x63042)
#define REG_ISP_GENERAL_PURPOSE_REGISTER1	(0x63910)
#define REG_ISP_GENERAL_PURPOSE_REGISTER	(0x63917)
#define REG_ISP_GENERAL_PURPOSE_REGISTER2	(0x63912)
#define REG_ISP_GENERAL_PURPOSE_REGISTER3	(0x63913)

//Modified by Lynn@07/04/2013
#define REG_ISP_INT_STAT_1           		(0x63928)
#define REG_ISP_INT_STAT_2           		(0x63929)
#define REG_ISP_INT_STAT_3           		(0x6392a)
#define REG_ISP_INT_STAT_4           		(0x6392b)

#define REG_ISP_INT_EN_1             		(0x63924)
#define REG_ISP_INT_EN_2             		(0x63925)
#define REG_ISP_INT_EN_3             		(0x63926)
#define REG_ISP_INT_EN_4             		(0x63927)

#define MAC1_INT				(1)
#define MAC2_INT				(1 << 1)
#define MAC3_INT				(1 << 2)

#define MAC1_BASE 				(0x63b00)
#define MAC2_BASE 				(0x63e00)
#define MAC3_BASE 				(0x63f00)


#define REG_ISP_MAC1_INT_STAT_H			(MAC1_BASE + 0x32)
#define REG_ISP_MAC1_INT_STAT_S0		(MAC1_BASE + 0x33)
#define REG_ISP_MAC1_INT_STAT_S1		(MAC1_BASE + 0xb5)
#define REG_ISP_MAC1_STREAM_SELECT		(MAC1_BASE + 0xd1)

#define REG_ISP_MAC1_INT_EN_H			(MAC1_BASE + 0x53)
#define REG_ISP_MAC1_INT_EN_L			(MAC1_BASE + 0x54)
#define REG_BASE_MAC1_WRITE_READY_ADDR		(MAC1_BASE + 0x30)
#define REG_BASE_MAC1_READ_READY_ADDR		(MAC1_BASE + 0x57)
#define REG_ISP_MAC1_CUR_STATUE			(MAC1_BASE + 0x31)

#define REG_ISP_MAC2_INT_STAT_H			(MAC2_BASE + 0x32)
#define REG_ISP_MAC2_INT_STAT_S0		(MAC2_BASE + 0x33)
#define REG_ISP_MAC2_INT_STAT_S1		(MAC2_BASE + 0xb5)
#define REG_ISP_MAC2_STREAM_SELECT		(MAC2_BASE + 0xd1)

#define REG_ISP_MAC2_INT_EN_H			(MAC2_BASE + 0x53)
#define REG_ISP_MAC2_INT_EN_L			(MAC2_BASE + 0x54)
#define REG_BASE_MAC2_WRITE_READY_ADDR		(MAC2_BASE + 0x30)
#define REG_BASE_MAC2_READ_READY_ADDR		(MAC2_BASE + 0x57)
#define REG_ISP_MAC2_CUR_STATUE			(MAC2_BASE + 0x31)

#define REG_ISP_MAC3_INT_STAT_H			(MAC3_BASE + 0x32)
#define REG_ISP_MAC3_INT_STAT_S0		(MAC3_BASE + 0x33)
#define REG_ISP_MAC3_INT_STAT_S1		(MAC3_BASE + 0xb5)
#define REG_ISP_MAC3_STREAM_SELECT		(MAC3_BASE + 0xd1)

#define REG_ISP_MAC3_INT_EN_H			(MAC3_BASE + 0x53)
#define REG_ISP_MAC3_INT_EN_L			(MAC3_BASE + 0x54)
#define REG_BASE_MAC3_WRITE_READY_ADDR		(MAC3_BASE + 0x30)
#define REG_BASE_MAC3_READ_READY_ADDR		(MAC3_BASE + 0x57)
#define REG_ISP_MAC3_CUR_STATUE			(MAC3_BASE + 0x31)

#define CMD_FIRMWARE_DOWNLOAD 0xff
#define WAIT_FW_LOAD_TIMEOUT	1000

#define REG_SHIFT_CMD_DONE					(6)
#define ISP_COMMAND_DONE_INT					(1 << REG_SHIFT_CMD_DONE)

#define REG_FW_VISION							(0x3357e)

#define REG_FW_AE_INT_TYPE(pipe)				(0x33596 + FW_REG_OFFSET * (pipe))
#define REG_FW_CMD_DONE_TYPE					(0x33597)
#define COMMAND_FINISHED					(0x63910)
#define COMMAND_RESULT						(0x63911)

#define CMD_WRITEBACK_EXPO_GAIN					(0xf1)
#define CMD_WRITEBACK_EXPO					(0xf2)
#define CMD_WRITEBACK_GAIN					(0xf3)
#define FW_REG_OFFSET						(0x600)
#define FW_STAT_REG_BASE(flow)					((flow) == 0 ? 0x30200 : 0x30030)
#define REG_FW_AECAGC_MANUAL_EXPO(flow)				(0x33030 + FW_REG_OFFSET * (flow))
#define REG_FW_AECAGC_MANUAL_GAIN(flow)				(0x33034 + FW_REG_OFFSET * (flow))
#define HOST_HOLD_FLAG(pipe)					(0x32c61 + 0x10 * (pipe))
#define MCU_HOLD_FLAG(pipe)					(0x32c62 + 0x10 * (pipe))

#define PIPE_REG_OFFSET					(0x3000)
#define MANUAL_AWB_GAIN_B(pipe)			(0x65300 + PIPE_REG_OFFSET * (pipe))
#define MANUAL_AWB_GAIN_GB(pipe)		(0x65302 + PIPE_REG_OFFSET * (pipe))
#define MANUAL_AWB_GAIN_GR(pipe)		(0x65304 + PIPE_REG_OFFSET * (pipe))
#define MANUAL_AWB_GAIN_R(pipe)			(0x65306 + PIPE_REG_OFFSET * (pipe))

#define REG_FW_CURRENT_Y(flow)					(FW_STAT_REG_BASE(flow) + 0x06)
#define REG_FW_WRITEBACK_GAIN(flow)				(FW_STAT_REG_BASE(flow) + 0x1e)
#define REG_FW_WRITEBACK_EXPO(flow)				(FW_STAT_REG_BASE(flow) + 0x20)
#define REG_FW_AECAGC_WRITESENSOR_ENABLE(flow)			(0x33011 + FW_REG_OFFSET * (flow))

#define REG_SHIFT_PIPE0_SOF_IDI		5
#define REG_SHIFT_PIPE0_EOF_IDI		6
#define REG_SHIFT_PIPE1_SOF_IDI		0
#define REG_SHIFT_PIPE1_EOF_IDI		1

/* Irq enable bit. */
#define ISP_PIPE0_SOF_IDI				(1 << REG_SHIFT_PIPE0_SOF_IDI)
#define ISP_PIPE0_EOF_IDI				(1 << REG_SHIFT_PIPE0_EOF_IDI)
#define ISP_PIPE1_SOF_IDI				(1 << REG_SHIFT_PIPE1_SOF_IDI)
#define ISP_PIPE1_EOF_IDI				(1 << REG_SHIFT_PIPE1_EOF_IDI)

#define INT_ISP_MAC1_START0		(1<<0)
#define INT_ISP_MAC1_DONE0			(1<<1)
#define INT_ISP_MAC1_DROP0			(1<<2)
#define INT_ISP_MAC1_OVERFLOW0		(1<<3)

#define INT_ISP_MAC1_START1			(1<<0)
#define INT_ISP_MAC1_DONE1			(1<<1)
#define INT_ISP_MAC1_DROP1			(1<<2)
#define INT_ISP_MAC1_OVERFLOW1		(1<<3)

#define INT_ISP_MAC2_START0			(1<<0)
#define INT_ISP_MAC2_DONE0			(1<<1)
#define INT_ISP_MAC2_DROP0			(1<<2)
#define INT_ISP_MAC2_OVERFLOW0		(1<<3)

#define INT_ISP_MAC2_START1			(1<<0)
#define INT_ISP_MAC2_DONE1			(1<<1)
#define INT_ISP_MAC2_DROP1			(1<<2)
#define INT_ISP_MAC2_OVERFLOW1		(1<<3)

#define INT_ISP_MAC3_START0			(1<<0)
#define INT_ISP_MAC3_DONE0			(1<<1)
#define INT_ISP_MAC3_DROP0			(1<<2)
#define INT_ISP_MAC3_OVERFLOW0		(1<<3)

#define INT_ISP_MAC3_START1			(1<<0)
#define INT_ISP_MAC3_DONE1			(1<<1)
#define INT_ISP_MAC3_DROP1			(1<<2)
#define INT_ISP_MAC3_OVERFLOW1		(1<<3)

#define ISP_MAC_INPUT_ADDR			(COMMAND_SET_BASE + 0xC4)
#define INPUT_TYPE_MEMORY			(4 << 3)
#define INPUT_TYPE_ISP_PROCESS_ENABLE		(1 << 6)

//ZOOMIN RATIO
#define ISP_ZOOMIN_RATIO	        (COMMAND_SET_BASE + 0x84)

#define ISP_INPUT_TYPE				(COMMAND_SET_BASE + 0x0)
#define ISP_INPUT_WIDTH                 	(COMMAND_SET_BASE + 0x2)
#define ISP_INPUT_HEIGHT                	(COMMAND_SET_BASE + 0x4)

/* added for meta data */
#define ROI_ENABLE_OFFSET					(0x78)
#define ROI_MEM_SIZE_OFFSET					(0x48)
#define MAC_WRITE_ADDRESS_OFFSET			(0x70)
#define SHIFT_BIT_0							(1)
#define SHIFT_BIT_1							(1 << 1)
#define SHIFT_BIT_2							(1 << 2)
#define SHIFT_BIT_4							(1 << 4)

#define G_GAIN_BASE							(0x80)

#define VC_IDI_SIZE							(0x63c40)
#define VC_IDI_LINES						(0x63c42)
#define VC_IDI_ENABLE						(0x63c54)
#define VC_IDI_MIPI_INDEX					(0x63c55)
#define VC_IDI_CHANNEL_ID					(0x63c56)

/*************************** isp register macro definition *****************************/

#define FIRMWARE_FILE_PATH		"/system/isp/isp.bin"

#define RESET_DELAY_INTERVAL		4
#define STAND_BY_DELAY_INTERVAL	10

typedef enum {
	UNALLOCATED = -1,

	ISP_PORT_WRITE0 = 0,
	ISP_PORT_WRITE1,
	ISP_PORT_WRITE2,
	ISP_PORT_WRITE3,
	ISP_PORT_WRITE4,
	ISP_PORT_WRITE5,

	ISP_PORT_READ0,
	ISP_PORT_READ1,
	ISP_PORT_READ2,
        
	ISP_PORT_VC0,

	ISP_PORT_MAX,
} isp_port_e;

typedef enum {
	PORT_LEFT = 0,
	PORT_RIGHT,
} port_side_e;

struct irq_reg_t{
	u8  irq_status_1;
	u8  irq_status_2;
	u8  irq_status_3;
	u8  irq_status_4;

	u8  mac1_irq_status_h;
	u8  mac1_irq_status_s0;
	u8  mac1_irq_status_s1;
	u8  mac1_irq_status_ss;

	u8  mac2_irq_status_h;
	u8  mac2_irq_status_s0;
	u8  mac2_irq_status_s1;
	u8  mac2_irq_status_ss;

	u8  mac3_irq_status_h;
	u8  mac3_irq_status_s0;
	u8  mac3_irq_status_s1;
	u8  mac3_irq_status_ss;
	u8 cmd_done_id;
	u8 cmd_result;

	u32 expo;
	u32 gain;
	u16 hts;
	u16 vts;
	/*host ae take effect*/
	int host_ae_applied;

};

struct ovisp32_mac {	
	hwisp_buf_t*  buf[2];
	spinlock_t lock;
};


#define META_DATA_RAW_SIZE	(4096)

typedef struct _isp_hw_data{

	struct semaphore sem_cmd_done;
	spinlock_t irq_status_lock;
	wait_queue_head_t poll_queue_head;
	bool poll_start;

	void __iomem * viraddr;
	phys_addr_t phyaddr;
	u32 mem_size;
	u32 irq_no;

	/* meta data */
	u8 *meta_viraddr;
	dma_addr_t meta_phyaddr;
	bool meta_running;
	u32 meta_attach_port;
	struct timeval meta_attach_timeval;
	u8 meta_data_raw_buf[META_DATA_RAW_SIZE];
	meta_data_t meta_data;

	struct irq_reg_t irq_val;
	bool irq_query_flag;
	struct regulator_bulk_data inter_ldo;
	/* pinctrl */
	struct pinctrl *isp_pinctrl;
	struct pinctrl_state *pinctrl_def;
	struct pinctrl_state *pinctrl_idle;

	struct ion_client *client;
	struct ion_handle *handle;
	struct iommu_map_format format;
	struct ovisp32_mac mac_array[ISP_PORT_MAX];

	u32 frame_index[ISP_PORT_MAX];
	
}isp_hw_data_t;

typedef struct _camera_frame_buf {
	int index;
	u32 phyaddr;
	u32 u_offset;
	u32 v_offset;
	u32 size;
	void *viraddr;
	u32 statphyaddr;
	void *statviraddr;
	u32 type;//raw,yuv etc

	u32 flags;		/* reference to CAMERA_FLAG_XXX */
	struct list_head queue;
	struct timeval timestamp;
} camera_frame_buf;


#define MAX_EG_SEQ_SIZE 5
struct expo_gain_seq {
	u32 expo[MAX_EG_SEQ_SIZE];
	u32 gain[MAX_EG_SEQ_SIZE];
	u16 hts;
	u16 vts;
	int seq_size;
	int eof_trigger;
};

typedef struct {
	struct sensor_t *sensor;
	struct expo_gain_seq me_seq;
	int eof_trigger;
	int seq_index;
}hisi_eg_ctrl_t;

enum {
	PIPE0_TRIG = 0,
	PIPE1_TRIG,
	NONE_TRIG,
};

enum {
	MANUAL_AE_NOT_APPLIED = 0,
	MANUAL_AE_APPLIED,
};

enum {
	META_CTRL_DISABLE = 0,
	META_CTRL_ENABLE = 1,
};

enum {
	ISP_DEBUG_META_DATA      = (1U<<0),
	ISP_DEBUG_META_DATA_RAW  = (1U<<1),
	ISP_DEBUG_PDAF_DATA      = (1U<<2),
};

int hw_isp_init(struct device *pdev);
int hw_isp_deinit(struct device *pdev);
int hw_isp_poweron(void);
int hw_isp_poweroff(void);
unsigned int hw_poll_irq(struct file * filp, struct poll_table_struct *wait);
void hw_query_irq(struct irq_reg_t *irq_info);
phys_addr_t hw_get_isp_base_addr(void);
u32 hw_get_isp_mem_size(void);
int hw_setup_eof_tasklet(struct sensor_t *sensor, struct expo_gain_seq *me_seq);
int hw_destory_eof_tasklet(void);

void hw_isp_setup_port(int port);
void hw_isp_clear_port(int port);

void meta_data_ctrl(int ctrl, uint32_t attach_port);
int  meta_data_buf_prepare(struct device *pdev);

/* ISP mac registers */
typedef enum {
	ISP_MAC0 = 0,
	ISP_MAC1,
	ISP_MAC2,

	ISP_MAC_MAX,
} isp_mac_e;

#define REG_MAC_BASE(mac) \
		(((mac) == ISP_MAC0) ? 0x63b00 : (0x63e00 + 0x100 * ((mac) - ISP_MAC1)))

/* ISP mac write count registers */
#define REG_MAC_WRITE_COUNT(mac)		(REG_MAC_BASE(mac) + 0x95)

/* bit[0]=1:pingpang bufffer enable; bit[0]=0:single buffer */
#define REG_MAC_PINGPANG_BUF_ENABLE(mac)		(REG_MAC_BASE(mac) + 0x4c)

#define REG_PORT_READY_ENABLE(mac)	(REG_MAC_BASE(mac) + 0x47)
#define REG_PORT_READY(port)	(REG_MAC_BASE((port) / 2) + 0x30)
#define REG_MAC_READ_READY(mac)		(REG_MAC_BASE(mac) + 0x57)

/* ISP mac write address */
#define REG_PORT_WRITE_ADDR(port) \
	(((port) % 2) == 0 ? (REG_MAC_BASE((port) / 2)) : (REG_MAC_BASE((port) / 2) + 0xc))

#define REG_PORT_WRITE_ADDR_U(port) \
	(((port) % 2) == 0 ? (REG_MAC_BASE((port) / 2) + 0x4) : (REG_MAC_BASE((port) / 2) + 0x60))

#define REG_PORT_WRITE_ADDR_V(port) \
	(((port) % 2) == 0 ? (REG_MAC_BASE((port) / 2) + 0x8) : (REG_MAC_BASE((port) / 2) + 0x64))

#define COMMAND_SET_BASE 		(0x34000)

/* OUTPUT ADDR, for bracket 3 frames */
#define ISP_MAC_OUTPUT_ADDR(x)			(COMMAND_SET_BASE + 0xA0 + 12 * (x))
#define ISP_MAC_OUTPUT_U_ADDR(x)			(COMMAND_SET_BASE + 0xA4 + 12 * (x))
#define ISP_MAC_OUTPUT_V_ADDR(x)			(COMMAND_SET_BASE + 0xA8 + 12 * (x))

/* command set registers */
#define COMMAND_REG0            		(0x63900)
#define COMMAND_REG1            		(COMMAND_REG0 + 0x1)
#define COMMAND_REG2            		(COMMAND_REG0 + 0x2)
#define COMMAND_REG3            		(COMMAND_REG0 + 0x3)
#define COMMAND_REG4            		(COMMAND_REG0 + 0x4)
#define COMMAND_REG5            		(COMMAND_REG0 + 0x5)
#define COMMAND_REG6            		(COMMAND_REG0 + 0x6)
#define COMMAND_REG7            		(COMMAND_REG0 + 0x7)

/* OUTPUT */
#define ISP_OUTPORT_SELECTION			(COMMAND_SET_BASE + 0x20)
#define ISP_OUT_TYPE(x)				(COMMAND_SET_BASE + 0x22 + 2 * 5 * (x))
#define ISP_OUT_WIDTH(x)			(COMMAND_SET_BASE + 0x24 + 2 * 5 * (x))
#define ISP_OUT_HEIGHT(x)			(COMMAND_SET_BASE + 0x26 + 2 * 5 * (x))
#define ISP_OUT_MEM_WIDTH(x)		(COMMAND_SET_BASE + 0x28 + 2 * 5 * (x))
#define ISP_OUT_MEM_WIDTH_UV(x)		(COMMAND_SET_BASE + 0x2a + 2 * 5 * (x))

/* INPUT */
#define ISP_READBACK_PORT_SELECTION		(COMMAND_SET_BASE + 0x60)
#define ISP_READBACK_WIDTH			(COMMAND_SET_BASE + 0x62)
#define ISP_READBACK_HEIGHT			(COMMAND_SET_BASE + 0x64)
#define ISP_READBACK_MEM_WIDTH		(COMMAND_SET_BASE + 0x66)

#define REG_UV_ORDER_U_AHEAD			(0x00)
#define REG_UV_ORDER_V_AHEAD			(0x40)

#define ISP_REG_OFFSET	0x3000
#define REG_ISP_TOP7(flow)                    (0x65007 + ISP_REG_OFFSET * (flow))
#define CMD_PROCESS_RAW		         	(0x6)

/* INPUT INFORMATION */
#define ISP_EXPOSURE_INPUT_ADDR(x)			(COMMAND_SET_BASE + 0x300 + 0x00 + 0x80 * (x))
#define ISP_GAIN_INPUT_ADDR(x)				(COMMAND_SET_BASE + 0x300 + 0x04 + 0x80 * (x))
#define ISP_MEAN_Y_INPUT_ADDR_ADDR(x)		(COMMAND_SET_BASE + 0x300 + 0x06 + 0x80 * (x))
#define ISP_RAW_STRETCH_LOW_LEVEL_INPUT_ADDR(x) \
						(COMMAND_SET_BASE + 0x300 + 0x08 + 0x80 * (x))
#define ISP_RAW_STRETCH_GAIN_INPUT_ADDR(x) \
						(COMMAND_SET_BASE + 0x300 + 0x0a + 0x80 * (x))
#define ISP_BGAIN_INPUT_ADDR(x)				(COMMAND_SET_BASE + 0x300 + 0x0C + 0x80 * (x))
#define ISP_GGAIN_INPUT_ADDR(x)				(COMMAND_SET_BASE + 0x300 + 0x0E + 0x80 * (x))
#define ISP_RGAIN_INPUT_ADDR(x)				(COMMAND_SET_BASE + 0x300 + 0x10 + 0x80 * (x))
#define ISP_B_OFFSET_INPUT_ADDR(x)				(COMMAND_SET_BASE + 0x300 + 0x12 + 0x80 * (x))
#define ISP_G_OFFSET_INPUT_ADDR(x)				(COMMAND_SET_BASE + 0x300 + 0x14 + 0x80 * (x))
#define ISP_R_OFFSET_INPUT_ADDR(x)				(COMMAND_SET_BASE + 0x300 + 0x16 + 0x80 * (x))
#define ISP_LENS_ONLINE_BA_INPUT_ADDR(x)	(COMMAND_SET_BASE + 0x300 + 0x18 + 0x80 * (x))
#define ISP_LENS_ONLINE_BR_INPUT_ADDR(x) 	(COMMAND_SET_BASE + 0x300 + 0x1a + 0x80 * (x))
#define ISP_LENS_PROFILE_INPUT_ADDR(x)		(COMMAND_SET_BASE + 0x300 + 0x1c + 0x80 * (x))

/* OUTPUT INFORMATION */
#define ISP_EXPOSURE_OUTPUT_ADDR(x)			(COMMAND_SET_BASE + 0x200 + 0x00 + 0x80 * (x))
#define ISP_GAIN_OUTPUT_ADDR(x)				(COMMAND_SET_BASE + 0x200 + 0x04 + 0x80 * (x))
#define ISP_MEAN_Y_OUTPUT_ADDR_ADDR(x)		(COMMAND_SET_BASE + 0x200 + 0x06 + 0x80 * (x))
#define ISP_RAW_STRETCH_LOW_LEVEL_OUTPUT_ADDR(x) \
						(COMMAND_SET_BASE + 0x200 + 0x08 + 0x80 * (x))
#define ISP_RAW_STRETCH_GAIN_OUTPUT_ADDR(x) \
						(COMMAND_SET_BASE + 0x200 + 0x0a + 0x80 * (x))
#define ISP_BGAIN_OUTPUT_ADDR(x)				(COMMAND_SET_BASE + 0x200 + 0x0C + 0x80 * (x))
#define ISP_GGAIN_OUTPUT_ADDR(x)				(COMMAND_SET_BASE + 0x200 + 0x0E + 0x80 * (x))
#define ISP_RGAIN_OUTPUT_ADDR(x)				(COMMAND_SET_BASE + 0x200 + 0x10 + 0x80 * (x))
#define ISP_B_OFFSET_OUTPUT_ADDR(x)				(COMMAND_SET_BASE + 0x200 + 0x12 + 0x80 * (x))
#define ISP_G_OFFSET_OUTPUT_ADDR(x)				(COMMAND_SET_BASE + 0x200 + 0x14 + 0x80 * (x))
#define ISP_R_OFFSET_OUTPUT_ADDR(x)				(COMMAND_SET_BASE + 0x200 + 0x16 + 0x80 * (x))
#define ISP_LENS_ONLINE_BA_OUTPUT_ADDR(x)	(COMMAND_SET_BASE + 0x200 + 0x18 + 0x80 * (x))
#define ISP_LENS_ONLINE_BR_OUTPUT_ADDR(x) 	(COMMAND_SET_BASE + 0x200 + 0x1a + 0x80 * (x))
#define ISP_LENS_PROFILE_OUTPUT_ADDR(x)		(COMMAND_SET_BASE + 0x200 + 0x1c + 0x80 * (x))


/* ISP mmu control address*/
#define REG_MMU_BASE(mac) \
		(0x7fd00 + 0x100 * ((mac) - ISP_MAC0))

#define REG_PORT_MMU_CTL_ADDR(port) \
	((port) < ISP_PORT_READ0 ? \
	(REG_MMU_BASE((port) / 2)) : (REG_MMU_BASE((port) % 3)))

#define REG_PORT_MMU_RDY_ADDR(port) \
	((port) < ISP_PORT_READ0 ? \
	(REG_MMU_BASE((port) / 2) + 0x08) : (REG_MMU_BASE((port) % 3) + 0x08))

#define REG_PORT_MMU_PTBA_ADDR(port) \
	((port) < ISP_PORT_READ0 ? \
	(REG_MMU_BASE((port) / 2) + 0x20) : (REG_MMU_BASE((port) % 3) + 0x20))

#define REG_PORT_MMU_PTVA_ADDR(port) \
	((port) < ISP_PORT_READ0 ? \
	(REG_MMU_BASE((port) / 2) + 0x24) : (REG_MMU_BASE((port) % 3) + 0x24))

#define REG_PORT_MMU_IRQ_ADDR(port) \
	((port) < ISP_PORT_READ0 ? \
	(REG_MMU_BASE((port) / 2) + 0x10) : (REG_MMU_BASE((port) % 3) + 0x10))

#define REG_PORT_MMU_TRANSID_ADDR(port) \
	((port) < ISP_PORT_READ0 ? \
	(REG_MMU_BASE((port) / 2) + 0x2c) : (REG_MMU_BASE((port) % 3) + 0x2c))

#define REG_PORT_MAC_TRANSID_ADDR(port) \
	((port) < ISP_PORT_READ0 ? \
	(REG_MAC_BASE((port) / 2) + 0xab) : (REG_MAC_BASE((port) % 3) + 0xab))

#define REG_PORT_MMU_AR0_ADDR(port) \
	((port) < ISP_PORT_READ0 ? \
	(REG_MMU_BASE((port) / 2) + 0x30) : (REG_MMU_BASE((port) % 3) + 0x30))

#define REG_PORT_MMU_AW0_ADDR(port) \
	((port) < ISP_PORT_READ0 ? \
	(REG_MMU_BASE((port) / 2) + 0x34) : (REG_MMU_BASE((port) % 3) + 0x34))

#define REG_PORT_MMU_AW1_ADDR(port) \
	((port) < ISP_PORT_READ0 ? \
	(REG_MMU_BASE((port) / 2) + 0x38) : (REG_MMU_BASE((port) % 3) + 0x38))

#define REG_PORT_MMU_AW2_ADDR(port) \
	((port) < ISP_PORT_READ0 ? \
	(REG_MMU_BASE((port) / 2) + 0x3c) : (REG_MMU_BASE((port) % 3) + 0x3c))

#define MMU_MAC_TRANSID(side, id) \
	(((side) == PORT_LEFT) ? ((id) & 0xff0f0000) : ((id) & ~0xff0f0000))

/* cmd_set and capture_cmd register operation */
#define CMD_SET_ISP_IN_FMT_SIZE(fmt, width, height) \
	do { \
		ISP_SETREG16(ISP_INPUT_TYPE, fmt);    \
		ISP_SETREG16(ISP_INPUT_WIDTH, width);  \
		ISP_SETREG16(ISP_INPUT_HEIGHT, height); \
	} while (0)

#define CMD_SET_OUTPORT_PARAMS(index, type, width, height, mem_width, mem_width_uv) \
	do { \
		ISP_SETREG16(ISP_OUT_TYPE(index), type);    \
		ISP_SETREG16(ISP_OUT_WIDTH(index), width);  \
		ISP_SETREG16(ISP_OUT_HEIGHT(index), height); \
		ISP_SETREG16(ISP_OUT_MEM_WIDTH(index), mem_width);  \
		ISP_SETREG16(ISP_OUT_MEM_WIDTH_UV(index), mem_width_uv); \
	} while (0)

#define CMD_SET_READPORT_PARAMS(width, height, mem_width) \
	do { \
		ISP_SETREG16(ISP_READBACK_WIDTH, width);  \
		ISP_SETREG16(ISP_READBACK_HEIGHT, height); \
		ISP_SETREG16(ISP_READBACK_MEM_WIDTH, mem_width);  \
	} while (0)	

hwisp_buf_t* ovisp23_get_buf_from_readyq(isp_port_e port);
int ovisp23_put_buf_to_doneq(isp_port_e port,hwisp_buf_t* buf);
int ovisp23_put_buf_to_idelq(isp_port_e port,hwisp_buf_t* buf);
void ovisp23_notify_cmd_ready(uint32_t cmd, uint32_t result);
void ovisp23_notify_eof(uint32_t id);
void ovisp23_notify_sof( uint32_t id);
int isp_cmd_update_buffer_cmd(isp_port_e port);
hwisp_stream_t* ovisp23_get_stream(isp_port_e port);
int isp_reprocess_cmdset(struct reprocess_param_list *reprocess_params);
int hw_alloc_firmware_memory(void);
void hw_free_firmware_memory(void);

#endif /*_ISP_OPS_H_ */
