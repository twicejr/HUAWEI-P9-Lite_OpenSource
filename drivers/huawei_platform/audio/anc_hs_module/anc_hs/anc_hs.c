/*
 * anc_hs.c -- anc headset driver
 *
 * Copyright (c) 2014 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

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
#include <huawei_platform/log/hw_log.h>

#include <linux/huawei/hisi_adc.h>
#include <dsm/dsm_pub.h>
#include "huawei_platform/audio/anc_hs.h"

#define HWLOG_TAG anc_hs
HWLOG_REGIST();
extern int hifi_send_msg(unsigned int mailcode, void *data, unsigned int length);

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

enum anc_hs_gpio_type
{
    ANC_HS_GPIO_SOC           = 0,
    ANC_HS_GPIO_CODEC         = 1,
};

enum headset_status
{
    ANC_HS_HEADSET_PLUG_OUT         = 0,
    ANC_HS_HEADSET_PLUG_IN          = 1,
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
#define  MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC  262148

#define NO_BUTTON_PRESS                      (-1)

/* dmd error report definition*/
static struct dsm_dev dsm_anc_hs =
{
    .name = "dsm_anc_hs",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
    .fops = NULL,
    .buff_size = 1024,
};
static struct dsm_client* anc_hs_dclient = NULL;


struct anc_hs_data
{
#if 0
    struct regulator_bulk_data  regu_boost5v;
#endif
    int anc_hs_mode;         /* charge status */
    int gpio_mic_sw;         /* switch chip control gpio*/
    int mic_irq_gpio;
    int mic_irq;             /* charging btn irq num */
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
    int hs_status;

    struct mutex btn_mutex;
    struct mutex charge_lock;/* charge status protect lock */
    struct wake_lock wake_lock;

    int registered;          /* anc hs regester flag */
    struct anc_hs_dev *dev;     /* anc hs dev */
    void *private_data;      /* store codec decription data*/

    int gpio_type;

    /* charging button irq workqueue */
    struct workqueue_struct* anc_hs_btn_delay_wq;
    struct delayed_work anc_hs_btn_delay_work;

    int mic_sw_plugout_delay;
    struct workqueue_struct* anc_mic_sw_delay_wq;
    struct delayed_work anc_mic_sw_delay_work;
};

#ifdef CONFIG_LLT_TEST
struct anc_hs_static_ops {
    int (*anc_hs_gpio_get_value)(int gpio);
    void (*anc_hs_gpio_set_value)(int gpio, int value);
    void (*anc_hs_dump)(void);
    void (*anc_dsm_report)(int anc_errno, int sys_errno);
    void (*anc_hs_enable_irq)(void);
    void (*anc_hs_disable_irq)(void);
    int (*enable_boost)(bool enable);
    int (*anc_hs_get_adc_delta)(void);
    bool (*anc_hs_need_charge)(void);
    int (*anc_hs_get_btn_value)(void);
    void (*anc_hs_adc_calibration)(void);
    bool (*check_anc_hs_support)(void);
    long (*anc_hs_ioctl)(struct file* file, unsigned int cmd, unsigned long arg);
    ssize_t (*anc_detect_limit_store)(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
    ssize_t (*anc_gpio_sw_store)(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
    ssize_t (*anc_precharge_time_store)(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
    void (*load_anc_hs_config)(struct device_node* node);
    int (*anc_hs_probe)(struct platform_device* pdev);
    int (*anc_hs_remove)(struct platform_device* pdev);
    struct anc_hs_data** pdata;
};
#endif

static struct anc_hs_data* pdata = NULL;

//#define ANC_BTN_MASK (SND_JACK_BTN_0)
#define ANC_BTN_MASK (SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2)

extern void boost5v_denoise_headphone_enable(bool enable);

static inline int anc_hs_gpio_get_value(int gpio)
{
    if(pdata->gpio_type == ANC_HS_GPIO_CODEC) {
        return gpio_get_value_cansleep(gpio);
    } else {
        return gpio_get_value(gpio);
    }
}

static inline void anc_hs_gpio_set_value(int gpio, int value)
{
    if(pdata->gpio_type == ANC_HS_GPIO_CODEC) {
        gpio_set_value_cansleep(gpio, value);
    } else {
        gpio_set_value(gpio, value);
    }
}

static void anc_hs_dump(void)
{
    hwlog_info("%s: mode:%d,irq:%d,sleep_time:%d,mic_used:%d,switch:%d\n",
            __FUNCTION__,
            pdata->anc_hs_mode,
            pdata->irq_flag,
            pdata->sleep_time,
            pdata->mic_used,
            anc_hs_gpio_get_value(pdata->gpio_mic_sw));
}

static void anc_dsm_report(int anc_errno, int sys_errno)
{
    if (!dsm_client_ocuppy(anc_hs_dclient)) {
        dsm_client_record(anc_hs_dclient,
                          "mode:%d,irq:%d,sleep_time:%d,mic_used:%d,switch:%d,errno:%d\n",
                          pdata->anc_hs_mode,
                          pdata->irq_flag,
                          pdata->sleep_time,
                          pdata->mic_used,
                          anc_hs_gpio_get_value(pdata->gpio_mic_sw),
                          sys_errno);
        dsm_client_notify(anc_hs_dclient, anc_errno);
    }
}

static inline void anc_hs_enable_irq(void)
{
    if (!pdata->irq_flag) {
        enable_irq(pdata->mic_irq);
        pdata->irq_flag = true;
    }
}

static inline void anc_hs_disable_irq(void)
{
    if (pdata->irq_flag) {
        disable_irq_nosync(pdata->mic_irq);
        pdata->irq_flag = false;
    }
}

/**
 * enable_boost - enable or disable 5vboost module
 *
 * 5vboost need some time (which is dependent on hardware feature) to be stable time
 * now 50ms need at least, we add 80ms here
 **/
static int enable_boost(bool enable)
{
    int ret = 0;

    /* use boost_flag to void un-balance call */
    if (enable) {
        if (!pdata->boost_flag) {
#if 0
            ret = regulator_bulk_enable(1, &pdata->regu_boost5v);
            if (ret != 0) {
                hwlog_err("%s:bulk enable fail err = %d\n", __FUNCTION__, ret);
                return ret;
            }
#endif
            boost5v_denoise_headphone_enable(true);
            /* 5vboost stable time which is dependent on hardware feature */
            msleep(70);
            pdata->boost_flag = true;
        }
    }
    else {
        if (pdata->boost_flag) {
#if 0
            ret = regulator_bulk_disable(1, &pdata->regu_boost5v);
            if (ret != 0) {
                hwlog_err("%s:bulk disable fail err = %d\n", __FUNCTION__, ret);
                return ret;
            }
#endif
            boost5v_denoise_headphone_enable(false);
            pdata->boost_flag = false;
        }
    }
    return ret;
}

/**
 * anc_hs_get_adc_delta
 *
 * get 3 times adc value with 1ms delay and use average value(delta) of it,
 * charge for it when delta is between anc_hs_limit_min and anc_hs_limit_max
 **/
static int anc_hs_get_adc_delta(void)
{
    int ear_pwr_h = 0, ear_pwr_l = 0;
    int delta = 0, count, fail_count = 0;
    int loop = ADC_READ_COUNT;
    int temp;
    bool need_report = true;

    while (loop) {
        loop--;
        mdelay(1);
        ear_pwr_h = hisi_adc_get_value(pdata->channel_pwl_h);
        if (ear_pwr_h < 0) {
            hwlog_err("%s:get hkadc(h) fail, err:%d\n", __FUNCTION__, ear_pwr_h);
            fail_count++;
            continue;
        }
        ear_pwr_l = hisi_adc_get_value(pdata->channel_pwl_l);
        if (ear_pwr_l < 0) {
            hwlog_err("%s:get hkadc(l) fail, err:%d\n", __FUNCTION__, ear_pwr_l);
            fail_count++;
            continue;
        }
        hwlog_info("%s:adc_h:%d,adc_l:%d\n", __FUNCTION__, ear_pwr_h, ear_pwr_l);

        temp = ear_pwr_h - ear_pwr_l - pdata->adc_calibration_base;

        /* if the adc value far away from normal value, just abandon it*/
        if ((temp > ADC_NORMAL_LIMIT_MAX) || (temp < ADC_NORMAL_LIMIT_MIN) ) {
            fail_count++;
            need_report = false;
            continue;
        }

        delta += temp;
    }

    /* if adc value is out of rage, we make a dmd report */
    if(ear_pwr_h >= ADC_OUT_OF_RANGE || ear_pwr_l >= ADC_OUT_OF_RANGE) {
        anc_dsm_report(ANC_HS_ADC_FULL_ERR, 0);
    }

    count = ADC_READ_COUNT - loop - fail_count;
    if (count == 0) {
        hwlog_err("%s:get anc_hs hkadc failed\n", __FUNCTION__);
        if(need_report) {
            anc_dsm_report(ANC_HS_ADCH_READ_ERR, 0);
        }
        return false;
    }
    /* compute an average value */
    delta /= count;
    hwlog_info("%s:fianal adc value= %d  count=%d\n", __FUNCTION__, delta, count);
    return delta;
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

    if (NULL == pMLIBSetParaInfo)
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

    if(NULL == pPara_ANC_HS)
    {
        kfree(pMLIBSetParaInfo);
        hwlog_err("%s: kzalloc failed\n", __FUNCTION__);
        ret = ERROR_RET;// error return;
        return ret;
    }

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
static bool anc_hs_need_charge(void)
{
    int delta = 0;
    mdelay(30);
    delta = anc_hs_get_adc_delta();
    if ((delta >= pdata->anc_hs_limit_min) &&
        (delta <= pdata->anc_hs_limit_max)) {
        hwlog_info("[%s][%d] anc headset = true\n", __FUNCTION__,__LINE__);
        return true;
    } else {
        hwlog_info("[%s][%d] anc headset = false\n", __FUNCTION__,__LINE__);
        return false;
    }
}

/**
 * anc_hs_get_btn_value - judge which button is pressed
 *
 *
 **/
static int anc_hs_get_btn_value(void)
{
    int delta = 0;
    delta = anc_hs_get_adc_delta();
    if ((delta >= pdata->anc_hs_btn_hook_min_voltage) &&
        (delta <= pdata->anc_hs_btn_hook_max_voltage)) {
        return SND_JACK_BTN_0;
    } else if ((delta >= pdata->anc_hs_btn_volume_up_min_voltage) &&
        (delta <= pdata->anc_hs_btn_volume_up_max_voltage)) {
        return SND_JACK_BTN_1;
    } else if ((delta >= pdata->anc_hs_btn_volume_down_min_voltage) &&
        (delta <= pdata->anc_hs_btn_volume_down_max_voltage)) {
        return SND_JACK_BTN_2;
    } else {
        hwlog_err("[anc_hs]btn delta not in range delta:%d\n", delta);
        anc_dsm_report(ANC_HS_BTN_NOT_IN_RANGE, 0);
        return NO_BUTTON_PRESS;
    }
}

/**
 * anc_hs_adc_calibration - calibrate anc headset charge-circut
 *
 * make sure 5vboost is on and it is in float status before
 * call this function, if calibrate failed, set it as zero by default.
 **/
static void anc_hs_adc_calibration(void)
{
    int loop = ADC_CALIBRATION_TIMES;
    int count, fail_count = 0;
    pdata->adc_calibration_base = 0;

    while (loop) {
        int adc_h, adc_l;
        loop--;
        usleep_range(1000, 1100);
        adc_h = hisi_adc_get_value(pdata->channel_pwl_h);
        if (adc_h < 0) {
            hwlog_err("[anc_hs]get adc fail,adc_h:%d\n", adc_h);
            fail_count ++;
            continue;
        }
        adc_l = hisi_adc_get_value(pdata->channel_pwl_l);
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
        pdata->adc_calibration_base += (adc_h - adc_l);
    }

    count = ADC_CALIBRATION_TIMES - loop - fail_count;
    if (count == 0) {
        /* if all adc read fail, set 0 to it as default*/
        pdata->adc_calibration_base = 0;
        hwlog_err("[anc_hs] calibration whole failed\n");
    } else {
        pdata->adc_calibration_base /= count;
        hwlog_info("anc_hs:calibration_base = %d with %d times\n", pdata->adc_calibration_base, count);

        if (pdata->adc_calibration_base > 50 ||
            pdata->adc_calibration_base < -50) {
            pdata->adc_calibration_base = 0;
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
static void  anc_hs_charge_judge(void)
{
    struct anc_hs_dev *pdev = pdata->dev;
    struct anc_hs_codec_ops *fops = &pdev->ops;

    /* userspace prohibit charging with using hs-mic pin */
    if (ANC_HS_DISABLE_CHARGE == pdata->force_charge_ctl) {
        hwlog_info("%s(%u) : charge is occupied by app level\n", __FUNCTION__, __LINE__);
        /* need second detect for charge*/
        pdata->detect_again = true;
        return;
    }

    /* hs mic is using record, not take it */
    if (ANC_HS_DISABLE_CHARGE == pdata->hs_micbias_ctl) {
        /* need second detect for charge*/
        hwlog_info("%s(%u) :hs mic is in using!\n", __FUNCTION__, __LINE__);
        pdata->detect_again = true;
        return ;
    }

    pdata->detect_again = false;
    hwlog_debug("%s(%u) : anc hs charge !\n", __FUNCTION__, __LINE__);

    /* headset may have pluged out, just return */
    if (!fops->check_headset_in(pdata->private_data)) {
        hwlog_info("%s(%u) :headset has plug out!\n", __FUNCTION__, __LINE__);
        anc_hs_dump();
        return ;
    }

    mutex_lock(&pdata->charge_lock);
    /* connect 5vboost with hs_mic pin*/
    anc_hs_gpio_set_value(pdata->gpio_mic_sw, SWITCH_CHIP_5VBOOST);
    mutex_unlock(&pdata->charge_lock);

    /* waiting for anc chip start up*/
    hwlog_info("%s: delay %d ms to wait anc chip up!\n", __FUNCTION__, pdata->sleep_time);
    mdelay(pdata->sleep_time);

    mutex_lock(&pdata->charge_lock);

    if ((pdata->hs_micbias_ctl == ANC_HS_ENABLE_CHARGE) &&
         anc_hs_need_charge()) {
        /* start to charge for anc headset and respond charging btn event*/
        if (pdata->anc_hs_mode == ANC_HS_CHARGE_OFF) {

            hwlog_info("%s(%u) : anc_hs enable irq !\n", __FUNCTION__, __LINE__);
            anc_hs_enable_irq();
            pdata->anc_hs_mode = ANC_HS_CHARGE_ON;
        }
        if(ERROR_RET == anc_hs_send_hifi_msg(ANC_HS_CHARGE_ON))
        {
            hwlog_err("%s(%u) : anc_hs_send_hifi_msg TURN ON ANC_HS return ERROR !\n", __FUNCTION__, __LINE__);
        }
    } else {
        if (pdata->anc_hs_mode == ANC_HS_CHARGE_ON) {
            anc_hs_disable_irq();
            hwlog_info("%s(%u) : anc_hs disable irq !\n", __FUNCTION__, __LINE__);
        }
        /* stop charge and change status to CHARGE_OFF*/
        anc_hs_gpio_set_value(pdata->gpio_mic_sw, SWITCH_CHIP_HSBIAS);
        udelay(500);
        pdata->anc_hs_mode = ANC_HS_CHARGE_OFF;
        if(ERROR_RET == anc_hs_send_hifi_msg(ANC_HS_CHARGE_OFF))
        {
            hwlog_err("%s(%u) : anc_hs_send_hifi_msg TURN OFF ANC_HS return ERROR !\n", __FUNCTION__, __LINE__);
        }
    }

    anc_hs_dump();

    mutex_unlock(&pdata->charge_lock);

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
    struct anc_hs_dev *pdev = pdata->dev;
    struct anc_hs_codec_ops *fops = &pdev->ops;

    if (ANC_HS_DISABLE_CHARGE == pdata->hs_micbias_ctl ||
        ANC_HS_DISABLE_CHARGE == pdata->force_charge_ctl) {
        /* force stop charge function */
        mutex_lock(&pdata->charge_lock);

        if (pdata->anc_hs_mode == ANC_HS_CHARGE_ON) {
            anc_hs_disable_irq();
            anc_hs_gpio_set_value(pdata->gpio_mic_sw, SWITCH_CHIP_HSBIAS);
            udelay(500);

            hwlog_info("%s(%u) : stop charging for anc hs !\n", __FUNCTION__, __LINE__);
            pdata->anc_hs_mode = ANC_HS_CHARGE_OFF;
            pdata->mic_used = true;
        } else {
            /* here just make a dmd report */
            if (anc_hs_gpio_get_value(pdata->gpio_mic_sw) == SWITCH_CHIP_5VBOOST) {
                hwlog_err("%s(%u) : gpio status is not right !\n", __FUNCTION__, __LINE__);
                anc_dsm_report(ANC_HS_MIC_WITH_GPIO_ERR, 0);
            }
        }

        anc_hs_dump();
        mutex_unlock(&pdata->charge_lock);
    } else if (ANC_HS_ENABLE_CHARGE == pdata->hs_micbias_ctl &&
                 ANC_HS_ENABLE_CHARGE == pdata->force_charge_ctl) {
        if (pdata->mic_used) {
            pdata->mic_used = false;
            /* headset maybe have plug out here */
            if (!fops->check_headset_in(pdata->private_data)) {
                hwlog_info("%s(%u) :headset has plug out!\n", __FUNCTION__, __LINE__);
                anc_hs_dump();
            } else {
                /* force resume charge for anc headset */
                mutex_lock(&pdata->charge_lock);
                if(pdata->anc_hs_mode == ANC_HS_CHARGE_OFF){
                    pdata->anc_hs_mode = ANC_HS_CHARGE_ON;
                    anc_hs_gpio_set_value(pdata->gpio_mic_sw, SWITCH_CHIP_5VBOOST);
                    udelay(500);

                    anc_hs_enable_irq();
                    hwlog_info("%s(%u) : resume charging for anc hs!\n", __FUNCTION__, __LINE__);
                }
                mutex_unlock(&pdata->charge_lock);
            }
        } else if(pdata->detect_again) {
            /* need detect charge again due to interrupted before */
            anc_hs_charge_judge();
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
void anc_hs_start_charge(void)
{
    if ((pdata == NULL) || (pdata->registered == false)) {
        return;
    }

    pdata->hs_status = ANC_HS_HEADSET_PLUG_IN;
    anc_hs_disable_irq();

    /* enable 5vboost first, this need time to be stable */
    hwlog_info("%s(%u) :enable 5vboost\n", __FUNCTION__, __LINE__);

    /* default let hsbias connect to hs-mic pin*/
    anc_hs_gpio_set_value(pdata->gpio_mic_sw, SWITCH_CHIP_HSBIAS);
    anc_hs_gpio_set_value(pdata->anc_pwr_en_gpio, 1);
    enable_boost(true);
    pdata->anc_hs_mode = ANC_HS_CHARGE_OFF;

    anc_hs_dump();

    return;
}

/**
 * anc_hs_force_charge - when need hs-mic to record in charging status,
 *                       you must call this function to close charge
 *
 * @disable: charge control value, only enable and disable
 *
 **/
void anc_hs_force_charge(int disable)
{
    if ((pdata == NULL) || (pdata->registered == false)) {
        return;
    }
    /* don't make repeated switch with charge status*/
    if(disable == pdata->hs_micbias_ctl) {
        return;
    }
    pdata->hs_micbias_ctl = disable;

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
void anc_hs_charge_detect(int saradc_value, int headset_type)
{
    if ((pdata == NULL) || (pdata->registered == false)) {
        return ;
    }

    /* calibration adc resistance which can
	   make charge detect more accuracy*/
    anc_hs_adc_calibration();

    /* revert 4-pole headset still need 5vboost on
	   to support second recognition*/
    if (headset_type == ANC_HS_NORMAL_4POLE) {
        /* 4-pole headset maybe an anc headset*/
        hwlog_debug("%s : start anc hs charge judge\n", __FUNCTION__);
        anc_hs_charge_judge();
    } else if (headset_type == ANC_HS_NORMAL_3POLE) {
        hwlog_info("%s : no disable 5vboost for 3-pole headset\n", __FUNCTION__);
        /* 3-pole also support second-detect */
        //enable_boost(false);
    }

}

/**
 * anc_hs_5v_control - call this function to enable or disable 5v directly
 *
 **/
void anc_hs_5v_control(int enable)
{
    if ((pdata == NULL) || (pdata->registered == false)) {
        return;
    }

    if(enable) {
        anc_hs_gpio_set_value(pdata->anc_pwr_en_gpio, 1);
    }else {
        if(pdata->hs_status == ANC_HS_HEADSET_PLUG_OUT) {
            anc_hs_gpio_set_value(pdata->anc_pwr_en_gpio, 0);
        }
    }

    return;
}

/**
 * anc_hs_stop_charge - call this function when headset plug out
 *
 **/
void anc_hs_stop_charge(void)
{
    if ((pdata == NULL) || (pdata->registered == false)) {
        return;
    }

    hwlog_info("%s : stop anc hs charge\n", __FUNCTION__);

	/* keep irq always in mask status*/
    anc_hs_disable_irq();

    /* cancel the extra button delay work when headset plug out */
    cancel_delayed_work(&pdata->anc_hs_btn_delay_work);

    enable_boost(false);

    if(pdata->mic_sw_plugout_delay > 0) {
        queue_delayed_work(pdata->anc_mic_sw_delay_wq,
                       &pdata->anc_mic_sw_delay_work,
                       msecs_to_jiffies(pdata->mic_sw_plugout_delay));
    }
    else {
        anc_hs_gpio_set_value(pdata->gpio_mic_sw, SWITCH_CHIP_HSBIAS);
    }

    anc_hs_gpio_set_value(pdata->anc_pwr_en_gpio, 0);
    pdata->hs_status = ANC_HS_HEADSET_PLUG_OUT;
    pdata->anc_hs_mode = ANC_HS_CHARGE_OFF;
    if(ERROR_RET == anc_hs_send_hifi_msg(ANC_HS_CHARGE_OFF))
    {
        hwlog_err("%s(%u) : anc_hs_send_hifi_msg TURN OFF ANC_HS return ERROR !\n", __FUNCTION__, __LINE__);
    }

    return;
}

/**
 * anc_hs_dev_register - call this function to support anc headset,
 *                       this need hardware support
 *
 * @dev: anc_hs function and data description
 * @codec_data: codec description which is need by callback function
 *
 * only support one codec to be registered, and all the callback
 * functions must be realized.
 **/
int anc_hs_dev_register(struct anc_hs_dev *dev, void * codec_data)
{
    /* anc_hs driver not be probed, just return */
    if(pdata == NULL) {
        return -ENODEV;
    }

    /* only support one codec to be registered */
    if(pdata->registered) {
        hwlog_err("one codec has registered, no more permit\n");
        return -EEXIST;
    }
    if(!dev->ops.check_headset_in ||
        !dev->ops.btn_report ||
        !dev->ops.codec_resume_lock) {
        hwlog_err("codec ops funtion must be all registed\n");
        return -EINVAL;
    }

    pdata->dev = dev;
    pdata->private_data = codec_data;
    pdata->registered = true;

    hwlog_info("%s(%u) : anc hs has been register sucessful!\n", __FUNCTION__, __LINE__);

    return 0;
}

bool check_anc_hs_support(void)
{
    if((pdata == NULL) || (pdata->registered == false)) {
        return false;
    } else {
        return true;
    }
}

/**
 * anc_hs_btn_judge - delay work for anc headset irq
 *
 * @work: work struct
 *
 * should sync with codec power control, codec visit should
 * after codec_resume_lock(pdata->private_data, false).
 **/
static void anc_hs_btn_judge(struct work_struct* work)
{
    struct anc_hs_dev *pdev = pdata->dev;
    struct anc_hs_codec_ops *fops = &pdev->ops;
    int btn_report;

    if(!pdata->registered) {
        return;
    }

    if(pdata->anc_hs_mode == ANC_HS_CHARGE_OFF) {
        hwlog_info("%s(%u):ignore this irq\n", __FUNCTION__, __LINE__);
        if(pdata->button_pressed == 1) {
            btn_report = 0;
            pdata->button_pressed = 0;
            fops->btn_report(btn_report, ANC_BTN_MASK);
            hwlog_info("%s:irq level:%d", __FUNCTION__, anc_hs_gpio_get_value(pdata->mic_irq_gpio));
        }
        return;
    }

    hwlog_info("%s(%u):deal with button irq event!\n", __FUNCTION__, __LINE__);

    /* should get wake lock before codec power lock which may be blocked*/
    wake_lock(&pdata->wake_lock);

    /* enable irq first */
    anc_hs_enable_irq();
    mutex_lock(&pdata->btn_mutex);

    if (!anc_hs_gpio_get_value(pdata->mic_irq_gpio) && (pdata->button_pressed == 0)) {
        /*button down event*/
        hwlog_info("%s(%u) : button down event !\n", __FUNCTION__, __LINE__);
        mdelay(50);
        btn_report = anc_hs_get_btn_value();
        if(NO_BUTTON_PRESS != btn_report){
            pdata->button_pressed = 1;
            fops->btn_report(btn_report, ANC_BTN_MASK);
        }

    } else if (pdata->button_pressed == 1) {
        /*button up event*/
        hwlog_info("%s(%u) : button up event !\n", __FUNCTION__, __LINE__);

        btn_report = 0;
        pdata->button_pressed = 0;

        /* we permit button up event report to userspace,
           make sure down and up in pair*/
        fops->btn_report(btn_report, ANC_BTN_MASK);
    }

    mutex_unlock(&pdata->btn_mutex);
    wake_unlock(&pdata->wake_lock);

    return;
}


static void anc_mic_sw_func(struct work_struct* work)
{
    if(!pdata->registered) {
        return;
    }

    anc_hs_gpio_set_value(pdata->gpio_mic_sw, SWITCH_CHIP_HSBIAS);
    cancel_delayed_work(&pdata->anc_mic_sw_delay_work);

    return;
}

/**
 * anc_hs_btn_handler - respond button irq while charging
 *                      for anc headset
 * @irq: irq number
 * @data: irq data, not used now
 *
 * disable irq will be better until delay_work to be scheduled.
 **/
static irqreturn_t anc_hs_btn_handler(int irq, void* data)
{
    /* make sure delay_work to be scheduled*/
    wake_lock_timeout(&pdata->wake_lock, 50);

    anc_hs_disable_irq();

    /* deal with button judge at bottom*/
    queue_delayed_work(pdata->anc_hs_btn_delay_wq,
                       &pdata->anc_hs_btn_delay_work,
                       msecs_to_jiffies(20));

    return IRQ_HANDLED;
}

/**
 * anc_hs_ioctl - ioctl interface for userspeace
 *
 * @file: file description
 * @cmd: control commond
 * @arg: arguments
 *
 * userspeace can get charge status and force control
 * charge status.
 **/
static long anc_hs_ioctl(struct file* file, unsigned int cmd,
                         unsigned long arg)
{
    int ret = 0;
    int charge_mode;
    unsigned int __user* pUser = (unsigned int __user*) arg;

    if(pdata->registered == false) {
        return -EBUSY;
    }

    switch (cmd) {
        case IOCTL_ANC_HS_CHARGE_ENABLE_CMD:
            if(pdata->force_charge_ctl == ANC_HS_ENABLE_CHARGE) {
                break;
            }
            /* resume anc headset charge*/
            pdata->force_charge_ctl = ANC_HS_ENABLE_CHARGE;
            hwlog_info("app level contrl set charge status with %d\n", pdata->force_charge_ctl);
            update_charge_status();
            break;
        case IOCTL_ANC_HS_CHARGE_DISABLE_CMD:
            if(pdata->force_charge_ctl == ANC_HS_DISABLE_CHARGE) {
                break;
            }
            /* force stop anc headset charge*/
            pdata->force_charge_ctl = ANC_HS_DISABLE_CHARGE;
            hwlog_info("app level contrl set charge status with %d\n", pdata->force_charge_ctl);
            update_charge_status();
            break;
        case IOCTL_ANC_HS_GET_HEADSET_CMD:
            charge_mode = pdata->anc_hs_mode;
            if(charge_mode == ANC_HS_CHARGE_ON) {
                if(!anc_hs_need_charge()) {
                    charge_mode = ANC_HS_CHARGE_OFF;
                } else {
                    msleep(10);
                    if(!anc_hs_need_charge()) {
                        charge_mode = ANC_HS_CHARGE_OFF;
                    }
                }
            }
            if(charge_mode == ANC_HS_CHARGE_ON)
                ret = put_user((__u32)(ANC_HS_HEADSET), pUser);
            else {
                ret = put_user((__u32)(ANC_HS_NORMAL_4POLE), pUser);
            }
            break;
        case IOCTL_ANC_HS_GET_CHARGE_STATUS_CMD:
            ret = put_user((__u32)(pdata->anc_hs_mode), pUser);
            break;
        default:
            hwlog_err("unsupport cmd\n");
            ret = -EINVAL;
            break;
    }

    return (long)ret;
}

/*----------------------------------*/
/*sysfs definition for debug */
static ssize_t anc_hs_info_show(struct device* dev,
                                struct device_attribute* attr, char* buf)
{
    #define HS_INFO_SIZE 512

    memset(buf, 0, HS_INFO_SIZE);

    snprintf(buf, HS_INFO_SIZE, "%sanc_hs_limit_min: %d\n", buf, pdata->anc_hs_limit_min);
    snprintf(buf, HS_INFO_SIZE, "%sanc_hs_limit_max: %d\n", buf, pdata->anc_hs_limit_max);
    snprintf(buf, HS_INFO_SIZE, "%sanc_hs_mode: %d\n", buf, pdata->anc_hs_mode);
    snprintf(buf, HS_INFO_SIZE, "%sirq_flag: %d\n", buf, pdata->irq_flag);
    snprintf(buf, HS_INFO_SIZE, "%schannel_pwl_h: %d\n", buf, pdata->channel_pwl_h);
    snprintf(buf, HS_INFO_SIZE, "%schannel_pwl_l: %d\n", buf, pdata->channel_pwl_l);
    snprintf(buf, HS_INFO_SIZE, "%sgpio_mic_sw: %d\n", buf, anc_hs_gpio_get_value(pdata->gpio_mic_sw));
    snprintf(buf, HS_INFO_SIZE, "%smic_used: %d\n", buf, pdata->mic_used);
    snprintf(buf, HS_INFO_SIZE, "%sadc_calibration_base: %d\n", buf, pdata->adc_calibration_base);
    snprintf(buf, HS_INFO_SIZE, "%scalibration_current: %d\n", buf,
             (hisi_adc_get_value(pdata->channel_pwl_h) - hisi_adc_get_value(pdata->channel_pwl_l)));

    snprintf(buf, HS_INFO_SIZE, "%sadc_h: %d\n", buf, hisi_adc_get_value(pdata->channel_pwl_h));
    snprintf(buf, HS_INFO_SIZE, "%sadc_l: %d\n", buf, hisi_adc_get_value(pdata->channel_pwl_l));
    snprintf(buf, HS_INFO_SIZE, "%sanc_hs_btn_hook_min_voltage: %d\n", buf, pdata->anc_hs_btn_hook_min_voltage);
    snprintf(buf, HS_INFO_SIZE, "%sanc_hs_btn_hook_max_voltage: %d\n", buf, pdata->anc_hs_btn_hook_max_voltage);
    snprintf(buf, HS_INFO_SIZE, "%sanc_hs_btn_volume_up_min_voltage: %d\n", buf, pdata->anc_hs_btn_volume_up_min_voltage);
    snprintf(buf, HS_INFO_SIZE, "%sanc_hs_btn_volume_up_max_voltage: %d\n", buf, pdata->anc_hs_btn_volume_up_max_voltage);
    snprintf(buf, HS_INFO_SIZE, "%sanc_hs_btn_volume_down_min_voltage: %d\n", buf, pdata->anc_hs_btn_volume_down_min_voltage);
    snprintf(buf, HS_INFO_SIZE, "%sanc_hs_btn_volume_down_max_voltage: %d\n", buf, pdata->anc_hs_btn_volume_down_max_voltage);

    return HS_INFO_SIZE;
}

static ssize_t anc_detect_limit_show(struct device* dev,
                                     struct device_attribute* attr, char* buf)
{
    return snprintf(buf, 32, "%d\n", pdata->anc_hs_limit_min);
}

static ssize_t anc_detect_limit_store(struct device* dev,
                                      struct device_attribute* attr,
                                      const char* buf, size_t count)
{
    int ret;
    ret = kstrtoint(buf, 10, &(pdata->anc_hs_limit_min));
    if (ret) {
        hwlog_err("%s : convert to int type failed\n", __FUNCTION__);
        return ret;
    }

    return count;
}

static ssize_t anc_gpio_sw_show(struct device* dev,
                                struct device_attribute* attr, char* buf)
{
    return snprintf(buf, 32, "%d\n", anc_hs_gpio_get_value(pdata->gpio_mic_sw));
}

static ssize_t anc_gpio_sw_store(struct device* dev,
                                 struct device_attribute* attr,
                                 const char* buf, size_t count)
{
    int ret, value;

    ret = kstrtoint(buf, 10, &value);
    if (ret) {
        hwlog_err("%s : convert to int type failed\n", __FUNCTION__);
        return ret;
    }
    if (value) {
        anc_hs_gpio_set_value(pdata->gpio_mic_sw, 1);
    }
    else {
        anc_hs_gpio_set_value(pdata->gpio_mic_sw, 0);
    }

    return count;
}

static ssize_t anc_precharge_time_show(struct device* dev,
                                       struct device_attribute* attr, char* buf)
{
    return snprintf(buf, 32, "%d\n", pdata->sleep_time);
}

static ssize_t anc_precharge_time_store(struct device* dev,
                                        struct device_attribute* attr,
                                        const char* buf, size_t count)
{
    int ret, value;

    ret = kstrtoint(buf, 10, &value);
    if (ret) {
        hwlog_err("%s : convert to int type failed\n", __FUNCTION__);
        return ret;
    }
    pdata->sleep_time = value;
    return count;
}

static DEVICE_ATTR(hs_info, 0664, anc_hs_info_show,
                   NULL);
static DEVICE_ATTR(detect_limit, 0660, anc_detect_limit_show,
                   anc_detect_limit_store);
static DEVICE_ATTR(gpio_sw, 0660, anc_gpio_sw_show,
                   anc_gpio_sw_store);
static DEVICE_ATTR(precharge_time, 0660, anc_precharge_time_show,
                   anc_precharge_time_store);

static struct attribute* anc_hs_attributes[] =
{
    &dev_attr_hs_info.attr,
    &dev_attr_detect_limit.attr,
    &dev_attr_gpio_sw.attr,
    &dev_attr_precharge_time.attr,
    NULL
};

static const struct attribute_group anc_hs_attr_group =
{
    .attrs = anc_hs_attributes,
};

static const struct file_operations anc_hs_fops =
{
    .owner               = THIS_MODULE,
    .open                = simple_open,
    .unlocked_ioctl      = anc_hs_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl        = anc_hs_ioctl,
#endif
};

static struct miscdevice anc_hs_device =
{
    .minor  = MISC_DYNAMIC_MINOR,
    .name   = "anc_hs",
    .fops   = &anc_hs_fops,
};

static const struct of_device_id anc_hs_of_match[] =
{
    {
        .compatible = "huawei,anc_hs",
    },
    { },
};
MODULE_DEVICE_TABLE(of, anc_hs_of_match);

/* load dts config for board difference */
static void load_anc_hs_config(struct device_node* node)
{
    int temp;

    /* read adc channel number */
    if (!of_property_read_u32(node, "adc_channel_h", &temp)) {
        pdata->channel_pwl_h = temp;
    } else {
        pdata->channel_pwl_h = 15;
    }
    if (!of_property_read_u32(node, "adc_channel_l", &temp)) {
        pdata->channel_pwl_l = temp;
    } else {
        pdata->channel_pwl_l = 14;
    }
    /* read charge limit */
    if (!of_property_read_u32(node, "anc_hs_limit_min", &temp)) {
        pdata->anc_hs_limit_min = temp;
    } else {
        pdata->anc_hs_limit_min = ANC_HS_LIMIT_MIN;
    }
    if (!of_property_read_u32(node, "anc_hs_limit_max", &temp)) {
        pdata->anc_hs_limit_max = temp;
    } else {
        pdata->anc_hs_limit_max = ANC_HS_LIMIT_MAX;
    }
    if (!of_property_read_u32(node, "gpio_type", &temp)) {
        pdata->gpio_type = temp;
    } else {
        pdata->gpio_type = ANC_HS_GPIO_SOC;
    }
    /* read hook limit */
    if (!of_property_read_u32(node, "anc_hs_btn_hook_min_voltage", &temp)) {
        pdata->anc_hs_btn_hook_min_voltage = temp;
    } else {
        pdata->anc_hs_btn_hook_min_voltage = ANC_HS_HOOK_MIN;
    }
    if (!of_property_read_u32(node, "anc_hs_btn_hook_max_voltage", &temp)) {
        pdata->anc_hs_btn_hook_max_voltage = temp;
    } else {
        pdata->anc_hs_btn_hook_max_voltage = ANC_HS_HOOK_MAX;
    }
    /* read volume up limit */
    if (!of_property_read_u32(node, "anc_hs_btn_volume_up_min_voltage", &temp)) {
        pdata->anc_hs_btn_volume_up_min_voltage = temp;
    } else {
        pdata->anc_hs_btn_volume_up_min_voltage = ANC_HS_VOLUME_UP_MIN;
    }
    if (!of_property_read_u32(node, "anc_hs_btn_volume_up_max_voltage", &temp)) {
        pdata->anc_hs_btn_volume_up_max_voltage = temp;
    } else {
        pdata->anc_hs_btn_volume_up_max_voltage = ANC_HS_VOLUME_UP_MAX;
    }
    /* read volume down limit */
    if (!of_property_read_u32(node, "anc_hs_btn_volume_down_min_voltage", &temp)) {
        pdata->anc_hs_btn_volume_down_min_voltage = temp;
    } else {
        pdata->anc_hs_btn_volume_down_min_voltage = ANC_HS_VOLUME_DOWN_MIN;
    }
    if (!of_property_read_u32(node, "anc_hs_btn_volume_down_max_voltage", &temp)) {
        pdata->anc_hs_btn_volume_down_max_voltage = temp;
    } else {
        pdata->anc_hs_btn_volume_down_max_voltage = ANC_HS_VOLUME_DOWN_MAX;
    }
}

struct anc_hs_ops anc_hs_ops = {
    .anc_hs_dev_register = anc_hs_dev_register,
    .anc_hs_check_headset_pluged_in = NULL,
    .anc_hs_start_charge = anc_hs_start_charge,
    .anc_hs_charge_detect = anc_hs_charge_detect,
    .anc_hs_stop_charge = anc_hs_stop_charge,
    .anc_hs_force_charge = anc_hs_force_charge,
    .check_anc_hs_support = check_anc_hs_support,
    .anc_hs_5v_control = anc_hs_5v_control,
    .anc_hs_invert_hs_control = NULL,
    .anc_hs_refresh_headset_type = NULL,
};

static int anc_hs_probe(struct platform_device* pdev)
{
    struct device* dev = &pdev->dev;
    struct device_node* node =  dev->of_node;
    int ret = 0;

    pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
    if (NULL == pdata) {
        hwlog_err("cannot allocate anc hs dev data\n");
        return -ENOMEM;
    }

    mutex_init(&pdata->charge_lock);
    mutex_init(&pdata->btn_mutex);
    wake_lock_init(&pdata->wake_lock, WAKE_LOCK_SUSPEND, "anc_hs");

    /* init all values */
    pdata->anc_hs_mode = ANC_HS_CHARGE_OFF;
    pdata->irq_flag = true;
    pdata->mic_used = false;
    pdata->sleep_time = ANC_CHIP_STARTUP_TIME;
    pdata->adc_calibration_base = 0;
    pdata->hs_micbias_ctl = ANC_HS_ENABLE_CHARGE;
    pdata->force_charge_ctl = ANC_HS_ENABLE_CHARGE;
    pdata->boost_flag = false;
    pdata->registered = false;
    pdata->hs_status = ANC_HS_HEADSET_PLUG_OUT;

#if 0
    /* get boost5v resource */
    pdata->regu_boost5v.supply = "anc_hs_charge";
    ret = devm_regulator_bulk_get(dev, 1, &(pdata->regu_boost5v));
    if (0 != ret) {
        hwlog_err("couldn't get regulators(boost5v) %d\n", ret);
        return -ENODEV;
    }
#endif

    /* get switch chip control gpio */
    pdata->gpio_mic_sw =  of_get_named_gpio(node, "gpios", 0);
    if (pdata->gpio_mic_sw < 0) {
        hwlog_err("gpio_mic_sw is unvalid!\n");
        return -ENOENT;
    }

    if (!gpio_is_valid(pdata->gpio_mic_sw)) {
        hwlog_err("gpio is unvalid!\n");
        return -ENOENT;
    }

    /* get charge button irq gpio */
    pdata->mic_irq_gpio = of_get_named_gpio(node, "gpios", 1);
    if (pdata->mic_irq_gpio < 0) {
        hwlog_err("mic_irq_gpio is unvalid!\n");
        return -ENOENT;
    }

    if (!gpio_is_valid(pdata->mic_irq_gpio)) {
        hwlog_err("gpio is unvalid!\n");
        return -EINVAL;
    }

    /* get charge button irq gpio */
    pdata->anc_pwr_en_gpio = of_get_named_gpio(node, "gpios", 2);
    if (pdata->anc_pwr_en_gpio >= 0) {
        if (!gpio_is_valid(pdata->anc_pwr_en_gpio)) {
            hwlog_err("gpio is unvalid!\n");
            return -EINVAL;
        }

        ret = gpio_request(pdata->anc_pwr_en_gpio, "gpio_anc_pwr_en");
        if (ret) {
            hwlog_err("error request GPIO for gpio_anc_pwr_en fail %d\n", ret);
            return -ENODEV;
        }

        gpio_direction_output(pdata->anc_pwr_en_gpio, 0);
    }

    if(!of_property_read_u32(node, "mic_sw_plugout_delay", &pdata->mic_sw_plugout_delay)) {
        pdata->anc_mic_sw_delay_wq = create_singlethread_workqueue("anc_mic_sw_delay_wq");
        if (!(pdata->anc_mic_sw_delay_wq)) {
            hwlog_err("%s : anc_mic_sw_delay_wq create failed\n", __FUNCTION__);
            ret = -ENOMEM;
            goto anc_mic_sw_wq_err;
        }
        INIT_DELAYED_WORK(&pdata->anc_mic_sw_delay_work,anc_mic_sw_func);
    }
    else {
        pdata->mic_sw_plugout_delay = 0;
        pdata->anc_mic_sw_delay_wq = NULL;
    }

    /* applay for irq gpio */
    ret = gpio_request(pdata->mic_irq_gpio, "gpio_mic_irq");
    if (ret) {
        hwlog_err("error request GPIO for mic_irq_gpio fail %d\n", ret);
        goto gpio_mic_irq_err;
    }
    /* set irq gpio to input status */
    gpio_direction_input(pdata->mic_irq_gpio);

    pdata->mic_irq = gpio_to_irq(pdata->mic_irq_gpio);

    /* applay for switch chip gpio */
    ret = gpio_request(pdata->gpio_mic_sw, "gpio_mic_sw");
    if (ret) {
        hwlog_err("error request GPIO for mic_sw fail %d\n", ret);
        goto gpio_mic_sw_err;
    }
    gpio_direction_output(pdata->gpio_mic_sw, SWITCH_CHIP_HSBIAS);

    /* load dts config for board difference */
    load_anc_hs_config(node);

    /* create btn irq workqueue */
    pdata->anc_hs_btn_delay_wq =
        create_singlethread_workqueue("anc_hs_btn_delay_wq");
    if (!(pdata->anc_hs_btn_delay_wq)) {
        hwlog_err("%s : anc_hs_btn_delay_wq create failed\n", __FUNCTION__);
        ret = -ENOMEM;
        goto anc_hs_btn_wq_err;
    }
    INIT_DELAYED_WORK(&pdata->anc_hs_btn_delay_work, anc_hs_btn_judge);

    /*anc hs irq request */
    ret = request_threaded_irq(pdata->mic_irq, NULL,
                      anc_hs_btn_handler,
                      IRQF_ONESHOT | IRQF_TRIGGER_RISING |
                      IRQF_TRIGGER_FALLING | IRQF_NO_SUSPEND, "anc_hs_btn", NULL);
    if (0 > ret)
        goto anc_hs_btn_err;
    /* disable btn irq by default */
    anc_hs_disable_irq();

    /* register misc device for userspace */
    ret = misc_register(&anc_hs_device);
    if (ret) {
        hwlog_err("%s: anc hs misc device register failed", __FUNCTION__);
        goto anc_hs_irq_err;
    }

    /* create sysfs for debug function */
    if ((ret = sysfs_create_group(&dev->kobj, &anc_hs_attr_group)) < 0) {
        hwlog_err("failed to register sysfs\n");
    }

    /* register dsm client*/
    if (!anc_hs_dclient) {
        anc_hs_dclient = dsm_register_client(&dsm_anc_hs);
    }

    ret = anc_hs_ops_register(&anc_hs_ops);
    if(ret) {
        pr_err("register anc_hs_interface ops failed!\n");
        goto anc_hs_irq_err;
    }

    return 0;

anc_hs_irq_err:
    free_irq(pdata->mic_irq, NULL);
anc_hs_btn_err:
    if (pdata->anc_hs_btn_delay_wq) {
        cancel_delayed_work(&pdata->anc_hs_btn_delay_work);
        flush_workqueue(pdata->anc_hs_btn_delay_wq);
        destroy_workqueue(pdata->anc_hs_btn_delay_wq);
    }
anc_hs_btn_wq_err:
    gpio_free(pdata->gpio_mic_sw);
gpio_mic_sw_err:
    gpio_free(pdata->mic_irq_gpio);
gpio_mic_irq_err:
    if (pdata->anc_mic_sw_delay_wq) {
        cancel_delayed_work(&pdata->anc_mic_sw_delay_work);
        flush_workqueue(pdata->anc_mic_sw_delay_wq);
        destroy_workqueue(pdata->anc_mic_sw_delay_wq);
    }
anc_mic_sw_wq_err:
gpio_free(pdata->anc_pwr_en_gpio);

    return ret;

}

static int anc_hs_remove(struct platform_device* pdev)
{
    if (pdata == NULL) {
        return 0;
    }

    free_irq(pdata->mic_irq, NULL);

    if (pdata->anc_hs_btn_delay_wq) {
        cancel_delayed_work(&pdata->anc_hs_btn_delay_work);
        flush_workqueue(pdata->anc_hs_btn_delay_wq);
        destroy_workqueue(pdata->anc_hs_btn_delay_wq);
    }

    if(pdata->anc_pwr_en_gpio >= 0) {
        gpio_direction_output(pdata->anc_pwr_en_gpio, 0);
        gpio_free(pdata->anc_pwr_en_gpio);
    }
    gpio_free(pdata->gpio_mic_sw);
    gpio_free(pdata->mic_irq_gpio);

    return 0;
}

static struct platform_driver anc_hs_driver =
{
    .driver = {
        .name   = "anc_hs",
        .owner  = THIS_MODULE,
        .of_match_table = anc_hs_of_match,
    },
    .probe  = anc_hs_probe,
    .remove = anc_hs_remove,
};

static int __init anc_hs_init(void)
{
    return platform_driver_register(&anc_hs_driver);
}

static void __exit anc_hs_exit(void)
{
    platform_driver_unregister(&anc_hs_driver);
}

device_initcall(anc_hs_init);
module_exit(anc_hs_exit);

MODULE_DESCRIPTION("anc headset driver");
MODULE_LICENSE("GPL");

#ifdef CONFIG_LLT_TEST
struct anc_hs_static_ops anc_hs_ops = {
    .anc_hs_gpio_get_value = anc_hs_gpio_get_value,
    .anc_hs_gpio_set_value = anc_hs_gpio_set_value,
    .anc_hs_dump = anc_hs_dump,
    .anc_dsm_report = anc_dsm_report,
    .anc_hs_enable_irq = anc_hs_enable_irq,
    .anc_hs_disable_irq = anc_hs_disable_irq,
    .enable_boost = enable_boost,
    .anc_hs_get_adc_delta = anc_hs_get_adc_delta,
    .anc_hs_need_charge = anc_hs_need_charge,
    .anc_hs_get_btn_value = anc_hs_get_btn_value,
    .anc_hs_adc_calibration = anc_hs_adc_calibration,
    .check_anc_hs_support = check_anc_hs_support,
    .anc_hs_ioctl = anc_hs_ioctl,
    .anc_detect_limit_store = anc_detect_limit_store,
    .anc_gpio_sw_store = anc_gpio_sw_store,
    .anc_precharge_time_store = anc_precharge_time_store,
    .load_anc_hs_config = load_anc_hs_config,
    .anc_hs_probe = anc_hs_probe,
    .anc_hs_remove = anc_hs_remove,
    .pdata = &pdata,
};
#endif
