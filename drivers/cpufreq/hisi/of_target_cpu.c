/*
 * Hisilicon Platforms CPU MaxFreq support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/cpu.h>
#include <linux/cpufreq.h>
#include <linux/cpumask.h>
#include <linux/export.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/of_platform.h>
#include <linux/opp.h>
#include <linux/slab.h>
#include <linux/topology.h>
#include <linux/types.h>

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif

struct efuse_freq {
	unsigned int id;
	int val;
};

struct cpu_freq {
	unsigned long id;
	unsigned long freq;
};

#define LITTLE_CLUSTER	0
#define BIG_CLUSTER	1
#define MAX_CLUSTERS	2
#define MAX_FREQ_LIMIT 2304000000
#define EFUSE_TABLE_LEN 4
#define DEFAULT_EFUSE_FREQ_LEVEL 6
#define EFUSE_ADJUST_LEN 1

enum SOC_EFUSE_FREQ_ENUM {
	SOC_EFUSE_FREQ_0 = 0x00,/*480000*/
	SOC_EFUSE_FREQ_1 = 0x01,/*807000*/
	SOC_EFUSE_FREQ_2 = 0x02,/*1210000*/
	SOC_EFUSE_FREQ_3 = 0x03,/*1517000*/
	SOC_EFUSE_FREQ_4 = 0x04,/*1805000*/
	SOC_EFUSE_FREQ_5 = 0x05,/*2016000*/
	SOC_EFUSE_FREQ_6 = 0x06,/*2304000*/
	SOC_EFUSE_FREQ_7 = 0x07,/*2516000*/
	SOC_EFUSE_FREQ_MAX,/*max*/
};

/*the table will sync with dts*/
static struct cpu_freq *freqs_table[MAX_CLUSTERS];
static unsigned int g_max_prof[MAX_CLUSTERS];

struct efuse_freq soc_efuse_freq_table[EFUSE_TABLE_LEN] = {
	{0x00, SOC_EFUSE_FREQ_6},
	{0x01, SOC_EFUSE_FREQ_6},
	{0x10, SOC_EFUSE_FREQ_7},
	{0x11, SOC_EFUSE_FREQ_6},
};

static bool g_support_efuse;
extern int get_efuse_freq_value(unsigned char *pu8Buffer, unsigned int u32Length);

int dt_target_cpu(unsigned long *freq)
{
	struct device_node *np;
	char *target_cpu, *support_efuse;
	unsigned int target_max_freq = 0;
	int ret;
	unsigned int index;

	np = of_find_compatible_node(NULL, NULL, "hisi,targetcpu");
	if (!np)
		return -ENODEV;

	ret = of_property_read_string(np, "target_cpu", (const char **)(&target_cpu));
	if (ret)
		return -ENOENT;

	pr_debug("%s: target_cpu:%s.\n", __func__, target_cpu);

	np = of_find_compatible_node(NULL, NULL, "hisi,supportedtarget");
	if (!np)
		return -ENODEV;

	index = of_property_match_string(np, "support_name", target_cpu);
	pr_debug("%s: index :%u.\n", __func__, index);

	ret = of_property_read_u32_index(np, "support_value", index, &target_max_freq);
	if (ret)
		return -ENOENT;

	*freq = target_max_freq * 1000;

	g_support_efuse = false;
	ret = of_property_read_string(np, "support_efuse", (const char **)(&support_efuse));
	if (!ret) {
		if (strcmp(support_efuse, "true") == 0)
			g_support_efuse = true;
	}

	pr_info("target %lx.\n", *freq);

	return 0;
}

int of_init_efuse_freq_table(struct cpu_freq **table)
{
	struct cpu_freq *freq_table;
	struct device_node *np;
	const struct property *prop;
	const __be32 *val;
	int nr;
	int i = 0;

	np = of_find_node_by_path("/cpus/cpu@100");
	if (!np) {
		pr_err("cpu@100 not found.\n");
		return -ENODEV;
	}
	prop = of_find_property(np, "operating-points", NULL);
	if (!prop) {
		pr_err("operating-points node not found.\n");
		return -ENOENT;
	}
	if (!prop->value) {
		pr_err("operating-points value not found.\n");
		return -ENOENT;
	}

	/*
	 * Each OPP is a set of tuples consisting of frequency and
	 * voltage like <freq-kHz vol-uV>.
	 */
	nr = prop->length / sizeof(u32);
	if (nr % 2) {
		pr_err("%s: Invalid OPP list\n", __func__);
		return -EINVAL;
	}

	freq_table = kzalloc(sizeof(*freq_table) * nr, GFP_KERNEL);
	if (!freq_table)
		return -ENOMEM;

	val = prop->value;
	i = 0;
	while (nr) {
		unsigned long freq = be32_to_cpup(val++) * 1000;
		val++;

		freq_table[i].id = i;
		freq_table[i].freq = freq;

		pr_debug("id:0x%lu, freq:%llu.\n", freq_table[i].id, freq_table[i].freq);

		i++;
		nr -= 2;
	}
	*table = &freq_table[0];

	return 0;
}

void of_free_efuse_freq_table(struct cpu_freq **table)
{
	if (!table)
		return;

	kfree(*table);
	*table = NULL;
}

int check_cpu_profile(unsigned int *efuse_prof, unsigned int prof_len)
{
	unsigned int max_prof = 0;/* 1718-1721 */
	unsigned int max_prof_adjust = 0x0;/* 1714-1717 */
	unsigned int adjust_symbol = 0;
	unsigned int efuse_val = 0;

	pr_debug("%s:read freq_efuse start.\n", __func__);

	if (0 != get_efuse_freq_value((unsigned char *)(&efuse_val), 4)) {
		pr_err("%s:read efuse fail,val:0x%x.\n", __func__, efuse_val);
		return -EINVAL;
	}
	pr_debug("%s:read efuse ok,val:0x%x.\n", __func__, efuse_val);

	/*efuse 0,default 2.3G*/
	if (efuse_val != 0) {
		max_prof = (efuse_val >> 4) & 0xf;
		max_prof_adjust = efuse_val & 0x7;
		adjust_symbol = (efuse_val >> 3) & 0x1;
	} else {
		max_prof = 0;
		max_prof_adjust = 0;
	}

	pr_info("max:0x%x,adjust:0x%x,symbol:%d.\n", max_prof, max_prof_adjust, adjust_symbol);

	if (max_prof >= EFUSE_TABLE_LEN) {
		*efuse_prof = soc_efuse_freq_table[0].val;
		pr_err("%s:ATE efuse:0x%x err.\n", __func__, max_prof);
	} else {
		*efuse_prof = soc_efuse_freq_table[max_prof].val;
	}

	pr_info("real max:0x%x.\n", *efuse_prof);

	/*adjust limit to 1 level*/
	if (max_prof_adjust > EFUSE_ADJUST_LEN) {
		pr_err("%s:ATE efuse adjust:0x%x err.\n", __func__, max_prof_adjust);
		return -EINVAL;
	} else {
		if (adjust_symbol == 0)
			*efuse_prof += max_prof_adjust;
		else
			*efuse_prof -= max_prof_adjust;
	}

	if (*efuse_prof >= SOC_EFUSE_FREQ_MAX) {
		*efuse_prof = DEFAULT_EFUSE_FREQ_LEVEL;
		pr_err("%s: efuse adjust overflow,set to default.\n", __func__);
	}

	pr_info("adjust:0x%x.\n", *efuse_prof);

	if (*efuse_prof > prof_len - 1) {
		pr_err("%s:CHIP WARNING,efuse_adjust real:0x%x > max:0x%x.\n", __func__, *efuse_prof, prof_len - 1);
		*efuse_prof = prof_len - 1;
	}

	return 0;
}

void of_target_cpu(int cluster, struct device *cpu_dev)
{
	unsigned int max_efuse_profile = 0;
	unsigned long max_efuse_freq;
	unsigned long freq = ULONG_MAX;
	unsigned long target_freq = ULONG_MAX;
	struct opp *temp_opp;
	bool set_flag = true;

	if (cluster != BIG_CLUSTER)
		return;

	/*sync freq_table with dts*/
	if (of_init_efuse_freq_table(&freqs_table[cluster])) {
		pr_err("init table error.\n");
		set_flag = false;
		goto dev_check_chip_freq;
	}

	/*parse target_cpu to find max_freq of dts*/
	if (dt_target_cpu(&target_freq)) {
		pr_err("dt get target error.\n");
		set_flag = false;
		goto free_table;
	}

	/*get the target freq and disable unused prof*/
	rcu_read_lock();
	opp_find_freq_floor(cpu_dev, &freq);
	rcu_read_unlock();
	pr_debug("dts floor_freq %llu.\n", (long long unsigned int)freq);

	while (freq > target_freq) {
		opp_disable(cpu_dev, freq);

		rcu_read_lock();
		temp_opp = opp_find_freq_floor(cpu_dev, &freq);
		rcu_read_unlock();

		/* check if no opp left, break the infinite loop */
		if (IS_ERR(temp_opp))
			break;
	}
	pr_info("dt floor %lx.\n", freq);

	if (!g_support_efuse)
		goto free_table;

	/*get freq efuse level/adjust level*/
	if (check_cpu_profile(&max_efuse_profile, SOC_EFUSE_FREQ_MAX)) {
		set_flag = false;
		goto free_table;
	}

	max_efuse_freq = freqs_table[cluster][max_efuse_profile].freq;
	pr_info("ef max %lx.\n", max_efuse_freq);

	/*prevent adjust level too low*/
	if (max_efuse_freq < MAX_FREQ_LIMIT) {
		pr_err("%s:adjust error,set to default.\n", __func__);
		max_efuse_freq = MAX_FREQ_LIMIT;
	}
	pr_info("ef real %lx.\n", max_efuse_freq);

	/*if check failed,just delete the max profile*/
	if (freq > max_efuse_freq) {
		set_flag = false;
		/*SLT/UDP plat,set 2.5G as max_freq in dts*/
		opp_disable(cpu_dev, freq);
		pr_err("FAIL.\n");
	} else if (freq == max_efuse_freq) {
		pr_err("SUCCESS.OK.\n");
	} else {
		pr_err("SUCCESS.WARNING.\n");
	}

free_table:
	of_free_efuse_freq_table(&freqs_table[cluster]);

dev_check_chip_freq:
	/*detect current device successful, set the flag */
	if (set_flag == true) {
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
		set_hw_dev_flag(DEV_I2C_CPU_CHIP);
#endif
	}
}
EXPORT_SYMBOL_GPL(of_target_cpu);
