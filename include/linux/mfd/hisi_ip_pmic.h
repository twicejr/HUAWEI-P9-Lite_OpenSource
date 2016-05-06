/*
 * Header file for device driver hisi ip power manger
 *
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (C) 2011 Hisilicon.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef	__HISI_IP_PMIC_H
#define	__HISI_IP_PMIC_H

struct hisi_regulator_ip_core {
	struct resource	*res;
	struct device *dev;
	void __iomem *regs;
	spinlock_t lock;
};

/* Register Access Helpers */
static inline u32 hisi_regulator_ip_core_read(struct hisi_regulator_ip_core *pmic, int reg)
{
	return readl(pmic->regs + reg);
}

static inline void hisi_regulator_ip_core_write(struct hisi_regulator_ip_core *pmic, int reg, u32 val)
{
	writel(val, pmic->regs + reg);
}

#endif		/* __HISI_IP_PMIC_H */
