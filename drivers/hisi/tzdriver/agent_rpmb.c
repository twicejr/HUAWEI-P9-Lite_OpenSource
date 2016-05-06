#include <linux/fs.h>
#include <linux/mmc/ioctl.h> // for struct mmc_ioc_rpmb
#include <linux/mmc/card.h> // for struct mmc_card
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/mmc/rpmb.h>

#include "tee_client_constants.h"
//#define TC_DEBUG
#include "teek_ns_client.h"
#include "agent.h"

extern int mmc_blk_ioctl_rpmb_cmd(enum func_id id,
			   struct block_device *bdev,
			   struct mmc_blk_ioc_rpmb_data *idata);
extern struct mmc_card *get_mmc_card(struct block_device *bdev);

#define RPMB_DEVICE_NAME "/dev/block/mmcblk0rpmb"
static int rpmb_agent_open_blkdev(struct tee_agent_kernel_ops* agent_instance, int stage)
{
    struct block_device *bdev;

    if (agent_instance->agent_data)
        return 0;

    bdev = blkdev_get_by_path(RPMB_DEVICE_NAME, FMODE_READ | FMODE_WRITE | FMODE_NDELAY, 0);
    if (IS_ERR(bdev)) {
        TCERR("open %s failed with %ld in stage-%d\n",
            RPMB_DEVICE_NAME, PTR_ERR(bdev), stage);
        agent_instance->agent_data = NULL;
        return -1;
    } else {
        TCDEBUG("open %s success in stage-%d\n", RPMB_DEVICE_NAME, stage);
        agent_instance->agent_data = bdev;
        return 0;
    }
}
static int rpmb_agent_close_blkdev(struct tee_agent_kernel_ops* agent_instance)
{
    struct block_device *bdev;
    if (agent_instance->agent_data) {
        bdev = (struct block_device *)agent_instance->agent_data;
        blkdev_put(bdev, FMODE_READ | FMODE_WRITE | FMODE_NDELAY);
    }
    return 0;
}
static int rpmb_agent_init(struct tee_agent_kernel_ops* agent_instance)
{
    rpmb_agent_open_blkdev(agent_instance, 0); //dont care the return value
    return 0;
}
static int rpmb_agent_exit(struct tee_agent_kernel_ops* agent_instance)
{
    rpmb_agent_close_blkdev(agent_instance);
    return 0;
}

typedef enum{
    sec_get_devinfo,
    sec_send_ioccmd,
    sec_rpmb_lock,
    sec_rpmb_unlock,
} rpmb_cmd_t;

#define RPMB_EMMC_CID_SIZE 32
struct rpmb_devinfo {
    uint8_t cid[RPMB_EMMC_CID_SIZE]; /* eMMC card ID */
    uint8_t rpmb_size_mult; /* EXT CSD-slice 168 "RPMB Size" */
    uint8_t rel_wr_sec_cnt; /* EXT CSD-slice 222 "Reliable Write Sector Count" */
    uint32_t blk_size; /* RPMB blocksize*/
    uint32_t max_blk_idx; /* The highest block index supported by current device */
};

struct rpmb_ioc{
    struct mmc_ioc_rpmb ioc_rpmb;
    uint32_t buf_offset[MMC_IOC_MAX_RPMB_CMD];
    uint32_t buf[1];
};

struct rpmb_ctrl_t{
    rpmb_cmd_t cmd;
    int32_t ret;
    uint8_t lock_flag;
    union {
        struct rpmb_devinfo get_devinfo;
        struct rpmb_ioc send_ioccmd;
    } args;
};

static void get_devinfo(struct tee_agent_kernel_ops* agent_instance)
{
    struct rpmb_ctrl_t *trans_ctrl = (struct rpmb_ctrl_t *)agent_instance->agent_buffer->kernel_addr;
    struct block_device *bdev;
    struct mmc_card *card;

    if(rpmb_agent_open_blkdev(agent_instance, 1)) {
        trans_ctrl->ret = -1;
        return;
    }
    bdev = (struct block_device *)agent_instance->agent_data;

    card = get_mmc_card(bdev);
    if (IS_ERR(card)) {
        TCERR("get mmc card fail\n");
        trans_ctrl->ret = -1;
        return;
    }

    TCDEBUG("EMMC Card info:\n");
    TCDEBUG("cid: %08x%08x%08x%08x\n",
        card->raw_cid[0], card->raw_cid[1],	card->raw_cid[2], card->raw_cid[3]);
    TCDEBUG("raw_rpmb_size_mult=0x%x, rel_wr_sec_cnt=0x%x\n",
        card->ext_csd.raw_rpmb_size_mult,
        card->ext_csd.rel_sectors);

    /* Get EMMC CID*/
    // just copy to share memory, so dont care the memory bounds
    snprintf(trans_ctrl->args.get_devinfo.cid, sizeof(trans_ctrl->args.get_devinfo.cid)+1,
        "%08x%08x%08x%08x",
        card->raw_cid[0], card->raw_cid[1],	card->raw_cid[2], card->raw_cid[3]);

    /* Get RPMB size*/
    trans_ctrl->args.get_devinfo.rpmb_size_mult = card->ext_csd.raw_rpmb_size_mult;

    /* Get reliable write sector count */
    trans_ctrl->args.get_devinfo.rel_wr_sec_cnt = card->ext_csd.rel_sectors;

    trans_ctrl->ret = 0;
    return;
}

/*
 * the data_ptr from SecureOS is physical address,
 * so, we MUST update to the virtual address,
 * otherwise, segment default
 */
static void update_dataptr(struct rpmb_ctrl_t *trans_ctrl)
{
    uint32_t i, offset=0, datasize;
    uint8_t *dst;
    for (i=0;i<MMC_IOC_MAX_RPMB_CMD;i++) {
        offset = trans_ctrl->args.send_ioccmd.buf_offset[i];
        if (trans_ctrl->args.send_ioccmd.ioc_rpmb.cmds[i].data_ptr) {
            dst = (uint8_t*)trans_ctrl->args.send_ioccmd.buf + offset;
            datasize = trans_ctrl->args.send_ioccmd.ioc_rpmb.cmds[i].blksz
                * trans_ctrl->args.send_ioccmd.ioc_rpmb.cmds[i].blocks;
            //update the data_ptr
            mmc_ioc_cmd_set_data(trans_ctrl->args.send_ioccmd.ioc_rpmb.cmds[i], dst);
        }
    }
}

struct rpmb_agent_lock_info {
    unsigned int dev_id;
    bool lock_need_free;
};
static struct rpmb_agent_lock_info lock_info = {0};

static int process_rpmb_lock(struct tee_agent_kernel_ops* agent_instance)
{
    struct __smc_event_data *event_data;

    mutex_lock(&rpmb_counter_lock);
    TCDEBUG("obtain rpmb device lock\n");
    event_data = find_event_control(agent_instance->agent_id);
    if (event_data) {
        lock_info.dev_id = event_data->cmd.dev_file_id;
        lock_info.lock_need_free = true;
        TCDEBUG("rpmb counter lock context: dev_id=%d\n", lock_info.dev_id);
    }
    return 0;
}

static int process_rpmb_unlock(struct tee_agent_kernel_ops* agent_instance)
{
    memset(&lock_info, 0, sizeof(lock_info));
    lock_info.lock_need_free = false;
    mutex_unlock(&rpmb_counter_lock);
    TCDEBUG("free rpmb device lock\n");
    return 0;
}

#define GET_RPMB_LOCK_MASK 0x01
#define FREE_RPMB_LOCK_MASK 0x02
static void send_ioccmd(struct tee_agent_kernel_ops* agent_instance)
{
    struct rpmb_ctrl_t *trans_ctrl = (struct rpmb_ctrl_t *)agent_instance->agent_buffer->kernel_addr;
    struct block_device *bdev;
    uint8_t lock_flag = trans_ctrl->lock_flag;
    int32_t ret;
    struct mmc_ioc_rpmb *ioc_rpmb;
    struct mmc_blk_ioc_rpmb_data *rpmb_data = NULL;
    uint32_t i;

    if(rpmb_agent_open_blkdev(agent_instance, 1)) {
        trans_ctrl->ret = -1;
        return;
    }
    bdev = (struct block_device *)agent_instance->agent_data;

    update_dataptr(trans_ctrl);

    if (lock_flag & GET_RPMB_LOCK_MASK) {
        process_rpmb_lock(agent_instance);
    }

    rpmb_data = kzalloc(sizeof(struct mmc_blk_ioc_rpmb_data), GFP_KERNEL);
    if (rpmb_data == NULL) {
        TCERR("alloc rpmb_data failed\n");
        ret = -1;
        goto out;
    }
    ioc_rpmb = (struct mmc_ioc_rpmb *)&trans_ctrl->args.send_ioccmd;

    for (i=0;i<MMC_IOC_MAX_RPMB_CMD;i++) {
        rpmb_data->data[i].buf = (unsigned char *)ioc_rpmb->cmds[i].data_ptr;
        rpmb_data->data[i].buf_bytes = ioc_rpmb->cmds[i].blocks * ioc_rpmb->cmds[i].blksz;
        memcpy(&rpmb_data->data[i].ic, &ioc_rpmb->cmds[i], sizeof(struct mmc_ioc_cmd));
    }

    ret = mmc_blk_ioctl_rpmb_cmd(RPMB_FUNC_ID_SECURE_OS, bdev, rpmb_data);
    if (ret)
        TCERR("mmc_blk_ioctl_rpmb_cmd failed: %d\n", ret);

out:
    kfree(rpmb_data);

    //TODO: if globalTask or TA in TrustedCore is crash in middle, will never free this lock
    if (lock_flag & FREE_RPMB_LOCK_MASK) {
        process_rpmb_unlock(agent_instance);
    }

    trans_ctrl->ret = ret;
}

static int rpmb_agent_work(struct tee_agent_kernel_ops* agent_instance)
{
    struct rpmb_ctrl_t *trans_ctrl = (struct rpmb_ctrl_t *)agent_instance->agent_buffer->kernel_addr;
    switch (trans_ctrl->cmd) {
    case sec_get_devinfo:
        TCDEBUG("rpmb agent cmd is get_devinfo\n");
        get_devinfo(agent_instance);
        break;
    case sec_send_ioccmd:
        TCDEBUG("rpmb agent cmd is send ioc\n");
        send_ioccmd(agent_instance);
        break;
    case sec_rpmb_lock:
        TCDEBUG("rpmb agent cmd is lock\n");
        process_rpmb_lock(agent_instance);
        trans_ctrl->ret = 0;
        break;
    case sec_rpmb_unlock:
        TCDEBUG("rpmb agent cmd is unlock\n");
        process_rpmb_unlock(agent_instance);
        trans_ctrl->ret = 0;
        break;
    default :
        break;
    }
    return 0;
}

static int rpmb_agent_crash_work(struct tee_agent_kernel_ops* agent_instance, TC_NS_ClientContext *context, unsigned int dev_file_id)
{
    TCDEBUG("check free lock or not, dev_id=%d\n", dev_file_id);
    if (lock_info.lock_need_free && (lock_info.dev_id == dev_file_id)) {
        TCERR("CA crash, need to free lock\n");
        process_rpmb_unlock(agent_instance);
    }
    return 0;
}

static struct tee_agent_kernel_ops rpmb_agent_ops = {
    .agent_name = "rpmb",
    .agent_id = 0x4abe6198,
    .tee_agent_init = rpmb_agent_init,
    .tee_agent_work = rpmb_agent_work,
    .tee_agent_exit = rpmb_agent_exit,
    .tee_agent_crash_work = rpmb_agent_crash_work,
    .list = LIST_HEAD_INIT(rpmb_agent_ops.list)
};

int rpmb_agent_register(void)
{
    tee_agent_kernel_register(&rpmb_agent_ops);
    return 0;
}
EXPORT_SYMBOL(rpmb_agent_register);
