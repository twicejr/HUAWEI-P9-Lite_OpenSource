/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_tele_mntn_common.h
  版 本 号   : 初稿
  作    者   : 李彬彬 00186593
  生成日期   : 2014年5月17日
  最近修改   :
  功能描述   : drv_tele_mntn_common.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月17日
    作    者   : 李彬彬 00186593
    修改内容   : 创建文件
  2.注    意   : 如下几个文件夹 .c .h 内容必须完全相同
                 vendor\hisi\confidential\lpmcu\driver\tele_mntn\
                 kernel\drivers\hisi\tele_mntn\

******************************************************************************/

#ifndef __DRV_TELE_MNTN_COMMON_H__
#define __DRV_TELE_MNTN_COMMON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "bsp_tele_mntn.h"


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#ifndef WIN32
#define local_t static
#else
#define local_t
#endif

#define bool_t  unsigned int
#define void_t  void

#define s8_t    char
#define s16_t   short
#define s32_t   int

#define u8_t    unsigned char
#define u16_t   unsigned short
#define u32_t   unsigned int
#define udy_t   unsigned long
#define u64_t   unsigned long long

#define BIT_32(x)  ((u32_t)(((u32_t)0x1)<<((u32_t)(x))))
#define BIT_64(x)  ((u64_t)(((u64_t)0x1)<<((u32_t)(x))))

#ifndef WIN32
#define TELE_MNTN_NULL              ((void*)0)
#else
#define TELE_MNTN_NULL              (0)
#endif
#define TELE_MNTN_IS_NULL(p)        (TELE_MNTN_NULL == (p))
#define TELE_MNTN_NOT_NULL(p)       (TELE_MNTN_NULL != (p))

#define TELE_MNTN_ERR_BASE                 (0x40000000)
#define TELE_MNTN_OK                       0
#define TELE_MNTN_ERRO                     (TELE_MNTN_ERR_BASE | BIT_32(1))
#define TELE_MNTN_ALREADY_INIT             (TELE_MNTN_ERR_BASE | BIT_32(2))
#define TELE_MNTN_NOT_INIT                 (TELE_MNTN_ERR_BASE | BIT_32(5))
#define TELE_MNTN_PARA_INVALID             (TELE_MNTN_ERR_BASE | BIT_32(6))
#define TELE_MNTN_MUTEX_VIRT_ADDR_NULL     (TELE_MNTN_ERR_BASE | BIT_32(7))
#define TELE_MNTN_PROTECT_ERR              (TELE_MNTN_ERR_BASE | BIT_32(8))
#define TELE_MNTN_USER_DATA_OVERFLOW       (TELE_MNTN_ERR_BASE | BIT_32(9))
#define TELE_MNTN_BUF_FULL                 (TELE_MNTN_ERR_BASE | BIT_32(10))
#define TELE_MNTN_WAKEUP_ACORE_SUCC        (TELE_MNTN_ERR_BASE | BIT_32(11))
#define TELE_MNTN_LOCK_FAIL                (TELE_MNTN_ERR_BASE | BIT_32(12))
#define TELE_MNTN_DDR_SELF_REFRESH         (TELE_MNTN_ERR_BASE | BIT_32(13))
#define TELE_MNTN_FUNC_OFF                 (TELE_MNTN_ERR_BASE | BIT_32(14))


/*a按p字节对齐*/
#define TELE_MNTN_ALIGN(a,p)               (((a)+((p)-1)) & ~((p)-1))
/*a按p字节截断对齐*/
#define TELE_MNTN_SHORTCUT_ALIGN(a,p)      ((a) & ~((p)-1))

/*记录log大小按8字节对齐*/
#define TELE_MNTN_ALIGN_SIZE               (sizeof(u64_t))

#define TELE_MNTN_LOCK_TIMEOUT             (1000)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    TELE_MNTN_BUF_CONTROLLABLE = 0xA,
    TELE_MNTN_BUF_INCONTROLLABLE,
}TELE_MNTN_BUF_TYPE;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern s32_t tele_mntn_common_init (void_t);
extern u64_t tele_mntn_func_sw_get (void_t);
extern u64_t tele_mntn_func_sw_set (u64_t sw);
extern u64_t tele_mntn_func_sw_bit_set (u32_t bit);
extern u64_t tele_mntn_func_sw_bit_clr (u32_t bit);











#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of drv_tele_mntn_common.h */
