#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/printk.h>
#include <linux/huawei/hw_connectivity.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/stat.h>
#include <linux/of.h>

#define DTS_COMP_HW_CONNECTIVITY_NAME "huawei,hw_connectivity"
#define DTS_COMP_HISI_NFC_NAME "hisilicon,hisi_nfc"
#define HW_CONN_PROC_DIR "connectivity"
#define HW_CONN_PROC_CHIPTYPE_FILE "chiptype"
#define HW_CONN_PROC_NFC_CHIPTYPE_FILE "nfc_chiptype"

#define CHIP_TYPE_LEN       (129)

/* global variables */
static char g_chip_type[CHIP_TYPE_LEN] = {0};
static char g_nfc_chip_type[CHIP_TYPE_LEN] = {0};


static ssize_t hwconn_read_proc_chiptype(struct file *filp, const char __user *buffer, size_t len, loff_t *off)
{
    printk(KERN_INFO "[HW_CONN] hwconn_read_proc_chiptype\n");
    if (len < 1 || NULL == g_chip_type) {
        printk(KERN_ERR "[HW_CONN] hwconn_read_proc_chiptype g_chip_type is NULL or read length = 0.\n");
        return -EINVAL;
    }

    printk(KERN_INFO "[HW_CONN] hwconn_read_proc_chiptype off = %d\n", (unsigned long)*off);
    if ((unsigned long)*off > 0) {
        return 0;
    }

    printk(KERN_INFO "[HW_CONN] chip type[%s] \n", g_chip_type);

    len = strlen(g_chip_type);
    if (len <= 0) {
        printk(KERN_ERR "[HW_CONN] hwconn_read_proc_chiptype g_chip_type is blank\n");
        return 0;
    }
    if (copy_to_user(buffer, g_chip_type, len)) {
        printk(KERN_ERR "[HW_CONN] hwconn_read_proc_chiptype copy_to_user failed!\n");
        return -EFAULT;
    }
    *off += len;
    return len;
}

static const struct file_operations hwconn_proc_fops_chiptype= {
   .owner = THIS_MODULE,
   .read = hwconn_read_proc_chiptype,
};

static ssize_t hwconn_read_proc_nfc_chiptype(struct file *filp, const char __user *buffer, size_t len, loff_t *off)
{
    printk(KERN_INFO "[HW_CONN] hwconn_read_proc_nfc_chiptype\n");
    if (len < 1 || NULL == g_nfc_chip_type)
    {
        printk(KERN_ERR "[HW_CONN] hwconn_read_proc_nfc_chiptype g_nfc_chip_type is NULL or read length = 0.\n");
        return -EINVAL;
    }

    printk(KERN_INFO "[HW_CONN] hwconn_read_proc_nfc_chiptype off = %d\n", (unsigned long)*off);
    if ((unsigned long)*off > 0)
    {
        return 0;
    }

    printk(KERN_INFO "[HW_CONN] nfc chip type[%s] \n", g_nfc_chip_type);

    len = strlen(g_nfc_chip_type);
    if (len <= 0)
    {
        printk(KERN_ERR "[HW_CONN] hwconn_read_proc_nfc_chiptype g_nfc_chip_type is blank\n");
        return 0;
    }

    if (copy_to_user(buffer, g_nfc_chip_type, len))
    {
        printk(KERN_ERR "[HW_CONN] hwconn_read_proc_nfc_chiptype copy_to_user failed!\n");
        return -EFAULT;
    }
    *off += len;
    return len;
}

static const struct file_operations hwconn_proc_fops_nfc_chiptype= {
   .owner = THIS_MODULE,
   .read = hwconn_read_proc_nfc_chiptype,
};

static int create_hwconn_proc_file(void)
{
    int ret = 0;
    struct proc_dir_entry *hwconn_dir = NULL;
    struct proc_dir_entry *hwconn_chiptype_file = NULL;

    hwconn_dir = proc_mkdir(HW_CONN_PROC_DIR, NULL);
    if (!hwconn_dir)
    {
        printk(KERN_ERR "[HW_CONN] proc dir create failed\n");
        ret = -ENOMEM;
        return ret;
    }

    hwconn_chiptype_file = proc_create(HW_CONN_PROC_CHIPTYPE_FILE, S_IRUGO, hwconn_dir, &hwconn_proc_fops_chiptype);
    if (!hwconn_chiptype_file)
    {
        printk(KERN_ERR "[HW_CONN] proc chiptype file create failed\n");
        ret = -ENOMEM;
        return ret;
    }

    hwconn_chiptype_file = proc_create(HW_CONN_PROC_NFC_CHIPTYPE_FILE, S_IRUGO, hwconn_dir, &hwconn_proc_fops_nfc_chiptype);
    if (!hwconn_chiptype_file)
    {
        printk(KERN_ERR "[HW_CONN] proc nfc chiptype file create failed\n");
        ret = -ENOMEM;
        return ret;
    }

    printk(KERN_INFO "[HW_CONN] hwconn create proc file ok.\n");

    return ret;
}

static int read_chip_type_from_dts(char *buf, int buf_len) {
    struct device_node *np;
    char *chiptype = NULL;
    int ret = 0;

    if (!buf || buf_len <= 0) {
        printk(KERN_ERR "[HW_CONN] invalid input parameters in %s\n", __func__);
        return -EINVAL;
    }

    np = of_find_compatible_node(NULL, NULL, DTS_COMP_HW_CONNECTIVITY_NAME); // should be the same as dts node compatible property
    if (np == NULL) {
        /* if read fail, default is broadcom */
        printk(KERN_ERR "Unable to find hw_connectivity, using default\n");
        strncpy(buf, CHIP_TYPE_BCM, (buf_len - 1));
        return 0;
    }

    ret = of_property_read_string(np, "chip_type", &chiptype);
    if (ret < 0 || chiptype == NULL) {
        /* if read fail, default is broadcom */
        printk(KERN_ERR "[HW_CONN] %s: get chiptype failed, ret:%d, using default\n", __func__, ret);
        strncpy(buf, CHIP_TYPE_BCM, (buf_len - 1));
        ret = 0;
    } else {
        printk(KERN_ERR "[HW_CONN] %s:  chip_type :%s\n", __func__, chiptype);
        strncpy(buf, chiptype, (buf_len - 1));
    }

    return ret;
}

static int read_nfc_chip_type_from_dts(char *buf, int buf_len)
{
    struct device_node *np;
    char *chiptype = NULL;
    int ret = 0;

    if (!buf || buf_len <= 0)
    {
        printk(KERN_ERR "[HW_CONN] invalid input parameters in %s\n", __func__);
        return -EINVAL;
    }

    np = of_find_compatible_node(NULL, NULL, DTS_COMP_HISI_NFC_NAME); // should be the same as dts node compatible property
    if (np == NULL)
    {
        /* if read fail, default is nxp */
        printk(KERN_ERR "Unable to find hisi_nfc, nfc chip type using default\n");
        strncpy(buf, NFC_CHIP_TYPE_NXP, (buf_len - 1));
        return 0;
    }

    ret = of_property_read_string(np, "hisi_nfc_chip_type", &chiptype);
    if (ret < 0 || chiptype == NULL)
    {
        /* if read fail, default is nxp */
        printk(KERN_ERR "[HW_CONN] %s: get nfc chiptype failed, ret:%d, using default\n", __func__, ret);
        strncpy(buf, NFC_CHIP_TYPE_NXP, (buf_len - 1));
        ret = 0;
    }
    else
    {
        printk(KERN_ERR "[HW_CONN] %s:  nfc_chip_type :%s\n", __func__, chiptype);
        strncpy(buf, chiptype, (buf_len - 1));
    }

    return ret;
}

static int hw_connectivity_probe(struct platform_device *pdev)
{
    int ret = 0;

    printk(KERN_INFO "[HW_CONN] start find hw_connectivity\n");
    memset((void*)g_chip_type, 0, sizeof(g_chip_type));
    memset((void*)g_nfc_chip_type, 0, sizeof(g_nfc_chip_type));

    ret = read_chip_type_from_dts(g_chip_type, sizeof(g_chip_type));
    if (ret < 0)
    {
        printk(KERN_ERR "[HW_CONN] %s: get chiptype failed, ret:%d.\n", __func__, ret);
        goto err_free;
    }
    else
    {
        printk(KERN_ERR "[HW_CONN] %s:  chip_type :%s\n", __func__, g_chip_type);
    }

    ret = read_nfc_chip_type_from_dts(g_nfc_chip_type, sizeof(g_nfc_chip_type));
    if (ret < 0)
    {
        printk(KERN_ERR "[HW_CONN] %s: get nfc chiptype failed, ret:%d.\n", __func__, ret);
        goto err_free;
    }
    else
    {
        printk(KERN_ERR "[HW_CONN] %s:  nfc_chip_type :%s\n", __func__, g_nfc_chip_type);
    }

    ret = create_hwconn_proc_file();
    if (ret) {
        printk(KERN_ERR "[HW_CONN] create proc file failed.\n");
        goto err_free;
    }

    return 0;

err_free:
    memset((void*)g_chip_type, 0, sizeof(g_chip_type));
    memset((void*)g_nfc_chip_type, 0, sizeof(g_nfc_chip_type));
    return ret;
}

static void hw_connectivity_shutdown(struct platform_device *pdev)
{
    printk(KERN_INFO "[HW_CONN] hw_connectivity_shutdown!\n");

    memset((void*)g_chip_type, 0, sizeof(g_chip_type));
    memset((void*)g_nfc_chip_type, 0, sizeof(g_nfc_chip_type));

    return;
}

static const struct of_device_id hw_connectivity_match_table[] = {
    {
        .compatible = DTS_COMP_HW_CONNECTIVITY_NAME,   // compatible must match with which defined in dts
        .data = NULL,
    },
    {
    },
};

static struct platform_driver hw_connectivity_driver = {
    .probe          = hw_connectivity_probe,
    .suspend        = NULL,
    .remove         = NULL,
    .shutdown       = hw_connectivity_shutdown,
    .driver = {
        .name = "huawei,hw_connectivity",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(hw_connectivity_match_table), // dts required code
    },
};

static int __init hw_connectivity_init(void)
{
    printk(KERN_ERR "[HW_CONN] hw_connectivity_init enter\n");
    return platform_driver_register(&hw_connectivity_driver);
}

static void __exit hw_connectivity_exit(void)
{
    platform_driver_unregister(&hw_connectivity_driver);
}

bool isMyConnectivityChip(char* name) {
    char tmp[CHIP_TYPE_LEN] = {0};

    if (!name || strlen(name) <= 0) {
        printk(KERN_ERR "[HW_CONN] invalid input parameters in %s\n", __func__);
        return false;
    }

    memset((void*)tmp, 0, sizeof(tmp));
    if (strlen(g_chip_type) > 0) {
        printk(KERN_INFO "[HW_CONN] g_chip_type is %s\n", g_chip_type);
        strncpy(tmp, g_chip_type, (CHIP_TYPE_LEN - 1));
    } else {
        read_chip_type_from_dts(tmp, sizeof(tmp));
    }

    if (strlen(tmp) > 0) {
        if (!strcmp(tmp, name)) {
            return true;
        }
    } else {
        printk(KERN_ERR "[HW_CONN] can not get valid current chiptype\n");
    }

    return false;
}

bool isMyNfcChip(char* name)
{
    char tmp[CHIP_TYPE_LEN] = {0};

    if (!name || strlen(name) <= 0)
    {
        printk(KERN_ERR "[HW_CONN] invalid input parameters in %s\n", __func__);
        return false;
    }

    memset((void*)tmp, 0, sizeof(tmp));
    if (strlen(g_nfc_chip_type) > 0)
    {
        printk(KERN_INFO "[HW_CONN] g_nfc_chip_type is %s\n", g_nfc_chip_type);
        strncpy(tmp, g_nfc_chip_type, (CHIP_TYPE_LEN - 1));
    }
    else
    {
        read_nfc_chip_type_from_dts(tmp, sizeof(tmp));
    }

    if (strlen(tmp) > 0)
    {
        if (!strcmp(tmp, name))
        {
            return true;
        }
    }
    else
    {
        printk(KERN_ERR "[HW_CONN] can not get valid current chiptype\n");
    }

    return false;
}

EXPORT_SYMBOL(isMyConnectivityChip);
EXPORT_SYMBOL(isMyNfcChip);

module_init(hw_connectivity_init);
module_exit(hw_connectivity_exit);

MODULE_AUTHOR("DRIVER_AUTHOR");
MODULE_DESCRIPTION("Huawei connectivity OneTrack driver");
MODULE_LICENSE("GPL");
