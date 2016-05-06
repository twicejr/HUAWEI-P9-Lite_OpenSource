#ifndef __MDRV_CCORE_SCI_H__
#define __MDRV_CCORE_SCI_H__
#ifdef __cplusplus
extern "C"
{
#endif



#define SCI_RECORD_ATR_LEN      (40)
#define SCI_RECORD_REG_LEN      (36)
#define SCI_RECORD_DATA_CNT     (20)
/*14 = 1(收发标志)+4(时间戳)+1(len)+8(数据)*/
#define SCI_SIGLE_DATA_LEN      (14)
#define SCI_RECORD_DATA_LEN     (SCI_RECORD_DATA_CNT * SCI_SIGLE_DATA_LEN)
#define SCI_RECORD_EVENT_CNT    (80)
#define SCI_RECORD_EVENT_LEN    (SCI_RECORD_EVENT_CNT * 4 )


typedef void (*OMSCIFUNCPTR)(unsigned int ulVal);

typedef enum
{
    SIM_CARD_OUT = 0,
    SIM_CARD_IN  = 1
} SCI_DETECT_STATE_E;

typedef enum
{
	WARM_RESET = 0,     /* warm reset */
	COLD_RESET = 1,     /* cold reset */
	RESET_MODE_BUTTOM
}RESET_MODE_E;

   
/*for protocol mode*/
typedef enum
{
	T0_PROTOCOL_MODE = 0,          /*T=0*/
	T1_PROTOCOL_MODE = 1,          /*T=1*/
	PROTOCOL_MODE_BUTTOM
}PROTOCOL_MODE_E;

/*for EDC mode*/
typedef enum
{
	T1_ERR_DETECT_MODE_LRC = 0,     /*LRC*/
	T1_ERR_DETECT_MODE_CRC = 1,     /*CRC*/
	T1_ERR_DETECT_MODE_BUTTOM
}T1_ERR_DETECT_MODE_E;	

/*for dsda*/
typedef enum
{
    RF_ID0 = 0,
    RF_ID1 = 1,
    RF_ID2 = 2,
    RF_ID_BUTTOM
}RF_ID_E;

	/*for ATR info*/
typedef struct
{
	PROTOCOL_MODE_E         Tbyte;
	unsigned int            valIFSC;
	unsigned int            valIFSD;
	T1_ERR_DETECT_MODE_E    errDetectMode;
    unsigned int            tckLen;
}SCI_ATRINFO_S;

/*  SIM  硬件异常*/
typedef enum tagSCI_HW_ABNORMAL_E
{
    SCI_HW_STATE_OK  = 0,                   /*HW  OK*/
    SCI_HW_STATE_ATRSTOUT,                  /*ATR receive start timeout  */
    SCI_HW_STATE_ATRDTOUT,                  /*between ATR TIME OUT*/
    SCI_HW_STATE_TXERR,                     /*TX ERROR*/
    SCI_HW_STATE_CHTOUT,                    /*between char timeout*/
    SCI_HW_STATE_RORI,                      /*receive overrun interrupt*/

    SCI_HW_STATE_BUTT                       /* Butt*/
} SCI_HW_ABNORMAL_E;


/*for sci record info*/
typedef struct stSciRecordInfo{
    unsigned short            cardClass;                          /*卡电压类型:1800或3000*/
    unsigned short            ATRlen;                             /*ATR数据实际长度*/
    unsigned char             ATRData[SCI_RECORD_ATR_LEN];        /*ATR数据记录，不超过40个字节*/
    SCI_HW_ABNORMAL_E         enSciHwStatus;                      /*记录sci硬件状态*/
    unsigned int              SciRegData[SCI_RECORD_REG_LEN];     /*SCI所有寄存器记录*/
    unsigned char             SimRecordData[SCI_RECORD_DATA_LEN]; /*和卡交互的最后20条数据，每条不超过9个字节，同时需记录4字节时间戳*/
    unsigned int              SciEvent[SCI_RECORD_EVENT_LEN];     /*SCI 底层事件最后80条记录*/
}SCI_RECORD_INFO_S;


typedef enum
{
	SCI_CLK_STATE_LOW = 0,        /* 协议侧指示停低*/
	SCI_CLK_STATE_HIGH = 1,       /*协议侧指示停高*/
	SCI_CLK_STATE_UNSUPPORTED = 2,/*协议侧指示不支持*/
	SCI_CLK_STATE_BUTT
}SCI_CLK_STOP_TYPE_E;

/*  SIM  state*/
typedef enum tagSCI_CARD_STATE_E
{
    SCI_CARD_STATE_READY = 0,               /* Ready */
    SCI_CARD_STATE_NOCARD,                  /* No card */
    SCI_CARD_STATE_BUSY,                    /* In initialization*/
    SCI_CARD_STATE_BUTT                     /* Butt*/
} SCI_CARD_STATE_E;

/*下面两个定义后续移到mdrv_sci.h文件*/
typedef enum 
{
    SCI_ID_0 = 0,
    SCI_ID_1 = 1,
    SCI_ID_2 = 2,
    SCI_ID_BUTT
}SCI_SLOT;
    
/*for SCI_LOG  mode*/
typedef enum
{
    SCI_LOG_RESET_FAIL           = 0,     /*复位失败*/
    SCI_LOG_PROTECT_RESET_SUCC   = 1,     /*保护性复位成功*/
    SCI_LOG_PROTECT_RESET_FAIL   = 2,     /*保护性复位失败*/
    SCI_LOG_NO_DATA              = 3,     /*没有数据返回*/
    SCI_LOG_BUF_OVER             = 4,     /*数据接收溢出*/
    SCI_LOG_VOL_SWITCH_FAIL      = 5,     /*USIM电压切换失败*/
    SCI_LOG_BUTT
}SCI_LOG_MODE;


	/********************************************************************************
	 *  函 数 名  : mdrv_sci_get_cardstatus
	 *  功能描述  : 本接口用于获得卡当前的状态，目前LTE提供接口参数类型不一致
	 *  输入参数  : 无。
	 *  输出参数  :
	 *  返 回 值  : 0:  卡处于Ready；
	 *             -1：卡未处于Ready。
	 *                    注意事项  ：有效调用BSP_SCI_Reset()函数后，再调用此函数。
	 *********************************************************************************/
     int mdrv_sci_get_cardstatus(void);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_reset
	 *
	 * 功能描述  : 本接口用于复位SCI（Smart Card Interface）驱动和USIM（Universal
	 *           Subscriber Identity Module）卡
	 *
	 * 输入参数  : void
	 * 输出参数  : 无
	 *
	 * 返 回 值  : OK  复位成功
	 *
	 * 修改记录  : Yangzhi create
	 *
	 *****************************************************************************/
	int mdrv_sci_reset(RESET_MODE_E rstMode);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_send_data
	 *
	 * 功能描述  : 本接口用于发送一段数据到USIM卡
	 *
	 * 输入参数  : unsigned int u32DataLength 发送数据的有效长度。取值范围1～256，单位为字节
	 *             unsigned char *pu8DataBuffer 发送数据所在内存的首地址，如是动态分配，调用接口
	 *                                   后不能立即释放，依赖于硬件发完数据
	 * 输出参数  : 无
	 *
	 * 返 回 值  : OK
	 *           BSP_ERR_SCI_NOTINIT
	 *           BSP_ERR_SCI_INVALIDPARA
	 *           BSP_ERR_SCI_DISABLED
	 *           BSP_ERR_SCI_NOCARD
	 *           BSP_ERR_SCI_NODATA
	 *
	 * 修改记录  :
	 *
	 *****************************************************************************/
	int mdrv_sci_send_data(unsigned int u32DataLength, unsigned char * pu8DataBuffer);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_recv
	 *
	 * 功能描述  : 本接口用于USIM Manager读取来自SCI Driver的卡返回数据
	 *             该接口为阻塞接口，只有SCI接收到足够的数据量后才会返回；
	 *             该接口的超时门限为1s
	 *
	 * 输入参数  : unsigned int u32DataLength USIM Manager欲从SCI Driver读取的数据长度。
	 * 输出参数  : unsigned char *pu8DataBuffer USIM Manager指定的Buffer，SCI Driver将数据拷贝到本Buffer。
	 * 返 回 值  : OK
	 *             BSP_ERR_SCI_NOTINIT
	 *             BSP_ERR_SCI_INVALIDPARA
	 *
	 * 修改记录  : Yangzhi create
	 *
	 *****************************************************************************/
	int mdrv_sci_recv(unsigned int u32DataLength, unsigned char * pu8DataBuffer);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_get_atr
	 *
	 * 功能描述  : 本接口用于将Driver层缓存的ATR数据和数据个数返回给USIM Manager层
	 *
	 * 输入参数  : void
	 * 输出参数  : unsigned long *u8DataLength  Driver读取的ATR数据长度，返回给USIM Manager。
	 *                                   取值范围0～32，单位是字节
	 *           unsigned char *pu8ATR          USIM Manager指定的Buffer，SCI Driver将ATR
	 *                                   数据拷贝到本Buffer。一般为操作系统函数动态分配
	 *                                   或者静态分配的地址
	 *
	 *
	 * 返 回 值  : OK
	 *          BSP_ERR_SCI_NOTINIT
	 *          BSP_ERR_SCI_INVALIDPARA
	 *
	 * 修改记录  : Yangzhi create
	 *
	 *****************************************************************************/
	int mdrv_sci_get_atr(unsigned long * u32DataLength, unsigned char * pu8ATR,SCI_ATRINFO_S* stSCIATRInfo);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_switch_class
	 *
	 * 功能描述  : 本接口用于支持PS对卡的电压类型进行切换，从1.8V切换到3V
	 *
	 * 输入参数  : void
	 * 输出参数  : 无
	 *
	 * 返 回 值  :  OK    当前电压不是最高的，进行电压切换操作
	 *           BSP_ERR_SCI_CURRENT_STATE_ERR 切换失败 current SCI driver state is ready/rx/tx
	 *           BSP_ERR_SCI_VLTG_HIGHEST   当前电压已经是最高电压，没有进行电压切换
	 *           BSP_ERR_SCI_NOTINIT
	 *           BSP_ERR_SCI_CURRENT_VLTG_ERR 当前电压值异常（非class B或者C）
	 *
	 * 修改记录  :
	 *
	 *****************************************************************************/
	int  mdrv_sci_switch_class(void);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_stop_tm
	 *
	 * 功能描述  : 本接口用于支持PS关闭SIM卡时钟
	 *
	 * 输入参数  :
	 *           SCI_CLK_STOP_TYPE_E enTimeStopCfg 时钟停止模式
	 *
	 * 输出参数  : 无
	 *
	 * 返 回 值  : OK - successful completion
	 *               ERROR - failed
	 *               BSP_ERR_SCI_NOTINIT
	 *               BSP_ERR_SCI_INVALIDPARA - invalid mode specified
	 *               BSP_ERR_SCI_UNSUPPORTED - not support such a operation
	 * 修改记录  :
	 *
	 *****************************************************************************/
	int mdrv_sci_stop_tm(SCI_CLK_STOP_TYPE_E enTimeStopCfg);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_deact
	 *
	 * 功能描述  : 本接口用于对SIM卡的去激活操作
	 *
	 * 输入参数  : 无
	 *
	 * 输出参数  : 无
	 *
	 * 返 回 值  : OK
	 *             BSP_ERR_SCI_NOTINIT
	 * 修改记录  :
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_deact(void);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_get_clkstat
	 *
	 * 功能描述  : 本接口用于获取当前SIM卡时钟状态 (v8 打桩返回0)
	 *
	 * 输入参数  : unsigned int *pu32SciClkStatus   变量指针，用于返回SIM卡时钟状态：
	 *                                       0：时钟已打开；
	 *                                       1：时钟停止
	 * 输出参数  : 无
	 *
	 * 返 回 值  : OK    操作成功
	 *             BSP_ERR_SCI_INVALIDPARA
	 * 修改记录  :
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_get_clkstat(unsigned int * pu32SciClkStatus);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_get_clkfreq
	 *
	 * 功能描述  : 本接口用于获取当前SIM卡时钟频率
	 *
	 * 输入参数  : 无
	 *
	 * 输出参数  : unsigned long *pLen   时钟频率数据的长度
	 *             unsigned char        *pBuf   时钟频率数据
	 * 返 回 值  : OK    操作成功
	 *             BSP_ERR_SCI_INVALIDPARA
	 * 修改记录  :
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_get_clkfreq(unsigned long * pLen,unsigned char * pBuf);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_get_baudrate
	 *
	 * 功能描述  : 本接口用于获取当前SIM卡时钟频率
	 *
	 * 输入参数  : 无
	 *
	 * 输出参数  : unsigned long *pLen   波特率数据的长度
	 *             unsigned char i      *pBuf   波特率数据
	 *
	 * 返 回 值  : OK    操作成功
	 *             BSP_ERR_SCI_INVALIDPARA
	 * 修改记录  :
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_get_baudrate(unsigned long * pLen, unsigned char * pBuf);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_get_parameter
	 *
	 * 功能描述  : 本接口用于获取当前SIM卡的PCSC相关参数
	 *
	 * 输入参数  : 无
	 *
	 * 输出参数  : unsigned char *pBuf    PCSC相关参数
	 *
	 * 返 回 值  : OK    操作成功
	 *             BSP_ERR_SCI_INVALIDPARA
	 * 修改记录  :
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_get_parameter(unsigned char * pBuf);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_get_errno
	 *
	 * 功能描述  : 本接口获取接口调用返回的错误码
	 * 输入参数  :  无
	 * 输出参数  :  无
	 *
	 * 返 回 值  : 错误码
	 *
	 * 修改记录  :
	 *
	 *****************************************************************************/
	int mdrv_sci_get_errno(void);

	/*****************************************************************************
	 *  函 数 名  : mdrv_sci_save_recorddata
	 *  功能描述  : 本接口用于获取当前SIM卡交互数据。属于异常处理模块，V7先打桩
	 *  输入参数  : 无。
	 *  输出参数  : 无
	 *  返 回 值  : na
	 *  注意事项  ：
	 ******************************************************************************/
	void mdrv_sci_save_recorddata(SCI_LOG_MODE log_mode);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_register_callback
	 *
	 * 功能描述  : 本接口用于注册OAM的回调函数
	 *
	 * 输入参数  : omSciFuncPtr
	 * 输出参数  : 无
	 *
	 * 返 回 值  : NA
	 *
	 * 修改记录  :
	 *
	 *****************************************************************************/
	void mdrv_sci_register_callback(OMSCIFUNCPTR omSciFuncPtr);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_recv_all
	 *
	 * 功能描述  : 本接口用于USIM Manager在读数超时的时候，调用本函数，
	 *             读取接收数据缓冲中的所有数据
	 *
	 * 输入参数  : 无
	 * 输出参数  : unsigned int *u32DataLength Driver读取的数据长度，返回给USIM Manager。
	 *                                取值范围1～256，单位是字节
	 *             unsigned char  *pu8DataBuffer USIM Manager指定的Buffer，SCI Driver将
	 *                                数据拷贝到本Buffer
	 *
	 * 返 回 值  : OK
	 *          BSP_ERR_SCI_NOTINIT
	 *          BSP_ERR_SCI_INVALIDPARA
	 *
	 * 修改记录  : Yangzhi create
	 *
	 *****************************************************************************/
	unsigned int mdrv_sci_recv_all(unsigned int *u32DataLength,unsigned char * pu8DataBuffer);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_show_voltage
	 *
	 * 功能描述  : 本接口用于显示当前SIM卡接口电压
	 *
	 * 输入参数  : 无
	 * 输出参数  :unsigned int * pu32Vltgval 当前电压
	 *
	 * 返 回 值  : OK
	 *          BSP_ERR_SCI_NOTINIT
	 *          BSP_ERR_SCI_INVALIDPARA
	 *
	 * 修改记录  : Yangzhi create
	 *
	 *****************************************************************************/
	unsigned int  mdrv_sci_show_voltage(unsigned int* pu32Vltgval);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_set_bwt
	 *
	 * 功能描述  : 本接口用于配置块等待时间
	 *
	 * 输入参数  : unsigned int nBWT:  配置超时时间为BWT的nBWT倍
	 *
	 * 输出参数  : 无
	 *
	 * 返 回 值  : OK/ERROR
	 * 修改记录  : 2013年10月15日   liuyi  creat
	 *
	 *****************************************************************************/
	int mdrv_sci_set_bwt(unsigned int nBWT);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_switch_protocol
	 *
	 * 功能描述  : 本接口用于通知底软进行T=0和T=1协议类型切换
	 *
	 * 输入参数  : RESET_MODE_E enSIMProtocolMode:需要切换为的协议类型
	 *
	 * 输出参数  : 无
	 *
	 * 返 回 值  : OK/ERROR
	 * 修改记录  : 2013年10月15日   liuyi  creat
	 *
	 *****************************************************************************/
	int mdrv_sci_switch_protocol(PROTOCOL_MODE_E enSIMProtocolMode);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_rcv_blk
	 * 功能描述  : 本接口用于在T=1时USIM Manager读取来自SCI Driver的卡返回数据；
	 *             如果出现BWT超时，在数据读取时返回一个超时的值SCI_TIMEOUT
	 *
	 * 输入参数  : 无
	 * 输出参数  : unsigned char  *pu8Data USIM Manager指定的Buffer，SCI Driver将数据拷贝到本Buffer。
	 *             unsigned int *pulLength SCI Driver接收到的数据长度。
	 *
	 * 返 回 值  : OK : 0
	 *             ERROR : -1
	 *             SCI_TIMEOUT : 1
	 *
	 * 修改记录  : 2013年10月15日   liuyi  creat
	 *
	 *****************************************************************************/
	int mdrv_sci_rcv_blk(unsigned char *pu8Data,unsigned int *pulLength);

	/*****************************************************************************
	 * 函 数 名  : mdrv_sci_read_recordlog
	 *
	 * 功能描述  : 本接口获取sim卡异常时定位信息
	 * 输入参数  : pucDataBuff: 获取定位信息的buffer
	 *             ulMaxLength: 最大值，判断使用
	 *
	 * 返 回 值  : pulLength: 获取数据长度
	 *
	 *
	 * 返 回 值  : 无
	 *
	 * 修改记录  :
	 *
	 *****************************************************************************/
	int  mdrv_sci_read_recordlog(unsigned char *pucDataBuff, unsigned int * pulLength, unsigned int ulMaxLength);

    /*****************************************************************************
	 * 函 数 名  : mdrv_sci_slot_switch
	 *
	 * 功能描述  : 切换卡与卡槽的对应关系
	 * 输入参数  : sci_slot0 卡槽0期望的状态
	 *                           sci_slot1 卡槽1期望的状态
	 *
	 * 返 回 值  : 切换结果
	 *
	 *
	 * 返 回 值  : 无
	 *
	 * 修改记录  :
	 *
	 *****************************************************************************/
    int mdrv_sci_slot_switch(SCI_SLOT sci_slot0,SCI_SLOT sci_slot1,SCI_SLOT sci_slot2);

    /*****************************************************************************
	 * 函 数 名  : mdrv_sci_get_slot_state
	 *
	 * 功能描述  : 获取卡槽的对应关系
	 * 输入参数  : sci_slot0 卡槽0的状态
	 *                           sci_slot1 卡槽1的状态
	 *
	 * 返 回 值  : 切换结果
	 *
	 *
	 * 返 回 值  : 无
	 *
	 * 修改记录  :
	 *
	 *****************************************************************************/

    int mdrv_sci_get_slot_state(SCI_SLOT* sci_slot0,SCI_SLOT* sci_slot1,SCI_SLOT* sci_slot2);

#ifdef __cplusplus
}
#endif

#endif

