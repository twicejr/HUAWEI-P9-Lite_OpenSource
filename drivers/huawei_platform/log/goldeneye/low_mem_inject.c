
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/poll.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/syslog.h>
#include <linux/slab.h>
#include <linux/gfp.h>

#include <asm/uaccess.h>
#include <asm/io.h>

#include "low_mem_inject.h"


static t_low_mem_inject host_low_mem_inject;

static char* buffers[1024];
static int index_buffer = 0;

static int low_mem_inject_open(struct inode * inode, struct file * file)
{
    pr_info("[HW]: %s: init the GlodenEye driver open... \n", __func__);
    return 0;
}

static int low_mem_inject_release(struct inode * inode, struct file * file)
{
    pr_info("[HW]: %s: init the GlodenEye driver release... \n", __func__);
    return 0;
}

static ssize_t low_mem_inject_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    pr_info("[HW]: %s: init the GlodenEye driver read... \n", __func__);
    return 0;
}

static ssize_t low_mem_inject_write(struct file *file, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
    unsigned int i;
    unsigned long int j;

    char *cmd_buffer;
    unsigned long int alloc_size = 0;
    char *alloc_buffer;
    char buffer_defined[128] = {0};

    pr_info("[HW]: %s: init the GlodenEye driver write... \n", __func__);

    cmd_buffer = kmalloc(sizeof(char)*cnt, GFP_KERNEL);
    if (cmd_buffer == NULL) {
        return -ENOMEM;
    }
    memset(cmd_buffer, 0, sizeof(char)*cnt);

    if(copy_from_user(cmd_buffer, ubuf, cnt)){
        kfree(cmd_buffer);
        return -EFAULT;
    }else{
        strncpy(buffer_defined, cmd_buffer, cnt);
    }

    alloc_size = simple_strtol(cmd_buffer, NULL, 10);
    if(alloc_size){
        pr_info("[HW]: %s: alloc_size = %ld \n", __func__, alloc_size);
    }

    alloc_buffer = kmalloc(sizeof(char)*alloc_size, GFP_KERNEL);
    if (alloc_buffer == NULL) {
        pr_info("[HW]: %s: alloc error... \n", __func__);
        return -ENOMEM;
    }

    for(i=0; i< 0x80; i++){
        memset(alloc_buffer, i, sizeof(char)*alloc_size);
        for(j=0;j<alloc_size; j++){
            if(*(alloc_buffer + j) != i){
                pr_info("[HW]: %s: shift = %ld error \n", __func__, j);
            }
        }
    }

    return 0;
}

static unsigned int low_mem_inject_poll(struct file *file, poll_table *wait)
{
    pr_info("[HW]: %s: init the GlodenEye driver poll... \n", __func__);
    return 0;
}

static long low_mem_inject_unlocked_ioctl(struct file * file, unsigned int cmd, unsigned long arg)
{
    char *buffer;
    unsigned int i;
    unsigned long int j;
    pr_info("[HW]: %s: init the GlodenEye driver ioctrl... \n", __func__);
    pr_info("[HW]: %s: cmd = %d, arg = %ld \n", __func__, cmd, arg);

    if(_IOC_TYPE(cmd) != TEST_MAGIC){
        pr_info("[HW]: %s: cmd error \n", __func__);
        return - EINVAL;
    }

    if(_IOC_NR(cmd) > TEST_MAX_NR){
        pr_info("[HW]: %s: cmd error \n", __func__);
        return - EINVAL;
    }

    switch(cmd) {
        case LOW_MEM_SETTING_ENABLE:
            if(arg == 1)
                host_low_mem_inject.flags.enabled = 1;
            else if(arg == 0){
                host_low_mem_inject.flags.enabled = 0;
                pr_info("[HW] %s %d free memory \n", __func__, __LINE__);
                for(i=0; i < index_buffer; i++){
                    kfree(buffers[i]);
                }
                index_buffer = 0;
            }
            else
                pr_err("[HW]: %s: arg error \n", __func__);
            break;

        case LOW_MEM_SETTING_INJECT_SIZE:
            pr_info("[HW]: %s: arg = %d\n", __func__, (int)arg);

            if(host_low_mem_inject.flags.enabled){
                if (index_buffer >= 1024) {
                    pr_info("[HW]: %s: inject full\n", __func__);
                    return -ENOMEM;
                }
                buffer = kmalloc(sizeof(char)*arg, GFP_KERNEL);
                if (buffer == NULL) {
                    pr_info("[HW]: %s: kmalloc error\n", __func__);
                    return -ENOMEM;
                }else{
                    buffers[index_buffer++] = buffer;
                    pr_info("[HW]: %s: kmalloc addr = 0x%08x\n", __func__, (int)buffer);
                }

                for(i=0; i< 0xFE; i++){
                    memset(buffer, i, sizeof(char)*arg);
                    for(j=0;j<arg; j++){
                        if(*(buffer + j) != i){
                            pr_err("[HW]: %s: shift = %ld error \n", __func__, j);
                        }
                    }
                }
            }
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static const struct file_operations proc_low_mem_inject_operations = {
    .open				= low_mem_inject_open,
    .read				= low_mem_inject_read,
    .write				= low_mem_inject_write,
    .unlocked_ioctl		= low_mem_inject_unlocked_ioctl,
    .poll					= low_mem_inject_poll,
    .release				= low_mem_inject_release,
};

static int __init proc_low_mem_inject_init(void)
{
    pr_info("[HW]: %s GlodenEye driver built on %s @ %s\n", __func__, __DATE__, __TIME__);

    if(!proc_mkdir("goldeneye", NULL)){
        pr_info("[HW]: %s: error to create proc folder goldeneye \n", __func__);
    }

    proc_create("goldeneye/low_mem_inject", S_IRUSR|S_IWUSR, NULL, &proc_low_mem_inject_operations);
    return 0;
}
module_init(proc_low_mem_inject_init);
