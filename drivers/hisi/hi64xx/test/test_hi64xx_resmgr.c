#include <linux/module.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/kthread.h>
#include <linux/debugfs.h>
#include <linux/printk.h>
#include <linux/notifier.h>

#include <linux/hisi/hi64xx/hi64xx_resmgr.h>


static struct hi64xx_resmgr *resmgr = NULL;
static struct notifier_block nblock;

static int pll_enable_counter[PLL_MAX] = {0};
static int micbias_enable_counter = 0;
static int ibias_enable_counter = 0;
static int pll_lock_fail_counter = 0;

static enum hi64xx_resmgr_event notified_event = -1;

#define REG_ADDR_REQUIRE_PLL_LOW  1
#define REG_ADDR_REQUIRE_PLL_HIGH 2
#define REG_ADDR_REQUIRE_PLL_NONE 3

#define TEST_ASSERT(exp) \
	if (!(exp)) {\
		pr_info("[hi64xx_resmgr_test]%s:%d test failed\n", __func__, __LINE__); \
		return; \
	}

#define TEST_PASS  pr_info("[hi64xx_resmgr_test]%s: test pass\n", __func__)


static int notifier_callback (struct notifier_block *nb,
			unsigned long action, void *data)
{
	notified_event = action;
	if (action == PRE_PLL_SWITCH || action == POST_PLL_SWITCH) {
		struct pll_switch_event *event = (struct pll_switch_event *)data;
		pr_info("[hi64xx_resmgr_test] Notify: %s pll switch from %d to %d\n",
			action == PRE_PLL_SWITCH ? "pre" : "post", event->from, event->to);
	} else {
		pr_info("[hi64xx_resmgr_test] Notify: unknown event %d\n", notified_event);
	}
	return 0;
}


static int pll_low_turn_on(struct snd_soc_codec *codec)
{
	pll_enable_counter[PLL_LOW]++;
	return 0;
}

static int pll_low_turn_off(struct snd_soc_codec *codec)
{
	pll_enable_counter[PLL_LOW]--;
	return 0;
}

static int pll_high_turn_on(struct snd_soc_codec *codec)
{
	pll_enable_counter[PLL_HIGH]++;
	return 0;
}

static int pll_high_turn_off(struct snd_soc_codec *codec)
{
	pll_enable_counter[PLL_HIGH]--;
	return 0;
}

static bool pll_is_locked(struct snd_soc_codec *codec)
{
	if (pll_lock_fail_counter == 0)
		return true;
	else {
		pll_lock_fail_counter--;
		return false;
	}
}

static enum hi64xx_pll_type pll_for_reg_access(struct snd_soc_codec *codec,
					unsigned int regaddr)
{
	if (regaddr == REG_ADDR_REQUIRE_PLL_LOW)
		return PLL_LOW;
	else if (regaddr == REG_ADDR_REQUIRE_PLL_HIGH)
		return PLL_HIGH;
	else
		return PLL_NONE;
}

static int micbias_enable(struct snd_soc_codec *codec)
{
	micbias_enable_counter++;
	return 0;
}

static int micbias_disable(struct snd_soc_codec *codec)
{
	micbias_enable_counter--;
	return 0;
}

static int ibias_enable(struct snd_soc_codec *codec)
{
	ibias_enable_counter++;
	return 0;
}

static int ibias_disable(struct snd_soc_codec *codec)
{
	ibias_enable_counter--;
	return 0;
}

const struct resmgr_config resmgr_cfg = {
	.pll_num = 2,
	.pfn_pll_ctrls = {
		[PLL_LOW] = {
			.turn_on = pll_low_turn_on,
			.turn_off = pll_low_turn_off,
			.is_locked = pll_is_locked,
		},
		[PLL_HIGH] = {
			.turn_on = pll_high_turn_on,
			.turn_off = pll_high_turn_off,
			.is_locked = pll_is_locked,
		},
	},
	.pll_for_reg_access = pll_for_reg_access,
	.enable_micbias = micbias_enable,
	.disable_micbias = micbias_disable,
	.enable_ibias = ibias_enable,
	.disable_ibias = ibias_disable
};

static void test_init(void)
{
	if (resmgr)
		return;

	if (hi64xx_resmgr_init(NULL, NULL, NULL, &resmgr_cfg, &resmgr)) {
		pr_err("test_hi64xx_resmgr: hi64xx_resmgr_init failed");
		return;
	}

	memset(&nblock, 0, sizeof(nblock));
	nblock.notifier_call = notifier_callback;
	hi64xx_resmgr_register_notifier(resmgr, &nblock);
}

static void test_deinit(void)
{
	if (resmgr) {
		hi64xx_resmgr_deinit(resmgr);
		resmgr = NULL;
	}
}

/* ------------------ test cases ---------------------- */

static void test_single_pll_request_and_release(void)
{
	hi64xx_resmgr_request_pll(resmgr, PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 1);

	/* enable more than once, the pll will not change */
	hi64xx_resmgr_request_pll(resmgr, PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 1);

	/* ref count not reach 0, the pll will not change */
	hi64xx_resmgr_release_pll(resmgr, PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 1);

	hi64xx_resmgr_release_pll(resmgr, PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 0);

	TEST_PASS;
}

static void test_multi_pll_request_and_release(void) {
	hi64xx_resmgr_request_pll(resmgr, PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 1);

	hi64xx_resmgr_request_pll(resmgr, PLL_HIGH);
	TEST_ASSERT(pll_enable_counter[PLL_HIGH] == 1);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 0);

	hi64xx_resmgr_release_pll(resmgr, PLL_HIGH);
	TEST_ASSERT(pll_enable_counter[PLL_HIGH] == 0);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 1);

	hi64xx_resmgr_release_pll(resmgr, PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 0);

	TEST_PASS;
}

static void test_micbias_request_and_release(void) {
	hi64xx_resmgr_request_micbias(resmgr);
	TEST_ASSERT(micbias_enable_counter == 1);
	TEST_ASSERT(ibias_enable_counter == 1);

	hi64xx_resmgr_request_micbias(resmgr);
	TEST_ASSERT(micbias_enable_counter == 1);
	TEST_ASSERT(ibias_enable_counter == 1);

	hi64xx_resmgr_release_micbias(resmgr);
	TEST_ASSERT(micbias_enable_counter == 1);
	TEST_ASSERT(ibias_enable_counter == 1);

	hi64xx_resmgr_release_micbias(resmgr);
	TEST_ASSERT(micbias_enable_counter == 0);
	TEST_ASSERT(ibias_enable_counter == 0);

	TEST_PASS;
}

static void test_ibias_controlled_by_pll_and_micbias(void) {
	hi64xx_resmgr_request_micbias(resmgr);
	TEST_ASSERT(ibias_enable_counter == 1);

	hi64xx_resmgr_request_pll(resmgr, PLL_LOW);
	TEST_ASSERT(ibias_enable_counter == 1);

	hi64xx_resmgr_release_micbias(resmgr);
	TEST_ASSERT(ibias_enable_counter == 1);

	hi64xx_resmgr_release_pll(resmgr, PLL_LOW);
	TEST_ASSERT(ibias_enable_counter == 0);

	TEST_PASS;
}

static void test_reg_access_not_need_pll(void) {
	hi64xx_resmgr_request_reg_access(resmgr, REG_ADDR_REQUIRE_PLL_NONE);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 0);
	TEST_ASSERT(pll_enable_counter[PLL_HIGH] == 0);
	TEST_ASSERT(pll_enable_counter[PLL_44_1] == 0);

	hi64xx_resmgr_release_reg_access(resmgr, REG_ADDR_REQUIRE_PLL_NONE);

	TEST_PASS;
}


static void test_reg_access_need_pll(void) {
	hi64xx_resmgr_request_reg_access(resmgr, REG_ADDR_REQUIRE_PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 1);

	/* test delay release */
	hi64xx_resmgr_release_reg_access(resmgr, REG_ADDR_REQUIRE_PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 1);

	hi64xx_resmgr_request_reg_access(resmgr, REG_ADDR_REQUIRE_PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 1);
	hi64xx_resmgr_release_reg_access(resmgr, REG_ADDR_REQUIRE_PLL_LOW);
	msleep(600);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 0);

	TEST_PASS;
}

static void test_reg_pll_lock_retry_success(void)
{
	pll_lock_fail_counter = 4;
	hi64xx_resmgr_request_pll(resmgr, PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 1);
	hi64xx_resmgr_release_pll(resmgr, PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 0);

	TEST_PASS;
}

static void test_reg_pll_lock_retry_fail(void)
{
	pll_lock_fail_counter = 5;
	hi64xx_resmgr_request_pll(resmgr, PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 1);
	hi64xx_resmgr_release_pll(resmgr, PLL_LOW);
	TEST_ASSERT(pll_enable_counter[PLL_LOW] == 0);

	TEST_PASS;
}

struct test_case {
	const char* name;
	void (*test_func)(void);
};
#define ADD_CASE(func) \
	{#func, func}

struct test_case test_cases[] = {
	ADD_CASE(test_single_pll_request_and_release),
	ADD_CASE(test_multi_pll_request_and_release),
	ADD_CASE(test_micbias_request_and_release),
	ADD_CASE(test_ibias_controlled_by_pll_and_micbias),
	ADD_CASE(test_reg_access_not_need_pll),
	ADD_CASE(test_reg_access_need_pll),
	ADD_CASE(test_reg_pll_lock_retry_success),
	ADD_CASE(test_reg_pll_lock_retry_fail),
};

/* ---------------------------------------------------- */


static ssize_t do_test_read(struct file *file, char __user *user_buf,
			size_t count, loff_t *ppos)
{
	int i;
	char tmpbuf[2048] = {0};
	size_t n;
	size_t total = 0;

	n = snprintf(tmpbuf + total, sizeof(tmpbuf) - total - 1, "test menu\r\n");
	if (n < 0)
		return n;
	total += n;

	for (i = 0; i < ARRAY_SIZE(test_cases); i++) {
		n = snprintf(tmpbuf + total, sizeof(tmpbuf) - total - 1,
			"%d: %s\r\n", i, test_cases[i].name);
		if (n < 0)
			return n;
		total += n;
	}

	n = snprintf(tmpbuf + total, sizeof(tmpbuf) - total - 1,
			"%d: test all cases\r\n", i);
	if (n < 0)
		return n;
	total += n;

	return simple_read_from_buffer(user_buf, count, ppos, tmpbuf, total);
}

static ssize_t do_test_write(struct file *file, const char __user *user_buf,
			size_t count, loff_t *ppos)
{
	char cmdbuf[64] = {0};
	int i;
	int ret;
	long cmd;

	if (count >= sizeof(cmdbuf))
		count = sizeof(cmdbuf) - 1;

	if(copy_from_user(cmdbuf, user_buf, count))
		pr_warn("test_hi64xx_resmgr: user buffer is not completely copied");

	ret = kstrtol(cmdbuf, 10, &cmd);
	if (ret != 0) {
		pr_err("test_hi64xx_resmgr: invalid input");
		return 0;
	}

	if (cmd >= 0 && cmd < ARRAY_SIZE(test_cases)) {
		test_init();
		test_cases[cmd].test_func();
		test_deinit();
	}
	else if (cmd == ARRAY_SIZE(test_cases)) {
		/* test all */
		for (i = 0; i < ARRAY_SIZE(test_cases); i++) {
			test_init();
			test_cases[i].test_func();
			test_deinit();
		}
	} else {
	}

	return count;
}

static const struct file_operations do_test_fops = {
	.read = do_test_read,
	.write = do_test_write,
};


static int __init test_hi64xx_resmgr_init(void)
{
	struct dentry *dbg_fs_dir = debugfs_create_dir("hi64xx_resmgr", NULL);

	if (!dbg_fs_dir)
		return 0;

	if (!debugfs_create_file("test", 0644, dbg_fs_dir, NULL, &do_test_fops))
		pr_err("test_hi64xx_resmgr_init: failed to create debugfs node\n");

	return 0;
}

static void __exit test_hi64xx_resmgr_exit(void)
{
}

module_init(test_hi64xx_resmgr_init);
module_exit(test_hi64xx_resmgr_exit);

MODULE_AUTHOR("dingqing <dingqing@hisilicon.com>");
MODULE_DESCRIPTION("test hi64xx_resmgr");
MODULE_LICENSE("GPL");
