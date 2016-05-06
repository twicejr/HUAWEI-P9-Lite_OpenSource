/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_api.h
*
*  Project Code: VISPV100R007
*   Module Name: igmp  
*  Date Created: 2008-03-16
*        Author: zengshaoyang62531
*   Description: igmp模块对外头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-16   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_API_H
#define _IGMPV3_API_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define IGMP_TIMER_URI 1    /*定时器类型:主动报告周期*/
typedef enum tagIGMPERRCODE
{
    IGMP_OK = 0,                
    IGMP_ERR_TIMERNAME,          /* 定时器相关参数的类型不对，当前(VR7)只支持主动报告周期([1, 5]) */
    IGMP_ERR_TIMERVALUE,         /* 定时器的超时时间超出配置范围 */
    IGMP_ERR_NULLPOINTER,        /* 指针为空 */
    IGMP_ERR_IFNETTYPE,          /* 错误的接口类型 */
    IGMP_ERR_NOTLOCALIF,         /* 非本板接口 */   
    IGMP_ERR_IFNULL,             /* 接口为空 */
    IGMP_ERR_DEBUGFLAG,          /* flag值错误 */
    IGMP_COMP_NULL,              /* igmp组件虚表为空 */
    IGMP_ERR_HAISSMOOTHING,      /* 正在手动倒换或平滑处理中 */ 
    IGMP_ERR_IPCTLBLK_INVALID,   /* IP控制块无效 */
    IGMP_ERR_NOGROUP,             /* 接口未加入任何多播组 */
    IGMP_ERR_IF_NOT_EXIST,    		/* Interface does not exist */
    IGMP_ERR_OPENWAITLIST_FAIL, 	/* Open IGMP mlticast group table failed*/
    IGMP_ERR_GETWAITLIST_FAIL,		/* Get from IGMP table failed*/
    IGMP_ERR_NO_MG_FOR_IF,			/* No Multicast group for the interface */
    IGMP_ERR_NO_IP_CTRLBLK,			/* IP control block is NULL for interface*/
    IGMP_ERR_WAITLISTEND,			/* Set IGMP mlticast group table pointer failed*/
    IGMP_ERR_WAITLIST_SET_FAILED,	/* Set IGMP mlticast group table pointer failed*/
    IGMP_ERR_WAITLIST_CLOSE_FAILED	/*Open IGMP mlticast group table failed*/
}IGMPERRCODE_E;

typedef struct tagIGMPSTAT
{
    ULONG   ulIgmpv1RecvGenQuery;       /* 接收方向igmpv1通用查询报文统计 */
    ULONG   ulIgmpv1RecvMemRpt;         /* 接收方向igmpv1成员报告报文统计 */
    ULONG   ulIgmpv1RecvErr;            /* 接收方向igmpv1处理失败的报文统计 */
    ULONG   ulIgmpv1SendSuc;            /* 发送方向igmpv1处理成功的报文统计 */ 
    ULONG   ulIgmpv1SendErr;            /* 发送方向igmpv1处理失败的报文统计 */
    ULONG   ulIgmpv2RecvGenQuery;       /* 接收方向igmpv2通用查询报文统计 */
    ULONG   ulIgmpv2RecvSpeGrpQuery;    /* 接收方向igmpv2特定组查询报文统计 */
    ULONG   ulIgmpv2RecvMemRpt;         /* 接收方向igmpv2成员报告报文统计 */
    ULONG   ulIgmpv2RecvErr;            /* 接收方向igmpv2处理失败的报文统计 */
    ULONG   ulIgmpv2SendSuc;            /* 发送方向igmpv2处理成功的报文统计 */ 
    ULONG   ulIgmpv2SendLeaveRpt;       /* 发送方向igmpv2离开组报告报文统计 */
    ULONG   ulIgmpv2SendErr;            /* 发送方向igmpv2处理失败的报文统计 */
    ULONG   ulIgmpv3RecvGenQuery;       /* 接收方向igmpv3通用查询报文统计 */
    ULONG   ulIgmpv3RecvSpeGrpQuery;    /* 接收方向igmpv3特定组查询报文统计 */
    ULONG   ulIgmpv3RecvSpeGrpSrcQuery; /* 接收方向igmpv3特定组源查询报文统计 */
    ULONG   ulIgmpv3RecvErr;            /* 接收方向igmpv3处理失败的报文统计(含igmpv3成员报告) */
    ULONG   ulIgmpv3SendSuc;            /* 发送方向igmpv3处理成功的报文统计 */ 
    ULONG   ulIgmpv3SendErr;            /* 发送方向igmpv3处理失败的报文统计 */    
    ULONG   ulIgmpUnknowErr;            /* 未知错误的IGMP统计信息 */
}IGMPSTAT_S;

typedef struct tagHAIGMPSTAT
{
    ULONG   ulOutPackets;       /* 主板发送成功备份消息包个数 */
    ULONG   ulOutDropPackets;   /* 主板发送失败备份消息包个数 */
    ULONG   ulInPackets;        /* 备板接收并处理成功备份消息包个数 */
    ULONG   ulInDropPackets;    /* 备板接收、处理失败备份消息包个数 */
}HAIGMPSTAT_S;

/*This structure is used in callback function to fill the source address. */
typedef struct tagIGMPGETSRCIP
{
    ULONG ulSrcIp;              /*IGMP packet source address (host order), output parameter*/
}IGMPGETSRCIP_S;


/*Registeres hook function to get the source address for the outgoing IGMP packet
* Input: pstMbuf is input to the product.
* Output: pstData, The callback function has to update the src address */
typedef ULONG (*IGMP_GET_SRC_IP_HOOK)( MBUF_S *pstMbuf,IGMPGETSRCIP_S *pstData);


/*This structure is used in TCPIP_GetMGInfo to get the address for a particular interface.*/
typedef struct tagIGMPMGINFO
{
    ULONG   ulIfIndex;       /* 接口索引*/
    ULONG   ulIpAddr;        /* 组播地址，主机序*/
}IGMPMGINFO_S;


/* This structure is used in TCPIP_OpenMGInfoTable as a filter parameter */
typedef struct tagIGMPMGFILTER
{
    ULONG   ulIfIndex;       /* Interface index */
}IGMPMGFILTER_S;




extern ULONG TCPIP_ClearIgmpStat (ULONG  ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetIgmpDebug
* Description: Get the igmp module debug flag
* Input:
* Output: ULONG * pulDbg: to save the debug flag
* 	ULONG * pulVerboseDbg: used to save the verbose debugging
* Return: IGMP_COMP_NULL: igmp component is empty
* 	IGMP_ERR_NULLPOINTER: null pointer
* 	VOS_OK: success
* Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIgmpDebug (ULONG *pulDbg, ULONG *pulVerboseDbg);
/*******************************************************************************
* Func Name: TCPIP_GetIgmpHADebug
* Description: Get the igmp ha debugging value
* Input:
* Output: ULONG * pulDbg: to save the igmp ha debugging value
* Return: IGMP_COMP_NULL: igmp component is empty
* 	IGMP_ERR_NULLPOINTER: pointer is empty
* 	VOS_OK: success
* Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIgmpHADebug(ULONG *pulDbg);

extern ULONG TCPIP_GetIgmpStat(ULONG  ulIfIndex, IGMPSTAT_S *pstIgmpStat);
/*******************************************************************************
* Func Name: TCPIP_GetIgmpTimer
* Description: Get the timer timeout value
* Input: ULONG ulTimerType: the type of timing values
* Output: ULONG * pulTimerVal: returns the timer value time
* Return: IGMP_ERR_NULLPOINTER: pointer is empty
* 	IGMP_COMP_NULL: components of the virtual table is empty
* 	IGMP_ERR_TIMERNAME: timer type is incorrect
* VOS_OK: success
* Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIgmpTimer(ULONG ulTimerType, ULONG *pulTimerVal);

extern ULONG TCPIP_IGMP_ClearHaStat(VOID);

extern ULONG TCPIP_IGMP_GetHaStat(HAIGMPSTAT_S *pstHaIgmpStat);
/*******************************************************************************
* Func Name: TCPIP_SetIgmpDebug
* Description: set igmp module debug switch value
* Input: ULONG ulFlag: switch,0 --- Close 1 --- Open
* ULONG ulVerboseFlag: verbose debugging,0 --- Close 1 --- Open
* Output:
* Return: IGMP_ERR_DEBUGFLAG: switch value error
* 	IGMP_COMP_NULL: components of the virtual table is empty
* 	VOS_OK: success
* Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIgmpDebug (ULONG ulFlag, ULONG ulVerboseFlag);
/*******************************************************************************
* Func Name: TCPIP_SetIgmpHADebug
* Description: set igmp ha debugging value
* Input: ULONG ulDbg :0 --- close, 1 --- Open
*       Output: 
* Return: IGMP_ERR_DEBUGFLAG: debugging value error
* 	VOS_OK: success
* 	IGMP_COMP_NULL: igmp components of the virtual table is empty
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIgmpHADebug(ULONG ulDbg);
/*******************************************************************************
* Func Name: TCPIP_SetIgmpTimer
* Description: Set the IGMP timer configuration information
* Input: ULONG ulTimerType: timer type
* ULONG ulTimerVal: Timer time
* Output:
* Return: IGMP_ERR_HAISSMOOTHING: manual switching or smoothing processing in
* 	IGMP_ERR_TIMERNAME: timer wrong type
* 	IGMP_ERR_TIMERVALUE: timer timeout time exceeds the configured range
* 	IGMP_COMP_NULL: components of the virtual table is empty
* 	VOS_OK: success
*Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIgmpTimer(ULONG ulTimerType, ULONG ulTimerVal);
/*******************************************************************************
* Func Name: TCPIP_ShowIgmpDebug
* Description: display the igmp module debug switch
*        Input: 
*       Output: 
*       Return: VOID               
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern VOID TCPIP_ShowIgmpDebug (VOID);

extern VOID TCPIP_ShowIgmpStat (CHAR *pszIfName);

extern VOID TCPIP_ShowMGInfoByIfName (CHAR *pszIfName);



/*******************************************************************************
* Func Name: TCPIP_RegIgmpHookToGetSrcIP
* Description: This function is used to register the callback function to get the source 
* address for outgoing IGMP packets.
* Input: IGMP_GET_SRC_IP_HOOK pstHook: Callback function to be registered.
*       Output: 
*       Return: VOS_OK success,Other failure of type IGMPERRCODE_E
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         	           NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07           s72256                   Create
*
*******************************************************************************/
ULONG TCPIP_RegIgmpHookToGetSrcIP (IGMP_GET_SRC_IP_HOOK pstHook);

/*******************************************************************************
* Func Name: TCPIP_OpenMGInfoTable
* Description: Open handle query multicast group filter conditions in the interface
*                   index must be filled. Does not support query system-wide information.
* Input: 		pstFilter：Filter conditions. Currently supports based on interface index filter.
* Output: 	pulHandle：Query handle
*       Return: VOS_OK success,Other failure of type IGMPERRCODE_E
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         	           NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07           s72256                   Create
*
*******************************************************************************/
ULONG TCPIP_OpenMGInfoTable (UINTPTR *pulHandle, IGMPMGFILTER_S *pstFilter);

/*******************************************************************************
* Func Name: TCPIP_GetMGInfo
* Description: This function is used to get the multicast group information.
* Input: 		pulHandle：Query handle
* Output: 	pstMgInfo: Multicast group information
*       Return: VOS_OK success,Other failure of type IGMPERRCODE_E
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         	           NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07           s72256                   Create
*
*******************************************************************************/
ULONG TCPIP_GetMGInfo (UINTPTR ulHandle, IGMPMGINFO_S *pstMgInfo);


/*******************************************************************************
* Func Name: TCPIP_CloseMGInfoTable
* Description: This function is used to close the query handle.
* Input: 		pulHandle：Query handle
* Output: 	
*       Return: VOS_OK success,Other failure of type IGMPERRCODE_E
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         	           NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07           s72256                   Create
*
*******************************************************************************/
ULONG TCPIP_CloseMGInfoTable (UINTPTR ulHandle);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
