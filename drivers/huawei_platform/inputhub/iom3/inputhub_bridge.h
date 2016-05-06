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
#endif /* __LINUX_INPUTHUB_CMU_H__ */
