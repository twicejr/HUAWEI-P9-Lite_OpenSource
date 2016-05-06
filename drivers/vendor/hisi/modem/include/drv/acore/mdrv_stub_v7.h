

#ifndef __MDRV_ACORE_STUB_V7_H__
#define __MDRV_ACORE_STUB_V7_H__
#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
 * 函 数 名  : BSP_MALLOC
 *
 * 功能描述  : BSP 动态内存分配
 *
 * 输入参数  : sz: 分配的大小(byte)
 *             flags: 内存属性(暂不使用,预留)
 * 输出参数  : 无
 * 返 回 值  : 分配出来的内存指针
 *****************************************************************************/
static inline void* BSP_MALLOC(unsigned int u32Size, MEM_POOL_TYPE enFlags) {
    return 0;
}

/*****************************************************************************
 * 函 数 名  : BSP_FREE
 *
 * 功能描述  : BSP 动态内存释放
 *
 * 输入参数  : ptr: 动态内存指针
 * 输出参数  : 无
 * 返 回 值  : 无
 *****************************************************************************/
static inline void  BSP_FREE(void* pMem) {
}

/*****************************************************************
Function: free_mem_size_get
Description:
    get mem size
Input:
    N/A
Output:
    N/A
Return:
    free mem size
*******************************************************************/
static inline unsigned int FREE_MEM_SIZE_GET(void)
{
    return 0;
}

static inline int BSP_DLOAD_GetDloadType(void)
{
    return 1;
}

/*liuyi++ only for nas marenkun temp*/

/*****************************************************************************
 Function   : BSP_PWC_SetTimer4WakeSrc
 Description: 设置timer4作为唤醒源
 Input      :
 Return     : void
 Other      :
*****************************************************************************/
static inline void BSP_PWC_SetTimer4WakeSrc(void)
{
    return;
}


/*****************************************************************************
 Function   : BSP_PWC_DelTimer4WakeSrc
 Description: 设置timer4不作为唤醒源
 Input      :
            :
 Return     : void
 Other      :
*****************************************************************************/
static inline void BSP_PWC_DelTimer4WakeSrc(void)
{
    return;
}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_SLEEPVOTE_LOCK
 功能描述  : 外设禁止睡眠投票接口。
 输入参数  : enClientId:PWC_CLIENT_ID_E
 输出参数  : None
 返 回 值  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
static inline unsigned int  DRV_PWRCTRL_SLEEPVOTE_LOCK(PWC_CLIENT_ID_E enClientId)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_SLEEPVOTE_UNLOCK
 功能描述  : 外设允许睡眠投票接口。
 输入参数  : enClientId:PWC_CLIENT_ID_E
 输出参数  : None
 返 回 值  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
static inline unsigned int  DRV_PWRCTRL_SLEEPVOTE_UNLOCK(PWC_CLIENT_ID_E enClientId)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_PWRCTRL_StandbyStateCcpu/BSP_PWRCTRL_StandbyStateAcpu
 功能描述  : AT^PSTANDBY
 输入参数  :
 输出参数  :
 返回值：
*****************************************************************************/
static inline unsigned int DRV_PWRCTRL_STANDBYSTATEACPU(unsigned int ulStandbyTime, unsigned int ulSwitchtime)
{
    return 0;
}

/*dload begin*/

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
static inline int DRV_UPGRADE_NV_SET_RESULT(int status)
{
    return 0;
}

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
static inline int DRV_NV_FILE_SEC_CHECK(char * pnvFilePath)
{
    return 0;
}

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
static inline int DRV_NVBACKUP_READ(unsigned char *pRamAddr, unsigned int len)
{
    return 0;
}

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

static inline int DRV_NVBACKUP_WRITE(unsigned char *pRamAddr, unsigned int len)
{
    return 0;
}





#endif


#define UART_IOCTL_GET_RD_BUFF       0x7F001011
#define UART_IOCTL_SET_READ_CB       0x7F001001

typedef enum
{
    WWAN_WCDMA    = 1,/*WCDMA模式*/
    WWAN_CDMA    = 2  /*CDMA模式*/
}NDIS_WWAN_MODE;

/*管脚信号的定义*/
#define IO_CTRL_FC                      (0x02)
#define IO_CTRL_DSR                     (0x20)
#define IO_CTRL_DTR                     (0x01)
#define IO_CTRL_RFR                     (0x04)
#define IO_CTRL_CTS                     (0x10)
#define IO_CTRL_RI                      (0x40)
#define IO_CTRL_DCD                     (0x80)

#define DRV_GPIO_USB_SWITCH     200
#define DRV_GPIO_HIGH           1
#define DRV_GPIO_LOW            0

#define AT_USB_SWITCH_SET_VBUS_INVALID          2

/* 设备枚举最大端口个数 */
#define DYNAMIC_PID_MAX_PORT_NUM        17

/* NV项50091结构，代表设备将要枚举的端口形态 */
typedef struct
{
    unsigned int ulStatus;
    unsigned char aucFirstPortStyle[DYNAMIC_PID_MAX_PORT_NUM];  /* 设备切换前端口形态 */
    unsigned char aucRewindPortStyle[DYNAMIC_PID_MAX_PORT_NUM]; /* 设备切换后端口形态 */
    unsigned char reserved[22];
}DRV_DYNAMIC_PID_TYPE_STRU;

typedef void(* USB_NET_DEV_SWITCH_GATEWAY)(void);

static inline int DRV_OS_STATUS_SWITCH(int enable)
{
    return 0;
}

static inline int DRV_GET_LINUXSYSTYPE(void)
{
    return -1;
}

static inline unsigned int DRV_SET_PORT_QUIRY(DRV_DYNAMIC_PID_TYPE_STRU *pstDynamicPidType)
{
    return 0;
}

static inline int DRV_USB_NAS_SWITCH_GATEWAY_REGFUNC(USB_NET_DEV_SWITCH_GATEWAY switchGwMode)
{
    return 0;
}

static inline unsigned int DRV_GET_U2DIAG_DEFVALUE(void)
{
    return 0;
}

static inline int DRV_GET_DIAG_MODE_VALUE(unsigned char *pucDialmode,
                                          unsigned char *pucCdcSpec)
{
    return 0;
}

static inline int DRV_USB_PHY_SWITCH_SET(unsigned char ucValue)
{
    return 0;
}

static inline int DRV_USB_PORT_TYPE_VALID_CHECK(unsigned char *pucPortType,
                                                unsigned int ulPortNum)
{
    return 0;
}

static inline int DRV_UDIAG_VALUE_CHECK(unsigned int DiagValue)
{
    return 0;
}

static inline int DRV_U2DIAG_VALUE_CHECK(unsigned int DiagValue)
{
    return 0;
}

static inline unsigned char DRV_GET_PORT_MODE(char*PsBuffer, unsigned int*Length)
{
    return 0;
}

static inline int DRV_SET_PID(unsigned char u2diagValue)
{
    return 0;
}

static inline int DRV_GPIO_SET(unsigned char ucGroup, unsigned char ucPin, unsigned char ucValue)
{
    return 0;
}

static inline void DRV_AT_SETAPPDAILMODE(unsigned int ulStatus)
{
    return;
}
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
static inline unsigned int BSP_MNTN_ProductTypeGet(void)
{
	return 0;
}
#define DRV_PRODUCT_TYPE_GET()   BSP_MNTN_ProductTypeGet()

static inline int DRV_SDMMC_GET_STATUS(void)
{
    return 0;
}

/*om use begin*/
/*VERSIONINFO_I数据结构中版本字符串最大有效字符长度*/
#define VER_MAX_LENGTH                  30

typedef struct
{
    unsigned char CompId;              /* 组件号：参见COMP_TYPE */
    unsigned char CompVer[VER_MAX_LENGTH+1];         /* 最大版本长度 30 字符+ \0 */
}VERSIONINFO_I;

typedef enum{
    ADDRTYPE8BIT,
    ADDRTYPE16BIT,
    ADDRTYPE32BIT
}ENADDRTYPE;

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

/*om use end*/

/*taf used*/
enum SECURE_ENABLE_STATUS_I
{
    SECURE_DISABLE = 0,
    SECURE_ENABLE = 1
};

static inline int DRV_FILE_GET_DISKSPACE(const char *path,unsigned int *DskSpc,unsigned int *UsdSpc,  unsigned int *VldSpc)
{
    return 0;
}
/*liuyi--*/

#if 1  /*drv_timer.h*/
extern unsigned int omTimerGet(void);
#define DRV_GET_SLICE() omTimerGet()
#endif

#if 1  /*drv_oled.h*/

/*****************************************************************************
*  Function:  DRV_OLED_CLEAR_WHOLE_SCREEN
*  Description: oled clear *
*  Called By:AP
*  Table Accessed:
*  Table Updated:
*  Input:
*         N/A
*  Output:
*         N/A
*  Return:
*         N/A
*****************************************************************************/
extern void DRV_OLED_CLEAR_WHOLE_SCREEN(void);

/*****************************************************************************
*  Function:  DRV_OLED_UPDATE_STATE_DISPLAY
*  Description: oled display right or not right  *
*  Called By:AP
*  Table Accessed:
*  Table Updated:
*  Input:
*         N/A
*  Output:
*         N/A
*  Return:
*         N/A
*****************************************************************************/
extern  void DRV_OLED_UPDATE_STATE_DISPLAY(int UpdateStatus);

/*****************************************************************************
 函 数 名  : DRV_OLED_UPDATE_DISPLAY
 功能描述  : SD卡烧片版本升级，OLED显示
 输入参数  : BOOL UpdateStatus
 输出参数  : 无。
 返回值：   无
 其它:  升级成功，NV备份完成后调用该函数打勾
        升级失败后调用该函数打叉
*****************************************************************************/
extern void DRV_OLED_UPDATE_DISPLAY(int UpdateStatus);

/*****************************************************************************
 函 数 名  : DRV_OLED_STRING_DISPLAY
 功能描述  : oled字符串显示函数
 输入参数  :
 *           要显示字符串的起始坐标
 *           要显示的字符串
 输出参数  : none
 返 回 值  : void
*****************************************************************************/
extern void DRV_OLED_STRING_DISPLAY(unsigned char ucX, unsigned char ucY, unsigned char *pucStr);

#endif

#if 1  /*drv_nve.h*/
#define BSP_NVE_NAME_LENGTH          8       /*NV name maximum length*/
#define BSP_NVE_NV_DATA_SIZE        104     /*NV data maximum length*/

#define BSP_NV_READ                 1       /*NV read  operation*/
#define BSP_NV_WRITE                0       /*NV write operation*/

typedef struct nve_info_stru {
	unsigned int nv_operation;              /*0-write,1-read*/
	unsigned int nv_number;                 /*NV number you want to visit*/
	char nv_name[BSP_NVE_NAME_LENGTH];
	unsigned int valid_size;
	unsigned char nv_data[BSP_NVE_NV_DATA_SIZE];
}NVE_INFO_S;

/*****************************************************************************
* 函 数 名  : DRV_NVE_ACCESS
*
* 功能描述  : 访问LINUX NVE
*
* 输入参数  : nve  ID
*
* 输出参数  : 无
*
* 返 回 值  : OK& ERROR
*
* 修改记录 :  2013年6月27日  v1.00  yuanqinshun  创建
*****************************************************************************/
int DRV_NVE_ACCESS(NVE_INFO_S *nve);
#endif

#if 1  /*drv_nv.h*/
/*****************************************************************************
 函 数 名  : DRV_COPY_NVUSE_TO_NVBACKUP
 功能描述  : 将NV从使用区拷贝到备份区
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int，0成功，其它失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月21日
    作    者   : 杨诚 y00186965
    修改内容   : 新生成函数

*****************************************************************************/
extern int DRV_COPY_NVUSE_TO_NVBACKUP ( void );


/*****************************************************************************
 函 数 名  : DRV_COPY_NVUPGRADE_TO_NVUSE
 功能描述  : 将NV从升级区拷贝到使用区
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int，0成功，其它失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月21日
    作    者   : 杨诚 y00186965
    修改内容   : 新生成函数

*****************************************************************************/
extern int DRV_COPY_NVUPGRADE_TO_NVUSE( void );
#endif

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
#define DRV_MSP_PROC_REG(eFuncID, pFunc)
/*liuyi++ 该接口在文档中未体现--*/


/************************* 底软不用结构体(后续删除) ***************************/

/*TCP/IP协议栈可维可测捕获的消息标识*/
enum IPS_MNTN_TRACE_IP_MSG_TYPE_ENUM
{
    /* IP 数据包可维可测上报 */
    ID_IPS_TRACE_IP_ADS_UL                  = 0xD030,
    ID_IPS_TRACE_IP_ADS_DL                  = 0xD031,
    ID_IPS_TRACE_IP_USB_UL                  = 0xD032,
    ID_IPS_TRACE_IP_USB_DL                  = 0xD033,

    ID_IPS_TRACE_IP_MSG_TYPE_BUTT
};

static inline unsigned long USB_ETH_DrvSetHostAssembleParam(unsigned long ulHostOutTimeout)
{
    return 0;
}

static inline unsigned long USB_ETH_DrvSetDeviceAssembleParam(
    unsigned long ulEthTxMinNum,
    unsigned long ulEthTxTimeout,
    unsigned long ulEthRxMinNum,
    unsigned long ulEthRxTimeout)
{
    return 0;
}

static inline unsigned int DRV_USB_GET_AVAILABLE_PORT_TYPE(unsigned char *pucPortType,
                            unsigned int *pulPortNum, unsigned int ulPortMax)
{
    return 0;
}

static inline int USB_otg_switch_get(unsigned char *pucValue)
{
    return 0;
}
#define DRV_USB_PHY_SWITCH_GET(value) USB_otg_switch_get(value)
#define AT_USB_SWITCH_SET_VBUS_VALID            1
#define AT_USB_SWITCH_SET_VBUS_INVALID          2
#define USB_SWITCH_ON       1
#define USB_SWITCH_OFF      0


typedef void (*HSIC_UDI_ENABLE_CB_T)(void);
static inline unsigned int BSP_HSIC_RegUdiEnableCB(HSIC_UDI_ENABLE_CB_T pFunc)
{
    return 0;
}
#define DRV_HSIC_REGUDI_ENABLECB(x) BSP_HSIC_RegUdiEnableCB(x)

typedef void (*HSIC_UDI_DISABLE_CB_T)(void);
static inline unsigned int BSP_HSIC_RegUdiDisableCB(HSIC_UDI_DISABLE_CB_T pFunc)
{
    return 0;
}
#define DRV_HSIC_REGUDI_DISABLECB(x) BSP_HSIC_RegUdiDisableCB(x)

static inline unsigned int BSP_GetHsicEnumStatus(void)
{
    return 0;
}
#define DRV_GET_HSIC_ENUM_STATUS() BSP_GetHsicEnumStatus()


/************************* 底软不用结构体 END *********************************/

//struct sk_buff;
typedef void (*USB_IPS_MNTN_TRACE_CB_T)(struct sk_buff *skb,unsigned short usType);
static inline unsigned int DRV_USB_REG_IPS_TRACECB(USB_IPS_MNTN_TRACE_CB_T pFunc)
{
    if (!pFunc)
    {
        return 1;
    }

    return 0;
}

unsigned int DRV_UTRACE_START(unsigned char * pData);
unsigned int DRV_UTRACE_TERMINATE(unsigned char * pData);

#ifdef __cplusplus
}
#endif
#endif
