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

#ifndef __BSP_RFILE_H__
#define __BSP_RFILE_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */


#define     RFILE_RDONLY            (0x00000000)
#define     RFILE_WRONLY            (0x00000001)
#define     RFILE_RDWR              (0x00000002)
#define     RFILE_CREAT             (0x00000040)
#define     RFILE_EXCL              (0x00000080)
#define     RFILE_TRUNC             (0x00000200)
#define     RFILE_APPEND            (0x00000400)
#define     RFILE_DIRECTORY         (0x00004000)

#define RFILE_SEEK_SET            0               /* absolute offset, was L_SET */
#define RFILE_SEEK_CUR            1               /* relative to current offset, was L_INCR */
#define RFILE_SEEK_END            2               /* relative to end of file, was L_XTND */

#define     RFILE_NAME_MAX          255             /* max length of the file name*/

typedef struct {
    u64             d_ino;
    u64             d_off;
    u16             d_reclen;
    u8              d_type;
    s8              d_name[0];
}RFILE_DIRENT_STRU;

/* struct timespec */
typedef struct {
    u64        tv_sec;         /* seconds */
    u64        tv_nsec;        /* nanoseconds */
}RFILE_TIMESPEC_STRU;

struct rfile_stat_stru
{
    u64                     ino;
    u32                     dev;
    u16                     mode;
    u32                     nlink;
    u32                     uid;
    u32                     gid;
    u32                     rdev;
    u64                     size;
    RFILE_TIMESPEC_STRU     atime;
    RFILE_TIMESPEC_STRU     mtime;
    RFILE_TIMESPEC_STRU     ctime;
    u32                     blksize;
    u64                     blocks;
};


void adp_rfile_init(void);
s32 bsp_rfile_init(void);

s32 bsp_open(const s8 *path, s32 flags, s32 mode);
s32 bsp_close(u32 fp);
s32 bsp_write(u32 fd, const s8 *ptr, u32 size);
s32 bsp_write_sync(u32 fd, const s8 *ptr, u32 size);
s32 bsp_read(u32 fd ,s8 *ptr, u32 size);
s32 bsp_lseek(u32  fd, long offset, s32 whence);
long bsp_tell(u32 fd);
s32 bsp_remove(const s8 *pathname);
s32 bsp_mkdir(s8 *dirName, s32 mode);
s32 bsp_rmdir(s8 *path);
s32 bsp_opendir(s8 *dirName);
s32 bsp_readdir(u32 fd, void  *dirent, u32 count);
s32 bsp_closedir(s32 pDir);
s32 bsp_stat(s8 *name, void *pStat);
s32 bsp_access(s8 *path, s32 mode);
s32 bsp_rename( const char * oldname, const char * newname );



#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __BSP_RFILE_H__ */
