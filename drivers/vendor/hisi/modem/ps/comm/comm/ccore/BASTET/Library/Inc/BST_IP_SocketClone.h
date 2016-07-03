

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

