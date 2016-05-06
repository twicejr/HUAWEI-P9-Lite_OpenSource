/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_IP_SocketClone.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : 这个文件定义了复制SOCKET所使用的函数
  函数列表   :

  修改历史   :
  1.日    期   : 2014年04月16日
    作    者   : d00173029
    修改内容   : 创建文件
  1.日    期   : 2014年05月13日
    作    者   : D00173029
    修改内容   : 适配Balong平台
******************************************************************************/

#ifndef __BST_IP_SOCKET_CLONE_H__
#define __BST_IP_SOCKET_CLONE_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "BST_IP_Define.h"
#include "BST_Platform.h"
#include "lwip/tcp.h"
#include "lwip/tcp_impl.h"

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
  1 宏定义
*****************************************************************************/

/*****************************************************************************
  2 函数声明
*****************************************************************************/
BST_VOID            BST_IP_ApiRecordTcpProperty(
    BST_IP_PKT_ID_T                 stPktId,
    struct tcp_pcb                 *pstPcb );

BST_ERR_ENUM_UINT8  BST_IP_ApiSetTcpPcbProperty(
    struct tcp_pcb                 *pstPcb,
    BST_IP_SKT_PROPTY_STRU         *pstCurrentProperty,
    BST_UINT8                       ucFlag );

BST_ERR_ENUM_UINT8  BST_IP_ApiGetTcpPcbProperty(
    struct tcp_pcb                 *pstPcb,
    BST_IP_SKT_PROPTY_STRU         *pstCurrentProperty,
    BST_UINT8                       ucFlag );

BST_IP_ERR_T        BST_IP_TcpCloneConn(
    struct tcp_pcb                 *pstPcb,
    struct ip_addr                 *pstIpAddr,
    tcp_connected_fn                connected,
    BST_UINT16                      port );

BST_VOID            BST_IP_ApiDropTcpPcb(
    struct tcp_pcb                 *pstPcb );

BST_VOID            BST_IP_ApiResetTcpPcb(
    struct tcp_pcb                 *pstPcb );

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

