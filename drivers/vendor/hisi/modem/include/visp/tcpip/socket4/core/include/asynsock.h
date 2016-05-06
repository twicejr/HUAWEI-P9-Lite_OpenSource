/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              asynsock.h
*
*  Project Code: VISP1.5
*   Module Name: socket4
*  Date Created: 2006-4-28
*        Author: l(48769)
*   Description: 异步socket相关的结构定义和函数声明 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef     _ASYNSOCK_H
#define     _ASYNSOCK_H

#ifdef  __cplusplus
extern "C" {
#endif

/*define asynchonmous message identifier */
#define   ASYN_MESSAGE   0X12345678

#define   SE_QUEUEERR    0x0080 

#define         EQUEEMPTY    -1
#define         ENOTASYN     -2
#define         ENOTIME      -3
#define         ENORECORD    -4
#define         ENOASYNSOCK  -5
#define         EUDPNODATA   -6
#define         EMBUFEMPTY   -7
#define         EQUEUEERROR  -8
#define         EQUEUEFULL   -9
#define         EISASYNC     -10    
#define         EISBACKCALL  -11
#define         ETIMEWAIT    -15
#define         ENOFIOMAXMBUF    -16
#define         ENOFIOTCPDROPALL -17
#define         ENOFIOSENDONLY   -18
#define         ESENDDATAIF      -19
#define         ENORTENTRY       -20

#define         sid_SKT_ASYN    0X003F

/*消息结构定义*/
typedef struct tagASYNSOCKETMSG
{
    ULONG    ulMsgType;    /*表明此消息是异步SOCKET发送的消息,数值为ASYN_MESSAGE*/
    ULONG    ulPointer;    /*原先是src分配的buffer, 现表明是src指定的pointer */
                           /*绑定于异步SOCKET的一个数值*/
    LONG     iError;

#define SUCCEEDED       0
#define FAILED          1

    /* Modefied by fengjing209023 ASYNMSG_S.FD.type.defect 将FD由16位改为24位,涉及接口变更，需知会产品 */
    /* 注意: VOS_Que_Write函数写的消息最大长度为16字节(32bit环境)，故该结构体定义不能超过16字节*/
    unsigned usFd:24;
    unsigned usEventType:8;
    /* Modefied end */    

#define ASYN_READ       1
#define ASYN_WRITE      2
#define ASYN_CONNECT    3
#define ASYN_CLOSE      4
#define ASYN_ACCEPT     5
#define ASYN_PEERCLOSE  6
#define ASYN_KEEPALIVEDOWN  7

}ASYNMSG_S;

#define L_ASYNMSG_S  sizeof(ASYNMSG_S)

extern LONG    AsynWakeUp(SOCKET_S *, LONG, LONG);
extern ULONG   AsynReCall( SOCKET_S *, MBUF_S *, IP_S *, USHORT );

extern LONG IsAsynSocket(LONG iFd);

#ifdef  __cplusplus
}
#endif

#endif

