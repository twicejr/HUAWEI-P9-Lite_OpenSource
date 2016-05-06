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

#include <linux/string.h>
#include "ringbuffer.h"

/*lint -e838*/
void con_ring_init(struct con_ring_buffer * buf, unsigned char * addr, unsigned long size)
{
	buf->addr = addr;
	buf->size = (unsigned int)size;
	buf->rpos = 0;
	buf->wpos = 0;
}

static unsigned int con_ring_free_sz(const struct con_ring_buffer * buf)
{
	long long widx = 0, ridx = 0, bufsize = 0, empty = 0;

	widx = buf->wpos;
	ridx = buf->rpos;
	bufsize = buf->size;

	empty = (((ridx - widx) + bufsize) - 1);

	return (unsigned int)(empty & (bufsize - 1));
}

/*
 * NOTE:when this function is called, it is assumed that the 'buf' has enough space for 'inbuf'.
 */
static void ring_data_cpy(struct con_ring_buffer * buf, const unsigned char * inbuf, unsigned int size)
{
	unsigned int cpy_sz = 0, widx = 0, bufsize = 0;

	widx    = buf->wpos;
	bufsize = buf->size;

	cpy_sz = size <= (bufsize - widx) ? size : bufsize - widx;

	/* copy data to the right part of 'buf' */
	(void)memcpy(buf->addr + widx, inbuf, (size_t)cpy_sz);

	/* calc */
	size  -= cpy_sz;
	inbuf += cpy_sz;
	widx = (widx + cpy_sz) & (bufsize - 1);
	cpy_sz = size;

	/* copy data to the left part of 'buf' */
	(void)memcpy(buf->addr + widx, inbuf, (size_t)cpy_sz);

	buf->wpos = (widx + cpy_sz) & (bufsize - 1);
}

/*
 * The returned value indicates the accepted byte number.
 */
unsigned int con_ring_append(struct con_ring_buffer * buf, const unsigned char * inbuf, unsigned long size)
{
	unsigned int free_sz = 0;

	free_sz = con_ring_free_sz(buf);
	free_sz = free_sz <= size ? free_sz : (unsigned int)size;
	ring_data_cpy(buf, inbuf, free_sz);

	return free_sz;
}

/*
 * The returned value indicates the accepted byte number.
 * So, it is always equal to size.
 */
unsigned int con_ring_force_append(struct con_ring_buffer * buf, const unsigned char * inbuf, unsigned int size)
{
	unsigned int free_sz = 0;
	unsigned int org_sz = size;

	if(size >= buf->size)
	{
		inbuf = (const unsigned char *)((unsigned long)inbuf + (size - buf->size) + 1);
		size = buf->size - 1;
		buf->rpos = buf->wpos;
	}
	else
	{
		free_sz = con_ring_free_sz(buf);
		if(free_sz < size)
		{
			buf->rpos += (size - free_sz);
			buf->rpos &= (buf->size - 1);
		}
	}

	ring_data_cpy(buf, inbuf, size);

	return org_sz;
}

static unsigned int con_ring_size(const struct con_ring_buffer * buf)
{
	long long widx = 0, ridx = 0, bufsize = 0, empty = 0;

	widx = buf->wpos;
	ridx = buf->rpos;
	bufsize = buf->size;

	empty = ((widx - ridx) + bufsize);

	return (unsigned int)(empty & (bufsize - 1));
}

unsigned int con_ring_get(struct con_ring_buffer * buf, unsigned char * outbuf, unsigned long size)
{
	unsigned int cpy_sz = 0;
	unsigned int data_size = 0;

	data_size = con_ring_size(buf);

	for(cpy_sz = 0; (cpy_sz < size) && (cpy_sz < data_size); cpy_sz++)
	{
		outbuf[cpy_sz] = buf->addr[buf->rpos];
		buf->rpos = (buf->rpos + 1) & (buf->size - 1);
	}

	return cpy_sz;
}

void con_ring_reset(struct con_ring_buffer * buf)
{
	buf->rpos = buf->wpos;
}
/*lint +e838*/