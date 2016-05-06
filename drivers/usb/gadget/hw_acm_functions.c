#define HW_MAX_ACM_INSTANCES 4
struct hw_acm_function_config {
	int instances;
	int instances_on;
	struct usb_function *f_acm[HW_MAX_ACM_INSTANCES];
	struct usb_function_instance *f_acm_inst[HW_MAX_ACM_INSTANCES];
};

static int
hw_acm_function_init(struct android_usb_function *f,
		struct usb_composite_dev *cdev)
{
	int i;
	int ret;
	struct hw_acm_function_config *config;

	config = kzalloc(sizeof(struct hw_acm_function_config), GFP_KERNEL);
	if (!config)
		return -ENOMEM;
	f->config = config;

	for (i = 0; i < HW_MAX_ACM_INSTANCES; i++) {
		config->f_acm_inst[i] = usb_get_function_instance("hw_acm");
		if (IS_ERR(config->f_acm_inst[i])) {
			ret = PTR_ERR(config->f_acm_inst[i]);
			goto err_usb_get_function_instance;
		}
		config->f_acm[i] = usb_get_function(config->f_acm_inst[i]);
		if (IS_ERR(config->f_acm[i])) {
			ret = PTR_ERR(config->f_acm[i]);
			goto err_usb_get_function;
		}
	}
	return 0;
err_usb_get_function_instance:
	while (i-- > 0) {
		usb_put_function(config->f_acm[i]);
err_usb_get_function:
		usb_put_function_instance(config->f_acm_inst[i]);
	}
	return ret;
}

static void hw_acm_function_cleanup(struct android_usb_function *f)
{
	int i;
	struct hw_acm_function_config *config = f->config;

	for (i = 0; i < HW_MAX_ACM_INSTANCES; i++) {
		usb_put_function(config->f_acm[i]);
		usb_put_function_instance(config->f_acm_inst[i]);
	}
	kfree(f->config);
	f->config = NULL;
}

static int
hw_acm_function_bind_config(struct android_usb_function *f,
		struct usb_configuration *c)
{
	int i;
	int ret = 0;
	struct hw_acm_function_config *config = f->config;

	config->instances_on = config->instances;
	for (i = 0; i < config->instances_on; i++) {
		ret = usb_add_function(c, config->f_acm[i]);
		if (ret) {
			pr_err("Could not bind acm%u config\n", i);
			goto err_usb_add_function;
		}
	}

	return 0;

err_usb_add_function:
	while (i-- > 0)
		usb_remove_function(c, config->f_acm[i]);
	return ret;
}

/*
static void hw_acm_function_unbind_config(struct android_usb_function *f,
				       struct usb_configuration *c)
{
	int i;
	struct hw_acm_function_config *config = f->config;

	for (i = 0; i < config->instances_on; i++)
		usb_remove_function(c, config->f_acm[i]);
}
*/

static ssize_t hw_acm_instances_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct hw_acm_function_config *config = f->config;
	return sprintf(buf, "%d\n", config->instances);
}

static ssize_t hw_acm_instances_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct hw_acm_function_config *config = f->config;
	int value;

	sscanf(buf, "%d", &value);
	if (value > HW_MAX_ACM_INSTANCES)
		value = HW_MAX_ACM_INSTANCES;
	config->instances = value;
	return size;
}

static DEVICE_ATTR(hw_instances, S_IRUGO | S_IWUSR, hw_acm_instances_show,
						 hw_acm_instances_store);
static struct device_attribute *hw_acm_function_attributes[] = {
	&dev_attr_hw_instances,
	NULL
};

static struct android_usb_function hw_acm_function = {
	.name		= "hw_acm",
	.init		= hw_acm_function_init,
	.cleanup	= hw_acm_function_cleanup,
	.bind_config	= hw_acm_function_bind_config,
//	.unbind_config	= hw_acm_function_unbind_config,
	.attributes	= hw_acm_function_attributes,
};
