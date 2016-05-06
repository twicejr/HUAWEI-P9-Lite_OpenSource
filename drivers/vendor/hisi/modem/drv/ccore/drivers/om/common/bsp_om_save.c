/*************************************************************************
*   版权所有(C) 1987-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_om_save.c
*
*   作    者 :  z67193
*
*   描    述 :  可维可测模块，提供LOG文件存储功能
*
*   修改记录 :  2012年12月11日  v1.00  z67193  创建
*************************************************************************/
/* lint --e{801}*/

/*lint -save -e537 -e451 -e801*/
#ifdef __OS_VXWORKS__
#include <vxWorks.h>
#include <logLib.h>
#include <errnoLib.h>
#include <stdio.h>
#include <fcntl.h>
#else
#include "sre_libc.h"
#include "sre_shell.h"
#include "sre_err.h"
#endif
#include "securec.h"

#include <string.h>
#include <stdarg.h>
#include "bsp_om_api.h"
#include "bsp_om_log.h"
#include "bsp_om.h"
#include "bsp_om_save.h"
#include "bsp_rfile.h"
#include "bsp_rtc.h"
/*lint -restore*/
struct linux_dirent {
	unsigned long	d_ino;
	unsigned long	d_off;
	unsigned short	d_reclen;
	char		    d_name[2];
};

typedef struct {
    char *s;        /* The user's output buffer */
    int nmax;       /* The length of the user's output buffer */
    int length;     /* The current length of the string in s[] */
} print_data_t;

static char g_OmLogBuffer[256] = {0x00};

void om_trace(char *buffer, char *fmt,...);
int  om_create_dir(char *path);
int  om_open_dir(char *path);
int  om_close_dir(int fd);

void om_trace(char *buffer, char *fmt,...)
{
    /*lint -save -e830*/
    va_list arglist;/*lint !e40 !e522*/
    /*lint -restore +e830*/

    /*lint -save -e119 -e586 -e530*/
	va_start(arglist, fmt);
	(void)vsnprintf_s(buffer, 256,256, fmt, arglist); /* [false alarm]:屏蔽Fority错误 */
	va_end(arglist);
    /*lint -restore +e119 +e586 +e530*/
    return;
}

int om_create_dir(char *path)
{
    int fd;/* [false alarm]:fortify */

    /* 如果文件夹不存在，创建新文件夹*/
    fd = bsp_access((s8*)path, 0); /* [false alarm]:fortify *///F_OK, 检查文件是否存在
    if(0 != fd)
    {
        fd  = bsp_mkdir((s8*)path, 0660);
        if(fd < 0)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_OM, "create om dir failed! ret = %d\n", fd);
            return fd;
        }
    }

    return BSP_OK;
}

int om_open_dir(char *path)
{
    int fd;/* [false alarm]:fortify */

    fd = om_create_dir(path);
    if(BSP_OK == fd)
    {
        fd = bsp_open((s8*)path, RFILE_RDONLY , 0);
    }

    return fd;
}

int om_close_dir(int fd)
{
    (void)bsp_close((u32)fd);

    return BSP_OK;
}
/*lint -save -e801*/
int om_append_file(char * dir, char *filename, void * address, u32 length, u32 max_size)
{
    int ret = BSP_OK; /* [false alarm]:fortify */
    int fd; /* [false alarm]:fortify */
    u32 bytes;/* [false alarm]:fortify */
    int len;/* [false alarm]:fortify */

    ret = om_create_dir(dir);
    if(BSP_OK != ret)
    {
        om_error("create dir failed! ret = %d\n", ret);
        goto out;
    }

    ret = bsp_access((s8*)filename, 0);
    if(BSP_OK != ret)
    {
        /*create file */
        fd = bsp_open((s8*)filename, RFILE_CREAT|RFILE_RDWR, 0755);
        if(fd < 0)
        {
            om_error("open failed while mode is create, ret = %d\n", fd);
            goto out;
        }
    }
    else/* [false alarm]:fortify */
    {
        fd = bsp_open((s8*)filename, RFILE_APPEND|RFILE_RDWR, 0755);/* [false alarm]:fortify */
        if(fd < 0)
        {
            om_error("open failed while mode is append, ret = %d\n", fd);
            goto out;
        }

    }

    len = bsp_lseek((u32)fd, 0, SEEK_END);/* [false alarm]:fortify */
    if(ERROR == len)
    {
        om_error("seek failed! ret = %d\n", len);/* [false alarm]:fortify */
        goto out1;/* [false alarm]:fortify */
    }

    if (len >= (int)max_size)
    {
        (void)bsp_close((u32)fd);/* [false alarm]:fortify */
        ret = bsp_remove((s8*)filename);
        if (BSP_OK != ret)
        {
            om_error("remove failed! ret = %d\n", ret);
	        goto out;
        }

        /*重新建立reset文件*/
        fd = bsp_open((s8*)filename, RFILE_CREAT|RFILE_RDWR, 0755);/* [false alarm]:fortify */
        if(fd < 0)
        {
            om_error("create failed! ret = %d\n", fd);/* [false alarm]:fortify */
            goto out;
        }
    }

    bytes = (u32)bsp_write((u32)fd, address, length);/* [false alarm]:fortify */
    if(bytes != length)
    {
        om_error("write data failed! ret = %d\n", bytes);/* [false alarm]:fortify */
        ret = BSP_ERROR;
        goto out1;
    }

    (void)bsp_close((u32)fd);

    return BSP_OK;

out1:
    (void)bsp_close((u32)fd);/* [false alarm]:fortify */
out:
    return ret;
}
/*lint -restore*/
bool bsp_om_fs_check(void)
{
    int fd;/* [false alarm]:fortify */

    fd = bsp_access((s8*)OM_ROOT_DIR, 0); //F_OK, 检查文件是否存在
    if(0 != fd)
    {
        return false;/* [false alarm]:fortify */
    }

    om_fetal("om fs is ready\n"); /* [false alarm]:fortify */

    return true; /* [false alarm]:fortify */
}

int bsp_om_append_file(char *filename, void * address, u32 length, u32 max_size)
{
    if(filename == NULL || address == NULL)
    {
        om_error("invalid params\n");
        return BSP_ERROR;
    }

    return om_append_file(OM_LOG_PATH, filename, address, length, max_size);
}

void print2file(char* filename, char *fmt,...)
{
    /*lint -save -e830*/
    va_list arglist ;/*lint !e40 !e522*/
    /*lint -restore +e830*/

    /*lint -save -e119 -e586 -e530*/
	va_start(arglist, fmt);
	(void)vsnprintf_s(g_OmLogBuffer, 256,256, fmt, arglist); /* [false alarm]:屏蔽Fority错误 */
	va_end(arglist);
    /*lint -restore +e119 +e586 +e530*/
    (void)bsp_om_append_file(filename, (void*)g_OmLogBuffer, strlen(g_OmLogBuffer), OM_PRINT_LOG_MAX);

    return;
}

void bsp_om_save_reboot_log(const char * func_name, const void* caller)
{
    struct rtc_time tm = {0,};/* [false alarm]:fortify */
    char log_buff[200] = {0};
    char temp[30] = {0};

    (void)mdrv_rtc_read_time(&tm);
    (void)snprintf_s(temp, 30,sizeof(temp), "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    /* coverity[overrun-buffer-val] */
    om_trace((char*)log_buff,"system reboot reason: NORMAL_RESET C CORE, FUNC:%s, caller:%p, TIME:%s\n", func_name, caller, temp);
    (void)om_append_file(OM_DUMP_PATH, OM_RESET_LOG, (void*)log_buff, strlen(log_buff), OM_RESET_LOG_MAX);
}
/*lint -restore*/
