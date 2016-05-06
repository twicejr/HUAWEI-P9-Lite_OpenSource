/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                                 ptp_ann.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP
*  Date Created: 2008-06-02
*        Author: 谭强
*   Description: Announce消息接收和发送处理h文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME               DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-06-02    谭强        Create
*
*******************************************************************************/
#ifndef _PTP_ANN_H_
#define _PTP_ANN_H_

#include "tcpip/public/tcpip_config.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "ptp/cbb/include/ptp_base_inc.h"
#include "ptp/cbb/include/ptp_inc.h"


/******************************************************************************
*Func Name   : PTP_ANN_RcvMsg
*Description : announce消息接收处理
*Input       : UCHAR              *pucBuffer        报文内容
*              PTP_SRCIPUDPINFO_S *pstSrcAddrInfo   报文源地址信息
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
ULONG PTP_ANN_RcvMsg (UCHAR *pucBuffer, ULONG ulPktLen,PTP_ADDRINFO_S *pstAddrInfo);

/******************************************************************************
*Func Name   : PTP_ANN_SndMsg
*Description : announce消息接收处理
*Input       : PTP_PORT_S     *pstPtpPort     时钟端口控制块
*              PTP_ADDRINFO_S *pstAddrInfo    接收/发送报文的地址以及UDP信息
*              PTP_PORT_ID_S  *pstDstPortId   目的端口
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
ULONG PTP_ANN_SndMsg( PTP_PORT_S *pstPtpPort, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave);

/******************************************************************************
*Func Name   : PTP_PKT_PrintHeader
*Description : 事件消息报文打印接口
*Input       : PTP_MSGHEADER_S *pstMsgHeader 消息头
*              ULONG           ulFlag        标记:0-发送报文;非0-接收报文
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码                             
*Caution     : 
*Calls       : 
*Called by   : 
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-16            wangchengyang  Create
*******************************************************************************/
VOID PTP_ANN_PrintAnn(PTP_ANNOUNCE_MSG_S *pstAnnMsg, PTP_ADDRINFO_S *pstAddrInfo, ULONG ulFlag);

/******************************************************************************
*Func Name   : PTP_ANN_ResetAnnRecvTimer
*Description : 刷新ANN接收定时器
*Input       : PTP_PORT_S *pstPtpPort:时钟端口
*              PTP_ADDRINFO_S *pstAddrInfo:地址信息
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码                             
*Caution     : 
*Calls       : 
*Called by   : 
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-18           yaochengliang   Create
*******************************************************************************/
ULONG PTP_ANN_ResetAnnRecvTimer(PTP_PORT_S *pstPtpPort,PTP_ADDRINFO_S *pstAddrInfo);
/*******************************************************************************
*    Func Name: PTP_WarningOut
* Date Created: 2009-08-13
*       Author: xujun57575
*  Description: 
*        Input: ULONG ulWarnID:
*               VOID *pWarnParam:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-13   xujun57575              Create
*
*******************************************************************************/
VOID PTP_WarningOut(ULONG ulWarnID, VOID *pWarnParam);

extern VOID PTP_ANN_ClassBuild(PTP_ANNOUNCE_MSG_S *pstAnnMsg, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave,UCHAR ucLocalClass);

#ifdef __cplusplus
}
#endif

#endif 
