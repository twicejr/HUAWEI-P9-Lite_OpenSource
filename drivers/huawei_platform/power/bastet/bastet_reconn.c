/* bastet_reconn.c
 *
 * Bastet Tcp Reconnection.
 *
 * Copyright (C) 2014 Huawei Device Co.,Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/file.h>
#include <net/tcp.h>
#include <huawei_platform/power/bastet/bastet_utils.h>

extern int inet_release(struct socket *sock);

struct sk_reconn {
	struct list_head list;
	struct file *reconn_file;
	struct socket *old_sock;
	struct socket *orig_sock;
	struct sock *tmp_sk;
	struct bastet_reconn *rc;
	struct bst_sock_comm_prop comm;
};

struct list_head sk_reconn_list;
spinlock_t sk_reconn_lock;

void bastet_reconn_init(void)
{
	INIT_LIST_HEAD(&sk_reconn_list);
	spin_lock_init(&sk_reconn_lock);
}

void bastet_reconn_config(struct sock *sk, int val)
{
	struct bastet_reconn *reconn;

	BASTET_LOGI("val=%d", val);
	if (sk->reconn) {
		if (sk->reconn->enable == val) {
			return;
		}
	} else {
		if (val == 0) {
			return;
		}
		BASTET_LOGI("new struct bastet_reconn");
		reconn = kmalloc(sizeof(struct bastet_reconn), GFP_KERNEL);
		if (NULL == reconn) {
			BASTET_LOGE("kmalloc struct bastet_reconn failed");
			return;
		}
		memset(reconn, 0, sizeof(struct bastet_reconn));
		sk->reconn = reconn;
		sk->reconn->flag = true;
		sk->reconn->err_close = false;
		atomic_set(&sk->reconn->handover, 0);
	}

	sk->reconn->enable = (val != 0) ? true : false;
	if (sk->reconn->auto_connect) {
		if (sk->reconn->enable) {
			init_waitqueue_head(&sk->reconn->wq);
		} else {
			if (!sk->reconn->flag) {
				wake_up_interruptible(&sk->reconn->wq);
			}
		}
	}
}

static void bastet_notify_close(struct sock *sk, bst_ind_type type)
{
	struct bst_sock_comm_prop comm_prop;
	int ret = 0;

	BASTET_LOGI("sk=%p, type=%d", sk, type);
	ret = bastet_get_comm_prop(sk, &comm_prop);
	if (ret != 0) {
		BASTET_LOGE("Failed to get comm prop, ret=%d", ret);
		return;
	}
	post_indicate_packet(type, &comm_prop, sizeof(struct bst_sock_comm_prop));
}

static struct socket *bastet_sock_handover(struct socket *sock)
{
	int ret = 0;
	struct sock *sk;
	struct sock *tmp_sk;
	struct file *sk_file;
	struct socket *new_sock = NULL;
	struct sk_reconn *reconn;
	struct bst_sock_comm_prop comm_prop;

	sk = sock->sk;
	if (sk->bastet) {
		sk->bastet->bastet_sock_state = BST_SOCK_VALID;
	}
	atomic_inc(&sk->reconn->handover);
	bastet_get_comm_prop(sk, &comm_prop);
	post_indicate_packet(BST_IND_SOCK_DISCONNECT, &comm_prop, sizeof(struct bst_sock_comm_prop));
	sk_file = sock->file;
	BASTET_LOGI("old socket: file %p, socket %p, sock %p", sk_file, sock, sk);
	reconn = kmalloc(sizeof(struct sk_reconn), GFP_ATOMIC);
	if (reconn == NULL) {
		BASTET_LOGE("kmalloc struct sk_reconn failed");
		atomic_dec(&sk->reconn->handover);
		return NULL;
	}
	memset(reconn, 0, sizeof(struct sk_reconn));
	reconn->reconn_file = sk_file;
	reconn->old_sock = sock;
	reconn->orig_sock = sock->sk->reconn->orig_sock ? sock->sk->reconn->orig_sock : sock;
	reconn->comm = comm_prop;
	tmp_sk = sk_alloc(sock_net(sk), AF_INET, GFP_KERNEL, sk->sk_prot);
	if (!tmp_sk) {
		BASTET_LOGE("sk_alloc failed");
		atomic_dec(&sk->reconn->handover);
		kfree(reconn);
		return NULL;
	}
	security_sk_clone(sk, tmp_sk);
	reconn->tmp_sk = tmp_sk;
	reconn->rc = sk->reconn;
	spin_lock(&sk_reconn_lock);
	list_add_tail(&reconn->list, &sk_reconn_list);
	spin_unlock(&sk_reconn_lock);

	sk->reconn->flag = false;
	ret = wait_event_interruptible(sk->reconn->wq, sk->reconn->flag);
	BASTET_LOGI("wait_event_interruptible ret=%d", ret);
	atomic_dec(&sk->reconn->handover);
	new_sock = (struct socket *)sk_file->private_data;
	if (new_sock == sock) {
		BASTET_LOGI("no new sock");
		new_sock = NULL;
		sk_free(tmp_sk);
	} else {
		inet_release(sock);
	}

	return new_sock;
}

static bool check_sk_reconn(struct sk_reconn *reconn, struct bst_sock_comm_prop comm)
{
	bool ret = false;

	if (reconn->tmp_sk->sk_security) {
		if (memcmp(&reconn->comm, &comm, sizeof(struct bst_sock_comm_prop)) == 0) {
			ret = true;
		}
	}

	return ret;
}

int bastet_reconn_set(struct bst_get_sock_comm_prop get_prop)
{
	struct sk_reconn *reconn;
	struct socket *new_sock;
	struct file *new_file;
	struct file *reconn_file;
	struct bastet_reconn *rc;
	struct bst_sock_comm_prop comm_prop;
	int fd;
	int err;
	int ret;
	bool found = false;
	struct list_head *p, *n;

	fd = get_prop.guide.fd;
	comm_prop = get_prop.comm_prop;
	new_sock = sockfd_lookup(fd, &err);
	if (!new_sock) {
		ret = err;
		return -EFAULT;
	}
	bastet_reconn_config(new_sock->sk, true);
	new_file = new_sock->file;
	BASTET_LOGI("new socket: file %p, socket %p, sock %p, fd %d", new_file, new_sock, new_sock->sk, fd);
	new_sock->sk->reconn->old_fd = fd;
	new_sock->sk->reconn->renew = true;
	spin_lock(&sk_reconn_lock);
	list_for_each_safe(p, n, &sk_reconn_list) {
		reconn = list_entry(p, struct sk_reconn, list);
		if (check_sk_reconn(reconn, comm_prop)) {
			found = true;
			break;
		}
	}
	if (!found) {
		BASTET_LOGI("Can not find valid sk_reconn");
		spin_unlock(&sk_reconn_lock);
		return -EFAULT;
	}
	security_sk_clone(reconn->tmp_sk, new_sock->sk);
	sk_free(reconn->tmp_sk);
	reconn_file = reconn->reconn_file;
	rc = reconn->rc;
	spin_unlock(&sk_reconn_lock);

	new_sock->file = reconn_file;
	new_sock->sk->reconn->orig_sock = reconn->orig_sock;
	new_sock->sk->reconn->proxy_id = rc->proxy_id;
	reconn_file->private_data = new_sock;
	fput(new_file);
	rc->flag = true;
	BASTET_LOGI("wake up reconn wq");
	wake_up_interruptible(&rc->wq);
	// notify bastetd socket handover finished
	bastet_get_comm_prop(new_sock->sk, &comm_prop);
	post_indicate_packet(BST_IND_SOCK_EST, &comm_prop, sizeof(struct bst_sock_comm_prop));
	return 0;
}

void bastet_reconn_failed(struct bst_sock_comm_prop prop)
{
	struct sk_reconn *reconn = NULL;
	struct bastet_reconn *rc = NULL;
	struct list_head *p, *n;

	list_for_each_safe(p, n, &sk_reconn_list) {
		reconn = list_entry(p, struct sk_reconn, list);
		if (check_sk_reconn(reconn, prop)) {
			rc = reconn->rc;
			rc->flag = true;
			BASTET_LOGI("reconn break, wake up reconn wq");
			wake_up_interruptible(&rc->wq);
			return;
		}
	}
	BASTET_LOGI("cannot found valid sk_reconn, reset socket");
}

int bastet_reconn_proxyid_set(struct reconn_id id)
{
	struct sock *sk = NULL;
	struct bastet_reconn *rc = NULL;

	sk = get_sock_by_fd_pid(id.guide.fd, id.guide.pid);
	if (NULL == sk) {
		BASTET_LOGE("can not find sock by fd: %d pid: %d", id.guide.fd, id.guide.pid);
		return -ENOENT;
	}
	rc = sk->reconn;
	if (NULL == rc) {
		BASTET_LOGE("bastet_reconn is NULL");
		sock_put(sk);
		return -ENOENT;
	}
	rc->proxy_id = id.proxy_id;
	rc->auto_connect = id.auto_connect;
	sock_put(sk);

	return 0;
}

static void bastet_revert_orig_sock(struct socket *sock)
{
	struct socket *orig_sock;

	orig_sock = sock->sk->reconn->orig_sock;
	if (orig_sock) {
		orig_sock->file->private_data = orig_sock;
	}
}

static void bastet_reconn_release(struct bastet_reconn *rc)
{
	bool renew;
	struct reconn_id id;

	renew = rc->renew;
	id.guide.fd = rc->old_fd;
	id.proxy_id = rc->proxy_id;

	BASTET_LOGI("renew=%d", renew);
	if (renew) {
		BASTET_LOGI("notify close: proxy_id=0x%08X, fd=%d", id.proxy_id, id.guide.fd);
		post_indicate_packet(BST_IND_SOCK_RENEW_CLOSE, &id, sizeof(struct reconn_id));
	}
}

static bool bastet_sk_reconn_release(struct socket *sock)
{
	struct list_head *p, *n;
	struct sk_reconn *sk_rc = NULL;
	struct bastet_reconn *rc = NULL;

	spin_lock(&sk_reconn_lock);
	if (list_empty(&sk_reconn_list)) {
		BASTET_LOGI("sk_reconn_list empty");
		spin_unlock(&sk_reconn_lock);
		return false;
	}
	list_for_each_safe(p, n, &sk_reconn_list) {
		sk_rc = list_entry(p, struct sk_reconn, list);
		if (sk_rc->old_sock == sock) {
			rc = sk_rc->rc;
			bastet_reconn_release(rc);
			list_del(&sk_rc->list);
			kfree(sk_rc);
			BASTET_LOGI("kfree struct sk_reconn");
			spin_unlock(&sk_reconn_lock);
			return true;
		}
	}
	spin_unlock(&sk_reconn_lock);

	return false;
}

static inline bool is_socket_err_close(int err)
{
	if (err > 0) {
		return false;
	}
	// the following error code is not really error close
	switch (err) {
	case -EINTR:			/* Interrupted system call */
	case -EAGAIN:			/* Try again */
	case -ERESTARTSYS:		/* Normal close */
		return false;
	default:
		break;
	}

	return true;
}

void bastet_close_sock(struct socket *sock, int err)
{
#if 0
	struct sock *sk;
	struct bastet_reconn *rc;

	sk = sock->sk;
	if (!sk) {
		bastet_sk_reconn_release(sock);
		return;
	}
	if (!is_socket_err_close(err)) {
		return;
	}
	sock_hold(sk);
	rc = sk->reconn;
	if (!rc) {
		goto out;
	}
	bastet_revert_orig_sock(sock);
	if (!bastet_sk_reconn_release(sock)) {
		bastet_reconn_release(rc);
	}
out:
	sock_put(sk);
#endif
}

void bastet_inet_release(struct sock *sk)
{
	if (sk->reconn && !sk->reconn->err_close) {
		bastet_notify_close(sk, BST_IND_SOCK_NORMAL_CLOSE);
	}
	if (sk->prio_channel) {
		bastet_notify_close(sk, BST_IND_PRIO_SOCK_CLOSE);
		sk->prio_channel = false;
	}
}

static int bastet_block_recv_internal(struct kiocb *iocb, struct socket *sock, struct msghdr *msg,
		 size_t size, int flags, int *addr_len, int err)
{
	struct socket *old_sock = sock;
	struct socket *new_sock;
	struct sock *sk = sock->sk;
	bool close = false;

	sk = sock->sk;
	BASTET_LOGI("reconn enable=%d, err=%d", sock->sk->reconn->enable, err);
	while (is_socket_err_close(err) && old_sock->sk->reconn->enable) {
		if (is_cp_reset()) {
			return err;
		}
		new_sock = bastet_sock_handover(old_sock);
		if (close) {
			BASTET_LOGI("close old one, socket=%p, sock=%p, err=%d", old_sock, old_sock->sk, err);
			bastet_close_sock(old_sock, err);
			close = false;
		}
		if (!new_sock) {
			return err;
		}

		err = sk->sk_prot->recvmsg(iocb, new_sock->sk, msg, size, flags & MSG_DONTWAIT,
					flags & ~MSG_DONTWAIT, addr_len);
		BASTET_LOGI("err=%d", err);
		old_sock = new_sock;
		if (is_socket_err_close(err)) {
			close = true;
		}
	}

	if (is_socket_err_close(err) && !old_sock->sk->reconn->enable) {
		BASTET_LOGI("err=%d, reconn is disabled", err);
		bastet_notify_close(old_sock->sk, BST_IND_SOCK_ERR_CLOSE);
		bastet_close_sock(old_sock, err);
	}
	if (err == -ERESTARTSYS) {
		BASTET_LOGI("indicate socket normal close");
		bastet_notify_close(old_sock->sk, BST_IND_SOCK_NORMAL_CLOSE);
		bastet_close_sock(old_sock, err);
	}
	return err;
}

inline int bastet_block_recv(struct kiocb *iocb, struct socket *sock, struct msghdr *msg,
		 size_t size, int flags, int *addr_len, int err)
{
	if (err > 0 || !sock->sk) {
		return err;
	}

	if (sock->sk->prio_channel && is_socket_err_close(err)) {
		bastet_notify_close(sock->sk, BST_IND_PRIO_SOCK_CLOSE);
		sock->sk->prio_channel = false;
	}
	if (!sock->sk->reconn) {
		if (sock->sk->bastet && is_socket_err_close(err)) {
			bastet_notify_close(sock->sk, BST_IND_SOCK_ERR_CLOSE);
		}
	} else {
		if (sock->sk->reconn->auto_connect) {
			err = bastet_block_recv_internal(iocb, sock, msg, size, flags, addr_len, err);
		} else {
			if (is_socket_err_close(err)) {
				// net device down returns -ETIMEDOUT
				if (err == -ETIMEDOUT) {
					bastet_notify_close(sock->sk, BST_IND_SOCK_TIMEDOUT);
				} else {
					bastet_notify_close(sock->sk, BST_IND_SOCK_DISCONNECT);
				}
				sock->sk->reconn->err_close = true;
			}
		}
	}

	return err;
}

inline int bastet_check_reconn(struct socket *sock)
{
	if (sock->type != SOCK_STREAM) {
		return 0;
	}
	if (!sock->sk || (sock->sk->reconn && (atomic_read(&sock->sk->reconn->handover) > 0))) {
		BASTET_LOGI("Error return -EPIPE");
		return -EPIPE;
	}

	return 0;
}
