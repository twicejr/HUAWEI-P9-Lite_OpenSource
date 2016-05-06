

#include "hw_flash.h"
#include <linux/wakelock.h>

/* LM3646 Registers define */
#define REG_CHIPID                 0x00
#define REG_ENABLE			0x01
#define REG_FLAGS1			0x08
#define REG_FLAGS2			0x09
#define REG_LED1_FLASH_CURRENT_CONTROL		0x06
#define REG_LED1_TORCH_CURRENT_CONTROL		0x07
#define REG_FLASH_TIMEOUT		0x04
#define REG_MAX_CURRENT         0x05

#define CHIP_ID                              0x10
#define MODE_STANDBY			0x00
//#define MODE_INDICATOR			0x01
#define MODE_TORCH			0x02
#define MODE_FLASH			0x03
#define STROBE_ENABLE			0x80
#define TORCH_ENABLE			0x80
#define STROBE_DISABLE			0x00
#define TORCH_DISABLE			0x00
#define TX_ENABLE				0x08
#define INDUCTOR_CURRENT_LIMMIT 0xe0
#define FLASH_TIMEOUT_TIME        0x47    //400ms

#define FLASH_LED_MAX			0x7f
#define TORCH_LED_MAX			0x7f
#define MAX_BRIGHTNESS_FORMMI   0x09
#define ENABLE_SHORT_PROTECT       0x80
#define LM3646_RESET_HOLD_TIME      2

#define INVALID_GPIO            999
/* Internal data struct define */
typedef enum {
    RESET=0,
    STROBE,
    TORCH,
    MAX_PIN,
}lm3646_pin_type;

/* Internal data struct define */
struct hw_lm3646_private_data_t {
    unsigned char flash_led[FLASH_LED_MAX];
    unsigned char torch_led[TORCH_LED_MAX];
    unsigned int flash_led_num;
    unsigned int torch_led_num;
    struct wake_lock  lm3646_wakelock;
    int	need_wakelock;
    /* flash control pin */
    unsigned int pin[MAX_PIN];

    unsigned int chipid;
    unsigned int ctrltype;
};

/* Internal varible define */
static struct hw_lm3646_private_data_t hw_lm3646_pdata;
static struct hw_flash_ctrl_t hw_lm3646_ctrl;
static struct i2c_driver hw_lm3646_i2c_driver;

struct hw_lm3646_flash_level_matrix{
    unsigned int flash_level_min;
    unsigned int flash_level_max;

    unsigned char max_current_flash;
    unsigned char max_current_torch;
};

/*
    预闪总电流(mA)	强闪总电流(mA)	电流组合数
    187.2	                    1500	                            128
    140.2	                    1124.9	                      96
    93.4	                           749.8	                      64
    46.5	                           374.7	                      32
    23.1	                           187.2	                      16
*/

static struct hw_lm3646_flash_level_matrix hw_lm3646_flash_level[5] = {
    {0,       15,       1,        0},
    {16,     47,       3,         1},
    {48,    111,       7,        3},
    {112,  207,       11,       5},
    {208,  335,       15,       7},
};

static int support_dual_tempeture = 1;

DEFINE_HISI_FLASH_MUTEX(lm3646);

#ifdef CONFIG_LLT_TEST

struct UT_TEST_LM3646
{
    int (*hw_lm3646_set_pin_strobe)(struct hw_flash_ctrl_t *flash_ctrl,unsigned int state);
    int (*hw_lm3646_set_pin_torch)(struct hw_flash_ctrl_t *flash_ctrl,unsigned int state);
    int (*hw_lm3646_set_pin_reset)(struct hw_flash_ctrl_t *flash_ctrl,unsigned int state);
    int (*hw_lm3646_init)(struct hw_flash_ctrl_t *flash_ctrl);
    int (*hw_lm3646_exit)(struct hw_flash_ctrl_t *flash_ctrl);
    int (*hw_lm3646_flash_mode)(struct hw_flash_ctrl_t *flash_ctrl,int data);
    int (*hw_lm3646_torch_mode_mmi)(struct hw_flash_ctrl_t *flash_ctrl,int data);
    int (*hw_lm3646_set_mode)(struct hw_flash_ctrl_t *flash_ctrl, void *data);
    int (*hw_lm3646_on)(struct hw_flash_ctrl_t *flash_ctrl, void *data);
    int (*hw_lm3646_brightness)(struct hw_flash_ctrl_t *flash_ctrl, void *data);
    int (*hw_lm3646_off)(struct hw_flash_ctrl_t *flash_ctrl);
    int (*hw_lm3646_get_dt_data)(struct hw_flash_ctrl_t *flash_ctrl);
    ssize_t (*hw_lm3646_dual_leds_show)(struct device *dev,struct device_attribute *attr,char *buf);
    ssize_t (*hw_lm3646_dual_leds_store)(struct device *dev,struct device_attribute *attr, const char *buf, size_t count);
    ssize_t (*hw_lm3646_lightness_store)(struct device *dev,struct device_attribute *attr, const char *buf, size_t count);
    ssize_t (*hw_lm3646_lightness_show)(struct device *dev,struct device_attribute *attr,char *buf);
    ssize_t (*hw_lm3646_flash_mask_show)(struct device *dev,struct device_attribute *attr,char *buf);
    int (*hw_lm3646_register_attribute)(struct hw_flash_ctrl_t *flash_ctrl, struct device *dev);
    ssize_t (*hw_lm3646_flash_mask_store)(struct device *dev,struct device_attribute *attr, const char *buf, size_t count);
    int (*hw_lm3646_match)(struct hw_flash_ctrl_t *flash_ctrl);
    void (*hw_lm3646_torch_brightness_set)(struct led_classdev *cdev,enum led_brightness brightness);
    int (*hw_lm3646_param_check)(char *buf, unsigned long *param,int num_of_par);
};

#endif /* CONFIG_LLT_TEST */


/* Function define */
static int hw_lm3646_param_check(char *buf, unsigned long *param,
    int num_of_par);
static int hw_lm3646_set_pin_strobe(struct hw_flash_ctrl_t *flash_ctrl,
    unsigned int state)
{
    struct hw_lm3646_private_data_t *pdata;

    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }

    pdata = (struct hw_lm3646_private_data_t *)flash_ctrl->pdata;

    cam_debug("%s strobe0=%d, state=%d.", __func__,
        pdata->pin[STROBE], state);
    if(pdata->pin[STROBE] != INVALID_GPIO) {
        gpio_direction_output(pdata->pin[STROBE], state);
    }
    return 0;
}

static int hw_lm3646_set_pin_torch(struct hw_flash_ctrl_t *flash_ctrl,
unsigned int state)
{
    struct hw_lm3646_private_data_t *pdata;

    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }

    pdata = (struct hw_lm3646_private_data_t *)flash_ctrl->pdata;

    cam_debug("%s strobe1=%d, state=%d.", __func__,
    pdata->pin[TORCH], state);
    if(pdata->pin[TORCH] != INVALID_GPIO) {
        gpio_direction_output(pdata->pin[TORCH], state);
    }
    return 0;
}

static int hw_lm3646_set_pin_reset(struct hw_flash_ctrl_t *flash_ctrl,
unsigned int state)
{
    struct hw_lm3646_private_data_t *pdata;

    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }

    pdata = (struct hw_lm3646_private_data_t *)flash_ctrl->pdata;

    cam_debug("%s reset=%d, state=%d.", __func__,
        pdata->pin[RESET], state);
    gpio_direction_output(pdata->pin[RESET], state);
    return 0;
}

static int hw_lm3646_init(struct hw_flash_ctrl_t *flash_ctrl)
{
    struct hw_lm3646_private_data_t *pdata;
    int rc = 0;

    cam_debug("%s enter.\n", __func__);

    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }

    pdata = (struct hw_lm3646_private_data_t *)flash_ctrl->pdata;
    flash_ctrl->pctrl = devm_pinctrl_get_select(flash_ctrl->dev,
        PINCTRL_STATE_DEFAULT);
    if (NULL == flash_ctrl->pctrl) {
        cam_err("%s failed to set pin.", __func__);
        return -EIO;
    }

    rc = gpio_request(pdata->pin[RESET], "flash-reset");
    if (rc < 0) {
        cam_err("%s failed to request reset pin.", __func__);
        return -EIO;
    }

    if(pdata->pin[STROBE] != INVALID_GPIO) {
        rc = gpio_request(pdata->pin[STROBE], "flash-strobe");
        if (rc < 0) {
            cam_err("%s failed to request strobe pin.", __func__);
            goto err1;
        }
    }
    if(pdata->pin[TORCH] != INVALID_GPIO) {
        rc = gpio_request(pdata->pin[TORCH], "flash-torch");
        if (rc < 0) {
            cam_err("%s failed to request torch pin.", __func__);
            goto err2;
        }
    }
    rc = of_property_read_u32(flash_ctrl->dev->of_node, "huawei,need-wakelock", &pdata->need_wakelock);
    cam_info("%s huawei,need-wakelock %d, rc %d\n", __func__, pdata->need_wakelock, rc);
    if (rc < 0) {
        pdata->need_wakelock = 0;
        cam_err("%s failed %d\n", __func__, __LINE__);
        goto err3;
    }
    hw_lm3646_set_pin_reset(flash_ctrl,LOW);
    msleep(LM3646_RESET_HOLD_TIME);
    if(pdata->need_wakelock == 1)
        wake_lock_init(&pdata->lm3646_wakelock,WAKE_LOCK_SUSPEND,"lm3646");
    return rc;
err3:
    if(pdata->pin[TORCH] != INVALID_GPIO) {
        gpio_free(pdata->pin[TORCH]);
    }
err2:
    if(pdata->pin[STROBE] != INVALID_GPIO) {
        gpio_free(pdata->pin[STROBE]);
    }
err1:
    gpio_free(pdata->pin[RESET]);
    return rc;
}

static int hw_lm3646_exit(struct hw_flash_ctrl_t *flash_ctrl)
{
    struct hw_lm3646_private_data_t *pdata;

    cam_debug("%s enter.\n", __func__);

    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }

    flash_ctrl->func_tbl->flash_off(flash_ctrl);

    pdata = (struct hw_lm3646_private_data_t *)flash_ctrl->pdata;
    if(pdata->pin[TORCH] != INVALID_GPIO) {
        gpio_free(pdata->pin[TORCH]);
    }
    if(pdata->pin[STROBE] != INVALID_GPIO) {
        gpio_free(pdata->pin[STROBE]);
    }
    gpio_free(pdata->pin[RESET]);
    flash_ctrl->pctrl = devm_pinctrl_get_select(flash_ctrl->dev,
        PINCTRL_STATE_IDLE);

    return 0;
}

static int hw_lm3646_flash_mode(struct hw_flash_ctrl_t *flash_ctrl,
int data)
{
    struct hw_flash_i2c_client *i2c_client;
    struct hw_flash_i2c_fn_t *i2c_func;
    struct hw_lm3646_private_data_t *pdata;
    unsigned char val;

    cam_info("%s data=%d.\n", __func__, data);
    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }

    i2c_client = flash_ctrl->flash_i2c_client;
    i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
    pdata = flash_ctrl->pdata;

    /* clear error flag,resume chip */
    i2c_func->i2c_read(i2c_client, REG_FLAGS1, &val);
    i2c_func->i2c_read(i2c_client, REG_FLAGS2, &val);
    i2c_func->i2c_read(i2c_client, REG_LED1_FLASH_CURRENT_CONTROL, &val);

    /* set LED Flash current value */
    if (data < FLASH_LED_MAX) {
        cam_info("%s flash_led=0x%x.", __func__,
        pdata->flash_led[data]);
        /* REG_CURRENT_CONTROL[3:0] control flash current */
        val = ((val & 0x80) | (data & 0x7f));
    } else {
        cam_warn("%s data(%d) > flash_led_num(%d).", __func__,
        data, pdata->flash_led_num);
        /* REG_CURRENT_CONTROL[3:0] control flash current */
        val = ((val & 0x80) | (0x7f));
    }
    i2c_func->i2c_write(i2c_client, REG_MAX_CURRENT, 0x7c);
    i2c_func->i2c_write(i2c_client, REG_LED1_FLASH_CURRENT_CONTROL, 0x22);
    if (flash_ctrl->flash_mask_enable) {
        i2c_func->i2c_write(i2c_client, REG_ENABLE, 0xdb);
    } else {
        i2c_func->i2c_write(i2c_client, REG_ENABLE, 0xd3);
    }

    return 0;
}

static int hw_lm3646_torch_mode_mmi(struct hw_flash_ctrl_t *flash_ctrl,
int data)
{
    struct hw_flash_i2c_client *i2c_client;
    struct hw_flash_i2c_fn_t *i2c_func;
    struct hw_lm3646_private_data_t *pdata;
    unsigned char val;

    cam_info("%s data=%d.\n", __func__, data);
    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }

    i2c_client = flash_ctrl->flash_i2c_client;
    i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
    pdata = (struct hw_lm3646_private_data_t *)flash_ctrl->pdata;

    /* clear error flag,resume chip */
    i2c_func->i2c_read(i2c_client, REG_FLAGS1, &val);
    i2c_func->i2c_read(i2c_client, REG_FLAGS2, &val);
    i2c_func->i2c_read(i2c_client, REG_LED1_TORCH_CURRENT_CONTROL, &val);
    i2c_func->i2c_write(i2c_client, REG_MAX_CURRENT, 0x7c);
    /* set LED Flash current value */
    if (data == TORCH_LEFT_MODE) {
        cam_info("%s flash_led=TORCH_LEFT_MODE", __func__);
        /* REG_CURRENT_CONTROL[3:0] control flash current */
        val = ((val & 0x80) | (0x7f));

    } else if (data == TORCH_RIGHT_MODE){
        cam_info("%s flash_led=TORCH_RIGHT_MODE", __func__);
        /* REG_CURRENT_CONTROL[3:0] control flash current */
        val = ((val & 0x80) | (0x0));
    }else {
        cam_info("%s default flash_led=TORCH_LEFT_MODE  mode = %d", __func__,data);
        /* REG_CURRENT_CONTROL[3:0] control flash current */
        val = ((val & 0x80) | (0x7f));
    }

    i2c_func->i2c_write(i2c_client, REG_LED1_TORCH_CURRENT_CONTROL, val);
    if (flash_ctrl->flash_mask_enable) {
        i2c_func->i2c_write(i2c_client, REG_ENABLE, 0xda);
    } else {
        i2c_func->i2c_write(i2c_client, REG_ENABLE, 0xd2);
    };

    return 0;
}

static int hw_lm3646_set_mode(struct hw_flash_ctrl_t *flash_ctrl, void *data)
{
    struct hw_flash_cfg_data *cdata = (struct hw_flash_cfg_data *)data;

    struct hw_flash_i2c_client *i2c_client;
    struct hw_flash_i2c_fn_t *i2c_func;
    struct hw_lm3646_private_data_t *pdata;
    struct hw_lm3646_flash_level_matrix* matrix = NULL;
    unsigned char val = 0;
    unsigned char mode = 0;
    unsigned char regmaxcurrent = 0;
    unsigned char regcurrentflash = 0;
    unsigned char regcurrenttorch = 0;
    int current_index = 0;
    int i = 0;

    if ((NULL == flash_ctrl) || (NULL == cdata)) {
    cam_err("%s flash_ctrl or cdata is NULL.", __func__);
    return -1;
    }

    i2c_client = flash_ctrl->flash_i2c_client;
    i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
    pdata = flash_ctrl->pdata;

    current_index = cdata->data;
    if(current_index >= pdata->flash_led_num){
        current_index = pdata->flash_led_num -1;
        cam_err("%s user set flash curret[%d] index is out of range %d,set to maxval",__func__,cdata->data,pdata->flash_led_num);
    }

    for(i = 0;i<5;i++){
        if(hw_lm3646_flash_level[i].flash_level_min<= current_index
        && hw_lm3646_flash_level[i].flash_level_max >= current_index){
            matrix = &hw_lm3646_flash_level[i];
            break;
        }
    }

    /* clear error flag,resume chip */
    i2c_func->i2c_read(i2c_client, REG_FLAGS1, &val);
    i2c_func->i2c_read(i2c_client, REG_FLAGS2, &val);
    if(matrix != NULL)
    {
        if(FLASH_MODE == cdata->mode){
        /* 1 means I2C control, 0 means GPIO control. */
        if(pdata->ctrltype == 1) {
        mode = INDUCTOR_CURRENT_LIMMIT|TX_ENABLE|MODE_FLASH;
        regcurrentflash = STROBE_DISABLE|(current_index - matrix->flash_level_min);
        } else {
        mode = INDUCTOR_CURRENT_LIMMIT|TX_ENABLE|MODE_FLASH;
        regcurrentflash = STROBE_ENABLE|(current_index - matrix->flash_level_min);
        }
        regmaxcurrent = matrix->max_current_flash;
        }else{
            /* 1 means I2C control, 0 means GPIO control. */
            if(pdata->ctrltype == 1) {
                mode = INDUCTOR_CURRENT_LIMMIT|TX_ENABLE|MODE_TORCH;
                regcurrenttorch = TORCH_DISABLE|(current_index - matrix->flash_level_min);
            } else {
                mode = INDUCTOR_CURRENT_LIMMIT|TX_ENABLE|MODE_TORCH;
                regcurrenttorch = TORCH_ENABLE|(current_index - matrix->flash_level_min);
            }
                regmaxcurrent = matrix->max_current_torch<<4;
        }
    }

    i2c_func->i2c_write(i2c_client, REG_FLASH_TIMEOUT, FLASH_TIMEOUT_TIME);
    i2c_func->i2c_write(i2c_client, REG_MAX_CURRENT, regmaxcurrent | ENABLE_SHORT_PROTECT);
    i2c_func->i2c_write(i2c_client, REG_LED1_FLASH_CURRENT_CONTROL, regcurrentflash);
    i2c_func->i2c_write(i2c_client, REG_LED1_TORCH_CURRENT_CONTROL, regcurrenttorch);
    i2c_func->i2c_write(i2c_client, REG_ENABLE, mode);

    cam_debug("%s mode=%d, level=%d.\n", __func__, cdata->mode, cdata->data);
    cam_info("%s regmaxcurrent = %x regcurrentflash =%x regcurrenttorch = %x",__func__,regmaxcurrent,regcurrentflash&0x7f,regcurrenttorch&0x7f);
    return 0;
}


static int hw_lm3646_on(struct hw_flash_ctrl_t *flash_ctrl, void *data)
{
    struct hw_lm3646_private_data_t *pdata;
    struct hw_flash_cfg_data *cdata = (struct hw_flash_cfg_data *)data;
    int rc= 0;
    if ((NULL == flash_ctrl) || (NULL == cdata)) {
        cam_err("%s flash_ctrl or cdata is NULL.", __func__);
        return -1;
    }
    pdata = (struct hw_lm3646_private_data_t *)flash_ctrl->pdata;

    cam_info("%s mode=%d, level=%d.\n", __func__, cdata->mode, cdata->data);

    mutex_lock(flash_ctrl->hw_flash_mutex);
    if(pdata->need_wakelock ==1)
        wake_lock(&pdata->lm3646_wakelock);
    //Enable lm3646 switch to standby current is 10ua
    hw_lm3646_set_pin_reset(flash_ctrl,HIGH);
    hw_lm3646_set_pin_strobe(flash_ctrl,LOW);
    hw_lm3646_set_pin_torch(flash_ctrl,LOW);


    hw_lm3646_set_mode(flash_ctrl,data);
    flash_ctrl->state.mode = cdata->mode;
    flash_ctrl->state.data = cdata->data;
    hw_lm3646_set_pin_strobe(flash_ctrl,HIGH);
    hw_lm3646_set_pin_torch(flash_ctrl,HIGH);

    mutex_unlock(flash_ctrl->hw_flash_mutex);

    return rc;
}

static int hw_lm3646_brightness(struct hw_flash_ctrl_t *flash_ctrl, void *data)
{
    struct hw_flash_cfg_data *cdata = (struct hw_flash_cfg_data *)data;
    int rc=-1;

    if ((NULL == flash_ctrl) || (NULL == cdata)) {
        cam_err("%s flash_ctrl or cdata is NULL.", __func__);
        return -1;
    }

    cam_debug("%s mode=%d, level=%d.\n", __func__, cdata->mode, cdata->data);
    cam_info("%s enter.\n", __func__);
    mutex_lock(flash_ctrl->hw_flash_mutex);
    //Enable lm3646 switch to standby current is 10ua
    hw_lm3646_set_pin_reset(flash_ctrl,HIGH);
    if (FLASH_MODE == cdata->mode) {
        rc = hw_lm3646_flash_mode(flash_ctrl, cdata->data);
    } else {
        rc = hw_lm3646_torch_mode_mmi(flash_ctrl, cdata->mode);
    }
    flash_ctrl->state.mode = cdata->mode;
    flash_ctrl->state.data = cdata->data;
    mutex_unlock(flash_ctrl->hw_flash_mutex);

return rc;
}


static int hw_lm3646_off(struct hw_flash_ctrl_t *flash_ctrl)
{
    struct hw_flash_i2c_client *i2c_client;
    struct hw_flash_i2c_fn_t *i2c_func;
    unsigned char val;
    struct hw_lm3646_private_data_t *pdata;
    cam_debug("%s enter.\n", __func__);
    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }
    pdata = (struct hw_lm3646_private_data_t *)flash_ctrl->pdata;

    mutex_lock(flash_ctrl->hw_flash_mutex);
    if(flash_ctrl->state.mode == STANDBY_MODE){
        mutex_unlock(flash_ctrl->hw_flash_mutex);
        return 0;
    }
    flash_ctrl->state.mode = STANDBY_MODE;
    flash_ctrl->state.data = 0;
    i2c_client = flash_ctrl->flash_i2c_client;
    i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;

    i2c_func->i2c_read(i2c_client, REG_FLAGS1, &val);
    i2c_func->i2c_read(i2c_client, REG_FLAGS2, &val);
    i2c_func->i2c_write(i2c_client, REG_ENABLE, MODE_STANDBY);

    hw_lm3646_set_pin_strobe(flash_ctrl,LOW);
    hw_lm3646_set_pin_torch(flash_ctrl,LOW);
    //Enable lm3646 switch to shutdown current is 1.3ua
    hw_lm3646_set_pin_reset(flash_ctrl,LOW);
    if(pdata->need_wakelock == 1)
        wake_unlock(&pdata->lm3646_wakelock);
    cam_info("%s end", __func__);
    mutex_unlock(flash_ctrl->hw_flash_mutex);

return 0;
}

static int hw_lm3646_get_dt_data(struct hw_flash_ctrl_t *flash_ctrl)
{
    struct hw_lm3646_private_data_t *pdata;
    struct device_node *of_node;
    int i;
    int rc = -1;

    cam_debug("%s enter.\n", __func__);

    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return rc;
    }

    pdata = (struct hw_lm3646_private_data_t *)flash_ctrl->pdata;
    of_node = flash_ctrl->dev->of_node;


    rc = of_property_read_u32_array(of_node, "huawei,flash-pin",
    pdata->pin, MAX_PIN);
    if (rc < 0) {
        cam_err("%s bbbb failed line %d\n", __func__, __LINE__);
        return rc;
    } else {
        for (i=0; i<MAX_PIN; i++) {
            cam_info("%s pin[%d]=%d.\n", __func__, i,
            pdata->pin[i]);
        }
    }

    rc = of_property_read_u32(of_node, "huawei,flash-chipid",
    &pdata->chipid);
    cam_info("%s hisi,chipid 0x%x, rc %d\n", __func__,
    pdata->chipid, rc);
    if (rc < 0) {
        cam_err("%s failed %d\n", __func__, __LINE__);
        return rc;
    }

    rc = of_property_read_u32(of_node, "huawei,flash-ctrltype",
    &pdata->ctrltype);
    cam_info("%s hisi,ctrltype 0x%x, rc %d\n", __func__,
    pdata->ctrltype, rc);
    if (rc < 0) {
        cam_err("%s failed %d\n", __func__, __LINE__);
        return rc;
    }

    rc = of_property_read_u32(of_node, "huawei,flash_led_num",
    &pdata->flash_led_num);
    cam_info("%s hisi,flash_led_num %d, rc %d\n", __func__,
    pdata->flash_led_num, rc);
    if (rc < 0) {
        cam_err("%s failed %d\n", __func__, __LINE__);
        return rc;
    }

    rc = of_property_read_u32(of_node, "huawei,torch_led_num",
    &pdata->torch_led_num);
    cam_info("%s hisi,torch_led_num %d, rc %d\n", __func__,
    pdata->torch_led_num, rc);
    if (rc < 0) {
        cam_err("%s aaa failed %d\n", __func__, __LINE__);
        return rc;
    }
    return rc;
}

static ssize_t hw_lm3646_dual_leds_show(struct device *dev,
struct device_attribute *attr,char *buf)
{
    int rc=0;

    rc = scnprintf(buf, PAGE_SIZE, "%d\n",
        support_dual_tempeture);

    return rc;
}

static ssize_t hw_lm3646_dual_leds_store(struct device *dev,
struct device_attribute *attr, const char *buf, size_t count)
{
    unsigned long param[2]={0};
    int rc=0;

    rc = hw_lm3646_param_check((char *)buf, param, 1);
    if (rc < 0) {
        cam_err("%s failed to check param.", __func__);
        return rc;
    }
    support_dual_tempeture = (int)param[0];
    return count;
}


static ssize_t hw_lm3646_lightness_show(struct device *dev,
struct device_attribute *attr,char *buf)
{
    int rc=0;

    rc = scnprintf(buf, PAGE_SIZE, "mode=%d, data=%d.\n",
        hw_lm3646_ctrl.state.mode, hw_lm3646_ctrl.state.data);

    return rc;
}

static int hw_lm3646_param_check(char *buf, unsigned long *param,
int num_of_par)
{
    char *token;
    int base, cnt;

    token = strsep(&buf, " ");

    for (cnt = 0; cnt < num_of_par; cnt++) {
        if (token != NULL) {
            if ((token[1] == 'x') || (token[1] == 'X')) {
                base = 16;
            } else {
                base = 10;
            }
            if (strict_strtoul(token, base, &param[cnt]) != 0) {
                return -EINVAL;
            }
            token = strsep(&buf, " ");
        } else{
            return -EINVAL;
        }
    }
    return 0;
}

static ssize_t hw_lm3646_lightness_store(struct device *dev,
    struct device_attribute *attr, const char *buf, size_t count)
{
    struct hw_flash_cfg_data cdata = {0};
    unsigned long param[2]={0};
    int rc=0;

    rc = hw_lm3646_param_check((char *)buf, param, 2);
    if (rc < 0) {
        cam_err("%s failed to check param.", __func__);
        return rc;
    }

    cdata.mode = (int)param[0];
    cdata.data = (int)param[1];

    if (cdata.mode == STANDBY_MODE) {
        rc = hw_lm3646_off(&hw_lm3646_ctrl);
        if (rc < 0) {
            cam_err("%s lm3646 flash off error.", __func__);
            return rc;
        }
    } else {
        rc = hw_lm3646_on(&hw_lm3646_ctrl, &cdata);
        if (rc < 0) {
            cam_err("%s lm3646 flash on error.", __func__);
            return rc;
        }
    }

    return count;
}

static ssize_t hw_lm3646_flash_mask_show(struct device *dev,
    struct device_attribute *attr,char *buf)
{
    int rc=0;

    rc = scnprintf(buf, PAGE_SIZE, "flash_mask_disabled=%d.\n",
        hw_lm3646_ctrl.flash_mask_enable);

    return rc;
}

static ssize_t hw_lm3646_flash_mask_store(struct device *dev,
    struct device_attribute *attr, const char *buf, size_t count)
{
    if ('0' == buf[0]) {
        hw_lm3646_ctrl.flash_mask_enable = false;
    } else {
        hw_lm3646_ctrl.flash_mask_enable = true;
    }
    cam_debug("%s flash_mask_enable=%d.", __func__,
    hw_lm3646_ctrl.flash_mask_enable);
    return count;
}

static void hw_lm3646_torch_brightness_set(struct led_classdev *cdev,
    enum led_brightness brightness)
{
    struct hw_flash_cfg_data cdata;
    int rc;
    unsigned int led_bright = brightness;
    cam_info("%s brightness= %d",__func__,brightness);
    if (STANDBY_MODE == led_bright) {
        rc = hw_lm3646_off(&hw_lm3646_ctrl);
        if (rc < 0) {
            cam_err("%s pmu_led off error.", __func__);
            return;
        }
    } else {
        int max_level;
        max_level = 3;
        cdata.mode = ((brightness-1) / max_level) + TORCH_MODE;
        cdata.data =((brightness-1) % max_level);

        cam_info("%s brightness=0x%x, mode=%d, data=%d.", __func__, brightness, cdata.mode, cdata.data);

        rc = hw_lm3646_brightness(&hw_lm3646_ctrl, &cdata);
        if (rc < 0) {
            cam_err("%s pmu_led on error.",__func__);
            return;
        }
    }
}

static struct device_attribute hw_lm3646_lightness =
__ATTR(lightness, 0664, hw_lm3646_lightness_show, hw_lm3646_lightness_store);

static struct device_attribute hw_lm3646_dual_leds =
__ATTR(dual_leds, 0664, hw_lm3646_dual_leds_show, hw_lm3646_dual_leds_store);

static struct device_attribute hw_lm3646_flash_mask =
__ATTR(flash_mask, 0664, hw_lm3646_flash_mask_show, hw_lm3646_flash_mask_store);

static int hw_lm3646_register_attribute(struct hw_flash_ctrl_t *flash_ctrl, struct device *dev)
{
    int rc = 0;

    if ((NULL == flash_ctrl) || (NULL == dev)) {
        cam_err("%s flash_ctrl or dev is NULL.", __func__);
        return -1;
    }

    flash_ctrl->cdev_torch.name = "torch";
    flash_ctrl->cdev_torch.max_brightness
        = MAX_BRIGHTNESS_FORMMI;
    flash_ctrl->cdev_torch.brightness_set = hw_lm3646_torch_brightness_set;
    rc = led_classdev_register((struct device *)dev, &flash_ctrl->cdev_torch);
    if (rc < 0) {
        cam_err("%s failed to register torch classdev.", __func__);
        goto err_out;
    }

    rc = device_create_file(dev, &hw_lm3646_lightness);
    if (rc < 0) {
        cam_err("%s failed to creat lightness attribute.", __func__);
        goto err_create_lightness_file;
    }

    rc = device_create_file(dev, &hw_lm3646_flash_mask);
    if (rc < 0) {
        cam_err("%s failed to creat flash_mask attribute.", __func__);
        goto err_create_flash_mask_file;
    }
    return 0;
err_create_flash_mask_file:
    device_remove_file(dev, &hw_lm3646_lightness);
err_create_lightness_file:
    led_classdev_unregister(&flash_ctrl->cdev_torch);
err_out:
    return rc;
}

extern int register_camerafs_attr(struct device_attribute *attr);
static int hw_lm3646_match(struct hw_flash_ctrl_t *flash_ctrl)
{
    struct hw_flash_i2c_client *i2c_client;
    struct hw_flash_i2c_fn_t *i2c_func;
    struct hw_lm3646_private_data_t *pdata;
    unsigned char id;

    cam_debug("%s enter.\n", __func__);

    if (NULL == flash_ctrl) {
        cam_err("%s flash_ctrl is NULL.", __func__);
        return -1;
    }

    i2c_client = flash_ctrl->flash_i2c_client;
    i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
    pdata = (struct hw_lm3646_private_data_t *)flash_ctrl->pdata;

    //Enable lm3646 switch to standby current is 10ua
    hw_lm3646_set_pin_reset(flash_ctrl,HIGH);
    i2c_func->i2c_read(i2c_client, REG_CHIPID, &id);
    cam_info("%s id=0x%x.\n", __func__, id);
    id = id & CHIP_ID;
    if (id != CHIP_ID) {
        cam_err("%s match error, id(0x%x) != 0x%x.",
        __func__, id, CHIP_ID);
        return -1;
    }
    //Enable lm3646 switch to shutdown current is 1.3ua
    hw_lm3646_set_pin_reset(flash_ctrl,LOW);

    register_camerafs_attr(&hw_lm3646_dual_leds);
    //add for debug only
    register_camerafs_attr(&hw_lm3646_lightness);
    return 0;
}

static int hw_lm3646_remove(struct i2c_client *client)
{
    cam_debug("%s enter.", __func__);

    hw_lm3646_ctrl.func_tbl->flash_exit(&hw_lm3646_ctrl);

    client->adapter = NULL;
    return 0;
}

static const struct i2c_device_id hw_lm3646_id[] = {
    {"lm3646", (unsigned long)&hw_lm3646_ctrl},
    {}
};

static const struct of_device_id hw_lm3646_dt_match[] = {
    {.compatible = "huawei,lm3646"},
    {}
};
MODULE_DEVICE_TABLE(of, lm3646_dt_match);

static struct i2c_driver hw_lm3646_i2c_driver = {
    .probe	= hw_flash_i2c_probe,
    .remove = hw_lm3646_remove,
    .id_table	= hw_lm3646_id,
    .driver = {
    .name = "hw_lm3646",
    .of_match_table = hw_lm3646_dt_match,
    },
};

static int __init hw_lm3646_module_init(void)
{
    cam_info("%s erter.\n", __func__);
    return i2c_add_driver(&hw_lm3646_i2c_driver);
}

static void __exit hw_lm3646_module_exit(void)
{
    cam_info("%s enter.", __func__);
    i2c_del_driver(&hw_lm3646_i2c_driver);
    return;
}

static struct hw_flash_i2c_client hw_lm3646_i2c_client;

static struct hw_flash_fn_t hw_lm3646_func_tbl = {
    .flash_config = hw_flash_config,
    .flash_init = hw_lm3646_init,
    .flash_exit = hw_lm3646_exit,
    .flash_on = hw_lm3646_on,
    .flash_off = hw_lm3646_off,
    .flash_match = hw_lm3646_match,
    .flash_get_dt_data = hw_lm3646_get_dt_data,
    .flash_register_attribute = hw_lm3646_register_attribute,
};

static struct hw_flash_ctrl_t hw_lm3646_ctrl = {
    .flash_i2c_client = &hw_lm3646_i2c_client,
    .func_tbl = &hw_lm3646_func_tbl,
    .hw_flash_mutex = &flash_mut_lm3646,
    .pdata = (void*)&hw_lm3646_pdata,
    .flash_mask_enable = true,
    .state = {
        .mode = STANDBY_MODE,
    },
};

#ifdef CONFIG_LLT_TEST

struct UT_TEST_LM3646 UT_lm3646 =
{
    .hw_lm3646_set_pin_strobe   = hw_lm3646_set_pin_strobe,
    .hw_lm3646_set_pin_torch   = hw_lm3646_set_pin_torch,
    .hw_lm3646_set_pin_reset   = hw_lm3646_set_pin_reset,
    .hw_lm3646_init = hw_lm3646_init,
    .hw_lm3646_exit = hw_lm3646_exit,
    .hw_lm3646_flash_mode = hw_lm3646_flash_mode,
    .hw_lm3646_torch_mode_mmi   = hw_lm3646_torch_mode_mmi,
    .hw_lm3646_set_mode =hw_lm3646_set_mode,
    .hw_lm3646_on =hw_lm3646_on,
    .hw_lm3646_brightness = hw_lm3646_brightness,
    .hw_lm3646_off = hw_lm3646_off,
    .hw_lm3646_get_dt_data = hw_lm3646_get_dt_data,
    .hw_lm3646_dual_leds_show =hw_lm3646_dual_leds_show,
    .hw_lm3646_dual_leds_store =hw_lm3646_dual_leds_store,
    .hw_lm3646_lightness_store = hw_lm3646_lightness_store,
    .hw_lm3646_lightness_show = hw_lm3646_lightness_show,
    .hw_lm3646_flash_mask_show = hw_lm3646_flash_mask_show,
    .hw_lm3646_register_attribute = hw_lm3646_register_attribute,
    .hw_lm3646_flash_mask_store = hw_lm3646_flash_mask_store,
    .hw_lm3646_match = hw_lm3646_match,
    .hw_lm3646_torch_brightness_set = hw_lm3646_torch_brightness_set,
    .hw_lm3646_param_check = hw_lm3646_param_check,
};

#endif /* CONFIG_LLT_TEST */

module_init(hw_lm3646_module_init);
module_exit(hw_lm3646_module_exit);
MODULE_DESCRIPTION("LM3646 FLASH");
MODULE_LICENSE("GPL v2");
