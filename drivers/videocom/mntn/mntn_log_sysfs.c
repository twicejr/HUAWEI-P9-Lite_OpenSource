#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/types.h>

#include "video_mntn_kernel.h"

#define CMDLENTH 128

#define LOG_TAG "VIDEO_MNTN_PRINT"
#define KOBJECT_NAME "video_mntn_dev"

#define CMD_SHOW "show"
#define CMD_SETPRINTLEVEL  "setlevel"
#define CMD_SETSAVE        "setsave"

STATIC void set_log_level(uint32_t module_id, uint32_t log_level)
{
    if ((module_id >= EN_ID_MNTN_LOG_MODULE_MAX)||(log_level >= EN_VIDEO_LOG_LEVEL_MAX)){
        printk("["LOG_TAG"]""param module_id[%d],log_level[%d] error\n", module_id, log_level);
        return;
    }

    g_mntn_log_module_id[module_id].log_level = log_level;
    printk("["LOG_TAG"]" "set module[%d].level:[%d]\n", \
        module_id,\
        g_mntn_log_module_id[module_id].log_level);
}

STATIC void show_log_level(void)
{
    uint32_t i = 0;
    uint32_t name_len = 0;

    printk("["LOG_TAG"]" "start %s\n", __FUNCTION__);

    while (i < EN_ID_MNTN_LOG_MODULE_MAX){

        name_len = strlen(g_mntn_log_module_id[i].module_name);

        if (0 != name_len){
            printk("["LOG_TAG"]""[module_id]:%d, [module_name]:%s, [log_level]:%d\n",
                i,
                g_mntn_log_module_id[i].module_name,
                g_mntn_log_module_id[i].log_level);
        }

        i++;
    }
    printk("["LOG_TAG"]" "leave %s\n", __FUNCTION__);
}

STATIC void set_save_data(uint32_t module_id, uint32_t save_cnt, uint32_t save_type)
{
    if ((module_id >= EN_ID_MNTN_DATA_MODULE_ID_MAX)||(save_type >= 2)){
        printk("["LOG_TAG"]""param module_id[%d],save_type[%d] error\n", module_id, save_type);
        return;
    }

    g_mntn_video_save_data_module[module_id].FrameNum     = save_cnt;
    g_mntn_video_save_data_module[module_id].ImageOrVideo = save_type;

    printk("["LOG_TAG"]" "set module[%d], FrameNum:[%d], SaveType:[%d]\n",
            module_id,
            g_mntn_video_save_data_module[module_id].FrameNum,
            g_mntn_video_save_data_module[module_id].ImageOrVideo);
}

STATIC void show_save(void)
{
    uint32_t i = 0;
    uint32_t name_len = 0;

    printk("["LOG_TAG"]" "start %s\n", __FUNCTION__);

    while (i < EN_ID_MNTN_DATA_MODULE_ID_MAX){
        name_len = strlen(g_mntn_video_save_data_module[i].ModuleName);

        if (0 != name_len){
            printk("["LOG_TAG"]""[module_id]:%d, [module_name]:%s, [FrameNum]:%d, [ImageOrVideo]:%d\n",
                i,
                g_mntn_video_save_data_module[i].ModuleName,
                g_mntn_video_save_data_module[i].FrameNum,
                g_mntn_video_save_data_module[i].ImageOrVideo);
        }

        i++;
    }
    printk("["LOG_TAG"]" "leave %s\n", __FUNCTION__);
}


/*
* The "video_mntn" file where a static variable is read from and written to.
*/
static ssize_t video_mntn_show(struct kobject *kobj, struct kobj_attribute *attr,
                     char *buf)
{
    show_log_level();
    show_save();
    return strlen(buf);
}

static ssize_t video_mntn_store(struct kobject *kobj, struct kobj_attribute *attr,
                      const char *buf, size_t count)
{
    char cmd[CMDLENTH] = {0};
    int  ret           = 0;

    uint32_t module_id = -1;
    uint32_t param1    = -1;

    uint32_t param2    = -1;

    ret = sscanf(buf, "%s %d,%d,%d", cmd, &module_id, &param1, &param2);

    if (3 == ret){
        if (!strcmp(cmd, CMD_SETPRINTLEVEL)){
            set_log_level(module_id, param1);
        }
    }
    else if(4 == ret){
        if (!strcmp(cmd, CMD_SETSAVE)){
            set_save_data(module_id, param1, param2);
        }
    }
    else{
        printk("["LOG_TAG"]""Store fail.input format error[%d]:%s", ret, buf);
        printk("["LOG_TAG"]""fmt should be: echo [command] [module_id],[log_level] > mntn_video_log\n");
        printk("["LOG_TAG"]""or        fmt: echo [command] [module_id],[log_level] > mntn_video_log\n");
    }

    return count;
}

#ifndef UT_TEST
static struct kobj_attribute video_mntn_attribute =
     __ATTR(video_mntn, 0664, video_mntn_show, video_mntn_store);

/*
* Create a group of attributes so that we can create and destory them all
* at once.
*/
static struct attribute *attrs[] = {
     &video_mntn_attribute.attr,
     NULL,   /* need to NULL terminate the list of attributes */
};

/*
* An unnamed attribute group will put all of the attributes directly in
* the kobject directory.  If we specify a name, a subdirectory will be
* created for the attributes with the directory being the name of the
* attribute group.
*/
static struct attribute_group attr_group = {
     .attrs = attrs,
};
#endif
static struct kobject *mntn_video_dev_kobj;

static int __init mntn_video_dev_init(void)
{
    int retval;

/*
* Create a simple kobject with the name of "mntn_video_dev",
* located under /sys/kernel/
*
* As this is a simple directory, no uevent will be sent to
* userspace.  That is why this function should not be used for
* any type of dynamic kobjects, where the name and number are
* not known ahead of time.
*/
    mntn_video_dev_kobj = kobject_create_and_add(KOBJECT_NAME, kernel_kobj);

    if (!mntn_video_dev_kobj){
        printk("["LOG_TAG"]""video_mntn_dev_kobj add fail");
        return -ENOMEM;
    }
    /* Create the files associated with this kobject */
    retval = sysfs_create_group(mntn_video_dev_kobj, &attr_group);

    if (retval){
        printk("["LOG_TAG"]""video_mntn_dev_kobj group fail.%d", retval);
        kobject_put(mntn_video_dev_kobj);
    }

    init_mntn_log_module();
    init_mntn_video_module();

    printk("["LOG_TAG"]""mntn_video_dev_kobj init ok\n");

    return retval;
}

static void __exit mntn_video_dev_exit(void)
{
     kobject_put(mntn_video_dev_kobj);
}

module_init(mntn_video_dev_init);
module_exit(mntn_video_dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("HW");
