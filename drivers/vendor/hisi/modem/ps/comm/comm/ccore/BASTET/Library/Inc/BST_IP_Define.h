/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_IP_Define.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年06月04日
  最近修改   :
  功能描述   : 这个文件定义了Socket相关数据类型，出错类型
  函数列表   :

  修改历史   :
  1.日    期   : 2014年06月04日
    作    者   : d00173029
    修改内容   : 创建文件
******************************************************************************/

#ifndef __BST_IP_SOCKET_DEFINE_H__
#define __BST_IP_SOCKET_DEFINE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "lwip/err.h"
#include "lwip/ip_addr.h"

#include "BST_Platform.h"
#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_IP_V4ADDR_LENTH             ( 4 )
#define BST_IP_V6ADDR_LENTH             ( 6 )
#define BST_IP_PROTOCOL_ADDR            ( 9 )
#define BST_IP_DEFAULT_CS_ID            ( 1U )
#define BST_IP_RX_TIME_OUT              ( 15 * BST_OS_MS_IN_S )

#define BST_IP_ADDR_LENTH               ( BST_IP_V4ADDR_LENTH )
#define BST_IP_ADDRESS_ANY              ( 0u )

#define BST_IP_PROTOCOL_INVALID         ( 0x00u )
#define BST_IP_PROTOCOL_ICMP            ( 0x01u )
#define BST_IP_PROTOCOL_UDP             ( 0x11u )
#define BST_IP_PROTOCOL_TCP             ( 0x06u )

#define LWIP_NULL_PTR                   ( NULL )
#define BST_INVALID_FD                  ( -1 )
#define BST_INVALID_IP_ADDR             ( 0u )
#define BST_INVALID_PORT                ( 0u )

#define BST_IP_LWIP_DATA                ( 0x0U )
#define BST_IP_HPRI_DATA                ( 0x1U )
#define BST_IP_LPWR_DATA                ( 0x2U )
#define BST_IP_BSTT_DATA                ( 0x3U )

#define BST_IP_SEND_FLAG_VOID           ( 0x00U )
#define BST_IP_SEND_FLAG_MORE           ( 0x10U )

#define BST_IP_SET_PRIORITY(ucLvl,flag) ( ( ( (ucLvl)<<0x06U )&(0xC0U) )|((flag)&(~MSG_PRIORITY)) )
#define BST_IP_GET_PRIORITY(ucLvl)      ( ( (ucLvl)&(0xC0U) )>>0x06U )
#define BST_IP_ERR_OK                   ( ERR_OK )          /* No error, everything OK. */
#define BST_IP_ERR_MEM                  ( ERR_MEM )         /* Out of memory error.     */
#define BST_IP_ERR_BUF                  ( ERR_BUF )         /* Buffer error.            */
#define BST_IP_ERR_TIMEOUT              ( ERR_TIMEOUT )     /* Timeout.                 */
#define BST_IP_ERR_RTE                  ( ERR_RTE )         /* Routing problem.         */
#define BST_IP_ERR_INPROGRESS           ( ERR_INPROGRESS )  /* Operation in progress    */
#define BST_IP_ERR_VAL                  ( ERR_VAL )         /* Illegal value.           */
#define BST_IP_ERR_WOULDBLOCK           ( ERR_WOULDBLOCK )  /* Operation would block.   */
#define BST_IP_ERR_USE                  ( ERR_USE )         /* Address in use.          */
#define BST_IP_ERR_ISCONN               ( ERR_ISCONN )      /* Already Connectd.        */
#define BST_IP_ERR_ABRT                 ( ERR_ABRT )        /* Connection aborted.      */
#define BST_IP_ERR_RST                  ( ERR_RST )         /* Connection reset.        */
#define BST_IP_ERR_CLSD                 ( ERR_CLSD )        /* Connection closed.       */
#define BST_IP_ERR_CONN                 ( ERR_CONN )        /* Not Connectd.            */
#define BST_IP_ERR_ARG                  ( ERR_ARG )         /* Illegal argument.        */
#define BST_IP_ERR_IF                   ( ERR_IF )          /* Low-level netif error    */
#define BST_IP_INVALID_SOCKET_TYPE      ( BST_SCKT_TYPE_NUMBER )
#define BST_IP_IsFdValid( fd )          ( (fd) >= 0 )
#define BST_IP_IsValidSocketType(stype) ( stype < BST_SCKT_TYPE_NUMBER )
#define BST_IP_IsValidFun(pFun)         ( BST_NULL_PTR != (pFun) )
#define BST_IP_IsValidFunGrp(pFgrp)     ( BST_NULL_PTR != (pFgrp) )
#define BST_IP_IsSslConnection()        ( m_enSocketType == BST_SCKT_TYPE_SSL )
#define BST_IP_InitIpAddress( pSocket ) \
                                        ( pSocket )->usLocalPort     = BST_INVALID_PORT; \
                                        ( pSocket )->usRemotePort    = BST_INVALID_PORT; \
                                        ( pSocket )->aucRemoteIp[0]  = BST_INVALID_IP_ADDR;\
                                        ( pSocket )->aucRemoteIp[1]  = BST_INVALID_IP_ADDR;\
                                        ( pSocket )->aucRemoteIp[2]  = BST_INVALID_IP_ADDR;\
                                        ( pSocket )->aucRemoteIp[3]  = BST_INVALID_IP_ADDR;

#define BST_IP_IsValidIpAddress( pSocket ) \
                                       (!( ( BST_INVALID_PORT     == ( pSocket )->usRemotePort )\
                                        || ( BST_INVALID_PORT     == ( pSocket )->usLocalPort )\
                                        || ( (BST_INVALID_IP_ADDR == ( pSocket )->aucRemoteIp[0] )\
                                          &&( BST_INVALID_IP_ADDR == ( pSocket )->aucRemoteIp[1] )\
                                          &&( BST_INVALID_IP_ADDR == ( pSocket )->aucRemoteIp[2] )\
                                          &&( BST_INVALID_IP_ADDR == ( pSocket )->aucRemoteIp[3] ) ) ) )

#define BST_IP_IsLwipNull(ptr)          ( LWIP_NULL_PTR == (ptr) )



#define BST_IP_GetU32Addr(ipaddr, d0, d1, d2, d3) \
                                        ipaddr = ((BST_UINT32)((d3) & 0xff) << 24) | \
                                                 ((BST_UINT32)((d2) & 0xff) << 16) | \
                                                 ((BST_UINT32)((d1) & 0xff) << 8)  | \
                                                 (BST_UINT32)((d0) & 0xff)

#define BST_IP_GetU8Addr(d0, d1, d2, d3, ipaddr) \
                                        d3 = (BST_UINT8)(((ipaddr) >> 24) & 0xff); \
                                        d2 = (BST_UINT8)(((ipaddr) >> 16 ) & 0xff); \
                                        d1 = (BST_UINT8)(((ipaddr) >> 8 ) & 0xff); \
                                        d0 = (BST_UINT8)(((ipaddr) & 0xff))
#define BST_IP_IsConnErr( enIpErr )     ( ( BST_IP_ERR_ABRT == ( enIpErr ) ) ||     \
                                          ( BST_IP_ERR_RST  == ( enIpErr ) ) ||     \
                                          ( BST_IP_ERR_CONN == ( enIpErr ) ) ||     \
                                          ( BST_IP_ERR_CLSD == ( enIpErr ) ) )
#define BST_IP_IsTypeInited( enIpType ) ( BST_PRTC_TYPE_INVALID != ( enIpType ) )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
enum BST_SCKT_CMD_ENUM{
    BST_SCKT_CMD_SET_ADDRESS            = 0,
    BST_SCKT_CMD_GET_ADDRPTR,
    BST_SCKT_CMD_SET_SEQNO,
    BST_SCKT_CMD_SET_SEQNO_TS,
    BST_SCKT_CMD_SET_PROPERTY,
    BST_SCKT_CMD_GET_PROPERTY,
    BST_SCKT_CMD_RPT_PROPERTY,
    BST_SCKT_CMD_DBL_PROPERTY,
    BST_SCKT_CMD_SYNC_PROPERTY_START,
    BST_SCKT_CMD_SYNC_PROPERTY_STOP,
    BST_SCKT_CMD_REG_CALLBACK,
    BST_SCKT_CMD_INQ_STATE,
    BST_SCKT_CMD_INQ_FLOW,
    BST_SCKT_CMD_DEF_TYPE,                      /*使用无参Socket时，需要通过此命令来重新生成socket类*/
    BST_SCKT_CMD_CHK_FD,
    BST_SCKT_CMD_GET_TRAFFIC_FLOW,
    BST_SCKT_CMD_SET_TRAFFIC_FLOW,
    BST_SCKT_CMD_CHK_CONNECTED,
    BST_SCKT_CMD_BUTT,
};
typedef BST_UINT32                      BST_SCKT_CMD_ENUM_UINT32;

enum BST_SCKT_TYPE_ENUM{
    BST_SCKT_TYPE_TCP,                          /* 标准阻塞型BSD接口 */
    BST_SCKT_TYPE_UDP,                          /* LWIP 所采用的RAW-TCP接口，支持实体Connect, 支持Seq查/设 */
    BST_SCKT_TYPE_SSL,                          /* 标准SSL加密型接口 */
    BST_SCKT_TYPE_NUMBER
};
typedef BST_UINT32                      BST_SCKT_TYPE_ENUM_UINT32;

enum BST_PRTC_TYPE_ENUM
{
    BST_PRTC_TYPE_INVALID               = 0,    /* 非法数据类型 */
    BST_PRTC_TYPE_TCP_LONG,                     /* TCP长连接应用 */
    BST_PRTC_TYPE_TCP_SHORT,                    /* TCP短连接应用 */
    BST_PRTC_TYPE_UDP,                          /* UDP应用 */
    BST_PRTC_TYPE_SSL,
    BST_PRTC_TYPE_BUTT
};
typedef BST_UINT32                      BST_PRTC_TYPE_ENUM_UINT32;

enum BST_IP_EVENT_ENUM {
  BST_IP_EVENT_RECV,
  BST_IP_EVENT_CONNECTED,
  BST_IP_EVENT_ERR,
  BST_IP_EVENT_OVERFLOW,
  BST_IP_EVENT_ACKED,
  BST_IP_EVENT_BUTT
};
typedef BST_UINT32                      BST_IP_EVENT_ENUM_U32;

enum BST_IP_SKT_PROP_TYPE_ENUM {
  BST_IP_SKT_PROP_NONE,                 /* 0 没有property */
  BST_IP_SKT_PROP_SEQNO,                /* 1 只有seqno */
  BST_IP_SKT_PROP_SEQNO_TS,             /* 2 只有seqno+timestamp */
  BST_IP_SKT_PROP_TOTAL,                /* 3 完整property */
  BST_IP_SKT_PROP_BUTT
};
typedef BST_UINT8                       BST_IP_SKT_PROP_TYPE_ENUM_U8;


enum BST_IP_SKT_PATH_MODE_ENUM {
  BST_IP_PATH_MODE_NO_CHG,              /* 0 无变化，无需设置端口状态 */
  BST_IP_PATH_MODE_SINGLE,              /* 1 只给BASTET */
  BST_IP_PATH_MODE_DOUBLE,              /* 2 AP-BASTET双通模式 */
  BST_IP_PATH_MODE_STOP,                /* 3 停止模式 */
  BST_IP_PATH_MODE_BUTT
};
typedef BST_UINT8                       BST_IP_SKT_PATH_MODE_ENUM_U8;

#define BST_IP_SetPropPathFlag(prop, path)\
    ((( prop )&0x0FU) | (( path )<<0x04U) )

#define BST_IP_GetPropType( PropPath )\
    ( ( PropPath )&0x0FU )

#define BST_IP_GetPathMode( PropPath )\
    ( ( PropPath>>4 )&0x0FU )

/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/

typedef struct
{
    BST_UINT8                           aucRemoteIp[BST_IP_ADDR_LENTH];
    BST_UINT16                          usRemotePort;
    BST_UINT16                          usLocalPort;
} BST_IP_SOCKET_ADD_T;

typedef enum
{
    BST_IP_PKT_REMOVE_PROC              = 0,
    BST_IP_PKT_FORWARD_PROC,
    BST_IP_PKT_NO_PROC,
} BST_IP_PKTPROC_MODE;
typedef BST_UINT32                      BST_IP_PKTPROC_MODE_ENUM;

typedef BST_INT32                       BST_IP_ERR_T;

typedef struct
{
    BST_UINT32                          ulSeqNum;
    BST_UINT32                          ulAckNum;
    BST_UINT32                          ulSndWnd;
    BST_UINT32                          ulTsRecent;
    BST_UINT32                          ulMss;
    BST_UINT32                          ulTxByte;           /*为了接口一致，收发过程中不更新*/
    BST_UINT32                          ulRxByte;
    BST_UINT16                          usSndWscale;
    BST_UINT16                          usRcvWscale;
    BST_UINT32                          ulTsCurrent;
    BST_UINT32                          ulTsRecentStamp;
} BST_IP_SKT_PROPTY_STRU;

typedef BST_IP_SKT_PROPTY_STRU          BST_IP_SKT_PARAM_STRU;

typedef struct
{
    BST_UINT32                          ulTxByte;
    BST_UINT32                          ulRxByte;
} BST_IP_TRAFFIC_FLOW_STRU;

typedef BST_VOID*                       BST_ARG_T;
typedef BST_UINT32                      BST_IPADDR_U32T;
typedef BST_VOID*                       BST_IP_PKT_ID_T;
typedef BST_UINT16                      BST_IP_PROTOCOL_TYPE;

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
