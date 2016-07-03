

#ifndef _UAPI_DFU_H
#define _UAPI_DFU_H

#include <linux/types.h>

struct dfu_status {
	__u8  bStatus;
	__u8  bwPollTimeout0;
	__u8  bwPollTimeout1;
	__u8  bwPollTimeout2;
	__u8  bState;
	__u8  iString;
} __attribute__ ((packed));

#define DFU_MAX_WRITE_SIZE	0x100000
#define DFU_MAX_READ_SIZE	0x100000

/* ioctrl interface */
#define DFUIOCDETACH			_IO('D', 0x1)
#define DFUIOCDOWNLOAD(len)		_IOC(_IOC_WRITE|_IOC_READ, 'D', 0x2, len)
#define DFUIOCGETSTATUS			_IOR('D', 0x3, struct dfu_status)
#define DFUIOCABORT			_IO('D', 0x4)
#define DFUIOCFINISHDNLOAD		_IO('D', 0x5)

#endif /* _UAPI_DFU_H */
