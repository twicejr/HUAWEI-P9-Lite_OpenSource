#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#ifdef	CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#endif

#include "video_mntn_kernel.h"

#define CMDLENTH 32

#define LOG_TAG "VIDEO_MNTN_PRINT"

#define CMD_SETPRINTLEVEL  "setlevel"
#define CMD_SETSAVE        "setsave"

#ifdef CONFIG_DEBUG_FS
#define VIDEO_MNTN_DIR_NAME         "mit2mntn"
#define VIDEO_MNTN_CFG_FILE         "config"
#define VIDEO_MNTN_MAXSIZE          (128)

struct dentry *video_mntn_dir = NULL;
#endif

STATIC void set_log_level(uint32_t module_id, uint32_t log_level)
{
    if ((module_id >= EN_ID_MNTN_LOG_MODULE_MAX)||(log_level >= EN_VIDEO_LOG_LEVEL_MAX)){
        printk("["LOG_TAG"]""param module_id[%d],log_level[%d] error\n", module_id, log_level);
        return;
    }

    g_mntn_log_module_id[module_id].log_level = log_level;
    pr_info("["LOG_TAG"]" "set module[%d].level:[%d]\n", \
        module_id,\
        g_mntn_log_module_id[module_id].log_level);
}

STATIC void show_log_level(void)
{
    uint32_t i = 0;
    uint32_t name_len = 0;

    pr_info("["LOG_TAG"]" "start %s\n", __FUNCTION__);

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
    pr_info("["LOG_TAG"]" "leave %s\n", __FUNCTION__);
}

STATIC void set_save_data(uint32_t module_id, uint32_t save_cnt, uint32_t save_type)
{
    if ((module_id >= EN_ID_MNTN_DATA_MODULE_ID_MAX)||(save_type >= 2)){
        printk("["LOG_TAG"]""param module_id[%d],save_type[%d] error\n", module_id, save_type);
        return;
    }

    g_mntn_video_save_data_module[module_id].FrameNum     = save_cnt;
    g_mntn_video_save_data_module[module_id].ImageOrVideo = save_type;

    pr_info("["LOG_TAG"]" "set module[%d], FrameNum:[%d], SaveType:[%d]\n",
            module_id,
            g_mntn_video_save_data_module[module_id].FrameNum,
            g_mntn_video_save_data_module[module_id].ImageOrVideo);
}

STATIC void show_save(void)
{
    uint32_t i = 0;
    uint32_t name_len = 0;

    pr_info("["LOG_TAG"]" "start %s\n", __FUNCTION__);

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
    pr_info("["LOG_TAG"]" "leave %s\n", __FUNCTION__);
}

#ifdef CONFIG_DEBUG_FS
/*
 **************************************************************************
 * FunctionName: video_mntn_cfg_open;
 * Description : open video mntn file
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int video_mntn_cfg_open(struct inode *inode, struct file *filp)
{
    pr_info("enter %s.\n", __func__);
    filp->private_data = inode->i_private;
    return 0;
}

/*
 **************************************************************************
 * FunctionName: video_mntn_cfg_read;
 * Description : get video mntn param
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static ssize_t video_mntn_cfg_read(struct file *filp, char __user *buffer,
    size_t count, loff_t *ppos)
{
    char tips[CMDLENTH] = "help!\n";

    if (*ppos >= CMDLENTH)
        return 0;

    if (*ppos +count > CMDLENTH) {
        count = CMDLENTH - *ppos;
    }

    if (copy_to_user(buffer, tips + *ppos, count)) {
        return -EFAULT;
    }

    *ppos += count;

    show_log_level();
    show_save();

    return count;
}

/*
 **************************************************************************
 * FunctionName: video_mntn_cfg_write;
 * Description : set video mntn param
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static ssize_t video_mntn_cfg_write(struct file *filp, const char __user *buffer,
    size_t count, loff_t *ppos)
{
    char cmd_buf[VIDEO_MNTN_MAXSIZE];
    char cmd_name[CMDLENTH];
    int  ret           = 0;
    uint32_t module_id = -1;
    uint32_t param1    = -1;
    uint32_t param2    = -1;

    pr_info("enter %s.\n", __func__);

    if (count > VIDEO_MNTN_MAXSIZE) {
        printk("["LOG_TAG"]""set video mntn param failed! input format error: %s.", buffer);
        printk("["LOG_TAG"]""format should be: echo %s [module_id],[level] > video_mntn\n", CMD_SETPRINTLEVEL);
        printk("["LOG_TAG"]""             or : echo %s [module_id],[count],[type] > video_mntn\n", CMD_SETSAVE);
        return -EFAULT;
    }

    memset(cmd_buf, 0, VIDEO_MNTN_MAXSIZE);
    memset(cmd_name, 0, CMDLENTH);

    if (copy_from_user(cmd_buf, buffer, count)) {
        return -EFAULT;
    }
    pr_info("%s, length = %d, %s", __func__, count, cmd_buf);

    ret = sscanf(cmd_buf, "%s %d,%d,%d", cmd_name, &module_id, &param1, &param2);  /* [false alarm] kernel中的sscanf没有对应的安全函数  */

    if ((3 == ret) && (0 == strcmp(cmd_name, CMD_SETPRINTLEVEL))) {
        set_log_level(module_id, param1);
        printk("%s, module = %d, level = %d.\n", __func__, module_id, param1);
    } else if ((4 == ret) && (0 == strcmp(cmd_name, CMD_SETSAVE))) {
        set_save_data(module_id, param1, param2);
        printk("%s, module = %d, count = %d, type = %d.\n", __func__, module_id, param1, param2);
    } else {
        printk("["LOG_TAG"]""set video mntn param failed! input format error: %s.", buffer);
        printk("["LOG_TAG"]""format should be: echo %s [module_id],[level] > video_mntn\n", CMD_SETPRINTLEVEL);
        printk("["LOG_TAG"]""             or : echo %s [module_id],[count],[type] > video_mntn\n", CMD_SETSAVE);
    }

    return count;
}

struct file_operations video_mntn_cfg_fops = {
    .open = video_mntn_cfg_open,
    .read = video_mntn_cfg_read,
    .write = video_mntn_cfg_write,
};

#endif

static int __init mntn_video_dev_init(void)
{
/*
* Create a simple debugfs node with the name of "mit2mntn",
* located under /sys/kernel/debug/
*/

#ifdef CONFIG_DEBUG_FS
    video_mntn_dir = debugfs_create_dir(VIDEO_MNTN_DIR_NAME, NULL);
    if (ERR_PTR(-ENODEV) == video_mntn_dir) {
        printk("debugfs_create_dir create dir %s failed!\n", VIDEO_MNTN_DIR_NAME);
        return -EINVAL;
    }

    debugfs_create_file(VIDEO_MNTN_CFG_FILE, 0664, video_mntn_dir, NULL, &video_mntn_cfg_fops);

    pr_info("["LOG_TAG"]""mit2 mntn_video_dev debugfs init ok\n");
#endif

    init_mntn_log_module();
    init_mntn_video_module();

    return 0;
}

static void __exit mntn_video_dev_exit(void)
{
#ifdef CONFIG_DEBUG_FS
    debugfs_remove_recursive(video_mntn_dir);
    video_mntn_dir = NULL;
#endif

    return;
}

module_init(mntn_video_dev_init);
module_exit(mntn_video_dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("HW");
