#ifndef __EXMBIST_TEST_H__
#define __EXMBIST_TEST_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/pm.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/of.h>

#define EXM_OK						(0)
#define EXM_ERROR					(-1)

#define REG_BASE_DDRC_CFG			(0xfffc0000)

#define DDR_REG_DMSS(base,n)		(base + 0x0000)
#define DDR_REG_AXI(base,n)			(base + 0x0000 + 0x800 * (n))
#define DDR_REG_GLOBAL(base)		(base + 0x6000)
#define DDR_REG_QOSBUF(base,m)		(base + 0x8000 + 0x4000 * (m))
#define DDR_REG_DMC(base, m, n)		(base + 0x9000 + 0x4000 * (m) + 0x1000 * (n))
#define DDR_REG_PACK(base, n)		(base + 0x10000 + 0x2000 * (n))
#define DDR_REG_EXMBIST(base)		(base + 0x18000)

#define EXM_HOLD_UP					 0x55aa
#define EXM_ERROR_STOP				 1
#define EXM_ERROR_CONTINUE			 0

#define EXM_LOOP_START_CMD			"loop_start"
#define EXM_LOOP_END_CMD 			"loop_end"
#define EXM_OCCUR_ERROR_STOP		"error_stop"

struct hi3650_exmbist_dev {
	struct device		*dev;
	void __iomem		*base;
	spinlock_t			state_lock;
	struct clk			*clk;
	resource_size_t     mapbase;
	int					irq;
	struct device       *platform_dev;
};

typedef int (*DDR_TEST_FUNC_UNIT)(
	unsigned int arg0,
	unsigned int arg1,
	unsigned int arg2,
	unsigned int arg3);


struct ddr_test_func_def {
	DDR_TEST_FUNC_UNIT test_func;
	char* test_func_name;
};

struct exm_fsm_state{
	struct task_struct* exmbist_thread;
	unsigned int phy_addr_range_min;
	unsigned int phy_addr_range_max;
	unsigned int loop_cnt;
	unsigned int cur_loop_cnt;
	int 		 final_result;
	unsigned int exm_hold;
	struct file* mbist_log_file;
	
};

#define func_name_me(func) (#func)
#define NELEMENTS(arr) (sizeof(arr) / sizeof((arr)[0]))

int exm_default_conf_file(void);
int exm_set_test_loop_cnt(unsigned int loop_cnt);
void exm_set_phy_addr_range(unsigned int phy_addr_range_min, unsigned int phy_addr_range_max);
unsigned int exm_get_exmbist_addr_min(void);
unsigned int exm_get_exmbist_addr_max(void);
void __iomem * exm_get_reg_base(void);
int exm_ddr_density_get(void);
int exm_parse_conf_file(void);
int exm_set_pmu_enable(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
