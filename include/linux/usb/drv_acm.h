/*************************************************************************
*   版权所有(C) 1987-2011, 深圳华为技术有限公司.
*
*   文 件 名 :  drv_acm.h
*
*   作    者 :  fangchangdong
*
*   描    述 :  usb acm模块对外接口
*
*   修改记录 :  2013年2月2日  v1.00  fangchangdong创建
*************************************************************************/

#ifndef __DRV_ACM_H__
#define __DRV_ACM_H__

/* IOCTL CMD 定义 */
#define ACM_IOCTL_SET_WRITE_CB      0x7F001000
#define ACM_IOCTL_SET_READ_CB       0x7F001001
#define ACM_IOCTL_SET_EVT_CB        0x7F001002
#define ACM_IOCTL_SET_FREE_CB       0x7F001003

#define ACM_IOCTL_WRITE_ASYNC       0x7F001010
#define ACM_IOCTL_GET_RD_BUFF       0x7F001011
#define ACM_IOCTL_RETURN_BUFF       0x7F001012
#define ACM_IOCTL_RELLOC_READ_BUFF  0x7F001013

#define ACM_IOCTL_WRITE_DO_COPY     0x7F001021

/* Modem 控制命令码 */
#define ACM_MODEM_IOCTL_SET_MSC_READ_CB 0x7F001030
#define ACM_MODEM_IOCTL_MSC_WRITE_CMD   0x7F001031
#define ACM_MODEM_IOCTL_SET_REL_IND_CB  0x7F001032

/* MODEM SIG define */
#define SIGNALNOCH		0
#define SIGNALCH		1
#define RECV_ENABLE		1
#define RECV_DISABLE		0
#define SEND_ENABLE		1
#define SEND_DISABLE		0
#define HIGHLEVEL		1
#define LOWLEVEL		0

#define MODEM_CTRL_RI		(1 << 3)
#define MODEM_CTRL_DSR		(1 << 1)
#define MODEM_CTRL_DCD		(1 << 0)

/* 异步数据收发结构 */
typedef struct tagACM_WR_ASYNC_INFO {
	char *pVirAddr;
	char *pPhyAddr;
	unsigned int u32Size;
	void *pDrvPriv;
} ACM_WR_ASYNC_INFO;

/* ACM设备事件类型 */
typedef enum tagACM_EVT_E {
	ACM_EVT_DEV_SUSPEND = 0,        /* 设备不可以进行读写(主要用于事件回调函数的状态) */
	ACM_EVT_DEV_READY = 1,          /* 设备可以进行读写(主要用于事件回调函数的状态) */
	ACM_EVT_DEV_BOTTOM
} ACM_EVT_E;

typedef enum tagACM_IOCTL_FLOW_CONTROL_E {
	ACM_IOCTL_FLOW_CONTROL_DISABLE = 0,	/* resume receiving data from ACM port */
	ACM_IOCTL_FLOW_CONTROL_ENABLE		/* stop receiving data from ACM port */
} ACM_IOCTL_FLOW_CONTROL_E;

/* 读buffer信息 */
typedef struct tagACM_READ_BUFF_INFO {
	unsigned int u32BuffSize;
	unsigned int u32BuffNum;
} ACM_READ_BUFF_INFO;

typedef struct tagMODEM_MSC_STRU {
	u32 OP_Dtr:1;		/*DTR CHANGE FLAG*/
	u32 OP_Dsr:1;		/*DSR CHANGE FLAG*/
	u32 OP_Cts:1;		/*CTSCHANGE FLAG*/
	u32 OP_Rts:1;		/*RTS CHANGE FLAG*/
	u32 OP_Ri:1;		/*RI CHANGE FLAG*/
	u32 OP_Dcd:1;		/*DCD CHANGE FLAG*/
	u32 OP_Fc:1;		/*FC CHANGE FLAG*/
	u32 OP_Brk:1;		/*BRK CHANGE FLAG*/
	u32 OP_Spare:24;	/*reserve*/
	u8   ucDtr;		/*DTR  VALUE*/
	u8   ucDsr;		/*DSR  VALUE*/
	u8   ucCts;		/*DTS VALUE*/
	u8   ucRts;		/*RTS  VALUE*/
	u8   ucRi;		/*RI VALUE*/
	u8   ucDcd;		/*DCD  VALUE*/
	u8   ucFc;		/*FC  VALUE*/
	u8   ucBrk;		/*BRK  VALUE*/
	u8   ucBrkLen;		/*BRKLEN VALUE*/
} MODEM_MSC_STRU, *PMODEM_MSC_STRU;

typedef void (*ACM_WRITE_DONE_CB_T)(char *pVirAddr, char *pPhyAddr, int size);
typedef void (*ACM_READ_DONE_CB_T)(void);
typedef void (*ACM_EVENT_CB_T)(ACM_EVT_E evt);
typedef void (*ACM_FREE_CB_T)(char *buf);
typedef void (*ACM_MODEM_MSC_READ_CB_T)(MODEM_MSC_STRU *pModemMsc);
typedef void (*ACM_MODEM_REL_IND_CB_T)(unsigned int bEnable);


#endif
