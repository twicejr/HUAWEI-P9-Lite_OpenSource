/* bastet_utils.c
 *
 * Provide Bastet utilities.
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

#include <linux/sched.h>
#include <linux/fdtable.h>
#include <linux/file.h>
#include <linux/inetdevice.h>
#include <linux/of.h>
#include <linux/wakelock.h>
#include <linux/fb.h>
#include <linux/mm.h>
#include <linux/timer.h>
#include <uapi/linux/if.h>
#include <asm/atomic.h>
#include <net/tcp.h>
#include <huawei_platform/power/bastet/bastet_utils.h>

#define BASTET_WAKE_LOCK				"bastet_wl"
#define BASTET_DEFAULT_NET_DEV			"rmnet0"

#define MIN_UID				0				/* minimum uid number */
#define MAX_UID				65535			/* maximum uid number */

#define SCREEN_ON			1
#define SCREEN_OFF			0

#define CHANNEL_OCCUPIED_TIMEOUT			(5 * HZ)

static void channel_occupied_timeout(unsigned long data);

static struct wake_lock wl_bastet;
static bool bastet_cfg_en = false;
static DEFINE_TIMER(channel_timer, channel_occupied_timeout, 0, 0);

bool bastet_dev_en = false;
char cur_netdev_name[IFNAMSIZ] = BASTET_DEFAULT_NET_DEV;
atomic_t proxy = ATOMIC_INIT(0);
atomic_t buffer = ATOMIC_INIT(0);
atomic_t channel = ATOMIC_INIT(0);
atomic_t cp_reset = ATOMIC_INIT(0);
int hrt_uid = -1;

inline bool is_bastet_enabled(void)
{
	return bastet_cfg_en && bastet_dev_en;
}

inline bool is_proxy_available(void)
{
	return atomic_read(&proxy) != 0;
}

inline bool is_buffer_available(void)
{
	return atomic_read(&buffer) != 0;
}

inline bool is_channel_available(void)
{
	return atomic_read(&channel) == 0;
}

inline bool is_cp_reset(void)
{
	return atomic_read(&cp_reset) != 0;
}

inline bool is_sock_foreground(struct sock *sk)
{
	return hrt_uid == sock_i_uid(sk);
}

void set_channel_occupied(void)
{
	atomic_inc(&channel);
	mod_timer(&channel_timer, jiffies + CHANNEL_OCCUPIED_TIMEOUT);
}

void clear_channel_occupied(void)
{
	atomic_dec(&channel);
	if (atomic_read(&channel) == 0 && timer_pending(&channel_timer)) {
		del_timer(&channel_timer);
	}
}

static void channel_occupied_timeout(unsigned long data)
{
	BASTET_LOGI("set channel available");
	atomic_set(&channel, 0);
}

static void bastet_modem_reset_notify(void)
{
	if (!is_bastet_enabled()) {
		return;
	}
	post_indicate_packet(BST_IND_MODEM_RESET, NULL, 0);
	atomic_set(&cp_reset, 1);
}

#if defined CONFIG_MSM_SUBSYSTEM_RESTART
#include <soc/qcom/subsystem_notif.h>

static void *subsys_h = NULL;

static int bastet_mss_reset_notifier_cb(struct notifier_block *this, unsigned long code, void *data)
{
	if (SUBSYS_AFTER_SHUTDOWN == code) {
		BASTET_LOGI("SUBSYS_AFTER_SHUTDOWN");
		bastet_modem_reset_notify();
	}

	return 0;
}

static struct notifier_block mss_reset_notifier = {
	.notifier_call = bastet_mss_reset_notifier_cb,
};

static void reg_mss_reset_notify(void)
{
	BASTET_LOGI("register msm mss reset notification");
	subsys_h = subsys_notif_register_notifier("modem", &mss_reset_notifier);
	if (IS_ERR(subsys_h)) {
		BASTET_LOGE("failed to register for ssr rc: %d\n", (int)PTR_ERR(subsys_h));
	}
}

static void unreg_mss_reset_notify(void)
{
	if (subsys_h != NULL) {
		subsys_notif_unregister_notifier(subsys_h, &mss_reset_notifier);
	}
}

#elif defined CONFIG_BALONG_MODEM_RESET
#include <linux/hisi/reset.h>

#if defined (CONFIG_HISI_BALONG_MODEM_HI3XXX) || defined (CONFIG_HISI_BALONG_MODEM_HI6XXX)
extern int ccorereset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
#elif defined CONFIG_HISI_BALONG_MODEM_HI3650
extern int bsp_reset_cb_func_register(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
#endif

static int bastet_ccorereset_cb(DRV_RESET_CB_MOMENT_E eparam, int userdata)
{
	if (MDRV_RESET_CB_BEFORE == eparam) {
		BASTET_LOGI("MDRV_RESET_CB_BEFORE");
		bastet_modem_reset_notify();
	}

	return BSP_RESET_OK;
}

static void reg_mss_reset_notify(void)
{
	BASTET_LOGI("register balong mss reset notification");
#if defined (CONFIG_HISI_BALONG_MODEM_HI3XXX) || defined (CONFIG_HISI_BALONG_MODEM_HI6XXX)
	ccorereset_regcbfunc("BASTET", bastet_ccorereset_cb, 0, BSP_DRV_CBFUN_PRIOLEVEL);
#elif defined CONFIG_HISI_BALONG_MODEM_HI3650
	bsp_reset_cb_func_register("BASTET", bastet_ccorereset_cb, 0, BSP_DRV_CBFUN_PRIOLEVEL);
#endif
}

static void unreg_mss_reset_notify(void)
{
}

#else
static void reg_mss_reset_notify(void)
{
	BASTET_LOGE("mss reset notify is not supported");
}

static void unreg_mss_reset_notify(void)
{
	BASTET_LOGE("mss reset notify is not supported");
}
#endif

static int bastet_fb_event(struct notifier_block *self, unsigned long event, void *data)
{
	int state = SCREEN_OFF;
	struct fb_event *fb_event = data;
	int *blank = fb_event->data;

	switch (event) {
	case FB_EVENT_BLANK:
		switch (*blank) {
		case FB_BLANK_UNBLANK:
			state = SCREEN_ON;
			post_indicate_packet(BST_IND_SCREEN_STATE, &state, sizeof(state));
			break;
		case FB_BLANK_POWERDOWN:
			state = SCREEN_OFF;
			post_indicate_packet(BST_IND_SCREEN_STATE, &state, sizeof(state));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}

static struct notifier_block bastet_fb_notifier = {
	.notifier_call = bastet_fb_event,
};

static void init_fb_notification(void)
{
	fb_register_client(&bastet_fb_notifier);
}

static void deinit_fb_notification(void)
{
	fb_unregister_client(&bastet_fb_notifier);
}

static struct file *fget_by_pid(unsigned int fd, pid_t pid)
{
	struct file *file;
	struct task_struct *task;
	struct files_struct *files;

	task = find_task_by_vpid(pid);
	if (!task)
		return NULL;

	files = task->files;

	/*process is removed, task isn't null, but files is null*/
	if (NULL == files) {
		return NULL;
	}

	rcu_read_lock();
	file = fcheck_files(files, fd);
	if (file) {
		/* File object ref couldn't be taken */
		if (file->f_mode & FMODE_PATH ||
			!atomic_long_inc_not_zero(&file->f_count))
			file = NULL;
	}
	rcu_read_unlock();

	return file;
}

struct socket *sockfd_lookup_by_fd_pid(int fd, pid_t pid, int *err)
{
	struct file *file;
	struct socket *sock;

	file = fget_by_pid(fd, pid);
	if (!file) {
		*err = -EBADF;
		return NULL;
	}

	sock = sock_from_file(file, err);
	if (!sock)
		fput(file);

	return sock;
}

/*
 * Get sock by fd and pid.
 */
struct sock *get_sock_by_fd_pid(int fd, pid_t pid)
{
	int err;
	struct socket *sock;
	struct sock *sk;

	sock = sockfd_lookup_by_fd_pid(fd, pid, &err);
	if (NULL == sock) {
		return NULL;
	}

	sk = sock->sk;
	if (NULL != sk) {
		sock_hold(sk);
	}
	if (NULL != sock->file) {
		sockfd_put(sock);
	}

	return sk;
}

int get_fd_by_addr(struct addr_to_fd *guide)
{
	struct task_struct *task;
	struct files_struct *files;
	struct fdtable *fdt;
	struct sock *sk;
	struct inet_sock *inet;
	unsigned int i = 0;
	int count = 0;
	int fd = -1;

	if (guide == NULL)
		return -EFAULT;

	task = find_task_by_vpid(guide->pid);
	if (!task)
		return -EFAULT;

	files = task->files;

	/*process is removed, task isn't null, but files is null*/
	if (NULL == files) {
		return -EFAULT;
	}
	fdt = files_fdtable(files);
	for (i = 0; i <= fdt->max_fds; i++) {
		sk = get_sock_by_fd_pid(i, guide->pid);
		if (!sk) {
			continue;
		}
		inet = inet_sk(sk);
		if (!inet) {
			sock_put(sk);
			continue;
		}
		if (inet->inet_daddr == guide->remote_ip && inet->inet_dport == guide->remote_port) {
			count++;
			fd = i;
		}
		sock_put(sk);
	}
	if (count == 1) {
		guide->fd = fd;
		BASTET_LOGE("fd=%d", fd);
	} else if (count == 0) {
		BASTET_LOGE("No socket with given address exist");
	} else {
		BASTET_LOGE("More than one socket with same address exist");
	}

	return 0;
}

int get_pid_cmdline(struct get_cmdline *cmdline)
{
	struct task_struct *task;
	struct mm_struct *mm;
	char buffer[MAX_PID_NAME_LEN];
	int res = 0;
	unsigned int len;

	if (NULL == cmdline) {
		return -1;
	}
	task = find_task_by_vpid(cmdline->pid);
	if (!task)
		return -1;
	mm = get_task_mm(task);
	if (!mm)
		goto out;
	if (!mm->arg_end)
		goto out_mm;	/* Shh! No looking before we're done */

	len = mm->arg_end - mm->arg_start;

	if (len > PAGE_SIZE)
		len = PAGE_SIZE;

	res = access_process_vm(task, mm->arg_start, buffer, len, 0);

	// If the nul at the end of args has been overwritten, then
	// assume application is using setproctitle(3).
	if (res > 0 && buffer[res-1] != '\0' && len < PAGE_SIZE) {
		len = strnlen(buffer, res);
		if (len < res) {
			res = len;
		} else {
			len = mm->env_end - mm->env_start;
			if (len > PAGE_SIZE - res)
				len = PAGE_SIZE - res;
			res += access_process_vm(task, mm->env_start, buffer+res, len, 0);
			res = strnlen(buffer, res);
		}
	}
	strcpy(cmdline->name, buffer);
out_mm:
	mmput(mm);
out:
	return 0;
}

int bastet_get_comm_prop(struct sock *sk, struct bst_sock_comm_prop *prop)
{
	struct inet_sock *inet = inet_sk(sk);

	if (inet == NULL) {
		BASTET_LOGE("inet is null");
		return -1;
	}
	prop->local_ip = inet->inet_saddr;
	prop->local_port = inet->inet_sport;
	prop->remote_ip = inet->inet_daddr;
	prop->remote_port = inet->inet_dport;

	return 0;
}

void bastet_get_sock_prop(struct sock *sk, struct bst_sock_sync_prop *prop)
{
	struct tcp_sock *tp = tcp_sk(sk);

	prop->seq = tp->write_seq;
	prop->rcv_nxt = tp->rcv_nxt;
	prop->snd_wnd = tp->snd_wnd;
	prop->mss = tp->advmss;
	prop->snd_wscale = tp->rx_opt.snd_wscale;
	prop->rcv_wscale = tp->rx_opt.rcv_wscale;
	prop->tx = 0;
	prop->rx = 0;

	if (likely(tp->rx_opt.tstamp_ok)) {
		prop->ts_current = tcp_time_stamp + tp->tsoffset;
		prop->ts_recent = tp->rx_opt.ts_recent;
		prop->ts_recent_tick = 0;
	}
}

/*
 * Get sock by ip and port.
 */
struct sock *get_sock_by_comm_prop(struct bst_sock_comm_prop* guide)
{
	struct net *net;
	struct net_device* dev;

	dev = dev_get_by_name(&init_net, cur_netdev_name);
	if (NULL == dev) {
		return NULL;
	}

	net = dev_net(dev);

	return __inet_lookup_established(net, &tcp_hashinfo, guide->remote_ip, guide->remote_port,
									guide->local_ip, ntohs(guide->local_port),dev->ifindex);
}

/*
 * Get two new continuous port, read inet_csk_get_port in inet_connection_sock.c for reference.
 * return the first port.
 */
int bind_local_ports(u16 *local_port)
{
	struct sock *sk, *exsk;
	struct inet_hashinfo *hashinfo = &tcp_hashinfo;
	struct inet_bind_hashbucket *head, *exhead;
	struct inet_bind_bucket *tb, *extb;
	struct net *net;
	struct net_device* dev;
	int ret = 1;
	int remaining, rover, exrover, low, high;

	dev = dev_get_by_name(&init_net, cur_netdev_name);
	if (NULL == dev) {
		*local_port = 0;
		return ret;
	}

	net = dev_net(dev);

	local_bh_disable();

	inet_get_local_port_range(&low, &high);
	remaining = (high - low) + 1;
	rover = net_random() % remaining + low;
	exrover = rover + 1;

	do {
		if (inet_is_reserved_local_port(rover)
			&& inet_is_reserved_local_port(exrover))
			goto next_nolock;
		head = &hashinfo->bhash[inet_bhashfn(net, rover,
					hashinfo->bhash_size)];
		spin_lock(&head->lock);
		inet_bind_bucket_for_each(tb, &head->chain) {
			if (net_eq(ib_net(tb), net) && tb->port == rover) {
				goto next_head;
			}
		}

		exhead = &hashinfo->bhash[inet_bhashfn(net, exrover,
					hashinfo->bhash_size)];
		spin_lock(&exhead->lock);
		inet_bind_bucket_for_each(extb, &exhead->chain) {
			if (net_eq(ib_net(extb), net) && extb->port == exrover) {
				goto next_exhead;
			}
		}
		break;
	next_exhead:
		spin_unlock(&exhead->lock);
	next_head:
		spin_unlock(&head->lock);
	next_nolock:
		if (++exrover > high)
			rover = low;
	} while (--remaining > 1); /* leave space for two ports */
	/* If remaining port is less than 2, goto fail */
	if (remaining <= 1) {
		goto fail;
	}

	tb = NULL;
	extb = NULL;

	if (!tb && (tb = inet_bind_bucket_create(hashinfo->bind_bucket_cachep,
				net, head, rover)) == NULL)
		goto fail_unlock;
	tb->fastreuse = 0;

	if (!extb && (extb = inet_bind_bucket_create(hashinfo->bind_bucket_cachep,
				net, exhead, exrover)) == NULL) {
		inet_bind_bucket_destroy(hashinfo->bind_bucket_cachep, tb);
		goto fail_unlock;
	}
	extb->fastreuse = 0;

	sk = sk_alloc(net, PF_INET, GFP_KERNEL, &tcp_prot);
	if (sk == NULL) {
		inet_bind_bucket_destroy(hashinfo->bind_bucket_cachep, tb);
		inet_bind_bucket_destroy(hashinfo->bind_bucket_cachep, extb);
		goto fail_unlock;
	}

	exsk = sk_alloc(net, PF_INET, GFP_KERNEL, &tcp_prot);
	if (exsk == NULL) {
		inet_bind_bucket_destroy(hashinfo->bind_bucket_cachep, tb);
		inet_bind_bucket_destroy(hashinfo->bind_bucket_cachep, extb);
		sk_free(sk);
		goto fail_unlock;
	}

	inet_bind_hash(sk, tb, rover);
	inet_bind_hash(exsk, extb, exrover);

	ret = 0;
	*local_port = rover;
fail_unlock:
	spin_unlock(&exhead->lock);
	spin_unlock(&head->lock);
fail:
	local_bh_enable();

	BASTET_LOGI("port: %d", rover);

	return ret;
}

/*
 * Release a port, read inet_put_port in inet_hashtables.c for reference.
 */
int unbind_local_ports(u16 local_port)
{
	struct sock *sk, *exsk;
	struct inet_hashinfo *hashinfo = &tcp_hashinfo;
	int bhash;
	struct inet_bind_hashbucket *head, *exhead;
	struct inet_bind_bucket *tb, *extb;
	struct net *net;
	struct net_device* dev;
	int port, ex_port;
	int find_port = 0, ex_find_port = 0;
	int ret = 1;

	BASTET_LOGI("port: %d", local_port);

	port = local_port;
	ex_port = local_port+1;

	dev = dev_get_by_name(&init_net, cur_netdev_name);
	if (NULL == dev)
		return ret;
	net = dev_net(dev);

	local_bh_disable();

	bhash = inet_bhashfn(net, port, hashinfo->bhash_size);
	head = &hashinfo->bhash[bhash];

	spin_lock(&head->lock);

	inet_bind_bucket_for_each(tb, &head->chain) {
		if (net_eq(ib_net(tb), net) && tb->port == port) {
			find_port = 1;
			break;
		}
	}

	bhash = inet_bhashfn(net, ex_port, hashinfo->bhash_size);
	exhead = &hashinfo->bhash[bhash];

	spin_lock(&exhead->lock);

	inet_bind_bucket_for_each(extb, &exhead->chain) {
		if (net_eq(ib_net(extb), net) && extb->port == ex_port) {
			ex_find_port = 1;
			break;
		}
	}

	if (find_port && ex_find_port) {
		atomic_dec(&hashinfo->bsockets);
		tb->num_owners--;
		sk = hlist_entry(tb->owners.first, struct sock, sk_bind_node);
		__sk_del_bind_node(sk);
		if (NULL != sk) {
			sk_free(sk); 
		}

		inet_bind_bucket_destroy(hashinfo->bind_bucket_cachep, tb);

		atomic_dec(&hashinfo->bsockets);
		extb->num_owners--;
		exsk = hlist_entry(extb->owners.first, struct sock, sk_bind_node);
		__sk_del_bind_node(exsk);
		if (NULL != exsk) {
			sk_free(exsk); 
		}

		inet_bind_bucket_destroy(hashinfo->bind_bucket_cachep, extb);

	} else {
		BASTET_LOGE("port: %u ex_port : %u not find in tcp_hashinfo!", port, ex_port);
	}

	spin_unlock(&exhead->lock);
	spin_unlock(&head->lock);

	local_bh_enable();

	return 0;
}

void bastet_wakelock_acquire(void)
{
	wake_lock(&wl_bastet);
}

void bastet_wakelock_acquire_timeout(long timeout)
{
	if (wake_lock_active(&wl_bastet)) {
		wake_unlock(&wl_bastet);
	}
	wake_lock_timeout(&wl_bastet, timeout);
}

void bastet_wakelock_release(void)
{
	wake_unlock(&wl_bastet);
}

void ind_hisi_com(void *info, u32 len)
{
	post_indicate_packet(BST_IND_HISICOM, info, len);
}
inline bool is_uid_valid(__u32 uid)
{
	return uid >= MIN_UID && uid <= MAX_UID;
}

int set_current_net_device_name(char *iface)
{
	if (NULL == iface) {
		return -EINVAL;
	}

	memcpy(cur_netdev_name, iface, IFNAMSIZ);
	return 0;
}

/**
 * Function: get_uid_by_pid
 * Description: get Uid by Pid
 * Input:pid_to_uid pid and uid
 * Output:
 * Return:
 * Date: 2015.12.24
 * Author: Zhang Kaige ID: 00220931
 */

int get_uid_by_pid(struct set_process_info *info)
{
	struct task_struct *task;

	if (info == NULL) {
		BASTET_LOGE("invalid parameter");
		return -EFAULT;
	}

	task = find_task_by_vpid(info->pid);
	if (!task) {
		BASTET_LOGE("find task by pid failed");
		return -EFAULT;
	}

	if (!(task->real_cred)) {
		BASTET_LOGE("task->real_cred is NULL");
		return -EFAULT;
	}

	info->uid = task->real_cred->uid;
	BASTET_LOGI("uid=%d", info->uid);

	return 0;
}
void bastet_utils_init(void)
{
	BASTET_LOGI("bastet feature enabled");
	bastet_cfg_en = true;
	wake_lock_init(&wl_bastet, WAKE_LOCK_SUSPEND, BASTET_WAKE_LOCK);
	reg_mss_reset_notify();
	init_fb_notification();
}

void bastet_utils_exit(void)
{
	wake_lock_destroy(&wl_bastet);
	unreg_mss_reset_notify();
	deinit_fb_notification();
}
