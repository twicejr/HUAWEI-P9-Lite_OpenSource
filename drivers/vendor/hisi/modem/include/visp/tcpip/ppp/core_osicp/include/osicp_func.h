/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              osicp_func.h
 *
 *  Project Code: VISPV1R6C03
 *   Module Name: osicp
 *  Date Created: 2007-07-11
 *        Author: Zhangchunyu
 *   Description: OSICPº¯ÊýÉùÃ÷
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      Zhangchunyu        Create
 *
 *************************************************************************/
#ifndef _OSICP_FUNC_H_
#define _OSICP_FUNC_H_

#ifdef  __cplusplus
extern "C"{
#endif
extern ULONG OSICP_Init_Com(const COM_ID_INFO_S *pstComInfo, ULONG ulComLen);
extern ULONG OSICP_Active_Com(VOID);
extern ULONG OSICP_SetModuleInfo(OSICP_MOD_INFO_S *pstMInfo);

#ifdef  __cplusplus
}
#endif

#endif
