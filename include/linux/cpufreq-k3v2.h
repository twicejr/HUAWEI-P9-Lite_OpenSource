/*
 * include/linux/cpufreq-k3v2.h - generic cpu definition
 */

#ifndef _LINUX_CPUFREQ_K3V2_H_
#define _LINUX_CPUFREQ_K3V2_H_

#include "linux/ipps.h"

#define QOS_REMOVE_NOTIFY(cls, notify)	\
	do {	\
		ret = pm_qos_remove_notifier(cls, &notify);	\
		if (ret != 0) {	\
			pr_err("PM_QOS_CPU_NUMBER_LOCK remove err=%x\n", ret);\
			return;	\
		}	\
	} while (0)

#define QOS_ADD_NOTIFY(cls, notify) \
	do {	\
		ret = pm_qos_add_notifier(cls, &notify);	\
		if (ret != 0) {	\
			pr_err("[%s] add PM_QOS_CPU_NUMBER_LOCK err=%x\n",\
				__func__, ret);	\
			goto ERROR;	\
		}	\
	} while (0)

#define PARAM_MAX(obj)		(gipps_param.obj.max_freq)
#define PARAM_MIN(obj)		(gipps_param.obj.min_freq)
#define PARAM_SAFE(obj)		(gipps_param.obj.safe_freq)
#define PARAM_BLOCK(obj)	(gipps_param.obj.block_freq)
#define PARAM_VAL(obj, par)	(gipps_param.obj.par)

struct cpu_num_limit {
	int min;
	int max;
	int safe;
	int block;
};

extern struct cpu_num_limit gcpu_num_limit;
#endif /* _LINUX_CPUFREQ_K3V2_H_ */
