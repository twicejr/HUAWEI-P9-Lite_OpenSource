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

#define REG_FW_CURRENT_Y(flow)					(FW_STAT_REG_BASE(flow) + 0x06)
#define REG_FW_WRITEBACK_GAIN(flow)				(FW_STAT_REG_BASE(flow) + 0x1e)
#define REG_FW_WRITEBACK_EXPO(flow)				(FW_STAT_REG_BASE(flow) + 0x20)
#define REG_FW_AECAGC_WRITESENSOR_ENABLE(flow)			(0x33011 + FW_REG_OFFSET * (flow))

/*************************** isp register macro definition *****************************/

#define FIRMWARE_FILE_PATH		"/system/isp/isp.bin"

#define RESET_DELAY_INTERVAL		4
#define STAND_BY_DELAY_INTERVAL	10



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
};


typedef struct _isp_hw_data{

	struct semaphore sem_cmd_done;
	spinlock_t irq_status_lock;
	wait_queue_head_t poll_queue_head;
	bool poll_start;

	void __iomem * viraddr;
	u32 phyaddr;
	u32 mem_size;
	u32 irq_no;

	struct irq_reg_t irq_val;
	bool irq_query_flag;
	struct clk *isp_sclk;
	struct clk *ispmipi_clk;
	struct clk *isp_mclk;
	struct regulator_bulk_data inter_ldo;
	/* pinctrl */
	struct pinctrl *isp_pinctrl;
	struct pinctrl_state *pinctrl_def;
	struct pinctrl_state *pinctrl_idle;

	struct ion_client *client;
	struct ion_handle *handle;
	struct iommu_map_format format;
}isp_hw_data_t;


int k3_isp_init(struct device *pdev);
int k3_isp_deinit(void);
int k3_isp_poweron(void);
int k3_isp_poweroff(void);
unsigned int k3_poll_irq(struct file * filp, struct poll_table_struct *wait);
void k3_query_irq(struct irq_reg_t *irq_info);
u32 k3_get_isp_base_addr(void);
u32 k3_get_isp_mem_size(void);

#ifdef SEATTLE_FPGA
	#define set8(reg, value) (*((volatile unsigned char *)(reg)) = (value))
	#define set32(reg, value) (*((volatile u32 *)(reg)) = (value))
	#define get8(reg) (*(volatile unsigned char *)(reg))
	#define get32(reg) (*(volatile u32 *)(reg))
#endif

#endif /*_ISP_OPS_H_ */