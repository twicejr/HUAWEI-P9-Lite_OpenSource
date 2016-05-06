/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trrt_sh_info.h
*
*  Project Code: VISP1.5
*   Module Name: Traceroute Module 
*  Date Created: 2003-07-14
*        Author: Suraj( )
*   Description: TRRT模块枚举声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-07-14  Suraj( )         Creat the first version.
*
*******************************************************************************/

#ifndef _TRRT_INFO_H_
#define _TRRT_INFO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*输出信息索引*/
extern ULONG      g_ulTrrtExecInforIndex;    

/*------------------------------------------------------------------------*/
/* Index of Message                                                       */
/*------------------------------------------------------------------------*/
enum enumTracertInf
{ 
    Help_Trrt_Help = 0,
    Help_Trrt_Ipv6,
    Help_Trrt_FirstHLOpt,
    Help_Trrt_FirstHL,
    Help_Trrt_MaxHLOpt,
    Help_Trrt_MaxHL,
    Help_Trrt_UDPPortOpt,
    Help_Trrt_UDPPort,
    Help_Trrt_NumProbesOpt,
    Help_Trrt_NumProbes,
    Help_Trrt_TimeoutOpt,
    Help_Trrt_Timeout,
    Help_Trrt_HostName,
    Help_Trrt_SrcAddress,
    Help_Trrt_SrcSetAddress,
    Help_Trrt_Vpn,
    Help_Trrt_VpnName,

};


/* Trrt错误英文输出信息 */
extern CHAR * Inf_Tracert_En[];


#ifdef __cplusplus
}
#endif


#endif
