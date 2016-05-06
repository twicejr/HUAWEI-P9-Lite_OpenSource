

#include <linux/module.h>
#include <linux/platform_device.h>

#include "mdrv.h"
#include "bsp_pm_om.h"
#include "bsp_nandc.h"

#include "rfile_balong.h"


/*lint --e{830, 529, 533, 64, 732, 737,607}*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define RFILE_AUTO_MKDIR

struct bsp_rfile_main_stru g_stRfileMain = {EN_RFILE_INIT_INVALID, };


typedef s32 (*RFILE_REQ_FUN)(void *pstRfileQue, u32 ulId);


struct bsp_rfile_table_stru
{
    u32                             enRfileType;
    void                            *pFun;
};


/* 接收C核的请求处理函数表 */
struct bsp_rfile_table_stru astAcoreRfileReq[] = {
    {EN_RFILE_OP_OPEN,              rfile_AcoreOpenReq},
    {EN_RFILE_OP_CLOSE,             rfile_AcoreCloseReq},
    {EN_RFILE_OP_WRITE,             rfile_AcoreWriteReq},
    {EN_RFILE_OP_WRITE_SYNC,        rfile_AcoreWriteSyncReq},
    {EN_RFILE_OP_READ,              rfile_AcoreReadReq},
    {EN_RFILE_OP_SEEK,              rfile_AcoreSeekReq},
    {EN_RFILE_OP_TELL,              rfile_AcoreTellReq},
    {EN_RFILE_OP_REMOVE,            rfile_AcoreRemoveReq},
    {EN_RFILE_OP_MKDIR,             rfile_AcoreMkdirReq},
    {EN_RFILE_OP_RMDIR,             rfile_AcoreRmdirReq},
    {EN_RFILE_OP_OPENDIR,           rfile_AcoreOpendirReq},
    {EN_RFILE_OP_READDIR,           rfile_AcoreReaddirReq},
    {EN_RFILE_OP_CLOSEDIR,          rfile_AcoreClosedirReq},
    {EN_RFILE_OP_STAT,              rfile_AcoreStatReq},
    {EN_RFILE_OP_ACCESS,            rfile_AcoreAccessReq},
    {EN_RFILE_OP_MASSRD,            rfile_AcoreMassrdReq},
    {EN_RFILE_OP_MASSWR,            rfile_AcoreMasswrReq},
    {EN_RFILE_OP_RENAME,            rfile_AcoreRenameReq},
};

struct rfile_mntn_stru g_stRfileMntnInfo;

s8 * rfileerror = (s8*)"error";

s32 rfile_lpmcallback(int x)
{
    g_stRfileMain.lpmstate = 1;
	return 0;
}

s8 *rfile_getdirpath(s32 fp)
{
    struct list_head *p, *n;
    struct dir_list *tmp;

    list_for_each_safe(p,n,&(g_stRfileMain.dplist))
    {
        tmp = list_entry(p, struct dir_list ,stlist);
        if (tmp->dp == fp)
        {
            return tmp->name;
        }
    }

    return rfileerror;
}

s8 *rfile_getfilepath(s32 fp)
{
    struct list_head *p, *n;
    struct fp_list *tmp;

    list_for_each_safe(p,n,&(g_stRfileMain.fplist))
    {
        tmp = list_entry(p, struct fp_list ,stlist);
        if (tmp->fp == fp)
        {
            return tmp->name;
        }
    }

    return rfileerror;
}

#define RFILE_LPM_PRINT_PATH(op, path) \
do{ \
    if(g_stRfileMain.lpmstate) \
    { \
        char rfile_pm[256];\
        snprintf(rfile_pm,256,"op %d,path %s.\n",op,path);\
        bsp_pm_log(PM_OM_ARFILE, strlen(rfile_pm),rfile_pm);\
        g_stRfileMain.lpmstate = 0; \
        printk("[C SR] rfile op %d, path %s.\n", op, path); \
    } \
}while(0);

#define RFILE_LPM_PRINT_DIRPATH(op, fd) \
do{ \
    if(g_stRfileMain.lpmstate) \
    { \
        char rfile_pm[256];\
        snprintf(rfile_pm,256,"op %d,path %s.\n",op,rfile_getdirpath((s32)fd));\
        bsp_pm_log(PM_OM_ARFILE, strlen(rfile_pm),rfile_pm);\
        g_stRfileMain.lpmstate = 0; \
        printk("[C SR] rfile op %d, path %s.\n", op, rfile_getdirpath((s32)fd)); \
    } \
}while(0);

#define RFILE_LPM_PRINT_FILEPATH(op, fd) \
do{ \
    if(g_stRfileMain.lpmstate) \
    { \
        char rfile_pm[256];\
        snprintf(rfile_pm,256,"op %d,path %s.\n",op,rfile_getfilepath((s32)fd));\
        bsp_pm_log(PM_OM_ARFILE, strlen(rfile_pm),rfile_pm);\
        g_stRfileMain.lpmstate = 0; \
        printk("[C SR] rfile op %d, path %s.\n", op, rfile_getfilepath((s32)fd)); \
    } \
}while(0);

void rfile_MntnDotRecord(u32 line)
{
    u32 ptr = g_stRfileMntnInfo.stdot.ptr;
    g_stRfileMntnInfo.stdot.line[ptr] = line;
    g_stRfileMntnInfo.stdot.slice[ptr] = bsp_get_slice_value();
    g_stRfileMntnInfo.stdot.ptr = (g_stRfileMntnInfo.stdot.ptr+1)%RFILE_MNTN_DOT_NUM;
}


/* 查看输入的路径是否可访问，如不能访问则创建此目录 */
/* 本函数为递归调用函数 */
s32 AccessCreate(char *pathtmp, s32 mode)
{
    char *p;
    s32 ret;
    unsigned long old_fs;

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);
    ret = sys_access(pathtmp, 0);
    set_fs(old_fs);

    if(ret != 0)
    {
        /* 路径中不包含'/'，返还失败 */
        p = strrchr(pathtmp, '/');
        if(NULL == p)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
                "[rfile]: <%s> strrchr %s no '/'.\n", __FUNCTION__, pathtmp);

            return -1;
        }

        /* 已经不是根目录下的文件夹，判断上一级目录是否存在 */
        if(p != pathtmp)
        {
            /* 查看上一级目录是否存在，如果不存在则创建此目录 */
            *p = '\0';
            ret = AccessCreate(pathtmp, mode);
            if(0 != ret)
            {
                return -1;
            }

            /* 创建当前目录 */
            *p = '/';
        }

        old_fs = get_fs();
        set_fs((unsigned long)KERNEL_DS);
        ret = sys_mkdir(pathtmp, 0660);
        set_fs(old_fs);

        if(0 != ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
                "[rfile]: <%s> sys_mkdir %s failed ret %d.\n", __FUNCTION__, pathtmp, ret);

            return -1;
        }
    }

    return 0;
}

void rfile_FpListDel(s32 fp)
{
    struct list_head *p, *n;
    struct fp_list *tmp;

    rfile_MntnDotRecord(__LINE__);

    list_for_each_safe(p,n,&(g_stRfileMain.fplist))
    {
        tmp = list_entry(p, struct fp_list ,stlist);
        if (tmp->fp == fp)
        {
            list_del(&tmp->stlist);
            Rfile_Free(tmp);
        }
    }
}

void rfile_FpListAdd(s32 fp, s8 *name)
{
    struct fp_list *fp_elemt;
    u32 len;

    rfile_MntnDotRecord(__LINE__);

    /* coverity[alloc_fn] */
    fp_elemt = (struct fp_list *)Rfile_Malloc(sizeof(struct fp_list));
    if(fp_elemt == NULL)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
            "[rfile]: <%s> malloc fp_elemt failed.\n", __FUNCTION__);

        return;
    }
    fp_elemt->fp=fp;

    len = (u32)strlen(name);
    if(len > RFILE_NAME_MAX)
    {
        len = RFILE_NAME_MAX;
    }

    memcpy(fp_elemt->name, name, (s32)len);
    fp_elemt->name[len] = '\0';

    list_add(&(fp_elemt->stlist), &(g_stRfileMain.fplist));

    /* coverity[leaked_storage] */
    return;
}

void rfile_DpListDel(s32 dp)
{
    struct list_head *p, *n;
    struct dir_list *tmp;

    rfile_MntnDotRecord(__LINE__);

    list_for_each_safe(p,n,&(g_stRfileMain.dplist))
    {
        tmp = list_entry(p, struct dir_list ,stlist);
        if (tmp->dp == dp)
        {
            list_del(&tmp->stlist);
            Rfile_Free(tmp);
        }
    }
}

void rfile_DpListAdd(s32 dp, s8 *name)
{
    struct dir_list *dp_elemt;
    u32 len;

    rfile_MntnDotRecord(__LINE__);

    /* coverity[alloc_fn] */
    dp_elemt=(struct dir_list *)Rfile_Malloc(sizeof(struct dir_list));
    if(dp_elemt == NULL)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
            "[rfile]: <%s> malloc dp_elemt failed.\n", __FUNCTION__);

        return;
    }
    dp_elemt->dp=dp;

    len = (u32)strlen(name);
    if(len > RFILE_NAME_MAX)
    {
        len = RFILE_NAME_MAX;
    }

    memcpy(dp_elemt->name, name, (s32)len);
    dp_elemt->name[len] = '\0';

    list_add(&(dp_elemt->stlist), &(g_stRfileMain.dplist));

    /* coverity[leaked_storage] */
    return;
}

/*************************************************************************
 函 数 名   : rfile_init_done
 功能描述   : 判断rfile模块是否初始化完成
 输入参数   : 无

 返 回 值   : 失败返回-1，成功返回0
*************************************************************************/
static u32 rfile_init_done(void)
{
    if(g_stRfileMain.eInitFlag == EN_RFILE_INIT_INVALID)
    {
        printk(KERN_ERR" rfile_init_done g_stRfileMain.eInitFlag %x!\n",g_stRfileMain.eInitFlag);
        dump_stack();
        return -1;
    }
    return 0;
}
/*************************************************************************
 函 数 名   : bsp_open
 功能描述   : bsp_open
 输入参数   : const s8 *path
              s32 flags
              s32 mode

 返 回 值   : 失败返回-1，成功返回文件句柄

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_open(const s8 *path, s32 flags, s32 mode)
{
    s32 ret = -1;
    unsigned long old_fs;
#ifdef RFILE_AUTO_MKDIR
    char *p;
    char pathtmp[256] = {0};
#endif
    ret=rfile_init_done();
    if(ret)
    {
        return ret;
    }
#ifdef RFILE_AUTO_MKDIR

    rfile_MntnDotRecord(__LINE__);

    if(strlen(path) > 255)
    {
        return ret;
    }

    memcpy(pathtmp, (char *)path, strlen(path));

    /* 路径中包含'/'并且不在根目录，则检查当前目录是否存在，不存在则创建目录 */
    p = strrchr(pathtmp, '/');
    if((NULL != p) && (p != pathtmp))
    {
        /* 查看上一级目录是否存在，如果不存在则创建此目录 */
        *p = '\0';
        ret = AccessCreate(pathtmp, mode);
        if(ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
                "[rfile]: <%s> AccessCreate failed.\n", __FUNCTION__);
        }
    }
#endif

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_open(path, flags, mode); /*lint !e734*/

    set_fs(old_fs);

    return ret;
}

/*************************************************************************
 函 数 名   : bsp_close
 功能描述   : bsp_close
 输入参数   : fd
 输出参数   :
 返 回 值   : 成功返回0，失败返回-1

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_close(u32 fp)
{
    s32 ret;
    unsigned long old_fs;
#ifdef CONFIG_RFILE_MEM_OPTIMISE
	struct file *file_p=NULL;
#endif

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

#ifdef CONFIG_RFILE_MEM_OPTIMISE
	file_p = fget(fp);
	if(file_p && file_p->f_inode)
	{
		invalidate_mapping_pages(file_p->f_inode->i_mapping, 0, -1);
	}
	if(file_p)
	{
		fput(file_p);
	}
#endif

    ret = sys_close(fp);

    set_fs(old_fs);

    return ret;
}


/*************************************************************************
 函 数 名   : bsp_write
 功能描述   : bsp_write
 输入参数   : u32 fd
              const s8 *ptr
              u32 size
 输出参数   :
 返 回 值   : 返回写入的数据长度

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_write(u32 fd, const s8 *ptr, u32 size)
{
    s32 ret = BSP_ERROR;
    unsigned long old_fs;

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_write(fd, ptr, (s32)size);

    set_fs(old_fs);

    return ret;

}

/*************************************************************************
 函 数 名   : bsp_write_sync
 功能描述   : bsp_write_sync
 输入参数   : u32 fd
              const s8 *ptr
              u32 size
 输出参数   :
 返 回 值   : 返回写入的数据长度

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_write_sync(u32 fd, const s8 *ptr, u32 size)
{
    s32 ret = BSP_ERROR;
    unsigned long old_fs;

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_write(fd, ptr, (s32)size);

    (void)sys_fsync(fd);

    set_fs(old_fs);

    return ret;

}

/*************************************************************************
 函 数 名   : bsp_read
 功能描述   : bsp_read
 输入参数   : u32 fd
              s8 *ptr
              u32 size
 返 回 值   : 返回读取的数据长度

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_read(u32 fd, s8 *ptr, u32 size)
{
    s32 ret = BSP_ERROR;
    unsigned long old_fs;

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_read(fd, ptr, (s32)size);

    set_fs(old_fs);

    return ret;

}


/*************************************************************************
 函 数 名   : bsp_lseek
 功能描述   : bsp_lseek
 输入参数   : u32 fd, long offset, s32 whence
 输出参数   :
 返 回 值   : 成功返回0，失败返回-1

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_lseek(u32 fd, long offset, s32 whence)
{
    s32 ret = BSP_ERROR;
    unsigned long old_fs;

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_lseek(fd, offset, (u32)whence);

    set_fs(old_fs);

    return ret;
}


/*************************************************************************
 函 数 名   : bsp_tell
 功能描述   : bsp_tell
 输入参数   : u32 fd
 输出参数   :
 返 回 值   : 成功返回当前读写位置，失败返回-1

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
long bsp_tell(u32 fd)
{
    s32 ret = BSP_ERROR;
    loff_t offset = 0;
    unsigned long old_fs;

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_llseek(fd, 0, 0, &offset, SEEK_CUR);
    if(0 != ret)
    {
    }

    set_fs(old_fs);

    return (long)offset;
}


/*************************************************************************
 函 数 名   : bsp_remove
 功能描述   : bsp_remove
 输入参数   : const s8 *pathname
 输出参数   :
 返 回 值   : 成功返回0，失败返回-1

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_remove(const s8 *pathname)
{
    s32 ret = BSP_ERROR;
    unsigned long old_fs;
    ret=rfile_init_done();
    if(ret)
    {
        return ret;
    }
    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_unlink(pathname);

    set_fs(old_fs);

    return ret;
}


/*************************************************************************
 函 数 名   : bsp_mkdir
 功能描述   : bsp_mkdir
 输入参数   : s8 *dirName
              s32 mode
 返 回 值   :

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_mkdir(s8 *dirName, s32 mode)
{
    s32 ret = BSP_ERROR;
#ifdef RFILE_AUTO_MKDIR
    char pathtmp[255+1] = {0};
#endif
    ret=rfile_init_done();
    if(ret)
    {
        return ret;
    }
#ifdef RFILE_AUTO_MKDIR

    rfile_MntnDotRecord(__LINE__);

    if(strlen(dirName) > 255)
    {
        return ret;
    }

    memcpy(pathtmp, (char *)dirName, strlen(dirName));

    ret = AccessCreate((char *)pathtmp, mode);
    if(ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
            "[rfile]: <%s> AccessCreate failed.\n", __FUNCTION__);
    }
#else
    unsigned long old_fs;

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_mkdir(dirName, mode); /*lint !e734*/

    set_fs(old_fs);
#endif

    return ret;

}


/*************************************************************************
 函 数 名   : bsp_rmdir
 功能描述   : bsp_rmdir
 输入参数   : s8 *path
 返 回 值   : 返回0

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_rmdir(s8 *path)
{
    s32 ret = BSP_ERROR;
    unsigned long old_fs;
    ret=rfile_init_done();
    if(ret)
    {
        return ret;
    }
    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_rmdir(path);

    set_fs(old_fs);

    return ret;

}

/*************************************************************************
 函 数 名   : bsp_opendir
 功能描述   : bsp_opendir
 输入参数   :
 输出参数   :
 返 回 值   : 目录句柄

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_opendir(s8 *dirName)
{
    s32 handle = 0;
    s32 ret=0;
    unsigned long old_fs;
    ret=rfile_init_done();
    if(ret)
    {
        return ret;
    }
    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    handle = sys_open(dirName, RFILE_RDONLY|RFILE_DIRECTORY, 0);

    set_fs(old_fs);

    return handle;
}


/*************************************************************************
 函 数 名   : bsp_readdir
 功能描述   : bsp_readdir
 输入参数   :
 输出参数   :
 返 回 值   : s32

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_readdir(u32 fd, void  *dirent, u32 count)
{
    s32 ret = BSP_ERROR;
    unsigned long old_fs;

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_getdents64(fd, dirent, count);

    set_fs(old_fs);

    return ret;
}


/*************************************************************************
 函 数 名   : bsp_closedir
 功能描述   : bsp_closedir
 输入参数   :
 输出参数   :
 返 回 值   :

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_closedir(s32 pDir)
{
    s32 ret = BSP_ERROR;
    unsigned long old_fs;

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_close((u32)pDir);

    set_fs(old_fs);

    return ret;
}


s32 bsp_access(s8 *path, s32 mode)
{
    s32 ret = BSP_ERROR;
    unsigned long old_fs;
    ret=rfile_init_done();
    if(ret)
    {
        return ret;
    }
    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_access(path, mode);

    set_fs(old_fs);

    return ret;
}


void rfile_TransStat(struct rfile_stat_stru *pstRfileStat, struct kstat *pRfileKstat)
{
    /* 兼容 32位和64位 */
    pstRfileStat->ino               = (u64)pRfileKstat->ino          ;
    pstRfileStat->dev               = (u32)pRfileKstat->dev          ;
    pstRfileStat->mode              = (u16)pRfileKstat->mode         ;
    pstRfileStat->nlink             = (u32)pRfileKstat->nlink        ;
    pstRfileStat->uid               = (u32)pRfileKstat->uid          ;
    pstRfileStat->gid               = (u32)pRfileKstat->gid          ;
    pstRfileStat->rdev              = (u32)pRfileKstat->rdev         ;
    pstRfileStat->size              = (u64)pRfileKstat->size         ;
    pstRfileStat->atime.tv_sec      = (u64)pRfileKstat->atime.tv_sec ;
    pstRfileStat->atime.tv_nsec     = (u64)pRfileKstat->atime.tv_nsec;
    pstRfileStat->ctime.tv_sec      = (u64)pRfileKstat->ctime.tv_sec ;
    pstRfileStat->mtime.tv_nsec     = (u64)pRfileKstat->mtime.tv_nsec;
    pstRfileStat->mtime.tv_sec      = (u64)pRfileKstat->mtime.tv_sec ;
    pstRfileStat->ctime.tv_nsec     = (u64)pRfileKstat->ctime.tv_nsec;
    pstRfileStat->blksize           = (u32)pRfileKstat->blksize      ;
    pstRfileStat->blocks            = (u64)pRfileKstat->blocks       ;
}

/*************************************************************************
 函 数 名   : bsp_stat
 功能描述   : bsp_stat
 输入参数   : s8 *name: 要读取的文件名称
 输出参数   : void *pStat: 文件的状态信息，结构为struct rfile_stat_stru
 返 回 值   : 成功返回0,失败返回-1

 修改历史   :
 日    期   : 2013年2月4日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_stat(s8 *name, void *pStat)
{
    s32 ret = BSP_ERROR;
    struct kstat kstattmp = {0};
    unsigned long old_fs;

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = vfs_stat(name, &kstattmp);
    if(0 == ret)
    {
        rfile_TransStat(pStat, &kstattmp);
    }

    set_fs(old_fs);

    return ret;
}


/*************************************************************************
 函 数 名   : bsp_rename
 功能描述   : bsp_rename
 输入参数   : const char * oldname
              const char * newname
 输出参数   : no
 返 回 值   : 成功返回0,失败返回-1

 修改历史   :
 日    期   : 2013年11月21日
 作    者   : c64416
 修改内容   :

*************************************************************************/
s32 bsp_rename( const char * oldname, const char * newname )
{
    s32 ret = BSP_ERROR;
    unsigned long old_fs;

    if((NULL == oldname)||(NULL == newname))
    {
        return -1;
    }

    rfile_MntnDotRecord(__LINE__);

    old_fs = get_fs();
    set_fs((unsigned long)KERNEL_DS);

    ret = sys_rename(oldname,newname);

    set_fs(old_fs);

    return ret;
}


/*****************************************************************************
 函 数 名  : rfile_IccSend
 功能描述  : 向ICC通道发送数据，如果通道满，则重复尝试多次
 输入参数  :
 输出参数  : 无
 返 回 值  : void

 修改历史      :
  1.日    期   : 2013年10月29日
    作    者   : c64416
    修改内容   : 新生成函数(适配ICC通道回调中不能malloc、信号量阻塞修改)

*****************************************************************************/
void rfile_IccSend(void *pdata, u32 len, u32 ulId)
{
    s32 ret, i;

    rfile_MntnDotRecord(__LINE__);

    for(i = 0; i < RFILE_MAX_SEND_TIMES; i++)
    {
        if(g_stRfileMain.eInitFlag != EN_RFILE_INIT_FINISH)
        {
            return;
        }

        ret = bsp_icc_send(((RFILE_CCORE_ICC_WR_CHAN == ulId)?ICC_CPU_MODEM:ICC_CPU_MCU), ulId, (u8*)pdata, len);

        if(ICC_INVALID_NO_FIFO_SPACE == ret)
        {
            /* buffer满，延时后重发 */
            RFILE_SLEEP(50);
            continue;
        }
		else if(BSP_ERR_ICC_CCORE_RESETTING == ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "![rfile]: <%s> icc  cannot use.\n", __FUNCTION__);
        }
        else if(len != (u32)ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "![rfile]: <%s> icc_send failed.\n", __FUNCTION__);
            return;
        }
        else
        {
            return;
        }
    }
}


/*lint -save -e64*/

/*****************************************************************************
 函 数 名  : rfile_AcoreOpenReq
 功能描述  : fopen的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreOpenReq(struct bsp_rfile_open_req *pstRfileReq, u32 ulId)
{
    u32 ulNameLen;
    BSP_CHAR *pcName;
    struct bsp_rfile_open_cnf stRfileCnf = {0};

#ifdef RFILE_AUTO_MKDIR
    s32 ret = -1;
    char *p;
    char pathtmp[256] = {0};
#endif

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;
    stRfileCnf.ret = -1;

    ulNameLen = (u32)(pstRfileReq->nameLen) ;

    pcName = Rfile_Malloc(ulNameLen);
    if(!pcName)
    {
        goto rfile_AcoreFopenCnf;
    }

    pcName[0] = '\0' ;
    /* coverity[secure_coding] */
    strcat(pcName, (char*)pstRfileReq->aucData); /* [false alarm]: 屏蔽Fortify错误 */

#ifdef RFILE_AUTO_MKDIR
    if(ulNameLen > 255)
    {
        Rfile_Free(pcName);
        goto rfile_AcoreFopenCnf;
    }

    memcpy(pathtmp, pcName, ulNameLen);/*lint !e713 */

    /* 路径中包含'/'并且不在根目录，则检查当前目录是否存在，不存在则创建目录 */
    p = strrchr(pathtmp, '/');
    if((NULL != p) && (p != pathtmp))
    {
        /* 查看上一级目录是否存在，如果不存在则创建此目录 */
        *p = '\0';
        ret = AccessCreate(pathtmp, pstRfileReq->mode);
        if(ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
                "[rfile]: <%s> AccessCreate failed.\n", __FUNCTION__);
        }
    }
#endif
    RFILE_LPM_PRINT_PATH(EN_RFILE_OP_OPEN, pcName);

    stRfileCnf.ret = bsp_open(pcName, pstRfileReq->flags, pstRfileReq->mode);

    if(stRfileCnf.ret >= 0)
    {
        rfile_FpListAdd(stRfileCnf.ret, pcName);
    }

    Rfile_Free(pcName);

rfile_AcoreFopenCnf:

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreCloseReq
 功能描述  : fclose的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreCloseReq(struct bsp_rfile_close_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_common_cnf stRfileCnf = {0};

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;
    stRfileCnf.ret = BSP_ERROR;

    RFILE_LPM_PRINT_FILEPATH(EN_RFILE_OP_CLOSE, pstRfileReq->fd);

    stRfileCnf.ret = bsp_close(pstRfileReq->fd);

    rfile_FpListDel((s32)pstRfileReq->fd);

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreWriteReq
 功能描述  : fwrite的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreWriteReq(struct bsp_rfile_write_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_common_cnf stRfileCnf = {0};

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;
    stRfileCnf.ret = BSP_ERROR;

    RFILE_LPM_PRINT_FILEPATH(EN_RFILE_OP_WRITE, pstRfileReq->fd);

    stRfileCnf.ret = bsp_write(pstRfileReq->fd, (s8*)pstRfileReq->aucData, pstRfileReq->ulSize);

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}

/*****************************************************************************
 函 数 名  : rfile_AcoreWriteSyncReq
 功能描述  : fwrite的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreWriteSyncReq(struct bsp_rfile_write_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_common_cnf stRfileCnf = {0};

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;
    stRfileCnf.ret = BSP_ERROR;

    RFILE_LPM_PRINT_FILEPATH(EN_RFILE_OP_WRITE_SYNC, pstRfileReq->fd);

    stRfileCnf.ret = bsp_write_sync(pstRfileReq->fd, (s8*)pstRfileReq->aucData, pstRfileReq->ulSize);

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreReadReq
 功能描述  : fopen的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreReadReq(struct bsp_rfile_read_req *pstRfileReq, u32 ulId)
{
    u32 ulLen;
    s32 ret = BSP_ERROR;
    struct bsp_rfile_read_cnf *pstRfileCnf;

    rfile_MntnDotRecord(__LINE__);
    if((u32)pstRfileReq->ulSize > RFILE_LEN_MAX)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
            "![rfile]: <%s> pstRfileCnf->Size %d > RFILE_LEN_MAX.\n", __FUNCTION__, pstRfileReq->ulSize);
        return ret;
    }
    ulLen = sizeof(struct bsp_rfile_read_cnf) + pstRfileReq->ulSize;

    pstRfileCnf = Rfile_Malloc(ulLen);
    if(!pstRfileCnf)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[rfile]: <%s> Rfile_Malloc failed.\n", __FUNCTION__);
        return ret;
    }

    pstRfileCnf->opType = pstRfileReq->opType;
    pstRfileCnf->pstlist = pstRfileReq->pstlist;

    RFILE_LPM_PRINT_FILEPATH(EN_RFILE_OP_READ, pstRfileReq->fd);

    pstRfileCnf->Size = bsp_read(pstRfileReq->fd, (s8*)pstRfileCnf->aucData, pstRfileReq->ulSize);

    /* 由C核请求的地方保证读取的数据长度不超过ICC最大长度限制 */

    rfile_IccSend(pstRfileCnf, ulLen, ulId);

    Rfile_Free(pstRfileCnf);

    return BSP_OK;
}

/*****************************************************************************
 函 数 名  : rfile_AcoreSeekReq
 功能描述  : fseek的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreSeekReq(struct bsp_rfile_seek_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_common_cnf stRfileCnf = {0};

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;

    RFILE_LPM_PRINT_FILEPATH(EN_RFILE_OP_SEEK, pstRfileReq->fd);

    stRfileCnf.ret = bsp_lseek(pstRfileReq->fd, (long)pstRfileReq->offset, pstRfileReq->whence);

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreTellReq
 功能描述  : ftell的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreTellReq(struct bsp_rfile_tell_req *pstRfileReq, u32 ulId)
{
    s32 ret = BSP_ERROR;
    struct bsp_rfile_common_cnf stRfileCnf = {0};

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;

    RFILE_LPM_PRINT_FILEPATH(EN_RFILE_OP_TELL, pstRfileReq->fd);

    ret = (s32)bsp_tell(pstRfileReq->fd);

    if(0!=ret)
    {
    }

    stRfileCnf.ret = (s32)ret;

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}

/*****************************************************************************
 函 数 名  : rfile_AcoreRemoveReq
 功能描述  : remove的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreRemoveReq(struct bsp_rfile_remove_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_common_cnf stRfileCnf = {0};
    BSP_CHAR *pcPath;
    u32 ulPathLen;

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;

    ulPathLen =  (u32)(pstRfileReq->pathLen) ;

    pcPath = Rfile_Malloc(ulPathLen);
    if(BSP_NULL == pcPath)
    {
        goto rfile_AcoreRemoveCnf;
    }

    pcPath[0] = '\0' ;
    /* coverity[secure_coding] */
    strcat(pcPath, (char*)pstRfileReq->aucData); /* [false alarm]: 屏蔽Fortify错误 */

    RFILE_LPM_PRINT_PATH(EN_RFILE_OP_REMOVE, pcPath);

    stRfileCnf.ret = bsp_remove((s8*)pcPath);

    Rfile_Free(pcPath);

rfile_AcoreRemoveCnf:

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreMkdirReq
 功能描述  : mkdir的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreMkdirReq(struct bsp_rfile_mkdir_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_common_cnf stRfileCnf = {0};
    BSP_CHAR *pcPath;
    u32 ulPathLen;

#ifdef RFILE_AUTO_MKDIR
    char pathtmp[255+1] = {0};
#endif

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;
    stRfileCnf.ret = BSP_ERROR;

    ulPathLen = (u32)(pstRfileReq->pathLen) ;

    pcPath = Rfile_Malloc(ulPathLen);
    if(BSP_NULL == pcPath)
    {
        goto rfile_AcoreMkdirCnf;
    }

    pcPath[0] = '\0' ;
    /* coverity[secure_coding] */
    strcat(pcPath, (char*)pstRfileReq->aucData); /* [false alarm]: 屏蔽Fortify错误 */

    RFILE_LPM_PRINT_PATH(EN_RFILE_OP_MKDIR, pcPath);

#ifdef RFILE_AUTO_MKDIR

    if(ulPathLen > 255)
    {
        Rfile_Free(pcPath);
        goto rfile_AcoreMkdirCnf;
    }

    memcpy(pathtmp, pcPath, ulPathLen);/*lint !e713 */

    stRfileCnf.ret = AccessCreate((char *)pathtmp, pstRfileReq->mode);
    if(stRfileCnf.ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
            "[rfile]: <%s> AccessCreate failed.\n", __FUNCTION__);
    }
#else
    stRfileCnf.ret = bsp_mkdir(pcPath, pstRfileReq->mode); /*lint !e734*/
#endif
    Rfile_Free(pcPath);

rfile_AcoreMkdirCnf:

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}

/*****************************************************************************
 函 数 名  : rfile_AcoreRmdirReq
 功能描述  : rmdir的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreRmdirReq(struct bsp_rfile_rmdir_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_common_cnf stRfileCnf = {0};
    BSP_CHAR *pcPath;
    u32 ulPathLen;

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;
    stRfileCnf.ret = BSP_ERROR;

    ulPathLen =  (u32)(pstRfileReq->pathLen) ;

    pcPath = Rfile_Malloc(ulPathLen);
    if(BSP_NULL == pcPath)
    {
        goto rfile_AcoreRmdirCnf;
    }

    pcPath[0] = '\0' ;
    /* coverity[secure_coding] */
    strcat(pcPath, (char*)pstRfileReq->aucData); /* [false alarm]: 屏蔽Fortify错误 */

    RFILE_LPM_PRINT_PATH(EN_RFILE_OP_RMDIR, pcPath);

    stRfileCnf.ret = bsp_rmdir(pcPath);

    Rfile_Free(pcPath);

rfile_AcoreRmdirCnf:

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreOpendirReq
 功能描述  : opendir的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreOpendirReq(struct bsp_rfile_opendir_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_opendir_cnf stRfileCnf = {0};
    BSP_CHAR *pcPath;
    u32 ulPathLen;

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;
    stRfileCnf.dirhandle = BSP_ERROR;

    ulPathLen =  (u32)(pstRfileReq->nameLen) ;

    pcPath = Rfile_Malloc(ulPathLen);
    if(BSP_NULL == pcPath)
    {
        goto rfile_AcoreOpendirCnf;
    }

    pcPath[0] = '\0' ;
    /* coverity[secure_coding] */
    strcat(pcPath, (char*)pstRfileReq->aucData); /* [false alarm]: 屏蔽Fortify错误 */

    RFILE_LPM_PRINT_PATH(EN_RFILE_OP_OPENDIR, pcPath);

    stRfileCnf.dirhandle = bsp_opendir(pcPath);

    if(stRfileCnf.dirhandle >= 0)
    {
        rfile_DpListAdd(stRfileCnf.dirhandle, pcPath);
    }

    Rfile_Free(pcPath);

rfile_AcoreOpendirCnf:

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreReaddirReq
 功能描述  : readdir的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreReaddirReq(struct bsp_rfile_readdir_req *pstRfileReq, u32 ulId)
{
    s32 ret = BSP_ERROR;
    u32 ulLen;
    struct bsp_rfile_readdir_cnf *pstRfileCnf = NULL;

    rfile_MntnDotRecord(__LINE__);

    ulLen = sizeof(struct bsp_rfile_readdir_cnf) + pstRfileReq->count;

    pstRfileCnf = Rfile_Malloc(ulLen);
    if(!pstRfileCnf)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[rfile]: <%s> Rfile_Malloc failed.\n", __FUNCTION__);
        return ret;
    }

    pstRfileCnf->opType = pstRfileReq->opType;
    pstRfileCnf->pstlist = pstRfileReq->pstlist;

    RFILE_LPM_PRINT_DIRPATH(EN_RFILE_OP_READDIR, pstRfileReq->dir);

    pstRfileCnf->Size = bsp_readdir(pstRfileReq->dir, (struct linux_dirent *)(pstRfileCnf->aucData), pstRfileReq->count);

    rfile_IccSend(pstRfileCnf, ulLen, ulId);

    Rfile_Free(pstRfileCnf);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreClosedirReq
 功能描述  : closedir的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreClosedirReq(struct bsp_rfile_closedir_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_common_cnf stRfileCnf = {0};

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;

    RFILE_LPM_PRINT_DIRPATH(EN_RFILE_OP_CLOSEDIR, pstRfileReq->dir);

    stRfileCnf.ret = bsp_closedir(pstRfileReq->dir);

    rfile_DpListDel(pstRfileReq->dir);

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreStatReq
 功能描述  : stat的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreStatReq(struct bsp_rfile_stat_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_stat_cnf stRfileCnf = {0};
    BSP_CHAR *pcPath;
    u32 ulPathLen;

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;
    stRfileCnf.ret = BSP_ERROR;

    ulPathLen =  pstRfileReq->ulSize ;

    pcPath = Rfile_Malloc(ulPathLen);
    if(!pcPath)
    {
        goto rfile_AcoreStatCnf;
    }

    pcPath[0] = '\0' ;
    /* coverity[secure_coding] */
    strcat(pcPath, (char*)pstRfileReq->aucData); /* [false alarm]: 屏蔽Fortify错误 */

    RFILE_LPM_PRINT_PATH(EN_RFILE_OP_STAT, pcPath);

    stRfileCnf.ret = bsp_stat(pcPath, &(stRfileCnf.ststat));    /*lint !e740*/

    Rfile_Free(pcPath);

rfile_AcoreStatCnf:

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreRenameReq
 功能描述  : rename的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年11月21日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreRenameReq(struct bsp_rfile_rename_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_rename_cnf stRfileCnf = {0};
    char * oldname;
    char * newname;
    u32 uloldnamelen, ulnewnamelen;

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;
    stRfileCnf.ret = BSP_ERROR;

    uloldnamelen = (u32)(strlen((char*)(pstRfileReq->aucData)) + 1);
    if(uloldnamelen >= pstRfileReq->ulSize)
    {
        goto rfile_AcoreRenameCnf;
    }

    ulnewnamelen = (u32)(strlen((char*)(pstRfileReq->aucData+ uloldnamelen)) + 1);

    if((uloldnamelen + ulnewnamelen) != pstRfileReq->ulSize)
    {
        goto rfile_AcoreRenameCnf;
    }


    oldname = Rfile_Malloc(uloldnamelen);
    if(!oldname)
    {
        goto rfile_AcoreRenameCnf;
    }

    newname = Rfile_Malloc(ulnewnamelen);
    if(!newname)
    {
        Rfile_Free(oldname);
        goto rfile_AcoreRenameCnf;
    }

    oldname[0] = '\0' ;
    /* coverity[secure_coding] */
    strcat(oldname, (char*)pstRfileReq->aucData); /* [false alarm]: 屏蔽Fortify错误 */
    newname[0] = '\0' ;
    /* coverity[secure_coding] */
    strcat(newname, (char*)(pstRfileReq->aucData + uloldnamelen )); /* [false alarm]: 屏蔽Fortify错误 */

    RFILE_LPM_PRINT_PATH(EN_RFILE_OP_RENAME, newname);

    stRfileCnf.ret = bsp_rename(oldname, newname);

    Rfile_Free(oldname);
    Rfile_Free(newname);

rfile_AcoreRenameCnf:

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreAccessReq
 功能描述  : stat的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreAccessReq(struct bsp_rfile_access_req *pstRfileReq, u32 ulId)
{
    struct bsp_rfile_common_cnf stRfileCnf = {0};
    BSP_CHAR *pcPath;
    u32 ulPathLen;

    rfile_MntnDotRecord(__LINE__);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;
    stRfileCnf.ret = BSP_ERROR;

    ulPathLen =  (u32)pstRfileReq->pathlen ;

    pcPath = Rfile_Malloc(ulPathLen);
    if(!pcPath)
    {
        goto rfile_AcoreAccessCnf;
    }

    pcPath[0] = '\0' ;
    /* coverity[secure_coding] */
    strcat(pcPath, (char*)pstRfileReq->aucData); /* [false alarm]: 屏蔽Fortify错误 */

    RFILE_LPM_PRINT_PATH(EN_RFILE_OP_ACCESS, pcPath);

    stRfileCnf.ret = bsp_access(pcPath, pstRfileReq->mode);

    Rfile_Free(pcPath);

rfile_AcoreAccessCnf:

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreMassrdReq
 功能描述  : massread的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreMassrdReq(struct bsp_rfile_massread_req *pstRfileReq, u32 ulId)
{
    s32 ret = BSP_ERROR;
    u32 ulLen;
    struct bsp_rfile_read_cnf *pstRfileCnf;

    rfile_MntnDotRecord(__LINE__);

    ulLen = sizeof(struct bsp_rfile_read_cnf) + pstRfileReq->size;

    pstRfileCnf = Rfile_Malloc(ulLen);
    if(!pstRfileCnf)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[rfile]: <%s> Rfile_Malloc failed.\n", __FUNCTION__);
        return ret;
    }

    pstRfileCnf->opType = pstRfileReq->opType;
    pstRfileCnf->pstlist = pstRfileReq->pstlist;

    RFILE_LPM_PRINT_PATH(EN_RFILE_OP_MASSRD, pstRfileReq->aucData);

#if 0
    ret = bsp_nand_read((char*)pstRfileReq->aucData, pstRfileReq->offset, pstRfileCnf->aucData, pstRfileReq->size ,NULL);
    if(0 == ret)
    {
        pstRfileCnf->Size = pstRfileReq->size;
    }
#else
    pstRfileCnf->Size = 0;
#endif
    pstRfileCnf->errorno = -1;

    /* 由C核请求的地方保证读取的数据长度不超过ICC最大长度限制 */
    /*[false alarm]:误报*/
    if((u32)pstRfileCnf->Size > RFILE_LEN_MAX)
    {
        /*[false alarm]:误报*/
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
            "![rfile]: <%s> pstRfileCnf->Size %d > RFILE_LEN_MAX.\n", __FUNCTION__, pstRfileCnf->Size);
    }

    rfile_IccSend(pstRfileCnf, ulLen, ulId);

    Rfile_Free(pstRfileCnf);

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : rfile_AcoreMasswrReq
 功能描述  : massread的请求处理
 输入参数  : struct bsp_rfile_que_stru *pstRfileQue
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_AcoreMasswrReq(struct bsp_rfile_masswrite_req *pstRfileReq, u32 ulId)
{
    s32 ret = BSP_ERROR;
    s8 *partition;
    struct bsp_rfile_common_cnf stRfileCnf = {0};

    rfile_MntnDotRecord(__LINE__);

    partition = Rfile_Malloc(pstRfileReq->partitionlen);
    if(!partition)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[rfile]: <%s> Rfile_Malloc failed.\n", __FUNCTION__);
        return ret;
    }
    memcpy(partition, pstRfileReq->aucData, (s32)pstRfileReq->partitionlen);

    stRfileCnf.opType = pstRfileReq->opType;
    stRfileCnf.pstlist = pstRfileReq->pstlist;

    RFILE_LPM_PRINT_PATH(EN_RFILE_OP_MASSWR, pstRfileReq->aucData);

#if 0
    ret = bsp_nand_write(partition, pstRfileReq->offset,
                                    (pstRfileReq->aucData + pstRfileReq->partitionlen), pstRfileReq->size);
    if(0 == ret)
    {
        stRfileCnf.ret = pstRfileReq->size;
    }
#else
    stRfileCnf.ret = 0;
#endif
    stRfileCnf.errorno = -1;

    rfile_IccSend(&stRfileCnf, sizeof(stRfileCnf), ulId);

    Rfile_Free(partition);

    return BSP_OK;
}
/*lint -restore*/


/*****************************************************************************
 函 数 名  : bsp_RfileCallback
 功能描述  : icc回调处理函数
 输入参数  : u32 channel_id
             u32 len
             void *context
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月4日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 bsp_RfileCallback(u32 channel_id, u32 len, void *context)
{
    rfile_MntnDotRecord(__LINE__);

    if((RFILE_CCORE_ICC_RD_CHAN != channel_id) && (RFILE_MCORE_ICC_RD_CHAN != channel_id))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "![rfile]: <%s> channel_id %d error.\n", __FUNCTION__, channel_id);

        return BSP_ERROR;
    }

    /* 如果rfile未初始化则利用icc的缓存机制保存数据 */
    if(EN_RFILE_INIT_FINISH != g_stRfileMain.eInitFlag)
    {
        bsp_trace(BSP_LOG_LEVEL_WARNING, BSP_MODU_RFILE, "![rfile]: <%s> initflag %d.\n",
            __FUNCTION__, g_stRfileMain.eInitFlag);

        return BSP_OK;
    }
    wake_lock(&g_stRfileMain.wake_lock);
    osl_sem_up(&g_stRfileMain.semTask);

    return BSP_OK;
}

void rfile_ResetProc(void)
{
    int ret = 0;
    struct list_head *p = 0;
    struct list_head *n = 0;
    struct fp_list  *tmpfp;
    struct dir_list *tmpdir;

    /*close dir or files*/

    rfile_MntnDotRecord(__LINE__);

    list_for_each_safe(p,n,&(g_stRfileMain.fplist))
    {
        tmpfp = list_entry(p, struct fp_list ,stlist);

        ret = bsp_close(tmpfp->fp);
        if(ret != BSP_OK)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
                "[rfile]: <%s> bsp_close failed.\n", __FUNCTION__);
        }

        list_del(&tmpfp->stlist);
        Rfile_Free(tmpfp);
    }

    list_for_each_safe(p,n,&(g_stRfileMain.dplist))
    {
        tmpdir = list_entry(p, struct dir_list ,stlist);
        ret = bsp_closedir(tmpdir->dp);
        if(ret != BSP_OK)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE,
                "[rfile]: <%s> bsp_close failed.\n", __FUNCTION__);
        }

        list_del(&tmpdir->stlist);
        Rfile_Free(tmpdir);
    }

    g_stRfileMain.eInitFlag = EN_RFILE_INIT_FINISH;
}

/*lint -save -e716*/
/*****************************************************************************
 函 数 名  : rfile_TaskProc
 功能描述  : 自处理任务
 输入参数  : void* obj
 输出参数  : 无
 返 回 值  : s32

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 rfile_TaskProc(void* obj)
{
    s32 ret;
    u32 enOptype;
    u32 channel_id;
    RFILE_REQ_FUN   pReqFun;

    bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "[rfile]: <%s> entry.\n", __FUNCTION__);

    while(1)
    {
        /* coverity[check_return] */
        osl_sem_down(&g_stRfileMain.semTask);

        if(EN_RFILE_INIT_SUSPEND == g_stRfileMain.eInitFlag)
        {
            rfile_ResetProc();
            continue;
        }

        channel_id = RFILE_CCORE_ICC_RD_CHAN;
        /*未初始化完成或者处于睡眠状态则利用icc缓冲请求数据*/
        if(g_stRfileMain.eInitFlag != EN_RFILE_INIT_FINISH)
        {
            continue;
        }

        g_stRfileMain.opState = EN_RFILE_DOING;
        wake_lock(&g_stRfileMain.wake_lock);
        if(g_stRfileMain.pmState == EN_RFILE_SLEEP_STATE)
        {
            printk("%s cur state in sleeping,wait for resume end!\n",__func__);
            continue;
        }

        /* 读取ICC-C通道，输入的长度是buff的size，返回值是实际读取的数据长度 */
        ret = bsp_icc_read(channel_id, g_stRfileMain.data, RFILE_LEN_MAX);
        if(((u32)ret > RFILE_LEN_MAX) || (ret <= 0))
        {
            bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "![rfile]: <%s> icc_read %d.\n", __FUNCTION__, ret);

            channel_id = RFILE_MCORE_ICC_RD_CHAN;

            /* 读取ICC-M通道 */
            ret = bsp_icc_read(channel_id, g_stRfileMain.data, RFILE_LEN_MAX);
            if(((u32)ret > RFILE_LEN_MAX) || (ret <= 0))
            {
                wake_unlock(&g_stRfileMain.wake_lock);
                g_stRfileMain.opState = EN_RFILE_IDLE;
                bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "![rfile]: <%s> icc_read failed %d.\n", __FUNCTION__, ret);
                continue;   /* A-C通道、A-M通道都没读到数据 */
            }
        }


        /* 请求的第一个四字节对应的是 op type */
        enOptype = *(u32*)(g_stRfileMain.data);

        if(enOptype >= EN_RFILE_OP_BUTT)
        {
            bsp_trace(BSP_LOG_LEVEL_CRIT, BSP_MODU_RFILE, "![rfile]: <%s> enOptype %d.\n", __FUNCTION__, enOptype);
        }
        else
        {
            pReqFun = astAcoreRfileReq[enOptype].pFun;

            ret = pReqFun(g_stRfileMain.data, channel_id);
            if(BSP_OK != ret)
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "![rfile]: <%s> pFun failed %d.\n", __FUNCTION__, enOptype);
            }
        }
        wake_unlock(&g_stRfileMain.wake_lock);

        /* 处理结束后避免ICC通道中有缓存，再次启动读取 */
        osl_sem_up(&g_stRfileMain.semTask);
    }
}

/*lint -restore*/


s32 bsp_rfile_reset_cb(DRV_RESET_CB_MOMENT_E eparam, s32 userdata)    /*lint !e830*/
{
    if(MDRV_RESET_CB_BEFORE == eparam)
    {
        /* 设置为suspend状态，待close打开的文件、目录后恢复为FINISH状态 */
        g_stRfileMain.eInitFlag = EN_RFILE_INIT_SUSPEND;

        /* 启动任务中的close处理 */
        osl_sem_up(&g_stRfileMain.semTask);
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : bsp_rfile_init
 功能描述  : rfile模块初始化
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月4日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 bsp_rfile_init(void)
{
    s32 ret;
    struct sched_param sch_para;
    sch_para.sched_priority = 15;

    osl_sem_init(0, &(g_stRfileMain.semTask));

    wake_lock_init(&g_stRfileMain.wake_lock,WAKE_LOCK_SUSPEND, "rfile_wakelock");

    g_stRfileMain.taskid = kthread_run(rfile_TaskProc, BSP_NULL, "rfile");
    if (IS_ERR(g_stRfileMain.taskid))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[rfile]: <%s> kthread_run failed.\n", __FUNCTION__);
        return BSP_ERROR;
    }

    if (BSP_OK != sched_setscheduler(g_stRfileMain.taskid, SCHED_FIFO, &sch_para))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[rfile]: <%s> sched_setscheduler failed.\n", __FUNCTION__);
        return BSP_ERROR;
    }

    INIT_LIST_HEAD(&g_stRfileMain.fplist);
    INIT_LIST_HEAD(&g_stRfileMain.dplist);

    memset((void*)&g_stRfileMntnInfo, 0, sizeof(g_stRfileMntnInfo));

    g_stRfileMain.eInitFlag = EN_RFILE_INIT_FINISH;

    bsp_icc_debug_register(RFILE_CCORE_ICC_RD_CHAN, rfile_lpmcallback, 0);

    ret = bsp_icc_event_register(RFILE_CCORE_ICC_RD_CHAN, bsp_RfileCallback, NULL, NULL, NULL);
    if(ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[rfile]: <%s> bsp_icc_event_register failed.\n", __FUNCTION__);
        return BSP_ERROR;
    }

    ret = bsp_icc_event_register(RFILE_MCORE_ICC_RD_CHAN, bsp_RfileCallback, NULL, NULL, NULL);
    if(ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[rfile]: <%s> bsp_icc_event_register MCORE failed.\n", __FUNCTION__);
        return BSP_ERROR;
    }
    adp_rfile_init();

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[rfile]: <%s> success.\n", __FUNCTION__);

    return BSP_OK;
}

/*****************************************************************************
 函 数 名  : bsp_rfile_release
 功能描述  : rfile模块去初始化
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月4日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
s32 bsp_rfile_release(void)    /*lint !e830*/
{
    s32 ret;

    bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_RFILE, "[rfile]: <%s> entry.\n", __FUNCTION__);

    g_stRfileMain.eInitFlag = EN_RFILE_INIT_INVALID;

    osl_sema_delete(&g_stRfileMain.semTask);

    kthread_stop(g_stRfileMain.taskid);

    ret = bsp_icc_event_unregister(RFILE_CCORE_ICC_RD_CHAN);
    if(ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RFILE, "[rfile]: <%s> bsp_icc_event_unregister failed.\n", __FUNCTION__);
        return BSP_ERROR;
    }

    return BSP_OK;
}


EXPORT_SYMBOL(bsp_open);
EXPORT_SYMBOL(bsp_access);
EXPORT_SYMBOL(bsp_close);
EXPORT_SYMBOL(bsp_write);
EXPORT_SYMBOL(bsp_read);
EXPORT_SYMBOL(bsp_lseek);
EXPORT_SYMBOL(bsp_tell);
EXPORT_SYMBOL(bsp_remove);
EXPORT_SYMBOL(bsp_mkdir);
EXPORT_SYMBOL(bsp_rmdir);
EXPORT_SYMBOL(bsp_opendir);
EXPORT_SYMBOL(bsp_readdir);
EXPORT_SYMBOL(bsp_closedir);
EXPORT_SYMBOL(bsp_stat);

#ifdef BSP_CONFIG_PHONE_TYPE

static int  modem_rfile_probe(struct platform_device *dev)
{
    int ret = -1;

    g_stRfileMain.pmState = EN_RFILE_WAKEUP_STATE;
    g_stRfileMain.opState = EN_RFILE_IDLE;

    ret= bsp_rfile_init();

    return ret;
}

static void  modem_rfile_shutdown(struct platform_device *dev)
{
    printk("%s shutdown start %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n",__func__);

    g_stRfileMain.eInitFlag = EN_RFILE_INIT_INVALID;
}
#ifdef CONFIG_PM
static s32 modem_rfile_suspend(struct device *dev)
{
    static s32 count = 0;
    dev_info(dev,"%s:+\n",__func__);
    if(g_stRfileMain.opState != EN_RFILE_IDLE)
    {
        printk(KERN_ERR" %s modem rfile is in doing!\n",__func__);
        return -1;
    }
    g_stRfileMain.pmState = EN_RFILE_SLEEP_STATE;
    printk(KERN_ERR"modem rfile enter suspend! %d times \n",++count);
    dev_info(dev,"%s:-\n",__func__);
    return 0;
}
static s32 modem_rfile_resume(struct device *dev)
{
    static s32 count = 0;
    dev_info(dev,"%s:+\n",__func__);
    g_stRfileMain.pmState = EN_RFILE_WAKEUP_STATE;
    if(g_stRfileMain.opState == EN_RFILE_DOING)
    {
        printk(KERN_ERR"%s need to enter task proc!\n",__func__);
        osl_sem_up(&g_stRfileMain.semTask);
    }
    printk(KERN_ERR"modem rfile enter resume! %d times \n",++count);
    dev_info(dev,"%s:-\n",__func__);
    return 0;
}
static const struct dev_pm_ops modem_rfile_pm_ops ={
	.suspend = modem_rfile_suspend,
    .resume  = modem_rfile_resume,
};

#define BALONG_RFILE_PM_OPS (&modem_rfile_pm_ops)
#else
#define BALONG_RFILE_PM_OPS  NULL
#endif
static struct platform_driver modem_rfile_drv = {
    .probe      = modem_rfile_probe,
    .shutdown   = modem_rfile_shutdown,
    .driver     = {
        .name     = "modem_rfile",
        .owner    = THIS_MODULE,
        .pm       = BALONG_RFILE_PM_OPS,
    },
};


static struct platform_device modem_rfile_device = {
    .name = "modem_rfile",
    .id = 0,
    .dev = {
    .init_name = "modem_rfile",
    },
};


int modem_rfile_init(void)
{
    int ret;

    ret = platform_device_register(&modem_rfile_device);
    if(ret)
    {
        printk(KERN_ERR"platform_device_register modem_rfile_device fail !\n");
        return -1;
    }

    ret = platform_driver_register(&modem_rfile_drv);
    if(ret)
    {
        printk(KERN_ERR"platform_device_register modem_rfile_drv fail !\n");
        platform_device_unregister(&modem_rfile_device);
        return -1;
    }

    return 0;
}

void  modem_rfile_exit(void)
{
    platform_device_unregister(&modem_rfile_device);
    platform_driver_unregister(&modem_rfile_drv);
}

//module_init(modem_rfile_init);
//module_exit(modem_rfile_exit);

#else
module_init(bsp_rfile_init);
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


