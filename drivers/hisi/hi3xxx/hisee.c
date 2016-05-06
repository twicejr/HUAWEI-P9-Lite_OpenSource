#include <linux/fd.h>
#include <linux/tty.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/notifier.h>
#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/hisi/ipc_msg.h>
#include <linux/hisi/hisi_rproc.h>
#include "hisee.h"

struct dentry *g_hisee_dir;
hisee_work_struct g_hisee_work;
hisee_work_struct g_hisee_log_work;
hisee_log_header *g_hisee_log_header;

static const struct file_operations hisee_ctrl_fops =
{
    .open       = hisee_open,
    .read       = seq_read,
    .write      = hisee_write,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static struct notifier_block hisee_msg_nb;

static struct semaphore g_rcv_lpmcu_sem;
static struct semaphore g_hisee_exc_sem;
static struct semaphore g_read_cos_apptable_sem;
int g_hisee_power_up_status;
extern int atfd_hisee_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2);

int hisee_read_image(char *path)
{
    long fd;
    mm_segment_t fs = 0;
    int ret;
    int read_size = 0;

    /* free work buffer */
    if (g_hisee_work.buffer) {
        dma_free_coherent(&g_hisee_work.dev, \
                          ALIGN_UP_4KB(g_hisee_work.size), \
                          g_hisee_work.buffer, \
                          g_hisee_work.phy);
    }

    fs = get_fs();
    set_fs(KERNEL_DS);
    pr_err("open %s\r\n", path);

    fd = sys_open(path, O_RDWR, 0);
    if (fd < 0) {
        pr_err("open %s failed\r\n", path);
        set_fs(fs);
        return ERROR;
    }

    g_hisee_work.size = sys_lseek(fd, 0, SEEK_END);
    pr_err("file size is 0x%x\r\n", g_hisee_work.size);
    sys_lseek(fd, 0, SEEK_SET);

    g_hisee_work.buffer = (unsigned int *)dma_alloc_coherent(&g_hisee_work.dev, \
                                                     ALIGN_UP_4KB(g_hisee_work.size),\
                                                     (dma_addr_t *)&g_hisee_work.phy,\
                                                     GFP_KERNEL);
    if (NULL == g_hisee_work.buffer) {
        pr_err("alloc 0x%x fail\r\n", ALIGN_UP_4KB(g_hisee_work.size));
        sys_close(fd);
        set_fs(fs);
        return ERROR;
    }
    pr_err("work buffer 0x%x, phy is 0x%x\r\n", (unsigned int)(unsigned long)g_hisee_work.buffer, g_hisee_work.phy);

    pr_err("g_hisee_work.size = 0x%x\r\n", g_hisee_work.size);
    read_size = sys_read(fd, (char *)g_hisee_work.buffer, (s32)g_hisee_work.size);
    pr_err("g_hisee_work.size = 0x%x\r\n", g_hisee_work.size);
    if(g_hisee_work.size == read_size) {
        pr_debug("read image success\r\n");
        ret = OK;
    }
    else {
        pr_err("read image fail\r\n");
        ret = ERROR;
    }

    sys_close(fd);
    set_fs(fs);

    return ret;
}


int hisee_ctrl(u32 smc_id, char *path)
{
    /*long fd;
    mm_segment_t fs = 0;*/
    static int hisee_init_flag = 0;

    pr_err("hisee_ctrl\n");
    /*if (0 == hisee_init_flag) {
        pr_debug("wait hisee init ok\n");
        down(&g_read_cos_apptable_sem);
        pr_debug("hisee init ok\n");
        hisee_init_flag = 1;
    }*/

    if (smc_id < SMC_DOWNLOAD_END) {
        if (OK == hisee_read_image(path)) {
            pr_err("g_hisee_work.size = 0x%x\r\n", g_hisee_work.size);
            atfd_hisee_smc(HISEE_FN_DOWNLOAD, (u64)smc_id, g_hisee_work.phy, g_hisee_work.size);
            return OK;
        }
        else {
            return ERROR;
        }
    }
    else {
        atfd_hisee_smc(HISEE_FN_DOWNLOAD, (u64)smc_id, 0, 0);
        return OK;
    }
}


void hisee_log_save_test(void)
{
    memset(g_hisee_log_work.buffer, 0xaa, HISEE_LOG_BUFFER_SIZE);
}

static void hisee_log_save(void)
{
    long fd;
    mm_segment_t fs = 0;

    fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_open("/data/hisee_log.bin", O_RDWR|O_CREAT, 0);
    sys_write(fd, (char *)g_hisee_log_work.buffer, HISEE_LOG_BUFFER_SIZE);
    sys_close(fd);

    set_fs(fs);
}


int hisee_rcv_lpmcu(struct notifier_block *nb, unsigned long len, void *msg)
{
    int * data = (int *)msg;
    if (HISEE_LPM3_CMD == data[0]) {
        pr_debug("hisee_rcv_lpmcu\n");
        g_hisee_power_up_status = data[1];
        up(&g_rcv_lpmcu_sem);
    }
    return OK;
}

/*static void  hisee_power_up_callback(rproc_msg_t *ack_buffer,
				rproc_msg_len_t ack_buffer_len,
				int error, void *data)
{

	if (error) {
		pr_err("[%s]: error = %d\n",
				__func__, error);
		return;
	}
    pr_err("xxxxxxx:%s , buff[0] = 0x%08x, len = %d, error = %d\n", __func__, (unsigned int)(ack_buffer[0]), ack_buffer_len, error);
}*/

static int hisee_power_up(void)
{
    /*int ack;*/
    union ipc_data lpm3Msg;

    lpm3Msg.cmd_mix.cmd_src     = OBJ_AP;
	lpm3Msg.cmd_mix.cmd_obj     = OBJ_LPM3;
	lpm3Msg.cmd_mix.cmd         = CMD_NOTIFY;
	lpm3Msg.cmd_mix.cmd_type    = 0;
	lpm3Msg.data[1]             = 0x01000101;

    pr_debug("hisee_power_up\n");
    /* send cmd to lpmcu */
    if (OK != RPROC_ASYNC_SEND(HISI_RPROC_LPM3_MBX13, (rproc_msg_t *)&lpm3Msg, sizeof(lpm3Msg)/sizeof(int))) {
        pr_err("send power up msg fail\n");
        pr_err("power up hisee fail\n");
        return ERROR;
    }

    /* wait ack from lpmcu */
    pr_info("power up hisee wait ack\n");
    down(&g_rcv_lpmcu_sem);

    /* print result */
    if (SE_ACK_AP_POWERUP_INSE_SUCCESS == g_hisee_power_up_status) {
        pr_info("power up hisee ok\n");
        return OK;
    }
    else {
        pr_err("ack fail\n");
        pr_err("power up hisee fail\n");
        return ERROR;
    }
}

static int hisee_show(struct seq_file *s, void *data)
{
    pr_debug("%s: %s\n", "hisee", __FUNCTION__);
    return 0;
}

static int hisee_open(struct inode *inode, struct file *file)
{
    return single_open(file, hisee_show, inode->i_private);
}

int str2value(char *str, int * cal_value)
{
    int bit_value = 10;
    int len = 0;
    int start = 0;
    int i;
    int value = 0;
    char tmp;
    int mul_value = 1;

    while ((*(str+len) != 0x20) && (*(str+len) != 0)) {
        len++;
    }

    if(0 == strncmp(str, "0x", 2))
    {
        bit_value = 16;
        start = 2;
    }

    for(i = len; i > start; i--)
    {
        tmp = *(str + i - 1);
        if(bit_value == 10)
        {
            if((tmp >= '0') && (tmp <= '9'))
            {
                tmp -= 0x30;
            }
            else
            {
                return ERROR;
            }

        }
        else
        {
            if((tmp >= '0') && (tmp <= '9'))
            {
                tmp -= 0x30;
            }
            else if((tmp >= 'a') && (tmp <= 'f'))
            {
                tmp -= ('a' - 10);
            }
            else if((tmp >= 'A') && (tmp <= 'F'))
            {
                tmp -= ('A' - 10);
            }
            else
            {
                return ERROR;
            }
        }

        value += tmp*mul_value;
        mul_value *= bit_value;
    }

    *cal_value = value;
    return OK;
}


static ssize_t hisee_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
    char hisee_cmd[CMD_MAX_SIZE] = {0};
    int offset = 0;
    u64 smc_id = 0;
    unsigned int addr = 0;
    unsigned int value = 0;

	if (count >= CMD_MAX_SIZE) {
	    pr_err("count is bad.\n");
		count = -EINVAL;
		return count;
	}

	if (copy_from_user(hisee_cmd, buf, count - 1)) {
		count = -EINVAL;
        pr_err("copy from user failed.\n");
		return count;
	}

    pr_debug("hisee_cmd:%s\n", hisee_cmd);

    /********************************************************
       hisee_cmd format ==>  download image path
                             exitloop (default is no_transfer_encode)
                             exitloop transfer_encode
       for example: download sloader /data/update/sloader.img
                    download otp /data/update/otp.img
                    download cos /data/update/cos.img
                    download patch /data/update/rom_patch.img
    ********************************************************/
    /* parse hisee_cmd */
    /* bypass space char */
    BYPASS_SPACE_CHAR(hisee_cmd,offset,count)

    /* check power up cmd */
    if (0 == strncmp(hisee_cmd + offset, "powerup", sizeof("powerup") - 1)) {
        hisee_power_up();
        return count;
    }

    /* check log save cmd */
    if (0 == strncmp(hisee_cmd + offset, "log", sizeof("log") - 1)) {
        hisee_log_save();
        return count;
    }

    /* check reset cmd */
    if (0 == strncmp(hisee_cmd + offset, "reset", sizeof("reset") - 1)) {
        hisee_ctrl(SMC_RESET_HISEE, hisee_cmd + offset);
        return count;
    }

    /* set download flag cmd */
    if (0 == strncmp(hisee_cmd + offset, "set download", sizeof("set download") - 1)) {
        hisee_ctrl(SMC_SET_DOWNLOAD, hisee_cmd + offset);
        return count;
    }

    /* read and write register */
    if (0 == strncmp(hisee_cmd + offset, "readreg", sizeof("readreg") - 1)) {
        offset += sizeof("readreg") - 1;
        /* bypass space char */
        BYPASS_SPACE_CHAR(hisee_cmd,offset,count)

        /* get register address */
        if (OK == str2value(hisee_cmd + offset, &addr)) {
            atfd_hisee_smc(HISEE_FN_DOWNLOAD, (u64)SMC_READ_REG, (u64)addr, 0);
        }
        return count;
    }
    if (0 == strncmp(hisee_cmd + offset, "writereg", sizeof("writereg") - 1)) {
        offset += sizeof("writereg") - 1;
        /* bypass space char */
        BYPASS_SPACE_CHAR(hisee_cmd,offset,count)

        /* get register address and value */
        if (OK == str2value(hisee_cmd + offset, &addr)) {
            while (0x20 != hisee_cmd[offset]) {
                offset++;
            }
            /* bypass space char */
            BYPASS_SPACE_CHAR(hisee_cmd,offset,count)
            str2value(hisee_cmd + offset, &value);
            atfd_hisee_smc(HISEE_FN_DOWNLOAD, (u64)SMC_WRITE_REG, (u64)addr, (u64)value);
        }
        return count;
    }

    if (0 == strncmp(hisee_cmd + offset, "set_emmc_flag", sizeof("set_emmc_flag") - 1)) {
        offset += sizeof("set_emmc_flag") - 1;
        /* bypass space char */
        BYPASS_SPACE_CHAR(hisee_cmd,offset,count)

        /* get value */
        if (OK == str2value(hisee_cmd + offset, &value)) {
            atfd_hisee_smc(HISEE_FN_DOWNLOAD, (u64)SMC_SET_EMMC_BUG_FLAG, (u64)value, 0);
        }
        return count;
    }

    if (0 == strncmp(hisee_cmd + offset, "writekey", sizeof("writekey") - 1)) {
        offset += sizeof("writekey") - 1;
        atfd_hisee_smc(HISEE_FN_DOWNLOAD, (u64)SMC_WRITE_KEY, 0, 0);
        return count;
    }

    /* run function */
    if (0 == strncmp(hisee_cmd + offset, "run", sizeof("run") - 1)) {
        offset += sizeof("run") - 1;
        /* bypass space char */
        BYPASS_SPACE_CHAR(hisee_cmd,offset,count)

        /* get function address */
        if (OK == str2value(hisee_cmd + offset, &addr)) {
            while (0x20 != hisee_cmd[offset]) {
                offset++;
            }
            /* bypass space char */
            BYPASS_SPACE_CHAR(hisee_cmd,offset,count)
            if (OK == str2value(hisee_cmd + offset, &value)) {
                atfd_hisee_smc(HISEE_FN_DOWNLOAD, (u64)SMC_RUN_FUNCTION, (u64)addr, (u64)value);
            }
        }
        return count;
    }

    /* check exitloop cmd */
    if (0 == strncmp(hisee_cmd + offset, "exitloop", sizeof("exitloop") - 1)) {
        offset += sizeof("exitloop") - 1;
        /* bypass space char */
        BYPASS_SPACE_CHAR(hisee_cmd,offset,count)

        if (0 == strncmp(hisee_cmd + offset, "bypass sec", sizeof("bypass sec") - 1)) {
            hisee_ctrl(SMC_EXIT_LOOP_BYPASS_SEC, hisee_cmd + offset);
        }
        else if (0 == strncmp(hisee_cmd + offset, "transfer_encode", sizeof("transfer_encode") - 1)) {
            hisee_ctrl(SMC_EXIT_LOOP_TRANSFER_ENC, hisee_cmd + offset);
        }
        else {
            hisee_ctrl(SMC_EXIT_LOOP_NO_TRANSFER_ENC, hisee_cmd + offset);
        }
		return count;
	}

    if (0 != strncmp(hisee_cmd + offset, "download", sizeof("download") - 1)) {
        pr_err("download string is bad.\n");
		count = -EINVAL;
		return count;
	}

    offset += sizeof("download") - 1;

    /* bypass space char */
    BYPASS_SPACE_CHAR(hisee_cmd,offset,count)

    if (0 == strncmp(hisee_cmd + offset, "sloader", sizeof("sloader") - 1)) {
        /* download sloader */
        offset += sizeof("sloader") - 1;
        smc_id = SMC_DOWNLOAD_SLODER;
    }
    else if (0 == strncmp(hisee_cmd + offset, "otp", sizeof("otp") - 1)) {
        /* download otp */
        offset += sizeof("otp") - 1;
        smc_id = SMC_DOWNLOAD_OTP;
    }
    else if (0 == strncmp(hisee_cmd + offset, "cos", sizeof("cos") - 1)) {
        /* download cos */
        offset += sizeof("cos") - 1;
        smc_id = SMC_DOWNLOAD_COS;
    }
    else if (0 == strncmp(hisee_cmd + offset, "patch", sizeof("patch") - 1)) {
        /* download cos */
        offset += sizeof("patch") - 1;
        smc_id = SMC_DOWNLOAD_PATCH;
    }
    else {
        pr_err("image name is bad.\n");
		count = -EINVAL;
		return count;
    }

    /* bypass space char */
    BYPASS_SPACE_CHAR(hisee_cmd,offset,count)

    if (OK != hisee_ctrl(smc_id, hisee_cmd + offset)) {
        count = -EINVAL;
    }

    return count;
}

int hisee_create_file(void)
{
    g_hisee_dir = debugfs_create_dir("hisee", NULL);
    if (g_hisee_dir) {
        if (NULL == debugfs_create_file("hisee_ctrl", S_IRUGO, g_hisee_dir, NULL, &hisee_ctrl_fops)) {
            debugfs_remove_recursive(g_hisee_dir);
            return ERROR;
        }
    } else {
        return ERROR;
    }

    return OK;
}


static void hisee_delete_file(void)
{

    debugfs_remove_recursive(g_hisee_dir);
}

int hisee_alloc_log_buffer(void)
{
    int timeout = 0;
    g_hisee_log_work.buffer = (unsigned int *)dma_alloc_coherent(&g_hisee_log_work.dev, \
                                                    HISEE_LOG_BUFFER_SIZE, \
                                                    (dma_addr_t *)&g_hisee_log_work.phy, \
                                                    GFP_KERNEL);
    if (NULL == g_hisee_log_work.buffer) {
        pr_err("alloc log buffer fail,size id 0x%x\n", HISEE_LOG_BUFFER_SIZE);
        return ERROR;
    }

    g_hisee_log_header      = (hisee_log_header *)g_hisee_log_work.buffer;
    g_hisee_log_header->ack = SE_CMD_ACK_NULL;

    atfd_hisee_smc(HISEE_FN_DOWNLOAD, SMC_TRANSFER_LOG_INFO, g_hisee_log_work.phy, HISEE_LOG_BUFFER_SIZE);

    /* wait ack from atf */
    while (1) {
        if (SE_CMD_ACK_NULL != g_hisee_log_header->ack) {
            break;
        }
        if (timeout++ > 10000) {
            break;
        }
        msleep(1);
    }

    if (SE_CMD_ACK_OK == g_hisee_log_header->ack) {
        pr_info("alloc log buffer ok\n");
        return OK;
    }
    else {
        pr_err("atf ack fail\n");
        pr_err("alloc log buffer fail\n");
        dma_free_coherent(&g_hisee_log_work.dev, \
                      HISEE_LOG_BUFFER_SIZE, \
                      g_hisee_log_work.buffer, \
                      g_hisee_log_work.phy);
        return ERROR;
    }
}

static void hisee_free_log_buffer(void)
{
    dma_free_coherent(&g_hisee_log_work.dev, \
                      HISEE_LOG_BUFFER_SIZE, \
                      g_hisee_log_work.buffer, \
                      g_hisee_log_work.phy);
}

void hisee_debug(void)
{
    pr_info("0x%x\n", g_hisee_log_header->ack);
}


int hisee_read_cos_apptable(void *data)
{
    int ret;
    /*static int first_flag = 0;*/
    pr_info("hisee_read_cos_apptable enter\n");
    /*if (0 == first_flag) {
        first_flag = 1;
        msleep(90000);
    }*/
    g_hisee_log_header->ack = SE_CMD_ACK_NULL;

    atfd_hisee_smc(HISEE_FN_DOWNLOAD, SMC_READ_COS_PARTITION, 0, 0);

    /* wait ack from atf */
    pr_info("wait cos partition ack\n");
    while (1) {
        if (SE_CMD_ACK_NULL != g_hisee_log_header->ack) {
            break;
        }
        msleep(1);
    }

    do {
        /* check cos partition flag */
        if ((SE_CMD_ACK_OK | (COS_PARTITION_ID << 8)) == g_hisee_log_header->ack) {
            pr_info("read cos partition ok\n");
        }
        else {
            pr_err("read cos partition fail\n");
            ret = ERROR;
            break;
        }

        /* wait ack from atf */
        while (1) {
            if ((SE_CMD_ACK_OK | (COS_PARTITION_ID << 8))  != g_hisee_log_header->ack) {
                break;
            }
            msleep(1);
        }

        if ((SE_CMD_ACK_OK | (APP_TABLE_ID << 8)) == g_hisee_log_header->ack) {
            pr_info("read apptable ok\n");
            ret = OK;
            break;
        }
        else {
            pr_err("read apptable fail\n");
            ret = ERROR;
            break;
        }
    }while(0);

    up(&g_read_cos_apptable_sem);
    return ret;
}

int hisee_exception_process(void)
{
    /* save exception log */
    up(&g_hisee_exc_sem);
    return OK;
}

int hisee_exception_save(void *data)
{
    while(1) {
        down(&g_hisee_exc_sem);
        hisee_log_save();
    }
}

/*static int __init  hisee_init(void)*/
int hisee_init(void)
{
    struct task_struct      *taskid;

    if (OK != hisee_create_file()) {
        pr_err("hisee create file failed.\n");
        return ERROR;
    }

#if defined (CONFIG_HISEE_TEST)
    if (OK != hisee_create_test_file()) {
        pr_err("hisee create test file failed.\n");
        return ERROR;
    }
#endif

    if (OK != hisee_alloc_log_buffer()) {
        hisee_delete_file();
        pr_err("hisee alloc log buffer failed.\n");
        return ERROR;
    }

#if 0
    taskid = kthread_run(hisee_read_cos_apptable, NULL, "read_cos");

    if (IS_ERR(taskid)) {
        hisee_delete_file();
        hisee_free_log_buffer();
        pr_err("hisee read cos partition failed.\n");
        return ERROR;
    }
#endif
    taskid = kthread_run(hisee_exception_save, NULL, "exc_save");

    if (IS_ERR(taskid)) {
        hisee_delete_file();
        hisee_free_log_buffer();
        pr_err("hisee create exception task failed.\n");
        return ERROR;
    }
    sema_init(&g_read_cos_apptable_sem, 0);
    sema_init(&g_hisee_exc_sem, 0);

    /* register call back for the message from lpmcu */
    sema_init(&g_rcv_lpmcu_sem, 0);
    hisee_msg_nb.next = NULL;
	hisee_msg_nb.notifier_call = hisee_rcv_lpmcu;
    RPROC_MONITOR_REGISTER(HISI_RPROC_LPM3_MBX0, &hisee_msg_nb);

    return OK;
}
late_initcall_sync(hisee_init);

#if defined (CONFIG_HISEE_TEST)
hisee_work_struct g_hisee_test;
hisee_work_struct g_hisee_result;

static const struct file_operations hisee_test_fops =
{
    .open       = hisee_open,
    .read       = seq_read,
    .write      = hisee_test_write,
    .llseek     = seq_lseek,
    .release    = single_release,
};

int hisee_test(char *path, long result_phy, long result_size)
{
    long fd;
    int ret = ERROR;
    mm_segment_t fs = 0;
    /*long rcv_result_phy;*/
    hisee_test_header *hisee_test_h;
    int temp = 0;

    if (g_hisee_test.buffer) {
        dma_free_coherent(&g_hisee_test.dev, \
                          ALIGN_UP_4KB(g_hisee_test.size), \
                          g_hisee_test.buffer, \
                          g_hisee_test.phy);
    }

    fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_open(path, O_RDWR, 0);
    if (fd < 0) {
        pr_err("open %s failed\r\n", path);
        set_fs(fs);
        return ERROR;
    }

    g_hisee_test.size = sys_lseek(fd, 0, SEEK_END);
    g_hisee_test.size += sizeof(hisee_test_header);
    pr_debug("file size is 0x%x\r\n", g_hisee_test.size);
    sys_lseek(fd, 0, SEEK_SET);

    g_hisee_test.buffer = (unsigned int *)dma_alloc_coherent(&g_hisee_test.dev, \
                                                     ALIGN_UP_4KB(g_hisee_test.size), \
                                                     (dma_addr_t *)&g_hisee_test.phy, \
                                                     GFP_KERNEL);
    if (NULL == g_hisee_test.buffer) {
        pr_err("alloc 0x%x fail\r\n", ALIGN_UP_4KB(g_hisee_test.size));
        sys_close(fd);
        set_fs(fs);
        return ERROR;
    }
    pr_debug("work buffer is 0x%x, phy is 0x%x\r\n", (unsigned int)(unsigned long)g_hisee_test.buffer, g_hisee_test.phy);

    hisee_test_h            = (hisee_test_header *)g_hisee_test.buffer;
    hisee_test_h->status    = TEST_RUNNING;
    hisee_test_h->phy       = (int)result_phy;
    hisee_test_h->size      = (int)result_size;

    ret = sys_read(fd, (char *)(g_hisee_test.buffer + (sizeof(hisee_test_header)/sizeof(int))), \
                   (s32)g_hisee_test.size - sizeof(hisee_test_header));
    if ((s32)g_hisee_test.size - sizeof(hisee_test_header) != ret) {
        pr_err("read 0x%x fail\r\n", (unsigned int)(g_hisee_test.size - sizeof(hisee_test_header)));
    }

    sys_close(fd);
    sys_unlink(TEST_SUCCESS_FILE);
    sys_unlink(TEST_FAIL_FILE);
    sys_unlink(TEST_RESULT_FILE);
    set_fs(fs);

    atfd_hisee_smc(HISEE_TEST_FN_DOWNLOAD, 0, g_hisee_test.phy, g_hisee_test.size);

    fs = get_fs();
    set_fs(KERNEL_DS);

    /*wait test finish flag*/
    while (1) {
        if (TEST_RUNNING != hisee_test_h->status) {
            break;
        }
        temp++;
        msleep(1);
        if ((temp % 1000) == 0) {
            pr_err("wait result\r\n");
        }

        if (temp  == 300000) {
            pr_err("test fail\r\n");
            break;
        }
    }

    if (TEST_SUCCESS == hisee_test_h->status) {
        /* create file for test flag */
        pr_debug("rcv result size is 0x%x\r\n", hisee_test_h->size);
        if ((g_hisee_result.phy == (long)hisee_test_h->phy) && \
            (g_hisee_result.size >= (long)hisee_test_h->size)) {
            fd = sys_open(TEST_RESULT_FILE, O_RDWR|O_CREAT, 0);
            sys_write(fd, (char *)g_hisee_result.buffer, hisee_test_h->size);
            sys_close(fd);
            fd = sys_open(TEST_SUCCESS_FILE, O_RDWR|O_CREAT, 0);
            sys_close(fd);
            ret = OK;
        }
        else {
            fd = sys_open(TEST_FAIL_FILE, O_RDWR|O_CREAT, 0);
            sys_close(fd);
            ret = ERROR;
        }
    }
    else {
        fd = sys_open(TEST_FAIL_FILE, O_RDWR|O_CREAT, 0);
        sys_close(fd);
        ret = ERROR;
    }
    set_fs(fs);
    return ret;
}

static ssize_t hisee_test_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
    char hisee_cmd[CMD_MAX_SIZE] = {0};
    int offset = 0;
    int i,j,k = 0;
    int temp;

	if (count >= CMD_MAX_SIZE) {
	    pr_err("count is bad.\n");
		count = -EINVAL;
		return count;
	}

	if (copy_from_user(hisee_cmd, buf, count - 1)) {
		count = -EINVAL;
        pr_err("copy from user failed.\n");
		return count;
	}

    pr_debug("hisee_cmd:%s\n", hisee_cmd);

    /********************************************************
       hisee_cmd format ==>  test result_size:0xXXXX path
       for example: test result_size:0x4000 /data/test/print.img
                    test /data/test/seceng.img
    ********************************************************/
    /* parse hisee_cmd */
    /* bypass space char */
    while (1) {
        if (0x20 != hisee_cmd[offset]) {
            break;
        }
        if (offset >= CMD_MAX_SIZE) {
            pr_err("hisee_cmd is bad.\n");
		    count = -EINVAL;
		    return count;
        }
        offset++;
    }

    if (0 != strncmp(hisee_cmd + offset, "test", sizeof("test") - 1)) {
        pr_err("test string is bad.\n");
		count = -EINVAL;
		return count;
	}

    offset += sizeof("test") - 1;

    /* bypass space char */
    while (1) {
        if (0x20 != hisee_cmd[offset]) {
            break;
        }
        if (offset >= CMD_MAX_SIZE) {
            pr_err("hisee_cmd is bad.\n");
		    count = -EINVAL;
		    return count;
        }
        offset++;
    }

    /* check buffer size */
    if (0 == strncmp(hisee_cmd + offset, "result_size:0x", sizeof("result_size:0x") - 1)) {
        offset += sizeof("result_size:0x") - 1;
        /* find last size char */
        i = 0;
        while (0x20 != hisee_cmd[offset + i]) {
            i++;
        }

        if (0 == i) {
            pr_err("result size is bad, use default size.\n");
            g_hisee_result.size = TEST_RESULT_SIZE_DEFAULT;
        }
        else {
            g_hisee_result.size = 0;
            k = i;
            i--;
            j = 0;
            while(i >= 0) {
                if ((hisee_cmd[offset + i] >= '0') && (hisee_cmd[offset + i] <= '9')) {
                    temp = hisee_cmd[offset + i] - 0x30;
                }
                else if ((hisee_cmd[offset + i] >= 'a') && (hisee_cmd[offset + i] <= 'f')) {
                    temp = hisee_cmd[offset + i] - 'a' + 0x10;
                }
                else if ((hisee_cmd[offset + i] >= 'A') && (hisee_cmd[offset + i] <= 'F')) {
                    temp = hisee_cmd[offset + i] - 'A' + 0x10;
                }
                else {
                    pr_err("result size is bad, use default size.\n");
                    g_hisee_result.size = TEST_RESULT_SIZE_DEFAULT;
                    break;
                }
                g_hisee_result.size += (temp << j);
                i--;
                j += 4;
            }
        }
        offset += k;
    }
    else {
        g_hisee_result.size = TEST_RESULT_SIZE_DEFAULT;
    }

    pr_debug("result size is 0x%x.\n", g_hisee_result.size);
    if (0 == g_hisee_result.size) {
        pr_err("result size is bad.\r\n");
        return ERROR;
    }

    /* bypass space char */
    while (1) {
        if (0x20 != hisee_cmd[offset]) {
            break;
        }
        if (offset >= CMD_MAX_SIZE) {
            pr_err("cmd is bad.\n");
		    count = -EINVAL;
		    return count;
        }
        offset++;
    }

    if (0 == hisee_cmd[offset]) {
        pr_err("test file path is bad.\n");
	    count = -EINVAL;
	    return count;
    }

    if (NULL != g_hisee_result.buffer) {
         dma_free_coherent(&g_hisee_result.dev, \
                      ALIGN_UP_4KB(g_hisee_result.size), \
                      g_hisee_result.buffer, \
                      g_hisee_result.phy);
    }

    g_hisee_result.buffer = (unsigned int *)dma_alloc_coherent(&g_hisee_result.dev, \
                                                       ALIGN_UP_4KB(g_hisee_result.size), \
                                                       (dma_addr_t *)&g_hisee_result.phy, \
                                                       GFP_KERNEL);
    if (NULL == g_hisee_result.buffer) {
        pr_err("hisee_test_write: alloc 0x%x fail.\r\n", ALIGN_UP_4KB(g_hisee_result.size));
        return ERROR;
    }

    if (ERROR == hisee_test(hisee_cmd + offset, g_hisee_result.phy, g_hisee_result.size)) {
        pr_err("hisee_test_write: test fail,keep test buffer.\r\n");
        return ERROR;
    }

    dma_free_coherent(&g_hisee_result.dev, \
                      ALIGN_UP_4KB(g_hisee_result.size), \
                      g_hisee_result.buffer, \
                      g_hisee_result.phy);
    g_hisee_result.buffer = NULL;

    return count;
}

static int hisee_create_test_file(void)
{
    if (g_hisee_dir) {
        if (NULL == debugfs_create_file("hisee_test", S_IRUGO, g_hisee_dir, NULL, &hisee_test_fops)) {
            debugfs_remove_recursive(g_hisee_dir);
            return ERROR;
        }
    } else {
        return ERROR;
    }

    return OK;
}

void hisee_exception_test(void)
{
    atfd_hisee_smc(HISEE_FN_DOWNLOAD, SMC_DOWNLOAD_TEST2, 0, 0);
}
#endif



MODULE_AUTHOR("chenyingguo@huawei.com>");
MODULE_DESCRIPTION("HISEE DRIVER");
MODULE_LICENSE("GPL");

