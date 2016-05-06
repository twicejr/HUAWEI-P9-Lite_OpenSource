/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : adp_rfile.c
  版 本 号   : 初稿
  作    者   : c64416
  生成日期   : 2013年2月4日
  最近修改   :
  功能描述   : 适配V7R1文件系统
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月4日
    作    者   : c64416
    修改内容   : 创建文件

******************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rfile_balong.h"
#include "bsp_rfile.h"  /*lint !e537*/
#include "mdrv_rfile_common.h"
#include "osl_malloc.h"
#include "securec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef __KERNEL__

#define rfile_print_info        printk

#else /* __VXWORKS__ */

#define rfile_print_info        printf

#endif /* end of __KERNEL__ */

#ifndef S_ISDIR
#define S_ISDIR(m) ((m)&(0x4000))
#endif

typedef struct
{
    void *      context;        /* 0x00: WRS defined context */
    u32         magic;          /* 0x04: magic. Used in HANDLE_VERIFY() */
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

extern struct bsp_rfile_main_stru g_stRfileMain;

#define RFILE_INVALID_ERROR_NO      0xa5a5a5a5

unsigned long g_err = RFILE_INVALID_ERROR_NO;

extern int rfile_getmode(const char *mode, int *flag);
extern RFILE_FILE *rfile_stdioFpCreate (void);
extern int rfile_stdioFpDestroy(RFILE_FILE *fp);
extern struct rfile_dirent_info * adp_get_node(DRV_DIR_S *dirp);
extern int adp_add_node(struct rfile_dirent_info *pdirent_list);
extern void adp_del_node(DRV_DIR_S *dirp);
extern int xcopy_sourcedest(const char *source,const char *dest);
extern int xdelete_source(const char *source);
extern DRV_DIR_S *rfile_stdioDirCreate (void);
extern int rfile_stdioDirDestroy(DRV_DIR_S *dir);
extern int xcopy_filecopy(const char *source,const char *dest);


unsigned long mdrv_file_get_errno()
{
    if(RFILE_INVALID_ERROR_NO == g_err)
    {
        return (unsigned long)(g_stRfileMain.errorno);
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
        fp->taskId      = 0;

        fp->handle.magic        = (u32) (&fp->handle);
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
        g_err = 1;/* [false alarm]:alarm */
        return (NULL);
    }
    /* [false alarm]:alarm */
    g_err = RFILE_INVALID_ERROR_NO;
    /* [false alarm]:alarm */
    ret = bsp_open((const s8 *)path, oflags, 0755);
    if(ret < 0)
    {
        ret = rfile_stdioFpDestroy (fp);      /* destroy file pointer */
        g_err = (u32)ret;
        return 0;
    }
    /* [false alarm]:alarm */
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
        ret = rfile_stdioFpDestroy(fp);/* [false alarm]:alarm */
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
    g_err = RFILE_INVALID_ERROR_NO;/* [false alarm]:alarm */
    /* [false alarm]:alarm */
    ret = bsp_lseek(((RFILE_FILE*)stream)->_file, offset, whence);/* [false alarm]:alarm */
    if(ret < 0)
    {
        return -1;
    }
    /* [false alarm]:alarm */
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

    /* coverity[alloc_fn] */
    if ((dir = (DRV_DIR_S *)Rfile_Malloc(sizeof(DRV_DIR_S))) != NULL)
    {
        dir->dd_fd      = -1;
        dir->dd_cookie  = 0;
        dir->dd_eof     = 0;

        (void)memset_s(&dir->dd_dirent, sizeof(DRV_DIRENT_S), 0, sizeof(DRV_DIRENT_S));
    }

    return (dir);
}


int rfile_stdioDirDestroy(DRV_DIR_S *dir)
{
    if(NULL == dir)
        return -1;

    dir->dd_fd = -1;
    (void)memset_s(&dir->dd_dirent, sizeof(DRV_DIRENT_S), 0, sizeof(DRV_DIRENT_S));

    Rfile_Free ((char *) dir);

    return 0;
}


DRV_DIR_S* mdrv_file_opendir(const char *dirName)
{
    int ret;
    DRV_DIR_S *dir;

    /* coverity[alloc_fn] */
    if((0 == dirName)
        || ((dir = rfile_stdioDirCreate ()) == NULL)) /* [false alarm]:fortify */
    {
        g_err = 1;
        return NULL;
    }
    g_err = RFILE_INVALID_ERROR_NO;/* [false alarm]:alarm */
    /* [false alarm]:alarm */
    ret = bsp_opendir((s8*)dirName);

    if(ret < 0)
    {
        return 0;
    }
    /* [false alarm]:alarm */
    dir->dd_fd = ret;/* [false alarm]:alarm */
    (void)memcpy_s(dir->dd_dirent.d_name, DRV_NAME_MAX + 1, dirName, strlen(dirName));
    /* [false alarm]:alarm */
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
};/*lint !e959*/

struct rfile_adp_ctrl g_adp_rfile;

void adp_rfile_init()
{
    INIT_LIST_HEAD(&g_adp_rfile.rfile_listhead);

    osl_sem_init(1, &g_adp_rfile.semList);
}


struct rfile_dirent_info * adp_get_node(DRV_DIR_S *dirp)
{
    int ret;
    struct list_head *me = NULL;
    struct rfile_dirent_info *pstDirent = NULL;

    ret = osl_sem_downtimeout(&g_adp_rfile.semList, RFILE_TIMEOUT_MAX);
    if(0 != ret)
    {
        return NULL;
    }

    list_for_each(me, &g_adp_rfile.rfile_listhead)
    {
        pstDirent = list_entry(me, struct rfile_dirent_info, stlist);

        if(dirp == pstDirent->phandle)
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


void adp_del_node(DRV_DIR_S *dirp)
{
    int ret;
    struct list_head *me = NULL;
    struct rfile_dirent_info *pstDirent = NULL;

    ret = osl_sem_downtimeout(&g_adp_rfile.semList, RFILE_TIMEOUT_MAX);
    if(0 != ret)
    {
        return ;
    }

    list_for_each(me, &g_adp_rfile.rfile_listhead)
    {
        pstDirent = list_entry(me, struct rfile_dirent_info, stlist);

        if(dirp == pstDirent->phandle)
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

        pdirent = (RFILE_DIRENT_STRU*)Rfile_Malloc(1024);
        if(!pdirent)
        {
            return 0;
        }

        pstDirent = Rfile_Malloc(sizeof(struct rfile_dirent_info));
        if(!pstDirent)
        {
            Rfile_Free(pdirent); /* [false alarm]:fortify */
            return 0;
        }

        (void)memcpy_s((void*)pdirent, 1024, data, (unsigned int)ret);

        pstDirent->phandle = dirp;
        pstDirent->pdirent = pdirent;
        pstDirent->len = ret;
        pstDirent->ptr = 0;

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

    pdirentcur = (RFILE_DIRENT_STRU *)((u8*)(pstDirent->pdirent) + pstDirent->ptr);
    g_stdirent.d_ino = (DRV_INO_T)pdirentcur->d_ino;

    (void)memset_s((void*)g_stdirent.d_name, (DRV_NAME_MAX+1),0, (DRV_NAME_MAX+1));

    if(strlen((char*)pdirentcur->d_name) > DRV_NAME_MAX)
    {
        (void)memcpy_s(g_stdirent.d_name, DRV_NAME_MAX+1, pdirentcur->d_name, DRV_NAME_MAX);
    }
    else
    {
        /* coverity[secure_coding] */
        (void)strcpy_s(g_stdirent.d_name, DRV_NAME_MAX + 1, (char*)pdirentcur->d_name); /* [false alarm]:fortify */
    }

    pstDirent->ptr += pdirentcur->d_reclen;

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
        ret =rfile_stdioDirDestroy(dirp);/* [false alarm]:alarm */
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
        buf->st_dev = ststat.dev;/* [false alarm]:alarm */
        buf->st_ino = (unsigned long)ststat.ino;
        buf->st_mode = ststat.mode;
        buf->st_nlink = ststat.nlink;
        buf->st_uid = (unsigned short)ststat.uid;
        buf->st_gid = (unsigned short)ststat.gid;
        buf->st_rdev = ststat.rdev;
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
    int ret, pfile_s, pfile_d;/* [false alarm]:alarm */
    int size;/* [false alarm]:alarm */
    unsigned char *psrc;/* [false alarm]:alarm */
    /* [false alarm]:alarm */
    pfile_s = bsp_open((const s8 *)source, (RFILE_CREAT|RFILE_RDWR), 0755);
    if(pfile_s < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_open source failed.\n", __FUNCTION__);

        return -1;
    }

    /* get size of source file */
    ret = bsp_lseek((unsigned int)pfile_s, 0, SEEK_END);/* [false alarm]:alarm */
    if(ret < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_lseek 0 failed.\n", __FUNCTION__);
        (void)bsp_close((unsigned int)pfile_s);
        return -1;
    }
    else if(0 == ret)               /* if source file is empty,create empty dest file */
    {
        pfile_d = bsp_open((const s8 *)dest, (RFILE_CREAT|RFILE_RDWR), 0755);/* [false alarm]:alarm */
        (void)bsp_close((unsigned int)pfile_d);
        return 0;
    }

    size = ret;/* [false alarm]:alarm */

    psrc = Rfile_Malloc((unsigned int)size);
    if(NULL == psrc)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] Rfile_Malloc failed.\n", __FUNCTION__); /* [false alarm]:fortify */
        (void)bsp_close((unsigned int)pfile_s);
        return -1;
    }

    ret = bsp_lseek((unsigned int)pfile_s, 0, SEEK_SET);
    if(ret < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_lseek 1 failed.\n", __FUNCTION__);

        Rfile_Free(psrc);
        (void)bsp_close((unsigned int)pfile_s);
        return -1;
    }

    /* get content of source file *//* [false alarm]:alarm */
    ret = bsp_read((unsigned int)pfile_s, (s8*)psrc, (unsigned int)size);
    if(ret != size)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_read failed.\n", __FUNCTION__);

        Rfile_Free(psrc);
        (void)bsp_close((unsigned int)pfile_s);
        return -1;
    }

    (void)bsp_close((unsigned int)pfile_s);

    /* create dest file */
    pfile_d = bsp_open((const s8 *)dest, (RFILE_CREAT|RFILE_RDWR), 0755);
    if(pfile_d < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_open dest failed.\n", __FUNCTION__);

        Rfile_Free(psrc);
        return -1;
    }

    ret = bsp_lseek((unsigned int)pfile_d, 0, SEEK_SET);/* [false alarm]:alarm */
    if(ret < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_lseek 2 failed.\n", __FUNCTION__);

        Rfile_Free(psrc);
        (void)bsp_close((unsigned int)pfile_d);
        return -1;
    }

    /* copy dest file *//* [false alarm]:alarm */
    ret = bsp_write((unsigned int)pfile_d, (s8*)psrc, (unsigned int)size);

    Rfile_Free(psrc);
    (void)bsp_close((unsigned int)pfile_d);

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
    int ret;/* [false alarm]:alarm */
    int pfile;/* [false alarm]:alarm */
    struct rfile_stat_stru s_stat,d_stat;/* [false alarm]:alarm */
    char *pdirent;/* [false alarm]:alarm */
    RFILE_DIRENT_STRU *pstDirent;/* [false alarm]:alarm */
    char *psubdir_s = NULL;/* [false alarm]:alarm */
    char *psubdir_d = NULL;/* [false alarm]:alarm */
    int dir;/* [false alarm]:alarm */
    int i;/* [false alarm]:alarm */
    unsigned int len;/* [false alarm]:alarm */
    /* [false alarm]:alarm */
    ret = bsp_stat((s8*)source, &s_stat);
    if(ret < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_stat source failed.\n", __FUNCTION__);

        return ret;
    }

    ret = bsp_stat((s8*)dest, &d_stat);/* [false alarm]:alarm */

    if(ret < 0) /* 目标文件或目录不存在 */
    {
        /* coverity[result_independent_of_operands] */
        if(S_ISDIR(s_stat.mode))    /*lint !e650*//* 源是目录 */
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
            pfile = bsp_open((const s8*)dest, (RFILE_CREAT|RFILE_RDWR), 0755);  /* TODO: mode */
            if(pfile < 0)
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_open failed.\n", __FUNCTION__);
                return -1;
            }
        }

        /* 递归调用 *//* [false alarm]:alarm */
        (void)xcopy_sourcedest(source, dest);
    }
    else    /* 目标文件或目录存在 */
    {
        /* coverity[result_independent_of_operands] */
        if(S_ISDIR(s_stat.mode))   /*lint !e650*/ /* 源是目录 *//* [false alarm]:alarm */
        {
            /* coverity[result_independent_of_operands] */
            if(!S_ISDIR(d_stat.mode))   /*lint !e650*//* 目标不是目录 *//* [false alarm]:alarm */
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
            /* [false alarm]:alarm */
            pdirent = Rfile_Malloc(RFILE_DIRENT_LEN);  /* 缓存子目录的名称 */
            if(NULL == pdirent)
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] malloc failed.\n", __FUNCTION__); /* [false alarm]:fortify */
                (void)bsp_closedir(dir);
                return -1;
            }

            ret = bsp_readdir((unsigned int)dir, pdirent, RFILE_DIRENT_LEN);
            if(ret <= 0)
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_readdir failed.\n", __FUNCTION__);
                Rfile_Free(pdirent);
                (void)bsp_closedir(dir);
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
                        len = strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1;
                        psubdir_s = Rfile_Malloc(len);
                        if(NULL == psubdir_s)
                        {
                            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] malloc src failed.\n", __FUNCTION__); /* [false alarm]:fortify */
                            Rfile_Free(pdirent);
                            (void)bsp_closedir(dir);
                            return -1;
                        }

                        len = strlen((char*)dest)+1+strlen((char*)pstDirent->d_name)+1;
                        psubdir_d = Rfile_Malloc(len);
                        if(NULL == psubdir_d)
                        {
                            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] malloc dst failed.\n", __FUNCTION__); /* [false alarm]:fortify */
                            Rfile_Free(pdirent);
                            Rfile_Free(psubdir_s);
                            (void)bsp_closedir(dir);
                            psubdir_s = NULL;
                            return -1;
                        }

                        (void)memset_s((void*)psubdir_s,(strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1), 0, (strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1));
                        /* coverity[secure_coding] */
                        (void)strcpy_s(psubdir_s, strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1, source); /* [false alarm]:fortify */
                        /* coverity[secure_coding] */
                        (void)strcat_s(psubdir_s, strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1, "/"); /* [false alarm]:fortify */
                        /* coverity[secure_coding] */
                        (void)strcat_s(psubdir_s, strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1, (char*)pstDirent->d_name); /* [false alarm]:fortify */

                        (void)memset_s((void*)psubdir_d, (strlen((char*)dest)+1+strlen((char*)pstDirent->d_name)+1), 0, (strlen((char*)dest)+1+strlen((char*)pstDirent->d_name)+1));
                        /* coverity[secure_coding] */
                        (void)strcpy_s(psubdir_d, strlen((char*)dest)+1+strlen((char*)pstDirent->d_name)+1, dest); /* [false alarm]:fortify */
                        /* coverity[secure_coding] */
                        (void)strcat_s(psubdir_d, strlen((char*)dest)+1+strlen((char*)pstDirent->d_name)+1, "/"); /* [false alarm]:fortify */
                        /* coverity[secure_coding] */
                        (void)strcat_s(psubdir_d, strlen((char*)dest)+1+strlen((char*)pstDirent->d_name)+1, (char*)pstDirent->d_name); /* [false alarm]:fortify */

                        /* 递归调用 */
                        (void)xcopy_sourcedest(psubdir_s, psubdir_d);

                        Rfile_Free(psubdir_s);
                        Rfile_Free(psubdir_d);
                    }
                }
            }
            (void)bsp_closedir(dir);

            Rfile_Free(pdirent);
        }
        else        /* 源是文件 */
        {
            /* coverity[result_independent_of_operands] */
            if(S_ISDIR(d_stat.mode))   /*lint !e650*//* 目标是目录 */
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
    int ret;/* [false alarm]:alarm */
    struct rfile_stat_stru s_stat;/* [false alarm]:alarm */
    char *pdirent;/* [false alarm]:alarm */
    RFILE_DIRENT_STRU *pstDirent;/* [false alarm]:alarm */
    char *psubdir_s = NULL;/* [false alarm]:alarm */
    int dir;/* [false alarm]:alarm */
    int i;/* [false alarm]:alarm */
    unsigned int len;

    ret = bsp_stat((s8*)source, &s_stat);
    if(ret < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_stat source failed.\n", __FUNCTION__);

        return ret;
    }
    /* coverity[result_independent_of_operands] */
    if(S_ISDIR(s_stat.mode))   /*lint !e650*/ /* 源是目录 *//* [false alarm]:alarm */
    {
        dir = bsp_opendir((s8*)source);
        if(dir < 0)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_opendir failed.\n", __FUNCTION__);
            return -1;
        }
        /* [false alarm]:alarm */
        pdirent = Rfile_Malloc(RFILE_DIRENT_LEN);  /* 缓存子目录的名称 */
        if(NULL == pdirent)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] malloc failed.\n", __FUNCTION__); /* [false alarm]:fortify */
            (void)bsp_closedir(dir);
            return -1;
        }

        ret = bsp_readdir((unsigned int)dir, pdirent, RFILE_DIRENT_LEN);
        if(ret <= 0)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] bsp_readdir failed.\n", __FUNCTION__);
            Rfile_Free(pdirent);
            (void)bsp_closedir(dir);
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
                    len = strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1;
                    psubdir_s = Rfile_Malloc(len);
                    if(NULL == psubdir_s)
                    {
                        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[%s] malloc src failed.\n", __FUNCTION__); /* [false alarm]:fortify */
                        Rfile_Free(pdirent);
                        (void)bsp_closedir(dir);
                        return -1;
                    }

                    (void)memset_s((void*)psubdir_s,(strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1), 0, (strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1));
                    /* coverity[secure_coding] */
                    (void)strcpy_s(psubdir_s, strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1, source); /* [false alarm]:fortify */
                    /* coverity[secure_coding] */
                    (void)strcat_s(psubdir_s, strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1, "/"); /* [false alarm]:fortify */
                    /* coverity[secure_coding] */
                    (void)strcat_s(psubdir_s, strlen((char*)source)+1+strlen((char*)pstDirent->d_name)+1, (char*)pstDirent->d_name); /* [false alarm]:fortify */

                    /* 递归调用 */
                    (void)xdelete_source(psubdir_s);

                    Rfile_Free(psubdir_s);
                }
            }
        }

        Rfile_Free(pdirent);

        (void)bsp_closedir(dir);

        (void)bsp_rmdir((s8*)source);
    }
    else        /* 源是文件 */
    {
        (void)bsp_remove((const s8 *)source);
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


