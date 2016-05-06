

/*#if( VRP_MODULE_TEMPLETE == VRP_YES )*/
#ifndef	_IPC_INC_H_
#define	_IPC_INC_H_

#ifndef VOS_INCLUDE_IPC
#define VOS_INCLUDE_IPC     VOS_NO
#endif

#ifdef	__cplusplus
extern "C"{
#endif

/* define a macro for debug and stat of IPC RPC VP */
#define  VOS_IPC_DEBUGANDSTAT           VRP_YES

/* 
 * Added by Pradeep Shastry for IPC Checksum Calculation, HA_IPC_DEBUG macro
 * is used for main and I/O boards and HA_IPC_INCLUDE_CHECKSUM is used only for 
 * main board.
 */

#if (VRP_YES == VRP_VERSION_5)

#if (VRP_YES == VRP_PRODUCT_8070)
#define HA_IPC_DEBUG           VRP_YES
#endif

#if ((VRP_YES == VRP_PRODUCT_WVRP) && (VRP_YES == VRP_DISTRIBUTED))
#define HA_IPC_DEBUG           VRP_YES
#endif

#endif

#if ((VRP_YES == VRP_MODULE_HA_SLAVE2MAIN) && (VRP_YES == HA_IPC_DEBUG))
#define HA_IPC_INCLUDE_CHECKSUM             VRP_YES
#endif


/*
the following two parameter can be configured
*/
/*#define IPC_NODE_TOTAL_NUMBER			(4*5)*/ /*需要为4的倍数，以方便字节对齐*/
#if (VRP_PRODUCT_GSR != VRP_YES)
    /*BYDD001520 begin,anhongjie 2003-12-15*/ 
    #if(VRP_CENTERALIZATION == VRP_YES)
        #define IPC_NODE_TOTAL_NUMBER			1	/*集中式环境下只存在板内IPC,最大节点号为1*/
    #else
        #define IPC_NODE_TOTAL_NUMBER			VRP_MAX_BOARD_NUM	/* mod by wuxiaoqian 2k/10/05*/
    #endif
    /*BYDD001520 end,anhongjie 2003-12-15*/ 
#else
#define IPC_NODE_TOTAL_NUMBER			19	/* mod by wuxiaoqian 2k/10/05*/
#endif

#if(VRP_PRODUCT_GSR == VRP_YES )
#define IPC_CHANNEL_TOTAL_NUMBER		/*(8*10)*/256
#define IPC_GROUP_TOTAL_NUMBER			(8*10)
#else
/* Increased to 85, after NE80 code sync.{B02D21 smk1 problem} 
   by satya 2004-08-17 */
#if (VRP_YES == VRP_VERSION_5)
#define IPC_CHANNEL_TOTAL_NUMBER		((8*10)+5) 
#define IPC_GROUP_TOTAL_NUMBER			((8*10)+5)
#else
#define IPC_CHANNEL_TOTAL_NUMBER		(8*10)
#define IPC_GROUP_TOTAL_NUMBER			(8*10)
#endif
#endif

#if (VRP_PRODUCT_GSR == VRP_YES)
extern ULONG SRM_GetMaxSlot(ULONG ulBoardType);
extern ULONG SRM_GetProductType(VOID);

#define IPC_LPUNODE_FOR_NE80VER24S   SRM_GetMaxSlot(3)
#define IPC_NODE_FOR_NE80VER24S      IPC_LPUNODE_FOR_NE80VER24S + (SRM_GetProductType() == 3 ? 1 : 2)
#endif

#define IPC_FRAGMENT					1

#define IPC_MEMORY_USER_INFO			0x12345678
#if (VRP_YES == VRP_VERSION_5)

#define IPC_MAX_REGISTER_ITEM       128

#endif


extern ULONG g_ulSelfNode;
#define IPC_SELF_NODE_ID		g_ulSelfNode
extern ULONG DRV_GetPhySlot(void);

#if (VRP_PRODUCT_GSR == VRP_YES)
/*cxx*/
#define IPC_EV_RECEIVE				0x0100
#define VP_EV_RECEIVE               0x0200
#define MPU_A                       MPUA    
#define MPU_B                       MPUB
#define IPC_LPU_NODE_TOTAL_NUMBER   16
#define IPC_RECV_QUE_LEN            2000
/*end cxx*/

typedef struct tagMacHead  /*add by ctx*/
{
	UCHAR   ucReserve[20];
	UCHAR	ucSrcMacAddr[6];
	UCHAR	ucDstMacAddr[6];
	USHORT	usLength;
	USHORT	usProtocol;
}SMacHead;
#endif

typedef struct tagIPC_MessageCommon
{
#if (VRP_PRODUCT_GSR == VRP_YES)
    SMacHead sMacHead;
#endif
	UCHAR ucMemoryId;/*no change, to transmit this element, the only meaning is to occupy place, when transmit, need not reassign value, intr, drv*/
	UCHAR ucIsSynSend;/*no change, intr*/

	UCHAR ucIsLastFragment;/*no change, frg*/
	
	UCHAR ucMessageType;/*no change, syn request, syn ack, data with ack, pure ack, que*/
	USHORT usSourceNodeId;/*no change,intr*/
	USHORT usSourceChannelId;/*no change,intr*/
	USHORT usDestinationNodeId;/*change, intr, que*/
	USHORT usDestinationChannelId;/*no change, intr*/
	USHORT usAckNumber;/*change, que*/
	USHORT usSendSequenceNumber;/*change, que*/
	ULONG ulDataLength;/*no change, intr*/
#if (VRP_PRODUCT_GSR == VRP_YES)
	UCHAR ucReserved[28];   /*add by ctx*/
#endif
    /*
     * Added by Pradeep Shastry, for IPC Checksum calculation. This part of the code should
     * there for both main and I/O boards.
     */
#if (VRP_YES == HA_IPC_DEBUG)
    ULONG ulIPCCksum;
#endif
}IPC_MESSAGE_COMMON_S;/*20 bytes, 11 elements*/


typedef struct tagIPC_SendMessage
{
	/*for send status*/
	ULONG ulSemphoreId;/*no change, intr*/
	USHORT usDestinationNodeTotalNumber;/*no change, intr*/
	USHORT usResponseNodeNumber;/*modified by notify, intr*/
	UCHAR ucSendStatusToDestinationNode[IPC_NODE_TOTAL_NUMBER];/* 4 * N set by send finish notify, intr*/
	struct tagIPC_SendMessage * pstOriginalSendMessage;/*only used when need fragment and in the last fragment, frg*/
	ULONG ulDestinationNodeId;/*no change, when multicast, group id, intr*/

	/*for transmit*/
	IPC_MESSAGE_COMMON_S stMessageCommon;
	
}IPC_SEND_MESSAGE_S;

typedef struct tagIPC_ReceiveMessage
{
	IPC_MESSAGE_COMMON_S stMessageCommon;
}IPC_RECEIVE_MESSAGE_S;


/*------------------------------------------------------------------------*/
/*                          相 关 宏 定 义                                */
/*------------------------------------------------------------------------*/
/* 消息头大小 - size of message envolope */
#define IPC_SEND_MESSAGE_HEAD_SIZE			sizeof(IPC_SEND_MESSAGE_S)
#define IPC_RECEIVE_MESSAGE_HEAD_SIZE		sizeof(IPC_RECEIVE_MESSAGE_S)
#define IPC_COMMON_MESSAGE_HEAD_SIZE		sizeof(IPC_MESSAGE_COMMON_S)

/* 从数据获取消息头 */
#define IPC_GET_COMMON_MESSAGE_HEAD(p)	\
		((IPC_MESSAGE_COMMON_S *)((ULONG)(p) - IPC_COMMON_MESSAGE_HEAD_SIZE))
#define IPC_GET_RECEIVE_MESSAGE_HEAD(p)	\
		((IPC_RECEIVE_MESSAGE_S *)((ULONG)(p) - IPC_RECEIVE_MESSAGE_HEAD_SIZE))
#define IPC_GET_SEND_MESSAGE_HEAD(p)	\
		((IPC_SEND_MESSAGE_S *)((ULONG)(p) - IPC_SEND_MESSAGE_HEAD_SIZE))

/* 消息内存来源 - source of memory */
#define IPC_MEMORY_SOURCE_VOS_SEND			0x00000001
#define IPC_MEMORY_SOURCE_DRIVER_RECEIVE	0x00000002


/* 通知IPC通道的使用者消息发送成功或失败以及消息接收 */
typedef VOID (*IPC_NOTIFY_FUNC)
(
    ULONG ulFlag,       /* 消息标志，表示消息发送成功、失败或接收到消息   */
    ULONG ulSrcChID,    /* IPC通道号                                      */
    ULONG ulDstNode,    /* 目的节点号，在组播发送时表示组播组ID           */
    ULONG ulDstChID,    /* 目的通道号									  */
    VOID *pData,        /* 发送或接收到的数据                             */
    ULONG ulLen         /* 数据长度                                       */
);

/* 向已经注册的管理实体报告节点状态的改变 */
typedef VOID (*IPC_REPORT_FUNC)
(
    ULONG ulNode,       /* 节点ID                                         */
	ULONG ulQueueId,    /* 队列号(发送或接收队列)                         */
    ULONG ulStatus      /* 节点状态                                       */
);

/* IPC底层发送函数 */
typedef ULONG (*IPC_SEND_FUNC)
(
    VOID *pData,        /* 数据指针                                       */
    ULONG ulLen,        /* 数据长度                                       */
    ULONG ulDstNode,    /* 目的节点号                                     */
    ULONG ulFlag        /* 发送类型（暂时无用）                           */
);

/* IPC底层接收函数 */
typedef ULONG (*IPC_RECV_FUNC)
(
    VOID *pData         /* 数据指针                                       */
);

/* IPC底层内存释放函数 */
typedef VOID (*IPC_FREE_FUNC)
(
     VOID *pData        /* 数据指针                                       */
);

/* IPC发送消息成功/失败或接收到消息时的通知方式 */
#define		IPC_NOTI_VIA_NONE	0x00000000
#define     IPC_NOTI_VIA_QUEUE  0x00000001      /* 通过消息通知           */
#define     IPC_NOTI_VIA_FUNC   0x00000002      /* 通过回调函数通知       */

/* 消息发送模式字 */
#define     IPC_MSG_TM_ASYNC    0x00000000      /* 异步发送               */
#define     IPC_MSG_TM_SYNC     0x00000004      /* 同步发送               */
#define     IPC_MSG_TM_MULTI    0x00000010      /* 组播                   */
#define     IPC_MSG_TM_BROAD    0x00000020      /* 广播                   */
#if (VRP_PRODUCT_GSR == VRP_YES)
#define     IPC_MSG_TM_MULTI2   0x00000080
#endif
#define		IPC_PRI1			0x00010000
#define		IPC_PRI2			0x00020000
#define		IPC_PRI3			0x00030000
#define		IPC_PRI4			0x00040000


/* 消息目标节点、通道以及源节点、通道宏 */
/* 消息目标节点、通道以及源节点、通道宏 */
#define		IPC_GET_SOURCE_NODEID(p)\
	(IPC_GET_COMMON_MESSAGE_HEAD(p)->usSourceNodeId)

#define		IPC_GET_SOURCE_CHANNELID(p)\
	(IPC_GET_COMMON_MESSAGE_HEAD(p)->usSourceChannelId)
	
#define		IPC_GET_DESTINATION_NODEID(p)\
	(IPC_GET_COMMON_MESSAGE_HEAD(p)->usDestinationNodeId)
	
#define		IPC_GET_DESTINATION_CHANNELID(p)\
	(IPC_GET_COMMON_MESSAGE_HEAD(p)->usDestinationChannelId)


/* 消息状态，用于通知IPC通道的使用者 */
#define     IPC_NOTI_FLG_RXDATA			0x00000001      /* 收到消息               */
#define     IPC_NOTI_FLG_SEND_FINISH	0x00000002      /* 发送完毕               */

/* 状态数组中, 各个节点的发送状态 */
#define IPC_SEND_STS_FAL			0x00000002			/* 发送成功		*/
#define IPC_SEND_STS_SUCC			0x00000001			/* 发送失败		*/
#define IPC_SEND_STS_NULL			0x00000000			/* 没有向此节点发送 */


/**************************************************************************/
/*                      Ｉ Ｐ Ｃ 函 数 申 明                              */
/*------------------------------------------------------------------------*/
/*                                                                        */
/*  IPC_Init            初始化IPC                                         */
/*  IPC_RegReport       注册IPC报告方式                                   */
/*  IPC_Create          创建IPC通道                                       */
/*  IPC_Delete          删除IPC通道                                       */
/*  IPC_AllocMsg        分配消息内存                                      */
/*  IPC_FreeMsg         释放消息内存                                      */
/*  IPC_Send            发送消息                                          */
/*	IPC_GetSendStatus	获取发送状态									  */
/*  IPC_CreateGroup     创建组播组                                        */
/*  IPC_JoinGroup       加入组播组                                        */
/*  IPC_LeaveGroup      离开组播组                                        */
/*  IPC_DeleteGroup     删除组播组                                        */
/*  IPC_AddDriver       注册驱动程序                                      */
/*                                                                        */
/**************************************************************************/
/* 初始化IPC */
ULONG IPC_Init ( );                 /* 返回：0成功，其他为错误码          */

/* 注册IPC报告方式 */
ULONG IPC_RegReport                 /* 返回：0成功，其他为错误码          */
(
    ULONG           ulFlag,         /* 报告方式                           */
    ULONG           ulQueueID,      /* 队列ID                             */
    IPC_REPORT_FUNC pfReport        /* 回调函数                           */
);

/* 创建IPC通道 */
ULONG IPC_Create                    /* 返回：0成功，其他为错误码          */
(
    ULONG           ulIpcChID,     /* 返回IPC通道ID                      */
    ULONG           ulFlag,         /* 通知方式                           */
    ULONG           ulQueueID,      /* 队列ID                             */
    IPC_NOTIFY_FUNC pfNotify        /* 回调函数                           */
);

/* 删除IPC通道 */
ULONG IPC_Delete                    /* 返回：0成功，其他为错误码          */
(
    ULONG   ulIpcChID               /* IPC通道ID                          */
);

/* 分配消息内存 */
VOID *IPC_AllocMsg                  /* 返回：地址指针，0失败              */
(
    ULONG   ulSize,                 /* 内存大小                           */
    ULONG   ulUserInfo              /* 用户信息                           */
);

/* 释放消息内存 */
VOID IPC_FreeMsg                    /* 返回：无                           */
(
    VOID    *pData                  /* 数据指针                           */
);

/* 发送消息 */
ULONG IPC_Send                      /* 返回：0成功，其他为错误码          */
(
    ULONG   ulIpcChId,              /* IPC通道ID                          */
    ULONG   ulDstNode,              /* 目的节点号                         */
    ULONG   ulDstIpcChId,           /* 目的实体号                         */
    ULONG   ulMode,                 /* 发送模式                           */
    VOID    *pMsg,                  /* 消息数据指针                       */
    ULONG   ulLen,                  /* 消息数据长度                       */
    ULONG   ulUserInfo              /* 用户信息                           */
);

/* 获取发送状态 */
ULONG IPC_GetSendStatus 
( 
	UCHAR ucSendStatus[],			/* 发送状态数组                       */
	VOID* pMsg						/* 消息数据指针                       */
 );

/* 创建组播组 */
ULONG IPC_CreateGroup               /* 返回：0成功，其他为错误码          */
(
    ULONG   *pulGroupID             /* 返回组播组ID                       */
);

/* 加入组播组 */
ULONG IPC_JoinGroup                 /* 返回：0成功，其他为错误码          */
(
    ULONG   ulGroupID,              /* 组播组ID                           */
    ULONG   ulDstNode
);

/* 退出一个组播组 */
ULONG IPC_LeaveGroup                /* 返回：0成功，其他为错误码          */
(
    ULONG ulGroupID,                /* 组播组ID                           */
    ULONG ulDstNode                 /* 目的实体所在节点                   */
);

/* 删除组播组 */
ULONG IPC_DeleteGroup               /* 返回：0成功，其他为错误码          */
(
    ULONG ulGroupID                 /* 组播组ID                           */
);

/* 增加IPC底层接口 */
ULONG IPC_AddDriver                 /* 返回：0成功，其他为错误码          */
(
    ULONG           ulNode,         /* 节点号                             */
    IPC_RECV_FUNC  *ppfRcvFunc,     /* 存储接收函数指针                   */
    IPC_SEND_FUNC   pfSdnFunc,      /* 发送函数指针                       */
    IPC_FREE_FUNC   pfFreeFunc,     /* 内存释放函数指针                   */
    ULONG           ulMaxMTU        /* 最大数据长度                       */
);

/* 得到IPC发送队列当前可用的空闲长度 */
ULONG IPC_GetQueFreeLength(ULONG ulDstNode, ULONG ulDstIpcChId, ULONG ulMode);

#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */
#endif	/* end of _TEMPLETE_H_ */

/*#endif*/	/* end of VRP_MODULE_TEMPLETE */

/* end of templete.h */
