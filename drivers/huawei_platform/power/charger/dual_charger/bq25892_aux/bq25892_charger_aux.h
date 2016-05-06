/*
 * Copyright (C) 2012-2015 HUAWEI
 * Author:  L.JH HW
 */

#include <linux/i2c.h>      /*for struct bq25899x_device_info*/
#include <linux/device.h>   /*for struct bq2589x_device_info*/
#include <linux/workqueue.h>    /*for struct bq2589x_device_info*/

#ifndef _BQ25892_CHARGER_AUX
#define _BQ25892_CHARGER_AUX

#ifndef BIT
#define BIT(x)    (1 << (x))
#endif

/*************************struct define area***************************/
struct param {
    int bat_comp;
    int vclamp;
    int fcp_support;
};
struct bq25892_aux_device_info {
    struct i2c_client *client;
    struct device *dev;
    struct work_struct irq_work;
    struct param param_dts;
    int gpio_cd;
    int gpio_int;
    int irq_int;
    int irq_active;
};
/*************************marco define area***************************/
#define BQ25892_AUX_REG_TOTAL_NUM   (21)

/**/
#define BQ25892_AUX_REG_NONE 0x00
#define BQ25892_AUX_REG_NONE_NONE_MASK  (0xFF)
#define BQ25892_AUX_REG_NONE_NONE_SHIFT (0x00)


/*EN_HIZ / EN_ILIM / IINLIM   Register REG0x00*/
#define BQ25892_AUX_REG_00     0x00
#define BQ25892_AUX_REG_00_IINLIM_MASK (BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define BQ25892_AUX_REG_00_IINLIM_SHIFT (0)
#define BQ25892_AUX_REG_00_EN_HIZ_MASK      BIT(7)
#define BQ25892_AUX_REG_00_EN_HIZ_SHIFT   (7)
#define BQ25892_AUX_REG_00_EN_ILIM_MASK      BIT(6)
#define BQ25892_AUX_REG_00_EN_ILIM_SHIFT   (6)
#define IINLIM_MIN_100          (100)
#define IINLIM_STEP_50          (50)
#define IINLIM_MAX_3250       (3250)


/*BHOT / BCOLD / VINDPM_OS  Register REG0x01*/
#define BQ25892_AUX_REG_01     0x01
#define BQ25892_AUX_REG_01_VINDPM_OS_MASK      (BIT(4)  | BIT(3) | BIT(2) | BIT(1) |BIT(0))
#define BQ25892_AUX_REG_01_VINDPM_OS_SHIFT   (0)
#define BHOT_THRESHOLD_37   (0 << 6)
#define BHOT_THRESHOLD_34   (1 << 6)
#define BCOLD_THRESHOLD_77  (0 << 5)
#define BCOLD_THRESHOLD_80  (1 << 5)
#define VINDPM_OS_MAX_3100  (3100)
#define VINDPM_OS_STEP_100      (100)
#define VINDPM_OS_DEFAULT_600   (600)

/*CONV_START / CONV_RATE / BOOST_FREQ / ICO_EN / HVDCP_EN / MAXC_EN / FORCE_DPDM / AUTO_DPDM_EN  Register REG0x02*/
#define BQ25892_AUX_REG_02     0x02
#define BQ25892_AUX_REG_02_CONV_START_MASK      BIT(7)
#define BQ25892_AUX_REG_02_CONV_START_SHIFT   (7)
#define BQ25892_AUX_REG_02_ICO_EN_MASK      BIT(4)
#define BQ25892_AUX_REG_02_ICO_EN_SHIFT   (4)
#define BQ25892_AUX_REG_02_FORCE_DPDM_MASK      BIT(1)
#define BQ25892_AUX_REG_02_FORCE_DPDM_SHIFT   (1)
#define BQ25892_AUX_REG_02_AUTO_DPDM_EN_MASK      BIT(0)
#define BQ25892_AUX_REG_02_AUTO_DPDM_EN_SHIFT   (0)

#define BQ25892_AUX_CONV_START_SHIFT           (7)
#define EN_ADC_CONVERSION               (1)
#define DIS_ADC_CONVERSION              (0)
#define BQ25892_AUX_CONV_RATE_SHIFT           (6)
#define ONE_SHORT_ADC_MODE                      (0)
#define ONE_SECOND_CONTINUOUS_ADC_MODE      (1)
#define BQ25892_AUX_BOOST_FREQ_SHIFT          5
#define FREQ_1500K_HZ                   (0)
#define FREQ_500K_HZ                   (1)
#define BQ25892_AUX_ICO_EN_SHIFT           4
#define EN_ICO                      (1)
#define DIS_ICO                     (0)
#define BQ25892_AUX_HVDCP_HANDSHAKE_EN_SHIFT           (3)
#define EN_HVDCP_HANDSHAKE      (1)
#define DIS_HVDCP_HANDSHAKE      (0)
#define BQ25892_AUX_MAXC_EN_SHIFT           2
#define EN_MAXC                     (1)
#define DIS_MAXC                    (0)
#define BQ25892_AUX_FORCE_DPDM_SHIFT       1
#define FORCE_DPDM_EN                            (1)
#define FORCE_DPDM_DIS                           (0)




/*BAT_LOADEN / WD_RST / OTG_CONFIG / CHG_CONFIG / SYS_MIN  Register REG0x03*/
#define BQ25892_AUX_REG_03     0x03

#define BQ25892_AUX_REG_03_CHG_CONFIG_MASK (BIT(5) | BIT(4))
#define BQ25892_AUX_REG_03_CHG_CONFIG_SHIFT  (4)

#define BQ25892_AUX_REG_03_OTG_CONFIG_MASK BIT(5)
#define BQ25892_AUX_REG_03_OTG_CONFIG_SHIFT 5

#define BQ25892_AUX_REG_03_WDT_RESET_MASK BIT(6)
#define BQ25892_AUX_REG_03_WDT_RESET_SHIFT 6

#define BQ25892_AUX_REG_03_SYS_MIN_MASK (BIT(3)|BIT(2)|BIT(1))
#define BQ25892_AUX_REG_03_SYS_MIN_SHIFT (1)

#define BAT_LOADEN_SHIFT               7
#define EN_BAT_LOADEN                   (1)
#define DIS_BAT_LOADEN                  (0)
#define WATCHDOG_TIMER_RST    (1 << 6)
#define BQ25892_AUX_EN_CHARGER_SHIFT    4
#define DIS_CHARGER                (0)
#define EN_CHARGER                 (1)
#define BQ25892_AUX_EN_OTG_SHIFT    5
#define EN_OTG             (1)
#define DIS_OTG             (0)
#define BQ25892_AUX_SYS_MIN_SHIFT       1
#define SYS_MIN_MIN_3000        (3000)
#define SYS_MIN_3500            (3500)
#define SYS_MIN_MAX_3700        (3700)
#define SYS_MIN_STEP_100        (100)



/*ICHG  Register REG0x04*/
#define BQ25892_AUX_REG_04     0x04

#define BQ25892_AUX_REG_04_ICHG_MASK (BIT(6) | BIT(5) | BIT(4) |\
	BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define BQ25892_AUX_REG_04_ICHG_SHIFT  (0)
#define ICHG_MAX_5056                (5056)
#define ICHG_STEP_64         (64)
#define ICHG_512                 (512)
#define ICHG_1024               (1024)
#define ICHG_2048               (2048)
#define ICHG_4096               (4096)




/*IPRECHG / ITERM Register REG0x05*/
#define BQ25892_AUX_REG_05     0x05
#define BQ25892_AUX_REG_05_IPRECHG_MASK (BIT(7) | BIT(6) | BIT(5) | BIT(4))
#define BQ25892_AUX_REG_05_IPRECHG_SHIFT 4

#define BQ25892_AUX_REG_05_ITERM_MASK (BIT(3) | BIT(2) | BIT(1) | BIT(0))

#define BQ25892_AUX_REG_05_ITERM_SHIFT  (0)


//#define BQ25892_IPRECHRG_SHIFT  4
#define IPRECHRG_MIN_64    (64)
#define IPRECHRG_MAX_1024  (1024)
#define IPRECHRG_STEP_64   (64)
#define IPRECHRG_256        (256)

#define ITERM_MIN_64       (64)
#define ITERM_MAX_1024     (1024)
#define ITERM_STEP_64      (64)
#define ITERM_256           (256)


/*Charge Voltage Limit / BATLOWV / VRECHG  Register REG0x06*/
#define BQ25892_AUX_REG_06     0x06
#define BQ25892_AUX_REG_06_VREG_MASK (BIT(7) | BIT(6) | BIT(5) | \
	BIT(4) | BIT(3) | BIT(2))
#define  BQ25892_AUX_REG_06_VREG_SHIFT  2
#define  BQ25892_AUX_REG_06_BATLOWV_MASK  BIT(1)

#define BQ25892_AUX_REG_06_BATLOWV_SHIFT 1

#define  BQ25892_AUX_REG_06_VRECHG_MASK  BIT(0)

#define BQ25892_AUX_REG_06_VRECHG_SHIFT 0


#define BQ25892_AUX_VCHARGE_SHIFT             2
#define VCHARGE_MIN_3840              (3840)
#define VCHARGE_MAX_4496              (4496)
#define VCHARGE_STEP_16               (16)
#define VCHARGE_4352                  (4352)

#define BATLOWV_3000                 (1 << 1)
#define BATLOWV_2800                 (0 << 1)
#define VRECHG_300                   (1 << 0)
#define VRECHG_100                   (0 << 0)



/*EN_TERM / WATCHDOG / EN_TIMER / CHG_TIMER  Register REG0x07*/
#define BQ25892_AUX_REG_07     0x07

#define BQ25892_AUX_REG_07_EN_TERM_MASK (BIT(7))
#define BQ25892_AUX_REG_07_EN_TERM_SHIFT 7
#define BQ25892_AUX_REG_07_WATCHDOG_MASK (BIT(5) | BIT(4))
#define BQ25892_AUX_REG_07_WATCHDOG_SHIFT 4
#define BQ25892_AUX_REG_07_EN_TIMER_MASK  BIT(3)
#define BQ25892_AUX_REG_07_EN_TIMER_SHIFT 3
#define BQ25892_AUX_REG_07_CHG_TIMER_MASK (BIT(2) | BIT(1))
#define BQ25892_AUX_REG_07_CHG_TIMER_SHIFT 1
#define BQ25892_AUX_REG_07_JEITA_ISET_MASK  BIT(0)
#define BQ25892_AUX_REG_07_JEITA_ISET_SHIFT 0

#define BQ25892_AUX_REG_07_WATCHDOG_DIS              (0)
#define BQ25892_AUX_REG_07_WATCHDOG_40                (1)
#define BQ25892_AUX_REG_07_WATCHDOG_80                (2)
#define BQ25892_AUX_REG_07_WATCHDOG_160              (3)
#define WATCHDOG_TIMER_40_S                               (40)
#define WATCHDOG_TIMER_80_S                               (80)
#define WATCHDOG_TIMER_160_S                             (160)

/*IR Compensation Resistor Setting / IR Compensation Voltage Clamp / Thermal Regulation Threshold Register REG0x08*/
#define BQ25892_AUX_REG_08     0x08

#define BQ25892_AUX_REG_08_BAT_COMP_MASK (BIT(7) | BIT(6) | BIT(5))
#define BQ25892_AUX_REG_08_BAT_COMP_SHIFT 5

#define BQ25892_AUX_REG_08_VCLAMP_MASK (BIT(4) | BIT(3) | BIT(2))
#define BQ25892_AUX_REG_08_VCLAMP_SHIFT 2

#define BQ25892_AUX_REG_08_TREG_MASK (BIT(1) | BIT(0))
#define BQ25892_AUX_REG_08_TREG_SHIFT 0


#define BQ25892_AUX_BAT_COMP_SHIFT      5
#define BAT_COMP_MIN_0             (0)
#define BAT_COMP_MAX_140           (140)
#define BAT_COMP_STEP_20          (20)
#define BAT_COMP_40               (40)
#define BQ25892_AUX_VCLAMP_SHIFT        2
#define VCLAMP_MIN_0               (0)
#define VCLAMP_MAX_224           (224)
#define VCLAMP_STEP_32            (32)
#define VCLAMP_64                 (64)
#define TREG_120                   (3)
#define TREG_100                   (2)
#define TREG_80                    (1)
#define TREG_60                    (0)


/*FORCE_ICO / TMR2X_EN / BATFET_DIS / JEITA_VSET / BATFET_RST_EN  Register REG0x09*/
#define BQ25892_AUX_REG_09     0x09

#define BQ25892_AUX_REG_09_FORCE_ICO_MASK BIT(7)
#define BQ25892_AUX_REG_09_FORCE_ICO_SHIFT 7

#define BQ25892_AUX_REG_09_BATFET_DISABLE_MASK BIT(5)
#define BQ25892_AUX_REG_09_BATFET_DISABLE_SHIFT 5

#define BQ25892_AUX_REG_09_JEITA_VSET_MASK BIT(4)
#define BQ25892_AUX_REG_09_JEITA_VSET_SHIFT 4

#define BQ25892_AUX_FORCE_ICO_SHIFT    7
#define EN_FORCE_ICO                   (1)
#define DIS_FORCE_ICO                   (0)
#define TMR2X_EN                      (1 << 6)
#define TMR2X_DIS                   (0 << 6)
#define BQ25892_AUX_BATFET_EN_SHIFT              5
#define EN_BATFET                          (0)
#define DIS_BATFET                         (1)
#define BQ25892_AUX_JEITA_VSET_VREG_SHIFT   4
#define JEITA_VSET_VREG_150        (0)  //Set Charge Voltage to VREG-150mV
#define JEITA_VSET_VREG               (1)
#define BQ25892_AUX_BATFET_RST_EN_SHIFT     2
#define EN_BATFET_RST       (1)
#define DIS_BATFET_RST      (0)




/* Boost Mode Voltage Regulation / Boost Mode Current Limit Register REG0x0A*/
#define BQ25892_AUX_REG_0A     0x0A
#define BQ25892_AUX_REG_0A_BOOSTV_MASK (BIT(7) | BIT(6) | BIT(5) | BIT(4))
#define BQ25892_AUX_REG_0A_BOOSTV_SHIFT  (4)


#define BQ25892_AUX_REG_0A_BOOST_LIM_MASK (BIT(2) | BIT(1) | BIT(0))
#define BQ25892_AUX_REG_0A_BOOST_LIM_SHIFT  (0)

#define BQ25892_AUX_BOOSTV_SHIFT    4
#define BOOSTV_MIN_4550             (4550)
#define BOOSTV_DEFAULT_4998     (4998)
#define BOOSTV_MAX_5510             (5510)
#define BOOSTV_STEP_64                 (64)
#define BOOST_LIM_MIN_500       (500)
#define BOOST_LIM_750        (750)
#define BOOST_LIM_1200        (1200)
#define BOOST_LIM_1400        (1400)
#define BOOST_LIM_1650        (1650)
#define BOOST_LIM_1875        (1875)
#define BOOST_LIM_2150        (2150)
#define BOOST_LIM_MAX_2450      (2450)




/*Read-only / VBUS_STAT /CHRG_STAT /PG_STAT / SDP_STAT / VSYS_STAT Status Register REG0x0B*/
#define  BQ25892_AUX_REG_0B     0x0B
#define  BQ25892_AUX_REG_0B_VBUS_STAT_MASK  (BIT(7) | BIT(6) | BIT(5))
#define  BQ25892_AUX_REG_0B_VBUS_STAT_SHIFT 5

#define  BQ25892_AUX_REG_0B_CHRG_STAT_MASK (BIT(4) | BIT(3))
#define  BQ25892_AUX_REG_0B_CHRG_STAT_SHIFT 3

#define  BQ25892_AUX_REG_0B_PG_STAT_MASK BIT(2)
#define  BQ25892_AUX_REG_0B_PG_STAT_SHIFT 2
#define  BQ25892_AUX_REG_0B_SDP_STAT_MASK BIT(1)
#define  BQ25892_AUX_REG_0B_SDP_STAT_SHIFT 1

#define  BQ25892_AUX_REG_0B_VSYS_STAT_MASK BIT(0)
#define  BQ25892_AUX_REG_0B_VSYS_STAT_SHIFT 0

#define BQ25892_AUX_VBUS_STAT_UNKNOWM        (0x00)
#define BQ25892_AUX_VBUS_STAT_USB_HOST       (0x20)
#define BQ25892_AUX_VBUS_STAT_ADATPTER       (0x40)
#define BQ25892_AUX_CHGR_STAT_NOT_CHARGING   (0x00)
#define BQ25892_AUX_CHGR_STAT_PRE_CHARGING   (0x08)
#define BQ25892_AUX_CHGR_STAT_FAST_CHARGING  (0x10)
#define BQ25892_AUX_CHGR_STAT_CHARGE_DONE    (BIT(4) | BIT(3))
#define BQ25892_AUX_PG_STAT                  (0x04)
#define BQ25892_AUX_NOT_PG_STAT              (0x04)
#define BQ25892_AUX_VSYS_STAT                (0x01)

/*Read-only / WATCHDOG_FAULT / BOOST_FAULT / CHRG_FAULT / BAT_FAULT / NTC_FAULT  Status Register REG0x0C*/
#define BQ25892_AUX_REG_0C     0x0C

#define BQ25892_AUX_REG_0C_WATCHDOG_FAULT_MASK BIT(7)
#define BQ25892_AUX_REG_0C_WATCHDOG_FAULT_SHIFT 7

#define BQ25892_AUX_REG_0C_BOOST_FAULT_MASK BIT(6)
#define BQ25892_AUX_REG_0C_BOOST_FAULT_SHIFT 6

#define BQ25892_AUX_REG_0C_CHRG_FAULT_MASK (BIT(5) | BIT(4))
#define BQ25892_AUX_REG_0C_CHRG_FAULT_SHIFT 4

#define BQ25892_AUX_REG_0C_BAT_FAULT_MASK BIT(3)
#define BQ25892_AUX_REG_0C_BAT_FAULT_SHIFT 3

#define BQ25892_AUX_REG_0C_NTC_FAULT_MASK (BIT(2) | BIT(1) | BIT(0))
#define BQ25892_AUX_REG_0C_NTC_FAULT_SHIFT 0

#define BQ25892_AUX_POWER_SUPPLY_OVP            (1 << 4)
#define BQ25892_AUX_THERMAL_SHUTDOWN        (2 << 4)
#define BQ25892_AUX_WATCHDOG_FAULT      (1 << 7)
#define BQ25892_AUX_OTG_FAULT             (1 << 6)
#define BQ25892_AUX_BAT_FAULT_OVP                  (1 << 3)
#define BQ25892_AUX_NTC_WARM                  (0x02)
#define BQ25892_AUX_NTC_COOL                  (0x03)
#define BQ25892_AUX_NTC_COLD                  (0x05)
#define BQ25892_AUX_NTC_HOT                  (0x06)
#define BQ25892_AUX_REG_0C_BOOST 0x40


/*FORCE_VINDPM /VINDPM Threshold  Register REG0x0D*/
#define BQ25892_AUX_REG_0D 0x0D
#define BQ25892_AUX_REG_0D_VINDPM_MASK    (BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define BQ25892_AUX_REG_0D_VINDPM_SHIFT  0

#define BQ25892_AUX_REG_0D_FORCE_VINDPM_MASK BIT(7)
#define BQ25892_AUX_REG_0D_FORCE_VINDPM_SHIFT      7

#define EN_ABSOLUTE_VINDPM             (1)
#define EN_RELATIVE_VINDPM              (0)
#define VINDPM_MAX_15300            (15300)
#define VINDPM_MIN_3900                (3900)
#define VINDPM_OFFSET_2600          (2600)
#define VINDPM_STEP_100                 (100)


/*Read-only / THERM_STAT / VBAT Voltage Register REG0x0E*/
#define BQ25892_AUX_REG_0E     0x0E
#define BQ25892_AUX_REG_0E_THERM_STAT_MASK BIT(7)
#define BQ25892_AUX_REG_0E_THERM_STAT_SHIFT      7
#define BQ25892_AUX_REG_0E_BATV_MASK (BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define BQ25892_AUX_REG_0E_BATV_SHIFT      0

#define BQ25892_AUX_REG_0E_VBAT_STEP_MV    (20)
#define BQ25892_AUX_REG_0E_VBAT_OFFSET_MV  (2304)

/*Read-only /System Voltage (VSYS) Register REG0x0F*/
#define BQ25892_AUX_REG_0F     0x0F
#define BQ25892_AUX_REG_0F_SYSV_MASK (BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define BQ25892_AUX_REG_0F_SYSV_SHIFT      0


/*Read-only / TS Voltage as percentage of REGN Register REG0x10*/
#define BQ25892_AUX_REG_10     0x10

/*Read-only / VBUS Good Status /VBUS voltage Register REG0x11*/
#define BQ25892_AUX_REG_11     0x11
#define BQ25892_AUX_REG_11_VBUSV_MASK (BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define BQ25892_AUX_REG_11_VBUSV_SHIFT      0

#define BQ25892_AUX_REG_11_VBUSV_STEP_MV    (100)
#define BQ25892_AUX_REG_11_VBUSV_OFFSET_MV  (2600)
#define BQ25892_AUX_REG_11_VBUS_GD_MASK     BIT(7)

/*Read-only / ICHGR Current Register REG0x12*/
#define BQ25892_AUX_REG_12     0x12
#define BQ25892_AUX_REG_12_ICHGR_MASK (BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define BQ25892_AUX_REG_12_ICHGR_SHIFT      0

#define BQ25892_AUX_REG_12_ICHGR_STEP_MA    (50)
#define BQ25892_AUX_REG_12_ICHGR_OFFSET_MA  (0)

/*Read-only / VDPM_STAT / IDPM_STAT / IDPM_LIM Status Register REG0x13*/
#define BQ25892_AUX_REG_13     0x13
#define BQ25892_AUX_REG_13_VDPM_STAT_MASK BIT(7)
#define BQ25892_AUX_REG_13_VDPM_STAT_SHIFT      7
#define BQ25892_AUX_REG_13_IDPM_STAT_MASK BIT(6)
#define BQ25892_AUX_REG_13_IDPM_STAT_SHIFT      6
#define BQ25892_AUX_REG_13_IDPM_LIM_MASK (BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define BQ25892_AUX_REG_13_IDPM_LIM_SHIFT      0


/*REG_RST / ICO_OPTIMIZED / Revision Status Register REG0x14*/
#define BQ25892_AUX_REG_14     0x14
#define BQ25892_AUX_REG_14_REG_RST_MASK BIT(7)
#define BQ25892_AUX_REG_14_REG_RST_SHIFT      7
#define BQ25892_AUX_REG_14_ICO_OPTIMIZED_MASK BIT(6)
#define BQ25892_AUX_REG_14_ICO_OPTIMIZED_SHIFT      6


#define CHIP_VERSION_MASK   (0x38)
#define CHIP_REVISION_MASK  (0x03)
#define BQ25890 (0x10)
#define BQ25892 (0x00)
#define BQ25895 (0x30)
#define CHIP_REVISION (0x01)

#endif
