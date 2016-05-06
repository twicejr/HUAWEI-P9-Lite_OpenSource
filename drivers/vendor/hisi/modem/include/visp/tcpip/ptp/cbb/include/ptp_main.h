/******************************************************************************

                  版权所有 (C), 2008-2018, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ptp_main.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2008年5月4日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   :2008-06-19
    作    者   :tanqiang
    修改内容   :按编程规范添加文件头注释，增加在头文件中未定义的函数定义

******************************************************************************/
#ifndef __ptp__main__h__
#define __ptp__main__h__

#ifdef __cplusplus
extern "C" {
#endif


/*PTP队列长度*/
#define PTP_QDEPTH                  2048

/*PTP队列类型标志*/
#define PTP_QMODE                   VOS_Q_FIFO | VOS_Q_SYN

/*PTP内部控制和配置的事件*/
/* Modified by jijianhua00169178, 事件id需要使用高16位, 2012/1/13   问题单号:DTS2012011304845 */
#define PTP_EVT_CTROL_Q             0x00010000
/*End of Modified by jijianhua00169178, 2012/1/13   问题单号:DTS2012011304845 */

/*PTP任务的消息类型*/
typedef enum tagPTP_TMSG_TYPE_E
{
    PTP_TMSG_ANN_REQ,                /*  0 发起ANN协商请求消息类型 */
    PTP_TMSG_SYNC_REQ,               /*  1 发起SYNC协商请求消息类型 */
    PTP_TMSG_ANN_CANCEL,             /*  2 发起ANN协商取消消息类型 */
    PTP_TMSG_ANN_CANCELED,           /*  3 ANN单播协商已取消 */
    PTP_TMSG_DELAY_RESP_SYNC_CANCEL, /*  4 发起delay resp/pdelay resp 和sync协商取消报文消息类型 */
    PTP_TMSG_DELAY_RESP_REQ,         /*  5 多播收到ann的时候启动这个请求 */
    PTP_TMSG_ACCEPT_MASTER_DEL,      /*  6 删除可接受master表中的节点 */

    PTP_TMSG_FSM_INIT,               /*  7 初始化PTP状态机消息类型 */
    PTP_TMSG_FSM_DISABLE,            /*  8 去使能PTP状态机消息类型 */
    PTP_TMSG_FSM_ENABLE,             /*  9 使能PTP状态机消息类型 */
    PTP_TMSG_FSM_LOCKED,             /* 10 给PTP状态机输送LOCKED事件消息类型 */
    PTP_TMSG_FSM_STATE_DECISION,     /* 11 改变手动选源自动选源的时候可能触发此事件 */
    PTP_TMSG_ACCEPT_MASTER_ENABLE,   /* 12 使能可接受Master列表 */
    PTP_TMSG_ACCEPT_MASTER_DISABLE,  /* 13 去使能可接受Master列表 */
}PTP_TMSG_TYPE_E;


/*PTP任务发送消息的数据结构*/
typedef struct tagPTP_TMSG_S
{
   ULONG   ulMsgType       ;   /* 消息类型 */
   ULONG   ulPortNumber;       /* 端口号*/
   PTP_PORT_ADDR_S stDstAddr;  /* 发起单播协商的目的地址*/
   ULONG   ulVrfIndex;
}PTP_TMSG_S;

/*定义PTP 模块系统级信息数据结构，供Shell编程时使用*/
typedef struct tagPTP_SYS_INFO_S
{
    ULONG ulPtpTaskId;      /*PTP任务Id*/
    ULONG ulPtpTimerQId;    /*PTP定时器队列Id*/
    ULONG ulPtpPktQId;      /*PTP报文*/
    ULONG ulPtpCtrolQId;    /*内部控制和配置队列Id*/
}PTP_SYS_INFO_S;


/******************************************************************************
*Func Name   : PTP_InitPtpClock
*Description : 初始化OC/BC PTP时钟实体
*Input       : 
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_Init
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_InitPtpClock();

/******************************************************************************
*Func Name   : PTP_InitTcPtpClock
*Description : 初始化TC时钟实体
*Input       : 
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_Init
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_InitTcPtpClock();

/******************************************************************************
*Func Name   : PTP_InitPtpPort
*Description : 初始化OC/BC时钟端口
*Input       : 
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_InitPtpClock
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_InitPtpPort(PTP_PORT_S * pstPtpPort);

/******************************************************************************
*Func Name   : PTP_InitTcPtpClock
*Description : 初始化TC时钟端口
*Input       : 
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_InitTcPtpClock
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_InitTcPtpPort(PTP_TC_PORT_DS_S* pstTcPtpPort);

/******************************************************************************
*Func Name   : PTP_SetPtpPktRcvEventId
*Description : 设置PTP任务接收报文的事件ID。注意用户定义时不要PTP内部的冲突；
*Input       : 
*Output      : PTP_SYS_INFO_S* pstPtpSysInfo: PTP系统资源信息;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_Init
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_SetPtpPktRcvEventId(ULONG ulEventId);

/******************************************************************************
*Func Name   : PTP_GetPtpSysInfo
*Description : 获取PTP模块的系统资源信息，供外围的Shell模块实现报文收发使用。
*Input       : 
*Output      : PTP_SYS_INFO_S* pstPtpSysInfo: PTP系统资源信息;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_Init
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_GetPtpSysInfo(PTP_SYS_INFO_S* pstPtpSysInfo);

/******************************************************************************
*Func Name   : PTP_StartAnnReq
*Description : 处理PTP_TMSG_ANN_REQ命令，发起ann单播协商请求
*Input       : ulPtpPortNumber:  端口号
               *pstUnicastMaster: 针对发起的节点
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartAnnReq(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);

/******************************************************************************
*Func Name   : PTP_StartSendAnnReq
*Description : 发起ann单播协商请求，由PTP_StartAnnReq调用
*Input       : ulPtpPortNumber  : 端口号
             : *pstUnicastMaster: 针对发起的节点
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_StartAnnReq
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
* 2011-12-2        chixiang 198096        Create
*******************************************************************************/
ULONG PTP_StartSendAnnReq(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);

/******************************************************************************
*Func Name   : PTP_PreSendAnnReq
*Description : start req预处理:针对unicast master 进行状态检查，为发起请求作准备
*Input       : *pstUnicastMaster: 针对发起的节点
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_StartAnnReq
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
* 2011-12-2        chixiang 198096        Create
*******************************************************************************/
ULONG PTP_PreSendAnnReq(PTP_UNI_MASTER_NODE_S *pstUnicastMaster);


/******************************************************************************
*Func Name   : PTP_StartSyncReq
*Description : 处理PTP_TMSG_SYNC_REQ命令，发起SYNC单播协商请求
*Input       : ulPtpPortNumber:  端口号
               *pstUnicastMaster: 针对发起的节点
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartSyncReq(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);

/******************************************************************************
*Func Name   : PTP_StartMultiDelayRespReq
*Description : 多播模式下发起delay resp单播协商请求
*Input       : ulPtpPortNumber:  端口号
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartMultiDelayRespReq(ULONG ulPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr);


/*******************************************************************************
*    Func Name: PTP_StartMasterDelayCancel
* Date Created: 2012-09-19
*       Author: limin00188004
*  Description: 1588 PTP支持多TLV处理和协商链路单独删除
*        Input: USHORT usPortNumber:
*               PTP_UNI_SLAVE_NODE_S *pstUnicastSlave:
*               PTP_PPI_S *pstPtpPpi:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-19   limin00188004           Create
*
*******************************************************************************/
ULONG PTP_StartMasterDelayCancel(USHORT usPortNumber, 
    PTP_UNI_SLAVE_NODE_S *pstUnicastSlave, PTP_PPI_S *pstPtpPpi);

/*******************************************************************************
*    Func Name: PTP_StartMasterSyncCancel
* Date Created: 2012-09-19
*       Author: limin00188004
*  Description: 1588 PTP支持多TLV处理和协商链路单独删除
*        Input: USHORT usPortNumber:
*               PTP_UNI_SLAVE_NODE_S *pstUnicastSlave:
*               PTP_PPI_S *pstPtpPpi:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-19   limin00188004           Create
*
*******************************************************************************/
ULONG PTP_StartMasterSyncCancel(USHORT usPortNumber, 
    PTP_UNI_SLAVE_NODE_S *pstUnicastSlave, PTP_PPI_S *pstPtpPpi);

/******************************************************************************
*Func Name   : PTP_StartSlaveDelaySyncCancel
*Description : SLAVE 侧 处理PTP_TMSG_DELAY_RESP_SYNC_CANCEL命令，发起delay resp/pdelay resp和sync的单播取消
*Input       : ulPtpPortNumber:  端口号
               *pstUnicastMaster: 针对发起的节点
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartSlaveDelaySyncCancel(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);

/******************************************************************************
*Func Name   : PTP_StartMasterDelaySyncCancel
*Description : Master 侧 处理PTP_TMSG_DELAY_RESP_SYNC_CANCEL命令，发起delay resp/pdelay resp和sync的单播取消
*Input       : ulPtpPortNumber:  端口号
               *pstUnicastSlave: 针对发起的节点
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartMasterDelaySyncCancel(ULONG ulPtpPortNumber, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave);

/******************************************************************************
*Func Name   : PTP_StartSlaveAnnCancel
*Description : SLAVE侧发起单播取消 处理PTP_TMSG_ANN_CANCE命令
*Input       : ulPtpPortNumber:  端口号
               *pstUnicastMaster: 针对发起的节点
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartSlaveAnnCancel(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);

/******************************************************************************
*Func Name   : PTP_StartMasterDelaySyncCancel
*Description :  MASTER 测发起单播取消, 处理PTP_TMSG_ANN_CANCE命令，发起ann单播协商取消
*Input       : ulPtpPortNumber:  端口号
               *pstUnicastSlave: 针对发起的节点
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartMasterAnnCancel(ULONG ulPtpPortNumber, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave);

/******************************************************************************
*Func Name   : PTP_ProcCtrolMsgAnnReq
*Description : 处理Control 消息的ann req
*Input       : *pstPtpRcvMsg  传入的消息参数
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_ProcCtrolMsgAnnReq(PTP_TMSG_S *pstPtpRcvMsg);

/******************************************************************************
*Func Name   : PTP_ProcCtrolMsgSyncReq
*Description : 处理Control 消息的sync req
*Input       : *pstPtpRcvMsg  传入的消息参数
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_ProcCtrolMsgSyncReq(PTP_TMSG_S *pstPtpRcvMsg);

/******************************************************************************
*Func Name   : PTP_ProcCtrolMsgAnnCancel
*Description : 处理Control 消息的announce cancel
*Input       : *pstPtpRcvMsg  传入的消息参数
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_ProcCtrolMsgAnnCancel(PTP_TMSG_S *pstPtpRcvMsg);

/******************************************************************************
*Func Name   : PTP_ProcCtrolMsgSyncCancel
*Description : 处理Control 消息的sync cancel
*Input       : *pstPtpRcvMsg  传入的消息参数
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_ProcCtrolMsgSyncCancel(PTP_TMSG_S *pstPtpRcvMsg);

/******************************************************************************
*Func Name   : PTP_ProcControlEvent
*Description : 处理Control 事件
*Input       : 
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_ProcControlEvent();


/******************************************************************************
*Func Name   : PTP_TaskMain
*Description : PTP主任务
*Input       : 
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_Init
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
VOID PTP_TaskMain(UINTPTR ul1, UINTPTR ul2, UINTPTR ul3, UINTPTR ul4);

/******************************************************************************
*Func Name   : PTP_InitPtpDev
*Description : 分配设备内存,并初始化
*Input       : ulPtpDevType:  设备类型参数
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_InitPtpDev(ULONG ulPtpDevType);

/******************************************************************************
*Func Name   : PTP_FreeRes
*Description : 释放队列以及设备,任务相关的资源
*Input       : 
*Output      : 
*Return      : 
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
VOID PTP_FreeRes();

/*******************************************************************************
*    Func Name: PTP_FreeAllSlaveTbl
* Date Created: 2011-11-14
*       Author: jijianhua00169178
*  Description: 
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 释放所有的slaveTbl. 基于链表中所有的slave 节点已经释放条件下调用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-14   jijianhua00169178       Create
*
*******************************************************************************/
VOID PTP_FreeAllSlaveTbl();

/******************************************************************************
*Func Name   : PTP_FreeAllSlaves
*Description : 释放所有SLAVE节点资源
*Input       : 
*Output      : 
*Return      : 
*Caution     :
*Calls       :
*Called by   : PTP_UnInit
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-07-21            lishenchuan            create
*******************************************************************************/
VOID PTP_FreeAllSlaves();

ULONG PTP_StartDelayReq(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);



VOID PTP_FreeAllAddrVrfNodes(USHORT usPortNum);


VOID PTP_FreeAllVrfSockNodes();


#ifdef __cplusplus
}
#endif

#endif


