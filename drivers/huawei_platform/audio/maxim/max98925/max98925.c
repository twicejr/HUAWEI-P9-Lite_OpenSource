/*
* max98925-mono.c -- ALSA SoC Mono MAX98925 driver
*
* Copyright 2013-2014 Maxim Integrated Products
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/irqreturn.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <dsm/dsm_pub.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/list.h>

#include "huawei_platform/audio/maxim.h"
#include "huawei_platform/audio/max98925.h"

#define SUPPORT_DEVICE_TREE
#ifdef SUPPORT_DEVICE_TREE
#include <linux/regulator/consumer.h>
#endif

#define HWLOG_TAG max98925
HWLOG_REGIST();

#define SPK_REC_DUAL_SMARTPA    2
static int maxim_num = 0;

struct maxim_gain_def type_gain_def[] = {
    {0x14, 0x14},//spk gain value
    {0x34, 0x36},//rcv gain value
};



static struct reg_default max98925_reg[] = {
    { 0x00, 0x00 }, /* Battery Voltage Data */
    { 0x01, 0x00 }, /* Boost Voltage Data */
    { 0x02, 0x00 }, /* Live Status0 */
    { 0x03, 0x00 }, /* Live Status1 */
    { 0x04, 0x00 }, /* Live Status2 */
    { 0x05, 0x00 }, /* State0 */
    { 0x06, 0x00 }, /* State1 */
    { 0x07, 0x00 }, /* State2 */
    { 0x08, 0x00 }, /* Flag0 */
    { 0x09, 0x00 }, /* Flag1 */
    { 0x0A, 0x00 }, /* Flag2 */
    { 0x0B, 0x00 }, /* IRQ Enable0 */
    { 0x0C, 0x00 }, /* IRQ Enable1 */
    { 0x0D, 0x00 }, /* IRQ Enable2 */
    { 0x0E, 0x00 }, /* IRQ Clear0 */
    { 0x0F, 0x00 }, /* IRQ Clear1 */
    { 0x10, 0x00 }, /* IRQ Clear2 */
    { 0x11, 0xC0 }, /* Map0 */
    { 0x12, 0x00 }, /* Map1 */
    { 0x13, 0x00 }, /* Map2 */
    { 0x14, 0xF0 }, /* Map3 */
    { 0x15, 0x00 }, /* Map4 */
    { 0x16, 0xAB }, /* Map5 */
    { 0x17, 0x89 }, /* Map6 */
    { 0x18, 0x00 }, /* Map7 */
    { 0x19, 0x00 }, /* Map8 */
    { 0x1A, 0x06 }, /* DAI Clock Mode 1 */
    { 0x1B, 0xC0 }, /* DAI Clock Mode 2 */
    { 0x1C, 0x00 }, /* DAI Clock Divider Denominator MSBs */
    { 0x1D, 0x00 }, /* DAI Clock Divider Denominator LSBs */
    { 0x1E, 0xF0 }, /* DAI Clock Divider Numerator MSBs */
    { 0x1F, 0x00 }, /* DAI Clock Divider Numerator LSBs */
    { 0x20, 0x50 }, /* Format */
    { 0x21, 0x00 }, /* TDM Slot Select */
    { 0x22, 0x00 }, /* DOUT Configuration VMON */
    { 0x23, 0x00 }, /* DOUT Configuration IMON */
    { 0x24, 0x00 }, /* DOUT Configuration VBAT */
    { 0x25, 0x00 }, /* DOUT Configuration VBST */
    { 0x26, 0x00 }, /* DOUT Configuration FLAG */
    { 0x27, 0xFF }, /* DOUT HiZ Configuration 1 */
    { 0x28, 0xFF }, /* DOUT HiZ Configuration 2 */
    { 0x29, 0xFF }, /* DOUT HiZ Configuration 3 */
    { 0x2A, 0xFF }, /* DOUT HiZ Configuration 4 */
    { 0x2B, 0x02 }, /* DOUT Drive Strength */
    { 0x2C, 0x90 }, /* Filters */
    { 0x2D, 0x00 }, /* Gain */
    { 0x2E, 0x03 }, /* Gain Ramping */
    { 0x2F, 0x00 }, /* Speaker Amplifier */
    { 0x30, 0x0A }, /* Threshold */
    { 0x31, 0x00 }, /* ALC Attack */
    { 0x32, 0x80 }, /* ALC Atten and Release */
    { 0x33, 0x00 }, /* ALC Infinite Hold Release */
    { 0x34, 0x92 }, /* ALC Configuration */
    { 0x35, 0x01 }, /* Boost Converter */
    { 0x36, 0x00 }, /* Block Enable */
    { 0x37, 0x00 }, /* Configuration */
    { 0x38, 0x00 }, /* Global Enable */
    { 0x3A, 0x00 }, /* Boost Limiter */
    { 0xFF, 0x50 }, /* Revision ID */
};

static bool max98925_volatile_register(struct device *dev, unsigned int reg)
{
    switch (reg) {
        case MAX98925_R000_VBAT_DATA:
        case MAX98925_R001_VBST_DATA:
        case MAX98925_R002_LIVE_STATUS0:
        case MAX98925_R003_LIVE_STATUS1:
        case MAX98925_R004_LIVE_STATUS2:
        case MAX98925_R005_STATE0:
        case MAX98925_R006_STATE1:
        case MAX98925_R007_STATE2:
        case MAX98925_R008_FLAG0:
        case MAX98925_R009_FLAG1:
        case MAX98925_R00A_FLAG2:
        case MAX98925_R0FF_VERSION:
            return true;
        default:
            return false;
    }
}

static bool max98925_readable_register(struct device *dev, unsigned int reg)
{
    switch (reg) {
        case MAX98925_R00E_IRQ_CLEAR0:
        case MAX98925_R00F_IRQ_CLEAR1:
        case MAX98925_R010_IRQ_CLEAR2:
        case MAX98925_R033_ALC_HOLD_RLS:
            return false;
        default:
            return true;
    }
}

#if 0
static int max98925_regulator_config(struct i2c_client *i2c, bool pullup, bool on)
{
    struct regulator *max98925_vcc_i2c;
    int rc;
#define VCC_I2C_MIN_UV    1800000
#define VCC_I2C_MAX_UV    1800000
#define I2C_LOAD_UA        300000

    hwlog_info("%s: enter\n", __func__);

    if (pullup) {
        hwlog_info("%s: I2C PULL UP.\n", __func__);

        max98925_vcc_i2c = regulator_get(&i2c->dev, "vcc_i2c");
        if (IS_ERR(max98925_vcc_i2c)) {
            rc = PTR_ERR(max98925_vcc_i2c);
            hwlog_info("%s: regulator get failed rc=%d\n", __func__, rc);
            goto error_get_vtg_i2c;
        }
        if (regulator_count_voltages(max98925_vcc_i2c) > 0) {
            rc = regulator_set_voltage(max98925_vcc_i2c,
            VCC_I2C_MIN_UV, VCC_I2C_MAX_UV);
            if (rc) {
                hwlog_info("%s: regulator set_vtg failed rc=%d\n", __func__, rc);
                goto error_set_vtg_i2c;
            }
        }

        rc = reg_set_optimum_mode_check(max98925_vcc_i2c, I2C_LOAD_UA);
        if (rc < 0) {
            hwlog_info("%s: regulator vcc_i2c set_opt failed rc=%d\n", __func__, rc);
            goto error_reg_opt_i2c;
        }

        rc = regulator_enable(max98925_vcc_i2c);
        if (rc) {
            hwlog_info("%s: regulator vcc_i2c enable failed rc=%d\n", __func__, rc);
            goto error_reg_en_vcc_i2c;
        }

    }

    return 0;

error_set_vtg_i2c:
    regulator_put(max98925_vcc_i2c);
    error_get_vtg_i2c:
    if (regulator_count_voltages(max98925_vcc_i2c) > 0)
        regulator_set_voltage(max98925_vcc_i2c, 0, VCC_I2C_MAX_UV);
error_reg_en_vcc_i2c:
    if(pullup)
        reg_set_optimum_mode_check(max98925_vcc_i2c, 0);
error_reg_opt_i2c:
    regulator_disable(max98925_vcc_i2c);

    return rc;
}
#endif

static ssize_t max98925_register_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    int value, i;
    char valStr[20];
    struct maxim_priv *p = NULL;

    p = find_maxim_by_dev(dev);
        if(NULL == p){
        return 0;
    }

    buf[0] = '\0';
    for (i = 0; i <= 0x38; i++){
        regmap_read(p->regmap, i, &value);
        sprintf(valStr, "0x%02x = 0x%02x\n", i, value);

        strcat(buf, valStr);
    }

    return strlen(buf);
}

static DEVICE_ATTR(register_list, S_IRUGO | S_IWUSR, max98925_register_show, NULL);

static ssize_t max98925_register_write(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    int reg = 0;
    int val = 0;
    char *pEnd = buf;
    struct maxim_priv *p = NULL;

    p = find_maxim_by_dev(dev);
        if(NULL == p){
        return 0;
    }

    reg = simple_strtol(buf, &pEnd, 16);
    pEnd++;
    hwlog_info("max98925_register_write reg : 0x%x\n", reg);
    val = simple_strtol(pEnd, &pEnd, 16);
    hwlog_info("max98925_register_write val : 0x%x\n", val);

    if((reg < 0x00 || reg > 0x38) && reg != 0x3a && reg != 0xff) {
        hwlog_err("invalid register address: 0x%x\n", reg);
        return -ENXIO;
    }
    regmap_write(p->regmap, reg, val);

    return count;
}

static DEVICE_ATTR(register_write, 0660, NULL, max98925_register_write);


static ssize_t max98925_num_show(struct device* dev, struct device_attribute* attr, char* buf)
{
    struct maxim_priv *p = NULL;

    p = find_maxim_by_dev(dev);
        if(NULL == p){
        return 0;
    }

    return snprintf(buf, 32, "%d-%d\n", maxim_num, p->type);
}

static DEVICE_ATTR(maxim_num, S_IRUGO | S_IWUSR, max98925_num_show, NULL);


static struct attribute* max98925_attributes[] =
{
    &dev_attr_register_list.attr,
    &dev_attr_register_write.attr,
    &dev_attr_maxim_num.attr,
    NULL
};

static const struct attribute_group max98925_attr_group =
{
    .attrs = max98925_attributes,
};


/* codec sample rate and n/m dividers parameter table */
static const struct {
    u32 rate;
    u8  sr;
    u32 divisors[3][2];
} rate_table[] = {
    { 8000, 0, {{  1,   375}, {5, 1764}, {  1,   384}}},
    {11025,    1, {{147, 40000}, {1,  256}, {147, 40960}}},
    {12000, 2, {{  1,   250}, {5, 1176}, {  1,   256}}},
    {16000, 3, {{  2,   375}, {5,  882}, {  1,   192}}},
    {22050, 4, {{147, 20000}, {1,  128}, {147, 20480}}},
    {24000, 5, {{  1,   125}, {5,  588}, {  1,   128}}},
    {32000, 6, {{  4,   375}, {5,  441}, {  1,    96}}},
    {44100, 7, {{147, 10000}, {1,   64}, {147, 10240}}},
    {48000, 8, {{  2,   125}, {5,  294}, {  1,    64}}},
};

static inline int max98925_rate_value(int rate, int clock, u8 *value, int *n, int *m)
{
    int ret = -EINVAL;
    int i;
    for (i = 0; i < ARRAY_SIZE(rate_table); i++) {
        if (rate_table[i].rate >= rate) {
            *value = rate_table[i].sr;
            *n = rate_table[i].divisors[clock][0];
            *m = rate_table[i].divisors[clock][1];
            ret = 0;
            break;
        }
    }

    hwlog_info("%s: sample rate is %d, returning %d\n", __func__, rate_table[i].rate, *value);

    return ret;
}

static int max98925_set_slave(struct list_head *maxim)
{
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;

    hwlog_info("%s: ENTER\n", __func__);


    list_for_each(pos, maxim){
        p = list_entry(pos, struct maxim_priv, list);

        /*
        * 1. use BCLK instead of MCLK
        */
        regmap_update_bits(p->regmap, MAX98925_R01A_DAI_CLK_MODE1,
                    M98925_DAI_CLK_SOURCE_MASK, M98925_DAI_CLK_SOURCE_MASK);

        /*
        * 2. set DAI to slave mode
        */
        regmap_update_bits(p->regmap, MAX98925_R01B_DAI_CLK_MODE2,
                    M98925_DAI_MAS_MASK, 0);

        /*
        * 3. set BLCKs to LRCLKs to 64
        */
        regmap_update_bits(p->regmap, MAX98925_R01B_DAI_CLK_MODE2,
                    M98925_DAI_BSEL_MASK, M98925_DAI_BSEL_64);

        /*
        * 4. set VMON slots  &  5. set IMON slots
        */
        regmap_update_bits(p->regmap, MAX98925_R022_DOUT_CFG_VMON,
                    M98925_DAI_VMON_EN_MASK, M98925_DAI_VMON_EN_MASK);
        regmap_update_bits(p->regmap, MAX98925_R023_DOUT_CFG_IMON,
                    M98925_DAI_IMON_EN_MASK, M98925_DAI_IMON_EN_MASK);
        if(1 == maxim_num){
            regmap_update_bits(p->regmap, MAX98925_R022_DOUT_CFG_VMON,
                        M98925_DAI_VMON_SLOT_MASK, M98925_DAI_VMON_SLOT_00_01);
            regmap_update_bits(p->regmap, MAX98925_R023_DOUT_CFG_IMON,
                        M98925_DAI_IMON_SLOT_MASK, M98925_DAI_IMON_SLOT_04_05);
        }else{
            switch(p->type){
                case MAXIM_L:
                    regmap_update_bits(p->regmap, MAX98925_R022_DOUT_CFG_VMON,
                                M98925_DAI_VMON_SLOT_MASK, M98925_DAI_VMON_SLOT_02_03);
                    regmap_update_bits(p->regmap, MAX98925_R023_DOUT_CFG_IMON,
                                M98925_DAI_IMON_SLOT_MASK, M98925_DAI_IMON_SLOT_00_01);
                    break;
                case MAXIM_R:
                    regmap_update_bits(p->regmap, MAX98925_R022_DOUT_CFG_VMON,
                                M98925_DAI_VMON_SLOT_MASK, M98925_DAI_VMON_SLOT_06_07);
                    regmap_update_bits(p->regmap, MAX98925_R023_DOUT_CFG_IMON,
                                M98925_DAI_IMON_SLOT_MASK, M98925_DAI_IMON_SLOT_04_05);    
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}

static void max98925_set_master(struct list_head *maxim)
{
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;


    hwlog_info("%s: ENTER\n", __func__);


    list_for_each(pos, maxim){
        p = list_entry(pos, struct maxim_priv, list);

        /*
        * 1. use MCLK for Left channel, right channel always BCLK
        */
        regmap_update_bits(p->regmap, MAX98925_R01A_DAI_CLK_MODE1,
                    M98925_DAI_CLK_SOURCE_MASK, 0);

        /*
        * 2. set left channel DAI to master mode, right channel always slave
        */
        regmap_update_bits(p->regmap, MAX98925_R01B_DAI_CLK_MODE2,
                    M98925_DAI_MAS_MASK, M98925_DAI_MAS_MASK);
    }
}

static int max98925_set_clock(struct list_head *maxim, unsigned int rate)
{
    unsigned int clock;
    unsigned int mdll;
    unsigned int n;
    unsigned int m;
    unsigned int sysclk;
    u8 dai_sr;
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;

    p = list_entry(maxim->next, struct maxim_priv, list);
    sysclk = p->sysclk;


    switch (sysclk) {
        case 6000000:
            clock = 0;
            mdll  = M98925_MDLL_MULT_MCLKx16;
            break;
        case 11289600:
            clock = 1;
            mdll  = M98925_MDLL_MULT_MCLKx8;
            break;
        case 12000000:
            clock = 0;
            mdll  = M98925_MDLL_MULT_MCLKx8;
            break;
        case 12288000:
            clock = 2;
            mdll  = M98925_MDLL_MULT_MCLKx8;
            break;
        default:
            hwlog_err("%s: unsupported sysclk %u\n", __func__, sysclk);
            return -EINVAL;
    }

    if (max98925_rate_value(rate, clock, &dai_sr, &n, &m))
        return -EINVAL;


    list_for_each(pos, maxim){
        p = list_entry(pos, struct maxim_priv, list);

        /*
        * 1. set DAI_SR to correct LRCLK frequency
        */
        regmap_update_bits(p->regmap, MAX98925_R01B_DAI_CLK_MODE2,
                    M98925_DAI_SR_MASK, dai_sr << M98925_DAI_SR_SHIFT);

        /*
        * 2. set DAI m divider
        */
        regmap_write(p->regmap, MAX98925_R01C_DAI_CLK_DIV_M_MSBS, m >> 8);
        regmap_write(p->regmap, MAX98925_R01D_DAI_CLK_DIV_M_LSBS, m & 0xFF);

        /*
        * 3. set DAI n divider
        */
        regmap_write(p->regmap, MAX98925_R01E_DAI_CLK_DIV_N_MSBS, n >> 8);
        regmap_write(p->regmap, MAX98925_R01F_DAI_CLK_DIV_N_LSBS, n & 0xFF);

        /*
        * 4. set MDLL
        */
        regmap_update_bits(p->regmap, MAX98925_R01A_DAI_CLK_MODE1,
                    M98925_MDLL_MULT_MASK, mdll << M98925_MDLL_MULT_SHIFT);
    }

    return 0;
}


static int max98925_get_version(struct list_head *maxim, unsigned int type, unsigned int *value)
{
    struct maxim_priv *p = NULL;

    p = find_maxim_by_type(maxim, type);
    if(NULL == p){
        hwlog_err("%s: it has no type[%d] in max98925 device\n", __func__, type);
        return -ENODEV;
    }

    return regmap_read(p->regmap, MAX98925_R0FF_VERSION, value);
}


static int max98925_get_reg_val(struct list_head *maxim, unsigned int type, struct maxim_reg_ops *reg_val, unsigned int __user *pUser)
{
    int ret = 0;
    struct maxim_priv *p = NULL;

    p = find_maxim_by_type(maxim, type);
    if(NULL == p){
        hwlog_err("%s: it has no type[%d] in max98925 device\n", __func__, type);
        return -ENODEV;
    }


    if(copy_from_user(reg_val,(void*)pUser, sizeof(struct maxim_reg_ops))){
        hwlog_err("%s: set reg copy_from_user fail", __func__);
        return -1;
    }
    ret = regmap_read(p->regmap, reg_val->reg_addr, &reg_val->reg_val);
    if(copy_to_user((void*)pUser, reg_val, sizeof(struct maxim_reg_ops))){
        hwlog_err("%s: send reg value to user fail", __func__);
        return -1;
    }

    return ret;
}


static int max98925_set_reg_val(struct list_head *maxim, struct maxim_reg_ops *reg_val, unsigned int __user *pUser)
{
    int ret = 0;
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;


    if(copy_from_user(reg_val,(void*)pUser, sizeof(struct maxim_reg_ops))) {
        hwlog_err("%s: set reg copy_from_user fail\n", __func__);
        return -1;
    }

    list_for_each(pos, maxim){
        p = list_entry(pos, struct maxim_priv, list);
        ret |= regmap_write(p->regmap, reg_val->reg_addr, reg_val->reg_val);
    }


    hwlog_info("%s:  maxim smartpa set reg val: addr = 0x%x, val = 0x%x\n", __func__, reg_val->reg_addr, reg_val->reg_val);

    return ret;
}


static int max98925_digital_mute(struct list_head *maxim, int mute)
{
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;
    int DAC_IN_SEL_X_DAI = 0;


    if (MUTE_OFF == mute) {
        hwlog_info("%s: maxim smartpa mute.\n",__func__);

        list_for_each(pos, maxim){
            p = list_entry(pos, struct maxim_priv, list);
            mutex_lock(&p->lock);
            regmap_update_bits(p->regmap, MAX98925_R02D_GAIN, M98925_SPK_GAIN_MASK, 0x00);
            regmap_update_bits(p->regmap, MAX98925_R038_GLOBAL_ENABLE, M98925_EN_MASK, 0x0);
            mutex_unlock(&p->lock);
        }
    }
    else {
        hwlog_info("%s: maxim smartpa unmute.\n, ",__func__);

        list_for_each(pos, maxim){
            p = list_entry(pos, struct maxim_priv, list);
            mutex_lock(&p->lock);

            switch(p->type){
                case MAXIM_L:
                    if(maxim_num > 1){
                        DAC_IN_SEL_X_DAI = M98925_DAC_IN_SEL_LEFT_DAI;
                    }else{
                        DAC_IN_SEL_X_DAI = M98925_DAC_IN_SEL_DIV2_SUMMED_DAI;
                    }
                    break;
                case MAXIM_R:
                    DAC_IN_SEL_X_DAI = M98925_DAC_IN_SEL_RIGHT_DAI;
                    break;
                default:
                    break;
            }
            regmap_write(p->regmap, MAX98925_R03A_BOOST_LIMITER, 0xF8);
            regmap_update_bits(p->regmap, MAX98925_R02D_GAIN, M98925_DAC_IN_SEL_MASK, DAC_IN_SEL_X_DAI);
            regmap_update_bits(p->regmap, MAX98925_R02D_GAIN, M98925_SPK_GAIN_MASK, p->gain);
            regmap_update_bits(p->regmap, MAX98925_R036_BLOCK_ENABLE,
                        M98925_BST_EN_MASK | M98925_SPK_EN_MASK |
                        M98925_ADC_IMON_EN_MASK | M98925_ADC_VMON_EN_MASK,
                        M98925_BST_EN_MASK | M98925_SPK_EN_MASK |
                        M98925_ADC_IMON_EN_MASK | M98925_ADC_VMON_EN_MASK);
            regmap_write(p->regmap, MAX98925_R038_GLOBAL_ENABLE, M98925_EN_MASK);

            mutex_unlock(&p->lock);
        }
    }

    return 0;
}


//max98925_spk_digital_mute && max98925_rec_digital_mute
//spk is set gain == gain_incall in dts
static int max98925_single_digital_mute(struct list_head *maxim, unsigned int type, int mute)
{
    struct maxim_priv *p = NULL;
    int val = 0;

    p = find_maxim_by_type(maxim, type);

    if(NULL == p){
        hwlog_err("%s: hardware donot sopport smartpa\n",__func__);
        return -ENODEV;
    }

    mutex_lock(&p->lock);

    if (MUTE_OFF == mute) {
        hwlog_info("%s: maxim smartpa mute\n",__func__);
        regmap_update_bits(p->regmap, MAX98925_R02D_GAIN,
                    M98925_SPK_GAIN_MASK, 0x00);
        if (SPK_REC_DUAL_SMARTPA == maxim_num) {
            val = (MAXIM_L == p->type) ? 0xF0:0x0F;
            regmap_write(p->regmap, MAX98925_R02A_DOUT_HIZ_CFG4, val);
        }
        regmap_update_bits(p->regmap, MAX98925_R038_GLOBAL_ENABLE,
                    M98925_EN_MASK, 0x0);
    }
    else {
        hwlog_info("%s: maxim smartpa unmute\n",__func__);
        /* Because smartpa algorithm is closed in only receiver scene,
         * set REC input source with Left/2 + Right/2 with dual smartpa product;
         */
        if (maxim_num > 1)
            val = (MAXIM_L == p->type) ? M98925_DAC_IN_SEL_LEFT_DAI:M98925_DAC_IN_SEL_DIV2_SUMMED_DAI;
        else
            val = M98925_DAC_IN_SEL_DIV2_SUMMED_DAI;
        regmap_write(p->regmap, MAX98925_R03A_BOOST_LIMITER, 0xF8);
        regmap_update_bits(p->regmap, MAX98925_R02D_GAIN,
                    M98925_DAC_IN_SEL_MASK, val);

        regmap_update_bits(p->regmap, MAX98925_R02D_GAIN,
                    M98925_SPK_GAIN_MASK, p->gain_incall);

        regmap_update_bits(p->regmap, MAX98925_R036_BLOCK_ENABLE,
                    M98925_BST_EN_MASK | M98925_SPK_EN_MASK |
                    M98925_ADC_IMON_EN_MASK | M98925_ADC_VMON_EN_MASK,
                    M98925_BST_EN_MASK | M98925_SPK_EN_MASK |
                    M98925_ADC_IMON_EN_MASK | M98925_ADC_VMON_EN_MASK);
        /* even if device have dual smartpa, when it only use spk or rec smartpa,
           it should set 0x2A = 0x00, use 8 IV idle slots, for avoiding DOUT I2S waving depression */
        regmap_write(p->regmap, MAX98925_R02A_DOUT_HIZ_CFG4, 0x00);
        regmap_write(p->regmap, MAX98925_R038_GLOBAL_ENABLE,
                    M98925_EN_MASK);
    }
    mutex_unlock(&p->lock);

    return 0;
}





static int max98925_get_volume(struct list_head *maxim, unsigned int type, unsigned int *value)
{
    struct maxim_priv *p = NULL;

    p = find_maxim_by_type(maxim, type);
    if(NULL == p){
        hwlog_err("%s: it has no type[%d] in max98925 device\n", __func__, type);
        return -ENODEV;
    }

    return regmap_read(p->regmap, MAX98925_R02D_GAIN, value);
}



static int max98925_set_volume(struct list_head *maxim, unsigned int value)
{
    int ret = 0;
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;

    list_for_each(pos, maxim){
        p = list_entry(pos, struct maxim_priv, list);
        ret |= regmap_write(p->regmap, MAX98925_R02D_GAIN, value);
    }

    return ret;
}


static int max98925_get_daiclock(struct list_head *maxim, unsigned int type, unsigned int *value)
{
    struct maxim_priv *p = NULL;

    p = find_maxim_by_type(maxim, type);
    if(NULL == p){
        hwlog_err("%s: it has no type[%d] in max98925 device\n", __func__, type);
        return -ENODEV;
    }

    return regmap_read(p->regmap, MAX98925_R01B_DAI_CLK_MODE2, value);
}


static int max98925_set_daiclock(struct list_head *maxim, unsigned int value)
{
    int ret = 0;
    ret |= max98925_set_clock(maxim, value);
    ret |= max98925_set_slave(maxim);

    return ret;
}




static int max98925_get_boostvolt(struct list_head *maxim, unsigned int type, unsigned int *value)
{
    struct maxim_priv *p = NULL;

    p = find_maxim_by_type(maxim, type);
    if(NULL == p){
        hwlog_err("%s: it has no type[%d] in max98925 device\n", __func__, type);
        return -ENODEV;
    }

    return regmap_read(p->regmap, MAX98925_R037_CONFIGURATION, value);
}


static int max98925_set_boostvolt(struct list_head *maxim, unsigned int value)
{
    int ret = 0;
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;

    list_for_each(pos, maxim){
        p = list_entry(pos, struct maxim_priv, list);
        ret |= regmap_write(p->regmap, MAX98925_R037_CONFIGURATION, value);
    }

    return ret;
}




static int max98925_get_alcthreshold(struct list_head *maxim, unsigned int type, unsigned int *value)
{
    struct maxim_priv *p = NULL;

    p = find_maxim_by_type(maxim, type);
    if(NULL == p){
        hwlog_err("%s: it has no type[%d] in max98925 device\n", __func__, type);
        return -ENODEV;
    }

    return regmap_read(p->regmap, MAX98925_R030_THRESHOLD, value);
}


static int max98925_set_alcthreshold(struct list_head *maxim, unsigned int value)
{
    int ret = 0;
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;

    list_for_each(pos, maxim){
        p = list_entry(pos, struct maxim_priv, list);
        ret |= regmap_write(p->regmap, MAX98925_R030_THRESHOLD, value);
    }

    return ret;
}




static int max98925_get_filters(struct list_head *maxim, unsigned int type, unsigned int *value)
{
    struct maxim_priv *p = NULL;

    p = find_maxim_by_type(maxim, type);
    if(NULL == p){
        hwlog_err("%s: it has no type[%d] in max98925 device\n", __func__, type);
        return -ENODEV;
    }

    return regmap_read(p->regmap, MAX98925_R02C_FILTERS, value);
}


static int max98925_set_filters(struct list_head *maxim, unsigned int value)
{
    int ret = 0;
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;

    list_for_each(pos, maxim){
        p = list_entry(pos, struct maxim_priv, list);
        ret |= regmap_write(p->regmap, MAX98925_R02C_FILTERS, value);
    }

    return ret;
}



static int max98925_get_gainramp(struct list_head *maxim, unsigned int type, unsigned int *value)
{
    struct maxim_priv *p = NULL;

    p = find_maxim_by_type(maxim, type);
    if(NULL == p){
        hwlog_err("%s: it has no type[%d] in max98925 device\n", __func__, type);
        return -ENODEV;
    }

    return regmap_read(p->regmap, MAX98925_R02E_GAIN_RAMPING, value);
}


static int max98925_set_gainramp(struct list_head *maxim, unsigned int value)
{
    int ret = 0;
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;

    list_for_each(pos, maxim){
        p = list_entry(pos, struct maxim_priv, list);
        ret |= regmap_write(p->regmap, MAX98925_R02E_GAIN_RAMPING, value);
    }

    return ret;
}



static int max98925_open(struct inode *inode, struct file *filp)
{
    int ret = 0;
    int reg = 0;
    int val = 0;

    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;
    struct list_head *maxim = get_maxim_list_head();
    maxim_num = get_maxim_num();

    list_for_each(pos, maxim){
        p = list_entry(pos, struct maxim_priv, list);

        p->sysclk = 12288000;


        ret = regmap_read(p->regmap, MAX98925_R0FF_VERSION, &reg);
        if ((ret < 0) || (reg == 0x00)) {
            hwlog_err("maxim initialization error (%d 0x%02X)\n", ret, reg);
            goto err_access;
        }

        hwlog_info("max98925 version 0x%02X\n", reg);

        regmap_write(p->regmap, MAX98925_R038_GLOBAL_ENABLE, 0x00);

        /* It's not the default but we need to set DAI_DLY */
        regmap_write(p->regmap, MAX98925_R020_FORMAT, M98925_DAI_DLY_MASK | M98925_DAI_CHANSZ_32);
        regmap_write(p->regmap, MAX98925_R021_TDM_SLOT_SELECT, 0xC0);

        if(1 == maxim_num){
            regmap_write(p->regmap, MAX98925_R027_DOUT_HIZ_CFG1, 0x00);
            regmap_write(p->regmap, MAX98925_R028_DOUT_HIZ_CFG2, 0x00);
            regmap_write(p->regmap, MAX98925_R029_DOUT_HIZ_CFG3, 0x00);
            regmap_write(p->regmap, MAX98925_R02A_DOUT_HIZ_CFG4, 0x00);
        }else{
            val = (MAXIM_L == p->type) ? 0xF0:0x0F;
            regmap_write(p->regmap, MAX98925_R027_DOUT_HIZ_CFG1, 0xFF);
            regmap_write(p->regmap, MAX98925_R028_DOUT_HIZ_CFG2, 0xFF);
            regmap_write(p->regmap, MAX98925_R029_DOUT_HIZ_CFG3, 0xFF);
            regmap_write(p->regmap, MAX98925_R02A_DOUT_HIZ_CFG4, val);
        }

        regmap_write(p->regmap, MAX98925_R02C_FILTERS, 0x49);
        regmap_write(p->regmap, MAX98925_R034_ALC_CONFIGURATION, 0x12);

        /*****************************************************************/
        /* Set boost output to minimum until DSM is implemented          */
        regmap_write(p->regmap, MAX98925_R037_CONFIGURATION, 0x00);
        /*****************************************************************/

        // Disable ALC muting
        regmap_write(p->regmap, MAX98925_R03A_BOOST_LIMITER, 0xF8);
        if(1 == maxim_num){
            regmap_update_bits(p->regmap, MAX98925_R02D_GAIN,
                        M98925_DAC_IN_SEL_MASK, M98925_DAC_IN_SEL_DIV2_SUMMED_DAI);
        }else{
            switch(p->type){
                case MAXIM_L:
                    regmap_update_bits(p->regmap, MAX98925_R02D_GAIN,
                                M98925_DAC_IN_SEL_MASK, M98925_DAC_IN_SEL_LEFT_DAI);
                    break;
                case MAXIM_R:
                    regmap_update_bits(p->regmap, MAX98925_R02D_GAIN,
                                M98925_DAC_IN_SEL_MASK, M98925_DAC_IN_SEL_RIGHT_DAI);
                    break;
                default:
                    break;
            }
        }

        max98925_set_clock(maxim, 48000);
        max98925_set_slave(maxim);
    }


    ret = nonseekable_open(inode, filp);
    if (ret)
        return ret;

    filp->private_data = (void*)(get_maxim_list_head());

err_access:

    hwlog_info("%s: exit %d\n", __func__, ret);

    return ret;
}



static int max98925_release(struct inode *inode, struct file *filp)
{
    hwlog_info("%s: enter\n", __func__);
    return 0;
}


struct maxim_ioctl_ops max98925_ioctl_ops = {
    .maxim_set_slave = max98925_set_slave,
    .maxim_set_master = max98925_set_master,
    .maxim_set_clock = max98925_set_clock,
    .maxim_open = max98925_open,
    .maxim_release = max98925_release,
    .maxim_get_version = max98925_get_version,
    .maxim_get_reg_val = max98925_get_reg_val,
    .maxim_set_reg_val = max98925_set_reg_val,
    .maxim_digital_mute = max98925_digital_mute,
    .maxim_single_digital_mute = max98925_single_digital_mute,
    .maxim_get_volume = max98925_get_volume,
    .maxim_set_volume = max98925_set_volume,
    .maxim_get_daiclock = max98925_get_daiclock,
    .maxim_set_daiclock = max98925_set_daiclock,
    .maxim_get_boostvolt = max98925_get_boostvolt,
    .maxim_set_boostvolt = max98925_set_boostvolt,
    .maxim_get_alcthreshold = max98925_get_alcthreshold,
    .maxim_set_alcthreshold = max98925_set_alcthreshold,
    .maxim_get_filters = max98925_get_filters,
    .maxim_set_filters = max98925_set_filters,
    .maxim_get_gainramp = max98925_get_gainramp,
    .maxim_set_gainramp = max98925_set_gainramp,
};


#ifdef CONFIG_PM
static int max98925_suspend(struct device *dev)
{
    struct list_head *head = NULL;
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;

    head = get_maxim_list_head();
    if(NULL == head){
        return -1;
    }

    list_for_each(pos, head){
        p = list_entry(pos, struct maxim_priv, list);
        regcache_cache_only(p->regmap, true);
    }

    return 0;
}

static int max98925_resume(struct device *dev)
{
    struct list_head *head = NULL;
    struct list_head *pos = NULL;
    struct maxim_priv *p = NULL;

    head = get_maxim_list_head();
    if(NULL == head){
        return -1;
    }

    list_for_each(pos, head){
        p = list_entry(pos, struct maxim_priv, list);
        regcache_cache_only(p->regmap, false);
        regcache_sync(p->regmap);
    }

    return 0;
}
#else
#define max98925_suspend NULL
#define max98925_resume NULL
#endif





static const struct regmap_config max98925_regmap = {
    .reg_bits         = 8,
    .val_bits         = 8,
    .max_register     = MAX98925_R0FF_VERSION,
    .reg_defaults     = max98925_reg,
    .num_reg_defaults = ARRAY_SIZE(max98925_reg),
    .volatile_reg     = max98925_volatile_register,
    .readable_reg     = max98925_readable_register,
    .cache_type       = REGCACHE_RBTREE,
};


static int max98925_i2c_probe(struct i2c_client *i2c, const struct i2c_device_id *id)
{
    int ret = FAILED;
    const char *type_dts_name = "smartpa_type";
    const char *gain_dts_name = "gain";
    const char *gain_incall_dts_name = "gain_incall";
    struct maxim_priv *max98925 = NULL;

    max98925 = kzalloc(sizeof(struct maxim_priv), GFP_KERNEL);
    if(NULL == max98925){
        hwlog_err("%s: max98925 kamlloc maxim_priv failed!!!\n", __func__);
        goto err_out;
    }

    ret = of_property_read_u32(i2c->dev.of_node, type_dts_name, &max98925->type);
    if(ret || max98925->type >= ARRAY_SIZE(type_gain_def)){
        hwlog_err("%s: get smartPA type from dts failed or type is more than default!!!\n", __func__);
        ret = FAILED;
        goto err_out;
    }

    ret = of_property_read_u32(i2c->dev.of_node, gain_dts_name, &max98925->gain);
    if (ret) {
        max98925->gain = type_gain_def[max98925->type].gain;
    }
    hwlog_info("%s: get max98925 type[%d]_gain =0x%x\n",__func__, max98925->type, max98925->gain);

    ret = of_property_read_u32(i2c->dev.of_node, gain_incall_dts_name, &max98925->gain_incall);
    if (ret) {
        max98925->gain_incall = type_gain_def[max98925->type].gain_incall;
    }
    hwlog_info("%s: get max98925 type[%d]_gain_incall =0x%x\n",__func__, max98925->type, max98925->gain_incall);


    max98925->regmap = regmap_init_i2c(i2c, &max98925_regmap);
    if(IS_ERR(max98925->regmap)){
        ret = PTR_ERR(max98925->regmap);
        dev_err(&i2c->dev, "Failed to allocate smartPA type[%d]'s regmap: %d\n", max98925->type, ret);
        goto err_out;
    }

    mutex_init(&max98925->lock);   
    maxim_list_add(max98925);

    if((ret = sysfs_create_group(&i2c->dev.kobj, &max98925_attr_group)) < 0){
        hwlog_err("%s: failed to register smartPA type[%d]'s i2c sysfs, ret =%d\n", __func__, max98925->type, ret);
    }


    if(maxim_ioctl_isregist()){
        maxim_ioctl_regist(&max98925_ioctl_ops);
    }
    hwlog_info("%s: ret %d\n", __func__, ret);


err_out:
    if(ret < 0){
        if(max98925 != NULL){
            if(max98925->regmap){
                regmap_exit(max98925->regmap);
            }

            kfree(max98925);
            max98925 = NULL;
        }
        maxim_list_del_all();
    }

    return ret;
}

static int max98925_i2c_remove(struct i2c_client *client)
{
    maxim_list_del_all();
    hwlog_info("%s: exit\n", __func__);

    return 0;
}

static void max98925_i2c_shutdown(struct i2c_client *client)
{
    struct list_head *head = get_maxim_list_head();


    hwlog_info("%s: shutdown for max98925\n", __func__);
    max98925_digital_mute(head, MUTE_OFF);

    return;
}


static const struct dev_pm_ops max98925_pm_ops = {
    .suspend        = max98925_suspend,
    .resume            = max98925_resume,
};
static const struct of_device_id max98925_match[] = {
    { .compatible = "huawei,max98925", },
    {},
};
MODULE_DEVICE_TABLE(of, max98925_match);

static const struct i2c_device_id max98925_i2c_id[] = {
    { "max98925", MAX98925 },
    { }
};
MODULE_DEVICE_TABLE(i2c, max98925_i2c_id);

static struct i2c_driver max98925_i2c_driver = {
    .driver = {
        .name = "max98925",
        .owner = THIS_MODULE,
        .pm = &max98925_pm_ops,
        .of_match_table = of_match_ptr(max98925_match),
    },
    .probe  = max98925_i2c_probe,
    .remove = max98925_i2c_remove,
    .shutdown = max98925_i2c_shutdown,
    .id_table = max98925_i2c_id,
};


static int __init maxim_init(void)
{

    return i2c_add_driver(&max98925_i2c_driver);
}


static void __exit maxim_exit(void)
{

    maxim_list_del_all();

    i2c_del_driver(&max98925_i2c_driver);
}


module_init(maxim_init);
module_exit(maxim_exit);

MODULE_DESCRIPTION("MAX98925 i2c device driver");
MODULE_AUTHOR("zhujiaxin<zhujiaxin@huawei.com>");
MODULE_LICENSE("GPL");
