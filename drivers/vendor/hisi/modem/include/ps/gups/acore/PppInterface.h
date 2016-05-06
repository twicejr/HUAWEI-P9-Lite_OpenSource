

#ifndef __PPP_INTERFACE_H__
#define __PPP_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 其他头文件包含
******************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "PsTypeDef.h"
#if (VOS_WIN32 == VOS_OS_VER) || (OSA_CPU_ACPU == VOS_OSA_CPU)
#include "ImmInterface.h"
#include "AdsDeviceInterface.h"
#endif
/******************************************************************************
  2 宏定义
******************************************************************************/
/*系统最多需要的PPP ID的数目 */
#define PPP_MAX_ID_NUM                      (1)

/*RABID相关*/
#define PPP_INVALID_RABID                   (0xFF)

/*PPPID*/
#define PPP_INVLAID_PPP_ID                  (0)


#define AUTHLEN                             (100)    /* Size of authname/authkey(porting from BSD, not alter) */
#define PASSWORDLEN                         (100)    /* Size of authname/authkey(define by fanzhibin) */
#define CHAPCHALLENGELEN                    (48)     /* Maximum chap challenge(porting from BSD, not alter) */
#define MD5DIGESTSIZE                       (16)     /* MD5 (Message-Digest) hash size */

#define PPP_PAP_REQ_BUF_MAX_LEN             (PASSWORDLEN + AUTHLEN)

/* code(1B)+id(1B)+length(2B)+challenge_size(1B)+challenge+name */
#define PPP_CHAP_CHALLENGE_BUF_MAX_LEN      (1 + 1 + 2 + 1 + CHAPCHALLENGELEN + AUTHLEN)

/* code(1B)+id(1B)+length(2B)+response_size(1B)+response+name */
#define PPP_CHAP_RESPONSE_BUF_MAX_LEN       (1 + 1 + 2 + 1 + PASSWORDLEN + AUTHLEN)

#define PPP_AUTH_FRAME_BUF_MAX_LEN          (256)
#define PPP_IPCP_FRAME_BUF_MAX_LEN          (256)

/*字符形式的IP地址长度，加上"."共16个字符*/
#define PPP_IPV4_ADDR_STR_MAX_LEN           (16)

#ifndef IPV4_ADDR_LEN
#define   IPV4_ADDR_LEN                     (4)       /*IPV4地址长度*/
#endif

#ifndef IPV6_ADDR_LEN
#define   IPV6_ADDR_LEN                     (16)      /*IPV6地址长度*/
#endif

/******************************************************************************
  3 枚举定义
******************************************************************************/
enum PPP_AT_CTRL_OPER_TYPE_ENUM
{
    PPP_AT_CTRL_REL_PPP_REQ = 0,              /* 释放IP类型PPP链路操作 */
    PPP_AT_CTRL_REL_PPP_RAW_REQ = 1,          /* 释放PPP类型PPP链路操作 */
    PPP_AT_CTRL_HDLC_DISABLE = 2,             /* HDLC硬化模块去使能操作 */
    PPP_AT_CTRL_CONFIG_INFO_IND = 3,          /* PDP激活消息 */

    PPP_AT_CTRL_BUTT
};
typedef VOS_UINT32  PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32;

/******************************************************************************
  4 全局变量声明
******************************************************************************/


/******************************************************************************
  5 消息头定义
******************************************************************************/


/******************************************************************************
  6 消息定义
******************************************************************************/


/******************************************************************************
  7 STRUCT定义
******************************************************************************/
#pragma pack(4)

typedef VOS_UINT16 PPP_ID;

/* 鉴权类型 */
enum PPP_AUTH_TYPE_ENUM
{
    PPP_NO_AUTH_TYPE                     = 0,
    PPP_PAP_AUTH_TYPE                    = 1,
    PPP_CHAP_AUTH_TYPE                   = 2,
    PPP_MS_CHAPV2_AUTH_TYPE              = 3,
    PPP_AUTH_TYPE_BUTT
};
typedef VOS_UINT8 PPP_AUTH_TYPE_ENUM_UINT8;

typedef struct
{
    VOS_UINT16  usPapReqLen;                    /*request长度: 24.008要求在[3,253]字节*/
    VOS_UINT8   aucReserve[2];                  /* 对齐保留 */
    VOS_UINT8  *pPapReq;                        /*request*/
} PPP_AUTH_PAP_CONTENT_STRU;

typedef struct
{
    VOS_UINT16  usChapChallengeLen;             /*challenge长度: 24.008要求在[3,253]字节*/
    VOS_UINT16  usChapResponseLen;              /*response长度: 24.008要求在[3,253]字节*/
    VOS_UINT8  *pChapChallenge;                 /*challenge*/
    VOS_UINT8  *pChapResponse;                  /*response*/
} PPP_AUTH_CHAP_CONTENT_STRU;

typedef struct
{
    PPP_AUTH_TYPE_ENUM_UINT8  ucAuthType;
    VOS_UINT8                 aucReserve[3];

    union
    {
        PPP_AUTH_PAP_CONTENT_STRU  PapContent;
        PPP_AUTH_CHAP_CONTENT_STRU ChapContent;
    } AuthContent;
} PPP_REQ_AUTH_CONFIG_INFO_STRU;

typedef struct
{
    VOS_UINT16  usIpcpLen;                      /*Ipcp帧长度*/
    VOS_UINT8   aucReserve[2];                  /* 对齐保留 */
    VOS_UINT8  *pIpcp;                          /*Ipcp帧*/
} PPP_REQ_IPCP_CONFIG_INFO_STRU;

typedef struct
{
    PPP_REQ_AUTH_CONFIG_INFO_STRU stAuth;
    PPP_REQ_IPCP_CONFIG_INFO_STRU stIPCP;
} PPP_REQ_CONFIG_INFO_STRU;

typedef struct
{
    VOS_UINT16  usAuthLen;                      /*鉴权帧长度*/
    VOS_UINT16  usIpcpLen;                      /*Ipcp帧长度*/
    VOS_UINT8  *pAuth;                          /*鉴权帧*/
    VOS_UINT8  *pIpcp;                          /*Ipcp帧*/
    VOS_UINT8   aucIpAddr[PPP_IPV4_ADDR_STR_MAX_LEN]; /*Ip地址*/
} PPP_IND_CONFIG_INFO_STRU;


/* PPP向AT发送的消息定义如下 */
#define AT_PPP_RELEASE_IND_MSG          0x00    /* 释放PDP连接的请求 */
#define AT_PPP_MODEM_MSC_IND_MSG        0x01    /* 向AT发送管脚信号指示(底软透传管脚信号，
                                                         由于无法模拟AT给自己发消息,故模拟PPP给AT发送该消息.) */
#define AT_PPP_PROTOCOL_REL_IND_MSG     0x02    /* PPP链路完成释放的指示 */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucReserve[3];
}AT_PPP_RELEASE_IND_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT8                           aucMscInd[2];  /* 管脚信号数据 */
}AT_PPP_MODEM_MSC_IND_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucReserve[2];
}AT_PPP_PROTOCOL_REL_IND_MSG_STRU;


typedef VOS_VOID (*PPP_PULL_MSG_EVENT_CALLBACK)(VOS_UINT32 ulMsgCnt);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/******************************************************************************
  8 UNION定义
******************************************************************************/


/******************************************************************************
  9 OTHERS定义
******************************************************************************/


/******************************************************************************
  10 函数声明
******************************************************************************/
/* PPP提供给AT的接口 */
extern VOS_UINT32 Ppp_CreatePppReq ( PPP_ID *pusPppId);
extern VOS_UINT32 Ppp_CreateRawDataPppReq ( PPP_ID *pusPppId);
extern VOS_UINT32 Ppp_ReleasePppReq ( PPP_ID usPppId);
extern VOS_UINT32 Ppp_ReleaseRawDataPppReq ( PPP_ID usPppId);
extern VOS_UINT32 PPP_RcvAtCtrlOperEvent(VOS_UINT16 usPppId, PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32 ulCtrlOperType);
extern VOS_VOID   PPP_UpdateWinsConfig(VOS_UINT8 ucWins);
extern VOS_VOID   PPP_SetRawDataByPassMode(VOS_UINT32 ulRawDataByPassMode);

#if (VOS_WIN32 == VOS_OS_VER) || (OSA_CPU_ACPU == VOS_OSA_CPU)
/* IP方式下提供的上行数据接收接口 */
extern VOS_UINT32 PPP_PullPacketEvent(VOS_UINT16 usPppId, IMM_ZC_STRU *pstImmZc);

/* IP方式下提供的下行数据接收接口 */
extern VOS_UINT32 PPP_PushPacketEvent(VOS_UINT8 ucRabId, IMM_ZC_STRU *pstImmZc, ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam);

/* PPP方式下提供的上行数据接收接口 */
extern VOS_UINT32 PPP_PullRawDataEvent(VOS_UINT16 usPppId, IMM_ZC_STRU *pstImmZc);

/* PPP方式下提供的下行数据接收接口 */
extern VOS_UINT32 PPP_PushRawDataEvent(VOS_UINT8 ucRabId, IMM_ZC_STRU *pstImmZc, ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam);
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* PppInterface.h */

