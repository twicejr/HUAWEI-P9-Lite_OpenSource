/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              acl6_api.h
*
*  Project Code: VISP V1R8
*   Module Name: ACL6
*  Date Created: 6
*        Author: 6
*   Description: ACL6随VISP发布(即不单独使用ACL6 CBB)时对外提供的数据结构和用户API声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------

*
*******************************************************************************/
#ifndef _ACL6_API_H_
#define _ACL6_API_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* 随visp发布时,用户除可以使用acl6_api.h中的数据结构和用户API声明外,
   还可以使用 acl6_cbb_api.h中数据结构和用户API声明*/  
#include "tcpip/acl6/include/acl6_cbb_api.h"

/*接口匹配输入信息*/
typedef struct tagAcl6ShClassifyByIfIn
{
    MBUF_S *pstMbuf;     
    ULONG ulIfType;      /*接口匹配类型:
                           1. 只匹配入接口
                           2. 只匹配出接口
                           3. 匹配入和出两种接口*/
    ULONG ulGroupIndex;
} ACL6_SH_CLASSIFY_IF_IN_S;

/*Mbuf匹配输入信息*/
typedef struct tagAcl6ShClassifyByIpIn
{
    MBUF_S *pMBuf;
    ULONG ulGroupIndex;    /* 规则组索引*/
    ULONG ulIgnoreByte;
} ACL6_SH_CLASSIFY_IP_IN_S;

/* PPI数据面匹配的统计信息 */
typedef struct tagAcl6PpiMatchCount
{
    ULONG ulCount;    /* 规则匹配的次数:
                         包括匹配拒绝的次数和匹配允许的次数*/
}ACL6_PPI_MATCH_COUNT_S;


/* ACL6 下发PPI数据结构/从NP获取匹配次数 */
typedef struct tagAcl6PpiMsg
{
    ULONG   ulGroupIndex;       /* 规则组索引 */
    ULONG   ulRuleIndex;        /* 规则索引 */
    union
    {
        ACL6_BASIC_CONTENT_INFO_S stBasicContentInfo;     /*基本规则信息*/
        ACL6_ADVANCE_CONTENT_INFO_S stAdvContentInfo;     /*高级规则信息*/
        ACL6_IFBASED_CONTENT_INFO_S stIfBasedContentInfo; /*基于接口规则信息*/
        ACL6_PPI_MATCH_COUNT_S stPpiMatchCount; /*用于从NP获取匹配次数*/
    } stContent;
}ACL6_PPI_MSG_S;

/* PPI统计信息 */
typedef struct tagAcl6PpiCount
{
    ULONG ulAcl6UpdateTotal;   /* ACL6更新通知总次数 */
    ULONG ulAcl6UpdateFailure; /* ACL6更新通知失败次数 */
}ACL6_PPI_COUNT_S;

/* ACL6 PPI操作类型, 修改此枚举需要同步修改ACL6_PPI_OprType_En处理*/
typedef enum enumAcl6PpiMsgType
{
    PPI_ACL6RULE_CREATE,   /* 创建规则 */
    PPI_ACL6RULE_UPDATE,   /* 更新规则 */
    PPI_ACL6RULE_DEL,      /* 删除规则 */
    PPI_ACL6RULE_DELALL,   /* 删除所有规则*/
    PPI_ACL6GROUP_CREATE,  /* 创建规则组 */
    PPI_ACL6GROUP_DEL,     /* 删除规则组 */
    PPI_ACL6_GETMATCHCOUNT,/* 获取数据面匹配的统计信息 */

    /*Start: ACLFW6 intreface security policy PPI operation type*/
    PPI_ACL6RULE_IF_CREATE,
    PPI_ACL6RULE_IF_DEL,
    /*End: ACLFW6 intreface security policy PPI operation type*/
    ACL6_PPI_MSG_MAX
}ACL6_PPI_MSG_TYPE_E;

typedef ULONG (*ACL6_PPI_HOOK_FUNC) (ULONG ulOprType, ULONG ulTypeId, ACL6_PPI_MSG_S* pstPpiMsg);
/*******************************************************************************
*    Func Name: ACL6_PPI_HookRegister
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ACL6 PPI信息下发钩子注册接口
*        Input: ACL6_PPI_HOOK_FUNC pfAcl6PpiHook:ACL6 PPI信息下发钩子函数指针
*       Output: 
*       Return: Help_ACL6_OK:成功
*                   其他参照错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_HookRegister(ACL6_PPI_HOOK_FUNC pfAcl6PpiHook);
/*******************************************************************************
*    Func Name: ACL6_PPI_SetDebugSwitch
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 设置ACL6 PPI调试开关
*        Input: ULONG ulSwitch:开关,1打开,0关闭
*       Output: 
*       Return: Help_ACL6_OK:成功
*                   其他参照错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_SetDebugSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: ACL6_PPI_GetDebugSwitch
* Date Created: 2009-06-02
*       Author: hanna55555
*  Description: 获取ACL6 PPI调试开关状态
*        Input: 
*       Output: ULONG *pulSwitch:ACL6 PPI调试开关状态
*       Return: Help_ACL6_OK:成功
*                   其他参照错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-02   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_GetDebugSwitch(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: ACL6_PPI_ShowDebugSwitch
* Date Created: 2009-06-02
*       Author: hanna55555
*  Description: 显示ACL6 PPI调试开关状态
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-02   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_PPI_ShowDebugSwitch(VOID);

/*******************************************************************************
*    Func Name: ACL6_PPI_Count_Get
*  Description: 获取ACL6 PPI下发统计信息
*        Input: 无
*       Output: ACL6_PPI_COUNT_S *pstCount:ACL PPI下发返回的统计指针
*       Return: 成功VOS_OK,失败VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern ULONG ACL6_PPI_Count_Get(ACL6_PPI_COUNT_S *pstCount);
/*******************************************************************************
*    Func Name: ACL6_PPI_Count_Reset
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 清除ACL6 PPI下发统计信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_PPI_Count_Reset(VOID);
/*******************************************************************************
*    Func Name: ACL6_PPI_ShowCount
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 显示ACL6 PPI下发统计信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_PPI_ShowCount(VOID);

/*******************************************************************************
*    Func Name: ACL6_PPI_SetUpdateCostDebug
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 使能/去使能计算ACL6 PPI下发时延开关
*        Input: ULONG ulSwitch:使能开关:1使能,0去使能
*       Output: 
*       Return: Help_ACL6_OK:成功
*                   其他参照错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_SetUpdateCostDebug(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: ACL6_PPI_GetUpdateCostDebug
* Date Created: 2009-06-02
*       Author: hanna55555
*  Description: 获取ACL6 PPI下发时延调试开关状态
*        Input: 
*       Output: ULONG *pulSwitch:ACL6 PPI下发时延调试开关状态
*       Return: Help_ACL6_OK:成功
*                   其他参照错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-02   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_GetUpdateCostDebug(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: ACL6_PPI_ShowUpdateCostDebug
* Date Created: 2009-06-02
*       Author: hanna55555
*  Description: 显示ACL6 PPI下发时延调试开关状态
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-02   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_PPI_ShowUpdateCostDebug(VOID);

/*******************************************************************************
*    Func Name: ACL6_PPI_ShowACLUpdateCost
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 显示ACL6 PPI下发耗时信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_PPI_ShowACLUpdateCost(VOID);
/*******************************************************************************
*    Func Name: ACL6_PPI_GetMatchCount
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 根据用户传入的规则组索引和规则索引获取PPI
*                     数据面的规则匹配统计信息
*        Input: ACL6_FILTER_S *pstACL6Filter:过滤器,必须输入规则组索引和规则索引
*       Output: ACL6_PPI_MATCH_COUNT_S *pstMatchCount:规则匹配统计次数
*       Return: Help_ACL6_OK:成功
*                   其他参照错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_GetMatchCount(ACL6_FILTER_S *pstACL6Filter,ACL6_PPI_MATCH_COUNT_S *pstMatchCount);
/*******************************************************************************
*    Func Name: ACL6_PPI_ShowMatchCount
*  Description: 显示PPI数据面的规则匹配统计信息
*        Input:ACL6_FILTER_S *pstACL6Filter:规则组索引和规则索引
*       Output: 
*       Return: VOID
*      Caution: 必须由数据面适配匹配的统计信息,否则显示失败
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern VOID ACL6_PPI_ShowMatchCount(ULONG ulGroupIndex,ULONG ulRuleIndex);
/*******************************************************************************
*    Func Name: ACL6_SH_ClassifyByIfInfo
*  Description: 根据接口进行报文匹配
*        Input: pstAcl6_ClassifyIn   待匹配信息
*       Output: pstAcl6_ClassifyOut->ulRuleIndex    匹配的ACL6规则的第几个节点
 *       Return: ACL_PERMIT      匹配且该匹配节点的动作为"permit"
*               ACL_DENY        匹配且该匹配节点的动作为"deny"
*               ACL_NOTFOUND    和该ACL规则的所有节点都不匹配, pulSubitem无意义
*       Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern ULONG ACL6_SH_ClassifyByIfInfo(ACL6_SH_CLASSIFY_IF_IN_S *pstAcl6_ClassifyIn,
                                             ACL6_CLASSIFY_IF_OUT_S *pstAcl6_ClassifyOut);
/*******************************************************************************
*    Func Name: ACL6_SH_ClassifyByIpInfo
*  Description: 判断一个分组(MBUF)是否满足一个ACL6 Group所描述的流
*        Input: pstAcl6_ClassifyIn   待匹配信息
*                  ULONG ulFlag :VRP_YES表示正向匹配，VRP_NO表示反向匹配        
*       Output: pstAcl6_ClassifyOut->ulRuleIndex    匹配的ACL6规则的第几个节点
 *       Return: ACL_PERMIT  匹配且该匹配节点的动作为"permit"
*               ACL_DENY    匹配且该匹配节点的动作为"deny"
*               ACL_NOTFOUND    和该ACL规则的所有节点都不匹配
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern ULONG ACL6_SH_ClassifyByIpInfo(ACL6_SH_CLASSIFY_IP_IN_S *pstAcl6_ClassifyIn,
                                              ACL6_CLASSIFY_IP_OUT_S *pstAcl6_ClassifyOut,
                                              ULONG ulFlag);

/*******************************************************************************
*    Func Name: ACL6_SH_OpenRuleTable
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 打开
*        Input: ACL6_FILTER_S* pstACL6Filter:过滤器
*                  pstACL6Filter->ulGroupIndex:规则组索引，必须指定
*                  pstACL6Filter->ulRuleIndex:规则索引，可以指定或不指定
*                                                               不指定时填写ACL6_INVALID_RULE_INDEX(值为0xffffffff)
*       Output: ULONG* pulACL6Handle:获取句柄的存放处
*       Return: 
*      Caution: 使用时，需要最后调用ACL6_SH_CloseRuleTable来释放句柄
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_OpenRuleTable(UINTPTR* pulACL6Handle, ACL6_FILTER_S* pstACL6Filter);
/*******************************************************************************
*    Func Name: ACL6_SH_GetNextRuleInfo
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 获取规则信息
*        Input: ULONG ulACL6Handle:句柄
*       Output: ACL6_RULE_INFO_OUT_S* pstACL6Info:规则信息
*       Return: Help_ACL6_OK:成功
*                    其他参加错误码
*      Caution: 先调用ACL6_SH_OpenRuleTable获取句柄
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_GetNextRuleInfo(UINTPTR ulACL6Handle, ACL6_RULE_INFO_OUT_S* pstACL6Info);
/*******************************************************************************
*    Func Name: ACL6_SH_CloseRuleTable
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 关闭句柄
*        Input: ULONG ulACL6Handle:句柄
*       Output: 
*       Return: Help_ACL6_OK:成功
*                    其他参加错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_CloseRuleTable(UINTPTR ulACL6Handle);
/*******************************************************************************
*    Func Name: ACL6_SH_OpenGroupTable
* Date Created: 2009-04-13
*       Author: hanna55555
*  Description: 打开Waitlist句柄，获取系统所有规则组的基本信息
*        Input: ULONG* pulAcl6Handle:
*                  ACL6_FILTER_S *pstGroupFilter: 过滤条件，
*                                               1.不指定过滤请置NULL；
*                                               2.指定规则组号过滤，此时规则号无效；
*       Output:  pulAcl6Handle Waitlist句柄
*       Return:  Help_ACL6_NotInit : ACL CBB未成功初始化
*                    Help_ACL6_NullPoint : 输入指针为空
*                    Help_ACL6_END : 遍历表项时到达最后一条表项
*                    Help_ACL6_WAITLIST_OpenFail : 打开waitlist失败 
*                    Help_ACL6_OK : 成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_OpenGroupTable(UINTPTR* pulAcl6Handle,ACL6_FILTER_S *pstGroupFilter);
/*******************************************************************************
*    Func Name: ACL6_SH_GetNextGroupInfo
* Date Created: 2009-04-13
*       Author: hanna55555
*  Description: 获取系统配置的规则组基本信息
*        Input: ULONG ulAcl6Handle:Waitlist句柄
*       Output: ACL6_GET_GROUP_INFO_S* pstGroupInfo:规则组基本信息
*       Return:  Help_ACL6_NotInit : ACL CBB未成功初始化
*                    Help_ACL6_NullPoint : 输入指针为空
*                    Help_ACL6_WAITLIST_GetFail : 获取waitlist节点失败
*                    Help_ACL6_END : 遍历表项时到达最后一条表项 
*                    Help_ACL6_OK : 成功
*      Caution: 调用该函数前先调用ACL6_SH_OpenGroupTable函数获取Waitlist句柄
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_GetNextGroupInfo(UINTPTR ulAcl6Handle,ACL6_GET_GROUP_INFO_S* pstGroupInfo);
/*******************************************************************************
*    Func Name: ACL6_SH_CloseGroupTable
* Date Created: 2009-04-13
*       Author: hanna55555
*  Description: 关闭Waitlist句柄
*        Input: ULONG ulAcl6Handle:Waitlist句柄
*       Output: 
*       Return:  Help_ACL6_NotInit : ACL CBB未成功初始化
*                    Help_ACL6_NullPoint : 输入指针为空
*                    Help_ACL6_WAITLIST_CloseFail : 关闭waitlist失败
*                    Help_ACL6_OK : 成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_CloseGroupTable(UINTPTR ulAcl6Handle);
/*******************************************************************************
*    Func Name: ACL6_ShowGroupInfo
* Date Created: 2009-04-13
*       Author: hanna55555
*  Description: 显示所有或指定规则组信息
*        Input: ULONG ulGroupIndex:过滤条件，
*               1.为0表示不指定规则组查询；
*               2.非0表示指定规则组查询；
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_ShowGroupInfo(ULONG ulGroupIndex);

/*******************************************************************************
*    Func Name: ACL6_ShowRuleInfo
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 显示指定规则组下的指定规则或所有规则信息
*        Input: ULONG ulGroupIndex:规则组索引
*                  ULONG ulRuleIndex:规则索引
*                           1.ulRuleIndex为ACL6_INVALID_RULE_INDEX(值为:0xffffffff)
*                              表示某规则组下所有规则查询；
*                           2.ulRuleIndex为非ACL6_INVALID_RULE_INDEX(值为:0xffffffff)
*                              表示某规则组下指定规则查询；
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_ShowRuleInfo(ULONG ulGroupIndex,ULONG ulRuleIndex);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

