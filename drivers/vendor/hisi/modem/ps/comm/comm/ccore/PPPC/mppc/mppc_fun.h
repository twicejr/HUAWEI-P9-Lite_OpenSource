/************************************************************************
 *                                                                      *
 *                             mppc_fun.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/06/20                                      *
 *  Author:             Shi  Yong                                       *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           MPPC部分与外界调用的接口	                    *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *												                        *
 *                                                                      *
 ************************************************************************/

/*#if( VRP_MODULE_MPPC == VRP_YES )*/

#ifndef		_MPPC_FUN_H_
#define		_MPPC_FUN_H_

#ifdef	__cplusplus
extern "C"{
#endif

/*mahui porting for BYHD02280*/

int
CMP_MppeCompress(void *arg, unsigned char *ibuf, unsigned char *obuf, int isize);

int mppe_init(void **arg,int comp);
void mppe_comp_free(void **arg);
/*mahui porting for BYHD02280 end*/

#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif

/*#endif*/	/*end of the *.h file*/
