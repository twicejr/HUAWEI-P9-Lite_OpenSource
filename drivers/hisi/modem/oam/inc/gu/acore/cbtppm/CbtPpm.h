

/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CbtPpm.h
  版 本 号   : 初稿
  作    者   : h59254
  生成日期   : 2014年5月31日
  最近修改   :
  功能描述   : CbtPpm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月31日
    作    者   : h59254
    修改内容   : 创建文件
******************************************************************************/

#ifndef __CBT_PPM_H__
#define __CBT_PPM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "omnvinterface.h"
#include "mdrv.h"

#if (FEATURE_HISOCKET == FEATURE_ON)
#include "hisocket.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (FEATURE_HISOCKET == FEATURE_ON)

#define CBTPPM_SOCK_MSG_LEN             (1000)

#define CBTPPM_SOCK_PORT_NUM            (20250)

#define CBTPPM_SOCKET_NUM_MAX           (1)

#if  (VOS_LINUX == VOS_OS_VER)
#define CBTPPM_SOCK_NULL                (-1)


#define CBTPPM_SOCKET_ERROR             (VOS_ERROR)


#define CBT_IP_NULL         0
#define CBT_Ip_sockaddr     sockaddr
#define CBT_Ip_socklen_t    int
#define CBT_Ip_fd           int
#define CBT_Ip_fd_set       hi_fd_set


#define CBT_socket(domain,type,protocol)        hi_socket(domain, type, protocol)

#define CBT_shutdown(fd,how)                    do{\
                                                    hi_shutdown((CBT_Ip_fd)fd, how);\
                                                    hi_close((CBT_Ip_fd)fd);\
                                                }while(0)
                                            
#define CBT_closesocket(s)                      CBT_shutdown(s, SHUT_RDWR)

#define CBT_bind(fd,addr,addrlen)               hi_bind((CBT_Ip_fd)fd, (struct  CBT_Ip_sockaddr *)addr, (CBT_Ip_socklen_t)addrlen)
#define CBT_accept(fd,addr,addrlenp)            hi_accept((CBT_Ip_fd)fd, (struct  CBT_Ip_sockaddr *)addr, (CBT_Ip_socklen_t *)addrlenp)
#define CBT_listen(fd,backlog)                  hi_listen((CBT_Ip_fd)fd, backlog)
#define CBT_select(nfds,rf,wf,ef,t)             hi_select(nfds, (CBT_Ip_fd_set *)rf, (CBT_Ip_fd_set *)wf, CBT_IP_NULL, t)
#define CBT_recv(fd,buf,len,flags)              hi_recv((CBT_Ip_fd)fd, (void *)buf, len, flags)
#define CBT_send(fd,msg,len,flags)              hi_send((CBT_Ip_fd)fd, (void *)msg, len, flags)
#else
#define CBTPPM_SOCK_NULL                       (0)

#define CBT_Ip_fd_set                          fd_set

#endif

#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* UDI设备句柄 */
enum OM_PROT_HANDLE_ENUM
{
    OM_USB_CBT_PORT_HANDLE      =   0,
    OM_PORT_HANDLE_BUTT
};

typedef VOS_UINT32  OM_PROT_HANDLE_ENUM_UINT32;

enum OM_LOGIC_CHANNEL_ENUM
{
     OM_LOGIC_CHANNEL_CBT = 0,
     OM_LOGIC_CHANNEL_BUTT
};

typedef VOS_UINT32     OM_LOGIC_CHANNEL_ENUM_UINT32;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/



/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/* 用于记录VCOM发送信息 */
typedef struct
{
    VOS_UINT32                          ulVCOMSendSn;
    VOS_UINT32                          ulVCOMSendNum;
    VOS_UINT32                          ulVCOMSendLen;
    VOS_UINT32                          ulVCOMSendErrNum;
    VOS_UINT32                          ulVCOMSendErrLen;

    VOS_UINT32                          ulVCOMRcvSn;
    VOS_UINT32                          ulVCOMRcvNum;
    VOS_UINT32                          ulVCOMRcvLen;
    VOS_UINT32                          ulVCOMRcvErrNum;
    VOS_UINT32                          ulVCOMRcvErrLen;
}CBT_ACPU_VCOM_DEBUG_INFO;

#if (FEATURE_HISOCKET == FEATURE_ON)

#if (VOS_LINUX == VOS_OS_VER)

typedef int    CBTPPM_SOCKET;

#else

typedef unsigned int     CBTPPM_SOCKET;

#endif

typedef struct
{
    CBTPPM_SOCKET                       socket;
    CBTPPM_SOCKET                       listener;
    VOS_SEM                             SmClose;
    VOS_CHAR                            aucBuf[CBTPPM_SOCK_MSG_LEN];
}CBTPPM_SOCKET_CTRL_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulListernNum1;
    VOS_UINT32                          ulListernNum2;
    VOS_UINT32                          ulRcvData;
    VOS_UINT32                          ulFailToProcess;
    VOS_UINT32                          ulSndData;
    VOS_UINT32                          ulFailToSend;
}CBTPPM_SOCKET_DEBUG_INFO_STRU;

#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 CBTPPM_OamCbtPortDataSnd(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_UINT32 CBTPPM_OamUsbCbtSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_VOID   CBTPPM_OamUsbCbtPortClose(VOS_VOID);

VOS_VOID   CBTPPM_OamUsbCbtPortOpen(VOS_VOID);

VOS_INT32  CBTPPM_OamUsbCbtReadDataCB(VOS_VOID);

VOS_VOID   CBTPPM_OamUsbCbtWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen);

VOS_VOID   CBTPPM_OamUsbCbtStatusCB(ACM_EVT_E enPortState);

VOS_VOID   CBTPPM_OamCbtPortDataInit(OM_PROT_HANDLE_ENUM_UINT32          enHandle,
                                                 VOS_VOID                            *pReadCB,
                                                 VOS_VOID                            *pWriteCB,
                                                 VOS_VOID                            *pStateCB);

VOS_UINT32 CBTPPM_OamUsbCbtPortInit(VOS_VOID);

VOS_INT    CBTPPM_OamVComCbtReadData(VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 ullength);

VOS_UINT32 CBTPPM_OamVComCbtSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_VOID   CBTPPM_OamVComCbtPortInit(VOS_VOID);

VOS_VOID   CBTPPM_OamCbtPortInit(VOS_VOID);

VOS_UINT32 PPM_DisconnectGUPort(OM_LOGIC_CHANNEL_ENUM_UINT32 enChannel);

VOS_UINT32 CBTPPM_SocketTaskInit(VOS_VOID);

VOS_VOID CBTPPM_SocketPortInit(VOS_VOID);

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

#endif /* end of cpm.h */
