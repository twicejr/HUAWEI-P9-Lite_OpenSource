/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_tele_mntn_node.c
  版 本 号   : 初稿
  作    者   : 李彬彬 00186593
  生成日期   : 2014年4月3日
  最近修改   :
  功能描述   : drv tele mntn node
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月3日
    作    者   : 李彬彬 00186593
    修改内容   : 创建文件
  2.注    意   : 如下几个文件夹 .c .h 内容必须完全相同
                 vendor\hisi\confidential\lpmcu\driver\tele_mntn\
                 kernel\drivers\hisi\tele_mntn\

******************************************************************************/
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/time.h>

#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/poll.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/syslog.h>
#if 0  /*sys_class_telemntnsw_dev_onoff*/
#include <linux/module.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#endif
#include <asm/uaccess.h>
#include <asm/io.h>

#include <linux/semaphore.h>
#include <linux/completion.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/debugfs.h>
#include <linux/of_platform.h>
/*#include <linux/delay.h>*/
#include "drv_tele_mntn_platform.h"


#include <linux/jiffies.h>
#include <linux/wait.h>
/*#include "mdrv.h" */
/*#include <linux/hisi/ipc_msg.h>*/

#define TELE_MNTN_NODE_READ_WAIT_TIMEOUT                      (msecs_to_jiffies(2000))  /*ms*/
#define TELE_MNTN_NODE_READ_WAIT_FOREVER                      (MAX_SCHEDULE_TIMEOUT)
#define TELE_MNTN_NODE_READ_WAIT_CONDITION_TRUE               (0x11)  /*wait*/
#define TELE_MNTN_NODE_READ_WAIT_CONDITION_FALSE              (0x10)  /*no wait*/
#define TELE_MNTN_WAKE_UP_ACORE_IPC_CMD ((8<<24) | (17<<16) | (3<<8) | (7<<0))
#define NO_SEQFILE 0

#define SPRINT_LPMCU_LOG(seq_file, fmt, args ...) \
    do{		\
        if (NO_SEQFILE == seq_file)	\
            printk(KERN_INFO fmt, ##args);	\
        else	\
            seq_printf(seq_file, fmt, ##args);	\
    }while(0)

static struct notifier_block tele_mntn_ipc_msg_nb;

#if defined(CONFIG_HISI_LPMCU_BB)
extern int rdr_lpm3_stat_dump(void);
#endif

DECLARE_WAIT_QUEUE_HEAD(node_read_wait);
//static int node_read_part_need_wait_delay_times = 0;
static signed long node_read_wait_timeout = TELE_MNTN_NODE_READ_WAIT_FOREVER;
static int node_read_wait_condition = TELE_MNTN_NODE_READ_WAIT_CONDITION_TRUE;

static struct semaphore rw_sem; /* get the access of modify the rp & wp, nobody can't modify them (means access to the buf) without rw_lock */

static int tele_mntn_node_open(struct inode * inode, struct file * file)
{
    /*printk(KERN_ERR"tele_mntn_node_open\n");*/
    /*tele_mntn_func_sw_bit_set(TELE_MNTN_NVME_LOGCAT);*/
    /*tele_mntn_func_sw_bit_set(TELE_MNTN_NVME_WAKEUP_ACPU);*/
	return 0;
}

static int tele_mntn_node_release(struct inode * inode, struct file * file)
{
    /*printk(KERN_ERR"tele_mntn_node_release\n");*/
    /*tele_mntn_func_sw_bit_clr(TELE_MNTN_NVME_WAKEUP_ACPU);*/
    /*tele_mntn_func_sw_bit_clr(TELE_MNTN_NVME_LOGCAT);*/
	return 0;
}
static ssize_t tele_mntn_node_read(struct file *file, char __user *buf,
			 size_t count, loff_t *ppos)
{
    struct tele_mntn_queue log_queue = {0};
    int ret = 0;
    unsigned int size_read = 0;
    /*8 bytes align*/
    unsigned int need_read = TELE_MNTN_SHORTCUT_ALIGN(count, TELE_MNTN_ALIGN_SIZE);

    /*printk(KERN_INFO"need_read: %d;\n", need_read);*/

    if ((need_read == 0) || (!buf)) {
        return 0;
    }
        /* now count > 0 */
    down(&rw_sem);

	ret = wait_event_interruptible_timeout(node_read_wait,
	    TELE_MNTN_NODE_READ_WAIT_CONDITION_FALSE == node_read_wait_condition,
		node_read_wait_timeout);
	if(ret < 0)
	{
		goto copy_error;
	}
	/*printk(KERN_ERR"tele_mntn_node_read, wait_timeout, ret=%d, node_read_wait_condition=%d, node_read_wait_timeout=%d \n", ret, node_read_wait_condition, node_read_wait_timeout);*/
	node_read_wait_condition = TELE_MNTN_NODE_READ_WAIT_CONDITION_TRUE;

    if((ret = tele_mntn_get_head(&log_queue)) != 0)
    {
        goto copy_error;
    }

/*
    if(log_queue.front == log_queue.rear)
    {
        up(&rw_sem);
        return 0;
    }
*/
    size_read = (log_queue.front >= log_queue.rear)?(log_queue.front-log_queue.rear):(log_queue.base + log_queue.length - log_queue.rear);
    size_read = size_read <= need_read ? size_read:need_read;

    /*printk(KERN_ERR" base=%x, len=%d, front=%x, rear=%x, size_read=%d, need_read=%d\n",log_queue.base, log_queue.length, log_queue.front,log_queue.rear, size_read, need_read);*/


    if(size_read)
    {
        if ((ret = copy_to_user(buf, log_queue.rear, size_read)) != 0) {
            goto copy_error;
        }

        log_queue.rear += size_read;

        if(log_queue.rear >= log_queue.base + log_queue.length)
        {
            log_queue.rear -= log_queue.length;
        }

        tele_mntn_set_head(&log_queue);
    }
    up(&rw_sem);
    /*printk(KERN_INFO"%d read, return", size_read);*/
	return size_read;

copy_error:
    up(&rw_sem);
    /*printk(KERN_ERR"return %d, some error happen!!!\n", ret);*/
    return -EIO;
}

static const struct file_operations proc_tele_mntn_node_operations = {
	.read		= tele_mntn_node_read,
	.open		= tele_mntn_node_open,
	.release	= tele_mntn_node_release,
};
/*sys_class_telemntnsw_dev_onoff*/
/*
static ssize_t tele_mntn_sw_show(struct device *_dev,
              struct device_attribute *attr, char *buf)
{
    unsigned long long sw_value = 0;
    unsigned int tmp_low = 0;
    unsigned int tmp_high = 0;

    sw_value = tele_mntn_func_sw_get();

    tmp_low = (unsigned int)(sw_value & (unsigned int)0xFFFFFFFF);

    tmp_high = (unsigned int)((sw_value >> 32) & (unsigned int)0xFFFFFFFF);

    return sprintf(buf, "0x%08x%08x\n", tmp_high, tmp_low);
}


static ssize_t tele_mntn_sw_on_store(struct device *_dev,
                 struct device_attribute *attr,
                 const char *buf, size_t count)
{
    unsigned int sw_bit = 0;
    sscanf(buf, "%u", &sw_bit);
    if(sw_bit < 64)
    {
        tele_mntn_func_sw_bit_set(sw_bit);
    }
    return count;
}

static ssize_t tele_mntn_sw_off_store(struct device *_dev,
                 struct device_attribute *attr,
                 const char *buf, size_t count)
{
    unsigned int sw_bit = 0;
    sscanf(buf, "%u", &sw_bit);
    if(sw_bit < 64)
    {
        tele_mntn_func_sw_bit_clr(sw_bit);
    }
    return count;
}
static DEVICE_ATTR(on, (S_IRUGO|S_IWUSR), tele_mntn_sw_show, tele_mntn_sw_on_store);
static DEVICE_ATTR(off, (S_IRUGO|S_IWUSR), tele_mntn_sw_show, tele_mntn_sw_off_store);


static struct attribute *tele_mntn_sw_attrs[] = {
	&dev_attr_on.attr,
	&dev_attr_off.attr,
	NULL,
};

static struct attribute_group tele_mntn_sw_attribute_group = {
	.attrs = tele_mntn_sw_attrs,
};

static struct class *tele_mntn_sw_dev_class = NULL;

static int tele_mntn_sw_dev_create(void)
{
    struct device *dev_t;
    int ret = 0;

    tele_mntn_sw_dev_class = class_create(THIS_MODULE, "telemntnsw");
    if (IS_ERR(tele_mntn_sw_dev_class))
    {
        printk("tele_mntn_sw_dev_create: exc class create fail\n");
        return -1;
    }

    dev_t = device_create(tele_mntn_sw_dev_class, NULL, MKDEV(0, 0),
                NULL, "dev");
    if (IS_ERR(dev_t))
    {
        printk("tele_mntn_sw_dev_create: exc device create fail\n");
        return -1;
    }

    ret = sysfs_create_group(&dev_t->kobj, &tele_mntn_sw_attribute_group);
    if (ret)
    {
        printk("tele_mntn_sw_dev_create: exc group create fail\n");
        return -1;
    }
    return 0;
}
*/

static ssize_t tele_mntn_sw_show(struct file *filp,  char  __user *buffer, size_t count, loff_t *ppos)
{
    int len = 0;
    char buf[32];
    unsigned long long sw_value = 0;
    unsigned int tmp_low = 0;
    unsigned int tmp_high = 0;
    memset(buf, 0, sizeof(buf));
    sw_value = tele_mntn_func_sw_get();

    tmp_low = (unsigned int)(sw_value & (unsigned int)0xFFFFFFFF);

    tmp_high = (unsigned int)((sw_value >> 32) & (unsigned int)0xFFFFFFFF);

    len = snprintf(buf, 32, "0x%08x%08x\n", tmp_high, tmp_low);
    if(len < count)
    {
        return simple_read_from_buffer(buffer, count, ppos, (void *)buf, len);
    }
    else
    {
        return 0;
    }
}


static ssize_t tele_mntn_sw_on_store(struct file *filp,  const char  __user *buffer, size_t count, loff_t *ppos)
{
    char buf[32] = {0};
    unsigned int sw_bit = 0;
    if(count >= sizeof(buf))
    {
        printk(KERN_ERR"tele_mntn_sw_on_store: input count larger than buf size \n");
        return (-ENOMEM);
    }
    if (copy_from_user(buf,buffer, count))
    {
        printk(KERN_ERR"tele_mntn_sw_on_store: copy_from_user from fm is err \n");
        return (-EFAULT);
    }
	if (1 != sscanf(buf, "%u", &sw_bit))
		return (-EDOM);

    if(sw_bit < 64)
    {
        tele_mntn_func_sw_bit_set(sw_bit);
    }
    else if(sw_bit == 64)
    {
        tele_mntn_func_sw_set(~((unsigned long long)0));
    }

    if(TELE_MNTN_NVME_LOGCAT == sw_bit)
    {
        node_read_wait_condition = TELE_MNTN_NODE_READ_WAIT_CONDITION_FALSE;
        node_read_wait_timeout = TELE_MNTN_NODE_READ_WAIT_TIMEOUT;
        wake_up_interruptible(&node_read_wait);
    }
    return count;
}

static ssize_t tele_mntn_sw_off_store(struct file *filp,  const char  __user *buffer, size_t count, loff_t *ppos)
{
    char buf[32] = {0};
    unsigned int sw_bit = 0;
    if(count >= sizeof(buf))
    {
        printk(KERN_ERR"tele_mntn_sw_off_store: input count larger than buf size \n");
        return (-ENOMEM);
    }
    if (copy_from_user(buf,buffer, count))
    {
        printk(KERN_ERR"tele_mntn_sw_off_store: copy_from_user from fm is err \n");
        return (-EFAULT);
    }
	if ( 1 != sscanf(buf, "%u", &sw_bit))
		return (-EDOM);

    if(sw_bit < 64)
    {
        tele_mntn_func_sw_bit_clr(sw_bit);
    }
    else if(sw_bit == 64)
    {
        tele_mntn_func_sw_set(0);
    }

    if(TELE_MNTN_NVME_LOGCAT == sw_bit)
    {
        node_read_wait_condition = TELE_MNTN_NODE_READ_WAIT_CONDITION_TRUE;
        node_read_wait_timeout = TELE_MNTN_NODE_READ_WAIT_FOREVER;
    }
    return count;
}
static int tele_mntn_dump_show(struct seq_file *s, void *unused)
{
    int idex = 0;
    if(!p_lpmcu_tele_mntn)
	{
		SPRINT_LPMCU_LOG(s, "ERR: M3_RDR_SYS_CONTEXT_BASE_ADDR is null\n");
		return 0;
	}
    /*发送中断给m3，更新rdr数据*/
#if defined(CONFIG_HISI_LPMCU_BB)
    (void)rdr_lpm3_stat_dump();
#endif

    SPRINT_LPMCU_LOG(s, "ccore:\n\t sleepCount %d\n\t wakeCount %d\n\t wakeSrc 0x%x\n\t pdSliceTime 0x%x\n\t puSliceTime 0x%x\n", \
                        p_lpmcu_tele_mntn->ccore.pdStat.sleepCount, \
                        p_lpmcu_tele_mntn->ccore.puStat.wakeCount, \
                        p_lpmcu_tele_mntn->ccore.puStat.wakeSrc, \
                        p_lpmcu_tele_mntn->ccore.pdSliceTime, \
                        p_lpmcu_tele_mntn->ccore.puSliceTime \
                    );


    SPRINT_LPMCU_LOG(s, "acore:\n\t sleepCount %d\n\t wakeCount %d\n\t wakeSrc 0x%x\n\t pdSliceTime 0x%x\n\t puSliceTime 0x%x\n", \
                        p_lpmcu_tele_mntn->acore.pdStat.sleepCount, \
                        p_lpmcu_tele_mntn->acore.puStat.wakeCount, \
                        p_lpmcu_tele_mntn->acore.puStat.wakeSrc, \
                        p_lpmcu_tele_mntn->acore.pdSliceTime, \
                        p_lpmcu_tele_mntn->acore.puSliceTime \
                    );


    SPRINT_LPMCU_LOG(s, "mcu_deepSleep:\n\t sleepCount %d\n\t wakeCount %d\n\t sleepSliceTime 0x%x\n\t wakeSliceTime 0x%x\n\t wakeSrc0 0x%x\n\t wakeSrc1 0x%x\n\t canSleepRet 0x%x\n", \
                        p_lpmcu_tele_mntn->mcu.info.stat.sleepCount, \
                        p_lpmcu_tele_mntn->mcu.info.stat.wakeCount, \
                        p_lpmcu_tele_mntn->mcu.info.stat.sleepSliceTime, \
                        p_lpmcu_tele_mntn->mcu.info.stat.wakeSliceTime, \
                        p_lpmcu_tele_mntn->mcu.info.stat.wakeSrc0, \
                        p_lpmcu_tele_mntn->mcu.info.stat.wakeSrc1, \
                        p_lpmcu_tele_mntn->mcu.info.notSleepReason.canSleepRet \
                    );


    SPRINT_LPMCU_LOG(s, "ddr_target:\n\t old_freq %d\n\t new_freq %d\n\t tag_freq %d\n\t targetSliceTime 0x%x\n", \
                        p_lpmcu_tele_mntn->dfsDdr.target.info.old_freq, \
                        p_lpmcu_tele_mntn->dfsDdr.target.info.new_freq, \
                        p_lpmcu_tele_mntn->dfsDdr.target.info.tag_freq, \
                        p_lpmcu_tele_mntn->dfsDdr.target.targetSliceTime \
                    );

    for(idex = 0; idex < PERI_SLEEP_CUR_STATE_NUM; idex++)
    {
        SPRINT_LPMCU_LOG(s, "lpmcu_vote[%d]:\n\t stat %d\t clientId %d\t stateId %d\t voteMap %d\t sliceTime 0x%x\n", \
                            idex, \
                            p_lpmcu_tele_mntn->vote[idex].voteStat.stat, \
                            p_lpmcu_tele_mntn->vote[idex].voteStat.clientId, \
                            p_lpmcu_tele_mntn->vote[idex].voteStat.stateId, \
                            p_lpmcu_tele_mntn->vote[idex].voteStat.voteMap,\
                            p_lpmcu_tele_mntn->vote[idex].sliceTime \
                        );
    }

    if (p_lpmcu_tele_mntn->iomcu.pu.up_cnt > p_lpmcu_tele_mntn->iomcu.pd.dn_cnt) {
        SPRINT_LPMCU_LOG(s, "iomcu state: 0x%x\n\t subsys vote 0x%x(ap:%d m7:%d)\n\t m7 reset count %d\n\t m7 current state %s\n" , \
                            p_lpmcu_tele_mntn->iomcu.pu.state, \
                            (p_lpmcu_tele_mntn->iomcu.pu.state >> 8) & 0xFF, \
                            (p_lpmcu_tele_mntn->iomcu.pu.state >> 8) & 0x1, \
                            (p_lpmcu_tele_mntn->iomcu.pu.state >> 9) & 0x1, \
                            p_lpmcu_tele_mntn->iomcu.pu.state & 0xFF, \
                            ((p_lpmcu_tele_mntn->iomcu.pu.state >> 16) & 0x1) ? "on" : "off" \
                        );
    } else {
        SPRINT_LPMCU_LOG(s, "iomcu state: 0x%x\n\t subsys vote 0x%x(ap:%d m7:%d)\n\t m7 reset count %d\n\t m7 current state %s\n" , \
                            p_lpmcu_tele_mntn->iomcu.pd.state, \
                            (p_lpmcu_tele_mntn->iomcu.pd.state >> 8) & 0xFF, \
                            (p_lpmcu_tele_mntn->iomcu.pd.state >> 8) & 0x1, \
                            (p_lpmcu_tele_mntn->iomcu.pd.state >> 9) & 0x1, \
                            p_lpmcu_tele_mntn->iomcu.pd.state & 0xFF, \
                            ((p_lpmcu_tele_mntn->iomcu.pd.state >> 16) & 0x1) ? "on" : "off" \
                        );
    }
    SPRINT_LPMCU_LOG(s, "\t powered on count %d\n\t powered off count %d\n\t waked irq %d\n\t\t waked mailbox %d\n\t\t waked type %s\n\t\t mailbox data0 0x%x\n" , \
                        p_lpmcu_tele_mntn->iomcu.pu.up_cnt, \
                        p_lpmcu_tele_mntn->iomcu.pd.dn_cnt, \
                        p_lpmcu_tele_mntn->iomcu.pu.wake_irq, \
                        p_lpmcu_tele_mntn->iomcu.pu.wake_mbx_id, \
                        (p_lpmcu_tele_mntn->iomcu.pu.wake_mbx_mode & 0x40) ? "receive irq" : "ack irq", \
                        p_lpmcu_tele_mntn->iomcu.pu.wake_mbx_data0 \
                    );

    if (p_lpmcu_tele_mntn->hifi.pu.up_cnt > p_lpmcu_tele_mntn->hifi.pd.dn_cnt) {
        SPRINT_LPMCU_LOG(s, "asp state: 0x%x\n\t subsys vote 0x%x(ap:%d hifi:%d)\n\t hifi reset count %d\n\t hifi current state %s\n" , \
                            p_lpmcu_tele_mntn->hifi.pu.state, \
                            (p_lpmcu_tele_mntn->hifi.pu.state >> 8) & 0xFF, \
                            (p_lpmcu_tele_mntn->hifi.pu.state >> 8) & 0x1, \
                            (p_lpmcu_tele_mntn->hifi.pu.state >> 9) & 0x1, \
                            p_lpmcu_tele_mntn->hifi.pu.state & 0xFF, \
                            ((p_lpmcu_tele_mntn->hifi.pu.state >> 16) & 0x1) ? "on" : "off" \
                        );
    } else {
        SPRINT_LPMCU_LOG(s, "asp state: 0x%x\n\t subsys vote 0x%x(ap:%d hifi:%d)\n\t hifi reset count %d\n\t hifi current state %s\n" , \
                            p_lpmcu_tele_mntn->hifi.pd.state, \
                            (p_lpmcu_tele_mntn->hifi.pd.state >> 8) & 0xFF, \
                            (p_lpmcu_tele_mntn->hifi.pd.state >> 8) & 0x1, \
                            (p_lpmcu_tele_mntn->hifi.pd.state >> 9) & 0x1, \
                            p_lpmcu_tele_mntn->hifi.pd.state & 0xFF, \
                            ((p_lpmcu_tele_mntn->hifi.pd.state >> 16) & 0x1) ? "on" : "off" \
                        );
    }

    SPRINT_LPMCU_LOG(s, "\t powered on count %d\n\t powered off count %d\n\t waked irq %d\n\t\t waked mailbox %d\n\t\t waked type %s\n\t\t mailbox data0 0x%x\n" , \
                        p_lpmcu_tele_mntn->hifi.pu.up_cnt, \
                        p_lpmcu_tele_mntn->hifi.pd.dn_cnt, \
                        p_lpmcu_tele_mntn->hifi.pu.wake_irq, \
                        p_lpmcu_tele_mntn->hifi.pu.wake_mbx_id, \
                        (p_lpmcu_tele_mntn->hifi.pu.wake_mbx_mode & 0x40) ? "receive irq" : "ack irq", \
                        p_lpmcu_tele_mntn->hifi.pu.wake_mbx_data0 \
                    );

        return 0;
}

static int tele_mntn_dump_open(struct inode *inode, struct file *file)
{
	return single_open(file, tele_mntn_dump_show, &inode->i_private);
}

static const struct file_operations tele_mntn_sw_on_fops = {
        .read = tele_mntn_sw_show,
        .write = tele_mntn_sw_on_store,
};

static const struct file_operations tele_mntn_sw_off_fops = {
        .read = tele_mntn_sw_show,
        .write = tele_mntn_sw_off_store,
};

static const struct file_operations tele_mntn_dump_fops = {
	.owner	    = THIS_MODULE,
	.open	    = tele_mntn_dump_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int tele_mntn_node_debugfs_create(void)
{
    struct dentry *debugfs_root;

    debugfs_root = debugfs_create_dir("telemntnsw", NULL);
    if ((!debugfs_root) || IS_ERR(debugfs_root))
        return (-ENOENT);

    (void)debugfs_create_file("on", (S_IRUSR | S_IRGRP | S_IWUSR), debugfs_root, NULL, &tele_mntn_sw_on_fops);

    (void)debugfs_create_file("off", (S_IRUSR | S_IRGRP | S_IWUSR), debugfs_root, NULL, &tele_mntn_sw_off_fops);

    (void)debugfs_create_file("dump", (S_IRUSR | S_IRGRP | S_IWUSR), debugfs_root, NULL, &tele_mntn_dump_fops);

    return 0;
}
static int tele_mntn_wake_up_acore_irq(struct notifier_block *nb, unsigned long len, void *msg)
{
	unsigned int *_msg = (unsigned int *)msg;
    if (_msg[0] == TELE_MNTN_WAKE_UP_ACORE_IPC_CMD)
    {
        node_read_wait_condition = TELE_MNTN_NODE_READ_WAIT_CONDITION_FALSE;
		/*=============test===========*/
        printk(KERN_ERR "tele_mntn_wake_up_acore_irq:  receive irq\n");
		/*=============test===========*/
    }
	return 0;
}

static int __init proc_tele_mntn_node_init(void)
{
	int err = 0;
    tele_mntn_init();
	if(TELE_MNTN_OK == tele_mntn_is_func_on(TELE_MNTN_NVME_LOGCAT))
	{
        node_read_wait_timeout = TELE_MNTN_NODE_READ_WAIT_TIMEOUT;
    }
    else
    {
        node_read_wait_timeout = TELE_MNTN_NODE_READ_WAIT_FOREVER;
    }
    sema_init(&rw_sem, 1);
    proc_create("telemntn", (S_IRUSR | S_IRGRP), NULL, &proc_tele_mntn_node_operations);

    /*sys_class_telemntnsw_dev_onoff*/
    /*tele_mntn_sw_dev_create();*/

    tele_mntn_node_debugfs_create();

	tele_mntn_ipc_msg_nb.next = NULL;
	tele_mntn_ipc_msg_nb.notifier_call = tele_mntn_wake_up_acore_irq;
	err = RPROC_MONITOR_REGISTER(HISI_RPROC_LPM3_MBX0, &tele_mntn_ipc_msg_nb);
	if (err)
		return err;

    pr_info("proc_tele_mntn_node_init success\n");
    return 0;

}

module_init(proc_tele_mntn_node_init);

/*=============test===========*/
/*
unsigned int test_telemntn_buf[20] = {0};
void test_tele_mntn(unsigned int type_id, unsigned int len, unsigned int data)
{
    unsigned int i= 0;

    memset(test_telemntn_buf, 0, sizeof(test_telemntn_buf));
    for(i = 0; i < len; ++i)
    {
        test_telemntn_buf[i] = data;
    }
    tele_mntn_write_log(type_id, len*4, test_telemntn_buf);
}
*/
/*=============test===========*/
