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


#ifndef _HI_SOCKET_H
#define _HI_SOCKET_H

#include <linux/socket.h>
#include <linux/net.h>
#include <linux/time.h>

#ifdef __KERNEL__

typedef struct {
    unsigned int fds_bits;
} hi_fd_set;

#define __HI_NFDBITS	(8 * sizeof(unsigned int))
#define	__HI_FDMASK(d)	(1UL << ((d) % __HI_NFDBITS))

#define HI_FD_ISSET(d, set) ((set)->fds_bits & __HI_FDMASK(d))
#define HI_FD_SET(d, set) ((set)->fds_bits |= __HI_FDMASK(d))
#define HI_FD_CLR(d, set)  ((set)->fds_bits &= ~ __HI_FDMASK(d))
#define HI_FD_ZERO(set)   (memset(set, 0, sizeof(*set)))

#define DISABLE_SOCKET_DEBUG 0
#define ENABLE_SOCKET_DEBUG 1



int hi_socket(int family, int type, int protocol);
int hi_bind(int fd, struct sockaddr *addr, int addrlen);
int hi_listen(int fd, int backlog);
int hi_accept(int fd, struct sockaddr *upeer_sockaddr, int *upeer_addrlen);
int hi_connect(int fd, struct sockaddr *addr, int addrlen);
int hi_select(int n, hi_fd_set *inp, hi_fd_set *outp, hi_fd_set *exp, struct timeval *tvp);
int hi_close(int fd);
int hi_send(int fd, void *buff, size_t len, int flags);
int hi_recv(int fd, void *ubuf, size_t size, int flags);
int hi_sendto(int fd, void *buff, size_t len, unsigned flags,
                    struct sockaddr *addr, int addr_len);
int hi_recvfrom(int fd, void *ubuf, size_t size, unsigned flags,
                      struct sockaddr *addr, int *addr_len);
int hi_getsockname(int fd, struct sockaddr *addr, int *addrlen);
int hi_getpeername(int fd, struct sockaddr *addr, int *addrlen);
int hi_getsockopt(int fd, int level, int optname, char *optval, int *optlen);
int hi_setsockopt(int fd, int level, int optname, char *optval, unsigned int optlen);
int hi_ioctl(int fd, int cmd, unsigned int arg);
int hi_shutdown(int fd, enum sock_shutdown_cmd how);
unsigned int hi_inet_addr(const char * str);

#endif


#endif
