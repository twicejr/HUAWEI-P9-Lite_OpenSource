/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                               mp_sh_disp.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2005-09-28
 *        Author: YaoChengLiang
 *   Description: Display MP Shell 部分的函数声明
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-28      YaoChengLiang   Create
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *
 *************************************************************************/

#ifndef _MP_SH_DISP_H_
#define _MP_SH_DISP_H_

#ifdef  __cplusplus
     extern  "C"{
#endif

VOID MP_PreArrayToStr(CHAR *pzBuf, MC_PREFIXE_S *pstPrefixE, ULONG ulBufLen);
VOID MP_ShowPrefixEInfo(ULONG ulIfIndex);
VOID MP_ShowMcConfig(ULONG ulIfIndex);
/* End of addition */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _MP_SH_DISP_H_ */
