/************************************************************************
 *                                                                      *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/25                                      *
 *  Author:                                                             *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *                                                                      *
 ************************************************************************/
 
#include	"vrpcfg.h"

#ifndef _MBUF_TR_H_
#define _MBUF_TR_H_

#ifdef	__cplusplus
extern "C"{
#endif
 
/************************************************************************

	                         private section

  请不要使用本部分的东西

*************************************************************************/


#define MBUF_TR_MAX_RECEIVER_NUMBER 50
#define MBUF_TR_MBUF_TAG_LENGTH ( sizeof(MBUF_S) - sizeof(MBUF_DATABLOCKDESCRIPTOR_S) )
#define MBUF_TR_CHANNEL_NAME "MBUF"
#define MBUF_TR_INIT_MESSAGE_BUFFER_LENGTH 100000

/*CPCI_SEND_MTU 1700*/
#define MBUF_TR_LOW_LEVEL_MTU 1700

#define MBUF_TR_TYPE_NOT_NEAT 0
#define MBUF_TR_TYPE_NEAT 1

#define MBUF_TR_VP_CHANNEL_ID 1

#define	MBUF_TR_RESERVE_HEAD_SPACE 100

typedef struct tagMBUF_TR_Message
{
	USHORT usType;/*由NeatSend产生的还是Send产生的*/
	ULONG ulReceiverId;/*接收者的ID*/
	ULONG ulAttachMessage;/*用户交给NeatSend或Send的ulAttachMessage*/
	UCHAR ucMBufTagA[MBUF_TR_MBUF_TAG_LENGTH];/*mbuf的tag的数据*/
}MBUF_TR_MESSAGE_S;/*message transmit format*/

/* dengyiou 2004-01-31 for performance optimization */
/* 记录IP_TR中USER TAG压缩信息。注意:长度必须是4的整数倍，否则会出错 */
typedef struct tagIP_TR_CompressMessage
{    
	ULONG ulFlag[2];       /* 每一位记录一个ULONG是否被压缩. 0:未压缩;1:压缩 */	
    ULONG ulLen;           /* 压缩后的长度 */
    ULONG ulQueId;         /* 传到目的板后要入的队列ID.以后如果USER TAG中增加了这个域，则这里可以去掉了 */
}IP_TR_COMPRESSMESSAGE_S;

typedef struct tagIP_TR_Message
{    
	ULONG ulType;       /* 对应MBUF_S头中stDataBlockDescriptor的ulType */	
    MBUF_USERTAGDATA_S stUserTagData;    
    ULONG ulMBufType;/*0 IP, 1 MPLS*/
}IP_TR_MESSAGE_S;
typedef struct tagMBUF_TR_DataBlockInfo
{
	/*5 item*/
	ULONG ulType;
	ULONG ulOption;
	ULONG ulOffset;
	ULONG ulDataLength;
	ULONG ulDataBlockLength;
}MBUF_TR_DATA_BLOCK_INFO_S;

typedef struct tagMBUF_TR_ReceiverInfo
{
	/*名字不能重复。名字的有效长度是4个字符，
	这4个字符不必是字符串，即不必以0结束。
	但若以0结束，则0之后的字符将全被存储为0。
	例如：字符串"T1"在系统中的存储将是"T1\0\0"。
	字符串"TEST"在系统中的存储将是"TEST"，
	不存储字符串的0结束标志。*/
	CHAR cReceiverQueueNameA[4];
	/*若用队列接收，存放队列的ID，
	否则，存放0，表示不用*/
	ULONG ulReceiverQueueId;
	/*接收的回调函数，如果不为NULL，则表示
	用回调函数通知用户，否则，表示用队列通知用户*/
	VOID (* pfReceiverNotifyFunction)(MBUF_S * pstMBuf, ULONG ulAttachMessage);
	/*0 或 1， 0 表示本项未使用，1 表示本项已使用*/
	ULONG ulInUse;
}MBUF_TR_RECEIVER_INFO_S;


typedef struct tagMBUF_TR_Info
{
	/*初始化时用VP_AllocMsg分配的内存，用来发送mbuf*/
	MBUF_TR_MESSAGE_S * pstMessageBuffer;
	/*pstMessageBuffer内存的长度*/
	ULONG ulMessageBufferLength;
	/*注册的各个接收者的信息*/
	MBUF_TR_RECEIVER_INFO_S stReceiverInfoA[MBUF_TR_MAX_RECEIVER_NUMBER];
}MBUF_TR_INFO_S;

/*private function*/
VOID MBUF_TR_Receive(ULONG ulReceiverChannelId, ULONG ulSourceBoardId, ULONG ulSourceVpChannelId,
					  VOID * pReceiveDataBuffer, ULONG ulReceiveDataLength);


/*********************************************************************************
                   
					 
					   public section
	这个部分是用户可用的部分

*********************************************************************************/

#define MBUF_TR_OK 0
#define MBUF_TR_ERROR_ALLOC_MEMORY 1
#define MBUF_TR_ERROR_VP_CREATE 2
#define MBUF_TR_ERROR_NULL_PIONTER 3
#define MBUF_TR_ERROR_DUP_QUEUE_NAME 4
#define MBUF_TR_ERROR_RECEIVER_FULL 5
#define MBUF_TR_ERROR_GET_QUEUE_ID 6
#define MBUF_TR_ERROR_NO_THIS_RECEIVER 7
#define MBUF_TR_ERROR_PARAMETER			8
#define MBUF_TR_DUP_REGISTER			9

#define CPCI_SEND_MTU              1700 /* bytes */
/**************************************************
     define a macro for debug and stat of mbuf_tr
     
**************************************************/
#define MBUF_TR_DBGANDSTAT           VRP_NO

ULONG MBUF_TR_Init();
VOID MBUF_TR_Exit();

ULONG MBUF_TR_RegisterReceiver(ULONG ulReceiverId, CHAR cReceiverQueueNameA[4], 
							   VOID (* pfReceiverNotifyFunction)(MBUF_S * pstMBuf, ULONG ulAttachMessage) );

VOID MBUF_TR_Send(MBUF_S * pstMBuf, ULONG ulReceiverBoardId, 
				  ULONG ulReceiverId, ULONG ulAttachMessage);
VOID MBUF_TR_NeatSend(MBUF_S * pstMBuf, ULONG ulReceiverBoardId, 
				  ULONG ulReceiverId, ULONG ulAttachMessage);

#if( VRP_OPTIM_VP == VRP_YES )
VOID IP_TR_Send( MBUF_S * pstMBuf, ULONG ulReceiverBoardId, ULONG ulReceiverId, ULONG ulPacketQueId );
#endif
#if(VRP_MODULE_IP_MPLS_SOFTFW == VRP_YES)
VOID MPLS_TR_Send( MBUF_S * pstMBuf,ULONG ulReceiverBoardId );
#endif



#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif /* end of _MBUF_TR_H_*/

