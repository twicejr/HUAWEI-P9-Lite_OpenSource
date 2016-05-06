/* bastet_sync_seq.c
 *
 * Bastet Tcp Seq Sync.
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

#include <net/tcp.h>
#include <net/inet_sock.h>
#include <huawei_platform/power/bastet/bastet_utils.h>

#define BST_MAX_SEQ_VALUE				0xFFFFFFFF

#define BST_REQ_SOCK_SYNC_TIME			(HZ / 2)
#define BST_SKIP_SOCK_OWNER_TIME		(HZ / 20)
#define BST_WAKELOCK_TIMEOUT			(HZ / 10)

enum {
	BST_TMR_EVT_INVALID = 0,
	BST_TMR_REQ_SOCK_SYNC,
	BST_TMR_SET_SOCK_SYNC,
	BST_TMR_DELAY_SOCK_SYNC,
	BST_TMR_CLOSE_SOCK,
};

enum {
	BST_USER_STOP = 0,
	BST_USER_START,
};

extern int adjust_traffic_flow_by_sock(struct sock *sk, unsigned long tx, unsigned long rx);

/*
 * Cancel bastet sock timer anyway.
 */
static void cancel_sock_bastet_timer(struct sock *sk)
{
	struct bastet_sock *bsk = sk->bastet;

	bsk->bastet_timer_event = BST_TMR_EVT_INVALID;
	sk_stop_timer(sk, &bsk->bastet_timer);
}

/*
 * Setup bastet sock delay sync timer.
 */
static void setup_sock_sync_delay_timer(struct sock *sk)
{
	struct bastet_sock *bsk = sk->bastet;

	BASTET_LOGI("delay_time=%ld", bsk->delay_sync_time_section);
	bsk->bastet_timer_event = BST_TMR_DELAY_SOCK_SYNC;
	bsk->bastet_timeout = bsk->last_sock_active_time_point + bsk->delay_sync_time_section;

	bastet_wakelock_acquire_timeout(bsk->delay_sync_time_section + BST_WAKELOCK_TIMEOUT);
	sk_reset_timer(sk, &bsk->bastet_timer, bsk->bastet_timeout);
}

/*
 * Send out user data and Recv User data if necessary.
 */
static void process_sock_send_and_recv(struct sock *sk)
{
	int mss_now;
	struct bastet_sock *bsk = sk->bastet;

	if (NULL != sk->sk_send_head) {
		mss_now = tcp_current_mss(sk);
		__tcp_push_pending_frames(sk, mss_now, tcp_sk(sk)->nonagle);
	}

	if (!skb_queue_empty(&bsk->recv_queue)) {
		struct sk_buff *skb;
		while((skb = __skb_dequeue(&bsk->recv_queue))) {
			sk_backlog_rcv(sk, skb);
		}
		bsk->recv_len = 0;
	}
}

/*
 * Setup bastet sock request sync timer,
 * Insure user sock can turn to valid after a while.
 */
static void setup_sock_sync_request_timer(struct sock *sk, bool retry)
{
	struct bastet_sock *bsk = sk->bastet;

	bsk->sync_retry = retry;
	bsk->bastet_timer_event = BST_TMR_REQ_SOCK_SYNC;
	bsk->bastet_timeout = jiffies + BST_REQ_SOCK_SYNC_TIME;

	sk_reset_timer(sk, &bsk->bastet_timer, bsk->bastet_timeout);
}

/*
 * Sock requests sock sync when sock is invalid.
 */
static int request_sock_sync(struct sock *sk)
{
	int err;
	struct bst_sock_comm_prop prop;

	sk->bastet->bastet_sock_state = BST_SOCK_UPDATING;

	setup_sock_sync_request_timer(sk, false);

	bastet_get_comm_prop(sk, &prop);

	err = post_indicate_packet(BST_IND_SOCK_SYNC_REQ, &prop, sizeof(prop));
	return err;
}

static bool do_sock_send_prepare(struct sock *sk)
{
	u8 sync_state = sk->bastet->bastet_sock_state;

	switch (sync_state) {
	case BST_SOCK_INVALID:
		/* Bastet Log should be outside of lock */
		BASTET_LOGI("sk: %p", sk);
		/* We should never add lock outside switch grammar,
		 * or it will cause interlock when we call process_sock_send_and_recv.
		 */
		spin_lock_bh(&sk->sk_lock.slock);
		request_sock_sync(sk);
		spin_unlock_bh(&sk->sk_lock.slock);
		return true;
	case BST_SOCK_UPDATING:
		return true;
	default:
		return false;
	}
}

/*
 * Judge if send data need to wait.
 * If current sock is invalid, requests socket sync and saves send data;
 * Otherwise, do nothing.
 */
bool bastet_sock_send_prepare(struct sock *sk)
{
	if (NULL != sk->bastet) {
		return do_sock_send_prepare(sk);
	}
	return false;
}

static inline bool bastet_rcvqueues_full(struct sock *sk, const struct sk_buff *skb)
{
	struct bastet_sock *bsk = sk->bastet;
	return bsk->recv_len + skb->truesize > sk->sk_rcvbuf;
}

static int add_rcvqueues_queue(struct sock *sk, struct sk_buff *skb)
{
	if (bastet_rcvqueues_full(sk, skb))
		return -ENOBUFS;

	__skb_queue_tail(&sk->bastet->recv_queue, skb);
	sk->bastet->recv_len += skb->truesize;
	return 0;
}

/*
 * Judge if recv data need to wait.
 * If current sock is invalid, requests socket sync and saves recv data;
 * Otherwise, do nothing.
 */
/*lint -e666*/
bool bastet_sock_recv_prepare(struct sock *sk, struct sk_buff *skb)
{
	u8 sync_state;
	struct bastet_sock *bsk = sk->bastet;

	if (NULL == bsk) {
		return false;
	}

	sync_state = bsk->bastet_sock_state;
	switch (sync_state) {
	case BST_SOCK_INVALID:
		bsk->bastet_sock_state = BST_SOCK_UPDATING;

		/* Set retry true, if timeout, request sock sync */
		setup_sock_sync_request_timer(sk, true);
		/* Ps: do not break */
	case BST_SOCK_UPDATING:
		if (unlikely(add_rcvqueues_queue(sk, skb))) {
			NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPBACKLOGDROP);
			kfree_skb(skb);
		}
		return true;
	default:
		return false;
	}
}
/*lint +e666*/

/*
 * BST_TMR_REQ_SOCK_SYNC timeout.
 * Request sync time is up, but sock sync properties still invalid.
 * Usually, daemon should set sock sync properties before timeout.
 */
static void request_sock_bastet_timeout(struct sock *sk)
{
	struct bastet_sock *bsk = sk->bastet;

	/* Accurating time */
	if (time_after(bsk->bastet_timeout, jiffies)) {
		sk_reset_timer(sk, &bsk->bastet_timer, bsk->bastet_timeout);
		return;
	}

	/* We must reset timer event, bastet_delay_sock_sync_notify depends on it
	 * this code must be put after accurating time
	 */
	bsk->bastet_timer_event = BST_TMR_EVT_INVALID;

	if (BST_SOCK_UPDATING != bsk->bastet_sock_state){
		BASTET_LOGE("sk: %p state: %d not expected", sk, bsk->bastet_sock_state);
		return;
	}

	/* Try reuqest timer again */
	if (bsk->sync_retry) {
		request_sock_sync(sk);
		return;
	}

	/* If goes here, bastet sock sync failed,
	 * Send or recv data anyway. */
	BASTET_LOGE("sk: %p request timeout", sk);

	if (BST_USER_START == bsk->user_ctrl) {
		/* Before send or recv data, set state to BST_SOCK_VALID*/
		bsk->bastet_sock_state = BST_SOCK_VALID;
		process_sock_send_and_recv(sk);
	} else {
		bsk->bastet_sock_state = BST_SOCK_NOT_USED;
	}
}

/*
 * BST_TMR_DELAY_SOCK_SYNC timeout.
 * If sock is ready, get sock sync properties and post them to daemon
 */
static void delay_sock_bastet_timeout(struct sock *sk)
{
	int err;
	struct bst_set_sock_sync_prop sock_p;
	struct bastet_sock *bsk = sk->bastet;

	/* Accurating time */
	if (time_after(bsk->bastet_timeout, jiffies)) {
		sk_reset_timer(sk, &bsk->bastet_timer, bsk->bastet_timeout);
		return;
	}

	/* We must reset timer event, bastet_delay_sock_sync_notify depends on it
	 * this code must be put after accurating time
	 */
	bsk->bastet_timer_event = BST_TMR_EVT_INVALID;

	/* In repair mode or userspace needs repair, do not sync sock */
	if (unlikely(tcp_sk(sk)->repair || bsk->need_repair)) {
		BASTET_LOGE("sk: %p in repair mode", sk);
		return;
	}

	if (TCP_ESTABLISHED != sk->sk_state) {
		BASTET_LOGE("sk: %p sk_state is not TCP_ESTABLISHED", sk);
		return;
	}

	if (BST_SOCK_VALID != bsk->bastet_sock_state) {
		BASTET_LOGE("sk: %p state: %d not expected", sk, bsk->bastet_sock_state);
		return;
	}

	/* Sock owner has used since last setup */
	if (time_after(bsk->last_sock_active_time_point + bsk->delay_sync_time_section, jiffies)) {
		setup_sock_sync_delay_timer(sk);
		return;
	}

	/* Sock owner has some data unacked,
	 * Coming ack would trigger delay timer again */
	if (!tcp_write_queue_empty(sk)) {
		BASTET_LOGI("sk: %p has sent data not acked", sk);
		post_indicate_packet(BST_IND_TRIGGER_THAW, &bsk->pid, sizeof(pid_t));
		return;
	}

	/* Sock owner has some data to recv, do not sync.
	 * If sock owner has none recv action,
	 * delay timer should be stopped. */
	if (!skb_queue_empty(&sk->sk_receive_queue)) {
		BASTET_LOGI("sk: %p has received data in queue", sk);
		bsk->last_sock_active_time_point = jiffies;
		setup_sock_sync_delay_timer(sk);
		post_indicate_packet(BST_IND_TRIGGER_THAW, &bsk->pid, sizeof(pid_t));
		return;
	}

	memset(&sock_p, 0, sizeof(struct bst_set_sock_sync_prop));
	bastet_get_comm_prop(sk, &sock_p.guide);
	bastet_get_sock_prop(sk, &sock_p.sync_prop);

	err = post_indicate_packet(BST_IND_SOCK_SYNC_PROP, &sock_p, sizeof(sock_p));
	if (!err) {
		/* if post success */
		bsk->bastet_sock_state = BST_SOCK_INVALID;
	}
}

static void bastet_store_ts_recent(struct tcp_sock *tp, u32 new_ts_recent, u32 new_ts_rencent_tick)
{
	tp->rx_opt.ts_recent = new_ts_recent;

	/* new_ts_rencent_tick has not changed since been passed to modem */
	if (0 != new_ts_rencent_tick) {
		long new_stamp = get_seconds() - ((tcp_time_stamp - new_ts_rencent_tick) / HZ);
		tp->rx_opt.ts_recent_stamp = new_stamp;
	}
}

/*
 * Adjust sock sync properties.
 */
static int adjust_sock_sync_prop(struct sock *sk, struct bst_sock_sync_prop *sync_p)
{
	struct tcp_sock *tp;
	struct sk_buff *skb = NULL;
	u32 seq_changed = 0;
	u32 new_seq;

	tp = tcp_sk(sk);
	new_seq = sync_p->seq;

	/*
	 * There may be more than one sk_buff in tcp write queue,
	 * Adjust them all.
	 */
	skb = tcp_write_queue_head(sk);
	while (NULL != skb) {
		struct tcp_skb_cb *tcb = TCP_SKB_CB(skb);

		if (skb == tcp_write_queue_head(sk)) {
			if (new_seq < tcb->seq) {
				seq_changed = BST_MAX_SEQ_VALUE - tcb->seq;
				seq_changed += new_seq;
			} else {
				seq_changed = new_seq - tcb->seq;
			}
			new_seq = tp->write_seq + seq_changed;
		}

		tcb->seq += seq_changed;
		tcb->end_seq += seq_changed;

		if (!tcp_skb_is_last(sk, skb))
			skb = tcp_write_queue_next(sk, skb);
		else
			skb = NULL;
	}

	if (NULL == tcp_write_queue_head(sk)) {
		seq_changed = new_seq - tp->write_seq;
	}

	tp->write_seq = new_seq;
	tp->rcv_nxt = sync_p->rcv_nxt;
	tp->snd_wnd = sync_p->snd_wnd;
	tp->snd_nxt += seq_changed;

	tp->copied_seq = tp->rcv_nxt;
	tp->rcv_wup = tp->rcv_nxt;
	tp->snd_una += seq_changed;

	if (likely(tp->rx_opt.tstamp_ok)) {
		tp->tsoffset = sync_p->ts_current - tcp_time_stamp;

		bastet_store_ts_recent(tp, sync_p->ts_recent, sync_p->ts_recent_tick);
	}

	return 0;
}

static void sock_set_internal(struct sock *sk, struct bst_sock_sync_prop *sync_p)
{
	struct bastet_sock *bsk = sk->bastet;

	if (BST_SOCK_INVALID == bsk->bastet_sock_state
		|| BST_SOCK_UPDATING == bsk->bastet_sock_state) {

		adjust_sock_sync_prop(sk, sync_p);

		bsk->bastet_sock_state = BST_SOCK_VALID;

		process_sock_send_and_recv(sk);
	}

	if (BST_USER_STOP == bsk->user_ctrl) {
		bsk->bastet_sock_state = BST_SOCK_NOT_USED;
	}
}

/*
 * BST_TMR_SET_SOCK_SYNC timeout.
 */
static void set_sock_bastet_timeout(struct sock *sk)
{
	struct bastet_sock *bsk = sk->bastet;

	bsk->bastet_timer_event = BST_TMR_EVT_INVALID;

	if (NULL == bsk->sync_p) {
		BASTET_LOGE("sk: %p not expected null sync prop", sk);
		return;
	}

	sock_set_internal(sk, bsk->sync_p);

	kfree(bsk->sync_p);
	bsk->sync_p = NULL;
}

/*
 * Read tcp_reset in tcp_input.c for reference.
 */
static void set_sock_close_internal(struct sock *sk)
{
	switch (sk->sk_state) {
	case TCP_SYN_SENT:
		sk->sk_err = ECONNREFUSED;
		break;
	case TCP_CLOSE_WAIT:
		sk->sk_err = EPIPE;
		break;
	case TCP_CLOSE:
		return;
	default:
		sk->sk_err = ECONNRESET;
	}
	/* This barrier is coupled with smp_rmb() in tcp_poll() */
	smp_wmb();

	if (!sock_flag(sk, SOCK_DEAD))
		sk->sk_error_report(sk);

	tcp_done(sk);
}

/*
 * BST_TMR_CLOSE_SOCK timeout.
 *
 */
static void close_sock_bastet_timeout(struct sock *sk)
{
	sk->bastet->bastet_timer_event = BST_TMR_EVT_INVALID;

	set_sock_close_internal(sk);
}

/*
 * Bastet sock timeout, include all bastet time events.
 */
static void bastet_sock_bastet_timeout(unsigned long data)
{
	int event;
	struct sock *sk = (struct sock *)data;
	struct bastet_sock *bsk = sk->bastet;

	BASTET_LOGI("sk: %p time event: %d", sk, bsk->bastet_timer_event);

	bh_lock_sock(sk);

	/* Include in lock */
	event = bsk->bastet_timer_event;

	if (sock_owned_by_user(sk)) {
		/* Try again later */
		if (BST_TMR_DELAY_SOCK_SYNC == event) {
			bastet_wakelock_acquire_timeout(BST_SKIP_SOCK_OWNER_TIME + BST_WAKELOCK_TIMEOUT);
		}
		sk_reset_timer(sk, &bsk->bastet_timer, jiffies + BST_SKIP_SOCK_OWNER_TIME);
		goto out_unlock;
	}

	switch(event){
	case BST_TMR_REQ_SOCK_SYNC:
		request_sock_bastet_timeout(sk);
		break;
	case BST_TMR_SET_SOCK_SYNC:
		set_sock_bastet_timeout(sk);
		break;
	case BST_TMR_DELAY_SOCK_SYNC:
		delay_sock_bastet_timeout(sk);
		break;
	case BST_TMR_CLOSE_SOCK:
		close_sock_bastet_timeout(sk);
		break;
	default:
		BASTET_LOGE("sk: %p invalid time event: %d", sk, event);
		break;
	}

	sk_mem_reclaim(sk);
out_unlock:
	bh_unlock_sock(sk);
	sock_put(sk);
}

/*
 * When sock owner uses sock, we should not sync sock for a while
 */
void bastet_delay_sock_sync_notify(struct sock *sk)
{
	struct bastet_sock *bsk = sk->bastet;

	if (!is_bastet_enabled()) {
		return;
	}
	if (NULL != bsk && TCP_ESTABLISHED == sk->sk_state) {
		bsk->last_sock_active_time_point = jiffies;

		if (BST_TMR_DELAY_SOCK_SYNC != bsk->bastet_timer_event
			&& BST_SOCK_VALID == bsk->bastet_sock_state
			&& BST_USER_START == bsk->user_ctrl) {
			setup_sock_sync_delay_timer(sk);
		}
	}
}

/*
 * CRIU's socket repair would stop bastet function
 * Returns true, if repair should be stopped.
 * Otherwise return false.
 */
bool bastet_sock_repair_prepare_notify(struct sock *sk, int val)
{
	if (!is_bastet_enabled()) {
		return false;
	}
	if (!sk || !sk->bastet)
		return false;

	sk->bastet->need_repair = val;

	if (val) {
		/* Userspace requires repair */
		return do_sock_send_prepare(sk);
	} else {
		/* Userspace restore repair */
		spin_lock_bh(&sk->sk_lock.slock);
		bastet_delay_sock_sync_notify(sk);
		spin_unlock_bh(&sk->sk_lock.slock);
		return false;
	}
}

/*
 * Set socket sync hold time
*/
int set_sock_sync_hold_time(struct bst_set_sock_sync_delay hold_delay)
{
	struct sock *sk = NULL;
	struct bastet_sock *bsk = NULL;
	unsigned long orig_delay = 0;
	unsigned long expire = 0;

	sk = get_sock_by_fd_pid(hold_delay.guide.fd, hold_delay.guide.pid);
	if (NULL == sk) {
		BASTET_LOGE("can not find sock by fd: %d pid: %d", hold_delay.guide.fd, hold_delay.guide.pid);
		return -ENOENT;
	}
	bsk = sk->bastet;
	if (NULL == bsk) {
		BASTET_LOGE("sk: %p not expected bastet null", sk);
		sock_put(sk);
		return -EPERM;
	}
	BASTET_LOGI("hold_time=%u", hold_delay.hold_time);
	orig_delay = bsk->delay_sync_time_section;
	bsk->delay_sync_time_section = msecs_to_jiffies(hold_delay.hold_time);
	if (timer_pending(&bsk->bastet_timer)) {
		if (orig_delay < bsk->delay_sync_time_section) {
			BASTET_LOGI("screen off to on");
			expire = bsk->last_sock_active_time_point + bsk->delay_sync_time_section;
		} else {
			BASTET_LOGI("screen on to off");
			if (time_after(jiffies, bsk->last_sock_active_time_point + bsk->delay_sync_time_section)) {
				BASTET_LOGI("need to timeout right now");
				expire = jiffies;
			} else {
				expire = bsk->last_sock_active_time_point + bsk->delay_sync_time_section;
			}
		}
		bsk->bastet_timeout = expire;
		mod_timer(&bsk->bastet_timer, expire);
	}
	sock_put(sk);

	return 0;
}

/*
 * Generate bastet sock in sock struct.
 */
static int create_bastet_sock(struct sock *sk, struct bst_set_sock_sync_delay *init_prop)
{
	struct bastet_sock *bsk;

	bsk = kmalloc(sizeof(*bsk), GFP_KERNEL);
	if (NULL == bsk) {
		BASTET_LOGE("kmalloc failed");
		return -ENOMEM;
	}

	bsk->bastet_sock_state = BST_SOCK_NOT_USED;
	bsk->bastet_timer_event = BST_TMR_EVT_INVALID;
	bsk->user_ctrl = BST_USER_STOP;
	bsk->fd = init_prop->guide.fd;
	bsk->pid = init_prop->guide.pid;
	bsk->proxy_id = init_prop->proxy_id;
	bsk->bastet_timeout = 0;
	bsk->last_sock_active_time_point = jiffies;
	bsk->sync_p = NULL;
	bsk->need_repair = 0;

	bsk->delay_sync_time_section = msecs_to_jiffies(init_prop->hold_time);

	setup_timer(&bsk->bastet_timer, bastet_sock_bastet_timeout, (unsigned long)sk);

	skb_queue_head_init(&bsk->recv_queue);
	bsk->recv_len = 0;
	init_waitqueue_head(&bsk->wq);
	bsk->flag = false;

	sk->bastet = bsk;
	return 0;
}

static int do_start_bastet_sock(struct sock *sk, struct bst_set_sock_sync_delay *init_prop)
{
	int err = 0;
	struct bastet_sock *bsk = sk->bastet;

	if (NULL == bsk) {
		err = create_bastet_sock(sk, init_prop);
		if (err < 0) {
			return err;
		}

		bsk = sk->bastet;
	}
	bsk->last_sock_active_time_point = jiffies;

	spin_lock_bh(&sk->sk_lock.slock);

	bsk->user_ctrl = BST_USER_START;

	if (BST_SOCK_INVALID == bsk->bastet_sock_state
		|| BST_SOCK_UPDATING == bsk->bastet_sock_state) {
		err = -EPERM;
		goto out_unlock;
	}

	bsk->bastet_sock_state = BST_SOCK_VALID;

	setup_sock_sync_delay_timer(sk);

out_unlock:
	spin_unlock_bh(&sk->sk_lock.slock);

	return err;
}

/*
 * Function is called when application starts bastet proxy.
 */
int start_bastet_sock(struct bst_set_sock_sync_delay *init_prop)
{
	int err = 0;
	struct sock *sk;
	struct bst_sock_id *guide = &init_prop->guide;

	sk = get_sock_by_fd_pid(guide->fd, guide->pid);
	if (NULL == sk) {
		BASTET_LOGE("can not find sock by fd: %d pid: %d", guide->fd, guide->pid);
		return -ENOENT;
	}

	if (TCP_ESTABLISHED != sk->sk_state) {
		BASTET_LOGE("sk: %p sk_state is not TCP_ESTABLISHED", sk);
		sock_put(sk);
		return -EPERM;
	}

	if (tcp_sk(sk)->repair) {
		BASTET_LOGE("sk: %p in repair mode", sk);
		sock_put(sk);
		return -EPERM;
	}

	BASTET_LOGI("sk: %p", sk);

	err = do_start_bastet_sock(sk, init_prop);
	sock_put(sk);
	return err;
}

/*
 * Function is called when application stops bastet proxy.
 */
int stop_bastet_sock(struct bst_sock_id *guide)
{
	struct sock *sk;
	struct bastet_sock *bsk;
	u8 sync_state;

	sk = get_sock_by_fd_pid(guide->fd, guide->pid);
	if (NULL == sk) {
		BASTET_LOGE("can not find sock by fd: %d pid: %d", guide->fd, guide->pid);
		return -ENOENT;
	}

	bsk = sk->bastet;
	if (NULL == bsk) {
		BASTET_LOGE("sk: %p not expected bastet null", sk);
		sock_put(sk);
		return -EPERM;
	}

	BASTET_LOGI("sk: %p", sk);

	spin_lock_bh(&sk->sk_lock.slock);

	bsk->user_ctrl = BST_USER_STOP;

	sync_state = bsk->bastet_sock_state;
	switch (sync_state) {
	case BST_SOCK_VALID:
		bsk->bastet_sock_state = BST_SOCK_NOT_USED;

		cancel_sock_bastet_timer(sk);
		break;
	case BST_SOCK_INVALID:
		request_sock_sync(sk);
		break;
	default:
		break;
	}

	spin_unlock_bh(&sk->sk_lock.slock);

	sock_put(sk);
	return 0;
}

/*
 * Function is called when application prepare bastet proxy.
 */
int prepare_bastet_sock(struct bst_set_sock_sync_delay *sync_prop)
{
	int err = 0;
	struct sock *sk;
	struct bastet_sock *bsk;

	sk = get_sock_by_fd_pid(sync_prop->guide.fd, sync_prop->guide.pid);
	if (NULL == sk) {
		BASTET_LOGE("can not find sock by fd: %d pid: %d", sync_prop->guide.fd, sync_prop->guide.pid);
		return -ENOENT;
	}

	if (TCP_ESTABLISHED != sk->sk_state) {
		BASTET_LOGE("sk: %p sk_state is not TCP_ESTABLISHED", sk);
		sock_put(sk);
		return -EPERM;
	}

	if (tcp_sk(sk)->repair) {
		BASTET_LOGE("sk: %p in repair mode", sk);
		sock_put(sk);
		return -EPERM;
	}

	BASTET_LOGI("sk: %p", sk);

	bsk = sk->bastet;
	if (NULL == bsk) {
		err = create_bastet_sock(sk, sync_prop);
		if (err < 0) {
			sock_put(sk);
			return err;
		}
		bsk = sk->bastet;
	}

	sock_put(sk);

	return err;
}

/*
 * Setup sock set timer.
 */
static int setup_sock_sync_set_timer(struct sock *sk, struct bst_sock_sync_prop *sync_p)
{
	struct bastet_sock *bsk = sk->bastet;

	bsk->sync_p = kmalloc(sizeof(*sync_p), GFP_KERNEL);
	if (NULL == bsk->sync_p) {
		return -ENOMEM;
	}

	memcpy(bsk->sync_p, sync_p, sizeof(*sync_p));

	bsk->bastet_timer_event = BST_TMR_SET_SOCK_SYNC;

	sk_reset_timer(sk, &bsk->bastet_timer, jiffies + BST_SKIP_SOCK_OWNER_TIME);
	return 0;
}

/*
 * Set sock sync properties.
 */
int set_tcp_sock_sync_prop(struct bst_set_sock_sync_prop *set_prop)
{
	int err = 0;
	struct sock *sk;
	struct bastet_sock *bsk;
	struct bst_sock_comm_prop *guide = &set_prop->guide;

	sk = get_sock_by_comm_prop(guide);
	if (NULL == sk) {
		BASTET_LOGE("can not find sock by lport: %d, lIp: %pI4, rport: %d, rIp: %pI4",
					guide->local_port, &guide->local_ip,
					guide->remote_port, &guide->remote_ip);
		return -ENOENT;
	}

	if (sk->sk_state == TCP_TIME_WAIT) {
		BASTET_LOGE("sk: %p not expected time wait sock", sk);
		inet_twsk_put(inet_twsk(sk));
		return -EPERM;
	}

	bsk = sk->bastet;
	if (NULL == bsk) {
		BASTET_LOGE("sk: %p not expected bastet null", sk);
		err = -EPERM;
		goto out_put;
	}

	BASTET_LOGI("sk: %p", sk);

	spin_lock_bh(&sk->sk_lock.slock);

	if (NULL != bsk->sync_p) {
		BASTET_LOGE("sk: %p has a pending sock set", sk);
		err = -EPERM;
		goto out_unlock;
	}

	cancel_sock_bastet_timer(sk);

	if (sock_owned_by_user(sk)) {
		err = setup_sock_sync_set_timer(sk, &set_prop->sync_prop);
		goto out_unlock;
	}

	sock_set_internal(sk, &set_prop->sync_prop);

out_unlock:
	spin_unlock_bh(&sk->sk_lock.slock);

	adjust_traffic_flow_by_sock(sk, set_prop->sync_prop.tx, set_prop->sync_prop.rx);

out_put:
	sock_put(sk);
	return err;
}

void bastet_sync_prop_cancel(struct sock *sk)
{
	if (sk->bastet) {
		sk->bastet->user_ctrl = BST_USER_STOP;
		cancel_sock_bastet_timer(sk);
	}
}

int bastet_sync_prop_start(struct bst_set_sock_sync_prop *set_prop)
{
	int err = 0;
	struct sock *sk;
	struct bastet_sock *bsk;
	struct bst_sock_comm_prop *guide = &set_prop->guide;

	sk = get_sock_by_comm_prop(guide);
	if (NULL == sk) {
		BASTET_LOGE("can not find sock by lport: %d, lIp: %pI4, rport: %d, rIp: %pI4",
					guide->local_port, &guide->local_ip,
					guide->remote_port, &guide->remote_ip);
		return -ENOENT;
	}

	if (sk->sk_state == TCP_TIME_WAIT) {
		BASTET_LOGE("sk: %p not expected time wait sock", sk);
		inet_twsk_put(inet_twsk(sk));
		return -EPERM;
	}

	bsk = sk->bastet;
	if (NULL == bsk) {
		BASTET_LOGE("sk: %p not expected bastet null", sk);
		err = -EPERM;
		goto out_put;
	}

	BASTET_LOGI("sk: %p", sk);

	if (NULL != bsk->sync_p) {
		BASTET_LOGE("sk: %p has a pending sock set", sk);
		err = -EPERM;
		goto out;
	}

	sock_set_internal(sk, &set_prop->sync_prop);
	bastet_sync_prop_cancel(sk);
	bsk->flag = true;
	BASTET_LOGI("wake up bastet wq");
	wake_up_interruptible(&bsk->wq);

out:
	adjust_traffic_flow_by_sock(sk, set_prop->sync_prop.tx, set_prop->sync_prop.rx);

out_put:
	sock_put(sk);
	return err;
}

int bastet_sync_prop_stop(struct bst_sock_comm_prop *comm_prop)
{
	struct sock *sk;
	struct bastet_sock *bsk;

	sk = get_sock_by_comm_prop(comm_prop);
	if (NULL == sk) {
		BASTET_LOGE("can not find sock by lport: %d, lIp: %pI4, rport: %d, rIp: %pI4",
					comm_prop->local_port, &comm_prop->local_ip,
					comm_prop->remote_port, &comm_prop->remote_ip);
		return -ENOENT;
	}

	if (sk->sk_state == TCP_TIME_WAIT) {
		BASTET_LOGE("sk: %p not expected time wait sock", sk);
		inet_twsk_put(inet_twsk(sk));
		return -EPERM;
	}
	BASTET_LOGI("sk: %p", sk);
	bsk = sk->bastet;
	if (bsk) {
		if (bsk->bastet_sock_state != BST_SOCK_NOT_USED) {
			bsk->user_ctrl = BST_USER_START;
			bsk->bastet_sock_state = BST_SOCK_VALID;
			setup_sock_sync_delay_timer(sk);
		}
	}

	sock_put(sk);
	return 0;
}

/*
 * Get sock common properties.
 */
int get_tcp_sock_comm_prop(struct bst_get_sock_comm_prop *get_prop)
{
	struct sock *sk;
	struct bst_sock_id *guide = &get_prop->guide;

	sk = get_sock_by_fd_pid(guide->fd, guide->pid);
	if (NULL == sk) {
		BASTET_LOGE("can not find sock by fd: %d pid: %d", guide->fd, guide->pid);
		return -ENOENT;
	}

	if (TCP_ESTABLISHED != sk->sk_state) {
		BASTET_LOGE("sk: %p sk_state not expected", sk);
		sock_put(sk);
		return -EPERM;
	}

	BASTET_LOGI("sk: %p", sk);

	bastet_get_comm_prop(sk, &get_prop->comm_prop);
	sock_put(sk);
	return 0;
}

static void setup_sock_sync_close_timer(struct sock *sk)
{
	struct bastet_sock *bsk = sk->bastet;

	bsk->bastet_timer_event = BST_TMR_CLOSE_SOCK;

	sk_reset_timer(sk, &bsk->bastet_timer, jiffies + BST_SKIP_SOCK_OWNER_TIME);
}

/*
 * Close sock, when modem bastet fails this sock.
 */
int set_tcp_sock_closed(struct bst_sock_comm_prop *guide)
{
	int err = 0;
	struct sock *sk;
	struct bastet_sock *bsk;

	sk = get_sock_by_comm_prop(guide);
	if (NULL == sk) {
		BASTET_LOGE("can not find sock by lport: %d, lIp: %pI4, rport: %d, rIp: %pI4",
					guide->local_port, &guide->local_ip,
					guide->remote_port, &guide->remote_ip);
		return -ENOENT;
	}

	if (sk->sk_state == TCP_TIME_WAIT) {
		BASTET_LOGE("sk: %p not expected time wait sock", sk);
		inet_twsk_put(inet_twsk(sk));
		return -EPERM;
	}

	bsk = sk->bastet;
	if (NULL == bsk) {
		BASTET_LOGE("sk: %p not expected bastet null", sk);
		err = -EPERM;
		goto out_put;
	}

	BASTET_LOGI("sk: %p", sk);

	spin_lock_bh(&sk->sk_lock.slock);

	if (BST_SOCK_INVALID != bsk->bastet_sock_state
		&& BST_SOCK_UPDATING != bsk->bastet_sock_state) {
		BASTET_LOGE("sk: %p sync_current_state: %d not expected", sk, bsk->bastet_sock_state);
		goto out_unlock;
	}

	cancel_sock_bastet_timer(sk);

	bsk->bastet_sock_state = BST_SOCK_NOT_USED;

	if (sock_owned_by_user(sk)) {
		setup_sock_sync_close_timer(sk);
		goto out_unlock;
	}

	set_sock_close_internal(sk);

out_unlock:
	spin_unlock_bh(&sk->sk_lock.slock);

out_put:
	sock_put(sk);
	return err;
}

/*
 * Release bastet sock and Post sock close information.
 */
void bastet_sock_release(struct sock *sk)
{
	struct bst_close_sock_prop prop;
	struct bastet_sock *bsk = sk->bastet;

	if (!is_bastet_enabled()) {
		return;
	}

	if (NULL != bsk) {
		bastet_get_comm_prop(sk, &prop.comm_prop);
		prop.proxy_id = bsk->proxy_id;

		BASTET_LOGI("indicate socket close, proxyId=0x%08X", prop.proxy_id);
		post_indicate_packet(BST_IND_SOCK_CLOSED, &prop, sizeof(struct bst_close_sock_prop));

		if (NULL != bsk->sync_p) {
			kfree(bsk->sync_p);
			bsk->sync_p = NULL;
		}

		kfree(sk->bastet);
		sk->bastet = NULL;
	}

	if (sk->reconn) {
		BASTET_LOGI("kfree sk reconn");
		kfree(sk->reconn);
		sk->reconn = NULL;
	}
}

int get_bastet_sock_state(struct sock *sk)
{
	return sk->bastet ? sk->bastet->bastet_sock_state : BST_SOCK_NOT_CREATED;
}

int get_tcp_bastet_sock_state(struct bst_get_bastet_sock_state *get_prop)
{
	struct sock *sk;
	struct bst_sock_id *guide = &get_prop->guide;

	sk = get_sock_by_fd_pid(guide->fd, guide->pid);
	if (NULL == sk) {
		BASTET_LOGE("can not find sock by fd: %d pid: %d", guide->fd, guide->pid);
		return -ENOENT;
	}
	BASTET_LOGI("sk: %p", sk);

	get_prop->sync_state = get_bastet_sock_state(sk);

	sock_put(sk);
	return 0;
}
