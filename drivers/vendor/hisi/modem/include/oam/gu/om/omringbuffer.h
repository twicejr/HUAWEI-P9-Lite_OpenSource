/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: OmRingBuffer.h                                                  */
/*                                                                           */
/* Author: Windriver                                                         */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-06                                                             */
/*                                                                           */
/* Description: implement ring buffer subroutine                             */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author: H59254                                                         */
/*    Modification: Adapt this file                                          */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#ifndef  _OM_RING_BUFFER_H
#define  _OM_RING_BUFFER_H

#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


typedef struct
{
    int  pToBuf;    /* offset from start of buffer where to write next */
    int  pFromBuf;  /* offset from start of buffer where to read next */
    int  bufSize;   /* size of ring in bytes */
    char acRsv[4];
    char *buf;      /* pointer to start of buffer */
} OM_RING;

typedef OM_RING * OM_RING_ID;

#if(FEATURE_ON == FEATURE_PTM)
OM_RING_ID OM_RingBufferCreateEx(char *pdata, int nbytes );
#endif

OM_RING_ID OM_RingBufferCreate( int nbytes );

void OM_RingBufferFlush( OM_RING_ID ringId );

int OM_RingBufferGet( OM_RING_ID rngId, char *buffer, int maxbytes );

int OM_RingBufferRemove( OM_RING_ID rngId, int maxbytes );

int OM_RingBufferGetReserve( OM_RING_ID rngId, char *buffer, int maxbytes );

int OM_RingBufferPut( OM_RING_ID rngId, char *buffer, int nbytes );

VOS_BOOL OM_RingBufferIsEmpty( OM_RING_ID ringId );

int OM_RingBufferFreeBytes( OM_RING_ID ringId);

int OM_RingBufferNBytes( OM_RING_ID ringId );


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _OM_RING_BUFFER_H */

