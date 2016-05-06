/************************************************************************
 *                                                                      *
 *                          rpc_pri.H									*
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/06/14                                      *
 *  Author:             19742                                                *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *             Copyright 2000 - 2002 HuaWei Tech, Inc.                  *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  请在这里添加以下内容：                                              *
 *    1、这个头文件是哪个模块的哪个头文件；                             *
 *    2、这个头文件中都定义了哪些东西（内容）；                         *
 *    3、什么样的C文件需要包含该头文件；                                *
 *    4、该头文件对应的文档的名称。                                       *
 *                                                                      *
 ************************************************************************/

/*#if( VRP_MODULE_TEMPLETE == VRP_YES )*/

#ifndef _RPC_PRI_H_
#define _RPC_PRI_H_


#ifdef	__cplusplus
extern "C"{
#endif


#define IPC_RPC_MODULE			0x10000011


#define IPC_RPC_TOTAL_MODULECB_NUMBER		100
#define	IPC_RPC_MAX_PEND_MESSAGE			1000
#if VRP_OPTIM_TASK == VRP_YES
#define IPC_RPC_MS_PER_TICK					200
#else
#define IPC_RPC_MS_PER_TICK					10
#endif

#define IPC_RPC_MAX_RCVQUELEN				1000
#if (VRP_PRODUCT_GSR == VRP_YES)
#define	IPC_RPC_RESENDTIMES					10
#endif

#define IPC_RPC_SUCCESS				0
#define ERR_IPC_RPC_INIT			1
#define ERR_IPC_RPC_NOMEM			2
#define ERR_IPC_RPC_TIMEOUT			3
#define ERR_IPC_RPC_TOMANYMSG		4
#define ERR_IPC_RPC_MDLCB			5

#if (VRP_PRODUCT_GSR == VRP_YES)
#define ERR_IPC_SND_FAIL             6
#endif

/****************************************************
*				RPC 消息头							*
****************************************************/
typedef struct tagIPC_RPC_MESSAGE_HEAD
{
	USHORT	usMessageType;			/* 消息类型		*/
	USHORT	usPriority;				/* 优先级		*/
	ULONG	ulSrcModuleID;			/* 发送模块ID	*/
	ULONG	ulDstModuleID;			/* 目的模块ID	*/
	ULONG	ulSequence;				/* 序号			*/
}IPC_RPC_MESSAGE_HEAD_S;

#define	IPC_RPC_MESSAGE_TYPE_SEND			0x0001
#define	IPC_RPC_MESSAGE_TYPE_REPLY			0x0002
#define	IPC_RPC_MESSAGE_ERR_NULL			0x0003	
#define	IPC_RPC_MESSAGE_ERR_DSTMDL			0x0004	

#define IPC_RPC_GET_MESSAGE_HEAD(p) \
	(IPC_RPC_MESSAGE_HEAD_S*)((UCHAR*)p-sizeof(IPC_RPC_MESSAGE_HEAD_S))
/****************************************************
*				RPC 消息控制块						*
****************************************************/
typedef struct tagIPC_RPC_MESSAGE_CB
{
#if (VRP_PRODUCT_GSR == VRP_YES)    
	ULONG	ulSrcModuleId;			/* 缓存RPS发送时的源模块号,
									   用于与接口板通信的适配.
									   added by huangmq */
#endif

	ULONG	ulSequence;				/* 消息的序号				*/
	ULONG	ulSendType;				/* 同步取 or 异步取			*/
#define	IPC_RPC_SEND_TYPE_SYNC			0
#define	IPC_RPC_SEND_TYPE_ASYNC			1
	ULONG	ulMillSec;				/* 定时器的尺度				*/
	LONG	lRunOut;				/* 余下的超时时间			*/
	IPC_RPC_MESSAGE_HEAD_S	*pMsg;	/* 消息指针					*/
	ULONG	ulDstNode;				/* 目的节点(槽) 2k/11/08	*/
	
	IPC_RPC_SENDFINISH_NOTIFY	pfSendFinish;
									/* 异步取发送结束通知函数	*/
	ULONG	ulSendLen;				/* 请求消息的长度,异步取	*/
	ULONG	ulSavedData;			/* 用户暂时保存的数据(发送时的),异步取*/

	ULONG	ulSemphoreID;			/* 信号量					*/

	IPC_RPC_MESSAGE_HEAD_S	*pReceiveMsg; 
									/* 接收到的消息,同步取		*/
	ULONG	ulReceiveDataLen;		/* 接收的数据的长度,同步取	*/

	struct tagIPC_RPC_MESSAGE_CB	*pstNext;	/* 下一个消息	*/
	struct tagIPC_RPC_MESSAGE_CB	*pstPrev;	/* 上一个消息	*/
}IPC_RPC_MESSAGE_CB_S;


/****************************************************
*				RPC 模块回调控制块						*
****************************************************/
typedef struct tagIPC_RPC_MODULE_CB
{
	ULONG	ulStatus;				/* 使用状态		*/
	ULONG	ulModuleID;				/* 模块ID		*/
	IPC_RPC_RECEIVE_NOTIFY	pfReceiveNotify;	/* 接收回调函数 */
}IPC_RPC_MODULE_CB_S;

#define	IPC_RPC_MODULE_CB_STS_NULL		0x00000000
#define	IPC_RPC_MODULE_CB_STS_USED		0x00000001

/****************************************************
*				RPC 私有函数(内部使用)				*
****************************************************/
VOID IPC_RPC_Notify_Func ( ULONG ulFlag, ULONG ulChID, ULONG ulDstNode,
					ULONG ulDstChannelId, VOID *pData, ULONG ulLen);
VOID IPC_RPC_ReceiveReply(IPC_RPC_MESSAGE_HEAD_S *pstRPCMsg, ULONG ulRPCDataLen);
VOID IPC_RPC_Callback(IPC_RPC_MESSAGE_HEAD_S *pstRPCMsg, ULONG ulRPCDataLen,
					  ULONG ulSrcNode);
VOID IPC_RPC_SendCallFinish(IPC_RPC_MESSAGE_HEAD_S *pstRPCMsg, ULONG ulDstNode, ULONG ulIPCLen);
VOID IPC_RPC_SendReplyFinish(IPC_RPC_MESSAGE_HEAD_S *pstRPCMsg, ULONG ulDstNode);
VOID IPC_RPC_ReplyTask(ULONG ulArg1, ULONG ulArg2, ULONG ulArg3, ULONG ulArg4);

ULONG IPC_RPC_InsMsg(IPC_RPC_MESSAGE_CB_S *pMsg);
ULONG IPC_RPC_ExtrMsg(IPC_RPC_MESSAGE_CB_S *pMsg);
VOID IPC_RPC_PassTime(ULONG ulMillSec);
VOID IPC_RPC_TimerTask(ULONG ulArg1,ULONG ulArg2,ULONG ulArg3,ULONG ulArg4);
VOID IPC_RPC_Notify(IPC_RPC_MESSAGE_HEAD_S *pstRPCMsg, ULONG ulRPCDataLen,
					  ULONG ulSrcNode);

VOID IPC_RPC_SyncDealWithIPCSendFail(ULONG ulMsgSequence);/* wuxiaoqian, 2k/11/08*/
VOID IPC_RPC_AsyncDealWithIPCSendFail(ULONG ulMsgSequence);/* wuxiaoqian, 2k/11/08*/



#if (VRP_YES == VRP_VERSION_5)
#define VRP_RPCQ_EVT_TIMER      0x0004
#define VRP_RPCQ_EVT_MESSAGE    0x0008

extern ULONG ulVRPTID_SOCK;
extern ULONG ulSOCKTmrQueID;
extern ULONG gulSockRunReady;

#define VRP_RPC_DELAY_COUNT     100
VOID IPC_RPC_TimerCallback (VOID *pData);
#endif


#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif	/* end of _RPC_PRI_H_ */
