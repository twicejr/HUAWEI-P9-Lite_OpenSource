/*
 *        Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1993, Internet Initiative Japan, Inc. All rights reserverd.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Internet Initiative Japan.  The name of the
 * IIJ may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $FreeBSD: src/usr.sbin/ppp/chap.h,v 1.18 2000/03/14 01:46:04 brian Exp $
 *
 * TODO:
 */

#ifndef __PPP_CHAP_H__
#define __PPP_CHAP_H__

#include "PPP/Inc/auth.h"

#pragma pack(4)

#define    CHAP_CHALLENGE    (1)
#define    CHAP_RESPONSE     (2)
#define    CHAP_SUCCESS      (3)
#define    CHAP_FAILURE      (4)

struct chap {
  struct authinfo auth;    /* common structure of authentication */
  struct {
    /*
     * format of local:
     *  --------------------------------- ------------------- --------
     * |  length of local challenge(1B)  |  local challenge  |  name  |
     *  --------------------------------- ------------------- --------
     */
    VOS_UINT8 local[1+CHAPCHALLENGELEN + AUTHLEN];    /* I invented this one */
    /*
     * format of peer:
     *  -------------------------------- ------------------
     * |  length of peer challenge(1B)  |  peer challenge  |
     *  -------------------------------- ------------------
     in fact, peer just need (1+CHAPCHALLENGELEN) bytes,
     but in BSD, peer is (CHAPCHALLENGELEN + AUTHLEN) bytes
     right now, we assume peer need (1+CHAPCHALLENGELEN + AUTHLEN) bytes
     */
    VOS_UINT8 peer[1+CHAPCHALLENGELEN + AUTHLEN];    /* Peer gave us this one */
  } challenge;    /* used in Authentication phase follow CHAP, RFC1994 */
  struct
  {
    /*
        这个结构是为了保留发送到GGSN完整的config req报文而设的,
        把发送的challenge报文和接收到的response报文发给AT,
        需要注意这部分内容需要提交给TAF使用, 根据PPP与TAF的接口设计,
        BufChallenge和BufResponse的长度都不能超过253Bytes
    */
    VOS_UINT16 LenOfChallenge;
    VOS_UINT16 LenOfResponse;
    VOS_UINT8  BufChallenge[1+1+2+1+CHAPCHALLENGELEN + AUTHLEN];    /* code(1B)+id(1B)+length(2B)+challenge_size(1B)+challenge+name */
    VOS_UINT8  BufResponse[1+1+2+1+PASSWORDLEN + AUTHLEN];    /* code(1B)+id(1B)+length(2B)+response_size(1B)+response+name */
  } RecordData;
};


void chap_Init(struct chap *);
void chap_ReInit(struct chap *);
PPP_ZC_STRU *chap_Input(struct link *, PPP_ZC_STRU *);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#endif    /* end of chap.h */


