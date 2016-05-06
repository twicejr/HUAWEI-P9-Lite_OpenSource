/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_IP_PreProc.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : 这个文件定义了在数据包到达LwIP协议栈前的端口解析处理和流量统计工作
  函数列表   :

  修改历史   :
  1.日    期 : 2014年04月16日
    作    者 : d00173029
    修改内容 : 创建文件
  1.日    期 : 2014年05月13日
    作    者 : D00173029
    修改内容 : 适配Balong平台
******************************************************************************/
#ifndef __BST_IP_PREPROC_H__
#define __BST_IP_PREPROC_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "BST_LIB_List.h"
#include "BST_IP_Define.h"
#include "lwip/tcp.h"
#include "BST_Platform.h"
#include "lwip/sys.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_IP_GetPreprocLstHead()      ( &g_stBstPortPreprocList )
#define BST_IP_GetFCTPtr()              ( &g_stBstIpFastPortCheck )
#define BST_IP_GetMirroredTimeStamp()   ( g_ulMirroredTimeStamp )
#define BST_IP_SetMirroredTimeStamp(tm) ( g_ulMirroredTimeStamp = (tm) + 30 )
#define BST_IP_ClrMirroredTimeStamp()   ( g_ulMirroredTimeStamp = 0 )
#define BST_IP_IsMirroredTimeStampUsed() ( 0 != g_ulMirroredTimeStamp )
#define BST_IP_IsPortValid(port)        ( port != 0x0000U )
#define BST_IP_FRAG_MASK                ( 0x3FFFU )
#define BST_IP_CLRPKT_TIMELEN           ( 3U*BST_OS_MS_IN_S )
#define BST_IP_FD_TIMELEN               ( 2U*BST_OS_MS_IN_S )
#define BST_IP_TCP_BASE_HDR_LEN         ( 20U )
#define BST_IP_PORT_ADRR_LEN            ( 4U )
#define BST_IP_VER_IPV4                 ( 4U )
#define BST_IP_TEST_DEEP                ( 8 )
#define BST_IP_NO_TRFC_LMT              ( 0 )
#define BST_IP_TRAFFIC_ADD              ( 1 )
#define BST_IP_TRAFFIC_DEC              ( 2 )
#define BST_IP_TIMESTAMP_FLAG           ( 0x0A080101U )
#define BST_IP_TCP_FLAG( pucData )      ( ( ( pucData )[33] ) & 0xFFU )
#define BST_IP_TCP_HEAD_LEN( pucData )  ( ( ( ( pucData )[32] >> 4 ) & 0x0FU ) * 4 )
#define BST_IP_IP_HEAD_LEN( pucData )   ( ( ( ( pucData )[0] ) & 0x0FU ) * 4 )
#define BST_IP_TCP_TIME_HEAD_LEN        ( 32U )
#define BST_IP_DEFAULT_SKT_PROPERTY     ( g_stDefaultSocktProperty )
#define BST_IP_IsPrprocWorking(Preproc) ( BST_IP_PORT_STATE_WORKING == Preproc->enState )
#define BST_IP_IsPrprocSuspend(Preproc) ( BST_IP_PORT_STATE_SUSPEND == Preproc->enState )

#define BST_IP_ReadFromPcbPropertey(dst, src)\
                                         (dst)->ulSeqNum    = (src)->snd_nxt;\
                                         (dst)->ulAckNum    = (src)->rcv_nxt;\
                                         (dst)->ulMss       = (src)->mss;\
                                         (dst)->ulSndWnd    = (src)->snd_wnd;\
                                         (dst)->usSndWscale = (src)->snd_scale;\
                                         (dst)->usRcvWscale = (src)->rcv_scale;\
                                         (dst)->ulTsRecentStamp \
                                                            = (src)->ts_recent_stamp;\
                                         (dst)->ulTsRecent  = (src)->ts_recent;\
                                         (dst)->ulTsCurrent = sys_timestamp() + (src)->ts_offset

#define BST_IP_WriteToPcbPropertey(dst, src)\
                                         (dst)->snd_nxt     = (src)->ulSeqNum;\
                                         (dst)->snd_lbb     = (src)->ulSeqNum;\
                                         (dst)->lastack     = (src)->ulSeqNum;\
                                         (dst)->snd_wl1     = (src)->ulAckNum;\
                                         (dst)->snd_wl2     = (src)->ulSeqNum;\
                                         (dst)->rcv_nxt     = (src)->ulAckNum;\
                                         (dst)->rcv_ann_right_edge \
                                                            = (src)->ulAckNum + (dst)->rcv_ann_wnd; \
                                         (dst)->mss         = (BST_UINT16)(src)->ulMss;\
                                         (dst)->snd_wnd     = (src)->ulSndWnd;\
                                         (dst)->snd_scale \
                                                            = (BST_UINT8)(src)->usSndWscale;\
                                         (dst)->rcv_scale \
                                                            = (BST_UINT8)(src)->usRcvWscale;\
                                         (dst)->ts_offset   = (src)->ulTsCurrent - sys_timestamp();\
                                         (dst)->ts_recent_stamp \
                                                            = (src)->ulTsRecentStamp; \
                                         (dst)->ts_recent   = (src)->ulTsRecent

#define BST_IP_SynPreProcRecord(dst, src)\
                                         (dst)->ulSeqNum    = (src)->ulSeqNum;\
                                         (dst)->ulAckNum    = (src)->ulAckNum;\
                                         (dst)->ulMss       = (src)->ulMss;\
                                         (dst)->ulSndWnd    = (src)->ulSndWnd;\
                                         (dst)->ulTsRecent  = (src)->ulTsRecent
#define BST_IP_IS_INVALID_PACKETID( packetId )      ( BST_NULL_PTR == (packetId) )


/*****************************************************************************
  4 枚举定义
*****************************************************************************/
#define BST_IP_PORT_STATE_WORKING       ( 1U ) /*端口应用中*/
#define BST_IP_PORT_STATE_STOPED        ( 2U ) /*端口停用*/
#define BST_IP_PORT_STATE_SUSPEND       ( 3U ) /*端口挂起*/
#define BST_IP_PORT_STATE_BUTT          ( 4U )
typedef BST_UINT32 BST_IP_PORT_STATE_ENUM_UINT32;

enum BST_IP_PKT_PROC
{
    BST_IP_PKT_TO_AP                    = 0,
    BST_IP_PKT_TO_BST,
    BST_IP_PKT_TO_AP_BST,
    BST_IP_PKT_FREE
};
typedef BST_INT8                        BST_IP_PKT_PROC_ENUM_INT8;

/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/

typedef struct
{
    NODE                                node;
    BST_IP_PKT_ID_T                     stPktId;
    BST_VOID                           *pstPktItem;
    BST_IP_SKT_PROPTY_STRU              stCurrentSktProperty;
} BST_IP_PKT_INFO_STRU;

typedef struct
{
    NODE                                node;
    LIST                               *pstPktList;
    BST_IP_PORT_STATE_ENUM_UINT32       enState;
    BST_UINT16                          usPortNum;
    BST_UINT16                          usProtocol;
    BST_IP_SKT_PATH_MODE_ENUM_U8        ucPathMode;
    BST_UINT8                           aucReserved[3];
    BST_IP_SKT_PROPTY_STRU              stLastSktProperty;
}BST_IP_PORT_PREPROC_STRU;

typedef struct
{
    BST_INT32                           lCnt;
    BST_UINT16                          ausPortNum[BST_MAX_CNNT_NUMBER];
    BST_UINT16                          ausProtocol[BST_MAX_CNNT_NUMBER];
    BST_IP_SKT_PATH_MODE_ENUM_U8        aucPathMode[BST_MAX_CNNT_NUMBER];
} BST_IP_FAST_CHECK_STRU;

typedef struct
{
    BST_UINT8                           ucIhl: 4;
    BST_UINT8                           ucVersion: 4;
    BST_UINT8                           ucTos;
    BST_UINT16                          usTotLen;
    BST_UINT16                          usId;
    BST_UINT16                          usFragOff;
    BST_UINT8                           ucTtl;
    BST_UINT8                           ucProtocol;
    BST_UINT16                          usCheck;
    BST_UINT32                          ulSaddr;
    BST_UINT32                          ulDaddr;
    //The options start here.
} BST_IP_IPHDR_STRU;

typedef struct
{
    BST_UINT16                          usSource;
    BST_UINT16                          usDest;
    BST_UINT32                          ulSeq;
    BST_UINT32                          ulAckSeq;
    BST_UINT16                          usRes1: 4;
    BST_UINT16                          usDoff: 4;
    BST_UINT16                          usFin:  1;
    BST_UINT16                          usSyn:  1;
    BST_UINT16                          usRst:  1;
    BST_UINT16                          usPsh:  1;
    BST_UINT16                          usAck:  1;
    BST_UINT16                          usUrg:  1;
    BST_UINT16                          usEce:  1;
    BST_UINT16                          usCwr:  1;
    BST_UINT16                          usWindow;
    BST_UINT16                          usCheck;
    BST_UINT16                          usUrgPtr;
} BST_IP_TCPHDR_STRU;

typedef struct
{
    BST_UINT16                          usSource;  //Source port
    BST_UINT16                          usDest;    //Dest port
    BST_UINT16                          usLen;     //UDP data+head length
    BST_UINT16                          usCheck;   //UDP Checksum
} BST_IP_UDPHDR_STRU;

typedef struct
{
    BST_UINT32                          ulOpt01;
    BST_UINT32                          ulOpt02;
    BST_UINT32                          ulOpt03;
} BST_IP_TCPOPT_STRU;
/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/
extern BST_UINT32                       g_ulMirroredTimeStamp;
/*****************************************************************************
  8 函数声明
*****************************************************************************/
BST_VOID    BST_IP_ApiInitPortPreproc( BST_VOID );

BST_VOID   *BST_IP_ApiAddPort(
    BST_IP_PROTOCOL_TYPE      usProtocol,
    BST_UINT16                usPortNum );

BST_VOID    BST_IP_ApiRmvPort(
    BST_IP_PROTOCOL_TYPE      usProtocol,
    BST_UINT16                usPortNum,
    BST_IP_TRAFFIC_FLOW_STRU *pstFlowOutput );

BST_UINT32 BST_IP_ApiChkPort(
    const BST_UINT16          usProtocol,
    const BST_UINT16          usPortNumber );

BST_IP_PKT_PROC_ENUM_INT8 BST_IP_ApiFastCheckDL(
    const BST_UINT8           aucPkt[],
    const BST_UINT32          ulPktLen );

BST_UINT8   BST_IP_ApiFastCheckUL(
    const BST_UINT8           aucPkt[],
    const BST_UINT32          ulPktLen );

BST_UINT16  BST_IP_ApiRegistPacket(
    BST_IP_PKT_ID_T           stPktId,
    BST_VOID                 *pstPktItem );

BST_VOID    BST_IP_ApiUnRegistPacket( BST_IP_PKT_ID_T stPktId );

BST_VOID    BST_IP_ApiForwordPacket(
    BST_IP_PKT_ID_T           stPktId );

BST_VOID    BST_IP_ApiRecordLastSktProp(
    BST_IP_PKT_ID_T           stPktId );

BST_VOID    BST_IP_ApiSetPreprocSuspend(
    BST_IP_PROTOCOL_TYPE      usProtocol,
    BST_UINT16                usPortNum );

BST_VOID    BST_IP_ApiSetPreprocWorking(
    BST_IP_PROTOCOL_TYPE            usProtocol,
    BST_UINT16                      usPortNum,
    BST_IP_SKT_PATH_MODE_ENUM_U8    ucPathMode );

BST_VOID    BST_IP_ApiSetPreprocStop(
    BST_IP_PROTOCOL_TYPE      usProtocol,
    BST_UINT16                usPortNum );

BST_UINT32  BST_IP_ApiUpdateTrafficFlow(
    BST_UINT32                ulTrfcAction,
    BST_UINT32                ulTrfcFlow );

BST_VOID    BST_IP_ClearPortPkt(
    BST_IP_PORT_PREPROC_STRU *pstPortPreproc );

BST_VOID    BST_IP_ClearAllPkt( BST_VOID );

BST_VOID    BST_IP_UpdateFCT( BST_VOID );

BST_IP_PKT_INFO_STRU *BST_IP_SrchPackItem(
    BST_IP_PKT_ID_T           stPktId );

BST_IP_PORT_PREPROC_STRU *BST_IP_SrchPreprocByPort(
    BST_IP_PROTOCOL_TYPE      ucProtocol,
    BST_UINT16                usPortNum );

BST_IP_PORT_PREPROC_STRU *BST_IP_SrchPreprocByPktId ( BST_IP_PKT_ID_T           stPktId );

struct tcp_pcb *BST_IP_SrchPcbByPort                ( BST_UINT16                usPortNum );

BST_ERR_ENUM_UINT8 BST_IP_GetDLPortProtocol(
    const BST_UINT8           aucPkt[],
    const BST_UINT32          ulPktLen,
    BST_IP_PROTOCOL_TYPE     *pucProtocol,
    BST_UINT16               *pusPortNum );

BST_ERR_ENUM_UINT8 BST_IP_GetULPortProtocol(
    const BST_UINT8           aucPkt[],
    const BST_UINT32          ulPktLen,
    BST_IP_PROTOCOL_TYPE     *pucProtocol,
    BST_UINT16               *pusPortNum );

BST_ERR_ENUM_UINT8  BST_IP_ApiGetTrafficFlow(
    BST_UINT16                usIsReset,
    BST_UINT16                ulLocalPort,
    BST_IP_TRAFFIC_FLOW_STRU *pstCurrentProperty );
/*****************************************************************************
  9 类定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if    __cplusplus
           }
#endif
#endif

#endif
