/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_QUE.H 
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/28
 *        Author: luohanjun
 *   Description: Ifnet消息队列头文件
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/28      luohanjun       Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/

#ifndef _TCPIP_IF_QUE_H_
#define _TCPIP_IF_QUE_H_

#ifdef  __cplusplus
extern "C"{
#endif

/************************************************************************
 * 请在这里填写该头文件的具体内容                                       *
 ************************************************************************/

typedef struct tagIFMsgQueue
{
    IFMSGHDR_S * pHead;              /* 头指针 */
    IFMSGHDR_S * pTail;              /* 尾指针 */
    ULONG           ulCurrentLength; /* 当前长度 */
    ULONG           ulMaxLength;     /* 队列最大长度 */
    IF_TIMER_S    stTimer;           /* 定时器字段 */

}IFMSG_QUEUE_S;

#define IFMSG_QUE_INIT(m_pQue, m_ulMaxLength)\
{\
    (m_pQue)->pHead = NULL;\
    (m_pQue)->pTail = NULL;\
    (m_pQue)->ulCurrentLength = 0;\
    (m_pQue)->ulMaxLength = (m_ulMaxLength);\
}

#define IFMSG_QUE_NOT_EMPTY(m_pQue) ( (m_pQue)->ulCurrentLength )
#define IFMSG_QUE_IS_FULL(m_pQue) ( (m_pQue)->ulCurrentLength >=  (m_pQue)->ulMaxLength )
#define IFMSG_QUE_ENQUEUE(m_pQue, m_pMsgHdr)\
{\
    (m_pMsgHdr)->pNext = NULL; \
    if( (m_pQue)->pTail != NULL)/*queue is NOT empty*/\
    {\
        m_pQue->pTail->pNext = (m_pMsgHdr); \
    }\
    else/*queue is empty*/\
    {\
        (m_pQue)->pHead = (m_pMsgHdr);\
    }\
    (m_pQue)->pTail = (m_pMsgHdr);\
    (m_pQue)->ulCurrentLength++;\
}

#define IFMSG_QUE_DEQUEUE(m_pQue, m_pMsgHdr)\
{\
    (m_pMsgHdr) = (m_pQue)->pHead;\
    if((m_pMsgHdr) != NULL)/*queue is NOT empty*/\
    {\
        (m_pQue)->pHead = (m_pMsgHdr)->pNext;\
        (m_pQue)->ulCurrentLength--;\
        if( (m_pQue)->pTail == (m_pMsgHdr) )/*this (m_pMsgHdr) is the last in the queue*/\
        {\
            (m_pQue)->pTail = NULL;\
        }\
    }\
}

#define IFMSG_QUE_PEEK(m_pQue) ((m_pQue)->pHead)

#define IFMSG_QUE_GET_CURRENT_LENGTH(m_pQue) ((m_pQue)->ulCurrentLength)

#define IFMSG_QUE_GET_MAX_LENGTH(m_pQue) ((m_pQue)->ulMaxLength)


#ifdef  __cplusplus
}
#endif

#endif

