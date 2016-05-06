/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ha.H
*
*  Project Code: VISPV100R006
*   Module Name: HA
*  Date Created: 2006-12-04
*        Author: xiehuaguo
*   Description: VISP HA 总体调度处理头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-12-04  xiehuaguo        Create
*
*******************************************************************************/

#ifndef _TCPIP_HA_H_
#define _TCPIP_HA_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/public/dopra_cbb/include/utldll.h"
#include "tcpip/public/tcpip_pub_api.h"
#include "tcpip/public/tcpip_pub.h"

/* 查看当前是否正在进行手动倒换或平滑操作 */
#define HA_IS_SMOOTH_OR_MANUAL   ((1 == g_ulHAManualOrSmooth))

/* HA 写任务事件宏定义 */
#define HA_SchedHATask(ulEvent) \
{ \
    (VOID)VOS_Ev_Write( g_ulHATaskID, ulEvent ); \
}

/* HA 写消息队列宏定义*/
#define HA_WriteHAQueue(ulQueueId,ulMsg,ulRet) \
{ \
    ulRet = VOS_Que_Write (ulQueueId, ulMsg, VOS_NO_WAIT | VOS_NORMAL, 0);\
}

/* HA 事件位定义 */
#define HA_EVENT_MANUALSW     0X00000001      /* 手动倒换事件 */
#define HA_EVENT_SMOOTH       0X00000002      /* 平滑处理事件 */
#define HA_EVENT_BAKRCV       0X00000004      /* 备份消息输入事件(包括传输层) */
#define HA_EVENT_BAKSND       0X00000008      /* 备份消息发送事件 (除传输层) */
#define HA_EVENT_SKTSND       0X00000010      /* 传输层备份消息发送事件  */
#define HA_EVENT_TIMER        VRP_EVENT_TIMERREQ /* HA保活定时器事件 */

/* VISP 各模块批备份是否完成标记定义 */
#define HA_ALL_BATCH_INIT     0X10000000      /* 批备份初始标记    */
#define HA_IFNET_BATCH_OVER   0X00000001      /* IFNET已完成批备份 */
#define HA_IP_BATCH_OVER      0X00000002      /* IP已完成批备份    */
#define HA_ETH_BATCH_OVER     0X00000004      /* ETH已完成批备份   */
#define HA_TRUNK_BATCH_OVER   0X00000008      /* TRUNK已完成批备份 */
#define HA_PPP_BATCH_OVER     0X00000010      /* PPP已完成批备份   */
#define HA_PPPOE_BATCH_OVER   0X00000020      /* PPPOE已完成批备份 */
#define HA_DHCP4C_BATCH_OVER  0X00000040      /* DHCP4C已完成批备份*/
#define HA_SFIB_BATCH_OVER    0X00000080      /* SFIB已完成批备份  */
#define HA_SOCKET_BATCH_OVER  0X00000100      /* SOCKET已完成批备份*/
#define HA_BFD_BATCH_OVER     0X00000200      /* BFD已完成批备份   */
#define HA_DHCP4R_BATCH_OVER  0X00000400      /* DHCP4R已完成批备份*/
#define HA_POES_BATCH_OVER    0X00000800      /* POES已完成批备份  */
#define HA_PUBLIC_BATCH_OVER  0X00001000      /* PUBLIC 公共部分完成批备份 */
#define HA_OAM3AH_BATCH_OVER  0X00002000      /* OAM3AH模块完成批备份 */
#define HA_OAM1AG_BATCH_OVER  0X00004000      /* 1AG部分完成批备份    */
#define HA_IGMP_BATCH_OVER    0x00008000      /* igmp已完成批备份  */
#define HA_VRF_BATCH_OVER     0x00010000      /* VRF已完成批备份  */
#define HA_TWAMP_BATCH_OVER     0x00020000      /* TWAMP has completed the Batch backUP */
#define HA_ALL_BATCH_OVER     0X20000000      /* 整个已完成批备份  */

/* IPV4队列中的批量备份消息处理完毕 */
#define HA_IPV4_BATCH_MSG_OVER   0X00000001

/* SOCKET队列中的批量备份消息处理完毕*/
#define HA_SOCKET_BATCH_MSG_OVER 0X00000002

/* IPV4队列、SOCKET队列中的批量备份消息处理完毕 */
#define HA_BATCH_MSG_OVER  ( HA_IPV4_BATCH_MSG_OVER|HA_SOCKET_BATCH_MSG_OVER )

#define HA_BAK_MAXMSG_LEN           2048        /* HA备份消息最大长度 */
#define HA_BAK_SCHQUE_NUM           0x00000100L /* HA任务批备份调度报文个数 */
#define HA_BAK_SCHQUE_MULTIPKT_NUM  8           /* HA任务批备份，调度复合包的个数 */
#define HA_BAK_DELAY_TIME           1           /* HA批备份延时处理时间 */

#define HA_DEBUG_SEND   0   /* HA报文发送 */
#define HA_DEBUG_RECV   1   /* HA报文接收 */

/* Added by z43740 for A82D17885:判断报文是否失序
   因为报文序号是会翻转的，可以理解为有向变量，a和b的距离在半环之内则说明当前报文序号较小
   具体可以参考mp模块的CircularSpaceCompare函数注释
*/
#define HA_SEQUENCE_DISORDER(a, b) \
   ((((a<b) && ((b-a) < (ULONG)0x80000000)) || ((a>b) && ((a-b) > (ULONG)0x80000000))) ? 1:0)

/*  HA模块号定义，用于标识HA备份消息所属模块 */
typedef enum enumHAMID
{
    HA_MID_MIN,
    HA_MID_IFNET = 1,   /* 1 */
    HA_MID_IP,          /* 2 */
    HA_MID_ETHARP,      /* 3 */
    HA_MID_TRUNK,       /* 4 */
    HA_MID_PPP,         /* 5 */
    HA_MID_POES,        /* 6 */
    HA_MID_PPPOE,       /* 7 */
    HA_MID_DHCP4C,      /* 8 */
    HA_MID_DHCP4R,      /* 9 */
    HA_MID_SFIB,        /* 10*/
    HA_MID_SOCKET,      /* 11*/
    HA_MID_BFD,         /* 12*/
    HA_MID_PUBLIC,      /* 13*/
    HA_MID_TCP,         /* 14*/
    HA_MID_EOAM3AH,     /* 15*/
    HA_MID_OAM1AG,      /* 16*/
    HA_MID_IGMP,        /* 17*/
    HA_MID_VRF,         /* 18*/
    HA_MID_HADETECT = 0x7e,    /* 探测报文使用的模块ID */
    HA_MID_TWAMP = 0x7f,    /* 探测报文使用的模块ID */
    HA_MID_MAX, /* VISP内部模块号上限，超过此值则为外部注册的模块号 */

    HA_MID_SLAVE_BOARD_ID = 255,    /* 主备板间发送信息的模块号 */
}HAMID_E;

/* 定义外层通知VISP的HA事件类型 */
typedef enum tagTCPIP_HA_EVENT
{
    HA_EVENT_NOTIFY_SWITCH,         /* 0 通知主板进行主备倒换 */
    HA_EVENT_NOTIFY_SMOOTH,         /* 1 通知备板进行平滑处理 */
    HA_EVENT_NOTIFY_S_CLR,          /* 2 由主板发送备份包通知备板清除备板上的所有VISP数据 */
    HA_EVENT_NOTIFY_MAX,            /* 消息类型的最大值，无意义 */
}TCPIP_HA_EVENT_E;

/* HA 消息首部定义 */
typedef struct tagHAMsgHeader
{
    /* HA备份消息编号, 如果有多个消息合成一个消息包，则只有最外面层才消息才存在编号 */
    ULONG         ulSeq ;

    /* HA版本号, 外部模块的HA版本号和VISP模块的版本号不相同 */
    ULONG         ulVer;

    /* 模块编号, VISP HA采用统一的消息号, 各备份模块可以增加自已的子模块编号 */
    UCHAR         ucModID;

    /* 操作命令字, 具体含义由各模块解释 */
    UCHAR         ucOperation;

    /* 备份消息长度(包括HA消息首部) */
    USHORT        usMsgLen;

    /* 校验和, 缺省为0 */
    ULONG         ulChksum;
}HAMSGHEADER_S;

/* HA通道质量探测报文数据结构 */
typedef struct tagHA_DETECT_TLV
{
    USHORT usSubMsgType; /* 备份子消息类型 */
    USHORT usSubMsgLen;  /* 备份子消息长度 */
    ULONG  ulLstSeqNum;  /* 上次发送的备份序号*/
}HA_DETECT_TLV_S;

/* BFD HA 回调函数结构定义 */
typedef struct tagHA_BFDCALLBACK
{
    /* BFD批备份处理钩子 */
    ULONG (*pfBFD_BATCH_HOOK_FUNC)(VOID);

    /* BFD平滑处理钩子 */
    ULONG (*pfBFD_SMOOTH_HOOK_FUNC)(VOID);

    /* BFD备份恢复处理钩子 */
    ULONG (*pfBFD_RESOTRE_HOOK_FUNC)(UCHAR *pBuf, ULONG ulMsgLen);

    /* BFD调试开关设置接口 */
    ULONG (*pfBFD_SETDBG_HOOK_FUNC)(ULONG ulDBG);

    /* BFD调试开关获取接口 */
    ULONG (*pfBFD_GETDBG_HOOK_FUNC)(ULONG *pulDBG);

    /* BFD HA报文调试设置开关 */
    ULONG (*pfBFD_GETVERBOSEDBG_HOOK_FUNC)(ULONG *pulDBG);

    /* BFD HA报文调试开关设置函数 */
    ULONG (*pfBFD_SETVERBOSETDBG_HOOK_FUNC)(ULONG pulDBG);

    /* BFD HA报文打印函数 */
    VOID (*pfBFD_HA_DBGOUTPUT_HOOK_FUNC)(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);

    ULONG (*pfBFD_HA_CLEAN_HOOK_FUNC)(VOID);

}HA_BFDCALLBACK_S ;


/* TWAMP HA callback function structure definition */
typedef struct tagHA_TWAMPCALLBACK
{
    /* Twamp Ha Batch backup hook function */
    ULONG (*pfTWAMP_BATCH_HOOK_FUNC)(VOID);

    /* Twamp Ha Smoothing hook function */
    ULONG (*pfTWAMP_SMOOTH_HOOK_FUNC)(VOID);

    /* TWAMP HA Input*/
    ULONG (*pfTWAMP_RESOTRE_HOOK_FUNC)(UCHAR *pBuf, ULONG ulMsgLen);

    /*TWAMP HA Clean Function*/
     ULONG (*pfTWAMP_HA_CLEAN_HOOK_FUNC)(VOID);


}HA_TWAMPCALLBACK_S ;


/*
   32位HA无损升级版本号组织方式, 基于大头序, 左边是高位, 右边是低位

   |---4bit---|---4bit---|--------12bit--------|--- 4bit---|-------8bit------|
      R版本号    C版本号         B版本号           补丁号    备份版本的修订号
*/
typedef struct tagHAVERSION
{
#if (VRP_BIG_ENDIAN == VRP_YES)
    ULONG ulRVersion: 4,    /* R版本号 */
          ulCVersion: 4,    /* C版本号 */
          ulBVersion: 12,   /* B版本号 */
          ulSPVersion:4,    /* SP补丁号 */
          ulHAUpdate: 8;    /* HA修订号 */
#else
    ULONG ulHAUpdate: 8,    /* HA修订号 */
          ulSPVersion:4,    /* SP补丁号 */
          ulBVersion: 12,   /* B版本号 */
          ulCVersion: 4,    /* C版本号 */
          ulRVersion: 4;    /* R版本号 */
#endif
}HAVERSION_S;

/* Begin of HA UPGRADE modification, 2010 December to 2011 January */
/* 定义这个结构，是为了解决VR6C02和VR6C05版本上，HAVERSION_S对于大端字节序宏使用不正确的问题 */
typedef struct tagHAVERSION_LD
{
    ULONG ulHAUpdate: 8,    /* HA修订号 */
          ulSPVersion:4,    /* SP补丁号 */
          ulBVersion: 12,   /* B版本号 */
          ulCVersion: 4,    /* C版本号 */
          ulRVersion: 4;    /* R版本号 */
}HAVERSION_LD_S;
/* End of HA UPGRADE modification, 2010 December to 2011 January */

/*----------------------HA注册新增加的宏--------------------------------*/
/* 批量备板标记,用于批量备份完成标记 */
#define HA_MODULE_CANNOT_BACKUP  0
#define HA_MODULE_CAN_BACKUP     1

/* 备板清除IPV4模块数据的消息 */
#define HA_SLAVE_IP4_CLEAN         1

/* 备板清除socket模块数据的消息 */
#define HA_SLAVE_SOCKET4_CLEAN     2

#define IS_EXTERN_HA_MID(MID) ((MID > HA_EXTERN_MID_MIN) && (MID < HA_EXTERN_MID_MAX))

#define IS_VISP_HA_MID(MID) (((MID > HA_MID_MIN) && (MID < HA_MID_MAX)) || (HA_MID_SLAVE_BOARD_ID == MID))

/* 设置HA保活探测功能使用的探测倍数最大最小范围宏定义 */
#define HA_KEEPALIVETHR_MAX 20
#define HA_KEEPALIVETHR_MIN 1
#define HA_KEEPALIVETHR_DEF 5

/*HA在手动倒换或平滑处理时，禁止用户配置操作,否则返回错误码*/
#define MODULE_CONFIGURE_DISABLE \
(\
    (TCPIP_HA_AMB == TCPIP_HA_GetBoardType()) && HA_IS_SMOOTH_OR_MANUAL && (!g_ulHABeforeSmooth) && g_ulHAInit\
)

/* Begin of HA UPGRADE modification, 2010 December to 2011 January */
#define VER_VISPV1R6C02 0x62
#define VER_VISPV1R6C05 0x65
#define VER_VISPV1R7C01 0x71
#define VER_VISPV1R8C01 0x81
#define VER_VISPV1R8C03 0x83
#define VER_VISPV1R8C05 0x85
#define VER_VISPV1R8C06 0x86
/* End of HA UPGRADE modification, 2010 December to 2011 January */

/* HA 注册节点 */
typedef struct tagHAREGISTERNODE
{
   DLL_NODE_S          stDLLNode;               /* List node,must be in first position in the struct */
   UCHAR               ucModuleId;              /* 注册模块的模块号(HA内部为其分配) */
   UCHAR               szMoudleName[HA_MOUDLE_NAME_LEN]; /* 注册模块的名称 */
   ULONG               ulPriority;              /* 模块优先级 */
   ULONG               ulPriorMoudleBatchOver;  /* 前一模块是否批量备份完成,完成1,未完成0 */
   TCPIP_HA_MODULE_CALLBACK_S stCallBackSet;    /* 注册的回掉函数集合 */
} HAREGISTERNODE_S;


/*支持HA主备倒换平滑操作时延可测试,定义HA平滑时延相关TICK结构*/
typedef struct tagHA_SMOOTH_TICK
{
    TCPIP_CPUTICK_S stStartTick;
    TCPIP_CPUTICK_S stEndTick;
}HA_SMOOTH_TICK_S;

extern ULONG HA_GetVISPCompVtbl(VOID);
extern ULONG TCPIP_HA_MainTaskEntry (ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);
extern ULONG TCPIP_HA_RegisterBFDVtbl (HA_BFDCALLBACK_S * pfBFDCallBack);
extern ULONG TCPIP_HA_RegisterTWAMPVtbl (HA_TWAMPCALLBACK_S * pfTWAMPCallBack);
extern ULONG HA_RestoreByMoudleId(UCHAR * pucBuf,ULONG ulMsglen);
extern VOID  HA_Smooth_InSequence(VOID);
extern LONG  TCPIP_HA_ModuleCmp(VOID * val, DLL_NODE_S * pNode);

/* 获取单板当前主备类型接口 */
extern ULONG TCPIP_HA_GetBoardType(VOID);
/* 备板是否准备就绪查询接口*/
extern ULONG TCPIP_HA_SlaveIsReady(VOID);

/* 主备消息发送接口,函数返回成功时由TCPIP_HA_SendMsg接口内部释放内存，否则由外部释放内存*/
extern ULONG TCPIP_HA_SendMsg(UCHAR *pMsgBuf, ULONG ulMsgLen);
/* HA内存申请函数 */
extern VOID *TCPIP_HA_Malloc(ULONG ulModID, ULONG ulLength);
/* HA内存释放函数 */
extern ULONG TCPIP_HA_Free (VOID *pBuf);

/* 根据接口类型获取底层初始化函数的接口*/
extern ULONG TCPIP_HA_GetPhyInitByType(ULONG ulType, UCHAR * szIfName, UINTPTR *pfPhyInitial);

/* 接口底层状态的查询接口*/
extern ULONG TCPIP_HA_GetIfPhyState (ULONG ulIfIndex);

/* 当前是否可以进行备份的判断接口*/
extern ULONG TCPIP_HA_IsCanSndBakMsg (ULONG ulMid);

/* HA调试相关接口 */
extern VOID  TCPIP_HA_DbgOutPut(UCHAR *pucBuf,ULONG ulMsglen,ULONG ulCmd);

extern ULONG g_ulHAManualOrSmooth ;
extern ULONG g_ulHABeforeSmooth ;
extern ULONG g_ulHARcvSmoothEvent ;
extern ULONG g_ulHAMsgSeq ;
extern ULONG g_ulHAIPv4QueID;
extern ULONG g_ulHASocketQueID;
extern ULONG g_ulHATaskID ;
extern ULONG g_ulHASm  ;
extern HASTAT_S  g_stBakStat;
extern ULONG g_ulHAInit ;
extern ULONG g_ulSRMInit ;
extern ULONG g_ulHABfdExist ;
extern ULONG g_ulHABatchflag  ;
extern ULONG g_ulHABatchMsgOver ;
extern ULONG g_ulHASockRunPri ;
extern ULONG g_ulEnableHAUpdate;
extern ULONG g_ulHAVersion;
extern ULONG g_ulNeedHACksum;
extern ULONG g_ulHaVersion_Old;

extern TCPIP_HA_CALLBACK_S    g_stHACallBack ;
extern HA_BFDCALLBACK_S       g_stBFDHACallBack ;

extern ULONG HA_RestoreByMoudleId(UCHAR * pucBuf, ULONG ulMsglen);
extern ULONG TCPIP_HA_Clean(VOID);

extern HA_GETBOARDTYPE_FUNC     g_pfHAGetBoardType;
extern HA_MALLOC_FUNC           g_pfHAMalloc;
extern HA_FREE_FUNC             g_pfHAFree;
extern HA_GETPHYINITBYTYPE_FUNC g_pfHAGetPhyInitByType;
extern HA_GETIFPHYSTATE_FUNC    g_pfHAGetIfPhyState;
extern HA_SENDMSG_FUNC          g_pfHASendMsg;
extern HA_SLAVEISREADY_FUNC     g_pfHASlaveIsReady;
extern HA_BADVERNOTIFY_FUNC     g_pfHABadVerNotify;

extern VOID   TCPIP_HA_ResolveVersion(const CHAR *szTCPIPVersion, const ULONG ulHAUpdate, ULONG *pulHAVersion);
extern ULONG  TCPIP_HA_GetVersion(UCHAR ucModID, ULONG *pulVersion);
extern ULONG  TCPIP_HA_IsInvalidVersion(UCHAR ucModID, ULONG ulVersion);
extern USHORT TCPIP_HA_GetChecksum(USHORT *pusCalcFrom, LONG lTotalLen);
extern USHORT TCPIP_HA_CalcCksum(USHORT *pusCalcFrom, LONG lTotalLen);
extern ULONG  TCPIP_HA_IsSpecRcVer(UCHAR ucVer);
/* 支持MBSC产品HA增强保活功能增加的函数 */
extern ULONG TCPIP_HA_SendDetectPkt(VOID);
extern VOID TCPIP_HA_DetectTimer(VOID *pPara);
extern ULONG TCPIP_HA_CreateDetectTimer(ULONG ulTime);

/* trunk模块平滑完成标志. 主板初始化为0; 备板初始化为1,在平滑完成后置位0 */
extern ULONG g_ulTrunkBeforeSmooth;

#ifdef  __cplusplus
}
#endif

#endif /* _TCPIP_HA_H_ */

