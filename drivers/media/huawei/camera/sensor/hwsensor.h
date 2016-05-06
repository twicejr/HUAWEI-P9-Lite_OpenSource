


#ifndef __HW_ALAN_KERNEL_SENSOR_INTERFACE_H__
#define __HW_ALAN_KERNEL_SENSOR_INTERFACE_H__

#include <linux/compiler.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <media/v4l2-subdev.h>
#include <media/huawei/sensor_cfg.h>
#include <linux/videodev2.h>
#include "hwcam_intf.h"
/**
 * @brief the power state of sensor.
 */
typedef enum _tag_hwsensor_state_kind
{
    HWSENSRO_POWER_DOWN,
    HWSENSOR_POWER_UP,
} hwsensor_state_kind_t;

typedef struct _tag_hwsensor_vtbl hwsensor_vtbl_t;
typedef struct _tag_hwsensor_intf hwsensor_intf_t;

/**
 * @brief the huawei sensor interface.
 */
typedef struct _tag_hwsensor_vtbl {
	/* sensor function table */
	char const *(*get_name)(hwsensor_intf_t*);
	int (*match_id)(hwsensor_intf_t *, void *);
	int (*config) (hwsensor_intf_t *, void *);
	int (*power_up) (hwsensor_intf_t *);
	int (*power_down) (hwsensor_intf_t *);
	int (*i2c_read) (hwsensor_intf_t *, void *);
	int (*i2c_write) (hwsensor_intf_t *, void *);
	int (*i2c_read_seq) (hwsensor_intf_t *, void *);
	int (*i2c_write_seq) (hwsensor_intf_t *, void *);
	int (*ioctl) (hwsensor_intf_t *, void *);
	int (*ext_power_ctrl)(int enable);
	int (*set_expo_gain)(hwsensor_intf_t *, u32 expo, u16 gain);
	int (*set_expo)(hwsensor_intf_t *, u32 expo);
	int (*set_gain)(hwsensor_intf_t *, u16 gain);
	int (*csi_enable)(hwsensor_intf_t *);
	int (*csi_disable)(hwsensor_intf_t *);
	int (*sensor_register_attribute)(hwsensor_intf_t *, struct device *);
    int (*ois_wpb_ctrl)(hwsensor_intf_t *, int state);
}hwsensor_vtbl_t;

typedef struct _tag_hwsensor_intf
{
    hwsensor_vtbl_t*                            vtbl;
} hwsensor_intf_t;

static inline int
hwsensor_intf_config(hwsensor_intf_t* hsi,
                     void __user* argp)
{
    return hsi->vtbl->config(hsi, argp);
}

static inline char const*
hwsensor_intf_get_name(hwsensor_intf_t* hsi)
{
    return hsi->vtbl->get_name(hsi);
}

static inline int
hwsensor_intf_power_up(hwsensor_intf_t* hsi)
{
    return hsi->vtbl->power_up(hsi);
}

static inline int
hwsensor_intf_power_down(hwsensor_intf_t* hsi)
{
    return hsi->vtbl->power_down(hsi);
}

static inline int
hwsensor_intf_match_id(hwsensor_intf_t* hsi,
                     void __user* argp)
{
    return hsi->vtbl->match_id(hsi, argp);
}

extern int hwsensor_register(struct platform_device *pdev,
                             hwsensor_intf_t* si);
extern void
hwsensor_unregister(hwsensor_intf_t* si);
/*
*  use this function to notify video device an event
*  pdev:  platform_device which creat by sensor module,like ov8865
*  ev:      v4l2 event to send to video device user
*/
extern int hwsensor_notify(struct device *pdev,struct v4l2_event* ev);

#endif // __HW_ALAN_KERNEL_SENSOR_INTERFACE_H__

