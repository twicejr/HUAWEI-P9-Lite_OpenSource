/*
 * LCD Tuning ioctl macros
 *
 */
#ifndef _LINUX_LCD_IOCTL_H
#define _LINUX_LCD_IOCTL_H

#include <linux/ioctl.h>
#include <linux/types.h>

#define LCD_IOR(num, dtype)	_IOR('L', num, dtype)

#define LCD_TUNING_DGAMMA	LCD_IOR(30, unsigned int)
#define LCD_TUNING_CABC LCD_IOR(31, unsigned int)
#define LCD_TUNING_DCPR	LCD_IOR(34, unsigned int)
#endif
