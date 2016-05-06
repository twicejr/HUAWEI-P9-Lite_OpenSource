/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Phy_Lapdm_Interface.h
  版 本 号   : 初稿
  作    者   : 方剑
  生成日期   : 2007年9月5日
  最近修改   :
  功能描述   : 该头文件是协议栈Lapdm和物理层之间的接口文件。
  函数列表   :
  修改历史   :
  1.日    期   : 2007年9月5日
    作    者   : 张稚彬
    修改内容   : 创建文件

******************************************************************************/
#ifndef _PHY_LAPDM_INTERFACE_H_
#define _PHY_LAPDM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#pragma pack(1)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* L1 与 Lapdm 之间的原语 */
#define ID_PH_CONNECT_IND                           0x7301
#define ID_PH_READY_TO_SEND                         0x7302
#define ID_PH_EMPTY_FRAME                           0x3701
#define ID_PH_DATA_REQ                              0x3702
#define ID_PH_DATA_IND                              0x7303

/* 信道类型定义 */
#define L2_CHANNEL_SACCH                            0x0001
#define L2_CHANNEL_SDCCH                            0x0002
#define L2_CHANNEL_FACCH_H                          0x0003
#define L2_CHANNEL_FACCH_F                          0x0004
#define L2_CHANNEL_CCCH                             0x0005
#define L2_CHANNEL_NBCCH                            0x0006
#define L2_CHANNEL_PCH                              0x0007
#define L2_CHANNEL_EPCH                             0x0008
#define L2_CHANNEL_CBCH                             0x0009
#define L2_CHANNEL_EBCCH                            0x000a

/* 枚举类型定义 */

/*******************************************************************************
 枚举名   : DL_ACCH_REPEATED_ENUM
 协议表格 :
 枚举说明 : ACCH_REPEATED_CAPABILITY
*******************************************************************************/
enum DL_REPEAT_SA_FLAG_ENUM
{
    DL_NOT_REPEAT_SA_FLAG  = 0,
    DL_REPEAT_SA_FLAG      = 1,
    DL_REPEAT_SA_FLAG_BUTT
};
typedef VOS_UINT16 DL_REPEAT_SA_FLAG_ENUM_UINT16;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgID;
    VOS_UINT16                      usChanType;
} PH_CONNECT_IND;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgID;
    VOS_UINT16                      usL2ChanType;   	/* 信令信道类型 */
    DL_REPEAT_SA_FLAG_ENUM_UINT16   usRepeatedSaFlg;    /* 是否需要重复发送SACCH，当usL2ChanType为L2_CHANNEL_SACCH时使用
                                                           usRepeatedSaCycFlg 为1时表示发送重复的SACCH,为0时发送正常SACCH */
    VOS_UINT16                      usRsv;              /* 保留，用于四字节对其 */
    VOS_UINT32                      ulRptFN;            /* 消息发送时的帧号 */
} PH_READY_TO_SEND;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgID;
    VOS_UINT16                      usL2ChanType;     	/* 信令信道类型 */
} PH_EMPTY_FRAME;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgID;
    VOS_UINT16                      usL2ChanType;
    VOS_UINT16                      usRepeatedSaFlg;    /* 是否为重复上行SACCH块指示 */
                                                        /* usRepeatedSaFlg 为1时表示发送重复上行SA块,为0时发送正常SA块 */
    VOS_UINT16                      usRsv;              /* 保留，用于四字节对其 */
    VOS_UINT16                      ausL2Frame[12];     /* 23x8比特的数据 */
} PH_DATA_REQ;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgID;            /* 原语类型 */
    VOS_UINT16                      usFreqInfo;         /* BCCH的频点,对应GSM的信道号 */
    VOS_UINT16                      usL2ChanType;       /* 信道的类型,对应各种信令信道 */
    VOS_UINT16                      usErrFlag;          /* L1是否译码正确,0表示译码正确,1表示错误 */
    VOS_UINT16                      usTC;               /* ( FN div 51 ) % 8 */
    VOS_UINT16                      usCCCHLevel;        /* CCCH信道的接收电平, (-120+316~-15+316)dbm */
    VOS_UINT32                      ulFN;

    /* usRepeatedSaFlg 需要结合usErrFlag使用, usErrFlag = 0，usRepeatedSaFlg = 1,
       说明该数据块是要丢弃的数据块;usErrFlag = 1，usRepeatedSaFlg = 1,说明该数据块用于T200计算
       usRepeatedSaFlg = 0，该标志不使用  */
    VOS_UINT16                      usRepeatedFaFlg;    /*  是否为重复FACCH块指示,如果CRC正确，并且前一块FACCH间隔8帧，
                                                            CRC也正确，并且两块FACCH内容相同，则该标志置为1，否则置为0 ;
                                                            8帧或者9帧之前受到过FACCH，如果CRC错误，则该标志置为1，否则置为0*/

    VOS_UINT16                      usHarqFlg;          /* 是否为联合译码结果,1:联合译码(Harq) 0:正常译码结果 */
    VOS_UINT16                      ausL2Frame[12];     /* 上报的L2帧数据, 有23X8比特的数据 */
} PH_DATA_IND ;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* end of _PHY_LAPDM_INTERFACE_H_ */

