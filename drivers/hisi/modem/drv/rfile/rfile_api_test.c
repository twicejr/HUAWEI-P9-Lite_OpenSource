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

#include "rfile_balong.h"
#include "mdrv_rfile.h"

typedef struct
{
    void *      context;        /* 0x00: WRS defined context */
    u32         magic;          /* 0x04: magic. Used in HANDLE_VERIFY() */
    u16         attributes;     /* 0x08: attribute bit set */
    s8          type;           /* 0x0a: enum windObjClassType */
    u8          contextType;    /* 0x0b: enum handleContextType */
} RFILE_HANDLE_T;

typedef struct           /* stdio buffers */
{
    u8 *            _base;      /* base address of {std,unget,line} buffer */
    int             _size;      /* size of the buffer */
} RFILE_SBUF_S;

typedef struct
{
    RFILE_HANDLE_T    handle;     /* file pointer handle managemet */
    u8 *            _p;         /* current position in (some) buffer */
    int             _r;         /* read space left for getc() */
    int             _w;         /* write space left for putc() */
    short           _flags;     /* flags, below;this FILE is free if 0*/
    short           _file;      /* fileno, if Unix descriptor, else -1*/
    RFILE_SBUF_S      _bf;        /* buffer (at least 1 byte,if !NULL) */
    int             _lbfsize;   /* 0 or -_bf._size, for inline putc */
    RFILE_SBUF_S      _ub;        /* ungetc buffer */
    u8 *            _up;        /* old _p if _p is doing ungetc data */
    int             _ur;        /* old _r if _r counting ungetc data */
    u8              _ubuf[3];   /* guarantee an ungetc() buffer */
    u8              _nbuf[1];   /* guarantee a getc() buffer */
    RFILE_SBUF_S      _lb;        /* buffer for fgetline() */
    int             _blksize;   /* stat.st_blksize (may be!=_bf._size)*/
    int             _offset;    /* current lseek offset */
    int             taskId;     /* task that owns this file pointer */
} RFILE_FILE_T;

/* 文件打开与关闭 */
int mdrv_rfile_test_001(void)
{
    char *path = "/modem_log/rfiletest/rfile001.txt";
    RFILE_FILE_T *fd;
    
    fd = mdrv_file_open(path, "w+");
    if (!fd){
        printk("[%s]mdrv_file_open faild\n",__FUNCTION__);
        return -1;
    }
    
    int ret = mdrv_file_close((void *)fd);
    if (ret != 0){
        printk("[%s]mdrv_file_close faild\n",__FUNCTION__);
        return -2;
    }
    printk("%s pass\n",__FUNCTION__);
    return 0;
}

/* 文件读写与重命名 */
int mdrv_rfile_test_002(void)
{
    char *path = "/modem_log/rfiletest/rfile002.txt";
    char *pathNew = "/rfiletest/rfile002_new.txt";
    char *wrbuf = "1234567890abcdefghijklmnopqrstuvwxyz";
    char rbbuf[64] = {0};
    RFILE_FILE_T *fd;
    
    fd = mdrv_file_open(path, "w+");
    if (!fd){
        printk("[%s]mdrv_file_open faild\n",__FUNCTION__);
        return -1;
    }

    int retWR = mdrv_file_write(wrbuf, 1, sizeof(wrbuf), fd);
    if (retWR < 0){
        printk("[%s]mdrv_file_write faild\n",__FUNCTION__);
        return -2;
    }

    int retRB = mdrv_file_read(rbbuf, 1, retWR, fd);
    if (retRB < 0){
        printk("[%s]mdrv_file_read faild\n",__FUNCTION__);
        return -3;
    }

    int retRe = mdrv_file_rename(path, pathNew);
    if (retRe < 0){
        printk("[%s]mdrv_file_rename faild\n",__FUNCTION__);
        return -5;
    }
    
    int ret = mdrv_file_close((void *)fd);
    if (ret != 0){
        printk("[%s]mdrv_file_close faild\n",__FUNCTION__);
        return -6;
    }
    printk("%s pass\n", __FUNCTION__); 
    return 0;
}

/* 修改文件偏移量、返回文件大小、与文件状态*/
int mdrv_rfile_test_003(void)
{
    char *path = "/modem_log/rfiletest/rfile003.txt";
    DRV_STAT_S buf;
    RFILE_FILE_T *fd;
    
    fd = mdrv_file_open(path, "w+");
    if (!fd){
        printk("[%s]mdrv_file_open faild\n", __FUNCTION__);
        return -1;
    }
    
    int retSk = mdrv_file_seek(fd, 0, SEEK_END);
    if (retSk != 0){
        printk("[%s]mdrv_file_seek faild\n", __FUNCTION__);
        return -2;
    }

    int retTl = mdrv_file_tell((void *)fd);
    if (retTl < 0){
        printk("[%s]mdrv_file_tell faild\n", __FUNCTION__);
        return -3;
    }
    int retSt = mdrv_file_get_stat(path, &buf);
    if (retSt != 0){
        printk("[%s]mdrv_file_get_stat faild\n", __FUNCTION__);
        return -4;
    }

    int ret = mdrv_file_close((void *)fd);
    if (ret != 0){
        printk("[%s]mdrv_file_close faild\n", __FUNCTION__);
        return -5;
    }
    
    printk("%s pass\n", __FUNCTION__);    
    return 0;
}

/* 判断文件是否存在与删除文件*/
int mdrv_rfile_test_004(void)
{
    char *path = "/modem_log/rfiletest/rfile004.txt";
    RFILE_FILE_T *fd;
    
    int retAc = mdrv_file_access(path, 0);
    if (retAc == -1){
        fd = mdrv_file_open(path, "w+");
        if (!fd){
            printk("[%s]mdrv_file_open faild\n", __FUNCTION__);
            return -1;
        }

        retAc = mdrv_file_access(path, 0);
        if (retAc == -1){
            printk("[%s]mdrv_file_access faild\n", __FUNCTION__);
            return -2;
        }
        
        int retRv = mdrv_file_remove(path);
        if (retRv == -1){
            printk("[%s]mdrv_file_remove faild\n", __FUNCTION__);
            return -3;
        }

        int retCl = mdrv_file_close((void *)fd);
        if (retCl != 0){
            printk("[%s]mdrv_file_close faild\n", __FUNCTION__);
            return -4;
        }
        printk("%s pass\n", __FUNCTION__);    
        return 0;
    }
    
    int retRv = mdrv_file_remove(path);
    if (retRv == -1){
        printk("[%s]mdrv_file_remove faild\n", __FUNCTION__);
        return -5;
    }
        
    printk("%s pass\n", __FUNCTION__);    
    return 0;
}

/* 目录创建与删除 */
int mdrv_rfile_test_005(void)
{
    char *dir = "/modem_log/rfiletest/rfile005";
    int retMk = mdrv_file_mkdir(dir);
    if (retMk != 0){
        printk("[%s]mdrv_file_mkdir faild\n", __FUNCTION__);
        return -1;
    }

    int retRm = mdrv_file_rmdir(dir);
    if (retRm != 0){
        printk("[%s]mdrv_file_rmdir faild\n", __FUNCTION__);
        return -2;
    }
    printk("%s pass\n", __FUNCTION__);    
    return 0;
}

/* 目录创建与删除 */
int mdrv_rfile_test_006(void)
{
    char *dir = "/modem_log/rfiletest/rfile006";
    DRV_DIR_S *pdir;
    DRV_DIRENT_S *pDirent;
    int retMk = mdrv_file_mkdir(dir);
    if (retMk != 0){
        printk("[%s]mdrv_file_mkdir faild\n", __FUNCTION__);
        return -1;
    }

    pdir = mdrv_file_opendir(dir);
    if (!pdir){
        printk("[%s]mdrv_file_opendir faild\n", __FUNCTION__);
        return -2;
    }
    
    pDirent = mdrv_file_readdir(pdir);
    if (!pDirent){
        printk("[%s]mdrv_file_readdir faild\n", __FUNCTION__);
        return -3;
    }

    int retCd = mdrv_file_closedir(pdir);
    if (retCd == -1){
        printk("[%s]mdrv_file_closedir faild\n", __FUNCTION__);
        return -4;
    }
    
    int retRm = mdrv_file_rmdir(dir);
    if (retRm != 0){
        printk("[%s]mdrv_file_rmdir faild\n", __FUNCTION__);
        return -5;
    }
    
    printk("%s pass\n", __FUNCTION__);    
    return 0;
}



