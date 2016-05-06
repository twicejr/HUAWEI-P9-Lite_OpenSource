/* drivers/android/bootloader_logger.c
 *
 * Copyright (C) 2008-2014 dongjinguang@huawei.com.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/types.h>
#include <linux/errno.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/poll.h>
#include <linux/proc_fs.h>
#include <linux/syslog.h>
#include <asm/io.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/console.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/seq_file.h>
#include <linux/debugfs.h>

#include <huawei_platform/log/hw_log.h>
#include <global_ddr_map.h>

#define HWLOG_TAG   bootloader_log
HWLOG_REGIST();

/*
* Here use a non-share DDR area, which size is 64k Bytes
* to save bootloader (fastboot1 & fastboot2 ) log.
* The offset & phy-addr follows shall be consist with platform
* pre-defined in kernel.
*/
struct bootloader_logger_buffer {
    uint32_t    sig;
    uint32_t    size;
};

#define bootloader_logger_SIG (0x43474244) /* DBGC */
#define DDR_SBL_ADDR            (FASTBOOT_DUMP_LOG_ADDR)
#define DDR_SBL_SIZE             (FASTBOOT_DUMP_LOG_SIZE)
struct bootloader_logger {
    char *tag;
    char *old_log;
    size_t old_log_size;
    struct bootloader_logger_buffer *buffer;
    size_t buffer_size;
};
extern unsigned int himntn_gobal_resetlog;
static struct bootloader_logger logger_main ;
static struct bootloader_logger logger_last  ;

static void __init
bootloader_logger_save_old(struct bootloader_logger *logger, char *dest)
{
    struct bootloader_logger_buffer *buffer = logger->buffer;
    size_t old_log_size = buffer->size;
    size_t total_size = old_log_size;

    if (dest == NULL) {
        dest = kmalloc(total_size, GFP_KERNEL);
        if (dest == NULL) {
            hwlog_err("bootloader_logger_%s: failed to allocate buffer\n",
                   logger->tag);
            return;
        }
    }

    logger->old_log = dest;
    logger->old_log_size = total_size;

    memcpy(logger->old_log, buffer+ sizeof(struct bootloader_logger_buffer), buffer->size );
}

static int bootloader_logger_init(struct bootloader_logger *logger, char *old_buf)
{
    struct bootloader_logger_buffer *buffer = logger->buffer;

    hwlog_info( "bootloader_logger_%s: buffer=%p, size=%d\n",
            logger->tag, logger->buffer, logger->buffer_size);

    if (buffer->sig == bootloader_logger_SIG) {
        if (buffer->size > logger->buffer_size)
            hwlog_info("bootloader_logger_%s: found existing invalid "
                   "buffer, size %d \n",
                   logger->tag, buffer->size);
        else {
            hwlog_info("bootloader_logger_%s: found existing buffer, "
                   "size %d \n",
                   logger->tag, buffer->size);
            if (buffer->size > 0)
                bootloader_logger_save_old(logger, old_buf);
        }
    } else {
        hwlog_info("bootloader_logger_%s: no valid data in buffer "
               "(sig = 0x%08x)\n", logger->tag, buffer->sig);
    }

    /* Erase old bootloader log */
    buffer->sig = 0;
    buffer->size = 0;

    return 0;
}


static ssize_t bootloader_logger_main_read_old(struct file *file, char __user *buf,
                    size_t len, loff_t *offset)
{
    loff_t pos = *offset;
    ssize_t count;

    if (pos >= logger_main.old_log_size)
        return 0;

    count = min(len, (size_t)(logger_main.old_log_size - pos));
    if (copy_to_user(buf, logger_main.old_log + pos, count))
        return -EFAULT;

    *offset += count;
    return count;
}

static const struct file_operations bootloader_logger_main_file_ops = {
    .owner = THIS_MODULE,
    .read = bootloader_logger_main_read_old,
};

static ssize_t bootloader_logger_last_read_old(struct file *file, char __user *buf,
                    size_t len, loff_t *offset)
{
    loff_t pos = *offset;
    ssize_t count;

    if (pos >= logger_last.old_log_size)
        return 0;

    count = min(len, (size_t)(logger_last.old_log_size - pos));
    if (copy_to_user(buf, logger_last.old_log + pos, count))
        return -EFAULT;

    *offset += count;
    return count;
}

static const struct file_operations bootloader_logger_last_file_ops = {
    .owner = THIS_MODULE,
    .read = bootloader_logger_last_read_old,
};

static void bootloader_logger_dump_old(struct bootloader_logger *logger)
{
    int i;
    char *p = logger->old_log;

    if (!p)
        return;

    hwlog_info( "*****************************"
            "bootloader_log_%s begin"
            "*****************************\n", logger->tag);
    for (i = 0; i < logger->old_log_size; i++) {
        if (logger->old_log[i] == '\0')
            logger->old_log[i] = ' ';
        if (logger->old_log[i] == '\n') {
            logger->old_log[i] = '\0';
            printk(KERN_INFO "bootloader_log_%s: %s\n", logger->tag, p);
            logger->old_log[i] = '\n';
            p = &logger->old_log[i + 1];
        }
    }
    hwlog_info( "******************************"
            "bootloader_log_%s end"
            "******************************\n", logger->tag);
}

static int __init bootloader_logger_late_init(void)
{
    size_t buffer_size;
    void *buffer;

    int ret = 0;
    struct proc_dir_entry *entry;

    hwlog_info( "bootloader_logger: got buffer at %zx, size %zx\n",
           DDR_SBL_ADDR, DDR_SBL_SIZE);
    buffer_size = DDR_SBL_SIZE;
    #ifdef CONFIG_ARM64
    buffer =  ioremap(DDR_SBL_ADDR, DDR_SBL_SIZE);
    #else
    buffer = phys_to_virt(DDR_SBL_ADDR);
    #endif
    if (buffer == NULL) {
        hwlog_err( "bootloader_logger: failed to map memory\n");
        ret = -ENOMEM;
        goto error;
    }
    hwlog_info( "bootloader_logger: buffer mapped at %p\n", buffer);

    logger_main.tag = "main";
    logger_main.buffer = buffer;
    logger_main.buffer_size = buffer_size / 2 - sizeof(struct bootloader_logger_buffer);

    logger_last.tag = "last";
    logger_last.buffer = buffer + buffer_size / 2;
    logger_last.buffer_size = buffer_size / 2 - sizeof(struct bootloader_logger_buffer);

    bootloader_logger_init(&logger_main, NULL/* allocate */);
    bootloader_logger_init(&logger_last, NULL/* allocate */);


    if (logger_main.old_log != NULL) {
           entry = proc_create("bootloader_log", S_IRUSR, NULL, &bootloader_logger_main_file_ops);
        if (!entry) {
            hwlog_err("bootloader_logger: failed to create bootloader_log proc entry\n");
            kfree(logger_main.old_log);
            logger_main.old_log = NULL;
            return 0;
              }
        if (himntn_gobal_resetlog){
            bootloader_logger_dump_old(&logger_main);
           }
       }

    if (logger_last.old_log != NULL) {
           entry = proc_create("bootloader_log_last", S_IRUSR, NULL, &bootloader_logger_last_file_ops);
        if (!entry) {
            hwlog_err("bootloader_logger: failed to create bootloader_log_last proc entry\n");
            kfree(logger_last.old_log);
            logger_last.old_log = NULL;
            return 0;
              }
        if (himntn_gobal_resetlog){
            bootloader_logger_dump_old(&logger_last);
           }
    }
error:
	#ifdef CONFIG_ARM64
	iounmap(buffer);
	#endif
       return ret;
}

static void __exit bootloader_logger_late_exit(void)
{
    if(NULL != logger_main.old_log){
        kfree(logger_main.old_log);
        logger_main.old_log = NULL;
    }

    if(NULL != logger_last.old_log){
        kfree(logger_last.old_log);
        logger_last.old_log = NULL;
    }
}


module_init(bootloader_logger_late_init);
module_exit(bootloader_logger_late_exit);
