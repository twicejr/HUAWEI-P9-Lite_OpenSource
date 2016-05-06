

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
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif
#include <linux/raid/pq.h>
#include <linux/power/hisi/charger/hisi_charger.h>
#include <linux/power/hisi/coul/hisi_coul_drv.h>
#include <linux/power/hisi/hisi_bci_battery.h>
#include <hisi_scharger_v200.h>
#include <linux/power/hisi_hi6521_charger_power.h>

struct hi6522_device_info *g_hi6522_dev = NULL;
struct hi6522_device_info *scharger_di = NULL;
static void lcd_ldo_ocp_notify_prepare(void);
static u8 dpm_switch_enable = 0;
static u8 is_board_type = 0; /*0:sft 1:udp 2:asic*/

#define CHG_REG_SETBITS(reg_val, shift, mask, set_val) \
                          ((reg_val  = (reg_val & (~((((unsigned int)1 << (mask)) - 1) << (shift)))) \
                           | ((unsigned int)((set_val) & (((unsigned int)1 << (mask)) - 1)) << (shift))))

#define CHG_REG_GETBITS(reg_val, shift, mask) \
                          (((reg_val >> (shift)) \
                           &(((unsigned int)1 << (mask)) - 1)))

/**********************************************************
*  Function:       hi6522_write_block
*  Discription:    register write block interface
*  Parameters:   di:hi6522_device_info
*                      value:register value
*                      reg:register name
*                      num_bytes:bytes number
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_write_block(struct hi6522_device_info *di, u8 *value,
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
    if (ret != 1) {
        SCHARGER_ERR("i2c_write failed to transfer all messages\n");
        if (ret < 0)
            return ret;
        else
            return -EIO;
     } else {
        return 0;
   }
}

/**********************************************************
*  Function:       hi6522_read_block
*  Discription:    register read block interface
*  Parameters:   di:hi6522_device_info
*                      value:register value
*                      reg:register name
*                      num_bytes:bytes number
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_read_block(struct hi6522_device_info *di, u8 *value,
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
    if (ret != 2) {
         SCHARGER_ERR("i2c_read failed to transfer all messages\n");
        if (ret < 0)
            return ret;
        else
            return -EIO;
    } else {
        return 0;
    }
}

/**********************************************************
*  Function:       hi6522_write_byte
*  Discription:    register write byte interface
*  Parameters:   reg:register name
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_write_byte(u8 reg,u8 value)
{
    struct hi6522_device_info *di = g_hi6522_dev;
    /* 2 bytes offset 1 contains the data offset 0 is used by i2c_write */
    u8 temp_buffer[2] = { 0 };
    /* offset 1 contains the data */
    if (NULL == di)
    {
        SCHARGER_ERR("%s hi6522_device_info is NULL!\n",__func__);
        return -ENOMEM;
    }
    temp_buffer[1] = value;
    return hi6522_write_block(di, temp_buffer, reg, 1);
}
/**********************************************************
*  Function:       hi6522_read_byte
*  Discription:    register read byte interface
*  Parameters:   reg:register name
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_read_byte(u8 reg, u8 *value)
{
    struct hi6522_device_info *di = g_hi6522_dev;
    if (NULL == di)
    {
        SCHARGER_ERR("%s hi6522_device_info is NULL!\n",__func__);
        return -ENOMEM;
    }

    return hi6522_read_block(di, value, reg, 1);
}
/**********************************************************
*  Function:       hi6522_write_mask
*  Discription:    register write mask interface
*  Parameters:   reg:register name
*                      MASK:mask value of the function
*                      SHIFT:shift number of the function
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_write_mask(u8 reg, u8 MASK, u8 SHIFT, u8 value)
{
    int ret = 0;
    u8 val = 0;

    ret = hi6522_read_byte(reg,&val);
    if(ret < 0)
        return ret;

    val &= ~MASK;
    val |= ((value << SHIFT) & MASK);

    ret = hi6522_write_byte(reg,val);

    return ret;
}
/**********************************************************
*  Function:       hi6522_read_mask
*  Discription:    register read mask interface
*  Parameters:   reg:register name
*                      MASK:mask value of the function
*                      SHIFT:shift number of the function
*                      value:register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_read_mask(u8 reg, u8 MASK, u8 SHIFT, u8 *value)
{
    int ret = 0;
    u8 val = 0;

    ret = hi6522_read_byte(reg,&val);
    if(ret < 0)
        return ret;
    val &= MASK;
    val >>= SHIFT;
    *value = val;

    return 0;
}

#define CONFIG_SYSFS_SCHG
#ifdef CONFIG_SYSFS_SCHG
/*
 * There are a numerous options that are configurable on the HI6521
 * that go well beyond what the power_supply properties provide access to.
 * Provide sysfs access to them so they can be examined and possibly modified
 * on the fly.
 */

#define hi6522_SYSFS_FIELD(_name, r, f, m, store)                  \
{                                                   \
    .attr = __ATTR(_name, m, hi6522_sysfs_show, store),    \
    .reg = CHG_##r##_REG,                      \
    .mask = CHG_##f##_MSK,                       \
    .shift = CHG_##f##_SHIFT,                     \
}

#define hi6522_SYSFS_FIELD_RW(_name, r, f)                     \
        hi6522_SYSFS_FIELD(_name, r, f, S_IWUSR | S_IRUGO, \
                hi6522_sysfs_store)

#define hi6522_SYSFS_FIELD_RO(_name, r, f)                         \
        hi6522_SYSFS_FIELD(_name, r, f, S_IRUGO, NULL)

static ssize_t hi6522_sysfs_show(struct device *dev,
        struct device_attribute *attr, char *buf);
static ssize_t hi6522_sysfs_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t count);

struct hi6522_sysfs_field_info {
    struct device_attribute	attr;
    u8  reg;
    u8  mask;
    u8  shift;
};

static struct hi6522_sysfs_field_info hi6522_sysfs_field_tbl[] = {
    hi6522_SYSFS_FIELD_RW(dpm_switch_enable,NONE,    NONE),
    hi6522_SYSFS_FIELD_RW(reg_addr,         NONE,    NONE),
    hi6522_SYSFS_FIELD_RW(reg_value,        NONE,    NONE),
};


static struct attribute *
        hi6522_sysfs_attrs[ARRAY_SIZE(hi6522_sysfs_field_tbl) + 1];

static const struct attribute_group hi6522_sysfs_attr_group = {
        .attrs = hi6522_sysfs_attrs,
};
/**********************************************************
*  Function:       hi6522_sysfs_init_attrs
*  Discription:    initialize hi6522_sysfs_attrs[] for HI6523 attribute
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void hi6522_sysfs_init_attrs(void)
{
    int i, limit = ARRAY_SIZE(hi6522_sysfs_field_tbl);

    for (i = 0; i < limit; i++)
        hi6522_sysfs_attrs[i] = &hi6522_sysfs_field_tbl[i].attr.attr;

    hi6522_sysfs_attrs[limit] = NULL; /* Has additional entry for this */
}
/**********************************************************
*  Function:       hi6522_sysfs_field_lookup
*  Discription:    get the current device_attribute from hi6522_sysfs_field_tbl by attr's name
*  Parameters:   name:evice attribute name
*  return value:  hi6522_sysfs_field_tbl[]
**********************************************************/
static struct hi6522_sysfs_field_info *hi6522_sysfs_field_lookup(const char *name)
{
    int i, limit = ARRAY_SIZE(hi6522_sysfs_field_tbl);

    for (i = 0; i < limit; i++)
        if (!strcmp(name, hi6522_sysfs_field_tbl[i].attr.attr.name))
            break;

    if (i >= limit)
        return NULL;

    return &hi6522_sysfs_field_tbl[i];
}
/**********************************************************
*  Function:       hi6522_sysfs_show
*  Discription:    show the value for all HI6523 device's node
*  Parameters:   dev:device
*                      attr:device_attribute
*                      buf:string of node value
*  return value:  0-sucess or others-fail
**********************************************************/
static ssize_t hi6522_sysfs_show(struct device *dev,
            struct device_attribute *attr, char *buf)
{
    struct hi6522_sysfs_field_info *info;
    struct hi6522_sysfs_field_info *info2;
    int ret;
    u8 v;

    info = hi6522_sysfs_field_lookup(attr->attr.name);
    if (!info)
        return -EINVAL;

    if(!strncmp("dpm_switch_enable",attr->attr.name,strlen("dpm_switch_enable")))
    {
        return scnprintf(buf,PAGE_SIZE,"%d\n",dpm_switch_enable);
    }

    if(!strncmp("reg_addr",attr->attr.name,strlen("reg_addr")))
    {
        return scnprintf(buf,PAGE_SIZE,"0x%hhx\n",info->reg);
    }

    if(!strncmp(("reg_value"),attr->attr.name,strlen("reg_value")))
    {
        info2 = hi6522_sysfs_field_lookup("reg_addr");
        if(!info2)
            return -EINVAL;
        info->reg = info2->reg;
    }

    ret = hi6522_read_mask(info->reg, info->mask, info->shift, &v);
    if (ret)
        return ret;

    return scnprintf(buf, PAGE_SIZE, "0x%hhx\n", v);
}
/**********************************************************
*  Function:       hi6522_sysfs_store
*  Discription:    set the value for all HI6523 device's node
*  Parameters:   dev:device
*                      attr:device_attribute
*                      buf:string of node value
*                      count:unused
*  return value:  0-sucess or others-fail
**********************************************************/
static ssize_t hi6522_sysfs_store(struct device *dev,
            struct device_attribute *attr, const char *buf, size_t count)
{
    struct hi6522_sysfs_field_info *info;
    struct hi6522_sysfs_field_info *info2;
    int ret;
    u8 v;

    info = hi6522_sysfs_field_lookup(attr->attr.name);
    if (!info)
        return -EINVAL;

    ret = kstrtou8(buf, 0, &v);
    if (ret < 0)
        return ret;

    if(!strncmp("dpm_switch_enable",attr->attr.name,strlen("dpm_switch_enable")))
    {
        if(v == 1 ||  v == 0)
        {
            dpm_switch_enable = v;
            return count;
        }
        else
        {
            return -EINVAL;
        }
    }

    if(!strncmp(("reg_value"),attr->attr.name,strlen("reg_value")))
    {
        info2 = hi6522_sysfs_field_lookup("reg_addr");
        if(!info2)
            return -EINVAL;
        info->reg = info2->reg;
    }
    if(!strncmp(("reg_addr"),attr->attr.name,strlen("reg_addr")))
    {
        if(v <(u8)HI6522_REG_TOTAL_NUM )
        {
            info->reg = v;
            return count;
        }
        else
        {
            return -EINVAL;
        }
    }

    ret = hi6522_write_mask(info->reg, info->mask, info->shift, v);
    if (ret)
        return ret;

    return count;
}
/**********************************************************
*  Function:       hi6522_sysfs_create_group
*  Discription:    create the HI6523 device sysfs group
*  Parameters:   di:hi6522_device_info
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_sysfs_create_group(struct hi6522_device_info *di)
{
    hi6522_sysfs_init_attrs();

    return sysfs_create_group(&di->dev->kobj,&hi6522_sysfs_attr_group);
}
/**********************************************************
*  Function:       charge_sysfs_remove_group
*  Discription:    remove the HI6523 device sysfs group
*  Parameters:   di:hi6522_device_info
*  return value:  NULL
**********************************************************/
static void hi6522_sysfs_remove_group(struct hi6522_device_info *di)
{
    sysfs_remove_group(&di->dev->kobj, &hi6522_sysfs_attr_group);
}
#else
static int hi6522_sysfs_create_group(struct hi6522_device_info *di)
{
    return 0;
}
static inline void hi6522_sysfs_remove_group(struct hi6522_device_info *di) {}
#endif

/**********************************************************
*  Function:       hi6522_set_input_current
*  Discription:    set the input current in charging process
*  Parameters:   value:input current value
*  return value:  0-sucess or others-fail
**********************************************************/

int hi6522_set_input_current(int cin_limit)
{
    u8 Iin_limit;
    if (cin_limit <= IINLIM_100)
        Iin_limit = 0;
    else if (cin_limit > IINLIM_100 && cin_limit <= IINLIM_150)
        Iin_limit = 1;
    else if (cin_limit > IINLIM_150 && cin_limit <= IINLIM_500)
        Iin_limit = 2;
    else if (cin_limit > IINLIM_500 && cin_limit <= IINLIM_900)
        Iin_limit = 3;
	else if (cin_limit > IINLIM_900 && cin_limit <= IINLIM_1000)
		Iin_limit = 4;
    else if (cin_limit > IINLIM_1000 && cin_limit <= IINLIM_1200)
        Iin_limit = 5;
    else if (cin_limit > IINLIM_1200 && cin_limit <= IINLIM_1500)
        Iin_limit = 6;
    else if (cin_limit > IINLIM_1500 && cin_limit <= IINLIM_1600)
        Iin_limit = 7;
    else if (cin_limit > IINLIM_1600 && cin_limit <= IINLIM_1800)
        Iin_limit = 8;
    else if (cin_limit > IINLIM_1800 && cin_limit <= IINLIM_2000)
        Iin_limit = 9;
    else if (cin_limit > IINLIM_2000 && cin_limit <= IINLIM_2200)
        Iin_limit = 10;
	else if (cin_limit > IINLIM_2200 && cin_limit <= IINLIM_2500)
        Iin_limit = 11;
    else
        Iin_limit = 4;
    SCHARGER_INF("input current reg is set 0x%x\n",Iin_limit);
    return hi6522_write_mask(CHG_INPUT_SOURCE_REG,CHG_ILIMIT_MSK,CHG_ILIMIT_SHIFT,Iin_limit);
}

/**********************************************************
*  Function:       hi6522_set_dpm_voltage
*  Discription:    set the dpm voltage in charging process
*  Parameters:   value:dpm voltage value
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_set_dpm_voltage(int vindpm)
{
    u8 vindpm_limit = 0;

    if (vindpm < VINDPM_MIN_3880)
        vindpm = VINDPM_MIN_3880;
    else if (vindpm > VINDPM_MAX_5080)
        vindpm = VINDPM_MAX_5080;
    vindpm_limit = (unsigned char)((vindpm -VINDPM_MIN_3880)/VINDPM_STEP_80);

    SCHARGER_INF("dpm will be set to %d mV, expect: vindpm = %d mV\n", (VINDPM_MIN_3880 + vindpm_limit* VINDPM_STEP_80), vindpm);
    return hi6522_write_mask(CHG_DPM_SEL_REG,CHG_DPM_SEL_MSK,CHG_DPM_SEL_SHIFT,vindpm_limit);
}
/**********************************************************
*  Function:     hi6522_set_precharge_current()
*  Discription:  config precharge current limit
*  Parameters:   precharge current
*  return value:
*                 0-sucess or others-fail
**********************************************************/
static int hi6522_set_precharge_current(int precharge_current)
{
    u8 prechg_limit;

    if (precharge_current < CHG_PRG_ICHG_MIN)
    {
        precharge_current = CHG_PRG_ICHG_MIN;
    }
    else if (precharge_current > CHG_PRG_ICHG_MAX)
    {
        precharge_current = CHG_PRG_ICHG_MAX;
    }
    else
    {
        //do nothing
    }

    prechg_limit = (u8)((precharge_current - CHG_PRG_ICHG_MIN) / CHG_PRG_ICHG_STEP);

    return hi6522_write_mask(CHG_PRE_ICHG_REG, CHG_PRE_ICHG_MSK, CHG_PRE_ICHG_SHIFT, prechg_limit);
}

/**********************************************************
*  Function:     hi6522_set_precharge_voltage()
*  Discription:  config precharge voltage
*  Parameters:   precharge voltage
*  return value:
*                 0-sucess or others-fail
**********************************************************/
static int hi6522_set_precharge_voltage(u32 pre_vchg)
{
    u8 vprechg;
    if (pre_vchg <= CHG_PRG_VCHG_2800)
        vprechg = 0;
    else if (pre_vchg > CHG_PRG_VCHG_2800 && pre_vchg <= CHG_PRG_VCHG_3000)
        vprechg = 1;
    else if (pre_vchg > CHG_PRG_VCHG_3000 && pre_vchg <= CHG_PRG_VCHG_3100)
        vprechg = 2;
    else if (pre_vchg > CHG_PRG_VCHG_3100 && pre_vchg <= CHG_PRG_VCHG_3200)
        vprechg = 3;
    else
        vprechg = 0; /*default 2.8V*/
    return hi6522_write_mask( CHG_PRE_VCHG_REG, CHG_PRE_VCHG_MSK, CHG_PRE_VCHG_SHIFT, vprechg);
}

/**********************************************************
*  Function:     hi6522_set_batfet_ctrl()
*  Discription:  config batfet status 1:enable, 0: disable
*  Parameters:   status
*  return value:
*                 0-sucess or others-fail
**********************************************************/
static int hi6522_set_batfet_ctrl(u32 status)
{
    return hi6522_write_mask(BATFET_CTRL_CFG_REG, BATFET_CTRL_CFG_MSK, BATFET_CTRL_CFG_SHIFT, status);
}

/**********************************************************
*  Function:       hi6522_set_batfet_disable
*  Discription:    set the batfet disable in charging process
*  Parameters:   disable:batfet disable or not
*  return value:  0-sucess or others-fail
**********************************************************/
int hi6522_set_batfet_disable(int disable)
{
    return hi6522_set_batfet_ctrl(!disable);
}

/**********************************************************
*  Function:       hi6522_set_charge_current
*  Discription:    set the charge current in charging process
*  Parameters:   value:charge current value ma
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_set_charge_current(int charge_current)
{
    u8 Ichg_limit;
    if (charge_current < CHG_FAST_ICHG_MIN)
        charge_current = CHG_FAST_ICHG_MIN;
    else if(charge_current > CHG_FAST_ICHG_MAX)
        charge_current = CHG_FAST_ICHG_MAX;
    Ichg_limit = (unsigned char)((charge_current - CHG_FAST_ICHG_MIN)/CHG_FAST_ICHG_STEP_100);
    SCHARGER_INF("charge current reg is set %d ma\n",charge_current);
    return hi6522_write_mask(CHG_FAST_CURRENT_REG, CHG_FAST_ICHG_MSK, CHG_FAST_ICHG_SHIFT, Ichg_limit);
}
/**********************************************************
*  Function:       hi6522_set_terminal_current
*  Discription:    set the terminal current in charging process
*  Parameters:   value:terminal current value ma
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_set_terminal_current(int term_current)
{
    u8 Iterm;
    if (term_current < CHG_TERM_ICHG_MIN)
        term_current = CHG_TERM_ICHG_MIN;
    else if(term_current > CHG_TERM_ICHG_MAX)
        term_current = CHG_TERM_ICHG_MAX;
    Iterm = (unsigned char)((term_current - CHG_TERM_ICHG_MIN)/CHG_TERM_ICHG_STEP_50);

    SCHARGER_INF(" term current is set %d ma\n",term_current);
    return hi6522_write_mask(CHG_TERM_ICHG_REG,CHG_TERM_ICHG_MSK,CHG_TERM_ICHG_SHIFT,Iterm);
}

/**********************************************************
*  Function:       hi6522_set_terminal_voltage
*  Discription:    set the terminal voltage in charging process
*  Parameters:   value:terminal voltage value mv
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_set_terminal_voltage(int charge_voltage)
{
    u8 data;
    if (charge_voltage < CHG_FAST_VCHG_MIN)
    {
        charge_voltage = CHG_FAST_VCHG_MIN;
    }
    else if (charge_voltage > CHG_FAST_VCHG_MAX)
    {
        charge_voltage = CHG_FAST_VCHG_MAX;
    }
    else
    {
        //do nothing
    }

    data = (u8)((charge_voltage - CHG_FAST_VCHG_MIN) / CHG_FAST_VCHG_STEP_50);
    return hi6522_write_mask(CHG_FAST_VCHG_REG, CHG_FAST_VCHG_MSK, CHG_FAST_VCHG_SHIFT, data);
}
/**********************************************************
*  Function:       hi6522_set_vclamp
*  Discription:    set the vclamp
*  Parameters:   value:vclamp mv
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_set_vclamp(int value)
{
    u8 reg;
    if (value < CHG_IR_VCLAMP_MIN)
        value = CHG_IR_VCLAMP_MIN;
    else if (value > CHG_IR_VCLAMP_MAX)
        value = CHG_IR_VCLAMP_MAX;
    else
    {
        //do nothing
    }
    reg = (value - CHG_IR_VCLAMP_MIN) / CHG_IR_VCLAMP_STEP;

    return hi6522_write_mask( CHG_IR_VCLAMP_REG, CHG_IR_VCLAMP_MSK, CHG_IR_VCLAMP_SHIFT, reg);
}

/**********************************************************
*  Function:     hi6522_set_fast_safe_timer()
*  Discription:  set fast safe timer
*  Parameters:   safe timer value
*  return value:
*                 0-sucess or others-fail
**********************************************************/
static int hi6522_set_fast_safe_timer(u32 chg_fastchg_safe_timer)
{
    return hi6522_write_mask(CHG_FAST_SAFE_TIMER_TERM_CTRL_REG,CHG_FAST_SAFE_TIMER_MSK,CHG_FAST_SAFE_TIMER_SHIFT, (u8)chg_fastchg_safe_timer);
}

/**********************************************************
*  Function:       hi6522_set_term_enable
*  Discription:    set the terminal enable in charging process
*  Parameters:   enable:terminal enable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_set_term_enable(int enable)
{
    return hi6522_write_mask(CHG_EN_TERM_REG,CHG_EN_TERM_MSK,CHG_EN_TERM_SHIFT,enable);
}

/**********************************************************
*  Function:       hi6522_set_watchdog_timer
*  Discription:    set the watchdog timer in charging process
*  Parameters:   value:watchdog timer value
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_set_watchdog_timer(int value)
{
    u8 val = 0;
    u8 dog_time = value;
    if(dog_time >= TIMER_40S)
    {
        val = 3;
    }
    else if(dog_time >= TIMER_20S)
    {
        val = 2;
    }
    else if(dog_time >= TIMER_10S)
    {
        val = 1;
    }
    else
    {
        val = 0;
    }
    SCHARGER_INF(" watch dog timer is %d ,the register value is set %u \n",dog_time,val);
    return hi6522_write_mask(CHG_WDT_TIMER_REG,CHG_WDT_TIMER_MSK,CHG_WDT_TIMER_SHIFT,val);
}

/**********************************************************
*  Function:       hi6522_reset_watchdog_timer
*  Discription:    reset watchdog timer in charging process
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_reset_watchdog_timer(void)
{
    u8 dog_status = 0;
    /*scharger v200 need to write wdt timer*/
    hi6522_read_byte(CHG_WDT_TIMER_REG,&dog_status);
    if (dog_status & CHG_WDT_TIMER_MSK == 0)
        hi6522_set_watchdog_timer(TIMER_40S);
	return hi6522_write_mask(CHG_WDT_RST_REG,CHG_WDT_RST_MSK,CHG_WDT_RST_SHIFT,CHG_WDT_RST);
}

/**********************************************************
*  Function:       hi6522_dump_register
*  Discription:    print the register value in charging process
*  Parameters:   reg_value:string for save register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_dump_register(char *reg_value)
{
    u8 reg[HI6522_REG_TOTAL_NUM] = {0};
    char buff[26] = {0};
    int i = 0;
    struct hi6522_device_info *di = g_hi6522_dev;
    if (NULL == di)
    {
        SCHARGER_ERR("%s hi6522_device_info is NULL!\n",__func__);
        return -ENOMEM;
    }
    memset(reg_value, 0, CHARGELOG_SIZE);
    hi6522_read_block(di,&reg[0],0,HI6522_REG_TOTAL_NUM);
    for (i = 0;i< HI6522_REG_TOTAL_NUM;i++){
        snprintf(buff, 26, "0x%-8x",reg[i]);
        strncat(reg_value, buff, strlen(buff));
    }
    return 0;
}
/**********************************************************
*  Function:       hi6522_get_register_head
*  Discription:    print the register head in charging process
*  Parameters:   reg_head:string for save register head
*  return value:  0-sucess or others-fail
**********************************************************/
static int hi6522_get_register_head(char *reg_head)
{
    char buff[26] = {0};
    int i = 0;

    memset(reg_head, 0, CHARGELOG_SIZE);
    for(i = 0;i<HI6522_REG_TOTAL_NUM;i++)
    {
        snprintf(buff, 26, "Reg[0x%2x] ",i);
        strncat(reg_head, buff, strlen(buff));
    }
    return 0;
}
/****************************************************************************
  Function:     hi6522_config_power_on_reg01
  Description:  config onff1 to disable/enable chg/otg/wled/ldo_200ma.
  Input:        struct hi6522_device_info
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int hi6522_config_power_on_reg01(struct hi6522_device_info *di)
{
	int ret = 0;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_power_on_reg01 sema fail! \n");
		return -EINTR;
	}
	di->power_on_config_reg01.reg.chg_en_int        = di->chg_en;
	di->power_on_config_reg01.reg.otg_en_int        = di->otg_en;
	di->power_on_config_reg01.reg.wled_en_int       = di->wled_en;
	di->power_on_config_reg01.reg.ldo1_200ma_en_int = di->ldo1_200ma_en;
	di->power_on_config_reg01.reg.ldo2_200ma_en_int = di->ldo2_200ma_en;

	ret = hi6522_write_byte(POWER_ON_CONFIG_REG01, di->power_on_config_reg01.value);
	up(&di->charger_data_busy_lock);
    SCHARGER_INF("hi6522_config_power_on_reg01 :0x%x \n",di->power_on_config_reg01.value);
	return ret;
}

/****************************************************************************
  Function:     hi6522_config_charger_enable_val
  Description:  config chg enable/disable.
  Input:        di->chg_en need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_set_charge_enable(int val)
{
    int ret = 0;
    struct hi6522_device_info *di = g_hi6522_dev;
    if (NULL == di)
    {
        SCHARGER_ERR("%s hi6522_device_info is NULL!\n",__func__);
        return -ENOMEM;
    }

    if (down_interruptible(&di->charger_data_busy_lock)){
        SCHARGER_ERR("hi6522_config_charger_enable sema fail! \n");
        return -EINTR;
    }
    di->chg_en=(unsigned char)val;
    ret = hi6522_read_byte(POWER_ON_CONFIG_REG01,&di->power_on_config_reg01.value);
    di->power_on_config_reg01.reg.chg_en_int = di->chg_en;
    ret |= hi6522_write_byte(POWER_ON_CONFIG_REG01,di->power_on_config_reg01.value);
    up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg01 is 0x%x \n",__func__,di->power_on_config_reg01.value);
    return ret;
}

/****************************************************************************
  Function:     hi6522_config_charger_nolock_enable
  Description:  config chg enable/disable.
  Input:        struct hi6522_device_info,di->chg_en need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_charger_nolock_enable(struct hi6522_device_info *di)
{

  int ret = 0;
  ret = hi6522_read_byte(POWER_ON_CONFIG_REG01,&di->power_on_config_reg01.value);
  di->power_on_config_reg01.reg.chg_en_int = di->chg_en;
  ret |= hi6522_write_byte(POWER_ON_CONFIG_REG01,di->power_on_config_reg01.value);
  SCHARGER_INF("[%s] :power_on_config_reg01 is 0x%x \n",__func__,di->power_on_config_reg01.value);
  return ret;
}
/****************************************************************************
  Function:     hi6522_config_otg_enable
  Description:  config otg enable/disable.
  Input:        di->otg_en and di->otg_force_en need setup
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_set_otg_enable(int val)
{
	int ret = 0;
    struct hi6522_device_info *di = g_hi6522_dev;
    if (NULL == di)
    {
        SCHARGER_ERR("%s hi6522_device_info is NULL!\n",__func__);
        return -ENOMEM;
    }

	if (down_interruptible(&di->charger_data_busy_lock))
    {
		SCHARGER_ERR("hi6522_config_otg_enable sema fail! \n");
		return -EINTR;
	}
    if (val)
    {
        di->otg_en = CHG_OTG_FORCE_EN;
        di->chg_en = CHG_DISABLE;
    }
    else
    {
        di->otg_en = CHG_OTG_FORCE_DIS;
    }
	/*config otg en*/
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG01,&di->power_on_config_reg01.value);
	di->power_on_config_reg01.reg.otg_en_int = di->otg_en;
    di->power_on_config_reg01.reg.chg_en_int = di->chg_en;
	ret |= hi6522_write_byte(POWER_ON_CONFIG_REG01,di->power_on_config_reg01.value);
	up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg01 is 0x%x \n",__func__,di->power_on_config_reg01.value);
	return ret;
}

/**********************************************************
*  Function:       hi6522_set_otg_current
*  Discription:    set the otg mdoe current
*  Parameters:     value :current value
*  return value:  0-sucess or others-fail
**********************************************************/
int hi6522_set_otg_current(int value)
{
    unsigned int temp_currentmA = 0;
    u8 reg = 0;
    temp_currentmA = value;

    if (temp_currentmA < BOOST_LIM_MIN || temp_currentmA > BOOST_LIM_MAX)
        SCHARGER_INF("set otg current %dmA is out of range!\n",value);

    if (temp_currentmA < BOOST_LIM_MAX)
    {
        reg = 0;
    }
    else
    {
        reg = 1;
    }

    SCHARGER_INF(" otg current reg is set %d ma\n",(reg + 1) * BOOST_LIM_MIN);
    return hi6522_write_mask(CHG_OTG_REG0,CHG_OTG_LIM_MSK,CHG_OTG_LIM_SHIFT,reg);
}
/****************************************************************************
  Function:     hi6522_config_wled_enable
  Description:  config wled enable/disable.
  Input:        struct hi6522_device_info,di->wled need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_wled_enable(struct hi6522_device_info *di)
{
	int ret = 0;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_wled_enable sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG01,&di->power_on_config_reg01.value);
	di->power_on_config_reg01.reg.wled_en_int = di->wled_en;
	ret |= hi6522_write_byte(POWER_ON_CONFIG_REG01,di->power_on_config_reg01.value);

	up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg01 is 0x%x \n",__func__,di->power_on_config_reg01.value);
	return ret;
}

/****************************************************************************
  Function:     hi6522_config_ldo1_200ma_enable
  Description:  config ldo1_200ma_en enable/disable,NFC use.
  Input:        struct hi6522_device_info,di->ldo1_200ma_en need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_ldo1_200ma_enable(struct hi6522_device_info *di)
{
	int ret = 0;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_ldo1_200ma_enable sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG01,&di->power_on_config_reg01.value);
	di->power_on_config_reg01.reg.ldo1_200ma_en_int = di->ldo1_200ma_en;
	ret |= hi6522_write_byte(POWER_ON_CONFIG_REG01,di->power_on_config_reg01.value);
	up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg01 is 0x%x \n",__func__,di->power_on_config_reg01.value);
	return ret;
}

/****************************************************************************
  Function:     hi6522_config_ldo2_200ma_enable
  Description:  config ldo1_200ma_en enable/disable,NFC use.
  Input:        struct hi6522_device_info,di->ldo1_200ma_en need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_ldo2_200ma_enable(struct hi6522_device_info *di)
{
	int ret = 0;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_ldo2_200ma_enable sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG01,&di->power_on_config_reg01.value);
	di->power_on_config_reg01.reg.ldo2_200ma_en_int = di->ldo2_200ma_en;
	ret |= hi6522_write_byte(POWER_ON_CONFIG_REG01,di->power_on_config_reg01.value);
	up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg01 is 0x%x \n",__func__,di->power_on_config_reg01.value);
	return ret;
}

/****************************************************************************
  Function:     hi6522_config_lcd_boost_enable
  Description:  config lcd_bst enable/disable.
  Input:        struct hi6522_device_info,di->lcd_bst_en need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_lcd_boost_enable(struct hi6522_device_info *di)
{
	int ret = 0;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_lcd_boost_enable sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG00,&di->power_on_config_reg00.value);
	di->power_on_config_reg00.reg.lcd_bst_en_int = di->lcd_bst_en;
	ret |= hi6522_write_byte(POWER_ON_CONFIG_REG00,di->power_on_config_reg00.value);
	up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg00 is 0x%x \n",__func__,di->power_on_config_reg00.value);
	return ret;
}

/****************************************************************************
  Function:     hi6522_config_lcd_ldo_enable
  Description:  config lcd_ldo enable/disable,LCD+5v.
  Input:        struct hi6522_device_info,di->lcd_ldo need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_lcd_ldo_enable(struct hi6522_device_info *di)
{
	int ret = 0;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_lcd_ldo_enable sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG00,&di->power_on_config_reg00.value);
	di->power_on_config_reg00.reg.lcd_ldo_en_int = di->lcd_ldo_en;
	ret |= hi6522_write_byte(POWER_ON_CONFIG_REG00,di->power_on_config_reg00.value);
	up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg00 is 0x%x \n",__func__,di->power_on_config_reg00.value);
	return ret;
}

/****************************************************************************
  Function:     hi6522_config_lcd_ncp_enable
  Description:  config lcd_ncp enable/disable,LCD-5V.
  Input:        struct hi6522_device_info:di->lcd_ncp need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_lcd_ncp_enable(struct hi6522_device_info *di)
{
	int ret = 0;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_lcd_ncp_enable sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG00,&di->power_on_config_reg00.value);
	di->power_on_config_reg00.reg.lcd_ncp_en_int = di->lcd_ncp_en;
	ret |= hi6522_write_byte(POWER_ON_CONFIG_REG00,di->power_on_config_reg00.value);
	up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg00 is 0x%x \n",__func__,di->power_on_config_reg00.value);
	return ret;
}
/****************************************************************************
  Function:     hi6522_config_lcd_ldo_ncp_enable
  Description:  config lcd_ldo_ncp enable/disable,LCD+5v-5v simultaneouly.
  Input:        struct hi6522_device_info,di->lcd_ldo & di->lcd_ncp need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_lcd_ldo_ncp_enable(struct hi6522_device_info *di)
{
    int ret = 0;
    if (down_interruptible(&di->charger_data_busy_lock)){
        SCHARGER_ERR("hi6522_config_lcd_ldo_enable sema fail! \n");
        return -EINTR;
    }
    ret = hi6522_read_byte(POWER_ON_CONFIG_REG00,&di->power_on_config_reg00.value);
    di->power_on_config_reg00.reg.lcd_ldo_en_int = di->lcd_ldo_en;
    di->power_on_config_reg00.reg.lcd_ncp_en_int = di->lcd_ncp_en;
    ret |= hi6522_write_byte(POWER_ON_CONFIG_REG00,di->power_on_config_reg00.value);
    up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg00 is 0x%x \n",__func__,di->power_on_config_reg00.value);
    return ret;
}

/****************************************************************************
  Function:     hi6522_config_flash_boost_enable
  Description:  config flash boost enable/disable.
  Input:        struct hi6522_device_info:di di->flash_bst_en need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_flash_boost_enable(struct hi6522_device_info *di)
{
	int ret = 0;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_flash_boost_enable sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG00,&di->power_on_config_reg00.value);
	di->power_on_config_reg00.reg.flash_bst_en_int = di->flash_bst_en;
	ret |= hi6522_write_byte(POWER_ON_CONFIG_REG00,di->power_on_config_reg00.value);
	up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg00 is 0x%x \n",__func__,di->power_on_config_reg00.value);
	return ret;
}

/****************************************************************************
  Function:     hi6522_config_flash_led_flash_enable
  Description:  config flash_led_flash enable/disable.
  Input:        struct hi6522_device_info:di->di->flash_led_flash_en need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_flash_led_flash_enable(struct hi6522_device_info *di)
{
	int ret = 0;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_flash_led_flash_enable sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG00,&di->power_on_config_reg00.value);
	di->power_on_config_reg00.reg.flash_led_flash_en = di->flash_led_flash_en;
	ret |= hi6522_write_byte(POWER_ON_CONFIG_REG00,di->power_on_config_reg00.value);
	up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg00 is 0x%x \n",__func__,di->power_on_config_reg00.value);
	return ret;
}
/****************************************************************************
  Function:     hi6522_config_flash_led_torch_enable
  Description:  config falsh_led_torch enable/disable.
  Input:        struct hi6522_device_info:di->di->flash_led_torch_en need setup.
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_flash_led_torch_enable(struct hi6522_device_info *di)
{
	int ret = 0;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_flash_led_torch_enable sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG00,&di->power_on_config_reg00.value);
	di->power_on_config_reg00.reg.flash_led_torch_en = di->flash_led_torch_en;
	ret |= hi6522_write_byte(POWER_ON_CONFIG_REG00,di->power_on_config_reg00.value);
	up(&di->charger_data_busy_lock);
    SCHARGER_INF("[%s] :power_on_config_reg00 is 0x%x \n",__func__,di->power_on_config_reg00.value);
	return ret;
}

/****************************************************************************
  Function:     hi6522_config_flash_led_timeout_enable
  Description:  config flash_led_torch current enable/disable.
  Input:        struct hi6522_device_info:di->di->flash_led_flash_en need setup.
                lightness
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_flash_led_timeout_enable(struct hi6522_device_info *di)
{
	int ret = 0;

	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_flash_led_timeout_enable sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(FLASH_LED_REG7_REG,&di->flash_led_reg7.value);
	di->flash_led_reg7.reg.flash_led_timeout_en = di->chg_flash_led_timeout_en;
	ret |= hi6522_write_byte(FLASH_LED_REG7_REG,di->flash_led_reg7.value);
	up(&di->charger_data_busy_lock);
	return ret;
}

/****************************************************************************
  Function:     hi6522_config_flash_led_timeout
  Description:  config flash_led_timeout.
  Input:        struct hi6522_device_info:di->chg_flash_led_timeout need setup.
                lightness
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_flash_led_timeout(struct hi6522_device_info *di)
{
	int ret = 0;
	unsigned int flash_led_timeout = 0;
	unsigned char tout = 0;

	flash_led_timeout = di->chg_flash_led_timeout;
    if(flash_led_timeout <= FLASH_LED_TIMEOUT_400)
        tout = 0;
    else if ((flash_led_timeout > FLASH_LED_TIMEOUT_400) && (flash_led_timeout <= FLASH_LED_TIMEOUT_600))
        tout = 0x1;
	else if ((flash_led_timeout > FLASH_LED_TIMEOUT_600) && (flash_led_timeout <= FLASH_LED_TIMEOUT_800))
        tout = 0x2;
    else
		tout = 0x3;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_flash_led_timeout sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(FLASH_LED_REG6_REG,&di->flash_led_reg6.value);
	di->flash_led_reg6.reg.flash_led_timeout = tout;
	ret |= hi6522_write_byte(FLASH_LED_REG6_REG,di->flash_led_reg6.value);
	up(&di->charger_data_busy_lock);
	return ret;
}

/****************************************************************************
  Function:     hi6522_config_flash_torch_timeout
  Description:  config flash_torch timeout.
  Input:        struct hi6522_device_info:di->chg_flash_torch_timeout need setup.
                lightness
  Output:       NA
  Return:       0:success others:fail
****************************************************************************/
static int  hi6522_config_flash_torch_timeout(struct hi6522_device_info *di)
{
	int ret = 0;
	unsigned int flash_torch_timeout = 0;
	unsigned char tout = 0;

	flash_torch_timeout = di->chg_flash_torch_timeout;
	/*config torch timeout*/
    if(flash_torch_timeout > CHG_FLASH_TORCH_TIMOUT_MAX)
       flash_torch_timeout = CHG_FLASH_TORCH_TIMOUT_MAX;
    tout = (unsigned char)((flash_torch_timeout - CHG_FLASH_TORCH_TIMOUT_MIN)/CHG_FLASH_TORCH_TIMOUT_STEP_2);

	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("hi6522_config_flash_torch_timeout sema fail! \n");
		return -EINTR;
	}
	ret = hi6522_read_byte(FLASH_LED_REG6_REG,&di->flash_led_reg6.value);
	di->flash_led_reg6.reg.flash_led_watchdog_timer = tout;
	ret |= hi6522_write_byte(FLASH_LED_REG6_REG,di->flash_led_reg6.value);
	up(&di->charger_data_busy_lock);
	return ret;
}

/****************************************************************************
  Function:     hi6522_config_opt_param
  Description:  scharger optimization config.
  Input:
  Output:       NA
  Return:       NA
***************************************************************************/

static int hi6522_config_opt_param(void)
{
	hi6522_write_byte(0x48, 0x14);
    hi6522_write_byte(0x40, 0x8A);

	hi6522_write_byte(0x42, 0x2A);
	hi6522_write_byte(0x3B, 0x11);
    hi6522_write_byte(0x37, 0xF3);
    hi6522_write_byte(0x45, 0x82);
    hi6522_write_byte(0x41, 0x25);
    hi6522_write_byte(0x3e, 0x11);

    hi6522_write_byte(0x1C, 0x7F);
    hi6522_write_byte(0x17, 0x78);
    hi6522_write_byte(0x16, 0xC8);
    hi6522_write_byte(0x1D, 0x6B);
    hi6522_write_byte(0x18, 0x99);
    hi6522_write_byte(0x2F, 0x18);
    hi6522_write_byte(0x31, 0x2C);

    hi6522_write_byte(0x21, 0x0A);
    hi6522_write_byte(0x25, 0x7B);
    hi6522_write_byte(0x27, 0x07);

    hi6522_write_byte(0x64, 0x26);
    hi6522_write_byte(0x69, 0x0F);
    /*scharger v220 need not to config 0x56 0x5e*/
    //hi6522_write_byte(0x56, 0x1A);
    //hi6522_write_byte(0x5E, 0x1D);
    hi6522_write_byte(0x58, 0x2F);
    hi6522_write_byte(0x59, 0x6C);
    hi6522_write_byte(0x5B, 0xF9);
    hi6522_write_byte(0x5D, 0x33);
    hi6522_write_byte(0x65, 0x12);
	hi6522_write_byte(0x33, 0x08);
	hi6522_write_byte(0x23, 0x85);

	hi6522_write_byte(0x63, 0x18);
    return 0;
}


/****************************************************************************
  Function:     scharger_power_status
  Description:  get scharger power on status .
  Input:        di :regulator id
  Output:       NA
  Return:       1:enable 0:disable other:read fail.
***************************************************************************/

int scharger_power_status(int id)
{
	int ret = 0;
	if (NULL == scharger_di){
		return -1;
	}
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG00, &scharger_di->power_on_config_reg00.value);
	if (ret){
		SCHARGER_ERR("read power_on reg00  fail ! \n");
		return ret;
	}
	ret = hi6522_read_byte(POWER_ON_CONFIG_REG01, &scharger_di->power_on_config_reg01.value);
	if (ret){
		SCHARGER_ERR("read power_on reg01  fail ! \n");
		return ret;
	}
	switch(id){
	case SCHG_BOOST1_ID://otg:
		ret = scharger_di->power_on_config_reg01.reg.otg_en_int;
		break;
	case SCHG_BOOST2_ID://wled :
		ret = scharger_di->power_on_config_reg01.reg.wled_en_int;
		break;
	case SCHG_BOOST3_ID://flash_bst:
		ret = scharger_di->power_on_config_reg00.reg.flash_bst_en_int;
		break;
	case SCHG_SOURCE1_ID://flash_led_flash:
		ret = scharger_di->power_on_config_reg00.reg.flash_led_flash_en;
		break;
	case SCHG_SOURCE2_ID://flash_led_torch:
		ret = scharger_di->power_on_config_reg00.reg.flash_led_torch_en;
		break;
	case SCHG_BOOST4_ID://lcd_boost:
		ret = scharger_di->power_on_config_reg00.reg.lcd_bst_en_int;
		break;
	case SCHG_LDO3_ID://lcd_ldo:
		ret = scharger_di->power_on_config_reg00.reg.lcd_ldo_en_int;
		break;
	case SCHG_CPN1_ID://lcd_ncp:
		ret = scharger_di->power_on_config_reg00.reg.lcd_ncp_en_int;
		break;
	case SCHG_LDO1_ID://ldo1:
		ret = scharger_di->power_on_config_reg01.reg.ldo1_200ma_en_int;
		break;
	case SCHG_LDO2_ID://ldo2:
		ret = scharger_di->power_on_config_reg01.reg.ldo2_200ma_en_int;
		break;
    case SCHG_LDO3_CPN1_ID://vsp && vsn:
        ret = (scharger_di->power_on_config_reg00.reg.lcd_ldo_en_int && scharger_di->power_on_config_reg00.reg.lcd_ncp_en_int);
        break;
	default:
		break;

	}
	return ret;

}
/****************************************************************************
  Function:     scharger_power_on
  Description:  enable scharger power .
  Input:        di :regulator id
  Output:       NA
  Return:       0:enable success other: fail.
***************************************************************************/

int scharger_power_on(int id)
{

	int ret = 0;
	if (NULL == scharger_di){
		return -1;
	}
	switch(id){
	case SCHG_BOOST1_ID://otg:
		//scharger_di->otg_en = CHG_POWER_EN;
		//scharger_di->otg_force_en= CHG_POWER_EN;
		//ret = hi6522_config_otg_enable(scharger_di);
		break;
	case SCHG_BOOST2_ID://wled :
		scharger_di->wled_en = CHG_POWER_EN;
		ret = hi6522_config_wled_enable(scharger_di);
		break;
	case SCHG_BOOST3_ID://flash_bst:
        scharger_di->flash_bst_en = CHG_POWER_EN;
		ret = hi6522_config_flash_boost_enable(scharger_di);
        udelay(500);
		break;
	case SCHG_SOURCE1_ID://flash_led_flash:
		scharger_di->flash_led_flash_en = CHG_POWER_EN;
		ret = hi6522_config_flash_led_flash_enable(scharger_di);
		break;
	case SCHG_SOURCE2_ID://flash_led_torch:
		scharger_di->flash_led_torch_en = CHG_POWER_EN;
		ret = hi6522_config_flash_led_torch_enable(scharger_di);
		break;
	case SCHG_BOOST4_ID://lcd_boost:
		scharger_di->lcd_bst_en = CHG_POWER_EN;
		ret = hi6522_config_lcd_boost_enable(scharger_di);
		break;
	case SCHG_LDO3_ID://lcd_ldo:
		scharger_di->lcd_ldo_en = CHG_POWER_EN;
		ret = hi6522_config_lcd_ldo_enable(scharger_di);
		break;
	case SCHG_CPN1_ID://lcd_ncp:
		scharger_di->lcd_ncp_en = CHG_POWER_EN;
		ret = hi6522_config_lcd_ncp_enable(scharger_di);
		break;
	case SCHG_LDO1_ID://ldo1:
		scharger_di->ldo1_200ma_en = CHG_POWER_EN;
		ret = hi6522_config_ldo1_200ma_enable(scharger_di);
		break;
	case SCHG_LDO2_ID://ldo2:
		scharger_di->ldo2_200ma_en = CHG_POWER_EN;
		ret = hi6522_config_ldo2_200ma_enable(scharger_di);;
		break;
	case SCHG_LDO3_CPN1_ID://vsp && vsn
		scharger_di->lcd_ldo_en = CHG_POWER_EN;
		scharger_di->lcd_ncp_en = CHG_POWER_EN;
		ret = hi6522_config_lcd_ldo_ncp_enable(scharger_di);
		break;

	default:
		break;

	}
	return ret;

}
/****************************************************************************
  Function:     scharer_power_off
  Description:  disable scharger power .
  Input:        di :regulator id
  Output:       NA
  Return:       0:disable success other: fail.
***************************************************************************/

int scharger_power_off(int id)
{
	int ret = 0;
	if (NULL == scharger_di){
		return -1;
	}
	switch(id){
	case SCHG_BOOST1_ID://otg:
		scharger_di->otg_en = CHG_POWER_DIS;
		//scharger_di->otg_force_en= CHG_POWER_DIS;
		//ret = hi6522_config_otg_enable(scharger_di);
		break;
	case SCHG_BOOST2_ID://wled :
		scharger_di->wled_en = CHG_POWER_DIS;
		ret = hi6522_config_wled_enable(scharger_di);
		break;
	case SCHG_BOOST3_ID://flash_bst:
	    mdelay(3);
        scharger_di->flash_bst_en = CHG_POWER_DIS;
		ret = hi6522_config_flash_boost_enable(scharger_di);
		break;
	case SCHG_SOURCE1_ID://flash_led_flash:
		scharger_di->flash_led_flash_en = CHG_POWER_DIS;
		ret = hi6522_config_flash_led_flash_enable(scharger_di);
		break;
	case SCHG_SOURCE2_ID://flash_led_torch:
		scharger_di->flash_led_torch_en = CHG_POWER_DIS;
		ret = hi6522_config_flash_led_torch_enable(scharger_di);
		break;
	case SCHG_BOOST4_ID://lcd_boost:
		scharger_di->lcd_bst_en = CHG_POWER_DIS;
		ret = hi6522_config_lcd_boost_enable(scharger_di);
		break;
	case SCHG_LDO3_ID://lcd_ldo:
		scharger_di->lcd_ldo_en = CHG_POWER_DIS;
		ret = hi6522_config_lcd_ldo_enable(scharger_di);
		break;
	case SCHG_CPN1_ID://lcd_ncp:
		scharger_di->lcd_ncp_en = CHG_POWER_DIS;
		ret = hi6522_config_lcd_ncp_enable(scharger_di);
		break;
	case SCHG_LDO1_ID://ldo1:
		scharger_di->ldo1_200ma_en = CHG_POWER_DIS;
		ret = hi6522_config_ldo1_200ma_enable(scharger_di);
		break;
	case SCHG_LDO2_ID://ldo2:
		scharger_di->ldo2_200ma_en = CHG_POWER_DIS;
		ret = hi6522_config_ldo2_200ma_enable(scharger_di);
		break;
	case SCHG_LDO3_CPN1_ID://vsp && vsn
		scharger_di->lcd_ncp_en = CHG_POWER_DIS;
		ret = hi6522_config_lcd_ncp_enable(scharger_di);
		mdelay(5);
		scharger_di->lcd_ldo_en = CHG_POWER_DIS;
		ret = hi6522_config_lcd_ldo_enable(scharger_di);
		break;
	default:
		break;

	}

	return ret;

}

/****************************************************************************
  Function:     scharger_power_set_voltage
  Description:  set scharger power voltage .
  Input:        vset_regs,mask,shift,index
  Output:       NA
  Return:       0:disable success other: fail.
***************************************************************************/

int scharger_power_set_voltage(unsigned int vset_regs,unsigned int mask,int shift,int index)
{
	int ret = 0;
	struct hi6522_device_info *di;
	unsigned char reg_value = 0;

	if (NULL == scharger_di){
		SCHARGER_ERR("hi6522 scharger_id is null! \n");
		return -1;
	}
	di = scharger_di;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("scharger_power_set_voltage get sema fail! \n");
		return -EINTR;
	}
	/*set voltage*/
	ret = hi6522_read_byte((u8)vset_regs,&reg_value);
	CHG_REG_SETBITS(reg_value ,shift, mask, index);
	ret |= hi6522_write_byte((u8)vset_regs, reg_value);
	up(&di->charger_data_busy_lock);
	return ret;
}

/****************************************************************************
  Function:     scharger_power_get_voltage_index
  Description:  get scharger power voltage index.
  Input:        vget_regs,mask,shift
  Output:       NA
  Return:       voltage index.
***************************************************************************/
int scharger_power_get_voltage_index(unsigned int vget_regs,unsigned int mask,int shift)
{
	int ret = 0;
	struct hi6522_device_info *di;
	unsigned char reg_value = 0;
	int index = 0;
	if (NULL == scharger_di){
		return -1;
	}
	di = scharger_di;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("scharger_power_get_current_limit get sema fail! \n");
		return -EINTR;
	}
	/*get voltage*/
	ret = hi6522_read_byte((u8)vget_regs,&reg_value);
	index = CHG_REG_GETBITS(reg_value, shift, mask);
	up(&di->charger_data_busy_lock);
	return index;

}

/****************************************************************************
  Function:     scharger_power_set_current_limit
  Description:  set scharger power current .
  Input:        vset_regs:reg,mask:mask bits,shift:shift value
  Output:       NA
  Return:       0:disable success other: fail.
***************************************************************************/
int scharger_power_set_current_limit(unsigned int vset_regs,unsigned int mask,int shift,int index)
{
	int ret = 0;
	struct hi6522_device_info *di;
	unsigned char reg_value = 0;

	if (NULL == scharger_di){
		SCHARGER_ERR("hi6522 scharger_id is null! \n");
		return -1;
	}
	di = scharger_di;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("scharger_power_set_current_limit get sema fail! \n");
		return -EINTR;
	}
	/*set current*/
	ret = hi6522_read_byte((u8)vset_regs,&reg_value);
	CHG_REG_SETBITS(reg_value ,shift, mask, index);
	ret |= hi6522_write_byte((u8)vset_regs, reg_value);
	up(&di->charger_data_busy_lock);
	return ret;
}
/****************************************************************************
  Function:     scharger_power_get_current_limit_index
  Description:  get scharger power current index.
  Input:        vget_regs,mask,shift
  Output:       NA
  Return:       voltage index
***************************************************************************/
int scharger_power_get_current_limit_index(unsigned int vget_regs,unsigned int mask,int shift)
{
	int ret = 0;
	struct hi6522_device_info *di;
	unsigned char reg_value = 0;
	int index = 0;

	if (NULL == scharger_di){
		return -1;
	}
	di = scharger_di;
	if (down_interruptible(&di->charger_data_busy_lock)){
		SCHARGER_ERR("scharger_power_get_current_limit get sema fail! \n");
		return -EINTR;
	}
	/*get current*/
	ret = hi6522_read_byte((u8)vget_regs,&reg_value);
	index = CHG_REG_GETBITS(reg_value, shift, mask);
	up(&di->charger_data_busy_lock);
	return index;
}

/****************************************************************************
  Function:     scharger_flash_led_timeout_enable
  Description:  enable flash led timeout.
  Input:        lightness
  Output:       NA
  Return:       0:enable success other: fail.
***************************************************************************/
int scharger_flash_led_timeout_enable(void)
{
	if (NULL == scharger_di){
		return -1;
	}
	scharger_di->chg_flash_led_timeout_en = 1;
    return hi6522_config_flash_led_timeout_enable(scharger_di);
}

/****************************************************************************
  Function:     scharger_flash_led_timeout_disable
  Description:  disable flash led timeout.
  Input:        lightness
  Output:       NA
  Return:       0:enable success other: fail.
***************************************************************************/
int scharger_flash_led_timeout_disable(void)
{
	if (NULL == scharger_di){
		return -1;
	}
	scharger_di->chg_flash_led_timeout_en = 0;
    return hi6522_config_flash_led_timeout_enable(scharger_di);
}

/****************************************************************************
  Function:     scharger_flash_led_timeout_config
  Description:  config flash led timeout.
  Input:        timeOutMs
  Output:       NA
  Return:       0:config success other: fail.
***************************************************************************/
int scharger_flash_led_timeout_config(unsigned int timeoutMs)
{
	if (NULL == scharger_di){
		return -1;
	}

	scharger_di->chg_flash_led_timeout = timeoutMs;

    return hi6522_config_flash_led_timeout(scharger_di);
}

/****************************************************************************
  Function:     scharger_flash_torch_timeout_config
  Description:  config flash torch timeout.
  Input:        timeoutSec
  Output:       NA
  Return:       0:config success other: fail.
***************************************************************************/
int scharger_flash_torch_timeout_config(unsigned int timeoutSec)
{
	if (NULL == scharger_di){
		return -1;
	}

	scharger_di->chg_flash_torch_timeout = timeoutSec;

    return hi6522_config_flash_torch_timeout(scharger_di);
}
/**********************************************************
*  Function:     hi6522_chip_init()
*  Discription:  chip init for hi6523
*  Parameters:   NULL
*  return value:
*                 0-sucess or others-fail
**********************************************************/
int hi6522_chip_init(void)
{
    int ret = 0;
    struct hi6522_device_info *di = g_hi6522_dev;
    if (NULL == di)
    {
        SCHARGER_ERR("%s hi6522_device_info is NULL!\n",__func__);
        return -ENOMEM;
    }

    ret |= hi6522_config_opt_param();
    ret |= hi6522_set_fast_safe_timer(CHG_FAST_SAFE_TIMER_8H);
    ret |= hi6522_set_term_enable(CHG_TERM_DIS);
    ret |= hi6522_set_input_current(IINLIM_500);
    ret |= hi6522_set_charge_current(CHG_FAST_ICHG_VALUE(500));
    ret |= hi6522_set_terminal_voltage(CHG_FAST_VCHG_VALUE(4350));
    ret |= hi6522_set_terminal_current(CHG_TERM_ICHG_150MA);
    ret |= hi6522_set_watchdog_timer(WATCHDOG_TIMER_40_S);
    ret |= hi6522_set_precharge_current(CHG_PRG_ICHG_200MA);
    ret |= hi6522_set_precharge_voltage(CHG_PRG_VCHG_2800);
    ret |= hi6522_set_batfet_ctrl(CHG_BATFET_EN);
    ret |= hi6522_set_dpm_voltage(VINDPM_4520);
    /*IR compensation voatge clamp ,IR compensation resistor setting */
    ret |= hi6522_set_vclamp(di->param_dts.vclamp);
    ret |= hi6522_set_otg_current(BOOST_LIM_MAX);
    ret |= hi6522_set_otg_enable(CHG_OTG_FORCE_DIS);

    return ret;
}

/**********************************************************
*  Function:        hi6522_get_ibus_ma
*  Discription:     get ibus
*  Parameters:     none
*  return value:   -1:fail;  other: ibus
**********************************************************/
int hi6522_get_ibus_ma(void)
{
    int ret = 0;
    u32 ibus = 0;
    u32 state = 0;

    ret |= hi6522_get_charge_state(&state);
    if(ret)
    {
        SCHARGER_ERR("[%s] get_charge_state fail,ret:%d\n",__func__,ret);
        return -1;
    }
    if(CHAGRE_STATE_NOT_PG & state)
    {
        SCHARGER_INF("[%s] CHAGRE_STATE_NOT_PG ,state:%d\n",__func__,state);
        return 0;
    }
    /*SchargerV200 do not support get-ibus function, for RunnintTest, we return a fake vulue*/
    ibus = 1000;//fake current value for Running test
    SCHARGER_INF("SchargerV200: ibus = %d, RunningTest Begin!\n", ibus);//Temperary log for RT flag

    return ibus;
}
/**********************************************************
*  Function:       hi6522_set_charger_hiz
*  Discription:    set the charger ovlo_47 to close ibus
*  Parameters:   enable:charger in hiz or not
*  return value:  0-sucess or others-fail
**********************************************************/
int hi6522_set_charger_hiz(int enable)
{
    struct hi6522_device_info *di = g_hi6522_dev;
    if(di->ovlo_flag == 1){
      SCHARGER_ERR("[%s] HIZ,ovlo is not used\n",__func__);
      return 0;
    }
    if(enable == 1){
         SCHARGER_ERR("[%s] HIZ,enable:%d\n",__func__,enable);
         return gpio_direction_output(di->gpio_ovlo_en,1);
    }
    else{
        SCHARGER_ERR("[%s] HIZ,enable:%d\n",__func__,enable);
        return gpio_direction_output(di->gpio_ovlo_en,0);
    }
}

/**********************************************************
*  Function:       hi6522_get_charge_state
*  Discription:    get the charge states in charging process
*  Parameters:   state:charge states
*  return value:  0-sucess or others-fail
**********************************************************/
int hi6522_get_charge_state(unsigned int *state)
{
    u8 reg1 = 0, reg2 = 0, reg3 = 0;
    int ret = 0;

    ret |= hi6522_read_byte(CHG_REG6,&reg1);
    ret |= hi6522_read_byte(CHG_STATUS0,&reg2);
    ret |= hi6522_read_byte(CHG_STATUS1,&reg3);
    if (ret)
    {
        SCHARGER_ERR("[%s]read charge status reg fail,ret:%d\n",__func__,ret);
        return -1;
    }

    if((reg1 & CHG_BUCK_OK) != CHG_BUCK_OK)
    {
        *state |= CHAGRE_STATE_NOT_PG;
    }
    if((reg2 & CHG_STATUS0_STAT_CHAEGE_DONE) == CHG_STATUS0_STAT_CHAEGE_DONE)
    {
        *state |= CHAGRE_STATE_CHRG_DONE;
    }
    if((reg2 & CHG_STATUS0_WDT_TIMER_OUT_MASK_BIT) == CHG_STATUS0_WDT_TIMER_OUT)
    {
        *state |= CHAGRE_STATE_WDT_FAULT;
    }
    if((reg3 & CHG_STATUS1_VBUS_OVP_6P5V) == CHG_STATUS1_VBUS_OVP_6P5V)
    {
        *state |= CHAGRE_STATE_VBUS_OVP;
    }
    #if 0
    if((reg & hi6522_BAT_FAULT_OVP) == hi6522_BAT_FAULT_OVP)
    {
        *state |= CHAGRE_STATE_BATT_OVP;
    }
    #endif
    SCHARGER_INF("[%s],state:%d, reg1 = 0x%x, reg2 = 0x%x\n",__func__,*state, reg1, reg2);
    return ret;
}

static int dpm_check_current_threshold_ma = 40;
module_param(dpm_check_current_threshold_ma, int, 0644);

static int dpm_switch_delay_time_ms = 200;
module_param(dpm_switch_delay_time_ms, int, 0644);

static int dpm_check_delay_time_ms = 1000;
module_param(dpm_check_delay_time_ms, int, 0644);

static int dpm_switch_with_charge_stop = 1;
module_param(dpm_switch_with_charge_stop, int, 0644);

static void hi6522_dpm_check_work(struct work_struct *work)
{
    int current_ma;
	unsigned char chg_en_status = 0;
    struct hi6522_device_info *di = container_of(work,
                 struct hi6522_device_info, hi6522_dpm_check_work.work);

    current_ma = hisi_battery_current();
    if ((current_ma > dpm_check_current_threshold_ma) || (dpm_switch_enable)){
        unsigned char reg;
        SCHARGER_INF("hi6522_dpm_check_work cur=%dmA do dpm switch\n", current_ma);

        if (dpm_switch_with_charge_stop){
            down_interruptible(&di->charger_data_busy_lock);
			chg_en_status = di->chg_en;
            di->chg_en = CHG_POWER_DIS;
            hi6522_config_charger_nolock_enable(di);
            hi6522_read_byte(BUCK_REG5_REG,&reg);
            reg = reg|0x08;
    		hi6522_write_byte(BUCK_REG5_REG, reg);
            msleep(dpm_switch_delay_time_ms);
            reg = reg&(~0x08);
    		hi6522_write_byte(BUCK_REG5_REG, reg);
			di->chg_en = chg_en_status;
            hi6522_config_charger_nolock_enable(di);
            up(&di->charger_data_busy_lock);
        }
        else{
            hi6522_read_byte(BUCK_REG5_REG,&reg);
            reg = reg|0x08;
    		hi6522_write_byte(BUCK_REG5_REG, reg);
            msleep(dpm_switch_delay_time_ms);
            reg = reg&(~0x08);
    		hi6522_write_byte(BUCK_REG5_REG, reg);
        }
    }

    schedule_delayed_work(&di->hi6522_dpm_check_work,
                 msecs_to_jiffies(dpm_check_delay_time_ms));
}
int hi6522_lcd_ldo_clear_int(void)
{
    u8 reg =0;
    struct hi6522_device_info *di;
    di = g_hi6522_dev;
    if (NULL == di)
    {
        SCHARGER_ERR("%s hi6522_device_info is NULL!\n",__func__);
        return -ENOMEM;
    }

    hi6522_read_byte(CHG_IRQ_REG3,&reg);
    reg = reg | HI6522_LCD_LDO_OCP_CLEAR_BIT;
    hi6522_write_byte(CHG_IRQ_REG3,reg);
    SCHARGER_INF("clear lcd ldo ocp reg is %d\n", reg);
    return 0;
}
EXPORT_SYSMOL_GPL(hi6522_lcd_ldo_clear_int);

struct charge_device_ops hi6522_ops = {
    .chip_init = hi6522_chip_init,
    .set_input_current = hi6522_set_input_current,
    .set_charge_current = hi6522_set_charge_current,
    .set_terminal_voltage = hi6522_set_terminal_voltage,
    .set_dpm_voltage = hi6522_set_dpm_voltage,
    .set_terminal_current = hi6522_set_terminal_current,
    .set_charge_enable = hi6522_set_charge_enable,
    .set_otg_enable = hi6522_set_otg_enable,
    .set_term_enable = hi6522_set_term_enable,
    .get_charge_state = hi6522_get_charge_state,
    .reset_watchdog_timer = hi6522_reset_watchdog_timer,
    .dump_register = hi6522_dump_register,
    .get_register_head = hi6522_get_register_head,
    .set_watchdog_timer = hi6522_set_watchdog_timer,
    .set_batfet_disable = hi6522_set_batfet_disable,
    .set_otg_current = hi6522_set_otg_current,
    .get_ibus = hi6522_get_ibus_ma,
    .set_charger_hiz = hi6522_set_charger_hiz,
};

static irqreturn_t hi6522_irq_handle(int irq, void *data)
{
	struct hi6522_device_info *di = (struct hi6522_device_info *)data;
	schedule_work(&di->irq_work);
	disable_irq_nosync(di->irq_int);

	return IRQ_HANDLED;
}
static void hi6522_irq_work_handle(struct work_struct *work)
{
    struct hi6522_device_info *di = container_of(work, struct hi6522_device_info, irq_work);
    unsigned char irq_status[5] = {0};
    static u8 flash_bst_scp_cnt = 0;
    static u8 otg_scp_cnt = 0;
    static u8 otg_uvp_cnt = 0;
    static u8 reg_read = 0;

	/*save irq status*/
	hi6522_read_byte(CHG_IRQ_REG0,&irq_status[0]);
	hi6522_read_byte(CHG_IRQ_REG1,&irq_status[1]);
	hi6522_read_byte(CHG_IRQ_REG2,&irq_status[2]);
	hi6522_read_byte(CHG_IRQ_REG3,&irq_status[3]);
	hi6522_read_byte(CHG_IRQ_REG4,&irq_status[4]);

	    /*handle irq*/
    if (irq_status[0] & CHG_IRQ0_VBUS_FAST_CHG_FAULT){
        SCHARGER_ERR("SCHARGER ERROR:FAST_CHG_FAULT!,reg[0x07]:0x%x.\n",irq_status[0]);
    }

    if (irq_status[0] & CHG_IRQ0_VBUS_PRE_CHG_FAULT){
        SCHARGER_ERR("SCHARGER ERROR:PRE_CHG_FAULT!,reg[0x07]:0x%x.\n",irq_status[0]);
    }

    if (irq_status[0] & CHG_IRQ0_VBUS_TRICKLE_CHG_FAULT){
        SCHARGER_ERR("SCHARGER ERROR:TRICKLE_CHG_FAULT!,reg[0x07]:0x%x.\n",irq_status[0]);
    }

    if (irq_status[1] & CHG_IRQ1_BUCK_SCP){
        SCHARGER_ERR("SCHARGER ERROR:BUCK_SCP,reg[0x08]:0x%x.\n",irq_status[1]);
    }

    if (irq_status[1] & CHG_IRQ1_WLED_OVP_38V){
        di->wled_en = CHG_POWER_DIS;
        hi6522_config_wled_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ1_WLED_OVP_38V,reg[0x08]:0x%x.\n",irq_status[1]);
    }

    if (irq_status[1] & CHG_IRQ1_WLED_OVP_4P5V){
        di->wled_en = CHG_POWER_DIS;
        hi6522_config_wled_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ1_WLED_OVP_4P5V,reg[0x08]:0x%x.\n",irq_status[1]);
    }

    if (irq_status[1] & CHG_IRQ1_WLED_UVP){
        di->wled_en = CHG_POWER_DIS;
        hi6522_config_wled_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ1_WLED_UVP,reg[0x08]:0x%x.\n",irq_status[1]);
    }

    if (irq_status[1] & CHG_IRQ1_WLED_SCP){
        di->wled_en = CHG_POWER_DIS;
        hi6522_config_wled_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ1_WLED_SCP,reg[0x08]:0x%x.\n",irq_status[1]);
    }

    if (irq_status[2] & CHG_IRQ2_FLASH_BST_UVP){
        di->flash_bst_en = CHG_POWER_DIS;
        hi6522_config_flash_boost_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ2_FLASH_BST_UVP,reg[0x09]:0x%x.\n",irq_status[2]);
    }

    if (irq_status[2] & CHG_IRQ2_FLASH_BST_OVP){
        di->flash_bst_en = CHG_POWER_DIS;
        hi6522_config_flash_boost_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ2_FLASH_BST_OVP,reg[0x09]:0x%x.\n",irq_status[2]);
    }

    if (irq_status[2] & CHG_IRQ2_FLASH_BST_SCP){
    /*To avoid Scharger v210 chip problem*/
        flash_bst_scp_cnt++;
        if (flash_bst_scp_cnt > 3){
            di->flash_bst_en = CHG_POWER_DIS;
            hi6522_config_flash_boost_enable(di);
            SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ2_FLASH_BST_SCP,reg[0x09]:0x%x.\n",irq_status[2]);
            flash_bst_scp_cnt = 0;
        }
    }

    if (irq_status[2] & CHG_IRQ2_FLASH_LED_SHORT){
        di->flash_led_flash_en = CHG_POWER_DIS;
        di->flash_led_torch_en = CHG_POWER_DIS;
        hi6522_config_flash_led_flash_enable(di);
        hi6522_config_flash_led_torch_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ2_FLASH_LED_SHORT,reg[0x09]:0x%x.\n",irq_status[2]);
    }

    if (irq_status[2] & CHG_IRQ2_FLASH_LED_OPEN){
        di->flash_led_flash_en = CHG_POWER_DIS;
        di->flash_led_torch_en = CHG_POWER_DIS;
        hi6522_config_flash_led_flash_enable(di);
        hi6522_config_flash_led_torch_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ2_FLASH_LED_OPEN,reg[0x09]:0x%x.\n",irq_status[2]);
    }

    if (irq_status[3] & CHG_IRQ3_LCD_NCP_SCP){
        di->lcd_bst_en = CHG_POWER_DIS;
        di->lcd_ncp_en = CHG_POWER_DIS;
        di->lcd_ldo_en = CHG_POWER_DIS;
        hi6522_config_lcd_ncp_enable(di);
        hi6522_config_lcd_ldo_enable(di);
        hi6522_config_lcd_boost_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ3_LCD_NCP_SCP,reg[0x0A]:0x%x.\n",irq_status[3]);
    }

    if (irq_status[3] & CHG_IRQ3_LCD_BST_UVP){
        di->lcd_bst_en = CHG_POWER_DIS;
        di->lcd_ncp_en = CHG_POWER_DIS;
        di->lcd_ldo_en = CHG_POWER_DIS;
        hi6522_config_lcd_ncp_enable(di);
        hi6522_config_lcd_ldo_enable(di);
        hi6522_config_lcd_boost_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ3_LCD_BST_UVP,reg[0x0A]:0x%x.\n",irq_status[3]);
    }

    if (irq_status[3] & CHG_IRQ3_LCD_BST_OVP){
        di->lcd_bst_en = CHG_POWER_DIS;
        di->lcd_ncp_en = CHG_POWER_DIS;
        di->lcd_ldo_en = CHG_POWER_DIS;
        hi6522_config_lcd_ncp_enable(di);
        hi6522_config_lcd_ldo_enable(di);
        hi6522_config_lcd_boost_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ3_LCD_BST_OVP,reg[0x0A]:0x%x.\n",irq_status[3]);
    }

    if (irq_status[3] & CHG_IRQ3_LCD_BST_SCP){
        hi6522_read_byte(SOC_SCHARGER_LCD_BOOST_REG10_ADDR(0), &reg_read);
        if (0x55 == reg_read){
            hi6522_write_byte(SOC_SCHARGER_LCD_BOOST_REG10_ADDR(0), 0x54);
            di->lcd_bst_en = CHG_POWER_DIS;
            di->lcd_ncp_en = CHG_POWER_DIS;
            di->lcd_ldo_en = CHG_POWER_DIS;
            hi6522_config_lcd_ncp_enable(di);
            hi6522_config_lcd_ldo_enable(di);
            hi6522_config_lcd_boost_enable(di);
            hi6522_write_byte(SOC_SCHARGER_LCD_BOOST_REG10_ADDR(0), 0x55);
        }
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ3_LCD_BST_SCP,reg[0x0A]:0x%x.\n",irq_status[3]);
    }

    if (irq_status[3] & CHG_IRQ3_LCD_LDO_OCP){
        di->lcd_bst_en = CHG_POWER_DIS;
        di->lcd_ncp_en = CHG_POWER_DIS;
        di->lcd_ldo_en = CHG_POWER_DIS;
        hi6522_config_lcd_ncp_enable(di);
        hi6522_config_lcd_ldo_enable(di);
        hi6522_config_lcd_boost_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ3_LCD_LDO_OCP,reg[0x0A]:0x%x.\n",irq_status[3]);
    }

    if (irq_status[3] & CHG_IRQ3_LDO1_200MA_OCP){
        di->ldo1_200ma_en= CHG_POWER_DIS;
        hi6522_config_ldo1_200ma_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ3_LDO1_200MA_OCP,reg[0x0A]:0x%x.\n",irq_status[3]);
    }

    if (irq_status[3] & CHG_IRQ3_LDO2_200MA_OCP){
        di->ldo2_200ma_en= CHG_POWER_DIS;
        hi6522_config_ldo2_200ma_enable(di);
        SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ3_LDO2_200MA_OCP,reg[0x0A]:0x%x.\n",irq_status[3]);
    }

    if (irq_status[4] & CHG_IRQ4_OTG_SCP){
            otg_scp_cnt++;
	        hi6522_write_byte(CHG_IRQ_REG4,irq_status[4] & CHG_IRQ4_OTG_SCP);
            msleep(600);
            hi6522_read_byte(CHG_STATUS0,&reg_read);
            if ((reg_read & CHG_STATUS0_OTG_ON) == CHG_STATUS0_OTG_ON){
                otg_scp_cnt = 0;
                }
            if (otg_scp_cnt > 3){
                otg_scp_cnt = 0;
                hi6522_set_otg_enable(CHG_POWER_DIS);
                SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ4_OTG_SCP,reg[0x0B]:0x%x.\n",irq_status[4]);
            }
    }

    if (irq_status[4] & CHG_IRQ4_OTG_UVP){
            otg_uvp_cnt++;
            hi6522_write_byte(CHG_IRQ_REG4,irq_status[4] & CHG_IRQ4_OTG_UVP);
            msleep(600);
            hi6522_read_byte(CHG_STATUS0,&reg_read);
            if ((reg_read & CHG_STATUS0_OTG_ON) == CHG_STATUS0_OTG_ON){
                otg_uvp_cnt = 0;
                }
            if (otg_uvp_cnt > 3){
                otg_uvp_cnt = 0;
                hi6522_set_otg_enable(CHG_POWER_DIS);
                SCHARGER_ERR("SCHARGER ERROR:CHG_IRQ4_OTG_UVP,reg[0x0B]:0x%x.\n",irq_status[4]);
            }
    }
	/*clean irq*/
	hi6522_write_byte(CHG_IRQ_REG0,irq_status[0]);
	hi6522_write_byte(CHG_IRQ_REG1,irq_status[1]);
	hi6522_write_byte(CHG_IRQ_REG2,irq_status[2]);
	hi6522_write_byte(CHG_IRQ_REG3,irq_status[3]);
	hi6522_write_byte(CHG_IRQ_REG4,irq_status[4]);

	enable_irq(di->irq_int);
}
static BLOCKING_NOTIFIER_HEAD(scharger_init_notifier_list);

int scharger_register_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&scharger_init_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(scharger_register_notifier);

int scharger_unregister_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&scharger_init_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(scharger_unregister_notifier);

static void scharger_notify_prepare(void)
{
blocking_notifier_call_chain(&scharger_init_notifier_list,0,NULL);
}
static BLOCKING_NOTIFIER_HEAD(lcd_ldo_ocp_init_notifier_list);

int lcd_ldo_ocp_register_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&lcd_ldo_ocp_init_notifier_list, nb);
}

EXPORT_SYMBOL_GPL(lcd_ldo_ocp_register_notifier);

int lcd_ldo_ocp_unregister_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&lcd_ldo_ocp_init_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(lcd_ldo_ocp_unregister_notifier);

static void lcd_ldo_ocp_notify_prepare(void)
{
    blocking_notifier_call_chain(&lcd_ldo_ocp_init_notifier_list,HI6522_LCD_LDO_OCP_EVENT,NULL);
}

static int hi6522_dpm_switch_notifier_call(struct notifier_block *usb_nb,
                        unsigned long event, void *data)
{
    struct hi6522_device_info *di =
          container_of(usb_nb, struct hi6522_device_info, usb_nb);
    switch (event) {
    case CHARGER_TYPE_SDP:
    case CHARGER_TYPE_DCP:
    case CHARGER_TYPE_CDP:
    case CHARGER_TYPE_UNKNOWN:
        schedule_delayed_work(&di->hi6522_dpm_check_work,msecs_to_jiffies(0));
        break;
    case CHARGER_TYPE_NONE:
        cancel_delayed_work_sync(&di->hi6522_dpm_check_work);
        break;
    case PLEASE_PROVIDE_POWER:
        break;
    default:
        return NOTIFY_OK;
    }

    return NOTIFY_OK;
}
/**********************************************************
*  Function:       parse_dts
*  Discription:    parse_dts
*  Parameters:   device_node:hi6522 device_node
*                      _di:hi6522_device_info
*  return value:  NULL
**********************************************************/
static void parse_dts(struct device_node *np,struct hi6522_device_info *di)
{
    int ret = 0;
    struct device_node *batt_node;
    di->param_dts.vclamp = 80;

    ret = of_property_read_u32(np, "vclamp", &(di->param_dts.vclamp));
    if(ret)
    {
        SCHARGER_ERR("get vclamp failed\n");
        return ;
    }
    SCHARGER_INF("prase_dts vclamp = %d\n",di->param_dts.vclamp);

    ret = of_property_read_u32( np,"fcp_support",&(di->param_dts.fcp_support));
    if(ret)
    {
        SCHARGER_ERR("get fcp_support failed\n");
        return ;
    }

    batt_node = of_find_compatible_node(NULL, NULL, "huawei,hisi_bci_battery");
    if (batt_node) {
        of_property_read_u32(batt_node, "battery_board_type",&is_board_type);
    } else {
		SCHARGER_ERR( "get board type fail\n");
	}
	SCHARGER_ERR( "get board type is %d !\n",is_board_type );
    return ;
}
static int  hi6522_charger_probe(struct i2c_client *client,
                           const struct i2c_device_id *id)
{
    struct hi6522_device_info *di;
    int ret = 0;
    u8 read_reg = 0;
	struct class *power_class = NULL;
	struct device_node* np;
    enum hisi_charger_type type = hisi_get_charger_type();

    di = kzalloc(sizeof(*di), GFP_KERNEL);
    if (NULL == di) {
        SCHARGER_ERR("hi6522_device_info is NULL!\n");
        return -ENOMEM;
    }
    g_hi6522_dev = di;
    scharger_di = di;
	sema_init(&di->charger_data_busy_lock, 1);
    di->dev = &client->dev;
	np = di->dev->of_node;
    di->client = client;

    i2c_set_clientdata(client, di);
    parse_dts(np,di);

    ret = hi6522_read_byte(SOC_SCHARGER_CHIP_VERSION_ADDR(0), &read_reg);
    if (ret < 0) {
        SCHARGER_ERR("chip not present at address %x\n",
                     client->addr);
        ret = -EINVAL;
        goto err_kfree;
    }

	/*set irq init*/
	di->charge_irq_mask0_reg.value = 0xFF;
	di->charge_irq_mask1_reg.value = 0xFF;
	di->charge_irq_mask2_reg.value = 0xFF;
	di->charge_irq_mask3_reg.value = 0xFF;
	di->charge_irq_mask4_reg.value = 0xFF;
    di->charge_irq_mask0_reg.reg.trickle_chg_fault_rm = CHG_IRQ_EN;
    di->charge_irq_mask0_reg.reg.pre_chg_fault_rm     = CHG_IRQ_EN;
    di->charge_irq_mask0_reg.reg.fast_chg_fault_rm    = CHG_IRQ_EN;
    di->charge_irq_mask1_reg.reg.wled_scp_rm          = CHG_IRQ_EN;
    di->charge_irq_mask1_reg.reg.buck_scp_rm          = CHG_IRQ_EN;
    di->charge_irq_mask1_reg.reg.wled_uvp_rm          = CHG_IRQ_EN;
    di->charge_irq_mask1_reg.reg.wled_ovp_4p5v_rm     = CHG_IRQ_EN;
    di->charge_irq_mask1_reg.reg.wled_ovp_38v_rm      = CHG_IRQ_EN;
    di->charge_irq_mask2_reg.reg.flash_bst_uvp_rm     = CHG_IRQ_EN;
    di->charge_irq_mask2_reg.reg.flash_bst_ovp_rm     = CHG_IRQ_EN;
    di->charge_irq_mask2_reg.reg.flash_bst_scp_rm     = CHG_IRQ_EN;
    di->charge_irq_mask2_reg.reg.flash_led_short_rm   = CHG_IRQ_EN;
    di->charge_irq_mask2_reg.reg.flash_led_open_rm    = CHG_IRQ_EN;
    di->charge_irq_mask3_reg.reg.lcd_ncp_scp_rm       = CHG_IRQ_EN;
    di->charge_irq_mask3_reg.reg.lcd_bst_uvp_rm       = CHG_IRQ_EN;
    di->charge_irq_mask3_reg.reg.lcd_bst_ovp_rm       = CHG_IRQ_EN;
    di->charge_irq_mask3_reg.reg.lcd_bst_scp_rm       = CHG_IRQ_EN;
    di->charge_irq_mask3_reg.reg.lcd_ldo_ocp_rm       = CHG_IRQ_EN;
    di->charge_irq_mask3_reg.reg.ldo1_200ma_ocp_rm    = CHG_IRQ_EN;
    di->charge_irq_mask3_reg.reg.ldo2_200ma_ocp_rm    = CHG_IRQ_EN;
    di->charge_irq_mask4_reg.reg.otg_uvp_rm     	  = CHG_IRQ_EN;
    di->charge_irq_mask4_reg.reg.otg_scp_rm     	  = CHG_IRQ_EN;

	/*interrput init*/
	hi6522_write_byte(CHG_IRQ_MASK_REG0, di->charge_irq_mask0_reg.value);
	hi6522_write_byte(CHG_IRQ_MASK_REG1, di->charge_irq_mask1_reg.value);
	hi6522_write_byte(CHG_IRQ_MASK_REG2, di->charge_irq_mask2_reg.value);
	hi6522_write_byte(CHG_IRQ_MASK_REG3, di->charge_irq_mask3_reg.value);
	hi6522_write_byte(CHG_IRQ_MASK_REG4, di->charge_irq_mask4_reg.value);

    INIT_WORK(&di->irq_work, hi6522_irq_work_handle);
    INIT_DELAYED_WORK(&di->hi6522_dpm_check_work,hi6522_dpm_check_work);
    di->usb_nb.notifier_call = hi6522_dpm_switch_notifier_call;
    ret = hisi_charger_type_notifier_register(&di->usb_nb);
    if (ret < 0)
    {
       SCHARGER_ERR("hisi_charger_type_notifier_register failed\n");
       goto err_io;
    }

    di->gpio_int = of_get_named_gpio(np,"gpio_int",0);
    if(!gpio_is_valid(di->gpio_int)){
        SCHARGER_ERR("%s failed %d\n", __func__, __LINE__);
        ret = -EFAULT;
        goto err_irq_gpio;
    }
	di->irq_int = gpio_to_irq(di->gpio_int);
	ret = gpio_request_one(di->gpio_int, GPIOF_IN, "Scharger_int");
	if (ret) {
		SCHARGER_ERR("no card-detect pin available!\n");
        ret = -ENOMEM;
		goto err_irq_gpio;
	}
	ret = request_irq(di->irq_int, hi6522_irq_handle,IRQF_TRIGGER_LOW | IRQF_DISABLED | IRQF_NO_SUSPEND , di->client->name, di);
	if (ret) {
		SCHARGER_ERR("request Scharger irq error\n");
		goto err_irq_request;
	}
    di->ovlo_flag = 0;
    di->gpio_ovlo_en = of_get_named_gpio(np,"gpio_ovlo_en",0);
    if(!!gpio_is_valid(di->gpio_ovlo_en)){
        ret = gpio_request(di->gpio_ovlo_en,"ovlo_en");
        if(ret<0){
            SCHARGER_ERR("%s failed %d\n", __func__, __LINE__);
            di->ovlo_flag = 1;
        }
    }
    else{
        SCHARGER_ERR("%s failed %d\n", __func__, __LINE__);
        di->ovlo_flag = 1;
    }

    ret = charge_ops_register(&hi6522_ops);
    if(ret)
    {
        SCHARGER_ERR("register charge ops failed!\n");
        goto err_sysfs;
    }
/* scharger v200 need to do dpm check when usb/charger is plugged on startup*/
    if (type < CHARGER_TYPE_NONE)
    {
        schedule_delayed_work(&di->hi6522_dpm_check_work,msecs_to_jiffies(0));
    }
    ret = hi6522_sysfs_create_group(di);
    if(ret)
    {
        SCHARGER_ERR("create sysfs entries failed!\n");
        goto err_create_group;
    }

    power_class = hw_power_get_class();
    if(power_class)
    {
        if(charge_dev == NULL)
        {
            charge_dev = device_create(power_class, NULL, 0, "%s", "charger");
            if (IS_ERR(charge_dev))
            {
                charge_dev = NULL;
                SCHARGER_ERR("create charge_dev failed!\n");
                goto err_create_group;
            }
        }
        ret = sysfs_create_link(&charge_dev->kobj, &di->dev->kobj, "HI6522");
        if (ret)
            SCHARGER_ERR("%s, create sysfs link failed!!!\n", __FUNCTION__);
    }
	scharger_notify_prepare();/*notify backlight open*/
    SCHARGER_INF("HI6522 probe ok!\n");
    return 0;

err_create_group:
    hi6522_sysfs_remove_group(di);
err_sysfs:
	free_irq(di->irq_int,di);
    if(!di->ovlo_flag)
    {
       gpio_free(di->gpio_ovlo_en);
    }
err_irq_request:
	gpio_free(di->gpio_int);
err_irq_gpio:
err_io:
err_kfree:
    kfree(di);
    di = NULL;
    g_hi6522_dev = NULL;
    scharger_di = NULL;
    return ret;
}

static int  hi6522_charger_remove(struct i2c_client *client)
{
    struct hi6522_device_info *di = i2c_get_clientdata(client);
    if (NULL == di){
        SCHARGER_ERR("%s:di is NULL\n",__func__);
        return 0;
    }
    hisi_charger_type_notifier_unregister(&di->usb_nb);
    hi6522_sysfs_remove_group(di);
    cancel_delayed_work(&di->hi6522_dpm_check_work);
	free_irq(di->irq_int,di);
	gpio_free(di->gpio_int);
    if(!di->ovlo_flag)
    {
      gpio_free(di->gpio_ovlo_en);
    }
    kfree(di);

    return 0;
}

static void hi6522_charger_shutdown(struct i2c_client *client)
{
    struct hi6522_device_info *di = i2c_get_clientdata(client);
    if (NULL == di){
        SCHARGER_ERR("%s:di is NULL\n",__func__);
        return 0;
    }
    hisi_charger_type_notifier_unregister(&di->usb_nb);
    cancel_delayed_work(&di->hi6522_dpm_check_work);
    return;
}

static const struct i2c_device_id hi6522_id[] = {
    { "hi6522_charger", 0 },
    {},
};

static int hi6522_charger_suspend(struct i2c_client *client,
              pm_message_t state)
{
    struct hi6522_device_info *di = i2c_get_clientdata(client);
    if (NULL == di){
        SCHARGER_ERR("%s:di is NULL\n",__func__);
        return 0;
    }
    SCHARGER_INF("%s:+\n",__func__);
    hi6522_config_power_on_reg01(di);
    SCHARGER_INF("%s:-\n",__func__);
    return 0;
}

static int hi6522_charger_resume(struct i2c_client *client)
{
    struct hi6522_device_info *di = i2c_get_clientdata(client);
    if (NULL == di){
        SCHARGER_ERR("%s:di is NULL\n",__func__);
        return 0;
    }
    SCHARGER_INF("%s:+\n",__func__);
    hi6522_config_power_on_reg01(di);
    SCHARGER_INF("%s:-\n",__func__);
    return 0;
}

MODULE_DEVICE_TABLE(i2c, hi6522);
static struct of_device_id hi6522_charger_match_table[] =
{
    {
	.compatible = "huawei,hi6522_charger",
	.data = NULL,
    },
    {
    },
};
static const struct i2c_device_id hi6522_i2c_id[] = {{"hi6522_charger",0},{}};
static struct i2c_driver hi6522_charger_driver = {
    .probe = hi6522_charger_probe,
    .remove = hi6522_charger_remove,
    .suspend = hi6522_charger_suspend,
    .resume = hi6522_charger_resume,
    .shutdown = hi6522_charger_shutdown,
    .id_table = hi6522_i2c_id,
    .driver = {
         .owner = THIS_MODULE,
         .name = "hi6522_charger",
    .of_match_table = of_match_ptr(hi6522_charger_match_table),
    },
};

static int __init hi6522_charger_init(void)
{
    int ret =0;

    ret =  i2c_add_driver(&hi6522_charger_driver);
    if(ret)
        SCHARGER_ERR("%s: i2c_add_driver error!!!\n", __func__);

    return ret;
}

module_init(hi6522_charger_init);

static void __exit hi6522_charger_exit(void)
{
    i2c_del_driver(&hi6522_charger_driver);
}
module_exit(hi6522_charger_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HW Inc");

int hi6522_show_power_status(void)
{
SCHARGER_ERR("power_status:\n chg_en:%d \n otg_en:%d \n"
    "wled_en:%d \n ldo1_en:%d \n ldo2_en:%d \n",
    g_hi6522_dev->chg_en,g_hi6522_dev->otg_en,
    g_hi6522_dev->wled_en,g_hi6522_dev->ldo1_200ma_en,
    g_hi6522_dev->ldo2_200ma_en);
    return 0;
}

