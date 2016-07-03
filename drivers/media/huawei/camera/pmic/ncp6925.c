/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "hw_pmic.h"
#include "../cam_log.h"
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif

/* NCP6925 Registers define */
#define CHIP_REV        0x00
#define EXTID           0x01
#define BUCK1_VOUT      0x02 /* BUCK VOUT=0.6V+BUCKx_VOUT[7:0]*0.0125      (0.6V to 2.1875V) */
#define BUCK2_VOUT      0x03
#define BUCK_VSEL       0x04
#define LDO1_VOUT       0x05 /* LDO VOUT = 0.5V + LDOx_VOUT[6:0] * 0.025V  ( Except  LDOx_VOUT[6:0] = 0x7F ) */
#define LDO2_VOUT       0x06
#define LDO3_VOUT       0x07
#define LDO4_VOUT       0x08
#define LDO5_VOUT       0x09
#define CHX_ERR         0x0a
#define CHX_EN          0x0b
//#define BUCK_SEQ_1_2  0x0c
//#define LDO_SEQ_1_2   0x0d
//#define LDO_SEQ_3_4   0x0e
//#define LDO_SEQ_5     0x0f
//#define SEQ_SPEED     0x10


#define BUCK_MIN        600000
#define BUCK_MAX        3012500
#define LDO_MIN         600000
#define LDO_MAX         3500000

#define BUCK1_ENABLE    (1<<0)
#define BUCK2_ENABLE    (1<<1)
#define LDO1_ENABLE     (1<<2)
#define LDO2_ENABLE     (1<<3)
#define LDO3_ENABLE     (1<<4)
#define LDO4_ENABLE     (1<<5)
#define LDO5_ENABLE     (1<<6)

#define MAX_ATTRIBUTE_BUFFER_SIZE       128

#define INVALID_GPIO                    999

/* Internal data struct define */
typedef enum {
    PMIC_POWER_CTRL = 0,
    GPIO_CTRL_0,
    GPIO_CTRL_1,
    MAX_PIN,
}ncp6925_pin_type;

struct ncp6925_private_data_t {

    /* pmic control pin */
    unsigned int pin[MAX_PIN];
    unsigned int voltage[VOUT_MAX];
    unsigned int chipid;
};

typedef struct {
    int chx_enable;
    int vout_reg;
}voltage_map_t;


static struct ncp6925_private_data_t ncp6925_pdata;
static struct i2c_driver ncp6925_i2c_driver;
struct hisi_pmic_ctrl_t ncp6925_ctrl;

static voltage_map_t voltage_map[VOUT_MAX] =
{
    {LDO1_ENABLE, LDO1_VOUT},
    {LDO2_ENABLE, LDO2_VOUT},
    {LDO3_ENABLE, LDO3_VOUT},
    {LDO4_ENABLE, LDO4_VOUT},
    {LDO5_ENABLE, LDO5_VOUT},
    {BUCK1_ENABLE, BUCK1_VOUT},
    {BUCK2_ENABLE, BUCK2_VOUT},
};

struct pmic_cfg_data cdata = {0};
u8 reg = 0;
u8 val = 0;

DEFINE_HISI_PMIC_MUTEX(ncp6925);

static int calc_buck_vlotage(u32 in, u8 *out);
static int calc_ldo_vlotage(u32 in, u8 *out);
static int ncp6925_seq_config(struct hisi_pmic_ctrl_t *pmic_ctrl, pmic_seq_index_t seq_index, u32 voltage, int state);

static int ncp6925_remove(struct i2c_client *client)
{
    cam_info("%s enter.", __func__);

    client->adapter = NULL;
    return 0;
}

static int ncp6925_init(struct hisi_pmic_ctrl_t *pmic_ctrl)
{
    struct hisi_pmic_i2c_client *i2c_client;
    struct hisi_pmic_i2c_fn_t *i2c_func;
    struct ncp6925_private_data_t *pdata;
    u8 device_id = 0;
    u8 external_id = 0;
    int ret = 0;

    cam_info("%s enter.", __func__);

    if (NULL == pmic_ctrl) {
        cam_err("%s pmic_ctrl is NULL.", __func__);
        return -1;
    }

    pmic_ctrl->pctrl = devm_pinctrl_get_select(pmic_ctrl->dev,
        PINCTRL_STATE_DEFAULT);

    if (NULL == pmic_ctrl->pctrl) {
        cam_err("%s failed to set pin.", __func__);
        return -EIO;
    }

    pdata = (struct ncp6925_private_data_t *)pmic_ctrl->pdata;

    cam_info("%s PMIC_POWER_CTRL = %d", __func__,
            pdata->pin[PMIC_POWER_CTRL]);

    ret = gpio_request(pdata->pin[PMIC_POWER_CTRL], "pmic-power-ctrl");
    if (ret < 0) {
        cam_err("%s failed to request pmic-power-ctrl pin.", __func__);
        goto err1;
    }

    gpio_direction_output(pdata->pin[PMIC_POWER_CTRL], 1);

    msleep(10);

    if (pdata->pin[GPIO_CTRL_0] != INVALID_GPIO) {
        ret = gpio_request(pdata->pin[GPIO_CTRL_0], "pmic-gpio-ctrl-0");
        if (ret < 0) {
            cam_err("%s failed to request gpio ctrl 0.", __func__);
            goto err1;
        }

        gpio_direction_output(pdata->pin[GPIO_CTRL_0], 1);
    }

    if (pdata->pin[GPIO_CTRL_1] != INVALID_GPIO) {
        ret = gpio_request(pdata->pin[GPIO_CTRL_1], "pmic-gpio-ctrl-1");
        if (ret < 0) {
            cam_err("%s failed to request gpio ctrl 1.", __func__);
            goto err2;
        }

        gpio_direction_output(pdata->pin[GPIO_CTRL_1], 1);
    }

    i2c_client = pmic_ctrl->pmic_i2c_client;
    i2c_func = pmic_ctrl->pmic_i2c_client->i2c_func_tbl;

    ret = i2c_func->i2c_read(i2c_client, CHIP_REV, &device_id);
    if (ret < 0) {
        cam_err("%s: read CHIP_REV failed, ret = %d ", __func__, ret);
        return ret;
    }
    cam_info("%s device id=%d", __func__,
            device_id);

    ret = i2c_func->i2c_read(i2c_client, EXTID, &external_id);
    if (ret < 0) {
        cam_err("%s: read EXTID failed, ret = %d ", __func__, ret);
        return ret;
    }
    cam_info("%s external id=%d", __func__,
            external_id);

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
    if(device_id == 0 && external_id == 0xff) {
        set_hw_dev_flag(DEV_I2C_CAMERA_PMIC);
    }
#endif


    return ret;
err2:
    gpio_free(pdata->pin[GPIO_CTRL_0]);
err1:
    gpio_free(pdata->pin[PMIC_POWER_CTRL]);
    return -EIO;
}

static int ncp6925_exit(struct hisi_pmic_ctrl_t *pmic_ctrl)
{
    struct ncp6925_private_data_t *pdata;

    cam_info("%s enter.", __func__);

    if (NULL == pmic_ctrl) {
        cam_err("%s pmic_ctrl is NULL.", __func__);
        return -1;
    }

    pdata = (struct ncp6925_private_data_t *)pmic_ctrl->pdata;
    gpio_free(pdata->pin[PMIC_POWER_CTRL]);
    pmic_ctrl->pctrl = devm_pinctrl_get_select(pmic_ctrl->dev,
        PINCTRL_STATE_IDLE);
    return 0;
}

static int ncp6925_on(struct hisi_pmic_ctrl_t *pmic_ctrl, void *data)
{
    struct hisi_pmic_i2c_client *i2c_client;
    struct hisi_pmic_i2c_fn_t *i2c_func;
    struct ncp6925_private_data_t *pdata;
    int gpio_value = 0;
    int ret = 0;

    cam_info("%s enter.", __func__);

    if (NULL == pmic_ctrl) {
        cam_err("%s pmic_ctrl is NULL.", __func__);
        return -1;
    }

    pdata = (struct ncp6925_private_data_t *)pmic_ctrl->pdata;
    i2c_client = pmic_ctrl->pmic_i2c_client;
    i2c_func = pmic_ctrl->pmic_i2c_client->i2c_func_tbl;

    gpio_value = gpio_get_value(pdata->pin[PMIC_POWER_CTRL]);
    cam_info("%s: pmic enable gpio value = %d.", __func__, gpio_value);

    i2c_func->i2c_write(i2c_client, CHX_ERR, 0x00);

    return 0;
}

static int ncp6925_off(struct hisi_pmic_ctrl_t *pmic_ctrl)
{
    struct ncp6925_private_data_t *pdata;
    cam_info("%s enter.", __func__);

    if (NULL == pmic_ctrl) {
        cam_err("%s pmic_ctrl is NULL.", __func__);
        return -1;
    }

    pdata = (struct ncp6925_private_data_t *)pmic_ctrl->pdata;
    if (NULL == pdata){
        cam_err("%s pdata is NULL.", __func__);
        return -1;
    }

    return 0;
}

static int ncp6925_match(struct hisi_pmic_ctrl_t *pmic_ctrl)
{
    cam_info("%s enter.", __func__);
    return 0;
}

static int ncp6925_get_dt_data(struct hisi_pmic_ctrl_t *pmic_ctrl)
{
    struct ncp6925_private_data_t *pdata;
    struct device_node *of_node;
    int i;
    int rc = -1;

    cam_info("%s enter.\n", __func__);

    if (NULL == pmic_ctrl) {
        cam_err("%s pmic_ctrl is NULL.", __func__);
        return rc;
    }

    pdata = (struct ncp6925_private_data_t *)pmic_ctrl->pdata;
    of_node = pmic_ctrl->dev->of_node;

    rc = of_property_read_u32_array(of_node, "hisi,pmic-pin",
            pdata->pin, MAX_PIN);
    if (rc < 0) {
        cam_err("%s failed line %d\n", __func__, __LINE__);
        return rc;
    } else {
        for (i=0; i<MAX_PIN; i++) {
            cam_info("%s pin[%d]=%d.\n", __func__, i,
                    pdata->pin[i]);
        }
    }

    rc = of_property_read_u32_array(of_node, "hisi,pmic-voltage",
            pdata->voltage, VOUT_MAX);
    if (rc < 0) {
        cam_err("%s failed line %d\n", __func__, __LINE__);
        return rc;
    } else {
        for (i=0; i<VOUT_MAX; i++) {
            cam_info("%s voltage[%d]=%d.\n", __func__, i,
                    pdata->voltage[i]);
        }
    }
    return 0;
}

static int calc_buck_vlotage(u32 in, u8 *out)
{
    int ret = -1;
    cam_info("%s enter.", __func__);
    if (in <= BUCK_MIN || in >= BUCK_MAX) {
        cam_err("do not support the buck voltage, %u", in);
        return ret;
    }
    *out = ((in - 600000) / 12500) & 0xff;
    return ret;
}

static int calc_ldo_vlotage(u32 in, u8 *out)
{
    int ret = -1;
    cam_info("%s enter, ldo in %d", __func__, in);
    if (in <= LDO_MIN || in >= LDO_MAX) {
        cam_err("do not support the ldo voltage");
        return ret;
    }
    *out = ((in - 500000) / 25000) & 0xff;
    return ret;
}

static int ncp6925_seq_config(struct hisi_pmic_ctrl_t *pmic_ctrl, pmic_seq_index_t seq_index, u32 voltage, int state)
{
    u8 chx_enable_tmp = 0;
    u8 chx_enable = 0;
    u8 voltage_reg = 0;
    u8 voltage_val = 0;
    u8 buck12_prog = 0;
    struct hisi_pmic_i2c_client *i2c_client;
    struct hisi_pmic_i2c_fn_t *i2c_func;
    int ret = 0;

    cam_info("%s enter.", __func__);

    if (NULL == pmic_ctrl) {
        cam_err("%s pmic_ctrl is NULL.", __func__);
        return -1;
    }

    i2c_client = pmic_ctrl->pmic_i2c_client;
    i2c_func = pmic_ctrl->pmic_i2c_client->i2c_func_tbl;

    chx_enable = voltage_map[seq_index].chx_enable;
    voltage_reg = voltage_map[seq_index].vout_reg;

    i2c_func->i2c_read(i2c_client, CHX_EN, &chx_enable_tmp);

    if (state == 1) {
        if (seq_index >= VOUT_BUCK_1) {
            calc_buck_vlotage(voltage, &voltage_val);
            buck12_prog = (voltage_val & 0x80)>>7;
            buck12_prog = (seq_index == VOUT_BUCK_1 ? buck12_prog : buck12_prog << 1);
        } else {
            calc_ldo_vlotage(voltage, &voltage_val);
        }

        i2c_func->i2c_write(i2c_client, voltage_reg, voltage_val);

        /* write Buck12_prog with Buckx_VOUT[7]
         *      D1           D0
         * BUCK2_VOUT[7] BUCK1_VOUT[7]
         * */
        if (seq_index >= VOUT_BUCK_1) {
            i2c_func->i2c_write(i2c_client, BUCK_VSEL, buck12_prog);
            cam_info("%s buck_vsel 0x%x", __func__, buck12_prog);
        }
        mdelay(1);
        i2c_func->i2c_write(i2c_client, CHX_EN, chx_enable_tmp | chx_enable);
        cam_info("%s chx_enable 0x%x, voltage_reg 0x%x, voltage_val 0x%x", __func__, chx_enable, voltage_reg, voltage_val);
    } else {
        i2c_func->i2c_write(i2c_client, CHX_EN, chx_enable_tmp & (~chx_enable));
        //i2c_func->i2c_write(i2c_client, voltage_reg, state);
        if (seq_index >= VOUT_BUCK_1) {
            i2c_func->i2c_write(i2c_client, BUCK_VSEL, 0);
        }
    }

    i2c_func->i2c_read(i2c_client, CHX_ERR, &chx_enable_tmp);

    return ret;
}

static ssize_t ncp6925_show(struct device *dev,
        struct device_attribute *attr,char *buf)
{
    int rc=0;
    cam_info("enter %s", __func__);

    snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "mode=%d, data=%d.\n", cdata.mode, cdata.data);
    rc = strlen(buf)+1;
    return rc;
}


static int ncp6925_check(char *buf, unsigned long *param,
        int num_of_par)
{
    char *token;
    int base, cnt;

    token = strsep(&buf, " ");

    for (cnt = 0; cnt < num_of_par; cnt++)
    {
        if (token != NULL)
        {
            if ((token[1] == 'x') || (token[1] == 'X')) {
                base = 16;
            } else {
                base = 10;
            }

            if (strict_strtoul(token, base, &param[cnt]) != 0) {
                return -EINVAL;
            }

            token = strsep(&buf, " ");
        }
        else
        {
            return -EINVAL;
        }
    }
    return 0;
}


static ssize_t ncp6925_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t count)
{
    unsigned long param[2]={0};
    int rc=0;
    cam_info("enter %s", __func__);

    rc = ncp6925_check((char *)buf, param, 2);
    if (rc < 0) {
        cam_err("%s failed to check param.", __func__);
        return rc;
    }

    cdata.mode = (int)param[0];
    cdata.data = (int)param[1];

    cam_info("%s, mode %d data %d", __func__, cdata.mode, cdata.data);

    ncp6925_seq_config(&ncp6925_ctrl, cdata.mode, cdata.data, 1);

    return count;
}

static ssize_t ncp6925_reg_show(struct device *dev,
        struct device_attribute *attr,char *buf)
{
    int rc=0;
    cam_info("enter %s", __func__);

    snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "reg=%d, val=%d.\n", reg, val);
    rc = strlen(buf)+1;
    return rc;
}


static ssize_t ncp6925_reg_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t count)
{
    unsigned long param[2]={0};
    int rc=0;
    struct hisi_pmic_i2c_client *i2c_client;
    struct hisi_pmic_i2c_fn_t *i2c_func;
    cam_info("enter %s", __func__);

    rc = ncp6925_check((char *)buf, param, 2);
    if (rc < 0) {
        cam_err("%s failed to check param.", __func__);
        return rc;
    }

    i2c_client = ncp6925_ctrl.pmic_i2c_client;
    i2c_func = ncp6925_ctrl.pmic_i2c_client->i2c_func_tbl;

    reg = (u8)param[0];
    val = (u8)param[1];

    cam_info("%s, reg 0x%x val 0x%x", __func__, reg, val);

    i2c_func->i2c_write(i2c_client, reg, val);

    return count;
}


static struct device_attribute ncp6925_debug =
__ATTR(debug_ctrl, 0664, ncp6925_show, ncp6925_store);

static struct device_attribute ncp6925_reg =
__ATTR(reg_ctrl, 0664, ncp6925_reg_show, ncp6925_reg_store);

static int ncp6925_register_attribute(struct hisi_pmic_ctrl_t *pmic_ctrl, struct device *dev)
{
    int rc = 0;
    cam_info("%s enter.", __func__);
    if (dev == NULL) {
        cam_err("%s dev is null", __func__);
        return -1;
    }
    rc = device_create_file(dev, &ncp6925_debug);
    if (rc < 0) {
        cam_err("%s failed to creat ctrol attribute.", __func__);
        goto err_create_ncp6925_file;
    }

    rc = device_create_file(dev, &ncp6925_reg);
    if (rc < 0) {
        cam_err("%s failed to creat reg attribute.", __func__);
        goto err_create_ncp6925_file;
    }

    return 0;
err_create_ncp6925_file:
    device_remove_file(dev, &ncp6925_debug);
    return rc;
}

static const struct i2c_device_id ncp6925_id[] = {
    {"ncp6925", (unsigned long)&ncp6925_ctrl},
    {}
};

static const struct of_device_id ncp6925_dt_match[] = {
    {.compatible = "hisi,ncp6925"},
    {}
};

MODULE_DEVICE_TABLE(of, ncp6925_dt_match);

static struct i2c_driver ncp6925_i2c_driver = {
    .probe    = hisi_pmic_i2c_probe,
    .remove = ncp6925_remove,
    .id_table    = ncp6925_id,
    .driver = {
        .name = "ncp6925",
        .of_match_table = ncp6925_dt_match,
    },
};

static int __init ncp6925_module_init(void)
{
    cam_info("%s enter.\n", __func__);
    return i2c_add_driver(&ncp6925_i2c_driver);
}

static void __exit ncp6925_module_exit(void)
{
    cam_info("%s enter.", __func__);
    i2c_del_driver(&ncp6925_i2c_driver);
    return;
}

static struct hisi_pmic_i2c_client ncp6925_i2c_client;

static struct hisi_pmic_fn_t ncp6925_func_tbl = {
    .pmic_config = hisi_pmic_config,
    .pmic_init = ncp6925_init,
    .pmic_exit = ncp6925_exit,
    .pmic_on = ncp6925_on,
    .pmic_off = ncp6925_off,
    .pmic_match = ncp6925_match,
    .pmic_get_dt_data = ncp6925_get_dt_data,
    .pmic_seq_config = ncp6925_seq_config,
    .pmic_register_attribute = ncp6925_register_attribute,
};

struct hisi_pmic_ctrl_t ncp6925_ctrl = {
    .pmic_i2c_client = &ncp6925_i2c_client,
    .func_tbl = &ncp6925_func_tbl,
    .hisi_pmic_mutex = &pmic_mut_ncp6925,
    .pdata = (void*)&ncp6925_pdata,
};

module_init(ncp6925_module_init);
module_exit(ncp6925_module_exit);
MODULE_DESCRIPTION("NCP6925 PMIC");
MODULE_LICENSE("GPL v2");

