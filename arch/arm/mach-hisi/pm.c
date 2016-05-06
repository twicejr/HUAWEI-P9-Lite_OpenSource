#include <linux/init.h>
#include <linux/cpu_pm.h>
#include <linux/suspend.h>
#include <linux/syscore_ops.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/clockchips.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/arm-cci.h>
#include <linux/irqchip/arm-gic.h>
#include <asm/suspend.h>
#include <asm/mcpm.h>
#include <asm/idmap.h>
#include <asm/cacheflush.h>
#include <asm/cputype.h>
#include <asm/cp15.h>
#include <asm/psci.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/delay.h>

#if defined(CONFIG_HI3630_LPM3_IPC)
#include "hisi_ipc.h"
#endif

#define PSCI_POWER_STATE_ID     (0)
#define IPC_SR_CMD (0x00000106)

/* gic reg offset */
#define GIC_ENABLE_OFFSET	(0x100)
#define GIC_PENDING_OFFSET	(0x200)

#define IRQ_NUM_MAX		(320)
#define IRQ_GROUP_MAX		(10)
#define IRQ_NUM_PER_WORD	(32)

char *irq_name[IRQ_NUM_MAX] = {
	"IPI_WAKEUP",		/* 0 */
	"IPI_TIMER",		/* 1 */
	"IPI_RESCHEDULE",	/* 2 */
	"IPI_CALL_FUNC",	/* 3 */
	"IPI_CALL_FUNC_SINGLE",	/* 4 */
	"IPI_CPU_STOP",		/* 5 */
	"IPI_COMPLETION",	/* 6 */
	"IPI_CPU_BACKTRACE",	/* 7 */
	"IPI_NOTIFY_FUNC",	/* 8 */
	NULL,		/* 9 */
	NULL,		/* 10 */
	NULL,		/* 11 */
	NULL,		/* 12 */
	NULL,		/* 13 */
	NULL,		/* 14 */
	NULL,		/* 15 */
	NULL,		/* 16 */
	NULL,		/* 17 */
	NULL,		/* 18 */
	NULL,		/* 19 */
	NULL,		/* 20 */
	NULL,		/* 21 */
	NULL,		/* 22 */
	NULL,		/* 23 */
	NULL,		/* 24 */
	"Virtual maintenance interrupt",	/* 25 */
	"Hypervisor timer",			/* 26 */
	"Virtual timer",			/* 27 */
	"Legacy FIQ signal",			/* 28 */
	"Secure physical timer",		/* 29 */
	"Non-secure physical timer",		/* 30 */
	"Legacy IRQ signal",			/* 31 */
	"MDM2AP[4]",	/* 32 */
	"A15_axierr",	/* 33 */
	"A15_pmu0",	/* 34 */
	"A15_pmu1",	/* 35 */
	"A15_pmu2",	/* 36 */
	"A15_pmu3",	/* 37 */
	"A15_cti0",	/* 38 */
	"A15_cti1",	/* 39 */
	"A15_cti2",	/* 40 */
	"A15_cti3",	/* 41 */
	"A15_COMMRX0",	/* 42 */
	"A15_COMMRX1",	/* 43 */
	"A15_COMMRX2",	/* 44 */
	"A15_COMMRX3",	/* 45 */
	"A15_COMMTX0",	/* 46 */
	"A15_COMMTX1",	/* 47 */
	"A15_COMMTX2",	/* 48 */
	"A15_COMMTX3",	/* 49 */
	"Reserved",	/* 50 */
	"A7_axierr",	/* 51 */
	"A7_pmu0",	/* 52 */
	"A7_pmu1",	/* 53 */
	"A7_pmu2",	/* 54 */
	"A7_pmu3",	/* 55 */
	"A7_cti0",	/* 56 */
	"A7_cti1",	/* 57 */
	"A7_cti2",	/* 58 */
	"A7_cti3",	/* 59 */
	"A7_COMMRX0",	/* 60 */
	"A7_COMMRX1",	/* 61 */
	"A7_COMMRX2",	/* 62 */
	"A7_COMMRX3",	/* 63 */
	"A7_COMMTX0",	/* 64 */
	"A7_COMMTX1",	/* 65 */
	"A7_COMMTX2",	/* 66 */
	"A7_COMMTX3",	/* 67 */
	"TIME00",	/* 68 */
	"TIME01",	/* 69 */
	"TIME10",	/* 70 */
	"TIME11",	/* 71 */
	"TIME20",	/* 72 */
	"TIME21",	/* 73 */
	"TIME30",	/* 74 */
	"TIME31",	/* 75 */
	"TIME40",	/* 76 */
	"TIME41",	/* 77 */
	"TIME50",	/* 78 */
	"TIME51",	/* 79 */
	"TIME60",	/* 80 */
	"TIME61",	/* 81 */
	"TIME70",	/* 82 */
	"TIME71",	/* 83 */
	"WatchDog0",	/* 84 */
	"WatchDog1",	/* 85 */
	"RTC0",		/* 86 */
	"RTC1",		/* 87 */
	"UART0",	/* 88 */
	"UART1",	/* 89 */
	"UART2",	/* 90 */
	"UART3",	/* 91 */
	"UART4",	/* 92 */
	"UART5",	/* 93 */
	"UART6",	/* 94 */
	"SPI0",		/* 95 */
	"SPI1",		/* 96 */
	"TSI0",		/* 97 */
	"TSI1",		/* 98 */
	"I2C0",		/* 99 */
	"I2C1",		/* 100 */
	"I2C2",		/* 101 */
	"I2C3",		/* 102 */
	"I2C4",		/* 103 */
	"I2C5",		/* 104 */
	"reserved",	/* 105 */
	"reserved",	/* 106 */
	"BLPWM",	/* 107 */
	"GPIO0",	/* 108 */
	"GPIO1",	/* 109 */
	"GPIO2",	/* 110 */
	"GPIO3",	/* 111 */
	"GPIO4",	/* 112 */
	"GPIO5",	/* 113 */
	"GPIO6",	/* 114 */
	"GPIO7",	/* 115 */
	"GPIO8",	/* 116 */
	"GPIO9",	/* 117 */
	"GPIO10",	/* 118 */
	"GPIO11",	/* 119 */
	"GPIO12",	/* 120 */
	"GPIO13",	/* 121 */
	"GPIO14",	/* 122 */
	"GPIO15",	/* 123 */
	"GPIO16",	/* 124 */
	"GPIO17",	/* 125 */
	"GPIO18",	/* 126 */
	"GPIO19",	/* 127 */
	"GPIO20",	/* 128 */
	"GPIO21",	/* 129 */
	"GPIO22",	/* 130 */
	"GPIO23",	/* 131 */
	"GPIO24",	/* 132 */
	"GPIO25",	/* 133 */
	"GPIO26",	/* 134 */
	"reserved",	/* 135 */
	"CoreSight_ETR_Full",	/* 136 */
	"CoreSight_ETF_Full",	/* 137 */
	"CCI400_overflow[3:0]",	/* 138 */
	"CCI400_overflow[4]",	/* 139 */
	"CCI400_err",		/* 140 */
	"SECENG_P",		/* 141 */
	"SECENG_S",		/* 142 */
	"SMMU0_combns",	/* 143 */
	"SMMU0_combs",	/* 144 */
	"SMMU1_combns",	/* 145 */
	"SMMU1_combs",	/* 146 */
	"USB2OTG",		/* 147 */
	"USB2HST",		/* 148 */
	"NANDC",		/* 149 */
	"EMMC",			/* 150 */
	"SD",			/* 151 */
	"SDIO0",		/* 152 */
	"DMAC0",		/* 153 */
	"DMAC_ns0",		/* 154 */
	"NOC-comb",		/* 155 */
	"DDRC",			/* 156 */
	"SCTRL",		/* 157 */
	"PMCTRL",		/* 158 */
	"TSENSOR_A15",	/* 159 */
	"TSENSOR_A7",	/* 160 */
	"TSENSOR_G3D",	/* 161 */
	"TSENSOR_Modem",/* 162 */
	"ISP",			/* 163 */
	"ISP-mmu",		/* 164 */
	"CSI-p",		/* 165 */
	"CSI-s",		/* 166 */
	"ASP",			/* 167 */
	"ASP-ns",		/* 168 */
	"G3D_JOB",		/* 169 */
	"G3D_MMU",		/* 170 */
	"G3D_GPU",		/* 171 */
	"JPEG",			/* 172 */
	"VPP",			/* 173 */
	"VPP_mmu",		/* 174 */
	"VENC",			/* 175 */
	"VDEC",			/* 176 */
	"DSS-pdp",		/* 177 */
	"DSS-sdp",		/* 178 */
	"DSS-offline",	/* 179 */
	"DSS_mcu_pdp",	/* 180 */
	"DSS_mcu_sdp",	/* 181 */
	"DSS_mcu_offline",	/* 182 */
	"DSS_dsi0",		/* 183 */
	"DSS_dsi1",		/* 184 */
	"DSS_hdmi",		/* 185 */
	"reserved",		/* 186 */
	"reserved",		/* 187 */
	"reserved",		/* 188 */
	"reserved",		/* 189 */
	"reserved",		/* 190 */
	"PMC-DDRC-DFS",	/* 191 */
	"PMC-DDRC-CFG", /* 192 */
	"PMC-DVFS-A15",	/* 193 */
	"PMC-DVFS-A7",	/* 194 */
	"PMC-DVFS-G3D",	/* 195 */
	"PMC-AVS-A15",	/* 196 */
	"PMC-AVS-A7",   /* 197 */
	"PMC-AVS-G3D",  /* 198 */
	"PMC-AVS-IDLE-A15",	/* 199 */
	"PMC-AVS-IDLE-A7",	/* 200 */
	"PMC-AVS-IDLE-G3D",	/* 201 */
	"M3_IO_wd",		/* 202 */
	"M3_LP_wd",		/* 203 */
	"reserved",		/* 204 */
	"IPC_S_int0",	/* 205 */
	"IPC_S_int1",	/* 206 */
	"IPC_S_int4",	/* 207 */
	"IPC_S_mbx0",	/* 208 */
	"IPC_S_mbx1",	/* 209 */
	"IPC_S_mbx2",	/* 210 */
	"IPC_S_mbx3",	/* 211 */
	"IPC_S_mbx4",	/* 212 */
	"IPC_S_mbx5",	/* 213 */
	"IPC_S_mbx6",	/* 214 */
	"IPC_S_mbx7",	/* 215 */
	"IPC_S_mbx8",	/* 216 */
	"IPC_S_mbx9",	/* 217 */
	"IPC_S_mbx18",	/* 218 */
	"reserved",	/* 219 */
	"IPC_NS_int0",	/* 220 */
	"IPC_NS_int1",	/* 221 */
	"IPC_NS_int4",	/* 222 */
	"IPC_NS_int5",	/* 223 */
	"IPC_NS_int6",	/* 224 */
	"IPC_NS_mbx0",	/* 225 */
	"IPC_NS_mbx1",	/* 226 */
	"IPC_NS_mbx2",	/* 227 */
	"IPC_NS_mbx3",	/* 228 */
	"IPC_NS_mbx4",	/* 229 */
	"IPC_NS_mbx5",	/* 230 */
	"IPC_NS_mbx6",	/* 231 */
	"IPC_NS_mbx7",	/* 232 */
	"IPC_NS_mbx8",	/* 233 */
	"IPC_NS_mbx9",	/* 234 */
	"IPC_NS_mbx18",	/* 235 */
	"MDM2AP[5]",	/* 236 */
	"MDM2AP[6]",	/* 237 */
	"reserved",	/* 238 */
	"ASP-IPC-ARM",	/* 239 */
	"ASP-IPC-MCPU",	/* 240 */
	"ASP-IPC-BBE16",/* 241 */
	"ASP_WD",	/* 242 */
	"ASP_AXI_DLOCK",/* 243 */
	"ASP_DMA_SECURE",	/* 244 */
	"ASP_DMA_SECURE_N",	/* 245 */
	"SCI0",			/* 246 */
	"SCI1",			/* 247 */
	"SOCP0",		/* 248 */
	"SOCP1",		/* 249 */
	"MDM2AP[0]",	/* 250 */
	"MDM2AP[1]",	/* 251 */
	"MDM2AP[2]",	/* 252 */
	"MDM2AP[3]",	/* 253 */
	"GIC_IRQ_OUT[0]",	/* 254 */
	"GIC_IRQ_OUT[1]",	/* 255 */
	"GIC_IRQ_OUT[2]",	/* 256 */
	"GIC_IRQ_OUT[3]",	/* 257 */
	"GIC_IRQ_OUT[4]",	/* 258 */
	"GIC_IRQ_OUT[5]",	/* 259 */
	"GIC_IRQ_OUT[6]",	/* 260 */
	"GIC_IRQ_OUT[7]",	/* 261 */
	"GIC_FIQ_OUT[0]",	/* 262 */
	"GIC_FIQ_OUT[1]",	/* 263 */
	"GIC_FIQ_OUT[2]",	/* 264 */
	"GIC_FIQ_OUT[3]",	/* 265 */
	"GIC_FIQ_OUT[4]",	/* 266 */
	"GIC_FIQ_OUT[5]",	/* 267 */
	"GIC_FIQ_OUT[6]",	/* 268 */
	"GIC_FIQ_OUT[7]" 	/* 269 */
};

static void __iomem *g_enable_base;
static void __iomem *g_pending_base;

extern void hisi_cci_enable_detect(u32 cluster);

static void __iomem *sctrl_base_addr = NULL;

void pm_gic_dump(void)
{
	unsigned int i;
	unsigned int j;
	unsigned int value;

	pr_info("============gic enable regs============\n");
	for (i = 0; i < IRQ_GROUP_MAX; i++) {
		value = readl(g_enable_base + i * 4);

		for (j = 0; j < IRQ_NUM_PER_WORD; j++) {
			if (((value >> j) & BIT_MASK(0)) && (irq_name[i * IRQ_NUM_PER_WORD + j] != NULL)){
				pr_info("irq num: %d, irq name: %s\n",
					i * IRQ_NUM_PER_WORD + j, irq_name[i * IRQ_NUM_PER_WORD + j]);
			}
		}
	}

	pr_info("============gic pending regs============\n");
	for (i = 0; i < IRQ_GROUP_MAX; i++) {
		value = readl(g_pending_base + i * 4);

		for (j = 0; j < IRQ_NUM_PER_WORD; j++) {
			if ((value >> j) & BIT_MASK(0)) {
				pr_info("irq num: %d, irq name: %s\n",
					i * IRQ_NUM_PER_WORD + j, irq_name[i * IRQ_NUM_PER_WORD + j]);
			}
		}
	}
}

static void hisi_pm_suspend(void)
{
	struct psci_power_state power_state;
	int cluster = 0;
	int cpu = 0;
	int mpidr = read_cpuid_mpidr();

	cpu = mpidr & 0xff;
	cluster = (mpidr >> 8) & 0xff;

	power_state.id = PSCI_POWER_STATE_ID;
	power_state.type = PSCI_POWER_STATE_TYPE_POWER_DOWN;
	power_state.affinity_level = PSCI_POWER_STATE_AFFINITY_LEVEL3;

	setup_mm_for_reboot();
	gic_cpu_if_down();
	set_cr(get_cr() & ~CR_C);
	flush_cache_all();

#if defined(CONFIG_SECURE_EXTENSION)
	psci_ops.cpu_suspend(power_state, virt_to_phys(mcpm_entry_point));
#else
	asm volatile ("clrex");
	set_auxcr(get_auxcr() & ~(1 << 6));
	cci_disable_port_by_cpu(mpidr);
	hisi_cci_enable_detect(1);
	cpu_proc_fin();

#if defined(CONFIG_HI3630_LPM3_IPC)
	hisi_ipc_pm_suspend(cpu, cluster, PSCI_POWER_STATE_AFFINITY_LEVEL3);
#endif
#endif
	dsb();
	while(1)
		wfi();
}

static int k3v3_cpu_suspend(unsigned long arg)
{
	writel(virt_to_phys(mcpm_entry_point), sctrl_base_addr + 0x31C);
	writel(0x2, sctrl_base_addr + 0x320);
	mcpm_set_entry_vector(0, 1, cpu_resume);
	hisi_pm_suspend();
	return 0;
}

#ifdef CONFIG_HISI_SR_DEBUG
extern void debuguart_reinit(void);
#endif

static int k3v3_pm_enter(suspend_state_t state)
{
	unsigned long flag = 0;

	printk("k3v3_pm_enter ++\n");

	local_irq_save(flag);

	cpu_suspend(0, k3v3_cpu_suspend);

#ifdef CONFIG_HISI_SR_DEBUG
	debuguart_reinit();
#endif

	pm_gic_dump();

	local_irq_restore(flag);

	printk("k3v3_pm_enter --\n");

	return 0;
}

static const struct platform_suspend_ops k3v3_pm_ops = {
	.enter		= k3v3_pm_enter,
	.valid		= suspend_valid_only_mem,
};

static void hisi_get_gic_base(void)
{
	void __iomem *hisi_gic_dist_base;
	struct device_node *node;

	node = of_find_compatible_node(NULL, NULL, "arm,cortex-a15-gic");
	hisi_gic_dist_base = of_iomap(node, 0);
	pr_info("hisi_gic_dist_base = 0x%x\n", (unsigned int)hisi_gic_dist_base);

	g_enable_base = hisi_gic_dist_base + GIC_ENABLE_OFFSET;
	g_pending_base = hisi_gic_dist_base + GIC_PENDING_OFFSET;
}

static __init int k3v3_pm_drvinit(void)
{
	struct device_node *np = NULL;
	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (!np) {
		pr_info("%s: hisilicon,sysctrl No compatible node found\n", __func__);
		return -ENODEV;
	}
	sctrl_base_addr = of_iomap(np, 0);

	hisi_get_gic_base();

	suspend_set_ops(&k3v3_pm_ops);
	return 0;
}
arch_initcall(k3v3_pm_drvinit);
