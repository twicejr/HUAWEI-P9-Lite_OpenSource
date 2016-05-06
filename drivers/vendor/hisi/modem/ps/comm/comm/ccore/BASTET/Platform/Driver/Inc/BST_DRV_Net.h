/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_DRV_NETDEVICE.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年06月26日
  最近修改   :
  功能描述   : 虚拟网卡驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月26日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef __BST_DRV_NETDEVICE_H__
#define __BST_DRV_NETDEVICE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_DRV_Common.h"
#include "BST_IP_Define.h"
#include "BST_PAL_Timer.h"
#include "BST_PAL_Net.h"
#include "BST_PAL_Thread.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_DRV_NetGetDvcHandle()       ( &g_BstDrvNetHandle )
#define BST_DRV_NetGetMainIfHandle()    ( &g_stMainNetDevice )
#define BST_DRV_NetGetRbshIfHandle()    ( &g_stRbshNetDevice )
#define BST_DRV_NetGetTimeStampHandle() ( &g_BstDrvNetTimeStamp )
#define BST_DRV_IsNetTimeStampValid()   ( 0U != g_BstDrvNetTimeStamp.ulApTimeUnitMs )
#define BST_DRV_NetInitInterface        BST_PAL_NetDeviceInitItf
#define BST_DRV_NET_ResumeToAp          BST_PAL_NetApiPacketResume
#define BST_DRV_NET_FreePackt           BST_PAL_NetApiPacketFree
#define BST_DRV_NET_Send                BST_PAL_NetApiPacketSend
#define BST_DRV_NetGetPktMode()         ( g_enBstPktMode )
#define BST_DRV_IsNetPktModeValid(pmod) ( ( (pmod) > BST_DRV_PKT_MODE_INVALID ) \
                                        &&( (pmod) < BST_DRV_PKT_MODE_BUTT ) )

#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
#define BST_DRV_NET_ForwardPPP          BST_PAL_NetApiPackPppForwd
#define BST_DRV_NET_INVALID_PPP_DESC    ( -1 )  
#define BST_DRV_NetGetPppDesc()         ( g_lBstDrvNetPppDesc )
#define BST_DRV_NetSetPppDesc(pppdesc)  ( g_lBstDrvNetPppDesc = (pppdesc) )
#define BST_DRV_IsPppDescValid()        ( g_lBstDrvNetPppDesc >= 0 )
#endif
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
#define BST_DRV_PKT_MODE_INVALID       ( 0U )
#define BST_DRV_PKT_MODE_IP            ( 1U )
#define BST_DRV_PKT_MODE_PPP           ( 2U )
#define BST_DRV_PKT_MODE_BUTT          ( 3U )

typedef BST_UINT32                      BST_DRV_NET_PKT_MODE_ENUM_UINT32;

enum BST_DRV_NET_STATE_ENUM
{
    BST_DRV_NETINVALID = 0,
    BST_DRV_NETSTATE_UP,
    BST_DRV_NETSTATE_DOWN,
    BST_DRV_NETSTATE_UNKOWN,
    BST_DRV_NETSTATE_MAX,
} ;
typedef BST_UINT32                      BST_DRV_NET_STATE_ENUM_UINT32;
typedef struct netif                    BST_NETIF_T;
typedef ip_addr_t                       BST_NET_IPADD_T;
typedef struct pbuf                     BST_NET_PBUF_T;

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/
typedef struct
{
    BST_UINT32                          ulIp;
    BST_UINT32                          ulMask;
    BST_UINT32                          ulGateWay;
} NET_DRV_LOCAL_IP_INFO_STRU;

typedef struct
{
    BST_DRV_NET_STATE_ENUM_UINT32       enState;
    NET_DRV_LOCAL_IP_INFO_STRU          stLocal;
} BST_NET_STATE_STRU;

typedef struct
{
    BST_UINT16                          usModemId;
    BST_UINT16                          usRabId;
}BST_DRV_NET_MODEM_RABID_STRU;

typedef struct
{
  BST_UINT32                            ulTimeStmp;
  BST_UINT32                            ulTimeFreq;
} BST_DRV_NET_TIME_CLBRT_STRU;

typedef struct
{
  BST_UINT32                            ulBstStartTime;
  BST_UINT32                            ulApStartTime;
  BST_UINT32                            ulApTimeUnitMs;
} BST_DRV_NET_TIMESTAMP_STRU;

typedef struct
{
    BST_UINT8                          *pucData;
    BST_UINT8                           ucDataType;
    BST_UINT8                           ucReverse[3];
} BST_DRV_IP_DATA_STRU;


/*****************************************************************************
  6 UNION定义
*****************************************************************************/

/*****************************************************************************
  7 全局变量声明
*****************************************************************************/
extern BST_DRV_STRU                     g_BstDrvNetHandle;
extern BST_DRV_NET_PKT_MODE_ENUM_UINT32 g_enBstPktMode;
extern BST_NETIF_T                      g_stMainNetDevice;
extern BST_NETIF_T                      g_stRbshNetDevice;
extern BST_BOOL                         g_bNetDeviceIsUp;
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
extern BST_INT32                        g_lBstDrvNetPppDesc;
#endif
/*****************************************************************************
  8 函数声明
*****************************************************************************/
BST_UINT32      BST_DRV_NetGetPktLen ( BST_VOID *pvPkt );
BST_UINT8      *BST_DRV_NetGetPktHead( BST_VOID *pvPkt );
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

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
