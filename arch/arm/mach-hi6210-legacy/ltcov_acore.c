/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
  文 件 名   : ltcov_acore.c
  版 本 号   : 初稿
  作    者   : 杨光 00187525
  生成日期   : 2012年09月03日
  最近修改   :
  功能描述   : 通过HUTAF接口获取A核覆盖率数据，并写到文件中
  修改历史   :
  1.日    期   : 2012年09月03日
    作    者   : 杨光 00187525
    修改内容   : 创建文件

*******************************************************************************/

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

/*******************************************************************************
  3 函数声明
*******************************************************************************/
extern unsigned long HLLT_Agent_GetCovDataSize();
extern int HLLT_Coverage_GetCoverageData(unsigned int *pCovData, unsigned long ulLen);

/*******************************************************************************
  4 函数实现
*******************************************************************************/
void ltcov_hutaf_save_acore_data()
{	
	unsigned long len = 0;
	void* k_buffer=NULL;
	struct file *fd = NULL;
	int file_flag = O_RDWR | O_CREAT;
	unsigned long fs;
	
	len = HLLT_Agent_GetCovDataSize();
	k_buffer = kmalloc(len, GFP_KERNEL);
	
	if(NULL == k_buffer)
	{
		printk("ltcov_hutaf_save_acore_data:kmalloc error\n");
		goto ERROR;
	}

	/* 将覆盖率数据写到Buffer中 */
	if(1 != HLLT_Coverage_GetCoverageData(k_buffer, len))
	{
		printk("ltcov_hutaf_save_acore_data:HLLT_Coverage_GetCoverageData error\n");
		goto ERROR;
	}
	
	/* 改变内存空间访问权限 */
    fs = get_fs();
    set_fs(KERNEL_DS);

	/* 创建文件 */
	fd = filp_open("/data/ltcov_acore.bin", file_flag, 0666);
    if (IS_ERR(fd))
    {
        printk("ltcov_hutaf_save_acore_data:open ltcov_acore.bin file error\n");
        set_fs(fs);
        goto ERROR;
    }
	
	/* 写文件 */
	vfs_write(fd, k_buffer, len, &(fd->f_pos));

    kfree(k_buffer);
    filp_close(fd, NULL);
    set_fs(fs);
	return;
	
ERROR:
    if(k_buffer) 
	{
	    kfree(k_buffer);
		k_buffer = NULL;
	}
}

/* 将函数导入符号表 */
EXPORT_SYMBOL(ltcov_hutaf_save_acore_data);

