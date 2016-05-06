

#ifndef _DSM_CORE_H
#define _DSM_CORE_H
#include <dsm/dsm_pub.h>
#include <linux/mutex.h>
#include <linux/ioctl.h>
#include <linux/err.h>

#define CLIENT_SIZE			(64)
#define UINT_BUF_MAX        	(12)

#define CBUFF_OCCUPY_BIT	(0)
#define CBUFF_READY_BIT		(1)

#define EXTERN_DSM_CLIENT_MAX  (20)

#define DSM_IOCTL_GET_CLIENT_COUNT	_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF0, CLIENT_NAME_LEN)
#define DSM_IOCTL_BIND					_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF1, CLIENT_NAME_LEN)
#define DSM_IOCTL_POLL_CLIENT_STATE	_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF2, CLIENT_NAME_LEN)
#define DSM_IOCTL_FORCE_DUMP			_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF3, CLIENT_NAME_LEN)
#define DSM_IOCTL_GET_CLIENT_ERROR	_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF4, CLIENT_NAME_LEN)
#define DSM_IOCTL_GET_DEVICE_NAME	_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF5, CLIENT_NAME_LEN)
#define DSM_IOCTL_GET_MODULE_NAME	_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF6, CLIENT_NAME_LEN)
#define DSM_IOCTL_GET_IC_NAME		_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF7, CLIENT_NAME_LEN)
#define DSM_IOCTL_REGISTER_EXTERN_CLIENT _IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF8, CLIENT_NAME_LEN)
#ifdef CONFIG_HUAWEI_SDCARD_VOLD
#define SDCARD_ERR_LEN   	5
#endif
enum {
	DSM_CLIENT_NOTIFY_BIT = 0,
	DSM_CLIENT_VAILD_BIT = 31,
	DSM_CLIENT_NOTIFY = 1<<DSM_CLIENT_NOTIFY_BIT,
	DSM_CLIENT_VAILD = 1<<DSM_CLIENT_VAILD_BIT,
};

enum {
	DSM_SERVER_UNINIT = 0,
	DSM_SERVER_INITED = 1,
};

struct dsm_server{
	unsigned long client_flag[CLIENT_SIZE];
	struct dsm_client *client_list[CLIENT_SIZE];
	int client_count;
	int server_state;
	struct workqueue_struct *dsm_wq;
	struct mutex mtx_lock;
};

#endif
