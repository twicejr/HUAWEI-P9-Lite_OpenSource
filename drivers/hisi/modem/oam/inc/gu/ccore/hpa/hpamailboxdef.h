/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: HPAMailBoxDef.h                                                 */
/*                                                                           */
/* Author: Xu cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-02                                                             */
/*                                                                           */
/* Description: Definition of HPA mailbox                                    */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2008-02                                                          */
/*    Author: Xu cheng                                                       */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef  _HPA_MAIL_BOX_DEF_H
#define  _HPA_MAIL_BOX_DEF_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "vos.h"
#include "hpaoperatertt.h"

/* Definition of mailbox protectword */
#define MAIL_BOX_WRITEABLE     0x55AA /* can write */
#define MAIL_BOX_READABLE      0x5A5A /* can read */

#define MAIL_BOX_PROTECTWORD_FST 0x55AA55AA
#define MAIL_BOX_PROTECTWORD_SND 0x5A5A5A5A

#define MAIL_BOX_PARTITION_FLAG  0xA5A5A5A5

/*增加AHB邮箱交互定位信息使用*/
#define AHB_TRACE

#define HPA_WRITE_AHB_INT       MAIL_BOX_PROTECTWORD_FST
#define HPA_WRITE_AHB_MSG       MAIL_BOX_PROTECTWORD_SND

#define HPA_TRACE_MASK_NUM      16
#define HPA_TRACE_WRITEABLE     MAIL_BOX_WRITEABLE

#define OM_MAIL_BOX_EMPTY       (0xAA55AA55)
#define OM_MAIL_BOX_EXIST       (0x55AA55AA)

typedef struct
{
    VOS_UINT32 ulPriority;      /* 消息优先级，参见：MSG_PRIORITY */
    VOS_UINT32 ulMsgLength;     /* 消息总长度 */
}HPA_RINGBUFFER_HEADER_STRU;

/******************************************************************************/
/* PP mailbox */
/******************************************************************************/
typedef struct
{
    VOS_UINT16 usMUTEX;
    VOS_UINT16 usRsv;
    VOS_UINT16 usCheck;
    VOS_UINT16 usMsgsLen;
    VOS_UINT32 ulARMSlice;   /* time when ARM writes ProtectWord */
    VOS_UINT32 ulDSPSlice;   /* time when DSP writes ProtectWord */
}PP_MAILBOX_HEADER_STRU;

/* Definition of PP mailbox primite header*/
typedef struct
{
    VOS_UINT16 MID;
    VOS_UINT16 SerialNo;
    VOS_UINT16 Rsv;
    VOS_UINT16 MsgLen;
}PP_MSG_HEADER_STRU;

#define PP_MAILBOX_MSGLENTH_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((PP_MAILBOX_HEADER_STRU *)(MbStartAddr))->usMsgsLen))

#define PP_MAILBOX_MUTEX_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((PP_MAILBOX_HEADER_STRU *)(MbStartAddr))->usMUTEX))

#define PP_MAILBOX_ARMSLICE_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((PP_MAILBOX_HEADER_STRU *)(MbStartAddr))->ulARMSlice))

/*PP mailbox header Length*/
#define PP_MAILBOX_HEADER_LEN      (sizeof(PP_MAILBOX_HEADER_STRU))

/*PP mailbox primite header Length*/
#define PP_MSG_HEADER_LEN          (sizeof(PP_MSG_HEADER_STRU))

/*PP mailbox max Msg size*/
#define PP_MAX_MSG_LEN             (PP_MAILBOX_REAL_SIZE - PP_MAILBOX_HEADER_LEN)

/******************************************************************************/
/* NPP mailbox */
/******************************************************************************/
typedef struct
{
    VOS_UINT16 usMutex;
    VOS_UINT16 usRsv1;
    VOS_UINT16 usMsgCnt;
    VOS_UINT16 usTotalMsgsLen;
    VOS_UINT16 usRsv2;
    VOS_UINT16 usCheck;
    VOS_UINT32 ulARMSlice;   /* time when ARM writes ProtectWord */
    VOS_UINT32 ulDSPSlice;   /* time when DSP writes ProtectWord */
}NPP_MAILBOX_HEADER_STRU;

/* Definition of NPP mailbox primite header*/
typedef struct
{
    VOS_UINT16 usSerialNo;
    VOS_UINT16 usMsgLen;
}NPP_MSG_HEADER_STRU;

#define NPP_MAILBOX_MUTEX_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((NPP_MAILBOX_HEADER_STRU *)(MbStartAddr))->usMutex))

#define NPP_MAILBOX_MSGCOUNT_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((NPP_MAILBOX_HEADER_STRU *)(MbStartAddr))->usMsgCnt))

#define NPP_MAILBOX_TOTALMSGLENTH_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((NPP_MAILBOX_HEADER_STRU *)(MbStartAddr))->usTotalMsgsLen))

#define NPP_MAILBOX_ARMSLICE_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((NPP_MAILBOX_HEADER_STRU *)(MbStartAddr))->ulARMSlice))

/*NPP mailbox header Length*/
#define NPP_MAILBOX_HEADER_LEN     (sizeof(NPP_MAILBOX_HEADER_STRU))

/*NPP mailbox primite header Length*/
#define NPP_MSG_HEADER_LENGTH      (sizeof(NPP_MSG_HEADER_STRU))

/* NPP mailbox max Msg size*/
#define NPP_MAX_MSG_LEN \
    (NPP_MAILBOX_REAL_SIZE - NPP_MAILBOX_HEADER_LEN)

/******************************************************************************/
/* LOCK and UnLock Mail Box, and Wake up Type*/
/******************************************************************************/
#define GHPA_LOCK_MAIL_REG_VALUE          0x5555
#define GHPA_CLS_LOCK_MAIL_REG_VALUE      0x0

#define GHPA_WAIT_DSP_UNLOCK_DELAY        10000
#define GHPA_WAIT_DSP_UNLOCK_CYCLE        10

/******************************************************************************/
/* AHB mailbox */
/******************************************************************************/
#define AHB_MAILBOX_PROTECTWORD1_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((IPC_MAILBOX_HEAD_STRU *)(MbStartAddr))->ulProtectWord1))

#define AHB_MAILBOX_PROTECTWORD2_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((IPC_MAILBOX_HEAD_STRU *)(MbStartAddr))->ulProtectWord2))

#define AHB_MAILBOX_PROTECTWORD3_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((IPC_MAILBOX_HEAD_STRU *)(MbStartAddr))->ulProtectWord3))

#define AHB_MAILBOX_PROTECTWORD4_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((IPC_MAILBOX_HEAD_STRU *)(MbStartAddr))->ulProtectWord4))

#define AHB_MAILBOX_FRONT_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((IPC_MAILBOX_HEAD_STRU *)(MbStartAddr))->ulFront))

#define AHB_MAILBOX_REAR_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((IPC_MAILBOX_HEAD_STRU *)(MbStartAddr))->ulRear))

#define AHB_MAILBOX_FRONTSLICE_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((IPC_MAILBOX_HEAD_STRU *)(MbStartAddr))->ulFrontslice))

#define AHB_MAILBOX_REARSLICE_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((IPC_MAILBOX_HEAD_STRU *)(MbStartAddr))->ulRearslice))

#ifdef AHB_TRACE
#define AHB_MAILBOX_COPY_ADDR(MbStartAddr) \
    ((VOS_UINT32)&(((IPC_MAILBOX_HEAD_STRU *)(MbStartAddr))->ausReserve[0]))
#endif

/* AHB mailbox header Length*/
#define AHB_MAILBOX_HEADER_LEN     (sizeof(IPC_MAILBOX_HEAD_STRU))

/*AHB mailbox primite header Length*/
#define AHB_MSG_HEADER_LEN         (sizeof(IPC_MSG_HEADER_STRU))

/* AHB mailbox Protect Word Length*/
#define AHB_MAILBOX_PROTECTWORD_LEN     (2*sizeof(VOS_UINT32))

/* AHB mailbox max Msg size ARM->DSP */
#define AHB_DL_MAX_MSG_LEN(max_real_size) \
    (((max_real_size-AHB_MAILBOX_HEADER_LEN)-AHB_MAILBOX_PROTECTWORD_LEN)-sizeof(VOS_UINT32))

/* AHB mailbox max Msg size DSP->ARM */
#define AHB_UL_MAX_MSG_LEN(max_real_size) \
    (((max_real_size-AHB_MAILBOX_HEADER_LEN)-AHB_MAILBOX_PROTECTWORD_LEN)-sizeof(VOS_UINT32))

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _HPA_RING_BUFFER_H */

