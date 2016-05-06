#include<linux/kernel.h>
#include<linux/module.h>
#include<huawei_platform/log/log_exception.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/aio.h>
#include<linux/types.h>

#include <huawei_platform/log/hw_log.h>
#define HWLOG_TAG	log_exception
HWLOG_REGIST();


/**
*  tag: the tag of this command
*  msg: concrete command string to write to /dev/log/exception
*  return: on success return the bytes writed successfully, on error return <0
*
*/
int log_to_exception(char* tag, char* msg)
{
	mm_segment_t oldfs;
	struct file *filp;
	unsigned char prio_err = 6;	//ANDROID_ERROR
	int ret = 0;
	struct iovec vec[3];

	if (NULL == tag || NULL == msg) {
		hwlog_err("%s: arguments invalidate\n", __func__);
		return -EINVAL;
	}

	hwlog_info("%s: exception tag '%s' msg '%s'", __func__, tag, msg);

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	filp = filp_open(LOG_EXCEPTION_FS, O_RDWR, 0);

	if (!filp || IS_ERR(filp)) {
		hwlog_err("%s: access '%s' fail %p", __func__, LOG_EXCEPTION_FS, filp);
		set_fs(oldfs);
		return -ENODEV;
	}

	vec[0].iov_base = &prio_err;
	vec[0].iov_len = 1;
	vec[1].iov_base = tag;
	vec[1].iov_len = strlen(tag)+1;
	vec[2].iov_base = msg;
	vec[2].iov_len = strlen(msg)+1;

	ret = vfs_writev(filp, &vec[0], 3, &filp->f_pos);
	if (ret < 0) {
		hwlog_err("%s: write '%s' fail %d\n", __func__, LOG_EXCEPTION_FS, ret);
		filp_close(filp, NULL);
		set_fs(oldfs);
		return -EIO;
	}

	filp_close(filp, NULL);
	set_fs(oldfs);

	return ret;
}

EXPORT_SYMBOL(log_to_exception);

