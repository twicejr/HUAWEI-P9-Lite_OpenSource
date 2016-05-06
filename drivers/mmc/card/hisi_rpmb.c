

#include <linux/cpumask.h>
#include <linux/debugfs.h>
#include <linux/fs.h>
#include <asm-generic/fcntl.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/mmc/rpmb.h>
#include <linux/mmc/core.h>
#include <linux/mmc/ioctl.h>
#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include <linux/mmc/mmc.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/slab.h>
#include <linux/smp.h>
#include <linux/types.h>
#include <linux/bootmem.h>
#include <linux/mm.h>
#include <linux/printk.h>
#include <linux/dma-mapping.h>
#include <linux/device.h>
#include <linux/wakelock.h>
#include <global_ddr_map.h>

#include <asm/byteorder.h>
#include <asm/hardirq.h>

#include "hisi_rpmb.h"

/* external function declaration */
extern int atfd_hisi_rpmb_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2);
extern int mmc_blk_ioctl_rpmb_cmd(enum func_id id, struct block_device *bdev, struct mmc_blk_ioc_rpmb_data *idata);

struct hisi_rpmb {
	struct rpmb_request *rpmb_request;
	struct device *dev;
	struct block_device *blkdev;
	struct workqueue_struct *rpmb_workqueue;
	struct work_struct rpmb_work;
	struct wake_lock wake_lock;
};

static struct hisi_rpmb hisi_rpmb;
DEFINE_MUTEX(rpmb_counter_lock);

static inline void rpmb_combine_request(struct mmc_blk_ioc_data *data, struct rpmb_frame *frame,
					int is_write, unsigned short blocks, unsigned short blksz, bool reliable)
{
	struct mmc_ioc_cmd *ioc;

	data->buf = (void *)frame;
	data->buf_bytes = (u64) blocks * blksz;

	ioc = &data->ic;

	ioc->write_flag = is_write | ((is_write & reliable) << 31);
	ioc->opcode = is_write ? MMC_WRITE_MULTIPLE_BLOCK : MMC_READ_MULTIPLE_BLOCK;
	ioc->flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	ioc->arg = 0x0;
	ioc->blksz = blksz;
	ioc->blocks = blocks;
}

static inline void mmc_rpmb_basic_request(uint32_t index, struct rpmb_request *request,
						struct mmc_blk_ioc_rpmb_data *rpmb_data, uint16_t block_count, uint32_t reliable)
{
	rpmb_combine_request(&rpmb_data->data[0], &request->frame[0], true, block_count, RPMB_BLK_SZ, reliable);
}

static inline void mmc_rpmb_status_request(uint32_t index, struct rpmb_request *request,
						struct mmc_blk_ioc_rpmb_data *rpmb_data, uint16_t block_count, uint32_t reliable)
{
	struct rpmb_frame *status_frame = &request->status_frame;
	memset(status_frame, 0, sizeof(*status_frame));
	status_frame->request = cpu_to_be16(RPMB_REQ_STATUS);

	rpmb_combine_request(&rpmb_data->data[1], status_frame, true, 0x1, RPMB_BLK_SZ, false);
}

static inline void mmc_rpmb_result_request(uint32_t index,struct rpmb_request *request,
						struct mmc_blk_ioc_rpmb_data *rpmb_data, uint16_t block_count, uint32_t reliable)
{
	rpmb_combine_request(&rpmb_data->data[index], &request->frame[0], false, block_count, RPMB_BLK_SZ, false);
}

void mmc_rpmb_set_key(struct rpmb_request *request, struct mmc_blk_ioc_rpmb_data *rpmb_data)
{
	mmc_rpmb_basic_request(0, request, rpmb_data, 0x1, true);
	mmc_rpmb_status_request(1, request, rpmb_data, 0x1, false);
	mmc_rpmb_result_request(2, request, rpmb_data, 0x1, false);
}

void mmc_rpmb_get_counter(struct rpmb_request *request, struct mmc_blk_ioc_rpmb_data *rpmb_data)
{
	mmc_rpmb_basic_request(0, request, rpmb_data, 0x1, false);
	mmc_rpmb_result_request(1, request, rpmb_data, 0x1, false);
}

void mmc_rpmb_read_data(struct rpmb_request *request, struct mmc_blk_ioc_rpmb_data *rpmb_data)
{
	unsigned short blocks_count = request->info.current_rqst.blks;

	mmc_rpmb_basic_request(0, request, rpmb_data, 0x1, false);
	mmc_rpmb_result_request(1, request, rpmb_data, blocks_count, false);
}

void mmc_rpmb_write_data(struct rpmb_request *request, struct mmc_blk_ioc_rpmb_data *rpmb_data)
{
	unsigned short blocks_count = request->info.current_rqst.blks;

	mmc_rpmb_basic_request(0, request, rpmb_data, blocks_count, true);
	mmc_rpmb_status_request(1, request, rpmb_data, 0x1, false);
	mmc_rpmb_result_request(2, request, rpmb_data, 0x1, false);
}

/* reserved for ufs */
/* static void ufs_rpmb_work(struct rpmb_request *request) */
static int32_t mmc_rpmb_work(struct rpmb_request *request)
{
	int32_t result;

	struct rpmb_frame *frame = &request->frame[0];
	struct mmc_blk_ioc_rpmb_data *rpmb_data = kzalloc(sizeof(*rpmb_data), GFP_KERNEL);

	hisi_rpmb.blkdev = blkdev_get_by_path("/dev/block/mmcblk0rpmb", O_RDWR | O_NDELAY, hisi_rpmb.dev);

	switch (request->info.state) {
	case RPMB_STATE_IDLE:
		printk("rpmb maybe issue an error\n");
		break;
	case RPMB_STATE_KEY:
		mmc_rpmb_set_key(request, rpmb_data);
		break;
	case RPMB_STATE_RD:
		mmc_rpmb_read_data(request, rpmb_data);
		break;
	case RPMB_STATE_CNT:
		mmc_rpmb_get_counter(request, rpmb_data);
		break;
	case RPMB_STATE_WR_CNT:
		/* TODO add a lock here for counter before write data */
		mutex_lock(&rpmb_counter_lock);
		mmc_rpmb_get_counter(request, rpmb_data);
		break;
	case RPMB_STATE_WR_DATA:
		mmc_rpmb_write_data(request, rpmb_data);
		/* TODO add a unlock for counter after write data */
		break;
	}

	/*
	 * we must unlock rpmb_counter_lock for some condition
	 * 1. RPMB_STATE_WR_CNT and result failed
	 * 2. RPMB_STATE_WR_CNT and result success but RESPONSE not valid
	 * 3. RPMB_STATE_WR_DATA we always unlock
	 */
	result = mmc_blk_ioctl_rpmb_cmd(request->info.func_id, hisi_rpmb.blkdev, rpmb_data);
	if ((request->info.state == RPMB_STATE_WR_CNT
				&& (result || (be16_to_cpu(frame->result) != RPMB_OK
				|| be16_to_cpu(frame->request) != RPMB_RESP_WCOUNTER)))
				|| (request->info.state == RPMB_STATE_WR_DATA)) {
		mutex_unlock(&rpmb_counter_lock);
	}

	blkdev_put(hisi_rpmb.blkdev, O_RDWR | O_NDELAY);
	kfree(rpmb_data);

	return result;
}

static void rpmb_work_routine(struct work_struct *work)
{
	unsigned short result;
	struct rpmb_request *request = hisi_rpmb.rpmb_request;
	wake_lock_timeout(&hisi_rpmb.wake_lock, 2 * HZ);

	result = mmc_rpmb_work(request);

	atfd_hisi_rpmb_smc(RPMB_SVC_REQUEST_DONE, result, 0, 0);

	/*wake_unlock(&hisi_rpmb.wake_lock);*/
}

/*
 * hisi_rpmb_active - handle rpmb request from ATF
 */
void hisi_rpmb_active(void)
{
	queue_work(hisi_rpmb.rpmb_workqueue, &hisi_rpmb.rpmb_work);
}

EXPORT_SYMBOL(hisi_rpmb_active);

#ifdef CONFIG_DEBUG_FS
/*
 * debugfs defination start here
 */
static int get_counter_fops_get(void *data, u64 *val)
{
	atfd_hisi_rpmb_smc(RPMB_SVC_COUNTER, 0x0, 0x0, 0x0);
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(get_counter_fops, get_counter_fops_get, NULL, "%llu\n");

static int read_fops_get(void *data, u64 *val)
{
	atfd_hisi_rpmb_smc(RPMB_SVC_READ, 0x0, 0x0, 0x0);
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(read_fops, read_fops_get, NULL, "%llu\n");

static int write_fops_get(void *data, u64 *val)
{
	atfd_hisi_rpmb_smc(RPMB_SVC_WRITE, 0x0, 0x0, 0x0);
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(write_fops, write_fops_get, NULL, "%llu\n");

static int hisi_rpmb_debugfs_init(void)
{
	/* debugfs for debug only */
	struct dentry *debugfs_hisi_rpmb = NULL;
	struct rpmb_request *request = hisi_rpmb.rpmb_request;
	debugfs_hisi_rpmb = debugfs_create_dir("hisi_rpmb", NULL);

	debugfs_create_file("counter", S_IRUSR | S_IWUSR, debugfs_hisi_rpmb, NULL, &get_counter_fops);
	debugfs_create_file("read", S_IRUSR | S_IWUSR, debugfs_hisi_rpmb, NULL, &read_fops);
	debugfs_create_file("write", S_IRUSR | S_IWUSR, debugfs_hisi_rpmb, NULL, &write_fops);

	debugfs_create_u32("func_id", S_IRUSR | S_IWUSR, debugfs_hisi_rpmb, &request->rpmb_debug.func_id);
	debugfs_create_u16("start", S_IRUSR | S_IWUSR, debugfs_hisi_rpmb, &request->rpmb_debug.start);
	debugfs_create_u16("block_count", S_IRUSR | S_IWUSR, debugfs_hisi_rpmb, &request->rpmb_debug.block_count);
	debugfs_create_u8("result", S_IRUSR | S_IWUSR, debugfs_hisi_rpmb, &request->rpmb_debug.result);

	return 0;
}
#endif

static ssize_t hisi_rpmb_key_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;

	struct rpmb_request *request = hisi_rpmb.rpmb_request;
	struct rpmb_frame *frame = &request->frame[0];

	struct mmc_blk_ioc_rpmb_data *rpmb_data = kzalloc(sizeof(*rpmb_data), GFP_KERNEL);
	if (!rpmb_data) {
		dev_err(dev, "alloc rpmb_data failed\n");
		return -1;
	}

	if (strncmp(buf, "set_key", count)) {
		dev_err(dev, "invalid key set command\n");
		kfree(rpmb_data);
		return -1;
	}

	hisi_rpmb.blkdev = blkdev_get_by_path("/dev/block/mmcblk0rpmb", O_RDWR | O_NDELAY, hisi_rpmb.dev);
	if (IS_ERR(hisi_rpmb.blkdev)) {
		dev_err(dev, "blkdev get mmcblk0rpmb failed\n");
		goto alloc_free;
	}

	/* get key from bl31 */
	atfd_hisi_rpmb_smc(RPMB_SVC_SET_KEY, 0x0, 0x0, 0x0);
	mmc_rpmb_set_key(request, rpmb_data);
	ret = mmc_blk_ioctl_rpmb_cmd(request->info.func_id, hisi_rpmb.blkdev, rpmb_data);

	blkdev_put(hisi_rpmb.blkdev, O_RDWR | O_NDELAY);
alloc_free:
	kfree(rpmb_data);

	if (ret || (be16_to_cpu(frame->result) != RPMB_OK || be16_to_cpu(frame->request) != RPMB_RESP_KEY))
		return -1;
	return count;
}

static ssize_t hisi_rpmb_key_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int ret = -1;

	struct rpmb_request *request = hisi_rpmb.rpmb_request;
	struct rpmb_frame *frame = &request->frame[0];

	struct mmc_blk_ioc_rpmb_data *rpmb_data = kzalloc(sizeof(*rpmb_data), GFP_KERNEL);
	if (!rpmb_data) {
		dev_err(dev, "alloc rpmb_data failed\n");
		return -1;
	}

	hisi_rpmb.blkdev = blkdev_get_by_path("/dev/block/mmcblk0rpmb", O_RDWR | O_NDELAY, hisi_rpmb.dev);
	if (IS_ERR(hisi_rpmb.blkdev)) {
		dev_err(dev, "blkdev get mmcblk0rpmb failed\n");
		goto alloc_free;
	}

	memset(frame, 0, sizeof(struct rpmb_frame));
	frame->request = cpu_to_be16(RPMB_REQ_WCOUNTER);
	mmc_rpmb_get_counter(hisi_rpmb.rpmb_request, rpmb_data);

	ret = mmc_blk_ioctl_rpmb_cmd(request->info.func_id, hisi_rpmb.blkdev, rpmb_data);

	blkdev_put(hisi_rpmb.blkdev, O_RDWR | O_NDELAY);
alloc_free:
	kfree(rpmb_data);

	if (ret) {
		dev_err(dev, "can not get rpmb key status\n");
		goto false_key;
	}

	if (be16_to_cpu(frame->result) != RPMB_OK || be16_to_cpu(frame->request) != RPMB_RESP_WCOUNTER) {
		goto false_key;
	}

	strncpy(buf, "true", sizeof("true"));
	return strlen(buf);
false_key:
	strncpy(buf, "false", sizeof("false"));
	return strlen(buf);
}

static DEVICE_ATTR(rpmb_key, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP), hisi_rpmb_key_show, hisi_rpmb_key_store);

/* create a virtual device for dma_alloc */
#define SECURE_STORAGE_NAME "secure_storage"
#define RPMB_DEVICE_NAME "hisi_rpmb"
static int hisi_rpmb_device_init(void)
{
	struct device *pdevice;
	struct class *rpmb_class;
	struct device_node *np = NULL;
	dma_addr_t rpmb_request_phy = 0;
	unsigned long mem_size = 0;
	phys_addr_t bl31_smem_base = HISI_SUB_RESERVED_BL31_SHARE_MEM_PHYMEM_BASE;
	u32 data[2] = { 0 };

	rpmb_class = class_create(THIS_MODULE, SECURE_STORAGE_NAME);
	if (IS_ERR(rpmb_class))
		return PTR_ERR(rpmb_class);

	pdevice = device_create(rpmb_class, NULL, MKDEV(0, 0), NULL, RPMB_DEVICE_NAME);
	if (IS_ERR(pdevice))
		goto err_class_destroy;

	hisi_rpmb.dev = pdevice;

	if (device_create_file(pdevice, &dev_attr_rpmb_key)) {
		pr_err("rpmb error: unable to create sysfs attributes\n");
		goto err_device_destroy;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,hisi-rpmb");
	if (!np) {
		pr_err("rpmb err of_find_compatible_node");
		goto err_device_remove_file;
	}

	if (of_property_read_u32_array(np, "hisi,bl31-share-mem", &data[0], 2)) {
		pr_err("rpmb get share_mem_address failed\n");
		goto err_node;
	}

	rpmb_request_phy = bl31_smem_base + data[0];
	mem_size = data[1];

	hisi_rpmb.rpmb_request = ioremap_wc(rpmb_request_phy, mem_size);
	if (!hisi_rpmb.rpmb_request)
		goto err_node;

	if (atfd_hisi_rpmb_smc(RPMB_SVC_REQUEST_ADDR, rpmb_request_phy, 0x0, 0x0)) {
		printk("rpmb set shared memory address failed\n");
		goto err_ioremap;
	}
	return 0;

err_ioremap:
	iounmap(hisi_rpmb.rpmb_request);
err_node:
	of_node_put(np);
err_device_remove_file:
	device_remove_file(pdevice, &dev_attr_rpmb_key);
err_device_destroy:
	device_destroy(rpmb_class, pdevice->devt);
err_class_destroy:
	class_destroy(rpmb_class);
	return -1;
}

static int __init hisi_rpmb_init(void)
{
	hisi_rpmb.rpmb_workqueue = alloc_workqueue("hisi-rpmb-queue", WQ_MEM_RECLAIM | WQ_NON_REENTRANT, 1);
	if (!hisi_rpmb.rpmb_workqueue)
		return -1;

	INIT_WORK(&hisi_rpmb.rpmb_work, rpmb_work_routine);

	if (hisi_rpmb_device_init())
		goto err_destroy_workqueue;

	wake_lock_init(&hisi_rpmb.wake_lock, WAKE_LOCK_SUSPEND, "hisi-rpmb-wakelock");

#ifdef CONFIG_DEBUG_FS
	hisi_rpmb_debugfs_init();
#endif

	return 0;

err_destroy_workqueue:
	destroy_workqueue(hisi_rpmb.rpmb_workqueue);

	return -1;
}

late_initcall(hisi_rpmb_init);

MODULE_AUTHOR("zangleigang@hisilicon.com>");
MODULE_DESCRIPTION("Hisilicon Secure RPMB.");
MODULE_LICENSE("GPL v2");
