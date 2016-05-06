/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ppmng_forward.h
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
#ifndef _IP6_PPMNGFORWARD_H
#define _IP6_PPMNGFORWARD_H

#ifdef __cplusplus
extern "C"{
#endif


 /* Prototypes Of the Functions in Forward.c */
VOID IP6_PP_Forward(MBUF_S *pstMBuf,  UCHAR ucbSrcRt, ROUTE6_S *pstRoute6);
/* END: Prototypes Of the Functions in Forward.c */


#ifdef __cplusplus
}
#endif

#endif

