/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CallImsaInterface.h
  版 本 号   : 初稿
  作    者   : 文露涛 00176964
  生成日期   : 2013年6月27日
  功能描述   : CALL和IMSA接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月14日
    作    者   : 文露涛 00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef  CALL_IMSA_INTERFACE_H
#define  CALL_IMSA_INTERFACE_H

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnCallApi.h"
#include "TafClientApi.h"
#include "SpmImsaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#define   CALL_IMSA_MAX_ENTITY_NUM                          7

#define   IMSA_CALL_MSG_SYNC_MAX_NUM                        2

#define   IMSA_CALL_DTMF_REQ_MSG_MAX_NUM                    16
/*****************************************************************************
  2 枚举定义
*****************************************************************************/
/*****************************************************************************
枚举名    : CALL_IMSA_SRVCC_STATUS_ENUM
结构说明  : SRVCC状态枚举信息
  1.日    期   : 2013年9月11日
    作    者   : w00176964
    修改内容   : 新建
*****************************************************************************/

enum CALL_IMSA_SRVCC_STATUS_ENUM
{
    CALL_IMSA_SRVCC_STATUS_START        = 0,     /* SRVCC开始 */
    CALL_IMSA_SRVCC_STATUS_SUCCESS      = 1,     /* SRVCC成功 */
    CALL_IMSA_SRVCC_STATUS_FAIL         = 2,     /* SRVCC失败 */
    CALL_IMSA_SRVCC_STATUS_BUTT
};
typedef VOS_UINT32  CALL_IMSA_SRVCC_STATUS_ENUM_UINT32;

/*****************************************************************************
枚举名    : CALL_IMSA_SRVCC_CALL_STATE_ENUM
结构说明  : SRVCC过程中的呼叫状态枚举信息
  1.日    期   : 2013年10月14日
    作    者   : w00176964
    修改内容   : 新建
*****************************************************************************/
enum CALL_IMSA_SRVCC_CALL_STATE_ENUM
{
    CALL_IMSA_SRVCC_CALL_DIALING,                                                          /* dialing (MO call) */
    CALL_IMSA_SRVCC_CALL_ALERTING,                                                         /* alerting (MO call) */
    CALL_IMSA_SRVCC_CALL_ACTVING,                                                          /* activing --这个状态协议规定要求GU下重传connect消息 */
    CALL_IMSA_SRVCC_CALL_ACTIVE,                                                           /* active */
    CALL_IMSA_SRVCC_CALL_HELD,                                                             /* held */
    CALL_IMSA_SRVCC_CALL_INCOMING,                                                         /* incoming (MT call) */
    CALL_IMSA_SRVCC_CALL_WAITING,                                                          /* waiting (MT call) */
    CALL_IMSA_SRVCC_CALL_BUTT
};
typedef VOS_UINT8  CALL_IMSA_SRVCC_CALL_STATE_ENUM_UINT8;

/*****************************************************************************
枚举名    : CALL_IMSA_MSG_TYPE_ENUM
结构说明  : CALL 和IMSA的之间的消息

  1.日    期   : 2013年10月14日
    作    者   : W00176964
    修改内容   : 定义CALL和IMSA之间的接口消息
*****************************************************************************/

enum CALL_IMSA_MSG_TYPE_ENUM
{
    ID_CALL_IMSA_SRVCC_STATUS_NOTIFY        = TAF_CALL_IMSA_MSG_BASE,            /* _H2ASN_MsgChoice CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU */

    ID_IMSA_CALL_SRVCC_CALL_INFO_NOTIFY     = TAF_CALL_IMSA_MSG_BASE+0x100,      /* _H2ASN_MsgChoice CALL_IMSA_SRVCC_CALL_INFO_NOTIFY_STRU */

    ID_IMSA_CALL_MSG_SYNC_IND,                                                   /* _H2ASN_MsgChoice IMSA_CALL_MSG_SYNC_IND_STRU */

    ID_IMSA_CALL_CCWA_CAP_NOTIFY,                                                /* _H2ASN_MsgChoice IMSA_CALL_CCWA_CAP_NOTIFY_STRU */

    ID_CALL_IMSA_MSG_TYPE_BUTT
};
typedef  VOS_UINT32  CALL_IMSA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  3 类型定义
****************************************************************************/
/*****************************************************************************
 结构名    : IMSA_CALL_DTMF_REQ_INFO_STRU
 结构说明  : DTMF缓存的请求信息结构

  1.日    期   : 2013年12月23日
    作    者   : y00245242
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    MN_CALL_ID_T                        CallId;
    VOS_CHAR                            cKey;                                   /* DTMF Key */
    VOS_UINT16                          usOnLength;                             /* DTMF持续时间，0: 代表停止DTMF */
    VOS_UINT16                          usOffLength;                            /* stop dtmf req和start dtmf req时间间隔，单位ms*/
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   opId;
    VOS_UINT8                           aucReserved1[3];
}IMSA_CALL_DTMF_REQ_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_CALL_DTMF_BUFF_STRU
 结构说明  : SRVCC发生前缓存的DTMF buffer结构

  1.日    期   : 2013年12月23日
    作    者   : y00245242
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNum;
    VOS_UINT8                           aucReserve[3];
    IMSA_CALL_DTMF_REQ_INFO_STRU        astDtmf[IMSA_CALL_DTMF_REQ_MSG_MAX_NUM];
}TAF_CALL_DTMF_BUFF_STRU;


/*****************************************************************************
 结构名    : CALL_IMSA_SRVCC_CALL_INFO_STRU
 结构说明  : IMSA模块同步过来的srvcc时的呼叫实体信息
 TI flag (octet 1) (参考协议24007 TI描述章节)
   Bit
   8
   0  The message is sent from the side that originates the TI
   1  The message is sent to the side that originates the TI

   TIO (octet 1)
   Bits
   7 6 5
   0 0 0  TI value 0
   0 0 1               1
   0 1 0               2
   0 1 1               3
   1 0 0                   4
   1 0 1               5
   1 1 0                   6
   1 1 1  The TI value is given by the TIE in octet 2

  TIE  (octet 2)
  Bits 7-1
  0000000
  0000001
  0000010
  0000011
  0000100
  0000101
  0000110 Reserved.
  All other values    The TI value is the binary representation of TIE
  Where bit 7 is the most significant bit
  And bit 1 is the least significant bit

  1.日    期   : 2013年9月11日
    作    者   : w00176964
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                                          clientId;
    MN_OPERATION_ID_T                                       opId;
    VOS_UINT8                                               ucCallId;
    VOS_UINT8                                               ucTi;                      /* TI信息，保护TI FLAG和TI两项，具体格式参考上面描述 */
    CALL_IMSA_SRVCC_CALL_STATE_ENUM_UINT8                   enCallState;               /* IMSA同步过来的IMS域下的呼叫状态 */
    MN_CALL_MODE_ENUM_U8                                    enCallMode;
    MN_CALL_MPTY_STATE_ENUM_U8                              enMptyState;
    MN_CALL_DIR_ENUM_U8                                     enCallDir;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;
    VOS_UINT8                                               ucLocalAlertedFlag; /* IMS域是否需要进行本地振铃 */
    VOS_UINT8                                               ucEConferenceFlag;  /* 用于标识通话是否是增强型多方通话: VOS_TRUE: 增强型多方通话 VOS_FALSE: 非增强型多方通话 */
    MN_CALL_BCD_NUM_STRU                                    stCallNumber;
    MN_CALL_CALLED_NUM_STRU                                 stCalledNumber;
    MN_CALL_BCD_NUM_STRU                                    stRedirectNumber;
    MN_CALL_BCD_NUM_STRU                                    stConnectNumber;
}CALL_IMSA_SRVCC_CALL_INFO_STRU;

/*****************************************************************************
 结构名    : CALL_IMSA_SRVCC_CALL_INFO_NOTIFY_STRU
 结构说明  : IMSA模块通知的SRVCC的呼叫信息

  1.日    期   : 2013年9月11日
    作    者   : w00176964
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           ucStartedHifiFlag;
    VOS_UINT8                           aucReserve[2];
    CALL_IMSA_SRVCC_CALL_INFO_STRU      astCallInfo[CALL_IMSA_MAX_ENTITY_NUM];
    TAF_CALL_DTMF_BUFF_STRU             stDtmfBuffInfo;
}CALL_IMSA_SRVCC_CALL_INFO_NOTIFY_STRU;


/*****************************************************************************
 结构名    : CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU
 结构说明  : CALL模块通知IMSA模块SRVCC信息

  1.日    期   : 2013年9月11日
    作    者   : w00176964
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    CALL_IMSA_SRVCC_STATUS_ENUM_UINT32  enSrvccStatus;
}CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU;

typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export CALL_IMSA_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CALL_IMSA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}CALL_IMSA_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CALL_IMSA_INTERFACE_MSG_DATA        stMsgData;
} CallImsaInterface_MSG;

/*****************************************************************************
 结构名    : IMSA_CALL_MSG_UNION
 结构说明  : 消息请求类型

  1.日    期   : 2013年12月14日
    作    者   : y00245242
    修改内容   : 新增结构
*****************************************************************************/
typedef union
{
    SPM_IMSA_CALL_ORIG_REQ_STRU         stOrigReq;
    SPM_IMSA_CALL_SUPS_CMD_REQ_STRU     stSupsCmd;
    SPM_IMSA_CALL_START_DTMF_REQ_STRU   stStartDtmf;
    SPM_IMSA_CALL_STOP_DTMF_REQ_STRU    stStopDtmf;
}IMSA_CALL_MSG_UNION;

/*****************************************************************************
 结构名    : IMSA_CALL_MSG_SYNC_IND_STRU
 结构说明  : IMSA模块通知CALL模块同步未发送的消息

  1.日    期   : 2013年12月14日
    作    者   : y00245242
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           aucReserve[3];
    IMSA_CALL_MSG_UNION                 astMsgArray[IMSA_CALL_MSG_SYNC_MAX_NUM];
}IMSA_CALL_MSG_SYNC_IND_STRU;

/*****************************************************************************
 结构名    : IMSA_CALL_CCWA_CAP_NOTIFY_STRU
 结构说明  : IMSA模块通知CALL模块呼叫等待(CCWAI)的配置

  1.日    期   : 2015年8月24日
    作    者   : n00269697
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucCcwaCap;                              /* 0:不支持ccwa; 1:支持ccwa */
    VOS_UINT8                           aucReserve[3];
}IMSA_CALL_CCWA_CAP_NOTIFY_STRU;
/*****************************************************************************
  4 宏定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
/*
  IMSA提供的API，供TAF CALL模块调用，该函数中会有内存的分配和释放。
  CALL模块通知IMSA SRVCC启动时，CALL模块调用该函数，用于获取SRVCC过程中转入CS域的呼叫信息。
  入参内存由CALL分配，pstCallInfo指向的内存大小为CALL_IMSA_MAX_ENTITY_NUM*sizeof(CALL_IMSA_SRVCC_CALL_INFO_STRU)
  返回值VOS_FALSE, VOS_TRUE
*/
extern VOS_UINT32 CALL_IMSA_GetSrvccCallInfo(VOS_UINT8* pucCallNum,
                                  CALL_IMSA_SRVCC_CALL_INFO_STRU* pstCallInfo);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* CALL_IMSA_INTERFACE_H */

