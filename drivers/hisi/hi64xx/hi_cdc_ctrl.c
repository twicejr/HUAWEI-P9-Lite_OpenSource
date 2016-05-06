#include <linux/module.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>

#include <linux/hisi/hi64xx/hi_cdc_ctrl.h>

struct reg_ops {
    unsigned int (*read8)(unsigned int reg);
    unsigned int (*read32)(unsigned int reg);
    void (*write8)(unsigned int reg, unsigned int val);
    void (*write32)(unsigned int reg, unsigned int val);
};

/* record the register operations for dump */
struct reg_op_item {
	struct timespec tm;
	int    rw;
	unsigned int reg;
	unsigned int val;
};

struct hi_cdc_ctrl_priv {
	struct hi_cdc_ctrl  cdc_ctrl;
	int irq;
	unsigned int regaddr8_begin;
	unsigned int regaddr8_end;
	struct mutex io_mutex;
	struct reg_ops reg_ops;
	struct clk *cdc_mclk;
	struct regulator *supplies[CDC_SUP_MAX];
	/* for debug */
	struct reg_op_item op_rec[128];
	int rec_wr_idx;
};

/* TODO: should use common interfaces, for both 6402 & 6403 */
extern unsigned int slimbus_read_1byte(unsigned int reg);
extern unsigned int slimbus_read_4byte(unsigned int reg);
extern void slimbus_write_1byte(unsigned int reg, unsigned int val);
extern void slimbus_write_4byte(unsigned int reg, unsigned int val);

extern unsigned int ssi_reg_read8(unsigned int reg);
extern unsigned int ssi_reg_read32(unsigned int reg);
extern void ssi_reg_write8(unsigned int reg, unsigned int val);
extern void ssi_reg_write32(unsigned int reg, unsigned int val);

/* this function can only be called when io_mutex is locked */
static void _record_reg_op(struct hi_cdc_ctrl_priv *priv, int rw,
	unsigned int reg_addr, unsigned int reg_val)
{
	int idx = priv->rec_wr_idx;
	struct reg_op_item *item = &priv->op_rec[idx];

	get_monotonic_boottime(&item->tm);
	item->rw = rw;
	item->reg = reg_addr;
	item->val = reg_val;

	if (++priv->rec_wr_idx == ARRAY_SIZE(priv->op_rec))
		priv->rec_wr_idx = 0;
}

static void _record_reg_dump(struct hi_cdc_ctrl_priv *priv)
{
	int i;
	struct reg_op_item *item;
	pr_info("!=== codec register operations dump begin: ===\n");
	mutex_lock(&priv->io_mutex);
	for (i = priv->rec_wr_idx; i < ARRAY_SIZE(priv->op_rec); i++) {
		item = &priv->op_rec[i];
		pr_info("[%6ld.%09ld]%c: %08x, %08x\n", item->tm.tv_sec,
			item->tm.tv_nsec, item->rw ? 'w' : 'r', item->reg, item->val);
	}

	for (i = 0; i < priv->rec_wr_idx; i++) {
		item = &priv->op_rec[i];
		pr_info("[%6ld.%09ld]%c: %08x, %08x\n", item->tm.tv_sec,
			item->tm.tv_nsec, item->rw ? 'w' : 'r', item->reg, item->val);
	}
	mutex_unlock(&priv->io_mutex);
	pr_info("!=== codec register operations dump end ===\n");
}

void hi_cdcctrl_dump(struct hi_cdc_ctrl *cdc_ctrl)
{
	struct hi_cdc_ctrl_priv *priv = (struct hi_cdc_ctrl_priv *)cdc_ctrl;
	_record_reg_dump(priv);
}
EXPORT_SYMBOL(hi_cdcctrl_dump);

unsigned int hi_cdcctrl_reg_read(struct hi_cdc_ctrl *cdc_ctrl,
                                 unsigned int reg_addr)
{
	struct hi_cdc_ctrl_priv *priv = (struct hi_cdc_ctrl_priv *)cdc_ctrl;
	unsigned int ret = 0;

	mutex_lock(&priv->io_mutex);
	if (reg_addr >= priv->regaddr8_begin && reg_addr <= priv->regaddr8_end)
		ret = priv->reg_ops.read8(reg_addr);
	else
		ret = priv->reg_ops.read32(reg_addr);

	_record_reg_op(priv, 0, reg_addr, ret);
	mutex_unlock(&priv->io_mutex);

	return ret;
}
EXPORT_SYMBOL(hi_cdcctrl_reg_read);

int hi_cdcctrl_reg_write(struct hi_cdc_ctrl *cdc_ctrl,
                         unsigned int reg_addr, unsigned int reg_val)
{
	struct hi_cdc_ctrl_priv *priv = (struct hi_cdc_ctrl_priv *)cdc_ctrl;

	mutex_lock(&priv->io_mutex);
	_record_reg_op(priv, 1, reg_addr, reg_val);

	if (reg_addr >= priv->regaddr8_begin && reg_addr <= priv->regaddr8_end)
		priv->reg_ops.write8(reg_addr, reg_val);
	else
		priv->reg_ops.write32(reg_addr, reg_val);
	mutex_unlock(&priv->io_mutex);

	return 0;
}
EXPORT_SYMBOL(hi_cdcctrl_reg_write);

void hi_cdcctrl_reg_update_bits(struct hi_cdc_ctrl *cdc_ctrl, unsigned int reg,
                                unsigned int mask, unsigned int value)
{
	unsigned int old, new;

	old = hi_cdcctrl_reg_read(cdc_ctrl, reg);
	new = (old & ~mask) | (value & mask);
	hi_cdcctrl_reg_write(cdc_ctrl, reg, new);
}
EXPORT_SYMBOL(hi_cdcctrl_reg_update_bits);

int hi_cdcctrl_hw_reset(struct hi_cdc_ctrl *cdc_ctrl)
{
	return 0;
}
EXPORT_SYMBOL(hi_cdcctrl_hw_reset);

int hi_cdcctrl_get_irq(struct hi_cdc_ctrl *cdc_ctrl)
{
	struct hi_cdc_ctrl_priv *priv = (struct hi_cdc_ctrl_priv *)cdc_ctrl;
	return priv->irq;
}
EXPORT_SYMBOL(hi_cdcctrl_get_irq);

int hi_cdcctrl_enable_supply(struct hi_cdc_ctrl *cdc_ctrl,
                             enum hi_cdcctrl_supply sup_type, bool enable)
{
	struct hi_cdc_ctrl_priv *priv = (struct hi_cdc_ctrl_priv *)cdc_ctrl;

	if (priv == NULL) {
		/* may be used by test program, just return */
		return 0;
	}

	if (!priv->supplies[sup_type]) {
		/* Some supplies don't need to be controlled, it's not an error */
		return 0;
	}

	if (enable)
		return regulator_enable(priv->supplies[sup_type]);
	else
		return regulator_disable(priv->supplies[sup_type]);

}
EXPORT_SYMBOL(hi_cdcctrl_enable_supply);

int hi_cdcctrl_enable_clk(struct hi_cdc_ctrl *cdc_ctrl,
                          enum hi_cdcctrl_clk clk_type, bool enable)
{
	struct hi_cdc_ctrl_priv *priv = (struct hi_cdc_ctrl_priv *)cdc_ctrl;

	if (priv == NULL) {
		/* may be used by test program, just return */
		return 0;
	}

	if (!priv->cdc_mclk){
		/* No mclk, it's not an error,  */
		return 0;
	}

	if (enable)
		return clk_prepare_enable(priv->cdc_mclk);
	else
		clk_disable_unprepare(priv->cdc_mclk);

	return 0;
}
EXPORT_SYMBOL(hi_cdcctrl_enable_clk);

static struct of_device_id of_codec_controller_child_match_tbl[] = {
	/* hi64xx_irq */
	{
		.compatible = "hisilicon,hi64xx-irq",
	},
	{ /* end */ }
};

static int hi_cdcctrl_probe(struct platform_device *pdev)
{
	int ret;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct hi_cdc_ctrl_priv *priv;
	const char *str;
	int gpio;
	enum of_gpio_flags flags;

	dev_info(dev, "probe begin");

	priv = devm_kzalloc(dev, sizeof(struct hi_cdc_ctrl_priv), GFP_KERNEL);
	if (!priv) {
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, priv);
	priv->cdc_ctrl.dev = dev;

	ret = of_property_read_string(np, "hisilicon,bus-sel", &str);
	if (ret == 0 && !strcmp(str, "slimbus")) {
		priv->cdc_ctrl.bus_sel = BUSTYPE_SELECT_SLIMBUS;
		priv->reg_ops.read8 = slimbus_read_1byte;
		priv->reg_ops.read32 = slimbus_read_4byte;
		priv->reg_ops.write8 = slimbus_write_1byte;
		priv->reg_ops.write32 = slimbus_write_4byte;
	} else {
		priv->cdc_ctrl.bus_sel = BUSTYPE_SELECT_SSI;
		priv->reg_ops.read8 = ssi_reg_read8;
		priv->reg_ops.read32 = ssi_reg_read32;
		priv->reg_ops.write8 = ssi_reg_write8;
		priv->reg_ops.write32 = ssi_reg_write32;
	}

	ret = of_property_read_u32(np, "hisilicon,reg-8bit-begin-addr", &priv->regaddr8_begin);
	if (ret) {
		dev_err(dev, "read reg-8bit-begin-addr error\n");
		goto err_exit;
	}

	ret = of_property_read_u32(np, "hisilicon,reg-8bit-end-addr", &priv->regaddr8_end);
	if (ret) {
		dev_err(dev, "read reg-8bit-end-addr error\n");
		goto err_exit;
	}

	priv->supplies[CDC_SUP_MAIN] = devm_regulator_get(dev, "codec-main");
	if (IS_ERR(priv->supplies[CDC_SUP_MAIN]))
		priv->supplies[CDC_SUP_MAIN] = NULL;
	else
		if (regulator_enable(priv->supplies[CDC_SUP_MAIN]))
			dev_err(dev, "failed to enable codec main supply\n");

	priv->supplies[CDC_SUP_ANLG] = devm_regulator_get(dev, "codec-anlg");
	if (IS_ERR(priv->supplies[CDC_SUP_ANLG]))
		priv->supplies[CDC_SUP_ANLG] = NULL;

	priv->cdc_mclk = devm_clk_get(dev, "clk_pmuaudioclk");
	if (IS_ERR(priv->cdc_mclk)) {
		dev_err(dev, "cdc mclk not found!\n");
		ret = PTR_ERR(priv->cdc_mclk);
		goto err_exit;
	}

	/*TODO: should enable/disable during read/write? */
	ret = clk_prepare_enable(priv->cdc_mclk);
	if (ret) {
		dev_err(dev, "clk prepare enable failed!\n");
		goto err_exit;
	} else {
		mdelay(1);
	}

	gpio = of_get_gpio_flags(np, 0, &flags);
	if (gpio < 0) {
		dev_err(dev, "get gpio flags failed\n");
		ret = gpio;
		goto err_exit;
	}

	dev_info(dev, "probe gpio %d", gpio);

	if (!gpio_is_valid(gpio)) {
		dev_err(dev, "gpio%d is invalid\n", gpio);
		ret = -EINVAL;
		goto err_exit;
	}

	ret = gpio_request_one(gpio, GPIOF_IN, "codec_interrupt");
	if (ret < 0) {
		dev_err(dev, "failed to request gpio%d\n", gpio);
		goto err_exit;
	}

	priv->irq = gpio_to_irq(gpio);

	dev_info(dev, "probe irq %d", priv->irq);

	mutex_init(&priv->io_mutex);

	/* populate sub nodes */
	of_platform_populate(np, of_codec_controller_child_match_tbl, NULL, dev);

	dev_info(dev, "codec-controller probe ok\n");
	return 0;

err_exit:
	dev_err(dev, "codec-controller probe fail\n");
	return ret;
}

static int hi_cdcctrl_remove(struct platform_device *pdev)
{
	struct hi_cdc_ctrl_priv *priv =
		(struct hi_cdc_ctrl_priv *)platform_get_drvdata(pdev);
	mutex_destroy(&priv->io_mutex);

	return 0;
}

static int hi_cdcctrl_suspend(struct platform_device *pdev, pm_message_t state)
{
	/*TODO: should enable/disable during read/write? */
	struct hi_cdc_ctrl_priv *priv =
		(struct hi_cdc_ctrl_priv *)platform_get_drvdata(pdev);
	clk_disable_unprepare(priv->cdc_mclk);
	return 0;
}

static int hi_cdcctrl_resume(struct platform_device *pdev)
{
	/*TODO: should enable/disable during read/write? */
	struct hi_cdc_ctrl_priv *priv =
		(struct hi_cdc_ctrl_priv *)platform_get_drvdata(pdev);
	int ret = clk_prepare_enable(priv->cdc_mclk);
	if (ret)
		dev_err(&pdev->dev, "clk prepare enable failed!\n");

	return 0;
}

static struct of_device_id of_hi_cdcctrl_match[] = {
	{
		.compatible = "hisilicon,codec-controller",
	},
	{ /* end */ }
};

static struct platform_driver hi_cdc_ctrl_driver = {
	.driver = {
		.name	= "codec_controller",
		.owner  = THIS_MODULE,
		.of_match_table = of_hi_cdcctrl_match,
	},
	.probe		= hi_cdcctrl_probe,
	.remove		= hi_cdcctrl_remove,
	.suspend	= hi_cdcctrl_suspend,
	.resume		= hi_cdcctrl_resume,

};

static int __init hi_cdcctrl_init(void)
{
	return platform_driver_register(&hi_cdc_ctrl_driver);
}

static void __exit hi_cdcctrl_exit(void)
{
	platform_driver_unregister(&hi_cdc_ctrl_driver);
}
fs_initcall_sync(hi_cdcctrl_init);
module_exit(hi_cdcctrl_exit);

MODULE_DESCRIPTION("hisi codec controller");
MODULE_AUTHOR("dingqing <dingqing@hisilicon.com>");
MODULE_LICENSE("GPL");
