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
#define IOM3_RECOVERY_FAILED	(IOM3_RECOVERY_DOING + 1)
#endif

//receive data from mcu,you should copy the buf each time.
//extern size_t (*api_inputhub_mcu_recv)(const char *buf,unsigned long length/*buf length*/);
extern int (*api_inputhub_mcu_recv)(const char *buf,unsigned int length/*buf length*/);
extern int (*api_mculog_process)(const char * buf,unsigned int length/*buf length*/);

int getSensorMcuMode( void );

//connect to mcu,register callback receive function.
int inputhub_mcu_connect( void );
int inputhub_mcu_disconnect( void );

//send data to mcu, impliment multithread safe.
int inputhub_mcu_send(const char *buf, unsigned int length/*buf length*/);

int iom3_need_recovery(void);
int is_sensorhub_disabled(void);
void restart_iom3(void);
#endif /* __LINUX_INPUTHUB_CMU_H__ */
