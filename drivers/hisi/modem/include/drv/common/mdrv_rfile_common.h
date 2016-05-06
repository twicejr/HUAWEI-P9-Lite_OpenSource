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

#ifndef __MDRV_RFILE_COMMON_H__
#define __MDRV_RFILE_COMMON_H__
#ifdef __cplusplus
extern "C"
{
#endif

    #pragma pack(4)

typedef unsigned int       DRV_INO_T;
typedef unsigned int       DRV_TIME;         /* type for file time fields */

#define DRV_NAME_MAX            255

#define DRV_S_IFDIR             0x4000          /* directory */
#define DRV_FILE_NULL            0              /* empty file*/
#define DRV_O_RDONLY            0               /* +1 == FREAD */
#define DRV_O_WRONLY            1               /* +1 == FWRITE */
#define DRV_O_RDWR              2               /* +1 == FREAD|FWRITE */
#define DRV_O_CREAT             0x0200          /* open with file create */
#define DRV_O_APPEND            0x0008          /* append (writes guaranteed at the end) */
#define DRV_O_TRUNC             0x0400          /* open with truncation */
#define DRV_O_EXCL              0x0800          /* error on open if file exists */
#define DRV_O_NONBLOCK          0x4000          /* non blocking I/O (POSIX style) */
#define DRV_O_NOCTTY            0x8000          /* don't assign a ctty on this open */

#define DRV_SEEK_SET            0               /* absolute offset, was L_SET */
#define DRV_SEEK_CUR            1               /* relative to current offset, was L_INCR */
#define DRV_SEEK_END            2               /* relative to end of file, was L_XTND */


    /* dirent */
    typedef struct tag_DRV_DIRENT_S
    {
        DRV_INO_T           d_ino;                      /* file serial number */
        char                d_name [DRV_NAME_MAX + 1];  /* file name, null-terminated */
    }DRV_DIRENT_S;

    /* Directory descriptor */
    typedef struct tag_DRV_DIR_S
    {
        int                 dd_fd;                      /* file descriptor for open directory */
        int                 dd_cookie;                  /* filesys-specific marker within dir */
        int                 dd_eof;                     /* readdir EOF flag */
        DRV_DIRENT_S        dd_dirent;                  /* obtained directory entry */
    }DRV_DIR_S;

    typedef struct tag_DRV_STAT_S
    {
        unsigned long       st_dev;     /* Device ID number */
        unsigned long       st_ino;     /* File serial number */
        int                 st_mode;    /* Mode of file */
        unsigned long       st_nlink;   /* Number of hard links to file */
        unsigned short      st_uid;     /* User ID of file */
        unsigned short      st_gid;     /* Group ID of file */
        unsigned long       st_rdev;    /* Device ID if special file */
        signed long long    st_size;    /* File size in bytes */
        DRV_TIME            st_atime;   /* Time of last access */
        DRV_TIME            st_mtime;   /* Time of last modification */
        DRV_TIME            st_ctime;   /* Time of last status change */
        long                st_blksize; /* File system block size */
        unsigned long       st_blocks;  /* Number of blocks containing file */
        unsigned char       st_attrib;  /* DOSFS only - file attributes */
        int                 st_reserved1;  /* reserved for future use */
        int                 st_reserved2;  /* reserved for future use */
        int                 st_reserved3;  /* reserved for future use */
        int                 st_reserved4;  /* reserved for future use */
    }DRV_STAT_S;

    void *mdrv_file_open(const char *path, const char *mode);
    int mdrv_file_close(void *fp);
    int mdrv_file_read(void *ptr, unsigned int size, unsigned int number, void *stream);
    int mdrv_file_write(void *ptr, unsigned int size, unsigned int number, void *stream);
    int mdrv_file_write_sync(void *ptr, unsigned int size, unsigned int number, void *stream);
    int mdrv_file_seek(void *stream, long offset, int whence);
    long mdrv_file_tell(void *stream);
    int mdrv_file_remove(const char *pathname);
    int mdrv_file_mkdir(const char *dirName);
    int mdrv_file_rmdir(const char *path);
    DRV_DIR_S* mdrv_file_opendir(const char *dirName);
    DRV_DIRENT_S* mdrv_file_readdir(DRV_DIR_S *dirp);
    int mdrv_file_closedir(DRV_DIR_S *dirp);
    int mdrv_file_get_stat(const char *path, DRV_STAT_S* buf);
    unsigned long mdrv_file_get_errno(void);
    int mdrv_file_access(const char *path, int amode);
    int mdrv_file_rename(const char *oldname, const char *newname);
    int mdrv_file_xcopy(const char *source,const char *dest);
    int mdrv_file_xdelete(const char *source);

    #pragma pack(0)
#ifdef __cplusplus
}
#endif
#endif
