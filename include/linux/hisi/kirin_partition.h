/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : kirin_partition.h
  版 本 号   : 初稿
  作        者   : denghao 00221160
  生成日期   : 2015年11月3日
  最近修改   :
  功能描述   : mmc_partition.h 的头文件
  函数列表   :
  修改历史   :
  日    期   : 2015年11月3日
  作    者   : denghao 00221160
  修改内容   : 创建文件

******************************************************************************/
#ifndef __KIRIN_PARTITION__
#define __KIRIN_PARTITION__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern int flash_find_ptn(const char* str, char* pblkname);
extern int get_cunrrent_total_ptn_num(void);
extern unsigned int flash_get_ptn_index(const char* pblkname);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

