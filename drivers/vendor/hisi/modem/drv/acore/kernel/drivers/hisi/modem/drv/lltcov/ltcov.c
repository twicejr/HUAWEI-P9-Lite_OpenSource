/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

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
extern unsigned long HLLT_Agent_GetCovDataSize_drivers();
extern int HLLT_Coverage_GetCoverageData_drivers(unsigned int *pCovData, unsigned long ulLen);

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
	int testdata[100]={0};
	int i;
	for(i=0; i<50; i++)
	{
	testdata[i]=i+1;
	}
	len = HLLT_Agent_GetCovDataSize_drivers();
	k_buffer = kmalloc(len, GFP_KERNEL);
	
	if(NULL == k_buffer)
	{
		printk("ltcov_hutaf_save_acore_data:kmalloc error\n");
		goto ERROR;
	}

	/* 将覆盖率数据写到Buffer中 */
	if(1 != HLLT_Coverage_GetCoverageData_drivers(k_buffer, len))
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
        printk("ltcov_hutaf_save_acore_data:open ltcov.bin file error\n");
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

