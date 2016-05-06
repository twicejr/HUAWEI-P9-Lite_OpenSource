/*
 * Copyright (C) 2012-2015 HUAWEI
 * Author:  L.JH HW
 */

#include <linux/i2c.h>      /*for struct bq2429x_device_info*/
#include <linux/device.h>   /*for struct bq2429x_device_info*/
#include <linux/workqueue.h>    /*for struct bq2429x_device_info*/

#ifndef _BQ2429X_CHARGER
#define _BQ2429X_CHARGER

#ifndef BIT
#define BIT(x)		(1 << (x))
#endif

/*************************struct define area***************************/
struct bq2429x_device_info
{
    struct i2c_client *client;
    struct device *dev;
    struct work_struct irq_work;
    int gpio_cd;
    int gpio_int;
    int irq_int;
    int irq_active;
};

/* REG02[7:2] (ICHG) in mAh */
static const int bq2429x_ichg_values[] =
{
    512,   576,  640,  704,  768,  832,  896,  960,
    1024, 1088, 1152, 1216, 1280, 1344, 1408, 1472,
    1536, 1600, 1664, 1728, 1792, 1856, 1920, 1984,
    2048, 2112, 2176, 2240, 2304, 2368, 2432, 2496,
    2560, 2624, 2688, 2752, 2816, 2880, 2944, 3008,
    3072, 3136, 3200, 3264, 3328, 3392, 3456, 3520,
    3584, 3648, 3712, 3776, 3840, 3904, 3968, 4032,
    4096, 4160, 4224, 4288, 4352, 4416, 4480, 4544
};

/* REG01[3:1] (VSYSMIN) in mV */
static const int bq2429x_vsysmin_values[] =
{
    3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700
};
/* REG00[2:0] (IINLIM) in mAh */
static const int bq2429x_iin_values[] =
{
    100, 150, 500, 900, 1000, 1500, 2000, 3000
};

/* REG03[7:4] (IPRECHG) in mAh */
static const int bq2429x_iprechg_values[] =
{
    128,   256,  384,   512,   640,  768,   896,  1024,
    1152, 1280, 1408, 1536, 1664, 1792, 1920, 2048
};

/* REG03[3:0] (ITERM) in mAh */
static const int bq2429x_iterm_values[] =
{
    128,   256,  384,   512,   640,  768,   896,  1024,
    1152, 1280, 1408, 1536, 1664, 1792, 1920, 2048
};

/* REG04[7:2] (VREG) in mV */
static const int bq2429x_vreg_values[] =
{
    3504, 3520, 3536, 3552, 3568, 3584, 3600, 3616,
    3632, 3648, 3664, 3680, 3696, 3712, 3728, 3744,
    3760, 3776, 3792, 3808, 3824, 3840, 3856, 3872,
    3888, 3904, 3920, 3936, 3952, 3968, 3984, 4000,
    4016, 4032, 4048, 4064, 4080, 4096, 4112, 4128,
    4144, 4160, 4176, 4192, 4208, 4224, 4240, 4256,
    4272, 4288, 4304, 4320, 4336, 4352, 4368, 4384,
    4400
};

/*REG00[6:3](VINDPM) in mV */
static const int bq2429x_vindpm_values[] =
{
    3880, 3960, 4040, 4120, 4200, 4280, 4360, 4440,
    4520, 4600, 4680, 4760, 4840, 4920, 5000, 5080
};

/*REG06[7:4](BOOSTV) in mV */
static const int bq2429x_boostv_values[] =
{
    4550, 4614, 4678, 4742, 4806, 4870, 4934, 4998,
    5062, 5126, 5190, 5254, 5318, 5382, 5446, 5510
};

/*REG05[5:4](WATCHDOG) in S */
static const int bq2429x_watchdog_values[] =
{
    0, 40, 80, 160
};

/*************************marco define area***************************/
#define BQ2429X_REG_NUM                              (11)
/*REG MASK & SHITF info*/
#define BQ2429X_REG_ISC		0x00 /* Input Source Control */
#define BQ2429X_REG_ISC_EN_HIZ_MASK		BIT(7)
#define BQ2429X_REG_ISC_EN_HIZ_SHIFT		7
#define BQ2429X_REG_ISC_VINDPM_MASK		(BIT(6) | BIT(5) | BIT(4) | \
						 BIT(3))
#define BQ2429X_REG_ISC_VINDPM_SHIFT		3
#define BQ2429X_REG_ISC_IINLIM_MASK		(BIT(2) | BIT(1) | BIT(0))
#define BQ2429X_REG_ISC_IINLIM_SHIFT		0

#define BQ2429X_REG_POC		0x01 /* Power-On Configuration */
#define BQ2429X_REG_POC_RESET_MASK		BIT(7)
#define BQ2429X_REG_POC_RESET_SHIFT		7
#define BQ2429X_REG_POC_WDT_RESET_MASK		BIT(6)
#define BQ2429X_REG_POC_WDT_RESET_SHIFT		6
#define BQ2429X_REG_POC_CHG_CONFIG_MASK		(BIT(5) | BIT(4))
#define BQ2429X_REG_POC_CHG_CONFIG_SHIFT	4
#define BQ2429X_REG_POC_SYS_MIN_MASK		(BIT(3) | BIT(2) | BIT(1))
#define BQ2429X_REG_POC_SYS_MIN_SHIFT		1
#define BQ2429X_REG_POC_BOOST_LIM_MASK		BIT(0)
#define BQ2429X_REG_POC_BOOST_LIM_SHIFT		0

#define BQ2429X_REG_CCC		0x02 /* Charge Current Control */
#define BQ2429X_REG_CCC_ICHG_MASK		(BIT(7) | BIT(6) | BIT(5) | \
						 BIT(4) | BIT(3) | BIT(2))
#define BQ2429X_REG_CCC_ICHG_SHIFT		2
#define BQ2429X_REG_CCC_BCOLD_MASK	BIT(1)
#define BQ2429X_REG_CCC_BCOLD_SHIFT	1
#define BQ2429X_REG_CCC_FORCE_20PCT_MASK	BIT(0)
#define BQ2429X_REG_CCC_FORCE_20PCT_SHIFT	0

#define BQ2429X_REG_PCTCC	0x03 /* Pre-charge/Termination Current Cntl */
#define BQ2429X_REG_PCTCC_IPRECHG_MASK		(BIT(7) | BIT(6) | BIT(5) | \
						 BIT(4))
#define BQ2429X_REG_PCTCC_IPRECHG_SHIFT		4
#define BQ2429X_REG_PCTCC_ITERM_MASK		(BIT(3) | BIT(2) | BIT(1) | \
						 BIT(0))
#define BQ2429X_REG_PCTCC_ITERM_SHIFT		0

#define BQ2429X_REG_CVC		0x04 /* Charge Voltage Control */
#define BQ2429X_REG_CVC_VREG_MASK		(BIT(7) | BIT(6) | BIT(5) | \
						 BIT(4) | BIT(3) | BIT(2))
#define BQ2429X_REG_CVC_VREG_SHIFT		2
#define BQ2429X_REG_CVC_BATLOWV_MASK		BIT(1)
#define BQ2429X_REG_CVC_BATLOWV_SHIFT		1
#define BQ2429X_REG_CVC_VRECHG_MASK		BIT(0)
#define BQ2429X_REG_CVC_VRECHG_SHIFT		0

#define BQ2429X_REG_CTTC	0x05 /* Charge Term/Timer Control */
#define BQ2429X_REG_CTTC_EN_TERM_MASK		BIT(7)
#define BQ2429X_REG_CTTC_EN_TERM_SHIFT		7
#define BQ2429X_REG_CTTC_TERM_STAT_MASK		BIT(6)
#define BQ2429X_REG_CTTC_TERM_STAT_SHIFT	6
#define BQ2429X_REG_CTTC_WATCHDOG_MASK		(BIT(5) | BIT(4))
#define BQ2429X_REG_CTTC_WATCHDOG_SHIFT		4
#define BQ2429X_REG_CTTC_EN_TIMER_MASK		BIT(3)
#define BQ2429X_REG_CTTC_EN_TIMER_SHIFT		3
#define BQ2429X_REG_CTTC_CHG_TIMER_MASK		(BIT(2) | BIT(1))
#define BQ2429X_REG_CTTC_CHG_TIMER_SHIFT	1
#define BQ2429X_REG_CTTC_JEITA_ISET_MASK	BIT(0)
#define BQ2429X_REG_CTTC_JEITA_ISET_SHIFT	0

#define BQ2429X_REG_BVTRC	0x06 /* Boost Voltage/Thermal Regulation Control */
#define BQ2429X_REG_BVTRC_BOOSTV_MASK		(BIT(7) | BIT(6) | BIT(5) | BIT(4))
#define BQ2429X_REG_BVTRC_BOOSTV_SHIFT	4
#define BQ2429X_REG_BVTRC_BHOT_MASK		(BIT(3) | BIT(2))
#define BQ2429X_REG_BVTRC_BHOT_SHIFT		2
#define BQ2429X_REG_BVTRC_TREG_MASK		(BIT(1) | BIT(0))
#define BQ2429X_REG_BVTRC_TREG_SHIFT		0

#define BQ2429X_REG_MOC		0x07 /* Misc. Operation Control */
#define BQ2429X_REG_MOC_DPDM_EN_MASK		BIT(7)
#define BQ2429X_REG_MOC_DPDM_EN_SHIFT		7
#define BQ2429X_REG_MOC_TMR2X_EN_MASK		BIT(6)
#define BQ2429X_REG_MOC_TMR2X_EN_SHIFT		6
#define BQ2429X_REG_MOC_BATFET_DISABLE_MASK	BIT(5)
#define BQ2429X_REG_MOC_BATFET_DISABLE_SHIFT	5
#define BQ2429X_REG_MOC_JEITA_VSET_MASK		BIT(4)
#define BQ2429X_REG_MOC_JEITA_VSET_SHIFT	4
#define BQ2429X_REG_MOC_INT_MASK_MASK		(BIT(1) | BIT(0))
#define BQ2429X_REG_MOC_INT_MASK_SHIFT		0

#define BQ2429X_REG_SS		0x08 /* System Status */
#define BQ2429X_REG_SS_VBUS_STAT_MASK		(BIT(7) | BIT(6))
#define BQ2429X_REG_SS_VBUS_PLUGGED		BIT(6)
#define BQ2429X_REG_SS_VBUS_STAT_SHIFT		6
#define BQ2429X_REG_SS_CHRG_STAT_MASK		(BIT(5) | BIT(4))
#define BQ2429X_REG_SS_CHRG_STAT_SHIFT		4
#define BQ2429X_REG_SS_DPM_STAT_MASK		BIT(3)
#define BQ2429X_REG_SS_DPM_STAT_SHIFT		3
#define BQ2429X_REG_SS_PG_STAT_MASK		BIT(2)
#define BQ2429X_REG_SS_PG_STAT_SHIFT		2
#define BQ2429X_REG_SS_THERM_STAT_MASK		BIT(1)
#define BQ2429X_REG_SS_THERM_STAT_SHIFT		1
#define BQ2429X_REG_SS_VSYS_STAT_MASK		BIT(0)
#define BQ2429X_REG_SS_VSYS_STAT_SHIFT		0

#define BQ2429X_REG_F		0x09 /* Fault */
#define BQ2429X_REG_F_WATCHDOG_FAULT_MASK	BIT(7)
#define BQ2429X_REG_F_WATCHDOG_FAULT_SHIFT	7
#define BQ2429X_REG_F_BOOST_FAULT_MASK		BIT(6)
#define BQ2429X_REG_F_BOOST_FAULT_SHIFT		6
#define BQ2429X_REG_F_CHRG_FAULT_MASK		(BIT(5) | BIT(4))
#define BQ2429X_REG_F_CHRG_FAULT_SHIFT		4
#define BQ2429X_REG_F_BAT_FAULT_MASK		BIT(3)
#define BQ2429X_REG_F_BAT_FAULT_SHIFT		3
#define BQ2429X_REG_F_NTC_FAULT_MASK		(BIT(2) | BIT(1) | BIT(0))
#define BQ2429X_REG_F_NTC_FAULT_SHIFT		0

#define BQ2429X_REG_VPRS	0x0A /* Vendor/Part/Revision Status */
#define BQ2429X_REG_VPRS_PN_MASK		(BIT(7) | BIT(6) | BIT(5))
#define BQ2429X_REG_VPRS_PN_SHIFT		5
#define BQ2429X_REG_VPRS_PN_24296			0x1
#define BQ2429X_REG_VPRS_PN_24297			0x3
#define BQ2429X_REG_VPRS_REV_MASK		(BIT(2) | BIT(1) | BIT(0))
#define BQ2429X_REG_VPRS_REV_SHIFT		0

/*Options For Setting*/
#define BQ2429X_REG_SS_CHRGDONE		(0x30)
#define BQ2429X_REG_SS_DPM		(0x08)
#define BQ2429X_REG_SS_PG		(0x04)
#define BQ2429X_REG_SS_NOTPG		(0x00)

#define BQ2429X_REG_F_WDT_TIMEOUT	             (0x80)
#define BQ2429X_REG_F_BOOST_OCP	      (0x40)
#define BQ2429X_REG_F_VBUS_OVP	      (0x10)
#define BQ2429X_REG_F_BATT_OVP	      (0x08)

#endif
