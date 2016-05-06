/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              md5.h
*
*  Project Code: VISPV100R005
*   Module Name: MD5  
*  Date Created: 2000-3-25
*        Author: x36317
*   Description: md5的头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000-3-25   x36317           Creat the first version.
*  2006-4-27   wang xin(03278)   根据编程规范，对文件进行规范化整理
*  2007-07-30  mafeng 59090      CBB
*******************************************************************************/

#ifndef _MD5_H_
#define _MD5_H_

#ifdef  __cplusplus
extern "C" {
#endif


/* MD5.H - header file for MD5C.C
 */

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
 */

/* MD5 context. */
typedef struct 
{
    ULONG state[4];        /* state (ABCD) */
    ULONG count[2];        /* number of bits, modulo 2^64 (lsb first) */
    UCHAR buffer[64];      /* input buffer */
}MD5_CTX;

void MD5Init(MD5_CTX *);
void MD5Update(MD5_CTX *, UCHAR *, ULONG);
void MD5Final(UCHAR [16], MD5_CTX *);
void MD5Calc(UCHAR *output, UCHAR *input, ULONG inlen);

#ifdef  __cplusplus
}
#endif

#endif /* _MD5_H_ */

