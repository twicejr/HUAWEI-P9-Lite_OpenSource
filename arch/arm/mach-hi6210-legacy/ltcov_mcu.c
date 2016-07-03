

/*******************************************************************************
  1 头文件包含
*******************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/debugfs.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/io.h>
#include "MemoryMap.h"
#include "bsp_mailbox.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  2 变量定义
*****************************************************************************/

static unsigned int *buffer;

/*******************************************************************************
  3 函数实现
*******************************************************************************/


long  hutaf_save_data(int len)
{
    struct file *fd = NULL;
    int file_flag = O_RDWR | O_CREAT;
    unsigned long fs;

    if((void *)0 == buffer) {
        printk("hutaf_save_data buffer is 0 \n");
        return 0;
    }

    /* 改变内存空间访问权限 */
    fs = get_fs();
    set_fs(KERNEL_DS);

    /* 创建文件 */
    fd = filp_open("/data/ltcov_mcu.bin", file_flag, 0666);
    if (IS_ERR(fd))
    {
        printk("hutaf_save_data:open ltcov_mcu.bin file error\n");
        set_fs(fs);
        return 0;
    }

    /* 写文件 */
    vfs_write(fd, buffer, len, &(fd->f_pos));
    filp_close(fd, NULL);
    set_fs(fs);
    return 0;
}


IFC_GEN_EXEC1(hutaf_save_data, IFC_INCNT, int , len, 0)

IFC_GEN_CALL0(MAILBOX_IFC_ACPU_TO_MCU_HUTAF_HLT, ltcov_hutaf_get_mcu_data)

void ltcov_hutaf_save_mcu_data(void)
{
    unsigned int ret;

    memset(buffer, 0, HUTAF_HLT_MEM_SIZE);

    mailbox_ifc_register(MAILBOX_IFC_MCU_TO_ACPU_HUTAF_HLT, hutaf_save_data);

    /* call IFC function in Mcu */
    ret = ltcov_hutaf_get_mcu_data(0);
    if(ret) {
        printk("MB_IFC_CommCall call hutaf_save_data failed \n");
        return;
    }
    return;
}
EXPORT_SYMBOL(ltcov_hutaf_save_mcu_data);



static int __init hutaf_init(void)
{
    buffer = (unsigned int*)ioremap(HUTAF_HLT_MEM_ADDR, HUTAF_HLT_MEM_SIZE);
}

subsys_initcall(hutaf_init);

#ifdef __cplusplus
}
#endif