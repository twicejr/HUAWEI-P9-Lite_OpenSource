#include <linux/usb.h>
#include <linux/debugfs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

/* buffer for write cmd to debugfs node */
char _debug_write_buf[PAGE_SIZE];

/* charger debugfs interface */
ssize_t hiusb_do_charger_show(void *dev_p, char *buf, size_t len);
ssize_t hiusb_do_charger_store(void *dev_p, const char *buf, size_t size);

/* cat charger interface */
static int hiusb_charger_show(struct seq_file *s, void *d)
{
	void *usbdev = s->private;
	char *buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	int alen  = 0;

	/* Show charger info to buf */
	alen = hiusb_do_charger_show(usbdev, buf, PAGE_SIZE);

	/* write buf to user */
	seq_write(s, buf, alen);

	kfree(buf);

	return 0;
}

int hiusb_debug_charger_open(struct inode *inode, struct file *file)
{
	return single_open(file, hiusb_charger_show, inode->i_private);
}

ssize_t hiusb_debug_charger_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	return seq_read(file, buf, size, ppos);
}

/* echo "xx" > charger interface */
ssize_t hiusb_debug_charger_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	void *usbdev = ((struct seq_file *)file->private_data)->private;

	if (size >= PAGE_SIZE) {
		printk(KERN_ERR "set charger type cmd too long!\n");
		return -ENOMEM;
	}

	if (copy_from_user(_debug_write_buf, buf, size)) {
		printk(KERN_ERR "[USB.ERROR] Can't get user data!\n");
		return -ENOSPC;
	}
	_debug_write_buf[size] = '\0';

	printk(KERN_ERR "[USB.DBGFS]use debug interface change charger type:(%s)\n", _debug_write_buf);

	hiusb_do_charger_store(usbdev, _debug_write_buf, size);

	return size;
}

int hiusb_debug_charger_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

/* charger files ops */
static const struct file_operations hiusb_debug_charger_fops = {
	.open = hiusb_debug_charger_open,
	.read = hiusb_debug_charger_read,
	.write = hiusb_debug_charger_write,
	.release = hiusb_debug_charger_release,
};

/* eventmask debugfs interface */
ssize_t hiusb_do_eventmask_show(void *dev_data, char *buf, size_t len);
ssize_t hiusb_do_eventmask_store(void *dev_data, const char *buf, size_t size);

/* cat eventmask interface */
static int hiusb_eventmask_show(struct seq_file *s, void *d)
{
	void *usbdev = s->private;
	char *buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	int alen = 0;

	alen = hiusb_do_eventmask_show(usbdev, buf, PAGE_SIZE);
	seq_write(s, buf, alen);

	kfree(buf);

	return 0;
}

int hiusb_debug_eventmask_open(struct inode *inode, struct file *file)
{
	return single_open(file, hiusb_eventmask_show, inode->i_private);
}

ssize_t hiusb_debug_eventmask_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	return seq_read(file, buf, size, ppos);
}

/* echo "xx" >eventmask interface */
ssize_t hiusb_debug_eventmask_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	void *usbdev = ((struct seq_file *)file->private_data)->private;

	if (size >= PAGE_SIZE) {
		printk(KERN_ERR "set charger type cmd too long!\n");
		return -ENOMEM;
	}

	if (copy_from_user(_debug_write_buf, buf, size)) {
		printk(KERN_ERR "[USB.ERROR] Can't get user data!\n");
		return -ENOSPC;
	}
	_debug_write_buf[size] = '\0';

	printk(KERN_ERR "[USB.DBGFS]use debug interface change charger type:(%s)\n", _debug_write_buf);

	hiusb_do_eventmask_store(usbdev, _debug_write_buf, size);

	return size;
}

int hiusb_debug_eventmask_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

/* eventmask file ops */
static const struct file_operations hiusb_debug_eventmask_fops = {
	.open = hiusb_debug_eventmask_open,
	.read = hiusb_debug_eventmask_read,
	.write = hiusb_debug_eventmask_write,
	.release = hiusb_debug_eventmask_release,
};

/* set eye diagram param debugfs interface */
int hiusb_get_eyepattern_param(void *dev_data, char *buf, size_t len);
int hiusb_set_eyepattern_param(void *dev_data, const char *buf, size_t size);

/* cat eyepattern interface */
static int hiusb_eyepattern_param_show(struct seq_file *s, void *d)
{
	void *usbdev = s->private;
	char *buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	int alen = 0;

	alen = hiusb_get_eyepattern_param(usbdev, buf, PAGE_SIZE);
	seq_write(s, buf, alen);

	kfree(buf);
	return 0;
}

int hiusb_debug_eyepattern_param_open(struct inode *inode, struct file *file)
{
	return single_open(file, hiusb_eyepattern_param_show, inode->i_private);
}

ssize_t hiusb_debug_eyepattern_param_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	return seq_read(file, buf, size, ppos);
}

/* echo "xx" > eyepattern interface */
ssize_t hiusb_debug_eyepattern_param_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	void *usbdev = ((struct seq_file *)file->private_data)->private;

	if (size >= PAGE_SIZE) {
		printk(KERN_ERR "set charger type cmd too long!\n");
		return -ENOMEM;
	}

	if (copy_from_user(_debug_write_buf, buf, size)) {
		printk(KERN_ERR "[USB.ERROR] Can't get user data!\n");
		return -ENOSPC;
	}
	_debug_write_buf[size] = '\0';

	printk(KERN_ERR "[USB.DBGFS]use debug interface change charger type:(%s)\n", _debug_write_buf);

	hiusb_set_eyepattern_param(usbdev, _debug_write_buf, size);

	return size;
}

int hiusb_debug_eyepattern_param_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

/* eyepattern file ops */
static const struct file_operations hiusb_debug_eyepattern_fops = {
	.open = hiusb_debug_eyepattern_param_open,
	.read = hiusb_debug_eyepattern_param_read,
	.write = hiusb_debug_eyepattern_param_write,
	.release = hiusb_debug_eyepattern_param_release,
};

/* gadget balong_acm cdev dump debugfs interface */
void hiusb_do_acm_cdev_dump(struct seq_file *s, unsigned int port_num);
static unsigned int g_acm_dump_port = 9;

/* acm_cdev_dump interface
 * dump the info is from balong_acm
 * inherited ecall acm_cdev_dump
 */
int hiusb_acm_cdev_show(struct seq_file *s, void *d)
{
	hiusb_do_acm_cdev_dump(s, g_acm_dump_port);

	return 0;
}

int hiusb_debug_acm_cdev_open(struct inode *inode, struct file *file)
{
	return single_open(file, hiusb_acm_cdev_show, inode->i_private);
}

ssize_t hiusb_debug_acm_cdev_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	return seq_read(file, buf, size, ppos);
}

/*
 * set acm_cdev_dump port
 */
ssize_t hiusb_debug_acm_cdev_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	if (size >= PAGE_SIZE) {
		printk(KERN_ERR "set charger type cmd too long!\n");
		return -ENOMEM;
	}

	if (copy_from_user(_debug_write_buf, buf, size)) {
		printk(KERN_ERR "[USB.ERROR] Can't get user data!\n");
		return -ENOSPC;
	}
	_debug_write_buf[size] = '\0';

	printk(KERN_ERR "[USB.DBGFS]use debug interface change charger type:(%s)\n", _debug_write_buf);

	if (sscanf(buf, "%32d", &g_acm_dump_port) != 1) {
		g_acm_dump_port = (unsigned int)-1;
		return size;
	}

	return size;
}

int hiusb_debug_acm_cdev_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

/* acm_cdev_dump file ops */
static const struct file_operations hiusb_debug_acm_cdev_fops = {
	.open = hiusb_debug_acm_cdev_open,
	.read = hiusb_debug_acm_cdev_read,
	.write = hiusb_debug_acm_cdev_write,
	.release = hiusb_debug_acm_cdev_release,
};

void hiusb_do_acm_cdev_port_dump(struct seq_file *s);

int hiusb_acm_cdev_dump_show(struct seq_file *s, void *d)
{
	hiusb_do_acm_cdev_port_dump(s);
	return 0;
}

int hiusb_debug_acm_cdev_dump_show_open(struct inode *inode, struct file *file)
{
	return single_open(file, hiusb_acm_cdev_dump_show, inode->i_private);
}

ssize_t hiusb_debug_acm_cdev_dump_show_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	return seq_read(file, buf, size, ppos);
}

int hiusb_debug_acm_cdev_dump_show_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

/* acm_cdev_dump_show file ops */
static const struct file_operations hiusb_debug_acm_cdev_dump_show_fops = {
	.open = hiusb_debug_acm_cdev_dump_show_open,
	.read = hiusb_debug_acm_cdev_dump_show_read,
	.release = hiusb_debug_acm_cdev_dump_show_release,
};

/* gadget balong_acm ioctl cdev dump debugfs interface */
int acm_cdev_ioctl_dump(struct seq_file *s);

/* acm_cdev_ioctl dump interface */
int hiusb_acm_cdev_ioctl_show(struct seq_file *s, void *d)
{
	acm_cdev_ioctl_dump(s);

	return 0;
}

int hiusb_debug_acm_cdev_ioctl_open(struct inode *inode, struct file *file)
{
	return single_open(file, hiusb_acm_cdev_ioctl_show, inode->i_private);
}

ssize_t hiusb_debug_acm_cdev_ioctl_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	return seq_read(file, buf, size, ppos);
}

int hiusb_debug_acm_cdev_ioctl_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

/* acm_cdev_ioctl_dump file ops */
static const struct file_operations hiusb_debug_acm_cdev_ioctl_fops = {
	.open = hiusb_debug_acm_cdev_ioctl_open,
	.read = hiusb_debug_acm_cdev_ioctl_read,
	.release = hiusb_debug_acm_cdev_ioctl_release,
};

/* gadget errno dump debugfs interface */
int acm_cdev_errno_dump(struct seq_file *s);

/* errno number to meaning dump interface */
int hiusb_errno_show(struct seq_file *s, void *d)
{
	acm_cdev_errno_dump(s);

	return 0;
}

int hiusb_debug_errno_open(struct inode *inode, struct file *file)
{
	return single_open(file, hiusb_errno_show, inode->i_private);
}

ssize_t hiusb_debug_errno_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	return seq_read(file, buf, size, ppos);
}

int hiusb_debug_errno_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

/* acm_errnor dump file ops */
static const struct file_operations hiusb_debug_acm_errno_fops = {
	.open = hiusb_debug_errno_open,
	.read = hiusb_debug_errno_read,
	.release = hiusb_debug_errno_release,
};

/* f_adb trace debugfs interface */
int dump_adb_trace(struct seq_file *s);

/* show the adb trace interface */
int hiusb_adb_trace_show(struct seq_file *s, void *d)
{
	dump_adb_trace(s);

	return 0;
}

int hiusb_adb_trace_open(struct inode *inode, struct file *file)
{
	return single_open(file, hiusb_adb_trace_show, inode->i_private);
}

ssize_t hiusb_adb_trace_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	return seq_read(file, buf, size, ppos);
}

int hiusb_adb_trace_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

/* adb trace file ops */
static const struct file_operations hiusb_adb_trace_fops = {
	.open = hiusb_adb_trace_open,
	.read = hiusb_adb_trace_read,
	.release = hiusb_adb_trace_release,
};

/* gadget balong_acm cdev dump debugfs interface */
void dump_ether_trace (struct seq_file *s);
void clear_ether_trace(void);

/* rndis dump interface */
int hiusb_ether_show(struct seq_file *s, void *d)
{
	dump_ether_trace(s);

	return 0;
}

int hiusb_ether_open(struct inode *inode, struct file *file)
{
	return single_open(file, hiusb_ether_show, inode->i_private);
}

ssize_t hiusb_ether_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	return seq_read(file, buf, size, ppos);
}

/* clear ether trace log if write */
ssize_t hiusb_ether_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	clear_ether_trace();
	return size;
}

int hiusb_ether_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

/* ether file ops */
static const struct file_operations hiusb_ether_fops = {
	.open = hiusb_ether_open,
	.read = hiusb_ether_read,
	.write = hiusb_ether_write,
	.release = hiusb_ether_release,
};

/* gadget balong_acm cdev dump debugfs interface */
void acm_adp_dump(struct seq_file *s);

/* cat acm_adp interface */
int hiusb_acm_adp_show(struct seq_file *s, void *d)
{
	acm_adp_dump(s);

	return 0;
}

int hiusb_acm_adp_open(struct inode *inode, struct file *file)
{
	return single_open(file, hiusb_acm_adp_show, inode->i_private);
}

ssize_t hiusb_acm_adp_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	return seq_read(file, buf, size, ppos);
}

int hiusb_acm_adp_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

/* acm_adp file ops */
static const struct file_operations hiusb_acm_adp_fops = {
	.open = hiusb_acm_adp_open,
	.read = hiusb_acm_adp_read,
	.release = hiusb_acm_adp_release,
};

/* debugfs interface template file operations */
typedef ssize_t (*hiusb_debug_show_ops)(void *, char *, ssize_t);
typedef ssize_t (*hiusb_debug_store_ops)(void *, const char *, ssize_t);

/* debugfs interface call back data */
struct hiusb_debug_attr {
	void *dev_data;
	hiusb_debug_show_ops show;
	hiusb_debug_store_ops write;
} _hiusb_debug_template;

/* A interface for help creat a debugfs file */
int hiusb_debug_template_show(struct seq_file *s, void *d)
{
	struct hiusb_debug_attr *dattr = s->private;
	void *usbdev = dattr->dev_data;
	char *buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	int alen = 0;

	alen = dattr->show(usbdev, buf, PAGE_SIZE);
	seq_write(s, buf, alen);

	kfree(buf);

	return 0;
}

int hiusb_debug_template_open(struct inode *inode, struct file *file)
{
	return single_open(file, hiusb_debug_template_show, inode->i_private);
}

/* A interface for help creat a debugfs file */
ssize_t hiusb_debug_template_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	struct hiusb_debug_attr *dattr = ((struct seq_file *)file->private_data)->private;
	void *usbdev = dattr->dev_data;

	if (size >= PAGE_SIZE) {
		printk(KERN_ERR "set charger type cmd too long!\n");
		return -ENOMEM;
	}

	if (copy_from_user(_debug_write_buf, buf, size)) {
		printk(KERN_ERR "[USB.ERROR] Can't get user data!\n");
		return -ENOSPC;
	}
	_debug_write_buf[size] = '\0';

	printk(KERN_ERR "[USB.DBGFS]use debug interface change charger type:(%s)\n", _debug_write_buf);

	dattr->write(usbdev, _debug_write_buf, size);

	return size;
}

static const struct file_operations hiusb_debug_template_fops = {
	.open = hiusb_debug_template_open,
	.read = seq_read,
	.write = hiusb_debug_template_write,
	.release = single_release,
};

struct dentry *hiusb_debug_root;
EXPORT_SYMBOL_GPL(hiusb_debug_root);

struct dentry *hiusb_debug_gadget;
EXPORT_SYMBOL_GPL(hiusb_debug_gadget);

/* register file show & store */
void hiusb_debug_quick_register(void *dev_data, hiusb_debug_show_ops show, hiusb_debug_store_ops store)
{
	if (_hiusb_debug_template.dev_data) {
		printk(KERN_ERR "[USB.DBGFS] Can't register quick node!\n");
		return;
	}

	_hiusb_debug_template.dev_data = dev_data;
	_hiusb_debug_template.show = show;
	_hiusb_debug_template.write = store;
}

/* hisi usb debugfs sys init */
void hiusb_debug_init(void *dev_data)
{
	hiusb_debug_root = debugfs_create_dir("hiusb", usb_debug_root);
	debugfs_create_file("charger", S_IWUSR | S_IRUSR, hiusb_debug_root, dev_data, &hiusb_debug_charger_fops);
	debugfs_create_file("eventmask", S_IWUSR | S_IRUSR, hiusb_debug_root, dev_data, &hiusb_debug_eventmask_fops);
	debugfs_create_file("eyepattern", S_IWUSR | S_IRUSR, hiusb_debug_root, dev_data, &hiusb_debug_eyepattern_fops);

	if (_hiusb_debug_template.dev_data) {
		debugfs_create_file("fakecharger", S_IWUSR | S_IRUSR, hiusb_debug_root, &_hiusb_debug_template, &hiusb_debug_template_fops);
	}

	hiusb_debug_gadget = debugfs_create_dir("gadget", hiusb_debug_root);
	debugfs_create_file("acm_cdev_dump", S_IWUSR | S_IRUSR, hiusb_debug_gadget, dev_data, &hiusb_debug_acm_cdev_fops);
	debugfs_create_file("acm_cdev_dump_show", S_IWUSR | S_IRUSR, hiusb_debug_gadget, dev_data, &hiusb_debug_acm_cdev_dump_show_fops);
	debugfs_create_file("acm_ioctl_dump", S_IWUSR | S_IRUSR, hiusb_debug_gadget, dev_data, &hiusb_debug_acm_cdev_ioctl_fops);
	debugfs_create_file("acm_errno_dump", S_IWUSR | S_IRUSR, hiusb_debug_gadget, dev_data, &hiusb_debug_acm_errno_fops);
	debugfs_create_file("adb_trace", S_IWUSR | S_IRUSR, hiusb_debug_gadget, dev_data, &hiusb_adb_trace_fops);
	debugfs_create_file("ether", S_IWUSR | S_IRUSR, hiusb_debug_gadget, dev_data, &hiusb_ether_fops);
	debugfs_create_file("acm_adp_dump", S_IWUSR | S_IRUSR, hiusb_debug_gadget, dev_data, &hiusb_acm_adp_fops);
}
