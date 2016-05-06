
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/debugfs.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include "inputhub_route.h"
#include "protocol.h"

#include <linux/proc_fs.h>


#include <linux/mm.h>
#include <linux/tty.h>
#include <linux/tty_driver.h>
#include <linux/console.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/nmi.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/interrupt.h>			/* For in_interrupt() */
#include <linux/delay.h>
#include <linux/smp.h>
#include <linux/security.h>
#include <linux/bootmem.h>
#include <linux/memblock.h>
#include <linux/aio.h>
#include <linux/syscalls.h>
#include <linux/kexec.h>
#include <linux/kdb.h>
#include <linux/ratelimit.h>
#include <linux/kmsg_dump.h>
#include <linux/syslog.h>
#include <linux/cpu.h>
#include <linux/notifier.h>
#include <linux/rculist.h>
#include <linux/poll.h>
#include <linux/irq_work.h>
#include <linux/utsname.h>
#include <linux/delay.h>

struct iom3_log {
	u32 ts_nsec;		/* timestamp in nanoseconds */
	u16 len;		/* length of entire record */
	u16 text_len;		/* length of text buffer */
	u8 level;		/* syslog level */
};

#define IOM3_LOG_LINE_MAX  	200
#define IOM3_PREFIX_MAX		30

/* record buffer */
#if defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
#define LOG_ALIGN 4
#else
#define LOG_ALIGN __alignof__(struct iom3_log)
#endif

#define IOM3_LOG_BUF_SHIFT 		20
#define __LOG_BUF_LEN (1 << IOM3_LOG_BUF_SHIFT)
static char __iom3_log_buf[__LOG_BUF_LEN] __aligned(LOG_ALIGN);
static char *iom3_log_buf = __iom3_log_buf;
static u32 iom3_log_buf_len = __LOG_BUF_LEN;

static u64 iom3_log_first_seq;
static u32 iom3_log_first_idx;

static u64 iom3_log_next_seq;
static u32 iom3_log_next_idx;

static DEFINE_RAW_SPINLOCK(iom3_logbuf_lock);

DECLARE_WAIT_QUEUE_HEAD(iom3_log_wait);

static u64 iom3_syslog_seq;
static u32 iom3_syslog_idx;
static bool iom3_syslog_prev;
static size_t iom3_syslog_partial;

static u32 iom3_log_next(u32 idx)
{
	struct iom3_log *msg = (struct iom3_log *)(iom3_log_buf + idx);

	if (!msg->len) {
		msg = (struct iom3_log *)iom3_log_buf;
		return msg->len;
	}
	return idx + msg->len;
}

static char *iom3_log_text(const struct iom3_log *msg)
{
	return (char *)msg + sizeof(struct iom3_log);
}

static struct iom3_log *iom3_log_from_idx(u32 idx)
{
	struct iom3_log *msg = (struct iom3_log *)(iom3_log_buf + idx);

	/*
	 * A length == 0 record is the end of buffer marker. Wrap around and
	 * read the message at the start of the buffer.
	 */
	if (!msg->len)
		return (struct iom3_log *)iom3_log_buf;
	return msg;
}

void iom3_log_store(int level, u32 ts_nsec, const char *text, u16 text_len)
{
	struct iom3_log *msg;
	u32 size, pad_len;

	size = sizeof(struct iom3_log) + text_len;
	pad_len = (-size) & (LOG_ALIGN - 1);
	size += pad_len;
	raw_spin_lock(&iom3_logbuf_lock);
	while (iom3_log_first_seq < iom3_log_next_seq) {
		u32 free;

		if (iom3_log_next_idx > iom3_log_first_idx)
			free = max(iom3_log_buf_len - iom3_log_next_idx, iom3_log_first_idx);
		else
			free = iom3_log_first_idx - iom3_log_next_idx;

		if (free > size + sizeof(struct iom3_log))
			break;

		iom3_log_first_idx = iom3_log_next(iom3_log_first_idx);
		iom3_log_first_seq++;
	}

	if (iom3_log_next_idx + size + sizeof(struct iom3_log) >= iom3_log_buf_len) {
		memset(iom3_log_buf + iom3_log_next_idx, 0, sizeof(struct iom3_log));
		iom3_log_next_idx = 0;
	}

	msg = (struct iom3_log *)(iom3_log_buf + iom3_log_next_idx);
	memcpy(iom3_log_text(msg), text, text_len);
	msg->text_len = text_len;
	msg->level = level & 7;
	msg->ts_nsec = ts_nsec;
	msg->len = sizeof(struct iom3_log) + text_len + pad_len;

	iom3_log_next_idx += msg->len;
	iom3_log_next_seq++;
	raw_spin_unlock(&iom3_logbuf_lock);
	wake_up_interruptible(&iom3_log_wait);
}

static size_t iom3_msg_print_text(const struct iom3_log *msg, bool partial, char *buf)
{
	const char *text = iom3_log_text(msg);
	size_t text_size = msg->text_len;
	size_t len = 0;

	if (buf) {
		if (!partial)
			len += snprintf(buf, 30, "<%d>[iom3][%10d]", msg->level, msg->ts_nsec);
		memcpy(buf + len, text, text_size);
		len += text_size;
	}
	return len;
}
static int iom3_log_print(char __user *buf, int size)
{
	char *text;
	struct iom3_log *msg;
	int len = 0;
	text = kmalloc(IOM3_LOG_LINE_MAX + IOM3_PREFIX_MAX, GFP_KERNEL);
	if (!text)
		return -ENOMEM;
	while (size > 0) {
		size_t n;
		size_t skip;

		raw_spin_lock_irq(&iom3_logbuf_lock);
		if (iom3_syslog_seq < iom3_log_first_seq) {
			/* messages are gone, move to first one */
			iom3_syslog_seq = iom3_log_first_seq;
			iom3_syslog_idx = iom3_log_first_idx;
			iom3_syslog_prev = 0;
			iom3_syslog_partial = 0;
		}
		if (iom3_syslog_seq == iom3_log_next_seq) {
			raw_spin_unlock_irq(&iom3_logbuf_lock);
			break;
		}
		skip = iom3_syslog_partial;
		msg = iom3_log_from_idx(iom3_syslog_idx);
		n = iom3_msg_print_text(msg, iom3_syslog_prev, text);
		if (n - iom3_syslog_partial <= size) {
			iom3_syslog_idx = iom3_log_next(iom3_syslog_idx);
			iom3_syslog_seq++;
			iom3_syslog_prev = 0;
			n -= iom3_syslog_partial;
			iom3_syslog_partial = 0;
		} else if (!len){
			n = size;
			iom3_syslog_partial += n;
			iom3_syslog_prev = 1;
		} else
			n = 0;
		raw_spin_unlock_irq(&iom3_logbuf_lock);

		if (!n)
			break;

		if (copy_to_user(buf, text + skip, n)) {
			if (!len){
				len = -EFAULT;
			}
			break;
		}
		len += n;
		size -= n;
		buf += n;
	}

	kfree(text);
	return len;
}

static ssize_t iom3_msg_read(struct file *file, char __user *buf,
			 size_t count, loff_t *ppos)
{
	int error = -EINVAL;
	if (!buf)
		goto out;
	if (!count)
		goto out;
	if (!access_ok(VERIFY_WRITE, buf, count)) {
		error = -EFAULT;
		goto out;
	}
	error = wait_event_interruptible(iom3_log_wait,
				iom3_syslog_seq != iom3_log_next_seq);
	if (error)
		goto out;
	return iom3_log_print(buf, count);
out:
	return error;
}


static const struct file_operations proc_iom3_kmsg_operations = {
	.read		= iom3_msg_read,
};


static int __init proc_iom3_msg_init(void)
{
	proc_create("iom3msg", S_IRUSR, NULL, &proc_iom3_kmsg_operations);
	return 0;
}
module_init(proc_iom3_msg_init);


#define LOG_CHANNEL_MIN (0)
#define LOG_CHANNEL_MAX (3)

enum
{
    LOG_NO=0,
    LOG_AP=1,
    LOG_UART=2,
    LOG_BOTH=3,
};

enum {
	CONFIG_LEVEL = 1,
	CONFIG_CHANNEL,
	CONFIG_NMI,
	CONFIG_NUM,
};

struct dentry *sensorhub_debugfs_root;
int module_val;
int loglevel_val = LOG_LEVEL_DEBUG;
int channel_val  = LOG_AP;
static int mcu_static_level = LOG_LEVEL_DEBUG;

//extern static int inputhub_mcu_write_cmd(const void *buf, unsigned long length);
extern int set_log_config(uint8_t type, uint8_t val);
#if 0
static ssize_t sensorhub_query_read(struct file *filp,  char  __user *buffer, size_t count, loff_t *ppos)
{
	int len = 0;
	char buf[3];
	memset(buf, 0, sizeof(buf));

	len = snprintf(buf, 2, "%d\n", module_val);
	return simple_read_from_buffer(buffer, count, ppos, (void *)buf, len);
}
#endif
extern void hisi_rdr_nmi_notify_iom3(void);
static ssize_t sensorhub_query_write(struct file *file, const char __user *ubuf,
						size_t count, loff_t *ppos)
{
	char buf[3];
	int result;

	memset(buf, 0, sizeof(buf));

	if (copy_from_user(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		return -EFAULT;

	if(buf[0] < '0' || buf[0] > '9' || buf[1] != '\n')
		return -EINVAL;

    result = buf[0] - '0';

    if (result == 1)
    {
        set_log_config(CONFIG_NMI,0);
#if 0
        hisi_rdr_nmi_notify_iom3();
#endif
    }
    else
    {
        return -EINVAL;
    }

    return count;
}

static ssize_t sensorhub_loglevel_read(struct file *filp,  char  __user *buffer, size_t count, loff_t *ppos)
{
	int len = 0;
	char buf[3];
	memset(buf, 0, sizeof(buf));

	len = snprintf(buf, 2, "%d\n", loglevel_val);
	return simple_read_from_buffer(buffer, count, ppos, (void *)buf, len);
}

static ssize_t sensorhub_loglevel_write(struct file *file, const char __user *ubuf,
						size_t count, loff_t *ppos)
{
	char buf[3];
	int result, ret;

	memset(buf, 0, sizeof(buf));

	if (copy_from_user(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		return -EFAULT;

	if(buf[0] < '0' || buf[0] > '9' || buf[1] != '\n')
		return -EINVAL;
	result = buf[0] - '0';

    hwlog_debug( "result=%d\n", result);
	if(result < LOG_LEVEL_FATAL)
	{
		hwlog_err( "loglevel must greater than %d\n",LOG_LEVEL_FATAL);
		return -EINVAL;
	}
	else if(result > mcu_static_level){
		hwlog_err( "loglevel must smaller than %d\n",mcu_static_level);
		return -EINVAL;
	}
	else if(result < LOG_LEVEL_ERR)
	{
		result = LOG_LEVEL_FATAL;
	}
	else if(result < LOG_LEVEL_WARNING)
	{
		result = LOG_LEVEL_ERR;
	}
	else if(result < LOG_LEVEL_INFO)
	{
		result = LOG_LEVEL_WARNING;
	}
	else if(result < LOG_LEVEL_DEBUG)
	{
		result = LOG_LEVEL_INFO;
	}
	else{
		result = LOG_LEVEL_DEBUG;
	}
	ret = set_log_config(CONFIG_LEVEL, result);
	if(ret < 0){
		hwlog_err( "set_log_config failed\n");
		return ret;
	}
	loglevel_val = result;

	return count;
}


static ssize_t sensorhub_channel_read(struct file *filp,  char  __user *buffer, size_t count, loff_t *ppos)
{
	int len = 0;
	char buf[3];
	memset(buf, 0, sizeof(buf));

	len = snprintf(buf, 2, "%d\n", channel_val);
	return simple_read_from_buffer(buffer, count, ppos, (void *)buf, len);
}

static ssize_t sensorhub_channel_write(struct file *file, const char __user *ubuf,
						size_t count, loff_t *ppos)
{
	char buf[3];
	int result, ret;
	memset(buf, 0, sizeof(buf));

	if (copy_from_user(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		return -EFAULT;

	if(buf[0] < '0' || buf[0] > '9' || buf[1] != '\n')
		return -EINVAL;
	result = buf[0] - '0';

	hwlog_debug( "result=%d\n",result);
	if(result < LOG_CHANNEL_MIN || result > LOG_CHANNEL_MAX)
	{
		hwlog_err( "illegal input\n");
		return -EINVAL;
	}
	ret = set_log_config(CONFIG_CHANNEL, result);
	if(ret){
		hwlog_err( "set_log_config failed\n");
		return ret;
	}
	channel_val = result;

	return count;
}


static const struct file_operations sensorhub_query_fops = {
	.write = sensorhub_query_write,
};

static const struct file_operations sensorhub_loglevel_fops = {
	.read = sensorhub_loglevel_read,
	.write= sensorhub_loglevel_write,
};

static const struct file_operations sensorhub_channel_fops = {
	.read = sensorhub_channel_read,
	.write = sensorhub_channel_write,
};

int  __init sensorhub_debugfs_init(void)
{
	struct dentry *query_file, *loglevel_file, *channel_file;
	sensorhub_debugfs_root = debugfs_create_dir("sensorhub", NULL);
	if (!sensorhub_debugfs_root){
		hwlog_err( "create sensorhub debugfs failed\n");
		return -ENOENT;
	}

	query_file = debugfs_create_file("query", 0200, sensorhub_debugfs_root, NULL, &sensorhub_query_fops);
	if(!query_file){
		hwlog_err( "create sensorhub_query file failed\n");
	}
	loglevel_file = debugfs_create_file("loglevel", 0664, sensorhub_debugfs_root, NULL, &sensorhub_loglevel_fops);
	if(!loglevel_file){
		hwlog_err( "create sensorhub loglevel_file failed\n");
	}
	channel_file = debugfs_create_file("logchannel", 0664, sensorhub_debugfs_root, NULL, &sensorhub_channel_fops);
	if(!channel_file){
		hwlog_err( "create sensorhub channel_file failed\n");
	}
	return 0;
}

late_initcall(sensorhub_debugfs_init);
