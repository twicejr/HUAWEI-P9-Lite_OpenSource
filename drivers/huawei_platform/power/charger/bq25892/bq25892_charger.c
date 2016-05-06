/*
 * drivers/power/bq25892_charger.c
 *
 * BQ25892/1/2/3/4 charging driver
 *
 * Copyright (C) 2012-2015 HUAWEI, Inc.
 * Author: HUAWEI, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/wakelock.h>
#include <linux/usb/otg.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/power_supply.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <linux/huawei/usb/hisi_usb.h>
#include <huawei_platform/log/hw_log.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif
#include <linux/raid/pq.h>
#include <huawei_platform/power/huawei_charger.h>
#include <linux/power/hisi/hisi_bci_battery.h>
#include <bq25892_charger.h>
#include <linux/huawei/hisi_adc.h>

#define HWLOG_TAG bq25892_charger

HWLOG_REGIST();

struct bq25892_device_info *g_bq25892_dev = NULL;
static unsigned int rilim = 124;//this should be configured in dts file based on the real value of the Iin limit resistance
static unsigned int adc_channel_iin = 10;//this should be configured in dts file based on the real adc channel number
static unsigned int adc_channel_vbat_sys = 14;
static u32 is_board_type = 0; /*0:sft 1:udp 2:asic*/
/**********************************************************
*  Function:       bq25892_write_block
*  Discription:    register write block interface
*  Parameters:   di:bq25892_device_info
*                      value:register value
*                      reg:register name
*                      num_bytes:bytes number
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_write_block(struct bq25892_device_info *di, u8 *value,
                               u8 reg, unsigned num_bytes)
{
    struct i2c_msg msg[1];
    int ret = 0;

    *value = reg;

    msg[0].addr = di->client->addr;
    msg[0].flags = 0;
    msg[0].buf = value;
    msg[0].len = num_bytes + 1;

   ret = i2c_transfer(di->client->adapter, msg, 1);

    /* i2c_transfer returns number of messages transferred */
    if (ret != 1)
    {
        hwlog_err("i2c_write failed to transfer all messages\n");
        if (ret < 0)
            return ret;
        else
            return -EIO;
    }
    else
    {
        return 0;
    }
}
/**********************************************************
*  Function:       bq25892_read_block
*  Discription:    register read block interface
*  Parameters:   di:bq25892_device_info
*                      value:register value
*                      reg:register name
*                      num_bytes:bytes number
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_read_block(struct bq25892_device_info *di, u8 *value,
                            u8 reg, unsigned num_bytes)
{
    struct i2c_msg msg[2];
    u8 buf = 0;
    int ret = 0;

    buf = reg;

    msg[0].addr = di->client->addr;
    msg[0].flags = 0;
    msg[0].buf = &buf;
    msg[0].len = 1;

    msg[1].addr = di->client->addr;
    msg[1].flags = I2C_M_RD;
    msg[1].buf = value;
    msg[1].len = num_bytes;

    ret = i2c_transfer(di->client->adapter, msg, 2);

    /* i2c_transfer returns number of messages transferred */
    if (ret != 2)
    {
        hwlog_err("i2c_write failed to transfer all messages\n");
        if (ret < 0)
            return ret;
        else
            return -EIO;
    }
    else
    {
        return 0;
    }
}
/**********************************************************
*  Function:       bq25892_write_byte
*  Discription:    register write byte interface
*  Parameters:   reg:register name
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_write_byte(u8 reg,u8 value)
{
    struct bq25892_device_info *di = g_bq25892_dev;
    /* 2 bytes offset 1 contains the data offset 0 is used by i2c_write */
    u8 temp_buffer[2] = { 0 };

    /* offset 1 contains the data */
    temp_buffer[1] = value;
    return bq25892_write_block(di, temp_buffer, reg, 1);
}
/**********************************************************
*  Function:       bq25892_read_byte
*  Discription:    register read byte interface
*  Parameters:   reg:register name
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_read_byte(u8 reg, u8 *value)
{
    struct bq25892_device_info *di = g_bq25892_dev;

    return bq25892_read_block(di, value, reg, 1);
}
/**********************************************************
*  Function:       bq25892_write_mask
*  Discription:    register write mask interface
*  Parameters:   reg:register name
*                      MASK:mask value of the function
*                      SHIFT:shift number of the function
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_write_mask(u8 reg, u8 MASK, u8 SHIFT, u8 value)
{
    int ret = 0;
    u8 val = 0;

    ret = bq25892_read_byte(reg,&val);
    if(ret < 0)
        return ret;

    val &= ~MASK;
    val |= ((value << SHIFT) & MASK);

    ret = bq25892_write_byte(reg,val);

    return ret;
}
/**********************************************************
*  Function:       bq25892_read_mask
*  Discription:    register read mask interface
*  Parameters:   reg:register name
*                      MASK:mask value of the function
*                      SHIFT:shift number of the function
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_read_mask(u8 reg, u8 MASK, u8 SHIFT, u8 *value)
{
    int ret = 0;
    u8 val = 0;

    ret = bq25892_read_byte(reg,&val);
    if(ret < 0)
        return ret;
    val &= MASK;
    val >>= SHIFT;
    *value = val;

    return 0;
}

#define CONFIG_SYSFS_BQ
#ifdef CONFIG_SYSFS_BQ
/*
 * There are a numerous options that are configurable on the bq25892
 * that go well beyond what the power_supply properties provide access to.
 * Provide sysfs access to them so they can be examined and possibly modified
 * on the fly.
 */

#define BQ25892_SYSFS_FIELD(_name, r, f, m, store)                  \
{                                                   \
    .attr = __ATTR(_name, m, bq25892_sysfs_show, store),    \
    .reg = BQ25892_REG_##r,                      \
    .mask = BQ25892_REG_##r##_##f##_MASK,                       \
    .shift = BQ25892_REG_##r##_##f##_SHIFT,                     \
}

#define BQ25892_SYSFS_FIELD_RW(_name, r, f)                     \
        BQ25892_SYSFS_FIELD(_name, r, f, S_IWUSR | S_IRUGO, \
                bq25892_sysfs_store)

#define BQ25892_SYSFS_FIELD_RO(_name, r, f)                         \
        BQ25892_SYSFS_FIELD(_name, r, f, S_IRUGO, NULL)

static ssize_t bq25892_sysfs_show(struct device *dev,
        struct device_attribute *attr, char *buf);
static ssize_t bq25892_sysfs_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t count);

struct bq25892_sysfs_field_info {
    struct device_attribute	attr;
    u8  reg;
    u8  mask;
    u8  shift;
};



static struct bq25892_sysfs_field_info bq25892_sysfs_field_tbl[] = {
        /* sysfs name reg field in reg */
    BQ25892_SYSFS_FIELD_RW(en_hiz,      00,        EN_HIZ),
    BQ25892_SYSFS_FIELD_RW(en_ilim,      00,        EN_ILIM),
    BQ25892_SYSFS_FIELD_RW(iinlim,      00,        IINLIM),
    BQ25892_SYSFS_FIELD_RW(dpm_os,      01,        VINDPM_OS),
    BQ25892_SYSFS_FIELD_RW(conv_start,      02,        CONV_START),
    BQ25892_SYSFS_FIELD_RW(ico_en,      02,        ICO_EN),
    BQ25892_SYSFS_FIELD_RW(force_dpdm,      02,        FORCE_DPDM),
    BQ25892_SYSFS_FIELD_RW(auto_dpdm_en,      02,        AUTO_DPDM_EN),
    BQ25892_SYSFS_FIELD_RW(chg_config,      03,        CHG_CONFIG),
    BQ25892_SYSFS_FIELD_RW(otg_config,      03,        OTG_CONFIG),
    BQ25892_SYSFS_FIELD_RW(sys_min,     03,        SYS_MIN),
    BQ25892_SYSFS_FIELD_RW(ichg,        04,        ICHG),
    BQ25892_SYSFS_FIELD_RW(iprechg,     05,      IPRECHG),
    BQ25892_SYSFS_FIELD_RW(iterm,       05,      ITERM),
    BQ25892_SYSFS_FIELD_RW(vreg,        06,        VREG),
    BQ25892_SYSFS_FIELD_RW(batlowv,     06,        BATLOWV),
    BQ25892_SYSFS_FIELD_RW(vrechg,      06,        VRECHG),
    BQ25892_SYSFS_FIELD_RW(en_term,     07,       EN_TERM),
    BQ25892_SYSFS_FIELD_RW(watchdog,        07,       WATCHDOG),
    BQ25892_SYSFS_FIELD_RW(en_timer,        07,       EN_TIMER),
    BQ25892_SYSFS_FIELD_RW(chg_timer,       07,       CHG_TIMER),
    BQ25892_SYSFS_FIELD_RW(jeta_iset,       07,       JEITA_ISET),
    BQ25892_SYSFS_FIELD_RW(bat_comp,        08,      BAT_COMP),
    BQ25892_SYSFS_FIELD_RW(vclamp,      08,      VCLAMP),
    BQ25892_SYSFS_FIELD_RW(treg,        08,      TREG),
    BQ25892_SYSFS_FIELD_RW(force_ico,      09,        FORCE_ICO),
    BQ25892_SYSFS_FIELD_RW(batfet_disable,      09,        BATFET_DISABLE),
    BQ25892_SYSFS_FIELD_RW(jeita_vset,      09,        JEITA_VSET),
    BQ25892_SYSFS_FIELD_RW(boost_vol,       0A,        BOOSTV),
    BQ25892_SYSFS_FIELD_RW(boost_lim,       0A,        BOOST_LIM),
    BQ25892_SYSFS_FIELD_RW(vindpm,      0D,        VINDPM),
    BQ25892_SYSFS_FIELD_RW(force_vindpm,      0D,        FORCE_VINDPM),
    BQ25892_SYSFS_FIELD_RW(reg_rst,        14,     REG_RST),
    BQ25892_SYSFS_FIELD_RO(vbus_stat,       0B,     VBUS_STAT),
    BQ25892_SYSFS_FIELD_RO(chrg_stat,       0B,     CHRG_STAT),
    BQ25892_SYSFS_FIELD_RO(pg_stat,     0B,     PG_STAT),
    BQ25892_SYSFS_FIELD_RO(sdp_stat,     0B,     SDP_STAT),
    BQ25892_SYSFS_FIELD_RO(vsys_stat,       0B,     VSYS_STAT),
    BQ25892_SYSFS_FIELD_RO(watchdog_fault,      0C,      WATCHDOG_FAULT),
    BQ25892_SYSFS_FIELD_RO(boost_fault,     0C,      BOOST_FAULT),
    BQ25892_SYSFS_FIELD_RO(chrg_fault,      0C,      CHRG_FAULT),
    BQ25892_SYSFS_FIELD_RO(bat_fault,       0C,      BAT_FAULT),
    BQ25892_SYSFS_FIELD_RO(ntc_fault,        0C,     NTC_FAULT),
    BQ25892_SYSFS_FIELD_RO(therm_stat,        0E,     THERM_STAT),
    BQ25892_SYSFS_FIELD_RO(bat_vol,        0E,     BATV),
    BQ25892_SYSFS_FIELD_RO(sys_volt,        0F,     SYSV),
    BQ25892_SYSFS_FIELD_RO(vbus_volt,        11,     VBUSV),
    BQ25892_SYSFS_FIELD_RO(ichg_adc,        12,     ICHGR),
    BQ25892_SYSFS_FIELD_RO(vdpm_stat,        13,     VDPM_STAT),
    BQ25892_SYSFS_FIELD_RO(idpm_stat,        13,     IDPM_STAT),
    BQ25892_SYSFS_FIELD_RO(idpm_lim,        13,     IDPM_LIM),
    BQ25892_SYSFS_FIELD_RO(ico_optimized,        14,     ICO_OPTIMIZED),
    BQ25892_SYSFS_FIELD_RW(reg_addr,     NONE,        NONE),
    BQ25892_SYSFS_FIELD_RW(reg_value,     NONE,        NONE),
};


static struct attribute *
        bq25892_sysfs_attrs[ARRAY_SIZE(bq25892_sysfs_field_tbl) + 1];

static const struct attribute_group bq25892_sysfs_attr_group = {
        .attrs = bq25892_sysfs_attrs,
};
/**********************************************************
*  Function:       bq25892_sysfs_init_attrs
*  Discription:    initialize bq25892_sysfs_attrs[] for bq25892 attribute
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void bq25892_sysfs_init_attrs(void)
{
    int i, limit = ARRAY_SIZE(bq25892_sysfs_field_tbl);

    for (i = 0; i < limit; i++)
        bq25892_sysfs_attrs[i] = &bq25892_sysfs_field_tbl[i].attr.attr;

    bq25892_sysfs_attrs[limit] = NULL; /* Has additional entry for this */
}
/**********************************************************
*  Function:       bq25892_sysfs_field_lookup
*  Discription:    get the current device_attribute from bq25892_sysfs_field_tbl by attr's name
*  Parameters:   name:evice attribute name
*  return value:  bq25892_sysfs_field_tbl[]
**********************************************************/
static struct bq25892_sysfs_field_info *bq25892_sysfs_field_lookup(const char *name)
{
    int i, limit = ARRAY_SIZE(bq25892_sysfs_field_tbl);

    for (i = 0; i < limit; i++)
        if (!strcmp(name, bq25892_sysfs_field_tbl[i].attr.attr.name))
            break;

    if (i >= limit)
        return NULL;

    return &bq25892_sysfs_field_tbl[i];
}
/**********************************************************
*  Function:       bq25892_sysfs_show
*  Discription:    show the value for all bq25892 device's node
*  Parameters:   dev:device
*                      attr:device_attribute
*                      buf:string of node value
*  return value:  0-sucess or others-fail
**********************************************************/
static ssize_t bq25892_sysfs_show(struct device *dev,
            struct device_attribute *attr, char *buf)
{
    struct bq25892_sysfs_field_info *info;
    struct bq25892_sysfs_field_info *info2;
    int ret;
    u8 v;

    info = bq25892_sysfs_field_lookup(attr->attr.name);
    if (!info)
        return -EINVAL;

    if(!strncmp("reg_addr",attr->attr.name,strlen("reg_addr")))
    {
        return scnprintf(buf,PAGE_SIZE,"0x%hhx\n",info->reg);
    }

    if(!strncmp(("reg_value"),attr->attr.name,strlen("reg_value")))
    {
        info2 = bq25892_sysfs_field_lookup("reg_addr");
        if(!info2)
            return -EINVAL;
        info->reg = info2->reg;
    }

    ret = bq25892_read_mask(info->reg, info->mask, info->shift, &v);
    if (ret)
        return ret;

    return scnprintf(buf, PAGE_SIZE, "%hhx\n", v);
}
/**********************************************************
*  Function:       bq25892_sysfs_store
*  Discription:    set the value for all bq25892 device's node
*  Parameters:   dev:device
*                      attr:device_attribute
*                      buf:string of node value
*                      count:unused
*  return value:  0-sucess or others-fail
**********************************************************/
static ssize_t bq25892_sysfs_store(struct device *dev,
            struct device_attribute *attr, const char *buf, size_t count)
{
    struct bq25892_sysfs_field_info *info;
    struct bq25892_sysfs_field_info *info2;
    int ret;
    u8 v;

    info = bq25892_sysfs_field_lookup(attr->attr.name);
    if (!info)
        return -EINVAL;

    ret = kstrtou8(buf, 0, &v);
    if (ret < 0)
        return ret;
    if(!strncmp(("reg_value"),attr->attr.name,strlen("reg_value")))
    {
        info2 = bq25892_sysfs_field_lookup("reg_addr");
        if(!info2)
            return -EINVAL;
        info->reg = info2->reg;
    }
    if(!strncmp(("reg_addr"),attr->attr.name,strlen("reg_addr")))
    {
        if(v <(u8)BQ25892_REG_TOTAL_NUM && v >=(u8)0x00 )
        {
            info->reg = v;
            return count;
        }
        else
        {
            return -EINVAL;
        }
    }

    ret = bq25892_write_mask(info->reg, info->mask, info->shift, v);
    if (ret)
        return ret;

    return count;
}
/**********************************************************
*  Function:       bq25892_sysfs_create_group
*  Discription:    create the bq25892 device sysfs group
*  Parameters:   di:bq25892_device_info
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_sysfs_create_group(struct bq25892_device_info *di)
{
    bq25892_sysfs_init_attrs();

    return sysfs_create_group(&di->dev->kobj,&bq25892_sysfs_attr_group);
}
/**********************************************************
*  Function:       charge_sysfs_remove_group
*  Discription:    remove the bq25892 device sysfs group
*  Parameters:   di:bq25892_device_info
*  return value:  NULL
**********************************************************/
static void bq25892_sysfs_remove_group(struct bq25892_device_info *di)
{
    sysfs_remove_group(&di->dev->kobj, &bq25892_sysfs_attr_group);
}
#else
static int bq25892_sysfs_create_group(struct bq25892_device_info *di)
{
    return 0;
}
static inline void bq25892_sysfs_remove_group(struct bq25892_device_info *di) {}
#endif
/**********************************************************
*  Function:       bq25892_device_check
*  Discription:    check chip i2c communication
*  Parameters:   null
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_device_check()
{
    int ret = 0;
    u8 reg = 0xff;
    ret |= bq25892_read_byte(BQ25892_REG_14,&reg);
    if(ret)
    {
        hwlog_err("read bq25892 version error.\n");
        return CHARGE_IC_BAD;
    }

    if((BQ25892 == (reg & CHIP_VERSION_MASK)) && (CHIP_REVISION == (reg & CHIP_REVISION_MASK)))
    {
        hwlog_info("bq25892 is good.\n");
        return CHARGE_IC_GOOD;
    }
    else
    {
        hwlog_err("bq25892 is bad.\n");
        return CHARGE_IC_BAD;
    }
}

/**********************************************************
*  Function:       bq25892_set_bat_comp
*  Discription:    set the bat comp
*  Parameters:   value:bat_comp m|?
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_bat_comp(int value)
{
    unsigned int bat_comp = 0;
    u8 bat_comp_reg = 0;
    bat_comp = value;

    if(bat_comp < BAT_COMP_MIN_0)
    {
        hwlog_info("set term current %dmA is out of range:%dmA!!",value,BAT_COMP_MIN_0);
        bat_comp = BAT_COMP_MIN_0;
    }
    else if (bat_comp > BAT_COMP_MAX_140)
    {
        hwlog_info("set term current %dmA is out of range:%dmA!!",value,BAT_COMP_MAX_140);
        bat_comp = BAT_COMP_MAX_140;
    }
    else
    {
        //do nothing
    }
    hwlog_debug(" bat_comp  is set %d\n",bat_comp);
    bat_comp_reg = (bat_comp - BAT_COMP_MIN_0)/BAT_COMP_STEP_20;
    return bq25892_write_mask(BQ25892_REG_08,BQ25892_REG_08_BAT_COMP_MASK,BQ25892_REG_08_BAT_COMP_SHIFT,bat_comp_reg);
}
/**********************************************************
*  Function:       bq25892_set_vclamp
*  Discription:    set the vclamp
*  Parameters:   value:vclamp mv
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_vclamp(int value)
{
    unsigned int vclamp = 0;
    u8 vclamp_reg = 0;
    vclamp = value;
    if(vclamp < VCLAMP_MIN_0)
    {
        hwlog_info("set term current %dmA is out of range:%dmA!!",value,VCLAMP_MIN_0);
        vclamp = VCLAMP_MIN_0;
    }
    else if (vclamp > VCLAMP_MAX_224)
    {
        hwlog_info("set term current %dmA is out of range:%dmA!!",value,VCLAMP_MAX_224);
        vclamp = VCLAMP_MAX_224;
    }
    else
    {
        //do nothing
    }
    hwlog_debug(" vclamp  is set %d\n",vclamp);
    vclamp_reg = (vclamp -VCLAMP_MIN_0)/VCLAMP_STEP_32;
    return bq25892_write_mask(BQ25892_REG_08,BQ25892_REG_08_VCLAMP_MASK,BQ25892_REG_08_VCLAMP_SHIFT,vclamp_reg);
}
/**********************************************************
*  Function:       bq25892_set_covn_start
*  Discription:    set covn start
*  Parameters:   value: 1(enable) or 0(disable)
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_covn_start(int enable)
{
    int ret = 0;
    u8 reg = 0;
    int i = 0;
    ret = bq25892_read_byte(BQ25892_REG_0B,&reg);

    if(ret)
    {
        hwlog_err(" bq25892 read PG STAT fail!.\n");
        return -1;
    }

    if(!(reg & BQ25892_NOT_PG_STAT))
    {
        hwlog_err(" bq25892 PG NOT GOOD ,can not set covn,reg:%x \n",reg);
        return -1;
    }
    ret = bq25892_write_mask(BQ25892_REG_02,BQ25892_REG_02_CONV_START_MASK,BQ25892_REG_02_CONV_START_SHIFT,enable);
    if(ret)
    {
        hwlog_err("set covn fail! ret =%d \n",ret);
        return -1;
    }
    /*The conversion result is ready after tCONV, max (10*100)ms*/
    for(i=0; i<10;i++)
    {
        ret =  bq25892_read_mask(BQ25892_REG_02, BQ25892_REG_02_CONV_START_MASK, BQ25892_REG_02_CONV_START_SHIFT, &reg);
        if(ret )
        {
            hwlog_err(" bq25892 read ADC CONV STAT fail!.\n");
            return -1;
        }
        /* if ADC Conversion finished, CONV_RATE bit will be 0 */
        if(reg == 0)
        {
            break;
        }
        msleep(100);
    }
    hwlog_debug(" one-shot covn start is set %d\n",enable);
    return 0;
}

static int bq25892_chip_init(void)
{
    int ret = 0;
    struct bq25892_device_info *di = g_bq25892_dev;

    /*reg init*/
    //bq25892_write_mask(REG0x14,BQ25892_REG_RST_MASK,BQ25892_REG_RST_SHIFT,0x01);
    /* do not init input current 500 ma(REG00) to support lpt without battery  */
    /*02 enable Start 1s Continuous Conversion ,others as default*/
    ret |= bq25892_write_byte(BQ25892_REG_02,0x1D);//adc off
    /*03 WD_RST 1,CHG_CONFIG 1,SYS_MIN 3.5*/
    ret |= bq25892_write_byte(BQ25892_REG_03,0x5A);
    /*04 Fast Charge Current Limit 2048mA*/
    ret |= bq25892_write_byte(BQ25892_REG_04,0x20);
    /*05 Precharge Current Limit 256mA,Termination Current Limit 256mA*/
    ret |= bq25892_write_byte(BQ25892_REG_05,0x33);
    /*06 Charge Voltage Limit 4.4,Battery Precharge to Fast Charge Threshold 3,Battery Recharge 100mV*/
    ret |= bq25892_write_byte(BQ25892_REG_06,0x8e);
    /*07 EN_TERM 0,Watchdog Timer 80s,EN_TIMER 1,Charge Timer 20h,JEITA Low Temperature Current Setting 1*/
    ret |= bq25892_write_byte(BQ25892_REG_07,0x2f);
    /*08 IR compensation voatge clamp = 224mV ,IR compensation resistor setting = 80mohm */
    ret |= bq25892_set_bat_comp(g_bq25892_dev->param_dts.bat_comp);
    ret |= bq25892_set_vclamp(g_bq25892_dev->param_dts.vclamp);
    /*boost mode current limit = 500mA,boostv 4.998v*/
    ret |= bq25892_write_byte(BQ25892_REG_0A,0x70);
    /*VINDPM Threshold Setting Method 1,Absolute VINDPM Threshold 4.4v*/
    //ret = bq25892_write_byte(BQ25892_REG_0D,0x92);

    gpio_set_value(di->gpio_cd, 0);//enable charging

    return ret;
}


/**********************************************************
*  Function:       bq25892_set_input_current
*  Discription:    set the input current in charging process
*  Parameters:   value:input current value
*  return value:  0-sucess or others-fail
**********************************************************/

static int bq25892_set_input_current(int value)
{
    unsigned int limit_current = 0;
    u8 Iin_limit = 0;
    limit_current = value ;
    if (limit_current <= IINLIM_MIN_100)
    {
        hwlog_info("input current %dmA is out of range:%dmA!!",value,IINLIM_MIN_100);
        limit_current = IINLIM_MIN_100;
    }
    else if (limit_current > IINLIM_MAX_3250)
    {
        hwlog_info("input current %dmA is out of range:%dmA!!",value,IINLIM_MAX_3250);
        limit_current = IINLIM_MAX_3250;
    }
    else
    {
        //do nothing
    }
    hwlog_debug("input current is set %dmA\n",limit_current);
    Iin_limit = (limit_current -IINLIM_MIN_100)/IINLIM_STEP_50;
    return bq25892_write_mask(BQ25892_REG_00,BQ25892_REG_00_IINLIM_MASK,BQ25892_REG_00_IINLIM_SHIFT,Iin_limit);
}
/**********************************************************
*  Function:       bq25892_set_charge_current
*  Discription:    set the charge current in charging process
*  Parameters:   value:charge current value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_charge_current(int value)
{
    unsigned int currentmA = 0;
    u8 ichg = 0;
    currentmA = value;
    if (currentmA < 0)
    {
        currentmA = 0 ;
    }
    else if (currentmA > ICHG_MAX_5056)
    {
        hwlog_info("set charge current %dmA is out of range:%dmA!!",value,ICHG_MAX_5056);
        currentmA = ICHG_MAX_5056 ;
    }
    else
    {
        //do nothing
    }
    hwlog_debug("charge current is set %dmA\n",currentmA);
    ichg = currentmA / ICHG_STEP_64;
    return bq25892_write_mask(BQ25892_REG_04,BQ25892_REG_04_ICHG_MASK,BQ25892_REG_04_ICHG_SHIFT,ichg);
}
/**********************************************************
*  Function:       bq25892_set_terminal_voltage
*  Discription:    set the terminal voltage in charging process
*  Parameters:   value:terminal voltage value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_terminal_voltage(int value)
{
    unsigned int voltagemV = 0;
    u8 Voreg = 0;
    voltagemV = value;
    if (voltagemV < VCHARGE_MIN_3840)
    {
        hwlog_info("set terminal voltage %dmV is out of range:%dmV!!",value,VCHARGE_MIN_3840);
        voltagemV = VCHARGE_MIN_3840;
    }
    else if (voltagemV > VCHARGE_MAX_4496)
    {
        hwlog_info("set terminal voltage %dmV is out of range:%dmV!!",value,VCHARGE_MAX_4496);
        voltagemV = VCHARGE_MAX_4496;
    }
    hwlog_debug("terminal voltage is set %dmV\n",voltagemV);
    Voreg = (voltagemV - VCHARGE_MIN_3840)/ VCHARGE_STEP_16;
    return bq25892_write_mask(BQ25892_REG_06,BQ25892_REG_06_VREG_MASK,BQ25892_REG_06_VREG_SHIFT,Voreg);
}
/**********************************************************
*  Function:       bq25892_set_dpm_voltage
*  Discription:    set the dpm voltage in charging process
*  Parameters:   value:dpm voltage value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_dpm_voltage(int value)
{
    int vindpm_voltage;
    u8 vindpm;
    u8 reg0d ;
    vindpm_voltage = value;
    if(vindpm_voltage > VINDPM_MAX_15300)
    {
        hwlog_info("set dpm voltage %d mv is out of range:%dmA!!",value,VINDPM_MAX_15300);
        vindpm_voltage = VINDPM_MAX_15300;
    }
    else if(vindpm_voltage < VINDPM_MIN_3900 )
    {
        hwlog_info("set dpm voltage %d mv is out of range:%dmA!!",value,VINDPM_MIN_3900);
        vindpm_voltage = VINDPM_MIN_3900;
    }
    else
    {
        //do nothing
    }

    hwlog_debug("vindpm absolute voltage is set %dmV\n",vindpm_voltage);
    vindpm = (vindpm_voltage - VINDPM_OFFSET_2600)/VINDPM_STEP_100;

    reg0d = (1<< BQ25892_REG_0D_FORCE_VINDPM_SHIFT) | vindpm ;/* 1 absolute dpm */

    return bq25892_write_byte(BQ25892_REG_0D,reg0d);
}
/**********************************************************
*  Function:       bq25892_set_terminal_current
*  Discription:    set the terminal current in charging process
*  Parameters:   value:terminal current value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_terminal_current(int value)
{
    unsigned int term_currentmA = 0;
    u8 iterm_reg = 0;
    term_currentmA = value;

    if(term_currentmA < ITERM_MIN_64)
    {
        hwlog_info("set term current %dmA is out of range:%dmA!!",value,ITERM_MIN_64);
        term_currentmA = ITERM_MIN_64;
    }
    else if (term_currentmA > ITERM_MAX_1024)
    {
        hwlog_info("set term current %dmA is out of range:%dmA!!",value,ITERM_MAX_1024);
        term_currentmA = ITERM_MAX_1024;
    }
    else
    {
        //do nothing
    }

    hwlog_debug(" term current  is set %dmA\n",term_currentmA);
    iterm_reg = term_currentmA/ITERM_STEP_64;
    return bq25892_write_mask(BQ25892_REG_05,BQ25892_REG_05_ITERM_MASK,BQ25892_REG_05_ITERM_SHIFT,iterm_reg);
}

/**********************************************************
*  Function:       bq25892_set_charge_enable
*  Discription:    set the charge enable in charging process
*  Parameters:   enable:charge enable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_charge_enable(int enable)
{
    struct bq25892_device_info *di = g_bq25892_dev;

    gpio_set_value(di->gpio_cd, !enable);

    return bq25892_write_mask(BQ25892_REG_03,BQ25892_REG_03_CHG_CONFIG_MASK,BQ25892_REG_03_CHG_CONFIG_SHIFT,enable);
}
/**********************************************************
*  Function:       bq25892_set_otg_enable
*  Discription:    set the otg mode enable in charging process
*  Parameters:   enable:otg mode  enable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_otg_enable(int enable)
{
    int val = 0;
    struct bq25892_device_info *di = g_bq25892_dev;
    gpio_set_value(di->gpio_cd, !enable);
    val = enable << 1;
    return bq25892_write_mask(BQ25892_REG_03,BQ25892_REG_03_CHG_CONFIG_MASK,BQ25892_REG_03_CHG_CONFIG_SHIFT,val);
}
/**********************************************************
*  Function:       bq25892_set_otg_current
*  Discription:    set the otg mdoe current
*  Parameters:     value :current value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_otg_current(int value)
{
    unsigned int temp_currentmA = 0;
    u8 reg = 0;
    temp_currentmA = value;

    if (temp_currentmA < BOOST_LIM_MIN_500 || temp_currentmA > BOOST_LIM_MAX_2450)
        hwlog_info("set otg current %dmA is out of range!",value);
    if(temp_currentmA < BOOST_LIM_750)
    {
        reg = 0;
    }
    else if (temp_currentmA >= BOOST_LIM_750 && temp_currentmA < BOOST_LIM_1200)
    {
        reg = 1;
    }
    else if (temp_currentmA >= BOOST_LIM_1200 && temp_currentmA < BOOST_LIM_1400)
    {
         reg = 2;
    }
    else if (temp_currentmA >= BOOST_LIM_1400 && temp_currentmA < BOOST_LIM_1650)
    {
        reg = 3;
    }
    else if (temp_currentmA >= BOOST_LIM_1650 && temp_currentmA < BOOST_LIM_1875)
    {
        reg = 4;
    }
    else if (temp_currentmA >= BOOST_LIM_1875 && temp_currentmA < BOOST_LIM_2150)
    {
        reg = 5;
    }
    else if (temp_currentmA >= BOOST_LIM_2150 && temp_currentmA < BOOST_LIM_MAX_2450)
    {
         reg = 6;
    }
    else
    {
        reg = 7;
    }

    hwlog_debug(" otg current is set %dmA\n",temp_currentmA);
    return bq25892_write_mask(BQ25892_REG_0A,BQ25892_REG_0A_BOOST_LIM_MASK,BQ25892_REG_0A_BOOST_LIM_SHIFT,reg);
}
/**********************************************************
*  Function:       bq25892_set_term_enable
*  Discription:    set the terminal enable in charging process
*  Parameters:   enable:terminal enable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_term_enable(int enable)
{
    return bq25892_write_mask(BQ25892_REG_07,BQ25892_REG_07_EN_TERM_MASK,BQ25892_REG_07_EN_TERM_SHIFT,enable);
}
/**********************************************************
*  Function:       bq25892_get_charge_state
*  Discription:    get the charge states in charging process
*  Parameters:   state:charge states
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_get_charge_state(unsigned int *state)
{
    u8 reg = 0;
    int ret = 0;
    ret = bq25892_read_byte(BQ25892_REG_0B,&reg);
    if(!(reg & BQ25892_NOT_PG_STAT))
    {
        *state |= CHAGRE_STATE_NOT_PG;
    }
    if((reg & BQ25892_CHGR_STAT_CHARGE_DONE) == BQ25892_CHGR_STAT_CHARGE_DONE)
    {
        *state |= CHAGRE_STATE_CHRG_DONE;
    }
    ret |= bq25892_read_byte(BQ25892_REG_0C,&reg);
    ret |= bq25892_read_byte(BQ25892_REG_0C,&reg);
    if((reg & BQ25892_WATCHDOG_FAULT) == BQ25892_WATCHDOG_FAULT)
    {
        *state |= CHAGRE_STATE_WDT_FAULT;
    }
    if((reg & BQ25892_POWER_SUPPLY_OVP_MASK) == BQ25892_POWER_SUPPLY_OVP)
    {
        *state |= CHAGRE_STATE_VBUS_OVP;
    }
    if((reg & BQ25892_BAT_FAULT_OVP) == BQ25892_BAT_FAULT_OVP)
    {
        *state |= CHAGRE_STATE_BATT_OVP;
    }
    if(reg != 0)
    {
        hwlog_err("state is not normal : BQ25892 REG[0x0C] is %x\n",reg);
    }

    return ret;
}
/**********************************************************
*  Function:       bq25892_get_vbus_mv
*  Discription:    get voltage of vbus
*  Parameters:   vbus_mv:voltage of vbus
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_get_vbus_mv(unsigned int *vbus_mv)
{
    u8 reg = 0;
    int ret = 0;
    ret = bq25892_read_byte(BQ25892_REG_11,&reg);
    reg = reg & BQ25892_REG_11_VBUSV_MASK;
    *vbus_mv = (unsigned int)reg * BQ25892_REG_11_VBUSV_STEP_MV + BQ25892_REG_11_VBUSV_OFFSET_MV;
    hwlog_debug(" vbus mv  is  %dmV\n",*vbus_mv);
    return ret;
}
/**********************************************************
*  Function:       bq25892_reset_watchdog_timer
*  Discription:    reset watchdog timer in charging process
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_reset_watchdog_timer(void)
{
	return bq25892_write_mask(BQ25892_REG_03,BQ25892_REG_03_WDT_RESET_MASK,BQ25892_REG_03_WDT_RESET_SHIFT,0x01);
}
/**********************************************************
*  Function:       bq25892_get_Vilim_sample
*  Discription:    get one sample Vilim from adc
*  Parameters:     NULL
*  return value:   adc sample value
**********************************************************/
static int bq25892_get_Vilim_sample(void)
{
    int i =0;
    int retry_times = 3;
    int V_sample = -1;

    for (i = 0; i < retry_times; ++i)
    {
        V_sample = hisi_adc_get_value(adc_channel_iin);
        if (V_sample < 0)
        {
            hwlog_err("adc read channel 10 fail!\n");
        }
        else
        {
            break;
        }
    }
    return V_sample;
}

/**********************************************************
*  Function:       bq25892_get_ilim
*  Discription:    get average value for ilim
*  Parameters:     NULL
*  return value:   average value for ilim
**********************************************************/
static int bq25892_get_ilim(void)
{
    int i;
    int cnt = 0;
    int V_temp;
    int delay_times = 100;
    int sample_num = 5; // use 5 samples to get an average value
    int sum = 0;
    int Kilim = 355; //based bq25892 spec

    for (i = 0; i < sample_num; ++i)
    {
        V_temp = bq25892_get_Vilim_sample();
        if (V_temp >= 0)
        {
            sum += V_temp;
            ++cnt;
        }
        else
        {
            hwlog_err("bq25892 get V_temp fail!\n");
        }
        msleep(delay_times);
    }
    if (cnt > 0)
    {
        return ((10*sum * Kilim) / (8 * rilim * cnt));/*I =(K* Vlim)/(rilim*0.8) new spec from TI*/
    }
    else
    {
        hwlog_err("use 0 as default Vilim!\n");
        return 0;
    }
}


static int bq25892_vbat_sys(void)
{
    int i =0;
    int retry_times = 3;
    int V_sample = -1;

    for (i = 0; i < retry_times; ++i)
    {
        V_sample = hisi_adc_get_value(adc_channel_vbat_sys);
        if (V_sample < 0)
        {
            hwlog_err("adc read channel 15 fail!\n");
        }
        else
        {
            break;
        }
    }
    return V_sample;
}

static int bq25892_get_vbat_sys(void)
{
    int i;
    int cnt = 0;
    int V_temp;
    int delay_times = 100;
    int sample_num = 5; // use 5 samples to get an average value
    int sum = 0;

    for (i = 0; i < sample_num; ++i)
    {
        V_temp = bq25892_vbat_sys();
        if (V_temp >= 0)
        {
            sum += V_temp;
            ++cnt;
        }
        else
        {
            hwlog_err("bq25892 get V_temp fail!\n");
        }
        msleep(delay_times);
    }
    if (cnt > 0)
    {
        return (3 * 1000 * sum / cnt);
    }
    else
    {
        hwlog_err("use 0 as default Vvlim!\n");
        return 0;
    }
}



/**********************************************************
*  Function:       bq25892_dump_register
*  Discription:    print the register value in charging process
*  Parameters:   reg_value:string for save register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_dump_register(char *reg_value)
{
    u8 reg[BQ25892_REG_TOTAL_NUM] = {0};
    char buff[26] = {0};
    int i = 0;

    memset(reg_value, 0, CHARGELOG_SIZE);
    snprintf(buff, 26, "%-8.2d", bq25892_get_ilim());
    strncat(reg_value, buff, strlen(buff));
    for(i = 0;i<BQ25892_REG_TOTAL_NUM;i++)
    {
        bq25892_read_byte(i,&reg[i]);
        bq25892_read_byte(i,&reg[i]);
        snprintf(buff, 26, "0x%-8.2x",reg[i]);
        strncat(reg_value, buff, strlen(buff));
    }
    return 0;
}
/**********************************************************
*  Function:       bq25892_get_register_head
*  Discription:    print the register head in charging process
*  Parameters:   reg_head:string for save register head
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_get_register_head(char *reg_head)
{
    char buff[26] = {0};
    int i = 0;

    memset(reg_head, 0, CHARGELOG_SIZE);
    snprintf(buff, 26, "Ibus    ");
    strncat(reg_head, buff, strlen(buff));
    for(i = 0;i<BQ25892_REG_TOTAL_NUM;i++)
    {
        snprintf(buff, 26, "Reg[%d] ",i);
        strncat(reg_head, buff, strlen(buff));
    }
    return 0;
}
/**********************************************************
*  Function:       bq25892_set_batfet_disable
*  Discription:    set the batfet disable in charging process
*  Parameters:   disable:batfet disable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_batfet_disable(int disable)
{
    return bq25892_write_mask(BQ25892_REG_09,BQ25892_REG_09_BATFET_DISABLE_MASK,BQ25892_REG_09_BATFET_DISABLE_SHIFT,disable);
}
/**********************************************************
*  Function:       bq25892_set_watchdog_timer
*  Discription:    set the watchdog timer in charging process
*  Parameters:   value:watchdog timer value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_watchdog_timer(int value)
{
    u8 val = 0;
    u8 dog_time = value;
    if(dog_time >= WATCHDOG_TIMER_160_S)
    {
        val = BQ25892_REG_07_WATCHDOG_160;
    }
    else if(dog_time >= WATCHDOG_TIMER_80_S)
    {
        val = BQ25892_REG_07_WATCHDOG_80;
    }
    else if(dog_time >= WATCHDOG_TIMER_40_S)
    {
        val = BQ25892_REG_07_WATCHDOG_40;
    }
    else
    {
        val = BQ25892_REG_07_WATCHDOG_DIS;
    }
    hwlog_debug(" watch dog timer is %d ,the register value is set %d \n",dog_time,val);
    return bq25892_write_mask(BQ25892_REG_07,BQ25892_REG_07_WATCHDOG_MASK,BQ25892_REG_07_WATCHDOG_SHIFT,val);
}
/**********************************************************
*  Function:       bq25892_set_charger_hiz
*  Discription:    set the charger hiz close watchdog
*  Parameters:   enable:charger in hiz or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_set_charger_hiz(int enable)
{
    int ret = 0;

    if(enable > 0)
    {
        ret |= bq25892_write_mask(BQ25892_REG_00,BQ25892_REG_00_EN_HIZ_MASK,BQ25892_REG_00_EN_HIZ_SHIFT,TRUE);
    }
    else
    {
        ret |= bq25892_write_mask(BQ25892_REG_00,BQ25892_REG_00_EN_HIZ_MASK,BQ25892_REG_00_EN_HIZ_SHIFT,FALSE);
    }
    return ret;
}
/**********************************************************
*  Function:       bq25892_fcp_chip_init
*  Discription:    bq25892 chipIC initialization for high voltage adapter
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_fcp_chip_init(void)
{
    int ret = 0;
    struct bq25892_device_info *di = g_bq25892_dev;

    /*reg init*/
    //bq25892_write_mask(REG0x14,BQ25892_REG_RST_MASK,BQ25892_REG_RST_SHIFT,0x01);
    /* do not init input current 500 ma(REG00) to support lpt without battery  */
    /*02 enable Start 1s Continuous Conversion ,others as default*/
    ret |= bq25892_write_byte(BQ25892_REG_02,0x1D);//adc off
    /*03 WD_RST 1,CHG_CONFIG 1,SYS_MIN 3.5*/
    ret |= bq25892_write_byte(BQ25892_REG_03,0x5A);
    /*04 Fast Charge Current Limit 2048mA*/
    ret |= bq25892_write_byte(BQ25892_REG_04,0x20);
    /*05 Precharge Current Limit 256mA,Termination Current Limit 256mA*/
    ret |= bq25892_write_byte(BQ25892_REG_05,0x33);
    /*06 Charge Voltage Limit 4.4,Battery Precharge to Fast Charge Threshold 3,Battery Recharge 100mV*/
    ret |= bq25892_write_byte(BQ25892_REG_06,0x8e);
    /*07 EN_TERM 1,Watchdog Timer 80s,EN_TIMER 1,Charge Timer 20h,JEITA Low Temperature Current Setting 1*/
    ret |= bq25892_write_byte(BQ25892_REG_07,0x2f);
    /*08 IR compensation voatge clamp = 224mV ,IR compensation resistor setting = 80mohm */
    ret |= bq25892_set_bat_comp(g_bq25892_dev->param_dts.bat_comp);
    ret |= bq25892_set_vclamp(g_bq25892_dev->param_dts.vclamp);
    /*09 FORCE_ICO 0,TMR2X_EN 1,BATFET_DIS 0,JEITA_VSET 0,BATFET_RST_EN 1 */
    ret |= bq25892_write_byte(BQ25892_REG_09,0x44);
    /*boost mode current limit = 500mA,boostv 4.998v*/
    ret |= bq25892_write_byte(BQ25892_REG_0A,0x70);
    /*VINDPM Threshold Setting Method 1,Absolute VINDPM Threshold 4.4v*/
    //ret = bq25892_write_byte(BQ25892_REG_0D,0x92);
    /* set dpm voltage as 4700mv instead of 7600mv because chargerIC cannot reset dpm after watchdog time out*/
    ret = bq25892_set_dpm_voltage(4700);

    gpio_set_value(di->gpio_cd, 0);//enable charging
    return ret;
}
/**********************************************************
*  Function:       bq25892_check_input_dpm_state
*  Discription:    check whether VINDPM or IINDPM
*  Parameters:     NULL
*  return value:   TRUE means VINDPM or IINDPM
*                  FALSE means NoT DPM
**********************************************************/
static int bq25892_check_input_dpm_state(void)
{
    u8 reg = 0;
    int ret = -1;

    ret = bq25892_read_byte(BQ25892_REG_13, &reg);
    if (ret < 0)
    {
        hwlog_err("bq25892_check_input_dpm_state err\n");
        return ret;
    }

    if ((reg & BQ25892_REG_13_VDPM_STAT_MASK) || (reg & BQ25892_REG_13_IDPM_STAT_MASK))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/**********************************************************
*  Function:       bq25892_stop_charge_config
*  Discription:    config chip after stop charging
*  Parameters:     NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_stop_charge_config(void)
{
    int ret=0;
    /* as vindpm of bq25892 won't be reset after watchdog timer out,if vindpm is higher than 5v ,IC will not supply power with USB/AC  */
    ret = bq25892_set_dpm_voltage(CHARGE_VOLTAGE_4520_MV);
    return ret;
}

struct charge_device_ops bq25892_ops = {
    .chip_init = bq25892_chip_init,
    .dev_check = bq25892_device_check,
    .set_input_current = bq25892_set_input_current,
    .set_charge_current = bq25892_set_charge_current,
    .set_terminal_voltage = bq25892_set_terminal_voltage,
    .set_dpm_voltage = bq25892_set_dpm_voltage,
    .set_terminal_current = bq25892_set_terminal_current,
    .set_charge_enable = bq25892_set_charge_enable,
    .set_otg_enable = bq25892_set_otg_enable,
    .set_term_enable = bq25892_set_term_enable,
    .get_charge_state = bq25892_get_charge_state,
    .reset_watchdog_timer = bq25892_reset_watchdog_timer,
    .dump_register = bq25892_dump_register,
    .get_register_head = bq25892_get_register_head,
    .set_watchdog_timer = bq25892_set_watchdog_timer,
    .set_batfet_disable = bq25892_set_batfet_disable,
    .get_ibus = bq25892_get_ilim,
    .get_vbus = bq25892_get_vbus_mv,
    .get_vbat_sys = bq25892_get_vbat_sys,
    .set_covn_start = bq25892_set_covn_start,
    .set_charger_hiz = bq25892_set_charger_hiz,
    .check_input_dpm_state = bq25892_check_input_dpm_state,
    .set_otg_current = bq25892_set_otg_current,
    .stop_charge_config=bq25892_stop_charge_config,
};
/**********************************************************
*  Function:       bq25892_irq_work
*  Discription:    handler for chargerIC fault irq in charging process
*  Parameters:   work:chargerIC fault interrupt workqueue
*  return value:  NULL
**********************************************************/
static void bq25892_irq_work(struct work_struct *work)
{
    struct bq25892_device_info *di = container_of(work,struct bq25892_device_info, irq_work);
    u8 reg = 0,reg1 = 0;

    msleep(100);
    bq25892_read_byte(BQ25892_REG_0B,&reg1);
    bq25892_read_byte(BQ25892_REG_0C,&reg);
    hwlog_info("1st  reg[0xB]:0x%x ,reg[0xC]:0x%0x \n",reg1,reg);
    bq25892_read_byte(BQ25892_REG_0C,&reg);
    hwlog_info("2nd  reg[0xB]:0x%x ,reg[0xC]:0x%0x \n",reg1,reg);

    if(reg & BQ25892_REG_0C_BOOST)
    {
        hwlog_info("CHARGE_FAULT_BOOST_OCP\n");
        atomic_notifier_call_chain(&fault_notifier_list,CHARGE_FAULT_BOOST_OCP, NULL);
    }

    if(di->irq_active== 0)
    {
        di->irq_active = 1;
        enable_irq(di->irq_int);
    }

}
/**********************************************************
*  Function:       bq25892_interrupt
*  Discription:    callback function for chargerIC fault irq in charging process
*  Parameters:   irq:chargerIC fault interrupt
*                      _di:bq25892_device_info
*  return value:  IRQ_HANDLED-sucess or others
**********************************************************/
static irqreturn_t bq25892_interrupt(int irq, void *_di)
{
    struct bq25892_device_info *di = _di;

    hwlog_info("bq25892 interrupt\n");
    if(di->irq_active == 1)
    {
        di->irq_active = 0;
        disable_irq_nosync(di->irq_int);
        schedule_work(&di->irq_work);
    }
    else
    {
        hwlog_info("The irq is not enable,do nothing!\n");
    }
    return IRQ_HANDLED;
}
void prase_dts(struct device_node *np,struct bq25892_device_info *di)
{
    struct device_node *batt_node;
    int ret = 0;
    di->param_dts.bat_comp = 80;
    di->param_dts.vclamp = 224;
    ret = of_property_read_u32(np, "bat_comp", &(di->param_dts.bat_comp));
    if(ret)
    {
        hwlog_err("get bat_comp failed\n");
        return ;
    }
    hwlog_info("prase_dts bat_comp = %d\n",di->param_dts.bat_comp);

    ret = of_property_read_u32(np, "vclamp", &(di->param_dts.vclamp));
    if(ret)
    {
        hwlog_err("get vclamp failed\n");
        return ;
    }
    hwlog_info("prase_dts vclamp = %d\n",di->param_dts.vclamp);

    if (of_property_read_u32(np, "rilim", &rilim))
    {
        hwlog_err("get rilim error,use default one!\n");
    }
    if (of_property_read_u32(np, "adc_channel_iin", &adc_channel_iin))
    {
        hwlog_err("get adc_channel_iin error,use default one!\n");
    }
    if (of_property_read_u32(np, "adc_channel_vbat_sys", &adc_channel_vbat_sys))
    {
        hwlog_err("get adc_channel_vbat_sys error,use default one!\n");
    }

    ret = of_property_read_u32( np,"fcp_support",&(di->param_dts.fcp_support));
    if(ret)
    {
        hwlog_err("get fcp_support failed\n");
        return ;
    }
    if(0 != di->param_dts.fcp_support)
    {
        bq25892_ops.fcp_chip_init = bq25892_fcp_chip_init;
        hwlog_info("support fcp charge \n");
    }

    batt_node = of_find_compatible_node(NULL, NULL, "huawei,hisi_bci_battery");
    if (batt_node) {
        if (of_property_read_u32(batt_node, "battery_board_type",&is_board_type)){
            hwlog_err("get battery_board_type fail!\n");
            is_board_type = BAT_BOARD_ASIC;
        }
    } else {

        hwlog_err("get hisi_bci_battery fail!\n");
		is_board_type = BAT_BOARD_ASIC;
	}
    return ;
}

/**********************************************************
*  Function:       bq25892_probe
*  Discription:    bq25892 module probe
*  Parameters:   client:i2c_client
*                      id:i2c_device_id
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
    int ret = 0;
    struct bq25892_device_info *di = NULL;
    struct charge_device_ops *ops = NULL;
    struct device_node *np = NULL;
    struct class *power_class = NULL;

    di = devm_kzalloc(&client->dev,sizeof(*di), GFP_KERNEL);
    if (!di)
    {
        hwlog_err("bq25892_device_info is NULL!\n");
        return -ENOMEM;
    }
    g_bq25892_dev = di;
    di->dev = &client->dev;
    np = di->dev->of_node;
    di->client = client;
    i2c_set_clientdata(client, di);
    prase_dts(np,di);
    INIT_WORK(&di->irq_work, bq25892_irq_work);
    di->gpio_cd = of_get_named_gpio(np,"gpio_cd",0);
    if(!gpio_is_valid(di->gpio_cd))
    {
        hwlog_err("gpio_cd is not valid\n");
        ret = -EINVAL;
        goto bq25892_fail_0;
    }
    di->gpio_int = of_get_named_gpio(np,"gpio_int",0);
    if(!gpio_is_valid(di->gpio_int))
    {
        hwlog_err("gpio_int is not valid\n");
        ret = -EINVAL;
        goto bq25892_fail_0;
    }
    /*set gpio to control CD pin to disable/enable bq25892 IC*/
    ret = gpio_request(di->gpio_cd, "charger_cd");
    if (ret)
    {
          hwlog_err("could not request gpio_cd\n");
          ret = -ENOMEM;
          goto bq25892_fail_0;
    }
    gpio_direction_output(di->gpio_cd, 0);
    ret = gpio_request(di->gpio_int,"charger_int");
    if(ret)
    {
        hwlog_err("could not request gpio_int\n");
        goto bq25892_fail_1;
    }
    gpio_direction_input(di->gpio_int);
    di->irq_int = gpio_to_irq(di->gpio_int);
    if(di->irq_int < 0)
    {
        hwlog_err("could not map gpio_int to irq\n");
        goto bq25892_fail_2;
    }
    if ( BAT_BOARD_UDP != is_board_type) {

    ret = request_irq(di->irq_int,bq25892_interrupt,IRQF_TRIGGER_FALLING,"charger_int_irq",di);
    if(ret)
    {
        hwlog_err("could not request irq_int\n");
        di->irq_int = -1;
        goto bq25892_fail_3;
    }
    di->irq_active = 1;
    }
    ops = &bq25892_ops;
    ret = charge_ops_register(ops);
    if(ret)
    {
        hwlog_err("register charge ops failed!\n");
        goto bq25892_fail_3;
    }
    ret = bq25892_sysfs_create_group(di);
    if(ret)
    {
        hwlog_err("create sysfs entries failed!\n");
        goto bq25892_fail_4;
    }
    power_class = hw_power_get_class();
    if(power_class)
    {
        if(charge_dev == NULL)
            charge_dev = device_create(power_class, NULL, 0, NULL,"charger");
        ret = sysfs_create_link(&charge_dev->kobj, &di->dev->kobj, "bq25892");
        if(ret)
            hwlog_err("create link to bq25892 fail.\n");
    }

    hwlog_info("bq25892 probe ok!\n");
    return 0;

bq25892_fail_4:
    bq25892_sysfs_remove_group(di);
bq25892_fail_3:
    free_irq(di->irq_int, di);
bq25892_fail_2:
    gpio_free(di->gpio_int);
bq25892_fail_1:
    gpio_free(di->gpio_cd);
bq25892_fail_0:
    g_bq25892_dev = NULL;
    np = NULL;

    return ret;
}
/**********************************************************
*  Function:       bq25892_remove
*  Discription:    bq25892 module remove
*  Parameters:   client:i2c_client
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq25892_remove(struct i2c_client *client)
{
    struct bq25892_device_info *di = i2c_get_clientdata(client);

    bq25892_sysfs_remove_group(di);

    gpio_set_value(di->gpio_cd, 1);
    if(di->gpio_cd)
    {
        gpio_free(di->gpio_cd);
    }
    if(di->irq_int)
    {
        free_irq(di->irq_int,di);
    }
    if(di->gpio_int)
    {
        gpio_free(di->gpio_int);
    }
    return 0;
}

#ifdef CONFIG_LLT_TEST
struct bq25892_static_ops bq25892_llt_ops = {
    .bq25892_write_mask = bq25892_write_mask,
    .bq25892_write_byte = bq25892_write_byte,
    .bq25892_read_byte = bq25892_read_byte,
    .bq25892_set_bat_comp = bq25892_set_bat_comp,
    .bq25892_set_vclamp = bq25892_set_vclamp,
    .bq25892_set_input_current = bq25892_set_input_current,
    .bq25892_set_charge_current = bq25892_set_charge_current,
    .bq25892_set_terminal_voltage = bq25892_set_terminal_voltage,
    .bq25892_set_dpm_voltage = bq25892_set_dpm_voltage,
    .bq25892_set_terminal_current = bq25892_set_terminal_current,
    .bq25892_set_otg_current = bq25892_set_otg_current,
    .bq25892_get_vbus_mv = bq25892_get_vbus_mv,
    .bq25892_set_watchdog_timer = bq25892_set_watchdog_timer,
    .bq25892_set_charger_hiz = bq25892_set_charger_hiz,
};
#endif

MODULE_DEVICE_TABLE(i2c, bq25892);
static struct of_device_id bq25892_of_match[] =
{
    {
	.compatible = "huawei,bq25892_charger",
	.data = NULL,
    },
    {
    },
};

static const struct i2c_device_id bq25892_i2c_id[] = {{"bq25892_charger",0},{}};

static struct i2c_driver bq25892_driver = {
    .probe  = bq25892_probe,
    .remove	= bq25892_remove,
    .id_table    = bq25892_i2c_id,
    .driver = {
        .owner = THIS_MODULE,
        .name    = "bq25892_charger",
        .of_match_table = of_match_ptr(bq25892_of_match),
    },
};
/**********************************************************
*  Function:       bq25892_init
*  Discription:    bq25892 module initialization
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int __init bq25892_init(void)
{
    int ret =0;

    ret =  i2c_add_driver(&bq25892_driver);
    if(ret)
        hwlog_err("%s: i2c_add_driver error!!!\n", __func__);

    return ret;
}
/**********************************************************
*  Function:       bq25892_exit
*  Discription:    bq25892 module exit
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void __exit bq25892_exit(void)
{
    i2c_del_driver(&bq25892_driver);
}
module_init(bq25892_init);
module_exit(bq25892_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("bq25892 charger module driver");
MODULE_AUTHOR("HW Inc");
