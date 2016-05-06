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

/*lint --e{533,750}*/
#ifdef __KERNEL__
/*lint -save -e537*/
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
/*lint -restore*/
#else /* __VXWORKS__ */
#include <stdio.h>
#include <stdlib.h>
#include <stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <semLib.h>

#endif /* end of __KERNEL__ */

#include "drv_comm.h"
#include "osl_types.h"
#include "osl_sem.h"
#include "osl_list.h"
#include "bsp_om.h"
#include "mdrv_memory.h"
#include "bsp_icc.h"
#include "bsp_rfile.h"

#include "mdrv_rfile_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef __KERNEL__

#define rfile_print_info        printk

typedef  struct semaphore       rfile_sem_id;

#define Rfile_Malloc(size)      kmalloc(size, GFP_KERNEL)

#define Rfile_Free(ptr)         kfree(ptr)

#else /* __VXWORKS__ */

typedef  SEM_ID                 rfile_sem_id;

#define rfile_print_info        printf

#define Rfile_Malloc(size)      malloc(size)

#define Rfile_Free(ptr)         free(ptr)

#endif /* end of __KERNEL__ */

#define RFILE_TIMEOUT_MAX           (2000)           /* 最长等待2s */

typedef struct
{
    void *      context;        /* 0x00: WRS defined context */
    void *      magic;          /* 0x04: magic. Used in HANDLE_VERIFY() */
    u16         attributes;     /* 0x08: attribute bit set */
    s8          type;           /* 0x0a: enum windObjClassType */
    u8          contextType;    /* 0x0b: enum handleContextType */
} RFILE_HANDLE;

typedef struct           /* stdio buffers */
{
    u8 *            _base;      /* base address of {std,unget,line} buffer */
    int             _size;      /* size of the buffer */
} RFILE_SBUF;

typedef struct
{
    RFILE_HANDLE    handle;     /* file pointer handle managemet */
    u8 *            _p;         /* current position in (some) buffer */
    int             _r;         /* read space left for getc() */
    int             _w;         /* write space left for putc() */
    short           _flags;     /* flags, below;this FILE is free if 0*/
    short           _file;      /* fileno, if Unix descriptor, else -1*/
    RFILE_SBUF      _bf;        /* buffer (at least 1 byte,if !NULL) */
    int             _lbfsize;   /* 0 or -_bf._size, for inline putc */
    RFILE_SBUF      _ub;        /* ungetc buffer */
    u8 *            _up;        /* old _p if _p is doing ungetc data */
    int             _ur;        /* old _r if _r counting ungetc data */
    u8              _ubuf[3];   /* guarantee an ungetc() buffer */
    u8              _nbuf[1];   /* guarantee a getc() buffer */
    RFILE_SBUF      _lb;        /* buffer for fgetline() */
    int             _blksize;   /* stat.st_blksize (may be!=_bf._size)*/
    int             _offset;    /* current lseek offset */
    int             taskId;     /* task that owns this file pointer */
} RFILE_FILE;

//extern struct bsp_rfile_main_stru g_stRfileMain;

#define RFILE_INVALID_ERROR_NO      0xa5a5a5a5

unsigned long g_err = RFILE_INVALID_ERROR_NO;


unsigned long mdrv_file_get_errno()
{
    if(RFILE_INVALID_ERROR_NO == g_err)
    {
//        return (unsigned long)(g_stRfileMain.errorno);
        return 1;
    }
    else
    {
        return g_err;
    }
}


int rfile_getmode(const char *mode, int *flag)
{
    int ret;
    int m;
    int o;

    switch (*mode++)
    {
    case 'r':               /* open for reading */
        ret = 0x0004;
        m = RFILE_RDONLY;
        o = 0;
        break;

    case 'w':               /* open for writing */
        ret = 0x0008;
        m = RFILE_WRONLY;
        o = RFILE_CREAT | RFILE_TRUNC;
        break;

    case 'a':               /* open for appending */
        ret = 0x0008;
        m = RFILE_WRONLY;
        o = RFILE_CREAT | RFILE_APPEND;
        break;

    default:                /* illegal mode */
        g_err = 22;
        return (0);
    }

    /* [rwa]\+ or [rwa]b\+ means read and write */

    if ((*mode == '+') || (*mode == 'b' && mode[1] == '+'))
    {
        ret = 0x0010;
        m = RFILE_RDWR;
    }

    *flag = m | o;

    /* check for garbage in second character */
    if ((*mode != '+') && (*mode != 'b') && (*mode != '\0'))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s]:1. mode:%c.\n", __FUNCTION__, *mode);
        return (0);
    }

    /* check for garbage in third character */
    if (*mode++ == '\0')
    {
        return (ret);           /* no third char */
    }

    if ((*mode != '+') && (*mode != 'b') && (*mode != '\0'))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s]:3. mode:%c.\n", __FUNCTION__, *mode);
        return (0);
    }

    /* check for garbage in fourth character */
    if (*mode++ == '\0')
    {
        return (ret);           /* no fourth char */
    }

    if (*mode != '\0')
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s]:5. mode:%c.\n", __FUNCTION__, *mode);
        return (0);
    }
    else
    {
        return (ret);
    }
}


RFILE_FILE *rfile_stdioFpCreate (void)
{
    RFILE_FILE *fp = NULL;

    if ((fp = (RFILE_FILE *)Rfile_Malloc(sizeof(RFILE_FILE))) != NULL)
    {
        fp->_p      = NULL;         /* no current pointer */
        fp->_r      = 0;
        fp->_w      = 0;            /* nothing to read or write */
        fp->_flags  = 1;            /* caller sets real flags */
        fp->_file   = -1;           /* no file */
        fp->_bf._base   = NULL;         /* no buffer */
        fp->_bf._size   = 0;
        fp->_lbfsize    = 0;            /* not line buffered */
        fp->_ub._base   = NULL;         /* no ungetc buffer */
        fp->_ub._size   = 0;
        fp->_lb._base   = NULL;         /* no line buffer */
        fp->_lb._size   = 0;
        fp->_blksize    = 0;
        fp->_offset     = 0;
#ifdef __KERNEL__
        fp->taskId      = 0;
#else /* __VXWORKS__ */
        fp->taskId      = (int) (taskIdSelf()); /* task id might be useful */
#endif

        fp->handle.magic        = (void*) (&fp->handle);
        fp->handle.type         = 102;      /* stdioLib FILE    */
        fp->handle.context      = NULL;
        fp->handle.contextType  = 0;        /* handleContextTypeNone */
    }

    return (fp);
}


int rfile_stdioFpDestroy(RFILE_FILE *fp)
{
    if(NULL == fp)
        return -1;
    /* fclose() deallocates any buffers associated with the file pointer */

    fp->handle.magic        = 0;
    fp->handle.type         = -1;      /* bad handle */

    /* deallocate file pointer */

    Rfile_Free ((char *) fp);

    return 0;
}


/*文件系统接口*/
void *mdrv_file_open(const char *path, const char *mode)
{
    int ret;
    int oflags;
    int flags;
    RFILE_FILE *fp;

    if((0 == path) || (0 == mode))
    {
        g_err = 1;
        return 0;
    }

    /* 将字符串参数转换成整数 */
    flags = rfile_getmode(mode, &oflags);
    if(0 == flags)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
            "[%s] rfile_getmode failed. ret = %d.\n", __FUNCTION__, flags);
        return 0;
    }

    if ((fp = rfile_stdioFpCreate ()) == NULL)
    {
        g_err = 1;
        return (NULL);
    }

    g_err = RFILE_INVALID_ERROR_NO;
    /* coverity[example_assign] */
    ret = bsp_open((const s8 *)path, oflags, 0755);
    /* coverity[example_checked] */
    if(ret < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
            "[%s] bsp_open failed,path=%s, ret = %x.\n", __FUNCTION__, path, ret);
        ret = rfile_stdioFpDestroy (fp);      /* destroy file pointer */
        g_err = (u32)ret;
        return 0;
    }

    fp->_file	= (short)ret;
    fp->_flags	= (short)flags;

    return (void*)fp;
}

/*lint -save -e732*/
int mdrv_file_close(void *fp)
{
    int ret;
    if(0 == fp)
    {
        g_err = 1;
        return -1;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    ret = bsp_close(((RFILE_FILE*)fp)->_file);
    if(0 == ret)
    {
        ret = rfile_stdioFpDestroy(fp);
    }

    return ret;
}

int mdrv_file_read(void *ptr, unsigned int size, unsigned int number, void *stream)
{
    int cnt;

    if((0 == ptr) || (0 == stream) || (0 == size))
    {
        g_err = 1;
        return -1;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    cnt = bsp_read(((RFILE_FILE*)stream)->_file, ptr, (size*number));

    return cnt/((int)size);
}

int mdrv_file_write(void *ptr, unsigned int size, unsigned int number, void *stream)
{
    int cnt;

    if((0 == ptr) || (0 == stream))
    {
        g_err = 1;
        return -1;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    cnt = bsp_write(((RFILE_FILE*)stream)->_file, ptr, (size*number));

    return cnt/((int)size);
}

int mdrv_file_write_sync(void *ptr, unsigned int size, unsigned int number, void *stream)
{
    int cnt;

    if((0 == ptr) || (0 == stream))
    {
        g_err = 1;
        return -1;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    cnt = bsp_write_sync(((RFILE_FILE*)stream)->_file, ptr, (size*number));

    return cnt/((int)size);
}

int mdrv_file_seek(void *stream, long offset, int whence)
{
    int ret;

    if(0 == stream)
    {
        g_err = 1;
        return -1;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    ret = bsp_lseek(((RFILE_FILE*)stream)->_file, offset, whence);
    if(ret < 0)
    {
        return -1;
    }

    return 0;
}

long mdrv_file_tell(void *stream)
{
    if(0 == stream)
    {
        g_err = 1;
        return -1;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    return bsp_tell(((RFILE_FILE*)stream)->_file);
}
/*lint -restore*/

int mdrv_file_remove(const char *pathname)
{
    if(0 == pathname)
    {
        g_err = 1;
        return -1;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    return bsp_remove((const s8 *)pathname);
}

int mdrv_file_mkdir(const char *dirName)
{
    if(0 == dirName)
    {
        g_err = 1;
        return -1;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    return bsp_mkdir((s8*)dirName, 0660);
}

int mdrv_file_rmdir(const char *path)
{
    if(0 == path)
    {
        g_err = 1;
        return -1;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    return bsp_rmdir((s8*)path);
}


DRV_DIR_S *rfile_stdioDirCreate (void)
{
    DRV_DIR_S *dir = NULL;

    dir = (DRV_DIR_S *)Rfile_Malloc(sizeof(DRV_DIR_S));
    if (dir != NULL)
    {
        dir->dd_fd      = -1;
        dir->dd_cookie  = 0;
        dir->dd_eof     = 0;

        memset(&dir->dd_dirent, 0, sizeof(DRV_DIRENT_S));
    }

    return (dir);
}


int rfile_stdioDirDestroy(DRV_DIR_S *dir)
{
    if(NULL == dir)
        return -1;

    dir->dd_fd = -1;
    memset(&dir->dd_dirent, 0, sizeof(DRV_DIRENT_S));

    Rfile_Free ((char *) dir);

    return 0;
}


DRV_DIR_S* mdrv_file_opendir(const char *dirName)
{
    int ret;
    DRV_DIR_S *dir;

    if(0 == dirName)
    {
        g_err = 1;
        return NULL;
    }

    ret = bsp_opendir((s8*)dirName);
    if(ret < 0)
    {
        g_err = 2;
        return 0;
    }

    dir = rfile_stdioDirCreate();
    if(dir == NULL)
    {
        g_err = 3;
        (void)bsp_closedir(ret);
        return NULL;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    dir->dd_fd = ret;
    memcpy(dir->dd_dirent.d_name, dirName, strlen(dirName));

    return dir;
}

DRV_DIRENT_S g_stdirent;

struct rfile_dirent_info
{
    DRV_DIR_S        *phandle;
    RFILE_DIRENT_STRU   *pdirent;
    int                 len;        /* 总长度 */
    int                 ptr;        /* 当前偏移 */
    struct list_head    stlist;     /* 链表节点 */
};

struct rfile_adp_ctrl
{
    struct list_head    rfile_listhead;
    rfile_sem_id        semList;
};

struct rfile_adp_ctrl g_adp_rfile;

void adp_rfile_init()
{
    INIT_LIST_HEAD(&g_adp_rfile.rfile_listhead);

#ifdef __KERNEL__
    sema_init(&g_adp_rfile.semList, 1);
#else /* __VXWORKS__ */
    g_adp_rfile.semList = semBCreate(SEM_Q_FIFO, (SEM_B_STATE)SEM_FULL);
#endif /* end of __KERNEL__ */

}

/*lint -save -e564 -e830*/
struct rfile_dirent_info * adp_get_node(DRV_DIR_S *dirp)
{
    int ret;
    struct list_head *me = NULL;
    struct rfile_dirent_info *pstDirent = NULL;

    if(NULL == dirp)
    {
        return NULL;
    }

    ret = osl_sem_downtimeout(&g_adp_rfile.semList, RFILE_TIMEOUT_MAX);
    if(0 != ret)
    {
        return NULL;
    }

    list_for_each(me, &g_adp_rfile.rfile_listhead)
    {
        pstDirent = list_entry(me, struct rfile_dirent_info, stlist);

        if((NULL != pstDirent) && (dirp == pstDirent->phandle))
        {
            break;
        }
        else
        {
            pstDirent = NULL;
        }
    }

    osl_sem_up(&g_adp_rfile.semList);

    return pstDirent;
}
/*lint -restore*/
int adp_add_node(struct rfile_dirent_info *pdirent_list)
{
    int ret;

    ret = osl_sem_downtimeout(&g_adp_rfile.semList, RFILE_TIMEOUT_MAX);
    if(0 != ret)
    {
        return -1;
    }

    list_add(&pdirent_list->stlist, &g_adp_rfile.rfile_listhead);

    osl_sem_up(&g_adp_rfile.semList);

    return 0;
}

/*lint -save -e438 -e830*/
void adp_del_node(DRV_DIR_S *dirp)
{
    int ret;
    struct list_head *me = NULL;
    struct rfile_dirent_info *pstDirent = NULL;

    if(NULL == dirp)
    {
        return ;
    }

    ret = osl_sem_downtimeout(&g_adp_rfile.semList, RFILE_TIMEOUT_MAX);
    if(0 != ret)
    {
        return ;
    }

    list_for_each(me, &g_adp_rfile.rfile_listhead)
    {
        pstDirent = list_entry(me, struct rfile_dirent_info, stlist);

        if((NULL != pstDirent) && (dirp == pstDirent->phandle))
        {
            list_del(&pstDirent->stlist);
            Rfile_Free(pstDirent->pdirent);
            Rfile_Free(pstDirent);
            break;
        }
    }

    osl_sem_up(&g_adp_rfile.semList);

    return ;
}
/*lint -restore*/

/*lint -save -e64 -e813 -e438 -e830 -e958 -e529*/

DRV_DIRENT_S* mdrv_file_readdir(DRV_DIR_S *dirp)
{
    int ret;
    char data[1024] = {0};
    struct rfile_dirent_info *pstDirent = NULL;
    RFILE_DIRENT_STRU *pdirent;
    RFILE_DIRENT_STRU *pdirentcur;

    if(0 == dirp)
    {
        g_err = 1;
        return 0;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    pstDirent = adp_get_node(dirp);

    if(NULL == pstDirent)
    {
        ret = bsp_readdir((unsigned int)dirp->dd_fd, data, 1024);

        if(ret <= 0)
        {
            return 0;
        }

        /* coverity[alloc_fn] */
        pdirent = (RFILE_DIRENT_STRU*)Rfile_Malloc(1024);
        if(!pdirent)
        {
            return 0;
        }

        /* coverity[alloc_fn] */
        pstDirent = Rfile_Malloc(sizeof(struct rfile_dirent_info));
        if(!pstDirent)
        {
            Rfile_Free(pdirent);
            return 0;
        }

        /* coverity[noescape] */
        memcpy((void*)pdirent, data, (unsigned int)ret);

        pstDirent->phandle = dirp;

        /* coverity[var_assign] */
        pstDirent->pdirent = pdirent;
        pstDirent->len = ret;
        pstDirent->ptr = 0;

        /* coverity[noescape] */
        if((ret = adp_add_node(pstDirent)) != 0)
        {
            Rfile_Free(pdirent);
            Rfile_Free(pstDirent);
            return 0;
        }
    }

    if(pstDirent->ptr >= pstDirent->len)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
            "[%s] ptr %d, len %d.\n", __FUNCTION__, pstDirent->ptr, pstDirent->len);
        return 0;
    }

    /* coverity[var_assign] */
    pdirentcur = (RFILE_DIRENT_STRU *)((u8*)(pstDirent->pdirent) + pstDirent->ptr);
    g_stdirent.d_ino = pdirentcur->d_ino;

    memset((void*)g_stdirent.d_name, 0, (DRV_NAME_MAX+1));

    if(strlen((char*)pdirentcur->d_name) > DRV_NAME_MAX)
    {
        memcpy(g_stdirent.d_name, pdirentcur->d_name, DRV_NAME_MAX);
    }
    else
    {
        /* coverity[secure_coding] */
        strcpy(g_stdirent.d_name, (char*)pdirentcur->d_name); /* [false alarm]:fortify */
    }

    pstDirent->ptr += pdirentcur->d_reclen;

    /* coverity[leaked_storage] */
    return &g_stdirent;
}

int mdrv_file_closedir(DRV_DIR_S *dirp)
{
    int ret;

    if(0 == dirp)
    {
        g_err = 1;
        return -1;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    adp_del_node(dirp);

    ret = bsp_closedir(dirp->dd_fd);
    if(0 == ret)
    {
        ret =rfile_stdioDirDestroy(dirp);
    }

    return ret;
}

int mdrv_file_get_stat(const char *path, DRV_STAT_S*buf)
{
    int ret;
    struct rfile_stat_stru ststat;

    if(0 == buf)
    {
        g_err = 1;
        return -1;
    }
    g_err = RFILE_INVALID_ERROR_NO;

    ret = bsp_stat((s8*)path, &ststat);
    if(0 == ret)
    {
        buf->st_dev = (unsigned long)ststat.dev;
        buf->st_ino = (unsigned long)ststat.ino;
        buf->st_mode = (int)ststat.mode;
        buf->st_nlink = (unsigned long)ststat.nlink;
        buf->st_uid = (unsigned short)ststat.uid;
        buf->st_gid = (unsigned short)ststat.gid;
        buf->st_rdev = (unsigned long)ststat.rdev;
        buf->st_size = (signed long long)ststat.size;
        buf->st_atime = (unsigned long)ststat.atime.tv_sec;
        buf->st_mtime = (unsigned long)ststat.mtime.tv_sec;
        buf->st_ctime = (unsigned long)ststat.ctime.tv_sec;
        buf->st_blksize = (long)ststat.blksize;
        buf->st_blocks = (unsigned long)ststat.blocks;
        buf->st_attrib = 0;
    }

    return ret;
}

int mdrv_file_access(const char *path, int amode)
{
    return bsp_access((s8*)path, amode);
}


int mdrv_file_rename(const char *oldname, const char *newname)
{
    return bsp_rename(oldname, newname);
}


int xcopy_filecopy(const char *source,const char *dest)
{
    int ret, pfile_s, pfile_d;
    int size;
    unsigned char *psrc;

    pfile_s = bsp_open((const s8 *)source, (RFILE_CREAT|RFILE_RDWR), 0755);
    if(pfile_s < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_open source failed.\n", __FUNCTION__);

        return -1;
    }

    /* get size of source file */
    ret = bsp_lseek((unsigned int)pfile_s, 0, SEEK_END);
    if(ret < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_lseek 0 failed.\n", __FUNCTION__);
        bsp_close((unsigned int)pfile_s);
        return -1;
    }
    else if(0 == ret)               /* if source file is empty,create empty dest file */
    {
        /* coverity[check_return] */
        pfile_d = bsp_open((const s8 *)dest, (RFILE_CREAT|RFILE_RDWR), 0755);
        /* coverity[unchecked_value] */
        bsp_close((unsigned int)pfile_d);
        return 0;
    }

    size = ret;

    psrc = Rfile_Malloc((unsigned int)size);
    if(NULL == psrc)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] Rfile_Malloc failed.\n", __FUNCTION__);
        bsp_close((unsigned int)pfile_s);
        return -1;
    }

    ret = bsp_lseek((unsigned int)pfile_s, 0, SEEK_SET);
    if(ret < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_lseek 1 failed.\n", __FUNCTION__);

        Rfile_Free(psrc);
        bsp_close((unsigned int)pfile_s);
        return -1;
    }

    /* get content of source file */
    ret = bsp_read((unsigned int)pfile_s, (s8*)psrc, (unsigned int)size);
    if(ret != size)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_read failed.\n", __FUNCTION__);

        Rfile_Free(psrc);
        bsp_close((unsigned int)pfile_s);
        return -1;
    }

    bsp_close((unsigned int)pfile_s);

    /* create dest file */
    /* coverity[example_assign] */
    pfile_d = bsp_open((const s8 *)dest, (RFILE_CREAT|RFILE_RDWR), 0755);
    /* coverity[example_checked] */
    if(pfile_d < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_open dest failed.\n", __FUNCTION__);

        Rfile_Free(psrc);
        return -1;
    }

    ret = bsp_lseek((unsigned int)pfile_d, 0, SEEK_SET);
    if(ret < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_lseek 2 failed.\n", __FUNCTION__);

        Rfile_Free(psrc);
        bsp_close((unsigned int)pfile_d);
        return -1;
    }

    /* copy dest file */
    ret = bsp_write((unsigned int)pfile_d, (s8*)psrc, (unsigned int)size);

    Rfile_Free(psrc);
    bsp_close((unsigned int)pfile_d);

    if(ret != size)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_write failed.\n", __FUNCTION__);

        return -1;
    }

    return 0;
}


#define RFILE_DIRENT_LEN        1024
int xcopy_sourcedest(const char *source,const char *dest)
{
    int ret;
    int pfile;
    /* coverity[var_decl] */
    struct rfile_stat_stru s_stat,d_stat;
    char *pdirent;
    RFILE_DIRENT_STRU *pstDirent;
    char *psubdir_s = NULL;
    char *psubdir_d = NULL;
    int dir;
    int i;

    ret = bsp_stat((s8*)source, &s_stat);
    if(ret < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_stat source failed.\n", __FUNCTION__);

        return ret;
    }

    ret = bsp_stat((s8*)dest, &d_stat);

    if(ret < 0) /* 目标文件或目录不存在 */
    {
        /* coverity[uninit_use] */
        if(S_ISDIR(s_stat.mode))    /* 源是目录 */
        {
            ret = bsp_mkdir((s8*)dest, 0660);
            if(0 != ret)
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_mkdir failed.\n", __FUNCTION__);
                return ret;
            }
        }
        else        /* 源是文件 */
        {
            /* coverity[example_assign] */
            pfile = bsp_open((const s8*)dest, (RFILE_CREAT|RFILE_RDWR), 0755);  /* TODO: mode */
            /* coverity[example_checked] */
            if(pfile < 0)
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_open failed.\n", __FUNCTION__);
                return -1;
            }
        }

        /* 递归调用 */
        xcopy_sourcedest(source, dest);
    }
    else    /* 目标文件或目录存在 */
    {
        /* coverity[uninit_use] */
        if(S_ISDIR(s_stat.mode))    /* 源是目录 */
        {
            /* coverity[uninit_use] */
            if(!S_ISDIR(d_stat.mode))   /* 目标不是目录 */
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] src is dir,dest is file.\n", __FUNCTION__);
                return -1;
            }

            dir = bsp_opendir((s8*)source);
            if(dir < 0)
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_opendir failed.\n", __FUNCTION__);
                return -1;
            }

            pdirent = Rfile_Malloc(RFILE_DIRENT_LEN);  /* 缓存子目录的名称 */
            if(NULL == pdirent)
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] malloc failed.\n", __FUNCTION__);
                bsp_closedir(dir);
                return -1;
            }

            ret = bsp_readdir((unsigned int)dir, pdirent, RFILE_DIRENT_LEN);
            if(ret <= 0)
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_readdir failed.\n", __FUNCTION__);
                Rfile_Free(pdirent);
                bsp_closedir(dir);
                return -1;
            }
            else
            {
                for(i=0; i<ret; )
                {
                    pstDirent = (RFILE_DIRENT_STRU*)(pdirent + i);
                    i += pstDirent->d_reclen;

                    if(0 == strcmp(".", (char*)pstDirent->d_name))
                    {
                        continue;
                    }
                    else if(0 == strcmp("..", (char*)pstDirent->d_name))
                    {
                        continue;
                    }
                    else
                    {
                        psubdir_s = Rfile_Malloc(strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1);
                        if(NULL == psubdir_s)
                        {
                            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] malloc src failed.\n", __FUNCTION__);
                            Rfile_Free(pdirent);
                            bsp_closedir(dir);
                            return -1;
                        }
                        psubdir_d = Rfile_Malloc(strlen((char*)dest)+1+strlen((char*)pstDirent->d_name)+1);
                        if(NULL == psubdir_d)
                        {
                            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] malloc dst failed.\n", __FUNCTION__);
                            Rfile_Free(pdirent);
                            Rfile_Free(psubdir_s);
                            bsp_closedir(dir);
                            psubdir_s = NULL;
                            return -1;
                        }

                        memset((void*)psubdir_s, 0, (strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1));
                        /* coverity[secure_coding] */
                        strcpy(psubdir_s, source); /* [false alarm]:fortify */
                        /* coverity[secure_coding] */
                        strcat(psubdir_s, "/");
                        /* coverity[secure_coding] */
                        strcat(psubdir_s, (char*)pstDirent->d_name);

                        memset((void*)psubdir_d, 0, (strlen((char*)dest)+1+strlen((char*)pstDirent->d_name)+1));
                        /* coverity[secure_coding] */
                        strcpy(psubdir_d, dest); /* [false alarm]:fortify */
                        /* coverity[secure_coding] */
                        strcat(psubdir_d, "/");
                        /* coverity[secure_coding] */
                        strcat(psubdir_d, (char*)pstDirent->d_name);

                        /* 递归调用 */
                        xcopy_sourcedest(psubdir_s, psubdir_d);

                        Rfile_Free(psubdir_s);
                        Rfile_Free(psubdir_d);
                    }
                }
            }
            bsp_closedir(dir);

            Rfile_Free(pdirent);
        }
        else        /* 源是文件 */
        {
            /* coverity[uninit_use] */
            if(S_ISDIR(d_stat.mode))   /* 目标是目录 */
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] src is file,dest is dir.\n", __FUNCTION__);
                return -1;
            }

            ret = xcopy_filecopy(source, dest);
            if(0 != ret)
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] xcopy_filecopy failed.\n", __FUNCTION__);
                return -1;
            }
        }
    }

    return 0;
}

int mdrv_file_xcopy(const char *source,const char *dest)
{
    int ret;

    if((!source) || (!dest))
    {
        return -1;
    }

    ret = xcopy_sourcedest(source, dest);
    if(0 != ret)
    {
        return -1;
    }

    return 0;
}


int xdelete_source(const char *source)
{
    int ret;
    /* coverity[var_decl] */
    struct rfile_stat_stru s_stat;
    char *pdirent;
    RFILE_DIRENT_STRU *pstDirent;
    char *psubdir_s = NULL;
    int dir;
    int i;

    ret = bsp_stat((s8*)source, &s_stat);
    if(ret < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_stat source failed.\n", __FUNCTION__);

        return ret;
    }

    /* coverity[uninit_use] */
    if(S_ISDIR(s_stat.mode))    /* 源是目录 */
    {
        dir = bsp_opendir((s8*)source);
        if(dir < 0)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_opendir failed.\n", __FUNCTION__);
            return -1;
        }

        pdirent = Rfile_Malloc(RFILE_DIRENT_LEN);  /* 缓存子目录的名称 */
        if(NULL == pdirent)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] malloc failed.\n", __FUNCTION__);
            bsp_closedir(dir);
            return -1;
        }

        ret = bsp_readdir((unsigned int)dir, pdirent, RFILE_DIRENT_LEN);
        if(ret <= 0)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_readdir failed.\n", __FUNCTION__);
            Rfile_Free(pdirent);
            bsp_closedir(dir);
            return -1;
        }
        else
        {
            for(i=0; i<ret; )
            {
                pstDirent = (RFILE_DIRENT_STRU*)(pdirent + i);
                i += pstDirent->d_reclen;

                if(0 == strcmp(".", (char*)pstDirent->d_name))
                {
                    continue;
                }
                else if(0 == strcmp("..", (char*)pstDirent->d_name))
                {
                    continue;
                }
                else
                {
                    psubdir_s = Rfile_Malloc(strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1);
                    if(NULL == psubdir_s)
                    {
                        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] malloc src failed.\n", __FUNCTION__);
                        Rfile_Free(pdirent);
                        bsp_closedir(dir);
                        return -1;
                    }

                    memset((void*)psubdir_s, 0, (strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1));
                    /* coverity[secure_coding] */
                    strcpy(psubdir_s, source); /* [false alarm]:fortify */
                    /* coverity[secure_coding] */
                    strcat(psubdir_s, "/");
                    /* coverity[secure_coding] */
                    strcat(psubdir_s, (char*)pstDirent->d_name);

                    /* 递归调用 */
                    xdelete_source(psubdir_s);

                    Rfile_Free(psubdir_s);
                }
            }
        }

        Rfile_Free(pdirent);

        bsp_closedir(dir);

        bsp_rmdir((s8*)source);
    }
    else        /* 源是文件 */
    {
        bsp_remove((const s8 *)source);
    }

    return 0;
}

int mdrv_file_xdelete(const char *source)
{
    int ret;

    if(!source)
    {
        return -1;
    }

    ret = xdelete_source(source);
    if(0 != ret)
    {
        return -1;
    }

    return 0;
}
/*lint -restore*/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


