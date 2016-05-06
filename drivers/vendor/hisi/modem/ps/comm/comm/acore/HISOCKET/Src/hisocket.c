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

#include "product_config.h"
#if (FEATURE_ON == FEATURE_HISOCKET)
/******************************************************************************
   1 头文件包含
******************************************************************************/
#include <linux/mm.h>
#include <linux/socket.h>
#include <linux/file.h>
#include <linux/net.h>
#include <linux/interrupt.h>
#include <linux/thread_info.h>
#include <linux/rcupdate.h>
#include <linux/netdevice.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mutex.h>
#include <linux/init.h>
#include <linux/poll.h>
#include <linux/cache.h>
#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/mount.h>
#include <linux/security.h>
#include <linux/syscalls.h>
#include <linux/compat.h>
#include <linux/kmod.h>
#include <linux/audit.h>
#include <linux/wireless.h>
#include <linux/nsproxy.h>
#include <linux/magic.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/unistd.h>
#include <net/compat.h>
#include <net/wext.h>
#include <net/cls_cgroup.h>
#include <net/sock.h>
#include <linux/netfilter.h>
#include <linux/if_tun.h>
#include <linux/ipv6_route.h>
#include <linux/route.h>
#include <linux/sockios.h>
#include <linux/atalk.h>
#include <linux/time.h>
#include <linux/sched.h>
#include <linux/ktime.h>
#include <linux/wait.h>
#include <linux/kernel.h>
#include <linux/personality.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <linux/in.h>

#include <linux/inet.h>

#include "hisocket.h"

#define HI_POLLIN_SET   (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
#define HI_POLLOUT_SET  (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
#define HI_POLLEX_SET   (POLLPRI)
#define HI_MAX_SLACK    (100 * NSEC_PER_MSEC)

extern int sock_create_kern(int family, int type, int protocol, struct socket **res);
extern void sock_release(struct socket *sock);
extern int kernel_sendmsg(struct socket *sock, struct msghdr *msg,
  struct kvec *vec, size_t num, size_t size);
extern int kernel_recvmsg(struct socket *sock, struct msghdr *msg,
  struct kvec *vec, size_t num, size_t size, int flags);
extern int kernel_bind(struct socket *sock, struct sockaddr *addr, int addrlen);
extern int kernel_listen(struct socket *sock, int backlog);
extern int kernel_accept(struct socket *sock, struct socket **newsock, int flags);
extern int kernel_connect(struct socket *sock, struct sockaddr *addr, int addrlen, int flags);
extern int kernel_getsockname(struct socket *sock, struct sockaddr *addr, int *addrlen);
extern int kernel_getpeername(struct socket *sock, struct sockaddr *addr, int *addrlen);
extern int kernel_getsockopt(struct socket *sock, int level, int optname, char *optval, int *optlen);
extern int kernel_setsockopt(struct socket *sock, int level, int optname, char *optval, unsigned int optlen);
extern int kernel_sock_ioctl(struct socket *sock, int cmd, unsigned long arg);
extern int kernel_sock_shutdown(struct socket *sock, enum sock_shutdown_cmd how);
extern int sock_create_lite(int family, int type, int protocol, struct socket **res);


#define HI_SOCKET_MAX  32
static int socket_debug=DISABLE_SOCKET_DEBUG;

#define SOCKET_DBG(format, arg...) {                    \
    if (socket_debug == ENABLE_SOCKET_DEBUG)            \
        printk(format, ## arg);             \
}

struct hi_files_struct
{
  struct socket *sock;
  atomic_t cnt;  /*reference count*/
};

struct hi_fs_table
{
  struct hi_files_struct hi_socks[HI_SOCKET_MAX];
  int used;
  struct mutex hi_mutex;
};

static struct hi_fs_table hifstable;

struct hi_poll_table_entry
{
  unsigned int key;
  wait_queue_t wait;
  wait_queue_head_t *wait_address;
};

struct hi_poll_wqueues
{
  poll_table pt;
  struct task_struct *polling_task;
  int triggered;
  int error;
  int inline_index;
  struct hi_poll_table_entry inline_entries[HI_SOCKET_MAX];
};

struct hi_fd_set_bits
{
  unsigned int  in;
  unsigned int  out;
  unsigned int  ex;
  unsigned int  res_in;
  unsigned int  res_out;
  unsigned int  res_ex;
};

static struct file file_stub;

#define hi_get_sock(fd) hifstable.hi_socks[fd].sock

/*register a socket to table,set reference count to 1*/
static int hi_sock_reg_fd(struct socket *sock)
{
  int i = -1;

  SOCKET_DBG("[%s][%d] enter\r\n "
    ,__FUNCTION__,__LINE__);

  mutex_lock(&hifstable.hi_mutex);

  if (HI_SOCKET_MAX == hifstable.used)
    goto fail;

  for (i = 0; i< HI_SOCKET_MAX ; i++)
    if (!atomic_read(&hifstable.hi_socks[i].cnt))
      break;

  if (HI_SOCKET_MAX <= i)
  {
      i = -1;
      goto fail;
  }

  sock->file = &file_stub;
  hifstable.hi_socks[i].sock = sock;
  atomic_set(&hifstable.hi_socks[i].cnt, 1);


  hifstable.used++;

fail:
  mutex_unlock(&hifstable.hi_mutex);

  SOCKET_DBG("[%s][%d] return [%d]\r\n"
    ,__FUNCTION__,__LINE__, i);

  return i;
}


static int hi_sock_unreg_fd(int fd)
{

  SOCKET_DBG("[%s][%d] enter and fd=[%d]\r\n"
    ,__FUNCTION__,__LINE__,fd);

  if(fd>HI_SOCKET_MAX-1 || fd<0){
    SOCKET_DBG("[%s][%d] fd=[%d] error\r\n"
      ,__FUNCTION__,__LINE__,fd);
    return -1;
  }

  mutex_lock(&hifstable.hi_mutex);

  hifstable.used--;

  atomic_set(&hifstable.hi_socks[fd].cnt, 0);

  hifstable.hi_socks[fd].sock = 0;

  mutex_unlock(&hifstable.hi_mutex);

  SOCKET_DBG("[%s][%d] return [%d]\r\n "
    ,__FUNCTION__,__LINE__, 1);

  return 1;
}


static int hi_sock_get_fd(int fd)
{
  int err = -1;

  SOCKET_DBG("[%s][%d] enter and fd=[%d]\r\n "
    ,__FUNCTION__,__LINE__, fd);

  if(fd>HI_SOCKET_MAX-1 || fd<0)
  {
    SOCKET_DBG("[%s][%d] fd=[%d] error\r\n "
      ,__FUNCTION__,__LINE__,fd);
    return err;
  }

  if (likely(atomic_inc_not_zero(&hifstable.hi_socks[fd].cnt)))
    err = 0;

  SOCKET_DBG("[%s][%d] return [%d]\r\n "
    ,__FUNCTION__,__LINE__, err);

  return err;
}


static int hi_sock_put_fd(int fd)
{

  struct socket *sock;

  int err=-1;

  SOCKET_DBG("[%s][%d] enter and fd=[%d]\r\n "
    ,__FUNCTION__,__LINE__,fd);

  if(fd>HI_SOCKET_MAX-1 || fd<0)
  {
    SOCKET_DBG("[%s][%d] fd=[%d] error\r\n "
      ,__FUNCTION__,__LINE__,fd);
    return err;
  }

  /*no use*/
  if (unlikely(atomic_dec_and_test(&hifstable.hi_socks[fd].cnt))){
    sock = hifstable.hi_socks[fd].sock;

    err=hi_sock_unreg_fd(fd);

    sock_release(sock);
  }

  SOCKET_DBG("[%s][%d] return [%d]\r\n "
    ,__FUNCTION__,__LINE__, 1);

  return 1;
}




int hi_socket(int family, int type, int protocol)
{
  struct socket *sock = 0;
  int retval=-1;

  SOCKET_DBG("[%s][%d] enter\r\n "
    ,__FUNCTION__,__LINE__);

  retval = sock_create_kern(family, type, protocol, &sock);
  if (retval < 0)
    goto out;

  retval = hi_sock_reg_fd(sock);
  if (retval < 0)
    goto out_release;

out:
  /* It may be already another descriptor 8) Not kernel problem. */
  SOCKET_DBG("[%s][%d] return [%d] \r\n "
    ,__FUNCTION__,__LINE__,retval);
  return retval;

out_release:
  sock_release(sock);

SOCKET_DBG("[%s][%d] return [%d] \r\n "
  ,__FUNCTION__,__LINE__,retval);

  return retval;
}


int hi_bind(int fd, struct sockaddr *addr, int addrlen)
{
  struct socket *sock;

  int retval=-1;

  SOCKET_DBG("[%s][%d] enter and fd=[%d]\r\n "
    ,__FUNCTION__,__LINE__,fd);

  if (hi_sock_get_fd(fd) < 0){
   SOCKET_DBG("[%s][%d] return [%d] \r\n "
     ,__FUNCTION__,__LINE__,retval);
   return retval;
  }

  sock = hi_get_sock(fd);

  retval = kernel_bind(sock, addr, addrlen);

  hi_sock_put_fd(fd);

  SOCKET_DBG("[%s][%d] return [%d] \r\n "
    ,__FUNCTION__,__LINE__,retval);

  return retval;
}


int hi_listen(int fd, int backlog)
{

  struct socket *sock;
  int retval=-1;

  SOCKET_DBG("[%s][%d] enter and fd=[%d]\r\n "
    ,__FUNCTION__,__LINE__,fd);

  if (hi_sock_get_fd(fd) < 0){
    SOCKET_DBG("[%s][%d] return [%d] \r\n "
      ,__FUNCTION__,__LINE__,retval);
    return retval;
  }

  sock = hi_get_sock(fd);

  retval = kernel_listen(sock, backlog);

  hi_sock_put_fd(fd);

  SOCKET_DBG("[%s][%d] return [%d] \r\n "
    ,__FUNCTION__,__LINE__,retval);

  return retval;
}


int hi_accept(int fd, struct sockaddr *upeer_sockaddr, int *upeer_addrlen)
{

  struct sock *sk;
  struct socket *newsock, *sock;
  int len;
  struct sockaddr_storage address;
  int newfd;
  int err = -1;

  SOCKET_DBG("[%s][%d] enter and fd=[%d]\r\n "
    ,__FUNCTION__,__LINE__,fd);

  if (hi_sock_get_fd(fd) < 0)
    return -1;

  sock = hi_get_sock(fd);

  sk = sock->sk;
  err = sock_create_lite(sk->sk_family, sk->sk_type, sk->sk_protocol,
      &newsock);
  if (err < 0)
    goto done;

  err = hi_sock_reg_fd(newsock);
  if (err < 0)
    goto done_rel_sock;

  newfd = err;

  err = sock->ops->accept(sock, newsock, O_NONBLOCK);
  if (err < 0)
    goto done_rel_fd;

  newsock->ops = sock->ops;

  err=-1;

  if (upeer_sockaddr){
    if (newsock->ops->getname(newsock, (struct sockaddr *)&address,
          &len, 2) < 0)
      goto done_rel_fd;
    if (*upeer_addrlen < len)
      goto done_rel_fd;
    memcpy(&upeer_sockaddr, &address, len);
    *upeer_addrlen = len;
  }

  err=newfd;

  goto done;

done_rel_fd:
  hi_sock_unreg_fd(newfd);
done_rel_sock:
  sock_release(newsock);
done:
  hi_sock_put_fd(fd);

  SOCKET_DBG("[%s][%d] return [%d] \r\n "
    ,__FUNCTION__,__LINE__,err);

  return err;
}


int hi_connect(int fd, struct sockaddr *addr, int addrlen)
{
  struct socket *sock;
  int err = -1;

  SOCKET_DBG("[%s][%d] enter and fd=[%d]\r\n "
    ,__FUNCTION__,__LINE__,fd);

  if (hi_sock_get_fd(fd) < 0)
    return -1;

  sock = hi_get_sock(fd);

  err = kernel_connect(sock, addr, addrlen, 0);

  hi_sock_put_fd(fd);

  SOCKET_DBG("[%s][%d] return [%d] \r\n "
    ,__FUNCTION__,__LINE__,err);

  return err;
}


static int hi_poll_select_copy_remaining(struct timespec *end_time, void *p,
      int timeval, int ret)
{
  struct timespec rts;
  struct timeval rtv;

  if (!p)
    return ret;

  if (current->personality & STICKY_TIMEOUTS)
    goto sticky;

  if (!end_time->tv_sec && !end_time->tv_nsec)
    return ret;

  ktime_get_ts(&rts);
  rts = timespec_sub(*end_time, rts);
  if (rts.tv_sec < 0)
    rts.tv_sec = rts.tv_nsec = 0;

  if (timeval) {
    if (sizeof(rtv) > sizeof(rtv.tv_sec) + sizeof(rtv.tv_usec))
        memset(&rtv, 0, sizeof(rtv));
    rtv.tv_sec = rts.tv_sec;
    rtv.tv_usec = rts.tv_nsec / NSEC_PER_USEC;

    memcpy(p, &rtv, sizeof(rtv));
  }

  sticky:
  if (ret == -ERESTARTNOHAND)
    ret = -EINTR;
  return ret;
}


static int __hi_estimate_accuracy(struct timespec *tv)
{
  int slack;
  int divfactor = 1000;

  if (tv->tv_sec < 0)
    return 0;

  if (task_nice(current) > 0)
    divfactor = divfactor / 5;

  if (tv->tv_sec > HI_MAX_SLACK / (NSEC_PER_SEC/divfactor))
    return HI_MAX_SLACK;

  slack = tv->tv_nsec / divfactor;
  slack += tv->tv_sec * (NSEC_PER_SEC/divfactor);

  if (slack > HI_MAX_SLACK)
    return HI_MAX_SLACK;

  return slack;
}


static int hi_estimate_accuracy(struct timespec *tv)
{
  unsigned int ret;
  struct timespec now;

  ktime_get_ts(&now);
  now = timespec_sub(*tv, now);
  ret = __hi_estimate_accuracy(&now);
  if (ret < current->timer_slack_ns)
    return current->timer_slack_ns;

  return ret;
}


static inline void hi_wait_key_set(poll_table *wait, unsigned int in,
  unsigned int out, unsigned int bit)
{
  if (wait) {
    wait->_key = HI_POLLEX_SET;
    if (in & bit)
      wait->_key |= HI_POLLIN_SET;
    if (out & bit)
      wait->_key |= HI_POLLOUT_SET;

  }
}


int __hi_pollwake(wait_queue_t *wait, unsigned mode, int sync, void *key)
{
  struct hi_poll_wqueues *pwq = wait->private;
  DECLARE_WAITQUEUE(dummy_wait, pwq->polling_task);

  smp_wmb();
  pwq->triggered = 1;

  return default_wake_function(&dummy_wait, mode, sync, key);
}


int hi_pollwake(wait_queue_t *wait, unsigned mode, int sync, void *key)
{
  struct hi_poll_table_entry *entry;

  entry = container_of(wait, struct hi_poll_table_entry, wait);
  if (key && !((unsigned int)key & entry->key))
    return 0;
  return __hi_pollwake(wait, mode, sync, key);
}


struct hi_poll_table_entry *hi_poll_get_entry(struct hi_poll_wqueues *p)
{
  if (p->inline_index < 32)
    return p->inline_entries + p->inline_index++;
  else
    return NULL;
}


void __hi_pollwait(struct file *filp, wait_queue_head_t *wait_address,
  poll_table *p)
{
  struct hi_poll_wqueues *pwq = container_of(p, struct hi_poll_wqueues, pt);
  struct hi_poll_table_entry *entry = hi_poll_get_entry(pwq);

  if (!entry)
    return;
  entry->wait_address = wait_address;

  entry->key = p->_key;

  init_waitqueue_func_entry(&entry->wait, hi_pollwake);
  entry->wait.private = pwq;
  add_wait_queue(wait_address, &entry->wait);

  return;
}


void hi_poll_initwait(struct hi_poll_wqueues *pwq)
{
  init_poll_funcptr(&pwq->pt, __hi_pollwait);
  pwq->polling_task = current;
  pwq->triggered = 0;
  pwq->error = 0;
  pwq->inline_index = 0;
}


int hi_poll_schedule_timeout(struct hi_poll_wqueues *pwq, int state,
  ktime_t *expires, unsigned int slack)
{
  int rc = -EINTR;

  set_current_state(state);
  if (!pwq->triggered)
    rc = schedule_hrtimeout_range(expires, slack, HRTIMER_MODE_ABS);

  __set_current_state(TASK_RUNNING);

  set_mb(pwq->triggered, 0);

  return rc;
}


static void hi_free_poll_entry(struct hi_poll_table_entry *entry)
{
  remove_wait_queue(entry->wait_address, &entry->wait);
}


void hi_poll_freewait(struct hi_poll_wqueues *pwq)
{
  int i;
  for (i = 0; i < pwq->inline_index; i++)
    hi_free_poll_entry(pwq->inline_entries + i);
}


int hi_do_select(int n, struct hi_fd_set_bits *fds, struct timespec *end_time)
{
  ktime_t expire, *to = NULL;
  struct hi_poll_wqueues table;
  poll_table *wait;
  int retval, i, timed_out = 0;
  unsigned int slack = 0;
  struct socket *sock;

  hi_poll_initwait(&table);
  wait = &table.pt;

  if (end_time && !end_time->tv_sec && !end_time->tv_nsec) {
    wait = NULL;
    timed_out = 1;
  }

  if (end_time && !timed_out)
    slack = hi_estimate_accuracy(end_time);

  retval = 0;
  for (;;) {
    unsigned int *rinp, *routp, *rexp;
    unsigned int in, out, ex;

    in = fds->in;
    out = fds->out;
    ex = fds->ex;

    rinp = &(fds->res_in);
    routp = &(fds->res_out);
    rexp = &(fds->res_ex);

    for (i = 0 ;i < n; i++)
    {
      unsigned int mask;
      unsigned int bit = 1<<i;
      unsigned int res_in = 0, res_out = 0, res_ex = 0;
      unsigned int all_bits;

      all_bits = in | out | ex;

      if ((all_bits & bit) == 0)
        continue;

      if (hi_sock_get_fd(i) < 0)
          continue;

      sock = hi_get_sock(i);

      mask = DEFAULT_POLLMASK;

      hi_wait_key_set(wait, in, out, bit);
      if (sock->ops->poll)
        mask = sock->ops->poll(&file_stub, sock, wait);

      hi_sock_put_fd(i);

      if ((mask & HI_POLLIN_SET) && (in & bit)) {
        res_in |= bit;
        retval++;
        wait = NULL;
      }
      if ((mask & HI_POLLOUT_SET) && (out & bit)) {
        res_out |= bit;
        retval++;
        wait = NULL;
      }
      if ((mask & HI_POLLEX_SET) && (ex & bit)) {
        res_ex |= bit;
        retval++;
        wait = NULL;
      }

      if (res_in)
          *rinp = res_in;
      if (res_out)
          *routp = res_out;
      if (res_ex)
          *rexp = res_ex;
      cond_resched();
    }

    wait = NULL;
    if (retval || timed_out)
      break;

    if (table.error) {
      retval = table.error;
      break;
    }

    if (end_time && !to) {
      expire = timespec_to_ktime(*end_time);
      to = &expire;
    }

    if (!hi_poll_schedule_timeout(&table, TASK_INTERRUPTIBLE,
            to, slack))
      timed_out = 1;
  }

  hi_poll_freewait(&table);

  return retval;
}


int hi_core_sys_select(int n, hi_fd_set *inp, hi_fd_set *outp,
   hi_fd_set *exp, struct timespec *end_time)
{

  int ret;
  struct hi_fd_set_bits fd_set_bits;

  ret = -EINVAL;
  if (n < 0)
    return ret;

  if (n > HI_SOCKET_MAX)
    n = HI_SOCKET_MAX;

  /*default 0*/
  memset(&fd_set_bits, 0, sizeof(fd_set_bits));

  if (inp)
    fd_set_bits.in = inp->fds_bits;
  if (outp)
    fd_set_bits.out = outp->fds_bits;
  if (exp)
    fd_set_bits.ex = exp->fds_bits;

  /*do*/
  ret = hi_do_select(n, &fd_set_bits, end_time);

  if (inp)
    inp->fds_bits = fd_set_bits.res_in;
  if (outp)
    outp->fds_bits = fd_set_bits.res_out;
  if (exp)
    exp->fds_bits = fd_set_bits.res_ex;

  return ret;
}


struct timespec hi_timespec_add_safe(const struct timespec lhs,
    const struct timespec rhs)
{
  struct timespec res;

  set_normalized_timespec(&res, lhs.tv_sec + rhs.tv_sec,
      lhs.tv_nsec + rhs.tv_nsec);

  if (res.tv_sec < lhs.tv_sec || res.tv_sec < rhs.tv_sec)
    res.tv_sec = TIME_T_MAX;

  return res;
}


int hi_poll_select_set_timeout(struct timespec *to, int sec, int nsec)
{
  struct timespec ts = {.tv_sec = sec, .tv_nsec = nsec};

  if (!timespec_valid(&ts))
    return -EINVAL;

  if (!sec && !nsec) {
    to->tv_sec = to->tv_nsec = 0;
  } else {
    ktime_get_ts(to);
    *to = hi_timespec_add_safe(*to, ts);
  }
  return 0;
}


int hi_select(int n, hi_fd_set *inp, hi_fd_set *outp, hi_fd_set *exp, struct timeval *tvp)
{
  struct timespec end_time, *to = NULL;
  struct timeval tv;
  int ret;

  if (tvp) {
    memcpy(&tv, tvp, sizeof(tv));
    to = &end_time;

    if (hi_poll_select_set_timeout(to,
          tv.tv_sec + (tv.tv_usec / USEC_PER_SEC),
          (tv.tv_usec % USEC_PER_SEC) * NSEC_PER_USEC))
      return -EINVAL;
  }

  ret = hi_core_sys_select(n, inp, outp, exp, to);
  ret = hi_poll_select_copy_remaining(&end_time, tvp, 1, ret);

  return ret;

}


int hi_close(int fd)
{
  int ret = -1;

  SOCKET_DBG("[%s][%d] enter and fd is[%d] \r\n "
    ,__FUNCTION__,__LINE__,fd);

  ret=hi_sock_put_fd(fd);

  SOCKET_DBG("[%s][%d] return [%d] \r\n "
    ,__FUNCTION__,__LINE__,ret);

  return ret;
}


int hi_send(int fd, void *buff, size_t len, int flags)
{
  struct socket *sock;
  struct msghdr msg;
  struct kvec iov;
  int err = -1;

  SOCKET_DBG("[%s][%d] enter and fd is[%d] \r\n "
    ,__FUNCTION__,__LINE__,fd);

  if (hi_sock_get_fd(fd) < 0)
    goto out;

  sock = hi_get_sock(fd);

  if (buff == NULL){
      SOCKET_DBG("[%s][%d] buff NULL \r\n",__FUNCTION__,__LINE__);
      return -1;
  }

  sock->file = &file_stub;
  sock->file->f_flags = 0;
  sock->file->f_flags |= flags;

  iov.iov_base = buff;
  iov.iov_len = len;

  msg.msg_name = NULL;
  msg.msg_control = NULL;
  msg.msg_controllen = 0;
  msg.msg_namelen = 0;
  msg.msg_flags = flags;

  err = kernel_sendmsg(sock, &msg, &iov, 1, len);

  hi_sock_put_fd(fd);

out:

  SOCKET_DBG("[%s][%d] return [%d] \r\n",__FUNCTION__,__LINE__,err);

  return err;
}


int hi_recv(int fd, void *ubuf, size_t size, int flags)
{
  struct socket *sock;
  struct kvec iov;
  struct msghdr msg;
  int err = -1;

   SOCKET_DBG("[%s][%d] enter and fd is[%d] \r\n "
    ,__FUNCTION__,__LINE__,fd);

  if (hi_sock_get_fd(fd) < 0)
    goto out;

  sock = hi_get_sock(fd);

  if (ubuf == NULL) {
    SOCKET_DBG("[%s][%d] buff NULL \r\n",__FUNCTION__,__LINE__);
    return -1;
  }

  sock->file = &file_stub;
  sock->file->f_flags = 0;
  sock->file->f_flags |= flags;

  iov.iov_len = size;
  iov.iov_base = ubuf;

  msg.msg_control = NULL;
  msg.msg_controllen = 0;
  msg.msg_name = NULL;
  msg.msg_namelen = 0;

  err = kernel_recvmsg(sock, &msg, &iov, 1, size, flags);

  hi_sock_put_fd(fd);

out:

  SOCKET_DBG("[%s][%d] return [%d] \r\n",__FUNCTION__,__LINE__,err);

  return err;
}

int hi_sendto(int fd, void *buff, size_t len, unsigned flags,
        struct sockaddr *addr, int addr_len)
{
  struct socket *sock;
  struct sockaddr_storage address;
  struct msghdr msg;
  struct kvec iov;
  int err = -1;

  SOCKET_DBG("[%s][%d] enter and fd is[%d] \r\n "
    ,__FUNCTION__,__LINE__,fd);

  if (hi_sock_get_fd(fd) < 0)
    goto out;

  sock = hi_get_sock(fd);

  sock->file = &file_stub;
  iov.iov_base = buff;
  iov.iov_len = len;
  msg.msg_name = NULL;
  msg.msg_control = NULL;
  msg.msg_controllen = 0;
  msg.msg_namelen = 0;
  if (addr) {
    memcpy((void *)&address, (void *)addr, sizeof(struct sockaddr_storage));
    msg.msg_name = (struct sockaddr *)&address;
    msg.msg_namelen = addr_len;
  }
  msg.msg_flags = flags;

  err = kernel_sendmsg(sock, &msg, &iov, 1, len);

  hi_sock_put_fd(fd);

  SOCKET_DBG("[%s][%d] return [%d] \r\n",__FUNCTION__,__LINE__,err);

out:
  return err;
}

int hi_recvfrom(int fd, void *ubuf, size_t size, unsigned flags,
          struct sockaddr *addr, int *addr_len)
{
  struct socket *sock;
  struct kvec iov;
  struct msghdr msg;
  struct sockaddr_storage address;
  int err = -1;

  SOCKET_DBG("[%s][%d] enter and fd is[%d] \r\n "
    ,__FUNCTION__,__LINE__,fd);

  if (hi_sock_get_fd(fd) < 0)
    goto out;

  sock = hi_get_sock(fd);
  sock->file = &file_stub;
  msg.msg_control = NULL;
  msg.msg_controllen = 0;
  iov.iov_len = size;
  iov.iov_base = ubuf;
  msg.msg_name = (struct sockaddr *)&address;
  msg.msg_namelen = sizeof(address);

  err = kernel_recvmsg(sock, &msg, &iov, 1, size, flags);

  if ((err >= 0) && (addr)) {
    if (msg.msg_namelen > *addr_len)
      err = -1;
    else{
      memcpy(addr, (struct sockaddr *)&address, msg.msg_namelen);
      *addr_len = msg.msg_namelen;
    }
  }

  hi_sock_put_fd(fd);
out:

  SOCKET_DBG("[%s][%d] return [%d] \r\n",__FUNCTION__,__LINE__,err);

  return err;
}

int hi_getsockname(int fd, struct sockaddr *addr, int *addrlen)
{
  struct socket *sock;
  int err = -1;

  if (hi_sock_get_fd(fd) < 0)
    goto out;

  sock = hi_get_sock(fd);

  err = kernel_getsockname(sock, addr, addrlen);

  hi_sock_put_fd(fd);
out:
  return err;
}


int hi_getpeername(int fd, struct sockaddr *addr, int *addrlen)
{
  struct socket *sock;
  int err = -1;

  if (hi_sock_get_fd(fd) < 0)
    goto out;

  sock = hi_get_sock(fd);

  err = kernel_getpeername(sock, addr, addrlen);

  hi_sock_put_fd(fd);
out:
  return err;
}


int hi_getsockopt(int fd, int level, int optname, char *optval, int *optlen)
{
  struct socket *sock;
  int err = -1;

  if (hi_sock_get_fd(fd) < 0)
    goto out;

  sock = hi_get_sock(fd);

  err = kernel_getsockopt(sock, level, optname, optval, optlen);

  hi_sock_put_fd(fd);
out:
  return err;
}


int hi_setsockopt(int fd, int level, int optname, char *optval, unsigned int optlen)
{
  struct socket *sock;
  int err = -1;

  if (hi_sock_get_fd(fd) < 0)
    goto out;

  sock = hi_get_sock(fd);

  err = kernel_setsockopt(sock, level, optname, optval, optlen);

  hi_sock_put_fd(fd);
out:
  return err;
}


int hi_ioctl(int fd, int cmd, unsigned int arg)
{
  struct socket *sock;
  int err = -1;

  if (hi_sock_get_fd(fd) < 0)
    goto out;

  sock = hi_get_sock(fd);

  err = kernel_sock_ioctl(sock, cmd, arg);

  hi_sock_put_fd(fd);
out:
  return err;
}

int hi_shutdown(int fd, enum sock_shutdown_cmd how)
{
  struct socket *sock;
  int err = -1;

  SOCKET_DBG("[%s][%d] enter and fd is[%d] \r\n "
    ,__FUNCTION__,__LINE__,fd);

  if (hi_sock_get_fd(fd) < 0)
    goto out;

  sock = hi_get_sock(fd);

  err = kernel_sock_shutdown(sock, how);

  hi_sock_put_fd(fd);
out:

  SOCKET_DBG("[%s][%d] return [%d] \r\n "
        ,__FUNCTION__,__LINE__,err);

  return err;
}

unsigned int hi_inet_addr(const char * str)
{
    return in_aton(str);
}


static int hisocket_proc_show(struct seq_file *m, void *v)
{
  int i;
  int ref_cnt;

  seq_printf(m, "open socket number %d\n", hifstable.used );

  for (i=0; i<HI_SOCKET_MAX; i++){
    ref_cnt = atomic_read(&hifstable.hi_socks[i].cnt);
    if (ref_cnt)
      seq_printf(m, "socket[%d] OPENED, Reference %d \n", i, ref_cnt);
    else
      seq_printf(m, "socket[%d] NULL\n", i);
  }

  return 0;
}

static int hisocket_proc_open(struct inode *inode, struct file *file)
{
  return single_open(file, hisocket_proc_show, NULL);
}


static const struct file_operations hisocket_proc_fops = {
  .open = hisocket_proc_open,
  .read = seq_read,
  .llseek = seq_lseek,
  .release = single_release
};

static __net_initdata struct ctl_path kernel_socket_debug_path[] = {
    { .procname = "net", },
    { },
};

static ctl_table kernel_socket_debug_table[] = {
    {
        .procname   = "kernel_socket_debug",
        .data       = &socket_debug,
        .maxlen     = sizeof(int),
        .mode       = 0644,
        .proc_handler   = proc_dointvec,
    },
    { },
};

static int __init hi_socket_init(void)
{
  int i;

  memset(&file_stub, 0, sizeof(file_stub));

  hifstable.used = 0;
  mutex_init(&hifstable.hi_mutex);

  for (i=0; i<HI_SOCKET_MAX; i++)
  {
    atomic_set(&hifstable.hi_socks[i].cnt, 0);
    hifstable.hi_socks[i].sock = NULL;
  }

  proc_create("hisocket", 0, NULL, &hisocket_proc_fops);

  register_sysctl_paths(kernel_socket_debug_path, kernel_socket_debug_table);

  return 0;
}

static void __exit hi_socket_exit(void)
{
  remove_proc_entry("hisocket", NULL);
  return;
}

MODULE_LICENSE("GPL");

module_init(hi_socket_init);
module_exit(hi_socket_exit);

EXPORT_SYMBOL(hi_socket);
EXPORT_SYMBOL(hi_bind);
EXPORT_SYMBOL(hi_close);
EXPORT_SYMBOL(hi_listen);
EXPORT_SYMBOL(hi_connect);
EXPORT_SYMBOL(hi_accept);
EXPORT_SYMBOL(hi_recv);
EXPORT_SYMBOL(hi_send);
EXPORT_SYMBOL(hi_select);
EXPORT_SYMBOL(hi_recvfrom);
EXPORT_SYMBOL(hi_sendto);
EXPORT_SYMBOL(hi_getsockname);
EXPORT_SYMBOL(hi_getpeername);
EXPORT_SYMBOL(hi_getsockopt);
EXPORT_SYMBOL(hi_setsockopt);
EXPORT_SYMBOL(hi_ioctl);
EXPORT_SYMBOL(hi_shutdown);
EXPORT_SYMBOL(hi_inet_addr);

#endif

