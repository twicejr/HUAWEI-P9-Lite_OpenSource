/* Copyright (c) 2012, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __CORESIGHT_DTS_H
#define __CORESIGHT_DTS_H

#ifdef CONFIG_OF
extern struct coresight_platform_data_s *of_get_coresight_platform_cfg(struct device_node *node);
#else
static inline struct coresight_platform_data_s *of_get_coresight_platform_cfg(struct device_node *node)
{
	return NULL;
}
#endif

#endif
