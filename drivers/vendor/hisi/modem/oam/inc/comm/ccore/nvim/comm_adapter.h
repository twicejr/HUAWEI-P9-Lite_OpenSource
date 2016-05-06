/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : comm_adapter.h
  版 本 号   : 初稿
  作    者   : 甘兰
  生成日期   : 2012年12月4日
  最近修改   :
  功能描述   : 适配OSA模块
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月4日
    作    者   : g47350
    修改内容   : V9R1 NV升级项目新增

******************************************************************************/

#ifndef __COMM_ADAPTER_H__
#define __COMM_ADAPTER_H__

#include "product_config.h"

#define VOS_WIN32                       1
#define VOS_PSOS                        2
#define VOS_VXWORKS                     3
#define VOS_LINUX                       4
#define VOS_RTOSCK                      5

#if !defined(VOS_OS_VER)

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#ifdef _DRV_LLT_
#define VOS_OS_VER                      VOS_WIN32
#else
    #if (FEATURE_ON == FEATURE_RTOSCK)
        #define VOS_OS_VER                      VOS_RTOSCK
    #else
        #define VOS_OS_VER                      VOS_VXWORKS
#endif
    #endif
#else
#define VOS_OS_VER                      VOS_LINUX
#endif

#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#if (VOS_VXWORKS == VOS_OS_VER)
#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "stat.h"
#include "usrFsLib.h"
#include "intLib.h"
#include "semLibCommon.h"
#include "taskLib.h"
#include "mdrv.h"
#endif

#if (VOS_WIN32 == VOS_OS_VER)
#include "Windows.h"
#include <Shellapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <direct.h>
#endif

#if (VOS_LINUX == VOS_OS_VER)
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <linux/in.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/fcntl.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/socket.h>
#include <linux/skbuff.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mm.h>
#include <linux/tty.h>
#include <linux/delay.h>
#include <net/sock.h>
#include <asm/uaccess.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/spinlock.h>
#endif

#if (VOS_RTOSCK == VOS_OS_VER)
#include "stdio.h"
#include "string.h"
#include "sre_base.h"
#include "sre_sem.h"
#include "sre_mem.h"
#include "mdrv.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define VOS_FILE_ID                     THIS_FILE_ID

#define VOS_SEMA4_FIFO                  0x00000001
#define VOS_SEMA4_PRIOR                 0x00000002
#define VOS_SEMA4_DELETE_SAFE           0x00000004
#define VOS_SEMA4_INVERSION_SAFE        0x00000008
#define VOS_SEMA4_GLOBAL                0x00000010


#define VOS_NULL_PTR                    (0L)
#define VOS_NULL                        (0)
#define VOS_NULL_WORD                   (0xFFFF)
#define VOS_NULL_DWORD                  (0xFFFFFFFF)
#define VOS_NULL_LONG                   (VOS_NULL_DWORD)


#define VOS_OK                          (0)
#define VOS_ERR                         (1)
#define VOS_ERROR                       (-1)

#define VOS_YES                         1
#define VOS_NO                          0

#define NV_FILE_OPEN_MODE_R             "rb"    /* open binary file for reading */
#define NV_FILE_OPEN_MODE_W             "wb"    /* open binary file for writing */
#define NV_FILE_OPEN_MODE_RW            "rb+"   /* open binary file for reading and writing */
#define NV_FILE_OPEN_MODE_NEW_RW        "wb+"   /* creat binary file for reading and writing*/
#define NV_FILE_OPEN_MODE_APEND         "a"
#define NV_FILE_SEEK_SET                0   /* the beginning of the file*/
#define NV_FILE_SEEK_CUR                1   /* the current value of the file position indicator */
#define NV_FILE_SEEK_END                2   /* the end of the file */
#define NV_FILE_EXIST_OK                (0)


#define VOS_DUMP_MEM_TOTAL_SIZE         (32*1024)

#define VOS_MemSet( ToSet, Char, Count )\
        memset(ToSet, Char, Count)

#define VOS_MemCpy( Dest, Src, Count )\
        memcpy(Dest, Src, Count)

#define VOS_MemCmp( Dest, Src, Count )\
        memcmp(Dest, Src, Count)

#define VOS_StrCmp(Str1, Str2)\
        strcmp(Str1, Str2)

#define VOS_StrNCmp(Str1, Str2, Count)\
        strncmp(Str1, Str2, Count)

#define VOS_StrTok(Str1, Str2)\
        strtok(Str1, Str2)

#define VOS_StrLen(Str)\
        strlen(Str)

#define VOS_StrCpy(Dest, Src)\
        strcpy(Dest, Src)

#define VOS_StrNCpy(Dest, Src, Count)\
        strncpy(Dest, Src, Count)

#define VOS_StrNCat(Dest, Src, Count)\
        strncat(Dest, Src, Count)

#if (VOS_WIN32 == VOS_OS_VER)

#define VOS_MemAlloc(ulInfo, ucPtNo, ulSize)\
        Stub_malloc(ulSize)

#define VOS_MemFree(ulInfo, ppAddr)\
        free(ppAddr)

#define VOS_SplIMP() (VOS_OK)

#define VOS_Splx(s) (VOS_OK)

#define VOS_SmDelete(Sm_ID) (VOS_OK)

#define VOS_TaskLock() (VOS_OK)

#define mdrv_file_open(name, flags) \
        fopen(name,flags)

#define mdrv_file_close(fp) \
        fclose(fp)

#define mdrv_file_read(buff,size,number,fp) \
        fread(buff,size,number,fp)

#define mdrv_file_write(buff,size,number,fp) \
        fwrite(buff,size,number,fp)

#define mdrv_file_write_sync(buff,size,number,fp) \
        fwrite(buff,size,number,fp)

#define mdrv_file_remove(fileName) \
        Stub_remove(fileName)

#define mdrv_file_seek(fp,offset,whence) \
        fseek(fp,offset,whence)

#define mdrv_file_tell(fp) \
        ftell(fp)

#define mdrv_file_mkdir(dirName) \
        mkdir(dirName)

#define mdrv_file_rmdir(path) \
        rmdir(path)

#define mdrv_file_xcopy(src, dest) \
        xcopy(src, dest)

#define mdrv_file_access(name,flags) \
        access(name,flags)
#elif (VOS_VXWORKS == VOS_OS_VER)

#define VOS_MemAlloc(ulInfo, ucPtNo, ulSize)\
        malloc(ulSize)

#define VOS_MemFree(ulInfo, ppAddr)\
        free(ppAddr)

#define VOS_SplIMP() \
        intLock()

#define VOS_Splx( s ) \
        intUnlock( (s) )

#define VOS_SmMCreate(Sm_Name, Flags, Sm_ID) \
        _VOS_SmCCreate(Sm_Name, 0xFFFFFFFF, Flags, Sm_ID)

#define VOS_SmP(Sm_ID, ulTimeOutInMillSec) \
        _VOS_SmP(Sm_ID, ulTimeOutInMillSec)

#define VOS_SmV(Sm_ID) \
        semGive((SEM_ID)Sm_ID)

#define VOS_SmDelete(Sm_ID) \
        semDelete((SEM_ID)Sm_ID)

#define VOS_TaskLock() \
        taskLock()

#elif (VOS_RTOSCK == VOS_OS_VER)

#define VOS_MemAlloc(ulInfo, ucPtNo, ulSize)\
        SRE_MemCacheAlloc(ulSize, MEM_ADDR_ALIGN_004)

#define VOS_MemFree(ulInfo, ppAddr)\
        SRE_MemCacheFree(ppAddr)

#define VOS_SplIMP() \
        (VOS_INT)SRE_IntLock()

#define VOS_Splx( s ) \
        SRE_IntRestore( (VOS_UINT32)(s) )

#define VOS_SmMCreate(Sm_Name, Flags, Sm_ID) \
        _VOS_SmCCreate(Sm_Name, 0xFFFFFFFF, Flags, Sm_ID)

#define VOS_SmP(Sm_ID, ulTimeOutInMillSec) \
        _VOS_SmP(Sm_ID, ulTimeOutInMillSec)

#define VOS_SmV(Sm_ID) \
        SRE_SemPost((SEM_HANDLE_T)Sm_ID)

#define VOS_SmDelete(Sm_ID) \
        SRE_SemDelete((SEM_HANDLE_T)Sm_ID)

#define VOS_TaskLock() \
        SRE_TaskLock()

#elif (VOS_LINUX == VOS_OS_VER)

#define VOS_TaskLock() \
        preempt_disable()

#define VOS_SmCCreate(Sm_Name, SmInit, Flags, Sm_ID) \
        _VOS_SmCCreate(Sm_Name, 0xFFFFFFFF, Flags, Sm_ID)

#define VOS_SmMCreate(Sm_Name, Flags, Sm_ID) \
        _VOS_SmMCreate(Sm_Name, 0xFFFFFFFF, Flags, Sm_ID)

#define VOS_SmP(Sm_ID, ulTimeOutInMillSec) \
        _VOS_SmP(Sm_ID, ulTimeOutInMillSec)

#define VOS_SmV(Sm_ID) \
        _VOS_SmV(Sm_ID)

#endif


#define LogPrint4                       NV_Printf
#define LogPrint                        NV_Printf
#define vos_printf                      NV_Printf

#define PS_LOG(ModulePID, SubMod, Level, String)\
    {\
        NV_Printf(String);\
    }\

#define PS_LOG1(ModulePID, SubMod, Level, String, Para1)\
    {\
        NV_Printf(String);\
        NV_Printf("Para is :%d.\r\n", Para1);\
    }\

#define PS_LOG2(ModulePID, SubMod, Level, String, Para1, Para2)\
    {\
        NV_Printf(String);\
        NV_Printf("Para is  :%d, %d.\r\n", Para1, Para2);\
    }\

/*****************************************************************************
  3 STRUCT定义
*****************************************************************************/

/*lint -save -e737*/

typedef int                    VOS_INT;

typedef void                   VOS_VOID;

typedef unsigned char          VOS_UINT8;

typedef signed char            VOS_INT8;

typedef char                   VOS_CHAR;           /* 8 bit ASCII */

typedef unsigned char          VOS_UCHAR;


typedef unsigned short         VOS_UINT16;

typedef signed   short         VOS_INT16;

typedef signed   short         VOS_WCHAR;          /* 16 bit Unicode */


typedef unsigned int           VOS_UINT32;

typedef signed   int           VOS_INT32;

typedef unsigned int           VOS_BOOL;

typedef long                   VOS_INT_PTR;

typedef unsigned long          VOS_UINT_PTR;

typedef VOS_UINT_PTR           VOS_SEM;

#if (VOS_WIN32 != VOS_OS_VER)

#if 0
typedef	unsigned long          DRV_INO_T;

/* dirent */
typedef struct dirent
{
    DRV_INO_T           d_ino;                      /* file serial number */
    char                d_name [256];               /* file name, null-terminated */
}DRV_DIRENT_S;

/* Directory descriptor */
typedef struct
{
    int                 dd_fd;                      /* file descriptor for open directory */
    int                 dd_cookie;                  /* filesys-specific marker within dir */
    int                 dd_eof;                     /* readdir EOF flag */
    DRV_DIRENT_S     dd_dirent;                  /* obtained directory entry */
}DRV_DIR_S;
#endif

#endif

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
#if (!defined(OAM_UT_DEBUG) && !defined(COMM_ST_SWITCH)) /* 解决UT/ST工程冲突 */

enum _BOOL_DEFINE
{
    VOS_FALSE = 0,
    VOS_TRUE = 1
};

/* 文件ID */
enum
{
    PS_FILE_ID_XML_C = 0x3000,
    PS_FILE_ID_NVIM_FUNCTION_C,
    PS_FILE_ID_NVIM_AFUNC_C,
    PS_FILE_ID_NVIM_COMMFUNC_C,
};
#endif  /*(!defined(OAM_UT_DEBUG) && !defined(COMM_ST_SWITCH))*/

/*为了PC工程编译通过，因此把原有的枚举改成宏定义*/
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#define MODEM_ID_0          0
#define MODEM_ID_1          1
#define MODEM_ID_BUTT       2
#else
#define MODEM_ID_0          0
#define MODEM_ID_BUTT       1
#define MODEM_ID_1          2
#endif  /*( FEATURE_MULTI_MODEM == FEATURE_ON )*/
typedef VOS_UINT16 MODEM_ID_ENUM_UINT16;

/* 复位文件MODID */
enum
{
    FAIL_TO_DECODE_XML = 0x2f000000,
    NV_MEMCPY_PARA_ERROR,
    NV_ACPU_GOBAL_ERROR,
};

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/

/*****************************************************************************
  6 消息头定义
*****************************************************************************/

/*****************************************************************************
  7 消息定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

/* 暂时这么写，后续确认一下 */
#if( VOS_LINUX == VOS_OS_VER )
typedef int FILE;
#endif

VOS_UINT32 _VOS_SmCCreate(VOS_CHAR   acSmName[4],
                          VOS_UINT32 ulSmInit,
                          VOS_UINT32 ulFlags,
                          VOS_SEM   *pulSmID);
VOS_UINT32 _VOS_SmP(VOS_SEM ulSemId, VOS_UINT32 ulTimeOutInMillSec);

VOS_UINT32 _VOS_SmV(VOS_SEM ulSemId);

#if ((VOS_VXWORKS == VOS_OS_VER)|| (VOS_RTOSCK == VOS_OS_VER))
/* 后续底软提供接口如下 */
extern int BSP_fread(void *ptr, unsigned int size, unsigned int number, FILE *stream);
extern int BSP_remove(const char *pathname);

extern int BSP_mkdir(const char *dirName);
extern int BSP_rmdir(const char *path);
extern int BSP_xcopy(const char *source,const char *dest);
extern int BSP_access(const char *path, int amode);
extern DRV_DIR_S* BSP_opendir(const char *dirName);
extern DRV_DIRENT_S* BSP_readdir(DRV_DIR_S *dirName);
extern int BSP_closedir(DRV_DIR_S *dirName);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
