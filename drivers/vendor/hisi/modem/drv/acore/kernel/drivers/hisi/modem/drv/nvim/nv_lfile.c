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

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#include "nv_file.h"
#include <linux/syscalls.h>



/*
 * local file sys open
 */
FILE* nv_lfile_open(s8* path,s8* mode)
{
#ifdef __KERNEL__
      return sys_open(path,0,mode);
#else
      return fopen(path,mode);
#endif
}

/*
 * local file read
 */

s32 nv_lfile_read(u8* ptr,u32 size,u32 count,FILE* fp)
{
#ifdef __KERNEL__
      return sys_read(fp,ptr,(size*count));
#else
      return fread(ptr,size,count,fp);
#endif
}

/*
 * local file write
 */
s32 nv_lfile_write(u8* ptr,u32 size,u32 count,FILE* fp)
{
#ifdef __KERNEL__
      return sys_write(fp,ptr,(size*count));
#else
      return fwrite(ptr,size,count,fp);
#endif
}

/*
 * local file seek
 */
s32 nv_lfile_seek(FILE* fp,s32 offset,s32 whence)
{
#ifdef __KERNEL__
      return sys_lseek(fp,offset,whence);
#else
      return fseek(fp,offset,whence);
#endif
}

/*
 * local file remove
 */
s32 nv_lfile_remove(s8* path)
{
#ifdef __KERNEL__
      return sys_unlink(path);
#else
      return unlink(path);
#endif
}

/*
 * local file close
 */
s32 nv_lfile_close(FILE* fp)
{
#ifdef __KERNEL__
      return sys_close(fp);
#else
      return fclose(fp);
#endif
}

/*
 * local file ftell
 */
s32 nv_lfile_ftell(FILE* fp)
{
#ifdef __KERNEL__
    s32 ret;
    s32 seek =0;

    ret = sys_llseek(fp, 0, 0, &seek, SEEK_CUR);
    if(ret)
    {
        printf("sys_llseek error 0x%x\n",ret);
        return NV_ERROR;
    }

    return seek;

#else
      return ftell(fp);
#endif
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

