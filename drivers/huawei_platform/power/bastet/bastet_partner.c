/* bastet_partner.c
 *
 * Bastet intereact with user space bastetd.
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
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/file.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/fdtable.h>
#include <linux/tcp.h>
#include <net/sock.h>
#include <net/ip.h>

#include <huawei_platform/power/bastet/bastet_utils.h>

#define UID_APP				10000

struct bastet_partner_sock {
	struct list_head list;
	struct sock *sk;
	struct bst_sock_comm_prop comm;
	bool identified;
};

struct bastet_partner_uid {
	struct list_head list;
	struct list_head socks_head;
	uid_t uid;
	bool identified;
};

static spinlock_t partner_uids_lock;
static struct list_head partner_uids_head;

static inline bool invalid_uid(uid_t uid)
{
	// if uid less than 10000, it is not an Android apk
	return (uid < UID_APP);
}

static int add_sock_info(struct list_head *socks_head, struct sock *sk, bool need_report)
{
	struct bastet_partner_sock *sock_node = NULL;
	struct list_head *p = NULL, *n = NULL;
	struct bst_sock_comm_prop comm;
	uid_t uid = sock_i_uid(sk);

	if (!list_empty(socks_head)) {
		// check if there is same sock in the list
		list_for_each_safe(p, n, socks_head) {
			sock_node = list_entry(p, struct bastet_partner_sock, list);
			if (sock_node->sk == sk) {
				BASTET_LOGI("sk=%p is already in the list", sk);
				return 0;
			}
		}
	}
	// create a new sock_node
	sock_node = (struct bastet_partner_sock *) kmalloc(sizeof(struct bastet_partner_sock), GFP_ATOMIC);
	if (NULL == sock_node) {
		BASTET_LOGE("Failed to kmalloc struct bastet_partner_sock");
		return -ENOMEM;
	}
	bastet_get_comm_prop(sk, &comm);
	sock_node->comm = comm;
	sock_node->sk = sk;
	sock_node->identified = false;
	list_add_tail(&sock_node->list, socks_head);
	BASTET_LOGI("add sock_node to list, sk=%p, uid=%d", sk, uid);
	if (need_report) {
		post_indicate_packet(BST_IND_SOCK_STATE_CHANGED, &uid, sizeof(uid_t));
	}

	return 0;
}

static void bastet_check_connect(struct sock *sk)
{
	uid_t uid = sock_i_uid(sk);
	struct bastet_partner_uid *uid_node = NULL;
	struct list_head *p = NULL, *n = NULL;

	if (invalid_uid(uid)) {
		return;
	}
	spin_lock_bh(&partner_uids_lock);
	if (!list_empty(&partner_uids_head)) {
		// check if there is same uid in the list
		list_for_each_safe(p, n, &partner_uids_head) {
			uid_node = list_entry(p, struct bastet_partner_uid, list);
			if (uid_node->uid == uid) {
				// If socket is identified, then it is no need to report.
				add_sock_info(&uid_node->socks_head, sk, !uid_node->identified);
				break;
			}
		}
	}
	spin_unlock_bh(&partner_uids_lock);
}

static bool del_sock_info(struct sock *sk, struct list_head *socks_head, bool need_report)
{
	struct bastet_partner_sock *sock_node = NULL;
	struct list_head *p = NULL, *n = NULL;
	bool ret = false;
	uid_t uid = 0;

	if (!list_empty(socks_head)) {
		// check if there is same sock in the list
		list_for_each_safe(p, n, socks_head) {
			sock_node = list_entry(p, struct bastet_partner_sock, list);
			if (sock_node->sk == sk) {
				if (sock_node->identified) {
					ret = true;
				}
				list_del(&sock_node->list);
				uid = sock_i_uid(sk);
				if (need_report || ret) {
					post_indicate_packet(BST_IND_SOCK_STATE_CHANGED, &uid, sizeof(uid_t));
				}
				BASTET_LOGI("kfree struct bastet_partner_sock, sk=%p, uid=%d", sk, uid);
				kfree(sock_node);
				break;
			}
		}
	}

	return ret;
}

static void bastet_check_disconnect(struct sock *sk)
{
	uid_t uid = sock_i_uid(sk);
	struct bastet_partner_uid *uid_node = NULL;
	struct list_head *p = NULL, *n = NULL;

	if (invalid_uid(uid)) {
		return;
	}
	spin_lock_bh(&partner_uids_lock);
	if (!list_empty(&partner_uids_head)) {
		// check if there is same uid in the list
		list_for_each_safe(p, n, &partner_uids_head) {
			uid_node = list_entry(p, struct bastet_partner_uid, list);
			if (uid_node->uid == uid) {
				// If socket is identified, then it is no need to report.
				if (del_sock_info(sk, &uid_node->socks_head, !uid_node->identified)) {
					uid_node->identified = false;
				}
				break;
			}
		}
	}
	spin_unlock_bh(&partner_uids_lock);
}

void bastet_check_partner(struct sock *sk, int state)
{
	uid_t uid = sock_i_uid(sk);

	if (invalid_uid(uid) || !is_proxy_available()) {
		return;
	}
	switch (state) {
	case TCP_ESTABLISHED:
		bastet_check_connect(sk);
		break;
	case TCP_FIN_WAIT1:
	case TCP_FIN_WAIT2:
	case TCP_TIME_WAIT:
	case TCP_CLOSE:
	case TCP_CLOSE_WAIT:
	case TCP_LAST_ACK:
	case TCP_CLOSING:
		bastet_check_disconnect(sk);
		break;
	default:
		break;
	}
}

static bool check_sock_valid(int fd, pid_t pid, struct bst_sock_comm_prop *comm)
{
	bool ret = false;
	struct sock *sk = NULL;

	sk = get_sock_by_fd_pid(fd, pid);
	if (NULL == sk) {
		goto out;
	}
	if (sk->sk_state != TCP_ESTABLISHED) {
		goto out_put;
	}
	if (sk->sk_socket->type != SOCK_STREAM) {
		goto out_put;
	}
	bastet_get_comm_prop(sk, comm);
	if (comm->remote_ip == 0 && comm->remote_port == 0) {
		goto out_put;
	}
	ret = true;
out_put:
	sock_put(sk);
out:
	return ret;
}

static bool set_sock_identified(struct bst_sock_comm_prop *comm, struct list_head *socks_head)
{
	struct bastet_partner_sock *sock_node = NULL;
	struct list_head *p = NULL, *n = NULL;
	bool ret = false;

	if (!list_empty(socks_head)) {
		// check if there is same comm prop in the list
		list_for_each_safe(p, n, socks_head) {
			sock_node = list_entry(p, struct bastet_partner_sock, list);
			if (memcpy(&sock_node->comm, comm, sizeof(struct bst_sock_comm_prop)) == 0) {
				sock_node->identified = true;
				ret = true;
				break;
			}
		}
	}

	return ret;
}

static void set_uid_identified(uid_t uid, struct bst_sock_comm_prop *comm)
{
	struct bastet_partner_uid *uid_node = NULL;
	struct list_head *p = NULL, *n = NULL;

	spin_lock_bh(&partner_uids_lock);
	if (!list_empty(&partner_uids_head)) {
		// check if there is same uid in the list
		list_for_each_safe(p, n, &partner_uids_head) {
			uid_node = list_entry(p, struct bastet_partner_uid, list);
			if (uid_node->uid == uid) {
				if (set_sock_identified(comm, &uid_node->socks_head)) {
					uid_node->identified = true;
				}
			}
		}
	}
	spin_unlock_bh(&partner_uids_lock);
}

static int post_unique_sock_prop(uid_t uid, int32_t tid_num, int32_t *tids)
{
	struct task_struct *task;
	struct files_struct *files;
	struct fdtable *fdt;
	struct bst_monitor_ind_prop prop;
	struct bst_sock_comm_prop comm;
	int i, fd;
	bool found = false;

	for (i = 0; i < tid_num; i++) {
		task = find_task_by_vpid(tids[i]);
		if (!task)
			return -EFAULT;

		files = task->files;
		if (NULL == files) {
			return -EFAULT;
		}

		fdt = files_fdtable(files);
		for (fd = 0; fd < fdt->max_fds; fd++) {
			if (check_sock_valid(fd, tids[i], &comm)) {
				if (!found) {
					prop.comm = comm;
					prop.sock_id.fd = fd;
					prop.sock_id.pid = tids[i];
					found = true;
				} else {
					if (fd == prop.sock_id.fd && comm.local_port == prop.comm.local_port) {
						continue;
					}
					BASTET_LOGE("More than one socket found fd=%d, pid=%d", fd, tids[i]);
					return -EEXIST;
				}
			}
		}
	}

	if (!found) {
		BASTET_LOGE("no sock found, exit");
		return -ENOENT;
	}
	prop.uid = uid;
	BASTET_LOGI("Found uid=%d has one tcp sock, pid=%d, fd=%d", prop.uid, prop.sock_id.pid, prop.sock_id.fd);
	set_uid_identified(uid, &prop.comm);

	return post_indicate_packet(BST_IND_UID_SOCK_PROP, &prop, sizeof(struct bst_monitor_ind_prop));
}

static int check_uid_sock(struct app_monitor_prop *prop, int32_t *tids)
{
	if (invalid_uid(prop->uid) || IS_ERR_OR_NULL(tids)) {
		return -EINVAL;
	}
	if (prop->tid_count > 0) {
		// if pid has one tcp sock
		post_unique_sock_prop(prop->uid, prop->tid_count, tids);
	}

	return 0;
}

static int add_uid(uid_t uid)
{
	struct bastet_partner_uid *uid_node = NULL;
	struct list_head *p = NULL, *n = NULL;

	if (invalid_uid(uid)) {
		return -EINVAL;
	}
	spin_lock_bh(&partner_uids_lock);
	// check if there is same uid in the list
	list_for_each_safe(p, n, &partner_uids_head) {
		uid_node = list_entry(p, struct bastet_partner_uid, list);
		if (uid_node->uid == uid) {
			BASTET_LOGI("uid=%d is already in the list", uid);
			spin_unlock_bh(&partner_uids_lock);
			return 0;
		}
	}
	// create a new uid_node
	uid_node = (struct bastet_partner_uid *) kmalloc(sizeof(struct bastet_partner_uid), GFP_ATOMIC);
	if (NULL == uid_node) {
		spin_unlock_bh(&partner_uids_lock);
		BASTET_LOGE("Failed to kmalloc struct bastet_partner_uid");
		return -ENOMEM;
	}
	uid_node->uid = uid;
	uid_node->identified = false;
	INIT_LIST_HEAD(&uid_node->socks_head);
	list_add_tail(&uid_node->list, &partner_uids_head);
	BASTET_LOGI("add uid=%d", uid);
	spin_unlock_bh(&partner_uids_lock);

	return 0;
}

static void del_socks(struct list_head *socks_head)
{
	struct bastet_partner_sock *sock_node = NULL;
	struct list_head *p = NULL, *n = NULL;

	if (!list_empty(socks_head)) {
		// clear all sock_node in uid_node
		list_for_each_safe(p, n, socks_head) {
			sock_node = list_entry(p, struct bastet_partner_sock, list);
			list_del(&sock_node->list);
			BASTET_LOGI("kfree struct bastet_partner_sock, sk=%p, uid=%d", sock_node->sk, sock_i_uid(sock_node->sk));
			kfree(sock_node);
		}
	}
}

static int del_uid(uid_t uid)
{
	struct bastet_partner_uid *uid_node = NULL;
	struct list_head *p = NULL, *n = NULL;

	if (invalid_uid(uid)) {
		return -EINVAL;
	}
	spin_lock_bh(&partner_uids_lock);
	if (!list_empty(&partner_uids_head)) {
		// check if there is same uid in the list
		list_for_each_safe(p, n, &partner_uids_head) {
			uid_node = list_entry(p, struct bastet_partner_uid, list);
			if (uid_node->uid == uid) {
				del_socks(&uid_node->socks_head);
				list_del(&uid_node->list);
				kfree(uid_node);
				BASTET_LOGI("kfree struct bastet_partner_uid uid=%d", uid);
				break;
			}
		}
	}
	spin_unlock_bh(&partner_uids_lock);

	return 0;
}

int bastet_partner_process_cmd(struct app_monitor_prop *prop, int32_t *tids)
{
	int rc = 0;

	if (IS_ERR_OR_NULL(prop)) {
		BASTET_LOGE("Invalid struct app_monitor_prop");
		return -EINVAL;
	}

	switch (prop->cmd) {
	case CMD_CHECK_UID_SOCK:
		rc = check_uid_sock(prop, tids);
		break;
	case CMD_ADD_UID:
		rc = add_uid(prop->uid);
		break;
	case CMD_DEL_UID:
		rc = del_uid(prop->uid);
		break;
	default:
		BASTET_LOGI("Unknown cmd");
		rc = -ENOENT;
		break;
	}

	return rc;
}

int bastet_partner_init(void)
{
	spin_lock_init(&partner_uids_lock);
	INIT_LIST_HEAD(&partner_uids_head);

	return 0;
}

void bastet_partner_clear(void)
{
	struct bastet_partner_uid *uid_node = NULL;
	struct list_head *p = NULL, *n = NULL;

	spin_lock_bh(&partner_uids_lock);
	if (!list_empty(&partner_uids_head)) {
		// clear all uid_node
		list_for_each_safe(p, n, &partner_uids_head) {
			uid_node = list_entry(p, struct bastet_partner_uid, list);
			del_socks(&uid_node->socks_head);
		}
	}
	spin_unlock_bh(&partner_uids_lock);
}

void bastet_partner_release(void)
{
	struct bastet_partner_uid *uid_node = NULL;
	struct list_head *p = NULL, *n = NULL;

	spin_lock_bh(&partner_uids_lock);
	if (!list_empty(&partner_uids_head)) {
		// clear all uid_node
		list_for_each_safe(p, n, &partner_uids_head) {
			uid_node = list_entry(p, struct bastet_partner_uid, list);
			del_socks(&uid_node->socks_head);
			list_del(&uid_node->list);
			BASTET_LOGI("kfree struct bastet_partner_uid uid=%d", uid_node->uid);
			kfree(uid_node);
		}
	}
	spin_unlock_bh(&partner_uids_lock);
}
