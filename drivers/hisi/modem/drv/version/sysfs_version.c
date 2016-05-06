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

#include <linux/device.h>
#include <linux/stat.h>
#include "bsp_version.h"

/*****************************************************************************
* 函 数 名  : show_product_version
*
* 功能描述  : 获取PRODUCT_FULL_VERSION_STRING
*
*****************************************************************************/
static ssize_t show_product_version(struct device *cdev,struct device_attribute *attr,char *buf)
{
       /* coverity[secure_coding] */
	return sprintf(buf,"%s\n",bsp_version_get_release());
}
static DEVICE_ATTR(product_version, S_IRUSR,show_product_version, NULL);

static struct device_attribute *version_attr[]={
    &dev_attr_product_version,
    NULL
};

struct device version_dev={
    .init_name="version",
};

int __init version_sysfs_init(void)
{
	int ret=0;
	int i=0,j=0;

	ret=device_register(&version_dev);
	if(ret<0){
		printk("Error:register version_dev device fail\n");
		goto err_out;
	}

	for(i=0;version_attr[i];i++)
	{
		ret=device_create_file(&version_dev, version_attr[i]);
		if(ret)
		    goto err_out;
	}

	return 0;

err_out:
	for(j=0;j<i;j++)
	    device_remove_file(&version_dev,version_attr[j]);
	device_del(&version_dev);
	return -1;
}

void __exit version_sysfs_exit(void)
{
	device_del(&version_dev);
}

module_init(version_sysfs_init);
module_exit(version_sysfs_exit);

