/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_PAL_Net.h
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

#ifndef __BST_PAL_NETDEVICE_H__
#define __BST_PAL_NETDEVICE_H__

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
  1 其他头文件包含
*****************************************************************************/
#include "BST_IP_Define.h"
#include "TTFMem.h"
#include "TTFMemInterface.h"
#include "TTFComm.h"
#include "BastetCdsInterface.h"
#include "LUPQueue.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_PAL_NetGetPacketHead(pPkt)  ( ( (TTF_MEM_ST *)(pPkt) )->pData )
#define BST_PAL_NetDeviceInitItf        ( BST_DRV_NET_IfInit )
#define BST_PAL_NetGetEntity()          ( &g_BstPalNetEntity )
#define BST_PAL_NetItfPacketRcvd(a, b)  ( 0x00U )
/*上行IDLE队列大小*/
#define BST_PAL_DL_QUE_SIZE             (256)

/*封装OSA消息头*/
#define BST_PAL_NetCfgMsgHead(pstMsg,ulRecvPid)\
                    (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid     = UEPS_PID_BASTET;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid   = (ulRecvPid)

/*封装BST发送OSA消息接口*/
#define BST_PAL_NetSendMsg(pMsg) \
                if (VOS_OK != PS_SND_MSG_ALL_CHECK(UEPS_PID_BASTET,(pMsg)))\
                {\
                    BST_RLS_LOG( "BST_PAL_NetSendMsg : Send Msg Fail" );\
                }

/*封装OSA消息申请接口*/
#define BST_PAL_NetAllocMsgWithHdr(MsgLen)  (VOS_VOID *)PS_ALLOC_MSG_ALL_CHECK(\
                                            UEPS_PID_BASTET,(MsgLen))

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/

/*****************************************************************************
 结构名    : CDS_BST_ENTITY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS_BST_ENTITY_STRU结构
*****************************************************************************/
typedef struct{
    CDS_BST_SEND_UL_DATA_FUNC           pfSndItf;
    CDS_BST_RESUME_UL_DATA_FUNC         pfRsmItf;
    LUP_QUEUE_STRU                     *pstDlDataQue;
}BST_PAL_NET_ENTITY_STRU;
/*****************************************************************************
  6 UNION定义
*****************************************************************************/

/*****************************************************************************
  7 全局变量声明
*****************************************************************************/

/*****************************************************************************
  8 函数声明
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_PAL_NetApiPacketResume(
    BST_VOID     *pstItem );

BST_ERR_ENUM_UINT8  BST_PAL_NetApiPacketFree(
    BST_VOID     *pstItem );

BST_ERR_ENUM_UINT8  BST_PAL_NetApiPacketSend (
    BST_UINT32    ulLength,
    BST_UINT8    *pucData );

#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
BST_ERR_ENUM_UINT8  BST_PAL_NetApiPackPppForwd (
    BST_UINT32    ulLength,
    BST_UINT8    *pucData );

BST_UINT32          BST_PAL_NetApiPacketPppRcvd(
    BST_UINT32    ulLength,
    BST_UINT8    *pucData );
#endif

BST_UINT32          BST_PAL_NetApiPacketLen(
    BST_VOID     *pvPkt );

BST_UINT32          BST_PAL_NetApiPacketRcved(
    const BST_UINT8    *pData,
    const BST_UINT32    ulLen );

BST_VOID            BST_PAL_NetSendNetStateMsg(
    BST_UINT32    ulNetState );

BST_VOID            BST_PAL_NetMsgEntry(
    MsgBlock     *pstMsg );

BST_VOID            BST_PAL_NetDLEvtProc(
    BST_VOID );

BST_VOID            BST_PAL_NetApiSetRxMsgEnable(
    BST_UINT32 ulEnableFlag );

BST_VOID            BST_PAL_NetApiSetTxMsgEnable(
    BST_UINT32 ulEnableFlag );

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
