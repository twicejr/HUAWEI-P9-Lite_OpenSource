/*
 * Block driver for media (i.e., flash cards)
 *
 * Copyright 2002 Hewlett-Packard Company
 * Copyright 2005-2008 Pierre Ossman
 *
 * Use consistent with the GNU GPL is permitted,
 * provided that this copyright notice is
 * preserved in its entirety in all copies and derived works.
 *
 * HEWLETT-PACKARD COMPANY MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,
 * AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS
 * FITNESS FOR ANY PARTICULAR PURPOSE.
 *
 * Many thanks to Alessandro Rubini and Jonathan Corbet!
 *
 * Author:  Andrew Christian
 *          28 May 2002
 */
#include <linux/moduleparam.h>
#include <linux/module.h>
#include <linux/init.h>

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/hdreg.h>
#include <linux/kdev_t.h>
#include <linux/blkdev.h>
#include <linux/mutex.h>
#include <linux/scatterlist.h>
#include <linux/string_helpers.h>
#include <linux/delay.h>
#include <linux/capability.h>
#include <linux/compat.h>
#include <linux/syscalls.h>
#include <linux/proc_fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

#include <linux/mmc/core.h>
#include <linux/pm_runtime.h>
#include <linux/ioprio.h>

#define CREATE_TRACE_POINTS
#include <trace/events/mmc.h>

#include <linux/mmc/ioctl.h>
#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/rpmb.h>
#include <linux/mmc/sd.h>
#include <linux/mmc/ffu.h>

#include <asm/uaccess.h>

#include "queue.h"

#include "hisi_partition.h"
#ifdef CONFIG_HW_SD_HEALTH_DETECT
#include "mmc_health_diag.h"
#endif

#ifdef CONFIG_HUAWEI_SDCARD_DSM
#include <linux/mmc/dsm_sdcard.h>
#endif
#ifdef CONFIG_HUAWEI_EMMC_DSM
#include <linux/mmc/dsm_emmc.h>

struct dsm_dev dsm_emmc = {
	.name = "dsm_emmc",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = NULL,
	.buff_size = EMMC_DSM_BUFFER_SIZE,
};
struct dsm_client *emmc_dclient = NULL;

/*the buffer which transffering to device radar*/
struct emmc_dsm_log g_emmc_dsm_log;

EXPORT_SYMBOL(emmc_dclient);
#endif
MODULE_ALIAS("mmc:block");
/*not referenced,modified for pclint*/
/*
#ifdef MODULE_PARAM_PREFIX
#undef MODULE_PARAM_PREFIX
#endif
#define MODULE_PARAM_PREFIX "mmcblk."
*/
#ifdef CONFIG_BALONG_MTD
enum{
	MODEMOM_PARTITION = 0,
	MODEMNV_PARTITION,
	MODEMNV_BACK_PARTITION,
	MODEMNV_UPDATE_PARTITION,
	MODEMNV_FACTORY_PARTITION,
	MODEMNV_SYSTEM_PARTITION,
	MODEM_PARTITION,
#ifndef CONFIG_BALONG_MODEM_REMOVE_HEAD
	MODEMDSP_PARTITION,
#endif
	MODEMVRL_P_PARTITION,
	MODEMVRL_M_PARTITION,
	MODEM_INVALID_PARTITION,
};

enum{
	MODEMOM_MOUNT = 0,
	MODEM_NV_MOUNT,
	MODEM_INVALID_MOUNT,
};

struct modem_partition_info {
	unsigned int  img_type;
	char partion_name[32];
};

struct modem_mount_info {
	unsigned int  partion_type;
	char mount_name[32];
};

static struct modem_partition_info modem_partition_list[MODEM_INVALID_PARTITION] = {
	{MODEMOM_PARTITION,			"modem_om"},
	{MODEMNV_PARTITION,			"modemnvm_img"},
	{MODEMNV_BACK_PARTITION,		"modemnvm_backup"},
	{MODEMNV_UPDATE_PARTITION,		"modemnvm_update"},
	{MODEMNV_FACTORY_PARTITION,		"modemnvm_factory"},
	{MODEMNV_SYSTEM_PARTITION,		"modemnvm_system"},
	{MODEM_PARTITION,			"modem"},
#ifndef CONFIG_BALONG_MODEM_REMOVE_HEAD
	{MODEMDSP_PARTITION,			"modem_dsp"},
#endif
	{MODEMVRL_P_PARTITION,			"vrl"},
	{MODEMVRL_M_PARTITION,			"vrl_backup"},
};


#if 0
static struct modem_mount_info modem_mount_list[MODEM_INVALID_MOUNT] = {
	{MODEMOM_MOUNT,				"modem_log"},
	{MODEM_NV_MOUNT,				"mnvm2:0"},
};
#endif


#endif
#define INAND_CMD38_ARG_EXT_CSD  113
#define INAND_CMD38_ARG_ERASE    0x00
#define INAND_CMD38_ARG_TRIM     0x01

#define INAND_CMD38_ARG_SECERASE 0x80
#define INAND_CMD38_ARG_SECTRIM1 0x81
#define INAND_CMD38_ARG_SECTRIM2 0x88

#define MMC_BLK_TIMEOUT_MS  (20 * 60 * 1000)        /* 20 minute timeout */
#define SD_BLK_TIMEOUT_MS  (1 * 60 * 1000)     /* for SD 1 minute timeout */

#define MMC_SANITIZE_REQ_TIMEOUT 240000
#define MMC_EXTRACT_INDEX_FROM_ARG(x) ((x & 0x00FF0000) >> 16)

#define mmc_req_rel_wr(req)	(((req->cmd_flags & REQ_FUA) || \
				  (req->cmd_flags & REQ_META)) && \
				  (rq_data_dir(req) == WRITE))
#define PACKED_CMD_VER	0x01
#define PACKED_CMD_WR	0x02

static DEFINE_MUTEX(block_mutex);

/*
 * The defaults come from config options but can be overriden by module
 * or bootarg options.
 */
static int perdev_minors = CONFIG_MMC_BLOCK_MINORS;
#ifdef CONFIG_BALONG_MTD
extern int block2mtd_setup2(const char *val);
#endif
/*
 * We've only got one major, so number of mmcblk devices is
 * limited to 256 / number of minors per device.
 */
static int max_devices;

/* 256 minors, so at most 256 separate devices */
static DECLARE_BITMAP(dev_use, 256);
static DECLARE_BITMAP(name_use, 256);

/*
 * There is one mmc_blk_data per slot.
 */
struct mmc_blk_data {
	spinlock_t	lock;
	struct gendisk	*disk;
	struct mmc_queue queue;
	struct list_head part;

	unsigned int	flags;
#define MMC_BLK_CMD23	(1 << 0)	/* Can do SET_BLOCK_COUNT for multiblock */
#define MMC_BLK_REL_WR	(1 << 1)	/* MMC Reliable write support */
#define MMC_BLK_PACKED_CMD	(1 << 2)	/* MMC packed command support */
#define MMC_BLK_CMD_QUEUE	(1 << 3) /* MMC command queue support */

	unsigned int	usage;
	unsigned int	read_only;
	unsigned int	part_type;
	unsigned int	name_idx;
	unsigned int	reset_done;
#define MMC_BLK_READ		BIT(0)
#define MMC_BLK_WRITE		BIT(1)
#define MMC_BLK_DISCARD		BIT(2)
#define MMC_BLK_SECDISCARD	BIT(3)

	/*
	 * Only set in main mmc_blk_data associated
	 * with mmc_card with dev_set_drvdata, and keeps
	 * track of the current selected device partition.
	 */
	unsigned int	part_curr;
	struct device_attribute force_ro;
	struct device_attribute power_ro_lock;
	int	area_type;
};

static DEFINE_MUTEX(open_lock);

enum {
	MMC_PACKED_NR_IDX = -1,
	MMC_PACKED_NR_ZERO,
	MMC_PACKED_NR_SINGLE,
};

unsigned int g_ulmmc_suspend_flag = false;
extern struct semaphore     sem_to_rfile_sync_req;


module_param(perdev_minors, int, 0444);
MODULE_PARM_DESC(perdev_minors, "Minors numbers to allocate per device");
static LIST_HEAD(mmcpart_notifiers);

#define MAX_MMC_HOST 8
/* mutex used to control both the table and the notifier list */
DEFINE_MUTEX(mmcpart_table_mutex);
struct mmcpart_alias {
	struct raw_hd_struct hd;
	char partname[BDEVNAME_SIZE];
};
static struct mmcpart_alias mmcpart_table[MAX_MMC_HOST][CONFIG_MMC_BLOCK_MINORS];
static struct raw_mmc_panic_ops mmc_panic_ops_table[MAX_MMC_HOST];
static inline int mmc_blk_part_switch(struct mmc_card *card,
				      struct mmc_blk_data *md);
static int get_card_status(struct mmc_card *card, u32 *status, int retries);
static int mmc_blk_cmdq_switch(struct mmc_card *card,
			struct mmc_blk_data *md, bool enable);

void register_mmcpart_user(struct mmcpart_notifier *new)
{
	int i, j;

	mutex_lock(&mmcpart_table_mutex);

	list_add(&new->list, &mmcpart_notifiers);

	__module_get(THIS_MODULE);

	for (i = 0; i < MAX_MMC_HOST; i++)
		for (j = 0; j < (perdev_minors); j++)
			if (!strncmp(mmcpart_table[i][j].partname,
					new->partname, BDEVNAME_SIZE) &&
					mmcpart_table[i][j].hd.nr_sects) {
				new->add(&mmcpart_table[i][j].hd,
					&mmc_panic_ops_table[i]);
				break;
			}

	mutex_unlock(&mmcpart_table_mutex);
}

int unregister_mmcpart_user(struct mmcpart_notifier *old)
{
	int i, j;

	mutex_lock(&mmcpart_table_mutex);

	module_put(THIS_MODULE);

	for (i = 0; i < MAX_MMC_HOST; i++)
		for (j = 0; j < (perdev_minors); j++)
			if (!strncmp(mmcpart_table[i][j].partname,
					old->partname, BDEVNAME_SIZE)) {
				old->remove(&mmcpart_table[i][j].hd);
				break;
			}

	list_del(&old->list);
	mutex_unlock(&mmcpart_table_mutex);
	return 0;
}
/*
 * split string to substrings according to char pattern
 * deal with multiple characters of pattern
 * more parameters than max_param are ignored
 * the input string is modified
 * return value range from 1~max_param
 */
static int split(char *string, char **index_array, char pattern,
		 int max_param)
{
	char *ptr;
	int count;

	/* thumb through the characters */
	for (ptr = string, count = 0; count < max_param; count++, ptr++) {
		/* find the start of substring */
		while (*ptr == pattern)
			ptr++;
		if (*ptr == '\0')
			break;
		*(index_array + count) = ptr;
		/* find the end of substring */
		while (*ptr != pattern && *ptr != '\0')
			ptr++;
		if (*ptr != '\0')
			*ptr = '\0';
		else {
			count++;
			break;
		}
	}

	return count;
}
/*
 * mmcparts=mmcblk0:p1(name1),p2(name2)...;mmcblk1:p1(name7)
 * build to gurantee no parts have the same name
 */
#define MMCPARTS_STR_LEN 512
static int __init mmcpart_setup(char *arg)
{
	int host_num;
	int part_num;
	int i, j;
	int host_index;
	int part_index;
	char mmcparts_str[MMCPARTS_STR_LEN];
	char *mmcparts_str_trim[1] = {0};
	char *subhost_index[MAX_MMC_HOST];
	char *subhostname_index[3];
	char *subpart_index[perdev_minors];
	char *subpartstr_index[2];
	char *subpartname_index[2];
	int ret;

	memset(mmcparts_str, 0, MMCPARTS_STR_LEN);
	memset(mmcpart_table, 0, sizeof(mmcpart_table));
	strncpy(mmcparts_str, arg, MMCPARTS_STR_LEN - 1);
	split(mmcparts_str, mmcparts_str_trim, ' ', 1);
	host_num = split(mmcparts_str_trim[0], subhost_index, ';',
		MAX_MMC_HOST);
	for (i = 0; i < host_num; i++) {
		if (split(subhost_index[i], subhostname_index, ':', 3) != 2)
			continue;
		if ((strlen(subhostname_index[0]) != 7) ||
			(strncmp(subhostname_index[0], "mmcblk", 6) != 0) ||
			(subhostname_index[0][6] < '0') ||
			(subhostname_index[0][6] > 0x30 + MAX_MMC_HOST - 1))
			continue;
		host_index = subhostname_index[0][6] - 0x30;
		part_num = split(subhostname_index[1], subpart_index, ',',
			perdev_minors);
		for (j = 0; j < part_num; j++) {
			if (split(subpart_index[j], subpartstr_index, ')', 2)
					!= 1)
				continue;
			if (split(subpartstr_index[0], subpartname_index,
					'(', 2) != 2)
				continue;
			if (strlen(subpartname_index[0]) < 2)
				continue;
			ret = strict_strtol(&subpartname_index[0][1], 0,
				(long *)&part_index);
			if ((subpartname_index[0][0] != 'p') || ret ||
				part_index >= (perdev_minors))
				continue;
			strncpy(mmcpart_table[host_index][part_index].partname,
				subpartname_index[1], BDEVNAME_SIZE - 1);
		}
	}
	return 0;
}
early_param("mmcparts", mmcpart_setup);
/*
 * return alias name of mmc partition
 * device may not be there
 */
void get_mmcalias_by_id(char *buf, int major, int minor)
{
	int host_index, partno;

	buf[0] = '\0';
	if (major != MMC_BLOCK_MAJOR)
		return;

	mutex_lock(&mmcpart_table_mutex);
	host_index = minor / (perdev_minors);
	partno = minor % (perdev_minors);
	strncpy(buf, mmcpart_table[host_index][partno].partname, BDEVNAME_SIZE);
	buf[BDEVNAME_SIZE - 1] = '\0';
	mutex_unlock(&mmcpart_table_mutex);
}
int get_mmcpart_by_name(char *part_name, char *dev_name)
{
	int i, j;

	mutex_lock(&mmcpart_table_mutex);
	for (i = 0; i < MAX_MMC_HOST; i++)
		for (j = 0; j < (perdev_minors); j++)
			if (!strncmp(part_name, mmcpart_table[i][j].partname,
					BDEVNAME_SIZE)) {
				snprintf(dev_name, BDEVNAME_SIZE,
					"mmcblk%dp%d", i, j);
				mutex_unlock(&mmcpart_table_mutex);
				return 0;
			}
	mutex_unlock(&mmcpart_table_mutex);
	return -1;
}

static inline void mmc_blk_clear_packed(struct mmc_queue_req *mqrq)
{
	struct mmc_packed *packed = mqrq->packed;

	BUG_ON(!packed);

	mqrq->cmd_type = MMC_PACKED_NONE;
	packed->nr_entries = MMC_PACKED_NR_ZERO;
	packed->idx_failure = MMC_PACKED_NR_IDX;
	packed->retries = 0;
	packed->blocks = 0;
}

struct mmc_blk_data *mmc_blk_get(struct gendisk *disk)
{
	struct mmc_blk_data *md;

	mutex_lock(&open_lock);
	md = disk->private_data;
	if (md && md->usage == 0)
		md = NULL;
	if (md)
		md->usage++;
	mutex_unlock(&open_lock);

	return md;
}

static inline int mmc_get_devidx(struct gendisk *disk)
{
	int devidx = disk->first_minor / perdev_minors;
	return devidx;
}

static void mmc_blk_put(struct mmc_blk_data *md)
{
	mutex_lock(&open_lock);
	md->usage--;
	if (md->usage == 0) {
		int devidx = mmc_get_devidx(md->disk);
		blk_cleanup_queue(md->queue.queue);

		__clear_bit(devidx, dev_use);

		put_disk(md->disk);
		kfree(md);
	}
	mutex_unlock(&open_lock);
}

struct mmc_card *get_mmc_card(struct block_device *bdev)
{
	struct mmc_blk_data *md;
	struct mmc_card *card;

	md = mmc_blk_get(bdev->bd_disk);
	if (!md) {
		return NULL;
	}

	card = md->queue.card;
	if (IS_ERR(card)) {
		return NULL;
	}

	return card;
}
EXPORT_SYMBOL(get_mmc_card);

static ssize_t power_ro_lock_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int ret;
	struct mmc_blk_data *md = mmc_blk_get(dev_to_disk(dev));
	struct mmc_card *card = md->queue.card;
	int locked = 0;

	if (card->ext_csd.boot_ro_lock & EXT_CSD_BOOT_WP_B_PERM_WP_EN)
		locked = 2;
	else if (card->ext_csd.boot_ro_lock & EXT_CSD_BOOT_WP_B_PWR_WP_EN)
		locked = 1;

	ret = snprintf(buf, PAGE_SIZE, "%d\n", locked);

	mmc_blk_put(md);

	return ret;
}

static ssize_t power_ro_lock_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int ret;
	struct mmc_blk_data *md, *part_md;
	struct mmc_card *card;
	unsigned long set;

	if (kstrtoul(buf, 0, &set))
		return -EINVAL;

	if (set != 1)
		return count;

	md = mmc_blk_get(dev_to_disk(dev));
	card = md->queue.card;

	mmc_get_card(card);

	ret = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_BOOT_WP,
				card->ext_csd.boot_ro_lock |
				EXT_CSD_BOOT_WP_B_PWR_WP_EN,
				card->ext_csd.part_time);
	if (ret)
		pr_err("%s: Locking boot partition ro until next power on failed: %d\n", md->disk->disk_name, ret);
	else
		card->ext_csd.boot_ro_lock |= EXT_CSD_BOOT_WP_B_PWR_WP_EN;

	mmc_put_card(card);

	if (!ret) {
		pr_info("%s: Locking boot partition ro until next power on\n",
			md->disk->disk_name);
		set_disk_ro(md->disk, 1);

		list_for_each_entry(part_md, &md->part, part)
			if (part_md->area_type == MMC_BLK_DATA_AREA_BOOT) {
				pr_info("%s: Locking boot partition ro until next power on\n", part_md->disk->disk_name);
				set_disk_ro(part_md->disk, 1);
			}
	}

	mmc_blk_put(md);
	return count;
}

static ssize_t force_ro_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	int ret;
	struct mmc_blk_data *md = mmc_blk_get(dev_to_disk(dev));

	ret = snprintf(buf, PAGE_SIZE, "%d\n",
		       get_disk_ro(dev_to_disk(dev)) ^
		       md->read_only);
	mmc_blk_put(md);
	return ret;
}

static ssize_t force_ro_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	int ret;
	char *end;
	struct mmc_blk_data *md = mmc_blk_get(dev_to_disk(dev));
	unsigned long set = simple_strtoul(buf, &end, 0);
	if (end == buf) {
		ret = -EINVAL;
		goto out;
	}

	set_disk_ro(dev_to_disk(dev), set || md->read_only);
	ret = count;
out:
	mmc_blk_put(md);
	return ret;
}

static int mmc_blk_open(struct block_device *bdev, fmode_t mode)
{
	struct mmc_blk_data *md = mmc_blk_get(bdev->bd_disk);
	int ret = -ENXIO;

	mutex_lock(&block_mutex);
	if (md) {
		if (md->usage == 2)
			check_disk_change(bdev);
		ret = 0;

		if ((mode & FMODE_WRITE) && md->read_only) {
			mmc_blk_put(md);
			ret = -EROFS;
		}
	}
	mutex_unlock(&block_mutex);

	return ret;
}

static void mmc_blk_release(struct gendisk *disk, fmode_t mode)
{
	struct mmc_blk_data *md = disk->private_data;

	mutex_lock(&block_mutex);
	mmc_blk_put(md);
	mutex_unlock(&block_mutex);
}

static int
mmc_blk_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	geo->cylinders = get_capacity(bdev->bd_disk) / (4 * 16);
	geo->heads = 4;
	geo->sectors = 16;
	return 0;
}

#if 0
struct mmc_blk_ioc_data {
	struct mmc_ioc_cmd ic;
	unsigned char *buf;
	u64 buf_bytes;
};
#endif

static struct mmc_blk_ioc_data *mmc_blk_ioctl_copy_from_user(
	struct mmc_ioc_cmd __user *user)
{
	struct mmc_blk_ioc_data *idata;
	int err;

	idata = kzalloc(sizeof(*idata), GFP_KERNEL);
	if (!idata) {
		err = -ENOMEM;
		goto out;
	}

	if (copy_from_user(&idata->ic, user, sizeof(idata->ic))) {
		err = -EFAULT;
		goto idata_err;
	}

	idata->buf_bytes = (u64) idata->ic.blksz * idata->ic.blocks;
	if (idata->buf_bytes > MMC_IOC_MAX_BYTES) {
		err = -EOVERFLOW;
		goto idata_err;
	}

	if (!idata->buf_bytes)
		return idata;

	idata->buf = kzalloc(idata->buf_bytes, GFP_KERNEL);
	if (!idata->buf) {
		err = -ENOMEM;
		goto idata_err;
	}

	if (copy_from_user(idata->buf, (void __user *)(unsigned long)
					idata->ic.data_ptr, idata->buf_bytes)) {
		err = -EFAULT;
		goto copy_err;
	}

	return idata;

copy_err:
	kfree(idata->buf);
idata_err:
	kfree(idata);
out:
	return ERR_PTR(err);
}

static int ioctl_rpmb_card_status_poll(struct mmc_card *card, u32 *status,
				       u32 retries_max)
{
	int err;
	u32 retry_count = 0;

	if (!status || !retries_max)
		return -EINVAL;

	do {
		err = get_card_status(card, status, 5);
		if (err)
			break;

		if (!R1_STATUS(*status) &&
				(R1_CURRENT_STATE(*status) != R1_STATE_PRG))
			break; /* RPMB programming operation complete */

		/*
		 * Rechedule to give the MMC device a chance to continue
		 * processing the previous command without being polled too
		 * frequently.
		 */
		usleep_range(1000, 5000);
	} while (++retry_count < retries_max);

	if (retry_count == retries_max)
		err = -EPERM;

	return err;
}

static int ioctl_do_sanitize(struct mmc_card *card)
{
	int err;

	if (!mmc_can_sanitize(card)) {
			pr_warn("%s: %s - SANITIZE is not supported\n",
				mmc_hostname(card->host), __func__);
			err = -EOPNOTSUPP;
			goto out;
	}

	pr_debug("%s: %s - SANITIZE IN PROGRESS...\n",
		mmc_hostname(card->host), __func__);
    trace_mmc_blk_erase_start(EXT_CSD_SANITIZE_START, 0, 0);
	err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
					EXT_CSD_SANITIZE_START, 1,
					MMC_SANITIZE_REQ_TIMEOUT);
	trace_mmc_blk_erase_end(EXT_CSD_SANITIZE_START, 0, 0);

	if (err)
		pr_err("%s: %s - EXT_CSD_SANITIZE_START failed. err=%d\n",
		       mmc_hostname(card->host), __func__, err);

	pr_debug("%s: %s - SANITIZE COMPLETED\n", mmc_hostname(card->host),
					     __func__);
out:
	return err;
}

static int mmc_blk_ioctl_cmd(struct block_device *bdev,
	struct mmc_ioc_cmd __user *ic_ptr)
{
	struct mmc_blk_ioc_data *idata;
	struct mmc_blk_data *md;
	struct mmc_card *card;
	struct mmc_command cmd = {0};
	struct mmc_data data = {0};
	struct mmc_request mrq = {NULL};
	struct scatterlist sg;
	int err;
#ifndef CONFIG_HISI_MMC_SECURE_RPMB
	int is_rpmb = false;
	u32 status = 0;
#endif
	/*
	 * The caller must have CAP_SYS_RAWIO, and must be calling this on the
	 * whole block device, not on a partition.  This prevents overspray
	 * between sibling partitions.
	 */
	if ((!capable(CAP_SYS_RAWIO)) || (bdev != bdev->bd_contains))
		return -EPERM;

	idata = mmc_blk_ioctl_copy_from_user(ic_ptr);
	if (IS_ERR(idata))
		return PTR_ERR(idata);

	md = mmc_blk_get(bdev->bd_disk);
	if (!md) {
		err = -EINVAL;
		goto cmd_err;
	}

	if (md->area_type & MMC_BLK_DATA_AREA_RPMB){
#if CONFIG_HISI_MMC_SECURE_RPMB
		/* enable secure rpmb will block access rpmb from ioctl */
		return -EINVAL;
#else
		is_rpmb = true;
#endif
	}

	card = md->queue.card;
	if (IS_ERR(card)) {
		err = PTR_ERR(card);
		goto cmd_done;
	}

	cmd.opcode = idata->ic.opcode;
	cmd.arg = idata->ic.arg;
	cmd.flags = idata->ic.flags;

	if (idata->buf_bytes) {
		data.sg = &sg;
		data.sg_len = 1;
		data.blksz = idata->ic.blksz;
		data.blocks = idata->ic.blocks;

		sg_init_one(data.sg, idata->buf, idata->buf_bytes);

		if (idata->ic.write_flag)
			data.flags = MMC_DATA_WRITE;
		else
			data.flags = MMC_DATA_READ;

		/* data.flags must already be set before doing this. */
		mmc_set_data_timeout(&data, card);

		/* Allow overriding the timeout_ns for empirical tuning. */
		if (idata->ic.data_timeout_ns)
			data.timeout_ns = idata->ic.data_timeout_ns;

		if ((cmd.flags & MMC_RSP_R1B) == MMC_RSP_R1B) {
			/*
			 * Pretend this is a data transfer and rely on the
			 * host driver to compute timeout.  When all host
			 * drivers support cmd.cmd_timeout for R1B, this
			 * can be changed to:
			 *
			 *     mrq.data = NULL;
			 *     cmd.cmd_timeout = idata->ic.cmd_timeout_ms;
			 */
			data.timeout_ns = idata->ic.cmd_timeout_ms * 1000000;
		}

		mrq.data = &data;
	}

	mrq.cmd = &cmd;

	mmc_get_card(card);

    if (cmd.opcode == MMC_FFU_DOWNLOAD_OP) {
        pr_debug("[emmc5.0]:%s cmd.opcode == MMC_FFU_DOWNLOAD_OP\n", __func__);

        err = mmc_ffu_download(card, &cmd, idata->buf, idata->buf_bytes);

        goto cmd_rel_host;
    }

    if (cmd.opcode == MMC_FFU_INSTALL_OP) {
        pr_debug("[emmc5.0]:%s cmd.opcode == MMC_FFU_INSTALL_OP\n", __func__);

        err = mmc_ffu_install(card);

        goto cmd_rel_host;
    }

#ifdef CONFIG_MMC_FFU_SAMSUNG45
    if (cmd.opcode == MMC_FFU_SAMSUNG45_OP) {
        pr_debug("[emmc5.0]:%s cmd.opcode == MMC_FFU_SAMSUNG45_OP\n", __func__);

        err = mmc_ffu_execute(card, &cmd, idata->buf, idata->buf_bytes);

        goto cmd_rel_host;
    }
#endif

	err = mmc_blk_part_switch(card, md);
	if (err)
		goto cmd_rel_host;

	if (idata->ic.is_acmd) {
		err = mmc_app_cmd(card->host, card);
		if (err)
			goto cmd_rel_host;
	}
#ifndef CONFIG_HISI_MMC_SECURE_RPMB
	if (is_rpmb) {
		err = mmc_set_blockcount(card, data.blocks,
			idata->ic.write_flag & (1 << 31));
		if (err)
			goto cmd_rel_host;
	}
#endif
	if ((MMC_EXTRACT_INDEX_FROM_ARG(cmd.arg) == EXT_CSD_SANITIZE_START) &&
	    (cmd.opcode == MMC_SWITCH)) {
		err = ioctl_do_sanitize(card);

		if (err)
			pr_err("%s: ioctl_do_sanitize() failed. err = %d",
			       __func__, err);

		goto cmd_rel_host;
	}

	mmc_wait_for_req(card->host, &mrq);

	if (cmd.error) {
		dev_err(mmc_dev(card->host), "%s: cmd error %d\n",
						__func__, cmd.error);
		err = cmd.error;
		goto cmd_rel_host;
	}
	if (data.error) {
		dev_err(mmc_dev(card->host), "%s: data error %d\n",
						__func__, data.error);
		err = data.error;
		goto cmd_rel_host;
	}

	/*
	 * According to the SD specs, some commands require a delay after
	 * issuing the command.
	 */
	if (idata->ic.postsleep_min_us)
		usleep_range(idata->ic.postsleep_min_us, idata->ic.postsleep_max_us);

	if (copy_to_user(&(ic_ptr->response), cmd.resp, sizeof(cmd.resp))) {
		err = -EFAULT;
		goto cmd_rel_host;
	}

	if (!idata->ic.write_flag) {
		if (copy_to_user((void __user *)(unsigned long) idata->ic.data_ptr,
						idata->buf, idata->buf_bytes)) {
			err = -EFAULT;
			goto cmd_rel_host;
		}
	}
#ifndef CONFIG_HISI_MMC_SECURE_RPMB
	if (is_rpmb) {
		/*
		 * Ensure RPMB command has completed by polling CMD13
		 * "Send Status".
		 */
		err = ioctl_rpmb_card_status_poll(card, &status, 5);
		if (err)
			dev_err(mmc_dev(card->host),
					"%s: Card Status=0x%08X, error %d\n",
					__func__, status, err);
	}
#endif
cmd_rel_host:
	mmc_put_card(card);

cmd_done:
	mmc_blk_put(md);
cmd_err:
	kfree(idata->buf);
	kfree(idata);

	return err;
}

#if 0
struct mmc_blk_ioc_rpmb_data {
	struct mmc_blk_ioc_data data[MMC_IOC_MAX_RPMB_CMD];
};
#endif


static struct mmc_blk_ioc_rpmb_data *mmc_blk_ioctl_rpmb_copy_data(
	struct mmc_blk_ioc_rpmb_data *rdata)
{
	struct mmc_blk_ioc_rpmb_data *idata;
	int err, i;

	idata = kzalloc(sizeof(*idata), GFP_KERNEL);
	if (!idata) {
		err = -ENOMEM;
		goto out;
	}

	for (i = 0; i < MMC_IOC_MAX_RPMB_CMD; i++) {
		idata->data[i].buf_bytes = rdata->data[i].buf_bytes;
		idata->data[i].buf = kzalloc(idata->data[i].buf_bytes, GFP_KERNEL);
		if (IS_ERR(idata->data[i].buf)) {
			err = PTR_ERR(idata->data[i].buf);
			goto copy_err;
		}
		memcpy(&idata->data[i].ic, &rdata->data[i].ic, sizeof(struct mmc_ioc_cmd));
		memcpy(idata->data[i].buf, rdata->data[i].buf, idata->data[i].buf_bytes);
	}

	return idata;

copy_err:
	while (--i >= 0) {
		kfree(idata->data[i].buf);
	}
	kfree(idata);
out:
	return ERR_PTR(err);
}

/*This function is responsible for handling RPMB command and is the interface with the eMMC driver.
 *It is used by BL31 and SecureOS.So when modify the fuction please check it with SecureOS.
 *During DMA 64bit development, we modify it using the method of memory copy.
 *idata:the parameter consist of  two command at least and three commd at most, so when copy retuning
 *      data, please confirm copy all the retuning data not include write command.
 */
#if CONFIG_HISI_MMC_SECURE_RPMB
int mmc_blk_ioctl_rpmb_cmd(enum func_id id,
			   struct block_device *bdev,
			   struct mmc_blk_ioc_rpmb_data *rdata)
{
	struct mmc_blk_data *md;
	struct mmc_card *card;
	struct mmc_command cmd = {0};
	struct mmc_data data = {0};
	struct mmc_request mrq = {NULL};
	struct scatterlist sg;
	struct mmc_blk_ioc_rpmb_data *idata = NULL;
	int err = 0, i = 0;
	u32 status = 0;

#if 0
	/* The caller must have CAP_SYS_RAWIO */
	if (!capable(CAP_SYS_RAWIO))
		return -EPERM;
#endif
	md = mmc_blk_get(bdev->bd_disk);
	/* make sure this is a rpmb partition */
	if ((!md) || (!(md->area_type & MMC_BLK_DATA_AREA_RPMB))) {
		err = -EINVAL;
		return err;
	}

	idata = mmc_blk_ioctl_rpmb_copy_data(rdata);
	if (IS_ERR(idata)) {
		err = PTR_ERR(idata);
		goto cmd_done;
	}

	card = md->queue.card;
	if (IS_ERR(card)) {
		err = PTR_ERR(card);
		goto idata_free;
	}

	mmc_get_card(card);
	/*mmc_claim_host(card->host);*/

	err = mmc_blk_part_switch(card, md);
	if (err)
		goto cmd_rel_host;

	for (i = 0; i < MMC_IOC_MAX_RPMB_CMD; i++) {
		struct mmc_blk_ioc_data *curr_data;
		struct mmc_ioc_cmd *curr_cmd;

		curr_data = &idata->data[i];
		curr_cmd = &curr_data->ic;
		if (!curr_cmd->opcode)
			break;

		cmd.opcode = curr_cmd->opcode;
		cmd.arg = curr_cmd->arg;
		cmd.flags = curr_cmd->flags;

		if (curr_data->buf_bytes) {
			data.sg = &sg;
			data.sg_len = 1;
			data.blksz = curr_cmd->blksz;
			data.blocks = curr_cmd->blocks;

			sg_init_one(data.sg, curr_data->buf,
					curr_data->buf_bytes);

			if (curr_cmd->write_flag)
				data.flags = MMC_DATA_WRITE;
			else
				data.flags = MMC_DATA_READ;

			/* data.flags must already be set before doing this. */
			mmc_set_data_timeout(&data, card);

			/*
			 * Allow overriding the timeout_ns for empirical tuning.
			 */
			if (curr_cmd->data_timeout_ns)
				data.timeout_ns = curr_cmd->data_timeout_ns;

			mrq.data = &data;
		}

		mrq.cmd = &cmd;

		err = mmc_set_blockcount(card, data.blocks,
				curr_cmd->write_flag & (1 << 31));
		if (err)
			goto cmd_rel_host;

		mmc_wait_for_req(card->host, &mrq);

		if (cmd.error) {
			dev_err(mmc_dev(card->host), "%s: cmd error %d\n",
					__func__, cmd.error);
			err = cmd.error;
			goto cmd_rel_host;
		}
		if (data.error) {
			dev_err(mmc_dev(card->host), "%s: data error %d\n",
					__func__, data.error);
			err = data.error;
			goto cmd_rel_host;
		}

		memcpy(curr_cmd->response, cmd.resp, sizeof(cmd.resp));

		if (!curr_cmd->write_flag){
			memcpy(rdata->data[i].buf, curr_data->buf, curr_data->buf_bytes);
		}

		/*
		 * Ensure RPMB command has completed by polling CMD13
		 * "Send Status".
		 */
		err = ioctl_rpmb_card_status_poll(card, &status, 5);
		if (err)
			dev_err(mmc_dev(card->host),
					"%s: Card Status=0x%08X, error %d\n",
					__func__, status, err);
	}

cmd_rel_host:
	mmc_put_card(card);
	/*mmc_release_host(card->host);*/

idata_free:
	for (i = 0; i < MMC_IOC_MAX_RPMB_CMD; i++)
		kfree(idata->data[i].buf);

	kfree(idata);

cmd_done:
	mmc_blk_put(md);

	return err;
}
#endif

#ifdef CONFIG_HW_SYSTEM_HW_WR_PROTECT
/* get write protection block info */
static int do_get_write_protection(struct gendisk *disk, struct hd_struct *part)
{
	struct mmc_blk_data *md;
	struct mmc_card *card;
	struct mmc_request mrq = {NULL};
	struct mmc_command cmd = {0};
	struct mmc_data data = {0};
	struct scatterlist sg;
	void *data_buf;
	int len = 8;
	unsigned char buf[8], temp_char, wp_flag;
	unsigned int sector_start_addr, wp_group_size;
	char line_buf[128];
	int i, j, ret = 0;

	/* make sure this is a main partition*/
	md = mmc_blk_get(disk);
	if ((!md) || (!(md->area_type & MMC_BLK_DATA_AREA_MAIN))) {
		ret = -EINVAL;
		return ret;
	}
	card = md->queue.card;
	if (IS_ERR(card)) {
		ret = PTR_ERR(card);
		return ret;
	}

	sector_start_addr = part->start_sect;
	wp_group_size = (512 * 1024) * card->ext_csd.raw_hc_erase_gap_size \
			* card->ext_csd.raw_hc_erase_grp_size / 512;
	pr_info("[INFO] %s: sector_start_addr = 0x%x. wp_group_size = 0x%x.\n", __func__, sector_start_addr, wp_group_size);
	data_buf = kzalloc(len, GFP_KERNEL);
	if (!data_buf) {
		pr_err("Malloc err at %d.\n", __LINE__);
		return -ENOMEM;
	}
	mrq.cmd = &cmd;
	mrq.data = &data;
	cmd.opcode = MMC_SEND_WRITE_PROT_TYPE;
	cmd.arg = sector_start_addr;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = len;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, data_buf, len);
	mmc_get_card(card);
	mmc_set_data_timeout(&data, card);
	mmc_wait_for_req(card->host, &mrq);
	mmc_put_card(card);

	memcpy(buf, data_buf, len);

	for (i = 7; i > 0; i--) {
		temp_char = buf[i];
		for(j = 0; j < 4; j++) {
			wp_flag = temp_char & 0x3;
			snprintf(line_buf, 128 - 1, "[0x%08x~0x%08x] Write protection group is ",
					sector_start_addr, sector_start_addr + wp_group_size - 1);
			sector_start_addr += wp_group_size;
			temp_char = temp_char >> 2;
			switch(wp_flag) {
				case 0:
					strncat(line_buf, "disable",strlen("disable"));
					break;
				case 1:
					strncat(line_buf, "temporary write protection",strlen("temporary write protection"));
					break;
				case 2:
					strncat(line_buf, "power-on write protection",strlen("power-on write protection"));
					break;
				case 3:
					strncat(line_buf, "permanent write protection",strlen("permanent write protection"));
					break;
			}
			pr_err("%s: %s\n", mmc_hostname(card->host), line_buf);
		}
	}

	if (cmd.error) {
		ret = 1;
		pr_err("cmd.error=%d\n", cmd.error);
		goto out;
	}
	if (data.error) {
		ret = 1;
		pr_err("data.error=%d\n", data.error);
		goto out;
	}
out:
	kfree(data_buf);
	return ret;
}

static int mmc_wp_condition_check_for_part(struct mmc_card *card, struct hd_struct *part)
{
	unsigned int sector_start, sector_size,wp_group_size;

	sector_start = (unsigned int)(part->start_sect);
	sector_size  = (unsigned int)(part->nr_sects);

	/*  check whether the parttion sector size is aligned with wp_group_size,
	    calculating the loop count for sending SET_WRITE_PROTECT (CMD28) */
	wp_group_size = (512 * 1024) * card->ext_csd.raw_hc_erase_gap_size \
			* card->ext_csd.raw_hc_erase_grp_size / 512;
	if (sector_size % wp_group_size) {
		pr_err("%s: Write protected areas need to be aligned in accordance with wp_group_size.\n",
				mmc_hostname(card->host));
		return -EINVAL;
	} else {
		pr_info("%s: Adrr is aligned with wp_gpoup_size.\n", mmc_hostname(card->host));
	}

	/* check whether sector start addr is aligned with wp_group_size*/
	if (sector_start % wp_group_size) {
		pr_err("addr sector_start is not aligned %d %d.\n", sector_start, wp_group_size);
		//return -EINVAL;
	} else {
		pr_info("addr sector_start is aliged.\n");
	}

	pr_info("write protection, part %s, start 0x%x,length 0x%x, group 0x%x\n",
			part->info->volname, sector_start, sector_size, wp_group_size);

	return 0;

}

static int mmc_wp_enable_hardware_reset(struct mmc_card *card)
{
	int err;

	if (0 == mmc_can_reset(card)) {
		err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
				EXT_CSD_RST_N_FUNCTION, EXT_CSD_RST_N_ENABLED,
				card->ext_csd.generic_cmd6_time);
		if (err) {
			pr_err("%s: set hardware reset fail\n", mmc_hostname(card->host));
			return -1;
		}
	}
	return 0;
}

static int mmc_wp_prepare_for_emmc(struct mmc_card *card)
{
	int err = 0;
	int retries = 3;
	unsigned char tmp;
	u8 *ext_csd;

	mmc_get_card(card);

	err = mmc_get_ext_csd(card, &ext_csd);
	if (err) {
		pr_err("%s: err %d sending ext_csd.\n", mmc_hostname(card->host), err);
		goto out;
	}

	// to enable hardware reset, in case no poweroff on reboot
	if (mmc_wp_enable_hardware_reset(card)) {
		err = -1;
		goto out;
	}

	if((ext_csd[EXT_CSD_ERASE_GROUP_DEF] & 0x01) == 0){
		pr_err("EXT_CSD_ERASE_GROUP_DEF in ext_csd  was set failed before\n");
		err = -1;
		goto out;
	}
	pr_info("ext_csd erase_group_def is 0x%x.\n",ext_csd[EXT_CSD_ERASE_GROUP_DEF]);
	pr_info("INFO mmc_switch before, ext_csd.user_wp is 0x%x.\n", ext_csd[EXT_CSD_USER_WP]);
	while (!(ext_csd[EXT_CSD_USER_WP] & EXT_CSD_BOOT_WP_B_PWR_WP_EN)) {
		if(retries-- == 0){
			err = -1;
			goto out;
		}

		/*
		 * US_PERM_WP_EN   US_PWR_WP_EN   Type of protection set by SET_WRITE_PROT command
		 *             0              0   Temporary
		 *             0              1   Power-On
		 *             1              0   Permanent
		 *             1              1   Permanent
		 */
		tmp = ext_csd[EXT_CSD_USER_WP];
		tmp |= EXT_CSD_BOOT_WP_B_PWR_WP_EN;
		tmp &= ~EXT_CSD_BOOT_WP_B_PERM_WP_EN;
		tmp |= EXT_CSD_BOOT_WP_B_PERM_WP_DIS;
		tmp |= EXT_CSD_BOOT_WP_B_PWR_WP_DIS;

		/* enable power-on bit */
		err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_USER_WP, tmp, card->ext_csd.generic_cmd6_time);
		if (err) {
			pr_err("%s: set write protect 0x%02x failed.\n", mmc_hostname(card->host), tmp);
		}

		err = mmc_get_ext_csd(card, &ext_csd);
		if (err){
			pr_err("%s: mmc_get_ext_csd failed.\n", mmc_hostname(card->host));
		}

		pr_info("mmc_switch end, ext_csd.user_wp is 0x%x.\n", ext_csd[EXT_CSD_USER_WP]);
	}

out:
	mmc_put_card(card);
	return err;
}

static int mmc_wp_start(struct mmc_card *card,struct hd_struct *part)
{
	unsigned int sector_start, sector_size,wp_group_size;
	unsigned int loop_count,status;
	struct mmc_command cmd = {0};
	int err = 0, i = 0;

	sector_start = (unsigned int)(part->start_sect);
	sector_size  = (unsigned int)(part->nr_sects);
	wp_group_size = (512 * 1024) * card->ext_csd.raw_hc_erase_gap_size \
			* card->ext_csd.raw_hc_erase_grp_size / 512;
	loop_count = sector_size / wp_group_size;

	mmc_get_card(card);
	cmd.opcode = MMC_SET_WRITE_PROT;
	cmd.flags = MMC_RSP_R1B | MMC_CMD_AC;

	for (i = 0; i < loop_count; i++) {
		/* Sending CMD28 for each WP group size */
		cmd.arg = sector_start + i * wp_group_size;
		err = mmc_wait_for_cmd(card->host, &cmd, 0);
		if(err) {
			goto out;
		}

		/* Sending CMD13 to check card status */
		do {
			err = get_card_status(card, &status, 3);
			if(R1_CURRENT_STATE(status) == R1_STATE_TRAN)
				break;
		} while((!err) && (R1_CURRENT_STATE(status) == R1_STATE_PRG));
		if(err)
			goto out;
	}

	pr_info("%s: sucessed.have protect num =%d,total loop= %d\n", __func__,i,loop_count);
out:
	mmc_put_card(card);
	return err;

}

static int do_set_write_protection(struct gendisk *disk, struct hd_struct *part)
{
	struct mmc_blk_data *md;
	struct mmc_card *card;
	int err = 0;

	md = mmc_blk_get(disk);
	/* make sure this is a main partition*/
	if ((!md) || (!(md->area_type & MMC_BLK_DATA_AREA_MAIN))) {
		err = -EINVAL;
		return err;
	}

	card = md->queue.card;
	err = mmc_wp_condition_check_for_part(card,part);
	if (err) {
		return err;
	}

	err = mmc_wp_prepare_for_emmc(card);
	if (err) {
		goto out;
	}

	err = mmc_wp_start(card,part);
	if (err) {
		goto out;
	}
out:
	return err;
}

static int part_wp_action(struct block_device *bdev, const char *partname,
		int (*func)(struct gendisk *disk, struct hd_struct *part))
{
	struct gendisk *sgp = bdev->bd_disk;
	struct disk_part_iter piter;
	struct hd_struct *part;
	int ret = 0;

	/* Don't show non-partitionable removeable devices or empty devices */
	if (!get_capacity(sgp) || (!disk_max_parts(sgp) &&
				(sgp->flags & GENHD_FL_REMOVABLE)))
		return -1;
	if (sgp->flags & GENHD_FL_SUPPRESS_PARTITION_INFO)
		return -1;

	/* show the full disk and all non-0 size partitions of it */
	disk_part_iter_init(&piter, sgp, DISK_PITER_INCL_PART0);
	while ((part = disk_part_iter_next(&piter))) {
		if (part->info && part->info->volname[0] &&
				!strncmp(part->info->volname, partname, strlen(partname))) {
			pr_info("SYS_WP: on partition: %s\n", partname);
			ret = func(sgp, part);
			break;
		}
	}
	disk_part_iter_exit(&piter);
	return ret;
}

static int mmc_hw_set_wp_state(struct block_device *bdev)
{
	int ret;

	ret  = part_wp_action(bdev, "system", do_set_write_protection);
	ret |= part_wp_action(bdev, "cust",   do_set_write_protection);

	return ret;
}

static int mmc_hw_get_wp_state(struct block_device *bdev)
{
	int ret;

	ret  = part_wp_action(bdev, "system", do_get_write_protection);
	ret |= part_wp_action(bdev, "cust",   do_get_write_protection);

	return ret;
}

#endif

static int mmc_blk_ioctl(struct block_device *bdev, fmode_t mode,
	unsigned int cmd, unsigned long arg)
{
	int ret = -EINVAL;
	if (cmd == MMC_IOC_CMD)
		ret = mmc_blk_ioctl_cmd(bdev, (struct mmc_ioc_cmd __user *)arg);
	#if 0
	if (cmd == MMC_IOC_RPMB_CMD)
		ret = mmc_blk_ioctl_rpmb_cmd(bdev,
				(struct mmc_ioc_rpmb __user *)arg);
	#endif
#ifdef CONFIG_HW_SYSTEM_WR_PROTECT
#define MMC_BLOCK_MAJOR 179
#define MMC_IOC_WP_CMD _IOWR(MMC_BLOCK_MAJOR, 0x0, char)
	if(cmd == MMC_IOC_WP_CMD) {
#ifdef CONFIG_HW_SYSTEM_HW_WR_PROTECT
		/* physical protection*/
		if (arg & 0x1) {
			ret = mmc_hw_set_wp_state(bdev);
			if(ret)
				pr_err("%s; set mmc system wp failed.\n", __func__);
		}

		/* get physical protection state*/
		if (arg & 0x10) {
			ret = mmc_hw_get_wp_state(bdev);
			if (ret)
				pr_err("%s: get wp info failed.\n", __func__);
		}
#endif
		/* software protection */
		ret = blk_set_ro_secure_debuggable(arg);
		if (ret)
			pr_err("%s: blk_set_ro_secure_debuggable failed.\n", __func__);
	}
#endif
	return ret;
}

#ifdef CONFIG_COMPAT
static int mmc_blk_compat_ioctl(struct block_device *bdev, fmode_t mode,
	unsigned int cmd, unsigned long arg)
{
	return mmc_blk_ioctl(bdev, mode, cmd, (unsigned long) compat_ptr(arg));
}
#endif

static const struct block_device_operations mmc_bdops = {
	.open			= mmc_blk_open,
	.release		= mmc_blk_release,
	.getgeo			= mmc_blk_getgeo,
	.owner			= THIS_MODULE,
	.ioctl			= mmc_blk_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl		= mmc_blk_compat_ioctl,
#endif
};

static int mmc_blk_cmdq_switch(struct mmc_card *card,
			struct mmc_blk_data *md, bool enable)
{
	int ret = 0;
	bool cmdq_mode = !!mmc_card_cmdq(card);
	struct mmc_host *host = card->host;

	if (!card->ext_csd.cmdq_mode_en ||
	    (enable && md && !(md->flags & MMC_BLK_CMD_QUEUE)) ||
	    (cmdq_mode == enable))
		return 0;


	if (host->cmdq_ops) {
		if (enable) {
			ret = mmc_set_blocklen(card, MMC_CARD_CMDQ_BLK_SIZE);
			if (ret) {
				pr_err("%s: failed to set block-size to 512\n",
				       __func__);
				BUG();
			}

			ret = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
					 EXT_CSD_CMDQ_MODE, enable,
					 card->ext_csd.generic_cmd6_time);
			if (ret) {
				pr_err("cmdq mode %sable failed %d\n",
				       enable ? "en" : "dis", ret);
				goto out;
			}
			mmc_card_set_cmdq(card);

			/* enable host controller command queue engine */
			ret = host->cmdq_ops->enable(card->host);
			if (ret) {
				pr_err("failed to enable host controller cqe %d\n",
						ret);
			}

		}

		if (ret || !enable) {
			ret = host->cmdq_ops->disable(card->host, true);
			if (ret) {
				pr_err("failed to disable host controller cqe %d\n", ret);
			}
			/* disable CQ mode in card */
			ret = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
					EXT_CSD_CMDQ_MODE, 0,
					card->ext_csd.generic_cmd6_time);
			if (ret) {
				pr_err("cmdq mode %sable failed %d\n",
					enable ? "en" : "dis", ret);
				BUG();
			}
			mmc_card_clr_cmdq(card);
		}
	} else {
		pr_err("%s: No cmdq ops defined !!!\n", __func__);
		BUG();
	}

out:

	return ret;
}

static inline int mmc_blk_part_switch(struct mmc_card *card,
				      struct mmc_blk_data *md)
{
	int ret;
	struct mmc_blk_data *main_md = dev_get_drvdata(&card->dev);

	if (main_md->part_curr == md->part_type)
		return 0;

	if (mmc_card_mmc(card)) {
		u8 part_config = card->ext_csd.part_config;

		part_config &= ~EXT_CSD_PART_CONFIG_ACC_MASK;
		part_config |= md->part_type;

		ret = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_PART_CONFIG, part_config,
				 card->ext_csd.part_time);
		if (ret)
			return ret;

		card->ext_csd.part_config = part_config;
	}

	main_md->part_curr = md->part_type;
	return 0;
}

static u32 mmc_sd_num_wr_blocks(struct mmc_card *card)
{
	int err;
	u32 result;
	__be32 *blocks;

	struct mmc_request mrq = {NULL};
	struct mmc_command cmd = {0};
	struct mmc_data data = {0};

	struct scatterlist sg;

	cmd.opcode = MMC_APP_CMD;
	cmd.arg = card->rca << 16;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;

	err = mmc_wait_for_cmd(card->host, &cmd, 0);
	if (err)
		return (u32)-1;
	if (!mmc_host_is_spi(card->host) && !(cmd.resp[0] & R1_APP_CMD))
		return (u32)-1;

	memset(&cmd, 0, sizeof(struct mmc_command));

	cmd.opcode = SD_APP_SEND_NUM_WR_BLKS;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = 4;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;
	mmc_set_data_timeout(&data, card);

	mrq.cmd = &cmd;
	mrq.data = &data;

	blocks = kmalloc(4, GFP_KERNEL);

	if (!blocks)
		return (u32)-1;

	sg_init_one(&sg, blocks, 4);

	mmc_wait_for_req(card->host, &mrq);

	result = ntohl(*blocks);
	kfree(blocks);

	if (cmd.error || data.error)
		result = (u32)-1;

	return result;
}

static int send_stop(struct mmc_card *card, u32 *status)
{
	struct mmc_command cmd = {0};
	int err;

	cmd.opcode = MMC_STOP_TRANSMISSION;
	cmd.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;
	err = mmc_wait_for_cmd(card->host, &cmd, 5);
	if (err == 0)
		*status = cmd.resp[0];
	return err;
}

static int get_card_status(struct mmc_card *card, u32 *status, int retries)
{
	struct mmc_command cmd = {0};
	int err;

	cmd.opcode = MMC_SEND_STATUS;
	if (!mmc_host_is_spi(card->host))
		cmd.arg = card->rca << 16;
	cmd.flags = MMC_RSP_SPI_R2 | MMC_RSP_R1 | MMC_CMD_AC;
	err = mmc_wait_for_cmd(card->host, &cmd, retries);
	if (err == 0)
		*status = cmd.resp[0];
	return err;
}

#define ERR_NOMEDIUM	3
#define ERR_RETRY	2
#define ERR_ABORT	1
#define ERR_CONTINUE	0

static int mmc_blk_cmd_error(struct request *req, const char *name, int error,
	bool status_valid, u32 status)
{
	switch (error) {
	case -EILSEQ:
		/* response crc error, retry the r/w cmd */
		pr_err("%s: %s sending %s command, card status %#x\n",
			req->rq_disk->disk_name, "response CRC error",
			name, status);
		return ERR_RETRY;

	case -ETIMEDOUT:
		pr_err("%s: %s sending %s command, card status %#x\n",
			req->rq_disk->disk_name, "timed out", name, status);

		/* If the status cmd initially failed, retry the r/w cmd */
		if (!status_valid) {
			pr_err("%s: status not valid, retrying timeout\n", req->rq_disk->disk_name);
			return ERR_RETRY;
		}
		/*
		 * If it was a r/w cmd crc error, or illegal command
		 * (eg, issued in wrong state) then retry - we should
		 * have corrected the state problem above.
		 */
		if (status & (R1_COM_CRC_ERROR | R1_ILLEGAL_COMMAND)) {
			pr_err("%s: command error, retrying timeout\n", req->rq_disk->disk_name);
			return ERR_RETRY;
		}

		/* Otherwise abort the command */
		pr_err("%s: not retrying timeout\n", req->rq_disk->disk_name);
		return ERR_ABORT;

	default:
		/* We don't understand the error code the driver gave us */
		pr_err("%s: unknown error %d sending read/write command, card status %#x\n",
		       req->rq_disk->disk_name, error, status);
		return ERR_ABORT;
	}
}

/*
 * Initial r/w and stop cmd error recovery.
 * We don't know whether the card received the r/w cmd or not, so try to
 * restore things back to a sane state.  Essentially, we do this as follows:
 * - Obtain card status.  If the first attempt to obtain card status fails,
 *   the status word will reflect the failed status cmd, not the failed
 *   r/w cmd.  If we fail to obtain card status, it suggests we can no
 *   longer communicate with the card.
 * - Check the card state.  If the card received the cmd but there was a
 *   transient problem with the response, it might still be in a data transfer
 *   mode.  Try to send it a stop command.  If this fails, we can't recover.
 * - If the r/w cmd failed due to a response CRC error, it was probably
 *   transient, so retry the cmd.
 * - If the r/w cmd timed out, but we didn't get the r/w cmd status, retry.
 * - If the r/w cmd timed out, and the r/w cmd failed due to CRC error or
 *   illegal cmd, retry.
 * Otherwise we don't understand what happened, so abort.
 */
static int mmc_blk_cmd_recovery(struct mmc_card *card, struct request *req,
	struct mmc_blk_request *brq, int *ecc_err, int *gen_err)
{
	bool prev_cmd_status_valid = true;
	u32 status, stop_status = 0;
	int err, retry;

	if (mmc_card_removed(card))
		return ERR_NOMEDIUM;

	/*
	 * Try to get card status which indicates both the card state
	 * and why there was no response.  If the first attempt fails,
	 * we can't be sure the returned status is for the r/w command.
	 */
	for (retry = 2; retry >= 0; retry--) {
		err = get_card_status(card, &status, 0);
		if (!err)
			break;

		prev_cmd_status_valid = false;

#if 0
		pr_err("%s: error %d sending status command, %sing\n",
		       req->rq_disk->disk_name, err, retry ? "retry" : "abort");
#endif
	}

	/* We couldn't get a response from the card.  Give up. */
	if (err) {
		/* Check if the card is removed */
		if (mmc_detect_card_removed(card->host))
			return ERR_NOMEDIUM;
		return ERR_ABORT;
	}

	if (status & (R1_CARD_ECC_FAILED | R1_ERROR) ||
		!(status & R1_READY_FOR_DATA)) {
		pr_err("%s: card status is %x \n", req->rq_disk->disk_name, status);
		pr_err("%s: card CURRENT_STATE is %x \n", req->rq_disk->disk_name, R1_CURRENT_STATE(status));
		if(status & R1_CARD_ECC_FAILED)
			pr_err("%s: card ECC \n", req->rq_disk->disk_name);
		if(!(status & R1_READY_FOR_DATA))
			pr_err("%s: card not ready \n", req->rq_disk->disk_name);
		if(status & R1_ERROR)
			pr_err("%s: card general or unknown \n", req->rq_disk->disk_name);
	}

	/* Flag ECC errors */
	if ((status & R1_CARD_ECC_FAILED) ||
	    (brq->stop.resp[0] & R1_CARD_ECC_FAILED) ||
	    (brq->cmd.resp[0] & R1_CARD_ECC_FAILED))
		*ecc_err = 1;

	/* Flag General errors */
	if (!mmc_host_is_spi(card->host) && rq_data_dir(req) != READ)
		if ((status & R1_ERROR) ||
			(brq->stop.resp[0] & R1_ERROR)) {
			pr_err("%s: %s: general error sending stop or status command, stop cmd response %#x, card status %#x\n",
			       req->rq_disk->disk_name, __func__,
			       brq->stop.resp[0], status);
			*gen_err = 1;
		}

	/*
	 * Check the current card state.  If it is in some data transfer
	 * mode, tell it to stop (and hopefully transition back to TRAN.)
	 */
	if (R1_CURRENT_STATE(status) == R1_STATE_DATA ||
	    R1_CURRENT_STATE(status) == R1_STATE_RCV) {
		err = send_stop(card, &stop_status);
		if (err)
			pr_err("%s: error %d sending stop command\n",
			       req->rq_disk->disk_name, err);

		/*
		 * If the stop cmd also timed out, the card is probably
		 * not present, so abort.  Other errors are bad news too.
		 */
		if (err)
			return ERR_ABORT;
		if (stop_status & R1_CARD_ECC_FAILED)
			*ecc_err = 1;
		if (!mmc_host_is_spi(card->host) && rq_data_dir(req) != READ)
			if (stop_status & R1_ERROR) {
				pr_err("%s: %s: general error sending stop command, stop cmd response %#x\n",
				       req->rq_disk->disk_name, __func__,
				       stop_status);
				*gen_err = 1;
			}
	}

	/* Check for set block count errors */
	if (brq->sbc.error)
		return mmc_blk_cmd_error(req, "SET_BLOCK_COUNT", brq->sbc.error,
				prev_cmd_status_valid, status);

	/* Check for r/w command errors */
	if (brq->cmd.error)
		return mmc_blk_cmd_error(req, "r/w cmd", brq->cmd.error,
				prev_cmd_status_valid, status);

	/* Data errors */
	if (!brq->stop.error)
		return ERR_CONTINUE;

	/* Now for stop errors.  These aren't fatal to the transfer. */
	pr_info("%s: error %d sending stop command, original cmd response %#x, card status %#x\n",
	       req->rq_disk->disk_name, brq->stop.error,
	       brq->cmd.resp[0], status);

	/*
	 * Subsitute in our own stop status as this will give the error
	 * state which happened during the execution of the r/w command.
	 */
	if (stop_status) {
		brq->stop.resp[0] = stop_status;
		brq->stop.error = 0;
	}
	return ERR_CONTINUE;
}

static int mmc_blk_reset(struct mmc_blk_data *md, struct mmc_host *host,
			 int type)
{
	int err;

	if (md->reset_done & type)
		return -EEXIST;

	if (!host->card)
		return -EINVAL;

	md->reset_done |= type;
	if (mmc_card_sd(host->card))
		err = mmc_sd_reset(host);
	else
		err = mmc_hw_reset(host);
	if (err && err != -EOPNOTSUPP) {
		/* We failed to reset so we need to abort the request */
		pr_err("%s: %s: failed to reset %d\n", mmc_hostname(host),
				__func__, err);
		return -ENODEV;
	} else if (err == -EOPNOTSUPP) {
		pr_err("%s: %s: not support reset %d\n", mmc_hostname(host),
				__func__, err);
		return err;
	} else {
		/* Ensure we switch back to the correct partition */
		struct mmc_blk_data *main_md =
		    dev_get_drvdata(&host->card->dev);
		int part_err;

		main_md->part_curr = main_md->part_type;
		part_err = mmc_blk_part_switch(host->card, md);
		if (part_err) {
			/*
			 * We have failed to get back into the correct
			 * partition, so we need to abort the whole request.
			 */
			return -ENODEV;
		}
	}
	return err;
}

static inline void mmc_blk_reset_success(struct mmc_blk_data *md, int type)
{
	md->reset_done &= ~type;
}

static int mmc_blk_issue_discard_rq(struct mmc_queue *mq, struct request *req)
{
	struct mmc_blk_data *md = mq->data;
	struct mmc_card *card = md->queue.card;
	unsigned int from, nr, arg;
	int err = 0, type = MMC_BLK_DISCARD;

	if (!mmc_can_erase(card)) {
		err = -EOPNOTSUPP;
		goto out;
	}

	from = blk_rq_pos(req);
	nr = blk_rq_sectors(req);

	if (mmc_can_discard(card))
		arg = MMC_DISCARD_ARG;
	else if (mmc_can_trim(card))
		arg = MMC_TRIM_ARG;
	else
		arg = MMC_ERASE_ARG;
retry:
	if (card->quirks & MMC_QUIRK_INAND_CMD38) {
		err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
				 INAND_CMD38_ARG_EXT_CSD,
				 arg == MMC_TRIM_ARG ?
				 INAND_CMD38_ARG_TRIM :
				 INAND_CMD38_ARG_ERASE,
				 0);
		if (err)
			goto out;
	}
	err = mmc_erase(card, from, nr, arg);
out:
	if (err == -EIO && !mmc_blk_reset(md, card->host, type))
		goto retry;
	if (!err)
		mmc_blk_reset_success(md, type);
	blk_end_request(req, err, blk_rq_bytes(req));

	return err ? 0 : 1;
}

static int mmc_blk_issue_secdiscard_rq(struct mmc_queue *mq,
				       struct request *req)
{
	struct mmc_blk_data *md = mq->data;
	struct mmc_card *card = md->queue.card;
	unsigned int from, nr, arg;
	int err = 0, type = MMC_BLK_SECDISCARD;

	if (!(mmc_can_secure_erase_trim(card))) {
		err = -EOPNOTSUPP;
		goto out;
	}

	from = blk_rq_pos(req);
	nr = blk_rq_sectors(req);

	if (mmc_can_trim(card) && !mmc_erase_group_aligned(card, from, nr))
		arg = MMC_SECURE_TRIM1_ARG;
	else
		arg = MMC_SECURE_ERASE_ARG;

retry:
	if (card->quirks & MMC_QUIRK_INAND_CMD38) {
		err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
				 INAND_CMD38_ARG_EXT_CSD,
				 arg == MMC_SECURE_TRIM1_ARG ?
				 INAND_CMD38_ARG_SECTRIM1 :
				 INAND_CMD38_ARG_SECERASE,
				 0);
		if (err)
			goto out_retry;
	}

	err = mmc_erase(card, from, nr, arg);
	if (err == -EIO)
		goto out_retry;
	if (err)
		goto out;

	if (arg == MMC_SECURE_TRIM1_ARG) {
		if (card->quirks & MMC_QUIRK_INAND_CMD38) {
			err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
					 INAND_CMD38_ARG_EXT_CSD,
					 INAND_CMD38_ARG_SECTRIM2,
					 0);
			if (err)
				goto out_retry;
		}

		err = mmc_erase(card, from, nr, MMC_SECURE_TRIM2_ARG);
		if (err == -EIO)
			goto out_retry;
		if (err)
			goto out;
	}

out_retry:
	if (err && !mmc_blk_reset(md, card->host, type))
		goto retry;
	if (!err)
		mmc_blk_reset_success(md, type);
out:
	blk_end_request(req, err, blk_rq_bytes(req));

	return err ? 0 : 1;
}

static int mmc_blk_issue_flush(struct mmc_queue *mq, struct request *req)
{
	struct mmc_blk_data *md = mq->data;
	struct mmc_card *card = md->queue.card;
	int ret = 0;

	ret = mmc_flush_cache(card);
	if (ret)
		ret = -EIO;

	blk_end_request_all(req, ret);

	return ret ? 0 : 1;
}

/*
 * Reformat current write as a reliable write, supporting
 * both legacy and the enhanced reliable write MMC cards.
 * In each transfer we'll handle only as much as a single
 * reliable write can handle, thus finish the request in
 * partial completions.
 */
static inline void mmc_apply_rel_rw(struct mmc_blk_request *brq,
				    struct mmc_card *card,
				    struct request *req)
{
	if (!(card->ext_csd.rel_param & EXT_CSD_WR_REL_PARAM_EN)) {
		/* Legacy mode imposes restrictions on transfers. */
		if (!IS_ALIGNED(brq->cmd.arg, card->ext_csd.rel_sectors))
			brq->data.blocks = 1;

		if (brq->data.blocks > card->ext_csd.rel_sectors)
			brq->data.blocks = card->ext_csd.rel_sectors;
		else if (brq->data.blocks < card->ext_csd.rel_sectors)
			brq->data.blocks = 1;
	}
}

#define CMD_ERRORS							\
	(R1_OUT_OF_RANGE |	/* Command argument out of range */	\
	 R1_ADDRESS_ERROR |	/* Misaligned address */		\
	 R1_BLOCK_LEN_ERROR |	/* Transferred block length incorrect */\
	 R1_WP_VIOLATION |	/* Tried to write to protected block */	\
	 R1_CC_ERROR |		/* Card controller error */		\
	 R1_ERROR)		/* General/unknown error */

static int mmc_blk_err_check(struct mmc_card *card,
			     struct mmc_async_req *areq)
{
	struct mmc_queue_req *mq_mrq = container_of(areq, struct mmc_queue_req,
						    mmc_active);
	struct mmc_blk_request *brq = &mq_mrq->brq;
	struct request *req = mq_mrq->req;
	int ecc_err = 0, gen_err = 0;
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	int buff_len = 0;
	char *log_buff = NULL;
#endif

	/*
	 * sbc.error indicates a problem with the set block count
	 * command.  No data will have been transferred.
	 *
	 * cmd.error indicates a problem with the r/w command.  No
	 * data will have been transferred.
	 *
	 * stop.error indicates a problem with the stop command.  Data
	 * may have been transferred, or may still be transferring.
	 */
	if (brq->sbc.error || brq->cmd.error || brq->stop.error ||
	    brq->data.error) {
		switch (mmc_blk_cmd_recovery(card, req, brq, &ecc_err, &gen_err)) {
		case ERR_RETRY:
			return MMC_BLK_RETRY;
		case ERR_ABORT:
			return MMC_BLK_ABORT;
		case ERR_NOMEDIUM:
			return MMC_BLK_NOMEDIUM;
		case ERR_CONTINUE:
			break;
		}
	}

	/*
	 * Check for errors relating to the execution of the
	 * initial command - such as address errors.  No data
	 * has been transferred.
	 */
	if (brq->cmd.resp[0] & CMD_ERRORS) {
		pr_err("%s: r/w command failed, status = %#x\n",
		       req->rq_disk->disk_name, brq->cmd.resp[0]);
		return MMC_BLK_ABORT;
	}

	/*
	 * Everything else is either success, or a data error of some
	 * kind.  If it was a write, we may have transitioned to
	 * program mode, which we have to wait for it to complete.
	 */
	if (!mmc_host_is_spi(card->host) && rq_data_dir(req) != READ) {
		u32 status;
		unsigned long timeout;
		unsigned long sd_timeout;

		/* Check stop command response */
		if (brq->stop.resp[0] & R1_ERROR) {
			pr_err("%s: %s: general error sending stop command, stop cmd response %#x\n",
			       req->rq_disk->disk_name, __func__,
			       brq->stop.resp[0]);
			gen_err = 1;
		}

		timeout = jiffies + msecs_to_jiffies(MMC_BLK_TIMEOUT_MS);
		sd_timeout = jiffies + msecs_to_jiffies(SD_BLK_TIMEOUT_MS);
		do {
			int err = get_card_status(card, &status, 5);
			if (err) {
				pr_err("%s: error %d requesting status\n",
				       req->rq_disk->disk_name, err);
				return MMC_BLK_CMD_ERR;
			}

			if (status & R1_ERROR) {
				pr_err("%s: %s: general error sending status command, card status %#x\n",
				       req->rq_disk->disk_name, __func__,
				       status);
				gen_err = 1;
			}

			if (mmc_card_sd(card)){
				/* Timeout if the SD never becomes ready for data
				 * and never leaves the program state.
				 */
				if (time_after(jiffies, sd_timeout)) {
					pr_err("%s: SD card stuck in programming state!"\
						" %s %s\n", mmc_hostname(card->host),
						req->rq_disk->disk_name, __func__);
#ifdef CONFIG_HW_SD_HEALTH_DETECT
						mmc_diag_sd_health_status(req->rq_disk,MMC_BLK_STUCK_IN_PRG_ERR);
#endif
#ifdef CONFIG_HUAWEI_SDCARD_DSM
						if(!dsm_client_ocuppy(sdcard_dclient))
						{
							log_buff = dsm_sdcard_get_log(DSM_SDCARD_STATUS_BLK_STUCK_IN_PRG_ERR, 0);
							buff_len = strlen(log_buff);
							dsm_client_copy(sdcard_dclient,log_buff,buff_len + 1);
							dsm_client_notify(sdcard_dclient, DSM_SDCARD_BLK_STUCK_IN_PRG_ERR);
						}
#endif

					return MMC_BLK_CMD_ERR;
				}
			} else {
				/* Timeout if the device never becomes ready for data
				 * and never leaves the program state.
				 */
				if (time_after(jiffies, timeout)) {
					pr_err("%s: Card stuck in programming state!"\
						" %s %s\n", mmc_hostname(card->host),
						req->rq_disk->disk_name, __func__);

					return MMC_BLK_CMD_ERR;
				}
			}
			/*
			 * Some cards mishandle the status bits,
			 * so make sure to check both the busy
			 * indication and the card state.
			 */
		} while (!(status & R1_READY_FOR_DATA) ||
			 (R1_CURRENT_STATE(status) == R1_STATE_PRG));
	}

	/* if general error occurs, retry the write operation. */
	if (gen_err) {
		pr_warn("%s: retrying write for general error\n",
				req->rq_disk->disk_name);
		return MMC_BLK_RETRY;
	}

	if (brq->data.error) {
		pr_err("%s: error %d transferring data, sector %u, nr %u, cmd response %#x, card status %#x\n",
		       req->rq_disk->disk_name, brq->data.error,
		       (unsigned)blk_rq_pos(req),
		       (unsigned)blk_rq_sectors(req),
		       brq->cmd.resp[0], brq->stop.resp[0]);

		if (rq_data_dir(req) == READ) {
			if (ecc_err)
				return MMC_BLK_ECC_ERR;
			return MMC_BLK_DATA_ERR;
		} else {
			return MMC_BLK_CMD_ERR;
		}
	}

	if (!brq->data.bytes_xfered)
		return MMC_BLK_RETRY;

	if (mmc_packed_cmd(mq_mrq->cmd_type)) {
		if (unlikely(brq->data.blocks << 9 != brq->data.bytes_xfered))
			return MMC_BLK_PARTIAL;
		else
			return MMC_BLK_SUCCESS;
	}

	if (blk_rq_bytes(req) != brq->data.bytes_xfered)
		return MMC_BLK_PARTIAL;

	return MMC_BLK_SUCCESS;
}

static int mmc_blk_packed_err_check(struct mmc_card *card,
				    struct mmc_async_req *areq)
{
	struct mmc_queue_req *mq_rq = container_of(areq, struct mmc_queue_req,
			mmc_active);
	struct request *req = mq_rq->req;
	struct mmc_packed *packed = mq_rq->packed;
	int err, check, status;
	u8 *ext_csd;

	BUG_ON(!packed);

	packed->retries--;
	check = mmc_blk_err_check(card, areq);
	err = get_card_status(card, &status, 0);
	if (err) {
		pr_err("%s: error %d sending status command\n",
		       req->rq_disk->disk_name, err);
		return MMC_BLK_ABORT;
	}

	if (status & R1_EXCEPTION_EVENT) {
		err = mmc_get_ext_csd(card, &ext_csd);
		if (err) {
			pr_err("%s: error %d sending ext_csd\n",
			       req->rq_disk->disk_name, err);
			return MMC_BLK_ABORT;
		}

		if ((ext_csd[EXT_CSD_EXP_EVENTS_STATUS] &
		     EXT_CSD_PACKED_FAILURE) &&
		    (ext_csd[EXT_CSD_PACKED_CMD_STATUS] &
		     EXT_CSD_PACKED_GENERIC_ERROR)) {
			if (ext_csd[EXT_CSD_PACKED_CMD_STATUS] &
			    EXT_CSD_PACKED_INDEXED_ERROR) {
				packed->idx_failure =
				  ext_csd[EXT_CSD_PACKED_FAILURE_INDEX] - 1;
				check = MMC_BLK_PARTIAL;
			}
#ifdef CONFIG_HUAWEI_EMMC_DSM
			DSM_EMMC_LOG(card, DSM_EMMC_PACKED_FAILURE,
				"%s: packed cmd failed, nr %u, sectors %u, "
		       "failure index: %d\n",
		       req->rq_disk->disk_name, packed->nr_entries,
		       packed->blocks, packed->idx_failure);
#endif
			pr_err("%s: packed cmd failed, nr %u, sectors %u, "
			       "failure index: %d\n",
			       req->rq_disk->disk_name, packed->nr_entries,
			       packed->blocks, packed->idx_failure);
		}
#ifdef CONFIG_HUAWEI_EMMC_DSM
		if(ext_csd[EXT_CSD_EXP_EVENTS_STATUS] &
		     EXT_CSD_DYNCAP_NEEDED) {
			DSM_EMMC_LOG(card, DSM_EMMC_DYNCAP_NEEDED,
				"%s: DYNCAP_NEEDED [58]: %d, the device may degrade in performance and eventually become non-functional\n",
		       req->rq_disk->disk_name, ext_csd[58]);
		}
		if(ext_csd[EXT_CSD_EXP_EVENTS_STATUS] &
		     EXT_CSD_SYSPOOL_EXHAUSTED) {
			DSM_EMMC_LOG(card, DSM_EMMC_SYSPOOL_EXHAUSTED,
				"%s: SYSPOOL_EXHAUSTED, System resources pool exhausted\n",
		       req->rq_disk->disk_name);
		}
#endif
		kfree(ext_csd);
	}

	return check;
}

static void mmc_blk_rw_rq_prep(struct mmc_queue_req *mqrq,
			       struct mmc_card *card,
			       int disable_multi,
			       struct mmc_queue *mq)
{
	u32 readcmd, writecmd;
	struct mmc_blk_request *brq = &mqrq->brq;
	struct request *req = mqrq->req;
	struct mmc_blk_data *md = mq->data;
	bool do_data_tag;

	/*
	 * Reliable writes are used to implement Forced Unit Access and
	 * REQ_META accesses, and are supported only on MMCs.
	 *
	 * XXX: this really needs a good explanation of why REQ_META
	 * is treated special.
	 */
	bool do_rel_wr = ((req->cmd_flags & REQ_FUA) ||
			  (req->cmd_flags & REQ_META)) &&
		(rq_data_dir(req) == WRITE) &&
		(md->flags & MMC_BLK_REL_WR);

	memset(brq, 0, sizeof(struct mmc_blk_request));
	brq->mrq.cmd = &brq->cmd;
	brq->mrq.data = &brq->data;

	brq->cmd.arg = blk_rq_pos(req);
	if (!mmc_card_blockaddr(card))
		brq->cmd.arg <<= 9;
	brq->cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	brq->data.blksz = 512;
	brq->stop.opcode = MMC_STOP_TRANSMISSION;
	brq->stop.arg = 0;
	brq->stop.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;
	brq->data.blocks = blk_rq_sectors(req);

	/*
	 * The block layer doesn't support all sector count
	 * restrictions, so we need to be prepared for too big
	 * requests.
	 */
	if (brq->data.blocks > card->host->max_blk_count)
		brq->data.blocks = card->host->max_blk_count;

	if (brq->data.blocks > 1) {
		/*
		 * After a read error, we redo the request one sector
		 * at a time in order to accurately determine which
		 * sectors can be read successfully.
		 */
		if (disable_multi)
			brq->data.blocks = 1;

		/*
		 * Some controllers have HW issues while operating
		 * in multiple I/O mode
		 */
		if (card->host->ops->multi_io_quirk)
			brq->data.blocks = card->host->ops->multi_io_quirk(card,
						(rq_data_dir(req) == READ) ?
						MMC_DATA_READ : MMC_DATA_WRITE,
						brq->data.blocks);
	}

	if (brq->data.blocks > 1 || do_rel_wr) {
		/* SPI multiblock writes terminate using a special
		 * token, not a STOP_TRANSMISSION request.
		 */
		if (!mmc_host_is_spi(card->host) ||
		    rq_data_dir(req) == READ)
			brq->mrq.stop = &brq->stop;
		readcmd = MMC_READ_MULTIPLE_BLOCK;
		writecmd = MMC_WRITE_MULTIPLE_BLOCK;
	} else {
		brq->mrq.stop = NULL;
		readcmd = MMC_READ_SINGLE_BLOCK;
		writecmd = MMC_WRITE_BLOCK;
	}
	if (rq_data_dir(req) == READ) {
		brq->cmd.opcode = readcmd;
		brq->data.flags |= MMC_DATA_READ;
	} else {
		brq->cmd.opcode = writecmd;
		brq->data.flags |= MMC_DATA_WRITE;
	}

	if (do_rel_wr)
		mmc_apply_rel_rw(brq, card, req);

	/*
	 * Data tag is used only during writing meta data to speed
	 * up write and any subsequent read of this meta data
	 */
	do_data_tag = (card->ext_csd.data_tag_unit_size) &&
		(req->cmd_flags & REQ_META) &&
		(rq_data_dir(req) == WRITE) &&
		((brq->data.blocks * brq->data.blksz) >=
		 card->ext_csd.data_tag_unit_size);

	/*
	 * Pre-defined multi-block transfers are preferable to
	 * open ended-ones (and necessary for reliable writes).
	 * However, it is not sufficient to just send CMD23,
	 * and avoid the final CMD12, as on an error condition
	 * CMD12 (stop) needs to be sent anyway. This, coupled
	 * with Auto-CMD23 enhancements provided by some
	 * hosts, means that the complexity of dealing
	 * with this is best left to the host. If CMD23 is
	 * supported by card and host, we'll fill sbc in and let
	 * the host deal with handling it correctly. This means
	 * that for hosts that don't expose MMC_CAP_CMD23, no
	 * change of behavior will be observed.
	 *
	 * N.B: Some MMC cards experience perf degradation.
	 * We'll avoid using CMD23-bounded multiblock writes for
	 * these, while retaining features like reliable writes.
	 */
	if ((md->flags & MMC_BLK_CMD23) && mmc_op_multi(brq->cmd.opcode) &&
	    (do_rel_wr || !(card->quirks & MMC_QUIRK_BLK_NO_CMD23) ||
	     do_data_tag)) {
		brq->sbc.opcode = MMC_SET_BLOCK_COUNT;
		brq->sbc.arg = brq->data.blocks |
			(do_rel_wr ? (1 << 31) : 0) |
			(do_data_tag ? (1 << 29) : 0);
		brq->sbc.flags = MMC_RSP_R1 | MMC_CMD_AC;
		brq->mrq.sbc = &brq->sbc;
	}

	mmc_set_data_timeout(&brq->data, card);

	brq->data.sg = mqrq->sg;
	brq->data.sg_len = mmc_queue_map_sg(mq, mqrq);

	/*
	 * Adjust the sg list so it is the same size as the
	 * request.
	 */
	if (brq->data.blocks != blk_rq_sectors(req)) {
		int i, data_size = brq->data.blocks << 9;
		struct scatterlist *sg;

		for_each_sg(brq->data.sg, sg, brq->data.sg_len, i) {
			data_size -= sg->length;
			if (data_size <= 0) {
				sg->length += data_size;
				i++;
				break;
			}
		}
		brq->data.sg_len = i;
	}

	mqrq->mmc_active.mrq = &brq->mrq;
	mqrq->mmc_active.err_check = mmc_blk_err_check;

	mmc_queue_bounce_pre(mqrq);
}

static inline u8 mmc_calc_packed_hdr_segs(struct request_queue *q,
					  struct mmc_card *card)
{
	unsigned int hdr_sz = mmc_large_sector(card) ? 4096 : 512;
	unsigned int max_seg_sz = queue_max_segment_size(q);
	unsigned int len, nr_segs = 0;

	do {
		len = min(hdr_sz, max_seg_sz);
		hdr_sz -= len;
		nr_segs++;
	} while (hdr_sz);

	return nr_segs;
}

static u8 mmc_blk_prep_packed_list(struct mmc_queue *mq, struct request *req)
{
	struct request_queue *q = mq->queue;
	struct mmc_card *card = mq->card;
	struct request *cur = req, *next = NULL;
	struct mmc_blk_data *md = mq->data;
	struct mmc_queue_req *mqrq = mq->mqrq_cur;
	bool en_rel_wr = card->ext_csd.rel_param & EXT_CSD_WR_REL_PARAM_EN;
	unsigned int req_sectors = 0, phys_segments = 0;
	unsigned int max_blk_count, max_phys_segs;
	bool put_back = true;
	u8 max_packed_rw = 0;
	u8 reqs = 0;

	if (!(md->flags & MMC_BLK_PACKED_CMD))
		goto no_packed;

	if ((rq_data_dir(cur) == WRITE) &&
	    mmc_host_packed_wr(card->host))
		max_packed_rw = card->ext_csd.max_packed_writes;

	if (max_packed_rw == 0)
		goto no_packed;

	if (mmc_req_rel_wr(cur) &&
	    (md->flags & MMC_BLK_REL_WR) && !en_rel_wr)
		goto no_packed;

	if (mmc_large_sector(card) &&
	    !IS_ALIGNED(blk_rq_sectors(cur), 8))/*lint !e666*/
		goto no_packed;

	mmc_blk_clear_packed(mqrq);

	max_blk_count = min(card->host->max_blk_count,
			    card->host->max_req_size >> 9);
	if (unlikely(max_blk_count > 0xffff))
		max_blk_count = 0xffff;

	max_phys_segs = queue_max_segments(q);
	req_sectors += blk_rq_sectors(cur);
	phys_segments += cur->nr_phys_segments;

	if (rq_data_dir(cur) == WRITE) {
		req_sectors += mmc_large_sector(card) ? 8 : 1;
		phys_segments += mmc_calc_packed_hdr_segs(q, card);
	}

	do {
		if (reqs >= max_packed_rw - 1) {
			put_back = false;
			break;
		}

		spin_lock_irq(q->queue_lock);
		next = blk_fetch_request(q);
		spin_unlock_irq(q->queue_lock);
		if (!next) {
			put_back = false;
			break;
		}

		if (mmc_large_sector(card) &&
		    !IS_ALIGNED(blk_rq_sectors(next), 8))/*lint !e666*/
			break;

		if (next->cmd_flags & REQ_DISCARD ||
		    next->cmd_flags & REQ_FLUSH)
			break;

		if (rq_data_dir(cur) != rq_data_dir(next))
			break;

		if (mmc_req_rel_wr(next) &&
		    (md->flags & MMC_BLK_REL_WR) && !en_rel_wr)
			break;

		req_sectors += blk_rq_sectors(next);
		if (req_sectors > max_blk_count)
			break;

		phys_segments +=  next->nr_phys_segments;
		if (phys_segments > max_phys_segs)
			break;

		list_add_tail(&next->queuelist, &mqrq->packed->list);
		cur = next;
		reqs++;
	} while (1);

	if (put_back) {
		spin_lock_irq(q->queue_lock);
		blk_requeue_request(q, next);
		spin_unlock_irq(q->queue_lock);
	}

	if (reqs > 0) {
		list_add(&req->queuelist, &mqrq->packed->list);
		mqrq->packed->nr_entries = ++reqs;
		mqrq->packed->retries = reqs;
		return reqs;
	}

no_packed:
	mqrq->cmd_type = MMC_PACKED_NONE;
	return 0;
}

static void mmc_blk_packed_hdr_wrq_prep(struct mmc_queue_req *mqrq,
					struct mmc_card *card,
					struct mmc_queue *mq)
{
	struct mmc_blk_request *brq = &mqrq->brq;
	struct request *req = mqrq->req;
	struct request *prq;
	struct mmc_blk_data *md = mq->data;
	struct mmc_packed *packed = mqrq->packed;
	bool do_rel_wr, do_data_tag;
	u32 *packed_cmd_hdr;
	u8 hdr_blocks;
	u8 i = 1;

	BUG_ON(!packed);

	mqrq->cmd_type = MMC_PACKED_WRITE;
	packed->blocks = 0;
	packed->idx_failure = MMC_PACKED_NR_IDX;

	packed_cmd_hdr = packed->cmd_hdr;
	memset(packed_cmd_hdr, 0, sizeof(packed->cmd_hdr));
	packed_cmd_hdr[0] = (packed->nr_entries << 16) |
		(PACKED_CMD_WR << 8) | PACKED_CMD_VER;
	hdr_blocks = mmc_large_sector(card) ? 8 : 1;

	/*
	 * Argument for each entry of packed group
	 */
	list_for_each_entry(prq, &packed->list, queuelist) {
		do_rel_wr = mmc_req_rel_wr(prq) && (md->flags & MMC_BLK_REL_WR);
		do_data_tag = (card->ext_csd.data_tag_unit_size) &&
			(prq->cmd_flags & REQ_META) &&
			(rq_data_dir(prq) == WRITE) &&
			((brq->data.blocks * brq->data.blksz) >=
			 card->ext_csd.data_tag_unit_size);
		/* Argument of CMD23 */
		packed_cmd_hdr[(i * 2)] =
			(do_rel_wr ? MMC_CMD23_ARG_REL_WR : 0) |
			(do_data_tag ? MMC_CMD23_ARG_TAG_REQ : 0) |
			blk_rq_sectors(prq);
		/* Argument of CMD18 or CMD25 */
		packed_cmd_hdr[((i * 2)) + 1] =
			mmc_card_blockaddr(card) ?
			blk_rq_pos(prq) : blk_rq_pos(prq) << 9;
		packed->blocks += blk_rq_sectors(prq);
		i++;
	}

	memset(brq, 0, sizeof(struct mmc_blk_request));
	brq->mrq.cmd = &brq->cmd;
	brq->mrq.data = &brq->data;
	brq->mrq.sbc = &brq->sbc;
	brq->mrq.stop = &brq->stop;

	brq->sbc.opcode = MMC_SET_BLOCK_COUNT;
	brq->sbc.arg = MMC_CMD23_ARG_PACKED | (packed->blocks + hdr_blocks);
	brq->sbc.flags = MMC_RSP_R1 | MMC_CMD_AC;

	brq->cmd.opcode = MMC_WRITE_MULTIPLE_BLOCK;
	brq->cmd.arg = blk_rq_pos(req);
	if (!mmc_card_blockaddr(card))
		brq->cmd.arg <<= 9;
	brq->cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	brq->data.blksz = 512;
	brq->data.blocks = packed->blocks + hdr_blocks;
	brq->data.flags |= MMC_DATA_WRITE;

	brq->stop.opcode = MMC_STOP_TRANSMISSION;
	brq->stop.arg = 0;
	brq->stop.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;

	mmc_set_data_timeout(&brq->data, card);

	brq->data.sg = mqrq->sg;
	brq->data.sg_len = mmc_queue_map_sg(mq, mqrq);

	mqrq->mmc_active.mrq = &brq->mrq;
	mqrq->mmc_active.err_check = mmc_blk_packed_err_check;

	mmc_queue_bounce_pre(mqrq);
}

static int mmc_blk_cmd_err(struct mmc_blk_data *md, struct mmc_card *card,
			   struct mmc_blk_request *brq, struct request *req,
			   int ret)
{
	struct mmc_queue_req *mq_rq;
	mq_rq = container_of(brq, struct mmc_queue_req, brq);

	/*
	 * If this is an SD card and we're writing, we can first
	 * mark the known good sectors as ok.
	 *
	 * If the card is not SD, we can still ok written sectors
	 * as reported by the controller (which might be less than
	 * the real number of written sectors, but never more).
	 */
	if (mmc_card_sd(card)) {
		u32 blocks;

		blocks = mmc_sd_num_wr_blocks(card);
		if (blocks != (u32)-1) {
			ret = blk_end_request(req, 0, blocks << 9);
		}
	} else {
		if (!mmc_packed_cmd(mq_rq->cmd_type))
			ret = blk_end_request(req, 0, brq->data.bytes_xfered);
	}
	return ret;
}

static int mmc_blk_end_packed_req(struct mmc_queue_req *mq_rq)
{
	struct request *prq;
	struct mmc_packed *packed = mq_rq->packed;
	int idx = packed->idx_failure, i = 0;
	int ret = 0;

	BUG_ON(!packed);

	while (!list_empty(&packed->list)) {
		prq = list_entry_rq(packed->list.next);
		if (idx == i) {
			/* retry from error index */
			packed->nr_entries -= idx;
			mq_rq->req = prq;
			ret = 1;

			if (packed->nr_entries == MMC_PACKED_NR_SINGLE) {
				list_del_init(&prq->queuelist);
				mmc_blk_clear_packed(mq_rq);
			}
			return ret;
		}
		list_del_init(&prq->queuelist);
		blk_end_request(prq, 0, blk_rq_bytes(prq));
		i++;
	}

	mmc_blk_clear_packed(mq_rq);
	return ret;
}

static void mmc_blk_abort_packed_req(struct mmc_queue_req *mq_rq)
{
	struct request *prq;
	struct mmc_packed *packed = mq_rq->packed;

	BUG_ON(!packed);

	while (!list_empty(&packed->list)) {
		prq = list_entry_rq(packed->list.next);
		list_del_init(&prq->queuelist);
		blk_end_request(prq, -EIO, blk_rq_bytes(prq));
	}

	mmc_blk_clear_packed(mq_rq);
}

static void mmc_blk_revert_packed_req(struct mmc_queue *mq,
				      struct mmc_queue_req *mq_rq)
{
	struct request *prq;
	struct request_queue *q = mq->queue;
	struct mmc_packed *packed = mq_rq->packed;

	BUG_ON(!packed);

	while (!list_empty(&packed->list)) {
		prq = list_entry_rq(packed->list.prev);
		if (prq->queuelist.prev != &packed->list) {
			list_del_init(&prq->queuelist);
			spin_lock_irq(q->queue_lock);
			blk_requeue_request(mq->queue, prq);
			spin_unlock_irq(q->queue_lock);
		} else {
			list_del_init(&prq->queuelist);
		}
	}

	mmc_blk_clear_packed(mq_rq);
}

int mmc_blk_cmdq_hangup(struct mmc_card *card)
{
	struct mmc_cmdq_context_info *ctx_info;
	unsigned long timeout = (1 * 60 * 1000);
	int ret = 0;

	if (card->ext_csd.cmdq_mode_en) {
		ctx_info = &card->host->cmdq_ctx;
		spin_lock_bh(&ctx_info->cmdq_ctx_lock);
		ctx_info->rpmb_in_wait = true;
		spin_unlock_bh(&ctx_info->cmdq_ctx_lock);
		/* wait for cmdq req handle done.*/
		while (ctx_info->active_reqs) {
			if (timeout == 0) {
				pr_err("%s: wait cmdq complete reqs timeout !\n", __func__);
			        return -ETIMEDOUT;
			}
			timeout--;
			mdelay(1);
		}
		/* disable CQ mode for ioctl */
		ret = mmc_blk_cmdq_switch(card, NULL, false);
	}
	return ret;
}
EXPORT_SYMBOL(mmc_blk_cmdq_hangup);

void mmc_blk_cmdq_restore(struct mmc_card *card)
{
	struct mmc_cmdq_context_info *ctx_info;
	struct mmc_blk_data *md = dev_get_drvdata(&card->dev);

	if (card->ext_csd.cmdq_mode_en) {
		ctx_info = &card->host->cmdq_ctx;
		spin_lock_bh(&ctx_info->cmdq_ctx_lock);
		ctx_info->rpmb_in_wait = false;
		if (test_and_clear_bit(0, &ctx_info->req_starved)) {
			spin_unlock_bh(&ctx_info->cmdq_ctx_lock);
			/*start handle cmdq req*/
			blk_run_queue(md->queue.queue);
		} else {
			spin_unlock_bh(&ctx_info->cmdq_ctx_lock);
		}
	}
}
EXPORT_SYMBOL(mmc_blk_cmdq_restore);

static int mmc_blk_cmdq_start_req(struct mmc_host *host,
				   struct mmc_cmdq_req *cmdq_req)
{
	struct mmc_request *mrq = &cmdq_req->mrq;

	/*cmdq_req->cmdq_req_flags |= QBR;*/

	mrq->done = mmc_blk_cmdq_req_done;
	return mmc_cmdq_start_req(host, cmdq_req);
}

/* prepare for non-data commands */
struct mmc_cmdq_req *mmc_cmdq_prep_dcmd(
		struct mmc_queue_req *mqrq, struct mmc_queue *mq)
{
	struct request *req = mqrq->req;
	struct mmc_cmdq_req *cmdq_req = &mqrq->mmc_cmdq_req;

	memset(&mqrq->mmc_cmdq_req, 0, sizeof(struct mmc_cmdq_req));

	cmdq_req->mrq.data = NULL;
	cmdq_req->cmd_flags = req->cmd_flags;
	cmdq_req->mrq.req = mqrq->req;
	req->special = mqrq;
	cmdq_req->cmdq_req_flags |= DCMD;
	cmdq_req->mrq.cmdq_req = cmdq_req;

	return &mqrq->mmc_cmdq_req;
}
EXPORT_SYMBOL(mmc_cmdq_prep_dcmd);

#define IS_RT_CLASS_REQ(x)     \
	(IOPRIO_PRIO_CLASS(req_get_ioprio(x)) == IOPRIO_CLASS_RT)

static struct mmc_cmdq_req *mmc_blk_cmdq_rw_prep(
		struct mmc_queue_req *mqrq, struct mmc_queue *mq)
{
	struct mmc_card *card = mq->card;
	struct request *req = mqrq->req;
	struct mmc_blk_data *md = mq->data;
	bool do_rel_wr = mmc_req_rel_wr(req) && (md->flags & MMC_BLK_REL_WR);
	bool do_data_tag;
	bool read_dir = (rq_data_dir(req) == READ);
	bool prio = IS_RT_CLASS_REQ(req);
	struct mmc_cmdq_req *cmdq_rq = &mqrq->mmc_cmdq_req;
	u32 map_sg_len = 0;

	memset(&mqrq->mmc_cmdq_req, 0, sizeof(struct mmc_cmdq_req));

	cmdq_rq->tag = req->tag;
	if (read_dir) {
		cmdq_rq->cmdq_req_flags |= DIR;
		cmdq_rq->data.flags = MMC_DATA_READ;
	} else {
		cmdq_rq->data.flags = MMC_DATA_WRITE;
	}
	if (prio)
		cmdq_rq->cmdq_req_flags |= PRIO;

	if (do_rel_wr)
		cmdq_rq->cmdq_req_flags |= REL_WR;

	cmdq_rq->data.blocks = blk_rq_sectors(req);
	cmdq_rq->blk_addr = blk_rq_pos(req);
	cmdq_rq->data.blksz = MMC_CARD_CMDQ_BLK_SIZE;
	cmdq_rq->data.bytes_xfered = 0;

	mmc_set_data_timeout(&cmdq_rq->data, card);

	do_data_tag = (card->ext_csd.data_tag_unit_size) &&
		(req->cmd_flags & REQ_META) &&
		(rq_data_dir(req) == WRITE) &&
		((cmdq_rq->data.blocks * cmdq_rq->data.blksz) >=
		 card->ext_csd.data_tag_unit_size);
	if (do_data_tag)
		cmdq_rq->cmdq_req_flags |= DAT_TAG;
	cmdq_rq->data.sg = mqrq->sg;
	cmdq_rq->data.sg_len = mmc_queue_map_sg(mq, mqrq);
	map_sg_len = cmdq_rq->data.sg_len;

	/*
	 * Adjust the sg list so it is the same size as the
	 * request.
	 */
	if (cmdq_rq->data.blocks > card->host->max_blk_count)
		cmdq_rq->data.blocks = card->host->max_blk_count;

	if (cmdq_rq->data.blocks != blk_rq_sectors(req)) {
		int i, data_size = cmdq_rq->data.blocks << 9;
		struct scatterlist *sg;

		for_each_sg(cmdq_rq->data.sg, sg, cmdq_rq->data.sg_len, i) {
			data_size -= sg->length;
			if (data_size <= 0) {
				sg->length += data_size;
				i++;
				break;
			}
		}
		cmdq_rq->data.sg_len = i;
	}

	mqrq->mmc_cmdq_req.cmd_flags = req->cmd_flags;
	mqrq->mmc_cmdq_req.mrq.req = mqrq->req;
	mqrq->mmc_cmdq_req.mrq.cmdq_req = &mqrq->mmc_cmdq_req;
	mqrq->mmc_cmdq_req.mrq.data = &mqrq->mmc_cmdq_req.data;
	/* mrq.cmd: no opcode, just for record error */
	mqrq->mmc_cmdq_req.mrq.cmd = &mqrq->mmc_cmdq_req.cmd;
	mqrq->req->special = mqrq;

	pr_debug("%s: %s: mrq: 0x%p req: 0x%p mqrq: 0x%p bytes to xf: %d mmc_cmdq_req: 0x%p card-addr: 0x%08x data_sg_len: %d map_sg_len: %d dir(r-1/w-0): %d\n",
		 mmc_hostname(card->host), __func__, &mqrq->mmc_cmdq_req.mrq,
		 mqrq->req, mqrq, (cmdq_rq->data.blocks * cmdq_rq->data.blksz),
		 cmdq_rq, cmdq_rq->blk_addr, cmdq_rq->data.sg_len, map_sg_len,
		 (cmdq_rq->cmdq_req_flags & DIR) ? 1 : 0);

    trace_mmc_blk_cmdq_rw_start(cmdq_rq->cmdq_req_flags, cmdq_rq->tag, cmdq_rq->blk_addr, 
            (cmdq_rq->data.blocks * cmdq_rq->data.blksz));

	return &mqrq->mmc_cmdq_req;
}

static int mmc_blk_cmdq_issue_rw_rq(struct mmc_queue *mq, struct request *req)
{
	struct mmc_queue_req *active_mqrq;
	struct mmc_card *card = mq->card;
	struct mmc_host *host = card->host;
	struct mmc_cmdq_req *mc_rq;
	int ret = 0;

	BUG_ON((req->tag < 0) || (req->tag > card->ext_csd.cmdq_depth));
	BUG_ON(test_and_set_bit(req->tag, &host->cmdq_ctx.active_reqs));

	active_mqrq = &mq->mqrq_cmdq[req->tag];
	active_mqrq->req = req;

	mc_rq = mmc_blk_cmdq_rw_prep(active_mqrq, mq);


	ret = mmc_blk_cmdq_start_req(card->host, mc_rq);
	return ret;
}

void mmc_blk_cmdq_dcmd_done(struct mmc_request *mrq)
{
	complete(&mrq->cmdq_completion);
}

static int mmc_blk_cmdq_wait_for_dcmd(struct mmc_host *host,
				   struct mmc_cmdq_req *cmdq_req)
{
	struct mmc_request *mrq = &cmdq_req->mrq;
	int ret = 0;

	init_completion(&mrq->cmdq_completion);
	mrq->done = mmc_blk_cmdq_dcmd_done;
	mrq->host = host;
	mmc_start_cmdq_request(host, mrq);
	ret = wait_for_completion_timeout(&mrq->cmdq_completion,
			msecs_to_jiffies(60000));
	ret = ret ? 0 : -ETIMEDOUT;

	return ret;
}

static int mmc_cmdq_do_erase(struct mmc_card *card, struct mmc_queue *mq, struct request *req, unsigned int from,
			unsigned int to, unsigned int arg)
{
	unsigned int qty = 0;
	unsigned int fr, nr;
	int err;
	struct mmc_queue_req *active_mqrq;
	struct mmc_cmdq_context_info *ctx_info;
	struct mmc_cmdq_req *cmdq_req;

	fr = from;
	nr = to - from + 1;
	trace_mmc_blk_erase_start(arg, fr, nr);

	/*
	 * qty is used to calculate the erase timeout which depends on how many
	 * erase groups (or allocation units in SD terminology) are affected.
	 * We count erasing part of an erase group as one erase group.
	 * For SD, the allocation units are always a power of 2.  For MMC, the
	 * erase group size is almost certainly also power of 2, but it does not
	 * seem to insist on that in the JEDEC standard, so we fall back to
	 * division in that case.  SD may not specify an allocation unit size,
	 * in which case the timeout is based on the number of write blocks.
	 *
	 * Note that the timeout for secure trim 2 will only be correct if the
	 * number of erase groups specified is the same as the total of all
	 * preceding secure trim 1 commands.  Since the power may have been
	 * lost since the secure trim 1 commands occurred, it is generally
	 * impossible to calculate the secure trim 2 timeout correctly.
	 */
	if (card->erase_shift)
		qty += ((to >> card->erase_shift) -
			(from >> card->erase_shift)) + 1;
	else if (mmc_card_sd(card))
		qty += to - from + 1;
	else
		qty += ((to / card->erase_size) -
			(from / card->erase_size)) + 1;

	if (!mmc_card_blockaddr(card)) {
		from <<= 9;
		to <<= 9;
	}

	ctx_info = &card->host->cmdq_ctx;
	active_mqrq = &mq->mqrq_cmdq[req->tag];
	active_mqrq->req = req;
	cmdq_req = mmc_cmdq_prep_dcmd(active_mqrq, mq);
	cmdq_req->cmdq_req_flags |= QBR;
	cmdq_req->mrq.cmd = &cmdq_req->cmd;
	cmdq_req->tag = req->tag;
	cmdq_req->cmd.opcode = MMC_ERASE_GROUP_START;
	cmdq_req->cmd.arg = from;
	cmdq_req->cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;

	err = mmc_blk_cmdq_wait_for_dcmd(card->host, cmdq_req);
	if (err) {
		pr_err("mmc_erase: group start error %d.", err);
		err = -EIO;
		goto out;
	}

	active_mqrq = &mq->mqrq_cmdq[req->tag];
	active_mqrq->req = req;
	cmdq_req = mmc_cmdq_prep_dcmd(active_mqrq, mq);
	cmdq_req->cmdq_req_flags |= QBR;
	cmdq_req->mrq.cmd = &cmdq_req->cmd;
	cmdq_req->tag = req->tag;
	cmdq_req->cmd.opcode = MMC_ERASE_GROUP_END;
	cmdq_req->cmd.arg = to;
	cmdq_req->cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;

	err = mmc_blk_cmdq_wait_for_dcmd(card->host, cmdq_req);
	if (err) {
		pr_err("mmc_erase: group end error %d.\n", err);
		err = -EIO;
		goto out;
	}

	active_mqrq = &mq->mqrq_cmdq[req->tag];
	active_mqrq->req = req;
	cmdq_req = mmc_cmdq_prep_dcmd(active_mqrq, mq);
	cmdq_req->cmdq_req_flags |= QBR;
	cmdq_req->mrq.cmd = &cmdq_req->cmd;
	cmdq_req->tag = req->tag;
	cmdq_req->cmd.opcode = MMC_ERASE;
	cmdq_req->cmd.arg = arg;
	cmdq_req->cmd.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;
	cmdq_req->cmd.busy_timeout = mmc_erase_timeout(card, arg, qty);

	err = mmc_blk_cmdq_wait_for_dcmd(card->host, cmdq_req);
	if (err) {
		pr_err("mmc_erase: erase error %d.\n", err);
		err = -EIO;
		goto out;
	}

out:
	trace_mmc_blk_erase_end(arg, fr, nr);
	return err;
}

static int mmc_cmdq_erase(struct mmc_card *card, struct mmc_queue *mq, struct request *req,
		unsigned int from, unsigned int nr, unsigned int arg)
{
	unsigned int rem, to = from + nr;

	if (!(card->host->caps & MMC_CAP_ERASE) ||
	    !(card->csd.cmdclass & CCC_ERASE))
		return -EOPNOTSUPP;

	if (!card->erase_size)
		return -EOPNOTSUPP;

	if (mmc_card_sd(card) && arg != MMC_ERASE_ARG)
		return -EOPNOTSUPP;

	if ((arg & MMC_SECURE_ARGS) &&
	    !(card->ext_csd.sec_feature_support & EXT_CSD_SEC_ER_EN))
		return -EOPNOTSUPP;

	if ((arg & MMC_TRIM_ARGS) &&
	    !(card->ext_csd.sec_feature_support & EXT_CSD_SEC_GB_CL_EN))
		return -EOPNOTSUPP;

	if (arg == MMC_SECURE_ERASE_ARG) {
		if (from % card->erase_size || nr % card->erase_size)
			return -EINVAL;
	}

	if (arg == MMC_ERASE_ARG) {
		rem = from % card->erase_size;
		if (rem) {
			rem = card->erase_size - rem;
			from += rem;
			if (nr > rem)
				nr -= rem;
			else
				return 0;
		}
		rem = nr % card->erase_size;
		if (rem)
			nr -= rem;
	}

	if (nr == 0)
		return 0;

	to = from + nr;

	if (to <= from)
		return -EINVAL;

	/* 'from' and 'to' are inclusive */
	to -= 1;

	return mmc_cmdq_do_erase(card, mq, req, from, to, arg);
}

static int mmc_blk_cmdq_issue_discard_rq(struct mmc_queue *mq, struct request *req)
{
	struct mmc_queue_req *active_mqrq;
	struct mmc_card *card = mq->card;
	struct mmc_host *host;
	struct mmc_cmdq_req *cmdq_req;
	struct mmc_cmdq_context_info *ctx_info;
	unsigned int from, nr, arg;
	int err = 0;

	BUG_ON(!card);
	host = card->host;
	BUG_ON(!host);
	BUG_ON((req->tag < 0) || (req->tag > card->ext_csd.cmdq_depth));
	BUG_ON(test_and_set_bit(req->tag, &host->cmdq_ctx.active_reqs));

	ctx_info = &host->cmdq_ctx;

	if (!mmc_can_erase(card)) {
		err = -EOPNOTSUPP;
		goto out;
	}

	from = blk_rq_pos(req);
	nr = blk_rq_sectors(req);

	if (mmc_can_discard(card))
		arg = MMC_DISCARD_ARG;
	else if (mmc_can_trim(card))
		arg = MMC_TRIM_ARG;
	else
		arg = MMC_ERASE_ARG;

	spin_lock_bh(&ctx_info->cmdq_ctx_lock);
	ctx_info->active_dcmd = true;
	spin_unlock_bh(&ctx_info->cmdq_ctx_lock);

	if (card->quirks & MMC_QUIRK_INAND_CMD38) {
		active_mqrq = &mq->mqrq_cmdq[req->tag];
		active_mqrq->req = req;
		cmdq_req = mmc_cmdq_prep_dcmd(active_mqrq, mq);
		cmdq_req->cmdq_req_flags |= QBR;
		cmdq_req->mrq.cmd = &cmdq_req->cmd;
		cmdq_req->tag = req->tag;

		err = __mmc_switch_cmdq_mode(cmdq_req->mrq.cmd, EXT_CSD_CMD_SET_NORMAL,
				INAND_CMD38_ARG_EXT_CSD,
				arg == MMC_TRIM_ARG ? INAND_CMD38_ARG_TRIM : INAND_CMD38_ARG_ERASE,
				0, true, true);
		if (err)
			goto out;
		err = mmc_blk_cmdq_wait_for_dcmd(card->host, cmdq_req);
		if (err)
			goto out;
	}

	err = mmc_cmdq_erase(card, mq, req, from, nr, arg);

out:
	blk_complete_request(req);
	return err;
}

static int mmc_blk_cmdq_issue_secdiscard_rq(struct mmc_queue *mq,
				       struct request *req)
{
	struct mmc_queue_req *active_mqrq;
	struct mmc_card *card = mq->card;
	struct mmc_host *host;
	struct mmc_cmdq_req *cmdq_req;
	struct mmc_cmdq_context_info *ctx_info;
	unsigned int from, nr, arg;
	int err = 0;

	BUG_ON(!card);
	host = card->host;
	BUG_ON(!host);
	BUG_ON((req->tag < 0) || (req->tag > card->ext_csd.cmdq_depth));
	BUG_ON(test_and_set_bit(req->tag, &host->cmdq_ctx.active_reqs));

	ctx_info = &host->cmdq_ctx;

	if (!(mmc_can_secure_erase_trim(card))) {
		err = -EOPNOTSUPP;
		goto out;
	}

	from = blk_rq_pos(req);
	nr = blk_rq_sectors(req);

	if (mmc_can_trim(card) && !mmc_erase_group_aligned(card, from, nr))
		arg = MMC_SECURE_TRIM1_ARG;
	else
		arg = MMC_SECURE_ERASE_ARG;

	spin_lock_bh(&ctx_info->cmdq_ctx_lock);
	ctx_info->active_dcmd = true;
	spin_unlock_bh(&ctx_info->cmdq_ctx_lock);

	if (card->quirks & MMC_QUIRK_INAND_CMD38) {
		active_mqrq = &mq->mqrq_cmdq[req->tag];
		active_mqrq->req = req;
		cmdq_req = mmc_cmdq_prep_dcmd(active_mqrq, mq);
		cmdq_req->cmdq_req_flags |= QBR;
		cmdq_req->mrq.cmd = &cmdq_req->cmd;
		cmdq_req->tag = req->tag;
		err = __mmc_switch_cmdq_mode(cmdq_req->mrq.cmd, EXT_CSD_CMD_SET_NORMAL,
				INAND_CMD38_ARG_EXT_CSD,
				arg == MMC_SECURE_TRIM1_ARG ? INAND_CMD38_ARG_SECTRIM1 : INAND_CMD38_ARG_SECERASE,
				0, true, true);
		if (err)
			goto out;
		err = mmc_blk_cmdq_wait_for_dcmd(card->host, cmdq_req);
		if (err)
			goto out;
	}
	err = mmc_cmdq_erase(card, mq, req, from, nr, arg);
	if (err)
		goto out;

	if (arg == MMC_SECURE_TRIM1_ARG) {
		if (card->quirks & MMC_QUIRK_INAND_CMD38) {
			active_mqrq = &mq->mqrq_cmdq[req->tag];
			active_mqrq->req = req;
			cmdq_req = mmc_cmdq_prep_dcmd(active_mqrq, mq);
			cmdq_req->cmdq_req_flags |= QBR;
			cmdq_req->mrq.cmd = &cmdq_req->cmd;
			cmdq_req->tag = req->tag;
			err = __mmc_switch_cmdq_mode(cmdq_req->mrq.cmd, EXT_CSD_CMD_SET_NORMAL,
					INAND_CMD38_ARG_EXT_CSD,
					INAND_CMD38_ARG_SECTRIM2,
					0, true, true);
			if (err)
				goto out;
			err = mmc_blk_cmdq_wait_for_dcmd(card->host, cmdq_req);
			if (err)
				goto out;
		}
		err = mmc_cmdq_erase(card, mq, req, from, nr, MMC_SECURE_TRIM2_ARG);
		if (err)
			goto out;
	}

out:
	blk_complete_request(req);

	return err ? 0 : 1;
}

/*
 * Issues a dcmd request
 * FIXME:
 *	Try to pull another request from queue and prepare it in the
 *	meantime. If its not a dcmd it can be issued as well.
 */
int mmc_blk_cmdq_issue_flush_rq(struct mmc_queue *mq, struct request *req)
{
	int err;
	struct mmc_queue_req *active_mqrq;
	struct mmc_card *card = mq->card;
	struct mmc_host *host;
	struct mmc_cmdq_req *cmdq_req;
	struct mmc_cmdq_context_info *ctx_info;

	BUG_ON(!card);
	host = card->host;
	BUG_ON(!host);
	BUG_ON((req->tag < 0) || (req->tag > card->ext_csd.cmdq_depth));
	BUG_ON(test_and_set_bit(req->tag, &host->cmdq_ctx.active_reqs));

	ctx_info = &host->cmdq_ctx;
#if 0
	if (in_irq() || irqs_disabled() || in_serving_softirq()) {
		lock_irq_flag = 0;
	} else {
		lock_irq_flag = 1;
	}

	if (0 == lock_irq_flag)
		spin_lock(&ctx_info->cmdq_ctx_lock);
	else
		spin_lock_bh(&ctx_info->cmdq_ctx_lock);
#else
	spin_lock_bh(&ctx_info->cmdq_ctx_lock);
#endif
	ctx_info->active_dcmd = true;
#if 0
	if (0 == lock_irq_flag)
		spin_unlock(&ctx_info->cmdq_ctx_lock);
	else
		spin_unlock_bh(&ctx_info->cmdq_ctx_lock);
#else
	spin_unlock_bh(&ctx_info->cmdq_ctx_lock);
#endif
	active_mqrq = &mq->mqrq_cmdq[req->tag];
	active_mqrq->req = req;

	cmdq_req = mmc_cmdq_prep_dcmd(active_mqrq, mq);
	cmdq_req->cmdq_req_flags |= QBR;
	cmdq_req->mrq.cmd = &cmdq_req->cmd;
	cmdq_req->tag = req->tag;

	// need this??? can do this???
	err = __mmc_switch_cmdq_mode(cmdq_req->mrq.cmd, EXT_CSD_CMD_SET_NORMAL,
					EXT_CSD_FLUSH_CACHE, 1,
				     MMC_FLUSH_REQ_TIMEOUT_MS, true, true);
	if (err)
		return err;

	err = mmc_blk_cmdq_start_req(card->host, cmdq_req);
	return err;
}
EXPORT_SYMBOL(mmc_blk_cmdq_issue_flush_rq);

/* invoked by block layer in softirq context */
void mmc_blk_cmdq_complete_rq(struct request *rq)
{
	struct mmc_queue_req *mq_rq = rq->special;
	struct mmc_request *mrq = &mq_rq->mmc_cmdq_req.mrq;
	struct mmc_host *host = mrq->host;
	struct mmc_cmdq_context_info *ctx_info = &host->cmdq_ctx;
	struct mmc_cmdq_req *cmdq_req = &mq_rq->mmc_cmdq_req;
	struct request_queue *q = rq->q;
	int err = 0;

	if (mrq->cmd && mrq->cmd->error)
		err = mrq->cmd->error;
	else if (mrq->data && mrq->data->error)
		err = mrq->data->error;

	mmc_cmdq_post_req(host, mrq, err);
	spin_lock(&ctx_info->cmdq_ctx_lock);
	if (err) {
		pr_err("%s: %s: txfr error: %d\n", mmc_hostname(mrq->host),
		       __func__, err);

		if (mmc_cmdq_halt(host, true))
			BUG();
		ctx_info->curr_state |= CMDQ_STATE_ERR;
		/* TODO: wake-up kernel thread to handle error */
	}

	BUG_ON(!test_and_clear_bit(cmdq_req->tag,
				   &ctx_info->active_reqs));
	if (cmdq_req->cmdq_req_flags & DCMD) {
		ctx_info->active_dcmd = false;
		spin_unlock(&ctx_info->cmdq_ctx_lock);
		blk_end_request_all(rq, 0);

	} else {
		spin_unlock(&ctx_info->cmdq_ctx_lock);
        trace_mmc_blk_cmdq_rw_end(cmdq_req->cmdq_req_flags, cmdq_req->tag, cmdq_req->blk_addr, 
            cmdq_req->data.bytes_xfered);
		blk_end_request(rq, 0, cmdq_req->data.bytes_xfered);
	}

	spin_lock(&ctx_info->cmdq_ctx_lock);
	if (test_and_clear_bit(0, &ctx_info->req_starved)) {
		spin_unlock(&ctx_info->cmdq_ctx_lock);
		blk_run_queue(q);
	} else {
		spin_unlock(&ctx_info->cmdq_ctx_lock);
	}
}

/*
 * Complete reqs from block layer softirq context
 * Invoked in irq context
 */
void mmc_blk_cmdq_req_done(struct mmc_request *mrq)
{
	struct request *req = mrq->req;

	blk_complete_request(req);
}
EXPORT_SYMBOL(mmc_blk_cmdq_req_done);

static int mmc_blk_issue_rw_rq(struct mmc_queue *mq, struct request *rqc)
{
	struct mmc_blk_data *md = mq->data;
	struct mmc_card *card = md->queue.card;
	struct mmc_blk_request *brq = &mq->mqrq_cur->brq;
	int ret = 1, disable_multi = 0, retry = 0, type;
	enum mmc_blk_status status;
	struct mmc_queue_req *mq_rq;
	struct request *req = rqc;
	struct mmc_async_req *areq;
	const u8 packed_nr = 2;
	u8 reqs = 0;
#ifdef CONFIG_HW_SD_HEALTH_DETECT
	unsigned long long time1 = 0;
	unsigned int rq_byte=0;
#endif

	if (!rqc && !mq->mqrq_prev->req)
		return 0;

#ifdef CONFIG_HW_SD_HEALTH_DETECT
	if(!strncmp(current->comm,"mmcqd/1",strlen("mmcqd/1")))
	{
		
		mmc_trigger_ro_check(rqc,md->disk,md->read_only);
		time1 = sched_clock();
		rq_byte = mmc_calculate_ioworkload_and_rwspeed(time1,rqc,md->disk);
	}
#endif
	if (rqc)
		reqs = mmc_blk_prep_packed_list(mq, rqc);

	do {
		if (rqc) {
			/*
			 * When 4KB native sector is enabled, only 8 blocks
			 * multiple read or write is allowed
			 */
			if ((brq->data.blocks & 0x07) &&
			    (card->ext_csd.data_sector_size == 4096)) {
				pr_err("%s: Transfer size is not 4KB sector size aligned\n",
					req->rq_disk->disk_name);
				mq_rq = mq->mqrq_cur;
				goto cmd_abort;
			}

			if (reqs >= packed_nr)
				mmc_blk_packed_hdr_wrq_prep(mq->mqrq_cur,
							    card, mq);
			else
				mmc_blk_rw_rq_prep(mq->mqrq_cur, card, 0, mq);
			areq = &mq->mqrq_cur->mmc_active;
		} else
			areq = NULL;
		areq = mmc_start_req(card->host, areq, (int *) &status);
		if (!areq) {
			if (status == MMC_BLK_NEW_REQUEST)
				set_bit(MMC_QUEUE_NEW_REQUEST_BIT, &mq->flags);
			return 0;
		}

		mq_rq = container_of(areq, struct mmc_queue_req, mmc_active);
		brq = &mq_rq->brq;
		req = mq_rq->req;
		type = rq_data_dir(req) == READ ? MMC_BLK_READ : MMC_BLK_WRITE;
		mmc_queue_bounce_post(mq_rq);

#ifdef CONFIG_HW_SD_HEALTH_DETECT
		if(mmc_card_sd(card))
		{
		mmc_diag_sd_health_status(md->disk,mmc_get_rw_status(status));
		}
#endif
		switch (status) {
		case MMC_BLK_SUCCESS:
		case MMC_BLK_PARTIAL:
			/*
			 * A block was successfully transferred.
			 */
			mmc_blk_reset_success(md, type);

			if (mmc_packed_cmd(mq_rq->cmd_type)) {
				ret = mmc_blk_end_packed_req(mq_rq);
				break;
			} else {
				ret = blk_end_request(req, 0,
						brq->data.bytes_xfered);
			}

			/*
			 * If the blk_end_request function returns non-zero even
			 * though all data has been transferred and no errors
			 * were returned by the host controller, it's a bug.
			 */
			if (status == MMC_BLK_SUCCESS && ret) {
				pr_err("%s BUG rq_tot %d d_xfer %d\n",
				       __func__, blk_rq_bytes(req),
				       brq->data.bytes_xfered);
				rqc = NULL;
				goto cmd_abort;
			}
			break;
		case MMC_BLK_CMD_ERR:
			ret = mmc_blk_cmd_err(md, card, brq, req, ret);
			if (mmc_blk_reset(md, card->host, type))
				goto cmd_abort;
			if (!ret)
				goto start_new_req;
			break;
		case MMC_BLK_RETRY:
			if (retry++ < 5)
				break;
			/* Fall through */
		case MMC_BLK_ABORT:
			if (!mmc_blk_reset(md, card->host, type))
				break;
			goto cmd_abort;
		case MMC_BLK_DATA_ERR: {
			int err;

			err = mmc_blk_reset(md, card->host, type);
			if (!err)
				break;
			goto cmd_abort;
			/* Fall through */
		}
		case MMC_BLK_ECC_ERR:
			if (!mmc_blk_reset(md, card->host, type))
				break;
			if (brq->data.blocks > 1) {
				/* Redo read one sector at a time */
				pr_warning("%s: retrying using single block read\n",
					   req->rq_disk->disk_name);
				disable_multi = 1;
				break;
			}
			/*
			 * After an error, we redo I/O one sector at a
			 * time, so we only reach here after trying to
			 * read a single sector.
			 */
			ret = blk_end_request(req, -EIO,
						brq->data.blksz);
			if (!ret)
				goto start_new_req;
			break;
		case MMC_BLK_NOMEDIUM:
			goto cmd_abort;
		default:
			pr_err("%s: Unhandled return value (%d)",
					req->rq_disk->disk_name, status);
			goto cmd_abort;
		}

		if (ret) {
			if (mmc_packed_cmd(mq_rq->cmd_type)) {
				if (!mq_rq->packed->retries)
					goto cmd_abort;
				mmc_blk_packed_hdr_wrq_prep(mq_rq, card, mq);
				mmc_start_req(card->host,
					      &mq_rq->mmc_active, NULL);
			} else {

				/*
				 * In case of a incomplete request
				 * prepare it again and resend.
				 */
				mmc_blk_rw_rq_prep(mq_rq, card,
						disable_multi, mq);
				mmc_start_req(card->host,
						&mq_rq->mmc_active, NULL);
			}
		}
	} while (ret);

#ifdef CONFIG_HW_SD_HEALTH_DETECT
	if(!strncmp(current->comm,"mmcqd/1",strlen("mmcqd/1")))
	{
		mmc_calculate_rw_size(time1,rq_byte,rqc);
	}
#endif
	return 1;

 cmd_abort:
	if (mmc_packed_cmd(mq_rq->cmd_type)) {
		mmc_blk_abort_packed_req(mq_rq);
	} else {
		if (mmc_card_removed(card))
			req->cmd_flags |= REQ_QUIET;
		while (ret)
			ret = blk_end_request(req, -EIO,
					blk_rq_cur_bytes(req));
	}

 start_new_req:
	if (rqc) {
		if (mmc_card_removed(card)) {
			rqc->cmd_flags |= REQ_QUIET;
			blk_end_request_all(rqc, -EIO);
		} else {
			/*
			 * If current request is packed, it needs to put back.
			 */
			if (mmc_packed_cmd(mq->mqrq_cur->cmd_type))
				mmc_blk_revert_packed_req(mq, mq->mqrq_cur);

			mmc_blk_rw_rq_prep(mq->mqrq_cur, card, 0, mq);
			mmc_start_req(card->host,
				      &mq->mqrq_cur->mmc_active, NULL);
		}
	}

	return 0;
}

static int mmc_blk_cmdq_issue_rq(struct mmc_queue *mq, struct request *req)
{
	int ret = 0;
	struct mmc_blk_data *md = mq->data;
	struct mmc_card *card = md->queue.card;
	unsigned int cmd_flags = req->cmd_flags;

	mmc_claim_host(card->host);

	if (mmc_card_suspended(card)) {
		pr_err("cmdq issue rq in suspend!!!!\n");
		if ((!(cmd_flags & REQ_DISCARD)) && (!(cmd_flags & REQ_FLUSH)))
			pr_err("%s<cmdq>: req addr: 0x%lx blocks: %d dir(r-1/w-0): %d\n",
				mmc_hostname(card->host), blk_rq_pos(req),
				blk_rq_sectors(req), (rq_data_dir(req) == READ) ? 1 : 0);
		spin_lock_irq(mq->queue->queue_lock);
		blk_requeue_request(mq->queue, req);
		spin_unlock_irq(mq->queue->queue_lock);
		goto switch_failure;
	}

	ret = mmc_blk_part_switch(card, md);
	if (ret) {
		pr_err("%s: %s: partition switch failed %d\n",
				md->disk->disk_name, __func__, ret);
		blk_end_request_all(req, ret);
		goto switch_failure;
	}

	ret = mmc_blk_cmdq_switch(card, md, true);
	if (ret) {
		pr_err("%s curr part config is %u\n", __func__, card->ext_csd.part_config);
		/* TODO: put a limit on the number of requeues if switch fails
		 * and if possible disable cmd queing for buggy cards.
		 */
		spin_lock_irq(mq->queue->queue_lock);
		blk_requeue_request(mq->queue, req);
		spin_unlock_irq(mq->queue->queue_lock);
		goto switch_failure;
	}

	if (cmd_flags & REQ_DISCARD) {
		 if (req->cmd_flags & REQ_SECURE &&
			!(card->quirks & MMC_QUIRK_SEC_ERASE_TRIM_BROKEN))
			ret = mmc_blk_cmdq_issue_secdiscard_rq(mq, req);
		 else
			ret = mmc_blk_cmdq_issue_discard_rq(mq, req);
	} else if (cmd_flags & REQ_FLUSH) {
		ret = mmc_blk_cmdq_issue_flush_rq(mq, req);
	} else {
		ret = mmc_blk_cmdq_issue_rw_rq(mq, req);
	}
	/*EHOSTDOWN means that cq_host->enabled is false when cmdq_request;
	 *we need re-enable the cmdq feature and requeue the
	 *failed request
	 */
	if (-EHOSTDOWN == ret) {
		ret = mmc_blk_cmdq_switch(card, NULL, false);
		if (ret)
			pr_err("%s %d disable cmdq feature false.\n", __func__, __LINE__);

		ret = mmc_blk_cmdq_switch(card, md, true);
		if (ret)
			pr_err("%s %d. enable cmdq feature false\n", __func__, __LINE__);

		clear_bit(req->tag, &card->host->cmdq_ctx.active_reqs);
		pr_err("%s reqest failed;requeue req.\n", __func__);
		spin_lock_irq(mq->queue->queue_lock);
		blk_requeue_request(mq->queue, req);
		spin_unlock_irq(mq->queue->queue_lock);
	}

switch_failure:
	mmc_release_host(card->host);
	return ret;
}

static int mmc_blk_issue_rq(struct mmc_queue *mq, struct request *req)
{
	int ret;
	struct mmc_blk_data *md = mq->data;
	struct mmc_card *card = md->queue.card;
	struct mmc_host *host = card->host;
	unsigned long flags;
	unsigned int cmd_flags = req ? req->cmd_flags : 0;

	if (req && !mq->mqrq_prev->req && !mq->tmp_get_card_flag) {
		/* claim host only for the first request */
		mmc_get_card(card);
		mq->tmp_get_card_flag = 1;
	}

	ret = mmc_blk_part_switch(card, md);
	if (ret) {
		if (req) {
			blk_end_request_all(req, -EIO);
		}
		ret = 0;
		goto out;
	}

	clear_bit(MMC_QUEUE_NEW_REQUEST_BIT, &mq->flags);
	if (cmd_flags & REQ_DISCARD) {
		/* complete ongoing async transfer before issuing discard */
		if (card->host->areq)
			mmc_blk_issue_rw_rq(mq, NULL);
		if (req->cmd_flags & REQ_SECURE &&
			!(card->quirks & MMC_QUIRK_SEC_ERASE_TRIM_BROKEN))
			ret = mmc_blk_issue_secdiscard_rq(mq, req);
		else
			ret = mmc_blk_issue_discard_rq(mq, req);
	} else if (cmd_flags & REQ_FLUSH) {
		/* complete ongoing async transfer before issuing flush */
		if (card->host->areq)
			mmc_blk_issue_rw_rq(mq, NULL);
		ret = mmc_blk_issue_flush(mq, req);
	} else {
		if (!req && host->areq) {
			spin_lock_irqsave(&host->context_info.lock, flags);
			host->context_info.is_waiting_last_req = true;
			spin_unlock_irqrestore(&host->context_info.lock, flags);
		}
		ret = mmc_blk_issue_rw_rq(mq, req);
	}

out:
	if ((!req && !test_bit(MMC_QUEUE_NEW_REQUEST_BIT, &mq->flags) && mq->tmp_get_card_flag) ||
	    ((cmd_flags & MMC_REQ_SPECIAL_MASK) && mq->tmp_get_card_flag)) {
		/*
		 * Release host when there are no more requests
		 * and after special request(discard, flush) is done.
		 * In case sepecial request, there is no reentry to
		 * the 'mmc_blk_issue_rq' with 'mqrq_prev->req'.
		 */
		mmc_put_card(card);
		mq->tmp_get_card_flag = 0;
	}
	return ret;
}

static inline int mmc_blk_readonly(struct mmc_card *card)
{
	return mmc_card_readonly(card) ||
	       !(card->csd.cmdclass & CCC_BLOCK_WRITE);
}

static struct mmc_blk_data *mmc_blk_alloc_req(struct mmc_card *card,
					      struct device *parent,
					      sector_t size,
					      bool default_ro,
					      const char *subname,
					      int area_type)
{
	struct mmc_blk_data *md;
	int devidx, ret;

	devidx = find_first_zero_bit(dev_use, max_devices);
	if (devidx >= max_devices)
		return ERR_PTR(-ENOSPC);
	__set_bit(devidx, dev_use);

	md = kzalloc(sizeof(struct mmc_blk_data), GFP_KERNEL);
	if (!md) {
		ret = -ENOMEM;
		goto out;
	}

	/*
	 * !subname implies we are creating main mmc_blk_data that will be
	 * associated with mmc_card with dev_set_drvdata. Due to device
	 * partitions, devidx will not coincide with a per-physical card
	 * index anymore so we keep track of a name index.
	 */
	if (!subname) {
		md->name_idx = find_first_zero_bit(name_use, max_devices);
		__set_bit(md->name_idx, name_use);
	} else
		md->name_idx = ((struct mmc_blk_data *)
				dev_to_disk(parent)->private_data)->name_idx;

	md->area_type = area_type;

	/*
	 * Set the read-only status based on the supported commands
	 * and the write protect switch.
	 */
	md->read_only = mmc_blk_readonly(card);

	md->disk = alloc_disk(perdev_minors);
	if (md->disk == NULL) {
		ret = -ENOMEM;
		goto err_kfree;
	}

	spin_lock_init(&md->lock);
	INIT_LIST_HEAD(&md->part);
	md->usage = 1;

	ret = mmc_init_queue(&md->queue, card, &md->lock, subname, area_type);
	if (ret)
		goto err_putdisk;

	md->queue.issue_fn = mmc_blk_issue_rq;
	md->queue.data = md;

	md->disk->major	= MMC_BLOCK_MAJOR;
	md->disk->first_minor = devidx * perdev_minors;
	md->disk->fops = &mmc_bdops;
	md->disk->private_data = md;
	md->disk->queue = md->queue.queue;
	md->disk->driverfs_dev = parent;
	set_disk_ro(md->disk, md->read_only || default_ro);
	md->disk->flags = GENHD_FL_EXT_DEVT;
	if (area_type & (MMC_BLK_DATA_AREA_RPMB | MMC_BLK_DATA_AREA_BOOT))
		md->disk->flags |= GENHD_FL_NO_PART_SCAN;

	/*
	 * As discussed on lkml, GENHD_FL_REMOVABLE should:
	 *
	 * - be set for removable media with permanent block devices
	 * - be unset for removable block devices with permanent media
	 *
	 * Since MMC block devices clearly fall under the second
	 * case, we do not set GENHD_FL_REMOVABLE.  Userspace
	 * should use the block device creation/destruction hotplug
	 * messages to tell when the card is present.
	 */

	snprintf(md->disk->disk_name, sizeof(md->disk->disk_name),
		 "mmcblk%d%s", md->name_idx, subname ? subname : "");

	if (mmc_card_mmc(card))
		blk_queue_logical_block_size(md->queue.queue,
					     card->ext_csd.data_sector_size);
	else
		blk_queue_logical_block_size(md->queue.queue, 512);

	set_capacity(md->disk, size);

	if (mmc_host_cmd23(card->host)) {
		if (mmc_card_mmc(card) ||
		    (mmc_card_sd(card) &&
		     card->scr.cmds & SD_SCR_CMD23_SUPPORT))
			md->flags |= MMC_BLK_CMD23;
	}

	if (mmc_card_mmc(card) &&
	    md->flags & MMC_BLK_CMD23 &&
	    ((card->ext_csd.rel_param & EXT_CSD_WR_REL_PARAM_EN) ||
	     card->ext_csd.rel_sectors)) {
		md->flags |= MMC_BLK_REL_WR;
		blk_queue_flush(md->queue.queue, REQ_FLUSH | REQ_FUA);
	}

	if (card->cmdq_init) {
		md->flags |= MMC_BLK_CMD_QUEUE;
		md->queue.cmdq_complete_fn = mmc_blk_cmdq_complete_rq;
		md->queue.cmdq_issue_fn = mmc_blk_cmdq_issue_rq;
	}

	if (mmc_card_mmc(card) && !card->cmdq_init &&
	    (area_type == MMC_BLK_DATA_AREA_MAIN) &&
	    (md->flags & MMC_BLK_CMD23) &&
	    card->ext_csd.packed_event_en) {
		if (!mmc_packed_init(&md->queue, card))
			md->flags |= MMC_BLK_PACKED_CMD;
	}

	return md;

 err_putdisk:
	put_disk(md->disk);
 err_kfree:
	kfree(md);
 out:
	return ERR_PTR(ret);
}

static struct mmc_blk_data *mmc_blk_alloc(struct mmc_card *card)
{
	sector_t size;
	struct mmc_blk_data *md;

	if (!mmc_card_sd(card) && mmc_card_blockaddr(card)) {
		/*
		 * The EXT_CSD sector count is in number or 512 byte
		 * sectors.
		 */
		size = card->ext_csd.sectors;
	} else {
		/*
		 * The CSD capacity field is in units of read_blkbits.
		 * set_capacity takes units of 512 bytes.
		 */
		size = card->csd.capacity << (card->csd.read_blkbits - 9);
	}

	md = mmc_blk_alloc_req(card, &card->dev, size, false, NULL,
					MMC_BLK_DATA_AREA_MAIN);
	return md;
}

static int mmc_blk_alloc_part(struct mmc_card *card,
			      struct mmc_blk_data *md,
			      unsigned int part_type,
			      sector_t size,
			      bool default_ro,
			      const char *subname,
			      int area_type)
{
	char cap_str[10];
	struct mmc_blk_data *part_md;

	part_md = mmc_blk_alloc_req(card, disk_to_dev(md->disk), size, default_ro,
				    subname, area_type);
	if (IS_ERR(part_md))
		return PTR_ERR(part_md);
	part_md->part_type = part_type;
	list_add(&part_md->part, &md->part);

	string_get_size((u64)get_capacity(part_md->disk) << 9, STRING_UNITS_2,
			cap_str, sizeof(cap_str));
	pr_info("%s: %s %s partition %u %s\n",
	       part_md->disk->disk_name, mmc_card_id(card),
	       mmc_card_name(card), part_md->part_type, cap_str);
	return 0;
}

/* MMC Physical partitions consist of two boot partitions and
 * up to four general purpose partitions.
 * For each partition enabled in EXT_CSD a block device will be allocatedi
 * to provide access to the partition.
 */

static int mmc_blk_alloc_parts(struct mmc_card *card, struct mmc_blk_data *md)
{
	int idx, ret = 0;

	if (!mmc_card_mmc(card))
		return 0;

	for (idx = 0; idx < card->nr_parts; idx++) {
		if (card->part[idx].size) {
			ret = mmc_blk_alloc_part(card, md,
				card->part[idx].part_cfg,
				card->part[idx].size >> 9,
				card->part[idx].force_ro,
				card->part[idx].name,
				card->part[idx].area_type);
			if (ret)
				return ret;
		}
	}

	return ret;
}

static void mmc_blk_remove_req(struct mmc_blk_data *md)
{
	struct mmc_card *card;

	if (md) {
		/*
		 * Flush remaining requests and free queues. It
		 * is freeing the queue that stops new requests
		 * from being accepted.
		 */
	        card = md->queue.card;
		mmc_cleanup_queue(&md->queue);
		if (md->flags & MMC_BLK_PACKED_CMD)
			mmc_packed_clean(&md->queue);
		if (md->flags & MMC_BLK_CMD_QUEUE)
			mmc_cmdq_clean(&md->queue, card);

		if (md->disk->flags & GENHD_FL_UP) {
			device_remove_file(disk_to_dev(md->disk), &md->force_ro);
			if ((md->area_type & MMC_BLK_DATA_AREA_BOOT) &&
					card->ext_csd.boot_ro_lockable)
				device_remove_file(disk_to_dev(md->disk),
					&md->power_ro_lock);

			del_gendisk(md->disk);
#ifdef CONFIG_HUAWEI_SDCARD_DSM
			if(MMC_TYPE_SD == card->type)
			{
				dsm_sdcard_cmd_logs[DSM_SDCARD_REPORT_UEVENT].value = DSM_REPORT_UEVENT_FALSE;
			}
#endif
		}
		mmc_blk_put(md);
	}
}

static void mmc_blk_remove_parts(struct mmc_card *card,
				 struct mmc_blk_data *md)
{
	struct list_head *pos, *q;
	struct mmc_blk_data *part_md;

	__clear_bit(md->name_idx, name_use);
	list_for_each_safe(pos, q, &md->part) {
		part_md = list_entry(pos, struct mmc_blk_data, part);
		list_del(pos);
		mmc_blk_remove_req(part_md);
	}
}

static int mmc_add_disk(struct mmc_blk_data *md)
{
	int ret;
	struct mmc_card *card = md->queue.card;

	add_disk(md->disk);
	md->force_ro.show = force_ro_show;
	md->force_ro.store = force_ro_store;
	sysfs_attr_init(&md->force_ro.attr);
	md->force_ro.attr.name = "force_ro";
	md->force_ro.attr.mode = S_IRUGO | S_IWUSR;
	ret = device_create_file(disk_to_dev(md->disk), &md->force_ro);
	if (ret)
		goto force_ro_fail;

	if ((md->area_type & MMC_BLK_DATA_AREA_BOOT) &&
	     card->ext_csd.boot_ro_lockable) {
		umode_t mode;

		if (card->ext_csd.boot_ro_lock & EXT_CSD_BOOT_WP_B_PWR_WP_DIS)
			mode = S_IRUGO;
		else
			mode = S_IRUGO | S_IWUSR;

		md->power_ro_lock.show = power_ro_lock_show;
		md->power_ro_lock.store = power_ro_lock_store;
		sysfs_attr_init(&md->power_ro_lock.attr);
		md->power_ro_lock.attr.mode = mode;
		md->power_ro_lock.attr.name =
					"ro_lock_until_next_power_on";
		ret = device_create_file(disk_to_dev(md->disk),
				&md->power_ro_lock);
		if (ret)
			goto power_ro_lock_fail;
	}
	return ret;

power_ro_lock_fail:
	device_remove_file(disk_to_dev(md->disk), &md->force_ro);
force_ro_fail:
	del_gendisk(md->disk);

	return ret;
}

#define CID_MANFID_SANDISK	0x2
#define CID_MANFID_TOSHIBA	0x11
#define CID_MANFID_MICRON	0x13
#define CID_MANFID_SAMSUNG	0x15

static const struct mmc_fixup blk_fixups[] =
{
	MMC_FIXUP("SEM02G", CID_MANFID_SANDISK, 0x100, add_quirk,
		  MMC_QUIRK_INAND_CMD38),
	MMC_FIXUP("SEM04G", CID_MANFID_SANDISK, 0x100, add_quirk,
		  MMC_QUIRK_INAND_CMD38),
	MMC_FIXUP("SEM08G", CID_MANFID_SANDISK, 0x100, add_quirk,
		  MMC_QUIRK_INAND_CMD38),
	MMC_FIXUP("SEM16G", CID_MANFID_SANDISK, 0x100, add_quirk,
		  MMC_QUIRK_INAND_CMD38),
	MMC_FIXUP("SEM32G", CID_MANFID_SANDISK, 0x100, add_quirk,
		  MMC_QUIRK_INAND_CMD38),

	/*
	 * Some MMC cards experience performance degradation with CMD23
	 * instead of CMD12-bounded multiblock transfers. For now we'll
	 * black list what's bad...
	 * - Certain Toshiba cards.
	 *
	 * N.B. This doesn't affect SD cards.
	 */
	MMC_FIXUP("MMC08G", CID_MANFID_TOSHIBA, CID_OEMID_ANY, add_quirk_mmc,
		  MMC_QUIRK_BLK_NO_CMD23),
	MMC_FIXUP("MMC16G", CID_MANFID_TOSHIBA, CID_OEMID_ANY, add_quirk_mmc,
		  MMC_QUIRK_BLK_NO_CMD23),
	MMC_FIXUP("MMC32G", CID_MANFID_TOSHIBA, CID_OEMID_ANY, add_quirk_mmc,
		  MMC_QUIRK_BLK_NO_CMD23),

	/*
	 * Some Micron MMC cards needs longer data read timeout than
	 * indicated in CSD.
	 */
	MMC_FIXUP(CID_NAME_ANY, CID_MANFID_MICRON, 0x200, add_quirk_mmc,
		  MMC_QUIRK_LONG_READ_TIME),

	/*
	 * On these Samsung MoviNAND parts, performing secure erase or
	 * secure trim can result in unrecoverable corruption due to a
	 * firmware bug.
	 */
	MMC_FIXUP("M8G2FA", CID_MANFID_SAMSUNG, CID_OEMID_ANY, add_quirk_mmc,
		  MMC_QUIRK_SEC_ERASE_TRIM_BROKEN),
	MMC_FIXUP("MAG4FA", CID_MANFID_SAMSUNG, CID_OEMID_ANY, add_quirk_mmc,
		  MMC_QUIRK_SEC_ERASE_TRIM_BROKEN),
	MMC_FIXUP("MBG8FA", CID_MANFID_SAMSUNG, CID_OEMID_ANY, add_quirk_mmc,
		  MMC_QUIRK_SEC_ERASE_TRIM_BROKEN),
	MMC_FIXUP("MCGAFA", CID_MANFID_SAMSUNG, CID_OEMID_ANY, add_quirk_mmc,
		  MMC_QUIRK_SEC_ERASE_TRIM_BROKEN),
	MMC_FIXUP("VAL00M", CID_MANFID_SAMSUNG, CID_OEMID_ANY, add_quirk_mmc,
		  MMC_QUIRK_SEC_ERASE_TRIM_BROKEN),
	MMC_FIXUP("VYL00M", CID_MANFID_SAMSUNG, CID_OEMID_ANY, add_quirk_mmc,
		  MMC_QUIRK_SEC_ERASE_TRIM_BROKEN),
	MMC_FIXUP("KYL00M", CID_MANFID_SAMSUNG, CID_OEMID_ANY, add_quirk_mmc,
		  MMC_QUIRK_SEC_ERASE_TRIM_BROKEN),
	MMC_FIXUP("VZL00M", CID_MANFID_SAMSUNG, CID_OEMID_ANY, add_quirk_mmc,
		  MMC_QUIRK_SEC_ERASE_TRIM_BROKEN),

	END_FIXUP
};

static const struct file_operations modem_log_chk = { .owner = THIS_MODULE, };
int modem_log_proc_init(void)
{
	if (NULL == proc_create("ModemLOGErrMount", 0660, NULL,
	    &modem_log_chk))
		return -1;
	return 0;
}

static const struct file_operations modem_nv_chk = { .owner = THIS_MODULE, };
int modem_nv_proc_init(void)
{
	if (NULL == proc_create("ModemNVErrMount", 0660, NULL, &modem_nv_chk))
		return -1;
	return 0;
}

static int mmc_blk_probe(struct device *dev)
{
	struct mmc_card *card = mmc_dev_to_card(dev);
	struct mmc_blk_data *md, *part_md;
	struct mmcpart_notifier *nt;
	int i, index;
	char cap_str[10];
	char cfq_name[15];
	int ret = 0;
#ifdef CONFIG_BALONG_MTD
	int sequence;
	int err;
#endif

#ifdef CONFIG_HUAWEI_SDCARD_DSM
	int   buff_len;
	char *log_buff;
#endif
	/*
	 * Check that the card supports the command class(es) we need.
	 */
	if (!(card->csd.cmdclass & CCC_BLOCK_READ))
		return -ENODEV;

	md = mmc_blk_alloc(card);
	if (IS_ERR(md))
		return PTR_ERR(md);

	string_get_size((u64)get_capacity(md->disk) << 9, STRING_UNITS_2,
			cap_str, sizeof(cap_str));
	pr_info("%s: %s %s %s %s\n",
		md->disk->disk_name, mmc_card_id(card), mmc_card_name(card),
		cap_str, md->read_only ? "(ro)" : "");

	if (mmc_blk_alloc_parts(card, md))
		goto out;

	if (mmc_card_sd(card)) {
		memset(cfq_name, 0 , sizeof(cfq_name));
		snprintf(cfq_name, sizeof(cfq_name), "cfq");
		ret = elevator_change(md->queue.queue, cfq_name);
		if (ret)
			pr_err("%s change SD scheduler to cfq failed. %d\n", __func__, ret);
	}

	dev_set_drvdata(dev, md);
	mmc_fixup_device(card, blk_fixups);
#ifdef CONFIG_HW_SD_HEALTH_DETECT
	if(mmc_card_sd(card))
	{
		mmc_clear_report_info();
	}
#endif
	if (mmc_add_disk(md))
		goto out;

	list_for_each_entry(part_md, &md->part, part) {
		if (mmc_add_disk(part_md))
			goto out;
	}
	mutex_lock(&mmcpart_table_mutex);
	index = md->disk->first_minor / perdev_minors;
	if (md->queue.card) {
		mmc_panic_ops_table[index].type = md->queue.card->type;
		mmc_panic_ops_table[index].panic_probe =
			md->queue.card->host->ops->panic_probe;
		mmc_panic_ops_table[index].panic_write =
			md->queue.card->host->ops->panic_write;
		mmc_panic_ops_table[index].panic_erase =
			md->queue.card->host->ops->panic_erase;
	}
	for (i = 0; i < md->disk->part_tbl->len; i++) {
		if (!md->disk->part_tbl->part[i])
			continue;
		mmcpart_table[index][i].hd.start_sect =
			md->disk->part_tbl->part[i]->start_sect;
		mmcpart_table[index][i].hd.nr_sects =
			md->disk->part_tbl->part[i]->nr_sects;
		mmcpart_table[index][i].hd.partno = i;
		mmcpart_table[index][i].hd.major = md->disk->major;
		mmcpart_table[index][i].hd.first_minor = md->disk->first_minor;

		list_for_each_entry(nt, &mmcpart_notifiers, list) {
			if (strlen(nt->partname) && !strncmp(nt->partname,
					mmcpart_table[index][i].partname,
					BDEVNAME_SIZE)) {
				printk(KERN_INFO "%s: adding mmcblk%dp%d:%s\n",
					__func__, index, i,
					mmcpart_table[index][i].partname);
				nt->add(&mmcpart_table[index][i].hd,
					&mmc_panic_ops_table[index]);
			}
		}
	}

#ifdef CONFIG_BALONG_MTD
	for (i = 0; i < md->disk->part_tbl->len; i++) {
		if (!md->disk->part_tbl->part[i])
			continue;

		for (sequence = 0; sequence < MODEM_INVALID_PARTITION; sequence++) {
			if (0 == strncmp(mmcpart_table[index][i].partname, modem_partition_list[sequence].partion_name, BDEVNAME_SIZE)) {
				char str_dev[32];

				memset(str_dev, 0 , sizeof(str_dev));
				sprintf(str_dev, "/dev/block/mmcblk%dp%d", index, i);
				if (sys_access((const char __user *)"/dev/block", 0) != 0) {
					err = sys_mkdir("/dev/block", S_IRWXU | S_IRWXG | S_IRWXO);
					if (err < 0)
					printk("[%s]: sys_mkdir /dev/block failed : %d\n", __func__, err);
				}

				err = sys_mknod(str_dev, S_IFBLK | S_IRWXU | S_IRWXG | S_IRWXO,
								(md->disk->major << 8) +  md->disk->first_minor + i);
				if (err < 0)
					printk("[%s]: sys_mknod %s [%d,%d] failed : %d\n", __func__, str_dev,
							md->disk->major, md->disk->first_minor, err);

				if (sequence >= MODEM_INVALID_MOUNT)
					block2mtd_setup2(str_dev);

			}
		}
	}
#endif

	mutex_unlock(&mmcpart_table_mutex);

	pm_runtime_set_autosuspend_delay(&card->dev, 3000);
	pm_runtime_use_autosuspend(&card->dev);

	/*
	 * Don't enable runtime PM for SD-combo cards here. Leave that
	 * decision to be taken during the SDIO init sequence instead.
	 */
	if (card->type != MMC_TYPE_SD_COMBO) {
		pm_runtime_set_active(&card->dev);
		pm_runtime_enable(&card->dev);
	}

#ifdef CONFIG_HUAWEI_SDCARD_DSM
	if(MMC_TYPE_SD == card->type)
	{
		dsm_sdcard_cmd_logs[DSM_SDCARD_REPORT_UEVENT].value = DSM_REPORT_UEVENT_TRUE;
	}
#endif

	return 0;

 out:
    #ifdef CONFIG_HUAWEI_SDCARD_DSM
	 if(MMC_TYPE_SD == card->type && !dsm_client_ocuppy(sdcard_dclient))
	 {
	 	 log_buff = dsm_sdcard_get_log(DSM_SDCARD_REPORT_UEVENT,0);
		 buff_len = strlen(log_buff);
		 dsm_client_copy(sdcard_dclient,log_buff,buff_len + 1);
		 dsm_client_notify(sdcard_dclient, DSM_SDCARD_NO_UEVENT_REPORT);
	 }
    #endif
	mmc_blk_remove_parts(card, md);
	mmc_blk_remove_req(md);
	return 0;
}

static int mmc_blk_remove(struct device *dev)
{
	int i, index;
	struct mmc_card *card = mmc_dev_to_card(dev);
	struct mmc_blk_data *md = dev_get_drvdata(dev);
	struct mmcpart_notifier *nt;

	if (md) {
		index = md->disk->first_minor / perdev_minors;
		mutex_lock(&mmcpart_table_mutex);
		for (i = 0; i < md->disk->part_tbl->len; i++) {
			list_for_each_entry(nt, &mmcpart_notifiers, list)
				if (strlen(nt->partname) &&
				    !strncmp(nt->partname,
				    mmcpart_table[index][i].partname,
				    BDEVNAME_SIZE))
					nt->remove(&mmcpart_table[index][i].hd);
			memset(&mmcpart_table[index][i].hd, 0,
				sizeof(struct raw_hd_struct));
		}
		memset(&mmc_panic_ops_table[index], 0,
			sizeof(struct raw_mmc_panic_ops));
		mutex_unlock(&mmcpart_table_mutex);
	}
	if (md)
		mmc_blk_remove_parts(card, md);
	pm_runtime_get_sync(&card->dev);
	mmc_claim_host(card->host);
	if (md)
		mmc_blk_part_switch(card, md);
	mmc_release_host(card->host);
	if (card->type != MMC_TYPE_SD_COMBO)
		pm_runtime_disable(&card->dev);
	pm_runtime_put_noidle(&card->dev);
	if (md)
		mmc_blk_remove_req(md);
	dev_set_drvdata(dev, NULL);
	return 0;
}


static int _mmc_blk_suspend(struct device *dev,int wait)
{
	struct mmc_blk_data *part_md;
	struct mmc_blk_data *md = dev_get_drvdata(dev);

	if (md) {
		if(mmc_queue_suspend(&md->queue,wait))
                                goto out;
		list_for_each_entry(part_md, &md->part, part) {
			if(mmc_queue_suspend(&part_md->queue,wait))
                                                goto out_resume;
		}
	}
	return 0;
out_resume:
      mmc_queue_resume(&md->queue);
      list_for_each_entry(part_md, &md->part, part) {
              mmc_queue_resume(&part_md->queue);
      }
out:
      return -EBUSY;
}

static void mmc_blk_shutdown(struct device *dev)
{
	printk("%s:%d ++\n", __func__, __LINE__);
	_mmc_blk_suspend(dev,1);
	printk("%s:%d --\n", __func__, __LINE__);
}

#ifdef CONFIG_PM_SLEEP
static int mmc_blk_suspend(struct device *dev)
{
	int ret;
	printk("%s:%d ++\n", __func__, __LINE__);
	ret = _mmc_blk_suspend(dev,0);
	printk("%s:%d --\n", __func__, __LINE__);
	return ret;
}

static int mmc_blk_resume(struct device *dev)
{
	struct mmc_blk_data *part_md;
	struct mmc_blk_data *md = dev_get_drvdata(dev);
	struct mmc_card *card = md->queue.card;
	u8 part_config = card->ext_csd.part_config;

	printk("%s:%d ++\n", __func__, __LINE__);
	if (md) {
#if 0
		/*
		 * Resume involves the card going into idle state,
		 * so current partition is always the main one.
		 */
		md->part_curr = md->part_type;
#else
		/*don't use the mainline code,because the card
		 *may in rpmb partition;so we use the card's
		 *real part access type.
		 */
		part_config &= EXT_CSD_PART_CONFIG_ACC_MASK;
		md->part_curr = part_config;
		if (md->part_curr != md->part_type)
			pr_err("%s md part_curr is %u,part_type is %u\n",
				__func__, md->part_curr, md->part_type);
#endif
		mmc_queue_resume(&md->queue);
		list_for_each_entry(part_md, &md->part, part) {
			mmc_queue_resume(&part_md->queue);
		}
	}
	printk("%s:%d --\n", __func__, __LINE__);
	return 0;
}
#endif

static SIMPLE_DEV_PM_OPS(mmc_blk_pm_ops, mmc_blk_suspend, mmc_blk_resume);

static struct device_driver mmc_driver = {
	.name           = "mmcblk",
	.pm             = &mmc_blk_pm_ops,
	.probe		= mmc_blk_probe,
	.remove		= mmc_blk_remove,
	.shutdown	= mmc_blk_shutdown,
};

static int __init mmc_blk_init(void)
{
	int res;

	if (perdev_minors != CONFIG_MMC_BLOCK_MINORS)
		pr_info("mmcblk: using %d minors per device\n", perdev_minors);

	max_devices = 256 / perdev_minors;

	res = register_blkdev(MMC_BLOCK_MAJOR, "mmc");
	if (res)
		goto out;

	res = mmc_register_driver(&mmc_driver);
	if (res)
		goto out2;

#ifdef CONFIG_HUAWEI_EMMC_DSM
	if (!emmc_dclient) {
		emmc_dclient = dsm_register_client(&dsm_emmc);
	}
	spin_lock_init(&g_emmc_dsm_log.lock);
#endif
	return 0;
 out2:
	unregister_blkdev(MMC_BLOCK_MAJOR, "mmc");
 out:
	return res;
}

static void __exit mmc_blk_exit(void)
{
	mmc_unregister_driver(&mmc_driver);
	unregister_blkdev(MMC_BLOCK_MAJOR, "mmc");
}

module_init(mmc_blk_init);
module_exit(mmc_blk_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Multimedia Card (MMC) block device driver");

