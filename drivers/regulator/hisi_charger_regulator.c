/*
 * Device driver for regulators in HI6522 IC
 *
 * Copyright (c) 2011 Hisilicon.
 *
 * Dongbin Yu <yudongbin@huawei.com>
 *
 * this regulator's probe function will be called lots of times,,
 * because of there are lots of regulator nodes in dtb.
 * so,that's say, the driver must be inited before the regulator nodes
 * registor to system.
 *
 * Makefile have proved my guess, please refor to the makefile.
 * when the code is rebuild i hope we can build pmu sub_system.
 * init order can not base on compile
 */
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/regmap.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/of_regulator.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/power/hisi_hi6521_charger_power.h>
#if 0 //def CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#endif

enum hisi_charger_regulator_type{
    PMIC_BUCK_TYPE = 0,
    PMIC_LDO_TYPE  = 1,
    PMIC_LVS_TYPE  = 2,
    PMIC_BOOST_TYPE= 3,
    MTCMOS_SC_ON_TYPE      = 4,
    MTCMOS_ACPU_ON_TYPE    = 5,
    SCHARGE_TYPE           = 6,
};

struct hisi_charger_regulator_ctrl_regs{
	unsigned int  enable_reg;
	unsigned int  disable_reg;
	unsigned int  status_reg;
};

struct hisi_charger_regulator_vset_regs{
	unsigned int vset_reg;
};

struct hisi_charger_regulator_ctrl_data{
	int          shift;
	unsigned int mask;
};

struct hisi_charger_regulator_vset_data{
	int          shift;
	unsigned int mask;
};

#ifdef _DRV_LLT_
#define static
static inline int of_property_read_string_index(struct device_node *np,
                        const char *propname, int index,
                        const char **out_string)
{
    return -ENOSYS;
}
#endif

/* when the Linux is runing,
 * in system there are a lot of regulator,
 * based on the nodes in dtb
 */
struct hisi_charger_regulator {
	int status;                             /*this property in child  node*/
	unsigned int off_on_delay;              /*this property in parent node*/
	enum hisi_charger_regulator_type type;        /*this property in child  node*/
	int regulator_id;

	/*this property must be unify which is in child node*/
    struct hisi_charger_regulator_ctrl_regs   ctrl_regs;
    struct hisi_charger_regulator_ctrl_data   ctrl_data;

    struct hisi_charger_regulator_vset_regs   vset_regs;
    struct hisi_charger_regulator_vset_data   vset_data;
    unsigned int                        vol_numb;
    unsigned int                        *vset_table;
	struct regulator_desc rdesc;
	int (*dt_parse)(struct hisi_charger_regulator*, struct platform_device*);
};

static int regulator_test_debug = 0;

#ifdef _DRV_LLT_
void regulator_has_full_constraints(void)
{

}
#endif

static int hisi_regulator_scharge_is_enabled(struct regulator_dev *dev)
{
	int ret = 0;
	int regulator_id = 0;
    struct hisi_charger_regulator *sreg = rdev_get_drvdata(dev);
    struct hisi_charger_regulator_ctrl_regs  *ctrl_regs = &(sreg->ctrl_regs);
    struct hisi_charger_regulator_ctrl_data  *ctrl_data = &(sreg->ctrl_data);
	regulator_id =  rdev_get_id(dev);
    if (regulator_test_debug) {
	    pr_err("++++++++ in [%s] regulator name %s+++++++\n",__func__,sreg->rdesc.name);
	    pr_err("++++++++ ctrl_reg->enable %x+++++++\n",(unsigned int)ctrl_regs->enable_reg);
	    pr_err("++++++++ ctrl_reg->disable %x+++++++\n",(unsigned int)ctrl_regs->disable_reg);
	    pr_err("++++++++ ctrl_reg->status %x+++++++\n",(unsigned int)ctrl_regs->status_reg);
	    pr_err("++++++++ ctrl_data->shift %x+++++++\n",(unsigned int)ctrl_data->shift);
	    pr_err("++++++++ ctrl_data->mask %x+++++++\n",(unsigned int)ctrl_data->mask);
	    pr_err("++++++++ sreg->off_on_delay %x+++++++\n",(unsigned int)sreg->off_on_delay);
		pr_err("++++++++ sreg->id %x+++++++\n",(unsigned int)regulator_id);
	}
	ret = scharger_power_status(regulator_id);
    if (1 == ret) {
        ret = 1;
    } else {
        ret = 0;
    }

    return ret;
}

static int hisi_regulator_scharge_enable(struct regulator_dev *dev)
{
	int ret = 0;
	int regulator_id = 0;
    struct hisi_charger_regulator *sreg = rdev_get_drvdata(dev);
    struct hisi_charger_regulator_ctrl_regs  *ctrl_regs = &(sreg->ctrl_regs);
    struct hisi_charger_regulator_ctrl_data  *ctrl_data = &(sreg->ctrl_data);
	regulator_id =  rdev_get_id(dev);

    if (regulator_test_debug) {
	    pr_err("++++++++ in [%s] regulator name %s+++++++\n",__func__,sreg->rdesc.name);
	    pr_err("++++++++ ctrl_reg->enable %x+++++++\n",(unsigned int)ctrl_regs->enable_reg);
	    pr_err("++++++++ ctrl_reg->disable %x+++++++\n",(unsigned int)ctrl_regs->disable_reg);
	    pr_err("++++++++ ctrl_reg->status %x+++++++\n",(unsigned int)ctrl_regs->status_reg);
	    pr_err("++++++++ ctrl_data->shift %x+++++++\n",(unsigned int)ctrl_data->shift);
	    pr_err("++++++++ ctrl_data->mask %x+++++++\n",(unsigned int)ctrl_data->mask);
	    pr_err("++++++++ sreg->off_on_delay %x+++++++\n",(unsigned int)sreg->off_on_delay);
		pr_err("++++++++ sreg->id %x+++++++\n",(unsigned int)regulator_id);
	}

    ret = scharger_power_on(regulator_id);
    if (0 == ret) {
        ret = 0;
    } else {
        ret = -1;
    }

    return ret;
}

static int hisi_regulator_scharge_disable(struct regulator_dev *dev)
{
	int ret = 0;
	int regulator_id = 0;
	regulator_id =  rdev_get_id(dev);
    ret = scharger_power_off(regulator_id);
    if (0 == ret) {
        ret = 0;
    } else {
        ret = -1;
    }

    return ret;
}

static int hisi_regulator_scharge_list_voltage_linear(struct regulator_dev *rdev,
				  unsigned int selector)
{
    int i;
    struct hisi_charger_regulator *sreg = rdev_get_drvdata(rdev);

    if (selector >= sreg->vol_numb) {
        pr_err("selector err %s %d  \n",__func__, __LINE__);
        return -1;
    }

	if (regulator_test_debug) {
	    for (i=0;i<sreg->vol_numb;i++)
		{
			pr_err("%d ",(int)sreg->vset_table[i]);
	    }
	    pr_err("+++++++++++++++++++++++++++++++++++\n");
    }

    return sreg->vset_table[selector];
}

static int hisi_regulator_scharge_get_voltage(struct regulator_dev *dev)
{
	int i;
    int index = 0;
    struct hisi_charger_regulator *sreg = rdev_get_drvdata(dev);
    struct hisi_charger_regulator_vset_regs  *vset_regs = &(sreg->vset_regs);
    struct hisi_charger_regulator_vset_data  *vset_data = &(sreg->vset_data);

    if (regulator_test_debug) {
	    pr_err("++++++++ in [%s] regulator name %s+++++++\n",__func__,sreg->rdesc.name);
	    pr_err("++++++++ sreg->vol_numb %x+++++++\n",(unsigned int)sreg->vol_numb);
		pr_err("++++++++ vset_regs->vset_reg %x+++++++\n",(unsigned int)vset_regs->vset_reg);
	    pr_err("++++++++ vset_data->shift %x+++++++\n",(unsigned int)vset_data->shift);
	    pr_err("++++++++ vset_data->mask %x+++++++\n",(unsigned int)vset_data->mask);
	}
    index = scharger_power_get_voltage_index(vset_regs->vset_reg,vset_data->mask,vset_data->shift);

	if (index == -1) {
		return -1;
	} else if (index < 0 || index >=sreg->vol_numb) {
		pr_err("++++++++ in [%s] index  %d outside +++++++\n",__func__,index);
		return -1;
	}

    if (regulator_test_debug) {
	    pr_err("++++++++ index %x+++++++\n",(unsigned int)index);
	    pr_err("+++++++++++++++++++++++++++++++++++\n");
	    for (i=0;i<sreg->vol_numb;i++)
		{
			pr_err("%d ",(int)sreg->vset_table[i]);
	    }
	    pr_err("+++++++++++++++++++++++++++++++++++\n");
    }

    return sreg->vset_table[index];
}

static int hisi_regulator_scharge_set_voltage(struct regulator_dev *dev,
				int min_uV, int max_uV, unsigned *selector)
{
	struct hisi_charger_regulator *sreg = rdev_get_drvdata(dev);
    struct hisi_charger_regulator_vset_regs  *vset_regs = &(sreg->vset_regs);
    struct hisi_charger_regulator_vset_data  *vset_data = &(sreg->vset_data);
	u32 vsel;
	int ret = 0;
	int uV = 0;

	for (vsel = 0; vsel < sreg->rdesc.n_voltages; vsel++)
	{
		uV = sreg->vset_table[vsel];
		/* Break at the first in-range value */
		if (min_uV <= uV && uV <= max_uV) {
			break;
		}
	}

	/* unlikely to happen. sanity test done by regulator core */
	if (unlikely(vsel == sreg->rdesc.n_voltages)) {
		return -EINVAL;
	}

	*selector = vsel;
	/* set voltage selector */
	ret = scharger_power_set_voltage(vset_regs->vset_reg,vset_data->mask,vset_data->shift,vsel);
    if (regulator_test_debug) {
	    pr_err("++++++++ in [%s] regulator name %s+++++++\n",__func__,sreg->rdesc.name);
		pr_err("++++++++ vset_regs->vset_reg 0x%x+++++++\n",(unsigned int)vset_regs->vset_reg);
	    pr_err("++++++++ vset_data->shift 0x%x+++++++\n",(unsigned int)vset_data->shift);
	    pr_err("++++++++ vset_data->mask 0x%x+++++++\n",(unsigned int)vset_data->mask);
		pr_err("++++++++ sel 0x%x+++++++\n",(unsigned int)vsel);
	}

	return ret;
}

static int hisi_regulator_scharge_set_current_limit(struct regulator_dev *dev,
				int min_uA, int max_uA)
{
	struct hisi_charger_regulator *sreg = rdev_get_drvdata(dev);
    struct hisi_charger_regulator_vset_regs  *vset_regs = &(sreg->vset_regs);
    struct hisi_charger_regulator_vset_data  *vset_data = &(sreg->vset_data);
	u32 vsel;
	int ret = 0;
	int uA = 0;

	for (vsel = 0; vsel < sreg->rdesc.n_voltages; vsel++)
	{
		uA = sreg->vset_table[vsel];
		/* Break at the first in-range value */
		if (min_uA <= uA && uA <= max_uA){
			break;
		}
	}

	/* unlikely to happen. sanity test done by regulator core */
	if (unlikely(vsel == sreg->rdesc.n_voltages)) {
		return -EINVAL;
	}

	/* set voltage selector */
	ret = scharger_power_set_current_limit(vset_regs->vset_reg,vset_data->mask,vset_data->shift,vsel);
    if (regulator_test_debug) {
	    pr_err("++++++++ in [%s] regulator name %s+++++++\n",__func__,sreg->rdesc.name);
		pr_err("++++++++ vset_regs->vset_reg 0x%x+++++++\n",(unsigned int)vset_regs->vset_reg);
	    pr_err("++++++++ vset_data->shift 0x%x+++++++\n",(unsigned int)vset_data->shift);
	    pr_err("++++++++ vset_data->mask 0x%x+++++++\n",(unsigned int)vset_data->mask);
		pr_err("++++++++ sel 0x%x+++++++\n",(unsigned int)vsel);
	}

	return ret;
}

static int hisi_regulator_scharge_get_current_limit(struct regulator_dev *dev)
{
	int i;
    int index = 0;
    struct hisi_charger_regulator *sreg = rdev_get_drvdata(dev);
    struct hisi_charger_regulator_vset_regs  *vset_regs = &(sreg->vset_regs);
    struct hisi_charger_regulator_vset_data  *vset_data = &(sreg->vset_data);

    if (regulator_test_debug){
	    pr_err("++++++++ in [%s] regulator name %s+++++++\n",__func__,sreg->rdesc.name);
	    pr_err("++++++++ sreg->vol_numb %x+++++++\n",(unsigned int)sreg->vol_numb);
		pr_err("++++++++ vset_regs->vset_reg %x+++++++\n",(unsigned int)vset_regs->vset_reg);
	    pr_err("++++++++ vset_data->shift %x+++++++\n",(unsigned int)vset_data->shift);
	    pr_err("++++++++ vset_data->mask %x+++++++\n",(unsigned int)vset_data->mask);

	}

    index = scharger_power_get_current_limit_index(vset_regs->vset_reg,vset_data->mask,vset_data->shift);
	if (index == -1) {
		return -1;
	} else if (index < 0 || index >=sreg->vol_numb) {
		pr_err("++++++++ in [%s] index  %d outside +++++++\n",__func__,index);
		return -1;
	}

    if (regulator_test_debug){
	    pr_err("++++++++ index %x+++++++\n",(unsigned int)index);
	    pr_err("+++++++++++++++++++++++++++++++++++\n");
	    for (i=0;i<sreg->vol_numb;i++){
			pr_err("%d ",(int)sreg->vset_table[i]);
	    }
	    pr_err("+++++++++++++++++++++++++++++++++++\n");
    }

    return sreg->vset_table[index];
}

static unsigned int hisi_regulator_scharge_get_mode(struct regulator_dev *dev)
{
    return 0;
}

static int hisi_regulator_scharge_set_mode(struct regulator_dev *dev,unsigned int mode)
{
    return 0;
}

static unsigned int hisi_regulator_scharge_get_optimum_mode(struct regulator_dev *dev,
			int input_uV, int output_uV, int load_uA)
{
    return 0;
}

static struct regulator_ops hisi_regulator_scharge_rops = {
	.is_enabled = hisi_regulator_scharge_is_enabled,
	.enable = hisi_regulator_scharge_enable,
	.disable = hisi_regulator_scharge_disable,
	.list_voltage = hisi_regulator_scharge_list_voltage_linear,
	.get_voltage = hisi_regulator_scharge_get_voltage,
	.set_voltage = hisi_regulator_scharge_set_voltage,
	.get_current_limit = hisi_regulator_scharge_get_current_limit,
	.set_current_limit = hisi_regulator_scharge_set_current_limit,
	.get_mode = hisi_regulator_scharge_get_mode,
	.set_mode = hisi_regulator_scharge_set_mode,
	.get_optimum_mode = hisi_regulator_scharge_get_optimum_mode,
};

static int hisi_regualtor_dt_parse_common(struct hisi_charger_regulator *sreg,
				struct platform_device *pdev)
{
    pr_err(KERN_INFO"for stub\n\r");
	return 0;
}
static int hisi_regualtor_scharge_dt_parse(struct hisi_charger_regulator *sreg,
					struct platform_device *pdev)
{
    int ret;
    ret = hisi_regualtor_dt_parse_common(sreg,pdev);
    pr_err(KERN_INFO"for stub\n\r");
	return ret;
}

static const struct hisi_charger_regulator hisi_charger_regulator = {
	.rdesc = {
		.ops = &hisi_regulator_scharge_rops,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	},
	.dt_parse = hisi_regualtor_scharge_dt_parse,
};

static struct of_device_id of_hisi_regulator_scharger_match_tbl[] = {
    {
		.compatible = "hisilicon,hisi-regulator-scharger",
		.data = &hisi_charger_regulator,
    },
	{ /* end */ }
};

#if 0 //def CONFIG_DEBUG_FS
extern void get_current_regulator_dev(void);
extern void set_regulator_state(char *ldo_name, int value);
extern void get_regulator_state(char *ldo_name);
static int dbg_hisi_charger_regulator_show(struct seq_file *s, void *data)
{

	pr_err("%-13s %-15s %-15s %-15s %-15s\n",
			"LDO_NAME", "ON/OFF", "Use_count", "Open_count", "Always_on");
	pr_err("-----------------------------------------"
			"-----------------------------------------------\n");
	get_current_regulator_dev();
	return 0;
}

static int dbg_hisi_charger_regulator_open(struct inode *inode, struct file *file)
{
	return single_open(file, dbg_hisi_charger_regulator_show, inode->i_private);
}

static const struct file_operations debug_regulator_state_fops = {
	.open		= dbg_hisi_charger_regulator_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int dbg_control_regulator_show(struct seq_file *s, void *data)
{
	pr_err("usage1: echo [r]/[w] LDO_Name > control_regulator\n\r \
		    enable and disable LDO; get LDO current voltage;\n\r \
		    eg: echo W LDO16 0 > control_regulator		:disable LDO16\n\r \
		    echo W LDO16 1 > control_regulator	:enable LDO16\n\r \
		    echo R LDO16 > control_regulator	:get LDO16 voltage\n\r\n\r");
	return 0;
}

static ssize_t dbg_control_regulator_set_value(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	char tmp[128] = {0};
	char ptr[128] = {0};
	char num = 0;
	int i;
	int next_flag = 1;

	if (count > 128) {
		pr_info("error! buffer size big than internal buffer\n");
		return -EFAULT;
	}

	if (copy_from_user(tmp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (tmp[0] == 'R' || tmp[0] == 'r') {
		for (i = 2; i < (count - 1); i++) {
			ptr[i - 2] = tmp[i];
		}
		ptr[i - 2] = '\0';
		get_regulator_state(ptr);
	} else if (tmp[0] == 'W' || tmp[0] == 'w') {
		for (i = 2; i < (count - 1); i++) {
			if (tmp[i] == ' ') {
				next_flag = 0;
				ptr[i - 2] = '\0';
				continue;
			}
			if (next_flag) {
				ptr[i - 2] = tmp[i];
			} else {
				num = tmp[i] - 48;
			}
		}
		set_regulator_state(ptr, num);
	}

	*ppos += count;

	return count;
}

static int dbg_control_regulator_open(struct inode *inode, struct file *file)
{
	file->private_data = inode->i_private;
	return single_open(file, dbg_control_regulator_show, &inode->i_private);
}

static const struct file_operations set_control_regulator_fops = {
	.open		= dbg_control_regulator_open,
	.read		= seq_read,
	.write		= dbg_control_regulator_set_value,
	.llseek		= seq_lseek,
	.release	= single_release,
};
#endif

static struct regulator_init_data *fake_of_get_regulator_init_data(struct device *dev,
                        struct device_node *np)
{
    struct regulator_init_data *init_data = NULL;
    const __be32 *num_consumer_supplies = NULL;
    struct regulator_consumer_supply *consumer_supplies = NULL;
    int consumer_id = 0;

    init_data = devm_kzalloc(dev, sizeof(*init_data), GFP_KERNEL);
    if (!init_data) {
		return NULL;
	}

    init_data->supply_regulator = of_get_property(np,"hisilicon,regulator-supply",NULL);

    num_consumer_supplies = of_get_property(np, "hisilicon,num_consumer_supplies", NULL);
    if((NULL == num_consumer_supplies)||(0 == *num_consumer_supplies)) {
       dev_warn(dev,"%s no consumer_supplies \n",__func__);
       return init_data;
    }

    init_data->num_consumer_supplies = be32_to_cpu(*num_consumer_supplies);
    init_data->consumer_supplies = (struct regulator_consumer_supply *)devm_kzalloc(dev,
    init_data->num_consumer_supplies *sizeof(struct regulator_consumer_supply),GFP_KERNEL);
    if(NULL == init_data->consumer_supplies) {
        dev_err(dev,"%s devm_kzalloc consumer_supplies err\n",__func__);
        return NULL;
    }

    consumer_supplies = init_data->consumer_supplies ;

    for(consumer_id = 0;consumer_id < init_data->num_consumer_supplies;consumer_id++,consumer_supplies++)
    {
        int ret = of_property_read_string_index(np,"hisilicon,consumer-supplies",consumer_id,&consumer_supplies->supply);
        if(ret) {
            dev_err(dev,"\n %s %s of_property_read_string_index consumer-supplies err\n",__func__,np->name);
        }
    }

	return init_data;
}

static int fake_of_get_regulator_constraint(struct regulation_constraints *constraints,
						struct device_node *np)
{
	const __be32 *min_uV, *max_uV;
	unsigned int *valid_modes_mask;
	unsigned int *valid_ops_mask;
	unsigned int *initial_mode;

	if ((!np) || (!constraints)) {
		return -1;
	}

    (constraints)->name = of_get_property(np, "regulator-name", NULL);

	min_uV = of_get_property(np, "regulator-min-microvolt", NULL);
	if (min_uV) {
		(constraints)->min_uV = be32_to_cpu(*min_uV);
		(constraints)->min_uA = be32_to_cpu(*min_uV);
	}

	max_uV = of_get_property(np, "regulator-max-microvolt", NULL);
	if (max_uV) {
		(constraints)->max_uV = be32_to_cpu(*max_uV);
		(constraints)->max_uA = be32_to_cpu(*max_uV);
	}

	valid_modes_mask = (unsigned int *)of_get_property(np, "hisilicon,valid-modes-mask", NULL);
	if (valid_modes_mask) {
		(constraints)->valid_modes_mask = be32_to_cpu(*valid_modes_mask);
	}

	valid_ops_mask = (unsigned int *)of_get_property(np, "hisilicon,valid-ops-mask", NULL);
	if (valid_ops_mask) {
		(constraints)->valid_ops_mask = be32_to_cpu(*valid_ops_mask);
	}

    initial_mode = (unsigned int *)of_get_property(np, "hisilicon,initial-mode", NULL);
	if (initial_mode) {
		(constraints)->initial_mode = be32_to_cpu(*initial_mode);
	}

	(constraints)->always_on = !!(of_find_property(np, "regulator-always-on", NULL));
    (constraints)->boot_on = !!(of_find_property(np, "regulator-boot-on", NULL));

	return 0;
}

static int fake_of_get_regulator_sreg(struct hisi_charger_regulator * sreg,struct device *dev,
						struct device_node *np)
{
	int *vol_numb;
    unsigned int *off_on_delay;
    enum hisi_charger_regulator_type *regulator_type;
    const char *status = NULL;
	unsigned int *vset_table = NULL;
	int *regulator_id;

    status = of_get_property(np, "hisilicon,regulator-status", NULL);
    if (status) {
		sreg->status = !(strcmp(status,"okey"));
	}

    regulator_type = (enum hisi_charger_regulator_type *)of_get_property(np, "hisilicon,regulator-type", NULL);
    if (regulator_type) {
		sreg->type = be32_to_cpu(*regulator_type);
	}

    off_on_delay = (unsigned int *)of_get_property(np, "hisilicon,off-on-delay", NULL);
	if (off_on_delay) {
		sreg->off_on_delay = be32_to_cpu(*off_on_delay);
	}

    (void)of_property_read_u32_array(np,"hisilicon,ctrl-regs", (unsigned int *)(&sreg->ctrl_regs),0x3);
    (void)of_property_read_u32_array(np,"hisilicon,ctrl-data", (unsigned int *)(&sreg->ctrl_data),0x2);
    (void)of_property_read_u32_array(np,"hisilicon,vset-regs", (unsigned int *)(&sreg->vset_regs),0x1);
    (void)of_property_read_u32_array(np,"hisilicon,vset-data", (unsigned int *)(&sreg->vset_data),0x2);

    vol_numb = (int *)of_get_property(np, "hisilicon,regulator-n-vol", NULL);
	if (vol_numb) {
		sreg->vol_numb = be32_to_cpu(*vol_numb);
	}

	regulator_id =(int *)of_get_property(np, "hisilicon,hisi-scharger-regulator-id",NULL);
	if (regulator_id) {
		sreg->regulator_id =  be32_to_cpu(*regulator_id);
	}

    /*
     * for the mem bug,if vset number > 8,stack will over
     * actual only buck2.return ok.

	if (sreg->vol_numb == (int)64){
        sreg->vset_table = scharger_pmic_get_buck_vol_table(2);
        return 0;
	}
    */
    vset_table = devm_kzalloc(dev, sreg->vol_numb * sizeof(int), GFP_KERNEL);
	if (!vset_table){
		return -1;
	}

    (void)of_property_read_u32_array(np,"hisilicon,vset-table", (unsigned int *)vset_table,sreg->vol_numb);
	sreg->vset_table = vset_table;

	return 0;
}

static int hisi_charger_regulator_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct regulator_dev *rdev = NULL;
	struct regulator_desc *rdesc = NULL;
	struct hisi_charger_regulator *sreg = NULL;
	struct regulator_init_data *initdata = NULL;
	const struct of_device_id *match = NULL;
	const struct hisi_charger_regulator *template = NULL;
	struct regulator_config config = { };

#if 0 // def CONFIG_DEBUG_FS
	struct dentry *d;
	static int debugfs_flag;
#endif

	/* to check which type of regulator this is */
	match = of_match_device(of_hisi_regulator_scharger_match_tbl, &pdev->dev);
	if (NULL == match) {
		pr_err("of match scharger regulator fail!\n\r");
		return -EINVAL;
	}
	/*tempdev is regulator device*/
	template = match->data;

    /*
     *initdata mem will release auto;
     *this is kernel 3.10 import.
     */

    /*just for getting "std regulator node" value-key about constraint*/
    initdata = fake_of_get_regulator_init_data(dev,np);
	if (!initdata){
		pr_err("get regulator init data error !\n");
		return -EINVAL;
	}

	ret = fake_of_get_regulator_constraint(&initdata->constraints,np);
	if (!!ret){
		pr_err("get regulator constraint error !\n");
		return -EINVAL;
	}

	/* TODO:scharger regulator supports two modes */
	sreg = kmemdup(template, sizeof(*sreg), GFP_KERNEL);
	if (!sreg)
		return -ENOMEM;

    if(0 != fake_of_get_regulator_sreg(sreg,dev,np)){
	    kfree(sreg);
		return -EINVAL;
    }

	rdesc = &sreg->rdesc;
	rdesc->n_voltages = sreg->vol_numb;
	rdesc->name = initdata->constraints.name;
	rdesc->id = sreg->regulator_id;
	rdesc->min_uV = initdata->constraints.min_uV;

	/*just for skeleton for future*/
#if 0
	ret = sreg->dt_parse(sreg, pdev);
	if (ret) {
		pr_err("device tree parameter parse error!\n");
		goto hisi_charger_probe_end;
	}
#endif
	/* to parse device tree data for regulator specific */
	config.dev = &pdev->dev;
	config.init_data = initdata;
	config.driver_data = sreg;
	config.of_node = pdev->dev.of_node;

	/* register regulator */
	rdev = regulator_register(rdesc, &config);
	if (IS_ERR(rdev)) {
		pr_err("regulator failed to register %s\n", rdesc->name);
		ret = PTR_ERR(rdev);
		//goto hisi_charger_probe_end;
		return -EINVAL;
	}

	platform_set_drvdata(pdev, rdev);
    regulator_has_full_constraints();

#if 0 //def CONFIG_DEBUG_FS
	if (debugfs_flag == 0) {
		d = debugfs_create_dir("hisi_charger_regulator_debugfs", NULL);
		if (!d) {
			pr_err("failed to create scharger regulator debugfs dir !\n");
			ret = -ENOMEM;
			goto hisi_charger_probe_fail;
		}
		(void) debugfs_create_file("regulator_state", S_IRUSR,
						d, NULL, &debug_regulator_state_fops);

		(void) debugfs_create_file("control_regulator", S_IRUSR,
						d, NULL, &set_control_regulator_fops);
		debugfs_flag = 1;
	}

hisi_charger_probe_fail:
	if (ret)
		regulator_unregister(rdev);

hisi_charger_probe_end:
	if (ret)
		kfree(sreg);
#endif

	return ret;
}

static int hisi_charger_regulator_remove(struct platform_device *pdev)
{
	return 0;
}


static struct platform_driver hisi_charger_regulator_driver = {
	.driver = {
		.name	= "hisi_charger_regulator",
		.owner  = THIS_MODULE,
		.of_match_table = of_hisi_regulator_scharger_match_tbl,
	},
	.probe	= hisi_charger_regulator_probe,
	.remove	= hisi_charger_regulator_remove,
};

static int __init hisi_charger_regulator_init(void)
{
	/*if there is some adapt layers so must be add its init-function*/
	return platform_driver_register(&hisi_charger_regulator_driver);
}

static void __exit hisi_charger_regulator_exit(void)
{
	platform_driver_unregister(&hisi_charger_regulator_driver);
}

fs_initcall(hisi_charger_regulator_init);
module_exit(hisi_charger_regulator_exit);

MODULE_AUTHOR("Dongbin Yu <yudongbin@huawei.com>");
MODULE_DESCRIPTION("Hisi hisi_charger regulator driver");
MODULE_LICENSE("GPL v2");
