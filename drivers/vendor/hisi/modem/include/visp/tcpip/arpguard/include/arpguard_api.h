/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              etharp_api.h
*
*  Project Code: VISPV100R007
*   Module Name: ETHARP
*  Date Created: 2008年1月25日
*        Author: x00100259
*   Description: ETHARP模块提供的对外数据结构定义和用户API声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008年1月25日  x00100259         Create the first version.
*  2008-08-13     f54882            Modify for BC3D00237
*
*******************************************************************************/

#ifndef _ARPGUARD_API_H_
#define _ARPGUARD_API_H_


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifndef MACADDRLEN
#define MACADDRLEN       6       /*physical地址长度*/
#endif

/* ARP防攻击告警门限 */
#define ARPGUARD_ARPCONFLICT_WARNING_THRESHOLD    1024

/* ARP防攻击告警产生 */
#define ARPGUARD_ARPCONFLICT_WARNING_BEGIN  1
/* ARP防攻击告警消除 */
#define ARPGUARD_ARPCONFLICT_WARNING_END  0


typedef struct tagARPGuardArpConflictWarning
{
    ULONG ulWarningType;        /* 告警类型 */
    ULONG ulIfIndex;            /* 接口索引 */    
    ULONG ulNeighbourIPAddr;    /* 邻居IP, 主机序 */ 
    /* Add by zhaoyue00171897, at 2011-10-08. 修改原因: 告警信息增加刷新MAC的次数 */
    ULONG ulAttackCount;        /* 试图刷新MAC的次数 */
    UCHAR ucMac[MACADDRLEN];    /* 记录攻击次数最多潜在攻击者的physical地址,如果一样，就取最后一次出现的攻击者*/
    UCHAR ucRes[2];
}ARPGUARD_ARPCONFLICT_WARNING_S;

/* 黑名单最大个数 */
#define ARP_GUARD_MAXBLACKNUM  10

/* 一个ARP防攻击节点上允许的最大潜在攻击者个数 */
#define ARP_GUARD_ATTACK_NODE_MAX_NUM            3


/*记录所有攻击者(含合法用户)最多个数*/
#define ARP_GUARD_ATK_NODE_MAX_NUM           10 

/*所有攻击者(含合法用户)上报告警用户门限*/
#define ARP_GUARD_ATK_NODE_WARN_LOW_NUM      2 

/* 潜在攻击者信息,用户可不必关注 */
typedef struct tagETHARP_GUARD_ATTACK_INFO
{
    ULONG  ulPktCount;           /* 一定时间内收到该MAC的计数 */
    UCHAR  ucMac[MACADDRLEN];    /* physical地址 */
    UCHAR  ucPadding[2];         /* 填充位 */ 
}ETHARP_GUARD_ATTACK_INFO_S;

/* 返回给用户的黑名单 */
typedef struct tagETHARP_GUARD_BLACKLIST
{
    ULONG ulIpAddr;                                            /* 地址 */
    ULONG ulVrfIndex;                                          /* VRF索引 */
    ULONG ulIfIndex;                                           /* 接口索引 */
    ULONG ulBlackNum;                                          /* 黑名单数目 */
    UCHAR ucBlackMac[ARP_GUARD_MAXBLACKNUM][MACADDRLEN];       /* 黑名单，最多十个,用户应根据ulBlackNum获取相关MAC */
    ULONG ulState;                                             /* 用户可不必关注,该节点ARP状态 */
    UCHAR szCurMac[MACADDRLEN];                                /* 用户可不必关注,当前节点MAC */
    UCHAR szTrustMac[MACADDRLEN];                              /* 用户可不必关注,当前信任MAC */

    ULONG ulAttackCount;                                       /* 用户可不必关注, 攻击次数,试图改变MAC的次数,内部信息测试使用 */
    UCHAR ucAttackWarningFlag;                                 /* 用户可不必关注,ARP攻击告警标志,1表示已经上报告警，0表示当前无告警 */
    UCHAR ucWarningFlag;                                       /* 用户可不必关注,告警标志,1表示已经上报告警，0表示恢复告警 */
    UCHAR ucPadd[2];
    ULONG ulAttackNodeCount;                                   /* 用户可不必关注, 潜在攻击者节点个数,内部信息测试使用 */
    ETHARP_GUARD_ATTACK_INFO_S stAttackNode[ARP_GUARD_ATTACK_NODE_MAX_NUM];/* 用户可不必关注, 潜在攻击者信息,内部信息测试使用 */
}ETHARP_GUARD_BLACKLIST_S;


/*******************************************************************************
*    Func Name: TCPIP_AddARPGuardStaticBlackNode
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 添加静态黑名单,一个地址最多对应ARP_GUARD_ONEIP_BLACKNUM个黑名单
*        Input: ULONG ulIpAddr: 地址
*               ULONG ulVrfIndex: VRF
*               UCHAR *pszMac: physical地址
*       Output:
*       Return: 成功:VOS_OK
*               其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_AddARPGuardStaticBlackNode(ULONG ulIpAddr, ULONG ulVrfIndex, UCHAR *pszMac);

/*******************************************************************************
*    Func Name: TCPIP_DelARPGuardStaticBlackNode
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 删除静态黑名单
*        Input: ULONG ulIpAddr: 地址
*               ULONG ulVrfIndex: VRF索引
*               UCHAR *pszMac: physical地址
*       Output:
*       Return: 成功:VOS_OK
*               其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DelARPGuardStaticBlackNode(ULONG ulIpAddr, ULONG ulVrfIndex, UCHAR *pszMac);


/*******************************************************************************
*    Func Name: TCPIP_OpenARPGuardDynamicBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: Open动态Guard节点waitlist
*        Input: ULONG *pulWaitListHandle: 输出参数,waitlist句柄
*       Output:
*       Return: 成功:VOS_OK
*               其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_OpenARPGuardDynamicBlack(ULONG *pulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_GetARPGuardDynamicBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 获取动态Guard节点
*        Input: ULONG ulWaitListHandle: waitlist句柄
*               ETHARP_GUARD_BLACKLIST_S *pstEntry:输出参数,获取黑名单列表
*       Output:
*       Return: 成功:VOS_OK
*               其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetARPGuardDynamicBlack(ULONG ulWaitListHandle, ETHARP_GUARD_BLACKLIST_S *pstEntry);


/*******************************************************************************
*    Func Name: TCPIP_CloseARPGuardBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 关闭获取黑名单表项waitlist,该函数可以关闭静态的也可以关闭动态的
*        Input: ULONG ulWaitListHandle: 句柄
*       Output:
*       Return: 成功:VOS_OK
*               其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_CloseARPGuardBlack(ULONG ulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_OpenARPGuardStaticBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 打开静态黑名单waitlist
*        Input: ULONG *pulWaitListHandle: waitlist句柄
*       Output:
*       Return: 成功:VOS_OK
*               其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_OpenARPGuardStaticBlack(ULONG *pulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_GetARPGuardStaticBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 获取waitlist下一个guard节点的所有黑名单
*        Input: ULONG ulWaitListHandle: waitlist句柄
*               ETHARP_GUARD_BLACKLIST_S *pstEntry: 输出参数,黑名单列表
*       Output:
*       Return: 成功:VOS_OK
                获取到尾部:ETHARP_GUARD_GET_BLACKNUMM_FINISH
*               其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetARPGuardStaticBlack(ULONG ulWaitListHandle, ETHARP_GUARD_BLACKLIST_S *pstEntry);

/*******************************************************************************
*    Func Name: TCPIP_SetARPGuardSwitch
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 设置Guard功能开关
*        Input: ULONG ulValue: 开关值
*       Output:
*       Return: 成功:VOS_OK
*               其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetARPGuardSwitch(ULONG ulValue);

/*******************************************************************************
*    Func Name: TCPIP_GetARPGuardSwitch
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description:获取Guard功能开关
*        Input: ULONG *pulValue: 输出参数,获取开关值
*       Output:
*       Return: 成功:VOS_OK
*               其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetARPGuardSwitch(ULONG *pulValue);

/*******************************************************************************
*    Func Name: TCPIP_SetARPGuardCheatDetectCount
* Date Created: 2009-9-18
*       Author: zhangchunyu(62474)
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 设置防欺骗检测发送ARP报文次数,取值范围是5到15
*        Input: ULONG ulCount: 次数
*       Output:
*       Return: 成功:VOS_OK
*               其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetARPGuardCheatDetectCount(ULONG ulValue);

/*******************************************************************************
*    Func Name: TCPIP_GetARPGuardCheatDetectCount
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 获取防欺骗检测发送ARP报文次数
*        Input: ULONG *pulCount: 输出参数
*       Output:
*       Return: 成功:VOS_OK
*               其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetARPGuardCheatDetectCount(ULONG *pulValue);


/*******************************************************************************
*    Func Name: TCPIP_ShowARPGuardDynamicBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 显示所有动态黑名单
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18   zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowARPGuardDynamicBlack(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowARPGuardStaticBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 显示所有静态黑名单
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18   zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowARPGuardStaticBlack(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DelARPGuardlAllStaticBlackNode
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 删除所有静态黑名单
*        Input: VOID
*       Output:
*       Return: VOS_OK:成功
*               ETHARP_NOT_INIT:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18   zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DelARPGuardlAllStaticBlackNode(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DelARPGuardlAllDynamicBlackNode
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: 删除所有动态黑名单
*        Input: VOID
*       Output:
*       Return: VOS_OK:成功
*               ETHARP_NOT_INIT:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DelARPGuardlAllDynamicBlackNode(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DelDynamicBlackNode
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)
*  Description: 删除一条黑名单记录
*        Input: ULONG ulIpAddr:地址
*               ULONG ulVrfIndex:VRF索引
*               UCHAR *pszMac:physical地址
*       Output: 
*       Return: 成功VOS_OK;失败错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-4    zengshaoyang(62531)      Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_DelDynamicBlackNode(ULONG ulIpAddr, ULONG ulVrfIndex, UCHAR *pszMac);

/*******************************************************************************
*    Func Name: TCPIP_SetARPGuardWarningThreshold
* Date Created: 2011-06-08
*       Author: w60786
*  Description: 配置ARP防攻击告警门限 
*        Input: ULONG ulValue: ARP防攻击告警门限 取值范围[0,1024]
*       Output: 
*       Return: VOS_OK           成功
*               其他             失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-08   w60786                  Create
*
*******************************************************************************/
ULONG TCPIP_SetARPGuardWarningThreshold(ULONG ulValue);

/*******************************************************************************
*    Func Name: TCPIP_GetARPGuardWarningThreshold
* Date Created: 2011-06-08
*       Author: w60786
*  Description: 获取ARP防攻击告警门限
*        Input: 
*       Output: ULONG *pulValue: ARP防攻击告警门限
*       Return: VOS_OK           成功
*               其他             失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-08   w60786                  Create
*
*******************************************************************************/
ULONG TCPIP_GetARPGuardWarningThreshold(ULONG *pulValue);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ETHARP_API_H_ */

