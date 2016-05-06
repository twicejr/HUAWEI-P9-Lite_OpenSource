/*
 * invert_hs.h -- invert headset driver
 *
 * Copyright (c) 2015 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef INVERT_HS_H
#define INVERT_HS_H

/* invert headset mic gnd connect status*/
enum mic_gnd_connect_status
{
    INVERT_HS_MIC_GND_DISCONNECT        = 0,
    INVERT_HS_MIC_GND_CONNECT           = 1,
};

#ifdef CONFIG_INVERT_HS
int invert_hs_control(int connect);
#else
static inline int invert_hs_control(int connect)
{
    return 0;
}
#endif

#endif //INVERT_HS_H