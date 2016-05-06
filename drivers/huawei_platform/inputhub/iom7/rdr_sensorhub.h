#ifndef __LINUX_INPUTHUB_RDR_H__
#define __LINUX_INPUTHUB_RDR_H__
#include <linux/hisi/rdr_pub.h>

#define WD_INT  144

#define SENSORHUB_MODID     HISI_BB_MOD_IOM_START
#define SENSORHUB_USER_MODID     (HISI_BB_MOD_IOM_START + 1)
#define SENSORHUB_MODID_END HISI_BB_MOD_IOM_END

//#define SCIOMCUCTRL  0x598

#define REG_UNLOCK_KEY  0x1ACCE551
#define WDOGCTRL		0x08
#define WDOGINTCLR	0x0C
#define WDOGLOCK	0xC00

int rdr_sensorhub_init(void);
int write_ramdump_info_to_sharemem(void);

#endif /*__LINUX_INPUTHUB_RDR_H__*/
