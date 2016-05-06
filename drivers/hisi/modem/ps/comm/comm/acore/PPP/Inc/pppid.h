/*
 * 
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
#ifndef __PPPID_H__
#define __PPPID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "PppInterface.h"
#include "vos.h"


#pragma pack(4)
#if 0
typedef VOS_UINT16 PPP_ID;
#endif

/*某PPP ID被分配出去的标志*/
#define PPP_ID_ALLO_fLAG 0xffff

/*最后一个空闲PPP ID的标志*/
#define PPP_ID_TAIL_FLAG 0

extern PPP_ID*    pgPppId;

#define PPP_ID_ALLOCED(i) (pgPppId[i] == PPP_ID_ALLO_fLAG)


extern VOS_VOID   PppIdInit(VOS_VOID);
extern PPP_ID     PppGetId(VOS_VOID);
extern VOS_VOID   PppFreeId(PPP_ID id_be_free);

extern PPP_ID     PppGetAllocedId(VOS_VOID);
extern VOS_UINT32 PppIsIdValid ( PPP_ID usPppId);
#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
