/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_api.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP api
*  Date Created: 2008-12-17
*        Author: wangchengyang
*   Description: ptp随visp发布时对外提供的接口声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-12-17  wangchengyang    Create the first version.
*
*******************************************************************************/

#ifndef _PTP_API_H_
#define _PTP_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 随visp发布时除了ptp_cbb_api.h里提供的接口外还另外定义了用户接口,参考下面的声明 */
#include "ptp/include/ptp_cbb_api.h"

/*PPI 命令枚举定义*/
typedef enum tagPTP_PPI_CMD_E
{
        PTP_PPI_ADD,            /* 下发建立SYNC报文发送链路命令 */
        PTP_PPI_SET,            /* 下发发起delay/pdelay请求修正时间命令 */
        PTP_PPI_UNSET,          /* 下发停止修正时间命令 */
        PTP_PPI_DEL,            /* 下发删除SYNC报文发送链路命令 */
        PTP_PPI_SETUTC,         /* 更新UTC标志位及偏移量*/
        /*Add By t00110672 For BC3D03060,2010-5-5,选源优化补充实现*/
        PTP_PPI_SET_BESTCLASS,
        PTP_PPI_SETIP,          /* 下发IP相关信息*/
        PTP_PPI_SETMAC,         /* 下发MAC相关信息*/
        PTP_PPI_BMC_PARA_CHANGED,/*IPCLK 需求:选源的参数发生变化，
                                   PPI 下发只携带本端、对端地址、对端PortId信息
                                  其他信息需要产品调PTP_GetParentDS来获取*/
        /*Add by heyijun 00218462 for DTS2014091108767 on 2014-9-11 增加timeScale变化后的PPI上报*/
        PTP_PPI_PARA_UPDATE,    /*ANN报文中timescale参数变化后下发更新*/
        PTP_PPI_MAX
} PTP_PPI_CMD_E;

/*PPI 参数结构定义*/
typedef struct tagPTP_PPI_S
{
        /*ST问题，远端时钟ID，我们不知道， 20080717， l00128792*/
        PTP_PORT_ID_S  stDstPortIdentity;        /*源端口标识*/
        /*Add By t00110672 For BC3D02767,2010-3-4,【TD产品需求】【PTP】实现1588无线选源方案优化；*/
        UCHAR  ucBestClass; /*是否为优选源，是否为优选源的字段，
                                    时钟等级是否满足6、7、13、14的时钟源为优选源
                                    BOOL_FALSE:非优选源
                                    BOOL_TRUE:优选源*/
         UCHAR ucPad;
        /*Mod End*/

        /*ST问题: END*/
        CHAR    cLogSyncInterval;                /*Sync 发送间隔*/
        CHAR    cLogMinDelayReqInterval;         /*DelayReq 发送间隔*/
        CHAR    cLogMinPdelayReqInterval;        /*PdelayReq 发送间隔*/
        UCHAR   ucPortState;                     /*端口工作模式(master  slave )*/
        PTP_PORT_ADDR_S stRemoteIP;              /*远端地址*/
        PTP_PORT_ADDR_S stLocalIP;               /*本地址*/
        ULONG ulRemotePort;                      /*远端端口*/
        ULONG ulLocalPort;                       /*本地端口*/
        UCHAR ucTimeSource;                      /* 时钟源类型,详见枚举值定义PTP_TIMESOURCE_E */
        /*Added by raofei for VISPV1R8C03*/
        UCHAR ucPadding;
        BOOL_T bTimeScale;

        /*Add By t00110672/z00146309  10-1-11,支持路由器关于实现最新草案的需求 */
        BOOL_T bTwoStep;/*TRUE:TwoStep;FALSE:OneStep,默认为OneStep;*/
        USHORT  usReserved1;
        ULONG ulSyncDurationField;/*下发Sync报文的发送时长*/
        ULONG ulDelayReqDurationField;/*下发DelayReq报文的发送时长*/
        ULONG ulPDelayReqDurationField;/*下发PDelayReq报文的发送时长*/
        /*Add By t00110672 For BC3D02586,IPCLK 产品实现双IP的需求*/
        PTP_PORT_ADDR_S stRemoteExtIP;              /*远端扩展地址*/
        /*Add By t00110672 For BC3D02987,IEEE1588V2 支持UTC时间实现方案*/
        BOOL_T bOffsetValid;
        SHORT sUtcOffset;
        /*Added by zhangbo146309, 物理端口对应, 2010/4/14 */
        ULONG ulIfIndex;/*下发本地接口索引*/
} PTP_PPI_S;

typedef  ULONG ( *PTP_PPI_HOOK_FUNC ) ( USHORT  usPtpPortNumber, ULONG ulPtpPpiCmd, PTP_PPI_S* pstPtpPpiInfo);

/* PPI统计信息 */
typedef struct tagPTP_PPI_COUNT_S
{
    /* PTP更新通知总次数 */
    ULONG ulPTPUpdateTotal; 
    /* PTP更新通知失败次数 */
    ULONG ulPTPUpdateFailure; 
}PTP_PPI_COUNT_S;


/******************************************************************************
*Func Name   : PTP__RegFuncPpiHook
*Description : PPI 注册函数
*Input       : pfPtpPpiHook   PTP_PPI_HOOK_FUNC 类型的函数指针
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME               DESCRIPTION
*
*******************************************************************************/
extern ULONG  PTP_RegFuncPpiHook(PTP_PPI_HOOK_FUNC pfPtpPpiHook);

/*******************************************************************************
*    Func Name: PTP_ComputePTPPPIUpdateCost
* Date Created: 2008-12-15
*       Author: 
*  Description: 使能计算PTP PPI下发时延开关
*        Input: ULONG ulSetYes:使能开关:1使能,0去使能
*       Output: 无
*       Return: 成功PTP_OK,其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern ULONG PTP_ComputePTPPPIUpdateCost(ULONG ulSetYes);

/*******************************************************************************
*    Func Name: PTP_ShowPTPPPIUpdateCost
* Date Created: 2008-12-15
*       Author: 
*  Description: 显示PTP PPI下发耗时信息
*        Input: 无
*       Output: 无
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern VOID PTP_ShowPTPPPIUpdateCost(VOID);

/******************************************************************************
*Func Name   : PTP_SetPpiDebugSwitch
*Description : 输出ppi调试信息
*Input       : ulDebugFlag:设置PPI调试标记,1-打开,0-关闭
*Output      : 
*Return      : .
*******************************************************************************/
extern ULONG PTP_SetPpiDebugSwitch(ULONG ulDebugFlag);

/******************************************************************************
*Func Name   : PTP_PPI_Count_Get
*Description : 获取PPI下发统计信息
*Input       : 
*Output      : PTP_PPI_COUNT_S *pstCount:下发统计指针
*Return      : 成功返回PTP_OK,失败返回PTP_ERR.
*******************************************************************************/
extern ULONG PTP_PPI_Count_Get(PTP_PPI_COUNT_S *pstCount);

/******************************************************************************
*Func Name   : PTP_PPI_Count_Reset
*Description : 清除PPI下发统计信息
*Input       : 
*Output      : 
*Return      : 成功返回PTP_OK,失败返回PTP_ERR.
*******************************************************************************/
extern ULONG PTP_PPI_Count_Reset(VOID);

/******************************************************************************
*Func Name   : PTP_PPI_ShowCount
*Description : 显示PTP PPI下发统计信息
*Input       : 
*Output      : 
*Return      : 
*******************************************************************************/
extern VOID PTP_PPI_ShowCount(VOID);

/*******************************************************************************
*    Func Name: PTP_GetCPUType
* Date Created: 2008-9-11
*       Author: wangchengyang
*  Description: 获取CPU类型
*        Input: CHAR *pCPUType: 保存输出CPU类型信息
*       Output: 
*       Return: BFD_OK/BFD_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-9-11    Wangchengyang    Creat the first version.
*
*******************************************************************************/
extern ULONG PTP_GetCPUType(CHAR *pCPUType);

/******************************************************************************
*Func Name   : PTP_SetDSCPPriority
*Description : 设置IP报文的优先级
*Input       : UInteger32 ulPriority  IP报文的优先级，范围：0～63
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码，                             
*Caution     : 提供设置IP报文的优先级，提供时钟包在某些网络中的转发速度，
*              server和clent端都要使用，默认设置最高优先级：63
*Calls       : 
*Called by   :  
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-3             wangchengyang  Create
*******************************************************************************/
extern ULONG PTP_SetDSCPPriority(UCHAR ucPriority);

/******************************************************************************
*Func Name   : PTP_GetDSCPPriority
*Description : 查询IP报文的优先级
*Input       : .
*Output      : UInteger32 *pulPriority  IP报文的优先级，范围：0～63.
*Return      : 成功返回PTP_OK，失败返回错误码，                             
*Caution     : 提供查询IP报文的优先级，server和client端都要使用
*Calls       : 
*Called by   :  
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-3             wangchengyang  Create
*******************************************************************************/
extern ULONG PTP_GetDSCPPriority(UCHAR *pucPriority);

/*******************************************************************************
*    Func Name: PTP_SetDSCPPriorityWithVrf
* Date Created: 2012-08-09
*       Author: wuxiaowu217009
*  Description: 设置指定Master的IP报文的优先级
*        Input: UCHAR ucPriority:  IP报文的优先级，范围：0～63.
*               PTP_PORT_ADDR_S *pstPortAddr: Master的地址.
*               pcVrfName: VRF名.
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码.
*      Caution: 提供设置指定Master的IP报文的优先级，只在slave侧的新模式中的单
*               播模式下使用，默认设置最高优先级：63
*        Calls: 
*    Called by: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-09   wuxiaowu217009          Create
*
*******************************************************************************/
extern ULONG PTP_SetDSCPPriorityWithVrf(UCHAR ucPriority, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);

/*******************************************************************************
*    Func Name: PTP_GetDSCPPriorityWithVrf
* Date Created: 2012-08-09
*       Author: wuxiaowu217009
*  Description: 查询指定Master的IP报文的优先级
*        Input: PTP_PORT_ADDR_S *pstPortAddr: Master的地址.
*               pcVrfName: VRF名.
*       Output: UCHAR *pucPriority: 指定Master的IP报文的优先级.
*       Return: 成功返回PTP_OK，失败返回错误码.
*      Caution: 提供查询指定Master的IP报文的优先级，只在slave侧的新模式中的单
*               播模式下使用，默认设置最高优先级：63
*        Calls: 
*    Called by: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-09   wuxiaowu217009          Create
*
*******************************************************************************/
extern ULONG PTP_GetDSCPPriorityWithVrf(PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName, UCHAR *pucPriority);

/******************************************************************************
*Func Name   : PTP_Shell_Init
*Description : PTP Shell 初始化
*Input       : ULONG ulFlag:是否需要创建event消息socket标记,0-不需要;非0-需要
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码                             
*Caution     : 
*Calls       : 
*Called by   :  
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-3             wangchengyang  Create
*  2008-8-27            wangchengyang  增加是否需要创建event消息socket的入参
*******************************************************************************/
extern ULONG PTP_Shell_Init(ULONG ulFlag);

/******************************************************************************
*Func Name   : PTP_Shell_UnInit
*Description : PTP Shell 去初始化
*Input       : NA，
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码                             
*Caution     : 
*Calls       : 
*Called by   :  
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-3             wangchengyang  Create
*******************************************************************************/
extern ULONG PTP_Shell_UnInit(VOID);

/******************************************************************************
*Func Name   : PTP_Shell_Profile
*Description : 模版设置函数
*Input       :  1. usPortNumber    端口号
                    2. ulProfileType   模版类型
                    3. ulFsmMode    状态机模式
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME               DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_Shell_Profile(USHORT usPortNumber,ULONG ulProfileType,ULONG ulFsmMode);


/*Added by limin00188004, PTP6_Shell_Init 和 PTP6_Shell_UnInit 的声明需要放到ptp_api.h中，方便产品调用, 2011/11/16   问题单号:DTS2011111600282 */
/******************************************************************************
*Func Name   : PTP6_Shell_Init
*Description : PTP6 Shell 初始化
*Input       : ULONG ulFlag:是否需要创建event消息socket标记,0-不需要;非0-需要
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码                             
*Caution     : 
*Calls       : 
*Called by   :  
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME                        DESCRIPTION
*  2010-09-21   raofei62469&zhangbo146309             Create
*******************************************************************************/
extern ULONG PTP6_Shell_Init (ULONG ulFlag);

/******************************************************************************
*Func Name   : PTP6_Shell_UnInit
*Description : PTP6 Shell 去初始化
*Input       : VOID
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码                             
*Caution     : 
*Calls       : 
*Called by   :  
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME                        DESCRIPTION
*  2010-09-21   raofei62469&zhangbo146309             Create
*******************************************************************************/
extern ULONG PTP6_Shell_UnInit(VOID);

/* End of Added by limin00188004, 2011/11/16   问题单号:DTS2011111600282 */


extern ULONG PTP_GetVrfIndexByName(CHAR *pcVrfName, ULONG *pulVrfIndex);


extern ULONG PTP_GetVrfNameByIndex(CHAR *pcVrfName, ULONG ulVrfIndex);
/******************************************************************************
*Func Name   : PTP6_SetDSCPPriority
*Description : 设置IP报文的优先级
*Input       : UCHAR ucPriority  IP报文的优先级，范围：0～63
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码，                             
*Caution     : 提供设置IP报文的优先级，提供时钟包在某些网络中的转发速度，
*              server和clent端都要使用，默认设置最高优先级：63
*Calls       : 
*Called by   :  
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME                        DESCRIPTION
*  2010-09-21   raofei62469&zhangbo146309             Create
*******************************************************************************/
extern ULONG PTP6_SetDSCPPriority(UCHAR ucPriority);
#ifdef __cplusplus 
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTP_API_H_    */ 


