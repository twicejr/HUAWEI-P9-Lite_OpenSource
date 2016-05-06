/*
 * maxim.h -- MAX98925 ALSA SoC Audio driver
 *
 * Copyright 2011-2012 Maxim Integrated Products
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#ifndef _MAXIM_H
#define _MAXIM_H

#include <linux/list.h>

typedef struct list_head maxim_list_t;



#define CHECK_IOCTL_OPS(ops, func) \
do{\
    if(NULL == ops || NULL == ops->func)\
        return -1;\
}while(0)



#define FAILED -1

/*IO controls for user*/
#define MAXIM_POWER_ON					_IO('M', 0x01)
#define MAXIM_POWER_OFF					_IO('M', 0x02)
#define MAXIM_POWER_SPK_ON				_IO('M', 0x03)
#define MAXIM_POWER_SPK_OFF				_IO('M', 0x04)
#define MAXIM_POWER_REC_ON				_IO('M', 0x05)
#define MAXIM_POWER_REC_OFF				_IO('M', 0x06)

#define MAXIM_GET_VERSION				_IOR('M', 0xFF, __u32)
#define MAXIM_R_GET_VERSION				_IOR('M', 0xFE, __u32)

/*Get M98925 related settings, nr from 0x10 to 0x3f*/
#define MAXIM_GET_VOLUME				_IOR('M', 0x10, __u32)
#define MAXIM_GET_DAIFORMAT				_IOR('M', 0x11, __u32)
#define MAXIM_GET_DAICLOCK				_IOR('M', 0x12, __u32)
#define MAXIM_GET_BOOSTVOLT				_IOR('M', 0x13, __u32)
#define MAXIM_GET_ALCTHRESHOLD			_IOR('M', 0x14, __u32)
#define MAXIM_GET_FILTERS				_IOR('M', 0x15, __u32)
#define MAXIM_GET_GAINRAMP				_IOR('M', 0x16, __u32)
#define MAXIM_GET_REG_VAL				_IOR('M', 0x17, struct maxim_reg_ops)

/*Get M98925_r related settings, nr from 0x10 to 0x3f*/
#define MAXIM_R_GET_VOLUME				_IOR('M', 0x20, __u32)
#define MAXIM_R_GET_DAIFORMAT			_IOR('M', 0x21, __u32)
#define MAXIM_R_GET_DAICLOCK			_IOR('M', 0x22, __u32)
#define MAXIM_R_GET_BOOSTVOLT			_IOR('M', 0x23, __u32)
#define MAXIM_R_GET_ALCTHRESHOLD		_IOR('M', 0x24, __u32)
#define MAXIM_R_GET_FILTERS				_IOR('M', 0x25, __u32)
#define MAXIM_R_GET_GAINRAMP			_IOR('M', 0x26, __u32)
#define MAXIM_R_GET_REG_VAL				_IOR('M', 0x27, struct maxim_reg_ops)


/*Change M98925 related settings, nr from 0x40 to 0x7f*/
#define MAXIM_SET_VOLUME				_IOW('M', 0x40, __u32)
#define MAXIM_SET_DAIFORMAT				_IOW('M', 0x41, __u32)
#define MAXIM_SET_DAICLOCK				_IOW('M', 0x42, __u32)
#define MAXIM_SET_BOOSTVOLT				_IOW('M', 0x43, __u32)
#define MAXIM_SET_ALCTHRESHOLD			_IOW('M', 0x44, __u32)
#define MAXIM_SET_FILTERS				_IOW('M', 0x45, __u32)
#define MAXIM_SET_GAINRAMP				_IOW('M', 0x46, __u32)
#define MAXIM_SET_REG_VAL				_IOW('M', 0x47, struct maxim_reg_ops)


struct maxim_priv {
    unsigned int gain;
    unsigned int gain_incall;
    unsigned int sysclk;
    unsigned int type; //0:left, 1:right
    struct regmap *regmap;
    struct mutex  lock;
    struct list_head list;
};


struct maxim_reg_ops{
    unsigned int reg_addr;
    unsigned int reg_val;
};


struct maxim_gain_def {
    unsigned int gain;
    unsigned int gain_incall;
};


struct maxim_ioctl_ops{
    int  (*maxim_set_slave)(struct list_head *maxim);
    void (*maxim_set_master)(struct list_head *maxim);
    int  (*maxim_set_clock)(struct list_head *maxim, unsigned int rate);
    int  (*maxim_open)(struct inode *inode, struct file *filp);
    int  (*maxim_release)(struct inode *inode, struct file *filp);
    int  (*maxim_get_version)(struct list_head *maxim, unsigned int type, unsigned int *value);
    int  (*maxim_get_reg_val)(struct list_head *maxim, unsigned int type, struct maxim_reg_ops *reg_val, unsigned int __user *pUser);
    int  (*maxim_set_reg_val)(struct list_head *maxim, struct maxim_reg_ops *reg_val, unsigned int __user *pUser);
    int  (*maxim_digital_mute)(struct list_head *maxim, int mute);
    int  (*maxim_single_digital_mute)(struct list_head *maxim, unsigned int type, int mute);
    int  (*maxim_get_volume)(struct list_head *maxim, unsigned int type, unsigned int *value);
    int  (*maxim_set_volume)(struct list_head *maxim, unsigned int value);
    int  (*maxim_get_daiclock)(struct list_head *maxim, unsigned int type, unsigned int *value);
    int  (*maxim_set_daiclock)(struct list_head *maxim, unsigned int value);
    int  (*maxim_get_boostvolt)(struct list_head *maxim, unsigned int type, unsigned int *value);
    int  (*maxim_set_boostvolt)(struct list_head *maxim, unsigned int value);
    int  (*maxim_get_alcthreshold)(struct list_head *maxim, unsigned int type, unsigned int *value);
    int  (*maxim_set_alcthreshold)(struct list_head *maxim, unsigned int value);
    int  (*maxim_get_filters)(struct list_head *maxim, unsigned int type, unsigned int *value);
    int  (*maxim_set_filters)(struct list_head *maxim, unsigned int value);
    int  (*maxim_get_gainramp)(struct list_head *maxim, unsigned int type, unsigned int *value);
    int  (*maxim_set_gainramp)(struct list_head *maxim, unsigned int value);
};


enum maxim_type{
    MAXIM_L = 0,
    MAXIM_R,
};

enum mute_val{
    MUTE_ON = 0,
    MUTE_OFF,
};

extern int maxim_ioctl_regist(struct maxim_ioctl_ops *ops);
extern int maxim_ioctl_isregist(void);
extern void maxim_list_add(struct maxim_priv *maxim);
extern struct maxim_priv *find_maxim_by_dev(struct device *dev);
extern int get_maxim_num(void);
extern struct list_head *get_maxim_list_head(void);
extern struct maxim_priv *find_maxim_by_type(struct list_head *maxim, unsigned int type);


#endif
