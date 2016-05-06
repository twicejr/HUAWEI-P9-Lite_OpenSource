/*
 *
 * (C) COPYRIGHT ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained
 * from Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 */





#include <linux/ioport.h>
#include <mali_kbase.h>
#include <mali_kbase_defs.h>
#include <mali_kbase_config.h>
#ifdef CONFIG_DEVFREQ_THERMAL
#include <linux/devfreq_cooling.h>
#endif

#include <linux/opp.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#ifdef CONFIG_REPORT_VSYNC
#include <linux/export.h>
#endif
#include <linux/delay.h>
#include "mali_kbase_config_platform.h"

#define MALI_TRUE ((uint32_t)1)
#define MALI_FALSE ((uint32_t)0)
typedef uint32_t     mali_bool;

typedef enum {
        MALI_ERROR_NONE = 0,
        MALI_ERROR_OUT_OF_GPU_MEMORY,
        MALI_ERROR_OUT_OF_MEMORY,
        MALI_ERROR_FUNCTION_FAILED,
}mali_error;

#define KBASE_PWR_KEY_VALUE			0x2968a819
#define KBASE_PWR_OVERRIDE_VALUE		0xc4b00960
#define HARD_RESET_AT_POWER_OFF 0

#ifndef CONFIG_OF
static struct kbase_io_resources io_resources = {
	.job_irq_number = 68,
	.mmu_irq_number = 69,
	.gpu_irq_number = 70,
	.io_memory_region = {
	.start = 0xFC010000,
	.end = 0xFC010000 + (4096 * 4) - 1
	}
};
#endif /* CONFIG_OF */

#define KBASE_HI6250_PLATFORM_GPU_REGULATOR_NAME      "gpu"
#define RUNTIME_PM_DELAY_TIME	100
#define DEFAULT_POLLING_MS	20
#define STOP_POLLING		0

#ifdef CONFIG_REPORT_VSYNC
static struct kbase_device *kbase_dev = NULL;
#endif

static inline void kbase_platform_on(struct kbase_device *kbdev)
{
	if (kbdev->regulator) {
		if (unlikely(regulator_enable(kbdev->regulator)))
		{
			printk("MALI-MIDGARD:  Failed to enable regulator\n");
		}
#ifdef CONFIG_ARCH_HI6250
		else
		{
			kbase_os_reg_write(kbdev,GPU_CONTROL_REG(PWR_KEY),KBASE_PWR_KEY_VALUE);
			kbase_os_reg_write(kbdev,GPU_CONTROL_REG(PWR_OVERRIDE1),KBASE_PWR_OVERRIDE_VALUE);
		}
#endif
	}
}

static inline void kbase_platform_off(struct kbase_device *kbdev)
{
	if (kbdev->regulator)
		regulator_disable(kbdev->regulator);

}

#ifdef CONFIG_PM_DEVFREQ
static int mali_kbase_devfreq_target(struct device *dev, unsigned long *_freq,
			      u32 flags)
{
	struct kbase_device *kbdev = (struct kbase_device *)dev->platform_data;
	unsigned long old_freq = kbdev->devfreq->previous_freq;
	struct opp *opp = NULL;
	unsigned long freq;

	rcu_read_lock();
	opp = devfreq_recommended_opp(dev, _freq, flags);
	if (IS_ERR(opp)) {
		printk("[mali-midgard]  Failed to get Operating Performance Point\n");
		rcu_read_unlock();
		return PTR_ERR(opp);
	}
	freq = opp_get_freq(opp);
	rcu_read_unlock();

	if (old_freq == freq)
		return 0;
#ifdef CONFIG_HISI_IPA_THERMAL
	freq = ipa_freq_limit(IPA_GPU,freq);
#endif
	if (clk_set_rate((kbdev->clk), freq)) {
		printk("[mali-midgard]  Failed to set gpu freqency, [%lu->%lu]\n", old_freq, freq);
		return -ENODEV;
	}


	return 0;
}

static int mali_kbase_get_dev_status(struct device *dev,
				      struct devfreq_dev_status *stat)
{
	struct kbase_device *kbdev = (struct kbase_device *)dev->platform_data;

	if (kbdev->pm.backend.metrics.kbdev != kbdev) {
		pr_err("[mali-midgard] pm backend metrics not initialized\n", __func__);
		return 0;
	}

	(void)kbase_pm_get_dvfs_action(kbdev);
	stat->busy_time = kbdev->pm.backend.metrics.utilisation;
	stat->total_time = 100;
	stat->private_data = (void *)(long)kbdev->pm.backend.metrics.vsync_hit;
	stat->current_frequency = kbdev->devfreq->previous_freq;

#ifdef CONFIG_DEVFREQ_THERMAL
	memcpy(&kbdev->devfreq_cooling->last_status, stat, sizeof(*stat));
#endif

	return 0;
}

static struct devfreq_dev_profile mali_kbase_devfreq_profile = {
	/* it would be abnormal to enable devfreq monitor during initialization. */
	.polling_ms	= DEFAULT_POLLING_MS, //STOP_POLLING,
	.target		= mali_kbase_devfreq_target,
	.get_dev_status	= mali_kbase_get_dev_status,
};
#endif

#ifdef CONFIG_REPORT_VSYNC
void mali_kbase_pm_report_vsync(int buffer_updated)
{
	if (kbase_dev)
		kbase_pm_report_vsync(kbase_dev, buffer_updated);
}
EXPORT_SYMBOL(mali_kbase_pm_report_vsync);
#endif

#ifdef CONFIG_MALI_MIDGARD_DVFS
int kbase_platform_dvfs_event(struct kbase_device *kbdev, u32 utilisation, u32 util_gl_share, u32 util_cl_share[2])
{
	return 1;
}

int kbase_platform_dvfs_enable(struct kbase_device *kbdev, bool enable, int freq)
{
	unsigned long flags;

	KBASE_DEBUG_ASSERT(kbdev != NULL);

	if (enable != kbdev->pm.backend.metrics.timer_active) {
		if (enable) {
			spin_lock_irqsave(&kbdev->pm.backend.metrics.lock, flags);
			kbdev->pm.backend.metrics.timer_active = MALI_TRUE;
			spin_unlock_irqrestore(&kbdev->pm.backend.metrics.lock, flags);
			hrtimer_start(&kbdev->pm.backend.metrics.timer,
					HR_TIMER_DELAY_MSEC(kbdev->pm.dvfs_period),
					HRTIMER_MODE_REL);
		} else {
			spin_lock_irqsave(&kbdev->pm.backend.metrics.lock, flags);
			kbdev->pm.backend.metrics.timer_active = MALI_FALSE;
			spin_unlock_irqrestore(&kbdev->pm.backend.metrics.lock, flags);
			hrtimer_cancel(&kbdev->pm.backend.metrics.timer);
		}
	}

	return 1;
}
#endif

#ifdef CONFIG_DEVFREQ_THERMAL
#define FALLBACK_STATIC_TEMPERATURE 85000
static unsigned long hisi_model_static_power(unsigned long voltage)
{
		struct thermal_zone_device *tz = NULL;
		unsigned long temperature;
        const unsigned long voltage_cubed = (voltage * voltage * voltage) >> 10;
		unsigned long temp,temp_squared,temp_cubed;
        unsigned long temp_scaling_factor =0;

        struct device_node * dev_node = NULL;
        u32 prop;
        int ret = -EINVAL,i;
        const char*  temperature_scale_capacitance[5];
        int capacitance[5]={0};
        dev_node = of_find_compatible_node(NULL,NULL,"arm,ipa-thermal");
        if(dev_node)
        {
            for(i = 0;i<5;i++)
            {
              ret =  of_property_read_string_index(dev_node,"hisilicon,gpu_temp_scale_capacitance",i,&temperature_scale_capacitance[i]);
              if(ret)
			{
				pr_err("%s temperature_scale_capacitance [%d] read err\n",__func__,i);
				continue;
			}

                (void)kstrtoint(temperature_scale_capacitance[i],10, &capacitance[i]);

            }
        }


		tz = thermal_zone_get_zone_by_name("soc_thermal");
		if (IS_ERR(tz)) {
			pr_warn_ratelimited("Error getting gpu thermal zone (%ld), not yet ready?\n",
					PTR_ERR(tz));
			temperature = FALLBACK_STATIC_TEMPERATURE;
		} else {
                    if(tz->ops->get_temp)
                    {
                        int ret;
                        ret = tz->ops->get_temp(tz, &temperature);
				if (ret) {
					pr_warn_ratelimited("Error reading temperature for gpu thermal zone: %d\n",
							ret);
					temperature = FALLBACK_STATIC_TEMPERATURE;
				}
                    }
                    else
                    {
                        temperature = FALLBACK_STATIC_TEMPERATURE;
                    }
		}

		temp = temperature / 1000;
		temp_squared = temp * temp;
		temp_cubed = temp_squared * temp;
        temp_scaling_factor = capacitance[3]*temp_cubed +
                              capacitance[2]*temp_squared +
                              capacitance[1]*temp +
                              capacitance[0];

        return (((capacitance[4] * voltage_cubed) >> 20) * temp_scaling_factor) / 1000000;
}

static unsigned long hisi_model_dynamic_power(unsigned long freq,
		unsigned long voltage)
{
	/* The inputs: freq (f) is in Hz, and voltage (v) in mV.
	 * The coefficient (c) is in mW/(MHz mV mV).
	 *
	 * This function calculates the dynamic power after this formula:
	 * Pdyn (mW) = c (mW/(MHz*mV*mV)) * v (mV) * v (mV) * f (MHz)
	 */
	const unsigned long v2 = (voltage * voltage) / 1000; /* m*(V*V) */
	const unsigned long f_mhz = freq / 1000000; /* MHz */
	unsigned long coefficient = 3600; /* mW/(MHz*mV*mV) */
    struct device_node * dev_node = NULL;
    u32 prop;
    dev_node = of_find_compatible_node(NULL,NULL,"arm,ipa-thermal");
    if(dev_node)
    {
        int ret = of_property_read_u32(dev_node,"hisilicon,gpu_dyn_capacitance",&prop);
        if(ret == 0)
        {
            coefficient = prop;
        }
    }

	return (coefficient * v2 * f_mhz) / 1000000; /* mW */
}

static struct devfreq_cooling_ops hisi_model_ops = {
        .get_static_power = hisi_model_static_power,
        .get_dynamic_power = hisi_model_dynamic_power,
};

#endif

static mali_bool kbase_platform_init(struct kbase_device *kbdev)
{
      int err;
	struct device *dev = kbdev->dev;
	dev->platform_data = kbdev;

#ifdef CONFIG_REPORT_VSYNC
	kbase_dev = kbdev;
#endif


	kbdev->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(kbdev->clk)) {
		printk("[mali-midgard]  Failed to get clk\n");
		return MALI_FALSE;
	}


	kbdev->regulator = devm_regulator_get(dev, KBASE_HI6250_PLATFORM_GPU_REGULATOR_NAME);
	if (IS_ERR(kbdev->regulator)) {
		printk("[mali-midgard]  Failed to get regulator\n");
		return MALI_FALSE;
	}

#ifdef CONFIG_PM_DEVFREQ
	if (opp_init_devfreq_table(dev,
			&mali_kbase_devfreq_profile.freq_table)) {
		printk("[mali-midgard]  Failed to init devfreq_table\n");
		kbdev->devfreq = NULL;
	} else {
		mali_kbase_devfreq_profile.initial_freq	= clk_get_rate(kbdev->clk);
		rcu_read_lock();
		mali_kbase_devfreq_profile.max_state = opp_get_opp_count(dev);
		rcu_read_unlock();
		dev_set_name(dev, "gpufreq");
		kbdev->devfreq = devfreq_add_device(dev,
						&mali_kbase_devfreq_profile,
						"mali_ondemand",
						NULL);
	}

	if (NULL == kbdev->devfreq) {
		printk("[mali-midgard]  NULL pointer [kbdev->devFreq]\n");
		goto JUMP_DEVFREQ_THERMAL;
	}

#ifdef CONFIG_DEVFREQ_THERMAL
	{
		struct devfreq_cooling_ops *callbacks;

		callbacks = (struct devfreq_cooling_ops *)POWER_MODEL_CALLBACKS;

		kbdev->devfreq_cooling = of_devfreq_cooling_register_power(
				kbdev->dev->of_node,
				kbdev->devfreq,
				callbacks);
		if (IS_ERR_OR_NULL(kbdev->devfreq_cooling)) {
			err = PTR_ERR(kbdev->devfreq_cooling);
			dev_err(kbdev->dev,
				"Failed to register cooling device (%d)\n",
				err);
			goto JUMP_DEVFREQ_THERMAL;
		}
	}
#endif

	/* make devfreq function */
	//mali_kbase_devfreq_profile.polling_ms = DEFAULT_POLLING_MS;
#endif/*CONFIG_PM_DEVFREQ*/
JUMP_DEVFREQ_THERMAL:
	return MALI_TRUE;
}

static void kbase_platform_term(struct kbase_device *kbdev)
{
#ifdef CONFIG_PM_DEVFREQ
	devfreq_remove_device(kbdev->devfreq);
#endif
}

kbase_platform_funcs_conf platform_funcs = {
	.platform_init_func = &kbase_platform_init,
	.platform_term_func = &kbase_platform_term,
};

static int pm_callback_power_on(struct kbase_device *kbdev)
{
#ifdef CONFIG_MALI_MIDGARD_RT_PM
	int result;
	int ret_val;
	struct device *dev = kbdev->dev;

#if (HARD_RESET_AT_POWER_OFF != 1)
	if (!pm_runtime_status_suspended(dev))
		ret_val = 0;
	else
#endif
		ret_val = 1;

	if (unlikely(dev->power.disable_depth > 0)) {
		kbase_platform_on(kbdev);
	} else {
		result = pm_runtime_resume(dev);
		if (result < 0 && result == -EAGAIN)
			kbase_platform_on(kbdev);
		else if (result < 0)
			printk("[mali-midgard]  pm_runtime_resume failed (%d)\n", result);
	}

	return ret_val;
#else
	kbase_platform_on(kbdev);

	return 1;
#endif
}

static void pm_callback_power_off(struct kbase_device *kbdev)
{
#ifdef CONFIG_MALI_MIDGARD_RT_PM
	struct device *dev = kbdev->dev;
	int ret = 0, retry = 0;

#if HARD_RESET_AT_POWER_OFF
	/* Cause a GPU hard reset to test whether we have actually idled the GPU
	 * and that we properly reconfigure the GPU on power up.
	 * Usually this would be dangerous, but if the GPU is working correctly it should
	 * be completely safe as the GPU should not be active at this point.
	 * However this is disabled normally because it will most likely interfere with
	 * bus logging etc.
	 */
	KBASE_TRACE_ADD(kbdev, CORE_GPU_HARD_RESET, NULL, NULL, 0u, 0);
	kbase_os_reg_write(kbdev, GPU_CONTROL_REG(GPU_COMMAND), GPU_COMMAND_HARD_RESET);
#endif

	if (unlikely(dev->power.disable_depth > 0)) {
		kbase_platform_off(kbdev);
	} else {
		do {
			ret = pm_schedule_suspend(dev, RUNTIME_PM_DELAY_TIME);
			if (ret != -EAGAIN) {
				if (unlikely(ret < 0)) {
					pr_err("[mali-midgard]  pm_schedule_suspend failed (%d)\n\n", ret);
					WARN_ON(1);
				}

				/* correct status */
				break;
			}

			/* -EAGAIN, repeated attempts for 1s totally */
			msleep(50);
		} while (++retry < 20);
	}
#else
	kbase_platform_off(kbdev);
#endif
}

static mali_error pm_callback_runtime_init(struct kbase_device *kbdev)
{
	pm_suspend_ignore_children(kbdev->dev, true);
	pm_runtime_enable(kbdev->dev);
	return MALI_ERROR_NONE;
}

static void pm_callback_runtime_term(struct kbase_device *kbdev)
{
	pm_runtime_disable(kbdev->dev);
}

static void pm_callback_runtime_off(struct kbase_device *kbdev)
{
#ifdef CONFIG_PM_DEVFREQ
	devfreq_suspend_device(kbdev->devfreq);
#elif defined(CONFIG_MALI_MIDGARD_DVFS)
	kbase_platform_dvfs_enable(kbdev, false, 0);
#endif

	kbase_platform_off(kbdev);
}

static int pm_callback_runtime_on(struct kbase_device *kbdev)
{
	kbase_platform_on(kbdev);

#ifdef CONFIG_PM_DEVFREQ
	devfreq_resume_device(kbdev->devfreq);
#elif defined(CONFIG_MALI_MIDGARD_DVFS)
	if (kbase_platform_dvfs_enable(kbdev, true, 0) != MALI_TRUE)
		return -EPERM;
#endif

	return 0;
}

static inline void pm_callback_suspend(struct kbase_device *kbdev)
{
#ifdef CONFIG_MALI_MIDGARD_RT_PM
	if (!pm_runtime_status_suspended(kbdev->dev))
		pm_callback_runtime_off(kbdev);
#else
	pm_callback_power_off(kbdev);
#endif
}

static inline void pm_callback_resume(struct kbase_device *kbdev)
{
#ifdef CONFIG_MALI_MIDGARD_RT_PM
	if (!pm_runtime_status_suspended(kbdev->dev))
		pm_callback_runtime_on(kbdev);
	else
		pm_callback_power_on(kbdev);
#else
	pm_callback_power_on(kbdev);
#endif
}

struct kbase_pm_callback_conf pm_callbacks = {
	.power_on_callback = pm_callback_power_on,
	.power_off_callback = pm_callback_power_off,
	.power_suspend_callback = pm_callback_suspend,
	.power_resume_callback = pm_callback_resume,
#ifdef CONFIG_MALI_MIDGARD_RT_PM
	.power_runtime_init_callback = pm_callback_runtime_init,
	.power_runtime_term_callback = pm_callback_runtime_term,
	.power_runtime_off_callback = pm_callback_runtime_off,
	.power_runtime_on_callback = pm_callback_runtime_on
#else
	.power_runtime_init_callback = NULL,
	.power_runtime_term_callback = NULL,
	.power_runtime_off_callback = NULL,
	.power_runtime_on_callback = NULL
#endif
};



static struct kbase_platform_config hi6250_platform_config = {
#ifndef CONFIG_OF
	.io_resources = &io_resources
#endif
};

struct kbase_platform_config *kbase_get_platform_config(void)
{
	return &hi6250_platform_config;
}

int kbase_platform_early_init(void)
{
	/* Nothing needed at this stage */
	return 0;
}
