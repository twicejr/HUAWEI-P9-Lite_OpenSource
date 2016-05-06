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

#ifndef __CKSUM_H__
#define __CKSUM_H__

#ifdef  __cplusplus
extern "C" {
#endif

#define MD5_CHECKSUM        1
#define FLETCHER_CHECKSUM   1

USHORT	INET_Cksum (void * cp, ULONG length);
ULONG	ISO_Cksum (void * pkt, ULONG len, UCHAR * cksum);
void	MD5_Cksum (void * data ,
		ULONG datalen ,
		ULONG totallen ,
		void * digest ,
		ULONG * init);

#ifdef  __cplusplus
}
#endif

#endif

