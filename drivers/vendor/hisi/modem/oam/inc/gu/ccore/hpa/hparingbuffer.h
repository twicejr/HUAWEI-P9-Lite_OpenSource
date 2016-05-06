/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: HPARingBuffer.h                                                 */
/*                                                                           */
/* Author: Windriver                                                         */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement ring buffer subroutine                             */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author: x51137                                                         */
/*    Modification: Adapt this file                                          */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#ifndef  _HPA_RING_BUFFER_H
#define  _HPA_RING_BUFFER_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "vos.h"
#include "hpaoperatertt.h"
#include "DspInterface.h"

#define HPA_ARM_ALIGNMENT         0x03
#define HPA_EVEN_NUBER            0x01

#define HPA_MIN(x, y)             (((x) < (y)) ? (x) : (y))

#define HPA_MAX_RING_BUFFER_NUM   16

/* the actual size of ringbuffer = user size + one byte.
    see HPA_RingBufferCreate functiong.
    ARM is 32bit CPU, three bytes reserved for 4 byte aligned */
#define HPA_RING_BUFFER_RESERVRD_BYTE 3

/* the length of HPA's ringbuffer. size = 1.5*real size + reserved byte */
#define HPA_RING_BUFFER_SIZE(RealSize) \
    (HPA_RING_BUFFER_RESERVRD_BYTE + RealSize + (RealSize >> 1))

/* the size of HPA's buffer.40 is reserved for 4byte aligned */
#define HPA_RING_BUF_SIZE (((HPA_RING_BUFFER_SIZE(R99_DL_MAILBOX_REAL_SIZE))\
    + (HPA_RING_BUFFER_SIZE(R99_UL_MAILBOX_REAL_SIZE))\
    + (HPA_RING_BUFFER_SIZE(PP_DL_MAILBOX_REAL_SIZE))\
    + (HPA_RING_BUFFER_SIZE(PP_UL_MAILBOX_REAL_SIZE))\
    + (HPA_RING_BUFFER_SIZE(NPP_UL_MAILBOX_REAL_SIZE))\
    + (HPA_RING_BUFFER_SIZE(ZSP_UP_MAILBOX_MAX_SIZE))+40)\
    & (~VOS_ARM_ALIGNMENT))

typedef struct
{
    int  pToBuf;    /* offset from start of buffer where to write next */
    int  pFromBuf;  /* offset from start of buffer where to read next */
    int  bufSize;   /* size of ring in bytes */
    char *buf;      /* pointer to start of buffer */
} HPA_RING;

typedef HPA_RING * HPA_RING_ID;

HPA_RING_ID HPA_RingBufferCreateNoMem( char* buffer, int nbytes );

HPA_RING_ID HPA_RingBufferCreate( int nbytes );

void HPA_RingBufferFlush( HPA_RING_ID ringId );

int HPA_RingBufferGet( HPA_RING_ID rngId, char *buffer, int maxbytes );

int HPA_RingBufferRemove( HPA_RING_ID rngId, int maxbytes );

int HPA_RingBufferGetReserve( HPA_RING_ID rngId, char *buffer, int maxbytes );

int HPA_DspRingBufferGetReserve( HPA_RING_ID rngId, char *buffer, int maxbytes );

int HPA_RingBufferPut( HPA_RING_ID rngId, char *buffer, int nbytes );

VOS_BOOL HPA_RingBufferIsEmpty( HPA_RING_ID ringId );

VOS_BOOL HPA_RingBufferIsFull( HPA_RING_ID ringId );

int HPA_RingBufferFreeBytes( HPA_RING_ID ringId);

int HPA_RingBufferNBytes( HPA_RING_ID ringId );

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _HPA_RING_BUFFER_H */

