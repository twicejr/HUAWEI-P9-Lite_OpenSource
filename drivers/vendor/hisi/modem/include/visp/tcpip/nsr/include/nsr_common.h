/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_common.h
*
*  Project Code: Dopra V3R2
*   Module Name: NSR Common模块对外头文件  
*  Date Created: 2013-09-25
*        Author: guojianjun178934
*   Description: NSR公共模块处理头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-09-25   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_COMMON_INCLUDED
#define NSR_COMMON_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*NSR功能模块定义*/
#define NSR_MODULE_TYPE_MIN       0
#define NSR_MODULE_TYPE_COMMON    1
#define NSR_MODULE_TYPE_BFD       2
#define NSR_MODULE_TYPE_TRUNK     3
#define NSR_MODULE_TYPE_OSPF      4
#define NSR_MODULE_TYPE_OTHER     5
#define NSR_MODULE_TYPE_MAX       6

#define NSR_MODULE_NAME_MAX     20

/*NSR公共消息类型*/
#define NSR_COMMON_MSG_BOARD            0x01    /*单板状态消息*/
#define NSR_COMMON_MSG_PHY_IF_READY    0x02    /*物理接口上报结束*/
#define NSR_COMMON_MSG_LOG_IF_READY    0x04    /*逻辑接口NSR平滑结束*/
#define NSR_COMMON_MSG_IF_READY    (NSR_COMMON_MSG_PHY_IF_READY | NSR_COMMON_MSG_LOG_IF_READY)
#define NSR_COMMON_MSG_OSFP_BFD_FINISH 0x08   /*OSPF动态会话恢复结束*/
#define NSR_COMMON_MSG_NSR_DISABLED    0x10   /*NSR功能已经去使能*/
#define NSR_COMMON_MSG_SWITCH_FINISH   0x20   /*NSR倒换结束(备升主完成平滑)*/

/*接口上报状态*/
#define NSR_IF_STATUS_NULL         0x00    /*物理接口Ready*/
#define NSR_IF_STATUS_PHY_READY   0x01    /*物理接口Ready*/
#define NSR_IF_STATUS_LOG_READY   0x02    /*逻辑接口Ready*/

/*NSR使能/去使能状态，适用于NSR公共模块和各特性的NSR功能*/
#define NSR_STATUS_UP           0x01    /*NSR使能并激活*/
#define NSR_STATUS_DOWN         0x02    /*NSR非激活*/
#define NSR_STATUS_GOING_UP    0x03     /*NSR使能中(此状态暂时未使用)*/
#define NSR_STATUS_GOING_DOWN  0x04     /*NSR去使能中*/

/*NSR倒换状态，适用于NSR公共模块和各特性的NSR功能*/
#define NSR_SWITCH_STATUS_ACTIVE   0x01   /*NSR处于倒换过程中*/
#define NSR_SWITCH_STATUS_INACTIVE 0x02   /*NSR处于非倒换过程*/

/*各模块NSR消息处理函数钩子类型*/
typedef VOID (*NSR_SUB_MODULE_MSG_PROCESS_HOOK_FUNC)(ULONG, UCHAR *, ULONG);
/*OSPF模块处理透传NSR消息钩子函数类型*/
typedef VOID (*NSR_MSG_PROCESS_HOOK_FUNC)(ULONG, UCHAR *, ULONG);
/*各模块NSR使能/去使能处理钩子类型*/
typedef ULONG (*NSR_SUB_MODULE_SET_NSR_CAPABILITY)(UCHAR);

/* Modified by w00207740, DTS2014021106399,为数据对齐修改pad保留字段, 2014/2/14 */
/*NSR COMMON的本地数据*/
typedef struct nsr_common_local
{
    BOOL_T bNSRInit;              /*NSR是否初始化 0-未初始化  1-已初始化*/
    UCHAR ucNSRCapability;       /*NSR是否使能   1-使能  2-不使能, 默认为2*/
    UCHAR ucNextNSRCapability;  /*延迟生效的NSR使能状态，默认为0*/
    UCHAR ucNSRRole;              /*NSR角色,默认为备*/
    UCHAR ucChannelStatus;       /*通道状态*/
    UCHAR ucSlaveBoardStatus;    /*备板状态*/
    UCHAR ucIFReadyFlag;          /*接口上报结束标识*/
    UCHAR ucIFReadyStatus;       /*接口上报状态*/
    UCHAR ucNSRStatus;           /*NSR状态*/
    UCHAR ucNSRSwitchStatus;    /*NSR倒换状态*/
    UCHAR Pad[1];
    ULONG ulNSRFlag;             /*NSR标记，按位使用*/
    DLL_S lsSubModuleList;
}NSR_COMMON_LOCAL;

/* Modified by w00207740, DTS2014021106399,为字节对齐，调整字段位置与pad保留字段大小, 2014/2/14 */
typedef struct nsr_sub_module_regist
{
    ULONG ulModID;
    ULONG ulSubscribeMsg;
    UCHAR ucNSRCapability;
    UCHAR szModuleName[NSR_MODULE_NAME_MAX+1];
    UCHAR pad[2];
    NSR_SUB_MODULE_SET_NSR_CAPABILITY pfSetNSRCapabilityHook;
    NSR_SUB_MODULE_MSG_PROCESS_HOOK_FUNC pfMsgProcessHook;
}NSR_SUB_MODULE_RESIST;

/* Modified by w00207740, DTS2014021106399,为字节对齐，删除pad保留字段, 2014/2/14 */
typedef struct nsr_sub_module_node
{
    DLL_NODE_S stNode;
    ULONG ulModID;                /*模块ID*/
    ULONG ulSubscribeMsg;        /*订阅的公共消息类型*/
    UCHAR szModuleName[NSR_MODULE_NAME_MAX+1];
    UCHAR ucNSRCapability;       /*NSR使能/去使能标识*/
    UCHAR ucNSRStatus;           /*NSR使能/去使能状态*/
    UCHAR ucNSRSwitchStatus;    /*NSR倒换状态*/
    NSR_SUB_MODULE_SET_NSR_CAPABILITY pfSetNSRCapabilityHook;
    NSR_SUB_MODULE_MSG_PROCESS_HOOK_FUNC pfMsgProcessHook;
}NSR_SUB_MODULE_NODE;

typedef struct nsr_common_msg
{
    ULONG ulModID;
    ULONG ulMsgType;
    UCHAR *pMsgInfo;
}NSR_COMMON_MSG;

/*判断是否为主板*/
#define NSR_IS_MASTER_BOARD() (g_stNSRCommonLocal.ucNSRRole == NSR_ROLE_MASTER)

/*NSR是否已初始化*/
#define NSR_IS_INIT()    (g_stNSRCommonLocal.bNSRInit == BOOL_TRUE)
#define NSR_SET_INIT(RESULT)    (g_stNSRCommonLocal.bNSRInit = ((RESULT) == NSR_OK ? BOOL_TRUE : BOOL_FALSE))

/*是否使能NSR*/
#define NSR_IS_ENABLE()    (g_stNSRCommonLocal.ucNSRCapability == NSR_CAPABILITY_ENABLE)

/*判断NSR功能是否激活*/
#define NSR_IS_ACTIVE() (g_stNSRCommonLocal.ucNSRStatus == NSR_STATUS_UP)
/*判断NSR功能是否激活*/
#define NSR_IS_INACTIVE() (g_stNSRCommonLocal.ucNSRStatus == NSR_STATUS_DOWN)

/*NSR判断接口是否上报结束*/
#define NSR_IS_ALL_IF_READY() \
  (g_stNSRCommonLocal.ucIFReadyStatus == g_stNSRCommonLocal.ucIFReadyFlag)

/*判断消息是否发送给主板*/
#define NSR_IS_MASTER_CONTROL_MSG(DIRECT_TYPE) \
  (((DIRECT_TYPE) & NSR_CONTROL_MSG_DEST_MASTER) && NSR_IS_MASTER_BOARD())
  
/*判断消息是否发送给备板*/
#define NSR_IS_SLAVE_CONTROL_MSG(DIRECT_TYPE) \
    (((DIRECT_TYPE) & NSR_CONTROL_MSG_DEST_SLAVE) && !NSR_IS_MASTER_BOARD())

/*判断控制类消息是否有效*/
#define NSR_IS_VALID_CONTROL_MSG(DIRECT_TYPE) \
  (((DIRECT_TYPE) & NSR_CONTROL_MSG_DIRECT_NSR) && \
  (NSR_IS_MASTER_CONTROL_MSG(DIRECT_TYPE) || \
   NSR_IS_SLAVE_CONTROL_MSG(DIRECT_TYPE)))

#define NSR_SET_IF_STATUS(IF_STATUS) \
  (g_stNSRCommonLocal.ucIFReadyStatus |= (IF_STATUS))

extern NSR_COMMON_LOCAL g_stNSRCommonLocal;
extern ULONG g_ulNSRTimerQueID;
extern NSR_MSG_PROCESS_HOOK_FUNC g_pfNSRMsgProcessHookForOSPF;
extern NSR_SEND_BACKUP_MSG_FUNC          g_pfNSRSendBackupMsg;
extern NSR_SEND_CONTROL_MSG_FUNC         g_pfNSRSendControlMsg;
extern NSR_GET_NSR_BASE_INFO_FUNC         g_pfNSRGetNSRBaseInfoHook;
extern ULONG g_ulSemForNSR;

ULONG NSR_Common_InitLocal();
VOID NSR_Common_RouteMessage(ULONG ulMsgType, UCHAR *pMsgInfo, ULONG ulMsgLen);
ULONG NSR_GetPreConfigInfo(ULONG ulKey, ULONG *pulNSRPreCfgInfo);
ULONG NSR_SendControlMsg(NSR_CONTROL_MSG *pstNSRControlMsg);
ULONG NSR_SendBackupMsg(UCHAR *pMsgBuf, ULONG ulMsgLen, BOOL_T bFirstBuf);
ULONG NSR_Common_ReceiveControlMsg(NSR_COMMON_MSG *pstNSRCommonMsg);
ULONG NSR_Common_AddModule(NSR_SUB_MODULE_RESIST *pstSubModuleRegist);
LONG NSR_Common_ModuleCmp(VOID * val, DLL_NODE_S * pNode);
VOID NSR_UpdateIfReadyFlags(NSR_SUB_MODULE_NODE *pstSubModuleNode);
ULONG NSR_GetNSRBaseInfo(NSR_BASE_INFO *pstNSRBaseInfo);
ULONG NSR_Common_GetNSRBaseInfo(UCHAR ucType, UCHAR *pucData);
ULONG NSR_EnableNSR();
ULONG NSR_DisableNSR();
VOID NSR_Common_DealNSRCapabilityMsg(NSR_COMMON_MSG *pstNSRCommonMsg);
VOID NSR_Common_DealNSRSwitchMsg(NSR_COMMON_MSG *pstNSRCommonMsg);






#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
