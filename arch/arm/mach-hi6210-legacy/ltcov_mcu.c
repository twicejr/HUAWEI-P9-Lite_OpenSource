/*************************************************************************
*   版权所有(C) 1987-2010, 深圳华为技术有限公司.
*
*   文 件 名 :  ltcov_mcu.c
*
*   作    者 :  y00187525
*
*   描    述 :  本文件主要完成MCU 覆盖率数据写文件操作
*
*   修改记录 :  2012年12月07日  v1.00  yangguang  创建
*************************************************************************/

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

/*****************************************************************************
 函 数 名  : hutaf_save_data
 功能描述  : A核 保存HUTAF覆盖率数据到文件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月07日
    作    者   : 杨光 00187525
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : ltcov_hutaf_save_mcu_data
 功能描述  : 跨核调用M核获取HUTAF覆盖率数据的函数，返回后调用保存为文件函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月07日
    作    者   : 杨光 00187525
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : hutaf_init
 功能描述  : A核 HUTAF物理地址转换为虚拟地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月07日
    作    者   : 杨光 00187525
    修改内容   : 新生成函数

*****************************************************************************/

static int __init hutaf_init(void)
{
    buffer = (unsigned int*)ioremap(HUTAF_HLT_MEM_ADDR, HUTAF_HLT_MEM_SIZE);
}

subsys_initcall(hutaf_init);

#ifdef __cplusplus
}
#endif