/*
 * LCD Tuning Lowlevel Control Abstraction
 *
 */

#ifndef _LINUX_LCD_TUNING_H
#define _LINUX_LCD_TUNING_H

#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/platform_device.h>

struct lcd_tuning_dev;

enum lcd_type
{
	OLED,
	TFT,
};

enum lcd_gamma
{
	GAMMA25,
	GAMMA22,
	GAMMA19,
};

enum tft_cabc
{
	CABC_OFF = 0,
	CABC_UI = 1,
	CABC_VID = 3,
};

struct lcd_properities {
	enum lcd_type type;
	enum lcd_gamma default_gamma;
};
	
struct lcd_tuning_ops {
	int (*set_gamma)(struct lcd_tuning_dev *ltd, enum lcd_gamma gamma);
	int (*set_cabc)(struct platform_device *dev, int cabc);
};

struct lcd_tuning_dev {
	struct lcd_properities props;
	const struct lcd_tuning_ops *ops;
	void *data;
};

struct lcd_mdevice {
	struct lcd_tuning_dev ltd;
	/* This protects the 'ops' field. If 'ops' is NULL, the driver that
	   registered this device has been unloaded, and if class_get_devdata()
	   points to something in the body of that driver, it is also invalid. */
	struct mutex ops_lock;
	struct miscdevice mdev;
};

//FIXME
#if 0 
static inline void * lcd_tuning_get_data(struct lcd_tuning_device *ltd)
{
	return dev_get_drvdata(&ltd->dev);
}
#endif

struct lcd_tuning_dev *lcd_tuning_dev_register(struct lcd_properities *props, const struct lcd_tuning_ops *lcd_ops, void *devdata);
void lcd_tuning_dev_unregister(struct lcd_tuning_dev *ltd);

#endif
