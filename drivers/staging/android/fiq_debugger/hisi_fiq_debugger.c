/*
 * Serial Debugger Interface for krin
 *
 * Copyright (C) 2012 huawei, Inc.
 * Copyright (C) 2008 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <asm/cacheflush.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/clk.h>
#include <linux/platform_device.h>
#include <linux/irq.h>
#include <linux/serial_reg.h>
#include <linux/slab.h>
#include <linux/stacktrace.h>
#include <linux/uaccess.h>
#include <linux/kfifo.h>
#include <linux/kthread.h>
#include <linux/amba/serial.h>
#include <linux/delay.h>
#include <linux/irqchip/arm-gic.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/serial_core.h>

#include <soc_ao_sctrl_interface.h>
#include <soc_baseaddr_interface.h>
#include <soc_irqs.h>
#include "fiq_debugger.h"
#include "fiq_watchdog.h"

struct hisi_fiq_debugger {
	struct fiq_debugger_pdata pdata;
	void __iomem *debug_port_base;
	void __iomem *gic_dist_base;
	void __iomem *gic_cpu_base;
	void __iomem *ao_sctrl_base;
};

unsigned int fiq_baudrate = 115200;

#define CONFIG_PL011_CLOCK		19200000   /*it's a shit*/
#define IPI_FIQ			15

static void hisi_fiq_init(struct platform_device *pdev, unsigned int fiq)
{
	unsigned int reg_offset;
	unsigned int bit_offset;
	unsigned int mask;
	struct hisi_fiq_debugger *t;
	t = container_of(dev_get_platdata(&pdev->dev), typeof(*t), pdata);
	
	reg_offset = fiq/32;
	reg_offset *= 4;
	bit_offset = fiq%32;
	mask = readl_relaxed(t->gic_dist_base + GIC_DIST_IGROUP+ reg_offset);
	bit_offset = 1<<bit_offset;
	mask &= ~bit_offset;
	writel_relaxed(mask, t->gic_dist_base + GIC_DIST_IGROUP + reg_offset);

	reg_offset = fiq/4;
	reg_offset *= 4;
	bit_offset = fiq%4;
	mask = readl_relaxed(t->gic_dist_base + GIC_DIST_PRI+ reg_offset);
	bit_offset = (0xff <<(bit_offset*8));
	mask &= ~bit_offset;
	writel_relaxed(mask, t->gic_dist_base + GIC_DIST_PRI + reg_offset);	

	if (fiq == IRQ_UART0) {
		reg_offset = fiq/4;
		reg_offset *= 4;
		bit_offset = fiq%4;
		mask = readl_relaxed(t->gic_dist_base + GIC_DIST_TARGET + reg_offset);
		mask &= ~(0xff <<(bit_offset*8));
		bit_offset = 1<<(bit_offset*8+FIQ_DEFAULT_CPU);
		writel_relaxed(mask | bit_offset, t->gic_dist_base + GIC_DIST_TARGET + reg_offset);
	}

	return;
}

static void hisi_uart_init(struct platform_device *pdev)
{
	unsigned int temp;
	unsigned int divider;
	unsigned int remainder;
	unsigned int fraction;
	struct hisi_fiq_debugger *t;
	
	t = container_of(dev_get_platdata(&pdev->dev), typeof(*t), pdata);

	/*
	 ** First, disable everything.
	 */
	writew (0, t->debug_port_base + UART011_CR);

	/*
	 ** Set baud rate
	 **
	 ** IBRD = UART_CLK / (16 * BAUD_RATE)
	 ** FBRD = ROUND((64 * MOD(UART_CLK,(16 * BAUD_RATE))) / (16 * BAUD_RATE))
	 */
	temp = 16 * fiq_baudrate;
	divider = CONFIG_PL011_CLOCK / temp;
	remainder = CONFIG_PL011_CLOCK % temp;
	temp = (8 * remainder) / fiq_baudrate;
	fraction = (temp >> 1) + (temp & 1);

	writew(divider, t->debug_port_base + UART011_IBRD);
	writew(fraction, t->debug_port_base + UART011_FBRD);

	/*
	 ** Set the UART to be 8 bits, 1 stop bit, no parity, fifo enabled.
	 */
	writew((UART01x_LCRH_WLEN_8 | UART01x_LCRH_FEN), t->debug_port_base + UART011_LCRH);
	writew(UART011_RTIM | UART011_RXIM, t->debug_port_base +  UART011_IMSC);

	/*
	 ** Finally, enable the UART
	 */
	writew ((UART01x_CR_UARTEN | UART011_CR_TXE | UART011_CR_RXE), t->debug_port_base + UART011_CR);
	
	return;
}

static int hisi_debug_port_init(struct platform_device *pdev)
{

	hisi_uart_init(pdev);
	hisi_fiq_init(pdev, IRQ_UART0);
	hisi_fiq_init(pdev, IRQ_ACPU_SOFT_FIQ);

	return 0;
}

static int hisi_debug_getc(struct platform_device *pdev)
{
	unsigned int c;
	struct hisi_fiq_debugger *t;
	t = container_of(dev_get_platdata(&pdev->dev), typeof(*t), pdata);

	c = readw(t->debug_port_base + UART01x_FR);
	if (c & UART01x_FR_RXFE) {
		writew((UART011_RTIS|UART011_RXIS), t->debug_port_base + UART011_ICR);
		return FIQ_DEBUGGER_NO_CHAR;
	}

	c = readw(t->debug_port_base + UART01x_DR) & 0xff;
	
	return c;
}

static void hisi_debug_putc(struct platform_device *pdev, unsigned int c)
{
	struct hisi_fiq_debugger *t;
	unsigned int count = 0;	
	
	t = container_of(dev_get_platdata(&pdev->dev), typeof(*t), pdata);
	while ((readw(t->debug_port_base + UART01x_FR) & UART01x_FR_TXFF)&& (count < 100000)){
		udelay(1);
		barrier();
		count++;
	}
	writew(c, t->debug_port_base + UART01x_DR);

	return;
}

static void hisi_fiq_enable(struct platform_device *pdev, unsigned int fiq, bool on)
{
	struct hisi_fiq_debugger *t;
	unsigned int reg_offset;
	unsigned int bit_offset;
	
	t = container_of(dev_get_platdata(&pdev->dev), typeof(*t), pdata);

	reg_offset = fiq/32;
	reg_offset *= 4;
	bit_offset = fiq%32;
	bit_offset = (1<<bit_offset);
	if (on == true) {
		writel_relaxed(bit_offset, t->gic_dist_base + GIC_DIST_ENABLE_SET+ reg_offset);
	} else {
		writel_relaxed(bit_offset, t->gic_dist_base + GIC_DIST_ENABLE_CLEAR+ reg_offset);		
	}

	return;
}

static void hisi_fiq_switch_cpu(struct platform_device *pdev, unsigned int fiq, unsigned int cpu)
{
	struct hisi_fiq_debugger *t;
	unsigned int reg_offset;
	unsigned int bit_offset;
	unsigned int mask;
	
	t = container_of(dev_get_platdata(&pdev->dev), typeof(*t), pdata);

	reg_offset = fiq/4;
	reg_offset *= 4;
	bit_offset = fiq%4;
	mask = readl_relaxed(t->gic_dist_base + GIC_DIST_TARGET + reg_offset);
	mask &= ~(0xff <<(bit_offset*8));
	bit_offset = 1<<(bit_offset*8+cpu);
	writel_relaxed(mask|bit_offset, t->gic_dist_base + GIC_DIST_TARGET + reg_offset);

	return;
}

static int get_signal_irq_type(struct platform_device *pdev, unsigned int irq)
{
	struct hisi_fiq_debugger *t;
	unsigned int reg_offset;
	unsigned int bit_offset;
	unsigned int mask;
	
	t = container_of(dev_get_platdata(&pdev->dev), typeof(*t), pdata);

	reg_offset = irq/32;
	reg_offset *= 4;
	bit_offset = irq%32;
	mask = readl_relaxed(t->gic_dist_base + GIC_DIST_IGROUP+ reg_offset);
	bit_offset = 1<<bit_offset;
	mask &= bit_offset;

	return mask;
}

static int set_signal_irq_type(struct platform_device *pdev, unsigned int irq, unsigned int is_irq)
{
	struct hisi_fiq_debugger *t;
	unsigned int reg_offset;
	unsigned int bit_offset;
	unsigned int mask;
	
	t = container_of(dev_get_platdata(&pdev->dev), typeof(*t), pdata);

	reg_offset = irq/32;
	reg_offset *= 4;
	bit_offset = irq%32;
	mask = readl_relaxed(t->gic_dist_base + GIC_DIST_IGROUP+ reg_offset);
	bit_offset = 1<<bit_offset;
	if (is_irq) {
		mask |= bit_offset;
	} else {
		mask &= ~bit_offset;
	}
	writel_relaxed(mask, t->gic_dist_base + GIC_DIST_IGROUP + reg_offset);
	
	return mask;
}

static void hisi_console_setup(struct platform_device *pdev, unsigned int baudrate)
{
	fiq_baudrate = baudrate;
	hisi_uart_init(pdev);
	return;
}

static void hisi_force_irq(struct platform_device *pdev, unsigned int irq)
{
	struct hisi_fiq_debugger *t;
	unsigned int ulRegValue = 0;
	
	t = container_of(dev_get_platdata(&pdev->dev), typeof(*t), pdata);

	set_signal_irq_type(pdev, irq, 1);

	writel(BIT(SOC_AO_SCTRL_SC_INT_EN_SET_sc_int_en0_4acpu_sft_fiq_START), 
		SOC_AO_SCTRL_SC_INT_EN_SET_ADDR(t->ao_sctrl_base));
	ulRegValue = BIT(SOC_AO_SCTRL_SC_PW_CTRL1_acpu_sft_fiq_req_START) |
		BIT(SOC_AO_SCTRL_SC_PW_CTRL1_acpu_sft_fiq_req_msk_START);
	writel(ulRegValue,SOC_AO_SCTRL_SC_PW_CTRL1_ADDR(t->ao_sctrl_base));  
}

static void hisi_force_irq_ack(struct platform_device *pdev, unsigned int irq)
{
	struct hisi_fiq_debugger *t;
	unsigned int ulRegValue = 0;
	
	t = container_of(dev_get_platdata(&pdev->dev), typeof(*t), pdata);

	ulRegValue = BIT(SOC_AO_SCTRL_SC_PW_CTRL1_acpu_sft_fiq_req_msk_START);
	writel(ulRegValue,SOC_AO_SCTRL_SC_PW_CTRL1_ADDR(t->ao_sctrl_base)); 
	writel(BIT(SOC_AO_SCTRL_SC_INT_EN_DIS_sc_int_dis0_4acpu_sft_fiq_START), 
		SOC_AO_SCTRL_SC_INT_EN_DIS_ADDR(t->ao_sctrl_base));
}

int hisi_uart_resume(struct platform_device *pdev)
{
	hisi_uart_init(pdev);
	hisi_fiq_init(pdev, IRQ_UART0);
	return 0;
}

extern void gic_raise_softirq(const struct cpumask *mask, unsigned int irq);
extern void hisi_usb_soft_disconnect(void); 
int hisi_fiq_handle(struct platform_device *pdev, const struct pt_regs *regs, void *svc_sp)
{
	struct hisi_fiq_debugger *t;
	unsigned int mask;
	unsigned int fiqnr;
	int ret = 0;
	
	t = container_of(dev_get_platdata(&pdev->dev), typeof(*t), pdata);
	
	mask = readl_relaxed(t->gic_cpu_base + GIC_CPU_INTACK);
	fiqnr = mask & (~0x1c00);
	if (fiqnr > 15)
		mask = fiqnr;

	if (fiqnr == IRQ_ACPU_SOFT_FIQ) {
		debug_locks_off();
		fiq_watchdog_triggered(regs, svc_sp);	
		hisi_force_irq_ack(pdev, IRQ_ACPU_SOFT_FIQ);
		writel_relaxed(0x0100000f, t->gic_dist_base + GIC_DIST_SOFTINT);
		flush_cache_all();
		hisi_usb_soft_disconnect(); 
		while(1);
	} else if (fiqnr == IPI_FIQ) {
		fiq_watchdog_triggered(regs, svc_sp);
		flush_cache_all();
		while(1);
	} else {
		ret = 1;
	}

	writel_relaxed(mask, t->gic_cpu_base + GIC_CPU_EOI);
	
	return ret;
}

void hisi_serial_debug_init(struct platform_device *pdev)
{
	struct hisi_fiq_debugger *t = NULL;
	struct resource *res = NULL;
	int res_count = 0;
	struct device_node *np;
	unsigned int irq = -1;
	unsigned int signal_irq = -1;
	unsigned int wakeup_irq = -1;
	
	t = kzalloc(sizeof(struct hisi_fiq_debugger), GFP_KERNEL);
	if (!t) {
		pr_err("Failed to allocate for fiq debugger\n");
		return;
	}

	np = of_find_node_by_name(NULL, "interrupt-controller");
	BUG_ON(!np);

	t->gic_dist_base = of_iomap(np, 0);
	BUG_ON(!t->gic_dist_base);	
	
	t->gic_cpu_base = of_iomap(np, 1);
	BUG_ON(!t->gic_cpu_base);

	np = of_find_node_by_name(NULL, "ao_sctrl");
	t->ao_sctrl_base= of_iomap(np, 0);
	BUG_ON(!t->ao_sctrl_base);
	
	np = of_find_node_by_path("/amba/uart@f8015000");
	t->debug_port_base = of_iomap(np, 0);
	BUG_ON(!t->debug_port_base);
	irq = irq_of_parse_and_map(np, 0);
	of_property_read_u32(np, "uart-baudRate", &fiq_baudrate);

	np = of_find_node_by_name(NULL, "watchdog");
	signal_irq = irq_of_parse_and_map(np, 1);

	t->pdata.uart_init = hisi_debug_port_init,
	t->pdata.console_setup = hisi_console_setup;
	t->pdata.uart_getc = hisi_debug_getc,
	t->pdata.uart_putc = hisi_debug_putc,
	t->pdata.fiq_enable = hisi_fiq_enable,
	t->pdata.fiq_switch_cpu = hisi_fiq_switch_cpu,
	t->pdata.force_irq = hisi_force_irq,
	t->pdata.force_irq_ack = hisi_force_irq_ack;
	t->pdata.get_signal_irq_type = get_signal_irq_type,
	t->pdata.set_signal_irq_type = set_signal_irq_type,
	t->pdata.fiq_handle = hisi_fiq_handle,
	t->pdata.uart_dev_resume = hisi_uart_resume,

	res = kzalloc(sizeof(struct resource) * 3, GFP_KERNEL);
	if (!res) {
		pr_err("Failed to alloc fiq debugger resources\n");
		goto out2;
	}

	if (irq >= 0) {
		res[0].flags = IORESOURCE_IRQ;
		res[0].start = irq;
		res[0].end = irq;
		res[0].name = "fiq";
		res_count++;
	}

	if (signal_irq >= 0) {
		res[1].flags = IORESOURCE_IRQ;
		res[1].start = signal_irq;
		res[1].end = signal_irq;
		res[1].name = "signal";
		res_count++;
	}

	if (wakeup_irq >= 0) {
		res[2].flags = IORESOURCE_IRQ;
		res[2].start = wakeup_irq;
		res[2].end = wakeup_irq;
		res[2].name = "wakeup";
		res_count++;
	}

	pdev->name = "fiq_debugger";
	pdev->dev.platform_data = &t->pdata;
	pdev->resource = res;
	pdev->num_resources = res_count;

	return;

out2:
	kfree(t);
}

