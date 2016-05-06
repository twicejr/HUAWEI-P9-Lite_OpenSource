/*
 * Record and handle CPU attributes.
 *
 * Copyright (C) 2014 ARM Ltd.
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <asm/arch_timer.h>
#include <asm/cachetype.h>
#include <asm/cpu.h>
#include <asm/cputype.h>
#include <asm/cpufeature.h>

#include <linux/bitops.h>
#include <linux/bug.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/preempt.h>
#include <linux/printk.h>
#include <linux/smp.h>

/*
 * In case the boot CPU is hotpluggable, we record its initial state and
 * current state separately. Certain system registers may contain different
 * values depending on configuration at or after reset.
 */
static bool mixed_endian_el0 = true;

bool cpu_supports_mixed_endian_el0(void)
{
	return id_aa64mmfr0_mixed_endian_el0(read_cpuid(ID_AA64MMFR0_EL1));
}

bool system_supports_mixed_endian_el0(void)
{
	return mixed_endian_el0;
}

static void update_mixed_endian_el0_support(struct cpuinfo_arm64 *info)
{
	mixed_endian_el0 &= id_aa64mmfr0_mixed_endian_el0(info->reg_id_aa64mmfr0);
}

static void update_cpu_features(struct cpuinfo_arm64 *info)
{
	update_mixed_endian_el0_support(info);
}
