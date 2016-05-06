/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4r_var.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R  
*  Date Created: 2007-7-10
*        Author: LY(57500)
*   Description: 变量声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-7-10  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _DHCP4R_VAR_H_
#define _DHCP4R_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

extern ULONG g_ulDHCP4RSocketQId;  /* Relay异步socket消息ID    */
extern ULONG g_ulDHCP4RCntrlQId;   /* Relay其他模块通知消息ID  */
extern ULONG g_ulDHCP4RSm;         /* Relay模块共享数据互斥信号量 */

/* RELAY用于保存接收的DHCP报文的缓冲区    */
extern UCHAR g_aucDHCP4RUdpBuf[DHCP4R_UDPBUF_MAXLEN]; 

/* (UDP 67)用于DHCP Relay从Client接收或者向Client发送DHCP报文  */
extern LONG  g_lDHCP4RSocket; 

/* 中继方式     */
extern ULONG g_ulDHCP4RFwdMode;     

/* 最大RELAY跳数    */
extern ULONG g_ulDHCP4RMaxHops;     

/* 要设置的TOS      */
extern UCHAR g_ucDHCP4RTos;    

/* DHCP4R模块信息 */
extern DHCP4R_MOD_INFO_S g_stDHCP4RModInfo;

/* Core中使用的回调函数集 */
extern DHCP4R_SHELL_CALLBACK_SET_S g_stDHCP4RShellApi;

/* DHCP4R模块统计信息 */
extern DHCP4R_STATINFO_S g_stDhcp4rStat;
    
/* DHCP4R模块的IFNET组件功能虚表指针 */
extern struct IIF_IFNET_ComIntFUNVtbl    *g_pstDHCP4RIfnetFunTable;

/* DHCP4R模块的AM4组件功能虚表指针 */
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl *g_pstDHCP4RAm4FunTable;

/* DHCP4R模块的UDP4组件配置虚表指针 */
extern struct IIF_IP4_UDP4_ComIntCfgVtbl *g_pstDHCP4RUdp4FunTable;

/* dhcp4r组件配置虚表 */
extern struct IIF_COMP_DHCP4R_ComIntCFGVtbl *g_pstDHCP4RCfgTable;

/* dhcp4r模块的Sfib组件功能虚表 */
extern struct IIF_COMP_FIBAGENT_ComIntFUNVtbl *g_pstDHCP4RSfibAComFUNTable;


/* dhcp4r ha */
extern ULONG g_ulDHCP4RHaDbg;           /* DHCP4R ha调试开关状态, 0-关闭, 1-打开       */
extern ULONG g_ulDHCP4RHaVerboseDbg;    /* DHCP4R ha详细调试开关状态, 0-关闭, 1-打开   */

/* 外部模块定义变量 */
/* VISP紧密模块全局互斥信号量 */
extern ULONG g_ulSemForTightMods;

/* dhcp4r debug status */
extern CHAR *g_aszDhcp4rDbgStatus[];

/* dhcp报文消息类型字符串 */
extern CHAR *g_aszDhcp4rPkt[]; 

/* 用户错误码对应的描述字符串 */
extern CHAR *g_aszDhcp4rErrInfo[];

/* 获取DHCP Relay请求报文的源地址回调函数指针 */
extern DHCP4R_GET_SRCADDR_HOOK g_pfDhcp4rGetSrcAddrHook;

extern ULONG g_ulDhcp4rMaxVrfIndex;

extern DHCP4R_CFG_VRF_S **g_ppstDhcp4rCfgVrf;

extern DHCP4R_DBG_VRF_S **g_ppstDhcp4rDbgVrf;

extern DHCP4R_PROC_REQUEST_HOOK g_pfDhcp4rProcRequestHook;

extern DHCP4R_GET_GIADDR_HOOK g_pfDhcp4rGetGiaddrHook;

/* 注册DHCP Relay模块报文预处理钩子，由产品完成所收到的DHCP Reply报文的预处理过程。
   (根据XID，修改Giaddr字段) */
extern DHCP4R_PROC_REPLY_HOOK  g_pfDhcp4rProcReplyHook;

/* 根据收到的Server报文的Giaddr获取转发的广播接口索引以及源地址 */
extern DHCP4R_GET_CLIENTIF_HOOK g_pfDhcp4rProcGetClientIfHook;

/* 根据收到的Server报文获取转发的广播接口索引以及源地址 ，针对Giaddr已经是VRRP IP(非接口IP)的场景*/
extern DHCP4R_GET_CLIENTIF_BYVRF_HOOK g_pfDhcp4rProcGetClientIfByVrfHook;

extern DHCP4R_OPTION82_HOOK g_pfDhcp4rOption82Hook;

/* 通过Server IP获取DHCP Relay请求报文的源地址回调函数指针 */
extern DHCP4R_GET_SRCADDR_BY_SVRIP_HOOK g_pfDhcp4rGetSrcAddrBySvrIpHook;

extern ULONG g_ulDR4TaskScheduleSwitch;
extern ULONG g_ulDR4PacketProCount;
extern ULONG g_ulDR4TaskDelayTime;

/* Added by likaikun00213099 at 20140806 for dhcp4r port security,dhcp4r使能计数 */
extern ULONG g_ulDhcp4rEnableCount;

#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _DHCP4R_VAR_H_    */

