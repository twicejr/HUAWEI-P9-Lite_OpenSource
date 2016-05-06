/*
 * Copyright (c) Huawei Technologies Co., Ltd. 1998-2014. All rights reserved.
 *
 * File name: hw_kstate.c
 * Description: This file use to send kernel state
 * Author: gavin.yangsong@huawei.com
 * Version: 0.1
 * Date:  2014/07/17
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>
#include <linux/kfifo.h>
#include <linux/kthread.h>
#include <linux/hw_kstate.h>
#include <net/sock.h>

MODULE_LICENSE("Dual BSD/GPL");

#define KSTATE_FIFO_SIZE	4096 // kfifo buffer size
#define KSTATE_THREAD_NAME	"hw_kstate"

static struct task_struct *kstate_thread = NULL;
static struct kfifo kstate_fifo; //fifo is full of pointer to struct ksmsg
static spinlock_t kstate_kfifo_lock;
static spinlock_t kstate_hook_lock;
static struct sock *nlfd = NULL;
static int kstate_user_pid = 0;
static struct list_head kstate_hooks;

static DECLARE_WAIT_QUEUE_HEAD(kstate_wait_queue);

/*
 * Function: is_channel_valid
 * Description: check channel valid or not
 * Input:	@channel - channel to check
 * Output:
 * Return:	false -- invalid
 *			true -- valid
*/
static inline bool is_channel_valid(int channel)
{
	return (channel > CHANNEL_ID_NONE && channel < CHANNEL_ID_END);
}

/*
 * Function: is_tag_valid
 * Description: check packet tag valid or not
 * Input:	@tag - tag to check
 * Output:
 * Return:	false -- invalid
 *			true -- valid
*/
static inline bool is_tag_valid(int tag)
{
	return (tag > PACKET_TAG_NONE && tag < PACKET_TAG_END);
}

/*
 * Function: send_to_user
 * Description: send message to user space and msg
 *				must be alloced memory in calling func,
 *				and be freed here
 * Input:	@msg - source msg
 * Output:
 * Return:	-1 -- failed
 *			0 -- successed
*/
static int send_to_user(struct ksmsg *msg)
{
	struct sk_buff *skb = NULL;
	struct nlmsghdr *nlh = NULL;
	int len = 0;
	int ret  = -1;

	if (IS_ERR_OR_NULL(msg)) {
		pr_err("hw_kstate %s: msg is NULL!\n", __func__);
		goto err;
	}

	len = sizeof(struct ksmsg) + msg->length;
	skb = alloc_skb(NLMSG_SPACE(len), GFP_ATOMIC);
	if (IS_ERR_OR_NULL(skb)) {
		pr_err("hw_kstate %s: alloc skb failed!\n", __func__);
		goto err;
	}

	nlh = nlmsg_put(skb, 0, 0, 0, len, 0);
	memcpy(NLMSG_DATA(nlh), msg, len);
	/*send up msg*/
	if (netlink_unicast(nlfd, skb, kstate_user_pid, MSG_DONTWAIT) < 0) {
		pr_err("hw_kstate %s: netlink_unicast failed!\n", __func__);
		goto err;
	}
	ret = 0;
err:
	return ret;
}

/*
 * Function: fifo_out
 * Description: receive data from module and process it here
 * Input:	@data - source data
 * Output:
 * Return:	void
*/
static int fifo_out(void *data) {
	struct ksmsg *msg = NULL;

	while (1) {
		/*wait module data*/
		wait_event_interruptible(kstate_wait_queue, !kfifo_is_empty(&kstate_fifo));
		/*fifo has data*/
		while (0 != kfifo_out(&kstate_fifo, &msg, sizeof(struct ksmsg*))) {
			/*send msg to user space*/
			if (send_to_user(msg) < 0) {
				pr_err("hw_kstate %s: send msg to user failed!\n", __func__);
			}
			kfree(msg);
		}
	}
	return 0;
}

/*
 * Function: fifo_in
 * Description: receive data from module and save it to fifo
 * Input:	@msg - msg to save
 * Output:
 * Return:	-1 -- failed
 *			0 -- successed
*/
static int fifo_in(struct ksmsg *msg)
{
	int ret = -1;

	if (IS_ERR_OR_NULL(msg)) {
		pr_err("hw_kstate %s: the msg point is err!\n", __func__);
		goto err;
	}

	/*put data in kfifo*/
	spin_lock_bh(&kstate_kfifo_lock);
	if (0 == kfifo_in(&kstate_fifo, &msg, sizeof(msg))) {
		/*put data failed*/
		if (kfifo_is_full(&kstate_fifo)) {
			if (send_to_user(msg) < 0) {
				pr_err("hw_kstate %s: send msg to user failed!\n", __func__);
			}
			kfree(msg);
		} else {
			pr_err("hw_kstate %s: kfifo in error!\n", __func__);
			kfree(msg);
		}
	} else {
		/*put data successfully*/
		ret = 0;
		wake_up_interruptible(&kstate_wait_queue);
	}
	spin_unlock_bh(&kstate_kfifo_lock);

err:
	return ret;
}

/*
 * Function: process_user_data
 * Description: receive data from user and process it here
 * Input:	@msg - source msg
 * Output:
 * Return:	void
*/
static void process_user_data(struct ksmsg *msg)
{
	struct kstate_opt *elem = NULL;
	struct ksmsg tmp_msg;

	if (IS_ERR_OR_NULL(msg)) {
		pr_err("hw_kstate %s: msg is NULL!\n", __func__);
		return;
	}

	if (PACKET_TAG_VALIDATE_CHANNEL == msg->tag) {
		/*confirm connection is still online*/
		tmp_msg.tag = PACKET_TAG_VALIDATE_CHANNEL;
		tmp_msg.src = CHANNEL_ID_NETLINK;
		tmp_msg.dst = CHANNEL_ID_NONE;
		tmp_msg.length= 0;

		/*tmp_msg should be freed in this func*/
		send_to_user(&tmp_msg);
	} else {
		/*receive msg from user*/
		if (CHANNEL_ID_NETLINK != msg->dst) {
			pr_err("hw_kstate %s: channel=%u is not netlink!\n", __func__, msg->dst);
			return;
		}

		/*calling corresponding hook func*/
		spin_lock(&kstate_hook_lock);
		list_for_each_entry(elem, &kstate_hooks, list) {
			if (elem->tag == msg->tag) {
				if (!IS_ERR_OR_NULL(elem->hook)) {
					elem->hook(msg->src, msg->tag, msg->buffer, msg->length);
				}
			}
		}
		spin_unlock(&kstate_hook_lock);
	}
}

/*
 * Function: recv_from_user
 * Description: receive data from user calling process_user_data() to process it
 * Input:	@skb - source data
 * Output:
 * Return:	void
*/
static void recv_from_user(struct sk_buff *skb)
{
	struct sk_buff *tmp_skb = NULL;
	struct nlmsghdr *nlh = NULL;
	struct ksmsg *msg = NULL;
	struct ksmsg *data = NULL;
	int len  = 0;

	if (IS_ERR_OR_NULL(skb)) {
		pr_err("hw_kstate %s: skb is NULL!\n", __func__);
		return;
	}

	tmp_skb = skb;
	if (tmp_skb->len >= NLMSG_SPACE(0)) {
		nlh = nlmsg_hdr(tmp_skb);
		kstate_user_pid = nlh->nlmsg_pid;
		len = NLMSG_PAYLOAD(nlh, 0);
		data = (struct ksmsg*)NLMSG_DATA(nlh);

		if (len >= (sizeof(struct ksmsg) + data->length)) {
			msg = (struct ksmsg*)kmalloc(len, GFP_ATOMIC);
			if (IS_ERR_OR_NULL(msg)) {
				pr_err("hw_kstate %s: msg is NULL!\n", __func__);
				return;
			}
			memcpy(msg, data, len);

			process_user_data(msg);
			kfree(msg);
		} else {
			pr_err("hw_kstate %s: length err!\n", __func__);
		}
	}
}

/*
 * Function: kstate
 * Description: kernel information entry function
 * Input:	@dst - user to send
 *			@tag - packet tag
 *			@data - source data
 *			@len - data len
 * Output:
 * Return:	-1 -- failed
 *			0 -- successed
*/
int kstate(CHANNEL_ID dst, PACKET_TAG tag, const char *data, size_t len)
{
	struct ksmsg *msg = NULL;
	int msg_len = 0;

	if (!is_channel_valid(dst)) {
		pr_err("hw_kstate %s: channel is invalid!\n", __func__);
		return -1;
	}

	if (!is_tag_valid(tag)) {
		pr_err("hw_kstate %s: tag is invalid!\n", __func__);
		return -1;
	}

	if (IS_ERR_OR_NULL(data)) {
		pr_err("hw_kstate %s: data is NULL!\n", __func__);
		return -1;
	}

	/*msg will be freed in fifo_in() or send_to_user()*/
	msg_len = sizeof(struct ksmsg) + len;
	msg = (struct ksmsg*)kmalloc(msg_len, GFP_ATOMIC);
	if (IS_ERR_OR_NULL(msg)) {
		pr_err("hw_kstate %s: msg is NULL!\n", __func__);
		return -1;
	}
	memset(msg, 0, msg_len);
	msg->tag = tag;
	msg->src = CHANNEL_ID_NETLINK;
	msg->dst = dst;
	msg->length = len;
	memcpy(msg->buffer, data, len);

	if (fifo_in(msg) < 0) {
		pr_err("hw_kstate %s: save msg from module failed!\n", __func__);
		return -1;
	}
	return 0;
}

/*
 * Function: kstate_register_hook
 * Description: register hook function to kstate
 * Input:	@opt - kstate_opt struct to register
 * Output:
 * Return:	-1 -- failed
 *			0 -- successed
*/
int kstate_register_hook(struct kstate_opt *opt)
{
	struct kstate_opt *elem = NULL;
	int ret = -1;

	if (IS_ERR_OR_NULL(opt)) {
		pr_err("hw_kstate %s: kstate_opt is NULL!\n", __func__);
		goto err;
	}

	if (!is_channel_valid(opt->dst)) {
		pr_err("hw_kstate %s: kstate channel=%u is invalid!\n", __func__, opt->dst);
		goto err;
	}

	if (!is_tag_valid(opt->tag)) {
		pr_err("hw_kstate %s: kstate tag=%u is invalid!\n", __func__, opt->tag);
		goto err;
	}

	spin_lock(&kstate_hook_lock);
	list_for_each_entry(elem, &kstate_hooks, list) {
		if (elem->tag == opt->tag) {
			ret  = 0;
			goto out;
		}
	}
	list_add_tail(&opt->list, &kstate_hooks);
	ret = 0;
out:
	spin_unlock(&kstate_hook_lock);
err:
	return ret;
}

/*
 * Function: kstate_unregister_hook
 * Description: unregister hook function from kstate
 * Input:	@opt - kstate_opt struct to unregister
 * Output:
 * Return:	void
*/
void kstate_unregister_hook(struct kstate_opt *opt)
{
	struct kstate_opt *elem = NULL;
	struct kstate_opt *n = NULL;

	if (IS_ERR_OR_NULL(opt)) {
		pr_err("hw_kstate %s: kstate_opt is NULL!\n", __func__);
		return;
	}

	spin_lock(&kstate_hook_lock);
	list_for_each_entry_safe(elem, n, &kstate_hooks, list) {
		if (opt == elem) {
			list_del(&elem->list);
			break;
		}
	}
	spin_unlock(&kstate_hook_lock);
}

/*
 * Function: release_netlink_sock
 * Description: release netlink sock from skb queue
 * Input:
 * Output:
 * Return:	void
*/
static void release_netlink_sock(void)
{
	if (!IS_ERR_OR_NULL(nlfd) && nlfd->sk_socket) {
		if (!IS_ERR_OR_NULL(nlfd->sk_socket)) {
			sock_release(nlfd->sk_socket);
			nlfd = NULL;
		}
	}
}

static int __init kstate_init(void)
{
	int ret = -1;
	struct netlink_kernel_cfg cfg;

	cfg.groups = 0;
	cfg.input = recv_from_user;

	INIT_LIST_HEAD(&kstate_hooks);

	spin_lock_init(&kstate_kfifo_lock);
	spin_lock_init(&kstate_hook_lock);

	/*create netlink sock to receive data from user space*/
	nlfd = netlink_kernel_create(&init_net, NETLINK_HW_KSTATE, &cfg);
	if (IS_ERR_OR_NULL(nlfd)) {
		ret = PTR_ERR(nlfd);
		pr_err("hw_kstate %s: create netlink error!\n", __func__);
		goto err_create_netlink;
	}

	/*init fifo*/
	ret = kfifo_alloc(&kstate_fifo, KSTATE_FIFO_SIZE , GFP_ATOMIC);
	if (0 != ret) {
		pr_err("hw_kstate %s: error kfifo_alloc!\n", __func__);
		goto err_alloc_kfifo;
	}

	/*run thread*/
	kstate_thread = kthread_run(fifo_out, NULL, KSTATE_THREAD_NAME);
	if (IS_ERR_OR_NULL(kstate_thread)) {
		pr_err("hw_kstate %s: error create thread!\n", __func__);
		goto err_create_thread;
	}
	pr_info("hw_kstate %s: inited!\n", __func__);
	return 0;

err_create_thread:
	kfifo_free(&kstate_fifo);
err_alloc_kfifo:
	release_netlink_sock();
err_create_netlink:
	return ret;
}

static void __exit kstate_exit(void)
{
	if (!IS_ERR_OR_NULL(kstate_thread)) {
		kthread_stop(kstate_thread);
	}
	kfifo_free(&kstate_fifo);

	release_netlink_sock();
}

module_init(kstate_init);
module_exit(kstate_exit);