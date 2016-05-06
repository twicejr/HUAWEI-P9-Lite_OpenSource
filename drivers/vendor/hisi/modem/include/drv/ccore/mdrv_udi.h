
/*************************************************************************
*   版权所有(C) 1987-2011, 深圳华为技术有限公司.
*
*   文 件 名 :  mdrv_udi.h
*
*   作    者 :  yangzhi
*
*   描    述 :  本文件命名为"mdrv.h", 给出V7R1底软和协议栈之间的API接口统计
*
*   修改记录 :  2011年1月18日  v1.00  yangzhi创建
*************************************************************************/

#ifndef __MDRV_CCORE_UDI_H__
#define __MDRV_CCORE_UDI_H__
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
        UDI_ICC_CCPU_HIFI_VOS_NORMAL_MSG = MDRV_ICC_CCPU_HIFI_VOS_NORMAL_MSG,
        UDI_ICC_CCPU_HIFI_VOS_URGENT_MSG = MDRV_ICC_CCPU_HIFI_VOS_URGENT_MSG,
        UDI_ICC_HIFI_TPHY_MSG_NRM = MDRV_ICC_HIFI_TPHY_MSG_NRM,
        UDI_ICC_HIFI_TPHY_MSG_URG = MDRV_ICC_HIFI_TPHY_MSG_URG,
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

	/**V8R2**************************************************************************************************/
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
	/****************************************************************************************************/

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
