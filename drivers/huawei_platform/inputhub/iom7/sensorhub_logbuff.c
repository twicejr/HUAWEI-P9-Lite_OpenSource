#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/proc_fs.h>
#include <linux/sysfs.h>
#include <linux/mutex.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/reboot.h>
#include <linux/rtc.h>
#include <linux/timer.h>
#include "inputhub_route.h"
#include "inputhub_bridge.h"
#include "protocol.h"
#include  <global_ddr_map.h>

#define LOG_BUFF_SIZE (1024*4)
#define DDR_LOG_BUFF_ADDR (HISI_RESERVED_SENSORHUB_SHARE_MEM_PHYMEM_BASE)
#define DDR_LOG_BUFF_SIZE ((0x80000 - IOMCU_CONFIG_SIZE)&~(LOG_BUFF_SIZE-1))
#define DDR_LOG_BUFF_UPDATE_NR	(DDR_LOG_BUFF_SIZE/LOG_BUFF_SIZE)
#define DDR_LOG_BUFF_UPDATE_WATER_MARK	(DDR_LOG_BUFF_UPDATE_NR * 3 / 4)
#define DDR_LOG_BUFF_COPY_SIZE  (DDR_LOG_BUFF_UPDATE_WATER_MARK * LOG_BUFF_SIZE)

#define LOG_SERIAL 1
#define LOG_BUFF 2

//unite jiffies
#define FLUSH_TIMEOUT (2*HZ)

static int isOpened = 0;
static int isNewDataAvailable = 0;
static int isFlushComplete = 0;
static int flush_cnt = 0;

static uint32_t sensorhub_log_r = 0;
static uint32_t sensorhub_log_buf_head = 0;
static uint32_t sensorhub_log_buf_rear = 0;
static uint8_t *pDDRLogBuff = NULL;
static uint8_t *pLocalLogBuff = NULL;
static struct mutex logbuff_mutex;
static struct mutex logbuff_flush_mutex;
static struct proc_dir_entry *logbuff_dentry = NULL;
static uint32_t log_method = LOG_BUFF;
static uint32_t sensorhub_log_full_flag = 0;

#define CONFIG_FLUSH '1'
#define CONFIG_SERIAL '2'
#define CONFIG_BUFF '3'

int32_t gmark = 0xF0;

typedef struct
{
    pkt_header_t hd;
    uint32_t index;
} log_buff_req_t;

static DECLARE_WAIT_QUEUE_HEAD (sensorhub_log_waitq);
static DECLARE_WAIT_QUEUE_HEAD (sensorhub_log_flush_waitq);

static inline void print_stat(int i)
{
//    hwlog_debug("[%d][r %x][head %x][rear %x][full_flag %d]\n", i,  sensorhub_log_r, sensorhub_log_buf_head, sensorhub_log_buf_rear, sensorhub_log_full_flag);
}

static inline int sensorhub_log_buff_left(void)
{
    hwlog_debug("%s %d\n", __func__ ,(sensorhub_log_buf_rear >= sensorhub_log_r)?(sensorhub_log_buf_rear - sensorhub_log_r):(DDR_LOG_BUFF_SIZE -(sensorhub_log_r - sensorhub_log_buf_rear)));
    if(sensorhub_log_full_flag && (sensorhub_log_buf_rear == sensorhub_log_r))
    {
        return 0;
    }
    return (sensorhub_log_buf_rear >= sensorhub_log_r)?(sensorhub_log_buf_rear - sensorhub_log_r):(DDR_LOG_BUFF_SIZE -(sensorhub_log_r - sensorhub_log_buf_rear));
}

static inline void update_local_buff_index(uint32_t new_rear)
{
//update sensorhub_log_r
    if(flush_cnt && sensorhub_log_buff_left() >= (DDR_LOG_BUFF_SIZE - DDR_LOG_BUFF_COPY_SIZE))
    {
        sensorhub_log_r = new_rear;
    }
//update sensorhub_log_buf_head
    if(flush_cnt)
    {
        sensorhub_log_buf_head = new_rear;
    }
//update sensorhub_log_buf_rear
    sensorhub_log_buf_rear = new_rear;
    sensorhub_log_full_flag = 0;
    print_stat(8);
}

static int sensorhub_logbuff_open(struct inode *inode, struct file *file)
{
    /* ÿ��cat /proc/sensorhub_logbuff����open ����sensorhub_log_r = sensorhub_log_r_head ��ʾÿ�ζ���r����Ϊ��ͷָ�롱����ͷ��ʼ�����?*/
    hwlog_info("[%s]\n", __func__);
    if (isOpened)
    {
        hwlog_err("%s sensorhub logbuff already opened !\n", __func__);
        return -1;
    }
    sensorhub_log_r = sensorhub_log_buf_head;
    isOpened = 1;
    return 0;
}

static int sensorhub_logbuff_release(struct inode *inode, struct file *file)
{
    hwlog_info("sensorhub logbuff release\n");
    isOpened = 0;
    return 0;
}

static ssize_t sensorhub_logbuff_read(struct file* file, char __user* buf, size_t count, loff_t* ppos)
{
    int error = 0;
    int cnt = (count > DDR_LOG_BUFF_COPY_SIZE) ? DDR_LOG_BUFF_COPY_SIZE : count;
    int remain;

    hwlog_debug("[%s]\n", __func__);
    if (!buf || !count || !pLocalLogBuff)
    {
        goto err;
    }

    // check cap
    print_stat(1);
    if (sensorhub_log_buff_left() >= count)
    {
        goto copy;
    }
    error = wait_event_interruptible(sensorhub_log_waitq, isNewDataAvailable != 0);
    if (error)
    {
        error = 0;
        goto err;
    }
    isNewDataAvailable = 0;
copy:
    print_stat(2);
    hwlog_debug("[%s] copy cnt %d, %x\n", __func__, cnt, sensorhub_log_r);
    mutex_lock(&logbuff_mutex);
    if ( DDR_LOG_BUFF_SIZE < sensorhub_log_r)
    {
        remain = 0;
        hwlog_err("%s sensorhub_log_r is too large\n", __func__);
    }
    else
    {
        remain = DDR_LOG_BUFF_SIZE - sensorhub_log_r;
    }
    error = cnt;
    // copy to user
    if (cnt > remain)
    {
        if (copy_to_user(buf + remain, pLocalLogBuff, (cnt - remain)))
        {
            hwlog_err("%s failed to copy to user\n", __func__);
            error = -EFAULT;
            goto out;
        }
        cnt = remain;
    }
    if (copy_to_user(buf, pLocalLogBuff + sensorhub_log_r, cnt))
    {
        hwlog_err("%s failed to copy to user\n", __func__);
        error = -EFAULT;
        goto out;
    }
    // update reader pointer
    sensorhub_log_r = (sensorhub_log_r + error) % DDR_LOG_BUFF_SIZE;
    if (!sensorhub_log_full_flag && sensorhub_log_r == sensorhub_log_buf_rear)
    {
        sensorhub_log_full_flag = 1;
    }
out:
    mutex_unlock(&logbuff_mutex);
err:
    print_stat(3);
    return error;
}


static const struct file_operations sensorhub_logbuff_operations = {
    .open = sensorhub_logbuff_open,
    .read = sensorhub_logbuff_read,
    .release = sensorhub_logbuff_release,
};


static int logbuff_full_callback(const pkt_header_t *head)
{
    int cnt = DDR_LOG_BUFF_COPY_SIZE;
    int remain = 0;
    uint32_t update_index = 0;
    uint32_t new_rear = 0;
    log_buff_req_t* pkt = (log_buff_req_t*) head;
    if (pkt->index > DDR_LOG_BUFF_SIZE / LOG_BUFF_SIZE)
    {
	hwlog_err("%s index is too large, log maybe lost\n",__func__);
	update_index = DDR_LOG_BUFF_SIZE;
    }
    else
    {
        update_index = (pkt->index * LOG_BUFF_SIZE);
    }
    new_rear = (update_index + DDR_LOG_BUFF_COPY_SIZE)%DDR_LOG_BUFF_SIZE;
    hwlog_info("[%s]\n", __func__);
    if(update_index != sensorhub_log_buf_rear)
    {
        hwlog_err("%s unsync index, log maybe lost\n",__func__);
    }
    // get rotate log buff index
    mutex_lock(&logbuff_mutex);
    print_stat(4);
    update_local_buff_index(new_rear);
    print_stat(5);
    remain = DDR_LOG_BUFF_SIZE - update_index;
    // update reader pointer
    if (remain < DDR_LOG_BUFF_COPY_SIZE)
    {
        memcpy(pLocalLogBuff, pDDRLogBuff, cnt - remain);
        cnt = remain;
    }
    memcpy(pLocalLogBuff + update_index,
            pDDRLogBuff + update_index, cnt);
    if(!flush_cnt )
    {
        flush_cnt = 1;
    }
    mutex_unlock(&logbuff_mutex);
    isNewDataAvailable = 1;
    // wake up reader
    hwlog_debug("%s wakeup\n",__func__);
    wake_up_interruptible(&sensorhub_log_waitq);
    return 0;
}

static int logbuff_flush_callback(const pkt_header_t *head)
{
    //sensorhub has flush tcm log buff we need update logbuff global vars and flush it to file system
    log_buff_req_t *pkt = (log_buff_req_t *) head;
    uint32_t flush_head = (pkt->index * LOG_BUFF_SIZE);
    uint32_t flush_size = (flush_head > sensorhub_log_buf_rear)?(flush_head - sensorhub_log_buf_rear):(DDR_LOG_BUFF_SIZE - (sensorhub_log_buf_rear -flush_head));
    int remain = 0;
    int timeout_cnt = 100;
    hwlog_debug("[%s] index: %d flush_size %d\n", __func__,pkt->index, flush_size);
    //wait reader till we can update the head
    while(sensorhub_log_buff_left() > (DDR_LOG_BUFF_COPY_SIZE - flush_size) && timeout_cnt--)
    {
        msleep(1);
    }
    if(timeout_cnt < 0)
    {
        hwlog_warn("%s timeout, some log will lost",__func__);
    }
    // get rotate log buff index
    mutex_lock(&logbuff_mutex);
    remain = DDR_LOG_BUFF_SIZE - sensorhub_log_buf_rear;
    if (remain < flush_size)
    {
        memcpy(pLocalLogBuff, pDDRLogBuff, flush_size - remain);
        flush_size = remain;
    }

    memcpy(pLocalLogBuff + sensorhub_log_buf_rear,
            pDDRLogBuff + sensorhub_log_buf_rear, flush_size);
    print_stat(6);
    update_local_buff_index(flush_head);
    print_stat(7);
    if(!flush_cnt)
    {
        flush_cnt = 1;
    }
    mutex_unlock(&logbuff_mutex);
    isNewDataAvailable = 1;
    // wake up reader
    wake_up_interruptible(&sensorhub_log_waitq);
    isFlushComplete = 1;
    //hwlog_debug("%s wakeup\n",__func__);
    wake_up_interruptible(&sensorhub_log_flush_waitq);
    return 0;
}

static void __manual_flush(pkt_header_t* pkt, int size)
{
        hwlog_debug("flush sensorhub log buff\n");
        //do log flush
        mutex_lock(&logbuff_flush_mutex);
        pkt->cmd = CMD_LOG_BUFF_FLUSH;
        inputhub_mcu_write_cmd((void*)pkt, size);
        if(! wait_event_interruptible_timeout(sensorhub_log_flush_waitq, isFlushComplete != 0,FLUSH_TIMEOUT))
        {
            hwlog_err("%s no response",__func__);
        }
        hwlog_debug("flush sensorhub log buff done\n");
        isFlushComplete = 0;
        mutex_unlock(&logbuff_flush_mutex);
}

static ssize_t logbuff_config_set(struct device *dev,
                  struct device_attribute *attr,
                  const char *buf, size_t count)
{
    pkt_header_t pkt = {
        .tag = TAG_LOG_BUFF,
        .resp = NO_RESP,
        .length = 0
    };

    if(buf[0] == CONFIG_FLUSH)
    {
        __manual_flush(&pkt, sizeof(pkt));
    }
    else if(buf[0] == CONFIG_SERIAL)
    {
        hwlog_info("sensorhub log use serial port\n");
        pkt.cmd = CMD_LOG_SER_REQ;
        inputhub_mcu_write_cmd((void*)&pkt,sizeof(pkt));
        log_method = LOG_SERIAL;
    }
    else if(buf[0] == CONFIG_BUFF)
    {
        hwlog_info("sensorhub log use log buff\n");
        pkt.cmd = CMD_LOG_USEBUF_REQ;
        inputhub_mcu_write_cmd((void*)&pkt,sizeof(pkt));
        log_method = LOG_BUFF;
    }
    else
    {
        hwlog_err("%s wrong input, \'1\' for flush \'2\' for serial \'3\' for buff\n",__func__);
        return -EINVAL;
    }
    return count;
}

static ssize_t logbuff_config_show(struct device *dev,
                  struct device_attribute *attr,
                  char *buf)
{
    return sprintf(buf,"%s\n",(log_method == LOG_SERIAL) ? "serial":"buff" );
}

static ssize_t logbuff_flush_show(struct device *dev,
                  struct device_attribute *attr,
                  char *buf)
{
    pkt_header_t pkt = {
        .tag = TAG_LOG_BUFF,
        .resp = NO_RESP,
        .length = 0
    };

//do flush here
    __manual_flush(&pkt, sizeof(pkt));

    return sprintf(buf,"0\n");
}

static DEVICE_ATTR(logbuff_config, S_IWUSR | S_IRUGO,
                  logbuff_config_show,
                  logbuff_config_set);

static DEVICE_ATTR(logbuff_flush, S_IRUGO,
                  logbuff_flush_show,
                  NULL);

static struct platform_device sensorhub_logbuff = {
	.name = "huawei_sensorhub_logbuff",
	.id = -1,
};

extern struct CONFIG_ON_DDR *pConfigOnDDr;
void emg_flush_logbuff(void)
{
    char *p = pDDRLogBuff;
    int i = 0;
    log_buff_req_t pkt;
    pkt.index = sensorhub_log_buf_rear / LOG_BUFF_SIZE;
    hwlog_info("[%s] update head %x\n", __func__,pkt.index);
    //notify userspace
    logbuff_full_callback((const pkt_header_t *)&pkt);
    msleep(100);
    if(pLocalLogBuff && pDDRLogBuff)
    {
        memset(pLocalLogBuff,0,DDR_LOG_BUFF_SIZE);
        //memset(pDDRLogBuff,0,DDR_LOG_BUFF_SIZE);
        for(i=0 ;i<DDR_LOG_BUFF_SIZE ;i++)
        {
            *p++ = 0;
        }
    }
    sensorhub_log_r = 0;
    sensorhub_log_buf_head = 0;
    sensorhub_log_buf_rear = 0;
    flush_cnt = 0;
    //write the head to ddr config block
    pConfigOnDDr->LogBuffCBBackup.mutex = 0;
}
static int sensorhub_logbuff_init(void)
{
    int ret = 0;
    hwlog_info("[%s]\n", __func__);

    if(!getSensorMcuMode()){
	hwlog_err("%s :mcu boot fail, logbuff init err\n", __func__);
	return -1;
    }

    logbuff_dentry = proc_create("sensorhub_logbuff", S_IRUSR | S_IRGRP, NULL, &sensorhub_logbuff_operations);
    if(NULL == logbuff_dentry)
    {
        hwlog_err("%s failed to create logbuff_dentry\n", __func__);
        goto PROC_ERR;
    }

    ret = platform_device_register(&sensorhub_logbuff);
    if (ret) {
    	hwlog_err("%s: platform_device_register failed, ret:%d.\n",
    			__func__, ret);
    	goto REGISTER_ERR;
    }

    ret = device_create_file(&sensorhub_logbuff.dev,&dev_attr_logbuff_config);
    if (ret) {
    	hwlog_err("%s: create %s file failed, ret:%d.\n",
    			__func__,"dev_attr_logbuff_config", ret);
    	goto SYSFS_ERR_1;
    }

    ret = device_create_file(&sensorhub_logbuff.dev,&dev_attr_logbuff_flush);
    if (ret) {
    	hwlog_err("%s: create %s file failed, ret:%d.\n",
    			__func__,"dev_attr_logbuff_flush", ret);
    	goto SYSFS_ERR_2;
    }


    ret = register_mcu_event_notifier(TAG_LOG_BUFF,
                    CMD_LOG_BUFF_ALERT, logbuff_full_callback);
    if (ret)
    {
        hwlog_err("%s failed register notifier CMD_LOG_BUFF_ALERT:ret %d\n", __func__,ret);
        goto NOTIFY_ERR;
    }

    ret = register_mcu_event_notifier(TAG_LOG_BUFF,
                    CMD_LOG_BUFF_FLUSHP, logbuff_flush_callback);
    if (ret)
    {
        hwlog_err("%s failed register notifier CMD_LOG_BUFF_FLUSH:ret %d\n", __func__,ret);
        goto NOTIFY_ERR_1;
    }

   pDDRLogBuff = (uint8_t *) ioremap(DDR_LOG_BUFF_ADDR, DDR_LOG_BUFF_SIZE);
    if (!pDDRLogBuff)
    {
        hwlog_err("%s failed remap log buff\n", __func__);
        goto REMAP_ERR;
    }
    pLocalLogBuff = (uint8_t *) kmalloc(DDR_LOG_BUFF_SIZE, GFP_KERNEL);
    if (!pLocalLogBuff)
    {
        hwlog_err("%s failed to malloc\n", __func__);
        goto MALLOC_ERR;
    }
    memset(pLocalLogBuff,0,DDR_LOG_BUFF_SIZE);
    mutex_init(&logbuff_mutex);
    mutex_init(&logbuff_flush_mutex);
    hwlog_info("[%s] done\n", __func__);
    return 0;
MALLOC_ERR:
    iounmap(pDDRLogBuff);
REMAP_ERR:
    unregister_mcu_event_notifier(TAG_LOG_BUFF, CMD_LOG_BUFF_FLUSHP, logbuff_flush_callback);
NOTIFY_ERR_1:
    unregister_mcu_event_notifier(TAG_LOG_BUFF, CMD_LOG_BUFF_ALERT, logbuff_full_callback);
NOTIFY_ERR:
    device_remove_file(&sensorhub_logbuff.dev,&dev_attr_logbuff_flush);
SYSFS_ERR_2:
    device_remove_file(&sensorhub_logbuff.dev,&dev_attr_logbuff_config);
SYSFS_ERR_1:
    platform_device_unregister(&sensorhub_logbuff);
REGISTER_ERR:
    proc_remove(logbuff_dentry);
PROC_ERR:
    return -1;
}

static void sensorhub_logbuff_exit(void)
{
    iounmap(pDDRLogBuff);
    pDDRLogBuff = NULL;
    kfree(pLocalLogBuff);
    pLocalLogBuff = NULL;
    unregister_mcu_event_notifier(TAG_LOG_BUFF, CMD_LOG_BUFF_FLUSHP, logbuff_flush_callback);
    unregister_mcu_event_notifier(TAG_LOG_BUFF, CMD_LOG_BUFF_ALERT, logbuff_full_callback);
    device_remove_file(&sensorhub_logbuff.dev,&dev_attr_logbuff_flush);
    device_remove_file(&sensorhub_logbuff.dev,&dev_attr_logbuff_config);
    platform_device_unregister(&sensorhub_logbuff);
    proc_remove(logbuff_dentry);
}

device_initcall_sync (sensorhub_logbuff_init);
module_exit (sensorhub_logbuff_exit);

MODULE_LICENSE("GPL");

