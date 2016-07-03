/*
 * anc_max14744.c -- anc max14744 headset driver
 *
 * Copyright (c) 2014 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/string.h>
#include <linux/interrupt.h>
#include <linux/ioctl.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/wakelock.h>
#include <linux/miscdevice.h>
#include <linux/regulator/consumer.h>
#include <linux/workqueue.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/uaccess.h>
#include <sound/jack.h>
#include <linux/fs.h>
#include <linux/regmap.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/pinctrl/consumer.h>

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif

#include <linux/huawei/hisi_adc.h>
#include <dsm/dsm_pub.h>
#include "huawei_platform/audio/anc_max14744.h"

#define HWLOG_TAG anc_max14744

HWLOG_REGIST();

extern int hifi_send_msg(unsigned int mailcode, void *data, unsigned int length);

/* dmd error report definition*/
static struct dsm_dev dsm_anc_max14744 =
{
    .name = "dsm_anc_max14744",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
    .fops = NULL,
    .buff_size = 1024,
};
static struct dsm_client* anc_max14744_dclient = NULL;

enum anc_hs_mode
{
    ANC_HS_CHARGE_OFF         = 0,
    ANC_HS_CHARGE_ON          = 1,
};

/* anc headset charge status*/
enum switch_chip_status
{
    SWITCH_CHIP_HSBIAS        = 0,  /* not charging */
    SWITCH_CHIP_5VBOOST       = 1,  /* charging */
};

enum anc_max14744_irq_type
{
    ANC_MAX14744_JACK_PLUG_IN = 0,
    ANC_MAX14744_JACK_PLUG_OUT,
    ANC_MAX14744_BUTTON_PRESS,

    ANC_MAX14744_IQR_MAX,
};

#define  ANC_HS_LIMIT_MIN                  20
#define  ANC_HS_LIMIT_MAX                  200
#define  ANC_CHIP_STARTUP_TIME             30
#define  ADC_CALIBRATION_TIMES             10
#define  ADC_READ_COUNT                    3
#define  ADC_NORMAL_LIMIT_MIN              -500
#define  ADC_NORMAL_LIMIT_MAX              500
#define  ADC_OUT_OF_RANGE                  2499
#define  ANC_HS_HOOK_MIN                  160
#define  ANC_HS_HOOK_MAX                  185
#define  ANC_HS_VOLUME_UP_MIN                  205
#define  ANC_HS_VOLUME_UP_MAX                  230
#define  ANC_HS_VOLUME_DOWN_MIN                  240
#define  ANC_HS_VOLUME_DOWN_MAX                  265

#define  ANC_HS_4POLE_MIN                  20
#define  ANC_HS_4POLE_MAX                  35
#define  ANC_HS_REVERT_4POLE_MIN           85
#define  ANC_HS_REVERT_4POLE_MAX           105
#define  ANC_HS_HEADSET_MIN                40
#define  ANC_HS_HEADSET_MAX                80

#define ADC_STEP                           (476)
#define ADC_OFFSET                         (170)
#define IDET_LVL1                          (110)
#define IDET_LVL2                          (220)
#define IDET_LVL3                          (550)

#define LDO1_SHUTDOWN_MODE                  0x00
#define LDO1_CALL_MODE                      0x03

#define NO_BUTTON_PRESS                      (-1)

#define CODEC_GPIO_BASE                      (224)

//#define ANC_BTN_MASK (SND_JACK_BTN_0)
#define ANC_BTN_MASK (SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2)

struct anc_max14744_priv {
    struct i2c_client *client;
    struct device *dev;
    void *control_data;

    struct regmap *regmapL;
    struct regmap *regmapR;

    int anc_hs_mode;         /* charge status */
    int anc_pwr_en_gpio;     /* VBST_5V EN */

    int channel_pwl_h;       /* adc channel for high voltage*/
    int channel_pwl_l;       /* adc channel for low voltage*/
    int anc_hs_limit_min;
    int anc_hs_limit_max;

    int anc_hs_btn_hook_min_voltage;
    int anc_hs_btn_hook_max_voltage;
    int anc_hs_btn_volume_up_min_voltage;
    int anc_hs_btn_volume_up_max_voltage;
    int anc_hs_btn_volume_down_min_voltage;
    int anc_hs_btn_volume_down_max_voltage;

    bool irq_flag;
    bool boost_flag;

    int sleep_time;          /* charge chip pre-charge time */
    bool mic_used;           /* flag to show mic status */
    bool detect_again;
    int force_charge_ctl;    /* force charge control for userspace*/
    int hs_micbias_ctl;      /* hs micbias control*/

    int adc_calibration_base;/* calibration value*/
    int button_pressed;
    int headset_type;

    struct mutex btn_mutex;
    struct mutex charge_lock;/* charge status protect lock */
    struct mutex invert_hs_lock;
    struct wake_lock wake_lock;
    spinlock_t    irq_lock;

    int registered;          /* anc hs regester flag */
    struct anc_hs_dev *anc_dev;     /* anc hs dev */
    void *private_data;      /* store codec decription data*/

    int gpio_int;
    int anc_max14744_irq;

    /* chip irq workqueue */
    struct workqueue_struct* anc_hs_plugin_delay_wq;
    struct delayed_work anc_hs_plugin_delay_work;

    struct workqueue_struct* anc_hs_plugout_delay_wq;
    struct delayed_work anc_hs_plugout_delay_work;

    struct workqueue_struct* anc_hs_btn_delay_wq;
    struct delayed_work anc_hs_btn_delay_work;

    struct workqueue_struct* anc_hs_invert_ctl_delay_wq;
    struct delayed_work anc_hs_invert_ctl_delay_work;
};

struct anc_max14744_priv *g_anc_max14744_priv = NULL;

static struct reg_default anc_max14744_reg[] = {
    { 0x00, 0x32 }, /* device id */
    { 0x01, 0x00 }, /* adc conversion */
    { 0x02, 0x00 }, /* adc status */
    { 0x03, 0x00 }, /* status */
    { 0x04, 0x00 }, /* Msic1 */
    { 0x05, 0x00 }, /* Msic2 */
    { 0x06, 0x00 }, /* interrupt */
    { 0x07, 0x00 }, /* Mask */
    { 0x08, 0x00 }, /* pins control1 */
    { 0x09, 0x00 }, /* pins control2 */
    { 0x0A, 0x00 }, /* adc control */
    { 0x0B, 0x10 }, /* acc control1 */
    { 0x0C, 0x00 }, /* acc control2 */
};

static bool anc_max14744_volatile_register(struct device *dev, unsigned int reg) {
    switch (reg) {
    case ANC_MAX14744_R000_DEVICE_ID:
    case ANC_MAX14744_R001_ADC_CONVERSION:
    case ANC_MAX14744_R002_ADC_STATUS:
    case ANC_MAX14744_R003_STATUS:
    case ANC_MAX14744_R004_MSIC1:
    case ANC_MAX14744_R005_MSIC2:
    case ANC_MAX14744_R006_INTERRUPT:
    case ANC_MAX14744_R00A_ADC_CONTROL:
        return true;
    default:
        return false;
    }
}

static bool anc_max14744_readable_register(struct device *dev, unsigned int reg) {
    return true;
}

static inline int anc_hs_max14744_get_value(int gpio)
{
    if(gpio >= CODEC_GPIO_BASE) {
        return gpio_get_value_cansleep(gpio);
    } else {
        return gpio_get_value(gpio);
    }
}

static inline void anc_max14744_gpio_set_value(int gpio, int value)
{
    if(gpio >= CODEC_GPIO_BASE) {
        gpio_set_value_cansleep(gpio, value);
    } else {
        gpio_set_value(gpio, value);
    }
}

static inline void anc_hs_enable_irq(int irq)
{
    if (!g_anc_max14744_priv->irq_flag) {
        enable_irq(irq);
        g_anc_max14744_priv->irq_flag = true;
    }
}

static inline void anc_hs_disable_irq(int irq)
{
    if (g_anc_max14744_priv->irq_flag) {
        disable_irq_nosync(irq);
        g_anc_max14744_priv->irq_flag = false;
    }
}

static int anc_max14744_regmap_read(int reg, int *value)
{
    int ret = 0;

    ret = regmap_read(g_anc_max14744_priv->regmapL, reg, value);
    if(ret < 0) {
        hwlog_err("anc_max14744 regmap read reg 0x%x error,%d\n", reg, ret);
        return ret;
    }

    return ret;
}

static int anc_max14744_regmap_write(int reg, int value)
{
    int ret = 0;

    ret = regmap_write(g_anc_max14744_priv->regmapL, reg, value);
    if(ret < 0) {
        hwlog_err("anc_max14744 regmap write reg 0x%x error,%d\n", reg, ret);
        return ret;
    }

    return ret;
}

static int anc_max14744_regmap_update_bits(int reg, int mask, int value)
{
    int ret = 0;

    ret = regmap_update_bits(g_anc_max14744_priv->regmapL, reg, mask, value);
    if(ret < 0) {
        hwlog_err("anc_max14744 regmap update bits error,%d\n", ret);
        return ret;
    }

    return ret;
}

bool anc_max14744_check_headset_pluged_in(void);
static int force_clear_irq()
{
    int value = 0;
    int ret = 0;

    ret = anc_max14744_regmap_read(ANC_MAX14744_R006_INTERRUPT, &value);
    if(ret < 0) {
        hwlog_err("anc_max14744 force_clear_irq, read irq reg fail. \n");
        return ret;
    }
    hwlog_info("anc_max14744 force_clear_irq, irq reg : 0x%x\n", value);

    if((value & ANC_MAX14744_PLUG_IRQ_BIT) && !anc_max14744_check_headset_pluged_in()) {
        queue_delayed_work(g_anc_max14744_priv->anc_hs_plugout_delay_wq,
                   &g_anc_max14744_priv->anc_hs_plugout_delay_work,
                  0);
        hwlog_info("anc_max14744 force_clear_irq, plugout event.\n");
    }

    return ret;
}

static void max14744_unmask_btn_irq()
{
    hwlog_info("anc_max14744 unmask btn irq\n");

    force_clear_irq();

    anc_max14744_regmap_update_bits(ANC_MAX14744_R007_MASK, ANC_MAX14744_BUTTON_PRESS_IRQ_BIT,ANC_MAX14744_BUTTON_PRESS_IRQ_BIT);
}

static void max14744_mask_btn_irq()
{
    hwlog_info("anc_max14744 mask btn irq\n");

    anc_max14744_regmap_update_bits(ANC_MAX14744_R007_MASK, ANC_MAX14744_BUTTON_PRESS_IRQ_BIT, 0x00);
}

static void max14744_unmask_plug_irq()
{
    hwlog_info("anc_max14744 unmask plug irq\n");

    anc_max14744_regmap_update_bits(ANC_MAX14744_R007_MASK, ANC_MAX14744_PLUG_IRQ_BIT, ANC_MAX14744_PLUG_IRQ_BIT);
}

static void max14744_mask_plug_irq()
{
    hwlog_info("anc_max14744 mask plug irq\n");

    anc_max14744_regmap_update_bits(ANC_MAX14744_R007_MASK, ANC_MAX14744_PLUG_IRQ_BIT, 0x00);
}

static void max14744_unmask_eoc_irq()
{
    hwlog_info("anc_max14744 unmask eoc irq\n");

    anc_max14744_regmap_update_bits(ANC_MAX14744_R007_MASK, ANC_MAX14744_EOC_IRQ_BIT, ANC_MAX14744_EOC_IRQ_BIT);
}

static void max14744_mask_eoc_irq()
{
    hwlog_info("anc_max14744 mask eoc irq\n");

    anc_max14744_regmap_update_bits(ANC_MAX14744_R007_MASK, ANC_MAX14744_EOC_IRQ_BIT, 0x00);
}

static void mic_bias_mode(int mode0)
{
    hwlog_info("max14744 go into mic_bias_mode.");
    if(NULL != g_anc_max14744_priv) {
        anc_max14744_regmap_update_bits(ANC_MAX14744_R00B_ACC_CONTROL1, 
                ANC_MAX14744_BYPASS_MASK, 0x00);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1,
                ANC_MAX14744_MODE1_MASK, 0x00);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1,
                ANC_MAX14744_MODE0_MASK, 0x00);
        mdelay(30);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_MODE0_MASK, mode0);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_MANUL_MIC_SW_MASK, ANC_MAX14744_MANUL_MIC_SW_MASK);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_FORCE_MIC_SW_MASK, 0x00);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_MANUL_CNTL_MASK, ANC_MAX14744_MANUL_CNTL_MASK);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_FORCE_CNTL_MASK, ANC_MAX14744_FORCE_CNTL_MASK);
    }

    return;
}

static void power_mode(void)
{
    hwlog_info("max14744 go into power_mode.");
    if(NULL != g_anc_max14744_priv) {
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1,
                ANC_MAX14744_MANUL_MIC_SW_MASK, ANC_MAX14744_MANUL_MIC_SW_MASK);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1,
                ANC_MAX14744_FORCE_MIC_SW_MASK, ANC_MAX14744_FORCE_MIC_SW_MASK);
        mdelay(1);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_MODE1_MASK, ANC_MAX14744_MODE1_MASK);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R00B_ACC_CONTROL1, 
                ANC_MAX14744_BYPASS_MASK, ANC_MAX14744_BYPASS_MASK);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_MANUL_CNTL_MASK, ANC_MAX14744_MANUL_CNTL_MASK);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_FORCE_CNTL_MASK, ANC_MAX14744_FORCE_CNTL_MASK);
    }

    return;
}

static void normal_mode(void)
{
    hwlog_info("max14744 go into normal_mode.");
    if(NULL != g_anc_max14744_priv) {
        anc_max14744_regmap_update_bits(ANC_MAX14744_R00B_ACC_CONTROL1, 
                ANC_MAX14744_BYPASS_MASK, 0x00);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_MODE1_MASK, 0x00);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_MODE0_MASK, 0x00);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_MANUL_MIC_SW_MASK, 0x00);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_FORCE_MIC_SW_MASK, 0x00);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_MANUL_CNTL_MASK, 0x00);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1, 
                ANC_MAX14744_FORCE_CNTL_MASK, 0x00);
    }

    return;
}

void anc_max14744_refresh_headset_type(int headset_type)
{
    if (NULL != g_anc_max14744_priv) {
        g_anc_max14744_priv->headset_type =  headset_type;
        hwlog_info("max14744: refresh headset_type %d.", g_anc_max14744_priv->headset_type);
    }
}

static void anc_hs_invert_ctl_work(struct work_struct* work)
{
    wake_lock(&g_anc_max14744_priv->wake_lock);
    mutex_lock(&g_anc_max14744_priv->invert_hs_lock);

    if (g_anc_max14744_priv->headset_type == ANC_HS_REVERT_4POLE) {
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1,
                ANC_MAX14744_MANUL_CNTL_MASK, ANC_MAX14744_MANUL_CNTL_MASK);
        anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1,
                ANC_MAX14744_FORCE_CNTL_MASK, 0x00);
        hwlog_info("max14744: invert headset plugin, connect MIC and GND.");
    }

    mutex_unlock(&g_anc_max14744_priv->invert_hs_lock);
    wake_unlock(&g_anc_max14744_priv->wake_lock);
}

void anc_max14744_invert_headset_control(int connect)
{
    switch(connect) {
        case ANC_HS_MIC_GND_DISCONNECT:
            cancel_delayed_work(&g_anc_max14744_priv->anc_hs_invert_ctl_delay_work);
            flush_workqueue(g_anc_max14744_priv->anc_hs_invert_ctl_delay_wq);

            mutex_lock(&g_anc_max14744_priv->invert_hs_lock);
            anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1,
                    ANC_MAX14744_MANUL_CNTL_MASK, 0x00);
            anc_max14744_regmap_update_bits(ANC_MAX14744_R008_PINS_CONTROL1,
                    ANC_MAX14744_FORCE_CNTL_MASK, 0x00);
            mutex_unlock(&g_anc_max14744_priv->invert_hs_lock);

            hwlog_info("max14744: headset plugout, disconnect MIC and GND.");
            break;
        case ANC_HS_MIC_GND_CONNECT:
            queue_delayed_work(g_anc_max14744_priv->anc_hs_invert_ctl_delay_wq,
                    &g_anc_max14744_priv->anc_hs_invert_ctl_delay_work,
                    msecs_to_jiffies(3000));
            hwlog_info("anc_max14744_invert_headset_control: queue delay work.");
            break;
        default:
            hwlog_info("anc_max14744_invert_headset_control: unknown connect type.");
            break;
    }
}

/**
 * anc_hs_get_adc_delta
 *
 * get 3 times adc value with 1ms delay and use average value(delta) of it,
 * charge for it when delta is between anc_hs_limit_min and anc_hs_limit_max
 **/
static int anc_max14744_get_adc_delta(void)
{
    int ear_pwr_h = 0, ear_pwr_l = 0;
    int delta = 0, count, fail_count = 0;
    int loop = ADC_READ_COUNT;
    int temp;
    bool need_report = true;

    while (loop) {
        loop--;
        mdelay(1);
        ear_pwr_h = hisi_adc_get_value(g_anc_max14744_priv->channel_pwl_h);
        if (ear_pwr_h < 0) {
            hwlog_err("%s:get hkadc(h) fail, err:%d\n", __FUNCTION__, ear_pwr_h);
            fail_count++;
            continue;
        }
        ear_pwr_l = hisi_adc_get_value(g_anc_max14744_priv->channel_pwl_l);
        if (ear_pwr_l < 0) {
            hwlog_err("%s:get hkadc(l) fail, err:%d\n", __FUNCTION__, ear_pwr_l);
            fail_count++;
            continue;
        }
        hwlog_info("%s:adc_h:%d,adc_l:%d\n", __FUNCTION__, ear_pwr_h, ear_pwr_l);

        temp = ear_pwr_h - ear_pwr_l - g_anc_max14744_priv->adc_calibration_base;

        /* if the adc value far away from normal value, just abandon it*/
        if ((temp > ADC_NORMAL_LIMIT_MAX) || (temp < ADC_NORMAL_LIMIT_MIN) ) {
            fail_count++;
            need_report = false;
            continue;
        }

        delta += temp;
    }

    /* if adc value is out of rage, we make a dmd report */
/*
    if(ear_pwr_h >= ADC_OUT_OF_RANGE || ear_pwr_l >= ADC_OUT_OF_RANGE) {
        anc_dsm_report(ANC_HS_ADC_FULL_ERR, 0);
    }
*/
    count = ADC_READ_COUNT - loop - fail_count;
    if (count == 0) {
        hwlog_err("%s:get anc_hs hkadc failed\n", __FUNCTION__);
/*
        if(need_report) {
            anc_dsm_report(ANC_HS_ADCH_READ_ERR, 0);
        }
*/
        return false;
    }
    /* compute an average value */
    delta /= count;
    hwlog_info("%s:final adc value= %d  count=%d\n", __FUNCTION__, delta, count);
    return delta;
}

/**
 * anc_hs_get_btn_value - judge which button is pressed
 *
 *
 **/
static int anc_max14744_get_btn_value(void)
{
    int delta = 0;
    delta = anc_max14744_get_adc_delta();
    if ((delta >= g_anc_max14744_priv->anc_hs_btn_hook_min_voltage) &&
        (delta <= g_anc_max14744_priv->anc_hs_btn_hook_max_voltage)) {
        return SND_JACK_BTN_0;
    } else if ((delta >= g_anc_max14744_priv->anc_hs_btn_volume_up_min_voltage) &&
        (delta <= g_anc_max14744_priv->anc_hs_btn_volume_up_max_voltage)) {
        return SND_JACK_BTN_1;
    } else if ((delta >= g_anc_max14744_priv->anc_hs_btn_volume_down_min_voltage) &&
        (delta <= g_anc_max14744_priv->anc_hs_btn_volume_down_max_voltage)) {
        return SND_JACK_BTN_2;
    } else {
        hwlog_err("[anc_max14744]btn delta not in range delta:%d\n", delta);
        //anc_dsm_report(ANC_HS_BTN_NOT_IN_RANGE, 0);
        return NO_BUTTON_PRESS;
    }
}

static bool anc_max14744_btn_press(void)
{
    int value = 0;

    if(g_anc_max14744_priv == NULL)
	    return false;

    anc_max14744_regmap_read(ANC_MAX14744_R004_MSIC1, &value);

    if(value & ANC_MAX14744_BUTTON_PRESS_BIT)
        return false;
    else
        return true;
}

/**
 * anc_hs_btn_judge - delay work for anc headset irq
 *
 * @work: work struct
 *
 * should sync with codec power control, codec visit should
 * after codec_resume_lock(pdata->private_data, false).
 **/
static void anc_max14744_btn_judge(void)
{
    struct anc_hs_dev *pdev = g_anc_max14744_priv->anc_dev;
    struct anc_hs_codec_ops *fops = &pdev->ops;
    int btn_report;

    if(!g_anc_max14744_priv->registered) {
        return;
    }

    hwlog_info("%s(%u):deal with button irq event!\n", __FUNCTION__, __LINE__);

    /* should get wake lock before codec power lock which may be blocked*/
    mutex_lock(&g_anc_max14744_priv->btn_mutex);

    if (anc_max14744_btn_press() && (g_anc_max14744_priv->button_pressed == 0)) {
        /*button down event*/
        hwlog_info("%s(%u) : button down event !\n", __FUNCTION__, __LINE__);
        mdelay(50);
        btn_report = anc_max14744_get_btn_value();
        if(NO_BUTTON_PRESS != btn_report) {
            g_anc_max14744_priv->button_pressed = 1;
            fops->btn_report(btn_report, ANC_BTN_MASK);
        } else {
            hwlog_warn("anc_max14744_btn_judge: it is not a button press.");
        }
    } else if (g_anc_max14744_priv->button_pressed == 1) {
        /*button up event*/
        hwlog_info("%s(%u) : button up event !\n", __FUNCTION__, __LINE__);

        btn_report = 0;
        g_anc_max14744_priv->button_pressed = 0;

        /* we permit button up event report to userspace,
             make sure down and up in pair*/
        fops->btn_report(btn_report, ANC_BTN_MASK);
    }

    mutex_unlock(&g_anc_max14744_priv->btn_mutex);

    return;
}

/**
 * anc_hs_send_hifi_msg - send hifi dsp message to set 3A parameter whether it is anc headset
 *
 *
 **/
static int anc_hs_send_hifi_msg(int anc_status)
{
    int ret = OK_RET;

    struct MLIBSetParaInfo* pMLIBSetParaInfo = (struct MLIBSetParaInfo*)kzalloc(sizeof(struct MLIBSetParaInfo)
                                                    + MLIB_PARA_LENGTH_MAX, 1);
    struct MlibParameterVoice*  pPara_ANC_HS = NULL;

    if (pMLIBSetParaInfo == NULL)
    {
        hwlog_err("%s: kzalloc failed\n", __FUNCTION__);
        ret = ERROR_RET;// error return;
        return ret;
    }

    pMLIBSetParaInfo->msgID = ID_AP_AUDIO_MLIB_SET_PARA_IND;
    pMLIBSetParaInfo->uwPathID = MLIB_PATH_CS_VOICE_CALL_MICIN;
    pMLIBSetParaInfo->uwSize = MLIB_PARA_LENGTH_MAX;
    pMLIBSetParaInfo->reserve = 0;
    pMLIBSetParaInfo->uwModuleID = MLIB_MODULE_3A_VOICE;

    pPara_ANC_HS = (struct MlibParameterVoice*)pMLIBSetParaInfo->aucData;
    pPara_ANC_HS->key = MLIB_ANC_HS_PARA_ENABLE;
    pPara_ANC_HS->value = anc_status;

    ret = hifi_send_msg(MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC,
                        pMLIBSetParaInfo,
                        sizeof(struct MLIBSetParaInfo) + MLIB_PARA_LENGTH_MAX);

    kfree(pMLIBSetParaInfo);

    return ret;
}


/**
 * anc_hs_need_charge - judge whether it is anc headset
 *
 *
 **/
static bool anc_max14744_need_charge(void)
{
    int delta = 0;
    mdelay(30);
    delta = anc_max14744_get_adc_delta();
    if ((delta >= g_anc_max14744_priv->anc_hs_limit_min) &&
        (delta <= g_anc_max14744_priv->anc_hs_limit_max)) {
        hwlog_info("[%s][%d] anc headset = true\n", __FUNCTION__,__LINE__);
        return true;
    } else {
        hwlog_info("[%s][%d] anc headset = false\n", __FUNCTION__,__LINE__);
        return false;
    }
}

/**
 * anc_hs_adc_calibration - calibrate anc headset charge-circut
 *
 * make sure 5vboost is on and it is in float status before
 * call this function, if calibrate failed, set it as zero by default.
 **/
static void anc_max14744_adc_calibration(void)
{
    int loop = ADC_CALIBRATION_TIMES;
    int count, fail_count = 0;
    g_anc_max14744_priv->adc_calibration_base = 0;

    while (loop) {
        int adc_h, adc_l;
        loop--;
        usleep_range(1000, 1100);
        adc_h = hisi_adc_get_value(g_anc_max14744_priv->channel_pwl_h);
        if (adc_h < 0) {
            hwlog_err("[anc_hs]get adc fail,adc_h:%d\n", adc_h);
            fail_count ++;
            continue;
        }
        adc_l = hisi_adc_get_value(g_anc_max14744_priv->channel_pwl_l);
        if (adc_l < 0) {
            hwlog_err("[anc_hs]get adc fail,adc_l:%d\n", adc_l);
            fail_count ++;
            continue;
        }

        /* one calibrate value completely unnormal, abandon it*/
        if ((adc_h - adc_l < -100) || (adc_h - adc_l > 100)) {
            hwlog_err("[anc_hs]adc value is not expect, %d\n", adc_h - adc_l);
            fail_count ++;
            continue;
        }
        g_anc_max14744_priv->adc_calibration_base += (adc_h - adc_l);
    }

    count = ADC_CALIBRATION_TIMES - loop - fail_count;
    if (count == 0) {
        /* if all adc read fail, set 0 to it as default*/
        g_anc_max14744_priv->adc_calibration_base = 0;
        hwlog_err("[anc_hs] calibration whole failed\n");
    } else {
        g_anc_max14744_priv->adc_calibration_base /= count;
        hwlog_info("anc_hs:calibration_base = %d with %d times\n", g_anc_max14744_priv->adc_calibration_base, count);

        if (g_anc_max14744_priv->adc_calibration_base > 50 ||
            g_anc_max14744_priv->adc_calibration_base < -50) {
            g_anc_max14744_priv->adc_calibration_base = 0;
            hwlog_err("[anc_hs] calibration value is not illegal, error occured\n");
        }
    }

    return;
}

/**
 * anc_hs_charge_judge - judge whether need charge for it
 *
 * get 3 times adc value with 1ms delay and use average value(delta) of it,
 * charge for it when delta is between anc_hs_limit_min and anc_hs_limit_max
 **/
static void  anc_max14744_charge_judge(void)
{
    struct anc_hs_dev *pdev = g_anc_max14744_priv->anc_dev;
    struct anc_hs_codec_ops *fops = &pdev->ops;

    /* userspace prohibit charging with using hs-mic pin */
    if (ANC_HS_DISABLE_CHARGE == g_anc_max14744_priv->force_charge_ctl) {
        hwlog_info("%s(%u) : charge is occupied by app level\n", __FUNCTION__, __LINE__);
        /* need second detect for charge*/
        g_anc_max14744_priv->detect_again = true;
        return;
    }

    /* hs mic is using record, not take it */
    if (ANC_HS_DISABLE_CHARGE == g_anc_max14744_priv->hs_micbias_ctl) {
        /* need second detect for charge*/
        hwlog_info("%s(%u) :hs mic is in using!\n", __FUNCTION__, __LINE__);
        g_anc_max14744_priv->detect_again = true;
        return ;
    }

    g_anc_max14744_priv->detect_again = false;
    hwlog_debug("%s(%u) : anc hs charge !\n", __FUNCTION__, __LINE__);

    /* headset may have pluged out, just return */
    if (!fops->check_headset_in(g_anc_max14744_priv->private_data)) {
        hwlog_info("%s(%u) :headset has plug out!\n", __FUNCTION__, __LINE__);
        return ;
    }

    mutex_lock(&g_anc_max14744_priv->charge_lock);
    /* connect 5vboost with hs_mic pin*/
    power_mode();
    mutex_unlock(&g_anc_max14744_priv->charge_lock);

    /* waiting for anc chip start up*/
    hwlog_info("%s: delay %d ms to wait anc chip up!\n", __FUNCTION__, g_anc_max14744_priv->sleep_time);
    mdelay(g_anc_max14744_priv->sleep_time);

    mutex_lock(&g_anc_max14744_priv->charge_lock);

    if ((g_anc_max14744_priv->hs_micbias_ctl == ANC_HS_ENABLE_CHARGE) &&
         anc_max14744_need_charge()) {
        /* start to charge for anc headset and respond charging btn event*/
        if (g_anc_max14744_priv->anc_hs_mode == ANC_HS_CHARGE_OFF) {

            hwlog_info("%s(%u) : anc_hs enable irq !\n", __FUNCTION__, __LINE__);
            g_anc_max14744_priv->anc_hs_mode = ANC_HS_CHARGE_ON;
            max14744_unmask_btn_irq();
        }
        if(ERROR_RET == anc_hs_send_hifi_msg(ANC_HS_CHARGE_ON))
        {
            hwlog_err("%s(%u) : anc_hs_send_hifi_msg TURN ON ANC_HS return ERROR !\n", __FUNCTION__, __LINE__);
        }
    } else {
        if (g_anc_max14744_priv->anc_hs_mode == ANC_HS_CHARGE_ON) {
            hwlog_info("%s(%u) : anc_hs disable irq !\n", __FUNCTION__, __LINE__);
        }
        /* stop charge and change status to CHARGE_OFF*/
        max14744_mask_btn_irq();
        mic_bias_mode(LDO1_CALL_MODE);
        udelay(500);
        g_anc_max14744_priv->anc_hs_mode = ANC_HS_CHARGE_OFF;
        if(ERROR_RET == anc_hs_send_hifi_msg(ANC_HS_CHARGE_OFF))
        {
            hwlog_err("%s(%u) : anc_hs_send_hifi_msg TURN OFF ANC_HS return ERROR !\n", __FUNCTION__, __LINE__);
        }
    }

    mutex_unlock(&g_anc_max14744_priv->charge_lock);

    return;
}

/**
 * update_charge_status - according to external control info to update
 *                        charge function
 *
 * get 3 times adc value with 1ms delay and use average value(delta) of it,
 * charge for it when delta is between anc_hs_limit_min and anc_hs_limit_max
 **/
static void update_charge_status(void)
{
    struct anc_hs_dev *pdev = g_anc_max14744_priv->anc_dev;
    struct anc_hs_codec_ops *fops = &pdev->ops;

    if (ANC_HS_DISABLE_CHARGE == g_anc_max14744_priv->hs_micbias_ctl ||
        ANC_HS_DISABLE_CHARGE == g_anc_max14744_priv->force_charge_ctl) {
        /* force stop charge function */
        mutex_lock(&g_anc_max14744_priv->charge_lock);

        if (g_anc_max14744_priv->anc_hs_mode == ANC_HS_CHARGE_ON) {
            max14744_mask_btn_irq();
            mic_bias_mode(LDO1_CALL_MODE);
            udelay(500);

            hwlog_info("%s(%u) : stop charging for anc hs !\n", __FUNCTION__, __LINE__);
            g_anc_max14744_priv->anc_hs_mode = ANC_HS_CHARGE_OFF;
            g_anc_max14744_priv->mic_used = true;
        } 

        mutex_unlock(&g_anc_max14744_priv->charge_lock);
    } else if (ANC_HS_ENABLE_CHARGE == g_anc_max14744_priv->hs_micbias_ctl &&
                 ANC_HS_ENABLE_CHARGE == g_anc_max14744_priv->force_charge_ctl) {
        if (g_anc_max14744_priv->mic_used) {
            g_anc_max14744_priv->mic_used = false;
            /* headset maybe have plug out here */
            if (!fops->check_headset_in(g_anc_max14744_priv->private_data)) {
                hwlog_info("%s(%u) :headset has plug out!\n", __FUNCTION__, __LINE__);
            } else {
                /* force resume charge for anc headset */
                mutex_lock(&g_anc_max14744_priv->charge_lock);
                if(g_anc_max14744_priv->anc_hs_mode == ANC_HS_CHARGE_OFF){
                    g_anc_max14744_priv->anc_hs_mode = ANC_HS_CHARGE_ON;
                    power_mode();
                    udelay(500);
                    max14744_unmask_btn_irq();

                    hwlog_info("%s(%u) : resume charging for anc hs!\n", __FUNCTION__, __LINE__);
                }
                mutex_unlock(&g_anc_max14744_priv->charge_lock);
            }
        } else if(g_anc_max14744_priv->detect_again) {
            /* need detect charge again due to interrupted before */
            anc_max14744_charge_judge();
        }
    }
}

/**
 * anc_hs_start_charge - call this to enbale 5vboost if support anc charge function
 *
 * make sure call this before headset sradc, the voltage stable time
 * should consider here, now 50ms need at least which is dependent
 * on hardware feature.
 **/
void anc_max14744_start_charge(void)
{
    if ((g_anc_max14744_priv == NULL) || (g_anc_max14744_priv->registered == false)) {
        return;
    }

    /* enable 5vboost first, this need time to be stable */
    hwlog_info("%s(%u) :enable 5vboost\n", __FUNCTION__, __LINE__);

    /* default let hsbias connect to hs-mic pin*/
    mic_bias_mode(LDO1_CALL_MODE);
    anc_max14744_gpio_set_value(g_anc_max14744_priv->anc_pwr_en_gpio, 1);
    g_anc_max14744_priv->anc_hs_mode = ANC_HS_CHARGE_OFF;

    return;
}


/**
 * anc_hs_force_charge - when need hs-mic to record in charging status,
 *                       you must call this function to close charge
 *
 * @disable: charge control value, only enable and disable
 *
 **/
void anc_max14744_force_charge(int disable)
{
    if ((g_anc_max14744_priv == NULL) || (g_anc_max14744_priv->registered == false)) {
        return;
    }
    /* don't make repeated switch with charge status*/
    if(disable == g_anc_max14744_priv->hs_micbias_ctl) {
        return;
    }
    g_anc_max14744_priv->hs_micbias_ctl = disable;

    /* update charge status here*/
    update_charge_status();

    return;
}

/**
 * anc_hs_charge_detect - detect whether plug-in headset is anc headset, if
 *                        it is anc headset, we will use mic-pin to charge with it
 *
 * @saradc_value: voltage number on mic-pin when headset plug in
 * @headset_type: headset type, only support 4-pole and 3-pole
 *
 * due to resistor difference , we should calibrate it first, then use
 * for 3-pole headset, don't make further judge.
 * (attention): revert 4-pole headset still need
 *            5vboost on to support second recognition
 **/
void anc_max14744_charge_detect(int saradc_value, int headset_type)
{
    if ((g_anc_max14744_priv == NULL) || (g_anc_max14744_priv->registered == false)) {
        return ;
    }

    /* calibration adc resistance which can
	   make charge detect more accuracy*/
    anc_max14744_adc_calibration();

    g_anc_max14744_priv->headset_type = headset_type;

    /* revert 4-pole headset still need 5vboost on
	   to support second recognition*/
    if (headset_type == ANC_HS_NORMAL_4POLE) {
        /* 4-pole headset maybe an anc headset*/
        hwlog_debug("%s : start anc hs charge judge\n", __FUNCTION__);
        anc_max14744_charge_judge();
    } else if (headset_type == ANC_HS_NORMAL_3POLE) {
        hwlog_info("%s : no disable 5vboost for 3-pole headset\n", __FUNCTION__);
        /* 3-pole also support second-detect */
        //enable_boost(false);
    }

}

/**
 * anc_hs_stop_charge - call this function when headset plug out
 *
 **/
void anc_max14744_stop_charge(void)
{
    if ((g_anc_max14744_priv == NULL) || (g_anc_max14744_priv->registered == false)) {
        return;
    }

    hwlog_info("%s : stop anc hs charge\n", __FUNCTION__);

    max14744_mask_btn_irq();
    normal_mode();
    anc_max14744_gpio_set_value(g_anc_max14744_priv->anc_pwr_en_gpio, 0);
    g_anc_max14744_priv->anc_hs_mode = ANC_HS_CHARGE_OFF;
    g_anc_max14744_priv->headset_type = ANC_HS_NONE;
    g_anc_max14744_priv->button_pressed = 0;

    if(ERROR_RET == anc_hs_send_hifi_msg(ANC_HS_CHARGE_OFF))
    {
        hwlog_err("%s(%u) : anc_hs_send_hifi_msg TURN OFF ANC_HS return ERROR !\n", __FUNCTION__, __LINE__);
    }

    return;
}

/**
 * anc_max14744_dev_register - call this function to support max14744,
 *                       this need hardware support
 *
 * @dev: anc_hs_dev function and data description
 * @codec_data: codec description which is need by callback function
 *
 * only support one codec to be registered, and all the callback
 * functions must be realized.
 **/
int anc_max14744_dev_register(struct anc_hs_dev *dev, void * codec_data)
{
    /* anc_hs driver not be probed, just return */
    if(g_anc_max14744_priv == NULL) {
        return -ENODEV;
    }

    /* only support one codec to be registered */
    if(g_anc_max14744_priv->registered) {
        hwlog_err("one codec has registered, no more permit\n");
        return -EEXIST;
    }
    if(!dev->ops.check_headset_in ||
        !dev->ops.btn_report ||
        !dev->ops.codec_resume_lock ||
        !dev->ops.plug_in_detect ||
        !dev->ops.plug_out_detect) {
        hwlog_err("codec ops funtion must be all registed\n");
        return -EINVAL;
    }

    g_anc_max14744_priv->anc_dev = dev;
    g_anc_max14744_priv->private_data = codec_data;
    g_anc_max14744_priv->registered = true;

    force_clear_irq();
    max14744_unmask_plug_irq();
    hwlog_info("%s(%u) : anc hs has been register sucessful!\n", __FUNCTION__, __LINE__);

    return 0;
}

bool check_anc_max14744_support(void)
{
    if((g_anc_max14744_priv == NULL) || (g_anc_max14744_priv->registered == false)) {
        return false;
    } else {
        return true;
    }
}

bool anc_max14744_plug_enable(void)
{
    if((g_anc_max14744_priv == NULL) || (g_anc_max14744_priv->registered == false)) {
        return false;
    } else {
        return true;
    }
}

bool anc_max14744_check_headset_pluged_in(void)
{
    int value = 0;

    if(g_anc_max14744_priv == NULL)
	    return false;

    anc_max14744_regmap_read(ANC_MAX14744_R003_STATUS, &value);

    if(!(value & ANC_MAX14744_JACK_DETECT_BIT))
        return true;
    else
        return false;
}

static int get_irq_type(void)
{
    int irq_type = ANC_MAX14744_IQR_MAX;
    int value = 0;
    int mask = 0;

    anc_max14744_regmap_read(ANC_MAX14744_R006_INTERRUPT, &value);
    anc_max14744_regmap_read(ANC_MAX14744_R007_MASK, &mask);

    if((value & ANC_MAX14744_PLUG_IRQ_BIT) && anc_max14744_check_headset_pluged_in())
        irq_type = ANC_MAX14744_JACK_PLUG_IN;
    else if((value & ANC_MAX14744_PLUG_IRQ_BIT) && !anc_max14744_check_headset_pluged_in())
        irq_type = ANC_MAX14744_JACK_PLUG_OUT;
    else if((value & ANC_MAX14744_BUTTON_PRESS_IRQ_BIT) && (mask & ANC_MAX14744_BUTTON_PRESS_IRQ_MASK_BIT))
        irq_type = ANC_MAX14744_BUTTON_PRESS;

    hwlog_info("max14744 irq value is 0x%x, mask is 0x%x, type is %d.", value, mask, irq_type);

    return irq_type;
}

static void anc_hs_plugin_work(struct work_struct* work)
{
    struct anc_hs_codec_ops *fops = &g_anc_max14744_priv->anc_dev->ops;

    wake_lock(&g_anc_max14744_priv->wake_lock);

    if(NULL != g_anc_max14744_priv->private_data) {
        fops->plug_in_detect(g_anc_max14744_priv->private_data);
    }

    wake_unlock(&g_anc_max14744_priv->wake_lock);

}

static void anc_hs_plugout_work(struct work_struct* work)
{
    struct anc_hs_codec_ops *fops = &g_anc_max14744_priv->anc_dev->ops;

    wake_lock(&g_anc_max14744_priv->wake_lock);

    if(NULL != g_anc_max14744_priv->private_data) {
        fops->plug_out_detect(g_anc_max14744_priv->private_data);
    }

    wake_unlock(&g_anc_max14744_priv->wake_lock);

}

static void anc_hs_btn_work(struct work_struct* work)
{
    wake_lock(&g_anc_max14744_priv->wake_lock);
    anc_max14744_btn_judge();
    wake_unlock(&g_anc_max14744_priv->wake_lock);

}

#if 0
static irqreturn_t max14744_handler(int irq, void *data)
{
    disable_irq_nosync(irq);
    return IRQ_WAKE_THREAD;
}
#endif

/**
 * anc_max14744_irq_handler - respond button irq while charging
 *                      for anc headset
 * @irq: irq number
 * @data: irq data, not used now
 *
 * disable irq will be better until delay_work to be scheduled.
 **/
static irqreturn_t anc_max14744_irq_handler(int irq, void* data)
{
    int irq_type;
    int value = 0;
    int loop = 5;

    if ((g_anc_max14744_priv == NULL) || (g_anc_max14744_priv->registered == false)) {
        pr_info("anc_max14744 dev has not been regestered\n");
        anc_max14744_regmap_read(ANC_MAX14744_R006_INTERRUPT, &value);
        return IRQ_HANDLED;
    }

    wake_lock_timeout(&g_anc_max14744_priv->wake_lock, msecs_to_jiffies(1000));
    irq_type = get_irq_type();

    switch(irq_type) {
        case ANC_MAX14744_JACK_PLUG_IN:
            queue_delayed_work(g_anc_max14744_priv->anc_hs_plugin_delay_wq,
                               &g_anc_max14744_priv->anc_hs_plugin_delay_work,
                               msecs_to_jiffies(800));
            break;
        case ANC_MAX14744_JACK_PLUG_OUT:
            queue_delayed_work(g_anc_max14744_priv->anc_hs_plugout_delay_wq,
                               &g_anc_max14744_priv->anc_hs_plugout_delay_work,
                               0);
            break;
        case ANC_MAX14744_BUTTON_PRESS:
            queue_delayed_work(g_anc_max14744_priv->anc_hs_btn_delay_wq,
                               &g_anc_max14744_priv->anc_hs_btn_delay_work,
                               msecs_to_jiffies(20));
            break;
        default:
            break;
    }

    while(loop > 0) {
        irq_type = get_irq_type();
        if(irq_type == ANC_MAX14744_IQR_MAX) {
            break;
        }
        if(irq_type == ANC_MAX14744_JACK_PLUG_OUT) {
            queue_delayed_work(g_anc_max14744_priv->anc_hs_plugout_delay_wq,
                               &g_anc_max14744_priv->anc_hs_plugout_delay_work,
                               0);
        }
        loop = loop - 1;
    }
    if(loop <= 0) {
        hwlog_err("anc_hs_max14744: there is irq unhandled in anc_max14744_irq_handler.\n");
    }

    return IRQ_HANDLED;
}

static int judge_headset_type_further(void)
{
    int value = 0;
    int value1 = 0;
    int idet_lvl = 0;
    int retry = 3;
    int idet = 0;

    while(retry--) {
        anc_max14744_regmap_read(ANC_MAX14744_R002_ADC_STATUS, &value);
        if(value & ANC_MAX14744_EOC_BIT)
            break;
        msleep(20);
    }
    if(retry < 0) {
        anc_max14744_regmap_read(ANC_MAX14744_R001_ADC_CONVERSION, &value);
        hwlog_err("headset resistance : adc not prepared first time %d.\n", value);
        return 255;
    }

    anc_max14744_regmap_read(ANC_MAX14744_R001_ADC_CONVERSION, &value);
	hwlog_info("headset resistance first time: %d\n", value);

#if 0
    if(g_anc_max14744_priv->anc_hs_mode == ANC_HS_CHARGE_OFF) {
        anc_max14744_regmap_write(ANC_MAX14744_R007_MASK, 0x00);
        anc_max14744_regmap_write(ANC_MAX14744_R009_PINS_CONTROL2, 0x10);
        anc_max14744_regmap_write(ANC_MAX14744_R009_PINS_CONTROL2, 0x00);

        retry = 5;
        while(retry--) {
            anc_max14744_regmap_read(ANC_MAX14744_R002_ADC_STATUS, &value);
            if(value & ANC_MAX14744_EOC_BIT)
                break;
            msleep(20);
        }
        if(retry < 0) {
            anc_max14744_regmap_read(ANC_MAX14744_R006_INTERRUPT, &value1);
            msleep(20);
            anc_max14744_regmap_write(ANC_MAX14744_R007_MASK, 0x31);

            hwlog_err("headset resistance : adc not prepared %d.\n", value);
            return 255;
        }
        anc_max14744_regmap_read(ANC_MAX14744_R001_ADC_CONVERSION, &value);

        anc_max14744_regmap_read(ANC_MAX14744_R006_INTERRUPT, &value1);
        msleep(20);
        anc_max14744_regmap_write(ANC_MAX14744_R007_MASK, 0x31);

        hwlog_info("headset resistance second time: %d, retry:%d\n", value, retry);
    }
#endif
    //compute adc final value
    anc_max14744_regmap_read(ANC_MAX14744_R00A_ADC_CONTROL, &idet_lvl);
    if(idet_lvl & ANC_MAX14744_IDETLVL_BIT) {
        idet =  IDET_LVL3;
    } else {
        idet =  IDET_LVL1;
    }
    value = ((value * ADC_STEP + ADC_OFFSET) / idet);

    hwlog_info("resistance value: %d with idet:%d\n", value, idet);

    return value;
}

static int compute_final_voltage()
{
    int R1 = 51;
    int R2 = 100;
    int voltage;

    msleep(70);
    voltage = hisi_adc_get_value(g_anc_max14744_priv->channel_pwl_l);

    return (voltage * (R1+R2))/R1;
}

/**
 * anc_max14744_ioctl - ioctl interface for userspeace
 *
 * @file: file description
 * @cmd: control commond
 * @arg: arguments
 *
 * userspeace can get charge status and force control
 * charge status.
 **/
static long anc_max14744_ioctl(struct file* file, unsigned int cmd,
                         unsigned long arg)
{
    int ret = 0;
    int charge_mode;
	int voltage;
	int adc_value;
    unsigned int __user* pUser = (unsigned int __user*) arg;

    if(g_anc_max14744_priv->registered == false) {
        return -EBUSY;
    }

    switch (cmd) {
        case IOCTL_ANC_HS_CHARGE_ENABLE_CMD:
            if(g_anc_max14744_priv->force_charge_ctl == ANC_HS_ENABLE_CHARGE) {
                break;
            }
            /* resume anc headset charge*/
            g_anc_max14744_priv->force_charge_ctl = ANC_HS_ENABLE_CHARGE;
            hwlog_info("app level contrl set charge status with %d\n", g_anc_max14744_priv->force_charge_ctl);
            update_charge_status();
            break;
        case IOCTL_ANC_HS_CHARGE_DISABLE_CMD:
            if(g_anc_max14744_priv->force_charge_ctl == ANC_HS_DISABLE_CHARGE) {
                break;
            }
            /* force stop anc headset charge*/
            g_anc_max14744_priv->force_charge_ctl = ANC_HS_DISABLE_CHARGE;
            hwlog_info("app level contrl set charge status with %d\n", g_anc_max14744_priv->force_charge_ctl);
            update_charge_status();
            break;
        case IOCTL_ANC_HS_GET_HEADSET_CMD:
            charge_mode = g_anc_max14744_priv->anc_hs_mode;
            if(charge_mode == ANC_HS_CHARGE_ON) {
                if(!anc_max14744_need_charge()) {
                    charge_mode = ANC_HS_CHARGE_OFF;
                } else {
                    msleep(10);
                    if(!anc_max14744_need_charge()) {
                        charge_mode = ANC_HS_CHARGE_OFF;
                    }
                }
            }
            if(charge_mode == ANC_HS_CHARGE_ON) {
                g_anc_max14744_priv->headset_type = ANC_HS_HEADSET;
            }
            ret = put_user((__u32)(g_anc_max14744_priv->headset_type), pUser);
            break;
        case IOCTL_ANC_HS_GET_CHARGE_STATUS_CMD:
            ret = put_user((__u32)(g_anc_max14744_priv->anc_hs_mode), pUser);
            break;
        case IOCTL_ANC_HS_GET_VBST_5VOLTAGE_CMD:
            mic_bias_mode(LDO1_CALL_MODE);
            anc_max14744_gpio_set_value(g_anc_max14744_priv->anc_pwr_en_gpio, 1);
            voltage = compute_final_voltage();
            anc_max14744_gpio_set_value(g_anc_max14744_priv->anc_pwr_en_gpio, 0);

            ret = put_user((__u32)voltage, pUser);
            break;
        case IOCTL_ANC_HS_GET_VDD_BUCK_VOLTAGE_CMD:
            mic_bias_mode(LDO1_CALL_MODE);
			anc_max14744_gpio_set_value(g_anc_max14744_priv->anc_pwr_en_gpio, 0);
            voltage = compute_final_voltage();

            ret = put_user((__u32)voltage, pUser);
            break;
        case IOCTL_ANC_HS_GET_HEADSET_RESISTANCE_CMD:
			adc_value = judge_headset_type_further();
            ret = put_user((__u32)(adc_value), pUser);
            break;
        default:
            hwlog_err("unsupport cmd\n");
            ret = -EINVAL;
            break;
    }

    return (long)ret;
}

static ssize_t anc_max14744_reg_list_show(struct device* dev,
                                     struct device_attribute* attr, char* buf)
{
    int value;
    int reg;
    char valStr[20];

    buf[0] = '\0';
    for(reg = 0; reg <= 0x0C; reg++) {

        anc_max14744_regmap_read(reg, &value);
        sprintf(valStr, "0x%02x = 0x%02x\n", reg, value);

        strcat(buf, valStr);
    }
    return strlen(buf);
}

static ssize_t anc_max14744_reg_single_show(struct device* dev,
                                     struct device_attribute* attr, char* buf)
{
    int value;
    int reg;
    char valStr[20];
    char *pEnd = buf;

    buf[0] = '\0';

    reg = simple_strtol(buf, &pEnd, 16);
    anc_max14744_regmap_read(reg, &value);
    sprintf(valStr, "0x%02x = 0x%02x\n", reg, value);
    strcat(buf, valStr);

    return strlen(buf);
}

static ssize_t anc_max14744_adc_show(struct device* dev,
                                     struct device_attribute* attr, char* buf)
{
    char valStr[20];
    int ear_pwr_h = 0, ear_pwr_l = 0;

    buf[0] = '\0';

    ear_pwr_h = hisi_adc_get_value(g_anc_max14744_priv->channel_pwl_h);
    mdelay(50);
    ear_pwr_l = hisi_adc_get_value(g_anc_max14744_priv->channel_pwl_l);
    mdelay(50);
    sprintf(valStr, "h = %d, l = %d\n", ear_pwr_h, ear_pwr_l);
    strcat(buf, valStr);

    return strlen(buf);
}
static ssize_t anc_max14744_reg_write_store(struct device* dev,
                                      struct device_attribute* attr,
                                      const char* buf, size_t count)
{
    int reg = 0;
    int val = 0;
    char *pEnd = (char*)buf;

    reg = simple_strtol(buf, &pEnd, 16);
    pEnd++;
    hwlog_info("anc_max14744_reg_write_store reg : 0x%x\n", reg);
    val = simple_strtol(pEnd, &pEnd, 16);
    hwlog_info("anc_max14744_reg_write_store val : 0x%x\n", val);

    if(reg <= 0x06 || reg > 0x0c) {
        hwlog_err("invalid register address: 0x%x\n", reg);
        return -ENXIO;
    }

    anc_max14744_regmap_write(reg, val);

    return count;
}


static DEVICE_ATTR(reg_list, 0664, anc_max14744_reg_list_show,
                   NULL);
static DEVICE_ATTR(reg_single, 0664, anc_max14744_reg_single_show,
                   NULL);
static DEVICE_ATTR(reg_write, 0660, NULL,
                   anc_max14744_reg_write_store);
static DEVICE_ATTR(adc, 0664, anc_max14744_adc_show,
                   NULL);

static struct attribute* anc_max14744_attributes[] =
{
    &dev_attr_reg_list.attr,
    &dev_attr_reg_single.attr,
    &dev_attr_reg_write.attr,
    &dev_attr_adc.attr,
    NULL
};

static const struct attribute_group anc_max14744_attr_group =
{
    .attrs = anc_max14744_attributes,
};

static const struct regmap_config anc_max14744_regmap = {
    .reg_bits         = 8,
    .val_bits         = 8,
    .max_register     = ANC_MAX14744_R014_CONTROL,
    .reg_defaults     = anc_max14744_reg,
    .num_reg_defaults = ARRAY_SIZE(anc_max14744_reg),
    .volatile_reg     = anc_max14744_volatile_register,
    .readable_reg     = anc_max14744_readable_register,
    .cache_type       = REGCACHE_RBTREE,
};

static const struct file_operations anc_max14744_fops =
{
    .owner               = THIS_MODULE,
    .open                = simple_open,
    .unlocked_ioctl      = anc_max14744_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl        = anc_max14744_ioctl,
#endif
};

static struct miscdevice anc_max14744_device =
{
    .minor  = MISC_DYNAMIC_MINOR,
    .name   = "anc_hs",
    .fops   = &anc_max14744_fops,
};

/* load dts config for board difference */
static void load_anc_hs_config(struct device_node* node)
{
    int temp;

    /* read adc channel number */
    if (!of_property_read_u32(node, "adc_channel_h", &temp)) {
        g_anc_max14744_priv->channel_pwl_h = temp;
    } else {
        g_anc_max14744_priv->channel_pwl_h = 15;
    }
    if (!of_property_read_u32(node, "adc_channel_l", &temp)) {
        g_anc_max14744_priv->channel_pwl_l = temp;
    } else {
        g_anc_max14744_priv->channel_pwl_l = 14;
    }
    /* read charge limit */
    if (!of_property_read_u32(node, "anc_hs_limit_min", &temp)) {
        g_anc_max14744_priv->anc_hs_limit_min = temp;
    } else {
        g_anc_max14744_priv->anc_hs_limit_min = ANC_HS_LIMIT_MIN;
    }
    if (!of_property_read_u32(node, "anc_hs_limit_max", &temp)) {
        g_anc_max14744_priv->anc_hs_limit_max = temp;
    } else {
        g_anc_max14744_priv->anc_hs_limit_max = ANC_HS_LIMIT_MAX;
    }
    /* read hook limit */
    if (!of_property_read_u32(node, "anc_hs_btn_hook_min_voltage", &temp)) {
        g_anc_max14744_priv->anc_hs_btn_hook_min_voltage = temp;
    } else {
        g_anc_max14744_priv->anc_hs_btn_hook_min_voltage = ANC_HS_HOOK_MIN;
    }
    if (!of_property_read_u32(node, "anc_hs_btn_hook_max_voltage", &temp)) {
        g_anc_max14744_priv->anc_hs_btn_hook_max_voltage = temp;
    } else {
        g_anc_max14744_priv->anc_hs_btn_hook_max_voltage = ANC_HS_HOOK_MAX;
    }
    /* read volume up limit */
    if (!of_property_read_u32(node, "anc_hs_btn_volume_up_min_voltage", &temp)) {
        g_anc_max14744_priv->anc_hs_btn_volume_up_min_voltage = temp;
    } else {
        g_anc_max14744_priv->anc_hs_btn_volume_up_min_voltage = ANC_HS_VOLUME_UP_MIN;
    }
    if (!of_property_read_u32(node, "anc_hs_btn_volume_up_max_voltage", &temp)) {
        g_anc_max14744_priv->anc_hs_btn_volume_up_max_voltage = temp;
    } else {
        g_anc_max14744_priv->anc_hs_btn_volume_up_max_voltage = ANC_HS_VOLUME_UP_MAX;
    }
    /* read volume down limit */
    if (!of_property_read_u32(node, "anc_hs_btn_volume_down_min_voltage", &temp)) {
        g_anc_max14744_priv->anc_hs_btn_volume_down_min_voltage = temp;
    } else {
        g_anc_max14744_priv->anc_hs_btn_volume_down_min_voltage = ANC_HS_VOLUME_DOWN_MIN;
    }
    if (!of_property_read_u32(node, "anc_hs_btn_volume_down_max_voltage", &temp)) {
        g_anc_max14744_priv->anc_hs_btn_volume_down_max_voltage = temp;
    } else {
        g_anc_max14744_priv->anc_hs_btn_volume_down_max_voltage = ANC_HS_VOLUME_DOWN_MAX;
    }
}

static void chip_init(void)
{
    int value = 0;

    anc_max14744_regmap_write(ANC_MAX14744_R007_MASK, 0x00);
    anc_max14744_regmap_write(ANC_MAX14744_R008_PINS_CONTROL1, 0x00);
    anc_max14744_regmap_write(ANC_MAX14744_R009_PINS_CONTROL2, 0x00);
    anc_max14744_regmap_write(ANC_MAX14744_R00B_ACC_CONTROL1, 0x10);
    anc_max14744_regmap_write(ANC_MAX14744_R00C_ACC_CONTROL2, 0x00);
    anc_max14744_regmap_read(ANC_MAX14744_R006_INTERRUPT, &value);
}

struct anc_hs_ops anc_max14744_ops = {
    .anc_hs_dev_register = anc_max14744_dev_register,
    .anc_hs_check_headset_pluged_in = anc_max14744_check_headset_pluged_in,
    .anc_hs_start_charge = anc_max14744_start_charge,
    .anc_hs_charge_detect = anc_max14744_charge_detect,
    .anc_hs_stop_charge = anc_max14744_stop_charge,
    .anc_hs_force_charge = anc_max14744_force_charge,
    .check_anc_hs_support = check_anc_max14744_support,
    .anc_hs_plug_enable = anc_max14744_plug_enable,
    .anc_hs_5v_control = NULL,
    .anc_hs_invert_hs_control = anc_max14744_invert_headset_control,
    .anc_hs_refresh_headset_type = anc_max14744_refresh_headset_type,
};

/**********************************************************
 *  Function:       anc_max14744_probe
 *  Discription:    anc_max14744 module probe
 *  Parameters:   client:i2c_client
 *                      id:i2c_device_id
 *  return value:  0-sucess or others-fail
**********************************************************/
static int anc_max14744_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
    int ret = -1;
    unsigned long flag = IRQF_ONESHOT | IRQF_NO_SUSPEND;
    struct anc_max14744_priv *di = NULL;
    struct device_node *np = NULL;
    struct pinctrl *p;
    struct pinctrl_state *pinctrl_def;

    hwlog_info("anc_max14744_probe++\n");
    di = devm_kzalloc(&client->dev,sizeof(*di), GFP_KERNEL);
    if (!di)
    {
        hwlog_err("anc_max14744_priv is NULL!\n");
        return -ENOMEM;
    }

    g_anc_max14744_priv = di;
    di->dev = &client->dev;
    np = di->dev->of_node;
    di->client = client;

    i2c_set_clientdata(client, di);

    mutex_init(&di->charge_lock);
    mutex_init(&di->btn_mutex);
    mutex_init(&di->invert_hs_lock);
    spin_lock_init(&di->irq_lock);
    wake_lock_init(&di->wake_lock, WAKE_LOCK_SUSPEND, "anc_max14744");

    /* init all values */
    di->anc_hs_mode = ANC_HS_CHARGE_OFF;
    di->irq_flag = true;
    di->mic_used = false;
    di->sleep_time = ANC_CHIP_STARTUP_TIME;
    di->adc_calibration_base = 0;
    di->hs_micbias_ctl = ANC_HS_ENABLE_CHARGE;
    di->force_charge_ctl = ANC_HS_ENABLE_CHARGE;
    di->boost_flag = false;
    di->registered = false;
	di->headset_type = ANC_HS_NONE;
    load_anc_hs_config(np);

    p = devm_pinctrl_get(di->dev);
    hwlog_info("max14744:node name is %s\n",np->name);
    if (IS_ERR(p)) {
        hwlog_err("could not get pinctrl dev.\n");
        goto err_out;
    }
    pinctrl_def = pinctrl_lookup_state(p, "default");
    if (IS_ERR(pinctrl_def)) {
        hwlog_err("could not get defstate.\n");
    }

    ret = pinctrl_select_state(p, pinctrl_def);
    if (ret)
        hwlog_err("could not set pins to default state.\n");

    di->regmapL = regmap_init_i2c(client, &anc_max14744_regmap);
    if (IS_ERR(di->regmapL)) {
        ret = PTR_ERR(di->regmapL);
        hwlog_err("Failed to allocate regmapL: %d\n", ret);
        goto err_out;
    }

    if ((ret = sysfs_create_group(&client->dev.kobj, &anc_max14744_attr_group)) < 0) {
        hwlog_err("failed to register sysfs\n");
    }

    /* create irq workqueue */
    di->anc_hs_plugin_delay_wq =
        create_singlethread_workqueue("anc_hs_plugin_delay_wq");
    if (!(di->anc_hs_plugin_delay_wq)) {
        hwlog_err("%s : plugin wq create failed\n", __FUNCTION__);
        ret = -ENOMEM;
        goto err_out_sysfs;
    }
    INIT_DELAYED_WORK(&di->anc_hs_plugin_delay_work, anc_hs_plugin_work);

    di->anc_hs_plugout_delay_wq =
        create_singlethread_workqueue("anc_hs_plugout_delay_wq");
    if (!(di->anc_hs_plugout_delay_wq)) {
        hwlog_err("%s : plugout wq create failed\n", __FUNCTION__);
        ret = -ENOMEM;
        goto err_plugin_delay_wq;
    }
    INIT_DELAYED_WORK(&di->anc_hs_plugout_delay_work, anc_hs_plugout_work);

    di->anc_hs_btn_delay_wq =
        create_singlethread_workqueue("anc_hs_btn_delay_wq");
    if (!(di->anc_hs_btn_delay_wq)) {
        hwlog_err("%s : btn wq create failed\n", __FUNCTION__);
        ret = -ENOMEM;
        goto err_plugout_delay_wq;
    }
    INIT_DELAYED_WORK(&di->anc_hs_btn_delay_work, anc_hs_btn_work);

    di->anc_hs_invert_ctl_delay_wq =
        create_singlethread_workqueue("anc_hs_invert_ctl_delay_wq");
    if (!(di->anc_hs_invert_ctl_delay_wq)) {
        hwlog_err("%s : invert_ctl wq create failed\n", __FUNCTION__);
        ret = -ENOMEM;
        goto err_invert_ctl_delay_wq;
    }
    INIT_DELAYED_WORK(&di->anc_hs_invert_ctl_delay_work, anc_hs_invert_ctl_work);

    di->anc_pwr_en_gpio = of_get_named_gpio(np,"gpio_pwr_en",0);
    if (di->anc_pwr_en_gpio < 0) {
        hwlog_err("anc_pwr_en_gpio is invalid!\n");
        goto err_btn_delay_wq;
    }
    ret = gpio_request(di->anc_pwr_en_gpio, "anc_max14744_pwr_en");
    if (ret) {
        hwlog_err("error request GPIO for anc_pwr_en_gpio fail %d\n", ret);
        goto err_btn_delay_wq;
    }
    gpio_direction_output(di->anc_pwr_en_gpio, 0);

    di->gpio_int = of_get_named_gpio(np,"gpio_int",0);
    if (di->gpio_int < 0) {
        hwlog_err("gpio_int is invalid!\n");
        goto err_gpio_pwr_en;
    }
    ret = gpio_request(di->gpio_int,"anc_max14744_int");
    if (ret) {
        hwlog_err("error request GPIO for gpio_int fail %d\n", ret);
        goto err_gpio_pwr_en;
    }

    /* set irq gpio to input status */
    gpio_direction_input(di->gpio_int);

    di->anc_max14744_irq = gpio_to_irq(di->gpio_int);

    /*anc max14744 irq request */
    flag |= IRQF_TRIGGER_FALLING;
    ret = request_threaded_irq(di->anc_max14744_irq, NULL,
                      anc_max14744_irq_handler,
                      flag, "anc_max14744_irq", NULL);

    if(ret < 0) {
        hwlog_err("anc_max14744_irq request fail: ret = %d\n", ret);
        goto err_out_gpio;
    }

    pr_info("anc_max14744 gpio:%d,%d\n", di->gpio_int, di->anc_pwr_en_gpio);

    ret = anc_hs_ops_register(&anc_max14744_ops);
    if(ret) {
        hwlog_err("register anc_hs_interface ops failed!\n");
        goto err_out_irq;
    }

    chip_init();

    /* register misc device for userspace */
    ret = misc_register(&anc_max14744_device);
    if (ret) {
        hwlog_err("%s: anc_max14744 misc device register failed", __FUNCTION__);
        goto err_out_irq;
    }

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
    /* detect current device successful, set the flag as present */
    set_hw_dev_flag(DEV_I2C_ANC_MAX14744);
#endif

    hwlog_info("anc_max14744_probe--\n");
    return 0;

err_out_irq:
    free_irq(di->anc_max14744_irq, NULL);
err_out_gpio:
    gpio_free(di->gpio_int);
err_gpio_pwr_en:
    gpio_free(di->anc_pwr_en_gpio);
err_btn_delay_wq:
    if (di->anc_hs_invert_ctl_delay_wq) {
        cancel_delayed_work(&di->anc_hs_invert_ctl_delay_work);
        flush_workqueue(di->anc_hs_invert_ctl_delay_wq);
        destroy_workqueue(di->anc_hs_invert_ctl_delay_wq);
    }
err_invert_ctl_delay_wq:
    if (di->anc_hs_btn_delay_wq) {
        cancel_delayed_work(&di->anc_hs_btn_delay_work);
        flush_workqueue(di->anc_hs_btn_delay_wq);
        destroy_workqueue(di->anc_hs_btn_delay_wq);
    }
err_plugout_delay_wq:
    if (di->anc_hs_plugout_delay_wq) {
        cancel_delayed_work(&di->anc_hs_plugout_delay_work);
        flush_workqueue(di->anc_hs_plugout_delay_wq);
        destroy_workqueue(di->anc_hs_plugout_delay_wq);
    }
err_plugin_delay_wq:
    if (di->anc_hs_plugin_delay_wq) {
        cancel_delayed_work(&di->anc_hs_plugin_delay_work);
        flush_workqueue(di->anc_hs_plugin_delay_wq);
        destroy_workqueue(di->anc_hs_plugin_delay_wq);
    }
err_out_sysfs:
    sysfs_remove_group(&client->dev.kobj, &anc_max14744_attr_group);
err_out:

    if (ret < 0) {
        if (di->regmapL)
            regmap_exit(di->regmapL);
        kfree(di);
    }
    g_anc_max14744_priv = NULL;
    np = NULL;

    return ret;
}

 /**********************************************************
 *  Function:       anc_max14744_remove
 *  Discription:    anc_max14744 module remove
 *  Parameters:   client:i2c_client
 *  return value:  0-sucess or others-fail
 **********************************************************/
 static int anc_max14744_remove(struct i2c_client *client)
{
    struct anc_max14744_priv *di = i2c_get_clientdata(client);

    if(di == NULL)
        return 0;

    if(di && di->regmapL)
        regmap_exit(di->regmapL);

    if (di->anc_hs_btn_delay_wq) {
        cancel_delayed_work(&di->anc_hs_btn_delay_work);
        flush_workqueue(di->anc_hs_btn_delay_wq);
        destroy_workqueue(di->anc_hs_btn_delay_wq);
    }

    if (di->anc_hs_plugout_delay_wq) {
        cancel_delayed_work(&di->anc_hs_plugout_delay_work);
        flush_workqueue(di->anc_hs_plugout_delay_wq);
        destroy_workqueue(di->anc_hs_plugout_delay_wq);
    }

    if (di->anc_hs_plugin_delay_wq) {
        cancel_delayed_work(&di->anc_hs_plugin_delay_work);
        flush_workqueue(di->anc_hs_plugin_delay_wq);
        destroy_workqueue(di->anc_hs_plugin_delay_wq);
    }

    if (di->anc_hs_invert_ctl_delay_wq) {
        cancel_delayed_work(&di->anc_hs_invert_ctl_delay_work);
        flush_workqueue(di->anc_hs_invert_ctl_delay_wq);
        destroy_workqueue(di->anc_hs_invert_ctl_delay_wq);
    }

    kfree(di);
    di = NULL;

    misc_deregister(&anc_max14744_device);

    hwlog_info("%s: exit\n", __func__);

    return 0;
}


 static struct of_device_id anc_max14744_of_match[] =
 {
     {
         .compatible = "huawei,anc_max14744",
         .data = NULL,
     },
     {
     },
 };
 MODULE_DEVICE_TABLE(of, anc_max14744_of_match);

static const struct i2c_device_id anc_max14744_i2c_id[] = {{"anc_max14744",0},{}};

MODULE_DEVICE_TABLE(i2c, anc_max14744_i2c_id);

 static struct i2c_driver anc_max14744_driver =
 {
     .probe       = anc_max14744_probe,
     .remove     = anc_max14744_remove,
     .id_table    = anc_max14744_i2c_id,
     .driver = {
         .owner = THIS_MODULE,
         .name    = "anc_max14744",
         .of_match_table = of_match_ptr(anc_max14744_of_match),
     },
 };




 /**********************************************************
 *  Function:       anc_max14744_init
 *  Discription:    anc_max14744 module initialization
 *  Parameters:   NULL
 *  return value:  0-sucess or others-fail
 **********************************************************/
 static int __init anc_max14744_init(void)
 {
    int ret =0;

     ret =  i2c_add_driver(&anc_max14744_driver);
     if(ret)
         hwlog_err("%s: i2c_add_driver error!!!\n", __func__);

     return ret;
 }
 /**********************************************************
*  Function:       anc_max14744_exit
*  Discription:    anc_max14744 module exit
 *  Parameters:   NULL
 *  return value:  NULL
 **********************************************************/
 static void __exit anc_max14744_exit(void)
 {
     i2c_del_driver(&anc_max14744_driver);
 }
 module_init(anc_max14744_init);
 module_exit(anc_max14744_exit);


MODULE_DESCRIPTION("anc max14744 headset driver");
MODULE_LICENSE("GPL");
