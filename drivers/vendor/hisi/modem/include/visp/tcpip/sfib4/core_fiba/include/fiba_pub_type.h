/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fiba_pub_type.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-07
*       Author: Zhang Hongyan
*  Description: Fibagent public type define in this file
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-07   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859 
*  2006-05-11   luyao(60000758)         为支持ARM CPU字节对齐特性，修改结构。
*  2006-05-13   l48923                  Delete useless code
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _FIBA_PUB_TYPE_H
#define _FIBA_PUB_TYPE_H

#include "tcpip/sfib4/include/sfib4_api.h"
#include "tcpip/ipv6/sfib6/include/sfib6_api.h"
/*注意:
如果修改错误码，请同步修改sfib_sh_main.c文件中的
CHAR *Inf_IP_FibA_En[]描述信息*/
typedef enum FIB6A_DBG_INFOtag 
{
    INFO_DBG_TIME_OUT =    1,           /*01*/
    INFO_RFSH_TIME_OUT,                 /*02*/
    INFO_AGE_TIME_OUT,                  /*03*/
    INFO_FRSH_WLK_BGN,                  /*04*/
    INFO_IN_FRSH_WLK,                   /*05*/
    INFO_FRSH_WLK_END,                  /*06*/
    INFO_AGE_WLK_BGN,                   /*07*/
    INFO_IN_AGE_WLK,                    /*08*/
    INFO_AGE_WLK_END,                   /*09*/
    INFO_BRD_RFSHD,                     /*10*/
    INFO_AGE_WLK_FNSH,                  /*11*/
    INFO_SND_DBG_ON_MSG,                /*12*/
    INFO_SND_DBG_OFF_MSG,               /*13*/
    INFO_SMOOTH_EV_SENT,                /*14*/
    INFO_HA_BATCH_BACKUP_SENT,          /*15*/
    INFO_HA_SLAVE_PLUGOUT,              /*16*/
    INFO_HA_ACK_DATA,                   /*17*/
    INFO_IPC_SEND_IO_BRD,               /*18*/
    INFO_FIB6TABLE_ABSENT,              /*19*/

    ERR_RT_CMD_BLD,                     /*20*/
    ERR_RT_CMD_EXT,                     /*21*/
    ERR_INVLD_RT_MSG,                   /*22*/
    ERR_RT_MSG_QWRTIE,                  /*23*/

    ERR_RT_EV_SEND,                     /*24*/
    ERR_IO_BRD_NOT_UP,                  /*25*/
    ERR_INVLD_RTCMD_BLK,                /*26*/
    ERR_DNLD_TMR_CRT,                   /*27*/
    ERR_DNLD_TMR_CRT_SH_CALLBK,         /*28*/
    ERR_RFSH_TMR_CRT_SH_CALLBK,         /*29*/
    ERR_AGE_TMR_CRT_SH_CALLBK,          /*30*/
    ERR_IPC_SEND_IO_BRD,                /*31*/
    ERR_RFSH_TMR_CRT_PRD_RFSH,          /*32*/

    ERR_RFSH_WLK_TMR_CRT,               /*33*/
    ERR_RFSH_TMR_CRT,                   /*34*/
    ERR_AGE_TMR_CRT,                    /*35*/
    ERR_RFSH_WLK_TMR_CRT_SH_CALLBK,     /*36*/
    ERR_IPC_SEND_SMOOTH_END,            /*37*/
    ERR_RFSH_WLK_TMR_CRT_NXT_WLK,       /*38*/
    ERR_TMR_AGE_WLK_CRT,                /*39*/
    ERR_TMR_AGE_WLK_CRT_SH_CALLBK,      /*40*/
    ERR_IPC_SEND_SMOOTH_START,          /*41*/
    ERR_SND_DBG_ON_MSG,                 /*42*/
    ERR_SND_DBG_OFF_MSG,                /*43*/
    ERR_DBG_MSG,                        /*44*/
    ERR_SMOOTH_SEND,                    /*45*/
    ERR_IPC_MSG_QUEUE,                  /*46*/
    ERR_ROUTE_EVENT,                    /*47*/
    ERR_SET_AGETIME_CALLBK,             /*48*/
    ERR_TM_AGE_TMR_CRT,                 /*49*/
    ERR_INVLD_IPC_MSG_RCVD,             /*50*/
    ERR_MALLOC_FAIL,                    /*51*/
    ERR_RTMSG_INVALID                   /*52*/
} FIB6A_DBG_INFO_E;

/* One of the data stores maintained by FIB6Agent subsystem. Acts as an unit of external data 
interface to be used by FIB6Agent to receive FIB entries from RM. This is defined by RM */
typedef struct tagRTMSG6
{
    USHORT  usType;             /* RTMSG_DEL, RTMSG_ADD, RTMSG_DELETE_ZONE */   
    USHORT  usZoneID;           /* zone ID */
    ULONG   aulDestination[4];
    ULONG   aulNexthop[4];
    ULONG   aulNexthop_Relay[4];
    ULONG   aulLocalAddress[4];        
    ULONG   ulIfIndex;          /* index of outgoing interface */
    ULONG   ulATIndex;          /* virtual link index */
    ULONG   ulSlot;
    ULONG   ulFlags;            /* RTF_GATEWAY, RTF_HOST, ...*/
    UCHAR   ucDestPrefixLength;
    UCHAR   ucLocalPrefixLength;
    /*USHORT  ucReserved1;*/
    USHORT  usRtPri;            /* route priority */
    ULONG   ulLabel;            /* Inner label */ 
    ULONG   ulToken;            /* >=1 - > indicates MPLS tunnel, 0 - indicates normal forwarding 
                                 V6 stack will decide MPLS forwarding/normal forwarding based on this */
    ULONG   aulOldNexthop[4];   
    ULONG   aulOldNexthop_Relay[4];
    ULONG   ulOldIfIndex;           
    ULONG   ulOldATIndex;   
    ULONG   ulOldLabel;          
    ULONG   ulOldToken;      
    /*Add by h55555 for defect BC3D00951 interface name*/
    UCHAR   ucIfName[MAX_IF_NAME_LENGTH + 1];
    ULONG   ulProto;
} RTMSG6_S;


/* One of the data stores maintained by FIB6Agent subsystem, Acts as an external data interface 
to be used between FIB6Agent and FIB6 Container to send route messages to update IPv6-FIB.
This interface should be defined and owned by one of the sub modules of FIB6Agent Core */
typedef struct tagIP6_FIB_MSGHDR
{
    ULONG   ulMsgType;          /* Indicates ROUTE, IPC_ROUTE, IPC_DEB, IPC_LICENSE */
    UINTPTR ulMsgPointer;       /* Pointer to Route message, or IPC deb or IPC route or IPC License  */  
    ULONG   ulTag1;             /* used to send zone id, to i/o boatrd while getting routes for display */
    ULONG   ulVer;              /* no use */
}IP6_FIB_MSGHDR_S;

/* One of the data stores maintained by FIB6Agent subsystem. Used for building route command
blocks for  downloading route entries to I/O board for refreshing  (adding/deiting routes in 
I/O FIB). FIB6 MsgHandler updates this during processing of RM messages, also FIB6 Synch 
will update this with all route entries during periodic refresh */
typedef struct tagRT6_CMD
{
    ULONG ulVer;
    union
    {            
        RTMSG6_S  stRtcmd_RtMsg;
        RTMSG4_S  stRtcmd4_RtMsg;
    }stRtcmd;
    ULONG       ulRtcmd_Group;
    struct tagRT6_CMD   *pstRtcmd_Next;
} RT6_CMD_S;

/*  One of the data stores maintained by FIB6Agent subsystem, Acts as an internal data interface 
    between FIB6 Kernel and FIB6 Synch.  Used for managing the route entries to be downloaded 
    to I/O board for refreshing (adding/deiting routes in I/O FIB). FIB6 Kernel updates this during
    processing of RM messages, also FIB6 Synch will update this with all route entries during 
    periodic refresh    */
typedef struct tagRT6_CMDQ
{
    ULONG       ulRtq_Len;      /* Current Length of RTMSG queue D13474*/
    RT6_CMD_S  *pstRtq_Head;    /* pointer to first element in the queue */
    RT6_CMD_S  *pstRtq_Tail;    /* Pointer to last element in the queue */     
} RT6_CMDQ_S;

/*  One of the data stores maintained by FIB6Agent subsystem, Acts as an internal data interface
    between FIB6 Synch in main board and MsgHandler submodule in I/O board. 
    This data strcuture Used for building blocks/chunks of routes commands to be sent to IPv6-DFP via 
    IPC channel */
typedef struct tagRT6_CMDBLOCK
{
    ULONG       ulRtblk_Cnt;
    RT6_CMD_S  *astRtblk_RtCmd;
} RT6_CMDBLOCK_S;

/*  One of the data stores maintained by FIB6Container subsystem. It contains route entry
    with various fields as specified below. This structure is used to store external information in
    FIB Table. This can be used in radix node or any other data store based on 
    implementation specifics. (to support multi algorithm). */
typedef struct tagRT6_ENTRY
{
    ULONG  aulRt_Dest[4];  
    ULONG  ulRt_Dest_PrefLen;
    ULONG  aulRt_Nexthop[4];
    ULONG  ulRt_Flags;         /* route flags -RTF_GATEWAY, RTF_HOST */ 
    ULONG  ulRt_IfIndex;       /* index of outgoing interface */
    ULONG  ulRt_ATIndex;       /* index of virtual link between rt_stLclAddr */
    ULONG  ulRt_Slot;          /* slot num of outgoing interface */
    ULONG  ulRt_TimeStamp;          
    ULONG  ulCacheEntryIndex;  /* used to access corr. cache entry, by guru, 11-28-03 */


    ULONG  ulLabel;            /* Inner label */ 
    ULONG  ulToken;            /* >=1 - > indicates MPLS tunnel, 0 - indicates normal forwarding 
                             V6 stack will decide MPLS forwarding/normal forwarding based on this */

    /*Add by h55555 for defect BC3D00951 interface name*/
    UCHAR   ucIfName[MAX_IF_NAME_LENGTH + 1];
    ULONG   ulProto;
    ULONG   ulRtPri;            /* route priority */
    ULONG   ulVrfIndex;
    struct tagRT6_ENTRY*   pstRt_Next;  
    struct tagRT6_ENTRY*   pstRt_Prev;  
    struct tagRT6_ENTRY*   pstRtBal_Next;
    struct tagRT6_ENTRY*   pstRtBal_Prev;
    UCHAR  ucDelFlag;
    UCHAR  ucPad[3];
} RT6_ENTRY_S;

/*  One of the data stores maintained by FIB4Container subsystem. It contains route entry
    with various fields as specified below. This structure is used to store external information in
    FIB Table. This can be used in radix node or any other data store based on 
    implementation specifics. (to support multi algorithm). */
typedef struct tagRT4_ENTRY
{
     ULONG  ulRt_Dest;  
     ULONG  ulRt_Dest_PrefLen;
     ULONG  ulRt_Nexthop;
     ULONG  ulRt_Flags;         /* route flags -RTF_GATEWAY, RTF_HOST */ 
     ULONG  ulRt_IfIndex;       /* index of outgoing interface */
     ULONG  ulRt_ATIndex;       /* index of virtual link between rt_stLclAddr */
     ULONG  ulRt_Slot;          /* slot num of outgoing interface */
     ULONG  ulRt_Use;           /* metrics to consider */
     ULONG  ulRt_State;  
     ULONG  ulRt_Proto;
     ULONG  ulRt_TimeStamp;          
     ULONG  ulCacheEntryIndex;  /* used to access corr. cache entry */
     ULONG  ulRt_Loc;           /* local address */
     ULONG  ulRt_Loc_PrefLen;   /* local address mask lenth */
     /*Add by q62011 for 大规格地址查询速度慢*/
     ULONG  ulRt_Loc_If;
     ULONG  ulRTPri;            /* route priority */
     
     /*Add by h55555 for defect BC3D00951 interface name*/
     UCHAR   ucIfName[MAX_IF_NAME_LENGTH + 1];
     ULONG  ulVrfIndex;
     ULONG ulPmtu;
     struct tagRT4_ENTRY*   pstRt_Next;  
     struct tagRT4_ENTRY*   pstRt_Prev;  
     struct tagRT4_ENTRY*   pstRtBal_Next;
     struct tagRT4_ENTRY*   pstRtBal_Prev;
} RT4_ENTRY_S;


/*  One of the data stores maintained by FIB6Container subsystem. It contains route info
    with various fields as specified above. This structure is used to store external information in 
    FIB Table. This can be used as radix node or any other data store based on
    implementation specifics. (to support multi algorithm). 
    This data structure is also used for maintaining Double-linked list of routes, which 
    is needed by FIB6Agent for getting bulk of FIB Data for refreshing or for performing 
    aging. Also this structure is for storing balanced routes using double link list in external
    node info for radix tree    */

typedef struct tagRT6_NODE
{
    ULONG ulRouteCount;
    /*Added by r62469 for VISPV1R8C03*/
    ULONG ulHighPriRTCount; /* 记录该路由节点下挂接的优先级相同且最高的平衡路由数量 */


    RT6_ENTRY_S *pstCurrRt_entry;
    RT6_ENTRY_S *pstFirstRt_entry;
} RT6_NODE_S;

/*  One of the data stores maintained by FIB4Container subsystem. It contains route info
    with various fields as specified above. This structure is used to store external information in 
    FIB Table. This can be used as radix node or any other data store based on
    implementation specifics. (to support multi algorithm). 
    This data structure is also used for maintaining Double-linked list of routes, which 
    is needed by FIB6Agent for getting bulk of FIB Data for refreshing or for performing 
    aging. Also this structure is for storing balanced routes using double link list in external
    node info for radix tree    */

typedef struct tagRT4_NODE
{
    ULONG   ulRouteCount;
    ULONG   ulHighPriRTCount; /* 记录该路由节点下挂接的优先级相同且最高的平衡路由数量 */
    ULONG   ulHighPriInterFaceCount;/* 记录该路由节点下挂接的接口优先级相同且最高的平衡路由数量*/

    RT4_ENTRY_S *pstCurrRt_entry;
    RT4_ENTRY_S *pstFirstRt_entry;
} RT4_NODE_S;


/*  This is a structure of callback function details. This is used during registering the callback
    functions of shell for writing into Message Queue, Reading from Message Queue by Core, 
    also writing timer  */
typedef struct tagIP6_FIBAgent_SHELL_EV_CALLBACUP_SET
{
    /* pstMsg is written to msg queue */
    ULONG (*pfShellAsynEnQueMsg) ( IP6_FIB_MSGHDR_S *pstMsg );

    /* pstMsg is read from msg queue */
    ULONG (*pfShellAsynDeQueMsg) (IP6_FIB_MSGHDR_S *pstMsg );

    /* Write event  */
    ULONG (*pfShellAsynEvWrite) (ULONG ulEvType);
    
    /* Timer creation for Complete Refreshing */
    ULONG (*pfShellCreateTmrForRefresh) (ULONG ulTmrValue, USHORT usLoopORNoLoop);

    /* Timer creation for Half Refreshing */
    ULONG (*pfShellCreateTmrForRefreshWalk) (ULONG ulTmrValue, USHORT usLoopORNoLoop);

    /* Timer creation for Real time download  */
    ULONG (*pfShellCreateTmrForDownload) (ULONG ulTmrValue, USHORT usLoopORNoLoop);

    /* Timer creation for Complete Aging */
    ULONG (*pfShellCreateTmrForAge) (ULONG ulTmrValue, USHORT usLoopORNoLoop);

    /* Timer creation for Half Aging */
    ULONG (*pfShellCreateTmrForAgeWalk) (ULONG ulTmrValue, USHORT usLoopORNoLoop);

    /* Added by Guru for memory shortage handling 05-05-2004 */
    /* Timer creation for Getting routes from RM and synching it to FIB */
    ULONG (*pfShellCreateTmrForGetRMRoutes) (ULONG ulTmrValue, USHORT usLoopORNoLoop);

    VOID (*pfShellDebugOut) (ULONG ulBoardId, FIB6A_DBG_INFO_E enState, ULONG ulMsgFmt);

    VOID (*pfShellSendInfoToIC) (ULONG ulBoardId, FIB6A_DBG_INFO_E enState, ULONG ulMsgFmt);

}IP6_FIBAgent_SHELL_EV_CALLBACUP_SET_S;

/*  This is a structure of callback function details. This is used during registering the callback 
    function for downloading FIB to FE, by FE */
typedef struct tagFE_DOWNLOAD_FUNC_SET
{
    ULONG (*pfFE_Download_IP6FIB) (RTMSG6_S *pstRTMsg);
} FE_DOWNLOAD_FUNC_SET_S;

/*  For shell to initilize module specific information of core, such as IPC queue ID, for sending and 
    eceiving IPC messages, this info is set in core, when apprpriate function is invoked by FIB6Main 
    (shell part) during initilization in main task entry ..FIBAGENGT支持IPV4和IPV6*/
typedef struct tagIP6_FIBAgent_MOD_INFO
{
    ULONG   ulModID;
    ULONG   ulSubModID;
    ULONG   ulLocalIPC_TID;
    ULONG   ulPeerIPC_TID;
    ULONG   ulTaskId;      /* Task ID of FIB6A module*/ 
    ULONG   ulQId;            /*Message queue ID of FIB6A module*/
    ULONG   ulTmrQId;
} IP6_FIBAgent_MOD_INFO_S;

   /* Added by Guru for Fib6Opt.. 17/03/2004  for Refreshing/download tuning parameters */
typedef struct tagIP6_FIBAgent_REFRESH_PARAMS
{
    ULONG   ulFIBv6IPCDownloadPackets;
    ULONG   ulFIBv6IPCDownloadTimes;
    ULONG   ulFIBv6DownloadFast;        
} IP6_FIBAgent_REFRESH_PARAMS;

typedef struct tagRTM_GET_FIB
{
USHORT  usRefreshState; /*0:RTM_FIBREFRESH_INIT, 
1: RTM_FIBREFRESH_UPDATE , */ 
    USHORT  usZoneID;           /* zone ID */
    ULONG   ulDestination;
    ULONG   ulNexthop;
    ULONG   ulLocalAddress;        
    ULONG   ulIfIndex;          /* index of outgoing interface */
    ULONG   ulATIndex;          /* virtual link index */
    ULONG   ulSlot;
    ULONG   ulFlags;            /* RTF_GATEWAY, RTF_HOST, ...*/
    UCHAR   ucDestPrefixLength;
    UCHAR   ucLocalPrefixLength;
    USHORT  usRTPri;            /* route priority */
    ULONG   ulProto;
    UCHAR   ucIfName[MAX_IF_NAME_LENGTH + 1];
} RTM_GET_FIB_S;


#endif  /* #ifndef _FIB6A_TYPE_H */


#ifdef  __cplusplus
}
#endif

