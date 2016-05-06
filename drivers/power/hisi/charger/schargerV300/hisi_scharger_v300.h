//****************************************************************************** 
// Copyright     :  Copyright (C) 2015, Hisilicon Technologies Co., Ltd.
// File name     :  hisi_scharger_v300.h
// Version       :  1.0 
// Date          :  2015-05-06
// Description   :  Define all registers/tables for HI6523

// ******************************************************************************

#ifndef __HI6523_CHARGER_H__
#define __HI6523_CHARGER_H__
#include <soc_schargerV300_interface.h>
#include <linux/i2c.h>      /*for struct device_info*/
#include <linux/device.h>   /*for struct device_info*/
#include <linux/workqueue.h>    /*for struct evice_info*/
#include <usb/switch/switch_chip.h>

extern int fsa9685_manual_sw(int input_select);

#define HI6523_MODULE_NAME              hi6523
#define HI6523_MODULE_NAME_STR          "hi6523"
#define HI6523_I2C_SLAVE_ADDRESS        (0x6B)
#define CHG_ENABLE                      (1)
#define CHG_DISABLE                     (0)

#define HI6523_REG_TOTAL_NUM            (0xEB)
#define HI6523_VBUS_STAT_UNKNOWN        (0x00)

#define CHG_NONE_REG                    (0x00)
#define CHG_NONE_MSK                   (0xFF)
#define CHG_NONE_SHIFT                  (0x00)

#ifndef BIT
#define BIT(x)                          (1 << (x))
#endif

#define SCHARGER_ERR(fmt,args...) do { printk(KERN_ERR    "[hisi_scharger]" fmt, ## args); } while (0)
#define SCHARGER_EVT(fmt,args...) do { printk(KERN_WARNING"[hisi_scharger]" fmt, ## args); } while (0)
#define SCHARGER_INF(fmt,args...) do { printk(KERN_INFO   "[hisi_scharger]" fmt, ## args); } while (0)
/*************************struct define area***************************/
struct param {
    int bat_comp;
    int vclamp;
    int fcp_support;
};
struct hi6523_device_info {
    struct i2c_client *client;
    struct device *dev;
    struct notifier_block   usb_nb;
    struct delayed_work plugout_check_work;
    struct work_struct irq_work;
    struct param param_dts;
    int gpio_cd;
    int gpio_int;
    int irq_int;
};

/******************************************************************************/
/*                      HI6523 Registers' Definitions                         */
/******************************************************************************/
#define CHIP_VERSION_0 (SOC_SCHARGER_CHIP_VERSION_0_ADDR(0))
#define CHIP_VERSION_1 (SOC_SCHARGER_CHIP_VERSION_1_ADDR(0))
#define CHIP_VERSION_2 (SOC_SCHARGER_CHIP_VERSION_2_ADDR(0))
#define CHIP_VERSION_3 (SOC_SCHARGER_CHIP_VERSION_3_ADDR(0))
#define CHIP_VERSION_4 (SOC_SCHARGER_CHIP_VERSION_4_ADDR(0))
#define CHIP_VERSION_5 (SOC_SCHARGER_CHIP_VERSION_5_ADDR(0))
#define CHIP_ID0 (0x03)

#define CHG_STATUS0_REG                 (SOC_SCHARGER_STATUS0_ADDR(0))
#define CHG_BUCK_OK                     (1<<SOC_SCHARGER_STATUS0_buck_ok_START)

/* BUCK_REG0调节寄存器。 */
/* buck平均限流环设定电流：00000：100mA；00001：150mA；00010：500mA；00011：900mA；00100：1A；00101：1.2A；00110：1.3A；00111：1.4A；01000：1.5A；01001：1.6A；01010：1.7A；01011：1.8A；01100：1.9A；01101：2A；01110：2.1A；01111：2.2A；10000：2.4A；10001：2.6A；10010：2.8A；10011：3A；10100：3.2A；10101~11111:3.2A。 */
#define CHG_INPUT_SOURCE_REG            (SOC_SCHARGER_BUCK_REG0_ADDR(0))
#define CHG_ILIMIT_SHIFT                (SOC_SCHARGER_BUCK_REG0_buck_ilimit_START)
#define CHG_ILIMIT_MSK                  (0x1f<<CHG_ILIMIT_SHIFT)

#define CHG_ILIMIT_100                  (100)
#define CHG_ILIMIT_150                  (150)
#define CHG_ILIMIT_500                  (500)
#define CHG_ILIMIT_900                  (900)
#define CHG_ILIMIT_1000                 (1000)
#define CHG_ILIMIT_1200                 (1200)
#define CHG_ILIMIT_1300                 (1300)
#define CHG_ILIMIT_1400                 (1400)
#define CHG_ILIMIT_1500                 (1500)
#define CHG_ILIMIT_1600                 (1600)
#define CHG_ILIMIT_1700                 (1700)
#define CHG_ILIMIT_1800                 (1800)
#define CHG_ILIMIT_1900                 (1900)
#define CHG_ILIMIT_2000                 (2000)
#define CHG_ILIMIT_2100                 (2100)
#define CHG_ILIMIT_2200                 (2200)
#define CHG_ILIMIT_2400                 (2400)
#define CHG_ILIMIT_2600                 (2600)
#define CHG_ILIMIT_2800                 (2800)
#define CHG_ILIMIT_3000                 (3000)
#define CHG_ILIMIT_3200                 (3200)

/* CHG_REG1调节寄存器 */
#define CHG_FAST_CURRENT_REG            (SOC_SCHARGER_CHG_REG1_ADDR(0))
#define CHG_FAST_ICHG_SHIFT             (SOC_SCHARGER_CHG_REG1_chg_fast_ichg_START)
#define CHG_FAST_ICHG_MSK               (0x1f<<CHG_FAST_ICHG_SHIFT)
#define CHG_FAST_ICHG_STEP_100          (100)
#define CHG_FAST_ICHG_STEP_200          (200)
#define CHG_FAST_ICHG_100MA             (100)
#define CHG_FAST_ICHG_200MA             (200)
#define CHG_FAST_ICHG_300MA             (300)
#define CHG_FAST_ICHG_400MA             (400)
#define CHG_FAST_ICHG_500MA             (500)
#define CHG_FAST_ICHG_600MA             (600)
#define CHG_FAST_ICHG_700MA             (700)
#define CHG_FAST_ICHG_800MA             (800)
#define CHG_FAST_ICHG_900MA             (900)
#define CHG_FAST_ICHG_1000MA            (1000)
#define CHG_FAST_ICHG_1200MA            (1200)
#define CHG_FAST_ICHG_1400MA            (1400)
#define CHG_FAST_ICHG_1600MA            (1600)
#define CHG_FAST_ICHG_1800MA            (1800)
#define CHG_FAST_ICHG_2000MA            (2000)
#define CHG_FAST_ICHG_2200MA            (2200)
#define CHG_FAST_ICHG_2400MA            (2400)
#define CHG_FAST_ICHG_2600MA            (2600)
#define CHG_FAST_ICHG_2800MA            (2800)
#define CHG_FAST_ICHG_3000MA            (3000)
#define CHG_FAST_ICHG_3200MA            (3200)
#define CHG_FAST_ICHG_3400MA            (3400)
#define CHG_FAST_ICHG_3600MA            (3600)
#define CHG_FAST_ICHG_3800MA            (3800)
#define CHG_FAST_ICHG_4000MA            (4000)
#define CHG_FAST_ICHG_4200MA            (4200)
#define CHG_FAST_ICHG_4500MA            (4500)

/* DET_TOP_REG0调节寄存器 */
#define CHG_VBUS_VSET_REG               (SOC_SCHARGER_DET_TOP_REG0_ADDR(0))
/* 适配器输入电压档位配置：00：5V；01：9V；10&11：12V。 */
#define VBUS_VSET_SHIFT                 (SOC_SCHARGER_DET_TOP_REG0_vbus_vset_START)
#define VBUS_VSET_MSK                   (0x03<<VBUS_VSET_SHIFT)
#define VBUS_VSET_5V                    (5)
#define VBUS_VSET_9V                    (9)
#define VBUS_VSET_12V                   (12) 

/* BUCK_REG2调节寄存器。 */ 
#define CHG_DPM_SEL_REG                 (SOC_SCHARGER_BUCK_REG2_ADDR(0))
/* DPM输入电压设定：000：82.5%;001：85%；010：87.5%；011：90%；100：92.5%；101：95%。 */
#define CHG_DPM_SEL_SHIFT               (SOC_SCHARGER_BUCK_REG2_buck_dpm_sel_START)
#define CHG_DPM_SEL_MSK                 (0x07<<CHG_DPM_SEL_SHIFT)
#define CHG_DPM_SEL_82_5                (0)
#define CHG_DPM_SEL_85_0                (1)
#define CHG_DPM_SEL_87_5                (2)
#define CHG_DPM_SEL_90_0                (3)
#define CHG_DPM_SEL_92_5                (4)
#define CHG_DPM_SEL_95_0                (5)
#define VINDPM_4520                     (4520)
#define VINDPM_4700                     (4700)
/* CHG_REG0调节寄存器。 */
/* charger使能信号：0：关闭；1：使能。 */
#define CHG_ENABLE_REG                  (SOC_SCHARGER_CHG_REG0_ADDR(0))
#define CHG_EN_SHIFT                    (SOC_SCHARGER_CHG_REG0_chg_en_START)
#define CHG_EN_MSK                      (1<<CHG_EN_SHIFT)

#define BATFET_CTRL_CFG_REG             (SOC_SCHARGER_CHG_REG0_ADDR(0))
/* batfet_ctrl配置寄存器该寄存器除了受到pwr_rst_n复位外，还受到模拟送给数字另外一个信号dc_plug_n控制：0：关闭batfet；1：打开batfet。 */
#define BATFET_CTRL_CFG_SHIFT           (SOC_SCHARGER_CHG_REG0_batfet_ctrl_cfg_START)
#define BATFET_CTRL_CFG_MSK             (1<<BATFET_CTRL_CFG_SHIFT)
#define CHG_BATFET_DIS                  (0)
#define CHG_BATFET_EN                   (1)

#define CHG_PRE_ICHG_REG                (SOC_SCHARGER_CHG_REG0_ADDR(0))
/* 预充电电流大小调节位：00：100mA；01：200mA；10：300mA；11：400mA。 */
#define CHG_PRE_ICHG_SHIFT              (SOC_SCHARGER_CHG_REG0_chg_pre_ichg_START)
#define CHG_PRE_ICHG_MSK                (0x03<<CHG_PRE_ICHG_SHIFT)
#define CHG_PRG_ICHG_STEP               (100)
#define CHG_PRG_ICHG_MIN                (100)
#define CHG_PRG_ICHG_100MA              (100)
#define CHG_PRG_ICHG_200MA              (200)
#define CHG_PRG_ICHG_300MA              (300)
#define CHG_PRG_ICHG_400MA              (400)
#define CHG_PRG_ICHG_MAX                (400)

#define CHG_PRE_VCHG_REG                (SOC_SCHARGER_CHG_REG0_ADDR(0))
/* 预充电电压阈值大小调节位：00：2.8V；01：3.0V；10：3.1V；11：3.2V。 */
#define CHG_PRE_VCHG_SHIFT              (SOC_SCHARGER_CHG_REG0_chg_pre_vchg_START)
#define CHG_PRE_VCHG_MSK                (0x03<<CHG_PRE_VCHG_SHIFT)
#define CHG_PRG_VCHG_2800               (2800)
#define CHG_PRG_VCHG_3000               (3000)
#define CHG_PRG_VCHG_3100               (3100)
#define CHG_PRG_VCHG_3200               (3200)

/* CHG_REG3调节寄存器。 */

/* 快充安全计时器（小时）：00：5 h；01：8 h；10：12 h；11：20 h。 */
#define CHG_FASTCHG_TIMER_REG           (SOC_SCHARGER_CHG_REG3_ADDR(0))
#define CHG_FASTCHG_TIMER_SHIFT         (SOC_SCHARGER_CHG_REG3_chg_fastchg_timer_START)
#define CHG_FASTCHG_TIMER_MSK           (0x03<<CHG_FASTCHG_TIMER_SHIFT)
#define CHG_FASTCHG_TIMER_5H            (0)
#define CHG_FASTCHG_TIMER_8H            (1)
#define CHG_FASTCHG_TIMER_12H           (2)
#define CHG_FASTCHG_TIMER_20H           (3)

/* CHG_REG4调节寄存器。 */
/* 终止充电控制位：0：Disabled；1：Enabled。 */
#define CHG_EN_TERM_REG                 (SOC_SCHARGER_CHG_REG4_ADDR(0))
#define CHG_EN_TERM_SHIFT               (SOC_SCHARGER_CHG_REG4_chg_en_term_START)
#define CHG_EN_TERM_MSK                 (0x01<<CHG_EN_TERM_SHIFT)
#define CHG_TERM_EN                     (1)
#define CHG_TERM_DIS                    (0)

/* CHG_REG2调节寄存器。 */
/* 快充电完成电压阈值大小调节位：0000：3.8V；0001：3.85V；0010：3.9V；0011：3.95V；0100：4V；0101：4.05V；0110：4.1V；0111：4.15V；1000：4.2；1001：4.25；1010：4.3；1011：4.35；1100：4.4；1101：4.45；1110：4.5；1111：4.5。 */
#define CHG_FAST_VCHG_REG               (SOC_SCHARGER_CHG_REG2_ADDR(0))
#define CHG_FAST_VCHG_SHIFT             (SOC_SCHARGER_CHG_REG2_chg_fast_vchg_START)
#define CHG_FAST_VCHG_MSK               (0x0f<<CHG_FAST_VCHG_SHIFT)
#define CHG_FAST_VCHG_STEP_50           (50)
#define CHG_FAST_VCHG_MIN               (3800)
#define CHG_FAST_VCHG_3800              (3800)
#define CHG_FAST_VCHG_3850              (3850)
#define CHG_FAST_VCHG_3900              (3900)
#define CHG_FAST_VCHG_3950              (3950)
#define CHG_FAST_VCHG_4000              (4000)
#define CHG_FAST_VCHG_4050              (4050)
#define CHG_FAST_VCHG_4100              (4100)
#define CHG_FAST_VCHG_4150              (4150)
#define CHG_FAST_VCHG_4200              (4200)
#define CHG_FAST_VCHG_4250              (4250)
#define CHG_FAST_VCHG_4300              (4300)
#define CHG_FAST_VCHG_4350              (4350)
#define CHG_FAST_VCHG_4400              (4400)
#define CHG_FAST_VCHG_4450              (4450)
#define CHG_FAST_VCHG_4500              (4500)
#define CHG_FAST_VCHG_MAX               (4500)

/* 终止充电电流阈值调节位：000：50；001：100mA；010：150mA；011：200mA；100：300mA；101：400mA；110：500mA；111：600mA。 */
#define CHG_TERM_ICHG_REG               (SOC_SCHARGER_CHG_REG2_ADDR(0))
#define CHG_TERM_ICHG_SHIFT             (SOC_SCHARGER_CHG_REG2_chg_term_ichg_START)
#define CHG_TERM_ICHG_MSK               (0x07<<CHG_TERM_ICHG_SHIFT)
#define CHG_TERM_ICHG_50MA              (50)
#define CHG_TERM_ICHG_100MA             (100)
#define CHG_TERM_ICHG_150MA             (150)
#define CHG_TERM_ICHG_200MA             (200)
#define CHG_TERM_ICHG_300MA             (300)
#define CHG_TERM_ICHG_400MA             (400)
#define CHG_TERM_ICHG_500MA             (500)
#define CHG_TERM_ICHG_600MA             (600)

/* 喂狗时间控制寄存器。 */
/* SOC每隔一定时间对V200进行一次寄存器写操作；如果没有写操作事件发生，则进入Default模式，复位chg_en和watchdog_timer寄存器；否则是正常的Host模式。系统watchdog_timer时间设置：00：系统watchdog_timer功能屏蔽；01：10s；10：20s；11：40s 。 */
#define WATCHDOG_CTRL_REG               (SOC_SCHARGER_WATCHDOG_CTRL_ADDR(0))
#define WATCHDOG_TIMER_SHIFT            (SOC_SCHARGER_WATCHDOG_CTRL_watchdog_timer_START) 
#define WATCHDOG_TIMER_MSK              (0x03<<WATCHDOG_TIMER_SHIFT)
#define WATCHDOG_TIMER_10_S             (10)
#define WATCHDOG_TIMER_20_S             (20)
#define WATCHDOG_TIMER_40_S             (40)

/* 看门狗软复位控制寄存器。 */
#define WATCHDOG_SOFT_RST_REG           (SOC_SCHARGER_WATCHDOG_SOFT_RST_ADDR(0))
#define WD_RST_N_SHIFT                  (SOC_SCHARGER_WATCHDOG_SOFT_RST_wd_rst_n_START)
#define WD_RST_N_MSK                    (1<<WD_RST_N_SHIFT)
#define WATCHDOG_TIMER_RST              (1<<WD_RST_N_SHIFT)
/* OTG控制寄存器0 */
#define CHG_OTG_REG0                    (SOC_SCHARGER_OTG_REG0_ADDR(0))
#define CHG_OTG_LIM_SHIFT               (SOC_SCHARGER_OTG_REG0_otg_lim_set_START)
#define CHG_OTG_LIM_MSK                 (0x03<<CHG_OTG_LIM_SHIFT)
#define BOOST_LIM_MIN                   (500)
#define BOOST_LIM_500                   (500)
#define BOOST_LIM_1000                  (1000)
#define BOOST_LIM_1500                  (1500)
#define BOOST_LIM_2000                  (2000)
#define BOOST_LIM_MAX                   (2000)
#define CHG_OTG_EN_SHIFT                (SOC_SCHARGER_OTG_REG0_otg_en_int_START)
#define CHG_OTG_EN_MSK                  (0x03<<CHG_OTG_EN_SHIFT)
#define OTG_ENABLE                      (1)
#define OTG_DISABLE                     (0)

/* 充电状态寄存器0 */
#define CHG_STATUS0_REG                 (SOC_SCHARGER_STATUS0_ADDR(0))
#define HI6523_CHG_BUCK_OK              (0x01<<SOC_SCHARGER_STATUS0_buck_ok_START)
#define HI6523_CHG_STAT_CHARGE_DONE     (0x03<<SOC_SCHARGER_STATUS0_chg_chgstate_START)
#define CHG_IN_DPM_STATE                (0x01<<SOC_SCHARGER_STATUS0_chg_dpm_state_START)

/* 充电状态寄存器1 */
#define CHG_STATUS1_REG                 (SOC_SCHARGER_STATUS1_ADDR(0))
#define HI6523_WATCHDOG_OK              (0x01<<SOC_SCHARGER_STATUS1_wdt_time_out_n_START)


/* ADC 控制寄存器 */
#define CHG_ADC_CTRL_REG                (SOC_SCHARGER_ADC_CTRL_ADDR(0))
#define CHG_ADC_EN_SHIFT                (SOC_SCHARGER_ADC_CTRL_hkadc_en_START)
#define CHG_ADC_EN_MSK                  (1<<CHG_ADC_EN_SHIFT)
#define CHG_ADC_RST_SHIFT               (SOC_SCHARGER_ADC_CTRL_hkadc_reset_START)
#define CHG_ADC_RST_MSK                 (1<<CHG_ADC_RST_SHIFT)
#define CHG_ADC_EN                      (1)
#define CHG_ADC_DIS                     (0)

#define CHG_ADC_CH_SHIFT                (SOC_SCHARGER_ADC_CTRL_hkadc_ch_sel_START)
#define CHG_ADC_CH_MSK                  (0x03<<CHG_ADC_CH_SHIFT)
#define CHG_ADC_CH_VBUS                 (0x02)
#define CHG_ADC_CH_IBUS_REF             (0x01)
#define CHG_ADC_CH_IBUS                 (0)
#define CHG_ADC_BUFF_LEN                (10)
/* ADC 开始转换寄存器 */
#define CHG_ADC_START_REG               (SOC_SCHARGER_ADC_START_ADDR(0))
#define CHG_ADC_START_SHIFT             (SOC_SCHARGER_ADC_START_hkadc_start_START)
#define CHG_ADC_START_MSK               (1<<CHG_ADC_START_SHIFT)

/* ADC 状态寄存器 */
#define CHG_ADC_CONV_STATUS_REG         (SOC_SCHARGER_ADC_CONV_STATUS_ADDR(0))
#define CHG_ADC_CONV_STATUS_SHIFT       (SOC_SCHARGER_ADC_CONV_STATUS_hkadc_valid_START)
#define CHG_ADC_CONV_STATUS_MSK         (1<<CHG_ADC_CONV_STATUS_SHIFT)

/* ADC 数据寄存器*/
#define CHG_ADC_DATA_REG                (SOC_SCHARGER_ADC_DATA1_ADDR(0))

/* Hiz MODE控制寄存器 */
#define CHG_HIZ_CTRL_REG                (SOC_SCHARGER_SCHG_LOGIC_CTRL_ADDR(0))
#define CHG_HIZ_ENABLE_SHIFT            (SOC_SCHARGER_SCHG_LOGIC_CTRL_buck_enb_START)
#define CHG_HIZ_ENABLE_MSK              (1<<CHG_HIZ_ENABLE_SHIFT)

/* irq中断寄存器*/
#define CHG_IRQ0                        (SOC_SCHARGER_IRQ0_ADDR(0))
#define CHG_OTG_OCP                     (1 << SOC_SCHARGER_IRQ0_otg_ocp_r_START)
#define CHG_IRQ1                        (SOC_SCHARGER_IRQ1_ADDR(0))
#define CHG_IRQ2                        (SOC_SCHARGER_IRQ2_ADDR(0))
#define CHG_WDT_IRQ                     (SOC_SCHARGER_WATCHDOG_IRQ_ADDR(0))


/* chg_reg5电池通道补偿寄存器 */
#define CHG_IR_COMP_REG                 (SOC_SCHARGER_CHG_REG5_ADDR(0))
#define CHG_IR_COMP_SHIFT               (SOC_SCHARGER_CHG_REG5_chg_ir_set_START)
#define CHG_IR_COMP_MSK                 (0x07<<CHG_IR_COMP_SHIFT)
#define CHG_IR_COMP_MIN                 (0)
#define CHG_IR_COMP_0mohm               (0)
#define CHG_IR_COMP_15mohm              (15)
#define CHG_IR_COMP_30mohm              (30)
#define CHG_IR_COMP_45mohm              (45)
#define CHG_IR_COMP_60mohm              (60)
#define CHG_IR_COMP_75mohm              (75)
#define CHG_IR_COMP_95mohm              (95)
#define CHG_IR_COMP_110mohm             (110)
#define CHG_IR_COMP_MAX                 (110)

#define CHG_IR_VCLAMP_REG               (SOC_SCHARGER_CHG_REG5_ADDR(0))
#define CHG_IR_VCLAMP_SHIFT             (SOC_SCHARGER_CHG_REG5_chg_vclamp_set_START)
#define CHG_IR_VCLAMP_MSK               (0x07<<CHG_IR_VCLAMP_SHIFT)
#define CHG_IR_VCLAMP_STEP              (50)
#define CHG_IR_VCLAMP_MIN               (0)
#define CHG_IR_VCLAMP_MAX               (350)

/* FCP UVP/OVP voltage set寄存器 */
#define CHG_UVP_OVP_VOLTAGE_REG         (SOC_SCHARGER_SYS_RESVO1_ADDR(0))
#define CHG_UVP_OVP_VOLTAGE_5V          (0)
#define CHG_UVP_OVP_VOLTAGE_9V          (BIT(1) | BIT(3))
#define CHG_UVP_OVP_VOLTAGE_12V         (BIT(2) | BIT(4))
#define CHG_UVP_OVP_VOLTAGE_MAX         (BIT(2))

/*fcp detect */
#define CHG_FCP_ADAPTER_DETECT_FAIL     (1)
#define CHG_FCP_ADAPTER_DETECT_SUCC     (0)
#define CHG_FCP_ADAPTER_DETECT_OTHER    (-1)
#define CHG_FCP_POLL_TIME               (100)   /* 100ms */
#define CHG_FCP_DETECT_MAX_COUT         (20)  /* fcp detect MAX COUT */

/*fcp adapter status */
#define FCP_ADAPTER_5V                      (5000)
#define FCP_ADAPTER_9V                      (9000)
#define FCP_ADAPTER_12V                     (12000)
#define FCP_ADAPTER_MAX_VOL                 (FCP_ADAPTER_12V)
#define FCP_ADAPTER_MIN_VOL                 (FCP_ADAPTER_5V)
#define FCP_ADAPTER_RST_VOL                 (FCP_ADAPTER_5V)
#define FCP_ADAPTER_VOL_CHECK_ERROR         (500)
#define FCP_ADAPTER_VOL_CHECK_POLLTIME      (100)
#define FCP_ADAPTER_VOL_CHECK_TIMEOUT       (10)

/* fcp 读写寄存器 */
#define CHG_FCP_CMD_REG                 (SOC_SCHARGER_CMD_ADDR(0))
#define CHG_FCP_ADDR_REG                (SOC_SCHARGER_ADDR_ADDR(0))
#define CHG_FCP_WDATA_REG               (SOC_SCHARGER_DATA0_ADDR(0))
#define CHG_FCP_RDATA_REG               (SOC_SCHARGER_FCP_RDATA_ADDR(0))

/* fcp 控制寄存器 */
#define CHG_FCP_CTRL_REG                (SOC_SCHARGER_CNTL_ADDR(0))
#define CHG_FCP_EN_SHIFT                (SOC_SCHARGER_CNTL_enable_START)
#define CHG_FCP_EN_MSK                  (1<<CHG_FCP_EN_SHIFT)
#define CHG_FCP_MSTR_RST_SHIFT          (SOC_SCHARGER_CNTL_mstr_rst_START)
#define CHG_FCP_MSTR_RST_MSK            (1<<CHG_FCP_MSTR_RST_SHIFT)
#define CHG_FCP_SNDCMD_SHIFT            (SOC_SCHARGER_CNTL_sndcmd_START)
#define CHG_FCP_SNDCMD_MSK              (1<<CHG_FCP_SNDCMD_SHIFT)
#define CHG_FCP_EN                      (1)
#define CHG_FCP_DIS                     (0)

/* fcp det 控制寄存器 */
#define CHG_FCP_DET_CTRL_REG            (SOC_SCHARGER_FCP_CTRL_ADDR(0))
#define CHG_FCP_DET_EN_SHIFT            (SOC_SCHARGER_FCP_CTRL_fcp_det_en_START)
#define CHG_FCP_DET_EN_MSK              (1<<CHG_FCP_DET_EN_SHIFT)
#define CHG_FCP_CMP_EN_SHIFT            (SOC_SCHARGER_FCP_CTRL_fcp_cmp_en_START)
#define CHG_FCP_CMP_EN_MSK              (1<<CHG_FCP_CMP_EN_SHIFT)
#define CHG_FCP_DET_EN                  (1)

/* fcp soft reset控制寄存器 */
#define CHG_FCP_SOFT_RST_REG            (SOC_SCHARGER_FCP_SOFT_RST_CTRL_ADDR(0))
#define CHG_FCP_SOFT_RST_VAL            (BIT(2))

/* fcp 状态寄存器*/
#define CHG_FCP_STATUS_REG              (SOC_SCHARGER_STATUIS_ADDR(0))
#define CHG_FCP_DVC_SHIFT               (SOC_SCHARGER_STATUIS_dvc_START)
#define CHG_FCP_DVC_MSK                 (0x03<<CHG_FCP_DVC_SHIFT)
#define CHG_FCP_ATTATCH_SHIFT           (SOC_SCHARGER_STATUIS_attach_START)
#define CHG_FCP_ATTATCH_MSK             (1<<CHG_FCP_ATTATCH_SHIFT)
#define CHG_FCP_SLAVE_GOOD              (CHG_FCP_DVC_MSK | CHG_FCP_ATTATCH_MSK)

/*高压快充adapter状态标志*/
#define CHG_FCP_SET_STATUS_REG          (SOC_SCHARGER_FCP_ADAP_CTRL_ADDR(0))
#define CHG_FCP_SET_STATUS_SHIFT        (SOC_SCHARGER_FCP_ADAP_CTRL_fcp_set_d60m_r_START)
#define CHG_FCP_SET_STATUS_MSK          (1<<CHG_FCP_SET_STATUS_SHIFT)

/* fcp 中断寄存器1 */
#define CHG_FCP_ISR1_REG                (SOC_SCHARGER_ISR1_ADDR(0))
#define CHG_FCP_CMDCPL                  (1<<SOC_SCHARGER_ISR1_cmdcpl_START)
#define CHG_FCP_ACK                     (1<<SOC_SCHARGER_ISR1_ack_START)
#define CHG_FCP_NACK                    (1<<SOC_SCHARGER_ISR1_nack_START)
#define CHG_FCP_CRCPAR                  (1<<SOC_SCHARGER_ISR1_crcpar_START)

/* fcp 中断寄存器2 */
#define CHG_FCP_ISR2_REG                (SOC_SCHARGER_ISR2_ADDR(0))
#define CHG_FCP_CRCRX                   (1<<SOC_SCHARGER_ISR2_crcrx_START)
#define CHG_FCP_PARRX                   (1<<SOC_SCHARGER_ISR2_parrx_START)
#define CHG_FCP_PROTSTAT                (1<<SOC_SCHARGER_ISR2_protstat_START)

/* fcp 中断寄存器3 */
#define CHG_FCP_IRQ3_REG                (SOC_SCHARGER_FCP_IRQ3_ADDR(0))

/* fcp 中断寄存器4 */
#define CHG_FCP_IRQ4_REG                (SOC_SCHARGER_FCP_IRQ4_ADDR(0))

/* fcp 中断寄存器5 */
#define CHG_FCP_IRQ5_REG                (SOC_SCHARGER_FCP_IRQ5_ADDR(0))
#define CHG_FCP_SET_DET_SHIFT           (SOC_SCHARGER_FCP_IRQ5_fcp_set_d60m_r_START)
#define CHG_FCP_SET_DET_MSK             (1<<SOC_SCHARGER_FCP_IRQ5_fcp_set_d60m_r_START)

/* adapter cmd */
#define CHG_FCP_CMD_SBRRD                   (0x0c)
#define CHG_FCP_CMD_SBRWR                   (0x0b)

/* adapter registers */
#define CHG_FCP_SLAVE_ID_OUT0               (0x04)
#define CHG_FCP_SLAVE_DISCRETE_CAPABILITIES (0x21)
#define CHG_FCP_SLAVE_MAX_PWR               (0x22)
#define CHG_FCP_SLAVE_OUTPUT_CONTROL        (0x2b)
#define CHG_FCP_SLAVE_VOUT_CONFIG           (0x2c)
#define CHG_FCP_SLAVE_REG_DISCRETE_OUT_V(n) (0x30+(n))
/* Register FCP_SLAVE_OUTPUT_CONTROL (0x2b)*/
#define CHG_FCP_SLAVE_SET_VOUT              (1<<0)
#define CHG_FCP_VOL_STEP                    (10)
#define CHG_FCP_OUTPUT_VOL_5V               (5)
#define CHG_FCP_OUTPUT_VOL_9V               (9)
#define CHG_FCP_OUTPUT_VOL_12V              (12)

/* fcp_adapter_transfer_status */
#define FCP_TRANSFER_SUCC                   (0)
#define FCP_TRANSFER_FAIL                   (-1)


#endif
