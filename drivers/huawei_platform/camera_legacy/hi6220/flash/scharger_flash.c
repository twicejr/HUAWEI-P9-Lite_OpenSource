
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/platform_device.h>
//#include <mach/scharger_flash.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <sound/hissc_common.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/leds.h>
#include <linux/power/hisi_hi6521_charger_power.h>

#include "../isp/k3_ispv1_io.h"
#include "../isp/sensor_common.h"
#include "../isp/cam_dbg.h"
#include "../isp/cam_log.h"
#include "../isp/k3_isp_io.h"

#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#endif

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "SCHAREGER_FLASH"

#define SCHG_FLASH_BOOST_REGULATOR      "pvdd_classd"   /*"schg_boost3"*/
#define SCHG_FLASH_FLASH_MODE_REGULATOR "flashled_power" /*"schg_source1"*/
#define SCHG_FLASH_TORCH_MODE_REGULATOR "torchled_power" /*"schg_source2"*/

#define SCHG_AUDIO_CODEC_MUTE_FLAG      "audio_codec_mute_flag"

#define FLASH_LUM_LEVEL_NUM    (16)
#define TORCH_LUM_LEVEL_NUM    (8)

#define FLASH_TIMEOUT_MS (300)

#define FLASH_TORCH_MODE (1)
#define FLASH_FLASH_MODE (1<<1)
#define SAFE_DOWN(lock) \
		do { \
			if (down_interruptible((lock))) { \
				print_error("%s get busy_lock fail", __func__); \
				return -EINTR; \
			} \
		} while (0)
#define SAFE_UP(lock) up((lock))

//source2 current table, values must be identical to scharger's dts
static const int torch_lum_table[TORCH_LUM_LEVEL_NUM]={50000, 100000, 150000,200000, 250000, 300000, 350000, 400000};
//source1 current table, values must be identical to scharger's dts
static const int flash_lum_table[FLASH_LUM_LEVEL_NUM]={125000, 250000, 375000, 500000, 625000, 750000, 875000, 1000000,
	1125000, 1250000, 1375000, 1500000, 1500000, 1500000, 1500000, 1500000};
//#define DEBUG_DEBUG 1

static camera_flashlight scharger_flash_intf;
static work_mode flash_mode = TORCH_MODE;
static struct regulator *flash_inter_ldo = NULL;
static struct regulator *flash_mode_ldo = NULL;
static struct regulator *torch_mode_ldo = NULL;
static int flash_on = 0;
static bool flash_mute = 0;
static int audio_codec_mute_flag = 0;
extern int register_torch_led(struct device_attribute *attr);
extern int mmi_register_torch_led(void	(*func)(struct led_classdev *led_cdev, enum led_brightness brightness), struct device_attribute *attr);
int scharger_flash_init(void);
void scharger_flash_exit(void);
int scharger_flash_reset(void);
static struct semaphore busy_lock;
static struct semaphore switch_lock;
static bool flash_init = false;
static int brightness_level = 0;
static ssize_t scharger_led_torch_mode_get_brightness(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t scharger_led_torch_mode_set_brightness(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);
static struct device_attribute scharger_led=
    __ATTR(lightness, 0664, scharger_led_torch_mode_get_brightness,
                        scharger_led_torch_mode_set_brightness);


/*
 **************************************************************************
 * FunctionName: scharger_flash_turn_off;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int scharger_flash_turn_off(void)
{

	print_info("enter %s flash_mode = %d ", __func__ ,flash_mode);
	
	SAFE_DOWN(&switch_lock);

	if ( FLASH_FLASH_MODE&flash_on){
		if(flash_mode_ldo){
			regulator_disable(flash_mode_ldo);
		}
		if (flash_inter_ldo){
			regulator_disable(flash_inter_ldo);
		}
		flash_on &= ~FLASH_FLASH_MODE;
		if (audio_codec_mute_flag && (true == flash_mute)){
			audio_codec_mute_pga(0);
			flash_mute = false;
		}
	}

	if(FLASH_TORCH_MODE&flash_on){
		if(torch_mode_ldo){
			regulator_disable(torch_mode_ldo);
		}
		if (flash_inter_ldo){
			regulator_disable(flash_inter_ldo);
		}
		flash_on &= ~FLASH_TORCH_MODE;

	}

	SAFE_UP(&switch_lock);

	return 0;
}
/*
 **************************************************************************
 * FunctionName: scharger_flash_turn_on;
 * Description : turn on flashlight;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int scharger_flash_turn_on(work_mode mode, flash_lum_level lum)
{
	int ret = 0;
	print_info("enter %s work_mode = %d , lum = %d",__func__, mode, lum);
	SAFE_DOWN(&switch_lock);
	if (mode == TORCH_MODE) {
		if (lum >= TORCH_LUM_LEVEL_NUM) {
			print_error("Unsupport torch_lum_level: %d", lum);
			ret = -1;
			goto out;
		}

		
		flash_mode = TORCH_MODE;

		/*if flash has already on go out do nothing*/
		if(FLASH_TORCH_MODE&flash_on){
			ret = 0;
			print_info("%s torch mode already in do nothing",__func__);
			goto out;
		}
		
		ret = regulator_enable(flash_inter_ldo);
		if (ret < 0){
			print_error("%s regulator_enable flash_inter_ldo fail ret = %d", __func__, ret);
			#if defined (CONFIG_HUAWEI_DSM)
			if (!dsm_client_ocuppy(client_ovisp22)){
			    dsm_client_record(client_ovisp22,"[%s]regulator_enable flash_inter_ldo fail mode %d\n",__func__,mode);
			    dsm_client_notify(client_ovisp22, DSM_ISP22_FLASH_ERROR_NO);
			}
			#endif
			goto out;
		}

		udelay(500);

		ret = regulator_set_current_limit(torch_mode_ldo, torch_lum_table[lum], torch_lum_table[lum]);
		if (ret < 0){
			print_error("%s regulator_set_current_limit  fail ret = %d current is %d", __func__, ret, (torch_lum_table[lum]));
			goto out;
		}

		ret = regulator_enable(torch_mode_ldo);
		if (ret < 0){
			print_error("%s regulator_enable torch_mode_ldo fail ret = %d", __func__, ret);
			#if defined (CONFIG_HUAWEI_DSM)
			if (!dsm_client_ocuppy(client_ovisp22)){
			    dsm_client_record(client_ovisp22,"[%s]regulator_enable torch_mode_ldo fail mode %d\n",__func__,mode);
			    dsm_client_notify(client_ovisp22, DSM_ISP22_FLASH_ERROR_NO);
			}
			#endif
			if (flash_inter_ldo){
				regulator_disable(flash_inter_ldo);
			}
			goto out;
		}
		flash_on |= FLASH_TORCH_MODE;
	} else {
		if (lum >= FLASH_LUM_LEVEL_NUM) {
			print_error("Unsupport flash_lum_level: %d", lum);
			ret = -1;
			goto out;
		}
		
		flash_mode = FLASH_MODE;
		
		if(FLASH_FLASH_MODE&flash_on){
			ret = 0;
			print_info("%s flash mode already in do nothing",__func__);
			goto out;
		}

		if(audio_codec_mute_flag){
			audio_codec_mute_pga(1);
			flash_mute = true;
		}

		ret = scharger_flash_led_timeout_config(FLASH_TIMEOUT_MS);
		if (ret < 0){
			print_error("%s scharger_flash_led_timeout_config  fail ret = %d ", __func__, ret);
			if (flash_inter_ldo){
				regulator_disable(flash_inter_ldo);
			}
			goto out;
		}
		ret = scharger_flash_led_timeout_enable();
		if (ret < 0){
			print_error("%s scharger_flash_led_timeout_enable  fail ret = %d ", __func__, ret);
			goto out;
		}
		ret = regulator_enable(flash_inter_ldo);
		if (ret < 0){
			print_error("%s regulator_enable flash_inter_ldo fail ret = %d", __func__, ret);
			#if defined (CONFIG_HUAWEI_DSM)
			if (!dsm_client_ocuppy(client_ovisp22)){
			    dsm_client_record(client_ovisp22,"[%s]regulator_enable flash_inter_ldo fail mode %d\n",__func__,mode);
			    dsm_client_notify(client_ovisp22, DSM_ISP22_FLASH_ERROR_NO);
			}
			#endif
			goto out;
		}
		udelay(500);

		ret = regulator_set_current_limit(flash_mode_ldo, flash_lum_table[lum], flash_lum_table[lum]);
		if (ret < 0){
			print_error("%s regulator_set_current_limit  fail ret = %d current is %d", __func__, ret, (flash_lum_table[lum]));
			if (flash_inter_ldo){
				regulator_disable(flash_inter_ldo);
			}
			goto out;
		}

		ret = regulator_enable(flash_mode_ldo);
		if (ret < 0){
			print_error("%s regulator_enable torch_mode_ldo fail ret = %d", __func__, ret);
			#if defined (CONFIG_HUAWEI_DSM)
			if (!dsm_client_ocuppy(client_ovisp22)){
			    dsm_client_record(client_ovisp22,"[%s]regulator_enable flash_mode_ldo fail mode %d\n",__func__,mode);
			    dsm_client_notify(client_ovisp22, DSM_ISP22_FLASH_ERROR_NO);
			}
			#endif
			if (flash_inter_ldo){
				regulator_disable(flash_inter_ldo);
			}
			goto out;
		}
		flash_on |= FLASH_FLASH_MODE;

	}
	
out:
	SAFE_UP(&switch_lock);
	return ret;
}
/*
 **************************************************************************
 * FunctionName: scharger_led_torch_mode_get_brightness;
 * Description : get torch lum level;
 * Input       : NA;
 * Output      : buff,current lum level;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static ssize_t scharger_led_torch_mode_get_brightness(struct device *dev, struct device_attribute *attr,char *buf)
{
    int ret = 0;

    sprintf(buf,"brightness_level= %d\n",brightness_level);
    ret = strlen(buf)+1;

    return ret;
}

/*
 **************************************************************************
 * FunctionName: scharger_led_torch_mode_set_brightness;
 * Description : get torch lum level;
 * Input       : buf, lum level to set (0 --turn off, 1~8 turn on);
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static ssize_t scharger_led_torch_mode_set_brightness(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	u8 level = 0;

	print_info("enter %s, previes level:%d", __func__, brightness_level);

	if(kstrtou8(buf,0,&level))
	{
		printk("fail to recover str to U8 %s\n",__func__);
		return -1;
	}

	if(brightness_level == level)
	{
		return count;
	}
	print_info("level is :%d", level);

	SAFE_DOWN(&busy_lock);

	if (flash_init == false)
	{
		scharger_flash_init();
	}

	if (0 == level)//close torch
	{
		brightness_level = level;
		scharger_flash_exit();
	}
	else//turn on torch
	{
		if(level >= TORCH_LUM_LEVEL_NUM)
		{
			print_error("Input the wrong number\n");
			ret = -1;
			goto out;
		}
		scharger_flash_turn_off();//turn off first if we want to change lum

		ret = scharger_flash_turn_on(TORCH_MODE, level);
		if(ret < 0) {
			print_error("set light level error");
			ret = -1;
			goto out;
		}
		brightness_level = level;
	}

	ret = count;

out:
	SAFE_UP(&busy_lock);
	return ret;
}

/*
 **************************************************************************
 * FunctionName: mini_scharger_led_torch_mode_set_brightness;
 * Description : get torch lum level;
 * Input       : buf, lum level to set (0 --turn off, 1~8 turn on);
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void mmi_scharger_led_torch_mode_set_brightness(struct led_classdev *led_cdev,
					  enum led_brightness brightness)
{
	int ret = 0;
	
	print_info("enter %s, previes level:%d", __func__, brightness_level);

	if(brightness_level == brightness)
	{
		return ;
	}
	print_info("level is :%d", brightness);

	SAFE_DOWN(&busy_lock);

	if (flash_init == false)
	{
		scharger_flash_init();
	}

	if (0 == brightness)//close torch
	{
		brightness_level = brightness;
		scharger_flash_exit();
	}
	else//turn on torch
	{
		if(brightness >= TORCH_LUM_LEVEL_NUM)
		{
			print_error("Input the wrong number\n");
			goto out;
		}
		scharger_flash_turn_off();//turn off first if we want to change lum

		ret = scharger_flash_turn_on(TORCH_MODE, brightness);
		if(ret < 0) {
			print_error("%s set light level error", __func__);
			goto out;
		}
		brightness_level = brightness;
	}


out:
	SAFE_UP(&busy_lock);
}

/*
 **************************************************************************
 * FunctionName: scharger_flash_reset;
 * Description : software reset;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int scharger_flash_reset(void)
{
	scharger_flash_turn_off();
	return 0;
}
/*
 **************************************************************************
 * FunctionName: scharger_flash_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void scharger_flash_exit(void)
{
	scharger_flash_turn_off();

	if (flash_inter_ldo) {
		regulator_put(flash_inter_ldo);
		flash_inter_ldo = NULL;
	}
	if (flash_mode_ldo) {
		regulator_put(flash_mode_ldo);
		flash_mode_ldo = NULL;
	}
	if (torch_mode_ldo) {
		regulator_put(torch_mode_ldo);
		torch_mode_ldo = NULL;
	}
	flash_init = false;

	return;
}

/*
 **************************************************************************
 * FunctionName: scharge_get_audio_codec_mute_flag;
 * Description : get audio_codec_mute_flag from hisi,hisi_sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : flag 1 : need mute
                      0 : no need mute;
                      -1: error
 * Other       : NA;
 **************************************************************************
 */
static int scharge_get_audio_codec_mute_flag(void)
{
    struct device_node *np = NULL;
    /*default is 1*/
    int flag = 1;

    np = of_find_compatible_node(NULL, NULL, "hisi,hisi_sensor");
    if (np ==NULL) {
        print_error("the device node hisi_sensor is null\n");
        return -1;
    }

    if (of_property_read_u32(np, SCHG_AUDIO_CODEC_MUTE_FLAG, &flag)){
        print_error("%s: audio_codec_mute_flag read nothing.\n",__FUNCTION__);
    } else {
        print_info("%s: audio_codec_mute_flag %d.\n",__FUNCTION__, flag);
    }

    return flag;
}

/*
 **************************************************************************
 * FunctionName: scharger_flash_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int scharger_flash_init(void)
{
	int ret = 0;

#if 0 /* refresh regulator logic name, z62576, 20140728 */
	struct device_node *np = NULL;
	struct platform_device *pdev =NULL;

	np = of_find_compatible_node(NULL, NULL, "hisi,scharger_flashlight");
	if (np ==NULL)
	{
		print_error("[Flash] the device node scharger_flashlight is null\n");
		return -1;
	}
	pdev=of_find_device_by_node(np);

	if (pdev == NULL)
	{
		print_error("[Flash]the device of scharger_flashlight is null\n");
		return -1;
	}
#endif

	/* get flash boost regulator */
	//flash_inter_ldo = regulator_get(&pdev->dev, SCHG_FLASH_BOOST_REGULATOR);
	flash_inter_ldo = regulator_get(NULL, SCHG_FLASH_BOOST_REGULATOR);
	if (IS_ERR_OR_NULL(flash_inter_ldo)) {
		print_error("%s: Could not get regulator : %s\n", __func__, SCHG_FLASH_BOOST_REGULATOR);
		return  -ENXIO;
	}

	/* get flash mode regulator */
	//flash_mode_ldo = regulator_get(&pdev->dev, SCHG_FLASH_FLASH_MODE_REGULATOR);
	flash_mode_ldo = regulator_get(NULL, SCHG_FLASH_FLASH_MODE_REGULATOR);
	if (IS_ERR_OR_NULL(flash_mode_ldo)) {
		print_error("%s: Could not get regulator : %s\n", __func__, SCHG_FLASH_FLASH_MODE_REGULATOR);
		ret =  -ENXIO;
		goto fail;
	}

	/* get torch mode regulator */
	//torch_mode_ldo = regulator_get(&pdev->dev, SCHG_FLASH_TORCH_MODE_REGULATOR);
	torch_mode_ldo = regulator_get(NULL, SCHG_FLASH_TORCH_MODE_REGULATOR);
	if (IS_ERR_OR_NULL(torch_mode_ldo)) {
		print_error("%s: Could not get regulator : %s\n", __func__, SCHG_FLASH_TORCH_MODE_REGULATOR);
		ret =  -ENXIO;
		goto fail;
	}
	/*get mute flag*/
	audio_codec_mute_flag = scharge_get_audio_codec_mute_flag();
	if(audio_codec_mute_flag < 0){
		print_error("%s: Could not get audio_codec_mute_flag");
	}

	flash_init = true;
	return 0;

fail:
	if (flash_inter_ldo) {
		regulator_put(flash_inter_ldo);
		flash_inter_ldo = NULL;
	}
	if (flash_mode_ldo) {
		regulator_put(flash_mode_ldo);
		flash_mode_ldo = NULL;
	}

	return ret;
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
	print_debug("enter %s", __func__);

	scharger_flash_turn_on(TORCH_MODE, 0);
	msleep(4000);
	scharger_flash_turn_off();
	msleep(1000);

	scharger_flash_turn_on(FLASH_MODE, 1);
	msleep(1000);
	scharger_flash_turn_off();

	return 0;
}
/*
 **************************************************************************
 * FunctionName: scharger_flash_set_default;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void scharger_flash_set_default(void)
{
	print_debug("enter %s", __func__);

	scharger_flash_intf.init		= scharger_flash_init;
	scharger_flash_intf.exit		= scharger_flash_exit;
	scharger_flash_intf.reset		= scharger_flash_reset;
	scharger_flash_intf.turn_on	= scharger_flash_turn_on;
	scharger_flash_intf.turn_off	= scharger_flash_turn_off;
	scharger_flash_intf.test		= test_flash;
	scharger_flash_intf.type		= LED_FLASH;
}

/*
 **************************************************************************
 * FunctionName: scharger_flash_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int __init scharger_flash_module_init(void)
{

	scharger_flash_set_default();
	register_camera_flash(&scharger_flash_intf);
	sema_init(&busy_lock, 1);
	sema_init(&switch_lock, 1);
	if(register_torch_led(&scharger_led))
	{
		print_error( "%s:Unable to create interface\n", __func__);
		return -ENOMEM;
    }

	if(mmi_register_torch_led(mmi_scharger_led_torch_mode_set_brightness, NULL))
	{
		print_warn( "%s:Unable to create mmi_register_torch_led", __func__);
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: scharger_flash_module_deinit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void __exit scharger_flash_module_deinit(void)
{
	print_debug("enter %s", __FUNCTION__);

	unregister_camera_flash(&scharger_flash_intf);
	return;
}


module_init(scharger_flash_module_init);
module_exit(scharger_flash_module_deinit);
MODULE_AUTHOR("hisi");
MODULE_DESCRIPTION("scharger_flash Flash Driver");
MODULE_LICENSE("GPL");

/********************************** END ***************************************/
