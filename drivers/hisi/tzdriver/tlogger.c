
/*******************************************************************************
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
 *******************************************************************************/
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/vmalloc.h>
#include <linux/aio.h>
#include <asm/ioctls.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/syscalls.h>

static char    *log_buffer = NULL;
static size_t  addr_offset = 0;
static size_t  addr_start = 0;
static size_t  addr_end = 0;
#define PER_LEN 1024

//#define TLOG_DEBUG
#ifdef TLOG_DEBUG
#define TLOGEBUG(fmt, args...) printk(KERN_INFO ": " fmt "\n", ## args)
#else
#define TLOGEBUG(fmt, args...)
#endif
#define TLOGERR(fmt, args...) printk(KERN_ERR ": " fmt "\n", ## args)

#define LOGGER_LOG_TEEOS               "hisi_teelog"     /* tee os log  */

#define __TEELOGGERIO	0xBE             /* for ioctl */
#define TEELOGGER_GET_LOG_LEVEL		_IO(__TEELOGGERIO, 1) /* get the TEE log level */
#define TEELOGGER_SET_LOG_LEVEL		_IO(__TEELOGGERIO, 2) /* set the TEE log leve */
#define TEELOGGER_GET_LOG_SIZE		_IO(__TEELOGGERIO, 3) /* get the TEE log size */
#define TEELOGGER_GET_MEMORY_STATUS		_IO(__TEELOGGERIO, 4) /* get the TEE memory status */
#define TEELOGGER_RESERVE		_IO(__TEELOGGERIO, 5) /* reserve */

#define LOG_PATH_HISI_LOGS "/data/hisi_logs/"
#define LOG_PATH_RUNNING_TRACE "/data/hisi_logs/running_trace/"
#define LOG_PATH_TEE_LOG "/data/hisi_logs/running_trace/teeos_logs/"
#define LOG_PATH_TEE_LOG_FILE "/data/hisi_logs/running_trace/teeos_logs/last_teemsg"

#define ROOT_UID                0
#define SYSTEM_GID              1000

/**
 * struct logger_log - represents a specific log, such as 'main' or 'radio'
 * @buffer:	The actual ring buffer
 * @misc:	The "misc" device representing the log
 * @wq:		The wait queue for @readers
 * @readers:	This log's readers
 * @mutex:	The mutex that protects the @buffer
 * @w_off:	The current write head offset
 * @head:	The head, or location that readers start reading at.
 * @size:	The size of the log
 * @logs:	The list of log channels
 *
 * This structure lives from module insertion until module removal, so it does
 * not need additional reference counting. The structure is protected by the
 * mutex 'mutex'.
 */
struct logger_log {
    unsigned char		*buffer;
    struct miscdevice	misc;
    wait_queue_head_t	wq;
    struct list_head	readers;
    struct mutex		mutex;
    size_t			w_off;
    size_t			head;
    size_t			size;
    struct list_head	logs;
};

static LIST_HEAD(log_list);


/**
 * struct logger_reader - a logging device open for reading
 * @log:	The associated log
 * @list:	The associated entry in @logger_log's list
 * @r_off:	The current read head offset.
 * @r_all:	Reader can read all entries
 * @r_ver:	notice:read the whole ring-buffer times, not version
 *
 * This object lives from open to release, so we don't need additional
 * reference counting. The structure is protected by log->mutex.
 */
struct logger_reader {
    struct logger_log	*log;
    struct list_head	list;
    size_t			r_off;
    bool			r_all;
    int			r_ver;
};

extern int TC_NS_get_rdr_mem_addr(void);
extern int TC_NS_get_rdr_mem_len(void);

/*
 * file_get_log - Given a file structure, return the associated log
 *
 * This isn't aesthetic. We have several goals:
 *
 *	1) Need to quickly obtain the associated log during an I/O operation
 *	2) Readers need to maintain state (logger_reader)
 *	3) Writers need to be very fast (open() should be a near no-op)
 *
 * In the reader case, we can trivially go file->logger_reader->logger_log.
 * For a writer, we don't want to maintain a logger_reader, so we just go
 * file->logger_log. Thus what file->private_data points at depends on whether
 * or not the file was opened for reading. This function hides that dirtiness.
 */
static inline struct logger_log *file_get_log(struct file *file)
{
    if (file->f_mode & FMODE_READ) {
        struct logger_reader *reader = file->private_data;
        return reader->log;
    } else
        return file->private_data;
}

static struct logger_log *g_log = NULL;
/*
 * logger_read - our log's read() method
 *
 * Behavior:
 *
 *	- O_NONBLOCK works
 *	- If there are no log entries to read, blocks until log is written to
 *	- Atomically reads exactly one log entry
 *
 * Will set errno to EINVAL if read
 * buffer is insufficient to hold next entry.
 */
#define CHECK_BOUNDARY(X)    (((X) < addr_start) ||(( X) > addr_end) )? true : false
static ssize_t tlogger_read(struct file *file, char __user *buf,
        size_t count, loff_t *pos)
{
    struct logger_reader *reader = file->private_data;
    struct logger_log *log = reader->log;
    ssize_t ret;
    size_t log_len;
    size_t sub;
    bool disjoin_flag;
    int real_addr=0;
    int ring_flag=0;

    DEFINE_WAIT(wait);
    TLOGEBUG("logger_read  start  ++ \n");

start:
    while (1) {
        mutex_lock(&log->mutex);
        prepare_to_wait(&log->wq, &wait, TASK_INTERRUPTIBLE);
        memcpy(&real_addr,log_buffer,4);
        memcpy(&ring_flag,log_buffer+4,4);
        TLOGEBUG(" real_addr=0x%x ring_flag=%d\n",real_addr, ring_flag);
        log->w_off = real_addr+addr_offset;

        ret = ((log->w_off == reader->r_off) && (ring_flag == reader->r_ver));
        TLOGEBUG("log->w_off=%llx reader->r_off=%llx ret=%llu current->pid=%d true=%d \n",log->w_off, reader->r_off, ret, current->pid, true);
        mutex_unlock(&log->mutex);
        if (!ret)
            break;

        if (file->f_flags & O_NONBLOCK) {
            TLOGERR("nonblock branch\n");
            ret = -EAGAIN;
            break;
        }

        if (signal_pending(current)) {
            TLOGERR("signal branch\n");
            ret = -EINTR;
            break;
        }
        schedule();
    }

    finish_wait(&log->wq, &wait);
    if (ret)
        return ret;

    mutex_lock(&log->mutex);

    /* is there still something to read or did we race? */
    if (unlikely(log->w_off == reader->r_off)) {
        mutex_unlock(&log->mutex);
        goto start;
    }

    TLOGEBUG("log->w_off == reader->r_off is not same, so should read log \n");

    if(ring_flag != reader->r_ver /*ring_flag not same*/){
        if((reader->r_off > log->w_off) && ((ring_flag-reader->r_ver)==1)){
            sub = (addr_end - reader->r_off)+(log->w_off - addr_start);
            TLOGEBUG("1 disjoin_flag=true sub=%llu  read->r_ver=%d\n",sub, reader->r_ver);
        }
        else{
            reader->r_off = log->w_off;
            sub = (addr_end - reader->r_off)+(log->w_off - addr_start);
            TLOGEBUG("2 disjoin_flag=true sub=%llu  read->r_ver=%d\n",sub, reader->r_ver);
        }
        disjoin_flag = true;
    }
    else{
        disjoin_flag = false;
        if(log->w_off < reader->r_off){
            TLOGERR("1225 tlogcaterrorinfo----addr_start=0x%lx  ring_flag=%d  read->r_ver=%d log->w_off=%lx reader->r_off=%lx \n"
				,addr_start, ring_flag, reader->r_ver, log->w_off, reader->r_off);
            reader->r_off = addr_start;
            ret = -1;
            goto out;
        }
        sub=log->w_off -reader->r_off;
        TLOGEBUG("sub=%llu  read->r_ver=%d\n",sub, reader->r_ver);
    }
    log_len = ( sub < PER_LEN)? sub : PER_LEN;

    if(disjoin_flag && ((reader->r_off + log_len )>  addr_end)){
        if(CHECK_BOUNDARY(reader->r_off) ){
            TLOGERR("1 CHECK_BOUNDARY error reader->r_off=0x%lu \n", reader->r_off);
        }
        ret = copy_to_user( buf,(void *)(reader->r_off), (addr_end-reader->r_off));
        TLOGEBUG("read (addr_end-reader->r_off)=%llu ret = %llu \n",(addr_end-reader->r_off),ret);

        ret = copy_to_user( buf,(void *)(addr_start), (log_len - (addr_end-reader->r_off)));
        TLOGEBUG("read (log_len - (addr_end-reader->r_off))=%llu log_len=%llu\n",(log_len - (addr_end-reader->r_off)),log_len);
        reader->r_ver = ring_flag;
    }
    else{
        if(CHECK_BOUNDARY(reader->r_off) || CHECK_BOUNDARY(reader->r_off+log_len)){
            TLOGERR("2 CHECK_BOUNDARY error reader->r_off=0x%lu reader->r_off+log_len =0x%lu\n",reader->r_off, reader->r_off+log_len);
        }

        if(log_len)
            ret = copy_to_user( buf,(void *)(reader->r_off), log_len);
        TLOGEBUG("read  log_len=%llu\n", log_len);
    }

    TLOGEBUG("ret = %llu \n",ret);

    /* update reader->r_off */
    if(disjoin_flag && ((reader->r_off + log_len )>  addr_end) )
        reader->r_off = addr_start+(log_len - (addr_end-reader->r_off));
    else
        reader->r_off+=log_len;

    /* return log_len */
    ret =log_len;
out:
    mutex_unlock(&log->mutex);

    return ret;
}

/*its role is same to logger_aio_write*/
void tz_log_write(void)
{
    TLOGEBUG("tz_log_write wake up start  log=0x%x \n",g_log);
    if(g_log != NULL)
        wake_up_interruptible(&g_log->wq);
}

/*
 * logger_aio_write - our write method, implementing support for write(),
 * writev(), and aio_write(). Writes are our fast path, and we try to optimize
 * them above all else.
 */
static ssize_t logger_aio_write(struct kiocb *iocb, const struct iovec *iov,
        unsigned long nr_segs, loff_t ppos)
{
    ssize_t ret = 0;
    return ret;
}


static struct logger_log *get_log_from_minor(int minor)
{
    struct logger_log *log;

    list_for_each_entry(log, &log_list, logs)
        if (log->misc.minor == minor)
            return log;
    return NULL;
}

/*
 * logger_open - the log's open() file operation
 *
 * Note how near a no-op this is in the write-only case. Keep it that way!
 */
static int tlogger_open(struct inode *inode, struct file *file)
{
    struct logger_log *log;
    int ret;
    int real_addr=0;
    int ring_flag=0;

    TLOGEBUG("open logger_open ++\n");
    //not support seek
    ret = nonseekable_open(inode, file);
    if (ret)
        return ret;
    TLOGEBUG("Before get_log_from_minor\n");
    log = get_log_from_minor(MINOR(inode->i_rdev));
    if (!log)
        return -ENODEV;

    if (file->f_mode & FMODE_READ) {
        struct logger_reader *reader;

        reader = kmalloc(sizeof(struct logger_reader), GFP_KERNEL);
        if (!reader)
            return -ENOMEM;

        reader->log = log;
        memcpy(&real_addr,log_buffer,4);
        memcpy(&ring_flag,log_buffer+4,4);
        TLOGEBUG(" real_addr=0x%x ring_flag=%d\n",real_addr, ring_flag);
        reader->r_ver = ring_flag;
        reader->r_all = true;

        INIT_LIST_HEAD(&reader->list);

        mutex_lock(&log->mutex);
        if(reader->r_ver){
            reader->r_off = log->w_off+1;
            if(log->w_off == (addr_end-1))
                reader->r_off = addr_end;
            reader->r_ver--;
        }
        else
            reader->r_off = log->head;

        TLOGEBUG("open log->w_off=0x%llx reader->r_off=0x%llx ring_flag=%d reader->r_ver=%d\n ",log->w_off,reader->r_off, ring_flag, reader->r_ver);

        list_add_tail(&reader->list, &log->readers);
        mutex_unlock(&log->mutex);

        file->private_data = reader;
    }else
        file->private_data = log;
    return 0;
}

/*
 * logger_release - the log's release file operation
 *
 * Note this is a total no-op in the write-only case. Keep it that way!
 */
static int tlogger_release(struct inode *ignored, struct file *file)
{
    TLOGEBUG("logger_release ++\n");
    if (file->f_mode & FMODE_READ) {
        struct logger_reader *reader = file->private_data;
        struct logger_log *log = reader->log;
        mutex_lock(&log->mutex);
        list_del(&reader->list);
        mutex_unlock(&log->mutex);
        kfree(reader);
    }
    return 0;
}

/*
 * logger_poll - the log's poll file operation, for poll/select/epoll
 *
 * Note we always return POLLOUT, because you can always write() to the log.
 * Note also that, strictly speaking, a return value of POLLIN does not
 * guarantee that the log is readable without blocking, as there is a small
 * chance that the writer can lap the reader in the interim between poll()
 * returning and the read() request.
 */
static unsigned int tlogger_poll(struct file *file, poll_table *wait)
{
    struct logger_reader *reader;
    struct logger_log *log;
    unsigned int ret = POLLOUT | POLLWRNORM;
    int ring_flag=0;
    memcpy(&ring_flag,log_buffer+4,4);


    TLOGEBUG("logger_poll ++\n");

    if (!(file->f_mode & FMODE_READ))
        return ret;

    reader = file->private_data;
    log = reader->log;

    poll_wait(file, &log->wq, wait);

    mutex_lock(&log->mutex);

    TLOGEBUG("poll before  log->w_off=%llx reader->r_off=%llx \n",log->w_off, reader->r_off);
    log->w_off = (size_t)(*((unsigned int *)log_buffer)+addr_offset);
    TLOGEBUG("poll after     log->w_off=%llx reader->r_off=%llx \n",log->w_off, reader->r_off);
    if ( (log->w_off != reader->r_off) || (ring_flag != reader->r_ver))
        ret |= POLLIN | POLLRDNORM;
    mutex_unlock(&log->mutex);

    return ret;
}

static int tee_get_loglevel(void)
{
    int real_addr=0;
    int ring_flag=0;
    int log_level = 0;
    memcpy(&real_addr,log_buffer,4);
    memcpy(&ring_flag,log_buffer+4,4);
    memcpy(&log_level,log_buffer+8,4);
    TLOGEBUG(" real_addr=0x%x ring_flag=%d log_level=%d\n",real_addr, ring_flag, log_level);
    return log_level;
}

static int tee_set_loglevel(unsigned long arg)
{
    int real_addr=0;
    int ring_flag=0;
    int log_level = 0;
    memcpy(&real_addr,log_buffer,4);
    memcpy(&ring_flag,log_buffer+4,4);
    memcpy(&log_level,log_buffer+8,4);
    TLOGEBUG(" real_addr=0x%x ring_flag=%d log_level=%d\n",real_addr, ring_flag, log_level);
    log_level = arg;
    memcpy(log_buffer+8,&log_level,4);
    return log_level;
}

static long tlogger_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct logger_log *log = file_get_log(file);
    long ret = -EINVAL;

    TLOGEBUG("logger_ioctl start ++\n");
    mutex_lock(&log->mutex);

    switch (cmd) {
        case TEELOGGER_GET_LOG_LEVEL:
            TLOGEBUG("excute tee_get_loglevel\n");
            ret = tee_get_loglevel();
            break;
        case TEELOGGER_SET_LOG_LEVEL:
            TLOGEBUG("excute tee_set_loglevel\n");
            ret = tee_set_loglevel(arg);
            break;
        case TEELOGGER_GET_LOG_SIZE:
            ret = log->size;
            break;
        case TEELOGGER_GET_MEMORY_STATUS:
            ret = log->size;
            break;
        default:
            TLOGERR("ioctl error default\n");
            break;
    }

    mutex_unlock(&log->mutex);

    return ret;
}

#ifdef CONFIG_COMPAT
static long tlogger_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    long ret = -ENOIOCTLCMD;
    TLOGEBUG("logger_compat_ioctl ++\n");
    arg = (unsigned long) compat_ptr(arg);
    ret = tlogger_ioctl(file, cmd, arg);
    return ret;
}
#endif

static const struct file_operations logger_fops = {
    .owner = THIS_MODULE,
    .read = tlogger_read,
    .aio_write = logger_aio_write,
    .poll = tlogger_poll,
    .unlocked_ioctl = tlogger_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = tlogger_compat_ioctl,
#endif
    .open = tlogger_open,
    .release = tlogger_release,
};


#define OFFSET (64+156)
#define OFFSET1 64
#define OFFSET2  (5*1024)
#define RESERVE_SIZE (20 * 1024)
static unsigned int RDR_MEM_LEN;
static unsigned int ADDR_P;
static unsigned int RDR_LOG_SIZE;
static int rdr_mem_init()
{
   int ret = 0;
   unsigned int rdr_mem_addr;
   rdr_mem_addr = TC_NS_get_rdr_mem_addr();
   RDR_MEM_LEN = TC_NS_get_rdr_mem_len();
   if (rdr_mem_addr != 0 && RDR_MEM_LEN != 0){
        ADDR_P = rdr_mem_addr + OFFSET2;
		RDR_LOG_SIZE = RDR_MEM_LEN - RESERVE_SIZE;
   }
   else
        ret = -1;
   return ret;
}

static int __init create_log(char *log_name, int size)
{
    int ret = 0;
    struct logger_log *log;
    unsigned char *buffer;
    buffer = log_buffer;
    if (buffer == NULL)
        return -ENOMEM;
    log = kzalloc(sizeof(struct logger_log), GFP_KERNEL);
    if (log == NULL) {
        ret = -ENOMEM;
        goto out_free_buffer;
    }
    log->buffer = buffer;
    log->misc.minor = MISC_DYNAMIC_MINOR;
    log->misc.name = kstrdup(log_name, GFP_KERNEL);
    if (log->misc.name == NULL) {
        ret = -ENOMEM;
        goto out_free_log;
    }
    log->misc.fops = &logger_fops;
    log->misc.parent = NULL;

    init_waitqueue_head(&log->wq);
    INIT_LIST_HEAD(&log->readers);
    mutex_init(&log->mutex);
    log->w_off = (size_t)(*((unsigned int *)log_buffer) + addr_offset);
    log->head = (size_t)(log_buffer+OFFSET1);
    log->size = size;
    TLOGEBUG("tlocat  log->w_off=%llx log->head=%llx addr_offset=%llu\n",log->w_off, log->head, addr_offset);
    INIT_LIST_HEAD(&log->logs);
    list_add_tail(&log->logs, &log_list);
    /* finally, initialize the misc device for this log */
    ret = misc_register(&log->misc);
    if (unlikely(ret)) {
        TLOGERR("failed to register misc device for log '%s'!\n",
                log->misc.name);
        goto out_free_log;
    }
    TLOGEBUG("created %luK log '%s'\n",
            (unsigned long) log->size >> 10, log->misc.name);
    g_log = log;
    return 0;

out_free_log:
    kfree(log);

out_free_buffer:
    //vfree(buffer);
    return ret;
}

static int tee_create_dir(char *path)
{
	int fd = -1;
	int ret = 0;
	fd = sys_access(path, 0);
	if (0 != fd) {
		TLOGEBUG("need create dir %s.\n", path);
		fd	= sys_mkdir(path, 0770);
		if (fd < 0) {
			TLOGERR("create dir %s fail, ret: %d.\n", path, fd);
			return fd;
		}
		TLOGEBUG("create dir %s successed, fd: %d.\n", path, fd);
		ret = (int)sys_chown((const char __user *)path, ROOT_UID, SYSTEM_GID);
		if(ret){
		    TLOGERR("Failed to chown %s\n", path);
		}
	}

	return 0;
}

int tlogger_store_lastmsg(void)
{
    struct file *filep;
    ssize_t write_len;
    char *tmp_log_buffer = phys_to_virt(ADDR_P);
    mm_segment_t old_fs;
    loff_t pos = 0;
    int ret;

    if(!virt_addr_valid(tmp_log_buffer)){
	    TLOGERR("tmp_log_buffer is not valid addr\n");
	    return -EFAULT;
    }

    ret = tee_create_dir(LOG_PATH_HISI_LOGS);
    if (0 != ret) {
	    TLOGERR("failed to creat log dir\n");
	    return -1;
    }

    ret = tee_create_dir(LOG_PATH_RUNNING_TRACE);
    if (0 != ret) {
	    TLOGERR("failed to creat log dir\n");
	    return -1;
    }

    ret = tee_create_dir(LOG_PATH_TEE_LOG);
    if (0 != ret) {
	    TLOGERR("failed to creat log dir\n");
	    return -1;
    }

    TLOGEBUG("tmp_log_buf is %p, size is %d\n", tmp_log_buffer, rdr_mem_len-OFFSET2);
    /*exception handling, store trustedcore exception info to file*/
    filep=filp_open(LOG_PATH_TEE_LOG_FILE,O_CREAT|O_RDWR,0640);
    if(IS_ERR(filep))
    {
        TLOGEBUG("Failed to filp_open last_teemsg, filep=0x%x\n", (unsigned long)filep);
        return -1;
    }

    TLOGEBUG("Succeed to filp_open last_teemsg, filep=0x%x\n", (unsigned long)filep);

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    ret = (int)sys_chown((const char __user *)LOG_PATH_TEE_LOG_FILE, ROOT_UID, SYSTEM_GID);
    if(ret){
	TLOGERR("Failed to chown last_teemsg\n");
    }

    write_len = vfs_write(filep, (char __user*)tmp_log_buffer, RDR_MEM_LEN-OFFSET2, &pos);
    if (write_len < 0)
    {
        TLOGERR("Failed to write to last_teemsg\n");
    }
    else
    {
        TLOGERR("Succeed to Write to last_teemsg, write_len=%ld\n", write_len);
    }
    pos = 0;

    set_fs(old_fs);
    filp_close(filep,0);
    return 0;
}

static int __init tlogger_init(void)
{
    int ret;
    ret = rdr_mem_init();
	if (ret < 0){
		TLOGERR("rdr mem init failed!!!\n");
		return -1;
	}
    log_buffer = (char *)hisi_bbox_map(ADDR_P,RDR_MEM_LEN-OFFSET2);
    addr_offset =(size_t)(log_buffer -(char *) ADDR_P );
    addr_start = (size_t)(log_buffer + 64);
    addr_end = (size_t)(log_buffer + RDR_LOG_SIZE);
    TLOGERR("1225 tlogcat:addr_start=0x%lx\taddr_end=0x%lx\n",addr_start,addr_end);
    ret = create_log(LOGGER_LOG_TEEOS, RDR_LOG_SIZE);
    return ret;
}

static void __exit tlogger_exit(void)
{
    struct logger_log *current_log, *next_log;

    list_for_each_entry_safe(current_log, next_log, &log_list, logs) {
        /* we have to delete all the entry inside log_list */
        misc_deregister(&current_log->misc);
        //vfree(current_log->buffer);
        kfree(current_log->misc.name);
        list_del(&current_log->logs);
        kfree(current_log);
    }
    iounmap(log_buffer);
}


device_initcall(tlogger_init);
module_exit(tlogger_exit);


MODULE_AUTHOR("z00202529");
MODULE_DESCRIPTION("TrustCore Logger");
MODULE_VERSION("1.00");
