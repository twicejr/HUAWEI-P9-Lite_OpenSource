

#ifndef __MDRV_ACORE_UDI_H__
#define __MDRV_ACORE_UDI_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_icc.h"
#include "mdrv_udi_common.h"

#define UDI_BUILD_DEV_ID(dev, type) ((dev << 8) | (type & 0x00ff))

typedef int UDI_HANDLE;

typedef enum tagUDI_DEVICE_MAIN_ID_E
{
    UDI_DEV_USB_ACM = 0,
    UDI_DEV_USB_NCM,
    UDI_DEV_ICC,
    UDI_DEV_UART,
    UDI_DEV_HSUART,
    UDI_DEV_MAX
}UDI_DEVICE_MAIN_ID_E;


typedef enum tagUDI_ACM_DEV_TYPE_E
{
    UDI_USB_ACM_CTRL,
    UDI_USB_ACM_AT,
    UDI_USB_ACM_SHELL,
    UDI_USB_ACM_LTE_DIAG,
    UDI_USB_ACM_OM,
    UDI_USB_ACM_MODEM,
    UDI_USB_ACM_GPS,
    UDI_USB_ACM_3G_GPS,
    UDI_USB_ACM_3G_PCVOICE,
    UDI_USB_ACM_PCVOICE,
    UDI_USB_ACM_SKYTONE,
    UDI_USB_HSIC_ACM0,
    UDI_USB_HSIC_ACM1,
    UDI_USB_HSIC_ACM2,
    UDI_USB_HSIC_ACM3,
    UDI_USB_HSIC_ACM4,
    UDI_USB_HSIC_ACM5,
    UDI_USB_HSIC_ACM6,
    UDI_USB_HSIC_ACM7,
    UDI_USB_HSIC_ACM8,
    UDI_USB_HSIC_ACM9,
    UDI_USB_HSIC_ACM10,
    UDI_USB_HSIC_ACM11,
    UDI_USB_HSIC_ACM12,
    UDI_USB_HSIC_ACM13,
    UDI_USB_HSIC_ACM14,
    UDI_USB_HSIC_MODEM0,
    UDI_USB_ACM_MAX
}UDI_ACM_DEV_TYPE_E;

typedef enum tagUDI_NCM_DEV_TYPE_E
{
    UDI_USB_NCM_NDIS,
    UDI_USB_NCM_CTRL,
    UDI_USB_NCM_NDIS1,
    UDI_USB_NCM_CTRL1,
	UDI_USB_NCM_NDIS2,
	UDI_USB_NCM_CTRL2,
	UDI_USB_NCM_NDIS3,
	UDI_USB_NCM_CTRL3,
    UDI_USB_NCM_BOTTOM,            /* 用于MBB多网卡场景 */
    UDI_USB_HSIC_NCM0,
    UDI_USB_HSIC_NCM1,
    UDI_USB_HSIC_NCM2,

    UDI_USB_NCM_MAX                /* 必须在最后, 用于边界值 */
}UDI_NCM_DEV_TYPE_E;


/* 架构整改,下列宏定义将被删除，禁止新增代码使用下列宏 */
typedef enum tagUDI_ICC_DEV_TYPE
{
        UDI_ICC_GUOM0 = MDRV_ICC_GUOM0,
        UDI_ICC_GUOM1 = MDRV_ICC_GUOM1,
        UDI_ICC_GUOM2 = MDRV_ICC_GUOM2,
        UDI_ICC_GUOM3 = MDRV_ICC_GUOM3,
        UDI_ICC_GUOM4 = MDRV_ICC_GUOM4,
        UDI_ICC_GUOM5 = MDRV_ICC_GUOM5,
        UDI_ICC_GUOM6 = MDRV_ICC_GUOM6,
        UDI_ICC_GUOM7 = MDRV_ICC_GUOM7,

        UDI_ICC_MAX
}UDI_ICC_DEV_TYPE_E;

/* 架构整改,上面宏定义将被删除，禁止新增代码使用上面宏 */


typedef enum tagUDI_DEVICE_ID_E
{
    /* USB ACM */
    UDI_ACM_CTRL_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_CTRL),
    UDI_ACM_AT_ID =    UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_AT),
    UDI_ACM_SHELL_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_SHELL),
    UDI_ACM_LTE_DIAG_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_LTE_DIAG),
    UDI_ACM_OM_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_OM),
    UDI_ACM_MODEM_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_MODEM),
    UDI_ACM_GPS_ID      = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_GPS),     /*HISO*/
    UDI_ACM_3G_GPS_ID   = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_GPS),  /*ashell*/
    UDI_ACM_3G_PCVOICE_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_PCVOICE),
    UDI_ACM_PCVOICE_ID    = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_PCVOICE),
    UDI_ACM_SKYTONE_ID  = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_SKYTONE),
    UDI_ACM_HSIC_ACM0_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM0),
    UDI_ACM_HSIC_ACM1_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM1),
    UDI_ACM_HSIC_ACM2_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM2),
    UDI_ACM_HSIC_ACM3_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM3),
    UDI_ACM_HSIC_ACM4_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM4),
    UDI_ACM_HSIC_ACM5_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM5),
    UDI_ACM_HSIC_ACM6_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM6),
    UDI_ACM_HSIC_ACM7_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM7),
    UDI_ACM_HSIC_ACM8_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM8),
    UDI_ACM_HSIC_ACM9_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM9),
    UDI_ACM_HSIC_ACM10_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM10),
    UDI_ACM_HSIC_ACM11_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM11),
    UDI_ACM_HSIC_ACM12_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM12),
    UDI_ACM_HSIC_ACM13_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM13),
    UDI_ACM_HSIC_ACM14_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM14),
    UDI_ACM_HSIC_MODEM0_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_MODEM0),
    /* USB NCM */
    UDI_NCM_NDIS_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_NDIS),
    UDI_NCM_CTRL_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_CTRL),
    UDI_NCM_HSIC_NCM0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM0),
    UDI_NCM_HSIC_NCM1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM1),
    UDI_NCM_HSIC_NCM2_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM2),

    /* UART */
    UDI_UART_0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_UART, 0),
    UDI_UART_1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_UART, 1),

    /* HSUART */
    UDI_HSUART_0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_HSUART, 0),
    UDI_HSUART_1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_HSUART, 1),

    /* ICC */
    UDI_ICC_IFC_ID  =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 0),
    UDI_ICC_IPM_ID  =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 1),
    UDI_ICC_LMSP_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 2),

    UDI_ICC_GUOM0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM0),
    UDI_ICC_GUOM1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM1),
    UDI_ICC_GUOM2_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM2),
    UDI_ICC_GUOM3_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM3),
    UDI_ICC_GUOM4_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM4),
    UDI_ICC_GUOM5_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM5),
    UDI_ICC_GUOM6_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM6),/*z00179562_check,?V9????*/
    UDI_ICC_GUOM7_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM7),/*y00145322_check,?V9????*/

    /* MUST BE LAST */
    UDI_INVAL_DEV_ID = 0xFFFF
} UDI_DEVICE_ID_E;


typedef struct tagUDI_OPEN_PARAM_S
{
    UDI_DEVICE_ID_E devid;                           /* 设备ID */
    void   *pPrivate;                            /* 模块特有的数据 */
} UDI_OPEN_PARAM_S;

typedef enum tagUDI_IOCTL_CMD_TYPE_E
{
    UDI_IOCTL_SET_WRITE_CB = 0xF001,            /* 设置一个起始码值防止与系统定义冲突 */
    UDI_IOCTL_SET_READ_CB,

    UDI_IOCTL_INVAL_CMD = -1
} UDI_IOCTL_CMD_TYPE_E;

/* ACM */
/* IOCTL CMD 定义 */

/* UDI IOCTL 命令ID */
#define UDI_ACM_IOCTL_SET_READ_CB           ACM_IOCTL_SET_READ_CB
#define UDI_ACM_IOCTL_GET_READ_BUFFER_CB    ACM_IOCTL_GET_RD_BUFF
#define UDI_ACM_IOCTL_RETUR_BUFFER_CB       ACM_IOCTL_RETURN_BUFF


/* ACM MODEM SIG define */
#define SIGNALNOCH 0
#define SIGNALCH 1
#define RECV_ENABLE 1
#define RECV_DISABLE 0
#define SEND_ENABLE 1
#define SEND_DISABLE 0
#define HIGHLEVEL 1
#define LOWLEVEL 0


/* ACM MODEM 管角信号结构体定义*/
typedef struct tagMODEM_MSC_STRU
{
    unsigned int OP_Dtr     :    1;          /*DTR CHANGE FLAG*/
    unsigned int OP_Dsr     :    1;          /*DSR CHANGE FLAG*/
    unsigned int OP_Cts     :    1;          /*CTSCHANGE FLAG*/
    unsigned int OP_Rts     :    1;          /*RTS CHANGE FLAG*/
    unsigned int OP_Ri      :    1;          /*RI CHANGE FLAG*/
    unsigned int OP_Dcd     :    1;          /*DCD CHANGE FLAG*/
    unsigned int OP_Fc      :    1;          /*FC CHANGE FLAG*/
    unsigned int OP_Brk     :    1;          /*BRK CHANGE FLAG*/
    unsigned int OP_Spare   :    24;         /*reserve*/
    unsigned char   ucDtr;                   /*DTR  VALUE*/
    unsigned char   ucDsr;                   /*DSR  VALUE*/
    unsigned char   ucCts;                   /*DTS VALUE*/
    unsigned char   ucRts;                   /*RTS  VALUE*/
    unsigned char   ucRi;                    /*RI VALUE*/
    unsigned char   ucDcd;                   /*DCD  VALUE*/
    unsigned char   ucFc;                    /*FC  VALUE*/
    unsigned char   ucBrk;                   /*BRK  VALUE*/
    unsigned char   ucBrkLen;                /*BRKLEN VALUE*/
} MODEM_MSC_STRU, *PMODEM_MSC_STRU,AT_DCE_MSC_STRU;

typedef void (*ACM_MODEM_MSC_READ_CB_T)(MODEM_MSC_STRU* pModemMsc);


/* NCM */
/* 上行线路收包函数指针 */
typedef void (*USBUpLinkRxFunc)(UDI_HANDLE handle, void * pPktNode);

/* USB IOCTL枚举 */
typedef enum tagNCM_IOCTL_CMD_TYPE_E
{
    NCM_IOCTL_NETWORK_CONNECTION_NOTIF,      /* 0x0,NCM网络是否连接上*/
    NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF, /* 0x1,NCM设备协商的网卡速度*/
    NCM_IOCTL_SET_PKT_ENCAP_INFO,            /* 0x2,设置包封装格式*/
    NCM_IOCTL_REG_UPLINK_RX_FUNC,            /* 0x3,注册上行收包回调函数*/
    NCM_IOCTL_REG_FREE_PKT_FUNC,             /* 0x4,注册释放包封装回调函数*/
    NCM_IOCTL_FREE_BUFF,                     /* 0x5,释放底软buffer*/
    NCM_IOCTL_GET_USED_MAX_BUFF_NUM,         /* 0x6,获取上层可以最多占用的ncm buffer个数*/
    NCM_IOCTL_GET_DEFAULT_TX_MIN_NUM,        /* 0x7,获取默认发包个数阈值，超过该阈值会启动一次NCM传输*/
    NCM_IOCTL_GET_DEFAULT_TX_TIMEOUT,        /* 0x8,获取默认发包超时时间，超过该时间会启动一次NCM传输*/
    NCM_IOCTL_GET_DEFAULT_TX_MAX_SIZE,       /* 0x9,获取默认发包字节阈值，超过该阈值会启动一次NCM传输*/
    NCM_IOCTL_SET_TX_MIN_NUM,                /* 0xa,设置发包个数阈值，超过该阈值会启动一次NCM传输*/
    NCM_IOCTL_SET_TX_TIMEOUT,                /* 0xb,设置发包超时时间，超过该时间会启动一次NCM传输*/
    NCM_IOCTL_SET_TX_MAX_SIZE,               /* 0xc,该命令字不再使用。设置发包字节阈值，超过该阈值会启动一次NCM传输*/
    NCM_IOCTL_GET_RX_BUF_SIZE,               /* 0xd,获取收包buffer大小*/
    NCM_IOCTL_FLOW_CTRL_NOTIF,               /* 0xe,流控控制开关*/
    NCM_IOCTL_REG_AT_PROCESS_FUNC,           /* 0xf,注册AT命令处理回调函数*/
    NCM_IOCTL_AT_RESPONSE,                   /* 0x10,AT命令回应*/
    NCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC,     /* 0x11,注册网卡状态改变通知回调函数*/
    NCM_IOCTL_SET_PKT_STATICS,               /* 0x12,配置统计信息*/
    NCM_IOCTL_GET_FLOWCTRL_STATUS,           /* 0x13 查询NCM流控状态*/

    NCM_IOCTL_GET_CUR_TX_MIN_NUM,            /* 0x14 获取当前发包个数阈值*/
    NCM_IOCTL_GET_CUR_TX_TIMEOUT,            /* 0x15 获取当前发包超时时间*/
    NCM_IOCTL_IPV6_DNS_NOTIF,                /*0x16 IPV6 DNS主动上报*/
    NCM_IOCTL_SET_IPV6_DNS,                  /* 0x16 配置IPV6 DNS*/
    NCM_IOCTL_CLEAR_IPV6_DNS,                /* 0x17 清除IPV6 DNS在板端的缓存,param在此命令字没有意义，不填空指针即可*/
    NCM_IOCTL_GET_NCM_STATUS,                /* 0x18 获取NCM网卡状态 enable:TRUE(1);disable:FALSE(0) */

    NCM_IOCTL_SET_ACCUMULATION_TIME,

	NCM_IOCTL_SET_RX_MIN_NUM,		         /*配置收包个数阈值*/
	NCM_IOCTL_SET_RX_TIMEOUT,			     /*配置收包超时时间*/

    NCM_IOCTL_REG_NDIS_RESP_STATUS_FUNC      /* NDIS通道AT命令状态处理回调函数 */
}NCM_IOCTL_CMD_TYPE_E;

/* NCM连接状态枚举,NCM_IOCTL_NETWORK_CONNECTION_NOTIF命令字对应参数枚举*/
typedef enum tagNCM_IOCTL_CONNECTION_STATUS_E
{
    NCM_IOCTL_CONNECTION_LINKDOWN,      /* NCM网络断开连接*/
    NCM_IOCTL_CONNECTION_LINKUP         /* NCM网络连接*/
}NCM_IOCTL_CONNECTION_STATUS_E;

/* NCM连接速度结构,NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF命令字对应参数结构体*/
typedef struct tagNCM_IOCTL_CONNECTION_SPEED_S
{
    unsigned int u32DownBitRate;
    unsigned int u32UpBitRate;
}NCM_IOCTL_CONNECTION_SPEED_S;

/* AT命令回复数据指针及长度 NCM_IOCTL_AT_RESPONSE*/
typedef struct tagNCM_AT_RSP_S
{
    unsigned char* pu8AtAnswer;
    unsigned int u32Length;
} NCM_AT_RSP_S;

/* AT命令接收函数指针，该函数为同步接口，对应NCM_IOCTL_REG_AT_PROCESS_FUNC命令字*/
typedef void (*USBNdisAtRecvFunc)(unsigned char * pu8Buf, unsigned int u32Len);

/* NCM流控开关枚举,NCM_IOCTL_NETWORK_CONNECTION_NOTIF命令字对应参数枚举*/
typedef enum tagNCM_IOCTL_FLOW_CTRL_E
{
    NCM_IOCTL_FLOW_CTRL_ENABLE,      /* 打开流控*/
    NCM_IOCTL_FLOW_CTRL_DISABLE      /* 关闭流控*/
}NCM_IOCTL_FLOW_CTRL_E;

/* NCM网卡状态改变通知枚举,NCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC命令字对应参数枚举*/
typedef enum tagNCM_IOCTL_CONNECT_STUS_E
{
    NCM_IOCTL_STUS_CONNECT,      /* 建链*/
    NCM_IOCTL_STUS_BREAK         /* 网卡断开,断链*/
}NCM_IOCTL_CONNECT_STUS_E;

/* 网卡状态切换通知函数，对应NCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC命令字*/
typedef void (*USBNdisStusChgFunc)(NCM_IOCTL_CONNECT_STUS_E enStatus, void * pBuffer);

/* NDIS通道AT命令状态处理回调函数 */
typedef void (*USBNdisRespStatusCB)(void *pBuffer, unsigned int status);

#define BSP_NCM_IPV6_DNS_LEN     32
typedef struct tagNCM_IPV6DNS_S  /* 0x16 配置IPV6 DNS*/
{
    unsigned char * pu8Ipv6DnsInfo;/* 32字节，低16字节表示primaryDNS；高16字节表示SecondaryDNS。*/
    unsigned int u32Length;
} NCM_IPV6DNS_S;

typedef int (*UDI_ADP_INIT_CB_T)(void);
typedef unsigned int (*UDI_GET_CAPABILITY_CB_T)(UDI_DEVICE_ID_E devId);
typedef int (*UDI_OPEN_CB_T)(UDI_OPEN_PARAM_S *param, UDI_HANDLE handle);
typedef int (*UDI_CLOSE_CB_T)(void* pPrivate);
typedef int (*UDI_WRITE_CB_T)(void* pPrivate, void* pMemObj, unsigned int u32Size);
typedef int (*UDI_READ_CB_T)(void* pPrivate, void* pMemObj, unsigned int u32Size);
typedef int (*UDI_IOCTL_CB_T) (void* pPrivate, unsigned int u32Cmd, void* pParam);


/* 驱动适配函数指针表 */
typedef struct tagUDI_DRV_INTEFACE_TABLE
{
	/* capability */
	UDI_ADP_INIT_CB_T		udi_get_capability_cb;

	/* data interfaces */
	UDI_OPEN_CB_T			udi_open_cb;
	UDI_CLOSE_CB_T			udi_close_cb;
	UDI_WRITE_CB_T			udi_write_cb;
	UDI_READ_CB_T			udi_read_cb;
	UDI_IOCTL_CB_T			udi_ioctl_cb;
}UDI_DRV_INTEFACE_TABLE;

/*****************************************************************************
* 函 数 名  : mdrv_udi_open
*
* 功能描述  : 打开设备(数据通道)
*
* 输入参数  : pParam: 设备的打开配置参数
* 输出参数  : 无
* 返 回 值  : -1:失败 / 其他:成功
*****************************************************************************/
UDI_HANDLE mdrv_udi_open(UDI_OPEN_PARAM_S *pParam);


/*****************************************************************************
* 函 数 名  : mdrv_udi_close
*
* 功能描述  : 关闭设备(数据通道)
*
* 输入参数  : handle: 设备的handle
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
int mdrv_udi_close(UDI_HANDLE handle);

/*****************************************************************************
* 函 数 名  : mdrv_udi_write
*
* 功能描述  : 数据写
*
* 输入参数  : handle:  设备的handle
*             pMemObj: buffer内存 或 内存链表对象
*             u32Size: 数据写尺寸 或 内存链表对象可不设置
* 输出参数  :
*
* 返 回 值  : 完成字节数 或 成功/失败
*****************************************************************************/
int mdrv_udi_write(UDI_HANDLE handle, void* pMemObj, unsigned int u32Size);


/*****************************************************************************
* 函 数 名  : mdrv_udi_read
*
* 功能描述  : 数据读
*
* 输入参数  : handle:  设备的handle
*             pMemObj: buffer内存 或 内存链表对象
*             u32Size: 数据读尺寸 或 内存链表对象可不设置
* 输出参数  :
*
* 返 回 值  : 完成字节数 或 成功/失败
*****************************************************************************/
int mdrv_udi_read(UDI_HANDLE handle, void* pMemObj, unsigned int u32Size);


/*****************************************************************************
* 函 数 名  : mdrv_udi_ioctl
*
* 功能描述  : 数据通道属性配置
*
* 输入参数  : handle: 设备的handle
*             u32Cmd: IOCTL命令码
*             pParam: 操作参数
* 输出参数  :
*
* 返 回 值  : 成功/失败
*****************************************************************************/
int mdrv_udi_ioctl(UDI_HANDLE handle, unsigned int u32Cmd, void* pParam);

#ifdef __cplusplus
}
#endif

#endif
