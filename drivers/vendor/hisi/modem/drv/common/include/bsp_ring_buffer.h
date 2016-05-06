/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2016. All rights reserved.
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

#ifndef  __BSP_RING_BUFFER_H__
#define  __BSP_RING_BUFFER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <osl_types.h>

struct ring_buffer
{
	char *buf;  /* The actual ring buffer */
	u32  size;  /* The size of the ring buffer */
	u32  write; /* The current write head offset of ring buffer */
	u32  read;  /* The current read head offset of ring buffer */
};


/* if return val == 0 success, else fail */
typedef int (*MEMCPY_FUNC)(void* dest, u32 destMax, void* src, u32 count);

int bsp_ring_buffer_in(struct ring_buffer *rb, void *data, u32 len, MEMCPY_FUNC memcpy_func);
int bsp_ring_buffer_out(struct ring_buffer *rb, void *data, u32 len, MEMCPY_FUNC memcpy_func);

/* readable size(the size writen) */
static inline u32 __attribute__((unused))bsp_ring_buffer_readable_size(struct ring_buffer *rb)
{
	return (rb->write >= rb->read)? (rb->write - rb->read): (rb->size - rb->read + rb->write); 
}

static inline u32 __attribute__((unused))bsp_ring_buffer_writen_size(struct ring_buffer *rb)
{
	return bsp_ring_buffer_readable_size(rb);
}

/* writable size(the size left to be write) */
static inline u32 __attribute__((unused))bsp_ring_buffer_writable_size(struct ring_buffer *rb)
{
	return (rb->read > rb->write)? (rb->read - rb->write): (rb->size - rb->write + rb->read); 
}

static inline u32 __attribute__((unused))is_ring_buffer_empty(struct ring_buffer *rb)
{
	return (rb->read == rb->write);
}

static inline u32 __attribute__((unused))is_ring_buffer_full(struct ring_buffer *rb)
{
	return (rb->write > rb->read)? ((rb->write - rb->read) == (rb->size - 1)): ((rb->read - rb->write) == 1); /*[false alarm]*/
}

#ifdef __cplusplus
}
#endif

#endif   /* __BSP_RING_BUFFER_H__ */
