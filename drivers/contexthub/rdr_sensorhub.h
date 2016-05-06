#ifndef __LINUX_INPUTHUB_RDR_H__
#define __LINUX_INPUTHUB_RDR_H__
#include <linux/hisi/rdr_pub.h>

#define WD_INT  144

#define SENSORHUB_MODID HISI_BB_MOD_IOM_START
#define SENSORHUB_MODID_END HISI_BB_MOD_IOM_END

#define SCIOMCUCTRL  0x598

#define REG_UNLOCK_KEY  0x1ACCE551
#define WDOGCTRL		0x08
#define WDOGINTCLR	0x0C
#define WDOGLOCK	0xC00

#define HISI_RESERVED_SENSORHUB_SHARE_MEM_PHYMEM_BASE    0x34A80000
#define IOMCU_CONFIG_SIZE  0x1000
#define IOMCU_CONFIG_START  (HISI_RESERVED_SENSORHUB_SHARE_MEM_PHYMEM_BASE + 0x80000 - IOMCU_CONFIG_SIZE)

typedef struct{
    u32 mutex;
    u16 index;
    u16 pingpang;
    u32 buff;
    u32 ddr_log_buff_cnt;
    u32 ddr_log_buff_index;
    u32 ddr_log_buff_last_update_index;
} log_buff_t;

typedef struct WRONG_WAKEUP_MSG{
    u32 flag;
    u64 time;
    u32 irq0;
    u32 irq1;
    u32 recvfromapmsg[4];
    u32 recvfromlpmsg[4];
    u32 sendtoapmsg[4];
    u32 sendtolpmsg[4];
    u32 recvfromapmsgmode;
    u32 recvfromlpmsgmode;
    u32 sendtoapmsgmode;
    u32 sendtolpmsgmode;
}wrong_wakeup_msg_t;

struct CONFIG_ON_DDR
{
    u64 dumpaddr64;
    u32 dumpsize;
    log_buff_t LogBuffCBBackup;
    wrong_wakeup_msg_t WrongWakeupMsg;
    int LABCConfig[4];
    u32 log_level;
};


int rdr_sensorhub_init(void);
int write_ramdump_info_to_sharemem(void);

#endif /*__LINUX_INPUTHUB_RDR_H__*/
