/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              acl6_ppi.h
*
*  Project Code: VISPV1R8
*   Module Name: ACL6  
*  Date Created: 
*        Author: 
*   Description: ACL6 PPI信息下发文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*
*******************************************************************************/
#ifndef __ACL6_PPI_H__
#define __ACL6_PPI_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*ACL6下发耗前耗时打点*/
#define MAKE_ACL6PPI_STARTDOT(OprType)\
{\
    if (g_ulACL6PpiTimeSwitch)\
    {\
        ULONG ii = g_ulACL6PpiTime.ulACL6PpiCount;\
        ii %= ACL6_PPI_COUNT;\
        VOS_GetCpuTick( &(g_ulACL6PpiTime.stStartTime[ii].ulLowTick),  \
                        &(g_ulACL6PpiTime.stStartTime[ii].ulHighTick) );\
        g_ulACL6PpiTime.ulOprType[ii] = OprType;\
    }\
}
/*ACL6下发耗返回后时间打点*/
#define MAKE_ACL6PPI_ENDDOT()\
{\
    if (g_ulACL6PpiTimeSwitch)\
    {\
        ULONG ii = g_ulACL6PpiTime.ulACL6PpiCount;\
        ii %= ACL6_PPI_COUNT;\
        VOS_GetCpuTick( &(g_ulACL6PpiTime.stEndTime[ii].ulLowTick),  \
                        &(g_ulACL6PpiTime.stEndTime[ii].ulHighTick) );\
        g_ulACL6PpiTime.ulACL6PpiCount++;\
    }\
}

/*ACL6基本规则PPI内容处理*/
#define ACL6_COPY_BASIC_CONTENT(stPpiBasicRule, pstRuleContent)\
{\
    stPpiBasicRule.ulAction = pstRuleContent->ulAction;\
    stPpiBasicRule.ulFrag = pstRuleContent->ulFrag;\
    stPpiBasicRule.ulVrfIndex = pstRuleContent->ulVrfIndex;\
    (VOID)TCPIP_Mem_Copy(stPpiBasicRule.stSrcIp.ucAddr, ACL6_IPV6_ADDR_LEN, pstRuleContent->stSrcIp.ucAddr,ACL6_IPV6_ADDR_LEN);\
    stPpiBasicRule.stSrcIp.ulMaskLen = pstRuleContent->stSrcIp.ulMaskLen;\
}

/*ACL6高级规则PPI内容处理*/
#define ACL6_COPY_ADV_CONTENT(stPpiAdvRule, pstRuleContent)\
{\
    stPpiAdvRule.ulAction = pstRuleContent->ulAction;\
    stPpiAdvRule.ulFrag = pstRuleContent->ulFrag;\
    stPpiAdvRule.ulVrfIndex = pstRuleContent->ulVrfIndex;\
    (VOID)TCPIP_Mem_Copy(stPpiAdvRule.stSrcIp.ucAddr, ACL6_IPV6_ADDR_LEN, pstRuleContent->stSrcIp.ucAddr,ACL6_IPV6_ADDR_LEN);\
    stPpiAdvRule.stSrcIp.ulMaskLen = pstRuleContent->stSrcIp.ulMaskLen;\
    (VOID)TCPIP_Mem_Copy(stPpiAdvRule.stDstIp.ucAddr, ACL6_IPV6_ADDR_LEN, pstRuleContent->stDstIp.ucAddr,ACL6_IPV6_ADDR_LEN);\
    stPpiAdvRule.stDstIp.ulMaskLen = pstRuleContent->stDstIp.ulMaskLen;\
    stPpiAdvRule.ulSrcPortOpType = pstRuleContent->ulSrcPortOpType;\
    stPpiAdvRule.stSrcPort.usBegin = pstRuleContent->stSrcPort.usBegin;\
    stPpiAdvRule.stSrcPort.usEnd = pstRuleContent->stSrcPort.usEnd;\
    stPpiAdvRule.ulDstPortOpType = pstRuleContent->ulDstPortOpType;\
    stPpiAdvRule.stDstPort.usBegin = pstRuleContent->stDstPort.usBegin;\
    stPpiAdvRule.stDstPort.usEnd = pstRuleContent->stDstPort.usEnd;\
    stPpiAdvRule.ucProtoBegin = pstRuleContent->ucProtoBegin;\
    stPpiAdvRule.ucProtoEnd = pstRuleContent->ucProtoEnd;\
    stPpiAdvRule.ucClass = pstRuleContent->ucClass;\
    stPpiAdvRule.ucHopLm = pstRuleContent->ucHopLm;\
}

/*ACL6基于接口规则PPI内容处理*/
#define ACL6_COPY_IFBASED_CONTENT(stPpiIfBasedRule, pstRuleContent)\
{\
    stPpiIfBasedRule.ulAction = pstRuleContent->ulAction;\
    stPpiIfBasedRule.ulIfIndex = pstRuleContent->ulIfIndex;\
}

/*添加ACL6 PPI下发可测试性相关变量及宏定义*/
typedef struct tagACL6_CPUTICK
{
    ULONG  ulLowTick;   
    ULONG  ulHighTick; 
}ACL6_CPUTICK_S;

#define ACL6_PPI_COUNT 5  /*下发次数*/
typedef struct tagACL6_PPI_TIME
{
    ACL6_CPUTICK_S stStartTime[ACL6_PPI_COUNT];/*下发记录的开始时间*/
    ACL6_CPUTICK_S stEndTime[ACL6_PPI_COUNT];  /*下发记录的结束时间*/
    ULONG         ulOprType[ACL6_PPI_COUNT];  /*下发的操作类型*/
    ULONG         ulACL6PpiCount;             /*下发次数*/
}ACL6_PPI_TIME_S;

typedef VOID (*ACL6_PPI_GROUP_Update_NODES) (ULONG ulOprType, ULONG ulGroupIndex);
typedef VOID (*ACL6_PPI_RULE_Update_NODES) (ULONG ulOprType, ULONG ulGroupIndex, ULONG ulRuleIndex, VOID *pstContent);

typedef VOID (*ACL6_GROUP_OR_RULE_CHANGE_HOOK) (ULONG ulGroupIndex);

extern VOID ACL6_PPI_Group_Update(ULONG ulOprType, ULONG ulGroupIndex);
extern VOID ACL6_PPI_Rule_Update(ULONG ulOprType, ULONG ulGroupIndex,
                                  ULONG ulRuleIndex, VOID *pstContent);
extern  VOID ACL6_Group_Or_Rule_Update(ULONG ulGroupIndex);
extern  VOID (*g_i3agent_notify_acl6)(ULONG,ULONG,ULONG);

extern ULONG ACLFW6_PPI_Update(ULONG ulOprType, ULONG ulMsgType, VOID *pData);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ACL6_PPI_H__ */

