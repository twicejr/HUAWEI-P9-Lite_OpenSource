/* bastet_dev.c
 *
 * Bastet Driver Device.
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
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/ioctl.h>
#include <linux/poll.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#include <huawei_platform/power/bastet/bastet.h>
#include <huawei_platform/power/bastet/bastet_utils.h>

#define BASTET_NAME						"bastet"

#define BST_FIRST_MINOR					0
#define BST_DEVICES_NUMBER				1

dev_t bastet_dev;
struct cdev bastet_cdev;
struct class *bastet_class = NULL;

struct data_packet {
	struct list_head list;
	struct bst_device_ind data;
};

struct bastet_driver_data {
	wait_queue_head_t read_wait;
	spinlock_t read_lock;
	struct list_head read_queue;
};

static struct bastet_driver_data bastet_data;

extern bool bastet_dev_en;
extern atomic_t proxy;
extern atomic_t buffer;
extern atomic_t cp_reset;
extern int hrt_uid;

extern void bastet_traffic_flow_init(void);
extern void bastet_utils_init(void);
extern void bastet_utils_exit(void);

#ifdef CONFIG_HUAWEI_BASTET_COMM
extern void bastet_comm_init(void);
extern int bastet_comm_write(u8 *msg, u32 len);
extern int get_modem_rab_id(struct bst_modem_rab_id *info);
#endif

extern int start_bastet_sock(struct bst_set_sock_sync_delay *init_prop);
extern int stop_bastet_sock(struct bst_sock_id *guide);
extern int prepare_bastet_sock(struct bst_set_sock_sync_delay *sync_prop);
extern int get_tcp_sock_comm_prop(struct bst_get_sock_comm_prop *get_prop);
extern int set_tcp_sock_sync_prop(struct bst_set_sock_sync_prop *set_prop);
extern int set_tcp_sock_closed(struct bst_sock_comm_prop *guide);
extern int get_tcp_bastet_sock_state(struct bst_get_bastet_sock_state *get_prop);
extern int bind_local_ports(u16 *local_port);
extern int unbind_local_ports(u16 local_port);
extern int adjust_traffic_flow_by_pkg(uint8_t *buf, int cnt);
extern void bastet_wake_up_traffic_flow(void);
extern int set_current_net_device_name(char *iface);
extern int bastet_reconn_set(struct bst_get_sock_comm_prop get_prop);
extern void bastet_reconn_failed(struct bst_sock_comm_prop prop);
extern int bastet_reconn_proxyid_set(struct reconn_id id);
extern int bastet_sync_prop_start(struct bst_set_sock_sync_prop *set_prop);
extern int bastet_sync_prop_stop(struct bst_sock_comm_prop *comm_prop);
extern int set_sock_sync_hold_time(struct bst_set_sock_sync_delay hold_delay);
extern void clear_channel_occupied(void);
extern int bastet_partner_process_cmd(struct app_monitor_prop *prop, int32_t *tids);
extern int bastet_partner_init(void);
extern void bastet_partner_release(void);
extern void bastet_partner_clear(void);
extern int set_proc_info(struct set_process_info *info);
extern int set_special_uid(int32_t uid);
extern int set_netfilter(bool state);
extern void bastet_filter_init(void);
/*
 * Indicate Message Api
 */
int post_indicate_packet(bst_ind_type type, void *info, unsigned int len)
{
	struct data_packet *pkt = NULL;

	if (!bastet_dev_en) {
		BASTET_LOGE("bastet is not opened");
		return -ENOENT;
	}

	pkt = kmalloc(sizeof(struct data_packet) + len, GFP_ATOMIC);
	if (NULL == pkt) {
		BASTET_LOGE("failed to kmalloc");
		return -ENOMEM;
	}
	memset(pkt, 0, sizeof(struct data_packet) + len);

	pkt->data.cons = 0;
	pkt->data.type = type;
	pkt->data.len = len;
	if (NULL != info) {
		memcpy(pkt->data.value, info, len);
	}

	spin_lock_bh(&bastet_data.read_lock);
	list_add_tail(&pkt->list, &bastet_data.read_queue);
	spin_unlock_bh(&bastet_data.read_lock);

	wake_up_interruptible_sync_poll(&bastet_data.read_wait,
								POLLIN | POLLRDNORM | POLLRDBAND);

	return 0;
}

/*
 * this is main method to exchange data with user space,
 * including socket sync, get ip and port, adjust kernel flow
 *
 * return "int" by standard.
 */
static long bastet_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
{
	int rc = -EFAULT;
	void __user *argp = (void __user *)arg;

	switch (cmd) {
		case BST_IOC_SOCK_SYNC_START: {
			struct bst_set_sock_sync_delay init_p;

			if (copy_from_user(&init_p, argp, sizeof(init_p)))
				break;

			rc = start_bastet_sock(&init_p);
			break;
		}
		case BST_IOC_SOCK_SYNC_STOP: {
			struct bst_sock_id guide;

			if (copy_from_user(&guide, argp, sizeof(guide)))
				break;

			rc = stop_bastet_sock(&guide);
			break;
		}
		case BST_IOC_SOCK_SYNC_SET: {
			struct bst_set_sock_sync_prop set_p;

			if (copy_from_user(&set_p, argp, sizeof(set_p)))
				break;

			rc = set_tcp_sock_sync_prop(&set_p);
			break;
		}
		case BST_IOC_SOCK_COMM_GET: {
			struct bst_get_sock_comm_prop get_p;

			if (copy_from_user(&get_p, argp, sizeof(get_p)))
				break;

			rc = get_tcp_sock_comm_prop(&get_p);
			if (rc < 0)
				break;

			if (copy_to_user(argp, &get_p, sizeof(get_p)))
				rc = -EFAULT;
			break;
		}
		case BST_IOC_SOCK_CLOSE_SET: {
			struct bst_sock_comm_prop guide;

			if (copy_from_user(&guide, argp, sizeof(guide)))
				break;

			rc = set_tcp_sock_closed(&guide);
			break;
		}
		case BST_IOC_SOCK_STATE_GET: {
			struct bst_get_bastet_sock_state get_p;

			if (copy_from_user(&get_p, argp, sizeof(get_p)))
				break;

			rc = get_tcp_bastet_sock_state(&get_p);
			if (rc < 0)
				break;

			if (copy_to_user(argp, &get_p, sizeof(get_p)))
				rc = -EFAULT;
			break;
		}
		case BST_IOC_APPLY_LOCAL_PORT: {
			u16 local_port;

			rc = bind_local_ports(&local_port);
			if (rc < 0)
				break;

			if (copy_to_user(argp, &local_port, sizeof(local_port)))
				rc = -EFAULT;
			break;
		}
		case BST_IOC_RELEASE_LOCAL_PORT: {
			u16 local_port;

			if (copy_from_user(&local_port, argp, sizeof(local_port)))
				break;

			rc = unbind_local_ports(local_port);
			break;
		}
		case BST_IOC_SET_TRAFFIC_FLOW: {
			uint8_t *buf = NULL;
			int buf_len = 0;
			struct bst_traffic_flow_pkg flow_p;

			if (copy_from_user(&flow_p, argp, sizeof(struct bst_traffic_flow_pkg))) {
				break;
			}

			if (0 == flow_p.cnt) {
				bastet_wake_up_traffic_flow();
				rc = 0;
				break;
			}
			buf_len = flow_p.cnt * sizeof(struct bst_traffic_flow_prop);
			buf = (uint8_t *)kmalloc(buf_len, GFP_KERNEL);
			if (NULL == buf) {
				BASTET_LOGE("kmalloc failed");
				rc = -ENOMEM;
				break;
			}

			if (copy_from_user(buf, argp + sizeof(struct bst_traffic_flow_pkg), buf_len)) {
				BASTET_LOGE("pkg copy_from_user error");
				kfree(buf);
				break;
			}

			rc = adjust_traffic_flow_by_pkg(buf, flow_p.cnt);
			kfree(buf);
			break;
		}
		case BST_IOC_GET_TIMESTAMP_INFO: {
			struct bst_timestamp_info info;

			info.time_now = ((uint32_t)(jiffies));
			info.time_freq = HZ;

			rc = 0;
			if (copy_to_user(argp, &info, sizeof(info)))
				rc = -EFAULT;
			break;
		}
		case BST_IOC_SET_NET_DEV_NAME: {
			struct bst_net_dev_name info;

			if (copy_from_user(&info, argp, sizeof(info)))
				break;

			rc = set_current_net_device_name(info.iface);
			break;
		}
#ifdef CONFIG_HUAWEI_BASTET_COMM
		case BST_IOC_GET_MODEM_RAB_ID: {
			struct bst_modem_rab_id info;

			rc = get_modem_rab_id(&info);
			if (rc < 0)
				break;

			if (copy_to_user(argp, &info, sizeof(info)))
				rc = -EFAULT;
			break;
		}
#endif
		case BST_IOC_SOCK_RECONN_SET: {
			struct bst_get_sock_comm_prop get_prop;

			if (copy_from_user(&get_prop, argp, sizeof(get_prop)))
				break;
			rc = bastet_reconn_set(get_prop);
			break;
		}
		case BST_IOC_SOCK_RECONN_FAIL: {
			struct bst_sock_comm_prop comm_prop;

			if (copy_from_user(&comm_prop, argp, sizeof(comm_prop)))
				break;
			BASTET_LOGI("BST_IOC_SOCK_RECONN_FAIL");
			bastet_reconn_failed(comm_prop);
			rc = 0;
			break;
		}
		case BST_IOC_SET_RECONN_PROXYID: {
			struct reconn_id id;

			if (copy_from_user(&id, argp, sizeof(struct reconn_id)))
				break;
			BASTET_LOGI("fd=%d, pid=%d, proxy_id=0x%08X", id.guide.fd, id.guide.pid, id.proxy_id);
			rc = bastet_reconn_proxyid_set(id);
			break;
		}
		case BST_IOC_SYNC_PROP_START: {
			struct bst_set_sock_sync_prop set_p;

			if (copy_from_user(&set_p, argp, sizeof(set_p)))
				break;

			rc = bastet_sync_prop_start(&set_p);
			break;
		}
		case BST_IOC_SYNC_PROP_STOP: {
			struct bst_sock_comm_prop comm_prop;

			if (copy_from_user(&comm_prop, argp, sizeof(comm_prop)))
				break;

			rc = bastet_sync_prop_stop(&comm_prop);
			break;
		}
		case BST_IOC_PROXY_AVAILABLE: {
			int available = 0;

			if (copy_from_user(&available, argp, sizeof(int32_t)))
				break;
			atomic_set(&proxy, available);
			if (!is_proxy_available()) {
				// proxy is unavailable, release all uid list
				bastet_partner_clear();
			}
			BASTET_LOGI("proxy_available=%d", is_proxy_available());
			rc = 0;
			break;
		}
		case BST_IOC_BUF_AVAILABLE: {
			int available = 0;

			if (copy_from_user(&available, argp, sizeof(int32_t)))
				break;
			atomic_set(&buffer, available);
			BASTET_LOGI("buffer_available=%d", is_buffer_available());
			rc = 0;
			break;
		}
		case BST_IOC_PRIO_SEND_SUC: {
			clear_channel_occupied();
			BASTET_LOGI("channel_available=%d", is_channel_available());
			rc = 0;
			break;
		}
		case BST_IOC_SOCK_SYNC_PREPARE: {
			struct bst_set_sock_sync_delay sync_prop;

			if (copy_from_user(&sync_prop, argp, sizeof(sync_prop)))
				break;

			rc = prepare_bastet_sock(&sync_prop);
			break;
		}
		case BST_IOC_GET_FD_BY_ADDR: {
			struct addr_to_fd guide;

			if (copy_from_user(&guide, argp, sizeof(guide)))
				break;

			rc = get_fd_by_addr(&guide);
			if (rc < 0) {
				BASTET_LOGE("failed to get fd by address");
				break;
			}
			if (copy_to_user(argp, &guide, sizeof(guide)))
				rc = -EFAULT;
			break;
		}
		case BST_IOC_GET_CMDLINE: {
			struct get_cmdline cmdline;

			if (copy_from_user(&cmdline, argp, sizeof(cmdline)))
				break;

			rc = get_pid_cmdline(&cmdline);
			if (rc < 0) {
				BASTET_LOGE("failed to get pid cmdline");
				break;
			}
			if (copy_to_user(argp, &cmdline, sizeof(cmdline)))
				rc = -EFAULT;
			break;
		}
		case BST_IOC_SYNC_HOLD_TIME: {
			struct bst_set_sock_sync_delay hold_delay;

			if (copy_from_user(&hold_delay, argp, sizeof(hold_delay)))
				break;

			rc = set_sock_sync_hold_time(hold_delay);
			if (rc < 0) {
				BASTET_LOGE("failed to set sock sync hold time");
				break;
			}
			break;
		}
		case BST_IOC_NET_DEV_RESET: {
			int reset = 0;

			if (copy_from_user(&reset, argp, sizeof(int32_t)))
				break;
			atomic_set(&cp_reset, reset);
			BASTET_LOGI("cp_reset=%d", is_cp_reset());
			rc = 0;
			break;
		}
		case BST_IOC_UID_PROP_MONITOR: {
			struct app_monitor_prop prop;
			int32_t *tids = NULL;

			if (copy_from_user(&prop, argp, sizeof(struct app_monitor_prop))) {
				rc = -EFAULT;
				break;
			}
			BASTET_LOGI("BST_IOC_UID_PROP_MONITOR: uid=%d, cmd=%d, count=%d", prop.uid, prop.cmd, prop.tid_count);
			if (prop.tid_count > 0) {
				tids = (int32_t *) kmalloc(prop.tid_count * sizeof(int32_t), GFP_KERNEL);
				if (NULL == tids) {
					BASTET_LOGE("kmalloc failed");
					rc = -ENOMEM;
					break;
				}
				if (copy_from_user(tids, argp + sizeof(struct app_monitor_prop), prop.tid_count * sizeof(int32_t))) {
					rc = -EFAULT;
					kfree(tids);
					break;
				}
			}
			rc = bastet_partner_process_cmd(&prop, tids);
			if (tids != NULL) {
				kfree(tids);
			}
			break;
		}
		case BST_IOC_SET_HRTAPP_ACTIVITY: {
			int uid = 0;

			if (copy_from_user(&uid, argp, sizeof(int32_t)))
				break;
			hrt_uid = uid;
			BASTET_LOGI("hrt_uid=%d", hrt_uid);
			rc = 0;
			break;
		}
		case BST_IOC_FAST_GRAB_INFO:
			BASTET_LOGI( "BST_IOC_FAST_GRAB_INFO Entered" );
			BST_FG_IoCtrl( arg );
			rc = 0;
			break;
		case BST_IOC_SET_PROC_INFO: {
			struct set_process_info info;

			if (copy_from_user(&info, argp, sizeof(struct set_process_info))) {
				rc = -EFAULT;
				break;
			}
			rc = set_proc_info(&info);
			if (rc < 0) {
				BASTET_LOGE("failed to set proc info");
				break;
			}
			if (copy_to_user(argp, &info, sizeof(struct set_process_info))) {
				rc = -EFAULT;
			}
			break;
		}
		case BST_IOC_SET_SPECIAL_UID: {
			int uid;
			if (copy_from_user(&uid, argp, sizeof(int))) {
				BASTET_LOGE("failed to copy uid from user");
				rc = -EFAULT;
				break;
			}
			rc = set_special_uid(uid);
			if (rc < 0) {
				BASTET_LOGE("failed to set proc info");
				break;
			}
			break;
		}
		case BST_IOC_NF_CONTROL: {
			bool isRegister;
			BASTET_LOGI("BST_IOC_NF_CONTROL");
			if (copy_from_user(&isRegister, argp, sizeof(bool))) {
				BASTET_LOGE("failed to get uid by pid");
				rc = -EFAULT;
				break;
			}
			rc = set_netfilter(isRegister);
			if (rc < 0) {
				BASTET_LOGE("failed to set netfilter");
				break;
			}
			break;
		}
		default: {
			BASTET_LOGE("unknown ioctl: %d", cmd);
			break;
		}
	}

	return rc;
}

/* support of 32bit userspace on 64bit platforms */
#ifdef CONFIG_COMPAT
static long compat_bastet_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
{
	return bastet_ioctl(flip, cmd, (unsigned long) compat_ptr(arg));
}
#endif

static int bastet_open(struct inode *inode, struct file *filp)
{
	spin_lock_bh(&bastet_data.read_lock);

	if (bastet_dev_en) {
		BASTET_LOGE("bastet device has been opened");
		spin_unlock_bh(&bastet_data.read_lock);
		return -EPERM;
	}

	bastet_dev_en = true;

	spin_unlock_bh(&bastet_data.read_lock);
	BASTET_LOGI("success");

	return 0;
}

static int bastet_packet_read(char __user *buf, size_t count)
{
	struct data_packet *pkt = NULL;
	uint8_t *data = NULL;
	bool isfree = false;
	int len = 0;
	int size = 0;

	if (NULL == buf) {
		return -EINVAL;
	}

	spin_lock_bh(&bastet_data.read_lock);
	if (list_empty(&bastet_data.read_queue)) {
		spin_unlock_bh(&bastet_data.read_lock);
		return -EAGAIN;
	}

	pkt = list_first_entry(&bastet_data.read_queue, struct data_packet, list);
	len = sizeof(struct bst_device_ind) - sizeof(pkt->data.cons) + pkt->data.len;
	data = (uint8_t *)(&pkt->data) + sizeof(pkt->data.cons);

	if ((0 == pkt->data.cons) && (count > len)) {
		list_del(&pkt->list);
		size = len;
		isfree = true;
	} else if (((0 == pkt->data.cons) && (count <= len))
		|| ((pkt->data.cons != 0) && (pkt->data.cons + count <= len))) {
		size = count;
		isfree = false;
	} else {
		list_del(&pkt->list);
		size = len - pkt->data.cons;
		isfree = true;
	}

	spin_unlock_bh(&bastet_data.read_lock);
	if (copy_to_user(buf, data + pkt->data.cons, size)) {
		pkt->data.cons = 0;
		if (isfree) {
			kfree(pkt);
		}
		return -EFAULT;
	}
	pkt->data.cons += count;

	if (isfree) {
		kfree(pkt);
	}

	return size;
}

/*
 * blocked read, it will be waiting here until net device state is change.
 *
 * standard arg is "const char __user *buf".
 */
/*lint -e666*/
static ssize_t bastet_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	int ret = 0;
	spin_lock_bh(&bastet_data.read_lock);
	while(list_empty(&bastet_data.read_queue)) {
		spin_unlock_bh(&bastet_data.read_lock);
		ret = wait_event_interruptible(bastet_data.read_wait, !list_empty(&bastet_data.read_queue));
		if (ret) {
			return ret;
		}
		spin_lock_bh(&bastet_data.read_lock);
	}
	spin_unlock_bh(&bastet_data.read_lock);

	return bastet_packet_read(buf, count);
}
/*lint +e666*/

#ifdef CONFIG_HUAWEI_BASTET_COMM
static ssize_t bastet_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	u8 msg[BST_MAX_WRITE_PAYLOAD];

	if (count > BST_MAX_WRITE_PAYLOAD) {
		BASTET_LOGE("write length over BST_MAX_WRITE_PAYLOAD!");
		return -EINVAL;
	}

	if (copy_from_user(msg, buf, count)) {
		BASTET_LOGE("copy_from_user error");
		return -EFAULT;
	}
	bastet_comm_write(msg, count);

	return count;
}
#endif

static unsigned int bastet_poll(struct file *file, poll_table *wait)
{
	unsigned int mask = 0;

	poll_wait(file, &bastet_data.read_wait, wait);
	mask = !list_empty(&bastet_data.read_queue) ? (POLLIN | POLLRDNORM) : 0;

	return mask;
}

static int bastet_release(struct inode *inode, struct file *filp)
{
	struct list_head *p, *n;
	struct data_packet *pkt = NULL;
	
	spin_lock_bh(&bastet_data.read_lock);

	if (list_empty(&bastet_data.read_queue)) {
		goto out_release;
	}

	list_for_each_safe(p, n, &bastet_data.read_queue) {
		pkt = list_entry(p, struct data_packet, list);
		list_del(&pkt->list);
		kfree(pkt);
	}

out_release:
	bastet_dev_en = false;
	spin_unlock_bh(&bastet_data.read_lock);
	bastet_partner_release();
	BASTET_LOGI("success");

	return 0;
}

static const struct file_operations bastet_dev_fops = {
	.owner = THIS_MODULE,
	.open = bastet_open,
	.unlocked_ioctl = bastet_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = compat_bastet_ioctl,
#endif
	.read = bastet_read,
#ifdef CONFIG_HUAWEI_BASTET_COMM
	.write = bastet_write,
#endif
	.poll = bastet_poll,
	.release = bastet_release,
};

static void bastet_data_init(void)
{
	spin_lock_init(&bastet_data.read_lock);
	INIT_LIST_HEAD(&bastet_data.read_queue);
	init_waitqueue_head(&bastet_data.read_wait);
}

static int bastet_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct device* dev = NULL;

	bastet_data_init();
	bastet_utils_init();
	bastet_traffic_flow_init();
#ifdef CONFIG_HUAWEI_BASTET_COMM
	bastet_comm_init();
#endif
	bastet_reconn_init();
	bastet_partner_init();
	BST_FG_Init();
	bastet_filter_init();
	/* register bastet major and minor number */
	ret = alloc_chrdev_region(&bastet_dev, BST_FIRST_MINOR, BST_DEVICES_NUMBER, BASTET_NAME);
	if (ret) {
		BASTET_LOGE("alloc_chrdev_region error");
		goto fail_region;
	}

	cdev_init(&bastet_cdev, &bastet_dev_fops);
	bastet_cdev.owner = THIS_MODULE;

	ret = cdev_add(&bastet_cdev, bastet_dev, BST_DEVICES_NUMBER);
	if (ret) {
		BASTET_LOGE("cdev_add error");
		goto fail_cdev_add;
	}

	bastet_class = class_create(THIS_MODULE, BASTET_NAME);
	if (IS_ERR(bastet_class)) {
		BASTET_LOGE("class_create error");
		goto fail_class_create;
	}

	dev = device_create(bastet_class, NULL, bastet_dev, NULL, BASTET_NAME);
	if (IS_ERR(dev)) {
		BASTET_LOGE("device_create error");
		goto fail_device_create;
	}

	return 0;

fail_device_create:
	class_destroy(bastet_class);
fail_class_create:
	cdev_del(&bastet_cdev);
fail_cdev_add:
	unregister_chrdev_region(bastet_dev, BST_DEVICES_NUMBER);
fail_region:
	bastet_partner_release();
	return ret;
}

static int bastet_remove(struct platform_device *pdev)
{
	bastet_partner_release();
	if (NULL != bastet_class) {
		device_destroy(bastet_class, bastet_dev);
		class_destroy(bastet_class);
	}
	cdev_del(&bastet_cdev);
	unregister_chrdev_region(bastet_dev, BST_DEVICES_NUMBER);
	bastet_utils_exit();

	return 0;
}

#ifdef CONFIG_OF
static struct of_device_id of_bastet_match_tbl[] = {
	{
		.compatible = "huawei,bastet",
	},
	{ /* end */ }
};

MODULE_DEVICE_TABLE(of, of_bastet_match_tbl);
#endif

static struct platform_driver bastet_driver = {
	.probe	= bastet_probe,
	.remove	= bastet_remove,
	.driver = {
		.name	= "bastet",
		.owner	= THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = of_match_ptr(of_bastet_match_tbl),
#endif
	},
};

module_platform_driver(bastet_driver);

MODULE_AUTHOR("zhuxiaolong@huawei.com");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Bastet driver");
