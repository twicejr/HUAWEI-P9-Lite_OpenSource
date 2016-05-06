/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ppmng_hdr_util.h
 *    Project Code:  VRP5.0
 *    Module Name:  IP6 PP
 *    Create Date:  2003/06/10
 *         Author:  Arun H S
 *     Description: 
 *------------------------------------------------------------------------------
 *  Modification History                                                        
 *  DATE        NAME             DESCRIPTION                                    
 * -----------------------------------------------------------------------------
 *  2003-06-10  Arun H S         Create
 ******************************************************************************/ 
#ifndef _IP6_PPMNGHDRUTIL_H
#define _IP6_PPMNGHDRUTIL_H

#ifdef __cplusplus
extern "C"{
#endif


#define PP_NO_BUF               -1
#define PP_ERROR_PROTOCOL       -1

ULONG IP6_PP_NoHdr_Input (MBUF_S **ppstMBuf, ULONG *pulOff, ULONG ulProto);
LONG IP6_PP_GetNextHdr (MBUF_S *pstMBuf, ULONG ulOff, ULONG ulProto, ULONG *pulNxtProto);
LONG IP6_PP_GetLastHdr (MBUF_S *pstMBuf, ULONG ulOff, ULONG ulProto, ULONG *pulNxtProto);
UCHAR *IP6_PP_GetPrevHdr (MBUF_S *pstMBuf, ULONG *pulOff, ULONG *pulProto);


#ifdef __cplusplus
}
#endif

#endif

