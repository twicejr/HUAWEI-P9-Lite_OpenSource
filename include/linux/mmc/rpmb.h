
#ifndef __RPMB_H__
#define __RPMB_H__

#include <linux/mmc/ioctl.h>

enum func_id {
	RPMB_FUNC_ID_RESERVED,
	RPMB_FUNC_ID_SE,
	RPMB_FUNC_ID_SECURE_OS,
	RPMB_FUNC_ID_MAX,
};

struct mmc_blk_ioc_data {
	struct mmc_ioc_cmd ic;
	unsigned char *buf;
	u64 buf_bytes;
};

struct mmc_blk_ioc_rpmb_data {
	struct mmc_blk_ioc_data data[MMC_IOC_MAX_RPMB_CMD];
};

extern struct mutex rpmb_counter_lock;
extern void hisi_rpmb_active(void);
#endif /* __RPMB_H__ */
