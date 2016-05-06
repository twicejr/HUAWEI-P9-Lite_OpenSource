

//#include <linux/mux.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/workqueue.h>
//#include <linux/moduleparam.h>
#include <linux/module.h>
//#include <mach/gpio.h>
#include <linux/pinctrl/consumer.h>
//#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <hsad/config_mgr.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif

#include "mini_cam_log.h"
#include "mini_sensor_common.h"
#include "../isp/sensor_common.h"


//#define DEBUG_DEBUG 1
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "K3_STROBE"
#define REG_ENABLE				 0x0a
#define REG_FLAGS			 0x0b
#define REG_FLASH_FEATURES	 0x08
#define REG_CURRENT_CONTROL	 0x09
#define REG_IVFM				 0x01
#define REG_TORCH_RAMP_TIME      0x06

/* reg_enable
     x x x x   x x x x
                   | |__mode bit 0
			       |__ _mode bit 1
*/
#define MODE_STANDBY			 0x00
#define MODE_INDICATOR			 0x01
#define MODE_TORCH				 0x02
#define MODE_FLASH				 0x03
#define STROBE_PIN				 0x20
#define TORCH_PIN				 0x10
#define TX_PIN					 0x40

#define TORCH_CURRENT_FOR_PREFLASH      3    //187.5ma
#define FLASH_CURRENT_FOR_FLASH         9    //937.5ma

#if 0
#define GPIO_FLASH_STRB         (GPIO_18_5)
#define GPIO_FLASH_MASK         (GPIO_9_0)
#endif
/* Flash Current
0000 = 93.75mA
0001 = 187.5mA
0010 = 281.25mA
0011 = 375mA
0100 = 468.75mA
0101 = 562.5mA
0110 = 656.25mA
0111 = 750mA
1000 = 843.75mA
1001 = 937.5mA
1010 = 1031.25mA
1011 = 1125mA
1100 = 1218.75mA
1101 = 1312.5mA
1110 = 1406.25mA
1111 = 1500mA(default) */
#define FLASH_LUM_LEVEL_NUM    (16)

/* Torch Current
0000 = 48.4mA(default)
0001 = 93.74mA
0010 = 140.63mA
0011 = 187.5mA
0100 = 234.38mA
0101 = 281.25mA
0110 = 328.13mA
0111 = 375mA */
#define TORCH_LUM_LEVEL_NUM    (8)

#define FLASH_TIMEOUT_400      (0x03)

static struct device_attribute lm3642_led;
static mini_camera_flashlight lm3642_intf;
struct i2c_client *lm3642_client;
typedef struct flash_config{
	struct pinctrl *pinctrl;
	struct pinctrl_state *pinctrl_def;
	struct pinctrl_state *pinctrl_idle;
	int flash_mask_pin;
	int flash_strb_pin;
}FLASH_CONFIG;

FLASH_CONFIG flash_config;
	
static int brightness_level = 0;
static unsigned int flash_config_type = 0;

#define I2C_BUS_NUM     0
#define DEVICE_LM3642_NAME   "LM3642"
#define DEVICE_LM3642_ADDR   0x63
static struct i2c_board_info lm3642_info = {
         .type = DEVICE_LM3642_NAME,
         .addr = DEVICE_LM3642_ADDR,
};

#define K3_FLASH_BLOCK	"block_flash"
//static struct iomux_block *gpio_block;
//static struct block_config *block_conf;
static int lm3642_camera_mode_flag = 0;
static int torch_level_backup = 0;
static int torch_level = 0;
static int brightness_level_backup = 0;
static struct workqueue_struct *power_key_4s_work_queue = NULL;
static struct work_struct power_key_4s_work;
static struct workqueue_struct *power_key_release_work_queue = NULL;
static struct work_struct power_key_release_work;

typedef enum {
	TX_PIN_MODE = 0,
	TORCH_PIN_MODE,
} pin_mode;

static pin_mode curr_pin_mode = TORCH_PIN_MODE;

extern int register_torch_led(struct device_attribute *attr);
static int lm3642_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int lm3642_remove(struct i2c_client *client);
static void lm3642_shutdown(struct i2c_client *client);
static ssize_t lm3642_led_torch_mode_get_brightness(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t lm3642_led_torch_mode_set_brightness(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);

static const struct i2c_device_id lm3642_id[] = {
	{DEVICE_LM3642_NAME, 0},
	{}
};

static struct i2c_driver lm3642_driver = {
	.driver = {
		   .name = DEVICE_LM3642_NAME,
		   },
	.probe = lm3642_probe,
	.remove = lm3642_remove,
	.shutdown = lm3642_shutdown,
	.id_table = lm3642_id,
};

static struct device_attribute lm3642_led=
    __ATTR(lightness, 0664, lm3642_led_torch_mode_get_brightness,
                        lm3642_led_torch_mode_set_brightness);

#ifdef CONFIG_FLASH_THERMAL_PROTECT
static DEFINE_SPINLOCK(led_stat_lock);
static bool thermal_protect_led_stat = true;
static void thermal_protect_set_flash_stat(bool thermal_led_stat);
static bool thermal_protect_get_flash_stat(void);
static ssize_t thermal_protect_flash_led_state_get(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t thermal_protect_flash_led_state_set(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);
static struct device_attribute thermal_protect_flash_led=
    __ATTR(thermal_protect_flash_led_state, 0664, thermal_protect_flash_led_state_get,
                        thermal_protect_flash_led_state_set);
#endif

/*
 **************************************************************************
 * FunctionName: lm3642_i2c_read;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int lm3642_i2c_read(char *rxData, int length)
{
	int ret = 0;
	struct i2c_msg msgs[] = {
		{
		 .addr = lm3642_client->addr,
		 .flags = I2C_M_RD,
		 .len = length,
		 .buf = rxData,
		 },
	};

	ret = i2c_transfer(lm3642_client->adapter, msgs, 1);
	if (ret < 0)
		print_error("%s: transfer error %d\n", __func__, ret);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: lm3642_i2c_write;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int lm3642_i2c_write(char *txData, int length)
{
	int ret = 0;
	struct i2c_msg msg[] = {
		{
		 .addr = lm3642_client->addr,
		 .flags = 0,
		 .len = length,
		 .buf = txData,
		 },
	};
	ret = i2c_transfer(lm3642_client->adapter, msg, 1);
	if (ret < 0)
		print_error("%s: transfer error %d\n", __func__, ret);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: lm3642_read_reg8;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int lm3642_read_reg8(u8 reg, u8 *val)
{
	int ret;
	u8 buf[1] = {0};

	print_debug("Enter Function:%s", __FUNCTION__);

	if (NULL == lm3642_client) {
		print_error("%s no client", __func__);
		return -ENODEV;
	}

	buf[0] = reg;
	ret = lm3642_i2c_write(buf, 1);
	if (ret < 0) {
		print_error("lm3642 read reg error(%d), reg=%x", ret, reg);
	}

	ret = lm3642_i2c_read(val, 1);
	if (ret < 0) {
		print_error("lm3642 read reg error(%d), reg=%x", ret, reg);
	}

	return ret;

}

/*
 **************************************************************************
 * FunctionName: lm3642_write_reg8;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int lm3642_write_reg8(u8 reg, u8 val)
{
	u8 buf[2];
	print_debug("Enter Function:%s", __FUNCTION__);

	if (NULL == lm3642_client) {
		print_error("%s no client", __func__);
		return -ENODEV;
	}

	buf[0] = reg;
	buf[1] = val;
	return lm3642_i2c_write(buf, 2);

}

/*
 **************************************************************************
 * FunctionName: lm3642_set_gpio;
 * Description : power for camera sensor;
 * Input       : camera_power_state power_state;
                     unsigned gpio
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int lm3642_set_gpio(unsigned gpio, char *name,int value)
{
    int ret = -EINVAL;

	print_debug("enter %s", __func__);

#if 0
    if (GPIO_FLASH_STRB == gpio) {
        label = "M_GPIO_FLASH_STRB";
    } else if (GPIO_FLASH_MASK == gpio) {
        label = "M_GPIO_FLASH_MASK";
    } else {
        print_error("%s: invalid request gpio %d for lm3642 flash", __func__, gpio);
        return -EINVAL;
    }
#endif

    ret = gpio_request(gpio, name);
    if (ret < 0) {
        print_error("%s: request flash gpio - %d(%s) failed, result = %d.", __func__, gpio, name, ret);
        return -EINVAL;
    }

    ret = gpio_direction_output(gpio, value);
    if (ret < 0) {
        print_error("%s: fail to set flash gpio - %d(%s), result = %d.", __func__, gpio, name, ret);
    }

    gpio_free(gpio);

	print_debug("leave %s", __func__);

    return ret;
}

/*
 **************************************************************************
 * FunctionName: lm3642_turn_off;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int lm3642_turn_off(void)
{
    int ret = 0;
	print_info("enter %s", __FUNCTION__);

	#ifdef CONFIG_FLASH_THERMAL_PROTECT
	spin_lock(&led_stat_lock);
	#endif
	lm3642_camera_mode_flag = 0;
    brightness_level = 0;
	#ifdef CONFIG_FLASH_THERMAL_PROTECT
	spin_unlock(&led_stat_lock);
	#endif
	lm3642_write_reg8(REG_ENABLE, MODE_STANDBY);
    torch_level = 0;
	if(flash_config_type >= 2) //default in lowpower mode
    {
        if(curr_pin_mode == TX_PIN_MODE)
        {
            /* set lowpower mode */
    		ret = pinctrl_select_state(flash_config.pinctrl, flash_config.pinctrl_idle); 
    		if (ret != 0) {
                print_error("%s: set lowpower mode fail.\n",__func__);
		}
            else {
                curr_pin_mode = TORCH_PIN_MODE;
            }
        }
    }
    else //default in normal mode
    {
        if(curr_pin_mode == TORCH_PIN_MODE)
        {
            if(flash_config_type == 1)
            {
                //lm3642_set_gpio(GPIO_FLASH_MASK, 0);
                lm3642_set_gpio(flash_config.flash_mask_pin,"M_GPIO_FLASH_MASK",1);			
            }
            /* set normal mode */
			
		ret =pinctrl_select_state(flash_config.pinctrl, flash_config.pinctrl_def); 
		if (ret != 0) {
                print_error("%s: set lowpower mode fail.\n",__func__);
		}
            else {
                curr_pin_mode = TX_PIN_MODE;
            }
        }
    }
	return 0;
}

/*
 **************************************************************************
 * FunctionName: _lm3642_turn_on;
 * Description : turn on flashlight;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int _lm3642_turn_on(work_mode mode, u8 lum)
{
	u8 val = 0;
	u8 enable = 0;
    int ret = 0;

	print_debug("enter %s", __FUNCTION__);

	#ifdef CONFIG_FLASH_THERMAL_PROTECT_CONTINUE
	if(!thermal_protect_get_flash_stat())
	{
		print_info("temperature is too high,can't open the flash led");
		return -1;
	}
	#endif

	lm3642_read_reg8(REG_FLAGS, &val);//clear error flag,resume chip
	print_info("@@@### lm3642 mode = %s, flags = 0x%02x", FLASH_MODE == mode ? "flash" : "torch", val);
	lm3642_read_reg8(REG_CURRENT_CONTROL, &val);

	if (mode == FLASH_MODE) {
		val = (val & 0xf0) | lum;
        enable = MODE_FLASH | TX_PIN;
        if(curr_pin_mode == TORCH_PIN_MODE) {
            ret = pinctrl_select_state(flash_config.pinctrl, flash_config.pinctrl_def); 
            if(ret != 0) {
                print_error("%s: set normal mode fail.\n",__func__);
            }
            else {
                curr_pin_mode = TX_PIN_MODE;
            }
        }
		print_debug("start FLASH_MODE");
	} else if (mode == TORCH_MODE) {
		val = (lum << 4) + (val & 0x0f);
		enable = MODE_TORCH;
        torch_level = lum;
        if(flash_config_type != 0) {
		if(curr_pin_mode == TX_PIN_MODE)
            {
                /* set gpio work mode */
		ret = pinctrl_select_state(flash_config.pinctrl, flash_config.pinctrl_idle); 
		if (ret != 0) {
                    print_error("%s: set gpio mode fail.\n",__func__);
		}
                else {
                    curr_pin_mode = TORCH_PIN_MODE;
                    enable |= TORCH_PIN;
                    if(flash_config_type == 1) {
						
                       // lm3642_set_gpio(GPIO_FLASH_MASK, 1);
                       lm3642_set_gpio(flash_config.flash_mask_pin,"M_GPIO_FLASH_MASK",1);
                    }
                }
            }
            else {
                enable |= TORCH_PIN;
                if(flash_config_type == 1) {
                   // lm3642_set_gpio(GPIO_FLASH_MASK, 1);
                   lm3642_set_gpio(flash_config.flash_mask_pin,"M_GPIO_FLASH_MASK",1);
                }
            }
        }
	print_debug("start TORCH_MODE");
	}

	lm3642_write_reg8(REG_CURRENT_CONTROL, val);
	lm3642_write_reg8(REG_ENABLE, enable);

    #ifdef CONFIG_FLASH_THERMAL_PROTECT
	spin_lock(&led_stat_lock);
	#endif
	lm3642_camera_mode_flag = 1;
	#ifdef CONFIG_FLASH_THERMAL_PROTECT
	spin_unlock(&led_stat_lock);
	#endif

	return 0;
}

/*
 **************************************************************************
 * FunctionName: lm3642_turn_on;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int lm3642_turn_on(work_mode mode, flash_lum_level lum)
{
	int ret = 0;

    if(lum > LUM_LEVEL_MAX)
	{
		print_error("Unsupport lum_level:%d", lum);
		return -1;
	}

    if (mode == TORCH_MODE) {
        lum = TORCH_CURRENT_FOR_PREFLASH;
        /*
        if (lum >= TORCH_LUM_LEVEL_NUM) {
		print_error("Unsupport torch_lum_level: %d", lum);
		return -1;
        }
        */
    } else {
        lum = FLASH_CURRENT_FOR_FLASH;
        /*
        if (lum >= FLASH_LUM_LEVEL_NUM) {
		print_error("Unsupport flash_lum_level: %d", lum);
		return -1;
        }
        */
    }
	ret = _lm3642_turn_on(mode, lum);
	if(ret)
	{
		return -1;
	}

	return ret;
}

/*
 **************************************************************************
 * FunctionName: lm3642_reset;
 * Description : software reset;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int lm3642_reset(void)
{
	print_error("enter %s", __FUNCTION__);
	lm3642_turn_off();
	return 0;
}

/*
 **************************************************************************
 * FunctionName: lm3642_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void lm3642_exit(void)
{
	int ret = 0;

	print_info("enter %s", __FUNCTION__);

	lm3642_turn_off();
    torch_level_backup = 0;
    brightness_level_backup = 0;
	/* set gpio work mode */
	ret = pinctrl_select_state(flash_config.pinctrl, flash_config.pinctrl_idle); 
	if (ret != 0) {
		print_error("%s: failed to set iomux flash to gpio mode.\n", __func__);
		return;
	}

	return;
}

/*
 **************************************************************************
 * FunctionName: lm3642_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int lm3642_init(void)
{
	int ret = 0;
	print_info("Enter Function:%s", __FUNCTION__);

    #ifdef CONFIG_FLASH_THERMAL_PROTECT
	spin_lock(&led_stat_lock);
	#endif
	lm3642_camera_mode_flag = 0;
	brightness_level = 0;
	#ifdef CONFIG_FLASH_THERMAL_PROTECT
	spin_unlock(&led_stat_lock);
	#endif
    torch_level = 0;
	lm3642_write_reg8(REG_ENABLE, MODE_STANDBY);

    if(flash_config_type >= 2)
    {
	    //lm3642_set_gpio(GPIO_FLASH_MASK, 1);
        lm3642_set_gpio(flash_config.flash_mask_pin,"M_GPIO_FLASH_MASK",1);
        curr_pin_mode = TORCH_PIN_MODE;
        /* set gpio work mode */
    	ret = pinctrl_select_state(flash_config.pinctrl, flash_config.pinctrl_idle); 
    	if (ret != 0) {
    		print_error("%s: failed to set iomux flash to gpio mode.\n", __func__);
    		return -EINVAL;
    	}
    }
    else
    {
        curr_pin_mode = TX_PIN_MODE;
        /* set gpio work mode */
        ret = pinctrl_select_state(flash_config.pinctrl, flash_config.pinctrl_def); 

        if (ret != 0) {
    		print_error("%s: failed to set iomux flash to gpio mode.\n", __func__);
            return -EINVAL;
	    }
    }
	return 0;
}

/*
 **************************************************************************
 * FunctionName: lm3642_led_torch_mode_get_brightness;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static ssize_t lm3642_led_torch_mode_get_brightness(struct device *dev, struct device_attribute *attr,char *buf)
{
    int ret = 0;

    sprintf(buf,"brightness_level= %d\n",brightness_level);
    ret = strlen(buf)+1;

    return ret;
}

/*
 **************************************************************************
 * FunctionName: lm3642_led_torch_mode_set_brightness;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static ssize_t lm3642_led_torch_mode_set_brightness(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	u8 level = 0;

	print_info("enter %s", __func__);

	if(kstrtou8(buf,0,&level))
	{
		printk("fail to recover str to U8 %s\n",__func__);
		return -1;
	}

    if(brightness_level == level)
    {
        return count;
    }

    if (level == 0)//close
    {
        if (lm3642_camera_mode_flag) {
		lm3642_exit();
	}
    }
    else
    {
        if(level > 7) {
			printk("Input the wrong number\n");
			return -1;
		}

        ret = _lm3642_turn_on(TORCH_MODE, level-1);
        if(ret < 0) {
            print_error("set light level error");
            return -1;
        }

        #ifdef CONFIG_FLASH_THERMAL_PROTECT
			spin_lock(&led_stat_lock);
		#endif
            brightness_level = level;
		#ifdef CONFIG_FLASH_THERMAL_PROTECT
			spin_unlock(&led_stat_lock);
		#endif
    }

    return count;
}

/*
 **************************************************************************
 * FunctionName: test_flash;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int test_flash(void)
{
	print_info("enter %s", __FUNCTION__);

	lm3642_turn_on(TORCH_MODE, 0);
	msleep(4000);
	//dump_reg();
	lm3642_turn_off();
	msleep(1000);
	//dump_reg();

	lm3642_turn_on(FLASH_MODE, 1);
	msleep(1000);
	//dump_reg();
	lm3642_turn_off();
	//dump_reg();

	return 0;
}

#ifdef CONFIG_FLASH_THERMAL_PROTECT
#if 0
static bool thermal_protect_get_flash_stat(void)
{
	return thermal_protect_led_stat;
}
#endif
static void thermal_protect_set_flash_stat(bool thermal_led_stat)
{
	thermal_protect_led_stat = thermal_led_stat;
}

static ssize_t thermal_protect_flash_led_state_get(struct device *dev, struct device_attribute *attr,char *buf)
{
    int ret;
    sprintf(buf,"thermal_protect_led_stat = %d\n",thermal_protect_led_stat);
    ret = strlen(buf)+1;
    return ret;
}

static ssize_t thermal_protect_flash_led_state_set(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	print_info("enter %s", __func__);
    if (buf[0] == '0')
    {
	if (lm3642_camera_mode_flag) {
		lm3642_exit();
	}
		thermal_protect_led_stat = false;
    }
	else if (buf[0] == '1')
	{
		thermal_protect_led_stat = true;
	}
	else
	{
		printk("Input the wrong number\n");
		return -1;
	}
	return count;
}
#endif

/*
 **************************************************************************
 * FunctionName: lm3642_set_default;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void lm3642_set_default(void)
{
	print_debug("enter %s", __FUNCTION__);

	lm3642_intf.init		= lm3642_init;
	lm3642_intf.exit		= lm3642_exit;
	lm3642_intf.reset		= lm3642_reset;
	lm3642_intf.turn_on		= lm3642_turn_on;
	lm3642_intf.turn_off	= lm3642_turn_off;
	lm3642_intf.test		= test_flash;
	lm3642_intf.type		= LED_FLASH;
}

//process long press key 4s event
static void lm3642_power_key_4s_work_func(struct work_struct *work)
{
    print_info("enter %s",__func__);
    if(torch_level > 0) {
        torch_level_backup = torch_level;
        brightness_level_backup = brightness_level;
        lm3642_turn_off();
    }
}

//process release key event
static void lm3642_power_key_release_work_func(struct work_struct *work)
{
    print_debug("enter %s",__func__);
    if(torch_level_backup > 0) {
        _lm3642_turn_on(TORCH_MODE, torch_level_backup);
        torch_level_backup = 0;
        if(brightness_level_backup) {
            #ifdef CONFIG_FLASH_THERMAL_PROTECT
			spin_lock(&led_stat_lock);
		    #endif
            brightness_level = brightness_level_backup;
		    #ifdef CONFIG_FLASH_THERMAL_PROTECT
			spin_unlock(&led_stat_lock);
		    #endif       
            brightness_level_backup = 0;
        }
    }
}

#if 0
//callback func
static void lm3642_torch_process(int status)
{
    if(status == 2) { //power_key_press_4s
        if(torch_level > 0) {
            queue_work(power_key_4s_work_queue, &power_key_4s_work);
        }
    } else if(status == 0) { //power_key_release
        if(torch_level_backup > 0) {
            queue_work(power_key_release_work_queue, &power_key_release_work);
        }
    }
}
#endif
extern void notify_key_status_to_device(void (*callback)(int)); //hi6620_pow_key.c
/*
 **************************************************************************
 * FunctionName: lm3642_probe;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int lm3642_probe(struct i2c_client *client, const struct i2c_device_id *id)
{

    struct device_node *np = NULL;
    struct platform_device *pdev =NULL;
    struct i2c_adapter *adapter = NULL;
    struct regulator *flash_mask_vdd = NULL;
    int ret = 0;
    u8 val = 0;
    
    print_debug("Enter %s", __FUNCTION__);
    np = of_find_compatible_node(NULL, NULL, "hisi,lm3642");
    if (np ==NULL)
    {
        print_error("the device node lm3642 is null\n");
        return -1;
    }
    pdev=of_find_device_by_node(np);
		
    if (pdev ==NULL)
    {
        print_error("the device lm3642 is null\n");
        return -1;
    }
	adapter = client->adapter;
	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA
				     | I2C_FUNC_SMBUS_WRITE_BYTE)) {
		return -EIO;
	}

	lm3642_client = client;

	lm3642_read_reg8(REG_FLASH_FEATURES,&val);
    if(val == 0)
    {
        lm3642_client = NULL;
        return -1;
    }

    val &= 0xF8;//clear timeout
    val |= FLASH_TIMEOUT_400; //set 400ms
    lm3642_write_reg8(REG_FLASH_FEATURES,val);

    lm3642_write_reg8(REG_IVFM,0x00);

	if(register_torch_led(&lm3642_led))
    {
	     print_error( "%s:Unable to create interface\n", __func__, &client->dev);
	     return -ENOMEM;
    }

	#ifdef CONFIG_FLASH_THERMAL_PROTECT
	if(register_torch_led(&thermal_protect_flash_led))
    {
	     print_error( "%s:Unable to create thermal_protect_flash_led interface\n", __func__);
	     return -ENOMEM;
    }
	#endif

    //adapter V3 board, flash_config_type = 1 means flash mask pin
    if(false == get_hw_config_int("flash/lm3642", &flash_config_type, NULL))
    {
        flash_config_type = 0;
        print_info("%s: no flash config, use VA as default. flash_config_type = %d\n",__func__,flash_config_type);
    }

	flash_config.pinctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(flash_config.pinctrl )) {
	    print_error("%s :could not get pinctrl\n",__FUNCTION__);
		return -1;
	}
	
	flash_config.pinctrl_def = pinctrl_lookup_state(flash_config.pinctrl,PINCTRL_STATE_DEFAULT);
	if (IS_ERR(flash_config.pinctrl_def)) {
        print_error("%s : could not get def state\n", __FUNCTION__);
		return -1;
    }  
	
	flash_config.pinctrl_idle = pinctrl_lookup_state(flash_config.pinctrl,PINCTRL_STATE_IDLE);
	if (IS_ERR(flash_config.pinctrl_idle)) {
        print_error("%s : could not get idle state\n", __FUNCTION__);
		return -1;
    }  	 
	
	ret = pinctrl_select_state(flash_config.pinctrl, flash_config.pinctrl_idle); 
	if (ret != 0) {
		print_error("%s: failed to set iomux flash to gpio mode.\n", __func__);
		return -1;
	}

	 if (of_property_read_u32(np, "huawei,flash_mask_pin",&flash_config.flash_mask_pin))
		 print_info("%s:huawei,switch_pin1 read error\n",__FUNCTION__);

	print_info("%s:huawei,switch_pin1 %d\n",__FUNCTION__,flash_config.flash_mask_pin);

	 if (of_property_read_u32(np, "huawei,flash_strb_pin",&flash_config.flash_strb_pin))
		 print_info("%s:huawei,flash_strb_pin read error\n",__FUNCTION__);

	print_info("%s:huawei,switch_pin1 %d\n",__FUNCTION__,flash_config.flash_strb_pin);
	#if 0
	/* get gpio block */
	gpio_block = iomux_get_block(K3_FLASH_BLOCK);
	if (!gpio_block) {
		print_error("%s: failed to get iomux %s\n", __func__, K3_FLASH_BLOCK);
		return -EINVAL;
	}

	/* get gpio config block */
	block_conf = iomux_get_blockconfig(K3_FLASH_BLOCK);
	if (!block_conf) {
		print_error("%s: failed to get iomux isp %s\n", __func__, K3_FLASH_BLOCK);
		return -EINVAL;
	}

	/* set gpio work mode */
	ret = blockmux_set(gpio_block, block_conf, LOWPOWER);
	if (ret != 0) {
		print_error("%s: failed to set iomux flash to gpio mode.\n", __func__);
		return -EINVAL;
	}
	#endif
	

    if(flash_config_type == 2) { //process long press key 4s
        INIT_WORK(&power_key_4s_work, lm3642_power_key_4s_work_func);
        power_key_4s_work_queue = create_singlethread_workqueue(DEVICE_LM3642_NAME);
        if(!power_key_4s_work_queue) {
            print_error("%s: create irq work failed.\n", __func__);
            return -EINVAL;
        }

        INIT_WORK(&power_key_release_work, lm3642_power_key_release_work_func);
        power_key_release_work_queue = create_singlethread_workqueue(DEVICE_LM3642_NAME);
        if(!power_key_release_work_queue) {
            destroy_workqueue(power_key_4s_work_queue);
            print_error("%s: create irq work failed.\n", __func__);
            return -EINVAL;
        }
		//register callback func
//        notify_key_status_to_device(lm3642_torch_process);
    } else if(flash_config_type == 3) { /*add a flash_mask_io_vdd to control the flash mask gpio*/
        flash_mask_vdd = regulator_get(&pdev->dev, "FLASH_MASK_IO_VDD");
        if (IS_ERR(flash_mask_vdd)) {
            print_error("%s: Regulator get failed flash_mask_io_vdd.\n", __func__);
            return -EINVAL;
        }
        ret = regulator_set_voltage(flash_mask_vdd, 1800000, 1800000);
        if(ret) {
            print_error("%s: Regulator set failed flash_mask_io_vdd.\n", __func__);
            return -EINVAL;
        }

        ret = regulator_enable(flash_mask_vdd);
	if (ret) {
		print_error("%s: Regulator enable failed flash_mask_io_vdd.\n", __func__);
		return -EINVAL;
		}
    }

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
    /* detect current device successful, set the flag as present */
        set_hw_dev_flag(DEV_I2C_TPS);
#endif

	return 0;
}

/*
 **************************************************************************
 * FunctionName: lm3642_remove;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int lm3642_remove(struct i2c_client *client)
{
	print_info("Enter %s", __FUNCTION__);
    if(power_key_4s_work_queue) {
        destroy_workqueue(power_key_4s_work_queue);
    }
    if(power_key_release_work_queue) {
        destroy_workqueue(power_key_release_work_queue);
    }
	lm3642_reset();
	lm3642_client->adapter = NULL;
	return 0;
}

/*
 **************************************************************************
 * FunctionName: lm3642_shutdown;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void lm3642_shutdown(struct i2c_client *client)
{
	print_info("Enter %s", __FUNCTION__);
	lm3642_reset();
	lm3642_client->adapter = NULL;
	return;
}

/*
 **************************************************************************
 * FunctionName: lm3642_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int __init lm3642_module_init(void)
{
	struct i2c_adapter  *Pr_i2c_adapter = NULL;
	u32 val = 0;
	int ret = 0;

	Pr_i2c_adapter = i2c_get_adapter(I2C_BUS_NUM);
	if(Pr_i2c_adapter == NULL)
	{
		printk("%s can't get number %d  i2c_adapter!!!!\n",__func__,I2C_BUS_NUM);
		return -1;
	}

	lm3642_client = i2c_new_device(Pr_i2c_adapter, &lm3642_info);
	if(lm3642_client == NULL)
	{
		printk("%s can't add device on number %d  i2c_adapter!!!!\n",__func__,I2C_BUS_NUM);
		return -1;
	}

	print_debug("enter %s", __FUNCTION__);
	i2c_add_driver(&lm3642_driver);

	if(lm3642_client == NULL)
	{
		printk("%s can't add driver on number %d  i2c_adapter!!!!\n",__func__,I2C_BUS_NUM);
		return -1;
	}

	lm3642_set_default();


    if(get_hw_config_int("camera/miniisp", &val, NULL) == true){
       if(val == 1){
#if defined(CONFIG_CAMERA_MINI_ISP)
           	ret = mini_register_camera_flash(&lm3642_intf);
#endif
       }
    }
    else{
        ret = register_camera_flash((camera_flashlight*)&lm3642_intf);
    }

	#ifdef CONFIG_FLASH_THERMAL_PROTECT
	thermal_protect_set_flash_stat(true);
	#endif
	return ret;
}

/*
 **************************************************************************
 * FunctionName: lm3642_module_deinit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void __exit lm3642_module_deinit(void)
{
	u32 val = 0;

	print_debug("enter %s", __FUNCTION__);

	i2c_del_driver(&lm3642_driver);

    if(get_hw_config_int("camera/miniisp", &val, NULL) == true){
       if(val == 1){
#if defined(CONFIG_CAMERA_MINI_ISP)
           	mini_unregister_camera_flash(&lm3642_intf);
#endif
       }
    }
    else{
        unregister_camera_flash((camera_flashlight*)(&lm3642_intf));
    }
	return;
}

module_init(lm3642_module_init);
module_exit(lm3642_module_deinit);
MODULE_AUTHOR("Jiezhou");
MODULE_DESCRIPTION("lm3642 Flash Driver");
MODULE_LICENSE("GPL");
/********************************** END ***************************************/
