/*
 * hifi msg define.
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#ifndef _AUDIO_HIFI_H
#define _AUDIO_HIFI_H

#include <linux/types.h>


typedef enum
{
	HIFI_CHN_SYNC_CMD = 0,
	HIFI_CHN_READNOTICE_CMD,
	HIFI_CHN_INVAILD_CMD
} HIFI_CHN_CMD_TYPE;

typedef struct HIFI_CHN_CMD_STRUCT
{
	HIFI_CHN_CMD_TYPE cmd_type;
	unsigned int		   sn;
} HIFI_CHN_CMD;

/*
	入参，透传给HIFI的参数
	出参，HIFI返回的，透传给AP的参数
*/
struct misc_io_async_param {
	unsigned int			para_in_l;		/*入参buffer*/
	unsigned int			para_in_h;		/*入参buffer*/
	unsigned int			para_size_in;	/*入参buffer长度*/
};


/* misc_io_sync_cmd */
struct misc_io_sync_param {
	unsigned int			para_in_l;			 /*入参buffer*/
	unsigned int			para_in_h;			 /*入参buffer*/
	unsigned int			para_size_in;		/*入参buffer长度*/

	unsigned int			para_out_l; 		  /*出参buffer*/
	unsigned int			para_out_h; 		  /*出参buffer*/
	unsigned int			para_size_out;		/*出参buffer长度*/
};

/* misc_io_senddata_cmd */
struct misc_io_senddata_async_param {
	unsigned int			para_in_l;			 /*入参buffer*/
	unsigned int			para_in_h;			 /*入参buffer*/
	unsigned int			para_size_in;		/*入参buffer长度*/

	unsigned int			data_src_l; 		  /*大数据源地址*/
	unsigned int			data_src_h; 		  /*大数据源地址*/
	unsigned int			data_src_size;		/*大数据源长度*/
};

struct misc_io_senddata_sync_param {
	unsigned int			para_in_l;			/*入参buffer*/
	unsigned int			para_in_h;			/*入参buffer*/
	unsigned int			para_size_in;		/*入参buffer长度*/

	unsigned int			src_l;				/*数据源地址*/
	unsigned int			src_h;				/*数据源地址*/
	unsigned int			src_size;			/*数据源长度*/

	unsigned int			dst_l;				/*地址*/
	unsigned int			dst_h;				/*地址*/
	unsigned int			dst_size;			/*长度*/

	unsigned int			para_out_l; 		/*出参buffer*/
	unsigned int			para_out_h; 		/*出参buffer*/
	unsigned int			para_size_out;		/*出参buffer长度*/
};

struct misc_io_get_phys_param {
	unsigned int		   flag;			   /**/
	unsigned int		   phys_addr_l; 		 /*获取的物理地址*/
	unsigned int		   phys_addr_h; 		 /*获取的物理地址*/
};

struct misc_io_dump_buf_param {
	unsigned int			user_buf_l; 		/*用户空间分配的内存地址*/
	unsigned int			user_buf_h; 		/*用户空间分配的内存地址*/
	unsigned int			clear;				/*clear current log buf*/
	unsigned int			buf_size;			/*用户空间分配的内存长度*/
};

//下面是AP发给HiFi Misc设备的ioctl命令，需要HiFi Misc设备进行响应
#define HIFI_MISC_IOCTL_ASYNCMSG		_IOWR('A', 0x70, struct misc_io_async_param)		  //AP向HiFi传递异步消息
#define HIFI_MISC_IOCTL_SYNCMSG 		_IOW('A', 0x71, struct misc_io_sync_param)			  //AP向HiFi传递同步消息
#define HIFI_MISC_IOCTL_SENDDATA_SYNC	_IOW('A', 0x72, struct misc_io_senddata_sync_param)    //AP向HiFi同步传递数据
#define HIFI_MISC_IOCTL_GET_PHYS		_IOWR('A', 0x73, struct misc_io_get_phys_param) 	   //AP获取物理地址
#define HIFI_MISC_IOCTL_TEST			_IOWR('A', 0x74, struct misc_io_senddata_sync_param)   //AP测试消息
#define HIFI_MISC_IOCTL_WRITE_PARAMS	_IOWR('A', 0x75, struct misc_io_sync_param) 		   //写算法参数到HIFI
#define HIFI_MISC_IOCTL_DUMP_HIFI		_IOWR('A', 0x76, struct misc_io_dump_buf_param) 	   //读取HIFI在DDR上的数据并传递至用户空间
#define HIFI_MISC_IOCTL_DUMP_CODEC		_IOWR('A', 0x77, struct misc_io_dump_buf_param) 	   //读取CODEC寄存器并传递至用户空间
#define HIFI_MISC_IOCTL_WAKEUP_THREAD	_IOW('A',  0x78, unsigned int) 	   //唤醒read线程,正常退出
#define HIFI_MISC_IOCTL_DISPLAY_MSG		_IOWR('A', 0x79, struct misc_io_dump_buf_param) 	   //读取HIFI在DDR上的数据并传递至用户空间

#define HIFI_MISC_IOCTL_GET_VOICE_BSD_PARAM	_IOWR('A',  0x7c, unsigned int)    //获取Voice BSD参数
#define INT_TO_ADDR(low,high) (void*) (unsigned long)((unsigned long long)(low) | ((unsigned long long)(high)<<32))
#define GET_LOW32(x) (unsigned int)(((unsigned long long)(unsigned long)(x))&0xffffffffULL)
#define GET_HIG32(x) (unsigned int)((((unsigned long long)(unsigned long)(x))>>32)&0xffffffffULL)

#endif // _AUDIO_HIFI_H

