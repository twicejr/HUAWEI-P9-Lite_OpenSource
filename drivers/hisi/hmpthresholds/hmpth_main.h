/*
 * set policy to hmp thresholds.
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef	__HMPTH_MAIN_H_
#define __HMPTH_MAIN_H_

#include <linux/types.h>


#define MAX_MUM_POLICY 16
/*16 is include '\0' */
#define MAX_LENGTH_OF_POLICY_NAME 16

/*
 * the bigger prior_num has the higher priority.
 */
enum prior_num {
	PRIOR_0 = 0,	/*default*/
	PRIOR_1,
	PRIOR_2,	/*performance*/
	PRIOR_3,
	PRIOR_4,	/*security*/
	PRIOR_5
};

enum prior_direct_num {
	PROFORM = 1,	/* PRIOR_2 */
	LOWPOWER	/* PRIOR_4 */
};

enum policy_state_num {
	STATE_OFF = 0,
	STATE_ON = 1
};

#define MAX_THRESHOLDS 1024
#define MIN_THRESHOLDS 0

#define DEFAULT_POLICY_NAME "default"

#define UP_MUST_BIG_THAN_DOWN 100
/*
 * name: the client's name which want to set policy.
 *       (applica, tempera, cpuidle, cpufreq,eg.)
 * prior: the priority of policy.
 *	  (PRIOR_1 - PRIOR_5)
 * state: if this policy is in use.
 * thrsh_up: hmp_up_threshold
 * thrsh_down: hmp_down_threshold
 * prior_direct: what's the purpoes of the priority.
 *		(PRIOR_2 intent to Improving performance)
 *		(PRIOR_4 intent to save power)
 *		(other priorities are unused for now)
 */
struct hmp_policy_struct {
	char name[MAX_LENGTH_OF_POLICY_NAME];
	int prior;
	int policy_state;
	unsigned int thrsh_up;
	unsigned int thrsh_down;
	int prior_direct;
};

/* is lowercase character*/
static inline int islowchac(int ch)
{
	return (ch >= 'a') && (ch <= 'z');
}

extern unsigned int hmp_up_threshold;
extern unsigned int hmp_down_threshold;


#ifdef HMPTH_SET_DEBUG
#define hmpth_debug(fmt, ...) pr_err(fmt, ...)
#else
#define hmpth_debug(fmt, ...) {}
#endif


#endif	/* End #define __HMPTH_MAIN_H_ */
