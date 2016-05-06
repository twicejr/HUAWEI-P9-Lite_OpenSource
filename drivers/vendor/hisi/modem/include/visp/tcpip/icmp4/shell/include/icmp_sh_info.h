/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_sh_info.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: 声明shell中调试信息用的枚举值和字符串数组
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-24   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
 
#ifdef __cplusplus
extern "C" {
#endif


#ifndef _ICMP_SH_INFO_H_
#define _ICMP_SH_INFO_H_

extern CHAR * ErrInf_ICMP_En[];
extern CHAR * ErrInf_ICMP_Ch[];

extern UCHAR *ucIcmpDebug[];
extern UCHAR *ucIcmpDiscardInfo[];
extern UCHAR *ucIcmpInfo[];
extern UCHAR  szMap[19][16];


#endif  /* end of _ICMP_SH_INFO_H_ */ 


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

