/*
 * viatel_cbp_oem.c
 *
 * VIA CBP driver for Linux
 *
 * Copyright (C) 2011 VIA TELECOM Corporation, Inc.
 * Author: VIA TELECOM Corporation, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include "viatel.h"


int oem_gpio_request(int gpio, const char* label)
{
    return gpio_request(gpio, label);
}

void oem_gpio_free(int gpio)
{
    gpio_free(gpio);
}

/*config the gpio to be input for irq if the SOC need*/
int oem_gpio_direction_input_for_irq(int gpio)
{
    return gpio_direction_input(gpio);
}

int oem_gpio_direction_output(int gpio, int value)
{
    return gpio_direction_output(gpio, value);
}

/*
 * Get the output level if the gpio is output type;
 * Get the input level if the gpio is input type
 */
int oem_gpio_get_value(int gpio)
{
    return gpio_get_value(gpio);
}

int oem_gpio_get_value_cansleep(int gpio)
{
    return gpio_get_value_cansleep(gpio);
}

int oem_gpio_to_irq(int gpio)
{
    return gpio_to_irq(gpio);
}

/*
 * Set the irq type of the pin.
 * Get the pin level and set the correct edge if the type is both edge and
 * the SOC do not support both edge detection at one time
 */
int oem_gpio_set_irq_type(int gpio, unsigned int type)
{
    return 0;
}


int oem_gpio_request_irq(int gpio, irq_handler_t handler, unsigned long flags,
                         const char* name, void* dev)
{
    return request_irq(oem_gpio_to_irq(gpio), handler, flags, name, dev);
}

//hi6402 extended gpio api
int oem_gpio_request_threaded_irq(int gpio, irq_handler_t handler, unsigned long flags,
                                  const char* name, void* dev)
{
    return request_threaded_irq(oem_gpio_to_irq(gpio), NULL, handler, flags, name, dev);
}

void oem_gpio_irq_mask(int gpio)
{
    return ;
}

void oem_gpio_irq_unmask(int gpio)
{
    return ;
}

