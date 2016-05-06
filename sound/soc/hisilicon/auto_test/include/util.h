/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : util.h
  版 本 号   : 初稿
  作    者   : 王秉达 00262566
  生成日期   : 2015年1月23日
  最近修改   :
  功能描述   : 提供自动化测试公共函数
  函数列表   :
  修改历史   :
  1.日    期   : 2015年1月23日
    作    者   : 王秉达 00262566
    修改内容   : 创建文件

******************************************************************************/
#ifndef _AUDIO_AUTO_TEST_UTIL_H
#define _AUDIO_AUTO_TEST_UTIL_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include <linux/mm.h>
#include <linux/vmalloc.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define AT_SUCCESS  0
#define AT_FAILED  -1

#define at_util_mem_remap_writecombine(phys_addr, size)  at_util_mem_remap_type(phys_addr, size, pgprot_writecombine(PAGE_KERNEL))

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/* 寄存器类型 */
enum at_util_reg_type{
    WO = 0,
    RO,
    RW,
    RC,
    WC,
    RWC,
};

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/

/* 寄存器定义 */
typedef struct at_util_reg_test_type
{
    unsigned int                        offset;                                 /* 寄存器偏移   */
    enum at_util_reg_type               rt;                                     /* 寄存器类型   */
    unsigned int                        default_value;                          /* 寄存器默认值 */
    unsigned int                        value;                                  /* 寄存器值     */
    unsigned int                        expect_value;                           /* 寄存器期望值 */
}AT_REG_TEST_TYPE;

/*****************************************************************************
  5 函数指针
*****************************************************************************/


/*****************************************************************************
  6 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/


extern unsigned int at_util_reg_read_u32    (unsigned int pAddr);
extern void         at_util_reg_write_u32   (unsigned int pAddr, unsigned int value);
extern void        *at_util_mem_remap_type  (unsigned long phys_addr, size_t size, pgprot_t pgprot);
extern int          at_util_reg_test        (struct at_util_reg_test_type regs[], int size,
                                                int (*reg_read)     (unsigned int reg),
                                                void(*reg_write)    (unsigned int reg, unsigned int value));
extern struct file *at_util_log_file_open   (char *path, char *file_name);
extern int          at_util_log_file_close  (void);
extern int          at_util_log             (void *data_addr,unsigned int data_len);
extern void        *at_util_mem_remap_and_init (unsigned int phys_addr, size_t size,
                                                unsigned int init_value);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of _AUDIO_AUTO_TEST_UTIL_H */


