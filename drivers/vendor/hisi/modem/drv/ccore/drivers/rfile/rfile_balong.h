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
#include <linux/delay.h>

#endif /* end of __KERNEL__ */

#include "product_config.h"
#include "osl_types.h"
#include "osl_sem.h"
#include "osl_list.h"
#include "osl_thread.h"
#include "osl_malloc.h"
#include "drv_comm.h"
#include "mdrv_memory.h"
#include "mdrv_timer.h"
#include "bsp_om.h"
#include "bsp_icc.h"
#include "bsp_rfile.h"


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define RFILE_TIMEOUT_MAX           (2000)           /* 最长等待2s */
#define RFILE_WAIT_FOREVER          (-1)

#define RFILE_MAX_SEND_TIMES        (10)                /* 发送失败时，最大尝试次数 */

#define RFILE_CCORE_ICC_RD_CHAN     (ICC_CHN_RFILE<<16 | RFILE_RECV_FUNC_ID)
#define RFILE_CCORE_ICC_WR_CHAN     (ICC_CHN_RFILE<<16 | RFILE_RECV_FUNC_ID)

#define RFILE_ICC_PACKET_HEAD_LEN   ICC_CHANNEL_PAYLOAD

#define RFILE_LEN_MAX               (0x00001000 - RFILE_ICC_PACKET_HEAD_LEN)

/* RFILE模块写操作依赖于ICC的最大长度 */
#define RFILE_WR_LEN_MAX            (0x00001000 - RFILE_ICC_PACKET_HEAD_LEN - sizeof(struct bsp_rfile_write_req))

/* RFILE模块读操作依赖于ICC的最大长度 */
#define RFILE_RD_LEN_MAX            (0x00001000 - RFILE_ICC_PACKET_HEAD_LEN - sizeof(struct bsp_rfile_read_cnf))


#define RFILE_MNTN_INFO_NUM         (20)            /* 记录20个可维可测信息 */

#define RFILE_MNTN_DATA_LEN         (32)            /* 可维可测信息数据的最大长度 */


typedef  osl_sem_id             rfile_sem_id;

#define Rfile_Malloc(size)      osl_malloc(size)
#define Rfile_Free(ptr)         osl_free(ptr)
#define RFILE_SLEEP(msecs)      osl_task_delay(msecs)
#define RFILE_TASK_STACK_SIZE   (0x1000)        /* TODO: */
#ifdef __KERNEL__






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
    EN_RFILE_OP_RENAME,
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
/* 操作信息 */
struct bsp_rfile_op_stru
{
    u32                     optype;         /* 当前的处理类型，见enum _BSP_RFILE_OP_EN */
    s32                     fd;             /* 文件描述符 */
    s32                     retlen;         /* 处理结果 */
    u32                     datalen;        /* 数据缓存长度，用于read,readdir,massread */
    s8                      *ptr;           /* 数据缓存指针，用于read,readdir,massread */
    long                    offset;         /* 偏移，用于lseek */
    s32                     whence;         /* 偏移类型 */
    s32                     dirhandle;      /* 目录句柄 */
    struct rfile_stat_stru  ststat;         /* 文件的信息 */
};


/* 队列元素 */
struct bsp_rfile_que_stru
{
    enum bsp_rfile_state_en     enState;
    rfile_sem_id                semReq;     /* 请求阻塞信号量 */
    struct bsp_rfile_op_stru    stData;     /* 请求数据信息 */
    struct list_head            stlist;     /* 链表节点 */
    void                        *pData;     /* 需要通过核间通信发给A核的数据 */
    u32                         ulLen;
    s32                         ret;
};/*lint !e959*/


/* 主控信息 */
struct bsp_rfile_main_stru
{
    BSP_BOOL                bInitFlag;
    s32                     errorno;
    u32                     taskid;
    rfile_sem_id            semTask;    /* 任务信号量 */
    rfile_sem_id            semList;    /* 链表信号量 */
    struct list_head        stlist;     /* 链表节点 */
    u8                      data[RFILE_LEN_MAX];    /* 缓存ICC通道读取的数据 */
};/*lint !e959*/


/* 可维可测信息 */
struct rfile_mntn_info_stru
{
    enum _BSP_RFILE_OP_EN   enType;
    enum bsp_rfile_err_en   enErr;
    s32                     param1;
    s32                     param2;
    s32                     param3;
    u32                     slice;
    u8                      pData[RFILE_MNTN_DATA_LEN];
};

struct bsp_rfile_mntn_stru
{
    s32                             position;
    struct rfile_mntn_info_stru     stMntnInfo[RFILE_MNTN_INFO_NUM];    /* 记录每种操作的最新20条记录 */
};

struct rfile_mntn_type_stru
{
    u32                     ptr;
    enum _BSP_RFILE_OP_EN   enType[RFILE_MNTN_INFO_NUM];
    u32                     slice[RFILE_MNTN_INFO_NUM];
};

struct rfile_mntn_stru
{
    struct rfile_mntn_type_stru     sttype;
};


struct bsp_rfile_common_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     ret;
};

/* open====================================================================*/
struct bsp_rfile_open_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     mode;
    s32                     flags;
    s32                     nameLen;
    u8                      aucData[0];/*lint !e43*/
};

struct bsp_rfile_open_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     ret;    /* 打开文件的描述符或错误码 */
};

/* seek====================================================================*/
struct bsp_rfile_seek_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     fd;
    s32                     offset;
    s32                     whence;
};

/* read ====================================================================*/
struct bsp_rfile_read_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     fd;
    u32                     ulSize;
};

struct bsp_rfile_read_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     Size;
    u8                      aucData[0];/*lint !e43*/
};

/* write ====================================================================*/
struct bsp_rfile_write_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     fd;
    u32                     ulSize;
    u8                      aucData[0];/*lint !e43*/
};

/* close ====================================================================*/
struct bsp_rfile_close_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    u32                     fd;
};

/* remove====================================================================*/
struct bsp_rfile_remove_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     pathLen;
    u8                      aucData[0];/*lint !e43*/
};

/* tell  ====================================================================*/
struct bsp_rfile_tell_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     fd;
};

/* mkdir ====================================================================*/
struct bsp_rfile_mkdir_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     pathLen;
    s32                     mode;
    u8                      aucData[0];/*lint !e43*/
};

/* rmdir ====================================================================*/
struct bsp_rfile_rmdir_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     pathLen;
    u8                      aucData[0];/*lint !e43*/
};

/* opendir =================================================================*/
struct bsp_rfile_opendir_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     nameLen;
    u8                      aucData[0];/*lint !e43*/
};

struct bsp_rfile_opendir_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     dirhandle;
};

/* readdir==================================================================*/
struct bsp_rfile_readdir_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     dir;
    u32                     count;
};

struct bsp_rfile_readdir_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     Size;
    u8                      aucData[0];/*lint !e43*/
};

/* closedir==================================================================*/
struct bsp_rfile_closedir_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     dir;
};

/* stat======================================================================*/
struct bsp_rfile_stat_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     ulSize;
    u8                      aucData[0];/*lint !e43*/
};

struct bsp_rfile_stat_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     ret;
    struct rfile_stat_stru  ststat;
};

/* access=====================================================================*/
struct bsp_rfile_access_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     mode;
    s32                     pathlen;
    u8                      aucData[0];/*lint !e43*/
};


/* mass read==================================================================*/
struct bsp_rfile_massread_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     offset;
    u32                     size;
    u32                     datalen;        /* the length of partition string(include \0) */
    u8                      aucData[0];     /*lint !e43*//* partition */
};


/* mass write=================================================================*/
struct bsp_rfile_masswrite_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     offset;
    u32                     size;
    u32                     partitionlen;   /* the length of partition string(include \0) */
    u32                     datalen;        /* the size of all data */
    u8                      aucData[0];     /*lint !e43*//* partition + write buffer */
};

/* rename======================================================================*/
struct bsp_rfile_rename_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     ulSize;
    u8                      aucData[0];/*lint !e43*/
};

struct bsp_rfile_rename_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     ret;
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

s32 rfile_HandleReq(struct bsp_rfile_que_stru *pstRfileQue);

void rfile_OpenCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_open_cnf *pstCnf);
void rfile_CloseCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_common_cnf *pstCnf);
void rfile_ReadCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_read_cnf *pstCnf);
void rfile_OpendirCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_opendir_cnf *pstCnf);
void rfile_ReaddirCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_readdir_cnf *pstCnf);
void rfile_StatCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_stat_cnf *pstCnf);
void rfile_MntnRecord(struct rfile_mntn_info_stru *pstmntn);
void rfile_MntnTypeIn(enum _BSP_RFILE_OP_EN entype);

s32 rfile_readdir(u32 fd, void *dirent, u32 count);
s32 rfile_CnfProc(struct list_head *plistcnf, u32 enOptype, void *pData);
s32 bsp_RfileCallback(u32 channel_id, u32 len, void *context);
struct bsp_rfile_que_stru *rfile_GetQueNode(void);
s32 rfile_RcvIccData(void);
void rfile_SendIccData(void);
void rfile_TaskProc(void* obj);
s32 rfile_AddNode(struct bsp_rfile_que_stru *pstNode);
s32 rfile_DelNode(struct bsp_rfile_que_stru *pstNode);

#pragma pack(0)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* end of rfile_balong.h */

