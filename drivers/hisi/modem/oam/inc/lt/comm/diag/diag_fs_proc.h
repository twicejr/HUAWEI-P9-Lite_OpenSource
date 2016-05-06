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


#ifndef __DIAG_FS_PROC_H__
#define __DIAG_FS_PROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "mdrv.h"
#include  "vos.h"
#include  "diag_common.h"


#if (VOS_OS_VER == VOS_LINUX)
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/personality.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/fs.h>
#include <linux/rcupdate.h>
#include <linux/hrtimer.h>
#include <linux/statfs.h>
#include <linux/stat.h>

#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/

#define diag_fs_log()\
        vos_printf("diag_fs_log: %d\n", __LINE__)

/*FILE OPEN MODE*/
#define DIAG_FS_RDONLY            (00000000)          /* +1 == FREAD */
#define DIAG_FS_WRONLY            (00000001)          /* +1 == FWRITE */
#define DIAG_FS_RDWR              (00000002)          /* +1 == FREAD|FWRITE */
#define DIAG_FS_CREAT             (00000100)          /* open with file create */
#define DIAG_FS_EXCL              (00000200)          /* error on open if file exists */
#define DIAG_FS_TRUNC             (00001000)          /* open with truncation */
#define DIAG_FS_APPEND            (00002000)          /* append (writes guaranteed at the end) */
#define DIAG_FS_DIRECTORY         (00040000)

#define DIAG_CMD_FILE_NAME_LEN    (64)
#define MSP_DF_DIR_MAX_LEN        (256)

#define DIAG_TRANSFER_BLOCK_MAX_SIZE                (2*1024)

#define DIAG_FILE_NULL                          (-1)
#define DIAG_FS_ERROR                           (-1)
#define MSP_DF_DIR_BUF_LEN                      (1024*5)

#define DIAG_FS_OPEN(filename,flags,mode)       sys_open(filename,flags,mode)
#define DIAG_FS_OPENDIR(dirname,flags,mode)     sys_open(dirname,flags,mode)
#define DIAG_FS_CLOSE(fd)                       sys_close(fd)
#define DIAG_FS_CLOSEDIR(dir_handle)            sys_close(dir_handle)
#define DIAG_FS_READ(fd,buffer,count)           sys_read(fd,buffer,count)
#define DIAG_FS_GETDENTS(fd, buf, count)        sys_getdents(fd, buf, count)
#define DIAG_FS_WRITE(fd,buffer,count)          sys_write(fd,buffer,count)
#define DIAG_FS_MKDIR(dirname,mode)             sys_mkdir(dirname,mode)
#define DIAG_FS_RMDIR(dirname)                  sys_rmdir(dirname )
#define DIAG_FS_RMFILE(filename)                sys_unlink(filename)
#define DIAG_FS_LSEEK(fd,offset,origin)         sys_lseek(fd,offset,origin)
#define DIAG_FS_STAT(path,buf)                  vfs_stat(path,buf)
#define DIAG_FS_SYNC() 							sys_sync()
#define DIAG_FS_FILE_SYNC(fd) 					sys_fsync(fd)

#define DIAG_IF_DIR             0040000          /* directory */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/
enum DIAG_FOLDER_TYPE_ENUM
{
    DIAG_FS_ROOT_FOLDER = 0,
    DIAG_FS_LOG_FOLDER,
    DIAG_FS_DUMP_FOLDER,
    DIAG_FS_FOLDER_BUTT
};

/*目录中各项的类型*/
typedef enum
{
    DIAG_FS_ITEM_FOLDER = 0,
    DIAG_FS_ITEM_FILE,
    DIAG_FS_ITEM_BUTT
}OM_ITEM_TYPE_ENUM;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*保存操作文件的信息*/
typedef struct
{
    VOS_INT     lFile;
    VOS_UINT32  ulFileType;
    HTIMER      hTimer;
}DIAG_FILE_INFO_STRU;

typedef struct
{
	VOS_UINT32	d_ino;
	VOS_UINT32	d_off;
	VOS_UINT16	d_reclen;
	VOS_CHAR	d_name[1];
}DIAG_DIRENT_STRU;

/*typedef struct
{
	VOS_UINT16 st_dev;
	VOS_UINT16 st_ino;
	VOS_UINT16 st_mode;
	VOS_UINT16 st_nlink;
	VOS_UINT16 st_uid;
	VOS_UINT16 st_gid;
	VOS_UINT16 st_rdev;
	VOS_UINT32  st_size;
	VOS_UINT32  st_atime;
	VOS_UINT32  st_mtime;
	VOS_UINT32  st_ctime;
}DIAG_STAT_STRU;*/
typedef struct kstat DIAG_STAT_STRU;


/*****************************************************************************
 描述 : 该命令用来查询根目录
ID   : DIAG_CMD_FS_QUERY_DIR
REQ : DIAG_CMD_FS_QUERY_REQ
CNF : DIAG_CMD_FS_QUERY_CNF
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulFolderType;                   /*查询的是根目录还是其他LOG目录*/
}DIAG_CMD_FS_QUERY_REQ;

typedef struct
{
    VOS_UINT32  ulAuid;                         /* 原AUID*/
    VOS_UINT32  ulSn;                           /* HSO分发，插件命令管理*/
    VOS_UINT32  ulRet;                          /*结果码*/
    VOS_UINT32  ulLength;                       /*目录长度*/
    VOS_UINT8   aucDirPath[DIAG_CMD_FILE_NAME_LEN];                  /*目录名*/
}DIAG_CMD_FS_QUERY_CNF;


/*****************************************************************************
 描述 : 该命令用来遍历每个文件或文件夹信息
ID   : DIAG_CMD_FS_SCAN_DIR
REQ : DIAG_CMD_FS_SCAN_DIR_REQ
CNF : DIAG_CMD_FS_SCAN_DIR_CNF
*****************************************************************************/
typedef struct
{
    VOS_CHAR   aucDirName[DIAG_CMD_FILE_NAME_LEN];  /* dir or file name*/
    VOS_INT32      st_mode;                         /* Mode of file */
    VOS_UINT64     st_size;                         /* File size in bytes */
    VOS_INT32      st_atime;                        /* Time of last access */
    VOS_INT32      st_mtime;                        /* Time of last modification */
    VOS_INT32      st_ctime;                        /* Time of last status change */
    VOS_UINT32    ulItemType;                       /*file or folder*/
} DIAG_DIR_FILE_INFO_STRU;

typedef struct
{
    VOS_CHAR szDirectory[MSP_DF_DIR_MAX_LEN];/*扫描文件夹名*/
}DIAG_CMD_FS_SCAN_DIR_REQ;

typedef struct
{
    VOS_UINT32  ulAuid;                     /* 原AUID*/
    VOS_UINT32  ulSn;                       /* HSO分发，插件命令管理*/
    VOS_UINT32  ulRet;                      /*结果码*/
    VOS_UINT32  ulDirNum;                   /*指定目录下文件/文件夹数*/
    VOS_UINT32  ulDirInfoLen;               /*指定目录下文件/文件夹长度*/
    DIAG_DIR_FILE_INFO_STRU stDirInfo[0];   /*指定目录下文件/文件夹属性*/
}DIAG_CMD_FS_SCAN_DIR_CNF;


/*****************************************************************************
 描述 : 该命令用来遍历每个文件或文件夹信息
ID   : DIAG_CMD_FS_MAKE_DIR
REQ : DIAG_CMD_FS_MAKE_DIR_REQ
CNF : DIAG_CMD_FS_MAKE_DIR_CNF
*****************************************************************************/
typedef struct
{
    VOS_CHAR szDirectory[MSP_DF_DIR_MAX_LEN];  /*创建文件夹名*/
}DIAG_CMD_FS_MAKE_DIR_REQ;

typedef struct
{
    VOS_UINT32  ulAuid;             /* 原AUID*/
    VOS_UINT32  ulSn;               /* HSO分发，插件命令管理*/
    VOS_UINT32  ulRet;              /*结果码*/
}DIAG_CMD_FS_MAKE_DIR_CNF;

/*****************************************************************************
 描述 : 该命令用来遍历每个文件或文件夹信息
ID   : DIAG_CMD_FS_DELETE
REQ : DIAG_CMD_FS_DELETE_REQ
CNF : DIAG_CMD_FS_DELETE_CNF
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulItemType;                   /*删除文件还是文件夹*/
    VOS_CHAR szDirectory[MSP_DF_DIR_MAX_LEN]; /*删除文件/文件夹名*/
}DIAG_CMD_FS_DELETE_REQ;

typedef struct
{
    VOS_UINT32  ulAuid;                 /* 原AUID*/
    VOS_UINT32  ulSn;                   /* HSO分发，插件命令管理*/
    VOS_UINT32  ulRet;                  /*结果码*/
}DIAG_CMD_FS_DELETE_CNF;

/*****************************************************************************
 描述 : 该命令用来打开或创建文件
ID   : DIAG_CMD_FS_OPEN
REQ : DIAG_CMD_FS_OPEN_REQ
CNF : DIAG_CMD_FS_OPEN_CNF
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulMode;                         /*打开方式*/
    VOS_CHAR   szDirectory[MSP_DF_DIR_MAX_LEN]; /*打开路径*/
}DIAG_CMD_FS_OPEN_REQ;

typedef struct
{
    VOS_UINT32  ulAuid;                 /* 原AUID*/
    VOS_UINT32  ulSn;                   /* HSO分发，插件命令管理*/
    VOS_UINT32  ulRet;                  /*结果码*/
}DIAG_CMD_FS_OPEN_CNF;

/*****************************************************************************
 描述 : 该命令用来导出文件
ID   : DIAG_CMD_FS_EXPORT
REQ : DIAG_CMD_FS_EXPORT_REQ
CNF : DIAG_CMD_FS_EXPORT_CNF
*****************************************************************************/


typedef struct
{
    VOS_UINT32  ulAuid;                 /* 原AUID*/
    VOS_UINT32  ulSn;                   /* HSO分发，插件命令管理*/
    VOS_UINT32  ulRet;                  /*结果码*/
    VOS_UINT32  ulSize;                 /* 返回的实际大小, 不超过 DIAG_TRANSFER_BLOCK_MAX_SIZE*/
    VOS_UINT8   aucData[0];             /*导出内容*/
}DIAG_CMD_FS_EXPORT_CNF;

/*****************************************************************************
 描述 : 该命令用来导入文件
ID   : DIAG_CMD_FS_IMPORT
REQ : DIAG_CMD_FS_IMPORT_REQ
CNF : DIAG_CMD_FS_IMPORT_CNF
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulSize;                         /*待导入长度*/
    VOS_CHAR    acContent[0];                   /*导入内容*/
}DIAG_CMD_FS_IMPORT_REQ;

typedef struct
{
    VOS_UINT32  ulAuid;                 /* 原AUID*/
    VOS_UINT32  ulSn;                   /* HSO分发，插件命令管理*/
    VOS_UINT32  ulRet;
}DIAG_CMD_FS_IMPORT_CNF;

/*****************************************************************************
 描述 : 该命令用来查询剩余及使用空间
ID   : DIAG_CMD_FS_SPACE
REQ : DIAG_CMD_FS_SPACE_REQ
CNF : DIAG_CMD_FS_SPACE_CNF
*****************************************************************************/
typedef struct
{
    VOS_CHAR    szDirectory[MSP_DF_DIR_MAX_LEN];  /*导入内容*/
}DIAG_CMD_FS_SPACE_REQ;

typedef struct
{
    VOS_UINT32  ulAuid;                 /* 原AUID*/
    VOS_UINT32  ulSn;                   /* HSO分发，插件命令管理*/
    VOS_UINT32  ulRet;                  /*Result of operation*/
    VOS_UINT32  ulDiskSpace;
    VOS_UINT32  ulUsedSpace;
    VOS_UINT32  ulValidSpace;
}DIAG_CMD_FS_SPACE_CNF;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/

extern VOS_VOID diag_FsClose(VOS_VOID);
extern VOS_INT32  diag_FsOpen(const VOS_CHAR *pcFileName, VOS_INT lFlag);
extern VOS_UINT32 diag_FsGetDirInfo(VOS_CHAR *pDirName, VOS_UINT32 *pulTotalNum);
extern VOS_UINT32 diag_FsGetItemInfo(VOS_CHAR *pDirectory,DIAG_DIR_FILE_INFO_STRU *pstDirFileInfo);
extern VOS_UINT32 diag_FsQueryProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_FsExportProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_FsDeleteProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_FsOpenProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_FsImportProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_FsSpaceProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_FsScanProc(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_FsMkdirProc(VOS_UINT8* pstReq);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of diag_fs_op.h */

