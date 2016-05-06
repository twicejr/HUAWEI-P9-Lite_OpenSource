#include <linux/module.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/debugfs.h>
#include <linux/of.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#include <linux/hisi/hi64xx/hi_cdc_ctrl.h>

#define CMD_LENGTH_MAX 64
#define CODEC_HPL_ADDR 0x200070b8 /*test read8/write8*/
#define CODEC_HPL_VALUE 0x11
#define CODEC_IOMUX_ADDR 0x20001104 /*test read32/write32*/
#define CODEC_IOMUX_VALUE 0x12

#define TEST_ASSERT(exp) \
	if (!(exp)) {\
		pr_info("[test_hi_cdc_ctrl]%s:%d test failed\n", __func__, __LINE__); \
		return; \
	}

#define TEST_PASS  pr_info("[test_hi_cdc_ctrl]%s: test pass\n", __func__);
#define TEST_START pr_info("[test_hi_cdc_ctrl]%s: test start\n", __func__);

struct test_cdc_ctrl_priv {
	struct hi_cdc_ctrl  *cdc_ctrl;
	struct dentry *cdc_ctrl_dbg_dir;
	struct dentry *cdc_ctrl_dbg_file;
};

static struct test_cdc_ctrl_priv *test_cdc_ctrl = NULL;

static void  test_cdc_ctrl_reg_write8_read8(void)
{
	int ret = 0;
	int reg_value = 0;

	TEST_START;

	ret = hi_cdcctrl_reg_write(test_cdc_ctrl->cdc_ctrl,
			CODEC_HPL_ADDR, CODEC_HPL_VALUE);
	TEST_ASSERT(0 == ret);

	reg_value = hi_cdcctrl_reg_read(test_cdc_ctrl->cdc_ctrl, CODEC_HPL_ADDR);
	TEST_ASSERT(CODEC_HPL_VALUE == reg_value);

	TEST_PASS;
}

static void  test_cdc_ctrl_reg_write32_read32(void)
{
	int ret = 0;
	int reg_vaule = 0;

	TEST_START;

	ret = hi_cdcctrl_reg_write(test_cdc_ctrl->cdc_ctrl,
			CODEC_IOMUX_ADDR, CODEC_IOMUX_VALUE);
	TEST_ASSERT(0 == ret);

	reg_vaule = hi_cdcctrl_reg_read(test_cdc_ctrl->cdc_ctrl, CODEC_IOMUX_ADDR);
	TEST_ASSERT(CODEC_IOMUX_VALUE == reg_vaule);

	TEST_PASS;
}

struct test_case {
	const char* name;
	void (*test_func)(void);
};
#define ADD_CASE(func) \
	{#func, func}

static struct test_case test_cases[] = {
	ADD_CASE(test_cdc_ctrl_reg_write8_read8),
	ADD_CASE(test_cdc_ctrl_reg_write32_read32),
};

static ssize_t test_cdc_ctrl_show(struct file *file, char __user *buf,
		size_t size, loff_t *data)
{
	pr_info("codec ctrl show\n");
	return 0;
}

static ssize_t test_cdc_ctrl_store(struct file *file, const char __user *user_buf,
		size_t size, loff_t *data)
{
	char cmd_buf[CMD_LENGTH_MAX] = {0};
	unsigned int cmd_size = 0;
	long cmd = 0;
	int i = 0;

	if (!test_cdc_ctrl) {
		pr_err("test_cdc_ctrl is NULL\n");
		return 0;
	}

	if (!test_cdc_ctrl->cdc_ctrl) {
		pr_err("codec ctrl is NULL\n");
		return 0;
	}

	if (!user_buf) {
		pr_err("user buf is NULL\n");
		return 0;
	}

	cmd_size = (size > CMD_LENGTH_MAX) ? CMD_LENGTH_MAX : size;

	if(copy_from_user(cmd_buf, user_buf, cmd_size)) {
		pr_err("cpy from user failed\n");
		return 0;
	}

	if (kstrtol(cmd_buf, 10, &cmd)) {
		pr_err("invalid input\n");
		return 0;
	}

	pr_info("cmd:%ld, cmd size:%d\n", cmd, cmd_size);

	if (cmd >= 0 && cmd < ARRAY_SIZE(test_cases)) {
		test_cases[cmd].test_func();
	} else {
		/* test all */
		for (i = 0; i < ARRAY_SIZE(test_cases); i++)
			test_cases[i].test_func();
	}

	return cmd_size;
}

static const struct file_operations test_cdc_ctrl_ops = {
	.read = test_cdc_ctrl_show,
	.write = test_cdc_ctrl_store,
};

static int test_cdc_ctrl_create_debugfs(void)
{
	struct dentry *cdc_ctrl_dbg_dir = NULL;
	struct dentry *cdc_ctrl_dbg_file = NULL;

	cdc_ctrl_dbg_dir = debugfs_create_dir("codec_ctrl", NULL);
	if (!cdc_ctrl_dbg_dir) {
		pr_err("create sys/kernel/debug/codec_ctrl dir failed\n");
		return -ENODEV;
	}
	test_cdc_ctrl->cdc_ctrl_dbg_dir = cdc_ctrl_dbg_dir;

	cdc_ctrl_dbg_file = debugfs_create_file("codec_ctrl_debug", 0644,
			cdc_ctrl_dbg_dir, NULL, &test_cdc_ctrl_ops);
	if (!cdc_ctrl_dbg_file) {
		pr_err("create codec ctrl debug file failed\n");
		return -ENODEV;
	}
	test_cdc_ctrl->cdc_ctrl_dbg_file = cdc_ctrl_dbg_file;

	return 0;
}

static int test_cdc_ctrl_probe(struct platform_device *pdev)
{
	struct hi_cdc_ctrl *cdc_ctrl = NULL;

	cdc_ctrl = (struct hi_cdc_ctrl *)dev_get_drvdata(pdev->dev.parent);

	test_cdc_ctrl = kzalloc(sizeof(struct test_cdc_ctrl_priv), GFP_KERNEL);
	if (!test_cdc_ctrl) {
		pr_err("malloc failed\n");
		return -ENOMEM;
	}

	test_cdc_ctrl->cdc_ctrl = cdc_ctrl;

	if (test_cdc_ctrl_create_debugfs()) {
		pr_err("create debugfs failed\n");
		return -EFAULT;
	}

	return 0;
}

static int test_cdc_ctrl_remove(struct platform_device *pdev)
{
	if (!test_cdc_ctrl)
	return 0;

	if (test_cdc_ctrl->cdc_ctrl_dbg_dir)
		debugfs_remove(test_cdc_ctrl->cdc_ctrl_dbg_dir);

	if (test_cdc_ctrl->cdc_ctrl_dbg_file)
		debugfs_remove(test_cdc_ctrl->cdc_ctrl_dbg_file);

	kfree(test_cdc_ctrl);
	test_cdc_ctrl = NULL;

	return 0;
}

static struct of_device_id of_test_cdc_ctrl_match[] = {
	{
		.compatible = "hisilicon,test-codec-controller",
	},
	{ /* end */ }
};

static struct platform_driver test_cdc_ctrl_driver = {
	.driver = {
		.name = "test_codec_controller",
		.owner  = THIS_MODULE,
		.of_match_table = of_test_cdc_ctrl_match,
	},
	.probe	= test_cdc_ctrl_probe,
	.remove	= test_cdc_ctrl_remove,
};

static int __init test_cdc_ctrl_init(void)
{
	return platform_driver_register(&test_cdc_ctrl_driver);
}

static void __exit test_cdc_ctrl_exit(void)
{
	platform_driver_unregister(&test_cdc_ctrl_driver);
}

module_init(test_cdc_ctrl_init);
module_exit(test_cdc_ctrl_exit);

MODULE_AUTHOR("liujinhong <liujinhong@hisilicon.com>");
MODULE_DESCRIPTION("test_cdc_ctrl");
MODULE_LICENSE("GPL");
