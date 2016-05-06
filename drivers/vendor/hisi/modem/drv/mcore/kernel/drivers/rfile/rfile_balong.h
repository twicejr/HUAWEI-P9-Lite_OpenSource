/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : rfile_balong.h
  版 本 号   : 初稿
  作    者   : c64416
  生成日期   : 2013年2月4日
  最近修改   :
  功能描述   : 远程文件系统头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月4日
    作    者   : c64416
    修改内容   : 创建文件

******************************************************************************/

#ifndef __RFILE_BALONG_H__
#define __RFILE_BALONG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifdef __KERNEL__

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/personality.h>
#include <linux/stat.h>
#include <linux/unistd.h>
#include <linux/types.h>
#include <linux/dirent.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/fs.h>
#include <linux/statfs.h>
#include <linux/rcupdate.h>
#include <linux/hrtimer.h>
#include <linux/kthread.h>

#elif defined(__VXWORKS__)

#include <stdio.h>
#include <stdlib.h>
#include <stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <semLib.h>

#elif defined(__CMSIS_RTOS)

#include <stdlib.h>
#include <cmsis_os.h>
#include <printk.h>
#include <string.h>

#endif /* end of __KERNEL__ */

#include "drv_comm.h"
#include "osl_types.h"
#include "osl_sem.h"
#include "bsp_icc.h"
#include "bsp_rfile.h"


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define RFILE_TIMEOUT_MAX           (2000)           /* 最长等待2s */
#define RFILE_WAIT_FOREVER          (-1)

#define RFILE_MCORE_ICC_RD_CHAN     (ICC_CHN_MCORE_ACORE<<16 | MCU_ACORE_RFILE)
#define RFILE_MCORE_ICC_WR_CHAN     (ICC_CHN_MCORE_ACORE<<16 | MCU_ACORE_RFILE)

#define RFILE_ICC_PACKET_HEAD_LEN   ICC_CHANNEL_PAYLOAD


#ifdef __KERNEL__

typedef struct semaphore        rfile_sem_id;

#define Rfile_Malloc(size)      kmalloc(size, GFP_KERNEL)

#define Rfile_Free(ptr)         kfree(ptr)


#define RFILE_SLEEP(msecs)      msleep(msecs)

#elif defined(__VXWORKS__)

typedef  SEM_ID*                rfile_sem_id;

#define Rfile_Malloc(size)      malloc(size)

#define Rfile_Free(ptr)         free(ptr)

#define RFILE_TASK_STACK_SIZE   (0x1000)        /* TODO: */

#define RFILE_SLEEP(msecs)      taskDelay(msecs / 10)

#elif defined(__CMSIS_RTOS)

#define RFILE_LEN_MAX               (0x00000400 - RFILE_ICC_PACKET_HEAD_LEN)

/* RFILE模块写操作依赖于ICC的最大长度 */
#define RFILE_WR_LEN_MAX            (0x00000400 - RFILE_ICC_PACKET_HEAD_LEN - sizeof(struct bsp_rfile_write_req))

typedef  osSemaphoreId          rfile_sem_id;

struct list_head {
	struct list_head *next, *prev;
};

#define Rfile_Malloc(size)      malloc(size)

#define Rfile_Free(ptr)         free(ptr)

#endif /* end of __KERNEL__ */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 操作类型 */
enum _BSP_RFILE_OP_EN
{
    EN_RFILE_OP_OPEN = 0,
    EN_RFILE_OP_CLOSE,
    EN_RFILE_OP_WRITE,
    EN_RFILE_OP_WRITE_SYNC,
    EN_RFILE_OP_READ,
    EN_RFILE_OP_SEEK,
    EN_RFILE_OP_TELL,
    EN_RFILE_OP_REMOVE,
    EN_RFILE_OP_MKDIR,
    EN_RFILE_OP_RMDIR,
    EN_RFILE_OP_OPENDIR,
    EN_RFILE_OP_READDIR,
    EN_RFILE_OP_CLOSEDIR,
    EN_RFILE_OP_STAT,
    EN_RFILE_OP_ACCESS,
    EN_RFILE_OP_MASSRD,
    EN_RFILE_OP_MASSWR,
    EN_RFILE_OP_BUTT
};

/* 处理状态 */
enum bsp_rfile_state_en
{
    EN_RFILE_IDLE = 0,      /* 待处理 */
    EN_RFILE_DOING,         /* 正在处理 */
    EN_RFILE_DONE           /* 处理结束 */
};

/* 错误类型，用于RFILE内部可维可测 */
enum bsp_rfile_err_en
{
    EN_RFILE_ERR_SUCCESS = 0,       /* success */
    EN_RFILE_ERR_PARA_INVALID,      /* invalid parameter */
    EN_RFILE_ERR_MALLOC,            /* malloc failed */
    EN_RFILE_ERR_TIMEOUT,           /* timeout */
    EN_RFILE_ERR_LEN,               /* length error */
    EN_RFILE_ERR_ICC,               /* icc process failed */
    EN_RFILE_ERR_BUTT               /* other failure */
};

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/* 主控信息 */
struct bsp_rfile_main_stru
{
    bool                    bInitFlag;
    s32                     ret;
    rfile_sem_id            semAll;     /* 阻塞信号量 */
    rfile_sem_id            semReq;     /* 请求信号量 */
};


struct bsp_rfile_common_cnf
{
    u32                     opType;
    struct list_head        *pstlist;
    s32                     errorno;
    s32                     ret;
};

/* open====================================================================*/
struct bsp_rfile_open_req
{
    u32                     opType;
    struct list_head        *pstlist;
    s32                     mode;
    s32                     flags;
    s32                     nameLen;
    u8                      aucData[0];
};

struct bsp_rfile_open_cnf
{
    u32                     opType;
    struct list_head        *pstlist;
    s32                     errorno;
    s32                     ret;    /* 打开文件的描述符或错误码 */
};

/* write ====================================================================*/
struct bsp_rfile_write_req
{
    u32                     opType;
    struct list_head        *pstlist;
    u32                     fd;
    u32                     ulSize;
    u8                      aucData[0];
};

/* close ====================================================================*/
struct bsp_rfile_close_req
{
    u32                     opType;
    struct list_head        *pstlist;
    s32                     errorno;
    u32                     fd;
};


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/

#pragma pack(0)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* end of rfile_balong.h */

