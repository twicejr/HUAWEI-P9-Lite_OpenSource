/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
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

#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/videodev2.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/clk.h>
#include <asm/io.h>

#include "../platform/sensor_commom.h"
#include "../io/hw_isp_io.h"
#include "hw_csi.h"
#include <dsm/dsm_pub.h>

/*csi register macro definition*/
#define CSI_INT_EN			0x00000000 /*lint -save -e750 */
#define CSI_INT_DIS			0xffffffff
#define CSI_REG_N_LANES     		(0x04)
#define CSI_REG_PHY_SHUTDOWNZ   	(0x08)
#define CSI_REG_DPHY_RSTZ		(0x0c)
#define CSI_REG_RESETN			(0x10)
#define CSI_REG_PHY_STATE		(0x14)
#define CSI_REG_MASK1			(0x28)
#define CSI_REG_MASK2          		(0x2c)

#define PHY_TST_CONTRL0			(0x30)
#define PHY_TST_CONTRL1			(0x34)

#define CSI_REG_ERR1			(0x20)
#define CSI_REG_ERR2			(0x24)

#define CSI_PERI_CTRL19                 (0x50)
#define CSI_PERI_CTRL24                 (0x64)

#define PCTRL_BASE			(0xE8A09000)

#define DPHY_DSI_CSI_2_CSI_P_1	(1 << 19)
#define DPHY_DSI_CSI_2_CSI_P_2	(1 << 22)
#define DPHY_CSI2_2_CSI_S	(1 << 23)
#define DPHY_MUX_SEL		(1 << 12)

#define PHY_STATE_STOPSTATE0      	(1 << 4)
#define PHY_STATE_STOPSTATE1      	(1 << 5)
#define PHY_STATE_RXCLKACTIVEHS    	(1 << 8)
#define PHY_STATE_STOPSTATECLK     	(1 << 10)

#define PHY_SELECT_PRIME_SENSOR         (1 << 19 | 1 << 22)
#define PHY_SELECT_SECOND_SENSOR        (1 << 23)


#define CSI_INIT_DELAY			10
#define DEBUG_CSI_IRQ                   (1)

static unsigned int csi_error_count = 0;
//#define THS_CSI
#define LANE0_THS_SETTLE (0x10)
#define LANE0_HS_CLK_SRC (0x11)
#define LANE1_THS_SETTLE (0x20)
#define LANE1_HS_CLK_SRC (0x21)
#define LANE2_THS_SETTLE (0x30)
#define LANE2_HS_CLK_SRC (0x31)
#define LANE3_THS_SETTLE (0x40)
#define LANE3_HS_CLK_SRC (0x41) /*lint -restore */

struct workqueue_struct	*csi_work_queue;
struct work_struct	dump_csi_err_work;//for csi error by wind
extern void misp_dump_default_reg(struct work_struct *work);

struct hw_csi_pad hw_csi_pad;

struct dsm_client_ops ops4={
	.poll_state = NULL,
	.dump_func = NULL,
};

struct dsm_dev dev_csi = {
	.name = "dsm_csi",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = &ops4,
	.buff_size = 256,
};

struct dsm_client *client_csi;

#define SAVE_DMD_LOG_OFF (false)
#define SAVE_DMD_LOG_ON  (true)

bool csi_dmd_log[CSI_INDEX_CNT] = {SAVE_DMD_LOG_OFF, SAVE_DMD_LOG_OFF};

void TSTCODE_SETREG8(unsigned int reg_base, unsigned int addr, unsigned int value)
{
	HW_CSI_SETREG32(reg_base + PHY_TST_CONTRL1, (1 << 16) | addr);
	HW_CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 2);
	HW_CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 0);
	HW_CSI_SETREG32(reg_base + PHY_TST_CONTRL1, value);
	HW_CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 2);
	HW_CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 0);
}

void TSTCODE_GETREG8(unsigned int reg_base, unsigned int addr, unsigned int *value)
{
	HW_CSI_SETREG32(reg_base + PHY_TST_CONTRL1, (1 << 16) | addr);
	HW_CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 2);
	HW_CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 0);
	*value = ((HW_CSI_GETREG32(reg_base + PHY_TST_CONTRL1) >> 8) & (0x000000ff));
}

void hisi_csi_clear_dmd_counter(void)
{
	csi_error_count = 0;
}

static irqreturn_t hisi_csi0_isr(int irq, void *dev_id)
{
	u32 irq_status1;
	u32 irq_status2;

	u32 reg_offset = hw_csi_pad.info.csi_base_offset[CSI_INDEX_0];

	irq_status1 = HW_CSI_GETREG32(reg_offset + CSI_REG_ERR1);
	irq_status2 = HW_CSI_GETREG32(reg_offset + CSI_REG_ERR2);

	if ((irq_status1 | irq_status2) != 0){
		cam_err("[I/DSM] %s ERR1[0x%x], ERR2[0x%x]", __func__, irq_status1, irq_status2);
		csi_error_count++;
		if((csi_dmd_log[CSI_INDEX_0]  == SAVE_DMD_LOG_ON) && (csi_error_count > 33)){
			if(!dsm_client_ocuppy(client_csi)){
				queue_work(csi_work_queue, &dump_csi_err_work);
				cam_info("[I/DSM] %s ocuppy sucess", __func__);
				dsm_client_record(client_csi, "%s ERR1[0x%x], ERR2[0x%x]\n", __func__, irq_status1, irq_status2);
				dsm_client_notify(client_csi, DSM_CSI_MIPI0_ERROR_NO);
				csi_dmd_log[CSI_INDEX_0] = SAVE_DMD_LOG_OFF;
				csi_error_count = 0;
			}
		}
	}

	/* automatic clear all interrupts */

	return IRQ_HANDLED;
}

static irqreturn_t hisi_csi1_isr(int irq, void *dev_id)
{
	u32 irq_status1;
	u32 irq_status2;

	u32 reg_offset = hw_csi_pad.info.csi_base_offset[CSI_INDEX_1];

	irq_status1 = HW_CSI_GETREG32(reg_offset + CSI_REG_ERR1);
	irq_status2 = HW_CSI_GETREG32(reg_offset + CSI_REG_ERR2);

	if ((irq_status1 | irq_status2) != 0){
		cam_err("%s ERR1[0x%x], ERR2[0x%x]", __func__, irq_status1, irq_status2);
		csi_error_count++;
		if((csi_dmd_log[CSI_INDEX_1]  == SAVE_DMD_LOG_ON) && (csi_error_count > 5)){
			if(!dsm_client_ocuppy(client_csi)){
				cam_info("[I/DSM] %s ocuppy sucess", __func__);
				dsm_client_record(client_csi, "%s ERR1[0x%x], ERR2[0x%x]\n", __func__, irq_status1, irq_status2);
				dsm_client_notify(client_csi, DSM_CSI_MIPI1_ERROR_NO);
				csi_dmd_log[CSI_INDEX_1] = SAVE_DMD_LOG_OFF;
				csi_error_count = 0;
			}
		}
	}

	/* automatic clear all interrupts */

	return IRQ_HANDLED;
}

#if !defined(THS_CSI)
int hw_csi_enable(csi_index_t csi_index, int csi_lane, int csi_mipi_clk)
{
	/*CSI PHY enbale*/
	u32 phy_state1;
	u32 reg_offset;
	u32 err1 ;
	u32 err2 ;
	int ret = 0;
	char csi_irq_name[16] = {0};

	cam_notice("%s enter:csi_index=%d,csi_lane=%d,csi_mipi_clk=%d.\n", __func__,
		csi_index, csi_lane, csi_mipi_clk);
	if (csi_index == 2) {
		csi_index = 1;
	}

	if(hw_csi_pad.csi_inited[csi_index]) {
		cam_info("csi  phy has already been enabled.");
		return ret;
	}

	reg_offset = hw_csi_pad.info.csi_base_offset[csi_index];
	cam_info("%s reg_offset = 0x%x.\n", __func__, reg_offset);

	if (!hw_is_fpga_board()) {//fixme
		void __iomem * pctrl_reg = 0;

		cam_debug("enter %s, excute enable csi clock", __func__);
		ret = clk_prepare_enable(hw_csi_pad.info.phyclk[csi_index]);
		if (0 != ret) {
			cam_err("%s, clock enable fail", __func__);
		}

		pctrl_reg = (void __iomem *)ioremap_nocache(PCTRL_BASE, 0x8000);
		if (IS_ERR_OR_NULL(pctrl_reg)){
			cam_err("%s, ioremap_nocache PCTRL_BASE fail", __func__);
			return -1;
		}

		if (!hw_csi_pad.info.dsi_csi_used) {
			/* config csi to sensor */
			cam_notice("%s Config CSI to Sensor.", __func__);

			writel(readl((pctrl_reg + CSI_PERI_CTRL19)) | DPHY_CSI2_2_CSI_S,
			(pctrl_reg + CSI_PERI_CTRL19));
			//writel_relaxed(value, (volatile void *)(pctrl_reg + CSI_PERI_CTRL19));
		} else {
			/* config csi to sensor */
			cam_notice("%s Config CSI to Sensor.", __func__);
			writel((readl(pctrl_reg + CSI_PERI_CTRL24)) & ~DPHY_MUX_SEL,
				(pctrl_reg + CSI_PERI_CTRL24));
			//writel_relaxed(readl_relaxed(prti_cfg_reg + REG_PCTRL24) & ~DPHY_MUX_SEL, prti_cfg_reg + REG_PCTRL24);
		}
		iounmap((void*)pctrl_reg);

	}
#ifdef DEBUG_CSI_IRQ

	csi_error_count = 0;
	csi_dmd_log[csi_index] = SAVE_DMD_LOG_ON;

	cam_info("%s request csi-%d irq", __func__, csi_index);
	snprintf(csi_irq_name, sizeof(csi_irq_name), "mipi-csi-irq-%d", csi_index);
	ret = request_irq(hw_csi_pad.info.csi_irq[csi_index], hw_csi_pad.info.irq_pfn[csi_index], 0, csi_irq_name, 0);
	if (ret < 0) {
		cam_err("fail to request irq [%d]", hw_csi_pad.info.csi_irq[CSI_INDEX_0]);
		return -EAGAIN;
	}

#endif

	HW_CSI_SETREG32(reg_offset + CSI_REG_PHY_SHUTDOWNZ, 0);
	HW_CSI_SETREG32(reg_offset + CSI_REG_PHY_SHUTDOWNZ, 1);

	HW_CSI_SETREG32(reg_offset + CSI_REG_N_LANES, csi_lane);

	HW_CSI_SETREG32(reg_offset + CSI_REG_DPHY_RSTZ, 0);
	HW_CSI_SETREG32(reg_offset + CSI_REG_DPHY_RSTZ, 1);

	HW_CSI_SETREG32(reg_offset + CSI_REG_RESETN, 0);
	HW_CSI_SETREG32(reg_offset + CSI_REG_RESETN, 1);

	HW_CSI_SETREG32(reg_offset + PHY_TST_CONTRL0, 1);
	HW_CSI_SETREG32(reg_offset + PHY_TST_CONTRL0, 0);

	HW_CSI_SETREG32(reg_offset + PHY_TST_CONTRL1, 0x10044);
	HW_CSI_SETREG32(reg_offset + PHY_TST_CONTRL0, 2);
	HW_CSI_SETREG32(reg_offset + PHY_TST_CONTRL0, 0);

	HW_CSI_SETREG32(reg_offset + PHY_TST_CONTRL1, csi_mipi_clk);
	HW_CSI_SETREG32(reg_offset + PHY_TST_CONTRL0, 2);
	HW_CSI_SETREG32(reg_offset + PHY_TST_CONTRL0, 0);


	/*
	   csi-2 Controller programming - Read the PHY status register (PHY_STATE) to confirm that all data
	   and clock lanes of the D-PHY are in Stop State (that is, ready to receive data).
	 */

	/*
	   Configure the MIPI Camera Sensor - Access Camera Sensor using CCI interface to initialize and
	   configure the Camera Sensor to start transmitting a clock on the D-PHY clock lane.
	 */

	/*
	   csi-2 Controller programming - Read the PHY status register (PHY_STATE) to confirm that the
	   D-PHY is receiving a clock on the D-PHY clock lane.
	 */

	phy_state1 = HW_CSI_GETREG32(reg_offset + CSI_REG_PHY_STATE);

	err1 = HW_CSI_GETREG32(reg_offset + CSI_REG_ERR1);

	err2 = HW_CSI_GETREG32(reg_offset + CSI_REG_ERR2);

	cam_debug("Not all data and clock lanes of the D-PHY are in Stop State,"
		"err1 : %#x, err2 : %#x", err1,  err2);

	if (0 == (phy_state1 & PHY_STATE_STOPSTATE0)
	&& 0 == (phy_state1 & PHY_STATE_STOPSTATECLK)) {
		cam_info("Not all data and clock lanes of the D-PHY are in Stop State,"
			"phy_state1 : %#x", phy_state1);
	}

	if (0 == (phy_state1 & PHY_STATE_RXCLKACTIVEHS)) {
		cam_info("D-PHY was not receive a clock");
	}

	HW_CSI_SETREG32(reg_offset + CSI_REG_MASK1, CSI_INT_EN);
	HW_CSI_SETREG32(reg_offset + CSI_REG_MASK2, CSI_INT_EN);

	phy_state1 = HW_CSI_GETREG32(reg_offset + CSI_REG_PHY_STATE);
	cam_debug("Not all data and clock lanes of the D-PHY are in Stop State,"
		"phy_state1 : %#x", phy_state1);
	hw_csi_pad.csi_inited[csi_index] = true;

	return ret;
}
#else
int hw_csi_enable(csi_index_t csi_index, int csi_lane, int csi_mipi_clk)
{
	/*CSI PHY enbale*/
	u32 phy_state1;
	u32 reg_base;
	u32 err1 ;
	u32 err2 ;
	u8 settle_time, value, camera_source;

	reg_base = 0x7F400;

	HW_CSI_SETREG32(reg_base + CSI_REG_PHY_SHUTDOWNZ, 0);
	HW_CSI_SETREG32(reg_base + CSI_REG_DPHY_RSTZ, 0);
	HW_CSI_SETREG32(reg_base + CSI_REG_RESETN, 0);

	HW_CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 1);
	HW_CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 0);
	msleep(1);

	HW_CSI_SETREG32(reg_base + CSI_REG_PHY_SHUTDOWNZ, 1);
	HW_CSI_SETREG32(reg_base + CSI_REG_N_LANES, 3);

	//settle_time = 26;
	//settle_time = 23;
	//settle_time = 10;
	settle_time = 23; //29; //16;
	camera_source = 1;

	HW_CSI_SETREG32(reg_base + CSI_REG_DPHY_RSTZ, 1);
	HW_CSI_SETREG32(reg_base + CSI_REG_RESETN, 1);

	TSTCODE_SETREG8(reg_base, LANE0_HS_CLK_SRC, camera_source);
	TSTCODE_GETREG8(reg_base, LANE0_HS_CLK_SRC, &value);
	cam_info("reg LANE0_HS_CLK_SRC = %d", value);

	TSTCODE_SETREG8(reg_base, LANE1_THS_SETTLE, settle_time);
	TSTCODE_GETREG8(reg_base, LANE1_THS_SETTLE, &value);
	cam_info("reg LANE1_THS_SETTLE = %d", value);

	TSTCODE_SETREG8(reg_base, LANE1_HS_CLK_SRC, camera_source);
	TSTCODE_GETREG8(reg_base, LANE1_HS_CLK_SRC, &value);
	cam_info("reg LANE1_HS_CLK_SRC = %d", value);

	TSTCODE_SETREG8(reg_base, LANE2_THS_SETTLE, settle_time);
	TSTCODE_GETREG8(reg_base, LANE2_THS_SETTLE, &value);
	cam_info("reg LANE2_THS_SETTLE = %d", value);

	TSTCODE_SETREG8(reg_base, LANE2_HS_CLK_SRC, camera_source);
	TSTCODE_GETREG8(reg_base, LANE2_HS_CLK_SRC, &value);
	cam_info("reg LANE2_HS_CLK_SRC = %d", value);

	TSTCODE_SETREG8(reg_base, LANE3_THS_SETTLE, settle_time);
	TSTCODE_GETREG8(reg_base, LANE3_THS_SETTLE, &value);
	cam_info("reg LANE3_THS_SETTLE = %d", value);

	/* diff with balong */
	TSTCODE_SETREG8(reg_base, LANE3_HS_CLK_SRC, camera_source);
	TSTCODE_GETREG8(reg_base, LANE3_HS_CLK_SRC, &value);
	cam_info("reg LANE3_HS_CLK_SRC = %d", value);

	/*
	   csi-2 Controller programming - Read the PHY status register (PHY_STATE) to confirm that all data
	   and clock lanes of the D-PHY are in Stop State (that is, ready to receive data).
	 */

	/*
	   Configure the MIPI Camera Sensor - Access Camera Sensor using CCI interface to initialize and
	   configure the Camera Sensor to start transmitting a clock on the D-PHY clock lane.
	 */

	/*
	   csi-2 Controller programming - Read the PHY status register (PHY_STATE) to confirm that the
	   D-PHY is receiving a clock on the D-PHY clock lane.
	 */


	phy_state1 = HW_CSI_GETREG32(reg_base + CSI_REG_PHY_STATE);

	err1 = HW_CSI_GETREG32(reg_base + CSI_REG_ERR1);
	err2 = HW_CSI_GETREG32(reg_base + CSI_REG_ERR2);
	cam_info("Not all data and clock lanes of the D-PHY are in Stop State, "
			"err1 : %#x, err2 : %#x ", err1,  err2);

	if (0 == (phy_state1 & PHY_STATE_STOPSTATE0)
	&& 0 == (phy_state1 & PHY_STATE_STOPSTATECLK)) {
		cam_err("Not all data and clock lanes of the D-PHY are in Stop State, "
			"phy_state1 : %#x ", phy_state1);

	}

	if (0 == (phy_state1 & PHY_STATE_RXCLKACTIVEHS))
		cam_err("D-PHY was not receive a clock \n");

	HW_CSI_SETREG32(reg_base + CSI_REG_MASK1, CSI_INT_EN);
	HW_CSI_SETREG32(reg_base + CSI_REG_MASK2, CSI_INT_EN);
	msleep(100);

	phy_state1 = HW_CSI_GETREG32(reg_base + CSI_REG_PHY_STATE);
	cam_err("Not all data and clock lanes of the D-PHY are in Stop State, "
			"phy_state1 : %#x ", phy_state1);

	cam_info("exit.");
	return 0;
}
#endif


int hw_csi_disable(csi_index_t csi_index)
{
	//u32 reg_offset;

	cam_info("%s enter:csi_index=%d.\n", __func__, csi_index);
	if (csi_index == 2) {
		csi_index = 1;
	}

	if(!hw_csi_pad.csi_inited[csi_index]) {
		cam_debug("csi is disabled now");
		return 0;
	}

	//reg_offset = hw_csi_pad.info.csi_base_offset[csi_index];

	//HW_CSI_SETREG32(reg_offset + CSI_REG_RESETN, 0);
	//HW_CSI_SETREG32(reg_offset + CSI_REG_PHY_SHUTDOWNZ, 0);

	if (!hw_is_fpga_board()) {
		clk_disable_unprepare(hw_csi_pad.info.phyclk[csi_index]);
	}
#ifdef DEBUG_CSI_IRQ
	cam_info("%s free csi%d & csi1 irq.\n", __func__, csi_index);
	free_irq(hw_csi_pad.info.csi_irq[csi_index], 0);
	csi_dmd_log[csi_index] = SAVE_DMD_LOG_OFF;
#endif
	hw_csi_pad.csi_inited[csi_index] = false;
	flush_workqueue(csi_work_queue);
	return 0;
}

int hw_csi_config(csi_index_t csi_index, int csi_lane, int csi_mipi_clk)
{
	cam_debug("%s enter.\n", __func__);
	/*TO DO ...*/
	return 0;
}

int hw_csi_platform_probe(struct platform_device *pdev)
{
	struct device_node *of_node = pdev->dev.of_node;
	uint32_t base_array[CSI_INDEX_CNT] = {0};
	uint32_t count = 0;
	int ret;
	int i;

	cam_debug("%s enter.\n", __func__);
	/*NOTE: should assign all the csi phy hardware info here*/

	/* property(hisi,csi-base) = <csi0_base_offset, csi1_base_offset>,
	 * so count is 2 .
	 */
	count = 2;
	if (of_node) {
		ret = of_property_read_u32_array(of_node, "huawei,csi-base-offset",
			base_array, count);
		if (ret < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			return ret;
		}
	} else {
		cam_err("%s csi of_node is NULL.\n", __func__);
		return -ENXIO;
	}

	for (i=0; i<count; i++) {
		cam_debug("%s csi base[%d] = 0x%x.\n", __func__, i, base_array[i]);
		hw_csi_pad.info.csi_base_offset[i] = base_array[i];
	}

	ret = of_property_read_u32(of_node, "huawei,csi0-irq",
		&hw_csi_pad.info.csi_irq[CSI_INDEX_0]);
	if (ret < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return ret;
	}

	ret = of_property_read_u32(of_node, "huawei,csi1-irq",
		&hw_csi_pad.info.csi_irq[CSI_INDEX_1]);
	if (ret < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return ret;
	}

	cam_notice("%s csi0-irq = %d, csi1-irq = %d.\n", __func__,
		hw_csi_pad.info.csi_irq[CSI_INDEX_0], hw_csi_pad.info.csi_irq[CSI_INDEX_1]);

	ret = of_property_read_u32(of_node, "huawei,dsi_csi_used",
		&hw_csi_pad.info.dsi_csi_used);
	if (ret < 0) {
		hw_csi_pad.info.dsi_csi_used = 0;
	}
	cam_notice("%s dsi_csi_used=%d\n", __func__, hw_csi_pad.info.dsi_csi_used);

	/* get csi clock */
	hw_csi_pad.info.phyclk[CSI_INDEX_0]= devm_clk_get(&pdev->dev, "clk_dphy1");
	if (IS_ERR_OR_NULL(hw_csi_pad.info.phyclk[CSI_INDEX_0])) {
		cam_err("failed to get dphy1 clock");
		ret = -ENXIO;
	}


	if (hw_csi_pad.info.dsi_csi_used) {
		hw_csi_pad.info.phyclk[CSI_INDEX_1]= devm_clk_get(&pdev->dev, "clk_dphy2");
		if (IS_ERR_OR_NULL(hw_csi_pad.info.phyclk[CSI_INDEX_1])) {
			cam_err("failed to get dphy2 clock");
			ret = -ENXIO;
		}
	} else {
		hw_csi_pad.info.phyclk[CSI_INDEX_1]= devm_clk_get(&pdev->dev, "clk_dphy3");
		if (IS_ERR_OR_NULL(hw_csi_pad.info.phyclk[CSI_INDEX_1])) {
			cam_err("failed to get dphy3 clock");
			ret = -ENXIO;
		}
	}

	if(client_csi == NULL){
		client_csi = dsm_register_client(&dev_csi);
	}

	hw_csi_pad.info.irq_pfn[CSI_INDEX_0] = hisi_csi0_isr;
	hw_csi_pad.info.irq_pfn[CSI_INDEX_1] = hisi_csi1_isr;

	return ret;
}

struct hw_csi_pad hw_csi_pad = {
	.csi_inited = {false, false},
	.hw_csi_enable = hw_csi_enable,
	.hw_csi_disable = hw_csi_disable,
	.hw_csi_config = hw_csi_config,
};

static const struct of_device_id hisi_csi_dt_match[] = {
	{.compatible = "huawei,csi-phy"},
	{}
};
MODULE_DEVICE_TABLE(of, hisi_csi_dt_match);
static struct platform_driver csi_platform_driver = {
	.driver = {
		.name = "csi-phy",
		.owner = THIS_MODULE,
		.of_match_table = hisi_csi_dt_match,
	},
};

static int32_t csi_platform_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	const struct of_device_id *match;

	match = of_match_device(hisi_csi_dt_match, &pdev->dev);
	cam_notice("%s compatible=%s.\n", __func__, match->compatible);
	rc = hw_csi_platform_probe(pdev);
	if(rc < 0){
		cam_info("%s fail rc =%x",__func__,rc);
		return rc;
	}

	csi_work_queue =
	create_singlethread_workqueue(dev_name(&pdev->dev));
	if (!csi_work_queue) {
		cam_err("%s - create workqueue error",__func__);
		return -1;
	}
	INIT_WORK(&dump_csi_err_work, misp_dump_default_reg);
	return rc;
}

static int __init csi_init_module(void)
{
	int rc = 0;
	cam_debug("%s:%d\n", __func__, __LINE__);

	rc = platform_driver_probe(&csi_platform_driver,
		csi_platform_probe);
	if (rc < 0) {
		cam_err("%s platform_driver_probe error(%d).\n", __func__, rc);
	}
	return rc;
}

static void __exit csi_exit_module(void)
{
	return platform_driver_unregister(&csi_platform_driver);
}

module_init(csi_init_module);
module_exit(csi_exit_module);
MODULE_DESCRIPTION("hisi_csi");
MODULE_LICENSE("GPL v2");

