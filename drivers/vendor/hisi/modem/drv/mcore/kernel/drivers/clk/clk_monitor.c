/*************************************************************************
*   版权所有(C) 2008-2016, 深圳华为技术有限公司.
*
*   文 件 名 :  clk_monitor.c
*
*   作    者 :  y00184236
*
*   描    述 :  本文件主要完成clk monitor功能
*
*   修改记录 :
*      1> 2015年11月10日  v1.00  y00184236  创建
*************************************************************************/
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <bsp_sysctrl.h>
#include <bsp_dump.h>
#include <libfdt.h>

#define CLK_MON_SLOW_EN_SHIFT         (8)
#define CLK_MON_STOP_EN_SHIFT         (9)
#define CLK_MON_SLOW_INT_MASK_SHIFT   (12)
#define CLK_MON_STOP_INT_MASK_SHIFT   (13)
#define CLK_ERROR                     (-1)
#define CLK_OK                        (0)
#define CLK_PRINT(fmt,...)            (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CLK, "[clk]: "fmt, ##__VA_ARGS__))
#define CLK_PRINT_DEBUG(fmt,...)      (bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_CLK, "[clk]: "fmt, ##__VA_ARGS__))

enum CLK_MONITOR_MODULE
{
	CLK_MON_A9PLL = 0,
	CLK_MON_DSPPLL,
	CLK_MON_USBPLL,
	CLK_MON_PERIPLL,
	CLK_MON_TCXO,
	CLK_MON_MAX
};

enum CLK_MONITOR_MODE
{
	CLK_MON_STOP_MODE = 0x01,
	CLK_MON_SLOW_MODE = 0x10,
};

enum CLK_MONITOR_REG_OFFSET
{
	CLK_MON_STAT_REG = 0,
	CLK_MON_CNT_REG  = 4,
	CLK_MON_CTRL_REG = 8
};

struct clk_monitor_reg
{
	u32 state;
	u32 cnt;
	u32 ctrl;
};

struct clk_monitor_ctrl
{
	struct clk_monitor_reg      reg;
	DRV_NV_CLK_MONITOR_CFG_STRU nv_cfg;
	u32 init_flag;
};

struct clk_ctrl
{
	struct clk_monitor_ctrl monitor;
	/* something else*/
};

struct clk_ctrl g_clk_ctrl;

static inline void clk_common_handle(u32 monitor_mode, u32 ctrl_reg_bit, u32 irq)
{
	u32 reg_val= 0;

	CLK_PRINT("pll[%d] exception, mode=0x%x, reboot\n", g_clk_ctrl.monitor.nv_cfg.pll_mon_moudle, monitor_mode);

	/* 清中断 */
	reg_val = readl(g_clk_ctrl.monitor.reg.ctrl);
	reg_val &= ~(1 << ctrl_reg_bit);
	writel((unsigned)reg_val, (unsigned)g_clk_ctrl.monitor.reg.ctrl);

	system_error((u32)DRV_ERRNO_CLK_EXCEPT, monitor_mode, irq, NULL, 0);
}

static void clk_slow_irq_handler(u32 irq)
{
	clk_common_handle(g_clk_ctrl.monitor.nv_cfg.pll_mon_mode, CLK_MON_SLOW_EN_SHIFT, irq);
}

static void clk_stop_irq_handler(u32 irq)
{
	clk_common_handle(g_clk_ctrl.monitor.nv_cfg.pll_mon_mode, CLK_MON_STOP_EN_SHIFT, irq);
}

void clk_monitor_init(void)
{
	int ret = CLK_OK;
	struct device_node *clk_node = NULL;
	u32 module = CLK_MON_TCXO;
	u32 reg_base = 0;;
	u32 dts_cfg[5] = {0};
	u32 reg_val = 0;

	memset(&g_clk_ctrl, 0x0, sizeof(g_clk_ctrl));

	/* 从nv中读取clk时钟变慢和时钟停止相关配置 */
	ret = bsp_nvm_read(NV_ID_DRV_NV_CLK_MONITOR,(u8*)&g_clk_ctrl.monitor.nv_cfg, sizeof(g_clk_ctrl.monitor.nv_cfg));
    if (NV_OK != ret)
    {
		CLK_PRINT("read nv fail, disable monitor\n");
		return;
    }
	module = g_clk_ctrl.monitor.nv_cfg.pll_mon_moudle;

	/* 从dts中读取寄存器基地址和中断配置 */
	clk_node = of_find_compatible_node(NULL, NULL, "clk_monitor");
	if (!clk_node)
	{
		goto dts_out;
	}

	ret = of_property_read_u32_array(clk_node, "reg_base", (void *)dts_cfg, 5);
	if(ret)
	{
		goto dts_out;
	}
	reg_base = (u32)bsp_sysctrl_addr_byindex(sysctrl_ao) + dts_cfg[module];
	g_clk_ctrl.monitor.reg.state = reg_base + CLK_MON_STAT_REG;
	g_clk_ctrl.monitor.reg.cnt   = reg_base + CLK_MON_CNT_REG;
	g_clk_ctrl.monitor.reg.ctrl  = reg_base + CLK_MON_CTRL_REG;

	ret = of_property_read_u32_array(clk_node, "irqs", (void *)dts_cfg, 2);
	if(ret)
	{
		goto dts_out;
	}

	/* 将配置信息写入寄存器,并挂接中断 */
	if (CLK_MON_STOP_MODE == (g_clk_ctrl.monitor.nv_cfg.pll_mon_mode&CLK_MON_STOP_MODE))
	{
		reg_val = readl((unsigned)g_clk_ctrl.monitor.reg.ctrl);
		reg_val &= ~(1 << CLK_MON_STOP_INT_MASK_SHIFT);
		reg_val |= (1 << CLK_MON_STOP_EN_SHIFT);
		reg_val &= ~ (0xFF);
		reg_val |= (g_clk_ctrl.monitor.nv_cfg.pll_stop_timeout)&0xFF;
		writel((unsigned)reg_val, (unsigned)g_clk_ctrl.monitor.reg.ctrl);

		ret = request_irq(dts_cfg[1], (irq_handler_t)clk_stop_irq_handler, \
			IRQF_DISABLED, "clk_stop irq", 0);/*lint !e713*/
		if (ret)
		{
			CLK_PRINT("request clk stop irq err\n");
		}
		else
		{
			enable_irq(dts_cfg[1]);
		}
	}
	if (CLK_MON_SLOW_MODE == (g_clk_ctrl.monitor.nv_cfg.pll_mon_mode&CLK_MON_SLOW_MODE)) /* 可能同时配置监控时钟停止和时钟变慢 */
	{
		reg_val = (g_clk_ctrl.monitor.nv_cfg.pll_mon_cnt_min& 0xffff);
		reg_val |= ((g_clk_ctrl.monitor.nv_cfg.pll_mon_cnt_max & 0xffff) << 16);
		writel((unsigned)reg_val, (unsigned)g_clk_ctrl.monitor.reg.cnt);

		reg_val = readl((unsigned)g_clk_ctrl.monitor.reg.ctrl);
		reg_val &= ~(1 << CLK_MON_SLOW_INT_MASK_SHIFT);
		reg_val |= (1 << CLK_MON_SLOW_EN_SHIFT);
		writel((unsigned)reg_val, (unsigned)g_clk_ctrl.monitor.reg.ctrl);

		ret = request_irq(dts_cfg[0], (irq_handler_t)clk_slow_irq_handler, \
			IRQF_DISABLED, "clk_slow irq", 0);/*lint !e713*/
		if (ret)
		{
			CLK_PRINT("request clk slow irq err\n");
		}
		else
		{
			enable_irq(dts_cfg[0]);
		}
	}

	g_clk_ctrl.monitor.init_flag = 1;
	CLK_PRINT("init ok\n");
	return;

dts_out:
	CLK_PRINT("read dts fail, disable monitor\n");
	return;
}

void bsp_clk_init(void)
{
	clk_monitor_init();

	/* something else to do */
}
