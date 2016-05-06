/************************************************************************
 *                                                                      *
 *                             ROOT.H                                   *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/01/25                                      *
 *  Author:             Hu Bo                                           *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  这是VRP的启动模块的头文件。                                         *
 *  在这个头文件中定义了以下东西（以下的“所有”不包括VOS）：           *
 *                                                                      *
 *    VRP中所有任务的名字、ID、入口函数、优先级、模式、栈长、入口参数； *
 *    VRP中所有队列的名字、长度、模式、ID；                             *
 *    VRP中所有事件的值；                                               *
 *    VRP的SockRun任务中所有子任务的标志位。                            *
 *                                                                      *
 *  这个头文件至少被root.c包含；如果某个C文件用到了上述变量或宏，则这个 *
 *  C文件也需要包含root.h。                                             *
 *                                                                      *
 *  具体描述VRP启动流程的文档是《VRP编程手册--VRP启动流程说明书》。     *
 *                                                                      *
 ************************************************************************/

 
#ifndef	_ROOT_H_
#define	_ROOT_H_

#ifdef	__cplusplus
extern "C"{
#endif


/************************************************************************
 * VRP的任务ID的参数(不包括FTPServer和EXEC用户管理任务):                *
 ************************************************************************/
 /* 初始化任务 */
#define	VRP_TASK_VRPI_NAME			"VRPI"
extern	ULONG						ulVRPTID_VRPI;
#define	VRP_TASK_VRPI_ENTRY			VRP_InitializeTask
#define	VRP_TASK_VRPI_PRIO			VOS_T_PRIORITY_ABOVE_NORMAL /* priority ??? */
#define	VRP_TASK_VRPI_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_VRPI_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_VRPI_ARG			0	/* means no argument */
 
#if( VRP_MODULE_CFG_IC_BASE == VRP_YES )
/* 信息处理中心任务 */
#define	VRP_TASK_INFO_NAME			"INFO"
extern	ULONG						ulVRPTID_INFO;
#define	VRP_TASK_INFO_ENTRY			IC_TaskEntry
#define	VRP_TASK_INFO_PRIO			VOS_T_PRIORITY_NORMAL /* priority ??? */
#define	VRP_TASK_INFO_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_INFO_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_INFO_ARG			0	/* means no argument */
#endif

#if( VRP_MODULE_VPN_L2VPN == VRP_YES )
/* MPLS L2VPN 任务 */
#define	VRP_TASK_L2V_NAME			"L2V"
extern	ULONG						ulVRPTID_L2V;
#define	VRP_TASK_L2V_ENTRY			L2VPN_TaskEntry
#define	VRP_TASK_L2V_PRIO			VOS_T_PRIORITY_NORMAL	/* priority ??? */
#define	VRP_TASK_L2V_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_L2V_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_L2V_ARG			0	/* means no argument */
#endif

#if(VRP_MODULE_CFA == VRP_YES)
extern	ULONG						ulVRPTID_CFAT;    /* 通信代理任务ID */
extern  VOID CFA_Agent_task( VOID );                /* 通信代理任务函数 */
#define	VRP_TASK_CFA_NAME			"CFA"           /* 通信代理任务名称 */
#define	VRP_TASK_CFA_ENTRY			CFA_Agent_task  /* 通信代理任务函数 */
#define	VRP_TASK_CFA_PRIO			VOS_T_PRIORITY_NORMAL /* priority */
#define	VRP_TASK_CFA_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_CFA_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_CFA_ARG			0	/* means no argument */
#endif

 /* 报文转发任务 */
#define	VRP_TASK_SOCK_NAME			"SOCK"
extern	ULONG						ulVRPTID_SOCK;
#define	VRP_TASK_SOCK_ENTRY			VRP_SockRun
#define	VRP_TASK_SOCK_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_SOCK_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_SOCK_ARG			0	/* means no argument */
extern	ULONG						ulSchedSockFlag;

 /* VTY任务 */
#define	VRP_TASK_VTYD_NAME			"VTYD"
extern	ULONG						ulVRPTID_VTYD;
#define	VRP_TASK_VTYD_ENTRY			VTY_TelnetServer
#define	VRP_TASK_VTYD_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_VTYD_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_VTYD_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_VTYD_ARG			0	/* means no argument */
 
#if( VRP_MODULE_IFNET == VRP_YES )
/* ifnet Task: */
#define	VRP_TASK_IFNT_NAME			"IFNT"
extern	ULONG						ulVRPTID_IFNT;
#define	VRP_TASK_IFNT_ENTRY			VRP_IfTask
#define	VRP_TASK_IFNT_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_IFNT_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_IFNT_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_IFNT_ARG			0	/* means no argument */

#if ((VRP_CENTERALIZATION == VRP_YES) && (IF_HOT_CTL == VRP_YES))
/*增加集中式热插拔   pengjimei for DEV_HOTCTL 2002/12/10*/
/* ifnetdev Task: */
#define	VRP_TASK_IFNTDEV_NAME			"IDEV"
extern	ULONG						ulVRPTID_IFNTDEV;
#define	VRP_TASK_IFNTDEV_ENTRY			VRP_IfDevTask
#define	VRP_TASK_IFNTDEV_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_IFNTDEV_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_IFNTDEV_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_IFNTDEV_ARG			0	/* means no argument */
#endif /*#if ((VRP_CENTERALIZATION == VRP_YES) && (IF_HOT_CTL == VRP_YES))*/
#endif /*#if( VRP_MODULE_IFNET == VRP_YES )*/

#if( VRP_MODULE_IP_BASE == VRP_YES )
/* FIB表维护任务 */
#define	VRP_TASK_FIB_NAME			"FIB"
extern	ULONG						ulVRPTID_FIB;
#define	VRP_TASK_FIB_ENTRY			FIBTASK_Main
#define	VRP_TASK_FIB_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_FIB_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_FIB_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_FIB_ARG			0	/* means no argument */
#endif

#if( VRP_MODULE_IPTN_BASE == VRP_YES )
/* IPTN维护任务 */
#define	VRP_TASK_IPTN_NAME			"IPTN"
extern	ULONG						ulVRPTID_IPTN;
#define	VRP_TASK_IPTN_ENTRY			IPTN_TaskEntry
#define	VRP_TASK_IPTN_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_IPTN_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_IPTN_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_IPTN_ARG			0	/* means no argument */
#endif

#if( VRP_MODULE_COPS_CLNT == VRP_YES )
/* IPTN维护任务 */
#define	VRP_TASK_COPS_CLNT_NAME			"COPS"
extern	ULONG						ulVRPTID_COPS_CLNT;
#define	VRP_TASK_COPS_CLNT_ENTRY			COPSclient_TaskEntry
#define	VRP_TASK_COPS_CLNT_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_COPS_CLNT_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_COPS_CLNT_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_COPS_CLNT_ARG			0	/* means no argument */
#endif


#if( VRP_MODULE_RTPRO_RM == VRP_YES )
/* 路由管理及路由协议任务 */
#define	VRP_TASK_ROUT_NAME			"ROUT"
extern	ULONG						ulVRPTID_ROUT;
#define	VRP_TASK_ROUT_ENTRY			RM_RoutingMain
#define	VRP_TASK_ROUT_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_ROUT_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_ROUT_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_ROUT_ARG			0	/* means no argument */
#endif

/*added by liuxueqin*/
#if( VRP_MODULE_LINK_IPX == VRP_YES )
/* 路由管理及路由协议任务 */
#define	VRP_TASK_IPXRM_NAME			"IPXRM"
extern	ULONG						ulVRPTID_IPXRM;
#define	VRP_TASK_IPXRM_ENTRY			IPXRM_RoutingMain
#define	VRP_TASK_IPXRM_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_IPXRM_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_IPXRM_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_IPXRM_ARG			0	/* means no argument */
#endif
/*end of addition by liuxueqin*/


#if( VRP_MODULE_SEC_IPSEC == VRP_YES )
/* IPSec任务 */
#define	VRP_TASK_IPSEC_NAME			"IPSP"
extern	ULONG						ulVRPTID_IPSEC;
#define	VRP_TASK_IPSEC_ENTRY		IPSecInit
#define	VRP_TASK_IPSEC_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_IPSEC_MODE			0
#define	VRP_TASK_IPSEC_SSIZE		0
#define	VRP_TASK_IPSEC_ARG			0	 /* means no argument */
#endif

#if( VRP_MODULE_SEC_IKE == VRP_YES )
/* IPSec协商任务 */
#define	VRP_TASK_IKE_NAME			"IKE"
extern	ULONG						ulVRPTID_IKE;
#define	VRP_TASK_IKE_ENTRY			isakmp_task_main
#define	VRP_TASK_IKE_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_IKE_MODE			VOS_T_MODE_PREEMPT | VOS_T_MODE_TSLICE
#define	VRP_TASK_IKE_SSIZE			0
#define	VRP_TASK_IKE_ARG			0	 /* means no argument */
#endif

#if( VRP_MODULE_UTIL_RSA == VRP_YES )
/* RSA任务，主要用于定时更新服务器密钥用 */
#define VRP_TASK_RSA_NAME			"RSA"
extern  ULONG						ulVRPTID_RSA;
#define VRP_TASK_RSA_ENTRY			RSA_TaskMain
#define VRP_TASK_RSA_PRIO			VOS_T_PRIORITY_NORMAL
#define VRP_TASK_RSA_MODE			0
#define VRP_TASK_RSA_SSIZE			0
#define VRP_TASK_RSA_ARG			0
#endif


/************************************************************************
 * VRP的任务初始化链,将记载除了ulVRPTID_VRPI以外的所有任务的ID:         *
 *		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!              *
 *		!!!                                            !!!              *
 *		!!! 请注意: 如果向任务初始化链加入新的任务,    !!!              *
 *      !!!         请一定同时修改宏VRP_TASK_NUMBER    !!!              *
 *      !!!         的值                               !!!              *
 *		!!!                                            !!!              *
 *		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!              *
 ************************************************************************/
#define	VRP_TASK_NUMBER				60
extern	ULONG						ulVRPTaskInitLink[ VRP_TASK_NUMBER ];

#if( VRP_MODULE_SEC_L2TP == VRP_YES )
/* L2TP Task: */
#define	VRP_TASK_L2TP_NAME			"L2TP"
extern	ULONG						ulVRPTID_L2TP;
VOID L2TP_Main(ULONG , ULONG , ULONG , ULONG );
#define	VRP_TASK_L2TP_ENTRY			L2TP_Main
#define	VRP_TASK_L2TP_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_L2TP_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_L2TP_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_L2TP_ARG			0	/* means no argument */
#endif

/* XOT 任务 */
#if ( VRP_MODULE_LINK_X25_XOT == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )
#define	VRP_TASK_XOT_NAME			"XOT"
extern	ULONG						ulVRPTID_XOT;
#define	VRP_TASK_XOT_ENTRY			XOT_Tcp_Main
#define	VRP_TASK_XOT_PRIO			VOS_T_PRIORITY_NORMAL	/* priority ??? */
#define	VRP_TASK_XOT_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_XOT_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_XOT_ARG			0	/* means no argument */
#endif
#endif
/* addition end by songyizhen for D24798 , 2003-08-27 */

#if( VRP_MODULE_SNMP == VRP_YES )
/* SNMP Agent Task: */
#define	VRP_TASK_SNMPAGNT_NAME			"AGNT"
extern	ULONG						    ulVRPTID_AGNT;
#define	VRP_TASK_SNMPAGNT_ENTRY			SNMP_Agent
#define	VRP_TASK_SNMPAGNT_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_SNMPAGNT_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_SNMPAGNT_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_SNMPAGNT_ARG			0	/* means no argument */

/* SNMP Trap Task: */
#define	VRP_TASK_SNMPTRAP_NAME			"TRAP"
extern	ULONG						    ulVRPTID_TRAP;
#define	VRP_TASK_SNMPTRAP_ENTRY			SNMP_Trap
#define	VRP_TASK_SNMPTRAP_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_SNMPTRAP_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_SNMPTRAP_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_SNMPTRAP_ARG			0	/* means no argument */
#endif

#if( VRP_MODULE_CFG_CLI_FTP_SERVER == VRP_YES )
/* FTP Server Task: */
#define	VRP_TASK_FTPS_NAME			"FTPS"
extern	ULONG						ulVRPTID_FTPS;
#define	VRP_TASK_FTPS_ENTRY			FTP_ServerRun
#define	VRP_TASK_FTPS_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_FTPS_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_FTPS_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_FTPS_ARG			0	/* means no argument */
#endif


#if( VRP_MODULE_LINK_TEL == VRP_YES )
/* TEL Task: */
#define	VRP_TASK_TEL_NAME			"TEL"
extern	ULONG						ulVRPTID_TEL;
#define	VRP_TASK_TEL_ENTRY			Tel_Pots
#define	VRP_TASK_TEL_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_TEL_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_TEL_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_TEL_ARG			0	/* means no argument */
/* POTS Task: */
#define	VRP_TASK_POTS_NAME			"POTS"
extern	ULONG						ulVRPTID_POTS;
#define	VRP_TASK_POTS_ENTRY			PotsCe_Pots
#define	VRP_TASK_POTS_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_POTS_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_POTS_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_POTS_ARG			0	/* means no argument */
#endif

#if( VRP_MODULE_LINK_CC == VRP_YES )
/* CC Task: */
#define	VRP_TASK_CC_NAME			"CC"
extern	ULONG						ulVRPTID_CC;
#define	VRP_TASK_CC_ENTRY			CC_Main
#define	VRP_TASK_CC_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_CC_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_CC_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_CC_ARG				0	/* means no argument */
#endif

#if( VRP_MODULE_LINK_Q921 == VRP_YES )
/* Q921 Task: */
#define	VRP_TASK_Q921_NAME			"Q921"
extern	ULONG						ulVRPTID_Q921;
#define	VRP_TASK_Q921_ENTRY			Q921_Main
#define	VRP_TASK_Q921_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_Q921_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_Q921_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_Q921_ARG			0	/* means no argument */
#endif

#if( VRP_MODULE_LINK_Q931 )
/* Q931 Task: */
#define	VRP_TASK_Q931_NAME			"Q931"
extern	ULONG						ulVRPTID_Q931;
#define	VRP_TASK_Q931_ENTRY			Q931_Main
#define	VRP_TASK_Q931_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_Q931_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_Q931_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_Q931_ARG			0	/* means no argument */
#endif

#if( VRP_MODULE_SAN_TRVS == VRP_YES )
/* TRVS Task: */
#define	VRP_TASK_TRVS_NAME			"TRVS"
extern	ULONG						ulVRPTID_TRVS;
#define	VRP_TASK_TRVS_ENTRY			TRVS_Main
#define	VRP_TASK_TRVS_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_TRVS_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_TRVS_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_TRVS_ARG			0	/* means no argument */
#endif

#if( VRP_MODULE_VOS_VFS == VRP_YES )
#define	VRP_TASK_VFS_NAME			"VFS"
extern	ULONG						ulVRPTID_VFS;
#define	VRP_TASK_VFS_ENTRY			VOS_VFS_Task
#define	VRP_TASK_VFS_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_VFS_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_VFS_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_VFS_ARG			0	/* means no argument */

/***sunliang 35592 add for D25081 R007 与R008 文件系统兼容项目*/ 
/*
#define VRP_TASK_ColdBackUp_NAME   "CBU"
extern  ULONG                         ulVRPTID_CBU;
#define VRP_TASK_ColdBackUp_ENTRY   VOS_CBU_Task
#define VRP_TASK_ColdBackUp_PRIO    VOS_T_PRIORITY_NORMAL
#define VRP_TASK_ColdBackUp_MODE   0
#define VRP_TASK_ColdBackUp_SSIZE   0
#define VRP_TASK_ColdBackUp_ARG     0
******/

#endif


#if( VRP_MODULE_CFG_CLI_CFGFILE == VRP_YES )
/* Config file Task: */
#define	VRP_TASK_CFM_NAME			"CFM"
extern	ULONG						ulVRPTID_CFM;
#define	VRP_TASK_CFM_ENTRY			CFM_Main
#define	VRP_TASK_CFM_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_CFM_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_CFM_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_CFM_ARG			0	/* means no argument */
#endif

#if( VRP_MODULE_HA_SLAVE2MAIN == VRP_YES )
/* HA Task: */
#define	VRP_TASK_HA_NAME			"HS2M"
extern	ULONG						ulVRPTID_HA;
#define	VRP_TASK_HA_ENTRY			HA_RoutineTask
#if (VRP_YES == VRP_VERSION_5)
#define	VRP_TASK_HA_PRIO			(VOS_T_PRIORITY_NORMAL + 10)
#else
#define	VRP_TASK_HA_PRIO			VOS_T_PRIORITY_NORMAL
#endif
#define	VRP_TASK_HA_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_HA_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_HA_ARG				0	/* means no argument */

#if (VRP_PRODUCT_GSR==VRP_YES)
#define HA_INITIALIZE_OK    0
#define HA_INITIALIZE_FAIL    1
#endif

#endif

#if( VRP_MODULE_HRP == VRP_YES )
/* HRP Task: */
#define	VRP_TASK_HRP_NAME		"HRP"
extern	ULONG						ulVRPTID_HRP;
#define	VRP_TASK_HRP_ENTRY		HRP_RoutineTask
#define	VRP_TASK_HRP_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_HRP_MODE		0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_HRP_SSIZE		0	/* means default value: 2048 */
#define	VRP_TASK_HRP_ARG			0	/* means no argument */
#endif

#if( VRP_MODULE_CFG_MODEM == VRP_YES )
/* modem Task: */
#define	VRP_TASK_MDM_NAME			"MDMT"
extern	ULONG						g_ulTID_MDM;
#define	VRP_TASK_MDM_ENTRY			MDM_Task
#define	VRP_TASK_MDM_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_MDM_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_MDM_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_MDM_ARG			0	/* means no argument */
#endif

#if( VRP_MODULE_NTP == VRP_YES )
/* NTP Task: */
#define	VRP_TASK_NTP_NAME			"NTPT"
extern	ULONG						g_ulVRPTID_NTP;
#define	VRP_TASK_NTP_ENTRY			NTP_MainTask
#define	VRP_TASK_NTP_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_NTP_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_NTP_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_NTP_ARG			0	/* means no argument */
#endif

/* added by mayun for tcp backup */
#if (VRP_VERSION_5 == VRP_YES)
#if (VRP_MAIN_BOARD == VRP_YES )
#if (VRP_MODULE_HA_DATA == VRP_YES && VRP_MODULE_HA_SLAVE2MAIN == VRP_YES)
#if( VRP_MODULE_IP_SOCKET == VRP_YES )
#define VRP_TASK_SOHA_NAME          "SOHA"
#define	VRP_TASK_SOHA_ENTRY			Sock_Ha_TaskEntry
extern ULONG                        g_ulVRPTID_SockHA;
#define VRP_TASK_SOHA_PRIO          VOS_T_PRIORITY_NORMAL
#define VRP_TASK_SOHA_MODE          0   /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define VRP_TASK_SOHA_SSIZE         0   /* means default value: 2048 */
#define VRP_TASK_SOHA_ARG           0   /* means no argument */
#endif
#endif
#endif
#endif

#if (VRP_PRODUCT_GSR==VRP_YES)
 
#if( NE80_MODULE_ADP == VRP_YES )
/* IO_AGENT Task: */
#define	NE80_TASK_IOAGT_NAME			"IOA"
extern	ULONG						ulRPS_IOAGT;
#define	NE80_TASK_IOAGT_ENTRY		RPS_IOAgentTask
#define	NE80_TASK_IOAGT_PRIO			VOS_T_PRIORITY_NORMAL	/* used temp */
#define	NE80_TASK_IOAGT_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	NE80_TASK_IOAGT_SSIZE		0	/* means default value: 2048 */
#define	NE80_TASK_IOAGT_ARG			0	/* means no argument */
#endif

/* defined by laixq */
#if( NE80_MODULE_SRM )
/* SRM Task: */
extern VOID SRM_MainFunction(ULONG	ulArg0,
				             ULONG	ulArg1,
				             ULONG	ulArg2,
				             ULONG	ulArg3  );
#define	NE80_TASK_SRM_NAME	        "SRM"            /* 系统运行管理任务名称 */
#define	NE80_TASK_SRM_ENTRY			SRM_MainFunction /* 系统运行管理任务函数 */
#define	NE80_TASK_SRM_PRIO			VOS_T_PRIORITY_ABOVE_NORMAL	/* 优先级 */
#define	NE80_TASK_SRM_MODE			0	/* 0表示使用缺省值T_NOPREEMPT | T_NOTSLICE */
#define	NE80_TASK_SRM_SSIZE			0	/* 0表示使用缺省值2048 */
#define	NE80_TASK_SRM_ARG			0	/* 0表示没有参数 */
#endif
#if( L3_MODULE_L2IF == VRP_YES )
/* L2IF Task: */
extern VOID L2IF_MainFunction(ULONG	ulArg0,
				             ULONG	ulArg1,
				             ULONG	ulArg2,
				             ULONG	ulArg3  );
#define	L3_TASK_L2IF_NAME	        "L2IF"            /* 二层接口管理任务 */
extern   ULONG                   g_ulL3TID_L2IF;
#define	L3_TASK_L2IF_ENTRY		 L2IF_MainFunction   /* 二层接口管理任务函数 */
#define	L3_TASK_L2IF_PRIO			VOS_T_PRIORITY_NORMAL	              /* 优先级 */
#define	L3_TASK_L2IF_MODE			0	               /* 0表示使用缺省值T_NOPREEMPT | T_NOTSLICE */
#define	L3_TASK_L2IF_SSIZE			0	               /* 0表示使用缺省值2048 */
#define	L3_TASK_L2IF_ARG			0	               /* 0表示没有参数 */
#endif
#if( L3_MODULE_ARP == VRP_YES )
/* PROXY Task: */
extern VOID Proxy_MainFunction(ULONG	ulArg0,
				             ULONG	ulArg1,
				             ULONG	ulArg2,
				             ULONG	ulArg3  );
#define	L3_TASK_PROXY_NAME	        "PRXY"            /* ARP PROXY任务 */
extern   ULONG                   g_ulL3TID_Proxy;
#define	L3_TASK_PROXY_ENTRY		 Proxy_MainFunction   /* ARP PROXY任务入口 */
#define	L3_TASK_PROXY_PRIO			VOS_T_PRIORITY_NORMAL	               /* 优先级 */
#define	L3_TASK_PROXY_MODE			0	               /* 0表示使用缺省值T_NOPREEMPT | T_NOTSLICE */
#define	L3_TASK_PROXY_SSIZE			0	               /* 0表示使用缺省值2048 */
#define	L3_TASK_PROXY_ARG			0	               /* 0表示没有参数 */
#endif

#if (NE80_MODULE_LOAD == VRP_YES )

extern VOID LOAD_Main(ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);
#define	NE80_TASK_LOAD_NAME			"LOAD"
extern	ULONG						ulRPSTID_DLD;
#define	NE80_TASK_LOAD_ENTRY		LOAD_Main
#define	NE80_TASK_LOAD_PRIO			VOS_T_PRIORITY_NORMAL	/* used temp */
#define	NE80_TASK_LOAD_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	NE80_TASK_LOAD_SSIZE		0	/* means default value: 2048 */
#define	NE80_TASK_LOAD_ARG			0	/* means no argument */

#endif /*(NE80_MODULE_LOAD == VRP_YES )*/
#if (NE80_MODULE_DIAG == VRP_YES )

/* DIAG Task: */
#define	NE80_TASK_DIAG_NAME			"DIAG"
extern	ULONG						g_ulDiagTaskID;
#define	NE80_TASK_DIAG_ENTRY		DIAG_Init
#define	NE80_TASK_DIAG_PRIO			VOS_T_PRIORITY_NORMAL	/* used temp */
#define	NE80_TASK_DIAG_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	NE80_TASK_DIAG_SSIZE		0	/* means default value: 2048 */
#define	NE80_TASK_DIAG_ARG			0	/* means no argument */

#endif /*(NE80_MODULE_DIAG == VRP_YES )*/

#if (VRP_MODULE_VOS_VFS == VRP_YES )

/* VFS Task: */
#define	NE80_TASK_VFS_NAME			"VFS"
extern	ULONG						g_ulVfsTaskID;
#define	NE80_TASK_VFS_ENTRY		    VOS_VFS_Task
#define	NE80_TASK_VFS_PRIO			VOS_T_PRIORITY_NORMAL	/* used temp */
#define	NE80_TASK_VFS_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	NE80_TASK_VFS_SSIZE			0	/* means default value: 2048 */
#define	NE80_TASK_VFS_ARG			0	/* means no argument */

#endif /*(NE80_MODULE_VFS == VRP_YES )*/

#if (NE80_MODULE_ETA == VRP_YES)
extern ULONG ETHTrunk_TaskMain ( ULONG , 
						  ULONG , 
						  ULONG , 
						  ULONG );

#define VRP_TASK_ETA_NAME   "ETA"
#define VRP_TASK_ETA_ENTRY  ETHTrunk_TaskMain
#define VRP_TASK_ETA_PRIO   VOS_T_PRIORITY_NORMAL
#define VRP_TASK_ETA_MODE   0
#define VRP_TASK_ETA_SSIZE  0
#define VRP_TASK_ETA_ARG    0
#endif

#if (NE80_MODULE_QOS == VRP_YES )
#define NE80_TASK_QOS_NAME		"QOS"				/* 监控与调试任务名称 */
#define NE80_TASK_QOS_ENTRY		QOS_Task	/* 监控与调试任务函数 */
#define NE80_TASK_QOS_PRIO		VOS_T_PRIORITY_NORMAL	/* 优先级 */
#define NE80_TASK_QOS_MODE		0	/* 0表示使用缺省值T_NOPREEMPT | T_NOTSLICE */
#define NE80_TASK_QOS_SSIZE		0	/* 0表示使用缺省值2048 */
#define NE80_TASK_QOS_ARG		0	/* 0表示没有参数 */
#endif /*(NE80_MODULE_QOS == VRP_YES ) */

#if ( NE80_MODULE_DPT == VRP_YES ) /*bywensomIT*/
extern	VOID DPT_Main(ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);
extern	ULONG	ulNE80TID_DPT;
#define VRP_TASK_DPT_NAME	"RPR"		
#define VRP_TASK_DPT_ENTRY	DPT_Main
#define VRP_TASK_DPT_PRIO	VOS_T_PRIORITY_NORMAL	/* 优先级 */
#define VRP_TASK_DPT_MODE	0	/* 0表示使用缺省值T_NOPREEMPT | T_NOTSLICE */
#define VRP_TASK_DPT_SSIZE	0	/* 0表示使用缺省值2048 */
#define VRP_TASK_DPT_ARG		0	/* 0表示没有参数 */
#endif

/* HGMP task process */
#if( L3_MODULE_HGMP == VRP_YES )
#define	L3_TASK_HGMP_NAME			"HGMP"
extern	ULONG       				g_ulHgmpTaskId;
#define	L3_TASK_HGMP_ENTRY        HGMP_Entry
#define	L3_TASK_HGMP_PRIO			VOS_T_PRIORITY_NORMAL	/* priority  */
#define	L3_TASK_HGMP_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	L3_TASK_HGMP_SSIZE			0	/* means default value: 2048 */
#define	L3_TASK_HGMP_ARG		    0   /* means no argument */
#endif

#if( L3_MODULE_HSRP == VRP_YES )
#define	L3_TASK_HSRP_NAME			"HSRP"
extern	ULONG       				g_ulHsrpTaskId;
#define	L3_TASK_HSRP_ENTRY			HSRP_TaskMain
#define	L3_TASK_HSRP_PRIO			VOS_T_PRIORITY_NORMAL	/* priority  */
#define	L3_TASK_HSRP_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	L3_TASK_HSRP_SSIZE			0	/* means default value: 2048 */
#define	L3_TASK_HSRP_ARG		    0   /* means no argument */
#endif

#if( L3_MODULE_RSTP == VRP_YES )
/* 和任务创建有关的宏 */
#define RSTP_TASK_NAME			"STP"                             /* 任务名称 */
#define RSTP_TASK_PRIORITY			VOS_T_PRIORITY_ABOVE_NORMAL                                  /* 任务优先级 */
#define RSTP_TASK_MODE			0	/* 任务运行模式(缺省) */
#define RSTP_TASK_STACKSIZE			0	/* 任务栈大小(缺省) */
#define RSTP_TASK_TASKARG			0	/* 启动参数(缺省) */
#define RSTP_TASK_ENTRY			RSTP_MainFunction       /* 任务入口地址 */
#endif

#if( L3_MODULE_RSTP == VRP_YES )
/* 端口状态变化通知消息队列 */
#define VRP_RSTP_QUEUE_NOTIFY_NAME   "STPN"
#define VRP_RSTP_QUEUE_NOTIFY_LENGTH 512
#define VRP_RSTP_QUEUE_NOTIFY_MODE   VOS_Q_FIFO | VOS_Q_ASYN
extern  ULONG                        ulRSTPNotifyQueID;

/* RSTP协议报文队列 */
#define VRP_RSTP_PACKET_QUEUE_NAME   "STPP"
#if(VRP_OS_VXWORKS == VRP_YES)
#define VRP_RSTP_PACKET_QUEUE_LENGTH 2000
#else
#define VRP_RSTP_PACKET_QUEUE_LENGTH 512
#endif
#define VRP_RSTP_PACKET_QUEUE_MODE   VOS_Q_FIFO | VOS_Q_ASYN

/* RSTP定时器事件队列 */
#define VRP_RSTP_TIMER_QUEUE_NAME   "STPT"
#if(VRP_OS_VXWORKS == VRP_YES)
#define VRP_RSTP_TIMER_QUEUE_LENGTH 1000
#else
#define VRP_RSTP_TIMER_QUEUE_LENGTH 512
#endif
#define VRP_RSTP_TIMER_QUEUE_MODE   VOS_Q_FIFO | VOS_Q_ASYN

extern  ULONG                      ulRstpQueID;

#endif

#endif  /* #if (VRP_PRODUCT_GSR==VRP_YES) */


#if( VRP_MODULE_BAS_LAM == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )
extern VOID LAM_TaskEntry( ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);
#define VRP_TASK_LAM_NAME           "LAM"
#define VRP_TASK_LAM_ENTRY          LAM_TaskEntry
#define VRP_TASK_LAM_PRIO           VOS_T_PRIORITY_NORMAL
#define VRP_TASK_LAM_MODE           0   /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define VRP_TASK_LAM_SSIZE          0   /* means default value: 2048 */
#define VRP_TASK_LAM_ARG            0   /* means no argument */
#endif
#endif

#if( VRP_MODULE_BAS_AAA == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )
/* AAA任务 */
#define	VRP_TASK_AAA_NAME	    "AAA"
extern	ULONG			    ulVRPTID_AAA;
#define	VRP_TASK_AAA_ENTRY	    AAA_TaskEntry
#define	VRP_TASK_AAA_PRIO	    VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_AAA_MODE	    0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_AAA_SSIZE	    0	/* means default value: 2048 */
#define	VRP_TASK_AAA_ARG	    0	/* means no argument */
#endif
#endif
/*end*/

#if( VRP_MODULE_BAS_RADIUS == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )
/* RADIUS Task: by zyl27499 */
#define	VRP_TASK_RADIUS_NAME		"RDS"
extern	ULONG                       ulVRPTID_RADIUS;
#define	VRP_TASK_RADIUS_ENTRY		RD_TaskEntry
#define	VRP_TASK_RADIUS_PRIO		VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_RADIUS_MODE	    0   /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_RADIUS_SSIZE		0	/* means default value: 2048 */
#define	VRP_TASK_RADIUS_ARG			0	/* means no argument */
#endif
#endif

#if( VRP_MODULE_BAS_HWTACACS == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )
/* TACACS Task: by sunyanfeng */
#define	VRP_TASK_TACACS_NAME		"TAC"
extern	ULONG                       g_ulVRPTID_TAC;
#define	VRP_TASK_TACACS_ENTRY		TAC_TaskEntry
#define	VRP_TASK_TACACS_PRIO		VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_TACACS_MODE	    0   /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_TACACS_SSIZE		0	/* means default value: 2048 */
#define	VRP_TASK_TACACS_ARG			0	/* means no argument */
#endif
#endif

#if (VRP_MODULE_BAS_WEB == VRP_YES)
#if( VRP_IO_BOARD == VRP_NO )
#define VRP_TASK_BAS_WEB_NAME       "WEB"
extern  ULONG                       ulVRPTID_WEB;
#define	VRP_TASK_BAS_WEB_ENTRY      WEB_TaskEntry
#define	VRP_TASK_BAS_WEB_PRIO	    VOS_T_PRIORITY_NORMAL /* question */
#define	VRP_TASK_BAS_WEB_MODE	    0   /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_BAS_WEB_SSIZE	    0   /* means default value: 2048 */
#define	VRP_TASK_BAS_WEB_ARG	    0   /* means no argument */
#endif
#endif
/* end of addition yangjianjun 2003-06-05 */

#if (VRP_MODULE_BAS_CM == VRP_YES)
#if( VRP_IO_BOARD == VRP_NO )
#define VRP_TASK_BAS_UCM_NAME       "UCM"
extern  ULONG                       ulVRPTID_UCM;
#define	VRP_TASK_BAS_UCM_ENTRY      CM_TaskEntry
#define	VRP_TASK_BAS_UCM_PRIO	    VOS_T_PRIORITY_NORMAL /* question */
#define	VRP_TASK_BAS_UCM_MODE	    0   /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_BAS_UCM_SSIZE	    0   /* means default value: 2048 */
#define	VRP_TASK_BAS_UCM_ARG	    0   /* means no argument */
#endif
#endif

#if( ( VRP_MODULE_MPLS_LSPM == VRP_YES) && ( ((VRP_DISTRIBUTED == VRP_YES)&&(VRP_MAIN_BOARD == VRP_YES)) || (VRP_CENTERALIZATION == VRP_YES)))  
/* MPLS LSPM Task: */
#define	VRP_TASK_LSPM_NAME			"LSPM"
extern	ULONG						ulVRPTID_LSPM;
#define	VRP_TASK_LSPM_ENTRY			LSPM_TaskMain
#define	VRP_TASK_LSPM_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_LSPM_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_LSPM_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_LSPM_ARG   	    0	/* means no argument */
#endif

#if (VRP_VERSION_5 == VRP_YES)
#else
#if( VRP_MODULE_MPLS_RSVP == VRP_YES )
/* MPLS RSVPTE 任务 */
#define	VRP_TASK_RSVP_NAME			"RSVP"
extern	ULONG						ulVRPTID_RSVP;
#define	VRP_TASK_RSVP_ENTRY			RSVP_TaskMain
#define	VRP_TASK_RSVP_PRIO			195	/* priority ??? */
#define	VRP_TASK_RSVP_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_RSVP_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_RSVP_ARG			0	/* means no argument */
#endif
#endif

#if( VRP_MODULE_MPLS_LDP== VRP_YES )
/* HA Task: */
#define	VRP_TASK_LDP_NAME			"LDP"
extern	ULONG						ulVRPTID_LDP;
#if (VRP_VERSION_5 == VRP_YES)
#define	VRP_TASK_LDP_ENTRY			LDP_TaskMain
#else
#define	VRP_TASK_LDP_ENTRY			ldpMain
#endif
#define	VRP_TASK_LDP_PRIO			VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_LDP_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_LDP_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_LDP_ARG			0	/* means no argument */
#endif

#if( VRP_PRODUCT_8060 == VRP_YES )
#define    VRP_TASK_SRM_NAME    "SRM"
extern     ULONG    ulVRPTID_SRM;
#define	VRP_TASK_SRM_ENTRY      SRM_MainFunction
#define	VRP_TASK_SRM_PRIO			220 /* question */
#define	VRP_TASK_SRM_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_SRM_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_SRM_ARG			0	/* means no argument */
#endif

#if( VRP_PRODUCT_8060 == VRP_YES )
#define    VRP_TASK_DIAG_NAME    "DIAG"
extern     ULONG    ulVRPTID_DIAG;
#define	VRP_TASK_DIAG_ENTRY      DIAG_TaskEntry
#define	VRP_TASK_DIAG_PRIO			190 /* question */
#define	VRP_TASK_DIAG_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_DIAG_SSIZE			0	/* means default value: 2048 */
#define	VRP_TASK_DIAG_ARG			0	/* means no argument */
#endif
/* end of addition luoli 20021209 */

#if( VRP_MODULE_MPLS_LSPAGT== VRP_YES )
#define	VRP_TASK_LSPAGT_NAME		"LAGT"
extern	ULONG						ulVRPTID_LSPAGT;
#define	VRP_TASK_LSPAGT_ENTRY		LSPAGT_TaskMain
#define	VRP_TASK_LSPAGT_PRIO		VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_LSPAGT_MODE		0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_LSPAGT_SSIZE		0	/* means default value: 2048 */
#define	VRP_TASK_LSPAGT_ARG			0	/* means no argument */
#endif
/*隧道管理任务*/
#if( VRP_MODULE_VPN_TNLM == VRP_YES )
#define	VRP_TASK_TNLM_NAME			"TNLM"
extern	ULONG						ulVRPTID_TNLM;
VOID TNLM_Main(ULONG , ULONG , ULONG , ULONG );
#define	VRP_TASK_TNLM_ENTRY			TNLM_Main
#define	VRP_TASK_TNLM_PRIO			VOS_T_PRIORITY_NORMAL/*D19927*/
#define	VRP_TASK_TNLM_MODE			0	/* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_TNLM_SSIZE			0	/* means default value: 2048 */ 
#define	VRP_TASK_TNLM_ARG			0	/* means no argument */ 
#endif 


/************************************************************************
 * 组播本机接收发送组播数据测试应用任务                                 *
 ************************************************************************/
#define	VRP_TASK_PIMTST_NAME        "PIMT"
extern	ULONG                       g_ulVRPTID_PIMTST;
#define	VRP_TASK_PIMTST_ENTRY       TEST_PIM_MainTask
#define	VRP_TASK_PIMTST_PRIO        VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_PIMTST_MODE        0   /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_PIMTST_SSIZE       0   /* means default value: 2048 */
#define	VRP_TASK_PIMTST_ARG         0   /* means no argument */

/* STAND BY任务 */
#define	VRP_TASK_STND_NAME          "STND"
extern	ULONG                       ulVRPTID_STANDBY;
#define	VRP_TASK_STND_ENTRY         VRP_StandByTask
#define	VRP_TASK_STND_PRIO          VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_STND_MODE          0   /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_STND_SSIZE         0   /* means default value: 2048 */
#define	VRP_TASK_STND_ARG           0   /* means no argument */

#if( R8070_MODULE_PFM == VRP_YES )
#define VRP_TASK_PFM_NAME           "PRMN"
#define VRP_TASK_PFM_ENTRY          PFM_MIB_PerformanceRMONTask
#define	VRP_TASK_PFM_PRIO           VOS_T_PRIORITY_NORMAL
#define	VRP_TASK_PFM_MODE           0   /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_PFM_SSIZE          0   /* means default value: 2048 */
#define	VRP_TASK_PFM_ARG            0   /* means no argument */
#endif

/************************************************************************
 * 报文转发任务的队列的参数:                                            *
 ************************************************************************/
/* 定时器消息队列 */
#define	VRP_SOCK_QUEUE_TIMER_NAME       "SKTM"
#define	VRP_SOCK_QUEUE_TIMER_LENGTH     2048
#define	VRP_SOCK_QUEUE_TIMER_MODE       VOS_Q_FIFO | VOS_Q_ASYN
extern	ULONG                           ulSOCKTmrQueID;
/* 配置消息队列 */
#define	VRP_SOCK_QUEUE_CONFIG_NAME      "SKCF"
#define	VRP_SOCK_QUEUE_CONFIG_LENGTH    VRP_CONFIG_MSG_QUEUE_LENGTH
#define	VRP_SOCK_QUEUE_CONFIG_MODE      VOS_Q_FIFO | VOS_Q_ASYN
extern	ULONG                           ulSOCKCfgQueID;

#if (VRP_YES == VRP_MODULE_IPV6)
#define VRP_SOCK_QUEUE_PMTU_NAME        "SKPM"
#define VRP_SOCK_QUEUE_PMTU_LENGTH      2048
#define VRP_SOCK_QUEUE_PMTU_MODE        VOS_Q_FIFO | VOS_Q_ASYN
extern  ULONG                           ulSOCKPmtuQueID;
#endif


#if(VRP_MODULE_SAN_AM == VRP_YES)
/* SAN BACKUP 任务 */
#define	VRP_TASK_BACK_NAME          "BAKT"
extern	ULONG                       ulVRPTID_BACK;
#define	VRP_TASK_BACK_ENTRY         AM_TaskMain
#define	VRP_TASK_BACK_PRIO          64  /* priority */
#define	VRP_TASK_BACK_MODE          0   /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define	VRP_TASK_BACK_SSIZE         0   /* means default value: 2048 */
#define	VRP_TASK_BACK_ARG           0   /* means no argument */
#endif

/************************************************************************
 * VRP启动的错误记录:                                                   *
 ************************************************************************/
extern	ULONG       ulVRPStartError;        /* 这里需要确定下面所有错误码 ??? */
#define	VRP_INIT_ERROR_INIT_HARD_SYS        1
#define	VRP_INIT_ERROR_INIT_VOS             2
#define	VRP_INIT_ERROR_CREATE_VRP_ROOT_TASK	3
#define	VRP_INIT_ERROR_CREATE_INIT_TASK     4
#define	VRP_INIT_ERROR_SET_DEVICE_LINK      5
#define	VRP_INIT_ERROR_INIT_CONFIG_PLANE    6
#define	VRP_INIT_ERROR_INIT_COMMAND_LINE    7

/************************************************************************
 * VRP任务的事件位,必须为2的整数次幂:                                   *
 * 这里定义的是所有任务都需要使用的公共事件位和任务SockRun的事件位.     *
 ************************************************************************/
/*--------------------------------*/
/* 公共事件位:定时器事件          */
/*--------------------------------*/
#define VRP_EVENT_TIMERREQ          0X00008000	/* "00000000 00000000 10000000 00000000" */
/*--------------------------------*/
/* 公共事件位:异步socket事件      */
/*--------------------------------*/
#define VRP_EVENT_ASOCKETREQ        0X00004000	/* "00000000 00000000 01000000 00000000" */
/*--------------------------------*/
/* 公共事件位:配置事件            */
/*--------------------------------*/
#define	VRP_EVENT_CONFIGREQ         0X00002000	/* "00000000 00000000 00100000 00000000" */
/*--------------------------------*/
/* 公共事件位:运行指示事件        */
/*--------------------------------*/
#define	VRP_EVENT_RUNINDICATION     0X00001000	/* "00000000 00000000 00010000 00000000" */
/*--------------------------------*/
/* 公共事件位:任务释放完毕事件    */
/*--------------------------------*/
#define	VRP_EVENT_STANDBYOVER       0X00000800	/* "00000000 00000000 00001000 00000000" */

/*--------------------------------*/
/* SockRun任务的私有事件:数据事件 */
/*--------------------------------*/
#define	VRP_SOCK_EVENT_DATAREQ      0X00000001	/* "00000000 00000000 00000000 00000001" */
/*--------------------------------*/
/* SockRun任务的私有事件:Tick事件 */
/*--------------------------------*/
#define VRP_SOCK_EVENT_TICK         0X00000400	/* "00000000 00000000 00000100 00000000" */
#define RSTP_PACKET_RECV            0x00010000    /* "00000000 00000001 00000000 00000000" */
#define RSTP_EVENT_NOTIFY           0x00020000    /* "00000000 00000010 00000000 00000000" */

#if (VRP_PRODUCT_GSR==VRP_YES)
/*------------------------------------*/
/* SockRun任务的私有事件:端口状态变化通知事件  */
/*-----------------------------------*/
#define VRP_EVENT_NOTIFY            0X00000800    /* "00000000 00000000 00001000 00000000" */

#define SOCK_PACKET_RSTP            0X00010000    /* "00000000 00000001 00000000 00000000" */
#endif

#if (VRP_YES == VRP_MODULE_IPV6)
#define VRP_EVENT_PMTUREQ           0X00080000    /* "00000000 00001000 00000000 00000000" */
#define VRP_EVENT_PMTUFLUSH	        0X00100000    /*  00000000 00010000 00000000 00000000" */
#endif

/*--------------------------------*/
/* Standby任务的调度事件:SOCK任务 */
/*--------------------------------*/
#define VRP_STND_EVENT_SOCK         (1 << 0)
/*--------------------------------*/
/* Standby任务的调度事件:ROUT任务 */
/*--------------------------------*/
#define VRP_STND_EVENT_ROUT         (1 << 1)

#if(VRP_MODULE_SAN_RTP == VRP_YES)
/*-----------------------------------*/
/* RTPRelay模块的队列的事件:SOCK任务 */
/*-----------------------------------*/
#define VRP_SOCK_EVENT_SRTP         0X00010000
#endif

/************************************************************************
 * SockRun任务的子任务调度标志,必须为2的整数次幂:                       *
 ************************************************************************/
#if( VRP_MODULE_QUEUE == VRP_YES )
#define VRP_SOCKTASK_QUEUE          (1 << 0)
#endif

#if( VRP_MODULE_LINK_X25 == VRP_YES )
#define VRP_SOCKTASK_X25            (1 << 14)
#endif

#if( VRP_MODULE_LINK_MODEM == VRP_YES )
#define VRP_SOCKTASK_MODEM          (1 << 6)
#endif

#if( VRP_MODULE_LINK_DDR == VRP_YES )
#define VRP_SOCKTASK_DDR            (1 << 7)
#endif

/* 使用这个宏通过向STND任务写事件释放CPU控制权: */
#define VRP_StandByEvent( ulEvWrite ) \
{ \
    ULONG ulEvRcv; \
    VOS_Ev_Write( ulVRPTID_STANDBY, ulEvWrite ); \
    VOS_Ev_Read( VRP_EVENT_STANDBYOVER, &ulEvRcv, VOS_WAIT, 1000 ); \
}

/************************************************************************
 * root.c中实现的所有函数                                               *
 ************************************************************************/
extern  VOID    root( VOID );
extern  VOID    VRP_Root( ULONG, ULONG, ULONG, ULONG );
extern  VOID    VRP_InitializeTask( ULONG, ULONG, ULONG, ULONG );
extern  VOID    VRP_RootInit( VOID );
extern  VOID    VRP_RegestAllCmd( VOID );
extern  VOID    VRP_RegestAllLINKCmd( VOID );
extern  VOID    VRP_SockRun( ULONG, ULONG, ULONG, ULONG );
extern  VOID    VRP_IfTask( ULONG, ULONG, ULONG, ULONG );
#if ((VRP_CENTERALIZATION == VRP_YES) && (IF_HOT_CTL == VRP_YES))
/*增加集中式热插拔   pengjimei for DEV_HOTCTL 2002/12/10*/
extern  VOID    VRP_IfDevTask( ULONG, ULONG, ULONG, ULONG );
#endif
extern  ULONG   VRP_SockRunInit( VOID );
extern  ULONG   VRP_GetTaskFollowMe( ULONG );
extern  VOID    VRP_SockTimerIntr( VOID );
extern  VOID    VRP_SockConfigIntr( VOID );
extern  ULONG   VRP_SendTickEventToSock( VOID );
extern  VOID    VRP_ProcTickEventBySock( VOID );
#if (VRP_PRODUCT_GSR==VRP_YES)
extern  VOID    VOS_SyncRtcSysTime();
extern  VOID    VOS_SetDiffTime(ULONG ulDiffTime);
#endif

/************************************************************************
 * root.c中调用的所有外部函数(不包括VOS等公共函数)                      *
 ************************************************************************/

#if ( VRP_CENTERALIZATION == VRP_YES )
extern  VOID    SWT_Clear( VOID );
extern  VOID    SWT_Close( VOID );
#endif

/* Added by liujianfeng*/
extern VOID PHY_RegCmd(VOID);
extern ULONG RegPhyMsgIC(VOID);

/*added by gongyibin*/
extern VOID VOS_RegMemMsgIC(VOID);
extern VOID VOS_RegToIC(VOID);

#if(VRP_IO_BOARD==VRP_NO &&  VRP_PRODUCT_8060 == VRP_NO)
#if (VRP_PRODUCT_8070 == VRP_YES)
extern VOID MAIN_BOARD_PHY_ConfigEntr(VOID* pMsgRcv, VOID**ppMsgSnd);
#elif (VRP_PRODUCT_GSR == VRP_YES)
extern ULONG MAIN_BOARD_PHY_ConfigEntr(VOID* pMsgRcv, VOID**ppMsgSnd);
#else
extern VOID MAIN_BOARD_PHY_ConfigEntr(VOID *);
#endif
#endif

/* Added by liujianfeng*/

extern  ULONG   VRP_HardSysInit( VOID );
extern  ULONG   VOS_Start( VOID );
extern  LONG    PhySetDevLink( void );	/* ??? 这个函数应该由底层提供,但是定义不规范 */

#if( VRP_MODULE_CFG_BASE == VRP_YES )
extern  ULONG   CFG_PlaneInit( VOID );
extern  ULONG   CFG_CheckMsg( VOID * );
extern  ULONG   CFG_GetFirstTabElemID( VOID * );
#endif

#if( VRP_MODULE_CFG_CLI_BASE == VRP_YES )
extern  ULONG   CLI_CmdInit( VOID );
extern  VOID    CLI_RegSysCmd( VOID );
#endif

#if( VRP_MODULE_CFG_CLI_CFGFILE == VRP_YES )
extern  ULONG   CFM_Init( VOID );
extern VOID CFM_RegCmd(VOID);
#endif
#if( VRP_MODULE_CFA == VRP_YES )
extern  ULONG   CFA_Init( VOID );
#endif
#if( VRP_MODULE_CFG_IC_BASE == VRP_YES )
extern  VOID    IC_TaskEntry( ULONG, ULONG, ULONG, ULONG );
extern  VOID    IC_RegCommand( VOID );
#endif

#if( VRP_MODULE_VPN_L2VPN == VRP_YES )
extern  VOID    L2VPN_TaskEntry( ULONG, ULONG, ULONG, ULONG );
extern  VOID    L2VPN_RegCommand( VOID );
#endif

#if( VRP_MODULE_TELNET_CLIENT == VRP_YES )
extern  VOID    TEL_RegCmd( VOID );
extern  ULONG   TEL_RegToIC( VOID );
#endif

#if( VRP_MODULE_FTP_SERVER == VRP_YES )
extern  VOID FTPS_RegCmd( VOID );
extern  ULONG FTPS_Init();
#endif

#if( VRP_MODULE_FTP_CLIENT == VRP_YES )
extern  VOID FTPC_RegCmd( VOID );
#endif

#if( VRP_MODULE_TFTP_CLIENT == VRP_YES )
extern  VOID TFTP_RegCmd(VOID);
#endif

#if( VRP_MODULE_XM == VRP_YES )
extern  VOID XM_InitCommandLine( VOID );
extern   ULONG XM_Init();

#endif

/* added by guoxiaojun for the "guodiao" version of VRP3.0 */
#if (VRP_PRODUCT_8040 == VRP_YES)
extern VOID M8040_MIB_Init();
#endif

#if( VRP_MODULE_RTPRO_RM == VRP_YES )
extern  VOID    RM_RoutingMain( ULONG, ULONG, ULONG, ULONG );
#if (VRP_VERSION_5 == VRP_YES)
extern ULONG RM_CmdInstall(VOID);
#else
extern  VOID    Rm_RegCmd( VOID );
#endif
#endif

#if( VRP_MODULE_LINK_IPX == VRP_YES )
extern  VOID    IPXRM_RoutingMain( ULONG, ULONG, ULONG, ULONG );
extern  VOID    IPXRM_RegAllCmd( VOID );
#endif
/*end of addition by liuxueqin on 2003/04/24*/

#if( VRP_MODULE_CFG_PING == VRP_YES )
extern  VOID    PIN_RegCmd( VOID );
#endif

#if( VRP_MODULE_CFG_TRACERT == VRP_YES )
extern VOID TRACERT_RegCmd( VOID );
#endif

#if( VRP_MODULE_SEC_NAT == VRP_YES )
extern VOID Nat_RegCmd( VOID );
#endif

/*add by gwei for netstream project*/
#if( VRP_MODULE_NETSTREAM == VRP_YES )
extern void NS_Init(void);
extern void NS_CFG_RegAllCmd();
#endif
/*end by gwei for netstream project*/

#if( VRP_MODULE_SEC_ZONE == VRP_YES )
extern VOID Zone_RegCmd( VOID );
#endif

#if (VRP_MODULE_IP_USERLOG == VRP_YES)
extern VOID USERLOG_Init(VOID);
extern VOID USERLOG_CFG_RegAllCmd(VOID);
#endif

#if( VRP_MODULE_IP_BASE == VRP_YES )
extern  VOID    FIBTASK_Main( ULONG, ULONG, ULONG, ULONG );
extern  ULONG   IP_AllInit( VOID );
extern  VOID    IP_RegCmd( VOID );
/* BYDD04093 BEGIN:dongweisi22007 20040303 */
#if ( VRP_DISTRIBUTED == VRP_YES || \
      (VRP_PRODUCT_8060 == VRP_YES && R8060_NP == VRP_YES) )
/* BYDD04093 END */
extern   VOID	FIB_RegCmd( VOID );
#endif
#endif

#if( VRP_MODULE_IPTN_BASE == VRP_YES )
extern VOID IPTN_TaskEntry();
extern VOID COPSclient_TaskEntry();

#endif

#if( VRP_MODULE_IP_VRRP == VRP_YES )
#if (VRP_VERSION_5 == VRP_YES)
extern  VOID    VRRP_Init( VOID );
#else
extern  ULONG   VRRP_Init( VOID );
#endif
extern  VOID    VRRP_RegCmd( VOID );
#endif


/* Begin by tianli29125 2001-12-10 for merging WCCP module */
#if (VRP_MODULE_WCCP2 == VRP_YES )
#if (VRP_IO_BOARD == VRP_NO)
extern LONG Wccp2ApplStart();
#else /* Modify by tianli for WCCP transplant */
extern LONG Wccp2IPCRPCInit();
#endif
#endif /* (VRP_MODULE_WCCP2 == VRP_YES ) */
/* Finish by tianli29125 2001-12-10 for merging WCCP module */

#if ( VRP_IO_BOARD == VRP_NO )
#if ( VRP_MODULE_IP_DHCP == VRP_YES )

#if ( VRP_MODULE_IP_DHCP_RELAY == VRP_YES )
#if ( VRP_MODULE_IP_HELPER_ADDRESS == VRP_YES )
    extern  VOID    HELPER_RegCmd(VOID);
    extern  VOID    DHCPR_RegCmd(VOID);
#endif
#endif

#if ( VRP_MODULE_IP_DHCP_SERVER == VRP_YES )
    extern  VOID    DHCPS_RegCmd(VOID);
#endif

extern  ULONG   DHCP_Init(VOID);

#endif
#endif

#if( VRP_MODULE_LINK_ETHERNET == VRP_YES )
extern  VOID    ETH_RegCmd( VOID );
#endif

#if( VRP_MODULE_CFG_VTY == VRP_YES )
extern  VOID    VTY_TelnetServer( ULONG, ULONG, ULONG, ULONG );
extern  VOID    VTY_RegCmd( VOID );
extern  ULONG   VTY_RegToIC( VOID );
#endif

#if( VRP_MODULE_VOS_CMDLINE == VRP_YES )
extern  VOID    VOS_RegCmd( VOID );
#endif

#if( VRP_MODULE_SEC_IPSEC == VRP_YES )
extern  VOID    IPSecInit( ULONG, ULONG, ULONG, ULONG );
#endif

#if( VRP_MODULE_SEC_IKE == VRP_YES )
extern  VOID    isakmp_task_main( ULONG, ULONG, ULONG, ULONG );
#endif

#if( VRP_MODULE_UTIL_RSA == VRP_YES )
extern  VOID    RSA_TaskMain( ULONG, ULONG, ULONG, ULONG );
#endif

#if( VRP_MODULE_SEC_L2TP == VRP_YES )
extern  VOID    L2TP_Init( ULONG, ULONG, ULONG, ULONG );
extern  VOID    L2TP_MsgRecv( ULONG, ULONG, ULONG, ULONG );
#endif

#if( VRP_MODULE_SNMP == VRP_YES )
extern  VOID    SNMP_Agent( ULONG, ULONG, ULONG, ULONG );
extern  VOID    SNMP_Trap( ULONG, ULONG, ULONG, ULONG );
#endif

#if( VRP_MODULE_CFG_CLI_FTP_SERVER == VRP_YES )
extern  VOID FTP_ServerRun( VOID );
#endif

#if( VRP_MODULE_LINK_TEL == VRP_YES )
extern  VOID    Tel_Pots( ULONG, ULONG, ULONG, ULONG );
extern  VOID    PotsCe_Pots( ULONG, ULONG, ULONG, ULONG );
#endif

#if( VRP_MODULE_LINK_CC == VRP_YES )
extern  VOID    CC_Main( ULONG, ULONG, ULONG, ULONG );
extern  VOID    CC_RegModuleCmd( VOID );
#endif

#if( VRP_MODULE_LINK_Q921 == VRP_YES )
extern  VOID    Q921_Main( ULONG, ULONG, ULONG, ULONG );
extern  VOID    Q921_RegCmd( VOID );
#endif

#if( VRP_MODULE_LINK_Q931 )
extern  VOID    Q931_Main( ULONG, ULONG, ULONG, ULONG );
extern  VOID    Q931_RegModuleCmd( VOID );
#endif

#if( VRP_MODULE_VOS_VFS == VRP_YES )
extern   VOID VOS_VFS_Task ( ULONG, ULONG, ULONG, ULONG );
#endif


#if ( VRP_PRODUCT_8060 == VRP_YES )
extern  VOID DIAG_TaskEntry(ULONG , ULONG , ULONG , ULONG );
extern  VOID SRM_MainFunction(ULONG , ULONG , ULONG , ULONG );
#endif
/* end of addition luoli 20021209*/


#if( VRP_MODULE_CFG_CLI_CFGFILE == VRP_YES )
extern  VOID CFM_Main( VOID );
#endif
#if( VRP_MODULE_QUEUE == VRP_YES )
extern  ULONG   Que_Init( VOID );
extern  VOID    Que_Schedule( VOID );
#endif

#if( VRP_MODULE_LINK_ETHERNET == VRP_YES )
extern  VOID    ETHARP_EtherInit( VOID );
#endif

#if( VRP_MODULE_LINK_PPP == VRP_YES )
extern  VOID    PPP_GlobalInit( VOID );
extern  VOID    PPP_RegCmd( VOID );
#if( VRP_MODULE_LINK_PPP_MP == VRP_YES )
extern  VOID    MP_RegCmd( VOID );
#endif
#endif

#if( VRP_MODULE_LINK_PPPOE == VRP_YES )
extern  VOID    PPPOE_GlobalInit( VOID );
extern  VOID    PPPOE_RegCmd( VOID );
#endif

#if( VRP_MODULE_LINK_PPPOE_CLIENT == VRP_YES )
extern  VOID    PPPOE_Client_GlobalInit(VOID);
extern  VOID    PPPOE_Client_RegCmd();
#endif

#if ( VRP_MODULE_IP_URPF == VRP_YES )
/*#if (VRP_MAIN_BOARD == VRP_YES)*/
extern VOID URPF_RegCmd(VOID );
/*#endif*/
extern VOID URPF_Init(VOID );
#endif
/*Endof by wangkaixiong for URPF*/

#if( VRP_MODULE_LINK_SLIP == VRP_YES )
extern  VOID    SLIP_GlobalInit( VOID );
extern  VOID    SLIP_RegCmd( VOID );
#endif

#if( VRP_MODULE_LINK_LAPB == VRP_YES )
extern  VOID    LAPB_RegModuleCmd( VOID );
extern  VOID    LAPB_GlobalInit( VOID );
extern  VOID    LAPB_ConfigProc( VOID * );
/* extern  VOID LAPB_Intr( VOID ); */
#endif

#if( VRP_MODULE_LINK_X25 == VRP_YES )
/*extern  VOID X25_Intr( VOID );*/
extern VOID X25_GlobalInit( VOID );
extern VOID X25_RegModuleAndCmd( VOID );
#endif

#if( VRP_MODULE_LINK_FR == VRP_YES )
extern	VOID	FR_GlobalInit( VOID );
extern	VOID	FR_RegCmd( VOID );
#endif

#if ( VRP_MODULE_LINK_FRTS== VRP_YES )
extern VOID FRTS_INIT ( VOID );

extern ULONG FRQOS_RegCmd(VOID);

#endif


#if( VRP_MODULE_LINK_ATM == VRP_YES )
extern	VOID	ATM_INIT_GlobalInit( VOID );
extern	VOID	ATM_CFG_RegCmd( VOID );
#endif

#if (VRP_MODULE_QOS == VRP_YES && VRP_MODULE_LINK_ATM == VRP_YES) 
#if (VRP_MODULE_ATMQOS == VRP_YES ) 
extern ULONG ATMQOS_RegCmd(VOID);
#endif  /*VRP_MODULE_ATMQOS END*/
#endif  /*VRP_MODULE_QOS&&VRP_MODULE_LINK_ATM END*/


#if( VRP_MODULE_LINK_CHDLC == VRP_YES )
extern	VOID	CHDLC_GlobalInit(	VOID	);
extern	VOID	CHDLC_RegModuleCmd(	VOID	);
#endif

#if( VRP_MODULE_LINK_IPX == VRP_YES )

extern ULONG IPXCORE_AllInit(VOID);
#endif

#if( VRP_MODULE_CFG_MODEM == VRP_YES )
extern VOID MDM_Task(VOID);
extern VOID MDM_RegCmd(VOID);
extern ULONG MDM_RegToIC( VOID );
#if( VRP_MODULE_CFG_CHATSCRIPT == VRP_YES )
extern ULONG CHAT_RegToIC(VOID);
#endif

#if( VRP_MODULE_CFG_EXEC == VRP_YES )
    #if( VRP_MODULE_CFG_IC_BASE == VRP_YES )
    	#if( VRP_IO_BOARD == VRP_NO )
   
    	#endif
    #endif
#endif
#endif

#if( VRP_MODULE_NTP == VRP_YES )
extern VOID NTP_MainTask(VOID);
extern VOID NTP_RegCmd(VOID);
extern ULONG NTP_RegToIC( VOID );
#endif

#if( VRP_MODULE_BAS_AAA == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )
extern VOID AAA_TaskEntry(VOID);
#endif
#endif

/* added by zyl27499 */
#if( VRP_MODULE_BAS_RADIUS == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )
extern VOID RD_TaskEntry(VOID);
#endif
#endif

#if( VRP_MODULE_BAS_HWTACACS == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )
extern VOID TAC_TaskEntry(VOID);
#endif
#endif
/*END OF ADDITION*/

#if( VRP_MODULE_BAS_WEB == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )
extern VOID WEB_TaskEntry(VOID);
#endif
#endif

#if( VRP_MODULE_BAS_CM == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )
extern VOID CM_TaskEntry(VOID);
#endif
#endif

#if( VRP_MODULE_SSH == VRP_YES )
extern VOID SSH_RegCmd(VOID);
extern ULONG SSH_RegToIC( VOID );
#endif
#if (VRP_MODULE_FINGER == VRP_YES)
extern VOID FINGER_RegCmd(VOID);
extern ULONG FINGER_RegToIC (VOID);
#endif

#if( VRP_MODULE_LINK_MODEM == VRP_YES )
extern	VOID	MODEM_Intr( VOID );
#endif

#if( VRP_MODULE_LINK_DDR == VRP_YES )
/*extern	VOID	DDR_Intr( VOID );*/
extern ULONG DDR_Init(VOID);
extern VOID DDR_RegCmd(VOID);/*注册命令行*/
#endif

#if( VRP_MODULE_LINK_DDRS == VRP_YES )
    extern VOID DDRS_CFG_RegCmd(VOID);
    extern VOID DDRS_INIT_GlobalInit(VOID);
#endif	

#if( VRP_MODULE_LINK_DLSW == VRP_YES )
extern	ULONG   DLSW_Init( VOID );
extern	VOID	DLSW_RegCmd( VOID );
extern   VOID   DLSW_LLC2_RegCmd(VOID);
#endif

#if( VRP_MODULE_LINK_SDLC == VRP_YES )
extern VOID SDLC_GlobalInit();
extern VOID SDLC_RegCmd (VOID);
#endif

#if(( VRP_MODULE_LINK_IB == VRP_YES )&&(VRP_IO_BOARD == VRP_NO))
/*VRPV3R001M07 backup 2002/11/06*/
	extern	VOID IB_RegCmd( VOID );
	extern VOID IB_Init(VOID);
#endif

#if( VRP_MODULE_SEC_FILTER == VRP_YES )
     extern VOID FLT_Init( VOID );
#endif

#if( VRP_MODULE_SEC_TIMERNG == VRP_YES )
	 extern VOID TRNG_Init(VOID) ;
#endif 

#if( VRP_MODULE_SEC_ACL == VRP_YES )
	 extern VOID ACL_Init(VOID) ;
#endif 

#if( VRP_MODULE_SEC_NAT == VRP_YES )
    extern VOID Nat_Init(VOID);
#endif

#if( VRP_MODULE_TP == VRP_YES ) /* TXD */
    extern VOID TP_Init(VOID);
    extern VOID TP_RegCmd(VOID);
#endif

#if( VRP_MODULE_TP_IDS_INTERACT == VRP_YES ) /* TXD */
   extern VOID TP_IdsInit(VOID);
   extern VOID TP_IdsRegCmd(VOID);
#endif

#if( VRP_MODULE_CFG_LINE_BASE == VRP_YES )
extern	VOID	LINE_RegLineCmd( VOID );
extern	ULONG	LINE_InitGlobal( VOID );
#endif

#if( VRP_MODULE_CFG_HOTKEY == VRP_YES )
extern ULONG HOTKEY_InitGlob(VOID);
extern VOID HOTKEY_RegCmd( VOID );
#endif


#if( VRP_MODULE_CFG_EXEC == VRP_YES )
    #if( VRP_MODULE_CFG_IC_BASE == VRP_YES )
     extern ULONG EXEC_RegLog2IC();  
    #endif
#endif

#if( VRP_MODULE_IFNET == VRP_YES )
extern  ULONG   IF_Init( VOID );
extern  VOID    IF_RegCmd( VOID );
#endif

#if( VRP_MODULE_VOS_VFS == VRP_YES )
/************************************************************************
 * 向命令行模块注册vfs命令:                                            *
 ************************************************************************/
extern VOID	VOS_VFS_Cmd_All(VOID);
#endif

/* added by mayun for tcp backup */
#if (VRP_VERSION_5 == VRP_YES)
#if (VRP_MAIN_BOARD == VRP_YES )
#if (VRP_MODULE_HA_DATA == VRP_YES && VRP_MODULE_HA_SLAVE2MAIN == VRP_YES)
#if( VRP_MODULE_IP_SOCKET == VRP_YES )
    extern VOID Sock_Ha_TaskEntry(ULONG ulArg1, ULONG ulArg2, ULONG ulArg3, ULONG ulArg4);
#endif
#endif
#endif
#endif

#if ( VRP_MODULE_HA_SLAVE2MAIN == VRP_YES && VRP_MAIN_BOARD == VRP_YES )
extern VOID HA_RoutineTask(ULONG ulArg1, ULONG ulArg2, ULONG ulArg3, ULONG ulArg4);
extern VOID HA_Cli_RegCmd(VOID);
#endif

#if ( VRP_MODULE_HRP == VRP_YES )
extern VOID HRP_RoutineTask(ULONG ulArg1, ULONG ulArg2, ULONG ulArg3, ULONG ulArg4);
extern VOID HRP_Cli_RegCmd(VOID);
#endif

#if(VRP_MODULE_IP_POLICY == VRP_YES)  
extern VOID PR_Init();
#endif

#if( VRP_MODULE_SEC_GRE == VRP_YES )
extern VOID Tunnel_Init(VOID);
extern VOID Tunn_RegCmd(VOID);
#endif
#if( VRP_MODULE_SAN_RTP == VRP_YES)
    extern VOID Srtp_RegCmd(VOID);
#endif

/* zhaoyujin 2003/11/03  */
#if (VRP_HWPING_SNMP == VRP_YES)
    extern VOID HWPing_Init();
    extern VOID HWPing_RegCmd();
#endif/*end of VRP_PRODUCT_ROUTER == VRP_YES*/
#if(R8070_MODULE_SECP == VRP_YES)
extern VOID Secp_Init(VOID);
#endif

#if (VRP_MODULE_LINK_VLAN == VRP_YES)
extern VOID ETHVLAN_RegCmd(VOID);
#endif


#if( VRP_MODULE_LICENSE == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )
#if( VRP_MODULE_VOS_VFS == VRP_YES && VRP_MODULE_VOS_VFS_FLS == VRP_YES )  
extern VOID LCNS_RegCmd();
#endif
#endif
#endif

#if(VRP_IO_BOARD == VRP_YES || VRP_CENTERALIZATION == VRP_YES)
/*#if (VRP_IO_BOARD == VRP_YES)*/
#endif
#if(VRP_IO_BOARD == VRP_YES )
    #if (VRP_MODULE_LINK_VLAN == VRP_YES)
    extern VOID ETHVLAN_Init(VOID);
    #endif
#endif
#if( ( VRP_MODULE_MPLS_LSPM == VRP_YES) && ( ((VRP_DISTRIBUTED == VRP_YES)&&(VRP_MAIN_BOARD == VRP_YES)) || (VRP_CENTERALIZATION == VRP_YES)))
extern VOID LSPM_TaskMain (ULONG ul1,ULONG ul2,ULONG ul3,ULONG ul4);

#endif

#if (VRP_VERSION_5 == VRP_YES)
#else
#if( VRP_MODULE_MPLS_RSVP == VRP_YES )
extern	VOID	RSVP_TaskMain( ULONG, ULONG, ULONG, ULONG );
extern	VOID	RSVP_RegCmd( VOID );
#endif
#endif

#if( VRP_MODULE_LINK_X25_XOT == VRP_YES )  
#if( VRP_IO_BOARD == VRP_NO )
extern	VOID XOT_Tcp_Main( ULONG ulArg1,ULONG ulArg2,ULONG ulArg3,ULONG ulArg4 );
#endif
#endif

/*add by renmin for maintain for ipc*/
#if( VRP_MODULE_VOS_IPC == VRP_YES )
extern VOID  VOS_IPC_Cli_RegCmd();
#endif

#if( VRP_MODULE_VOS_MBUF == VRP_YES && VRP_MODULE_VOS_IPC == VRP_YES )
extern VOID  MBUF_Cli_RegCmd();
#endif

#if(VRP_IO_BOARD == VRP_YES)
#if( VRP_MODULE_VOS_MBUF == VRP_YES && VRP_MODULE_VOS_IPC == VRP_YES )
extern VOID MBUF_TR_STAT_IoInitCmd();
#endif

#if( VRP_MODULE_VOS_IPC == VRP_YES )
extern VOID VOS_IPC_IoInitCmd();
#endif
#endif

#if (VRP_MODULE_CFG_IC_BASE == VRP_YES)
#if( VRP_MODULE_VOS_MBUF == VRP_YES && VRP_MODULE_VOS_IPC == VRP_YES )
extern VOID VOS_MBUF_TR_Reg2IC();
#endif

#if( VRP_MODULE_VOS_IPC == VRP_YES && VRP_PRODUCT_GSR != VRP_YES)
extern VOID VOS_IPC_Reg2IC();
#endif
#endif


#if( VRP_MODULE_MPLS== VRP_YES )
/*extern VOID  MPLS_LSR_InstallCommand(); */
#if( VRP_MODULE_MPLS_LDP== VRP_YES )
#if (VRP_VERSION_5 == VRP_YES)
extern VOID LDP_CMMAllCmdInstall (VOID);
extern VOID LDP_TaskMain (ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);
#else
extern VOID  LDP_InstallShowCommand();
extern VOID ldpMain(ULONG, ULONG, ULONG, ULONG);
#endif
#endif
extern VOID  MPLSFW_TaskMain(ULONG,ULONG,ULONG,ULONG);
#endif

#if( VRP_MODULE_RTPRO_MCAST_TEST == VRP_YES )
extern VOID TEST_PIM_MainTask( ULONG, ULONG, ULONG, ULONG );
extern VOID TEST_PIM_RegCmd( VOID );
#endif

#if( VRP_MODULE_MPLS_LSPAGT== VRP_YES )
extern VOID LSPAGT_TaskMain(ULONG ul1, ULONG ul2, ULONG ul3, ULONG ul4);
#endif

#if (( VRP_MODULE_QOS == VRP_YES ) && (VRP_IO_BOARD == VRP_NO))
extern ULONG QOS_RegCmd(VOID);
#endif

#if ( R8070_MODULE_PLB == VRP_YES )
extern  VOID PLB_Init(VOID);
#endif

#if( VRP_MODULE_CFG_IC_BASE == VRP_YES )
#if (VRP_IO_BOARD == VRP_NO)
extern ULONG CLI_ScheduleReboot_Init (VOID);
#endif
#endif

#if(VRP_MAIN_BOARD == VRP_NO && R8070_MEDIUMMIB == VRP_YES)
extern VOID IFMD_Init(VOID);
#endif

#if ((R8070_ENTITYEXTMIB == VRP_YES) || (R8011_ENTITYMIB == VRP_YES)) /*added by wangyue 2003.11.28 for 环境监控MIB*/
extern VOID ENTITYEXTMIB_Init( VOID );
#endif


#if ( VRP_MODULE_IPHC == VRP_YES )
extern VOID IPHC_Init ( VOID );
#if( VRP_MODULE_CFG_BASE == VRP_YES && VRP_MODULE_CFG_CLI_BASE == VRP_YES && VRP_IO_BOARD == VRP_NO)
extern VOID IPHC_RegCmd ( VOID );
#endif
#endif

#if ( VRP_MODULE_MQC == VRP_YES )
extern VOID MQC_INIT ( VOID );
#if( VRP_MODULE_CFG_BASE == VRP_YES && VRP_MODULE_CFG_CLI_BASE == VRP_YES && VRP_IO_BOARD == VRP_NO)
extern ULONG MQC_RegCmd(VOID);
#endif
#endif

#if ( CQC_8011 == VRP_YES )
extern VOID CQC_Init ( VOID );
#if( VRP_MODULE_CFG_BASE == VRP_YES && VRP_MODULE_CFG_CLI_BASE == VRP_YES && VRP_IO_BOARD == VRP_NO)
extern ULONG CQC_RegCmd(VOID);
#endif
#endif

#if( VRP_MODULE_QOS_TE == VRP_YES )
extern VOID QOS_TE_CFG_RegCmd (VOID);
#endif
#if(VRP_MODULE_SEC_EF == VRP_YES  )
     /* VRPV3R001M06B03D003_BRIDGE_TZB 支持桥模块*/
     extern VOID  EF_RegCmd(VOID);
     extern VOID EF_Init();
#endif

#if( VRP_MODULE_SAN_AM == VRP_YES )
extern VOID AM_TaskMain(ULONG ul1, ULONG ul2, ULONG ul3, ULONG ul4);
#endif

#if( VRP_MODULE_SAN_TRVS == VRP_YES)
extern	VOID	TRVS_Main( ULONG, ULONG, ULONG, ULONG );
extern	VOID	TRVS_RegCmd( VOID );
#endif

#if( VRP_MODULE_TB_BASE == VRP_YES )
     /* VRPV3R001M06B03D003_BRIDGE_TZB 支持过滤以太帧头的ACL*/
    extern VOID TB_RegCmd();
    extern VOID TB_Init();
#endif

#if (VRP_MODULE_PLATFORM_RMON == VRP_YES || VRP_MODULE_RMON == VRP_YES) 
extern	VOID	RMON_Init( VOID );
extern	VOID	RMON_RegCmd( VOID );
#endif

#if( VRP_MODULE_RMON2== VRP_YES )
extern	VOID	RMON2_init(VOID);
extern	VOID	RMON2_RegCmd( VOID );
#endif

#if (VRP_PRODUCT_GSR==VRP_YES)
#if( NE80_MODULE_ADP == VRP_YES)
extern VOID RPS_IOAgentTask(ULONG ulArg0,ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);
#endif

#if (NE80_MODULE_DIAG == VRP_YES )
extern VOID DIAG_Init(ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);
extern VOID DIAG_RegCmds (VOID);
#endif /* (NE80_MODULE_DIAG == VRP_YES )*/

#if (VRP_MODULE_VOS_VFS == VRP_YES )
extern VOID VOS_VFS_Task(ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);
#endif /* (VRP_MODULE_VOS_VFS == VRP_YES )*/

#if( L3_MODULE_RSTP == VRP_YES )
/*  MSTP Task:  */
extern VOID RSTP_MainFunction( ULONG  ulArg0, ULONG  ulArg1, ULONG  ulArg2, ULONG  ulArg3);
#endif

#if (NE80_MODULE_VLAN == VRP_YES)
extern VOID Vlan_RegCmd(VOID);
#endif

#endif

#if(VRP_MODULE_BAS_CM == VRP_YES)
#if(VRP_IO_BOARD == VRP_YES)
extern VOID CM_IO_Init();
#endif
#endif

#if(VRP_MODULE_BAS_ACM == VRP_YES)
extern VOID ACM_Init();
#endif

#if(VRP_MODULE_BAS_LAM == VRP_YES)
#if(VRP_IO_BOARD == VRP_NO)
extern VOID LAM_Init1();
#endif
#endif

#if( VRP_MODULE_LICENSE == VRP_YES )
#if( VRP_IO_BOARD == VRP_NO )    
#if( VRP_MODULE_VOS_VFS == VRP_YES && VRP_MODULE_VOS_VFS_FLS == VRP_YES )  
extern VOID LCNS_Init();
#endif
#endif
#endif

#if( VRP_PRODUCT_GSR == VRP_YES )
#if (NE80_MODULE_GSR_R002_VER==VRP_YES)
extern VOID IF_InitHotPlugRegister();
#endif
#endif

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _ROOT_H_ */

 
/* end of root.h */
