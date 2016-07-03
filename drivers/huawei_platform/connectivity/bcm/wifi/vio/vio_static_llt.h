
#ifndef _VIO_STATIC_LLT_H
#define _VIO_STATIC_LLT_H

#ifdef __cplusplus
extern "C" {
#endif

struct LLT_TEST {
	int (*vio_dev_ioctl)(struct file *filp, int cmd, int arg);
	int (*vio_dev_init)(void);
	void (*vio_dev_exit)(void);
};

#ifdef __cplusplus
}
#endif
#endif
