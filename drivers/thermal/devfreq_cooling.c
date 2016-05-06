/*
 * devfreq_cooling: Thermal cooling device implementation for devices using
 *                  devfreq
 *
 * Copyright (C) 2014 ARM Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/devfreq.h>
#include <linux/devfreq_cooling.h>
#include <linux/export.h>
#include <linux/slab.h>
#include <linux/opp.h>
#include <linux/thermal.h>
#include <trace/events/thermal_power_allocator.h>

static int devfreq_cooling_get_max_state(struct thermal_cooling_device *cdev,
		unsigned long *state)
{
	struct devfreq_cooling_device *dfc = cdev->devdata;
	struct devfreq *df = dfc->devfreq;

	*state = df->profile->max_state - 1;

	return 0;
}

static int devfreq_cooling_get_cur_state(struct thermal_cooling_device *cdev,
		unsigned long *state)
{
	struct devfreq_cooling_device *dfc = cdev->devdata;

	*state = dfc->cooling_state;

	return 0;
}

extern unsigned int g_ipa_freq_limit[];
static int devfreq_cooling_set_cur_state(struct thermal_cooling_device *cdev,
		unsigned long state)
{
	struct devfreq_cooling_device *dfc = cdev->devdata;
	struct devfreq *df = dfc->devfreq;
	struct device *dev = df->dev.parent;
	unsigned long freq;

	if (state == dfc->cooling_state)
		return 0;

	dev_dbg(dev, "Setting cooling state %lu\n", state);

	if (state == THERMAL_NO_LIMIT) {
		freq = 0;
	} else {
		unsigned long index;
		unsigned long max_state = df->profile->max_state;

		if (state >= max_state)
			return -EINVAL;

		index = (max_state - 1) - state;
		freq = df->profile->freq_table[index];
	}

	g_ipa_freq_limit[IPA_GPU] = freq;
	trace_IPA_actor_gpu_cooling(freq/1000,state);
	if (df->max_freq != freq)
		devfreq_qos_set_max(df, freq);

	dfc->cooling_state = state;

	return 0;
}

static unsigned long
freq_get_state(struct devfreq *df, unsigned long freq)
{
       unsigned long state = THERMAL_CSTATE_INVALID;
       int i;

       for (i = 0; i < df->profile->max_state; i++) {
               if (df->profile->freq_table[i] == freq)
                       state = (df->profile->max_state - 1) - i;
       }

       return state;
}

static unsigned long
state_get_freq(struct devfreq *df, unsigned long state)
{
	if (state >= df->profile->max_state)
		return 0;

	return df->profile->freq_table[state];
}

static unsigned long
get_static_power(struct devfreq_cooling_device *dfc, unsigned long freq)
{
	struct devfreq *df = dfc->devfreq;
	struct device *dev = df->dev.parent;
	unsigned long voltage;
	struct opp *opp;

	rcu_read_lock();
	opp = opp_find_freq_exact(dev, freq, true);
	voltage = opp_get_voltage(opp) / 1000; /* mV */
	rcu_read_unlock();

	if (voltage == 0) {
		dev_warn_ratelimited(dev,
				     "Failed to get voltage for frequency %lu: %ld\n",
				     freq, IS_ERR(opp) ? PTR_ERR(opp) : 0);
		return 0;
	}

	return dfc->power_ops->get_static_power(voltage);
}

 int devfreq_cooling_get_requested_power(struct thermal_cooling_device *cdev,
					       struct thermal_zone_device *tz,
					       u32 *power)
{
	struct devfreq_cooling_device *dfc = cdev->devdata;
	struct devfreq_dev_status *status = &dfc->last_status;
	struct devfreq *df = dfc->devfreq;
	unsigned long state;
	unsigned long freq = status->current_frequency;
	u32 dyn_power, static_power;
	unsigned long load = 0;

	if(status->total_time)
		load = 100* status->busy_time /status->total_time;

	/* Get dynamic power for state */
	state = freq_get_state(df, freq);
#ifdef CONFIG_HISI_IPA_THERMAL
	if (THERMAL_CSTATE_INVALID == state) {
		pr_err("[%s]freq_get_state err freq[%lu]\n",__func__,freq);
		return -EINVAL;
	}
#endif
	dyn_power = dfc->power_table[state];

	/* Scale dynamic power for utilization */
	if (status->total_time)
		dyn_power = (dyn_power * status->busy_time) / status->total_time;

	/* Get static power */
	static_power = get_static_power(dfc, freq);

	*power = dyn_power + static_power;

	trace_IPA_actor_gpu_get_power((freq/1000),load,dyn_power,static_power,*power);

	return 0;
}

static int devfreq_cooling_state2power(struct thermal_cooling_device *cdev,
				       struct thermal_zone_device *tz,
				       unsigned long state,
				       u32 *power)
{
	struct devfreq_cooling_device *dfc = cdev->devdata;
	struct devfreq *df = dfc->devfreq;
	unsigned long freq;
	u32 static_power;

	freq = state_get_freq(df, state);
	static_power = get_static_power(dfc, freq);

	*power = dfc->power_table[state] + static_power;
	return 0;
}

static int devfreq_cooling_power2state(struct thermal_cooling_device *cdev,
			               struct thermal_zone_device *tz, u32 power,
				       unsigned long *state)
{
	struct devfreq_cooling_device *dfc = cdev->devdata;
	struct devfreq_dev_status *status = &dfc->last_status;
	struct devfreq *df = dfc->devfreq;
	unsigned long freq = status->current_frequency;
	s32 dyn_power;
	u32 static_power;
	int i;

	static_power = get_static_power(dfc, freq);

	dyn_power = power - static_power;
	dyn_power = dyn_power > 0 ? dyn_power : 0;

	/* Scale dynamic power for utilization */
	dyn_power = (dyn_power * status->busy_time) / status->total_time;

	/* Find the first cooling state that is within the power budget for
	 * dynamic power.
	*/
	for (i = 0; i < df->profile->max_state - 1; i++)
		if (dyn_power >= dfc->power_table[i])
			break;

	*state = i;

	trace_IPA_actor_gpu_limit(freq/1000,*state, power);
	return 0;
}

static struct thermal_cooling_device_ops const devfreq_cooling_ops = {
	.get_max_state = devfreq_cooling_get_max_state,
	.get_cur_state = devfreq_cooling_get_cur_state,
	.set_cur_state = devfreq_cooling_set_cur_state,
	.get_requested_power = devfreq_cooling_get_requested_power,
	.state2power = devfreq_cooling_state2power,
	.power2state = devfreq_cooling_power2state,
};

/**
 * devfreq_cooling_gen_power_table(): - Generate power table.
 * @dfc: Pointer to devfreq cooling device.
 *
 * Generate a table with the device's maximum power usage at each cooling
 * state (OPP). The static and dynamic powerm using the appropriate voltage and
 * frequency for the state, is aquired from the struct devfreq_cooling_ops, and
 * summed to make the maximum power draw.
 *
 * The table is malloced, and a pointer put in dfc->power_table. This must be
 * freed when unregistering the devfreq cooling device.
 *
 * Return: 0 on success, negative error code on failure.
 */
static int devfreq_cooling_gen_power_table(struct devfreq_cooling_device *dfc)
{
	struct devfreq *df = dfc->devfreq;
	struct device *dev = df->dev.parent;
	int num_opps;
	struct devfreq_cooling_ops *callbacks = dfc->power_ops;
	unsigned long freq;
	u32 *table;
	int i;

	rcu_read_lock();
	num_opps = opp_get_opp_count(dev);
	rcu_read_unlock();

	if (num_opps != dfc->devfreq->profile->max_state)
		return -ERANGE;

	table = kcalloc(num_opps, sizeof(table[0]), GFP_KERNEL);
	if (!table)
		return -ENOMEM;

	dev_dbg(dev,"POWER TABLE\n			 FREQ(MHz)  @ VOLT(mV) :  DYN(mW)+STATIC(mW) = POWER(mW)\n");
	rcu_read_lock();
	for (i = 0, freq = ULONG_MAX; i < num_opps; i++, freq--) {
		unsigned long power_dyn,power_static =0, voltage;
		struct opp *opp;

		opp = opp_find_freq_floor(dev, &freq);
		if (IS_ERR(opp))
			break;

		voltage = opp_get_voltage(opp) / 1000; /* mV */

		power_dyn = callbacks->get_dynamic_power(freq, voltage);
		power_static = callbacks->get_static_power(voltage);
		pr_debug("%lu MHz @ %lu mV: %lu + %lu = %lu mW\n",
				freq / 1000000, voltage,
				power_dyn, power_static, power_dyn + power_static);

		table[i] = power_dyn;
	}
	rcu_read_unlock();

	if (i != num_opps) {
		kfree(table);
		return -EFAULT;
	}

	dfc->power_table = table;

	return 0;
}

/**
 * of_devfreq_cooling_register_power(): - Register devfreq cooling device,
 *                                      with OF and power information.
 * @np: Pointer to OF device_node.
 * @df: Pointer to devfreq device.
 * @ops: Pointer to power ops.
 */
struct devfreq_cooling_device *
of_devfreq_cooling_register_power(struct device_node *np, struct devfreq *df,
		struct devfreq_cooling_ops *ops)
{
	struct thermal_cooling_device *cdev;
	struct devfreq_cooling_device *dfc;

	/* freq_table is required to look map state index to frequency. */
	if (!df->profile->max_state && !df->profile->freq_table)
		return ERR_PTR(-EINVAL);


	dfc = kzalloc(sizeof(struct devfreq_cooling_device), GFP_KERNEL);
	if (!dfc)
		return ERR_PTR(-ENOMEM);

	dfc->devfreq = df;

	if (ops) {
		if (!ops->get_static_power || !ops->get_dynamic_power) {
			kfree(dfc);
			return ERR_PTR(-EINVAL);
		}
		dfc->power_ops = ops;

		devfreq_cooling_gen_power_table(dfc);
	}

	cdev = thermal_of_cooling_device_register(np, "devfreq", dfc,
			&devfreq_cooling_ops);
	if (IS_ERR(cdev)) {
		dev_err(df->dev.parent,
			"Failed to register devfreq cooling device (%ld)\n",
			PTR_ERR(cdev));
		kfree(dfc->power_table);
		kfree(dfc);
		return ERR_CAST(cdev);
	}

	dfc->cdev = cdev;

	return dfc;
}
EXPORT_SYMBOL(of_devfreq_cooling_register_power);

/**
 * of_devfreq_cooling_register(): - Register devfreq cooling device,
 *                                with OF information.
 * @np: Pointer to OF device_node.
 * @df: Pointer to devfreq device.
 */
struct devfreq_cooling_device *
of_devfreq_cooling_register(struct device_node *np, struct devfreq *df)
{
	return of_devfreq_cooling_register_power(np, df, NULL);
}
EXPORT_SYMBOL(of_devfreq_cooling_register);

/**
 * devfreq_cooling_register(): - Register devfreq cooling device.
 * @df: Pointer to devfreq device.
 */
struct devfreq_cooling_device *devfreq_cooling_register(struct devfreq *df)
{
	return of_devfreq_cooling_register(NULL, df);
}
EXPORT_SYMBOL(devfreq_cooling_register);

/**
 * devfreq_cooling_unregister(): - Unregister devfreq cooling device.
 * @dfc: Pointer to devfreq cooling device to unregister.
 */
void devfreq_cooling_unregister(struct devfreq_cooling_device *dfc)
{
	if (!dfc)
		return;

	thermal_cooling_device_unregister(dfc->cdev);

	kfree(dfc->power_table);
	kfree(dfc);
}
EXPORT_SYMBOL(devfreq_cooling_unregister);
