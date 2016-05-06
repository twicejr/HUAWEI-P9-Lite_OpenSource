/*
 * Driver for Texas Instruments INA231 power monitor chips
 *
 * Copyright (C) 2012 Lothar Felten <l-felten@ti.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * For further information, see the Documentation/hwmon/ina2xx file.
 */

/**
 * struct ina231_platform_data - ina231 info
 * @shunt_uohms		shunt resistance in microohms
 */
struct ina231_platform_data {
	long shunt_uohms;
};
