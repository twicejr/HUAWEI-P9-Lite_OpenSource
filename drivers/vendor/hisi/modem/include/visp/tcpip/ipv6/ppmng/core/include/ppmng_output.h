/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ppmng_output.h
 *    Project Code:  VRP5.0
 *    Module Name:  IP6 PP
 *    Create Date:  2003/06/10
 *         Author:  Arun H S
 *     Description: Packet Output Module of PP
 *------------------------------------------------------------------------------
 *  Modification History                                                        
 *  DATE        NAME             DESCRIPTION                                    
 *  ----------------------------------------------------------------------------
 *  2003-06-10  Arun H S         Create
 ******************************************************************************/ 
#ifndef _IP6_PPMNGOUTPUT_H
#define _IP6_PPMNGOUTPUT_H

#ifdef __cplusplus
extern "C"{
#endif

#ifndef NO_USE       /* Added by Guru; 22-04-2004; to avoid redefinition warning */ 
#define     NO_USE(var)     (VOID)(var)
#endif

/* Prototypes Of the Functions in output.c */
/*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
ULONG IP6_PP_Output (MBUF_S *pstMBuf, IP6_PKTOPTS_S *pstOpt, ULONG ulZoneId, LONG lFlags, IP6_MOPTIONS_S *pstMo);
ULONG IP6_PP_IF_Output( MBUF_S *pstMBuf );
ULONG IP6_PP_Fragment_Output (MBUF_S **ppstMBuf, ULONG ulMTU);
/* END: Prototypes Of the Functions in output.c */
ULONG IP6_PP_FindNHAndOGIntf(MBUF_S* pstMBuf,ULONG ulZoneId, LONG lFlags);
extern ULONG Ip6_RandomId();

#ifdef __cplusplus
}
#endif

#endif
 
