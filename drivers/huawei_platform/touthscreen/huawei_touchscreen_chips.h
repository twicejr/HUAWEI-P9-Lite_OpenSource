/*
 * Huawei Touchscreen chips
 *
 * Copyright (C) 2013 Huawei Device Co.Ltd
 * License terms: GNU General Public License (GPL) version 2
 *
 */
 /* this file list all support ts chip information */
#ifndef __HUAWEI_TOUCHSCREEN_CHIP_H_
#define __HUAWEI_TOUCHSCREEN_CHIP_H_
#include <huawei_platform/touthscreen/huawei_touchscreen.h>
#ifdef CONFIG_SYNAPTICS_TS
extern struct ts_device_ops ts_synaptics_ops;
#endif
#ifdef CONFIG_ATMEL_TS
extern struct ts_device_ops ts_atmel_ops;
#endif
#ifdef CONFIG_CYPRESS_TS
extern struct ts_device_ops ts_cypress_ops;
#endif
#ifdef CONFIG_HIDEEP_TS
extern struct ts_device_ops ts_hideep_ops;
#endif
#endif
