#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/hisi/hi64xx/hi64xx_utils.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#endif

#define SIZE_MAX_HI64xxDUMP            0x5000
#define AUDIO_DEBUG_DIR                "audio"
#define AUDIO_DEBUG_HI64XXdump         "hi64xxdump"

struct dsm_client *dsm_audio_client = NULL;
static struct proc_dir_entry *audio_debug_dir = NULL;
static struct utils_config *s_utils_config = NULL;

extern void hi64xx_resmgr_dump(struct hi64xx_resmgr *resmgr);

int hi64xx_update_bits(struct snd_soc_codec *codec, unsigned int reg,
                unsigned int mask, unsigned int value)
{
	int change;
	unsigned int old, new;

	old = snd_soc_read(codec, reg);
	new = (old & ~mask) | (value & mask);
	change = old != new;
	if (change)
		snd_soc_write(codec, reg, new);

	return change;
}
EXPORT_SYMBOL_GPL(hi64xx_update_bits);

int hi64xx_update_bits_locked(struct snd_soc_codec *codec, unsigned int reg,
                unsigned int mask, unsigned int value)
{
	int change;

	mutex_lock(&codec->mutex);
	change = hi64xx_update_bits(codec, reg, mask, value);
	mutex_unlock(&codec->mutex);

	return change;
}
EXPORT_SYMBOL_GPL(hi64xx_update_bits_locked);

#ifdef CONFIG_DEBUG_FS
#define HI64XX_DBG_PAGES (9)
#define HI64XX_DBG_SIZE_PAGE (0x1000)

/* instruction struct */
struct hi64xx_ins
{
	char ins;		/* w:wirte; r:read; p:read page. */
	u32	reg;
	u32	val;
};
struct hi64xx_ins g_hi64xx_ins;
spinlock_t	hi64xx_ins_lock;
/* g_data */
static struct snd_soc_codec *snd_cdc = NULL;
static struct dentry *debug_dir = NULL;
static struct hi_cdc_ctrl *s_cdc_ctrl = NULL;
static struct hi64xx_resmgr* s_resmgr = NULL;

#define REG_CACHE_NUM_MAX 1024
/* single line max size is
time,w reg val
8(time) +3 +4(reg) +1 +8(val) +1 = 25
min size is
time,r reg
8(time) +3 +4(reg) +1 = 16
so allocate 6 pages(=24K)
*/
#define DBG_SIZE_CACHE (24*REG_CACHE_NUM_MAX)
unsigned int cdc_rr_cache_idx = 0;       /* write/read index to cdc_rr_cache[] */
struct hi64xx_rr_cache {
	unsigned int reg;
	unsigned int val;
	unsigned long time;
};
struct hi64xx_rr_cache cdc_rr_cache[REG_CACHE_NUM_MAX];
spinlock_t hi64xx_rh_lock;
#endif

static ssize_t hi64xx_dump_read(struct file *file, char __user *user_buf,
			size_t count, loff_t *ppos)
{
	char * buf = NULL;
	ssize_t value_ret= 0;

	if (user_buf == NULL) {
		pr_err("%s user_buf is null.\n", __FUNCTION__);
		return -EINVAL;
	}

	hi64xx_resmgr_dump(s_resmgr);
	buf = vmalloc(SIZE_MAX_HI64xxDUMP);
	if (NULL == buf) {
		pr_err("buf NULL!\n");
		return  -ENOMEM;
	}
	memset(buf, 0, SIZE_MAX_HI64xxDUMP);

	if (s_utils_config->hi64xx_dump_reg != NULL) {
		s_utils_config->hi64xx_dump_reg(buf, SIZE_MAX_HI64xxDUMP);
	} else {
		snprintf(buf, SIZE_MAX_HI64xxDUMP, "hi64xx_dump_reg function is null. \n");
	}

	value_ret = simple_read_from_buffer(user_buf, count, ppos, buf, strlen(buf));

	vfree(buf);
	buf = NULL;

	return value_ret;
}

static void hi64xx_remove_audio_debug_procfs(void)
{
	remove_proc_entry(AUDIO_DEBUG_HI64XXdump, audio_debug_dir);
	remove_proc_entry(AUDIO_DEBUG_DIR, 0);
}

#ifdef CONFIG_DEBUG_FS
static ssize_t hi64xx_rr_read(struct file *file, char __user *user_buf,
			size_t count, loff_t *ppos)
{
	int len;
	char *kn_buf = NULL;
	ssize_t byte_read = 0;
	struct hi64xx_ins m_hi64xx_ins;
	spin_lock(&hi64xx_ins_lock);
	m_hi64xx_ins = g_hi64xx_ins;
	spin_unlock(&hi64xx_ins_lock);

	if (NULL == user_buf) {
		pr_err("input error: user_buf is NULL\n");
		return -EINVAL;
	}

	kn_buf = kzalloc(HI64XX_DBG_SIZE_PAGE, GFP_KERNEL);
	if (NULL == kn_buf) {
		pr_err("kn_buf is null\n");
		return -ENOMEM;
	}

	switch(m_hi64xx_ins.ins) {
	case 'r':
		snprintf(kn_buf, HI64XX_DBG_SIZE_PAGE, " %#08x:0x%x\n",
			m_hi64xx_ins.reg, snd_soc_read(snd_cdc, m_hi64xx_ins.reg));
		break;
	case 'w':
		snprintf(kn_buf, HI64XX_DBG_SIZE_PAGE, "write ok.\n");
		break;
	case 'n':
	default:
		snprintf(kn_buf, HI64XX_DBG_SIZE_PAGE, "error parameter.\n");
		break;
	}
	len = strlen(kn_buf);
	snprintf(kn_buf + len, HI64XX_DBG_SIZE_PAGE - len, "<cat end>\n");
	len = strlen(kn_buf);
	snprintf(kn_buf + len, HI64XX_DBG_SIZE_PAGE - len, "\n");

	byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

	kfree(kn_buf);
	kn_buf = NULL;

	return byte_read;
}

static ssize_t hi64xx_rr_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
{
	char *kn_buf = NULL;
	ssize_t byte_writen = 0;
	int num = 0;
	struct hi64xx_ins m_hi64xx_ins;

	if (NULL == user_buf) {
		pr_err("input error: user_buf is NULL\n");
		return -EINVAL;
	}

	memset(&m_hi64xx_ins, 0, sizeof(m_hi64xx_ins));

	kn_buf = kzalloc(HI64XX_DBG_SIZE_PAGE, GFP_KERNEL);
	if (NULL == kn_buf) {
		pr_err("kn_buf is null\n");
		return -EFAULT;
	}

	byte_writen = simple_write_to_buffer(kn_buf, HI64XX_DBG_SIZE_PAGE, ppos, user_buf, count);
	if (byte_writen != count) {
		kfree(kn_buf);
		pr_err("Input param buf read error, return value: %zd\n", byte_writen);
		return -EINVAL;
	}

	switch(kn_buf[0]) {
	case 'w':
		m_hi64xx_ins.ins = 'w';
		num = sscanf(kn_buf, "w 0x%x 0x%x", &m_hi64xx_ins.reg, &m_hi64xx_ins.val);
		if (2 != num) {
			pr_err("%s:wrong parameter for cmd w.\n", __FUNCTION__);
			g_hi64xx_ins.ins = 'n';
			byte_writen = -EINVAL;
			break;
		}
		snd_soc_write(snd_cdc, m_hi64xx_ins.reg, m_hi64xx_ins.val);
		spin_lock(&hi64xx_ins_lock);
		g_hi64xx_ins = m_hi64xx_ins;
		spin_unlock(&hi64xx_ins_lock);
		break;
	case 'r':
		m_hi64xx_ins.ins = 'r';
		num = sscanf(kn_buf, "r 0x%x", &m_hi64xx_ins.reg);
		if (1 != num) {
			pr_err("%s:wrong parameter for cmd r.\n", __FUNCTION__);
			byte_writen = -EINVAL;
			break;
		}
		spin_lock(&hi64xx_ins_lock);
		g_hi64xx_ins = m_hi64xx_ins;
		spin_unlock(&hi64xx_ins_lock);
		break;
	default:
		g_hi64xx_ins.ins = 'n';
		pr_err("%s:unknown cmd.\n", __FUNCTION__);
		byte_writen = -EINVAL;
		break;
	}

	kfree(kn_buf);
	kn_buf = NULL;

	return byte_writen;
}

static const struct file_operations hi64xx_rr_fops = {
	.read = hi64xx_rr_read,
	.write = hi64xx_rr_write,
};

/*
 * record reg write op
 * loop range (0-1023)
 * catch atomic ensured by read/write function
 */
void hi64xx_reg_wr_cache(unsigned int reg, int val)
{
	u64 sec = 0;
	unsigned int idx_wr = cdc_rr_cache_idx;

	idx_wr %= REG_CACHE_NUM_MAX;
	/* highest 16bit is r/w flag */
	cdc_rr_cache[idx_wr].reg = reg;
	cdc_rr_cache[idx_wr].val = val;

	sec = hisi_getcurtime();
	do_div(sec, 1000000000);
	cdc_rr_cache[idx_wr].time = (unsigned long int)sec;
	idx_wr++;
	cdc_rr_cache_idx = idx_wr % REG_CACHE_NUM_MAX;
}

static void hi64xx_reg_history_dp(char *buf)
{
	unsigned int idx_wr_now = 0, idx_wr_latter = 0;
	unsigned int idx = 0, idx_start = 0, idx_stop = 0;
	unsigned int time_next = 0;
	unsigned int reg = 0, val = 0, time = 0;
	int len;
	u64 sec = 0;

	memset(buf, 0, DBG_SIZE_CACHE);
	pr_err("%s(%u) ",__FUNCTION__,__LINE__);
	spin_lock(&hi64xx_rh_lock);
	idx_wr_now = cdc_rr_cache_idx;
	time_next = cdc_rr_cache[(idx_wr_now + 1) % REG_CACHE_NUM_MAX].time;
	spin_unlock(&hi64xx_rh_lock);
	pr_err("%s(%u) ",__FUNCTION__,__LINE__);
	if (idx_wr_now >= REG_CACHE_NUM_MAX) {
		snprintf(buf, DBG_SIZE_CACHE, "rr_idx(%u) err\n", idx_wr_now);
		return;
	}

	if (0 == idx_wr_now) {
		snprintf(buf, DBG_SIZE_CACHE, "no register cached now\n");
		return;
	}

	/* parameters: idx_wr_now */
	sec = hisi_getcurtime();
	do_div(sec, 1000000000);
	snprintf(buf, DBG_SIZE_CACHE, "time=%lu s, idx now=%u, BEGIN\n", (unsigned long int)sec, idx_wr_now);

	/* judge the position of idx in order to loop*/
	if (0 == time_next) {
		idx_start = 0;
		idx_stop = idx_wr_now;
	} else {
		/* loop */
		idx_start = idx_wr_now + 1;
		idx_stop = idx_wr_now + REG_CACHE_NUM_MAX;
	}

	for (idx = idx_start; idx < idx_stop; idx++) {
		spin_lock(&hi64xx_rh_lock);

		reg = cdc_rr_cache[idx % REG_CACHE_NUM_MAX].reg;
		val = cdc_rr_cache[idx % REG_CACHE_NUM_MAX].val;
		time = cdc_rr_cache[idx % REG_CACHE_NUM_MAX].time;
		len = strlen(buf);
		snprintf(buf + len, DBG_SIZE_CACHE - len, "%u  w 0x%04X 0x%02X\n", time, reg, val);
		spin_unlock(&hi64xx_rh_lock);
	}

	/* dump */
	spin_lock(&hi64xx_rh_lock);
	idx_wr_latter = cdc_rr_cache_idx;
	spin_unlock(&hi64xx_rh_lock);
	len = strlen(buf);
	snprintf(buf + len, DBG_SIZE_CACHE - len, "idx=%u -- %u, END\n", idx_wr_now, idx_wr_latter);
}

/*
 * history reg read
 */
static ssize_t hi64xx_rh_read(struct file *file, char __user *user_buf,
				size_t count, loff_t *ppos)
{
	char *kn_buf = NULL;
	ssize_t byte_read = 0;

	if (NULL == user_buf) {
		pr_err("input error: user_buf is NULL\n");
		return -EINVAL;
	}

	kn_buf = kzalloc(DBG_SIZE_CACHE, GFP_KERNEL);
	pr_err("%s(%u) :  enter",__FUNCTION__,__LINE__);

	if (NULL == kn_buf) {
		pr_err("kn_buf is null\n");
		return -ENOMEM;
	}

	hi64xx_reg_history_dp(kn_buf);

	byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

	kfree(kn_buf);
	kn_buf = NULL;

	return byte_read;
}


void hi64xx_dump_debug_info()
{
	hi_cdcctrl_dump(s_cdc_ctrl);
	hi64xx_resmgr_dump(s_resmgr);
}
EXPORT_SYMBOL(hi64xx_dump_debug_info);

static const struct file_operations hi64xx_rh_fops = {
	.read  = hi64xx_rh_read,
};


static ssize_t hi64xx_dump_write(struct file *file,
	const char __user *user_buf, size_t count, loff_t *ppos)
{
	hi64xx_dump_debug_info();
	return count;
}

static const struct file_operations hi64xx_dump_fops = {
	.write = hi64xx_dump_write,
};
#endif

static const struct file_operations hi64xx_dump_proc_ops = {
	.owner = THIS_MODULE,
	.read  = hi64xx_dump_read,
};

int hi64xx_utils_init(struct snd_soc_codec *codec, struct hi_cdc_ctrl *cdc_ctrl, const struct utils_config *config,
	struct hi64xx_resmgr* resmgr)
{
	struct proc_dir_entry * hi64xx_dump = NULL;

	s_utils_config = kzalloc(sizeof(struct utils_config), GFP_KERNEL);
	if (!s_utils_config) {
		pr_err("hi64xx_utils_init: Failed to kzalloc s_utils_config\n");
		goto error_exit;
	}
	memcpy(s_utils_config, config, sizeof(struct utils_config));

	audio_debug_dir = proc_mkdir(AUDIO_DEBUG_DIR, NULL);
	if (!audio_debug_dir) {
		pr_err("hi64xx_utils_init: Failed to create audio debug proc dir\n");
		goto error_exit;
	}
	hi64xx_dump = proc_create(AUDIO_DEBUG_HI64XXdump, S_IRUSR|S_IRGRP, audio_debug_dir, &hi64xx_dump_proc_ops);
	if (!hi64xx_dump) {
		pr_err("hi64xx_utils_init: Failed to create hi64xxdump proc\n");
		remove_proc_entry(AUDIO_DEBUG_DIR, 0);
	}

#ifdef CONFIG_DEBUG_FS
	debug_dir = debugfs_create_dir("hi6402", NULL);
	if (!debug_dir) {
		pr_err("anc_hs: Failed to create hi6402 debugfs dir\n");
		goto debugfs_exit;
	}
#ifdef ENABLE_HI64XX_CODEC_DEBUG
	if (!debugfs_create_file("rr", 0644, debug_dir, NULL, &hi64xx_rr_fops))
		pr_err("hi64xx: Failed to create hi64xx rr debugfs file\n");
#endif
	/* register history */
	if (!debugfs_create_file("rh", 0644, debug_dir, NULL, &hi64xx_rh_fops))
		pr_err("hi64xx: Failed to create hi64xx rh debugfs file\n");

	if (!debugfs_create_file("dump", 0644, debug_dir, NULL, &hi64xx_dump_fops))
		pr_err("hi64xx: Failed to create hi64xx dump debugfs file\n");

	spin_lock_init(&hi64xx_ins_lock);
	spin_lock_init(&hi64xx_rh_lock);
	snd_cdc = codec;
	s_cdc_ctrl = cdc_ctrl;
	s_resmgr = resmgr;
#endif

	return 0;

error_exit:
	if (!s_utils_config) {
		kfree(s_utils_config);
		s_utils_config = NULL;
	}

debugfs_exit:
	return 0;
}
EXPORT_SYMBOL(hi64xx_utils_init);

void hi64xx_utils_deinit(void)
{
	if (!s_utils_config) {
		kfree(s_utils_config);
		s_utils_config = NULL;
	}
	hi64xx_remove_audio_debug_procfs();
}
EXPORT_SYMBOL(hi64xx_utils_deinit);

MODULE_DESCRIPTION("hi64xx util");
MODULE_AUTHOR("liujinhong <liujinhong@hisilicon.com>");
MODULE_LICENSE("GPL");
