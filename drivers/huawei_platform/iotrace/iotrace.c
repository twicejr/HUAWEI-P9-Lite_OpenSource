
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/blkdev.h>
#include <linux/percpu.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/export.h>
#include <linux/time.h>
#include <linux/writeback.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/task_io_accounting_ops.h>

#include <trace/iotrace.h>

typedef u32 block_t;
typedef u32 nid_t;

#include <trace/events/f2fs.h>
/* data type for block offset of block group */
typedef int ext4_grpblk_t;
/* data type for filesystem-wide blocks number */
typedef unsigned long long ext4_fsblk_t;
/* data type for file logical block number */
typedef __u32 ext4_lblk_t;
/* data type for block group number */
typedef unsigned int ext4_group_t;
#include <trace/events/ext4.h>
#include <trace/events/block.h>
#include <trace/events/mmc.h>

/********************************************************************/

#define io_trace_print(fmt, arg...) printk("[[IO_TRACE] %s:%d]"fmt, __FUNCTION__, __LINE__, ##arg)
#define io_trace_assert(cond) \
{   \
    if(!(cond)) \
    { \
        io_trace_print("[IO_TRACE] %s\n", #cond); \
    }\
}

enum IO_TRACE_ACTION
{
    READ_BEGIN_TAG = 0x1,
    WRITE_BEGIN_TAG,
    EXT4_DA_WRITE_BEGIN_TAG,
    BLOCK_WRITE_BEGIN_TAG,
    EXT4_SYNC_ENTER_TAG,
    F2FS_SYNC_ENTER_TAG,
    /*FIXME: according it alloc pid log entry*/
    IO_TRACE_PARENT_END = F2FS_SYNC_ENTER_TAG,

    READ_END_TAG,
    BLOCK_WRITE_END_TAG,
    EXT4_DA_WRITE_END_TAG,
    WRITE_END_TAG,
    WRITE_WAIT_END_TAG, /*in sync file*/
    EXT4_SYNC_EXIT_TAG,
    F2FS_SYNC_EXIT_TAG,

    IO_TRACE_JANK_TAG = F2FS_SYNC_EXIT_TAG,
    EXT4_MAP_SUBMIT_TAG,

    EXT4_WRITE_PAGES_TAG,
    EXT4_WRITE_PAGE_TAG,
    EXT4_WRITE_PAGES_END_TAG, 

    F2FS_SYNC_FS_TAG,
    F2FS_WRITE_CP_TAG,

    BLOCK_BIO_DM_TAG,
    BLOCK_BIO_CRYPT_MAP,
    BLOCK_DM_CRYPT_TAG,
    BLOCK_DM_CRYPT_DEC_TAG,

    BLOCK_BIO_REMAP_TAG,
    BLOCK_BIO_QUEUE_TAG,
    BLOCK_BIO_BACKMERGE_TAG,
    BLOCK_BIO_FRONTMERGE_TAG,
    BLOCK_GETRQ_TAG,
    BLOCK_SLEEPRQ_TAG,
    BLOCK_RQ_INSERT_TAG,
    BLOCK_RQ_ISSUE_TAG,
    BLOCK_RQ_COMPLETE_TAG,
    BLOCK_EXT4_END_BIO_TAG,
    MMC_BLK_ISSUE_RQ_TAG,
    MMC_BLK_RW_START_TAG,
    MMC_BLK_RW_END_TAG,

    MMC_BLK_CMDQ_RW_START_TAG,
    MMC_BLK_CMDQ_RW_END_TAG,

    IO_TRACE_TAG_END,
};

struct io_trace_action
{
    unsigned int action;
    unsigned char *name;
};

static struct io_trace_action all_trace_action[] = { 
    {0, "0"},
    {READ_BEGIN_TAG,"r_begin"},
    {WRITE_BEGIN_TAG, "w_begin"},
    {EXT4_DA_WRITE_BEGIN_TAG, "e4_w_begin"},
    {BLOCK_WRITE_BEGIN_TAG, "b_w_begin"},
    {EXT4_SYNC_ENTER_TAG, "e4_sy_begin"},
    {F2FS_SYNC_ENTER_TAG, "f2fs_sy_begin"},

    {READ_END_TAG,"r_end"},
    {BLOCK_WRITE_END_TAG, "b_w_end"},
    {EXT4_DA_WRITE_END_TAG, "e4_w_end"},
    {WRITE_END_TAG, "w_end"},
    {WRITE_WAIT_END_TAG, "w_w_end"},
    {EXT4_SYNC_EXIT_TAG, "e4_sy_end"},
    {F2FS_SYNC_EXIT_TAG, "f2fs_sy_end"},

    {EXT4_MAP_SUBMIT_TAG, "e4_map_blk"},

    {EXT4_WRITE_PAGES_TAG, "e4_w_pages"},
    {EXT4_WRITE_PAGE_TAG, "e4_w_page"},
    {EXT4_WRITE_PAGES_END_TAG, "e4_w_pages_e"},

    {F2FS_SYNC_FS_TAG, "f2fs_sync_fs"},
    {F2FS_WRITE_CP_TAG, "f2fs_w_cp"},

    {BLOCK_BIO_DM_TAG, "b_b_dm"},
    {BLOCK_BIO_CRYPT_MAP, "b_crypt_map"},
    {BLOCK_DM_CRYPT_TAG, "b_crypt_s"},
    {BLOCK_DM_CRYPT_DEC_TAG, "b_crypt_e"},

    {BLOCK_BIO_REMAP_TAG, "b_b_remap"},
    {BLOCK_BIO_QUEUE_TAG, "b_b_queue"},
    {BLOCK_BIO_BACKMERGE_TAG, "b_b_back"},
    {BLOCK_BIO_FRONTMERGE_TAG, "b_b_front"},
    {BLOCK_GETRQ_TAG, "b_getq"},
    {BLOCK_SLEEPRQ_TAG, "b_slq"},
    {BLOCK_RQ_INSERT_TAG, "b_q_insert"},
    {BLOCK_RQ_ISSUE_TAG, "b_q_issue"},
    {BLOCK_RQ_COMPLETE_TAG, "b_q_comp"},
    {BLOCK_EXT4_END_BIO_TAG, "b_i_comp"},
    {MMC_BLK_ISSUE_RQ_TAG, "mmc_issue"},
    {MMC_BLK_RW_START_TAG, "mmc_start"},
    {MMC_BLK_RW_END_TAG, "mmc_end"},

    {MMC_BLK_CMDQ_RW_START_TAG, "mmc_cmdq_s"},
    {MMC_BLK_CMDQ_RW_END_TAG, "mmc_cmdq_e"},
};

static inline int action_is_read(unsigned char action)
{
    if(action == READ_END_TAG ||
            action == READ_BEGIN_TAG)    
    {
        return 1;
    }

    return 0;
}

static inline int action_is_write(unsigned char action)
{
    if(action == WRITE_END_TAG ||
            action == EXT4_SYNC_EXIT_TAG ||
                action == WRITE_BEGIN_TAG ||
                    action == EXT4_SYNC_ENTER_TAG)
    {
        return 1;
    }

    return 0;
}

enum IO_TRACE_TYPE
{
    __IO_TRACE_WRITE,

    __IO_TRACE_SYNC = 4,
	__IO_TRACE_META,		/* metadata io request */
	__IO_TRACE_PRIO,		/* boost priority in cfq */
	__IO_TRACE_DISCARD,		/* request to discard sectors */
};

#define IO_TRACE_READ   (0)
#define IO_TRACE_WRITE  (1 << __IO_TRACE_WRITE)
#define IO_TRACE_SYNC   (1 << __IO_TRACE_SYNC)
#define IO_TRACE_META   (1 << __IO_TRACE_META)
#define IO_TRACE_DISCARD (1 << __IO_TRACE_DISCARD)
unsigned char *rw_name[] = {"R", "W", "N", "N", "S", "M", "P", "D"};

#define IO_F_NAME_LEN  (32)
#define IO_P_NAME_LEN  (16)
struct io_trace_log_entry
{
    pid_t pid;
    pid_t tgid;
    unsigned char action;
    unsigned char rw;
    unsigned char cpu;
    unsigned char valid; /*whether it is running*/
    unsigned int  nr_bytes;
    unsigned long inode;
    unsigned long time;
    unsigned long delay;
    char comm[IO_P_NAME_LEN];
    char f_name[IO_F_NAME_LEN];
};

#define IO_MAX_PROCESS  (32768)
#define IO_RUNNING_MAX_PROCESS  (32)

#define IO_MAX_BUF_ENTRY    (4 * 1024)

#define IO_MAX_GLOBAL_ENTRY (4 * 1024 * 1024)
#define IO_MAX_OUTPUT_ENTRY (4 * 1024)

#define IO_MAX_OP_LOG_PER_BUF ((IO_MAX_BUF_ENTRY) / sizeof(struct io_trace_output_entry))
#define IO_MAX_LOG_PER_BUF ((IO_MAX_BUF_ENTRY) / sizeof(struct io_trace_log_entry))
#define IO_MAX_LOG_PER_GLOBAL \
    (((IO_MAX_GLOBAL_ENTRY) / sizeof(struct io_trace_log_entry)) - 1)

#define IO_TRACE_LIMIT_LOG  (50000000)
#define io_ns_to_ms(ns) ((ns) / 1000000)

struct io_trace_pid
{
    pid_t pid;
    unsigned short running;   /*pid already begin trace??*/
    unsigned long  log_count;
    struct io_trace_log_entry pid_entry[IO_TRACE_PARENT_END + 1];
};

struct io_trace_mem_mngt 
{
    int index;    
    unsigned char *buff[IO_RUNNING_MAX_PROCESS];
    unsigned char *all_trace_buff;
};

struct io_trace_ctrl
{
    struct platform_device *pdev;
    unsigned int enable;
    unsigned int first;

    unsigned int   all_log_index;
    unsigned int   all_log_count; /*not more than IO_MAX_LOG_PER_GLOBAL */

    unsigned int   out_log_index;
    unsigned int   out_log_count;
    unsigned int   out_valid;
    unsigned int   out_test;

    struct file *filp;

    struct io_trace_pid *all_trace[IO_MAX_PROCESS];
    struct io_trace_mem_mngt *mem_mngt;
};

static struct io_trace_ctrl *io_trace_this = NULL;
static DEFINE_RAW_SPINLOCK(trace_buff_spinlock);
static spinlock_t global_spinlock;
static struct mutex output_mutex;

static int trace_mm_init(struct io_trace_ctrl *trace_ctrl);
static void io_trace_setup(struct io_trace_ctrl *trace_ctrl);

static void io_trace_offline(struct io_trace_ctrl *trace_ctrl);
static unsigned char *io_mem_mngt_alloc(struct io_trace_mem_mngt *mem_mngt);
static void io_mem_mngt_free(struct io_trace_mem_mngt *mem_mngt, unsigned char *buf);

static ssize_t sysfs_io_trace_attr_show(struct device *dev, struct device_attribute *attr,
        char *buf);
static ssize_t sysfs_io_trace_attr_store(struct device *dev, struct device_attribute *attr,
        const char *buf, size_t count);

static ssize_t io_log_data_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t io_log_data_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);

static ssize_t io_log_stat_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t io_log_stat_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);

static struct file * open_log_file(char *name);
static int write_log_kernel(struct file *filp, struct io_trace_log_entry *entry);
static int write_head_kernel(struct file *filp);

#define IO_TRACE_DEVICE_ATTR(_name) \
    DEVICE_ATTR(_name, S_IRUGO | S_IWUSR, \
    sysfs_io_trace_attr_show, \
    sysfs_io_trace_attr_store)

static IO_TRACE_DEVICE_ATTR(enable);
static IO_TRACE_DEVICE_ATTR(pid);

static struct kobj_attribute io_log_data_attr = {
    .attr = {.name = "io_data", .mode= 0660},
    .show = io_log_data_show,
    .store = io_log_data_store
};

static struct kobj_attribute io_log_stat_attr = {
    .attr = {.name = "io_stat", .mode= 0660},
    .show = io_log_stat_show,
    .store = io_log_stat_store
};

static struct attribute *io_trace_attrs[] = {
    &dev_attr_enable.attr,
    //&dev_attr_pid.attr,
    &io_log_data_attr.attr,
    NULL,
};
struct attribute_group io_trace_attr_group = { 
    .name  = "iotrace",
    .attrs = io_trace_attrs,
};

struct io_trace_output_entry
{
    unsigned short rw;
    unsigned short action;
    pid_t pid;
    unsigned int  delay;
    unsigned long inode;
    unsigned long time_stamp;
    char comm[IO_P_NAME_LEN];
};

struct io_trace_output_head
{
    unsigned char version[4];
    unsigned int data_len;
    unsigned int r_max_delay;
    unsigned int r_aver_delay;
    unsigned int r_total_delay;
    unsigned int w_max_delay;
    unsigned int w_aver_delay;
    unsigned int w_total_delay;
};

struct io_stat_output_entry
{
    pid_t pid;
    int   stat_ret;
    unsigned long rchar; 
    unsigned long wchar;
    unsigned long syscr;
    unsigned long syscw;
    unsigned long read_bytes;
    unsigned long write_bytes;
    unsigned long cancel_write_bytes;
};

static inline void io_trace_version(unsigned char *v)
{
    *(v) = 'V';
    *(v + 1) = '2';
    *(v + 2) = '0';
    *(v + 3) = '0';

    return;
}

struct io_trace_interface
{
    unsigned int  magic;
    unsigned int  circum;
    unsigned long time_stamp;
    unsigned long time_span;
    unsigned int  buff_len;
    unsigned int  pid_num;
    pid_t pid[0];
};

enum
{
    SYS_IO_DATA,
    SYS_IO_STAT,
    SYS_IO_NUM,
};

static struct io_trace_interface *my_itface;
static struct io_trace_interface *all_itface[SYS_IO_NUM] = {NULL, NULL};

static int io_copy_interface_data(struct io_trace_interface *in_itface, 
        struct io_trace_interface *out_itface)
{
    int i;
    int len = -1;

    in_itface->buff_len = out_itface->buff_len;
    in_itface->circum = out_itface->circum;
    in_itface->pid_num = out_itface->pid_num;
    in_itface->time_stamp = out_itface->time_stamp;
    in_itface->time_span = out_itface->time_span;

    if(in_itface->buff_len > IO_MAX_BUF_ENTRY)
    {
        io_trace_print("in_itface buff_len: %d\n", in_itface->buff_len);
        return len;
    }

    len = sizeof(struct io_trace_interface);

    if(in_itface->pid_num > 0)
    {
        for(i = 0; i < in_itface->pid_num; i++)
        {
            len += sizeof(pid_t);
            if(len >= IO_MAX_BUF_ENTRY)
            {
                io_trace_print("limit buffer, real pid num: %d\n", i);
                in_itface->pid_num = i;
		len = len - sizeof(pid_t);
                break;
            }
            in_itface->pid[i] = out_itface->pid[i];
            io_trace_print("recv pid[%d]: %d\n", i, in_itface->pid[i]);
        }
    }
    else
    {
        io_trace_print("print all the process!\n");
    }

    return len;
}

static int do_io_accounting(struct task_struct *task, struct io_stat_output_entry *buffer, int whole)
{
	struct task_io_accounting acct = task->ioac;
	unsigned long flags;
	int result = 0;
    struct io_stat_output_entry *entry = buffer;

	result = mutex_lock_killable(&task->signal->cred_guard_mutex);
	if (result)
    {
        io_trace_print("mutex lock killable failed!\n");
		return result;
    }
/*
	if (!ptrace_may_access(task, PTRACE_MODE_READ)) {
		result = -EACCES;
		goto out_unlock;
	}
*/
	task_io_accounting_add(&acct, &task->signal->ioac);
	if (whole && lock_task_sighand(task, &flags))
    {
		struct task_struct *t = task;
		while_each_thread(task, t)
			task_io_accounting_add(&acct, &t->ioac);

		unlock_task_sighand(task, &flags);
	}

    entry->rchar = acct.rchar;
    entry->wchar = acct.wchar;
    entry->syscr = acct.syscr;
    entry->syscw = acct.syscw;
    entry->read_bytes = acct.read_bytes;
    entry->write_bytes = acct.write_bytes;
    entry->cancel_write_bytes = acct.cancelled_write_bytes;

	mutex_unlock(&task->signal->cred_guard_mutex);

	return result;
}

static ssize_t io_log_stat_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer)
{
    int ret = 0;
    int i, pid_index = 0;
    struct io_trace_interface *itface = all_itface[SYS_IO_STAT];
    int out_count;
    struct io_stat_output_entry *entry = NULL;

    mutex_lock(&output_mutex);

    if(!itface)
    {
        io_trace_print("itface is NULL\n");
        goto end;
    }

    if(buffer == NULL)
    {
        io_trace_print("itface buff NULL\n");
        goto end;
    }

    if(itface->buff_len > 4096 || itface->pid_num == 0)
    {
        io_trace_print("itface buff_len[%d] or pid_num[%d] failed\n", itface->buff_len,
                itface->pid_num);
        goto end;
    }

    out_count = itface->buff_len / sizeof(struct io_stat_output_entry);
    pid_index = 0;

    for(i = 0; i < out_count; i++)
    {
        struct pid *pid = NULL;
        struct task_struct *task = NULL;
        pid_t stat_pid = itface->pid[pid_index];
        io_trace_print("Find Pid: %d\n", stat_pid);
        pid = find_get_pid(stat_pid);
        entry = ((struct io_stat_output_entry*)buffer) + i;
        entry->pid = stat_pid;
        entry->stat_ret = 0;
        if(pid)
        {
            task = get_pid_task(pid, PIDTYPE_PID);
            if(task)
            {
                int whole = thread_group_leader(task) ? 1 : 0;
                if(do_io_accounting(task, entry, whole) < 0)
                {
                    entry->stat_ret = -1;
                    io_trace_print("do io accounting failed!\n");
                }
                put_task_struct(task);
            }
	    put_pid(pid);
        }
        else
        {
            entry->stat_ret = -1;
            io_trace_print("Not Found Pid: %d\n", stat_pid);
        }
        pid_index ++;
        if(pid_index >= itface->pid_num)
        {
            break;
        }
        ret += sizeof(struct io_stat_output_entry);
    }

    io_trace_print("ret length: %d\n", ret);

end:
    if(itface)
    {
        io_mem_mngt_free(io_trace_this->mem_mngt, (unsigned char *)itface);
        all_itface[SYS_IO_STAT] = NULL;
    }
    mutex_unlock(&output_mutex);

    return ret;
}

static ssize_t io_log_stat_store(struct kobject *kobj, struct kobj_attribute *attr, 
        const char *buf, size_t count)
{
    struct io_trace_interface *out_itface = (struct io_trace_interface *)buf;
    struct io_trace_interface *io_stat_itface = all_itface[SYS_IO_STAT];

    mutex_lock(&output_mutex);

    if(out_itface->magic == 0x5D)
    {
        unsigned char *mem= io_mem_mngt_alloc(io_trace_this->mem_mngt);
        if(mem == NULL)
        {
            io_trace_print("mem alloc failed!\n");
            goto end;
        }
        io_stat_itface = (struct io_trace_interface *)mem;
        if(!io_copy_interface_data(io_stat_itface, out_itface))
        {
            io_trace_print("out pid_num:%d, buff_len:%d, time: %ld\n",
                    io_stat_itface->pid_num, io_stat_itface->buff_len, io_stat_itface->time_stamp);
        }

        all_itface[SYS_IO_STAT] = io_stat_itface;
    }
    else 
    {
        io_trace_print("io trace magic error: 0x%x\n", out_itface->magic);
    }

end:
    mutex_unlock(&output_mutex);

    return count;
}

static inline int io_log_allow_pid(unsigned int pid_num, pid_t *o_pid, pid_t pid)
{
    unsigned int i;
    if(pid_num == 0)
    {
        //io_trace_print("output all the process!\n");
        return 1;
    }
    for(i = 0; i < pid_num; i++)
    {
        if(o_pid[i] == pid)
        {
            return 1;
        }
    }

    return 0;
}

static inline int io_log_allow_time(unsigned long time, unsigned long o_time, unsigned long time_span)
{
    if(o_time == 0 || time_span == 0)
    {
        //io_trace_print("o_time is %lu or span %lu!\n", o_time, time_span);
        return 1;
    }

    if(o_time > io_ns_to_ms(time))
    {
        if((o_time - io_ns_to_ms(time)) < time_span)
        {
            return 1;
        }
        else
        {
            io_trace_print("time[%lu]ms o_time[%lu]ms, time_span[%lu]ms\n", 
                    io_ns_to_ms(time), o_time, time_span);
            return 0;
        }
    }
    else
    {
        return 2;
    }
    //io_trace_print("o_time[%lu] beginer than [%lu]\n", o_time, io_ns_to_ms(time));
}

static inline int io_log_allow_action(unsigned int action)
{
    /*only the vfs log*/
    if(action <= IO_TRACE_JANK_TAG)
    {
        return 1;
    }

    return 0;
}

static struct io_trace_log_entry *io_trace_find_log(struct io_trace_interface *itface,
        struct io_trace_ctrl *trace_ctrl)
{
    unsigned int index = trace_ctrl->out_log_index;
    struct io_trace_log_entry *entry = NULL;
    unsigned int find_flag = 0;
    unsigned int total_count = io_trace_this->all_log_count;
    int ret = 0;

    while(trace_ctrl->out_log_count < total_count)
    {
        trace_ctrl->out_log_count ++;
        entry = (((struct io_trace_log_entry *)(trace_ctrl->mem_mngt->all_trace_buff)) + 
                index);
        /*next find log index*/
        index = (index == 0) ? (total_count - 1) : (index - 1);
        ret = io_log_allow_time(entry->time, itface->time_stamp, itface->time_span);
        if(!ret)
        {
            io_trace_print("time stamp not allow, first index: %u, now index: %u\n",
                    io_trace_this->all_log_index, index);   
            io_trace_print("entry time: %ld, time_stamp:%ld, time_span: %ld\n",
                    io_ns_to_ms(entry->time), itface->time_stamp, itface->time_span);   
            return NULL;
        }

        if(ret == 2)
        {
            continue;
        }
        /*
        io_trace_print("find entry time: %ld, time_stamp:%ld, time_span: %ld\n",
                    io_ns_to_ms(entry->time), itface->time_stamp, itface->time_span);   

        */
        if(io_log_allow_pid(itface->pid_num, itface->pid, entry->tgid) &&
                io_log_allow_action(entry->action))
        {
            trace_ctrl->out_log_index = index;
            find_flag = 1;
            break;
        }
    }
    /*write file*/
    if(find_flag)
    {
        int ret;
        struct io_trace_log_entry *blk_entry = NULL;
        unsigned int file_log_count = trace_ctrl->out_log_count;
        unsigned int file_log_index = trace_ctrl->out_log_index;
        unsigned int happen = 0;

        ret = write_log_kernel(trace_ctrl->filp, entry);
        if(ret < 0)
        {
            io_trace_print("write log kernel failed![%d]\n", ret);
            return NULL;
        }

        while(file_log_count < total_count)
        {
            /*scan the request*/
            file_log_count ++;
            blk_entry = (((struct io_trace_log_entry *)(trace_ctrl->mem_mngt->all_trace_buff)) + 
                file_log_index);
            file_log_index = (file_log_index == 0) ? (total_count - 1) : (file_log_index - 1);
            /*happen the jank log index*/
            if(!happen)
            {
                trace_ctrl->out_log_index = file_log_index;
                trace_ctrl->out_log_count = file_log_count;
            }
            /*this is only one break*/
            if(blk_entry->time < (entry->time - entry->delay))
            {
                break;
            }

            if((io_log_allow_pid(itface->pid_num, itface->pid, entry->tgid) &&
                        io_log_allow_action(entry->action)))
            {
                happen = 1;
            }

            ret = write_log_kernel(trace_ctrl->filp, blk_entry);
            if(ret < 0)
            {
                io_trace_print("write log kernel failed![%d]\n", ret);
                return NULL;
            }
        }

        return entry;
    }

    io_trace_print("loop all the log: %d\n", trace_ctrl->out_log_count);

    return NULL;
}

static ssize_t io_log_data_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int i = 0, ret = -1;
    unsigned int out_count = 0;
    struct io_trace_interface *itface = my_itface;
    char file_name[48];
    unsigned int data_len = 0, head_len = 0;
    char *head_buf = NULL;
    unsigned int r_max_delay = 0, r_total_delay = 0;
    unsigned int w_max_delay = 0, w_total_delay = 0;
    unsigned int r_cnt = 0, w_cnt = 0;
    
    mutex_lock(&output_mutex);
    if(!io_trace_this->enable)
    {
        io_trace_print("io trace enable failed!\n");
        mutex_unlock(&output_mutex);
        return ret;
    }

    io_trace_this->enable = 0;

    if(!io_trace_this->out_valid)
    {
        io_trace_print("out valid error: %d\n", io_trace_this->out_valid);
        goto end;
    }

    if(!itface)
    {
        io_trace_print("itface is NULL\n");
        goto end;
    }

    if(buf == NULL)
    {
        io_trace_print("itface buff NULL\n");
        goto end;
    }
    if(itface->buff_len == 0 || itface->buff_len > 4096)
    {
        io_trace_print("itface buff_len error: %d\n", itface->buff_len);
        goto end;
    }

    sprintf(file_name, "/data/log/jank/iotrace/%s", "iotrace.txt");
    io_trace_this->filp = open_log_file(file_name);
    if(io_trace_this->filp == NULL)
    {
        io_trace_print("io_trace open file %s failed!\n", file_name);
        goto end;
    }

    if(write_head_kernel(io_trace_this->filp) < 0)
    {
        io_trace_print("write head kernel filed!\n");
        goto end;
    }
    /*end*/
    io_trace_print("itface pid_num: %u\n", itface->pid_num);
    io_trace_print("itface time_stamp: %ld\n", itface->time_stamp);
    io_trace_print("itface time span: %ld\n", itface->time_span);
    io_trace_print("itface buff len: %u\n", itface->buff_len);

    data_len = itface->buff_len;
    head_len = sizeof(struct io_trace_output_head); /*reserved how many bytes*/
    /*skip the head buffer*/
    head_buf = buf;
    data_len -= head_len;
    buf += head_len;
    /*return value*/
    ret = head_len;

    out_count = data_len / (sizeof(struct io_trace_output_entry));
    io_trace_this->out_log_index = (io_trace_this->all_log_index == 0) ? (io_trace_this->all_log_count - 1) :
        (io_trace_this->all_log_index - 1);
    io_trace_this->out_log_count = 0;

    for(i = 0; i < out_count; i++)
    {
        struct io_trace_output_entry *out_entry = NULL;
        struct io_trace_log_entry *log_entry;

        out_entry = ((struct io_trace_output_entry *)buf) + i;
        log_entry = io_trace_find_log(itface, io_trace_this);
        if(log_entry == NULL)
        {
            io_trace_print("no such log entry output!,ret:%d\n", ret);
            goto log_end;
        }
        out_entry->action = log_entry->action;
        //out_entry->pid = log_entry->pid;
        out_entry->pid = log_entry->tgid;
        out_entry->inode = log_entry->inode;
        out_entry->rw = log_entry->rw;
        out_entry->time_stamp = log_entry->time;
        out_entry->delay = io_ns_to_ms(log_entry->delay);
        memcpy(out_entry->comm, log_entry->comm, IO_P_NAME_LEN);

        if(action_is_read(log_entry->action))
        {
            r_max_delay = (r_max_delay >= log_entry->delay) ? r_max_delay :
                log_entry->delay;
            r_total_delay += log_entry->delay;
            r_cnt ++;
        }

        if(action_is_write(log_entry->action))
        {
            w_max_delay = (w_max_delay >= log_entry->delay) ? w_max_delay :
                log_entry->delay;
            w_total_delay += log_entry->delay;
            w_cnt ++;
        }

        ret += sizeof(struct io_trace_output_entry);
    }

log_end:
    if(head_buf)
    {
        struct io_trace_output_head *head = (struct io_trace_output_head *)head_buf;
        memset(head_buf, 0, sizeof(struct io_trace_output_head));
        io_trace_version(head->version);
        io_trace_print("r_cnt:%d, r_max_delay: %u, r_total_delay: %u\n", r_cnt, r_max_delay, r_total_delay);
        io_trace_print("w_cnt:%d, w_max_delay: %u, w_total_delay: %u\n", w_cnt, w_max_delay, w_total_delay);
        if(r_cnt > 0)
        {
            head->r_max_delay = io_ns_to_ms(r_max_delay);
            head->r_aver_delay = io_ns_to_ms(r_total_delay / r_cnt);
            head->r_total_delay = io_ns_to_ms(r_total_delay);
        }
        if(w_cnt > 0)
        {
            head->w_max_delay = io_ns_to_ms(w_max_delay);
            head->w_aver_delay = io_ns_to_ms(w_total_delay / w_cnt);
            head->w_total_delay =  io_ns_to_ms(w_total_delay);
        }
        /*used for data check*/
        head->data_len = (unsigned int)ret;
    }

end:
    io_trace_this->out_valid = 0;
    if(my_itface)
    {
        io_mem_mngt_free(io_trace_this->mem_mngt, (unsigned char *)my_itface);
        my_itface = NULL;
    }

    if(io_trace_this->filp)
    {
        filp_close(io_trace_this->filp, NULL);
    }

    io_trace_this->enable = 1;
    mutex_unlock(&output_mutex);

    return ret;
}

static ssize_t io_log_data_store(struct kobject *kobj, 
        struct kobj_attribute *attr, const char *buf, size_t count)
{

    struct io_trace_interface *out_itface = (struct io_trace_interface *)buf;
    int ret = -1;

    mutex_lock(&output_mutex);
    if(!io_trace_this->enable)
    {
        io_trace_print("io trace enable failed!\n");
        mutex_unlock(&output_mutex);
        return ret;
    }

    if(out_itface->magic == 0x5A)
    {
        unsigned char *mem= io_mem_mngt_alloc(io_trace_this->mem_mngt);
        if(mem == NULL)
        {
            io_trace_print("mem alloc failed!\n");
            goto end;
        }
        my_itface = (struct io_trace_interface *)mem;
        ret = io_copy_interface_data(my_itface, out_itface);
        if(ret < 0)
        {
            io_mem_mngt_free(io_trace_this->mem_mngt, mem);
            goto end;
        }
        io_trace_print("out pid_num:%d, buff_len:%d, time: %ld, time_span: %ld\n",
                my_itface->pid_num, my_itface->buff_len, my_itface->time_stamp,
                my_itface->time_span);

        io_trace_this->out_valid = 1;
    }
    else 
    {
        io_trace_print("io trace magic error: 0x%x\n", out_itface->magic);
    }

end:
    mutex_unlock(&output_mutex);

    return ret;
}

static ssize_t sysfs_io_trace_attr_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    ssize_t ret = 0;
    unsigned long log_time, log_time_end;

    if(attr == &dev_attr_enable)    
    {
        ret = sprintf(buf, "%d\n", io_trace_this->enable);
    }

    if(attr == &dev_attr_pid)
    {
        int i,j;
        struct io_trace_log_entry *entry;
        char file_name[128];
        struct timespec realts;

        do_posix_clock_monotonic_gettime(&realts);
        //monotonic_to_bootbased(&realts);
        log_time = (unsigned long )realts.tv_sec*1000000000 + realts.tv_nsec;

        io_trace_this->enable = 0;
        sprintf(file_name, "/sdcard/log_%s", "end");
        io_trace_this->filp = open_log_file(file_name);
        if(io_trace_this->filp == NULL)
        {
            io_trace_print("io_trace open file %s failed!\n", file_name);
            io_trace_this->enable = 1;
            return ret;
        }
        write_head_kernel(io_trace_this->filp);
        if(io_trace_this->all_log_count > 0)
        {
            unsigned int count = io_trace_this->all_log_count;

            for(i = io_trace_this->all_log_index, j = 0; j < count; j++)
            {
                i = (i == 0) ? (count - 1) : (i - 1);
                io_trace_assert(i >= 0);
                entry = (((struct io_trace_log_entry *)
                        (io_trace_this->mem_mngt->all_trace_buff)) + i);
                write_log_kernel(io_trace_this->filp, entry);
            }
        }

        do_posix_clock_monotonic_gettime(&realts);
        //monotonic_to_bootbased(&realts);
        log_time_end = (unsigned long )realts.tv_sec*1000000000 + realts.tv_nsec;

        ret = sprintf(buf, "%ld\n", log_time_end - log_time);

        io_trace_this->enable = 1;
    }

    return ret;
}

static ssize_t sysfs_io_trace_attr_store(struct device *dev, 
        struct device_attribute *attr, const char *buf, size_t count)
{
    unsigned int value;
    int ret = 0;

    if(attr == &dev_attr_enable)
    {
        mutex_lock(&output_mutex);
        sscanf(buf, "%u", &value);
        if(value == 1)
        {
            if((io_trace_this->first == 0))
            {
                ret = trace_mm_init(io_trace_this);
                if(ret < 0)
                {
                    io_trace_print("trace mm init failed!\n");
                    io_trace_this->enable = 0;
                    mutex_unlock(&output_mutex);
                    return count;
                }
                io_trace_setup(io_trace_this);
                io_trace_this->first = 1;
            }
            io_trace_this->enable = value;
        }
        if(value == 0)
        {
            io_trace_this->enable = value;
        }
        mutex_unlock(&output_mutex);
    }

    if(attr == &dev_attr_pid)
    {
        unsigned char *mem= io_mem_mngt_alloc(io_trace_this->mem_mngt);
        if(mem == NULL)
        {
            io_trace_print("mem alloc failed!\n");
            return count;
        }
        my_itface = (struct io_trace_interface *)mem;
        my_itface->buff_len = 4096;
        my_itface->circum = 0;
        my_itface->time_stamp = 0;
        my_itface->pid_num = 0;
        if(value)
        {
            my_itface->pid_num = 1;
            my_itface->pid[0] = value;
        }
        io_trace_print("out pid_num:%d, buff_len:%d, time: %ld\n",
                my_itface->pid_num, my_itface->buff_len, my_itface->time_stamp);
        io_trace_this->out_valid = 1;
        io_trace_this->out_test = value;
    }

    return count;
}

static struct file *open_log_file(char *name)
{
    mm_segment_t oldfs;
    struct file *filp = NULL;

    oldfs = get_fs();
    set_fs(get_ds());

    filp = filp_open(name, O_CREAT| O_WRONLY | O_TRUNC, 0644);

    set_fs(oldfs);

    if (IS_ERR(filp)) {
        io_trace_print("failed to open %s: %ld \n", name, PTR_ERR(filp));
        return NULL;
    }

    return filp;
}
static int write_file(struct file *filp, struct iovec *vec)
{
    int ret;
    mm_segment_t oldfs;

    oldfs = get_fs();
    set_fs(get_ds());

    ret = vfs_writev(filp, vec, 1, &filp->f_pos);
    set_fs(oldfs);
    if (unlikely(ret < 0))
    {
        io_trace_print("failed to write\n");
    }

    return ret;
}

static int write_head_kernel(struct file *filp)
{
    struct iovec vec[1];
    unsigned char buf[164];
    int ret;

    unsigned len;

    len = sprintf(buf, "%-5s%-10s%-10s%-20s%-20s%-15s%-10s%-15s%-15s%-8s%-15s\n", "CPU","TGID",
            "PID", "PName","Time", "Inode/Sector", "Nr_Types","Action", "Delay", "RW", "F_NAME");
    vec[0].iov_base = buf;
    vec[0].iov_len  = len;

    ret = write_file(filp, &vec[0]);

    return ret;
}

static void io_entry_rw(unsigned char rw, char *buf)
{
    unsigned int len = 0;
    len += sprintf(buf + len, "%s", rw_name[rw & IO_TRACE_WRITE]);
    if(rw & IO_TRACE_SYNC)
    {
        len += sprintf(buf + len, "%s", rw_name[__IO_TRACE_SYNC]);
    }

    if(rw & IO_TRACE_META)
    {
        len += sprintf(buf + len, "%s", rw_name[__IO_TRACE_META]);
    }

    if(rw & IO_TRACE_DISCARD)
    {
        len += sprintf(buf + len, "%s", rw_name[__IO_TRACE_DISCARD]);
    }

    return;

}


static int write_log_kernel(struct file *filp, struct io_trace_log_entry *entry)
{
    struct iovec vec[1];
    int ret;
    char rw_type[32];
    unsigned char buf[180];
    unsigned len;
    

    if (IS_ERR(filp)) {
        io_trace_print("file descriptor to is invalid: %ld\n", PTR_ERR(filp));
        return -1;
    }
    // format: <priority:1><message:N>\0
    io_entry_rw(entry->rw, rw_type);
    len = sprintf(buf, "%-5d&%-10d&%-10d&%-20s&%-20ld&%-12ld&%-10d&%-10s&%-5d&%-15ld&%-5s&%-32s\n", entry->cpu,
            entry->tgid, entry->pid, entry->comm, entry->time, entry->inode, entry->nr_bytes,
            all_trace_action[entry->action].name, entry->action, entry->delay,
            rw_type, entry->f_name);

    vec[0].iov_base = buf;
    vec[0].iov_len  = len;

    ret = write_file(filp, &vec[0]);

    return ret;
}

static struct kobject *kobject_ts;
static int io_trace_probe(struct platform_device *pdev)
{
    int ret;
    kobject_ts = kobject_create_and_add("io_log_data", NULL);
    if(!kobject_ts)
    {
        io_trace_print("create object failed!\n");
        return -1;
    }

    ret = sysfs_create_group(kobject_ts, &io_trace_attr_group);
    if(ret)
    {
        kobject_put(kobject_ts);
        io_trace_print("create group failed!\n");
        return -1;
    }
    return ret;
}

static struct platform_driver io_trace_driver = {
    .probe = io_trace_probe,
    .driver = {
        .owner = THIS_MODULE, 
        .name = "io_trace",
    },
};

static struct io_trace_log_entry *io_get_pid_buf(struct io_trace_pid *trace_pid,
        unsigned int action)
{
    struct io_trace_log_entry *ret_trace = NULL;

    if(action > IO_TRACE_PARENT_END)
    {
        return NULL;
    }

    ret_trace = &trace_pid->pid_entry[action];

    return ret_trace;
}

static struct io_trace_log_entry *io_get_all_buf(struct io_trace_ctrl *trace_ctrl)
{
    struct io_trace_log_entry *ret_trace = NULL;
    unsigned long flags;

    /*must be irq save lock, because mmc end is done in irq context!*/
    //spin_lock(&global_spinlock);
    spin_lock_irqsave(&global_spinlock, flags);

    ret_trace = ((struct io_trace_log_entry *)(trace_ctrl->mem_mngt->all_trace_buff) + 
            trace_ctrl->all_log_index);
    trace_ctrl->all_log_index ++;
    /*point to next valid entry*/
    if(trace_ctrl->all_log_index >= IO_MAX_LOG_PER_GLOBAL)    
    {
        trace_ctrl->all_log_index = 0;
    }

    if(trace_ctrl->all_log_count < IO_MAX_LOG_PER_GLOBAL)
    {
        trace_ctrl->all_log_count ++;
    }
    //spin_unlock(&global_spinlock);
    spin_unlock_irqrestore(&global_spinlock, flags);

    return ret_trace;
}

struct io_trace_tag_attr
{
    unsigned int curr_attr;
    unsigned int parent;       
    unsigned int rw_flags;
    unsigned int fname_flag;
    unsigned int nr_bytes;
    char f_name[IO_F_NAME_LEN];

    unsigned long (*func)(struct io_trace_pid *trace_pid, unsigned int action,
        unsigned int parent, unsigned long log_time, unsigned long inode); /*handler from the begin tag to end*/
    void (*handler)(struct io_trace_pid *trace_pid, unsigned int action,
            unsigned int parent, unsigned long inode);
};

static unsigned int io_trace_find_index(struct io_trace_log_entry *begin_entry,
        unsigned int log_index, unsigned int log_count, unsigned int action,
        unsigned int parent, unsigned long inode)
{
    unsigned int index;
    unsigned int index_cnt = 0;
    struct io_trace_log_entry *entry = NULL;

    io_trace_assert(action > parent);

    index = log_index;
    while(log_count > 0)
    {
        index = (index == 0) ? (IO_MAX_LOG_PER_GLOBAL - 1) : (index - 1);
        entry = (((struct io_trace_log_entry *)(begin_entry)) + index);
        index_cnt ++;
        if(entry->action == parent && inode == entry->inode)
        {
            break;
        }
        log_count --;
    }

    if(!log_count)
    {
        return (unsigned int)-1;
    }

    return index; 
}

static unsigned long io_trace_direct_delay(struct io_trace_pid *trace_pid,
        unsigned int action, unsigned int parent, unsigned long log_time,
        unsigned long inode)
{
    unsigned long ret_delay;    
    struct io_trace_log_entry *ret_trace = NULL;

    io_trace_assert(action > parent);
    ret_trace = &trace_pid->pid_entry[parent];
    /*normal not happen, but only the enable and disable pair*/
    if(ret_trace->valid == 0)
    {
        //io_trace_assert(0);
        return 0;
    }
    if(ret_trace->inode != inode)
    {
        return (unsigned long)-1;
    }
    ret_trace->valid = 0;
    ret_delay = log_time - ret_trace->time;

    return ret_delay;
}

static void io_trace_global_log(unsigned int action, unsigned long sector, 
        unsigned int nr_bytes, unsigned int parent, unsigned long own_time, 
        unsigned long delay, unsigned int rw_flags, char *f_name)
{
    struct io_trace_ctrl *trace_ctrl = io_trace_this;
    struct io_trace_log_entry *all_log_entry = NULL;
    struct task_struct *tsk = current; 
    pid_t pid;
    pid_t tgid;
    struct timespec realts;
    unsigned long log_time;

    pid = tsk->pid;
    tgid = tsk->tgid;
    io_trace_assert(pid < 32768);
    /*dont handle max process*/
    if(pid >= IO_MAX_PROCESS || tgid >= IO_MAX_PROCESS)
    {
        return;
    }

    log_time = own_time;
    if(!log_time)
    {
        do_posix_clock_monotonic_gettime(&realts);
        //monotonic_to_bootbased(&realts);
        log_time = (unsigned long )realts.tv_sec*1000000000 + realts.tv_nsec;
    }

    if(sector == ((unsigned long)-1))
    {
        sector = (unsigned long)0;
    }
    /*exist sector 0, but no such parent???*/

#if 0
    if(parent && (sector != 0))
    {
        struct io_trace_log_entry *begin = 
            (struct io_trace_log_entry *)(trace_ctrl->mem_mngt->all_trace_buff);
        struct io_trace_log_entry *index_entry;
        unsigned index;

        index = io_trace_find_index(begin, trace_ctrl->all_log_index, 64, action, parent,
                sector);   

        if(index != (unsigned int)(-1))
        {
            index_entry = (begin + index);
            delay = log_time - index_entry->time;
        }
        else
        {
            delay = 0xFFFFFFFF;
        }
    }
#endif

    all_log_entry = io_get_all_buf(trace_ctrl);
    all_log_entry->action = action;
    all_log_entry->rw = (unsigned char)rw_flags;
    all_log_entry->cpu = raw_smp_processor_id();
    all_log_entry->pid = pid;
    all_log_entry->tgid = tgid;
    all_log_entry->nr_bytes = nr_bytes;
    all_log_entry->inode = sector;
    all_log_entry->time = log_time;
    all_log_entry->delay = delay;
    memcpy(all_log_entry->comm, tsk->comm, IO_P_NAME_LEN);
    memset(all_log_entry->f_name, '\0', IO_F_NAME_LEN);

    if(f_name)
    {
        memcpy(all_log_entry->f_name, f_name, IO_F_NAME_LEN);
    }

    return;
}

static int io_trace_need_action(unsigned int action)
{
    /*only parent action*/
    if((action >= READ_BEGIN_TAG) && 
            (action <= IO_TRACE_PARENT_END))    
    {
        return 1;
    }

    return 0;
}
static void io_trace_add_log(unsigned int action, unsigned long i_ino, 
        struct io_trace_tag_attr *tag_attr)
{
    struct io_trace_ctrl *trace_ctrl = io_trace_this;
    struct task_struct *tsk = current; 
    pid_t pid;
    pid_t tgid;
    struct io_trace_pid *trace_pid = NULL;
    struct io_trace_log_entry *log_entry = NULL;
    struct timespec realts;
    unsigned long log_time;
    unsigned long delay = 0;
    int skip = 0;
    unsigned int rw = tag_attr->rw_flags;

    if(trace_ctrl == NULL)
    {
        io_trace_print("trace_ctrl is NULL!\n");
        return;
    }
    pid = tsk->pid;
    tgid = tsk->tgid;
    io_trace_assert(pid < 32768);
    /*dont handle max process id*/
    if(pid >= IO_MAX_PROCESS || tgid >= IO_MAX_PROCESS)
    {
        return;
    }

    trace_pid = trace_ctrl->all_trace[pid];
    if(trace_pid->running == 0)
    {
        trace_pid->running = 1;
        trace_pid->pid = pid;
    }

    trace_pid->log_count ++;
    /*time based from boot*/
    do_posix_clock_monotonic_gettime(&realts);
    //monotonic_to_bootbased(&realts);
    log_time = (unsigned long )realts.tv_sec*1000000000 + realts.tv_nsec;
    if(tag_attr->parent)
    {
        char *f_name = NULL;
        unsigned int nr_bytes = 0;
        //io_trace_assert(tag_attr->func != NULL);
        if(tag_attr->func)
        {
            delay = tag_attr->func(trace_pid, action, tag_attr->parent, log_time, i_ino);
        }

        if(delay > IO_TRACE_LIMIT_LOG && (delay != ((unsigned long)-1)))
        {
            if(tag_attr->fname_flag)
            {
                f_name = tag_attr->f_name;
            }

            if(tag_attr->nr_bytes)
            {
                nr_bytes = tag_attr->nr_bytes;
            }
            /*don't need log the parent*/
            //io_trace_global_log(tag_attr->parent, i_ino, 0, log_time - delay, 0, rw, f_name);
            io_trace_global_log(action, i_ino, nr_bytes, 0, log_time, delay, rw, f_name);
            skip = 1;
        }
    }

    if(io_trace_need_action(action) && (skip == 0))
    {
        log_entry = io_get_pid_buf(trace_pid, action);
        if(log_entry == NULL)
        {
            //io_trace_print("log action:%d, error!\n", action);
            return;
        }
        log_entry->action = action;
        log_entry->rw = (unsigned char)rw;
        log_entry->cpu = raw_smp_processor_id();
        log_entry->pid = pid;
        log_entry->tgid = tgid;
        log_entry->inode = i_ino;
        log_entry->time = log_time;
        log_entry->delay = delay;

        {
            memcpy(log_entry->comm, tsk->comm, IO_P_NAME_LEN);
        }

        log_entry->valid = 1;
    }

    return;
}

static int io_entry_fname(struct io_trace_tag_attr *tag, struct file *filp)
{
    struct dentry *dir = filp->f_path.dentry;
    unsigned int len = (sizeof(tag->f_name) - 1);

    if(dir->d_name.name)
    {
        len = len > dir->d_name.len ? dir->d_name.len : len;
        memcpy(tag->f_name, dir->d_name.name, len);
        tag->f_name[len] = '\0';

        return 1;
    }
    else
    {
        memset(tag->f_name, '\0', IO_F_NAME_LEN);
    }

    return 0;
}

static void io_tag_attr_init(struct io_trace_tag_attr *attr)
{
    attr->curr_attr = 0;
    attr->parent = 0;
    attr->fname_flag = 0;
    attr->nr_bytes = 0;
    attr->func = NULL;

    return;
}

static void io_generic_file_read_begin(void *ignore, struct file *filp, size_t count)
{
	struct inode *inode = filp->f_mapping->host;
    struct io_trace_tag_attr tag_attr;

    io_tag_attr_init(&tag_attr);
    tag_attr.rw_flags = IO_TRACE_READ; 

    if(io_trace_this->enable)
    {
        io_trace_add_log(READ_BEGIN_TAG, inode->i_ino, &tag_attr);
    }

    return;
}

static void io_generic_file_read_end(void *ignore, struct file *filp, size_t count)
{
	struct inode *inode = filp->f_mapping->host;
    struct io_trace_tag_attr tag_attr;
    int ret = 0;

    io_tag_attr_init(&tag_attr);
    tag_attr.parent = READ_BEGIN_TAG;
    tag_attr.func = io_trace_direct_delay;
    tag_attr.rw_flags = IO_TRACE_READ; 
    tag_attr.nr_bytes = count;

    ret = io_entry_fname(&tag_attr, filp);
    if(ret)
    {
        tag_attr.fname_flag = 1;
    }

    if(io_trace_this->enable)
    {
        io_trace_add_log(READ_END_TAG, inode->i_ino, &tag_attr);
    }

    return;
}

static void io_generic_perform_write_enter(void *ignore, struct file *file,
        size_t count, loff_t pos)
{ 
	struct inode *inode = file->f_mapping->host;
    struct io_trace_tag_attr tag_attr;

    io_tag_attr_init(&tag_attr);
    tag_attr.rw_flags = IO_TRACE_WRITE; 

    if(io_trace_this->enable)
    {
        io_trace_add_log(WRITE_BEGIN_TAG, inode->i_ino, &tag_attr);
    }

    return;
}

static void io_generic_perform_write_end(void *ignore, struct file *file, size_t count)
{
	struct inode *inode = file->f_mapping->host;
    struct io_trace_tag_attr tag_attr;
    int ret = 0;

    io_tag_attr_init(&tag_attr);
    tag_attr.parent = WRITE_BEGIN_TAG;
    tag_attr.func = io_trace_direct_delay;
    tag_attr.rw_flags = IO_TRACE_WRITE; 
    tag_attr.nr_bytes = count;

    ret = io_entry_fname(&tag_attr, file);
    if(ret)
    {
        tag_attr.fname_flag = 1;
    }

    if(io_trace_this->enable)
    {
        io_trace_add_log(WRITE_END_TAG, inode->i_ino, &tag_attr);
    }

    return;
}

static void io_ext4_da_write_begin(void *ignore, struct inode *inode,
        loff_t pos, unsigned size, unsigned flags)
{
    struct io_trace_tag_attr tag_attr;

    io_tag_attr_init(&tag_attr);
    tag_attr.rw_flags = IO_TRACE_WRITE; 

    if(io_trace_this->enable)
    {
        io_trace_add_log(EXT4_DA_WRITE_BEGIN_TAG, inode->i_ino, &tag_attr);
    }

    return;
}

static void io_ext4_da_write_begin_end(void *ignore, struct inode *inode,
        loff_t pos, unsigned size, unsigned flags)
{
    struct io_trace_tag_attr tag_attr;

    io_tag_attr_init(&tag_attr);
    tag_attr.rw_flags = IO_TRACE_WRITE; 
    tag_attr.nr_bytes = size;

    if(io_trace_this->enable)
    {
        io_trace_add_log(EXT4_DA_WRITE_END_TAG, inode->i_ino, &tag_attr);
    }

    return;
}

static void io_ext4_sync_file_enter(void *ignore, struct file *file, int datasync)
{
	struct inode *inode = file->f_mapping->host;
    struct io_trace_tag_attr tag_attr;

    io_tag_attr_init(&tag_attr);
    tag_attr.rw_flags = IO_TRACE_WRITE; 

    if(io_trace_this->enable)
    {
        io_trace_add_log(EXT4_SYNC_ENTER_TAG, inode->i_ino, &tag_attr);
    }

    return;
}

static void io_ext4_sync_write_wait_end(void *ignore, struct file *file, int datasync)
{
    return;
}

static void io_ext4_sync_file_end(void *ignore, struct file *file, int ret)
{
	struct inode *inode = file->f_mapping->host;
    struct io_trace_tag_attr tag_attr;
    int r = 0;

    io_tag_attr_init(&tag_attr);
    tag_attr.parent = EXT4_SYNC_ENTER_TAG;
    tag_attr.func = io_trace_direct_delay;
    tag_attr.rw_flags = IO_TRACE_WRITE; 

    r = io_entry_fname(&tag_attr, file);
    if(r)
    {
        tag_attr.fname_flag = 1;
    }

    if(io_trace_this->enable)
    {
        io_trace_add_log(EXT4_SYNC_EXIT_TAG, inode->i_ino, &tag_attr);
    }

    return;
}

static void io_ext4_sync_file_exit(void *ignore, struct inode *inode, int ret)
{
    struct io_trace_tag_attr tag_attr;

    io_tag_attr_init(&tag_attr);
    tag_attr.parent = EXT4_SYNC_ENTER_TAG;
    tag_attr.func = io_trace_direct_delay;
    tag_attr.rw_flags = IO_TRACE_WRITE; 

    if(io_trace_this->enable)
    {
        io_trace_add_log(EXT4_SYNC_EXIT_TAG, inode->i_ino, &tag_attr);
    }

    return;
}

static void io_block_write_begin_enter(void *ignore, struct inode *inode,
        struct page *page, loff_t pos, unsigned size)
{
    struct io_trace_tag_attr tag_attr;

    io_tag_attr_init(&tag_attr);
    tag_attr.rw_flags = IO_TRACE_WRITE; 

    if(io_trace_this->enable)
        io_trace_add_log(BLOCK_WRITE_BEGIN_TAG, inode->i_ino, &tag_attr);

    return;
}

static void io_block_write_begin_end(void *ignore, struct inode *inode,
        struct page *page, int err)
{
    struct io_trace_tag_attr tag_attr;

    io_tag_attr_init(&tag_attr);
    tag_attr.rw_flags = IO_TRACE_WRITE; 

    if(io_trace_this->enable)
        io_trace_add_log(BLOCK_WRITE_END_TAG, inode->i_ino, &tag_attr);

    return;
}

#if 0
static void io_ext4_da_writepages(void *ignore, struct inode *inode,
        struct writeback_control *wbc)
{
    struct io_trace_tag_attr tag_attr;
    tag_attr.curr_attr = 0;
    tag_attr.parent = 0;
    tag_attr.rw_flags = IO_TRACE_WRITE; 
    tag_attr.fname_flag = 0;

    if(io_trace_this->enable)
        io_trace_add_log(EXT4_WRITE_PAGES_TAG, inode->i_ino, &tag_attr);

    return;
}

static void io_ext4_da_write_pages(void *ignore, struct inode *inode,
        void *mpd)
{
    struct io_trace_tag_attr tag_attr;
    tag_attr.curr_attr = 0;
    tag_attr.parent = 0;
    tag_attr.rw_flags = IO_TRACE_WRITE; 
    tag_attr.fname_flag = 0;

    if(io_trace_this->enable)
        io_trace_add_log(EXT4_WRITE_PAGE_TAG, inode->i_ino, &tag_attr);

    return;
}

static void io_ext4_da_writepages_result(void *ignore, struct inode *inode, 
        struct writeback_control *wbc, int ret, int pages_written)
{
    
    struct io_trace_tag_attr tag_attr;
    tag_attr.curr_attr = 0;
    tag_attr.parent = 0;
    tag_attr.rw_flags = IO_TRACE_WRITE; 
    tag_attr.fname_flag = 0;

    if(io_trace_this->enable)
        io_trace_add_log(EXT4_WRITE_PAGES_END_TAG, inode->i_ino, &tag_attr);

    return;
}
#endif

static void io_mpage_da_map_and_submit(void *ignore, struct inode *inode, 
        ext4_fsblk_t fblk, unsigned int len)
{
    if(io_trace_this->enable)
    {
        io_trace_global_log(EXT4_MAP_SUBMIT_TAG, inode->i_ino, len << inode->i_blkbits, 
                0, 0, fblk << 3, 1, NULL);
    }

    return;
}


static void blk_dm_request(void *ignore, struct request_queue *q, struct bio *bio)
{
    if(io_trace_this->enable)
    {
        io_trace_global_log(BLOCK_BIO_DM_TAG, bio->bi_sector, bio->bi_size, 
                0, 0, 0, bio->bi_rw, NULL);
    }

    return;
}

static void blk_crypt_map(void *ignore, struct bio *bio, sector_t sector)
{
    if(io_trace_this->enable)
    {
        io_trace_global_log(BLOCK_BIO_CRYPT_MAP, bio->bi_sector, bio->bi_size, 
                0, 0, sector, bio->bi_rw, NULL);
    }

    return;
}
static void blk_kcryptd_crypt(void *ignore, struct bio *bio)
{
    if(io_trace_this->enable)
    {
        io_trace_global_log(BLOCK_DM_CRYPT_TAG, bio->bi_sector, bio->bi_size, 
                0, 0, 0, bio->bi_rw, NULL);
    }

    return;
}
static void blk_crypt_dec_pending(void *ignore, struct bio *bio)
{
    if(io_trace_this->enable)
    {
        io_trace_global_log(BLOCK_DM_CRYPT_DEC_TAG, bio->bi_sector, bio->bi_size, 
                0, 0, 0, bio->bi_rw, NULL);
    }

    return;
}


static void blk_add_trace_rq_insert(void *ignore, struct request_queue *q, struct request *rq)
{
    if(io_trace_this->enable)
    {
        io_trace_global_log(BLOCK_RQ_INSERT_TAG, blk_rq_pos(rq), blk_rq_bytes(rq), 
                0, 0, 0, rq->cmd_flags, NULL);
    }

    return;
}
static void blk_add_trace_rq_issue(void *ignore, struct request_queue *q, struct request *rq)
{

    if(io_trace_this->enable)
    {
        io_trace_global_log(BLOCK_RQ_ISSUE_TAG, blk_rq_pos(rq), blk_rq_bytes(rq),
                BLOCK_BIO_QUEUE_TAG, 0, 0, rq->cmd_flags, NULL);
    }

    return;
}

static void blk_add_trace_rq_complete(void *ignore, struct request_queue *q,
        struct request *rq, unsigned int nr_bytes)
{

    if(io_trace_this->enable)
    {
        io_trace_global_log(BLOCK_RQ_COMPLETE_TAG, blk_rq_pos(rq), blk_rq_bytes(rq), 
                BLOCK_RQ_ISSUE_TAG, 0, 0, rq->cmd_flags, NULL);
    }

    return;
}

static void blk_add_trace_bio_remap(void *ignore, struct request_queue *q, 
        struct bio *bio, dev_t dev, sector_t from)
{
    if(io_trace_this->enable)
    {
        io_trace_global_log(BLOCK_BIO_REMAP_TAG, bio->bi_sector, bio->bi_size,
                0, 0, from, bio->bi_rw, NULL);
    }

    return;
}

static void blk_add_trace_bio_queue(void *ignore, struct request_queue *q, struct bio *bio)
{
    if(io_trace_this->enable)
    {
        io_trace_global_log(BLOCK_BIO_QUEUE_TAG, bio->bi_sector, bio->bi_size,
                0, 0, 0, bio->bi_rw, NULL);
    }

    return;
}


static void mmc_blk_rw_start(void *ignore, unsigned int cmd, 
        unsigned int addr, struct mmc_data *data)
{
    unsigned int rw_flags = 0;

    if(cmd == MMC_WRITE_MULTIPLE_BLOCK || cmd == MMC_WRITE_BLOCK)
    {
        rw_flags |= IO_TRACE_WRITE;
    }
    if(io_trace_this->enable)
        io_trace_global_log(MMC_BLK_RW_START_TAG, addr, 0, 0, 0, 0, rw_flags, NULL);

    return;
}

static void mmc_blk_rw_end(void *ignore, unsigned int cmd, 
        unsigned int addr, struct mmc_data *data)
{
    unsigned int rw_flags = 0;

    if(cmd == MMC_WRITE_MULTIPLE_BLOCK || cmd == MMC_WRITE_BLOCK)
    {
        rw_flags |= IO_TRACE_WRITE;
    }
    if(io_trace_this->enable)
        io_trace_global_log(MMC_BLK_RW_END_TAG, addr, 0, MMC_BLK_RW_START_TAG, 0, 0, rw_flags, NULL);
    return;
}

static void mmc_blk_cmdq_rw_start(void *ignore, unsigned int cmd, unsigned int tag, 
        unsigned int addr, unsigned int size)
{
    unsigned int rw_flags = 0;
    if(!(cmd & (1 << 2)))
    {
        rw_flags |= IO_TRACE_WRITE;
    }

    if(io_trace_this->enable)
    {
        io_trace_global_log(MMC_BLK_CMDQ_RW_START_TAG, addr, size, 0, 0, 0, rw_flags, NULL);
    }

    return;
}

static void mmc_blk_cmdq_rw_end(void *ignore, unsigned int cmd, unsigned int tag, 
        unsigned int addr, unsigned int size)
{
    unsigned int rw_flags = 0;
    if(!(cmd & (1 << 2)))
    {
        rw_flags |= IO_TRACE_WRITE;
    }

    if(io_trace_this->enable)
    {
        io_trace_global_log(MMC_BLK_CMDQ_RW_END_TAG, addr, size, 0, 0, 0, rw_flags, NULL);
    }

    return;
}

static void io_f2fs_sync_file_enter(void *ignore, struct inode *inode)
{
    struct io_trace_tag_attr tag_attr;
    io_tag_attr_init(&tag_attr);
    tag_attr.rw_flags = IO_TRACE_WRITE; 

    if(io_trace_this->enable)
    {
        io_trace_add_log(F2FS_SYNC_ENTER_TAG, inode->i_ino, &tag_attr);
    }
    return;
}

static void io_f2fs_sync_file_exit(void *ignore, struct inode *inode, bool need_cp, 
        int datasync, int ret)
{
    struct io_trace_tag_attr tag_attr;

    io_tag_attr_init(&tag_attr);
    tag_attr.parent = F2FS_SYNC_ENTER_TAG;
    tag_attr.func = io_trace_direct_delay;
    tag_attr.rw_flags = IO_TRACE_WRITE; 

    if(io_trace_this->enable)
    {
        io_trace_add_log(F2FS_SYNC_EXIT_TAG, inode->i_ino, &tag_attr);
    }
    return;
}

static void io_f2fs_sync_fs(void *ignore, struct super_block *sb, int sync)
{
    if(io_trace_this->enable)
    {
        io_trace_global_log(F2FS_SYNC_FS_TAG, sync, 0, 0, 0, 0, IO_TRACE_WRITE, NULL);
    }

    return;
}

static void io_f2fs_write_checkpoint(void *ignore, struct super_block *sb, bool reason, 
        char *str_phase)
{
    
    if(io_trace_this->enable)
    {
        unsigned int handle = 1;
        if(strncmp(str_phase, "finish block_ops", 15) == 0)
        {
            handle = 2;
        }
        else if(strncmp(str_phase, "finish checkpoint", 15) == 0)
        {
            handle = 3;
        }
        io_trace_global_log(F2FS_WRITE_CP_TAG, reason, handle,
                0, 0, 0, IO_TRACE_WRITE, NULL);
    }
    return;
}

static void iotrace_register_tracepoints(void)
{
	int ret;
    /*vfs*/
	ret = register_trace_generic_perform_write_enter(io_generic_perform_write_enter, NULL);
	WARN_ON(ret);
	ret = register_trace_generic_perform_write_end(io_generic_perform_write_end, NULL);
	WARN_ON(ret);
	ret = register_trace_generic_file_read_begin(io_generic_file_read_begin, NULL);
	WARN_ON(ret);
	ret = register_trace_generic_file_read_end(io_generic_file_read_end, NULL);
	WARN_ON(ret);
	ret = register_trace_ext4_da_write_begin(io_ext4_da_write_begin, NULL);
	WARN_ON(ret);
	ret = register_trace_ext4_da_write_begin_end(io_ext4_da_write_begin_end, NULL);
	WARN_ON(ret);
    /*ext4*/
	ret = register_trace_ext4_sync_file_enter(io_ext4_sync_file_enter, NULL);
	WARN_ON(ret);
	ret = register_trace_ext4_sync_write_wait_end(io_ext4_sync_write_wait_end, NULL);
	WARN_ON(ret);
	ret = register_trace_ext4_sync_file_end(io_ext4_sync_file_end, NULL);
	WARN_ON(ret);
    /*
	ret = register_trace_ext4_sync_file_exit(io_ext4_sync_file_exit, NULL);
	WARN_ON(ret);
    */
#if 0
    ret = register_trace_ext4_da_writepages(io_ext4_da_writepages, NULL);
    WARN_ON(ret);
    ret = register_trace_ext4_da_write_pages(io_ext4_da_write_pages, NULL);
    WARN_ON(ret);
    ret = register_trace_ext4_da_writepages_result(io_ext4_da_writepages_result, NULL);
    WARN_ON(ret);
#endif
    /*F2FS*/
    ret = register_trace_f2fs_sync_file_enter(io_f2fs_sync_file_enter, NULL);
    WARN_ON(ret);
    ret = register_trace_f2fs_sync_file_exit(io_f2fs_sync_file_exit, NULL);
    WARN_ON(ret);
    ret = register_trace_f2fs_sync_fs(io_f2fs_sync_fs, NULL);
    WARN_ON(ret);
    ret = register_trace_f2fs_write_checkpoint(io_f2fs_write_checkpoint, NULL);
    WARN_ON(ret);

    /*page cache*/
	ret = register_trace_block_write_begin_enter(io_block_write_begin_enter, NULL);
	WARN_ON(ret);
	ret = register_trace_block_write_begin_end(io_block_write_begin_end, NULL);
	WARN_ON(ret);
	ret = register_trace_mpage_da_map_and_submit(io_mpage_da_map_and_submit, NULL);
	WARN_ON(ret);

    /*block layer*/
    /*
    ret = register_trace_block_dm_request(blk_dm_request, NULL);
	WARN_ON(ret);
    */
    ret = register_trace_block_crypt_map(blk_crypt_map, NULL);
	WARN_ON(ret);
    ret = register_trace_block_kcryptd_crypt(blk_kcryptd_crypt, NULL); 
	WARN_ON(ret);
    ret = register_trace_block_crypt_dec_pending(blk_crypt_dec_pending, NULL);
	WARN_ON(ret);

    ret = register_trace_block_rq_insert(blk_add_trace_rq_insert, NULL);
	WARN_ON(ret);
    ret = register_trace_block_rq_issue(blk_add_trace_rq_issue, NULL); 
	WARN_ON(ret);
    ret = register_trace_block_rq_complete(blk_add_trace_rq_complete, NULL);
	WARN_ON(ret);
    ret = register_trace_block_bio_remap(blk_add_trace_bio_remap, NULL);
	WARN_ON(ret);
    /*
    ret = register_trace_block_bio_queue(blk_add_trace_bio_queue, NULL);
	WARN_ON(ret);
    */
    /*
    ret = register_trace_block_getrq(blk_add_trace_getrq, NULL); 
	WARN_ON(ret);
    */
    ret = register_trace_mmc_blk_rw_start(mmc_blk_rw_start, NULL);
    WARN_ON(ret);
    ret = register_trace_mmc_blk_rw_end(mmc_blk_rw_end, NULL);
    WARN_ON(ret);

    ret = register_trace_mmc_blk_cmdq_rw_start(mmc_blk_cmdq_rw_start, NULL);
    WARN_ON(ret);
    ret = register_trace_mmc_blk_cmdq_rw_end(mmc_blk_cmdq_rw_end, NULL);
    WARN_ON(ret);
    
    return;
}

static void iotrace_unregister_tracepoints(void)
{
    /*vfs*/
	unregister_trace_generic_perform_write_enter(io_generic_perform_write_enter, NULL);
	unregister_trace_generic_perform_write_end(io_generic_perform_write_end, NULL);
	unregister_trace_generic_file_read_begin(io_generic_file_read_begin, NULL);
	unregister_trace_generic_file_read_end(io_generic_file_read_end, NULL);
    /*ext4*/
	unregister_trace_ext4_da_write_begin(io_ext4_da_write_begin, NULL);
	unregister_trace_ext4_da_write_begin_end(io_ext4_da_write_begin_end, NULL);
	unregister_trace_ext4_sync_file_enter(io_ext4_sync_file_enter, NULL);
	unregister_trace_ext4_sync_write_wait_end(io_ext4_sync_write_wait_end, NULL);
	unregister_trace_ext4_sync_file_exit(io_ext4_sync_file_exit, NULL);
	unregister_trace_mpage_da_map_and_submit(io_mpage_da_map_and_submit, NULL);
    /*page cache*/
	unregister_trace_block_write_begin_enter(io_block_write_begin_enter, NULL);
	unregister_trace_block_write_begin_end(io_block_write_begin_end, NULL);
    /*block layer*/
    unregister_trace_block_dm_request(blk_dm_request, NULL);
    unregister_trace_block_kcryptd_crypt(blk_kcryptd_crypt, NULL); 
    unregister_trace_block_crypt_dec_pending(blk_crypt_dec_pending, NULL);

    unregister_trace_block_rq_insert(blk_add_trace_rq_insert, NULL);
    unregister_trace_block_rq_issue(blk_add_trace_rq_issue, NULL); 
    unregister_trace_block_rq_complete(blk_add_trace_rq_complete, NULL);
    unregister_trace_block_bio_queue(blk_add_trace_bio_queue, NULL);

    unregister_trace_mmc_blk_rw_start(mmc_blk_rw_start, NULL);
    unregister_trace_mmc_blk_rw_end(mmc_blk_rw_end, NULL);
    /*
    ret = register_trace_block_getrq(blk_add_trace_getrq, NULL); 
	WARN_ON(ret);
    */
    unregister_trace_mmc_blk_cmdq_rw_start(mmc_blk_cmdq_rw_start, NULL);
    unregister_trace_mmc_blk_cmdq_rw_end(mmc_blk_cmdq_rw_end, NULL);
    return;
}

static void io_trace_offline(struct io_trace_ctrl *trace_ctrl)
{
    io_trace_print("io_trace_offline!\n");
    iotrace_unregister_tracepoints();

    return;
}

static void io_trace_setup(struct io_trace_ctrl *trace_ctrl)
{
    io_trace_print("io_trace_setup!\n");
    iotrace_register_tracepoints();

    return;
}

static unsigned char *io_mem_mngt_alloc(struct io_trace_mem_mngt *mem_mngt)
{
    unsigned char *ret_buf = NULL;

    raw_spin_lock(&trace_buff_spinlock);
    if(mem_mngt->index >= IO_RUNNING_MAX_PROCESS)
    {
        io_trace_print("mem alloc is full!\n");
        /*TODO: free memory*/
        raw_spin_unlock(&trace_buff_spinlock);
        return NULL;
    }
    ret_buf = mem_mngt->buff[mem_mngt->index];
    mem_mngt->index ++;
    raw_spin_unlock(&trace_buff_spinlock);

    return ret_buf;
}

static void io_mem_mngt_free(struct io_trace_mem_mngt *mem_mngt, unsigned char *buf)
{
    if(buf == NULL)
    {
        io_trace_print("free null buffer!\n");
        return;
    }
    raw_spin_lock(&trace_buff_spinlock);
    if((mem_mngt->index - 1) >= 0)
    {
        mem_mngt->index --;
        mem_mngt->buff[mem_mngt->index] = buf;
    }
    raw_spin_unlock(&trace_buff_spinlock);

    return;
}

static int io_mem_mngt_init(struct io_trace_mem_mngt *mem_mngt)
{
    int i = 0;

    mem_mngt->index = 0;

    for(i = 0; i < IO_RUNNING_MAX_PROCESS; i++)
    {
        mem_mngt->buff[i] = kmalloc(2 * IO_MAX_BUF_ENTRY, GFP_KERNEL);
        if(mem_mngt->buff[i] == NULL)
        {
            io_trace_print("io_mem_mngt_init kmalloc failed!\n");
            goto failed;
        }
    }

    mem_mngt->all_trace_buff = kmalloc(IO_MAX_GLOBAL_ENTRY, GFP_KERNEL);
    if(mem_mngt->all_trace_buff == NULL)
    {
        io_trace_print("io_mem_mngt_free all trace buff failed!\n");
        goto failed;
    }

    return 0;

failed:
    i--;
    for(; i >=0; i--)
        kfree(mem_mngt->buff[i]);

    return -1;
}


static int trace_mm_init(struct io_trace_ctrl *trace_ctrl)
{
    int i = 0;

    io_trace_print("trace mm init start!\n");
    for(i = 0; i < IO_MAX_PROCESS; i++)
    {
        trace_ctrl->all_trace[i] = (struct io_trace_pid *)kmalloc(
                sizeof(struct io_trace_pid), GFP_KERNEL);   
        if(trace_ctrl->all_trace[i] == NULL)
        {
            io_trace_print("all trace kmalloc failed!\n");
            goto failed;
        }
        memset(trace_ctrl->all_trace[i], 0, sizeof(struct io_trace_pid));
    }

    trace_ctrl->mem_mngt = (struct io_trace_mem_mngt *)kmalloc(
            sizeof(struct io_trace_mem_mngt), GFP_KERNEL);
    if(trace_ctrl->mem_mngt == NULL)
    {
        io_trace_print("mem mngt kmalloc failed!\n");
        goto failed;
    }

    if(io_mem_mngt_init(trace_ctrl->mem_mngt) < 0)
    {
        kfree(trace_ctrl->mem_mngt);
        goto failed;
    }

    return 0;

failed:
    i--;
    for(; i >=0; i--)
        kfree(trace_ctrl->all_trace[i]);

    return -1;
}

static int trace_ctrl_init(struct io_trace_ctrl *trace_ctrl, unsigned int *total_mem)
{
    trace_ctrl->first = 0;
    trace_ctrl->enable = 0;
    trace_ctrl->pdev = NULL;
    trace_ctrl->filp = NULL;

    return 0;

#if 0
    for(i = 0; i < IO_MAX_PROCESS; i++)
    {
        trace_ctrl->all_trace[i] = (struct io_trace_pid *)kmalloc(
                sizeof(struct io_trace_pid), GFP_KERNEL);   
        if(trace_ctrl->all_trace[i] == NULL)
        {
            io_trace_print("all trace kmalloc failed!\n");
            goto failed;
        }
        memset(trace_ctrl->all_trace[i], 0, sizeof(struct io_trace_pid));
        (*total_mem) += sizeof(struct io_trace_pid);
    }

    trace_ctrl->mem_mngt = (struct io_trace_mem_mngt *)kmalloc(
            sizeof(struct io_trace_mem_mngt), GFP_KERNEL);
    if(trace_ctrl->mem_mngt == NULL)
    {
        io_trace_print("mem mngt kmalloc failed!\n");
        goto failed;
    }

    (*total_mem) += sizeof(struct io_trace_mem_mngt);

    if(io_mem_mngt_init(trace_ctrl->mem_mngt, total_mem) < 0)
    {
        kfree(trace_ctrl->mem_mngt);
        goto failed;
    }

    return 0;

failed:
    i--;
    for(; i >=0; i--)
        kfree(trace_ctrl->all_trace[i]);

    return -1;
#endif

}

static int __init io_trace_init(void)
{
    int ret = -1;

    int total_mem = 0;

    io_trace_print("Enter %s\n", __FUNCTION__);
    if(io_trace_this == NULL)
    {
        io_trace_this = (struct io_trace_ctrl *)kmalloc(
                sizeof(struct io_trace_ctrl), GFP_KERNEL);
        total_mem += sizeof(struct io_trace_ctrl);
        if(NULL == io_trace_this)
        {
            io_trace_print("(%s)kmalloc failed!", __FUNCTION__);
            return -1;
        }
        io_trace_print("io_trace_this is init!\n");
        memset(io_trace_this, 0, sizeof(struct io_trace_ctrl));
        if(trace_ctrl_init(io_trace_this, &total_mem) < 0)
        {
            return -1;
        }
    }

    io_trace_print("total mem : %d\n", total_mem);
    io_trace_print("Enter %s:%d\n", __FUNCTION__, __LINE__);
    spin_lock_init(&global_spinlock);
    mutex_init(&output_mutex);

    io_trace_this->pdev = platform_device_register_simple("io_trace", -1, NULL, 0);
    if(!io_trace_this->pdev)
    {
        io_trace_print("(%s)register platform_device_register_simple null!", __FUNCTION__);
        return -1;
    }

    ret = platform_driver_register(&io_trace_driver);
    if(ret < 0)
    {
        io_trace_print("(%s)register platform_driver_register failed!", __FUNCTION__);
        return ret;
    }

    return 0;
}

static void __exit io_trace_exit(void)
{
    if(io_trace_this->pdev)
        platform_device_unregister(io_trace_this->pdev);    

    platform_driver_unregister(&io_trace_driver);
}

subsys_initcall(io_trace_init);
module_exit(io_trace_exit);
