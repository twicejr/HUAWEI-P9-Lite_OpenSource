#ifndef __MDRV_CCORE_STUB_V7_H__
#define __MDRV_CCORE_STUB_V7_H__
#ifdef __cplusplus
extern "C"
{
#endif

static inline unsigned int DRV_PWRCTRL_STANDBYSTATECCPU(unsigned int ulStandbyTime, unsigned int ulSwitchtime)
{
    return 0;
}

/*liuyi++ phase4*/
static inline unsigned int DRV_ABB_WRX_CTRL(unsigned char ucStatus)
{
    return 0;
}

static inline void DRV_RF_LDODOWN(unsigned int enRfID)
{
    return;
}

static inline unsigned long DRV_GET_WCDMA_PLL_STATUS(void)
{
    return 1;
}

static inline unsigned long DRV_GET_GSM_PLL_STATUS(void)
{
    return 0;
}

static inline unsigned long DRV_GET_DSP_PLL_STATUS(void)
{
    return 0;
}
static inline int DRV_GET_ARM_PLL_STATUS(void)
{
    return 0;
}

/*one track 接口归一项目遗留nv备份恢复接口，后续om NV归一清理*/
#if 1
/* Begin: DRV为OAM实现NV备份恢复流程而提供的接口 */

/********************************************************************************************************
 函 数 名  : DRV_UPGRADE_NV_SET_RESULT
 功能描述  : OAM通过该接口告诉底软NV升级成功了还是失败了
 输入参数  : status：0      表示NV升级成功
                     其他值 表示NV升级失败
 输出参数  :
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 其他注意  : V3R3 SFT 和 V9 BBIT 打桩
             V9 SFT  实现
                如果NV升级成功，底软往fastboot共享区置成功标识
                如果NV升级失败，底软往fastboot共享区置失败标识

 修改历史  :
 1.日    期   : 2012年12月6日
   作    者   : 蔡喜 00220237
   修改内容   : 新生成函数
********************************************************************************************************/
extern int DRV_UPGRADE_NV_SET_RESULT(int status);

/********************************************************************************************************
 函 数 名  : DRV_NV_FILE_SEC_CHECK
 功能描述  : 对文件进行校验
 输入参数  : pnvFilePath：待校验文件的路径
 输出参数  :
 返 回 值  : 0 :    文件校验正确
             -1：   文件校验失败
 其他注意  : 目前条件不具备，直接打桩，以后实现

 修改历史  :
 1.日    期   : 2012年12月6日
   作    者   : 蔡喜 00220237
   修改内容   : 新生成函数
********************************************************************************************************/
extern int DRV_NV_FILE_SEC_CHECK(char * pnvFilePath);

/********************************************************************************************************
 函 数 名  : BSP_DLOAD_NVBackupRead
 功能描述  : 从Flash中的NV项备份区读取数据，实现NV项的恢复功能。
 输入参数  : len：从NV项备份区起始处开始，需要读取的NV项长度（字节数）。
 输出参数  : pRamAddr：目的RAM地址，用于存放读出的NV项数据。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 其他注意  : V3R3 SFT 和 V9 BBIT 保持原样
             V9 SFT  将调用nand接口修改为调用emmc接口读写NV备份区

 修改历史  :
 1.日    期   : 2012年12月6日
   作    者   : 蔡喜 00220237
   修改内容   : 修改函数
********************************************************************************************************/
extern int BSP_DLOAD_NVBackupRead(unsigned char *pRamAddr, unsigned int len);
#define DRV_NVBACKUP_READ(pRamAddr,len)    BSP_DLOAD_NVBackupRead(pRamAddr, len)

/********************************************************************************************************
 函 数 名  : BSP_DLOAD_NVBackupWrite
 功能描述  : 将特定数据写入Flash中的NV项备份区，实现NV项的备份功能。
 输入参数  : pRamAddr：源RAM地址，用于存放需要写入的NV项数据。
             len：从NV项备份区起始处开始，需要写入的NV项长度（字节数）。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 其他注意  : V3R3 SFT 和 V9 BBIT 保持原样
             V9 SFT  将调用nand接口修改为调用emmc接口读写NV备份区

 修改历史  :
 1.日    期   : 2012年12月6日
   作    者   : 蔡喜 00220237
   修改内容   : 修改函数
********************************************************************************************************/
extern int BSP_DLOAD_NVBackupWrite(unsigned char *pRamAddr, unsigned int len);
#define DRV_NVBACKUP_WRITE(pRamAddr, len)   BSP_DLOAD_NVBackupWrite(pRamAddr, len)

/********************************************************************************************************
 函 数 名  : DRV_NVBACKUP_EXT_READ
 功能描述  : 从Flash中的LastBackup区读取数据，为NV备份数据丢失的容错恢复机制提供支持
 输入参数  : len：从LastBackup起始处开始，需要读取的NV项长度（字节数）。
 输出参数  : pRamAddr：目的RAM地址，用于存放读出的NV项数据。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 其他注意  : V3R3 SFT  打桩
             V9R1 SFT  实现

 修改历史  :
 1.日    期   : 2013年10月22日
   作    者   : 蔡喜 00220237
   修改内容   : 新增函数
********************************************************************************************************/
extern int DRV_NVBACKUP_EXT_READ(unsigned char *pRamAddr, unsigned int len);

/********************************************************************************************************
 函 数 名  : DRV_NVBACKUP_EXT_WRITE
 功能描述  : 将特定数据写入Flash中的LastBackup区，为NV备份数据丢失的容错恢复机制提供支持
 输入参数  : pRamAddr：源RAM地址，用于存放需要写入的NV项数据。
             len：从LastBackup区起始处开始，需要写入的NV项长度（字节数）。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 其他注意  : V3R3 SFT  打桩
             V9R1 SFT  实现

 修改历史  :
 1.日    期   : 2013年10月22日
   作    者   : 蔡喜 00220237
   修改内容   : 新增函数
********************************************************************************************************/
extern int DRV_NVBACKUP_EXT_WRITE(unsigned char *pRamAddr, unsigned int len);
/* End: DRV为OAM实现NV备份恢复流程而提供的接口 */

/********************************************************************************************************
 函 数 名  : NVBackupFlashDataWrite
 功能描述  : 实现FLASH 中NV备份恢复区从指定位置写功能。
 输入参数  : pRamAddr：源RAM地址，用于存放需要写入的NV项数据。
             offset :从NV备份区地址开始的偏移
             len：从偏移处开始，需要写入NV数据的长度（字节数）。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 其他注意  : V3R3 SFT 和 V9 BBIT 保持原样
             V9 SFT  将调用nand接口修改为调用emmc接口读写NV备份区；设计时将备份分区名字定义为"/mnvbp"

 修改历史  :
 1.日    期   : 2012年12月6日
   作    者   : 蔡喜 00220237
   修改内容   : 修改函数
********************************************************************************************************/
extern int NVBackupFlashDataExtWrite(unsigned char* pRamAddr, unsigned int offset,unsigned int len);
#define DRV_NV_FLASH_EXT_WRITE(pRamAddr, offset,len) NVBackupFlashDataExtWrite(pRamAddr, offset,len)

/********************************************************************************************************
 函 数 名  : NVBackupFlashDataWrite
 功能描述  : 实现FLASH 中NV备份恢复区从指定位置写功能。
 输入参数  : pRamAddr：源RAM地址，用于存放需要写入的NV项数据。
             offset :从NV备份区地址开始的偏移
             len：从偏移处开始，需要写入NV数据的长度（字节数）。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 其他注意  : V3R3 SFT 和 V9 BBIT 保持原样
             V9 SFT  将调用nand接口修改为调用emmc接口读写NV备份区；设计时将备份分区名字定义为"/mnvbp"

 修改历史  :
 1.日    期   : 2012年12月6日
   作    者   : 蔡喜 00220237
   修改内容   : 修改函数
********************************************************************************************************/
extern int NVBackupFlashDataWrite(unsigned char* pRamAddr, unsigned int offset,unsigned int len);
#define DRV_NV_FLASH_WRITE(pRamAddr, offset,len) NVBackupFlashDataWrite(pRamAddr, offset,len)

/********************************************************************************************************
 函 数 名  : BSP_DLOAD_EXT_SCBackupWrite
 功能描述  : 将特定数据写入Flash中的SC备份区，实现SC项的备份功能。
 输入参数  : pRamAddr：源RAM地址，用于存放需要写入的NV项数据。
             len：从NV项备份区起始处开始，需要写入的NV项长度（字节数），不超过1Block。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
********************************************************************************************************/
extern int BSP_DLOAD_EXT_SCBackupWrite(unsigned char *pRamAddr, unsigned int len);
#define DRV_SCBACKUP_EXT_WRITE(pRamAddr, len)   BSP_DLOAD_EXT_SCBackupWrite(pRamAddr, len)

/********************************************************************************************************
 函 数 名  : BSP_DLOAD_EXT_SCBackupRead
 功能描述  : 从Flash中的LastBackup区读取数据，为SC备份数据丢失的容错恢复机制提供支持
 输入参数  : len：从LastBackup起始处开始，需要读取的NV项长度（字节数）。
 输出参数  : pRamAddr：目的RAM地址，用于存放读出的NV项数据。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 其他注意  : V3R3 SFT  打桩
             V9R1 SFT  实现

 修改历史  :
 1.日    期   : 2013年10月22日
   作    者   : 蔡喜 00220237
   修改内容   : 新增函数
********************************************************************************************************/
extern int BSP_DLOAD_EXT_SCBackupRead(unsigned char *pRamAddr, unsigned int len);
#define DRV_SCBACKUP_EXT_READ(pRamAddr,len)    BSP_DLOAD_EXT_SCBackupRead(pRamAddr, len)


/*sd*/
/*SD卡设备类型*/
typedef struct _sd_dev_type_str
{
    unsigned int   devNameLen;
    char            devName[16];
}SD_DEV_TYPE_STR;

static inline SD_DEV_TYPE_STR * DRV_GET_SD_PATH(void)
{
    return 0;
}

/*****************************************************************************
 * 函 数 名  : DRV_GET_CDROM_VERSION
 *
 * 功能描述  : 获取后台版本号字符串
 *
 * 输入参数  : s8 *str   :字符串缓冲区
 *             int len   :字符串长度
 * 输出参数  : s8 *str   :字符串缓冲区
 *
 * 返 回 值  : DLOAD_ERROR   :输入参数非法
 *             其它          :返回字符串长度
 *
 * 其它说明  : AT模块调用
 *             正常模式支持
 *             下载模式支持
 *****************************************************************************/
static inline int DRV_GET_CDROM_VERSION(char *pVersionInfo,unsigned int ulLength)
{
        return 0;
}


#endif

/* 下载模式枚举 */
typedef enum tagDLOAD_MODE_E
{
    DLOAD_MODE_DOWNLOAD = 0,
    DLOAD_MODE_NORMAL,
    DLOAD_MODE_DATA,
    DLOAD_MODE_MAX
}DLOAD_MODE_E;

/*升级Flash信息*/
typedef struct
{
    unsigned int ulblockCount;    /*Block个数*/
    unsigned int ulpageSize;    /*page页大小*/
    unsigned int ulpgCntPerBlk;    /*一个Block中的page个数*/
}DLOAD_FLASH_STRU;

static inline int DRV_GET_DLOAD_INFO(unsigned char atCmdBuf[], unsigned int dloadType)
{
    return 0;
}

static inline int DRV_SET_UPDATA_FLAG(int flag)
{
    return 0;
}

static inline unsigned int BSP_MNTN_ProductTypeGet(void)
{
	return 0;
}

#define DRV_PRODUCT_TYPE_GET()   BSP_MNTN_ProductTypeGet()

#if 1  /*drv_pmu.h*/
/*****************************************************************************
 函 数 名  : DRV_GET_PMU_STATE
 功能描述  : 获取PMU模块开机方式、充电状态、电池电量、电池在位状态。
 输入参数  : 无。
 输出参数  : Pmu_State :开机方式、充电状态、电池电量、电池在位状态。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 注意事项　：该接口仅在PS的PC工程中使用，目前没有应用，暂保留。
*****************************************************************************/
static inline unsigned int DRV_GET_PMU_STATE(void* Pmu_State)
{
	return 0;
}
#endif

/*****************************************************************************
 函 数 名  : DRV_GET_DLOAD_VERSION
 功能描述  : Get dload version
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
static inline int DRV_GET_DLOAD_VERSION(unsigned char *str, int len)
{
    return 0;
}

static inline int DRV_GET_AUTHORITY_VERSION(unsigned char *str, unsigned int len)
{
    return 0;
}

static inline int DRV_GET_AUTHORITY_ID(unsigned char *buf, unsigned int len)
{
    return 0;
}

static inline unsigned int DRV_SDMMC_USB_STATUS(void)
{
    return 0;
}

/*nand模块的stub,从v8r2上复制过来*/

/*************************************************
 函 数 名   : BSP_MNTN_ProductTypeGet
 功能描述   : 返回当前产品类型
 输入参数   : 无
 输出参数   : 无
 返 回 值   :0:STICK
             1:MOD
             2:E5
             3:CPE
*************************************************/
extern unsigned int BSP_MNTN_ProductTypeGet(void);
#define DRV_PRODUCT_TYPE_GET()   BSP_MNTN_ProductTypeGet()

#if 1 /*drv_usb.h*/
/* MODEM 管角信号结构体定义*/
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
    unsigned char   ucDtr;                     /*DTR  VALUE*/
    unsigned char   ucDsr;                     /*DSR  VALUE*/
    unsigned char   ucCts;                     /*DTS VALUE*/
    unsigned char   ucRts;                     /*RTS  VALUE*/
    unsigned char   ucRi;                      /*RI VALUE*/
    unsigned char   ucDcd;                     /*DCD  VALUE*/
    unsigned char   ucFc;                      /*FC  VALUE*/
    unsigned char   ucBrk;                     /*BRK  VALUE*/
    unsigned char   ucBrkLen;                  /*BRKLEN VALUE*/
} MODEM_MSC_STRU, *PMODEM_MSC_STRU,AT_DCE_MSC_STRU;


typedef unsigned int (*MNTN_ERRLOGREGFUN)(char * cFileName,unsigned int ulFileId, unsigned int ulLine,
                unsigned int ulErrNo, void * pBuf, unsigned int ulLen);

/*****************************************************************************
 函 数 名  : ErrlogRegFunc
 功能描述  : USB MNTN注册异常日志接口，Porting项目中打桩
                Added by c00204787 for errorlog,20120211
 输入参数  : 无。
 输出参数  : 无。
 返回值：   无

*****************************************************************************/
/*extern void ErrlogRegFunc(MNTN_ERRLOGREGFUN pRegFunc);
 */
extern void MNTN_ERRLOG_REG_FUNC(MNTN_ERRLOGREGFUN pRegFunc);

/********************************************************
函数说明：协议栈注册HSIC使能通知回调函输
函数功能:
输入参数：pFunc: HSIC使能回调函输指针
输出参数：无
输出参数：无
返回值：  0：成功
          1：失败
********************************************************/
typedef void (*HSIC_UDI_ENABLE_CB_T)(void);
extern unsigned int BSP_HSIC_RegUdiEnableCB(HSIC_UDI_ENABLE_CB_T pFunc);
#define DRV_HSIC_REGUDI_ENABLECB(x) BSP_HSIC_RegUdiEnableCB(x)

/********************************************************
函数说明：协议栈注册HSIC去使能通知回调函输
函数功能:
输入参数：pFunc: HSIC去使能回调函输指针
输出参数：无
输出参数：无
返回值：  0：成功
          1：失败
********************************************************/
typedef void (*HSIC_UDI_DISABLE_CB_T)(void);
extern unsigned int BSP_HSIC_RegUdiDisableCB(HSIC_UDI_DISABLE_CB_T pFunc);
#define DRV_HSIC_REGUDI_DISABLECB(x) BSP_HSIC_RegUdiDisableCB(x)
/********************************************************
函数说明：协议栈查询HSIC枚举状态
函数功能:
输入参数：无
输出参数：无
输出参数：无
返回值：  1：枚举完成
          0：枚举未完成
********************************************************/
extern unsigned int BSP_GetHsicEnumStatus(void);
#define DRV_GET_HSIC_ENUM_STATUS() BSP_GetHsicEnumStatus()

/*****************************************************************************
* 函 数 名  : BSP_NCM_Write_Ready
* 功能描述  : 准备发送数据
* 输入参数  : void
* 输出参数  :
* 返 回 值  : void
* 修改记录  :
*****************************************************************************/
void BSP_NCM_Write_Ready(void);

/********************************************************
函数说明： 返回当前NV项中的设备形态值，是否支持PCSC
函数功能:
输入参数： dev_type是设备形态值（OAM从NV中读出）

输出参数： 无。
返回值：
          0: dev_type不支持PCSC设备；
          1：dev_type支持PCSC设备
********************************************************/
/*unsigned int pcsc_info_quiry(unsigned int ulDevType);*/

typedef unsigned int (*pFunAPDUProcess)(unsigned int CmdType, unsigned char *pApdu, unsigned int ApduLen);
typedef unsigned int (*GetCardStatus)(void);

typedef struct
{
    pFunAPDUProcess   pFuncApdu;
    GetCardStatus  pFuncGetCardStatus;
}BSP_CCID_REGFUNC;

/*****************************************************************************
 函 数 名  : pcsc_usim_int
 功能描述  : 注册PCSC命令接收函数
 输入参数  :
 输出参数  : None
 返 回 值  : void
*****************************************************************************/
extern void pcsc_usim_int(pFunAPDUProcess pFun1, GetCardStatus pFun2);
#define DRV_PCSC_REG_CALLBACK(pFun1, pFun2) pcsc_usim_int((pFun1), (pFun2))


/*****************************************************************************
 函 数 名  : pcsc_usim_ctrl_cmd
 功能描述  : PCSC命令回复函数
 输入参数  :
 输出参数  : None
 返 回 值  : void
*****************************************************************************/
extern unsigned int pcsc_usim_ctrl_cmd(unsigned int CmdTpye, unsigned int Result,
                                        unsigned char *Buf, unsigned int Length);
#define DRV_PCSC_SEND_DATA(CmdType, Result, Buffer, Length) pcsc_usim_ctrl_cmd(CmdType, Result, Buffer, Length)

/************************************************************************
 * FUNCTION
 *       PDP_ACT_DRV_CALLBACK
 * DESCRIPTION
 *       PDP激活后调用底软的回调函数，原本在闪电卡上用作加载符号表信息，现在打桩
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
extern int PDP_ACT_DRV_CALLBACK(void);

typedef void(* USB_NET_DEV_SWITCH_GATEWAY)
(
    void
);

/************************************其余宏定义为空的函数******************************************/
/*****************************************************************************
 函 数 名  : UsbStatusCallbackRegister
 功能描述  : 记录pCallBack至全局变量中。SD卡功耗相关接口，V7先打桩
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
 /*extern int  UsbStatusCallbackRegister(pUsbState pCallBack);*/
#define DRV_USB_STATUS_CALLBACK_REGI(pCallBack)              MDRV_OK

#define DRV_GPIO_USB_SWITCH     200
#define DRV_GPIO_HIGH           1
#define DRV_GPIO_LOW            0

#define AT_USB_SWITCH_SET_VBUS_VALID            1
#define AT_USB_SWITCH_SET_VBUS_INVALID          2

#define USB_SWITCH_ON       1
#define USB_SWITCH_OFF      0

/* IOCTL CMD 定义 */
#define ACM_IOCTL_SET_WRITE_CB      0x7F001000
#define ACM_IOCTL_SET_READ_CB       0x7F001001
#define ACM_IOCTL_SET_EVT_CB        0x7F001002
#define ACM_IOCTL_SET_FREE_CB       0x7F001003

#define ACM_IOCTL_WRITE_ASYNC       0x7F001010
#define ACM_IOCTL_GET_RD_BUFF       0x7F001011
#define ACM_IOCTL_RETURN_BUFF       0x7F001012
#define ACM_IOCTL_RELLOC_READ_BUFF  0x7F001013
#define ACM_IOCTL_SEND_BUFF_CAN_DMA 0x7F001014

#define ACM_IOCTL_IS_IMPORT_DONE    0x7F001020
#define ACM_IOCTL_WRITE_DO_COPY     0x7F001021

/* Modem 控制命令码 */
#define ACM_MODEM_IOCTL_SET_MSC_READ_CB 0x7F001030
#define ACM_MODEM_IOCTL_MSC_WRITE_CMD   0x7F001031
#define ACM_MODEM_IOCTL_SET_REL_IND_CB  0x7F001032

/* UDI IOCTL 命令ID */
#define UDI_ACM_IOCTL_SET_READ_CB           ACM_IOCTL_SET_READ_CB
#define UDI_ACM_IOCTL_GET_READ_BUFFER_CB    ACM_IOCTL_GET_RD_BUFF
#define UDI_ACM_IOCTL_RETUR_BUFFER_CB       ACM_IOCTL_RETURN_BUFF

#define UART_IOCTL_SET_WRITE_CB      0x7F001000
#define UART_IOCTL_SET_READ_CB       0x7F001001
#define UART_IOCTL_SET_EVT_CB        0x7F001002
#define UART_IOCTL_SET_FREE_CB       0x7F001003
#define UART_IOCTL_WRITE_ASYNC       0x7F001010
#define UART_IOCTL_GET_RD_BUFF       0x7F001011
#define UART_IOCTL_RETURN_BUFF       0x7F001012
#define UART_IOCTL_RELLOC_READ_BUFF  0x7F001013
#define UART_IOCTL_SEND_BUFF_CAN_DMA 0x7F001014
#define UART_IOCTL_SET_WRITE_TIMEOUT 0x7F001015
#define UART_IOCTL_SET_BAUD           0X7F001016
#define UART_IOCTL_SET_WLEN           0X7F001017
#define UART_IOCTL_SET_STP2           0X7F001018
#define UART_IOCTL_SET_EPS            0X7F001019
#define UART_IOCTL_IS_IMPORT_DONE    0x7F001020
#define UDI_UART_IOCTL_SET_READ_CB           UART_IOCTL_SET_READ_CB
#define UDI_UART_IOCTL_GET_READ_BUFFER_CB    UART_IOCTL_GET_RD_BUFF
#define UDI_UART_IOCTL_RETUR_BUFFER_CB       UART_IOCTL_RETURN_BUFF
#define UART_IOCTL_SET_MSC_READ_CB 0x7F001021
#define UART_IOCTL_MSC_WRITE_CMD 0x7F001022
#define UART_IOCTL_SWITCH_MODE_CB 0x7F001023
#define UART_IOCTL_SET_FLOW_CONTROL 0x7F001024
#define UART_IOCTL_SET_AC_SHELL 0x7F001025

/* UART UDI 错误码*/
#define UART_UDI_ERROR_BASE               0x80000000

#define UART_ERR_MODULE_NOT_INITED      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_MODULE_NOT_INITED) | UART_UDI_ERROR_BASE))
#define UART_ERR_NULL_PTR      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_NULL_PTR) | UART_UDI_ERROR_BASE))
#define UART_ERR_INVALID_PARA      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_INVALID_PARA) | UART_UDI_ERROR_BASE))
#define UART_ERR_RETRY_TIMEOUT      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_RETRY_TIMEOUT) | UART_UDI_ERROR_BASE))
#define UART_ERR_BUF_ALLOC_FAILED      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_BUF_ALLOC_FAILED) | UART_UDI_ERROR_BASE))
#define UART_ERR_BUF_FREE_FAILED      ((int)(BSP_DEF_ERR(BSP_MODU_UART, (int) BSP_ERR_BUF_FREE_FAILED) | UART_UDI_ERROR_BASE))

#define UART_A_SHELL  (0x5A5A5A5A)
#define UART_C_SHELL  (0xA5A5A5A5)

/* UART数据位长*/
typedef enum
{
    WLEN_5_BITS,
    WLEN_6_BITS,
    WLEN_7_BITS,
    WLEN_8_BITS,
    WLEN_MAX
}UART_WLEN_ENUM;

/* UART停止位长*/
typedef enum
{
    STP2_OFF,
    STP2_ON,
    STP2_MAX
}uart_stp2_enum;

/* UART校验方式*/
typedef enum
{
    PARITY_NO_CHECK,
    PARITY_CHECK_ODD,        /*奇校验*/
    PARITY_CHECK_EVEN,        /*偶校验*/
    PARITY_CHECK_MARK,        /*校验位始终为1*/
    PARITY_CHECK_SPACE,       /*校验位始终为0*/
    PARITY_CHECK_MAX
}uart_parity_enum;

/* 异步数据收发结构 */
typedef struct tagUART_WR_ASYNC_INFO
{
    char* pBuffer;
    unsigned int u32Size;
    void* pDrvPriv;
}uart_wr_async_info;
/* 读buffer配置信息 */
typedef struct tagUART_READ_BUFF_INFO
{
    unsigned int u32BuffSize;
    unsigned int u32BuffNum;
}uart_read_buff_info;
/* 流控开关结构 */
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved1 : 14;/* bit[0-13] : reversed */
        unsigned int  rtsen         : 1;/* bit[14] : rts enable, up stream flow ctrl  */
        unsigned int  ctsen         : 1;/* bit[15] : cts enable, down stream flow ctrl */
        unsigned int  reserved2 : 16;/* bit[16-31] : reversed */
    } reg;
} uart_flow_ctrl_union;

typedef void (*uart_free_cb_t)(char* pBuff);
typedef void (*uart_read_cb_t)(void);
typedef void (*uart_msc_read_cb_t)(MODEM_MSC_STRU* pModemMsc);
typedef void (*uart_switch_mode_cb_t)(void);

/* 异步数据收发结构 */
typedef struct tagACM_WR_ASYNC_INFO
{
    char* pVirAddr;
    char* pPhyAddr;
    unsigned int u32Size;
    void* pDrvPriv;
}ACM_WR_ASYNC_INFO;

/* ACM设备事件类型 */
typedef enum tagACM_EVT_E
{
    ACM_EVT_DEV_SUSPEND = 0,        /* 设备不可以进行读写(主要用于事件回调函数的状态) */
    ACM_EVT_DEV_READY = 1,          /* 设备可以进行读写(主要用于事件回调函数的状态) */
    ACM_EVT_DEV_BOTTOM
}ACM_EVT_E;

/* 读buffer信息 */
typedef struct tagACM_READ_BUFF_INFO
{
    unsigned int u32BuffSize;
    unsigned int u32BuffNum;
}ACM_READ_BUFF_INFO;


typedef struct tagNCM_PKT_S
{
    unsigned char *pBuffer;       /* buffer指针*/
    unsigned int  u32BufLen;      /* buffer长度 */
}NCM_PKT_S;

/* NCM设备类型枚举*/
typedef enum tagNCM_DEV_TYPE_E
{
    NCM_DEV_DATA_TYPE,      /* 数据通道类型，PS使用*/
    NCM_DEV_CTRL_TYPE       /* 控制通道，MSP传输AT命令使用*/
}NCM_DEV_TYPE_E;

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
    /* BEGIN: Modified by liumengcun, 2011-4-21 DTS2011042101113
       【BSP 新需求 USB NCM】PS需要底软提供NCM流控状态查询接口*/
    NCM_IOCTL_GET_FLOWCTRL_STATUS,           /* 0x13 查询NCM流控状态*/

    /* BEGIN: Modified by liumengcun, 2011-6-23 DTS2011062301762
       PS和MSP新需求，提供查询当前发包门限个数接口和NCM 挂起时回调函数增加NCM 设备ID参数*/
    NCM_IOCTL_GET_CUR_TX_MIN_NUM,              /* 0x14 获取当前发包个数阈值*/
    NCM_IOCTL_GET_CUR_TX_TIMEOUT,               /* 0x15 获取当前发包超时时间*/
    NCM_IOCTL_IPV6_DNS_NOTIF,              /*0x16 IPV6 DNS主动上报*/
    /* BEGIN: Modified by liumengcun, 2011-7-20 支持IPV6 DNS配置*/
    NCM_IOCTL_SET_IPV6_DNS,                     /* 0x16 配置IPV6 DNS*/
    /* BEGIN: Modified by liumengcun, 2011-8-10 MSP新需求*/
    NCM_IOCTL_CLEAR_IPV6_DNS,                     /* 0x17 清除IPV6 DNS在板端的缓存,param在此命令字没有意义，不填空指针即可*/
    NCM_IOCTL_GET_NCM_STATUS,                     /* 0x18 获取NCM网卡状态 enable:TRUE(1);disable:FALSE(0) */

    NCM_IOCTL_SET_ACCUMULATION_TIME,

    /* BEGIN: Modified by baoxianchun, 2012-5-17 GU PS 新需求*/
    NCM_IOCTL_SET_RX_MIN_NUM,        /*配置收包个数阈值*/
    NCM_IOCTL_SET_RX_TIMEOUT,        /*配置收包超时时间*/
    /* END: Modified by baoxianchun, 2012-5-17 GU PS 新需求*/

    NCM_IOCTL_REG_NDIS_RESP_STATUS_FUNC   /* NDIS通道AT命令状态处理回调函数 */
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

/* 包封装结构体,NCM_IOCTL_SET_PKT_ENCAP_INFO命令字对应参数结构体*/
typedef struct tagNCM_PKT_ENCAP_INFO_S
{
    int s32BufOft;      /* buf偏移量 */
    int s32LenOft;      /* len偏移量 */
    int s32NextOft;     /* next偏移量 */
}NCM_PKT_ENCAP_INFO_S;

/* AT命令回复数据指针及长度 NCM_IOCTL_AT_RESPONSE*/
typedef struct tagNCM_AT_RSP_S
{
    unsigned char* pu8AtAnswer;
    unsigned int u32Length;
} NCM_AT_RSP_S;
typedef struct tagNCM_IPV6_DNS_NTF_S
{
    unsigned char* pu8Ipv6DnsNtf;
    unsigned int u32Length;
} NCM_AT_IPV6_DNS_NTF_S;

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

/*  下传上传、下载包的各种统计信息，
    不发送给PC，被动等待PC的读取,NCM_IOCTL_SET_PKT_STATICS命令字对应参数结构*/
typedef struct tagNCM_IOCTL_PKT_STATISTICS_S
{
    unsigned int     u32TxOKCount;         /*发送包数*/
    unsigned int     u32RxOKCount;         /*接收包数*/
    unsigned int     u32TxErrCount;        /*发送错误*/
    unsigned int     u32RxErrCount;        /*接收错误*/
    unsigned int     u32TxOverFlowCount;   /*发送溢出丢包*/
    unsigned int     u32RxOverFlowCount;   /*接收溢出丢包*/
    unsigned int     u32CurrentTx;         /*发送速率*/
    unsigned int     u32CurrentRx;         /*接收速率*/
} NCM_IOCTL_PKT_STATISTICS_S;

/* BEGIN: Modified by liumengcun, 2011-7-20 IPV6 DNS配置结构,NCM_IOCTL_SET_IPV6_DNS对应参数结构*/
#define BSP_NCM_IPV6_DNS_LEN     32
 typedef struct tagNCM_IPV6DNS_S  /* 0x16 配置IPV6 DNS*/
 {
     unsigned char * pu8Ipv6DnsInfo;/* 32字节，低16字节表示primaryDNS；高16字节表示SecondaryDNS。*/
     unsigned int u32Length;
 } NCM_IPV6DNS_S;
typedef struct tagNCM_PKT_INFO_S
{
    unsigned int u32PsRcvPktNum;              /* 收包送到PS的包个数*/
    unsigned int u32RcvUnusedNum;             /* 收包不符合PS要求丢弃包个数*/
    unsigned int u32NcmSendPktNum;            /* 发包个数*/
}NCM_PKT_INFO_S;

struct sk_buff;
typedef void (*USB_IPS_MNTN_TRACE_CB_T)(struct sk_buff *skb,unsigned short usType);
extern unsigned int BSP_USB_RegIpsTraceCB(USB_IPS_MNTN_TRACE_CB_T pFunc);
#define DRV_USB_REG_IPS_TRACECB(x) BSP_USB_RegIpsTraceCB(x)

#endif

/*audio module*/
#define AUDIO_IOCTL_BASE                    (0x30000000)
#define IOCTL_AUDIO_VOICE_OPEN              (AUDIO_IOCTL_BASE+23)
#define IOCTL_AUDIO_VOICE_CLOSE             (AUDIO_IOCTL_BASE+24)

static inline int DRV_CODEC_OPEN(const char *devname, int flags, int mode)
{
    return 0;
}

static inline int DRV_CODEC_IOCTL(int devid, int cmd, int arg)
{
    return 0;
}

static inline int DRV_GET_CODEC_FUNC_STATUS(void)
{
    /*note: asic return 1,sft need to return 0*/
    return 1;
}

static inline int DRV_FILE_GET_DISKSPACE(const char *path,unsigned int *DskSpc,unsigned int *UsdSpc,  unsigned int *VldSpc)
{
    return 0;
}

/*mntn module*/
typedef int  (*OM_SAVE_FUNC)(int funcType, unsigned char *data, unsigned int* ulLength);

/****************************************************
Function:     BSP_MNTN_ExchOMSaveRegister
Description:  注册给底软的trace保存函数，用来在单板复位时，保存当前的信令和日志信息，先打桩，后续根据异常处理方案再做设计
Input:             NA;
Output:       NA;
Return:       0;
Others:       NA;
****************************************************/
static inline int DRV_SAVE_REGISTER(int funcType, OM_SAVE_FUNC *pFunc)
{
    return 0;
}

static inline int DRV_GET_FLASH_INFO(unsigned char * pFlashInfo, unsigned int ulLength)
{
    return 0;
}
static inline int DRV_ABB_SELFCHECK (void)
{
    return 0;
}

static inline int DRV_PMU_SELFCHECK (void)
{
    return 0;
}

static inline int DRV_I2C_SELFCHECK (void)
{
    return 0;
}

static inline int DRV_SPI_SELFCHECK (void)
{
    return 0;
}

/***************************************************************************
 * 函 数 名  : DRV_GET_RF_GLOCKSTATE
 * 功能描述  : 读取GSM RF锁定状态。
 * 输入参数  : 无。
 * 输出参数  : Status：存放锁定状态的输出值，
 *                  0：TX或者RX被锁定。
 *                  1：TX、RX都没有被锁定；
 * 返 回 值  : 0:  操作成功；
 *            -1： 操作失败。
 ****************************************************************************/
static inline int DRV_GET_RF_GLOCKSTATE(unsigned int *Status)
{
    return 0;
}


static inline int DRV_BOOTFLAG_CFG(unsigned int ulBootFlag)
{
    return 0;
}

static inline int DRV_GET_GPIO_INFO(unsigned char * pGpioInfo, unsigned long ulLength)
{
    return 0;
}

static inline int DRV_GET_HEAPINFO(unsigned int *allocSize, unsigned int *totalSize)
{
    return 0;
}

static inline int DRV_BACKUP_SYS_FILE(void)
{
    return 0;
}

#define DRV_LOG_INSTALL(fptr, fptr1, fptr2, fptr3, fptr4)     MDRV_OK

static inline int DRV_MNTN_GET_BATT_STATE(void)
{
    return 0;
}


static inline unsigned int BSP_CPU_GetTotalUtilize(void)
{
    return 0;
}


/*VERSIONINFO_I数据结构中版本字符串最大有效字符长度*/
#define VER_MAX_LENGTH                  30

typedef struct
{
    unsigned char CompId;              /* 组件号：参见COMP_TYPE */
    unsigned char CompVer[VER_MAX_LENGTH+1];         /* 最大版本长度 30 字符+ \0 */
}VERSIONINFO_I;

/*lmsp 在diag_common.h 中使用，不知道为什么*/
typedef enum{
     ADDRTYPE8BIT,
     ADDRTYPE16BIT,
     ADDRTYPE32BIT
}ENADDRTYPE;

/*taf used ,don't know why*/
enum SECURE_SUPPORT_STATUS_I
{
    SECURE_NOT_SUPPORT = 0,
    SECURE_SUPPORT = 1
};

/*LPS used,don't konw why begin*/
#ifndef PS_L2_UL_TRACE
#define PS_L2_UL_TRACE 0
#endif

#ifndef PS_L2_DL_TRACE
#define PS_L2_DL_TRACE 1
#endif

#define PROCESS_ENTER(pADDRESS)  do { } while (0)
#define PROCESS_EXIT(pADDRESS)   do { } while (0)


typedef struct tagBSP_OM_NET_S
{
    unsigned int u32NetRxStatOverFlow;       /* 接收FIFO溢出统计计数 */
    unsigned int u32NetRxStatPktErr;         /* 接收总错包计数 */
    unsigned int u32NetRxStatCrcErr;         /* 接收CRC错包计数 */
    unsigned int u32NetRxStatLenErr;         /* 接收无效长度包计数 */
    unsigned int u32NetRxNoBufInt;           /* 接收没有BUFFER中断计数 */
    unsigned int u32NetRxStopInt;            /* 接收停止中断计数 */
    unsigned int u32NetRxDescErr;            /* 接收描述符错误 */

    unsigned int u32NetTxStatUnderFlow;      /* 发送FIFO下溢统计计数 */
    unsigned int u32NetTxUnderFlowInt;       /* 发送FIFO下溢中断计数 */
    unsigned int u32NetTxStopInt;            /* 发送停止中断计数 */
    unsigned int u32NetTxDescErrPs;          /* 发送描述符错误(Ps) */
    unsigned int u32NetTxDescErrOs;          /* 发送描述符错误(Os) */
    unsigned int u32NetTxDescErrMsp;         /* 发送描述符错误(Msp) */

    unsigned int u32NetFatalBusErrInt;      /* 总线错误*/
}BSP_OM_NET_S;

static inline void BSP_OM_NET(BSP_OM_NET_S *pstNetOm)
{
    return ;
}

/*LPS used,don't konw why end*/



/*该接口待删除*/
/*****************************************************************************
 函 数 名  : DRV_MEM_READ
 功能描述  : 按32位宽度查询内存，输出4字节数据。可维可测，V7先打桩
 输入参数  : ulAddress：查询地址空间地址，地址需在内存范围内，否则返回-1。
 输出参数  : pulData：指向查询内容的指针。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int DRV_MEM_READ(unsigned int ulAddress, unsigned int* pulData);

#if 1  /*drv_timer.h*/
extern unsigned int omTimerGet(void);
#define DRV_GET_SLICE() omTimerGet()
#endif

#if 1  /*drv_pmu.h*/
/*****************************************************************************
 函 数 名  : DRV_GET_PMU_STATE
 功能描述  : 获取PMU模块开机方式、充电状态、电池电量、电池在位状态。
 输入参数  : 无。
 输出参数  : Pmu_State :开机方式、充电状态、电池电量、电池在位状态。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 注意事项　：该接口仅在PS的PC工程中使用，目前没有应用，暂保留。
*****************************************************************************/
extern unsigned int DRV_GET_PMU_STATE(void*  Pmu_State);
#endif

/*drv_mntn module*/
typedef enum tagMSP_PROC_ID_E
{
    OM_REQUEST_PROC = 0,
    OM_ADDSNTIME_PROC = 1,
    OM_PRINTF_WITH_MODULE = 2,
    OM_PRINTF = 3,

    OM_PRINTF_GET_MODULE_IDLEV = 4,
    OM_READ_NV_PROC = 5,
    OM_WRITE_NV_PROC = 6,
    OM_MNTN_ERRLOG = 7,

    MSP_PROC_REG_ID_MAX
}MSP_PROC_ID_E;

typedef void (*BSP_MspProc)(void);
#define EXCH_CB_NAME_SIZE           (32)
typedef struct
{
    char   aucName[EXCH_CB_NAME_SIZE];
    unsigned char *pucData;
    unsigned int  ulDataLen;
}cb_buf_t;

typedef int  (*exchCBReg)(cb_buf_t *);

/*liuyi++ 该接口在文档中未体现 ++*/
/*******************************************************************************
 函 数 名: DRV_EXCH_CUST_FUNC_REG
 功能描述: 临终遗言模块提供对外接口，供上层注册回调，用于复位时保存上层指定信息
 输入参数: cb 上层指定回调接口
 输出参数: 无
 返 回 值: 0-添加成功，其他-添加失败
 说明    :  pucData :指定记录信息地址，请注意不要指定栈等临时数据区，堆空间数据，
                     使用者自己维护，包括空间使用完，自己释放。建议全局变量。
            aucName :名称
            ulDataLen: 数据长度

返回值列表:
    CUST_REG_OK = 0,                        添加成功
    CUST_REG_PARM_NULL,                     入参为空
    CUST_REG_EXCH_NOT_READY,                EXCH模块尚未初始化
    CUST_REG_EXCH_REBOOT_CONTEXT,           已经进入复位流程
    CUST_REG_EXCH_QUEUE_NOT_INIT,           注册队列尚未初始化
    CUST_REG_EXCH_QUEUE_FULL,               队列已满
    CUST_REG_EXCH_ALREADY_IN_QUEUE,         重复注册
    CUST_REG_EXCH_MUTEX_REJECT,             MUTEX REJECT
    CUST_REG_EXCH_QUEUE_IN_ERR              入队列失败

请通过返回值定位解决错误

*******************************************************************************/
extern int DRV_EXCH_CUST_FUNC_REG(exchCBReg cb);
/*liuyi++ 该接口在文档中未体现 --*/

/*liuyi++ 该接口在文档中未体现*/
/*****************************************************************************
* 函 数 名  : DRV_MSP_PROC_REG
*
* 功能描述  : DRV提供给OM的注册函数
*
* 输入参数  : MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc
* 输出参数  : NA
*
* 返 回 值  : NA
*
* 其它说明  : 可维可测接口函数
*
*****************************************************************************/
extern void DRV_MSP_PROC_REG(MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc);
/*liuyi++ 该接口在文档中未体现--*/

/*drv*/
/*****************************************************************************
 函 数 名  : BSP_GUDSP_ShareAddrGet
 功能描述  : 获取物理层共享地址段的信息。
 输入参数  : 无。
 输出参数  : pulAddr：存放物理层共享地址段信息的缓存。
 返 回 值  : 无。
*****************************************************************************/
extern int BSP_GUDSP_ShareAddrGet(unsigned int * pulAddrInTcm, unsigned int * pulAddrInDdr, unsigned int * pulLength);
#define DRV_DSP_SHARE_ADDR_GET(pulAddrInTcm,pulAddrInDdr,pulLength)    BSP_GUDSP_ShareAddrGet(pulAddrInTcm,pulAddrInDdr,pulLength)

static inline int DRV_DSP_DRX_GPIO_VAL_SET(unsigned int  u32Data)
{
    return 0;
}

static inline int  NAND_GET_BAD_BLOCK(unsigned int *pNum, unsigned int **ppBadBlock)
{
    return -1;
}

static inline void  NAND_FREE_BAD_BLOCK_MEM(unsigned int* pBadBlock)
{
    return ;
}

/******************************************************************************
*
  函数名:   BSP_Sram_BackupInfoReg
  函数描述: 注册SRAM段备份恢复信息
  输入参数: pucSramAddr 注册的段在SRAM的加载地址
            ulSectLen   注册的段的字节大小，函数内部默认不做任何字节对齐处理
            ulNeedMulBck该段是否需要每次下电都做备份处理，一般启动之后可能数据
                        会变的段，例如:data段需要每次都备份最新内容，那么该参数
                        填写为1；而text段启动之后一直不变，故备份一次即可，减少
                        总线访问次数，该参数填写为0
            ulNeedCheck 恢复的数据是否需要校验，由于校验对性能影响较大，故该功能
                        参数目前留作后续扩展，暂不实现，传入值无效
  输出参数: None
  返回值:   BSP_OK      处理成功
            BSP_ERROR   处理失败
*******************************************************************************/
extern int BSP_SRAM_BackupInfoReg(unsigned char *pucSramAddr, unsigned long ulSectLen, unsigned long ulNeedMulBak, unsigned long ulNeedCheck);
#define DRV_SRAM_BACKUP_INFO_REG(pucSramAddr, ulSectLen, ulNeedMulBak, ulNeedCheck)  BSP_SRAM_BackupInfoReg(pucSramAddr, ulSectLen, ulNeedMulBak, ulNeedCheck)

#define NAND_MFU_NAME_MAX_LEN    16
#define NAND_DEV_SPEC_MAX_LEN    32

typedef struct
{
    unsigned int           MufId;                                         /* 厂商ID */
    unsigned char      aucMufName[NAND_MFU_NAME_MAX_LEN];             /* 厂商名称字符串 */
    unsigned int           DevId;                                         /* 设备ID */
    unsigned char      aucDevSpec[NAND_DEV_SPEC_MAX_LEN];             /* 设备规格字符串 */
}NAND_DEV_INFO_S;

/******************************************************************************
*
  函数名:       int nand_get_dev_info (NAND_DEV_INFO_S *pNandDevInfo)
  函数描述:     查询NAND设备相关信息：包括厂商ID、厂商名称、设备ID、设备规格
  输入参数:     无
  输出参数:     pNandDevInfo    存储NAND设备相关信息的结构体
  返回值:       0    : 查询成功
                负数 : 查询失败
*******************************************************************************/
static inline int NAND_GET_DEV_INFO(NAND_DEV_INFO_S *pNandDevInfo)
{
    return -1;
}

/*****************************************************************************
* 函 数 名  : BSP_IPM_FreeBspBuf
*
* 功能描述  : 释放内存接口
*
* 输入参数  : unsigned char *pBuf 需要释放的指针
*
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  :2011年1月27日   鲁婷  创建
*****************************************************************************/

static inline int DRV_GET_DLOAD_FLASHINFO(DLOAD_FLASH_STRU* pFlashInfo)
{
	return 0;
}

void MNTN_ERRLOG_REG_FUNC(MNTN_ERRLOGREGFUN pRegFunc);


#ifdef __cplusplus
}
#endif
#endif
