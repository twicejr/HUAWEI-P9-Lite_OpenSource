/*
 *	linux/kernel/drivers/hisi/hi3xxx/hisi_lpregs.c
 *
 * Copyright (C) 2015 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
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
#include <linux/irqflags.h>
#include <linux/arm-cci.h>
#include <linux/irqchip/arm-gic.h>
#include <linux/hw_power_monitor.h>
#include <linux/console.h>
#include "hisi_lpregs.h"
/*lint -e322 -esym(750,*) */
#include "hisi_gpio_auto_gen.h"
#ifdef CONFIG_HISI_LPMCU_BB
#include "m3_rdr_ddr_map.h"
#endif

#define PM_WAKE_STATUS_OFFSET			(0x034)
#define PM_SYS_SLEEP_CNT_OFFSET			(0x060)
#define PM_SYS_WAKE_CNT_OFFSET			(0x064)
#define PM_AP_WAKE_CNT_OFFSET			(0x068)
#define PM_HIFI_WAKE_CNT_OFFSET			(0x06C)
#define PM_MODEM_WAKE_CNT_OFFSET		(0x070)
#define PM_IOMCU_WAKE_CNT_OFFSET			(0x074)
#define PM_LPM3_WAKE_CNT_OFFSET			(0x078)
#define PM_AP_SUSPEND_CNT_OFFSET			(0x07C)
#define PM_AP_RESUME_CNT_OFFSET			(0x080)
#define PM_IOMCU_SUSPEND_CNT_OFFSET		(0x084)
#define PM_IOMCU_RESUME_CNT_OFFSET		(0x088)
#define PM_MODEM_SUSPEND_CNT_OFFSET		(0x08C)
#define PM_MODEM_RESUME_CNT_OFFSET		(0x090)
#define PM_HIFI_SUSPEND_CNT_OFFSET		(0x094)
#define PM_HIFI_RESUME_CNT_OFFSET			(0x098)
#define PM_WAKE_IRQ_OFFSET				(0x09C)
#define PM_AP_WAKE_IRQ_OFFSET			(0x0A0)
#define PM_AP_NSIPC_IRQ_OFFSET			(0x0A4)
#define IDLE_SLEEP_CNT_OFFSET			(0x0F4)
#define IDLE_RESUME_CNT_OFFSET			(0x0F8)
#define PM_WAKE_IRQ1_OFFSET				(0x0FC)

#define SCINT_STAT_OFFSET					(0x458)
#define SCINT_STAT1_OFFSET					(0x468)

#define PM_BUFFER_SIZE						(256)

#define WAKE_STATUS_AP_MASK     (0x01)
#define WAKE_STATUS_MODEM_MASK  (0x02)
#define WAKE_STATUS_HIFI_MASK   (0x04)
#define WAKE_STATUS_IOMCU_MASK  (0x08)
#define WAKE_STATUS_LPMCU_MASK  (0x10)
#define WAKE_STATUS_GPS_MASK    (0x20)
#define WAKE_STATUS_HOTPLUG_MASK(cluster)       (0x1 << ((cluster) + 6))

/* FIXME: need to supplement */
/***************************
 * SCINT_STAT
	bit 0:gpio_22_int,
	bit 1:gpio_23_int,
	bit 2:gpio_24_int,
	bit 3:gpio_25_int,
	bit 5:gpio_27_int,
	bit 6:rtc_int,
	bit 7:rtc1_int,
	bit 11:timer11_int, for secure os
***************************/
#define AP_INT_MASK (0x000008ef)

/*******************
 * SCINT_STAT
 *  bit 31: intr_wakeup_iomcu
 *  bit 28: intr_iomcu_wdog
*******************/
#define IOMCU_INT_MASK (0x90000000)

/*******************
 * SCINT_STAT
	bit 4:gpio_26_int,
	bit 9:timer01_int
	bit 12:timer20_int
	bit 13:timer21_int
	bit 14:timer30_int
	bit 15:timer31_int
*******************/
#define MODEM_INT_MASK (0x0000f210)

/*******************
 * SCINT_STAT1
 * bit 0: drx0_int
 * bit 1: drx1_int
 * bit 2: drx2_int
 * bit 3: drx3_int
 * bit 4: drx4_int
 * bit 5: drx5_int
********************/
#define MODEM_DRX_INT_MASK (0x0000003f)

/*******************
 * FIXME: need to supplement
 * #define LPM3_INT_MASK (0x0000)
*******************/

/*******************
 * bit 26: intr_asp_ipc_arm
 * bit 27: intr_asp_watchdog
*******************/
#define HIFI_INT_MASK  (0x0c000000)



#define WAKE_IRQ_NUM_MAX 30

#define DEBG_SUSPEND_PRINTK		(1<<0)
#define DEBG_SUSPEND_IO_SHOW		(1<<1)
#define DEBG_SUSPEND_PMU_SHOW	(1<<2)
#define DEBG_SUSPEND_IO_SET		(1<<3)
#define DEBG_SUSPEND_PMU_SET		(1<<4)
#define DEBG_SUSPEND_IO_S_SET		(1<<5)
#define DEBG_SUSPEND_RTC_EN		(1<<6)
#define DEBG_SUSPEND_TIMER_EN		(1<<7)
#define DEBG_SUSPEND_WAKELOCK	(1<<8)
#define DEBG_SUSPEND_AUDIO		(1<<9)
#define DEBG_SUSPEND_CLK_SHOW	(1<<10)
#define DEBG_SUSPEND_IPC_DATA_SHOW	(1<<11)
#define DEBUG_INFO				(1<<31)

#define REG_SCLPM3CLKEN_OFFSET	(0x500)
#define REG_SCLPM3RSTEN_OFFSET	(0x504)

#define REG_SCLPM3RSTDIS_OFFSET	(0x508)

#define BIT_CLK_UART_SHIFT			(1 << 8)
#define BIT_RST_UART_SHIFT			(1 << 9)

#define REG_PEREN2_OFFSET	(0x020)
#define REG_PERDIS2_OFFSET	(0x024)
#define REG_PERRSTEN2_OFFSET	(0x078)
#define REG_PERRSTDIS2_OFFSET	(0x07C)
#define BIT_UART0_SHIFT		(10)

#define IOMG_066_OFFSET	(0x108)
#define IOMG_067_OFFSET	(0x10C)
#define IOMG_030_OFFSET	(0x078)
#define IOMG_031_OFFSET	(0x07C)
#define IOC_UART6_VAL		(0x1)
#define IOC_UART0_VAL		(0x2)

/* pmu */
#define PMU_CTRL_END_A		0x117
#define PMU_CTRL_END_D		0x253

#define PMUSSI_REG(x) (sysreg_base.pmic_base + ((x)<<2))

#define SCTRLBASE       0xfff0a000
#define CRGBASE          0xfff35000
#define PMCBASE          0xfff31000
#define PMUBASE          0xfff34000
#define PCTRLBASE		0xE8A09000


/*ipc processor max*/
#define IPC_PROCESSOR_MAX		6
/*ipc mailbox max*/
#define NSIPC_MAILBOX_MAX		27

#define AP_IPC_PROC_MAX			2

#define IPC_MBXDATA_MAX			8
#define IPC_MBX_SOURCE_OFFSET(m)		((m) << 6)
#define IPC_MBX_DSTATUS_OFFSET(m)		(0x0C + ((m) << 6))
#define IPC_MBXDATA_OFFSET(m, idex)		(0x20 + 4 * (idex) + ((m) << 6))

#define CLK_DEBUG_FILE_MODE     (S_IRUSR)
#define PMU_DEBUG_FILE_MODE     (S_IRUSR)
#define IO_DEBUG_FILE_MODE     (S_IRUSR)
#define CFG_DEBUG_FILE_MODE     (S_IRUSR | S_IWUSR)
#define DEBUGSR_DEBUG_FILE_MODE     (S_IRUSR)
#define NO_SEQFILE 0
#define LOWPM_MSG(seq_file, fmt, args ...) \
		{		\
			if (NO_SEQFILE == seq_file)	\
				printk(KERN_INFO fmt, ##args);	\
			else	\
				seq_printf(seq_file, fmt, ##args);	\
		}

#define PLAT_A	(0x1)
#define PLAT_D	(0x2)
unsigned int g_plat_flag;

unsigned char *processor_name[IPC_PROCESSOR_MAX] = {
	"gic1",
	"gic2",
	"iomcu",
	"lpm3",
	"hifi",
	"modem"
};

#define LPM3_IRQ_MAX		230
static unsigned char *lpm3_irq_name[LPM3_IRQ_MAX] = {
	"maia_pmu",		/*0*/
	"modem_ipc0[1]",		/*1*/
	"modem_ipc1[1]",		/*2*/
	"a53_pmu",		/*3*/
	"modem_ipc0[3]",		/*4*/
	"modem_ipc1[3]",		/*5*/
	"modem_ipc0[0]",		/*6*/
	"modem_ipc1[3]",		/*7*/
	"watchdog0",		/*8*/
	"watchdog1",		/*9*/
	"rtc0",		/*10*/
	"rtc1",		/*11*/
	"time00",		/*12*/
	"time01",		/*13*/
	"time10",		/*14*/
	"time11",		/*15*/
	"time20",		/*16*/
	"time21",		/*17*/
	"time30",		/*18*/
	"time31",		/*19*/
	"time40",		/*20*/
	"time41",		/*21*/
	"time50",		/*22*/
	"time51",		/*23*/
	"time60",		/*24*/
	"time61",		/*25*/
	"time70",		/*26*/
	"time71",		/*27*/
	"time80",		/*28*/
	"time81",		/*29*/
	"time90",		/*30*/
	"time91",		/*31*/
	"time100",		/*32*/
	"time101",		/*33*/
	"time110",		/*34*/
	"time111",		/*35*/
	"time120",		/*36*/
	"time121",		/*37*/
	"UART0",		/*38*/
	"UART1",		/*39*/
	"UART3",		/*40*/
	"UART4",		/*41*/
	"UART5",		/*42*/
	"UART6",		/*43*/
	"SPI1",		/*44*/
	"i2c3",		/*45*/
	"i2c4",		/*46*/
	"i2c5",		/*47*/
	"gpio0",		/*48*/
	"gpio1",		/*49*/
	"gpio2",		/*50*/
	"gpio3",		/*51*/
	"gpio4",		/*52*/
	"gpio5",		/*53*/
	"gpio6",		/*54*/
	"gpio7",		/*55*/
	"gpio8",		/*56*/
	"gpio9",		/*57*/
	"gpio10",		/*58*/
	"gpio11",		/*59*/
	"gpio12",		/*60*/
	"gpio13",		/*61*/
	"gpio14",		/*62*/
	"gpio15",		/*63*/
	"gpio16",		/*64*/
	"gpio17",		/*65*/
	"gpio18",		/*66*/
	"gpio19",		/*67*/
	"gpio20",		/*68*/
	"gpio21",		/*69*/
	"gpio22",		/*70*/
	"gpio23",		/*71*/
	"gpio24",		/*72*/
	"gpio25",		/*73*/
	"gpio26",		/*74*/
	"gpio27",		/*75*/
	"mdm_wdog",		/*76*/
	"iomcu_wd",		/*77*/
	"iomcu_wakeup",		/*78*/
	"iomuc_dmac_int2",		/*79*/
	"iomuc_dmac_ns_int2",		/*80*/
	"iomcu_uart3",		/*81*/
	"iomcu_spi",		/*82*/
	"iomcu_blpwm",		/*83*/
	"iomcu_comb",		/*84*/
	"iomcu_i2c0",		/*85*/
	"iomcu_i2c1",		/*86*/
	"iomcu_i2c2",		/*87*/
	"iomcu_i2c3",		/*88*/
	"iomcu_uart8",		/*89*/
	"iomcu_spi2",		/*90*/
	"iomcu_gpio0_int2",		/*91*/
	"iomcu_gpio1_int2",		/*92*/
	"iomcu_gpio2_int2",		/*93*/
	"iomcu_gpio3_int2",		/*94*/
	"perf_stat",		/*95*/
	"isp_a7_to_mcu_mbx_int[0]",		/*96*/
	"isp_a7_to_mcu_mbx_int[1]",		/*97*/
	"isp_a7_to_mcu_ipc_int",		/*98*/
	"isp_a7_watchdog",		/*99*/
	"NOC_comb",		/*100*/
	"intr_dmss",		/*101*/
	"intr_ddrc0_err",		/*102*/
	"intr_ddrc1_err",		/*103*/
	"pmctrl",		/*104*/
	"intr_tds_hifi",		/*105*/
	"modem_ipc0[4]",		/*106*/
	"modem_ipc1[4]",		/*107*/
	"seceng_p",		/*108*/
	"seceng_s",		/*109*/
	"emmc0",		/*110*/
	"emmc1",		/*111*/
	"sd",		/*112*/
	"sdio0",		/*113*/
	"sdio1",		/*114*/
	"dmac_int2",		/*115*/
	"dmac_ns_int2",		/*116*/
	"clk_monitor",		/*117*/
	"tsensor_maia",		/*118*/
	"tsensor_a53",		/*119*/
	"tsensor_g3d",		/*120*/
	"tsensor_modem",		/*121*/
	"asp_arm_secure",		/*122*/
	"asp_arm",		/*123*/
	"a53_0_core_pwr",		/*124*/
	"a53_1_core_pwr",		/*125*/
	"vdm_int2",		/*126*/
	"vdm_int0",		/*127*/
	"vdm_int1",		/*128*/
	"dss_mcu_pdp",		/*129*/
	"dss_mcu_sdp",		/*130*/
	"dss_mcu_offline",		/*131*/
	"ddrc_fatal_int[3:0]",		/*132*/
	"modem_ipc0[2]",		/*133*/
	"reserved",		/*134*/
	"reserved",		/*135*/
	"modem_ipc1[2]",		/*136*/
	"reserved",		/*137*/
	"mdm_edmac_ns[2]",		/*138*/
	"mdm_bus_err",		/*139*/
	"usb3[0]",		/*140*/
	"usb3[1]",		/*141*/
	"usb3_otg",		/*142*/
	"usb3_bc",		/*143*/
	"pwc_dvfs_maia",		/*144*/
	"pwc_dvfs_a53",		/*145*/
	"pwc_dvfs_g3d",		/*146*/
	"pwc_avs_maia",		/*147*/
	"pwc_avs_a53",		/*148*/
	"pwc_avs_g3d",		/*149*/
	"pwc_avs_idle_maia",		/*150*/
	"pwc_avs_idle_a53",		/*151*/
	"pwc_avs_idle_g3d",		/*152*/
	"m3_lp_wd",		/*153*/
	"CCI400_overflow[4:0]",		/*154*/
	"IPC_S_int3",		/*155*/
	"IPC_S_int4",		/*156*/
	"IPC_S_int5",		/*157*/
	"IPC_S_mbx13",		/*158*/
	"IPC_S_mbx14",		/*159*/
	"IPC_S_mbx15",		/*160*/
	"IPC_S_mbx16",		/*161*/
	"IPC_S_mbx17",		/*162*/
	"IPC_S_mbx18",		/*163*/
	"IPC_S_mbx[20:19]",		/*164*/
	"IPC_S_mbx23",		/*165*/
	"IPC_S_mbx24",		/*166*/
	"IPC_NS_int3",		/*167*/
	"IPC_NS_int4",		/*168*/
	"IPC_NS_int5",		/*169*/
	"IPC_NS_int6",		/*170*/
	"IPC_NS_mbx13",		/*171*/
	"IPC_NS_mbx14",		/*172*/
	"IPC_NS_mbx15",		/*173*/
	"IPC_NS_mbx16",		/*174*/
	"IPC_NS_mbx17",		/*175*/
	"IPC_NS_mbx18",		/*176*/
	"IPC_NS_mbx[21:19]",		/*177*/
	"IPC_NS_mbx[24:22]",		/*178*/
	"IPC_NS_mbx27",		/*179*/
	"IPC_NS_mbx28",		/*180*/
	"ipc_combo",		/*181*/
	"intr_ipc[2]",		/*182*/
	"intr_ipc[6]",		/*183*/
	"aximon_cpufast",		/*184*/
	"asp_ipc_arm",		/*185*/
	"asp_ipc_mcpu",		/*186*/
	"asp_ipc_bbe16",		/*187*/
	"asp_wd",		/*188*/
	"asp_axi_dlock",		/*189*/
	"sci0",		/*190*/
	"sci1",		/*191*/
	"socp0",		/*192*/
	"socp1",		/*193*/
	"ldrx2arm_times_int",		/*194*/
	"ldrx2arm_wakeup_int",		/*195*/
	"tdrx2arm_wakeup_int",		/*196*/
	"tdrx2arm_times_int",		/*197*/
	"g1_bbp_to_cpu_clkswitch",		/*198*/
	"g1_bbp_to_cpu_32k_wakeup",		/*199*/
	"g1_bbp_to_dsp_32k_wakeup",		/*200*/
	"g2_bbp_to_cpu_clkswitch",		/*201*/
	"g2_bbp_to_cpu_32k_wakeup",		/*202*/
	"g2_bbp_to_dsp_32k_wakeup",		/*203*/
	"w_arm_int02_wakeup",		/*204*/
	"w_arm_int03_clkswitch",		/*205*/
	"reserved",		/*206*/
	"reserved",		/*207*/
	"MDM_IPF_intr0",		/*208*/
	"MDM_IPF_intr1",		/*209*/
	"MDM_EDMAC_intr[2]",		/*210*/
	"GIC_IRQ_OUT[0]",		/*211*/
	"GIC_IRQ_OUT[1]",		/*212*/
	"GIC_IRQ_OUT[2]",		/*213*/
	"GIC_IRQ_OUT[3]",		/*214*/
	"GIC_IRQ_OUT[4]",		/*215*/
	"GIC_IRQ_OUT[5]",		/*216*/
	"GIC_IRQ_OUT[6]",		/*217*/
	"GIC_IRQ_OUT[7]",		/*218*/
	"CBBP_INT01",		/*219*/
	"NANDC",		/*220*/
	"IVP32_WATCH_DOG",		/*221*/
	"mmbuf_asc0",		/*222*/
	"mmbuf_asc1",		/*223*/
	"reserved",		/*224*/
	"reserved",		/*225*/
	"reserved",		/*226*/
	"reserved",		/*227*/
	"reserved",		/*228*/
	"reserved",		/*229*/
};

#define PMU_NAME(a, b, c, d) \
	{ .name = a, .module = b, .status = c, .status_name = d}

/* note: hisi_pmu_idx[k] must be matched with pmuregs_lookups[k],
 * otherwise the array may be out of range.
 */
struct pmu_idx hisi_pmu_idx_a[] = {
	PMU_NAME("BUCK1_LDO0_2",	"<SYS CORE PLL>",
			PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BUCK2_LDO1",		"<main sim card for hi6362(modem)>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK3_LDO2",		"<1.8V IO>",
			PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BUCK3_LDO3",		"<hi6362 avdd2(modem)>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK3_LDO4",		"<LCD&TP 1.8V IO>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK3_LDO5",		"<1.8V LDO: PHY Tsensor 1.8V HKADC>",
			PERI_EN_CLOSE, "PERI_EN_ECO"),
	PMU_NAME("BUCK3_LDO7",		"<AVDDH_ABB AVDD1P8_PLL>",
			PERI_EN_CLOSE,	"PERI_EN_CLOSE"),
	PMU_NAME("BUCK3_LDO8",		"<SOC PLL Codec Hi6402 CLASS D 1.8V>",
			SOFT_ECO, "SOFT_ECO"),
	PMU_NAME("BOOST_LDO9",		"<vdd of sd io>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO10",		"<3.2V LDO:USB PHY>",
			PERI_EN_CLOSE,	"PERI_EN_CLOSE"),/* AP soft eco*/
	PMU_NAME("BOOST_LDO11",		"<SIM0>",
			PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BOOST_LDO12",		"<SIM1>",
			PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BOOST_LDO13",		"<TCXO0+CLK_Buffer camera analog>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO14",		"<TCXO1+CLK_Buffer SWITCH VCC 2.8V>",
			AP_DIS, "AP_DIS"),
	PMU_NAME("BOOST_LDO15",		"<eMMC Flash>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO16",		"<SD>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO17",		"<LCD &TP AVDD 2.8V>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO19",		"<M_Camera Analog 2.8V>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK2_LDO20",		"<M_Camera Core>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK3_LDO21",		"<BISR Fuse>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK2_LDO22",		"<hi36362 avdd1(modem)>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO23",		"<HKADC+Aux DAC>",
			PERI_EN_CLOSE,	"PERI_EN_CLOSE"),
	PMU_NAME("BOOST_LDO24",		"<X_Sensor AVDD & IRDA>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("VSYS_LDO25",		"<Camera AFVDD Motor>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK3_LDO26",		"<DCXO_XO>",
			PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BOOST_LDO27",		"<pmu clk buffer Hi6362 AVDD3>",
			CLK_EN_CLOSE,	"CLK_EN_CLOSE"),
	PMU_NAME("BUCK3_LDO28",		"<PA STAR RF TUNER SWITCH VIO 1.8V>",
			AP_DIS,	"AP_DIS"),
	PMU_NAME("BUCK2_LDO29",		"<hi6402 1.2V dig>",
			PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BUCK1_LDO30",		"<emmc phy 0.8V Core USB PHY Core>",
			PERI_EN_CLOSE,	"PERI_EN_CLOSE"),
	PMU_NAME("VSYS_LDO31",		"<vibrator>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK2_LDO32",		"<s_camera core>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK0",		"<PERI LPDDR3 Tsensor 0.8V ABB>",
			PERI_EN_CLOSE, "PERI_EN_CLOSE"),
	PMU_NAME("BUCK1",			"<1.2V Power plane: DDR>",
			PERI_EN_ECO, "PERI_EN_ECO"),
	PMU_NAME("BUCK2",			"<1.45V Power plane>",
			PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BUCK3",			"<2.15V Power plane>",
			PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BUCK4",			"<NULL>",
			AP_DIS,			"AP_DIS"),
};

struct pmu_idx hisi_pmu_idx_d[] = {
	PMU_NAME("Buck0",	"<peri core phy core>",
			PERI_EN_CLOSE,		"PERI_EN_ECO"),
	PMU_NAME("Buck1",	"<DDRPHY IO>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	PMU_NAME("Buck2",	"<1.35V Power plane>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	PMU_NAME("BUCK3",	"<2.0V Power plane>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	PMU_NAME("LDO0",	"<sys core PLL>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	/* ccore */
	PMU_NAME("LDO1",	"<main sim for Hi6362 Analog 1>",
			PERI_EN_CLOSE,		"PERI_EN_CLOSE"),
	PMU_NAME("LDO2",	"<1.8V IO>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	/* ccore */
	PMU_NAME("LDO3",	"<RFIC0&1 AVDD2 1.85V>",
			PERI_EN_CLOSE,		"PERI_EN_CLOSE"),
	/* support gesture-->eco */
	PMU_NAME("LDO4",	"<LCD &TP 1.8V I/O >",
			AP_DIS,		"AP_DIS"),
	/* with LDO23 */
	PMU_NAME("LDO5",	"<LPDDR3 PHY Tsensor 1.8V HKADC REF>",
			PERI_EN_CLOSE,	"PERI_EN_CLOSE"),
	/* close on init of dallas */
	PMU_NAME("LDO7",	"<AVDDH_ABB>",
			PERI_EN_CLOSE,		"PERI_EN_CLOSE"),
	/* mcore: hi6402 always on */
	PMU_NAME("LDO8",	"<Codec  Hi6402 1.8V>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	PMU_NAME("LDO9",	"<SD IO>",
			PERI_EN_CLOSE,		"PERI_EN_CLOSE"),
	PMU_NAME("LDO10",	"<USB PHY3.0 RF PA BIAS>",
			PERI_EN_CLOSE,		"PERI_EN_CLOSE"),
	/* ccore */
	PMU_NAME("LDO11",	"<sim0>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	/* ccore */
	PMU_NAME("LDO12",	"<sim1>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	PMU_NAME("LDO13",	"<Camera Analog>",
			PERI_EN_CLOSE,		"PERI_EN_CLOSE"),
	/* ccore */
	PMU_NAME("LDO14",	"<RF FEM VCC 2.8V>",
			PERI_EN_CLOSE,		"PERI_EN_CLOSE"),
	PMU_NAME("LDO15",	"<eMMC Flash>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	/* SD on-->eco */
	PMU_NAME("LDO16",	"<SDR104>",
			AP_DIS,				"AP_DIS"),
	/* support gesture-->eco */
	PMU_NAME("LDO17",	"<LCD &TP AVDD>",
			AP_DIS,				"AP_DIS"),
	PMU_NAME("LDO19",	"<M_Camera Analog>",
			AP_DIS,				"AP_DIS"),
	PMU_NAME("LDO20",	"<M_Camera Core>",
			AP_DIS,				"AP_DIS"),
	PMU_NAME("LDO21",	"<BISR Fuse>",
			AP_DIS,				"AP_DIS"),
	/* ccore */
	PMU_NAME("LDO22",	"<Hi6362 Analog 1>",
			PERI_EN_CLOSE,		"PERI_EN_CLOSE"),
	/* with LDO5 */
	PMU_NAME("LDO23",	"<HKADC>",
			PERI_EN_CLOSE,		"PERI_EN_CLOSE"),
	PMU_NAME("LDO24",	"<X Sensor AVDD>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	PMU_NAME("LDO25",	"<Camera  AFVDD>",
			AP_DIS,				"AP_DIS"),
	PMU_NAME("LDO26",	"<DCXO_XO>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	/* sensor hub open buffer */
	PMU_NAME("LDO27",	"<PMU CLK Buffer Hi6362 AVDD3>",
			PERI_EN_CLOSE,		"PERI_EN_CLOSE"),
	/* ccore */
	PMU_NAME("LDO28",	"<RF MIPI VIO 1.8V>",
			PERI_EN_CLOSE,		"PERI_EN_CLOSE"),
	PMU_NAME("LDO29",	"<Hi6402 1.2v>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
	PMU_NAME("LDO31",	"<Vibrator>",
			AP_DIS,			"AP_DIS"),
	PMU_NAME("LDO32",	"<S_Camera Core>",
			AP_DIS,				"AP_DIS"),
	PMU_NAME("LDO33",	"<M&S CAM IO>",
			AP_DIS,				"AP_DIS"),
	PMU_NAME("LDO34",	"<PMU_H MICBIAS>",
			PERI_EN_ECO,		"PERI_EN_ECO"),
};

#define PMU_LOW(x, y, z) \
		{ .ucoffset = (x), .cval = (y), .cmask = (z), .old_val = 0,}
static struct pmuregs pmuregs_lookups_a[] = {
	PMU_LOW(0x5A , 0x02, 0x02),/*LDO0_2 */
	PMU_LOW(0x5C , 0x02, 0x02),/*LDO1*/
	PMU_LOW(0x5E , 0x02, 0x02),/*LDO2*/
	PMU_LOW(0x60 , 0x02, 0x02),/*LDO3*/
	PMU_LOW(0x62 , 0x02, 0x02),/*LDO4*/
	PMU_LOW(0x64 , 0x02, 0x02),/*LDO5*/
	PMU_LOW(0x66 , 0x02, 0x02),/*LDO7*/
	PMU_LOW(0x68 , 0x02, 0x02),/*LDO8*/
	PMU_LOW(0x6A , 0x02, 0x02),/*LDO9*/
	PMU_LOW(0x6C , 0x02, 0x02),/*LDO10*/
	PMU_LOW(0x6E , 0x02, 0x02),/*LDO11*/
	PMU_LOW(0x70 , 0x02, 0x02),/*LDO12*/
	PMU_LOW(0x72 , 0x02, 0x02),/*LDO13*/
	PMU_LOW(0x74 , 0x02, 0x02),/*LDO14*/
	PMU_LOW(0x76 , 0x02, 0x02),/*LDO15*/
	PMU_LOW(0x78 , 0x02, 0x02),/*LDO16*/
	PMU_LOW(0x7A , 0x02, 0x02),/*LDO17*/
	PMU_LOW(0x7C , 0x02, 0x02),/*LDO19*/
	PMU_LOW(0x7E , 0x02, 0x02),/*LDO20*/
	PMU_LOW(0x80 , 0x02, 0x02),/*LDO21*/
	PMU_LOW(0x82 , 0x02, 0x02),/*LDO22*/
	PMU_LOW(0x84 , 0x02, 0x02),/*LDO23*/
	PMU_LOW(0x86 , 0x02, 0x02),/*LDO24*/
	PMU_LOW(0x88 , 0x02, 0x02),/*LDO25*/
	PMU_LOW(0x8A , 0x02, 0x02),/*LDO26*/
	PMU_LOW(0x8C , 0x02, 0x02),/*LDO27*/
	PMU_LOW(0x8E , 0x02, 0x02),/*LDO28*/
	PMU_LOW(0x90 , 0x02, 0x02),/*LDO29*/
	PMU_LOW(0x92 , 0x02, 0x02),/*LDO30*/
	PMU_LOW(0x94 , 0x02, 0x02),/*LDO31*/
	PMU_LOW(0x96 , 0x02, 0x02),/*LDO32*/
	PMU_LOW(0x98 , 0x02, 0x02),/*BUCK0*/
	PMU_LOW(0x9A , 0x02, 0x02),/*BUCK1*/
	PMU_LOW(0x9C , 0x02, 0x02),/*BUCK2*/
	PMU_LOW(0x9E , 0x02, 0x02),/*BUCK3*/
	PMU_LOW(0xA0 , 0x02, 0x02),/*BUCK4*/

};

static struct pmuregs pmuregs_lookups_d[] = {
	PMU_LOW(0x10 , 0x01 , 0x01),/*BUCK0*/
	PMU_LOW(0x11 , 0x01 , 0x01),/*BUCK1*/
	PMU_LOW(0x12 , 0x01 , 0x01),/*BUCK2*/
	PMU_LOW(0x13 , 0x01 , 0x01),/*BUCK3*/
	/*PMU_LOW(0x14 , 0x01 , 0x01),LDO0_1*/
	PMU_LOW(0x15 , 0x01 , 0x01),/*LDO0_2*/
	PMU_LOW(0x16 , 0x01 , 0x01),/*LDO1*/
	PMU_LOW(0x17 , 0x01 , 0x01),/*LDO2*/
	PMU_LOW(0x18 , 0x01 , 0x01),/*LDO3*/
	PMU_LOW(0x19 , 0x01 , 0x01),/*LDO4*/
	PMU_LOW(0x1a , 0x01 , 0x01),/*LDO5*/
	PMU_LOW(0x1b , 0x01 , 0x01),/*LDO7*/
	PMU_LOW(0x1c , 0x01 , 0x01),/*LDO8*/
	PMU_LOW(0x1d , 0x01 , 0x01),/*LDO9*/
	PMU_LOW(0x1e , 0x01 , 0x01),/*LDO10*/
	PMU_LOW(0x1f , 0x01 , 0x01),/*LDO11*/
	PMU_LOW(0x20 , 0x01 , 0x01),/*LDO12*/
	PMU_LOW(0x21 , 0x01 , 0x01),/*LDO13*/
	PMU_LOW(0x22 , 0x01 , 0x01),/*LDO14*/
	PMU_LOW(0x23 , 0x01 , 0x01),/*LDO15*/
	PMU_LOW(0x24 , 0x01 , 0x01),/*LDO16*/
	PMU_LOW(0x25 , 0x01 , 0x01),/*LDO17*/
	PMU_LOW(0x26 , 0x01 , 0x01),/*LDO19*/
	PMU_LOW(0x27 , 0x01 , 0x01),/*LDO20*/
	PMU_LOW(0x28 , 0x01 , 0x01),/*LDO21*/
	PMU_LOW(0x29 , 0x01 , 0x01),/*LDO22*/
	PMU_LOW(0x2a , 0x01 , 0x01),/*LDO23*/
	PMU_LOW(0x2b , 0x01 , 0x01),/*LDO24*/
	PMU_LOW(0x2c , 0x01 , 0x01),/*LDO25*/
	PMU_LOW(0x2d , 0x01 , 0x01),/*LDO26*/
	PMU_LOW(0x2e , 0x01 , 0x01),/*LDO27*/
	PMU_LOW(0x2f , 0x01 , 0x01),/*LDO28*/
	PMU_LOW(0x30 , 0x01 , 0x01),/*LDO29*/
	PMU_LOW(0x31 , 0x01 , 0x01),/*LDO31*/
	PMU_LOW(0x32 , 0x01 , 0x01),/*LDO32*/
	PMU_LOW(0x33 , 0x01 , 0x01),/*LDO33*/
	PMU_LOW(0x34 , 0x01 , 0x01),/*LDO34*/
};

#define IPC_COMBO_AP		181

static unsigned g_usavedcfg;
static int g_suspended;
extern int get_console_index(void);

#include <linux/wakelock.h>
static struct wake_lock lowpm_wake_lock;

#define IO_GROUP_NUM	(30)
/* struct sysreg_bases to hold the base address of some system registers.*/
struct sysreg_base_addr {
	void __iomem *uart_base;
	void __iomem *pctrl_base;
	void __iomem *pmctrl_base;
	void __iomem *sysctrl_base;
	void __iomem *ioc_base[4];
	void __iomem *gpio_base[IO_GROUP_NUM];
	void __iomem *crg_base;
	void __iomem *pmic_base;
	void __iomem *reserved_base;
	void __iomem *nsipc_base;
};

struct sysreg_base_addr sysreg_base;

struct lp_clk {
	unsigned int reg_base;
	unsigned int reg_off;
	unsigned int bit_idx;
	const char *clk_name;
	unsigned int status;
};

struct sys_reg {
	unsigned int reg_base;
	unsigned int reg_off;
	const char *reg_name;
};

#define IO_BUFFER_LENGTH		40

unsigned int g_boardid;

static int map_io_regs(void)
{
	int i = 0;
	int ret = 0;
	struct device_node *np = NULL;
	char *io_buffer = NULL;
	unsigned int boardid[4] = {0};

	io_buffer = kmalloc(IO_BUFFER_LENGTH * sizeof(char), GFP_KERNEL);
	if (NULL == io_buffer) {
		pr_err("%s: io buffer kmalloc fail.\n", __func__);
		goto err;
	}

	ret = of_property_read_u32_array(of_find_node_by_path("/"),
			"hisi,boardid", &boardid[0], 4);
	if (ret) {
		pr_err("%s: not find boardid.\n", __func__);
		goto err_free_buffer;
	}

	g_boardid = boardid[0] * 1000 + boardid[1] * 100
				+ boardid[2] * 10 + boardid[3];

	pr_info("%s: boardid %x\n", __func__, g_boardid);

	for (i = 0; i < IO_GROUP_NUM; i++) {
		memset(io_buffer, 0, IO_BUFFER_LENGTH * sizeof(char));
		snprintf(io_buffer, IO_BUFFER_LENGTH * sizeof(char),
				"arm,primecell%d", i);
		np = of_find_compatible_node(NULL, NULL, io_buffer);
		sysreg_base.gpio_base[i] = of_iomap(np, 0);
		pr_debug("%s: sysreg_base.gpio_base[%d] %p\n",
				__func__, i, sysreg_base.gpio_base[i]);
		if (!sysreg_base.gpio_base[i])
			pr_err("%s: gpio%d not find.\n", __func__, i);
	}

	for (i = 0; i < 4; i++) {
		memset(io_buffer, 0, IO_BUFFER_LENGTH * sizeof(char));
		snprintf(io_buffer, IO_BUFFER_LENGTH * sizeof(char),
				"pinctrl-single%d", i);
		np = of_find_compatible_node(NULL, NULL, io_buffer);
		sysreg_base.ioc_base[i] = of_iomap(np, 0);
		pr_debug("%s: sysreg_base.ioc_base[%d] %p\n",
				__func__, i, sysreg_base.ioc_base[i]);
		if (!sysreg_base.ioc_base[i])
			pr_err("%s: pinctrl-single%d not find.\n", __func__, i);
	}
	kfree(io_buffer);
	io_buffer = NULL;
	return 0;

err_free_buffer:
	kfree(io_buffer);
err:
	pr_err("hisi_lpregs:map_io_regs failed.\n");
	return -ENODEV;
}

/*map system registers*/
static int map_sysregs(void)
{
	unsigned int uart_idx = 0;
	struct device_node *np = NULL;

	uart_idx = get_console_index();
	switch (uart_idx) {
	case 0:
		np = of_find_compatible_node(NULL, NULL, "arm,pl011");
		if (!np)
			pr_err("%s: dts[%s] node not found\n",
					__func__, "arm,pl011");
		break;
	case 6:
		/* FIXME */
		np = of_find_compatible_node(NULL, NULL,
						"hisilicon,lowpm_func");
		if (!np)
			pr_err("%s: dts[%s] node not found\n",
					__func__, "hisilicon,lowpm_func");
		break;
	default:
		break;
	}

	if (NULL != np) {
		sysreg_base.uart_base = of_iomap(np, 0);
		pr_debug("%s: uart_base:%p\n", __func__, sysreg_base.uart_base);
		if (!sysreg_base.uart_base)
			pr_err("%s: uart_base of iomap fail!\n", __func__);
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,hi3650");
	if (!np)
		pr_err("%s: not plat hi3650.\n", __func__);
	else
		g_plat_flag = PLAT_A;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,hi6250");
	if (!np)
		pr_err("%s: not plat hi6250.\n", __func__);
	else
		g_plat_flag = PLAT_D;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (!np)
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,sysctrl");
	sysreg_base.sysctrl_base = of_iomap(np, 0);
	pr_debug("%s: sysctrl_base:%p\n", __func__, sysreg_base.sysctrl_base);
	if (!sysreg_base.sysctrl_base)
		pr_err("%s: sysctrl_base of iomap fail!\n", __func__);

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pctrl");
	if (!np)
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,pctrl");
	sysreg_base.pctrl_base = of_iomap(np, 0);
	pr_debug("%s: pctrl_base:%p\n", __func__, sysreg_base.pctrl_base);
	if (!sysreg_base.pctrl_base)
		pr_err("%s: pctrl_base of iomap fail!\n", __func__);

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pmctrl");
	if (!np)
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,pmctrl");
	sysreg_base.pmctrl_base = of_iomap(np, 0);
	pr_debug("%s: pmctrl_base:%p\n", __func__, sysreg_base.pmctrl_base);
	if (!sysreg_base.pmctrl_base)
		pr_err("%s: pmctrl_base of iomap fail!\n", __func__);

	np = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");
	if (!np)
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,crgctrl");
	sysreg_base.crg_base = of_iomap(np, 0);
	pr_debug("%s: crg_base:%p\n", __func__, sysreg_base.crg_base);
	if (!sysreg_base.crg_base)
		pr_err("%s: crg_base of iomap fail!\n", __func__);

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pmu");
	if (!np)
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,pmu");
	sysreg_base.pmic_base = of_iomap(np, 0);
	pr_debug("%s: pmic_base:%p\n", __func__, sysreg_base.pmic_base);
	if (!sysreg_base.pmic_base)
		pr_err("%s: pmic_base of iomap fail!\n", __func__);

	np = of_find_compatible_node(NULL, NULL, "hisilicon,HiIPCV230");
	if (!np)
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,HiIPCV230");
	sysreg_base.nsipc_base = of_iomap(np, 0);
	pr_debug("%s: nsipc_base:%p\n", __func__, sysreg_base.nsipc_base);
	if (!sysreg_base.nsipc_base)
		pr_err("%s: nsipc_base of iomap fail!\n", __func__);

	return 0;
}

/****************************************
 *function: debuguart_reinit
 *description:
 *  reinit debug uart.
 *****************************************/
void debuguart_reinit(void)
{
	unsigned int uart_idx = 0;
	unsigned int uregv = 0;

	if ((console_suspend_enabled == 1) || (sysreg_base.uart_base == NULL))
		return;

	uart_idx = get_console_index();
	if (uart_idx == 6) {
		/*Config necessary IOMG configuration*/
		writel(IOC_UART6_VAL, (sysreg_base.ioc_base + IOMG_066_OFFSET));
		writel(IOC_UART6_VAL, (sysreg_base.ioc_base + IOMG_067_OFFSET));
		/*disable clk*/
		uregv = readl(sysreg_base.sysctrl_base + REG_SCLPM3CLKEN_OFFSET)
						& (~BIT_CLK_UART_SHIFT);
		writel(uregv,
			(sysreg_base.sysctrl_base + REG_SCLPM3CLKEN_OFFSET));
		/*enable clk*/
		uregv = readl(sysreg_base.sysctrl_base + REG_SCLPM3CLKEN_OFFSET)
						| (BIT_CLK_UART_SHIFT);
		writel(uregv,
			(sysreg_base.sysctrl_base + REG_SCLPM3CLKEN_OFFSET));
		/*reset undo*/
		writel(BIT_RST_UART_SHIFT,
			(sysreg_base.sysctrl_base + REG_SCLPM3RSTEN_OFFSET));
		writel(BIT_RST_UART_SHIFT,
			(sysreg_base.sysctrl_base + REG_SCLPM3RSTDIS_OFFSET));
	} else if (uart_idx == 0) {
		/* Config necessary IOMG configuration */
		writel(IOC_UART0_VAL, (sysreg_base.ioc_base + IOMG_030_OFFSET));
		writel(IOC_UART0_VAL, (sysreg_base.ioc_base + IOMG_031_OFFSET));

		uregv = (1 << (uart_idx + BIT_UART0_SHIFT));
		writel(uregv, (sysreg_base.crg_base + REG_PERDIS2_OFFSET));
		/*@ enable clk*/
		writel(uregv, (sysreg_base.crg_base + REG_PEREN2_OFFSET));

		/*reset undo*/
		writel(uregv, (sysreg_base.crg_base + REG_PERRSTEN2_OFFSET));
		writel(uregv, (sysreg_base.crg_base + REG_PERRSTDIS2_OFFSET));
	} else {
		return;
	}

	/*@;disable recieve and send*/
	uregv = 0x0;
	writel(uregv, (sysreg_base.uart_base + 0x30));

	/*@;enable FIFO*/
	uregv = 0x70;
	writel(uregv, (sysreg_base.uart_base + 0x2c));

	/*@;set baudrate*/
	uregv = 0xA;
	writel(uregv, (sysreg_base.uart_base + 0x24));

	uregv = 0x1B;
	writel(uregv, (sysreg_base.uart_base + 0x28));

	/*@;clear buffer*/
	uregv = readl(sysreg_base.uart_base);

	/*@;enable FIFO*/
	uregv = 0x70;
	writel(uregv, (sysreg_base.uart_base + 0x2C));

	/*@;set FIFO depth*/
	uregv = 0x10A;
	writel(uregv, (sysreg_base.uart_base + 0x34));

	uregv = 0x50;
	writel(uregv, (sysreg_base.uart_base + 0x38));

	/*@;enable uart trans*/
	uregv = 0x301;
	writel(uregv, (sysreg_base.uart_base + 0x30));
}


unsigned int proc_mask_to_id(unsigned int mask)
{
	unsigned int i = 0;

	for (i = 0; i < IPC_PROCESSOR_MAX; i++) {
		if (mask & BIT(i))
			break;
	}

	return i;
}

void ipc_mbx_irq_show(struct seq_file *s, void __iomem *base, unsigned int mbx)
{
	unsigned int ipc_source = 0;
	unsigned int ipc_dest = 0;
	unsigned int src_id = 0;
	unsigned int dest_id = 0;
	unsigned int i = 0;

	ipc_source = readl(base + IPC_MBX_SOURCE_OFFSET(mbx));
	src_id = proc_mask_to_id(ipc_source);
	if (src_id < AP_IPC_PROC_MAX) {
		/*is ack irq*/
		ipc_dest = readl(base + IPC_MBX_DSTATUS_OFFSET(mbx));
		dest_id = proc_mask_to_id(ipc_dest);
		if (dest_id < IPC_PROCESSOR_MAX) {
			LOWPM_MSG(s, "SR:mailbox%d: ack from %s\n", mbx, processor_name[dest_id]);
		} else {
			LOWPM_MSG(s, "SR:mailbox%d: ack from unknown\n", mbx);
		}
	} else if (src_id < IPC_PROCESSOR_MAX) {
		/*is receive irq*/
		LOWPM_MSG(s, "SR:mailbox%d: send by %s\n",
				mbx, processor_name[src_id]);
	} else {
		LOWPM_MSG(s, "SR:mailbox%d: src id unknown\n", mbx);
	}


	/*if ((g_usavedcfg & DEBG_SUSPEND_IPC_DATA_SHOW) > 0) {*/
	for (i = 0; i < IPC_MBXDATA_MAX; i++) {
		LOWPM_MSG(s, "SR:[MBXDATA%d]:0x%x\n",
				i, readl(base + IPC_MBXDATA_OFFSET(mbx, i)));
	}
}

void combo_ipc_irq_show(struct seq_file *s, unsigned int nsipc_state)
{
	unsigned int mbx = 0;

	/*ns ipc irq detail show*/
	LOWPM_MSG(s, "SR:nsipc irq state:0x%x\n", nsipc_state);
	if (sysreg_base.nsipc_base == NULL) {
		LOWPM_MSG(s, "SR:nsipc base is NULL\n");
		return;
	}
	for (mbx = 0; mbx <= NSIPC_MAILBOX_MAX; mbx++) {
		if ((nsipc_state & BIT(mbx)) > 0)
			ipc_mbx_irq_show(s, sysreg_base.nsipc_base, mbx);
	}

}

/****************************************
 *function: pm_status_show
 *description:
 *  show pm status.
 *****************************************/
void pm_status_show(struct seq_file *s)
{
	unsigned int wake_status = 0;
	unsigned int wake_irq = 0;
	unsigned int wake_irq1 = 0;
	unsigned int bit_shift = 0;
	unsigned int i = 0;
	unsigned int ap_irq = 0;

	if (!sysreg_base.reserved_base) {
#ifdef CONFIG_HISI_LPMCU_BB
		if (M3_RDR_SYS_CONTEXT_BASE_ADDR)
			sysreg_base.reserved_base = M3_RDR_SYS_CONTEXT_RUNTIME_VAR_ADDR;
		else
			return;
#else
		return;
#endif
	}

	wake_status = readb(sysreg_base.reserved_base + PM_WAKE_STATUS_OFFSET);
	LOWPM_MSG(s,
		"SR:wakelock status, ap:%d, modem:%d, hifi:%d, iomcu:%d, gps:%d, hotplug:%d,%d.\n",
		(wake_status & WAKE_STATUS_AP_MASK) ? 1 : 0,
		(wake_status & WAKE_STATUS_MODEM_MASK) ? 1 : 0,
		(wake_status & WAKE_STATUS_HIFI_MASK) ? 1 : 0,
		(wake_status & WAKE_STATUS_IOMCU_MASK) ? 1 : 0,
		(wake_status & WAKE_STATUS_GPS_MASK) ? 1 : 0,
		(wake_status & WAKE_STATUS_HOTPLUG_MASK(0)) ? 1 : 0,
		(wake_status & WAKE_STATUS_HOTPLUG_MASK(1)) ? 1 : 0);
	LOWPM_MSG(s, "SR:system sleeped %u times.\n",
		readl(sysreg_base.reserved_base + PM_SYS_SLEEP_CNT_OFFSET));
	LOWPM_MSG(s,
		"SR:wake times, system:%u, woken up by ap:%u, modem:%u, hifi:%u, iomcu:%u, lpm3:%u.\n",
		readl(sysreg_base.reserved_base + PM_SYS_WAKE_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_AP_WAKE_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_MODEM_WAKE_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_HIFI_WAKE_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_IOMCU_WAKE_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_LPM3_WAKE_CNT_OFFSET));
	LOWPM_MSG(s,
		"SR:sr times of sub system, ap:s-%u, r-%u, modem:s-%u, r-%u, hifi:s-%u, r-%u, iomcu:s-%u, r-%u.\n",
		readl(sysreg_base.reserved_base + PM_AP_SUSPEND_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_AP_RESUME_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_MODEM_SUSPEND_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_MODEM_RESUME_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_HIFI_SUSPEND_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_HIFI_RESUME_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_IOMCU_SUSPEND_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_IOMCU_RESUME_CNT_OFFSET));

	LOWPM_MSG(s, "SR:SCINT_STAT:0x%x.\n",
			readl(sysreg_base.sysctrl_base + SCINT_STAT_OFFSET));
	LOWPM_MSG(s, "SR:SCINT_STAT1:0x%x.\n",
			readl(sysreg_base.sysctrl_base + SCINT_STAT1_OFFSET));

	wake_irq = readl(sysreg_base.reserved_base + PM_WAKE_IRQ_OFFSET);
	wake_irq1 = readl(sysreg_base.reserved_base + PM_WAKE_IRQ1_OFFSET);
	for (i = 0; i < WAKE_IRQ_NUM_MAX; i++) {
		bit_shift = (1 << i);
		if ((wake_irq & AP_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST DEEPSLEEP WAKE BIT: %d(AP)\n", i);

		if ((wake_irq & IOMCU_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST DEEPSLEEP WAKE BIT: %d(IOMCU)\n", i);

		if ((wake_irq & MODEM_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST DEEPSLEEP WAKE BIT: %d(MODEM)\n", i);

		if ((wake_irq1 & MODEM_DRX_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST DEEPSLEEP WAKE DRX_BIT: %d(MODEM)\n", i);

		if ((wake_irq & HIFI_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST DEEPSLEEP WAKE BIT: %d(HIFI)\n", i);
	}

	ap_irq = readl(sysreg_base.reserved_base + PM_AP_WAKE_IRQ_OFFSET);
	if (LPM3_IRQ_MAX > ap_irq) {
		LOWPM_MSG(s, "SR:AP WAKE IRQ(LPM3 NVIC): %d (%s)\n",
				ap_irq, lpm3_irq_name[ap_irq]);
	} else {
		LOWPM_MSG(s,
			"SR:AP WAKE IRQ(LPM3 NVIC): %d (no exist)\n", ap_irq);
	}
	if (IPC_COMBO_AP == ap_irq)
		combo_ipc_irq_show(s,
			readl(sysreg_base.reserved_base + PM_AP_NSIPC_IRQ_OFFSET));

	LOWPM_MSG(s, "light sleep 0x%x times,resume 0x%x times.\n",
		readl(sysreg_base.reserved_base + IDLE_SLEEP_CNT_OFFSET),
		readl(sysreg_base.reserved_base + IDLE_RESUME_CNT_OFFSET));
}

void set_wakelock(int iflag)
{
	if ((1 == iflag) && (0 == wake_lock_active(&lowpm_wake_lock)))
		wake_lock(&lowpm_wake_lock);
	else if ((0 == iflag) && (0 != wake_lock_active(&lowpm_wake_lock)))
		wake_unlock(&lowpm_wake_lock);
}

#define GPIO_DIR(x)		((x) + 0x400)
#define GPIO_DATA(x, y)		((x) + (1 << (2 + y)))
#define GPIO_BIT(x, y)		((x) << (y))
#define GPIO_IS_SET(x, y)	(((x) >> (y)) & 0x1)

/* check all io status */
void dbg_io_status_show(void)
{
	int i = 0;
	int gpio_id = 0;
	int value = 0;
	int	data = 0;
	unsigned int len = 0;
	void __iomem *addr, *addr1;
	struct iocfg_lp *hisi_iocfg_lookups = NULL;

	if (!(g_usavedcfg & DEBG_SUSPEND_IO_SHOW))
		return;

#ifdef CONFIG_HISI_AUTO_GPIO
	/* get iocfg table */
	for (i = 0; i < sizeof(boardid_tables) / sizeof(boardid_tables[0]); i++) {
		if (g_boardid == boardid_tables[i].boardid) {
			hisi_iocfg_lookups = boardid_tables[i].iocfg;
			break;
		}
	}

	if (i == sizeof(boardid_tables) / sizeof(boardid_tables[0])) {
		pr_err("%s: not find iocfg table.\n", __func__);
		return;
	}
#endif
	hisi_iocfg_lookups = boardid_tables[0].iocfg;

	if (NULL == hisi_iocfg_lookups) {
		pr_err("%s: hisi_iocfg_lookups is null\n", __func__);
		return;
	}

	/* calc hisi_iocfg_lookups[] length */
	for (i = 0; hisi_iocfg_lookups[i].iomg_offset != CFG_END; i++)
		len = i;

	printk("io list length is %d\n", len);
	for (i = 0; i <= len; i++) {
		gpio_id = ((hisi_iocfg_lookups[i].gpio_group_id << 3)
					+ hisi_iocfg_lookups[i].ugpio_bit);

		printk("gpio - %d  gpio_logic - %s\t",
				gpio_id, hisi_iocfg_lookups[i].gpio_logic);

		/* show iomg register's value */
		if (hisi_iocfg_lookups[i].iomg_offset != -1) {
			if (gpio_id <= 164)
				addr = sysreg_base.ioc_base[0] + hisi_iocfg_lookups[i].iomg_offset;
			else
				addr = sysreg_base.ioc_base[1] + hisi_iocfg_lookups[i].iomg_offset;

			value = readl(addr);
			printk("iomg = Func-%d", value);
			if (FUNC1 == value)
				printk("(%s)", hisi_iocfg_lookups[i].gpio_func1);
			if (FUNC2 == value)
				printk("(%s)", hisi_iocfg_lookups[i].gpio_func2);
			if (FUNC3 == value)
				printk("(%s)", hisi_iocfg_lookups[i].gpio_func3);

			if (value != hisi_iocfg_lookups[i].iomg_val) {
				printk(" -E [Func-%d]", hisi_iocfg_lookups[i].iomg_val);
				if (FUNC1 == hisi_iocfg_lookups[i].iomg_val)
					printk("(%s)", hisi_iocfg_lookups[i].gpio_func1);
				if (FUNC2 == hisi_iocfg_lookups[i].iomg_val)
					printk("(%s)", hisi_iocfg_lookups[i].gpio_func2);
				if (FUNC3 == hisi_iocfg_lookups[i].iomg_val)
					printk("(%s)", hisi_iocfg_lookups[i].gpio_func3);
			} else {
				printk("             ");
			}
			printk("\t");
		} else {
			printk("iomg = Null               \t");
		}

		/* show iocg register */
		if (gpio_id <= 164)
			addr = sysreg_base.ioc_base[2] + hisi_iocfg_lookups[i].iocg_offset;
		else
			addr = sysreg_base.ioc_base[3] + hisi_iocfg_lookups[i].iocg_offset;

		value = readl(addr);
		printk("[0x%x]iocg = %s", value, pulltype[value&0x3]);

		if ((value != hisi_iocfg_lookups[i].iocg_val) &&
				(hisi_iocfg_lookups[i].iocg_val != -1)) {
			printk(" -E [%s]", pulltype[hisi_iocfg_lookups[i].iocg_val]);
		} else {
			printk("        ");
		}
		printk("\t");

		/* if this is gpio pin*/
		if (hisi_iocfg_lookups[i].iomg_val == FUNC0) {
			addr = GPIO_DIR(sysreg_base.gpio_base[hisi_iocfg_lookups[i].gpio_group_id]);
			addr1 = GPIO_DATA(sysreg_base.gpio_base[hisi_iocfg_lookups[i].gpio_group_id], hisi_iocfg_lookups[i].ugpio_bit);

			value = GPIO_IS_SET(readl(addr), hisi_iocfg_lookups[i].ugpio_bit);
			data = GPIO_IS_SET(readl(addr1), hisi_iocfg_lookups[i].ugpio_bit);
			printk("[0x%x 0x%x]gpio - %s", value, data, value ? "O" : "I ");

			if (value)
				printk("%s", data ? "H" : "L");

			if (value != hisi_iocfg_lookups[i].gpio_dir) {
				printk("     -E [%s", hisi_iocfg_lookups[i].gpio_dir ? "O" : "I");
				if (hisi_iocfg_lookups[i].gpio_dir && (data != hisi_iocfg_lookups[i].gpio_val))
					printk("%s", hisi_iocfg_lookups[i].gpio_val ? "H" : "L");
				printk("]");
			}

			printk("\n");
		} else {
			printk("\n");
		}

	}
}

/*****************************************************************
 * function:    dbg_pmu_status_show
 * description:
 *  show the pmu status.
 ******************************************************************/
void dbg_pmu_status_show(void)
{
	unsigned int i = 0;
	unsigned int k = 0;
	unsigned int uregv;
	unsigned int pmu_reg_end =
		(g_plat_flag == PLAT_A) ? PMU_CTRL_END_A : PMU_CTRL_END_D;
	struct pmu_idx *hisi_pmu_idx_temp =
		(g_plat_flag == PLAT_A) ? hisi_pmu_idx_a : hisi_pmu_idx_d;
	struct pmuregs *pmuregs_lookups_temp =
		(g_plat_flag == PLAT_A) ? pmuregs_lookups_a : pmuregs_lookups_d;

	if (!(g_usavedcfg & DEBG_SUSPEND_PMU_SHOW))
		return;
	printk("[%s] %d enter.\n", __func__, __LINE__);
	printk("PMU_CTRL register value list:\n");

	for (i = 0x0; i <= pmu_reg_end; i++) {
		uregv = readl(PMUSSI_REG(i));
		printk("PMU_CTRL 0x%02X=0x%02X", i, uregv);
		printk("\t");

		/* NOTE!! pmuregs_lookups[k] must be matched with hisi_pmu_idx[k],
		 * otherwise the array may be out of range.
		 */
		if (i == pmuregs_lookups_temp[k].ucoffset) {
			printk("[%s]", hisi_pmu_idx_temp[k].name);
			if ((uregv & pmuregs_lookups_temp[k].cmask) == pmuregs_lookups_temp[k].cval)
				printk("enabled  %s\t",
						(hisi_pmu_idx_temp[k].status & AP_DIS) ? "-E" : "");
			printk("[%s]owner:%s",
					hisi_pmu_idx_temp[k].status_name, hisi_pmu_idx_temp[k].module);
			k++;
		}

		printk("\n");
	}

	printk("[%s] %d leave.\n", __func__, __LINE__);
}


#define NULL_CLOSE	0
#define AP_CLOSE	1
#define LPM3_CLOSE	2
#define	AP_ON		3
#define AO_ON		4
#define ON_OFF		5
#define MODEM_ON	6

#define LP_CLK(_base, _offset, _bit, _clk_name, _status) \
{                               \
	.reg_base = _base, \
	.reg_off = _offset,  \
	.bit_idx    = _bit, \
	.clk_name = _clk_name,  \
	.status = _status,	\
}

static struct lp_clk clk_lookups_a[] = {
	LP_CLK(SCTRLBASE, 0x038, 31, "clk_ppll0_sscg", NULL_CLOSE),
	LP_CLK(SCTRLBASE, 0x038, 30, "pclk_efusec", AP_ON),
	LP_CLK(SCTRLBASE, 0x038, 29, "clk_aobus", AP_ON),
	LP_CLK(SCTRLBASE, 0x038, 28, "clk_bbpdrx", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x038, 27, "clk_asp_tcxo", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x038, 26, "clk_asp_subsys", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x038, 25, "clk_memrep", AO_ON),
	LP_CLK(SCTRLBASE, 0x038, 24, "clk_sci1", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x038, 23, "clk_sci0", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x038, 22, "pclk_ao_gpio5", NULL_CLOSE),
	LP_CLK(SCTRLBASE, 0x038, 21, "pclk_ao_gpio4", AP_ON),
	LP_CLK(SCTRLBASE, 0x038, 20, "clk_syscnt", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x038, 19, "pclk_syscnt", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x038, 18, "clk_jtag_auth", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x038, 17, "clk_out1", AP_CLOSE),
	LP_CLK(SCTRLBASE, 0x038, 16, "clk_out0", AP_CLOSE),
	LP_CLK(SCTRLBASE, 0x038, 15, "pclk_ao_ioc", AO_ON),
	LP_CLK(SCTRLBASE, 0x038, 14, "pclk_ao_gpio3", AO_ON),
	LP_CLK(SCTRLBASE, 0x038, 13, "pclk_ao_gpio2", AO_ON),
	LP_CLK(SCTRLBASE, 0x038, 12, "pclk_ao_gpio1", AO_ON),
	LP_CLK(SCTRLBASE, 0x038, 11, "pclk_ao_gpio0", AO_ON),
	LP_CLK(SCTRLBASE, 0x038, 10, "clk_timer3", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x038,  9,  "pclk_timer3", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x038,  8,  "clk_timer2", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x038,  7,  "pclk_timer2", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x038,  6,  "clk_timer1", AP_ON),
	LP_CLK(SCTRLBASE, 0x038,  5,  "pclk_timer1", AP_ON),
	LP_CLK(SCTRLBASE, 0x038,  4,  "clk_timer0", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x038,  3,  "pclk_timer0", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x038,  2,  "pclk_rtc1", AP_ON),/* secureos */
	LP_CLK(SCTRLBASE, 0x038,  1,  "pclk_rtc", AP_ON),
	LP_CLK(SCTRLBASE, 0x038,  0,  "clk_ref_crc", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  24,  "clk_mmbuf_dss", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  23,  "pclk_mmbuf", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  22,  "aclk_mmbuf", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  20,  "timerclk_refh", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  19,  "clk_timer8", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  18,  "pclk_timer8", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  17,  "clk_timer7", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  16,  "pclk_timer7", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  15,  "clk_timer6", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  14,  "pclk_timer6", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  13,  "clk_timer5", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  12,  "pclk_timer5", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  11,  "clk_timer4", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  10,  "pclk_timer4", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  8,  "aclk_asc", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  6,  "clk_noc_aobus2mmbuf", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  5,  "clk_aobus_noc", AP_ON),
	LP_CLK(SCTRLBASE, 0x048,  4,  "clk_bbpdrx_oth", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x048,  3,  "clk_asp_cfg", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x048,  2,  "clk_asp_h2p", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x048,  1,  "clk_asp_x2p", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x048,  0,  "clk_asp_dw_axi", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x108, 7,  "pclkgt_mmbuf", AP_ON),
	LP_CLK(SCTRLBASE, 0x108, 6,  "pll_clkgt_mmbuf", AP_ON),
	LP_CLK(SCTRLBASE, 0x108, 5,  "sclkgt_tp", AP_ON),
	LP_CLK(SCTRLBASE, 0x108, 4,  "clkgt_asp_hclk", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x108, 3,  "clkgt_aobus", AO_ON),
	LP_CLK(SCTRLBASE, 0x108, 2,  "clkgt_sci", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x108, 1,  "clkgt_hifidsp", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x108, 0,  "clkgt_asp_subsys", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x008, 31,  "clk_aomm", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 30,  "hclk_sd", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 29,  "clk_ddrphy_d", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 26,  "clk_dbgsechsic2sysbus", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x008, 25,  "clk_dbgsechsicbus", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x008, 24,  "clk_hclk_memrep", AP_ON),
	LP_CLK(CRGBASE, 0x008, 23,  "clk_dma2cfgbus", AO_ON),
	LP_CLK(CRGBASE, 0x008, 22,  "clk_dmabus", AO_ON),
	LP_CLK(CRGBASE, 0x008, 21,  "hclk_sdio1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 20,  "clk_lpm32cfgbus", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 19,  "hclk_sdio0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 18,  "clk_mmc0_peribus", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 17,  "clk_mmc0peri2sysbus", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 16,  "hclk_emmc1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 15,  "clk_mmc1_peribus", AP_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x008, 14,  "clk_mmc1peri2sysbus", AP_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x008, 13,  "hclk_emmc0", AP_CLOSE),/* FIXME */
	/*LP_CLK(CRGBASE, 0x008, 12,  "clk_vivobus2ddrc", NULL_CLOSE),*/
	LP_CLK(CRGBASE, 0x008, 11,  "clk_sys2cfgbus", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x008, 10,  "clk_cfgbus", AO_ON),
	LP_CLK(CRGBASE, 0x008,  9,  "clk_sysbus", AO_ON),
	LP_CLK(CRGBASE, 0x008,  6,  "clk_vcodecbus", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008,  5,  "clk_vcodeccfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008,  4,  "clk_ddrphy_ref", AO_ON),
	LP_CLK(CRGBASE, 0x008,  2,  "clk_ddrc", AO_ON),
	LP_CLK(CRGBASE, 0x008,  1,  "clk_ddrbyp_ckp0", AO_ON),
	LP_CLK(CRGBASE, 0x008,  0,  "clk_ddrphy_b", AO_ON),
	LP_CLK(CRGBASE, 0x018, 29, "clk_socp_mcpu", AO_ON),
	LP_CLK(CRGBASE, 0x018, 28, "clk_socp_acpu", AO_ON),
	LP_CLK(CRGBASE, 0x018, 27, "clk_djtag", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 26, "clk_socp_lpm3", AP_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x018, 25, "pclk_timer12", MODEM_ON),
	LP_CLK(CRGBASE, 0x018, 24, "pclk_timer11", MODEM_ON),/* modem and secureos */
	LP_CLK(CRGBASE, 0x018, 23, "pclk_timer10", AP_ON),
	LP_CLK(CRGBASE, 0x018, 22, "pclk_timer9", AP_ON),
	LP_CLK(CRGBASE, 0x018, 21, "pclk_gpio21", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 20, "pclk_gpio20", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 19, "pclk_gpio19", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 18, "pclk_gpio18", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 17, "pclk_gpio17", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 16,  "pclk_gpio16", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 15,  "pclk_gpio15", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 14,  "pclk_gpio14", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 13,  "pclk_gpio13", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 12,  "pclk_gpio12", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 11,  "pclk_gpio11", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 10,  "pclk_gpio10", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  9,  "pclk_gpio9", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  8,  "pclk_gpio8", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  7,  "pclk_gpio7", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  6,  "pclk_gpio6", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  5,  "pclk_gpio5", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  4,  "pclk_gpio4", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  3,  "pclk_gpio3", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  2,  "pclk_gpio2", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  1,  "pclk_gpio1", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  0,  "pclk_gpio0", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x028, 31,  "pclk_pctrl", AO_ON),
	LP_CLK(CRGBASE, 0x028, 27,  "clk_i2c4", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x028, 26,  "clk_codecssi", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028, 25,  "pclk_ioc", AO_ON),
	LP_CLK(CRGBASE, 0x028, 24,  "clk_hkadcssi", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x028, 23,  "clk_gic", AP_ON),
	LP_CLK(CRGBASE, 0x028, 22,  "clk_adb_mst_a57", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028, 21,  "clk_adb_mst_a53", AP_CLOSE),/* FIXME */
	LP_CLK(CRGBASE, 0x028, 20,  "pclk_ipc_mdm", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028, 18,  "pclk_tzpc", AP_ON),
	LP_CLK(CRGBASE, 0x028, 17,  "pclk_wd1", AP_ON),
	LP_CLK(CRGBASE, 0x028, 16,  "pclk_wd0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028, 15,  "clk_uart5", MODEM_ON),
	LP_CLK(CRGBASE, 0x028, 14,  "clk_uart4", ON_OFF),/* FIXME */
	LP_CLK(CRGBASE, 0x028, 12,  "clk_uart2", ON_OFF),/* FIXME */
	LP_CLK(CRGBASE, 0x028, 11,  "clk_uart1", ON_OFF),/* FIXME */
	LP_CLK(CRGBASE, 0x028, 10,  "clk_uart0", AP_ON),
	LP_CLK(CRGBASE, 0x028,  9,  "clk_spi1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028,  7,  "clk_i2c3", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028,  3,  "clk_ipc1", AP_ON),
	LP_CLK(CRGBASE, 0x028,  2,  "clk_ipc0", AP_ON),
	LP_CLK(CRGBASE, 0x028,  0,  "clk_pwm", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 31, "clk_txdphy1_ref", AP_ON),
	LP_CLK(CRGBASE, 0x038, 30, "clk_txdphy1_cfg", AO_ON),
	LP_CLK(CRGBASE, 0x038, 29, "clk_txdphy0_ref", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 28, "clk_txdphy0_cfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 27, "clk_ispa7cfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 25, "clk_ispfunc", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 24, "hclk_isp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 23, "aclk_isp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 22, "clk_rxdphy2_cfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 21, "clk_rxdphy1_cfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 20, "clk_rxdphy0_cfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 17, "clk_edc0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 15, "clk_ldi0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 14, "clk_ldi1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 13, "aclk_dss", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 12, "pclk_dss", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 11, "clk_vdec", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 10, "clk_venc", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038,  5,  "clk_g3d", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x038,  4,  "clk_g3dmt", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x038,  3,  "pclk_g3d", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x038,  1,  "clk_dmac1", AO_ON),
	LP_CLK(CRGBASE, 0x038,  0,  "clk_dmac0", AO_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x048, 31,  "clk_a53_tp", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x048, 30,  "clk_ppll5_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 29,  "clk_ppll4_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 28,  "clk_ppll3_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 27,  "clk_ppll2_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 26,  "clk_ppll1_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 25,  "clk_apll2_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 24,  "clk_apll1_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 23,  "clk_apll0_sscg", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x048, 22,  "clk_a53_tsensor", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x048, 21,  "clk_a57_tsensor", LPM3_CLOSE),
	/*LP_CLK(CRGBASE, 0x048, 20,  "clk_smmu", NULL_CLOSE),*/
	LP_CLK(CRGBASE, 0x048, 19,  "clk_sdio1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 18,  "clk_sdio0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 17,  "clk_sd", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 16,  "clk_emmc1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 15,  "clk_emmc0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 14,  "clk_emmc1_3p2m", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 12,  "clk_secp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 10,  "aclk_perf_stat", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  9,  "pclk_perf_stat", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  8,  "clk_perf_stat", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  7,  "clk_ivp32dsp_tcxo", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  6,  "clk_usb3phy_ref_pll", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  5,  "clk_ivp32dsp_sysbus", AP_CLOSE),
	/*LP_CLK(CRGBASE, 0x048,  4, "clk_usbhost12", AP_CLOSE),*/
	LP_CLK(CRGBASE, 0x048,  3,  "clk_ivp32dsp_core", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  2,  "clk_usb3phy_ref", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  1,  "aclk_usb3otg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  0,  "clk_usb3otg_ref", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 31, "clk_sysbus_tp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 30, "clk_lpmcu_tp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 29, "pclk_dsi1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 28, "pclk_dsi0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 27, "clk_ddrphy_apb_dfi_a", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 26, "clk_ddrphy_apb_dfi_b", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 25, "clk_ddrphy_apb_dfi_d", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 24, "clk_ddrphy_apb_dfi_c", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 23, "clk_modem_mcpu_tp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 18, "clk_isp_snclk2", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x058, 17, "clk_isp_snclk1", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x058, 16, "clk_isp_snclk0", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x058, 15, "clk_gpu_hpm", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x058, 14, "clk_cci400", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058, 13, "clk_a53_hpm", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058, 12, "clk_peri_hpm", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058, 11, "clk_ao_hpm", AO_ON),
	LP_CLK(CRGBASE, 0x058, 10, "clk_cci2sysbus_asyn", AO_ON),
	LP_CLK(CRGBASE, 0x058,  9,  "clk_a57_hpm", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058,  8,  "clk_lpmcu", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058,  7,  "clk_slimbus", LPM3_CLOSE),/* FIXME */
	LP_CLK(CRGBASE, 0x058,  6,  "clk_modem_tsensor", MODEM_ON),
	LP_CLK(CRGBASE, 0x058,  5,  "clk_g3d_tsensor", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058,  4,  "clk_ispa7", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058,  3,  "clk_noc_timeout_extref", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058,  2,  "clk_modem_subsys", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058,  1,  "clk_modem_sys", AP_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x058,  0,  "clk_sysbus2hkmem", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0, 15,  "clkgt_vdec", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0, 14,  "clkgt_ispfunc2", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0, 13,  "clkgt_ispfunc1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0, 12,  "clkgt_rxdphy_cfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0, 11,  "clkgt_out1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0, 10,  "clkgt_out0", AP_CLOSE),
	/*LP_CLK(CRGBASE, 0x0F0,  9,  "clkgt_edc1", AP_CLOSE),*/
	LP_CLK(CRGBASE, 0x0F0,  8,  "clkgt_edc0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  7,  "clkgt_ldi1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  6,  "clkgt_ldi0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  4,  "clkgt_lpmcu", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  2,  "clkgt_ddr", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  1,  "clkgt_g3daxi1", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  0,  "clkgt_g3daxi0", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x0F4, 15,  "clkgt_slimbus", LPM3_CLOSE),
	/*LP_CLK(CRGBASE, 0x0F4, 14,  "pclkgt_hdmi", AP_CLOSE),*/
	LP_CLK(CRGBASE, 0x0F4, 13,  "clkgt_spi", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4, 12,  "clkgt_uartl", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4, 11,  "clkgt_uarth", AP_CLOSE),
	/*LP_CLK(CRGBASE, 0x0F4, 10,  "clkgt_modem_uart", MODEM_ON),*/
	/*LP_CLK(CRGBASE, 0x0F4,  9,  "clkgt_uicc", AP_ON), FIXME */
	LP_CLK(CRGBASE, 0x0F4,  8,  "clkgt_sdio1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4,  7,  "clkgt_a53hpm", AP_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x0F4,  4,  "clkgt_sdio0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4,  3,  "clkgt_sd", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4,  2,  "clkgt_emmc0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4,  0,  "clkgt_venc", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F8,  9,  "clkgt_ivp32dsp_core", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  8,  "clkgt_modem_bbe16_tdl", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  7,  "clkgt_modem_bbe16", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  6,  "clkgt_modem_mcpu", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  5,  "clkgt_ptp", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  4,  "clkgt_ispa7", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  3,  "clkgt_aomm", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  2,  "clkgt_vcodecbus", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  1,  "clkgt_vivobus", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F8,  0,  "clkgt_i2c", AP_ON),
};

static struct lp_clk clk_lookups_d[] = {
	LP_CLK(SCTRLBASE, 0x168, 31, "clk_ppll0_sscg", NULL_CLOSE),
	LP_CLK(SCTRLBASE, 0x168, 30, "pclk_efusec", AP_ON),
	LP_CLK(SCTRLBASE, 0x168, 29, "clk_aobus", AP_ON),
	LP_CLK(SCTRLBASE, 0x168, 28, "clk_bbpdrx", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x168, 27, "clk_asp_tcxo", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x168, 26, "clk_asp_subsys", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x168, 25, "reserved", AO_ON),
	LP_CLK(SCTRLBASE, 0x168, 24, "clk_sci1", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x168, 23, "clk_sci0", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x168, 22, "pclk_ao_gpio5", NULL_CLOSE),
	LP_CLK(SCTRLBASE, 0x168, 21, "pclk_ao_gpio4", AP_ON),
	LP_CLK(SCTRLBASE, 0x168, 20, "clk_syscnt", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x168, 19, "pclk_syscnt", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x168, 18, "clk_jtag_auth", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x168, 17, "clk_out1", AP_CLOSE),
	LP_CLK(SCTRLBASE, 0x168, 16, "clk_out0", AP_CLOSE),
	LP_CLK(SCTRLBASE, 0x168, 15, "pclk_ao_ioc", AO_ON),
	LP_CLK(SCTRLBASE, 0x168, 14, "pclk_ao_gpio3", AO_ON),
	LP_CLK(SCTRLBASE, 0x168, 13, "pclk_ao_gpio2", AO_ON),
	LP_CLK(SCTRLBASE, 0x168, 12, "pclk_ao_gpio1", AO_ON),
	LP_CLK(SCTRLBASE, 0x168, 11, "pclk_ao_gpio0", AO_ON),
	LP_CLK(SCTRLBASE, 0x168, 10, "clk_timer3", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x168,  9,  "pclk_timer3", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x168,  8,  "clk_timer2", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x168,  7,  "pclk_timer2", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x168,  6,  "reserved", AP_ON),
	LP_CLK(SCTRLBASE, 0x168,  5,  "reserved", AP_ON),
	LP_CLK(SCTRLBASE, 0x168,  4,  "clk_timer0", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x168,  3,  "pclk_timer0", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x168,  2,  "pclk_rtc1", AP_ON),/* secureos */
	LP_CLK(SCTRLBASE, 0x168,  1,  "pclk_rtc", AP_ON),
	LP_CLK(SCTRLBASE, 0x168,  0,  "clk_ref_crc", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  24,  "clk_mmbuf_dss", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  23,  "pclk_mmbuf", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  22,  "aclk_mmbuf", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  20,  "timerclk_refh", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  19,  "clk_timer8", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  18,  "pclk_timer8", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  17,  "clk_timer7", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  16,  "pclk_timer7", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  15,  "clk_timer6", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  14,  "pclk_timer6", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  13,  "clk_timer5", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  12,  "pclk_timer5", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  11,  "clk_timer4", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  10,  "pclk_timer4", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  8,  "aclk_asc", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  6,  "clk_noc_aobus2mmbuf", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  5,  "clk_aobus_noc", AP_ON),
	LP_CLK(SCTRLBASE, 0x188,  4,  "clk_bbpdrx_oth", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x188,  3,  "clk_asp_cfg", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x188,  2,  "clk_asp_h2p", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x188,  1,  "clk_asp_x2p", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x188,  0,  "clk_asp_dw_axi", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x198,  20,  "gt_clk_mdm2aspcodec", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x198,  19,  "gt_pclk_ao_gpio8", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x198,  18,  "gt_pclk_ao_gpio7", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x198,  17,  "gt_pclk_ao_gpio6", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x258, 7,  "pclkgt_mmbuf", AP_ON),
	LP_CLK(SCTRLBASE, 0x258, 6,  "pll_clkgt_mmbuf", AP_ON),
	LP_CLK(SCTRLBASE, 0x258, 5,  "sclkgt_tp", AP_ON),
	LP_CLK(SCTRLBASE, 0x258, 4,  "clkgt_asp_hclk", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x258, 3,  "clkgt_aobus", AO_ON),
	LP_CLK(SCTRLBASE, 0x258, 2,  "clkgt_sci", MODEM_ON),
	LP_CLK(SCTRLBASE, 0x258, 1,  "clkgt_hifidsp", LPM3_CLOSE),
	LP_CLK(SCTRLBASE, 0x258, 0,  "clkgt_asp_subsys", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x008, 31,  "gt_clk_socp_hifi", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 30,  "hclk_sd", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 29,  "reserved", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 27,  "gt_clk_pack_dfi", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 26,  "gt_clk_dbgsechsic2sysbus", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x008, 25,  "clk_dbgsechsicbus", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x008, 24,  "reserved", AP_ON),
	LP_CLK(CRGBASE, 0x008, 23,  "clk_dma2cfgbus", AO_ON),
	LP_CLK(CRGBASE, 0x008, 22,  "clk_dmabus", AO_ON),
	LP_CLK(CRGBASE, 0x008, 21,  "reserved", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 20,  "clk_lpm32cfgbus", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 19,  "hclk_sdio0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 18,  "clk_mmc0_peribus", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 17,  "clk_mmc0peri2sysbus", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 16,  "gt_clk_vivobus", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008, 15,  "clk_mmc1_peribus", AP_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x008, 14,  "clk_mmc1peri2sysbus", AP_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x008, 13,  "hclk_emmc0", AP_CLOSE),/* FIXME */
	LP_CLK(CRGBASE, 0x008, 12,  "clk_vivobus2ddrc", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x008, 11,  "clk_sys2cfgbus", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x008, 10,  "clk_cfgbus", AO_ON),
	LP_CLK(CRGBASE, 0x008,  9,  "clk_sysbus", AO_ON),
	LP_CLK(CRGBASE, 0x008,  6,  "clk_vcodecbus", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008,  5,  "clk_vcodeccfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x008,  4,  "clk_ddrphy_ref", AO_ON),
	LP_CLK(CRGBASE, 0x008,  2,  "clk_ddrc", AO_ON),
	LP_CLK(CRGBASE, 0x008,  1,  "clk_ddrbyp_ckp0", AO_ON),
	LP_CLK(CRGBASE, 0x008,  0,  "reserved", AO_ON),
	LP_CLK(CRGBASE, 0x018, 31, "gt_clk_socp_cbbe16", AO_ON),
	LP_CLK(CRGBASE, 0x018, 30, "gt_clk_socp_tlbbe16", AO_ON),
	LP_CLK(CRGBASE, 0x018, 29, "clk_socp_mcpu", AO_ON),
	LP_CLK(CRGBASE, 0x018, 28, "clk_socp_acpu", AO_ON),
	LP_CLK(CRGBASE, 0x018, 27, "clk_djtag", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 26, "clk_socp_lpm3", AP_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x018, 25, "pclk_timer12", MODEM_ON),
	LP_CLK(CRGBASE, 0x018, 24, "pclk_timer11", MODEM_ON),/* modem and secureos */
	LP_CLK(CRGBASE, 0x018, 23, "pclk_timer10", AP_ON),
	LP_CLK(CRGBASE, 0x018, 22, "pclk_timer9", AP_ON),
	LP_CLK(CRGBASE, 0x018, 21, "pclk_gpio21", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 20, "pclk_gpio20", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 19, "pclk_gpio19", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 18, "pclk_gpio18", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 17, "pclk_gpio17", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 16,  "pclk_gpio16", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 15,  "pclk_gpio15", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 14,  "pclk_gpio14", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 13,  "pclk_gpio13", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 12,  "pclk_gpio12", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 11,  "pclk_gpio11", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018, 10,  "pclk_gpio10", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  9,  "pclk_gpio9", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  8,  "pclk_gpio8", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  7,  "pclk_gpio7", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  6,  "pclk_gpio6", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  5,  "pclk_gpio5", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  4,  "pclk_gpio4", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  3,  "pclk_gpio3", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  2,  "pclk_gpio2", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  1,  "pclk_gpio1", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x018,  0,  "pclk_gpio0", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x028, 31,  "pclk_pctrl", AO_ON),
	LP_CLK(CRGBASE, 0x028, 28,  "gt_pclk_ipc_mdm_s", AO_ON),
	LP_CLK(CRGBASE, 0x028, 27,  "clk_i2c4", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x028, 26,  "clk_codecssi", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028, 25,  "pclk_ioc", AO_ON),
	LP_CLK(CRGBASE, 0x028, 24,  "clk_hkadcssi", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x028, 23,  "clk_gic", AP_ON),
	LP_CLK(CRGBASE, 0x028, 22,  "clk_adb_mst_a57", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028, 21,  "clk_adb_mst_a53", AP_CLOSE),/* FIXME */
	LP_CLK(CRGBASE, 0x028, 20,  "pclk_ipc_mdm", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028, 19,  "gt_pclk_loadmonitor", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028, 18,  "pclk_tzpc", AP_ON),
	LP_CLK(CRGBASE, 0x028, 17,  "pclk_wd1", AP_ON),
	LP_CLK(CRGBASE, 0x028, 16,  "pclk_wd0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028, 15,  "clk_uart5", MODEM_ON),
	LP_CLK(CRGBASE, 0x028, 14,  "clk_uart4", ON_OFF),/* FIXME */
	LP_CLK(CRGBASE, 0x028, 12,  "clk_uart2", ON_OFF),/* FIXME */
	LP_CLK(CRGBASE, 0x028, 11,  "clk_uart1", ON_OFF),/* FIXME */
	LP_CLK(CRGBASE, 0x028, 10,  "clk_uart0", AP_ON),
	LP_CLK(CRGBASE, 0x028,  9,  "clk_spi1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028,  7,  "clk_i2c3", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028,  6,  "gt_clk_loadmonitor1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028,  5,  "gt_clk_loadmonitor0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028,  4,  "gt_clk_60m", AP_CLOSE),
	LP_CLK(CRGBASE, 0x028,  3,  "clk_ipc1", AP_ON),
	LP_CLK(CRGBASE, 0x028,  2,  "clk_ipc0", AP_ON),
	LP_CLK(CRGBASE, 0x028,  1,  "gt_clk_hkadcssi1", AP_ON),
	LP_CLK(CRGBASE, 0x028,  0,  "clk_pwm", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 29, "clk_txdphy0_ref", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 28, "clk_txdphy0_cfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 27, "clk_ispa7cfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 25, "clk_ispfunc", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 24, "hclk_isp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 23, "aclk_isp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 22, "sc_abb_pll_gps_gt_en1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 21, "clk_rxdphy1_cfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 20, "clk_rxdphy0_cfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 19, "sc_abb_pll_audio_gt_en0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 18, "sc_abb_pll_gps_gt_en0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 17, "clk_edc0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 15, "clk_ldi0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 14, "sc_abb_pll_audio_gt_en1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 13, "aclk_dss", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 12, "pclk_dss", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 11, "clk_vdec", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 10, "clk_venc", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 9, "sc_abb_pll_audio_en", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 8, "sc_abb_pll_audio_en", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 7, "sc_abb_pll_gps_en", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038, 6, "sc_abb_pll_gps_en", AP_CLOSE),
	LP_CLK(CRGBASE, 0x038,  5,  "clk_g3d", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x038,  4,  "clk_g3dmt", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x038,  3,  "pclk_g3d", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x038,  2,  "gt_clk_dmac_mcpu", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x038,  1,  "gt_clk_dmac_acpu", AO_ON),
	LP_CLK(CRGBASE, 0x038,  0,  "gt_clk_dmac_lpm3", AO_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x048, 31,  "clk_a53_tp", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x048, 30,  "clk_ppll5_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 29,  "clk_ppll4_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 28,  "clk_ppll3_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 27,  "clk_ppll2_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 26,  "clk_ppll1_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 25,  "clk_apll2_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 24,  "clk_apll1_sscg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 23,  "clk_apll0_sscg", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x048, 22,  "clk_a53_tsensor", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x048, 21,  "clk_a57_tsensor", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x048, 18,  "clk_sdio0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 17,  "clk_sd", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 15,  "clk_emmc0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 12,  "clk_secp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048, 10,  "aclk_perf_stat", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  9,  "pclk_perf_stat", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  8,  "clk_perf_stat", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  6,  "clk_usb3phy_ref_pll", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  4, "gt_clk_ipf1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  3,  "gt_clk_ipf0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  2,  "gt_clk_usb2phy_ref", AP_CLOSE),
	LP_CLK(CRGBASE, 0x048,  1,  "gt_hclk_usb2otg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 31, "clk_sysbus_tp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 30, "clk_lpmcu_tp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 28, "pclk_dsi0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 27, "clk_ddrphy_apb_dfi_a", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 23, "clk_modem_mcpu_tp", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 19, "gt_clk_isp_timer", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058, 18, "clk_isp_snclk2", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x058, 17, "clk_isp_snclk1", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x058, 16, "clk_isp_snclk0", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x058, 15, "clk_gpu_hpm", NULL_CLOSE),
	LP_CLK(CRGBASE, 0x058, 14, "clk_cci400", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058, 13, "clk_a53_hpm", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058, 12, "clk_peri_hpm", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058, 11, "clk_ao_hpm", AO_ON),
	LP_CLK(CRGBASE, 0x058, 10, "clk_cci2sysbus_asyn", AO_ON),
	LP_CLK(CRGBASE, 0x058,  9,  "clk_a57_hpm", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058,  8,  "clk_lpmcu", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058,  7,  "clk_slimbus", LPM3_CLOSE),/* FIXME */
	LP_CLK(CRGBASE, 0x058,  5,  "clk_g3d_tsensor", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058,  4,  "clk_ispa7", AP_CLOSE),
	LP_CLK(CRGBASE, 0x058,  3,  "clk_noc_timeout_extref", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058,  2,  "clk_modem_subsys", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x058,  1,  "clk_modem_sys", AP_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x058,  0,  "clk_sysbus2hkmem", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0, 15,  "clkgt_vdec", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0, 13,  "clkgt_ispfunc1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0, 12,  "clkgt_rxdphy_cfg", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0, 11,  "clkgt_out1", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0, 10,  "clkgt_out0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  8,  "clkgt_edc0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  6,  "clkgt_ldi0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  4,  "clkgt_lpmcu", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  3,  "gt_clk_loadmonitor0", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  2,  "gt_clk_ddrc", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  1,  "clkgt_g3daxi1", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x0F0,  0,  "clkgt_g3daxi0", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x0F4, 15,  "clkgt_slimbus", LPM3_CLOSE),
	LP_CLK(CRGBASE, 0x0F4, 13,  "clkgt_spi", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4, 12,  "clkgt_uartl", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4, 11,  "clkgt_uarth", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4,  7,  "clkgt_a53hpm", AP_ON),/* FIXME */
	LP_CLK(CRGBASE, 0x0F4,  4,  "clkgt_sdio0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4,  3,  "clkgt_sd", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4,  2,  "clkgt_emmc0", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F4,  0,  "clkgt_venc", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F8,  8,  "clkgt_modem_bbe16_tdl", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  7,  "clkgt_modem_bbe16", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  6,  "clkgt_modem_mcpu", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  5,  "clkgt_ptp", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  4,  "clkgt_ispa7", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  2,  "clkgt_vcodecbus", MODEM_ON),
	LP_CLK(CRGBASE, 0x0F8,  1,  "clkgt_vivobus", AP_CLOSE),
	LP_CLK(CRGBASE, 0x0F8,  0,  "clkgt_i2c", AP_ON),
};

void clk_showone(char *ctrl_name, int index)
{
	u32 regval = 0;
	u32	bitval = 0;
	u32 regoff = 0;
	u32 bit_idx = 0;
	void __iomem *regbase = NULL;
	struct lp_clk *clk_lookups_temp =
		(g_plat_flag == PLAT_A) ? clk_lookups_a : clk_lookups_d;

	switch (clk_lookups_temp[index].reg_base) {
	case SCTRLBASE:
		strncpy(ctrl_name, "SYSCTRL", sizeof(char) * 10);
		regbase = sysreg_base.sysctrl_base;
		break;
	case CRGBASE:
		strncpy(ctrl_name, "CRGPERI", sizeof(char) * 10);
		regbase = sysreg_base.crg_base;
		break;
	case PMCBASE:
		strncpy(ctrl_name, "PMCCTRL", sizeof(char) * 10);
		regbase = sysreg_base.pctrl_base;
		break;
	case PMUBASE:
		strncpy(ctrl_name, "PMUCTRL", sizeof(char) * 10);
		regbase = sysreg_base.pmic_base;
		clk_lookups_temp[index].reg_off =  clk_lookups_temp[index].reg_off << 2;
		break;
	}

	regoff = clk_lookups_temp[index].reg_off;
	bit_idx = clk_lookups_temp[index].bit_idx;
	regval = readl(regbase + regoff);
	bitval = regval & BIT(bit_idx);

	printk("[%s] offset:0x%x regval:0x%x bit_idx:%s%d state:%d %s",
			ctrl_name, regoff, regval, bit_idx > 9 ? "" : "0",
			bit_idx, bitval ? 1 : 0, clk_lookups_temp[index].clk_name);

	if (bitval) {
		if ((NULL_CLOSE == clk_lookups_temp[index].status)
				|| (AP_CLOSE == clk_lookups_temp[index].status))
			printk(" -E[OFF]");
	} else {
		if ((AP_ON == clk_lookups_temp[index].status)
				|| (AO_ON == clk_lookups_temp[index].status))
			printk(" -E[ON]");
	}
	if (ON_OFF == clk_lookups_temp[index].status)
		printk("[FIXME: on or off]");
	if (MODEM_ON == clk_lookups_temp[index].status)
		printk("[MODEM: on or off]");

	printk("\n");
}

#define SYS_REG(_base, _offset, _reg_name) \
{                               \
	.reg_base = _base, \
	.reg_off = _offset,  \
	.reg_name = _reg_name,  \
}
static struct sys_reg sysreg_lookups[] = {
	/*sysctrlregs*/
	SYS_REG(SCTRLBASE, 0x020, "SCPPLLCTRL0"),
	SYS_REG(SCTRLBASE, 0x024, "SCPPLLCTRL1"),
	SYS_REG(SCTRLBASE, 0x028, "SCPPLLSSCCTRL"),
	SYS_REG(SCTRLBASE, 0x02C, "SCPPLLSTAT"),
	SYS_REG(SCTRLBASE, 0x038, "SCPERCLKEN0"),
	SYS_REG(SCTRLBASE, 0x048, "SCPERCLKEN1"),
	SYS_REG(SCTRLBASE, 0x088, "SCPERRSTSTAT0"),
	SYS_REG(SCTRLBASE, 0x094, "SCPERRSTSTAT1"),
	SYS_REG(SCTRLBASE, 0x0A0, "SCPERRSTSTAT2"),
	SYS_REG(SCTRLBASE, 0x0A4, "SCIPCLKRSTBUS"),
	SYS_REG(SCTRLBASE, 0x0C8, "SCISOSTAT"),
	SYS_REG(SCTRLBASE, 0x0D8, "SCPWRSTAT"),
	SYS_REG(SCTRLBASE, 0x100, "SCCLKDIV0"),
	SYS_REG(SCTRLBASE, 0x104, "SCCLKDIV1"),
	SYS_REG(SCTRLBASE, 0x108, "SCCLKDIV2"),
	SYS_REG(SCTRLBASE, 0x10C, "SCCLKDIV3"),
	SYS_REG(SCTRLBASE, 0x110, "SCCLKDIV4"),
	SYS_REG(SCTRLBASE, 0x114, "SCCLKDIV5"),
	SYS_REG(SCTRLBASE, 0x204, "SCPERCTRL1"),
	SYS_REG(SCTRLBASE, 0x208, "SCPERCTRL2"),
	SYS_REG(SCTRLBASE, 0x20C, "SCPERCTRL3"),
	SYS_REG(SCTRLBASE, 0x21C, "SCPERSTATUS0"),
	SYS_REG(SCTRLBASE, 0x220, "SCPERSTATUS1"),
	SYS_REG(SCTRLBASE, 0x224, "SCPERSTATUS2"),
	SYS_REG(SCTRLBASE, 0x228, "SCPERSTATUS3"),
	SYS_REG(SCTRLBASE, 0x22C, "SCPERSTATUS4"),
	SYS_REG(SCTRLBASE, 0x300, "SCDEEPSLEEPED"),
	SYS_REG(SCTRLBASE, 0x304, "SCMRBBUSYSTAT"),
	SYS_REG(SCTRLBASE, 0x314, "SCBAKDATA0"),
	SYS_REG(SCTRLBASE, 0x318, "SCBAKDATA1"),
	SYS_REG(SCTRLBASE, 0x31C, "SCBAKDATA2"),
	SYS_REG(SCTRLBASE, 0x320, "SCBAKDATA3"),
	SYS_REG(SCTRLBASE, 0x324, "SCBAKDATA4"),
	SYS_REG(SCTRLBASE, 0x328, "SCBAKDATA5"),
	SYS_REG(SCTRLBASE, 0x32C, "SCBAKDATA6"),
	SYS_REG(SCTRLBASE, 0x330, "SCBAKDATA7"),
	SYS_REG(SCTRLBASE, 0x334, "SCBAKDATA8"),
	SYS_REG(SCTRLBASE, 0x338, "SCBAKDATA9"),
	SYS_REG(SCTRLBASE, 0x33C, "SCBAKDATA10"),
	SYS_REG(SCTRLBASE, 0x340, "SCBAKDATA11"),
	SYS_REG(SCTRLBASE, 0x344, "SCBAKDATA12"),
	SYS_REG(SCTRLBASE, 0x348, "SCBAKDATA13"),
	SYS_REG(SCTRLBASE, 0x34C, "SCBAKDATA14"),
	SYS_REG(SCTRLBASE, 0x350, "SCBAKDATA15"),
	SYS_REG(SCTRLBASE, 0x450, "SCINT_GATHER_STAT"),
	SYS_REG(SCTRLBASE, 0x454, "SCINT_MASK"),
	SYS_REG(SCTRLBASE, 0x458, "SCINT_STAT"),
	SYS_REG(SCTRLBASE, 0x45C, "SCDRX_INT_CFG"),
	SYS_REG(SCTRLBASE, 0x460, "SCLPM3WFI_INT_CLR"),
	SYS_REG(SCTRLBASE, 0x48C, "SCMALIBYPCFG"),
	SYS_REG(SCTRLBASE, 0x500, "SCLPM3CLKEN"),
	SYS_REG(SCTRLBASE, 0x50C, "SCLPM3RSTSTAT"),
	SYS_REG(SCTRLBASE, 0x510, "SCLPM3CTRL"),
	SYS_REG(SCTRLBASE, 0x514, "SCLPM3STAT"),
	SYS_REG(SCTRLBASE, 0x518, "SCLPM3RAMCTRL"),
	SYS_REG(SCTRLBASE, 0x530, "SCBBPDRXSTAT0"),
	SYS_REG(SCTRLBASE, 0x550, "SCA7_EVENT_MASK"),
	SYS_REG(SCTRLBASE, 0x554, "SCA15_EVENT_MASK"),
	SYS_REG(SCTRLBASE, 0x558, "SCIOM3_EVENT_MASK"),
	SYS_REG(SCTRLBASE, 0x55C, "SCLPM3_EVENT_MASK"),
	SYS_REG(SCTRLBASE, 0x560, "SCMCPU_EVENT_MASK"),
	SYS_REG(SCTRLBASE, 0x564, "SCEVENT_STAT"),
	/*crgperiregs*/
	SYS_REG(CRGBASE, 0x008, "PERCLKEN0"),
	SYS_REG(CRGBASE, 0x018, "PERCLKEN1"),
	SYS_REG(CRGBASE, 0x028, "PERCLKEN2"),
	SYS_REG(CRGBASE, 0x038, "PERCLKEN3"),
	SYS_REG(CRGBASE, 0x048, "PERCLKEN4"),
	SYS_REG(CRGBASE, 0x058, "PERCLKEN5"),
	SYS_REG(CRGBASE, 0x068, "PERRSTSTAT0"),
	SYS_REG(CRGBASE, 0x074, "PERRSTSTAT1"),
	SYS_REG(CRGBASE, 0x080, "PERRSTSTAT2"),
	SYS_REG(CRGBASE, 0x08C, "PERRSTSTAT3"),
	SYS_REG(CRGBASE, 0x098, "PERRSTSTAT4"),
	SYS_REG(CRGBASE, 0x0A8, "CLKDIV0"),
	SYS_REG(CRGBASE, 0x0AC, "CLKDIV1"),
	SYS_REG(CRGBASE, 0x0B0, "CLKDIV2"),
	SYS_REG(CRGBASE, 0x0B4, "CLKDIV3"),
	SYS_REG(CRGBASE, 0x0B8, "CLKDIV4"),
	SYS_REG(CRGBASE, 0x0BC, "CLKDIV5"),
	SYS_REG(CRGBASE, 0x0C0, "CLKDIV6"),
	SYS_REG(CRGBASE, 0x0C4, "CLKDIV7"),
	SYS_REG(CRGBASE, 0x0C8, "CLKDIV8"),
	SYS_REG(CRGBASE, 0x0CC, "CLKDIV9"),
	SYS_REG(CRGBASE, 0x0D0, "CLKDIV10"),
	SYS_REG(CRGBASE, 0x0D4, "CLKDIV11"),
	SYS_REG(CRGBASE, 0x0D8, "CLKDIV12"),
	SYS_REG(CRGBASE, 0x0DC, "CLKDIV13"),
	SYS_REG(CRGBASE, 0x0E0, "CLKDIV14"),
	SYS_REG(CRGBASE, 0x0E4, "CLKDIV15"),
	SYS_REG(CRGBASE, 0x0E8, "CLKDIV16"),
	SYS_REG(CRGBASE, 0x0EC, "CLKDIV17"),
	SYS_REG(CRGBASE, 0x0F0, "CLKDIV18"),
	SYS_REG(CRGBASE, 0x0F4, "CLKDIV19"),
	SYS_REG(CRGBASE, 0x0F8, "CLKDIV20"),
	SYS_REG(CRGBASE, 0x0FC, "CLKDIV21"),
	SYS_REG(CRGBASE, 0x100, "CLKDIV22"),
	SYS_REG(CRGBASE, 0x104, "CLKDIV23"),
	SYS_REG(CRGBASE, 0x108, "CLKDIV24"),
	SYS_REG(CRGBASE, 0x10C, "CLKDIV25"),
	SYS_REG(CRGBASE, 0x114, "PER_STAT1"),
	SYS_REG(CRGBASE, 0x118, "PER_STAT2"),
	SYS_REG(CRGBASE, 0x11C, "PER_STAT3"),
	SYS_REG(CRGBASE, 0x120, "PERCTRL0"),
	SYS_REG(CRGBASE, 0x124, "PERCTRL1"),
	SYS_REG(CRGBASE, 0x128, "PERCTRL2"),
	SYS_REG(CRGBASE, 0x12C, "PERCTRL3"),
	SYS_REG(CRGBASE, 0x130, "PERCTRL4"),
	SYS_REG(CRGBASE, 0x134, "PERCTRL5"),
	SYS_REG(CRGBASE, 0x138, "PERCTRL6"),
	SYS_REG(CRGBASE, 0x140, "PERTIMECTRL"),
	SYS_REG(CRGBASE, 0x14C, "ISOSTAT"),
	SYS_REG(CRGBASE, 0x158, "PERPWRSTAT"),
	SYS_REG(CRGBASE, 0x160, "A53CLKEN"),
	SYS_REG(CRGBASE, 0x16C, "A53RSTSTAT"),
	SYS_REG(CRGBASE, 0x174, "A53ADBLPSTAT"),
	SYS_REG(CRGBASE, 0x178, "A53CTRL0"),
	SYS_REG(CRGBASE, 0x17C, "A53CTRL1"),
	SYS_REG(CRGBASE, 0x180, "A53CTRL2"),
	SYS_REG(CRGBASE, 0x194, "A53STAT"),
	SYS_REG(CRGBASE, 0x1C0, "MAIACLKEN"),
	SYS_REG(CRGBASE, 0x1CC, "MAIARSTSTAT"),
	SYS_REG(CRGBASE, 0x1D4, "MAIAADBLPSTAT"),
	SYS_REG(CRGBASE, 0x1D8, "MAIACTRL0"),
	SYS_REG(CRGBASE, 0x1DC, "MAIACTRL1"),
	SYS_REG(CRGBASE, 0x1E0, "MAIACTRL2"),
	SYS_REG(CRGBASE, 0x1F4, "MAIASTAT"),

	SYS_REG(CRGBASE, 0x204, "CORESIGHTLPSTAT"),
	SYS_REG(CRGBASE, 0x208, "CORESIGHTCTRL0"),
	SYS_REG(CRGBASE, 0x20C, "CORESIGHTETFINT"),
	SYS_REG(CRGBASE, 0x210, "CORESIGHTETRINT"),

	SYS_REG(CRGBASE, 0x21C, "CCI400STAT1"),
	SYS_REG(CRGBASE, 0x220, "ADB400STAT"),
	SYS_REG(CRGBASE, 0x228, "CCI400CTRL0"),
	SYS_REG(CRGBASE, 0x22C, "CCI400CTRL1"),
	SYS_REG(CRGBASE, 0x230, "CCI400STAT"),
	SYS_REG(CRGBASE, 0x234, "G3D_0_ADBLPSTAT"),
	SYS_REG(CRGBASE, 0x238, "G3D_1_ADBLPSTAT"),
	/*pmctrlregs*/
	SYS_REG(PMCBASE, 0x004, "PMCINTSTAT"),
	SYS_REG(PMCBASE, 0x00C, "PMCSTATUS"),
	SYS_REG(PMCBASE, 0x010, "APLL0CTRL0"),
	SYS_REG(PMCBASE, 0x014, "APLL0CTRL1"),
	SYS_REG(PMCBASE, 0x018, "APLL1CTRL0"),
	SYS_REG(PMCBASE, 0x01C, "APLL1CTRL1"),
	SYS_REG(PMCBASE, 0x020, "APLL2CTRL0"),
	SYS_REG(PMCBASE, 0x024, "APLL2CTRL1"),
	SYS_REG(PMCBASE, 0x038, "PPLL1CTRL0"),
	SYS_REG(PMCBASE, 0x03C, "PPLL1CTRL1"),
	SYS_REG(PMCBASE, 0x040, "PPLL2CTRL0"),
	SYS_REG(PMCBASE, 0x044, "PPLL2CTRL1"),
	SYS_REG(PMCBASE, 0x048, "PPLL3CTRL0"),
	SYS_REG(PMCBASE, 0x04C, "PPLL3CTRL1"),
	SYS_REG(PMCBASE, 0x070, "APLL0SSCCTRL"),
	SYS_REG(PMCBASE, 0x074, "APLL1SSCCTRL"),
	SYS_REG(PMCBASE, 0x078, "APLL2SSCCTRL"),
	SYS_REG(PMCBASE, 0x084, "PPLL1SSCCTRL"),
	SYS_REG(PMCBASE, 0x088, "PPLL2SSCCTRL"),
	SYS_REG(PMCBASE, 0x08C, "PPLL3SSCCTRL"),
	/*pctrlregs*/
	SYS_REG(PCTRLBASE, 0x408, "RESOURCE0_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x414, "RESOURCE1_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x420, "RESOURCE2_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x42C, "RESOURCE3_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x808, "RESOURCE4_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x814, "RESOURCE5_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x820, "RESOURCE6_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x82C, "RESOURCE7_LOCK_ST"),
};

#define SYSREG_LIST_LENGTH	\
		(int)(sizeof(sysreg_lookups)/sizeof(sysreg_lookups[0]))

void sysreg_showone(char *ctrl_name, int index)
{
	u32 regval = 0;
	u32 regoff = 0;
	void __iomem *regbase = NULL;

	switch (sysreg_lookups[index].reg_base) {
	case SCTRLBASE:
		strncpy(ctrl_name, "SYSCTRL", sizeof(char) * 10);
		regbase = sysreg_base.sysctrl_base;
		break;
	case CRGBASE:
		strncpy(ctrl_name, "CRGPERI", sizeof(char) * 10);
		regbase = sysreg_base.crg_base;
		break;
	case PCTRLBASE:
		strncpy(ctrl_name, "PCTRL", sizeof(char) * 10);
		regbase = sysreg_base.pctrl_base;
		break;
	case PMCBASE:
		strncpy(ctrl_name, "PMCTRL", sizeof(char) * 10);
		regbase = sysreg_base.pmctrl_base;
		break;
	case PMUBASE:
		strncpy(ctrl_name, "PMUCTRL", sizeof(char) * 10);
		regbase = sysreg_base.pmic_base;
		sysreg_lookups[index].reg_off = sysreg_lookups[index].reg_off << 2;
		break;
	default:
		pr_err("%s not exist the ip defined field\n",
				__func__);
		return;
	}

	regoff = sysreg_lookups[index].reg_off;
	regval = readl(regbase + regoff);

	pr_info("[%7s]%s [%17s]%s [0x%3x]%s  val = 0x%x\n",
			ctrl_name, "", sysreg_lookups[index].reg_name, "", regoff, "", regval);

}

void hisi_sysregs_dump(void)
{
	int i = 0;
	char *ctrl_name;

	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	ctrl_name = kzalloc(sizeof(char) * 10, GFP_ATOMIC);
	if (!ctrl_name) {
		pr_err("Cannot allocate ctrl_name.\n");
		return;
	}

	for (i = 0; i < SYSREG_LIST_LENGTH; i++)
		sysreg_showone(ctrl_name, i);

	kfree(ctrl_name);
	ctrl_name = NULL;

	pr_info("[%s] %d leave.\n", __func__, __LINE__);
}
EXPORT_SYMBOL_GPL(hisi_sysregs_dump);

/*****************************************************************
 * function:    dbg_clk_status_show
 * description:
 *  show the clk status.
 ******************************************************************/
void dbg_clk_status_show(void)
{
	int i = 0;
	char *ctrl_name;
	unsigned int clk_list_len =
		(g_plat_flag == PLAT_A) ? (int)(sizeof(clk_lookups_a)/sizeof(clk_lookups_a[0]))
								: (int)(sizeof(clk_lookups_d)/sizeof(clk_lookups_d[0]));

	if (!(g_usavedcfg & DEBG_SUSPEND_CLK_SHOW))
		return;
	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	ctrl_name = kzalloc(sizeof(char) * 10, GFP_KERNEL);
	if (!ctrl_name) {
		pr_err("%s: Cannot allocate clk_name.\n", __func__);
		return;
	}

	for (i = 0; i < clk_list_len; i++)
		clk_showone(ctrl_name, i);

	kfree(ctrl_name);

	pr_info("[%s] %d leave.\n", __func__, __LINE__);
}

#ifdef CONFIG_DEBUG_FS

#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

#define MX_BUF_LEN		1024
char g_ctemp[MX_BUF_LEN] = {0};

/*****************************************************************
 * function:    dbg_common_open
 * description:
 *  adapt to the interface.
 ******************************************************************/
static int dbg_common_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
 * function:    dbg_cfg_read
 * description:
 *  show the debug cfg for user.
 ******************************************************************/
static ssize_t dbg_cfg_read(struct file *filp, char __user *buffer,
		size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, sizeof(g_ctemp));

	snprintf(g_ctemp, sizeof(g_ctemp),
			"0x1<<0 enable suspend console\n"
			"0x1<<1 ENABLE IO STATUS SHOW\n"
			"0x1<<2 ENABLE PMU STATUS SHOW\n"
			"0x1<<3 ENABLE IO SET\n"
			"0x1<<4 ENABLE PMU SET\n"
			"0x1<<5 ENABLE SINGLE IO SET\n"
			"0x1<<6 ENABLE 1s RTC wakeup (no support now)\n"
			"0x1<<7 ENABLE 500ms TIMER wakeup (no support now)\n"
			"0x1<<8 ENABLE a wakelock\n"
			"0x1<<9 ENABLE SUSPEND AUDIO\n"
			"0x1<<10 ENABLE CLK STATUS SHOW\n"
			"0x1<<11 ENABLE IPC DATA SHOW\n"
			"0x1<<31 ENABLE DEBUG INFO\n"
			"g_usavedcfg=%x\n", g_usavedcfg);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
 * function:    dbg_cfg_write
 * description:
 *  recieve the configuer of the user.
 ******************************************************************/
static ssize_t dbg_cfg_write(struct file *filp, const char __user *buffer,
		size_t count, loff_t *ppos)
{
	int index = 0;

	if (count >= sizeof(g_ctemp)) {
		pr_err("input size(%lu) >= buf size(%lu)\n", count, sizeof(g_ctemp));
		return -ENOMEM;
	}

	memset(g_ctemp, 0, sizeof(g_ctemp));

	if (copy_from_user(g_ctemp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (('0' == g_ctemp[0]) && ('x' == g_ctemp[1])) {
		if (sscanf(g_ctemp + 2, "%x", &index))
			g_usavedcfg = index;
		else
			pr_info("sscanf error!\n");
	} else {
		if (sscanf(g_ctemp, "%d", &index))
			g_usavedcfg = index;
		else
			pr_info("sscanf error\n");
	}

	pr_info("%s %d, g_usavedcfg=0x%x\n", __func__, __LINE__, g_usavedcfg);

	/*suspend print enable*/
	if (DEBG_SUSPEND_PRINTK & g_usavedcfg)
		console_suspend_enabled = 0;
	else
		console_suspend_enabled = 1;

	if (DEBG_SUSPEND_WAKELOCK & g_usavedcfg)
		set_wakelock(1);
	else
		set_wakelock(0);

	*ppos += count;

	return count;
}

const struct file_operations dbg_cfg_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_common_open,
	.read	= dbg_cfg_read,
	.write	= dbg_cfg_write,
};

/*****************************************************************
 * function:    dbg_pm_status_show
 * description:
 *  show the debug cfg for user.
 ******************************************************************/
static int dbg_pm_status_show(struct seq_file *s, void *unused)
{
	pm_status_show(s);
	return 0;
}

/*****************************************************************
 * function:    dbg_pm_status_open
 * description:
 * adapt to the interface.
 ******************************************************************/
static int dbg_pm_status_open(struct inode *inode, struct file *file)
{
	return single_open(file, dbg_pm_status_show, &inode->i_private);
}

const struct file_operations dbg_pm_status_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_pm_status_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

/*****************************************************************
 * function:    dbg_iomux_read
 * description:
 *  print out he io status on the COM.
 ******************************************************************/
static ssize_t dbg_iomux_read(struct file *filp, char __user *buffer,
		size_t count, loff_t *ppos)
{
	char temp[32] = {0};
	if (!(g_usavedcfg & DEBG_SUSPEND_IO_SHOW))
		return 0;

	if (*ppos >= 32)
		return 0;

	if (*ppos + count > 32)
		count = 32 - *ppos;

	if (copy_to_user(buffer, temp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	dbg_io_status_show();
	return count;
}

const struct file_operations dbg_iomux_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_common_open,
	.read	= dbg_iomux_read,
};

int dbg_pmu_show(struct seq_file *s, void *unused)
{
	dbg_pmu_status_show();

	return 0;
}

/*****************************************************************
 * function:    dbg_pmu_open
 * description:
 *  adapt to the interface.
 ******************************************************************/
static int dbg_pmu_open(struct inode *inode, struct file *file)
{
	return single_open(file, dbg_pmu_show, &inode->i_private);
}

static const struct file_operations debug_pmu_fops = {
	.open		= dbg_pmu_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int dbg_clk_show(struct seq_file *s, void *unused)
{
	dbg_clk_status_show();

	return 0;
}

/*****************************************************************
 * function:    dbg_clk_open
 * description:
 *  adapt to the interface.
 ******************************************************************/
static int dbg_clk_open(struct inode *inode, struct file *file)
{
	return single_open(file, dbg_clk_show, &inode->i_private);
}

static const struct file_operations debug_clk_fops = {
	.open		= dbg_clk_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};
#endif /*CONFIG_DEBUG_FS*/

/*****************************************************************
 * function:    lowpm_func_probe
 * description:
 *  driver interface.
 ******************************************************************/
static int lowpm_func_probe(struct platform_device *pdev)
{
	int status = 0;
#ifdef CONFIG_DEBUG_FS
	struct dentry *pdentry;
#endif

	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	g_suspended = 0;

	map_sysregs();
	map_io_regs();

	wake_lock_init(&lowpm_wake_lock, WAKE_LOCK_SUSPEND, "lowpm_func");

#ifndef CONFIG_HISI_SR_DEBUG_SLEEP
	set_wakelock(1);
#endif

#ifdef CONFIG_DEBUG_FS
	pdentry = debugfs_create_dir("lowpm_func", NULL);
	if (!pdentry) {
		pr_info("%s %d error can not create debugfs lowpm_func.\n",
				__func__, __LINE__);
		return -ENOMEM;
	}

	(void) debugfs_create_file("clk", CLK_DEBUG_FILE_MODE, pdentry, NULL, &debug_clk_fops);

	(void) debugfs_create_file("pmu", PMU_DEBUG_FILE_MODE, pdentry, NULL, &debug_pmu_fops);

	(void) debugfs_create_file("io", IO_DEBUG_FILE_MODE, pdentry, NULL, &dbg_iomux_fops);

	(void) debugfs_create_file("cfg", CFG_DEBUG_FILE_MODE, pdentry, NULL, &dbg_cfg_fops);

	(void) debugfs_create_file("debug_sr", DEBUGSR_DEBUG_FILE_MODE, pdentry, NULL, &dbg_pm_status_fops);
#endif /*CONFIG_DEBUG_FS*/

	pr_info("[%s] %d leave.\n", __func__, __LINE__);

	return status;
}

/*****************************************************************
 * function:    lowpm_func_remove
 * description:
 *  driver interface.
 ******************************************************************/
static int lowpm_func_remove(struct platform_device *pdev)
{
	return 0;
}

#ifdef CONFIG_PM
static int lowpm_func_suspend(struct platform_device *pdev,
		pm_message_t state)
{
	g_suspended = 1;
	return 0;
}

static int lowpm_func_resume(struct platform_device *pdev)
{
	g_suspended = 0;
	return 0;
}
#else
#define lowpm_func_suspend	NULL
#define lowpm_func_resume	NULL
#endif

#define MODULE_NAME		"hisilicon,lowpm_func"

static const struct of_device_id lowpm_func_match[] = {
	{ .compatible = MODULE_NAME },
	{},
};

static struct platform_driver lowpm_func_drv = {
	.probe		= lowpm_func_probe,
	.remove		= lowpm_func_remove,
	.suspend	= lowpm_func_suspend,
	.resume		= lowpm_func_resume,
	.driver = {
		.name	= MODULE_NAME,
		.of_match_table = of_match_ptr(lowpm_func_match),
	},
};

static int __init lowpmreg_init(void)
{
	return platform_driver_register(&lowpm_func_drv);
}

static void __exit lowpmreg_exit(void)
{
	platform_driver_unregister(&lowpm_func_drv);
}


module_init(lowpmreg_init);
module_exit(lowpmreg_exit);
