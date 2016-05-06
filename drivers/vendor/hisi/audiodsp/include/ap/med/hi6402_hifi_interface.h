/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hi6402_hifi_interface.h
  版 本 号   : 初稿
  作    者   : C00137131
  生成日期   : 2012年8月16日
  最近修改   :
  功能描述   : Hifi与DRV之间的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月16日
    作    者   : C00137131
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含

  notice:  不要包含任何其他头文件!!!
*****************************************************************************/


#ifndef __HI6402_HIFI_INTERFACE_H__
#define __HI6402_HIFI_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* AP侧Kernel音频驱动发送数据给hifi时的buff描述，bufAddr为总线地址，bufSize和dataSize单位byte */
#if 0                                                                           /*_H2ASN_Skip*/
#define DRV_SEND_DATA_STRU                                                      \
    VOS_UINT32                              uwBufAddr;                          \
    VOS_UINT32                              uwBufSize;                          \
    VOS_UINT32                              uwDataSize;
#else
#define DRV_SEND_DATA_STRU                                                      \
    unsigned long                           uwBufAddr;                          \
    unsigned long                           uwBufSize;                          \
    unsigned long                           uwDataSize;
#endif

#define HIFI_AUDIO_PCM_COMP_COEF_LEN_MAX    (128)
/*********************************************************
6402消息枚举
*********************************************************/
enum DSP_POWER_STATE_ENUM
{
    HIFI_POWER_ON = 0xA0,
    HIFI_POWER_CLK_ON = 0xB0,
    HIFI_POWER_CLK_OFF,
};

enum MLIB_PATH_ENUM
{
    MLIB_PATH_DATA_HOOK     = 0,
    MLIB_PATH_DEFAULT,
    MLIB_PATH_WAKEUP,
    MLIB_PATH_SMARTPA,
    MLIB_PATH_BUTT
};
typedef unsigned int MLIB_PATH_ENUM_UINT32;


enum MLIB_MODULE_ENUM
{
	MLIB_MODULE_DEFAULT     = 0,
	MLIB_MODULE_IVW,
	MLIB_MODULE_SWU,
	MLIB_MODULE_DSM,
	MLIB_MODULE_ELVIS,
	MLIB_MODULE_TSLICE,
	MLIB_MODULE_OEM,
	MLIB_MODULE_GOOGLE,
	MLIB_MODULE_DSM_STEREO,
	MLIB_MODULE_BUTT,

    MLIB_MODULE_BROADCAST   = 0xFFFFFFFF,
};
typedef unsigned int MLIB_MODULE_ENUM_UINT32;

enum APDSP_MSG_ENUM
{
    ID_AP_DSP_IF_OPEN          = 0xDD10,  /*AP 发给 DSP，端口开*/
    ID_AP_DSP_IF_CLOSE         = 0xDD11,  /*AP 发给 DSP，端口关*/
    ID_AP_DSP_PARAMETER_SET    = 0xDD12,  /*AP 发给 DSP，算法set*/
    ID_AP_DSP_PARAMETER_GET    = 0xDD13,  /*AP 发给 DSP，算法get*/
    ID_AP_DSP_OM               = 0xDD14,  /*AP 发给 DSP，配置勾取PCM或Log数据*/

    ID_AP_DSP_IF_ST_OPEN       = 0xDD15,  /*AP 发给 DSP，Sound Trigger端口开*/
    ID_AP_DSP_IF_ST_CLOSE      = 0xDD16,  /*AP 发给 DSP，Sound Trigger端口关*/

    ID_AP_DSP_FASTTRANS_OPEN   = 0XDD17,  /*AP 发给 DSP，快速数据上报开*/
    ID_AP_DSP_FASTTRANS_CLOSE  = 0XDD18,  /*AP 发给 DSP，快速数据上报关*/
    ID_AP_DSP_WAKEUP_TEST      = 0XDD19,  /*AP 发给 DSP，Sound Trigger唤醒测试*/

    ID_DSP_UPDATE_BUF          = 0xDD20,  /*DSP 音频播放数据更新中断消息*/
    ID_DSP_LOG_HOOK            = 0xDD21,  /*DSP 抓取log数据*/
    ID_DSP_UPDATE_FASTBUF      = 0XDD22,  /*DSP 语音唤醒快速上报通道*/
    ID_DSP_UPDATE_RECORDBUF    = 0XDD23,  /*DSP 语音唤醒普通录音上报*/
    ID_AP_DSP_MADTEST_START    = 0xDD31,  /*AP发给DSP 用于产线启动测试MAD*/
    ID_AP_DSP_MADTEST_STOP     = 0xDD32,  /*AP发给DSP 用于产线停止测试MAD*/
    ID_AP_DSP_UARTMODE         = 0xDD33,  /*AP发给DSP 用于设定当前UART模式和抓取点*/
    ID_AP_DSP_FASTMODE         = 0xDD34,  /*AP发给DSP 用于打开快速通道的消息*/
    ID_AP_IMGAE_DOWNLOAD       = 0xDD40,  /*AP 发给 DSP，镜像加载*/

    ID_FAULTINJECT             = 0xDDA0,
};

enum UART_MODE_ENUM
{
    UART_MODE_115200 = 0, /* for pc uart */
    UART_MODE_500K   = 1, /* for phone in mad mode */
    UART_MODE_6M     = 2, /* for phone in normal mode */
    UART_MODE_OFF    = 3, /* force writing log to 36K om buffer*/
};

typedef struct
{
    unsigned short  msgID;           /*语音唤醒快速通道设置*/
    unsigned short  fastTransEnable; /*语音唤醒快速通道使能标志*/
} FAST_TRANS_MSG_STRU;

typedef struct _PCM_IF_MSG_STRU
{
    unsigned int    uwIFId;         /* IF口 id    */
    unsigned int    uwIFDirect;     /* 数据传输方向,输入 输出 即输入又输出 */
    unsigned int    uwSampleRateIn; /* 输入采样率 */
    unsigned int    uwSampleRateOut;/* 输出采样率 */
    unsigned int    uwChannelCount; /* 声道数, 用来标识有效数据, 位宽固定32位, 26位有效 */
    unsigned int    uwDMASetId;     /* 组合id, 0 无组合  */
    unsigned int    ucResolution;    /* 音频流的有效比特率 16bit/24bit */

} PCM_IF_MSG_STRU;

typedef struct _PCM_PROCESS_DMA_MSG_STRU
{
   unsigned int     uwProcessId;    /* 场景 id    */
   unsigned int     uwIFCount;      /* 需要的IF口个数*/
   unsigned int     uwModuleID;     /* 模块ID*/
   PCM_IF_MSG_STRU  stIFCfgList[0]; /* if口参数列表,可变长度*/
} PCM_PROCESS_DMA_MSG_STRU;
/*****************************************************************************
 实体名称  : DSP_IF_OPEN_REQ_STRU
 功能描述  : 该消息打开IF通道
*****************************************************************************/
typedef struct
{
    unsigned short                          uhwMsgId;   /*ID_AP_DSP_IF_OPEN 0xDD10*/
    unsigned short                          uhwReserve;
    PCM_PROCESS_DMA_MSG_STRU                stProcessDMA;
} DSP_IF_OPEN_REQ_STRU;

typedef struct
{
    unsigned short                          uhwMsgId;   /*ID_AP_DSP_FASTTRANS_CONFIG 0xDD17*/
    unsigned short                          uhwReserve;
    int                                     swStatus;
} FAST_TRANS_CFG_REQ_STRU;


/* Mlib para control*/
typedef struct
{
    unsigned short  msgID;
    unsigned short  reserve;
    unsigned int    uwProcessID;      /* 场景 ID       */
    unsigned int    uwModuleID;       /* 模块Module ID */
    unsigned int    uwSize;           /* 参数大小      */
    unsigned char   aucData[0];       /* 参数起始地址  */
} MLIB_PARA_SET_REQ_STRU;

typedef struct
{
    unsigned short  msgID;
    unsigned short  reserve;
    unsigned int    uwProcessID;      /* 场景 ID       */
    unsigned int    uwModuleID;       /* 模块Module ID */
    unsigned int    uwSize;           /* 参数大小      */
} MLIB_PARA_GET_REQ_STRU;

typedef struct
{
    int result;
    unsigned char para_data[0];
} MLIB_PARA_GET_DATA;

/* OM control */
enum PCM_HOOK_POINT_ENUM{
    TRACK_LOG_NONE                 = 0x00000000,
    TRACK_LOG_MAINMIC              = 0x00000001,  /* 主mic数据      */
    TRACK_LOG_SUBMIC               = 0x00000002,  /* 副mic数据      */
    TRACK_LOG_THIRDMIC             = 0x00000004,  /* 三mic数据      */
    TRACK_LOG_FORTHMIC             = 0x00000008,  /* 四mic数据      */
    TRACK_LOG_UPLINK_AFTERPRO      = 0x00000010,  /* 上行音效处理后 */
    TRACK_LOG_UPLINK_AFTERCODE     = 0x00000020,  /* 上行编码后     */
    TRACK_LOG_DOWNLINK_AFTERPRO    = 0x00000100,  /* 下行音效处理后 */
    TRACK_LOG_DOWNLINK_AFTERCODE   = 0x00000200,  /* 下行解码后     */
    TRACK_LOG_DOWNLINK_BEFORECODE  = 0x00000400,  /* 下行解码前     */
    TRACK_LOG_SMARTPA_IN           = 0x00001000,  /* smartpa输入    */
    TRACK_LOG_SMARTPA_OUT          = 0x00002000,  /* smartpa输出    */
    TRACK_LOG_SMARTPA_I            = 0x00004000,  /* smartpa I信号  */
    TRACK_LOG_SMARTPA_V            = 0x00008000,  /* smartpa V信号  */
    TRACK_LOG_AEC                  = 0x00010000,  /* AEC参考信号    */
    TRACK_LOG_SOUNDTRIGGER_KEYWORD = 0x00020000,  /* 语音唤醒唤醒词数据 */
    TRACK_LOG_UPDATA_LEFT          = 0X00100000,  /* updata中算法前左声道数据 */
    TRACK_LOG_UPDATA_RIGHT         = 0X00200000,  /* updata中算法前右声道数据 */
    TRACK_LOG_ALGORITHM_FAILURE    = 0x00400000,  /* 算法异常 */
};

typedef struct
{
    unsigned short  uhwMsgId;         /* OM控制消息ID  0xDD14*/
    unsigned short  uhwReserve;
    unsigned int    uwHookType;       /* 抓取类型: 0-HOOK_OFF, 1-HOOK_LOG, 2-HOOK_LOG_PCM*/
    unsigned int    uwOutputMode;     /* 输出模式：0-Uart、1-dspif */
    unsigned int    uwPortNum;        /* 输出模式为dspif时的dsp if端口号 */
    unsigned int    uwForceOutPutLog; /* 强制输出log数据：0-不强制、1-强制输出 */
    unsigned int    uwHookPoints;     /* 数据勾取点 */
    unsigned int    uwLogMode;        /* 类型为LOG数据时的LOG打印模式：0-直通模式、1-缓存模式 */
    unsigned int    uwLogLevel;       /* 打印级别：0-Error、1-Warning、2-Infor、3-Debug */
} OM_CTRL_BLOCK_STRU;

/*****************************************************************************
 实体名称  : FW_DOWNLOAD_STRU
 功能描述  : 镜像加载命令结构，misc和hal层共用，不涉及hifi
*****************************************************************************/
typedef struct
{
    unsigned short                           uhwMsgId;
    unsigned short                           uhwReserve;
    char                                     chwname[50];
} FW_DOWNLOAD_STRU;

typedef struct
{
    unsigned short  uhwMsgId;/*MAD语音唤醒老化测试*/
    unsigned short  uhwReserve;
} MAD_TEST_STRU;

typedef struct
{
    unsigned short  uhwMsgId;   /*0xDD33,AP发给DSP 用于设定当前UART模式*/
    unsigned short  uhwReserve;
    unsigned int    uwUartMode; /*0--115200, 1--500K, 2--6M*/
} UARTMODE_STRU;

struct fault_inject {
    unsigned short  uhwMsgId;
    unsigned short  uhwReserve;
    unsigned int    fault_type;
};

typedef unsigned short  APDSP_MSG_ENUM_UINT16;
#define AUDIO_PLAY_DEBUG_OPEN_RESERVE (0x0000)

/* OM状态信息中目前抓取类型*/
enum HOOK_TYPE_ENUM
{
    HOOK_OFF = 0,
    HOOK_LOG = 1,
    HOOK_LOG_PCM = 2,
};

/* OM状态信息中目前抓取的数据类型*/
enum HOOK_FORCE_OUTPUT_LOG_ENUM
{
    HOOK_DEFUALT = 0,
    HOOK_FORCE_OUTPUT_LOG = 1,
};

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hi6402_hifi_interface.h */
