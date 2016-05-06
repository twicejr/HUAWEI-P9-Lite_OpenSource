/*
 *  drivers/misc/inputhub/inputhub_mcu.h
 *  Sensor Hub Channel Bridge
 *
 *  Copyright (C) 2013 Huawei, Inc.
 *  Author: huangjisong <inputhub@huawei.com>
 *
 */
#ifndef __LINUX_INPUTHUB_CMU_H__
#define __LINUX_INPUTHUB_CMU_H__
#include <linux/types.h>
#include  <global_ddr_map.h>

#define STARTUP_IOM3_CMD		(0x00070001)
#define RELOAD_IOM3_CMD		(0x0007030D)

//for iom3 recovery debug used
#define CLKEN0_OFFSET    0x010
#define CLKSTAT0_OFFSET  0x18
#define CLKEN1_OFFSET        0x090
#define RSTEN0_OFFSET	   0x020
#define RSTDIS0_OFFSET  0x024
#define RSTSTAT0_OFFSET    0x028

#ifdef CONFIG_IOM3_RECOVERY
#define IOM3_RECOVERY_UNINIT	(0)
#define IOM3_RECOVERY_IDLE		(IOM3_RECOVERY_UNINIT + 1)
#define IOM3_RECOVERY_START	(IOM3_RECOVERY_IDLE + 1)
#define IOM3_RECOVERY_MINISYS	(IOM3_RECOVERY_START + 1)
#define IOM3_RECOVERY_DOING	(IOM3_RECOVERY_MINISYS + 1)
#define IOM3_RECOVERY_3RD_DOING	(IOM3_RECOVERY_DOING + 1)
#define IOM3_RECOVERY_FAILED	(IOM3_RECOVERY_3RD_DOING + 1)
#endif

#define IOMCU_CONFIG_SIZE  0x1000
#define IOMCU_CONFIG_START  (HISI_RESERVED_SENSORHUB_SHARE_MEM_PHYMEM_BASE + 0x80000 - IOMCU_CONFIG_SIZE)

#define WARN_LEVEL 2
#define INFO_LEVEL 3

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
    float gyro_offset[3];
};

//receive data from mcu,you should copy the buf each time.
//extern size_t (*api_inputhub_mcu_recv)(const char *buf,unsigned long length/*buf length*/);
extern int (*api_inputhub_mcu_recv)(const char *buf,unsigned int length/*buf length*/);
extern int (*api_mculog_process)(const char * buf,unsigned int length/*buf length*/);

int getSensorMcuMode( void );
int get_iomcu_power_state(void);
//connect to mcu,register callback receive function.
int inputhub_mcu_connect( void );
int inputhub_mcu_disconnect( void );

//send data to mcu, impliment multithread safe.
int inputhub_mcu_send(const char *buf, unsigned int length/*buf length*/);

int iom3_need_recovery(int modid);
int is_sensorhub_disabled(void);
void restart_iom3(void);
#endif /* __LINUX_INPUTHUB_CMU_H__ */
