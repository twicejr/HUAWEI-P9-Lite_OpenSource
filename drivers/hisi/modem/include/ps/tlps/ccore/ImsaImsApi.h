/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaImsApi.h
    Description : IMSA与IMS协议栈函数接口头文件
    History     :
      1.sunbing 00049683    2013-07-15  Draft Enact
      2.sunbing 00049683    2013-10-10  调整部分API名称

******************************************************************************/

#ifndef __IMSAIMSAPI_H__
#define __IMSAIMSAPI_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
enum IMSA_VOICE_CODEC_ENUM
{
    IMSA_VOICE_CODEC_AMR_NB = 0,
    IMSA_VOICE_CODEC_EFR,
    IMSA_VOICE_CODEC_FR,
    IMSA_VOICE_CODEC_HR,
    IMSA_VOICE_CODEC_AMR_NB2,
    IMSA_VOICE_CODEC_AMR_WB,
    IMSA_VOICE_CODEC_G711,
    IMSA_VOICE_CODEC_BUTT
};
typedef unsigned short IMSA_VOICE_CODEC_ENUM_UINT16;

enum IMSA_CODEC_AMR_TYPE_TX_ENUM
{
    IMSA_CODEC_AMR_TYPE_TX_SPEECH_GOOD   = 0,
    IMSA_CODEC_AMR_TYPE_TX_SID_FIRST,
    IMSA_CODEC_AMR_TYPE_TX_SID_UPDATE,
    IMSA_CODEC_AMR_TYPE_TX_NO_DATA,
    IMSA_CODEC_AMR_TYPE_TX_SPEECH_DEGRADED,
    IMSA_CODEC_AMR_TYPE_TX_SPEECH_BAD,
    IMSA_CODEC_AMR_TYPE_TX_SID_BAD,
    IMSA_CODEC_AMR_TYPE_TX_ONSET,
    IMSA_CODEC_AMR_TYPE_TX_BUTT
};
typedef unsigned short IMSA_CODEC_AMR_TYPE_TX_ENUM_UINT16;

/* TIMER */
enum IMSA_TIMER_PRECISION_ENUM
{
    IMSA_TIMER_PRECISION_0   = 0,
    IMSA_TIMER_PRECISION_5   = 5,
    IMSA_TIMER_PRECISION_10   = 10,
    IMSA_TIMER_PRECISION_20   = 20,
    IMSA_TIMER_PRECISION_30   = 30,
    IMSA_TIMER_PRECISION_40   = 40,
    IMSA_TIMER_PRECISION_50   = 50,
    IMSA_TIMER_PRECISION_60   = 60,
    IMSA_TIMER_PRECISION_70   = 70,
    IMSA_TIMER_PRECISION_80   = 80,
    IMSA_TIMER_PRECISION_90   = 90,
    IMSA_TIMER_PRECISION_100   = 100,
    IMSA_TIMER_NO_PRECISION,
    IMSA_TIMER_PRECISION_BUTT
};
typedef unsigned int IMSA_TIMER_PRECISION_ENUM_UINT32;


typedef enum
{
    IMSA_IMS_TIMER_NAME_XXX = 500,
    IMSA_IMS_TIMER_NAME_BUTT
}IMSA_IMS_TIMER_NAME_ENUM;

typedef void (*TIMER_FUNC)(unsigned int ulParam, unsigned int ulTimerName);

typedef struct
{
    unsigned int                     ulLen;          /*定时器时长，单位millisecond*/
    unsigned int                     ulTimerName;    /*定时器名，标识定时器，采用IMSA_IMS_TIMER_NAME_ENUM枚举值*/
    unsigned int                     ulParam;        /*定时器附加参数*/
    unsigned char                    ucMode;         /*定时器工作模式，0单次定时器,1循环定时器，超时自动重启*/
    unsigned char                    ucRever[3];
    IMSA_TIMER_PRECISION_ENUM_UINT32 enPrecision;    /*定时器精度，表示可容忍的定时误差百分比*/
    TIMER_FUNC                       TimeOutRoutine; /*回调函数，定时器超时后调用，回调函数的参数为ulTimerName和ulTimerName*/
}IMSA_TIMER_PARA_STRU;


typedef struct
{
    IMSA_VOICE_CODEC_ENUM_UINT16  enCodecType;   /*当前语音帧的codec类型,0表示AMR,5表示WB AMR,6表示G711*/
    unsigned short                usDtxEnable;   /*下帧的编码DTX是否启用，0表示不启动，1表示启用*/
    unsigned short                usRateMode;    /*下帧的编码编码速率，值为0到8，AMR和AMR_WB时有效*/
    unsigned short                usErrorFlag;   /*本帧是否是lost packet,0表示否，1表示是*/
    unsigned short                usFrameType;   /* 下行本帧的FrameType */
    unsigned short                usQualityIdx;  /* Quality indification */
    unsigned short                usSN;          /* 包序列号 */
    unsigned short                usReserve;
    unsigned long                 ulTS;          /* 包时间戳 */
    unsigned long                 ulSsrc;        /* synchronization source */
}IMSA_RX_VOICE_PARA_STRU;


typedef struct
{
    IMSA_CODEC_AMR_TYPE_TX_ENUM_UINT16  usStatus;
    unsigned short                      usFrameType;  /* 上行本帧的FrameType */
}IMSA_TX_VOICE_PARA_STRU;



/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/**
 * \brief 海思提供的API，用于IMS协议栈打电话启动HIFI或者语音编码格式改变时调用，
 *        在该API中，IMSA会通知HIFI启动编解码，并且设置codec类型
 * @param[in]   enCodeType     语音数据codec类型
 * @retval 0成功，1失败
 */
extern unsigned int IMSA_StartVoiceDsp
(
    IMSA_VOICE_CODEC_ENUM_UINT16    enCodecType,
    unsigned long                   ulPacketTime,
    unsigned long                   ulSendBitrate
);

/**
 * \brief 海思提供的API，用于IMS协议栈在挂断所有电话后调用
 *        在该API中，IMSA会通知HIFI,停止语音编解码
 * @retval 0成功，1失败
 */
extern unsigned int IMSA_StopVoiceDsp(void);

/**
 * \brief 海思提供的API，用于IMS协议栈收到下行数据后调用，
 *        将语音数据发送给HIFI，HIFI收到后进行译码
 * @param[in]   pstVoicePara   参数信息存放地址，该数据空间由调用者释放
 * @param[in]   pusData        语音数据存放地址，空间大小为160byte，该数据空间由调用者释放
 * @retval 0成功，1失败
 */
extern unsigned int IMSA_Send2HifiRxVoiceData(const IMSA_RX_VOICE_PARA_STRU *pstVoicePara,
                                                        const unsigned short *pusData);
/**
 * \brief IMS协议栈提供给海思的API，
 *        HIFI完成上行语音编码后，发送码流给IMSA，IMSA收到后调用该API，将数据发给IMS协议栈
 * @param[in]   pstVoicePara   参数信息存放地址，该数据空间由调用者(海思)释放
 * @param[in]   pusData        语音数据存放地址，空间大小为160byte，该数据空间由调用者(海思)释放
 * @retval 无
 */
extern void IMSA_Send2ImsTxVoiceData(const IMSA_TX_VOICE_PARA_STRU *pstVoicePara,
                                              const unsigned short *pusData);

/**
 * \brief 海思提供给API，用于IMS协议栈给IMSA发送消息时调用
 *
 * @param[in]   pstOutputEvent    事件存放地址，该数据空间由调用者释放，类型为IMSA_IMS_OUTPUT_EVENT_STRU
 * @retval 0成功，1失败
 */
extern unsigned int IMSA_Send2ImsaMsg(void *pstOutputEvent);

/**
 * \brief 海思提供给的API，用于IMS协议栈启动定时器
 *
 * @param[in]    pstTimerPara： 定时器参数存放地址，该数据空间由调用者释放
 * @retval 0成功，1失败
 */
extern unsigned int IMSA_ImsStartTimer(const IMSA_TIMER_PARA_STRU  *pstTimerPara);


/**
 * \brief 海思提供的API，用于IMS协议栈停止定时器
 *
 * @param[in]    ulTimerName： 定时器名称
 * @retval 0成功，1失败
 */
extern unsigned int IMSA_ImsStopTimer(unsigned int  ulTimerName);

/**
 * \brief IMS协议栈提供给海思的API，用于IMS协议栈的初始化
 * @retval 0失败，1成功
 */
extern unsigned int IMSA_ImsInit(void);


/**
 * \brief IMS协议栈提供给海思的API，用于给IMS协议栈发送事件
 *
 * @param[in]    pstInputEvent： INPUT事件指针 类型为IMSA_IMS_INPUT_EVENT_STRU
 * @retval 0失败，1成功
 */
extern unsigned int IMSA_WriteImsEvent(void *pstInputEvent);

/**
 * \brief IMS协议栈提供给海思的API，用于IMS协议栈提供Srvcc过程中转入CS域的呼叫列表
 *
 * @param[in]    pstSrvccCallList： 类型为IMSA_IMS_SRVCC_CALL_LIST_STRU，内存由海思分配
 * @retval 0失败，1成功
 */
extern unsigned int IMSA_ImsWriteSrvccCallList(void *pstSrvccCallList);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaImsApi.h */




