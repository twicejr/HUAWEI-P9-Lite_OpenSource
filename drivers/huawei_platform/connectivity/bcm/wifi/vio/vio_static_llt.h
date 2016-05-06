/******************************************************************************
   版权所有 (C), 2001-2015, 华为技术有限公司

/******************************************************************************
  文件名          :
  版本号          : 1.0
  作者                : K 项目组
  生成日期     : 2015-10-26
  最近修改     :
  功能描述     : VIO LLT测试用例
  函数列表     :
  修改历史     :
  日期                : 2015-10-26
  作者                : s00163283
    修改内容      : 生成
*******************************************************************************/
#ifndef _VIO_STATIC_LLT_H
#define _VIO_STATIC_LLT_H

#ifdef __cplusplus
extern "C" {
#endif

struct LLT_TEST {
	int (*vio_dev_ioctl)(struct file *filp, int cmd, int arg);
	int (*vio_dev_init)(void);
	void (*vio_dev_exit)(void);
};

#ifdef __cplusplus
}
#endif
#endif
