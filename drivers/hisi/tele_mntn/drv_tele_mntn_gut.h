/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_tele_mntn_gut.h
  版 本 号   : 初稿
  作    者   : 李彬彬 00186593
  生成日期   : 2014年4月1日
  最近修改   :
  功能描述   : drv_tele_mntn_gut.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月1日
    作    者   : 李彬彬 00186593
    修改内容   : 创建文件
  2.注    意   : 如下几个文件夹 .c .h 内容必须完全相同
                 vendor\hisi\confidential\lpmcu\driver\tele_mntn\
                 kernel\drivers\hisi\tele_mntn\

******************************************************************************/

#ifndef __DRV_TELE_MNTN_GUT_H__
#define __DRV_TELE_MNTN_GUT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "drv_tele_mntn_common.h"
#include  "drv_tele_mntn_platform.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*#define TELE_MNTN_DEBUG_SW*/
#undef TELE_MNTN_DEBUG_SW

#ifdef TELE_MNTN_DEBUG_SW
#define TELE_MNTN_DISCARD_SLICE_BUF_NUM (64)           /*必须为2的n次幂*/
#define TELE_MNTN_WUACORE_SLICE_BUF_NUM (64)           /*必须为2的n次幂*/
#endif

#define TELE_MNTN_PROTECT1              (0x55AA55AA)
#define TELE_MNTN_PROTECT2              (0x5A5A5A5A)
#define TELE_MNTN_PROTECT_LEN           (u32_t)(sizeof(u32_t)) /* 邮箱保护字长度，单位byte，邮箱头及邮箱头、尾均有两个这样的保护字 */
#define TELE_MNTN_PROTECT               (0x43415254)    /*TRAC*/

#define TELE_MNTN_INIT_MAGIC            (0x20140407)
#define TELE_MNTN_VALID_MAGIC           (0x20142137)

#define TELE_MNTN_HEAD_SIZE             (u32_t)(sizeof(struct tele_mntn_head))
#define TELE_MNTN_DATA_SIZE             (u32_t)(sizeof(struct tele_mntn_data))

#define TELE_MNTN_SECOND_TO_SLICE(s)    ((s)*32768)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/
typedef struct tele_mntn_head
{
    u32_t protect_word1;     /*保护字 0x55AA55AA*/
    u32_t front;             /*队列待写单元距离队列(不含保护字)头的长度，单位32bit */
    u32_t rear;              /*队列待读单元距离队列(不含保护字)头的长度，单位32bit */
    u32_t protect_word2;     /*保护字 0x55AA55AA*/
} TELE_MNTN_HEAD_STRU;

typedef struct tele_mntn_data
{
    u32_t protect;
    u32_t type_id:7;
    u32_t len:7;
    u32_t idex:16;
    u32_t cpu_id:2;
    u32_t rtc;
    u32_t slice;
}TELE_MNTN_DATA_STRU;
/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

typedef struct tele_mntn_cfg
{
    u64_t data_addr;   /*内存地址*/
    u32_t data_size;   /*大小*/
    u32_t wake_threshold;
    u32_t wake_interval_threshold;/*两次唤醒的时间间隔，单位 s*/
    u32_t user_data_threshold;
    u32_t ipc_int_num;
    u32_t global_lock_num;
}TELE_MNTN_CFG_STRU;

#ifdef TELE_MNTN_DEBUG_SW
typedef struct tele_mntn_debug
{
    u32_t discard_num;
    u32_t discard_silce[TELE_MNTN_DISCARD_SLICE_BUF_NUM];
    u32_t wakeup_accore_num;
    u32_t wakeup_accore_silce[TELE_MNTN_WUACORE_SLICE_BUF_NUM];
    u32_t peak_left_size;
    u32_t peak_left_slice;
}TELE_MNTN_DEBUG_STRU;
#endif

typedef struct tele_mntn_handle
{
    u32_t init_flag;
    u32_t idex;
    u8_t* data_virt_addr;
    u32_t prior_wakeup_acore_slice;
#ifdef TELE_MNTN_DEBUG_SW
    struct tele_mntn_debug debug;
#endif
    struct tele_mntn_head head;
    struct tele_mntn_queue queue;
    struct tele_mntn_data data;
#if defined (CONFIG_TELE_MNTN_CORE_APP)
    spinlock_t local_lock;
    udy_t local_flag;
    u8_t *global_lock;
    udy_t global_flag;
#else
    u32_t local_lock;
    u32_t local_flag;
    u32_t global_lock;
    u32_t global_flag;
#endif
}TELE_MNTN_HANDLE;


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
extern s32_t tele_mntn_init_cfg(void_t);
extern s32_t tele_mntn_write_buf(const TELE_MNTN_DATA_STRU *head_data, const void_t * data, u32_t len, TELE_MNTN_BUF_TYPE buf_type);
#ifdef TELE_MNTN_DEBUG_SW
extern void_t tele_mntn_debug_out(void_t);
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of drv_tele_mntn_gut.h */
