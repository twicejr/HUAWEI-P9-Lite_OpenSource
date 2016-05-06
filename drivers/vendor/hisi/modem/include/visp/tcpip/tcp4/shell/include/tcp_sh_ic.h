/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_sh_ic.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4  
*  Date Created: 2002-7-20
*        Author: zhangfeng
*   Description: TCP MD5相关的宏定义和IC相关的函数申明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-7-20   zhangfeng        Create the first version.
*
*******************************************************************************/
#ifndef _TCP_SH_IC_H
#define _TCP_SH_IC_H
 
#ifdef  __cplusplus
extern "C"{
#endif


/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */
#define TCP_MD5_SYS_LOG             IC_INFOID_DEF(MID_COMP_TCP4, IC_INFO_LOG | IC_INFO_HIDE, 0)
/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */

#define TCP_DBGID_GENERAL           IC_INFOID_DEF(MID_COMP_TCP4,IC_INFO_DEBUG,0)
#define TCP_DBGID_PACKET            IC_INFOID_DEF(MID_COMP_TCP4,IC_INFO_DEBUG,1)
#define TCP_DBGID_TRANSA            IC_INFOID_DEF(MID_COMP_TCP4,IC_INFO_DEBUG,2)

/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */
#define TCP_MD5_FAIL                IC_INFOID_DEF(MID_COMP_TCP4,IC_INFO_DEBUG,3)
#define TCP_MD5_SUCCESS             IC_INFOID_DEF(MID_COMP_TCP4,IC_INFO_DEBUG,4)
#define TCP_MD5_OUTPUT              IC_INFOID_DEF(MID_COMP_TCP4,IC_INFO_DEBUG,5)
#define TCP_MD5_DETAIL              IC_INFOID_DEF(MID_COMP_TCP4,IC_INFO_DEBUG,6)
/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */

/*added by xujin for md5 trap*/
#define TCP_MD5_FAIL_TRAP              IC_INFOID_DEF(MID_COMP_TCP4,IC_INFO_TRAP,0)

ULONG IP4_TCP4_SH_Reg2IC();

#ifdef  __cplusplus
}
#endif
 
#endif  /* #ifndef _TCP_SH_IC_H */



