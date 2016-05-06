/*
 * drivers/power/bq2429x_charger.c
 *
 * bq2429x/1/2/3/4 charging driver
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
#include <bq2429x_charger.h>

#define HWLOG_TAG bq2429x_charger
HWLOG_REGIST();

struct bq2429x_device_info *g_bq2429x_dev = NULL;
/**********************************************************
*  Function:       params_to_reg
*  Discription:    turn the setting parameter to register value
*  Parameters:   const int tbl[], int tbl_size, int val
*  return value:  register value
**********************************************************/
static int params_to_reg(const int tbl[], int tbl_size, int val)
{
    int i;

    for (i = 1; i < tbl_size; i++)
    {
        if (val < tbl[i])
            return i - 1;
    }
    return (tbl_size -1);
}
/**********************************************************
*  Function:       bq2429x_write_block
*  Discription:    register write block interface
*  Parameters:   di:bq2429x_device_info
*                      value:register value
*                      reg:register name
*                      num_bytes:bytes number
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_write_block(struct bq2429x_device_info *di, u8 *value,
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
*  Function:       bq2429x_read_block
*  Discription:    register read block interface
*  Parameters:   di:bq2429x_device_info
*                      value:register value
*                      reg:register name
*                      num_bytes:bytes number
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_read_block(struct bq2429x_device_info *di, u8 *value,
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
*  Function:       bq2429x_write_byte
*  Discription:    register write byte interface
*  Parameters:   reg:register name
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_write_byte(u8 reg,u8 value)
{
    struct bq2429x_device_info *di = g_bq2429x_dev;
    /* 2 bytes offset 1 contains the data offset 0 is used by i2c_write */
    u8 temp_buffer[2] = { 0 };

    /* offset 1 contains the data */
    temp_buffer[1] = value;
    return bq2429x_write_block(di, temp_buffer, reg, 1);
}
/**********************************************************
*  Function:       bq2429x_read_byte
*  Discription:    register read byte interface
*  Parameters:   reg:register name
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_read_byte(u8 reg, u8 *value)
{
    struct bq2429x_device_info *di = g_bq2429x_dev;

    return bq2429x_read_block(di, value, reg, 1);
}
/**********************************************************
*  Function:       bq2429x_write_mask
*  Discription:    register write mask interface
*  Parameters:   reg:register name
*                      MASK:mask value of the function
*                      SHIFT:shift number of the function
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_write_mask(u8 reg, u8 MASK, u8 SHIFT, u8 value)
{
    int ret = 0;
    u8 val = 0;

    ret = bq2429x_read_byte(reg,&val);
    if(ret < 0)
        return ret;

    val &= ~MASK;
    val |= ((value << SHIFT) & MASK);

    ret = bq2429x_write_byte(reg,val);

    return ret;
}
/**********************************************************
*  Function:       bq2429x_read_mask
*  Discription:    register read mask interface
*  Parameters:   reg:register name
*                      MASK:mask value of the function
*                      SHIFT:shift number of the function
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_read_mask(u8 reg, u8 MASK, u8 SHIFT, u8 *value)
{
    int ret = 0;
    u8 val = 0;

    ret = bq2429x_read_byte(reg,&val);
    if(ret < 0)
        return ret;
    val &= MASK;
    val >>= SHIFT;
    *value = val;

    return 0;
}

#ifdef CONFIG_SYSFS
/*
 * There are a numerous options that are configurable on the bq2429x
 * that go well beyond what the power_supply properties provide access to.
 * Provide sysfs access to them so they can be examined and possibly modified
 * on the fly.
 */

#define BQ2429X_SYSFS_FIELD(_name, r, f, m, store)                  \
{                                                   \
    .attr = __ATTR(_name, m, bq2429x_sysfs_show, store),    \
    .reg = BQ2429X_REG_##r,                      \
    .mask = BQ2429X_REG_##r##_##f##_MASK,                       \
    .shift = BQ2429X_REG_##r##_##f##_SHIFT,                     \
}

#define BQ2429X_SYSFS_FIELD_RW(_name, r, f)                     \
        BQ2429X_SYSFS_FIELD(_name, r, f, S_IWUSR | S_IRUGO, \
                bq2429x_sysfs_store)

#define BQ2429X_SYSFS_FIELD_RO(_name, r, f)                         \
        BQ2429X_SYSFS_FIELD(_name, r, f, S_IRUGO, NULL)

static ssize_t bq2429x_sysfs_show(struct device *dev,
                                  struct device_attribute *attr, char *buf);
static ssize_t bq2429x_sysfs_store(struct device *dev,
                                   struct device_attribute *attr, const char *buf, size_t count);

struct bq2429x_sysfs_field_info
{
    struct device_attribute	attr;
    u8  reg;
    u8  mask;
    u8  shift;
};

/* On i386 ptrace-abi.h defines SS that breaks the macro calls below. */
#undef SS

static struct bq2429x_sysfs_field_info bq2429x_sysfs_field_tbl[] =
{
    /* sysfs name reg field in reg */
    BQ2429X_SYSFS_FIELD_RW(en_hiz,      ISC,        EN_HIZ),
    BQ2429X_SYSFS_FIELD_RW(vindpm,      ISC,        VINDPM),
    BQ2429X_SYSFS_FIELD_RW(iinlim,      ISC,        IINLIM),
    BQ2429X_SYSFS_FIELD_RW(chg_config,      POC,        CHG_CONFIG),
    BQ2429X_SYSFS_FIELD_RW(sys_min,     POC,        SYS_MIN),
    BQ2429X_SYSFS_FIELD_RW(boost_lim,       POC,        BOOST_LIM),
    BQ2429X_SYSFS_FIELD_RW(ichg,        CCC,        ICHG),
    BQ2429X_SYSFS_FIELD_RW(bcold,        CCC,        BCOLD),
    BQ2429X_SYSFS_FIELD_RW(force_20_pct,        CCC,        FORCE_20PCT),
    BQ2429X_SYSFS_FIELD_RW(iprechg,     PCTCC,      IPRECHG),
    BQ2429X_SYSFS_FIELD_RW(iterm,       PCTCC,      ITERM),
    BQ2429X_SYSFS_FIELD_RW(vreg,        CVC,        VREG),
    BQ2429X_SYSFS_FIELD_RW(batlowv,     CVC,        BATLOWV),
    BQ2429X_SYSFS_FIELD_RW(vrechg,      CVC,        VRECHG),
    BQ2429X_SYSFS_FIELD_RW(en_term,     CTTC,       EN_TERM),
    BQ2429X_SYSFS_FIELD_RW(term_stat,       CTTC,       TERM_STAT),
    BQ2429X_SYSFS_FIELD_RO(watchdog,        CTTC,       WATCHDOG),
    BQ2429X_SYSFS_FIELD_RW(en_timer,        CTTC,       EN_TIMER),
    BQ2429X_SYSFS_FIELD_RW(chg_timer,       CTTC,       CHG_TIMER),
    BQ2429X_SYSFS_FIELD_RW(jeta_iset,       CTTC,       JEITA_ISET),
    BQ2429X_SYSFS_FIELD_RW(boostv,        BVTRC,      BOOSTV),
    BQ2429X_SYSFS_FIELD_RW(bhot,      BVTRC,      BHOT),
    BQ2429X_SYSFS_FIELD_RW(treg,        BVTRC,      TREG),
    BQ2429X_SYSFS_FIELD_RW(dpdm_en,     MOC,        DPDM_EN),
    BQ2429X_SYSFS_FIELD_RW(tmr2x_en,        MOC,        TMR2X_EN),
    BQ2429X_SYSFS_FIELD_RW(batfet_disable,      MOC,        BATFET_DISABLE),
    BQ2429X_SYSFS_FIELD_RW(jeita_vset,      MOC,        JEITA_VSET),
    BQ2429X_SYSFS_FIELD_RO(int_mask,        MOC,        INT_MASK),
    BQ2429X_SYSFS_FIELD_RO(vbus_stat,       SS,     VBUS_STAT),
    BQ2429X_SYSFS_FIELD_RO(chrg_stat,       SS,     CHRG_STAT),
    BQ2429X_SYSFS_FIELD_RO(dpm_stat,        SS,     DPM_STAT),
    BQ2429X_SYSFS_FIELD_RO(pg_stat,     SS,     PG_STAT),
    BQ2429X_SYSFS_FIELD_RO(therm_stat,      SS,     THERM_STAT),
    BQ2429X_SYSFS_FIELD_RO(vsys_stat,       SS,     VSYS_STAT),
    BQ2429X_SYSFS_FIELD_RO(watchdog_fault,      F,      WATCHDOG_FAULT),
    BQ2429X_SYSFS_FIELD_RO(boost_fault,     F,      BOOST_FAULT),
    BQ2429X_SYSFS_FIELD_RO(chrg_fault,      F,      CHRG_FAULT),
    BQ2429X_SYSFS_FIELD_RO(bat_fault,       F,      BAT_FAULT),
    BQ2429X_SYSFS_FIELD_RO(ntc_fault,        F,     NTC_FAULT),
    BQ2429X_SYSFS_FIELD_RO(pn,      VPRS,       PN),
    BQ2429X_SYSFS_FIELD_RO(rev,     VPRS,       REV),
};

static struct attribute *
bq2429x_sysfs_attrs[ARRAY_SIZE(bq2429x_sysfs_field_tbl) + 1];

static const struct attribute_group bq2429x_sysfs_attr_group =
{
    .attrs = bq2429x_sysfs_attrs,
};
/**********************************************************
*  Function:       bq2429x_sysfs_init_attrs
*  Discription:    initialize bq2429x_sysfs_attrs[] for bq2429x attribute
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void bq2429x_sysfs_init_attrs(void)
{
    int i, limit = ARRAY_SIZE(bq2429x_sysfs_field_tbl);

    for (i = 0; i < limit; i++)
        bq2429x_sysfs_attrs[i] = &bq2429x_sysfs_field_tbl[i].attr.attr;

    bq2429x_sysfs_attrs[limit] = NULL; /* Has additional entry for this */
}
/**********************************************************
*  Function:       bq2429x_sysfs_field_lookup
*  Discription:    get the current device_attribute from bq2429x_sysfs_field_tbl by attr's name
*  Parameters:   name:evice attribute name
*  return value:  bq2429x_sysfs_field_tbl[]
**********************************************************/
static struct bq2429x_sysfs_field_info *bq2429x_sysfs_field_lookup(const char *name)
{
    int i, limit = ARRAY_SIZE(bq2429x_sysfs_field_tbl);

    for (i = 0; i < limit; i++)
        if (!strcmp(name, bq2429x_sysfs_field_tbl[i].attr.attr.name))
            break;

    if (i >= limit)
        return NULL;

    return &bq2429x_sysfs_field_tbl[i];
}
/**********************************************************
*  Function:       bq2429x_sysfs_show
*  Discription:    show the value for all bq2429x device's node
*  Parameters:   dev:device
*                      attr:device_attribute
*                      buf:string of node value
*  return value:  0-sucess or others-fail
**********************************************************/
static ssize_t bq2429x_sysfs_show(struct device *dev,
                                  struct device_attribute *attr, char *buf)
{
    struct bq2429x_sysfs_field_info *info;
    int ret;
    u8 v;

    info = bq2429x_sysfs_field_lookup(attr->attr.name);
    if (!info)
        return -EINVAL;

    ret = bq2429x_read_mask(info->reg, info->mask, info->shift, &v);
    if (ret)
        return ret;

    return scnprintf(buf, PAGE_SIZE, "%hhx\n", v);
}
/**********************************************************
*  Function:       bq2429x_sysfs_store
*  Discription:    set the value for all bq2429x device's node
*  Parameters:   dev:device
*                      attr:device_attribute
*                      buf:string of node value
*                      count:unused
*  return value:  0-sucess or others-fail
**********************************************************/
static ssize_t bq2429x_sysfs_store(struct device *dev,
                                   struct device_attribute *attr, const char *buf, size_t count)
{
    struct bq2429x_sysfs_field_info *info;
    int ret;
    u8 v;

    info = bq2429x_sysfs_field_lookup(attr->attr.name);
    if (!info)
        return -EINVAL;

    ret = kstrtou8(buf, 0, &v);
    if (ret < 0)
        return ret;

    ret = bq2429x_write_mask(info->reg, info->mask, info->shift, v);
    if (ret)
        return ret;

    return count;
}
/**********************************************************
*  Function:       bq2429x_sysfs_create_group
*  Discription:    create the bq2429x device sysfs group
*  Parameters:   di:bq2429x_device_info
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_sysfs_create_group(struct bq2429x_device_info *di)
{
    bq2429x_sysfs_init_attrs();

    return sysfs_create_group(&di->dev->kobj,&bq2429x_sysfs_attr_group);
}
/**********************************************************
*  Function:       charge_sysfs_remove_group
*  Discription:    remove the bq2429x device sysfs group
*  Parameters:   di:bq2429x_device_info
*  return value:  NULL
**********************************************************/
static void bq2429x_sysfs_remove_group(struct bq2429x_device_info *di)
{
    sysfs_remove_group(&di->dev->kobj, &bq2429x_sysfs_attr_group);
}
#else
static int bq2429x_sysfs_create_group(struct bq2429x_device_info *di)
{
    return 0;
}
static inline void bq2429x_sysfs_remove_group(struct bq2429x_device_info *di) {}
#endif

/**********************************************************
*  Function:       bq2429x_check_ic_type
*  Discription:    bq2429x chipIC config
*  Parameters:   NULL
*  return value:  1-bq2429x or others no bq2419x
**********************************************************/
static int bq2429x_check_ic_type(void)
{
    u8 reg = 0;
    int ret = 0;

    ret = bq2429x_read_byte(BQ2429X_REG_VPRS,&reg);
    if(ret < 0)
    {
        hwlog_err("read charger version erro !\n");
        return ret;
    }

    if((0 == (reg & BQ2429X_REG_VPRS_REV_MASK))
       && (reg & BQ2429X_REG_VPRS_PN_MASK))
    {
        return BQ2429X_REG_VPRS_PN_24296;
    }

    return 0;
}
static int bq2429x_device_check()
{
    if(BQ2429X_REG_VPRS_PN_24296 == bq2429x_check_ic_type())
    {
        hwlog_info("bq2429x is good.\n");
        return CHARGE_IC_GOOD;
    }
    else
    {
        hwlog_err("bq2429x is bad.\n");
        return CHARGE_IC_BAD;
    }
}
/**********************************************************
*  Function:       bq2429x_chip_init
*  Discription:    bq2429x chipIC initialization
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_chip_init(void)
{
    int ret = 0;
    struct bq2429x_device_info *di = g_bq2429x_dev;
    
    /*boost mode current limit = 1000mA*/
    ret = bq2429x_write_byte(BQ2429X_REG_POC,0x1a);
    /*I2C watchdog timer setting = 80s*/
    /*fast charge timer setting = 12h*/
    ret |= bq2429x_write_byte(BQ2429X_REG_CTTC,0x2d);
    
    if (BQ2429X_REG_VPRS_PN_24296 != bq2429x_check_ic_type())
    {
        /*IR compensation voatge clamp = 48mV*/
        /*IR compensation resistor setting = 40mohm*/
        ret |= bq2429x_write_byte(BQ2429X_REG_BVTRC,0x8f); 
    }

    gpio_set_value(di->gpio_cd, 0);//enable charging

    return ret;
}
/**********************************************************
*  Function:       bq2429x_set_input_current
*  Discription:    set the input current in charging process
*  Parameters:   value:input current value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_set_input_current(int value)
{
    int val = 0;
    int array_size = ARRAY_SIZE(bq2429x_iin_values);

    if(value > bq2429x_iin_values[array_size-1])
    {
        return bq2429x_iin_values[array_size-1];
    }
    else if(value < bq2429x_iin_values[0])
    {
        return bq2429x_iin_values[0];
    }

    val = params_to_reg(bq2429x_iin_values,array_size,value);
    return bq2429x_write_mask(BQ2429X_REG_ISC,
                              BQ2429X_REG_ISC_IINLIM_MASK,
                              BQ2429X_REG_ISC_IINLIM_SHIFT,
                              val);
}
/**********************************************************
*  Function:       bq2429x_set_charge_current
*  Discription:    set the charge current in charging process
*  Parameters:   value:charge current value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_set_charge_current(int value)
{
    int ret = 0;
    int val = 0;
    int force_20pct_en = 0;
    int array_size = ARRAY_SIZE(bq2429x_ichg_values);

    if(value > bq2429x_ichg_values[array_size-1])
    {
        return bq2429x_ichg_values[array_size-1];
    }
    /* 1.If currentmA is below ICHG_512, we can set the ICHG to 5*currentmA and
         set the FORCE_20PCT in REG02 to make the true current 20% of the ICHG
        2.To slove the OCP BUG of bq2429x, we need set the ICHG(lower than 1024mA)
         to 5*currentmA and set the FORCE_20PCT in REG02.*/
    else if(value < 1024)
    {
        value *= 5;
        force_20pct_en = 1;
    }
    if(value < bq2429x_ichg_values[0])
    {
        value = bq2429x_ichg_values[0];
    }
    ret = bq2429x_write_mask(BQ2429X_REG_CCC,
                             BQ2429X_REG_CCC_FORCE_20PCT_MASK,
                             BQ2429X_REG_CCC_FORCE_20PCT_SHIFT,
                             force_20pct_en);
    if(ret < 0)
        return ret;

    val = params_to_reg(bq2429x_ichg_values,array_size, value);
    return bq2429x_write_mask(BQ2429X_REG_CCC,
                              BQ2429X_REG_CCC_ICHG_MASK,
                              BQ2429X_REG_CCC_ICHG_SHIFT,
                              val);
}
/**********************************************************
*  Function:       bq2429x_set_terminal_voltage
*  Discription:    set the terminal voltage in charging process
*  Parameters:   value:terminal voltage value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_set_terminal_voltage(int value)
{
    int val = 0;
    int array_size = ARRAY_SIZE(bq2429x_vreg_values);

    if(value > bq2429x_vreg_values[array_size-1])
    {
        return bq2429x_vreg_values[array_size-1];
    }
    else if(value < bq2429x_vreg_values[0])
    {
        return bq2429x_vreg_values[0];
    }

    val = params_to_reg(bq2429x_vreg_values, array_size, value);
    return bq2429x_write_mask(BQ2429X_REG_CVC,
                              BQ2429X_REG_CVC_VREG_MASK,
                              BQ2429X_REG_CVC_VREG_SHIFT,
                              val);
}
/**********************************************************
*  Function:       bq2429x_set_dpm_voltage
*  Discription:    set the dpm voltage in charging process
*  Parameters:   value:dpm voltage value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_set_dpm_voltage(int value)
{
    int val = 0;
    int array_size = ARRAY_SIZE(bq2429x_vindpm_values);

    if(value > bq2429x_vindpm_values[array_size-1])
    {
        return bq2429x_vindpm_values[array_size-1];
    }
    else if(value < bq2429x_vindpm_values[0])
    {
        return bq2429x_vindpm_values[0];
    }

    val = params_to_reg(bq2429x_vindpm_values,array_size, value);
    return bq2429x_write_mask(BQ2429X_REG_ISC,
                              BQ2429X_REG_ISC_VINDPM_MASK,
                              BQ2429X_REG_ISC_VINDPM_SHIFT,
                              val);
}
/**********************************************************
*  Function:       bq2429x_set_terminal_current
*  Discription:    set the terminal current in charging process
*  Parameters:   value:terminal current value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_set_terminal_current(int value)
{
    int val = 0;
    int array_size = ARRAY_SIZE(bq2429x_iterm_values);

    if(value > bq2429x_iterm_values[array_size-1])
    {
        return bq2429x_iterm_values[array_size-1];
    }
    else if(value < bq2429x_iterm_values[0])
    {
        return bq2429x_iterm_values[0];
    }

    val = params_to_reg(bq2429x_iterm_values,array_size, value);
    return bq2429x_write_mask(BQ2429X_REG_PCTCC,
                              BQ2429X_REG_PCTCC_ITERM_MASK,
                              BQ2429X_REG_PCTCC_ITERM_SHIFT,
                              val);
}
/**********************************************************
*  Function:       bq2429x_set_charge_enable
*  Discription:    set the charge enable in charging process
*  Parameters:   enable:charge enable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_set_charge_enable(int enable)
{
    struct bq2429x_device_info *di = g_bq2429x_dev;

    gpio_set_value(di->gpio_cd, !enable);
    return bq2429x_write_mask(BQ2429X_REG_POC,
                              BQ2429X_REG_POC_CHG_CONFIG_MASK,
                              BQ2429X_REG_POC_CHG_CONFIG_SHIFT,
                              enable);
}
/**********************************************************
*  Function:       bq2429x_set_otg_enable
*  Discription:    set the otg mode enable in charging process
*  Parameters:   enable:otg mode  enable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_set_otg_enable(int enable)
{
    int val = 0;
    struct bq2429x_device_info *di = g_bq2429x_dev;

    gpio_set_value(di->gpio_cd, !enable);
    val = enable << 1;

    /*NOTICE:
       why enable irq when entry to OTG mode only?
       because we care VBUS overloaded OCP or OVP's interrupt in boost mode
    */
    if((!di->irq_active)&&(enable))
    {
        di->irq_active = 1;
        enable_irq(di->irq_int);
    }
    else if((di->irq_active)&&(!enable))
    {
        di->irq_active = 0;
        disable_irq(di->irq_int);
    }
    else
    {
        //do nothing!!
    }

    return bq2429x_write_mask(BQ2429X_REG_POC,
                              BQ2429X_REG_POC_CHG_CONFIG_MASK,
                              BQ2429X_REG_POC_CHG_CONFIG_SHIFT,
                              val);
}

/**********************************************************
*  Function:       bq2429x_reset_otg
*  Discription:    set the otg mode disable and enable
*  Parameters:   void
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_reset_otg(void)
{
    int val = 0;
    int ret = 0;
    struct bq2429x_device_info *di = g_bq2429x_dev;

    gpio_set_value(di->gpio_cd, !(FALSE));
    val = (FALSE) << 1;
    ret = bq2429x_write_mask(BQ2429X_REG_POC,
                              BQ2429X_REG_POC_CHG_CONFIG_MASK,
                              BQ2429X_REG_POC_CHG_CONFIG_SHIFT,
                              val);
    if(ret)
    {
       hwlog_info("bq2429x_reset_otg false fail \n");
       return ret;
    }

    gpio_set_value(di->gpio_cd, !(TRUE));
    val = (TRUE) << 1;
    ret = bq2429x_write_mask(BQ2429X_REG_POC,
                              BQ2429X_REG_POC_CHG_CONFIG_MASK,
                              BQ2429X_REG_POC_CHG_CONFIG_SHIFT,
                              val);
    if(ret)
    {
       hwlog_info("bq2429x_reset_otg true fail \n");
       return ret;
    }
    return 0;
}

/**********************************************************
*  Function:       bq2429x_set_term_enable
*  Discription:    set the terminal enable in charging process
*  Parameters:   enable:terminal enable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_set_term_enable(int enable)
{
    return bq2429x_write_mask(BQ2429X_REG_CTTC,
                              BQ2429X_REG_CTTC_EN_TERM_MASK,
                              BQ2429X_REG_CTTC_EN_TERM_SHIFT,
                              enable);
}
/**********************************************************
*  Function:       bq2429x_get_charge_state
*  Discription:    get the charge states in charging process
*  Parameters:   state:charge states
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_get_charge_state(unsigned int *state)
{
    u8 reg = 0;
    int ret = 0;

    ret = bq2429x_read_byte(BQ2429X_REG_SS,&reg);
    if((reg & BQ2429X_REG_SS_PG) == BQ2429X_REG_SS_NOTPG)
    {
        *state |= CHAGRE_STATE_NOT_PG;
    }
    if((reg & BQ2429X_REG_SS_DPM) == BQ2429X_REG_SS_DPM)
    {
        *state |= CHAGRE_STATE_INPUT_DPM;
    }
    if((reg & BQ2429X_REG_SS_CHRGDONE) == BQ2429X_REG_SS_CHRGDONE)
    {
        *state |= CHAGRE_STATE_CHRG_DONE;
    }
    ret |= bq2429x_read_byte(BQ2429X_REG_F,&reg);
    ret |= bq2429x_read_byte(BQ2429X_REG_F,&reg);
    if((reg & BQ2429X_REG_F_WDT_TIMEOUT) == BQ2429X_REG_F_WDT_TIMEOUT)
    {
        *state |= CHAGRE_STATE_WDT_FAULT;
    }
    if((reg & BQ2429X_REG_F_VBUS_OVP) == BQ2429X_REG_F_VBUS_OVP)
    {
        *state |= CHAGRE_STATE_VBUS_OVP;
    }
    if((reg & BQ2429X_REG_F_BATT_OVP) == BQ2429X_REG_F_BATT_OVP)
    {
        *state |= CHAGRE_STATE_BATT_OVP;
    }

    return ret;
}
/**********************************************************
*  Function:       bq2429x_reset_watchdog_timer
*  Discription:    reset watchdog timer in charging process
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_reset_watchdog_timer(void)
{
    return bq2429x_write_mask(BQ2429X_REG_POC,
                              BQ2429X_REG_POC_WDT_RESET_MASK,
                              BQ2429X_REG_POC_WDT_RESET_SHIFT,
                              0x01);
}
/**********************************************************
*  Function:       bq2429x_check_charger_plugged
*  Discription:    check whether USB or adaptor is plugged
*  Parameters:     NULL
*  return value:   TRUE means USB or adaptor plugged
*                  FALSE means USB or adaptor not plugged
**********************************************************/
static int bq2429x_check_charger_plugged(void)
{
    u8 reg = 0;
    int ret = 0;

    ret = bq2429x_read_byte(BQ2429X_REG_SS, &reg);
    if (BQ2429X_REG_SS_VBUS_PLUGGED == (reg & BQ2429X_REG_SS_VBUS_STAT_MASK))
    {
        return TRUE;
    }
    return FALSE;
}

/**********************************************************
*  Function:       bq2429x_check_input_dpm_state
*  Discription:    check whether VINDPM or IINDPM
*  Parameters:     NULL
*  return value:   TRUE means VINDPM or IINDPM
*                  FALSE means NoT DPM
**********************************************************/
static int bq2429x_check_input_dpm_state(void)
{
    u8 reg = 0;
    int ret = -1;

    ret = bq2429x_read_byte(BQ2429X_REG_SS, &reg);
    if (ret < 0)
    {
        hwlog_err("bq2429x_check_input_dpm_state err\n");
        return ret;
    }

    if (reg & BQ2429X_REG_SS_DPM_STAT_MASK)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**********************************************************
*  Function:       bq2429x_dump_register
*  Discription:    print the register value in charging process
*  Parameters:   reg_value:string for save register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_dump_register(char *reg_value)
{
    u8 reg[BQ2429X_REG_NUM] = {0};
    char buff[26] = {0};
    int i = 0;

    memset(reg_value, 0, CHARGELOG_SIZE);
    for(i = 0; i<BQ2429X_REG_NUM; i++)
    {
        bq2429x_read_byte(i,&reg[i]);
        bq2429x_read_byte(i,&reg[i]);
        sprintf(buff,"0x%-8.2x",reg[i]);
        strncat(reg_value, buff, strlen(buff));
    }
    return 0;
}
/**********************************************************
*  Function:       bq2429x_dump_register
*  Discription:    print the register head in charging process
*  Parameters:   reg_head:string for save register head
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_get_register_head(char *reg_head)
{
    char buff[26] = {0};
    int i = 0;

    memset(reg_head, 0, CHARGELOG_SIZE);
    for(i = 0; i<BQ2429X_REG_NUM; i++)
    {
        sprintf(buff,"Reg[%d]    ",i);
        strncat(reg_head, buff, strlen(buff));
    }
    return 0;
}
/**********************************************************
*  Function:       bq2429x_set_batfet_disable
*  Discription:    set the batfet disable in charging process
*  Parameters:   disable:batfet disable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_set_batfet_disable(int disable)
{
    return bq2429x_write_mask(BQ2429X_REG_MOC,
                              BQ2429X_REG_MOC_BATFET_DISABLE_MASK,
                              BQ2429X_REG_MOC_BATFET_DISABLE_SHIFT,
                              disable);
}
/**********************************************************
*  Function:       bq2429x_set_watchdog_timer
*  Discription:    set the watchdog timer in charging process
*  Parameters:   value:watchdog timer value
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_set_watchdog_timer(int value)
{
    u8 val = 0;
    int array_size = ARRAY_SIZE(bq2429x_watchdog_values);

    if(value > bq2429x_watchdog_values[array_size-1])
    {
        return bq2429x_watchdog_values[array_size-1];
    }
    else if(value < bq2429x_watchdog_values[0])
    {
        return bq2429x_watchdog_values[0];
    }

    val = params_to_reg(bq2429x_watchdog_values,array_size,value);
    return bq2429x_write_mask(BQ2429X_REG_CTTC,
                              BQ2429X_REG_CTTC_WATCHDOG_MASK,
                              BQ2429X_REG_CTTC_WATCHDOG_SHIFT,
                              val);
}

/**********************************************************
*  Function:       bq2429x_set_charger_hiz
*  Discription:    set the charger hiz close watchdog
*  Parameters:   enable:charger in hiz or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_set_charger_hiz(int enable)
{
    int ret = 0;

    if(enable > 0)
    {
        ret |= bq2429x_write_mask(BQ2429X_REG_ISC,
                                                   BQ2429X_REG_ISC_EN_HIZ_MASK,
                                                   BQ2429X_REG_ISC_EN_HIZ_SHIFT,TRUE);
    }
    else
    {
        ret |= bq2429x_write_mask(BQ2429X_REG_ISC,
                                                   BQ2429X_REG_ISC_EN_HIZ_MASK,
                                                   BQ2429X_REG_ISC_EN_HIZ_SHIFT,FALSE);
    }
    return ret;
}

struct charge_device_ops bq2429x_ops =
{
    .chip_init = bq2429x_chip_init,
    .dev_check = bq2429x_device_check,
    .set_input_current = bq2429x_set_input_current,
    .set_charge_current = bq2429x_set_charge_current,
    .set_terminal_voltage = bq2429x_set_terminal_voltage,
    .set_dpm_voltage = bq2429x_set_dpm_voltage,
    .set_terminal_current = bq2429x_set_terminal_current,
    .set_charge_enable = bq2429x_set_charge_enable,
    .set_otg_enable = bq2429x_set_otg_enable,
    .set_term_enable = bq2429x_set_term_enable,
    .get_charge_state = bq2429x_get_charge_state,
    .reset_watchdog_timer = bq2429x_reset_watchdog_timer,
    .dump_register = bq2429x_dump_register,
    .get_register_head = bq2429x_get_register_head,
    .set_watchdog_timer = bq2429x_set_watchdog_timer,
    .set_batfet_disable = bq2429x_set_batfet_disable,
    .check_charger_plugged = bq2429x_check_charger_plugged,
    .check_input_dpm_state = bq2429x_check_input_dpm_state,
    .set_charger_hiz = bq2429x_set_charger_hiz,
};
/**********************************************************
*  Function:       bq2429x_irq_work
*  Discription:    handler for chargerIC fault irq in charging process
*  Parameters:   work:chargerIC fault interrupt workqueue
*  return value:  NULL
**********************************************************/
static void bq2429x_irq_work(struct work_struct *work)
{
    struct bq2429x_device_info *di = container_of(work,struct bq2429x_device_info, irq_work);
    u8 reg = 0;

    msleep(100);
    bq2429x_read_byte(BQ2429X_REG_F, &reg);
    bq2429x_read_byte(BQ2429X_REG_F, &reg);

    if(reg & BQ2429X_REG_F_BOOST_OCP)
    {
        hwlog_info("CHARGE_FAULT_BOOST_OCP once!! \n");
        // retry otg once
        bq2429x_reset_otg();
        msleep(100);
        bq2429x_read_byte(BQ2429X_REG_F, &reg);
        bq2429x_read_byte(BQ2429X_REG_F, &reg);
        if(reg & BQ2429X_REG_F_BOOST_OCP)
        {   
            hwlog_info("CHARGE_FAULT_BOOST_OCP twice!! \n");
            atomic_notifier_call_chain(&fault_notifier_list,CHARGE_FAULT_BOOST_OCP, NULL);
        }
    }

    if(di->irq_active== 0)
    {
        di->irq_active = 1;
        enable_irq(di->irq_int);
    }
}
/**********************************************************
*  Function:       bq2429x_interrupt
*  Discription:    callback function for chargerIC fault irq in charging process
*  Parameters:   irq:chargerIC fault interrupt
*                      _di:bq2429x_device_info
*  return value:  IRQ_HANDLED-sucess or others
**********************************************************/
static irqreturn_t bq2429x_interrupt(int irq, void *_di)
{
    struct bq2429x_device_info *di = _di;

    hwlog_info("bq2429x interrupt\n");
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
/**********************************************************
*  Function:       bq2429x_probe
*  Discription:    bq2429x module probe
*  Parameters:   client:i2c_client
*                      id:i2c_device_id
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
    int ret = 0;
    struct bq2429x_device_info *di = NULL;
    struct charge_device_ops *ops = NULL;
    struct device_node *np = NULL;
    struct class *power_class = NULL;

    di = kzalloc(sizeof(*di), GFP_KERNEL);
    if (!di)
    {
        hwlog_err("bq2429x_device_info is NULL!\n");
        return -ENOMEM;
    }
    g_bq2429x_dev = di;
    di->dev = &client->dev;
    np = di->dev->of_node;
    di->client = client;
    i2c_set_clientdata(client, di);

    INIT_WORK(&di->irq_work, bq2429x_irq_work);
    di->gpio_cd = of_get_named_gpio(np,"gpio_cd",0);
    if(!gpio_is_valid(di->gpio_cd))
    {
        hwlog_err("gpio_cd is not valid\n");
        ret = -EINVAL;
        goto bq2429x_fail_0;
    }
    di->gpio_int = of_get_named_gpio(np,"gpio_int",0);
    if(!gpio_is_valid(di->gpio_int))
    {
        hwlog_err("gpio_int is not valid\n");
        ret = -EINVAL;
        goto bq2429x_fail_0;
    }
    /*set gpio to control CD pin to disable/enable bq2429x IC*/
    ret = gpio_request(di->gpio_cd, "charger_cd");
    if (ret)
    {
        hwlog_err("could not request gpio_cd\n");
        ret = -ENOMEM;
        goto bq2429x_fail_0;
    }
    gpio_direction_output(di->gpio_cd, 0);
    ret = gpio_request(di->gpio_int,"charger_int");
    if(ret)
    {
        hwlog_err("could not request gpio_int\n");
        goto bq2429x_fail_1;
    }
    gpio_direction_input(di->gpio_int);
    di->irq_int = gpio_to_irq(di->gpio_int);
    if(di->irq_int < 0)
    {
        hwlog_err("could not map gpio_int to irq\n");
        goto bq2429x_fail_2;
    }

    ret = request_irq(di->irq_int,bq2429x_interrupt,IRQF_TRIGGER_FALLING,"charger_int_irq",di);
    if(ret)
    {
        hwlog_err("could not request irq_int\n");
        di->irq_int = -1;
        goto bq2429x_fail_2;
    }
    disable_irq(di->irq_int);
    di->irq_active = 0;

    ops = &bq2429x_ops;
    ret = charge_ops_register(ops);
    if(ret)
    {
        hwlog_err("register charge ops failed!\n");
        goto bq2429x_fail_3;
    }
    ret = bq2429x_sysfs_create_group(di);
    if(ret)
        hwlog_err("create sysfs entries failed!\n");
    power_class = hw_power_get_class();
    if(power_class)
    {
        if(charge_dev == NULL)
            charge_dev = device_create(power_class, NULL, 0, NULL,"charger");
        ret = sysfs_create_link(&charge_dev->kobj, &di->dev->kobj, "bq2429x");
        if(ret)
        {
            hwlog_err("create link to bq2429x fail.\n");
            goto bq2429x_fail_4;
        }
    }

    hwlog_info("bq2429x probe ok!\n");
    return 0;

bq2429x_fail_4:
    bq2429x_sysfs_remove_group(di);
bq2429x_fail_3:
    free_irq(di->irq_int, di);
bq2429x_fail_2:
    gpio_free(di->gpio_int);
bq2429x_fail_1:
    gpio_free(di->gpio_cd);
bq2429x_fail_0:
    kfree(di);
    g_bq2429x_dev = NULL;
    np = NULL;

    return ret;
}
/**********************************************************
*  Function:       bq2429x_remove
*  Discription:    bq2429x module remove
*  Parameters:   client:i2c_client
*  return value:  0-sucess or others-fail
**********************************************************/
static int bq2429x_remove(struct i2c_client *client)
{
    struct bq2429x_device_info *di = i2c_get_clientdata(client);

    bq2429x_sysfs_remove_group(di);

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
    kfree(di);
    return 0;
}

MODULE_DEVICE_TABLE(i2c, bq24192);
static struct of_device_id bq2429x_of_match[] =
{
    {
        .compatible = "huawei,bq2429x_charger",
        .data = NULL,
    },
    {
    },
};

static const struct i2c_device_id bq2429x_i2c_id[] = {{"bq2429x_charger",0},{}};

static struct i2c_driver bq2429x_driver =
{
    .probe       = bq2429x_probe,
    .remove	= bq2429x_remove,
    .id_table    = bq2429x_i2c_id,
    .driver = {
        .owner = THIS_MODULE,
        .name    = "bq2429x_charger",
        .of_match_table = of_match_ptr(bq2429x_of_match),
    },
};
/**********************************************************
*  Function:       bq2429x_init
*  Discription:    bq2429x module initialization
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int __init bq2429x_init(void)
{
    int ret =0;

    ret =  i2c_add_driver(&bq2429x_driver);
    if(ret)
        hwlog_err("%s: i2c_add_driver error!!!\n", __func__);

    return ret;
}
/**********************************************************
*  Function:       bq2429x_exit
*  Discription:    bq2429x module exit
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void __exit bq2429x_exit(void)
{
    i2c_del_driver(&bq2429x_driver);
}
module_init(bq2429x_init);
module_exit(bq2429x_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("bq2429x charger module driver");
MODULE_AUTHOR("HW Inc");

