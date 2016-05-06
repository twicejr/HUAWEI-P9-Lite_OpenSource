/************************************************************************
 *                                                                      *
 *                          rpc_inc.H									*
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

#ifndef _RPC_INC_H_
#define _RPC_INC_H_


#ifdef	__cplusplus
extern "C"{
#endif

/****************************************************
*				RPC 接收回调函数						*
****************************************************/
typedef VOID (*IPC_RPC_RECEIVE_NOTIFY)
(
		ULONG ulSrcNode,				/* 源节点ID			*/
		ULONG ulSrcModuleID,			/* 源模块ID			*/
		VOID *pReceiveData,				/* 接收的数据		*/
		ULONG ulReceiveDataLen,			/* 接收数据的长度	*/
		VOID **ppSendData,				/* 发送的数据		*/
		ULONG *pulSendDataLen			/* 发送数据的长度	*/
);

/****************************************************
*			RPC 发送结束(成功/超时)回调函数			*
****************************************************/
typedef VOID (*IPC_RPC_SENDFINISH_NOTIFY)
(
	ULONG ulFlag,
#define IPC_RPC_MESSAGE_ERR_TIMEOUT		0		/* 发送超时				*/
#define	IPC_RPC_MESSAGE_ERR_MDLCB		1		/* 接收方没有注册		*/
#define IPC_RPC_MESSAGE_NULL			2		/* 接收方没有应答消息空	*/
#define IPC_RPC_MESSAGE_SUCC			3		/* 接收到应答消息		*/
	ULONG ulSrcModuleID,		/* 源模块ID			*/
	ULONG ulDstNode,			/* 目的节点ID		*/
	ULONG ulDstModuleID,		/* 目的模块ID		*/
	VOID *pSendData,			/* 发送数据			*/
	ULONG ulSendLen,			/* 发送数据长度		*/
	ULONG ulTimeOut,			/* 超时时间（ms）	*/
	VOID *pReceiveData,			/* 接收数据指针		*/
	ULONG ulReceiveLen,			/* 接收数据长度		*/
	ULONG ulSavedData			/* 用户暂时保存的数据(发送时的)	*/
);

/****************************************************
*				RPC 初始化							*
****************************************************/
ULONG IPC_RPC_Init();


/****************************************************
*				RPC异步取调用函数					*
****************************************************/
ULONG IPC_RPC_AsyncCall
(
	ULONG ulSrcModuleID,		/* 源模块ID			*/
	ULONG ulDstNode,			/* 目的节点ID		*/
	ULONG ulDstModuleID,		/* 目的模块ID		*/
	ULONG ulPriority,			/* 发送优先级		*/
	VOID *pSendData,			/* 发送数据			*/
	ULONG ulSendLen,			/* 发送数据长度		*/
	IPC_RPC_SENDFINISH_NOTIFY pfSendFinish,
								/* 异步取发送结束通知函数	*/
	ULONG ulTimeOut,			/* 超时时间（ms）	*/
	ULONG ulSavedData			/* 用户暂时保存的数据(发送时的)	*/
);


/****************************************************
*				RPC同步取调用函数					*
****************************************************/
ULONG IPC_RPC_SyncCall
(
	ULONG ulSrcModuleID,		/* 源模块ID			*/
	ULONG ulDstNode,			/* 目的节点ID		*/
	ULONG ulDstModuleID,		/* 目的模块ID		*/
	ULONG ulPriority,			/* 发送优先级		*/
	VOID *pSendData,			/* 发送数据			*/
	ULONG ulSendLen,			/* 发送数据长度		*/
	VOID **ppReceiveData,		/* 接收数据指针		*/
	ULONG *ulReceiveLen,		/* 接收数据长度		*/
	ULONG ulTimeOut				/* 超时时间（ms）	*/
);

/****************************************************
*			RPC 消息分配函数(对外接口)				*
****************************************************/
VOID *IPC_RPC_AllocMsg
(
	ULONG ulSize,				/* 数据区的尺寸		*/
	ULONG ulUserInfo			/* 用户信息			*/
);

/****************************************************
*			RPC 消息释放函数(对外接口)				*
****************************************************/
VOID IPC_RPC_FreeMsg
(
	VOID *pData					/* 释放的数据指针	*/
);

/****************************************************
*			RPC 模块注册(对外接口)					*
****************************************************/
ULONG IPC_RPC_Register
(
	ULONG ulModuleID,			/* 接收请求的模块ID	*/
	IPC_RPC_RECEIVE_NOTIFY pfReceiveNotify
								/* 接收到消息后调用的函数 */
);

#if (VRP_VERSION_5 == VRP_YES)
/****************************************************
*           RPC Setting Message Len in the Header   *
****************************************************/
/* 2003-07-30 Pradeep Shastry for HA Framework */
VOID IPC_RPC_SetMsgLen
(
    VOID *pRPCSendMsg,
    ULONG ulMsgLen
);
#endif

#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif	/* end of _RPC_PRI_H_ */
