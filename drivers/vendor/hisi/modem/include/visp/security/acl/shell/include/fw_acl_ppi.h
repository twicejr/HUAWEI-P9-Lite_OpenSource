/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              acl_ppi.h
*
*  Project Code: VISPV1R7
*   Module Name: ACL  
*  Date Created: 2008-07-25
*        Author: wuhailan
*   Description: ACL PPI信息下发文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-07-25   wuhailan                Create
*  2008-09-10   liangjicheng          V1R7C02 同步V1R7C01  文件新增
*  2011-08-13   Eswar-72335          Added PPI download for MAC based rules
*******************************************************************************/
#ifndef __FW_ACL_PPI_H__
#define __FW_ACL_PPI_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*physical address/mask length*/
#define MAC_ADD_LEN 6


/*ACL基本规则PPI内容处理*/
#define ACL_COPY_BASE_Context(stPpiBaseRule, pstRuleContext)\
{\
    stPpiBaseRule.usAction = (USHORT)pstRuleContext->ulAction;\
    stPpiBaseRule.usFrag   = pstRuleContext->bFrag;\
    stPpiBaseRule.ulSrcAddr= pstRuleContext->stSIP.ulAddr;\
    stPpiBaseRule.ulSrcMask= pstRuleContext->stSIP.ulMask;\
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */\
    stPpiBaseRule.ulVrfIndex = pstRuleContext->ulVrfIndex;\
    /* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */\
}


/*ACL高级规则PPI内容处理*/
#define ACL_COPY_EXTEND_Context(stPpiExtendRule, pstRuleContext)\
{\
    stPpiExtendRule.usAction = (USHORT)pstRuleContext->ulAction;\
    stPpiExtendRule.usFrag   = pstRuleContext->bFrag;\
    \
    stPpiExtendRule.usSPNum  = pstRuleContext->ucSPNum;\
    stPpiExtendRule.usDPNum  = pstRuleContext->ucDPNum;\
    stPpiExtendRule.usSP_Begin1 = pstRuleContext->stSP[0].usBegin;\
    stPpiExtendRule.usSP_End1   = pstRuleContext->stSP[0].usEnd;\
    stPpiExtendRule.usSP_Begin2  = pstRuleContext->stSP[1].usBegin;\
    stPpiExtendRule.usSP_End2  = pstRuleContext->stSP[1].usEnd;\
    stPpiExtendRule.usDP_Begin1 = pstRuleContext->stDP[0].usBegin;\
    stPpiExtendRule.usDP_End1 = pstRuleContext->stDP[0].usEnd;\
    stPpiExtendRule.usDP_Begin2   = pstRuleContext->stDP[1].usBegin;\
    stPpiExtendRule.usDP_End2  = pstRuleContext->stDP[1].usEnd;\
    \
    stPpiExtendRule.ulSrcAddr  = pstRuleContext->stSIP.ulAddr;\
    stPpiExtendRule.ulSrcMask  = pstRuleContext->stSIP.ulMask;\
    stPpiExtendRule.ulDscAddr  = pstRuleContext->stDIP.ulAddr;\
    stPpiExtendRule.ulDscMask  = pstRuleContext->stDIP.ulMask;\
    \
    stPpiExtendRule.ucPID_Begin= pstRuleContext->stPID.ucBegin;\
    stPpiExtendRule.ucPID_End  = pstRuleContext->stPID.ucEnd;\
    stPpiExtendRule.ucPre      = pstRuleContext->ucPre;\
    stPpiExtendRule.ucTos      = pstRuleContext->ucTos;\
    stPpiExtendRule.ucDscp     = pstRuleContext->ucDscp;\
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */\
    stPpiExtendRule.ulVrfIndex = pstRuleContext->ulVrfIndex;\
    /* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */\
}

/*MAC ACL content copying to PPI strucuture*/


#define ACL_COPY_MAC_Context(stPpiExtendRule, pstRuleContext)\
{\
    stPpiExtendRule.ulAction = pstRuleContext->ulAction;\
    (VOID)FWCOMMON_MEMCPY(stPpiExtendRule.usDstMac,MAC_ADD_LEN,pstRuleContext->stMac.unMac.ucMac,MAC_ADD_LEN);\
    (VOID)FWCOMMON_MEMCPY(stPpiExtendRule.usSrcMac,MAC_ADD_LEN,&(pstRuleContext->stMac.unMac.ucMac[MAC_ADD_LEN]),MAC_ADD_LEN);\
    (VOID)FWCOMMON_MEMCPY(stPpiExtendRule.usDstMask,MAC_ADD_LEN,pstRuleContext->stMac.unMacMask.ucMask,MAC_ADD_LEN);\
    (VOID)FWCOMMON_MEMCPY(stPpiExtendRule.usSrcMask,MAC_ADD_LEN,&(pstRuleContext->stMac.unMacMask.ucMask[MAC_ADD_LEN]),MAC_ADD_LEN);\
    stPpiExtendRule.ulFrameType = pstRuleContext->ulFrameType;\
    if(EXTENDEDMACACL_RULEID_TYPE == pstRuleContext->ulFrameType)\
    {\
        stPpiExtendRule.usCode = pstRuleContext->stType.unCode.usCode;\
        stPpiExtendRule.usCodeMask = pstRuleContext->stType.unCodeMask.usCodeMask;\
    }\
    else if(EXTENDEDMACACL_RULEID_LSAP == pstRuleContext->ulFrameType)\
    {\
        stPpiExtendRule.usCode = pstRuleContext->stLsap.unCode.usCode;\
        stPpiExtendRule.usCodeMask = pstRuleContext->stLsap.unCodeMask.usCodeMask;\
    }\
    stPpiExtendRule.usVlanIdStart = pstRuleContext->stVlanRange.usVlanIdStart;\
    stPpiExtendRule.usVlanIdEnd = pstRuleContext->stVlanRange.usVlanIdEnd;\
}

/*extern ULONG g_ulACLPpiTimeSwitch; */  /*ACL下发耗时计算开关*/
/*extern ACL_PPI_TIME_S g_ulACLPpiTime;*/ /*ACL下发耗时统计处理变量*/

/*ACL下发耗前耗时打点*/
#define MAKE_ACLPPI_STARTDOT(OprType)\
{\
    if (g_ulACLPpiTimeSwitch)\
    {\
        ULONG ii = g_ulACLPpiTime.ulACLPpiCount;\
        ii %= ACL_PPI_COUNT;\
        VOS_GetCpuTick( &(g_ulACLPpiTime.stStartTime[ii].ulLowTick),  \
                        &(g_ulACLPpiTime.stStartTime[ii].ulHighTick) );\
        g_ulACLPpiTime.ulOprType[ii] = OprType;\
    }\
}
/*ACL下发耗返回后时间打点*/
#define MAKE_ACLPPI_ENDDOT()\
{\
    if (g_ulACLPpiTimeSwitch)\
    {\
        ULONG ii = g_ulACLPpiTime.ulACLPpiCount;\
        ii %= ACL_PPI_COUNT;\
        VOS_GetCpuTick( &(g_ulACLPpiTime.stEndTime[ii].ulLowTick),  \
                        &(g_ulACLPpiTime.stEndTime[ii].ulHighTick) );\
        g_ulACLPpiTime.ulACLPpiCount++;\
    }\
}

/*ACLFW下发耗前耗时打点*/
#define MAKE_ACLFWPPI_STARTDOT(OprType)\
{\
    if (g_ulACLFWPPITimeSwitch)\
    {\
        ULONG ii = g_ulACLFWPPITime.ulACLFWPPICount;\
        ii %= ACLFW_PPI_COUNT;\
        VOS_GetCpuTick( &(g_ulACLFWPPITime.stStartTime[ii].ulLowTick),  \
        &(  g_ulACLFWPPITime.stStartTime[ii].ulHighTick) );\
        g_ulACLFWPPITime.ulOprType[ii] = OprType;\
    }\
}
    /*ACLFW下发耗返回后时间打点*/
#define MAKE_ACLFWPPI_ENDDOT()\
{\
    if (g_ulACLFWPPITimeSwitch)\
    {\
        ULONG ii = g_ulACLFWPPITime.ulACLFWPPICount;\
        ii %= ACLFW_PPI_COUNT;\
        VOS_GetCpuTick( &(g_ulACLFWPPITime.stEndTime[ii].ulLowTick),  \
        &(g_ulACLFWPPITime.stEndTime[ii].ulHighTick) );\
        g_ulACLFWPPITime.ulACLFWPPICount++;\
    }\
}


/*调试信息输出宏*/
#define ACL_PPI_DebugOutput(pBuf)\
{\
    (VOID)TCPIP_IC_SendMsg(0, 0, pBuf);\
}

/*添加ACL PPI下发可测试性相关变量及宏定义*/
/**
* @defgroup tagACL_CPUTICK ACL_CPUTICK_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_CPUTICK
* {
*     ULONG  ulLowTick;
*     ULONG  ulHighTick;
* }ACL_CPUTICK_S;
* @endcode 
* 
* @par Description
* This structure is used in ACL timer configuration structures.
*
* @datastruct ulLowTick Start time
* @datastruct ulHighTick End time
*/
typedef struct tagACL_CPUTICK
{
    ULONG  ulLowTick;   
    ULONG  ulHighTick; 
}ACL_CPUTICK_S;

#define ACL_PPI_COUNT 5  /*下发次数*/
/**
* @defgroup tagACL_PPI_TIME ACL_PPI_TIME_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_PPI_TIME
* {
*     ACL_CPUTICK_S stStartTime[ACL_PPI_COUNT];
*     ACL_CPUTICK_S stEndTime[ACL_PPI_COUNT];
*     ULONG ulOprType[ACL_PPI_COUNT];
*     ULONG ulACLPpiCount;
* }ACL_PPI_TIME_S;
* @endcode 
* 
* @par Description
* This structure notifies ACL timer configuration to PPI call back function.
*
* @datastruct stStartTime[ACL_PPI_COUNT] Record start time issued
* @datastruct stEndTime[ACL_PPI_COUNT] Record end time issued
* @datastruct ulOprType[ACL_PPI_COUNT] Type of operation issued
* @datastruct ulACLPpiCount Number of times notified
*/
typedef struct tagACL_PPI_TIME
{
    ACL_CPUTICK_S stStartTime[ACL_PPI_COUNT];/*下发记录的开始时间*/
    ACL_CPUTICK_S stEndTime[ACL_PPI_COUNT];  /*下发记录的结束时间*/
    ULONG         ulOprType[ACL_PPI_COUNT];  /*下发的操作类型*/
    ULONG         ulACLPpiCount;             /*下发次数*/
}ACL_PPI_TIME_S;

#define ACLFW_PPI_COUNT 5  /*下发次数*/
/**
* @defgroup tagACLFW_PPI_TIME ACLFW_PPI_TIME_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACLFW_PPI_TIME
* {
*     ACL_CPUTICK_S stStartTime[ACLFW_PPI_COUNT];
*     ACL_CPUTICK_S stEndTime[ACLFW_PPI_COUNT];
*     ULONG ulOprType[ACLFW_PPI_COUNT];
*     ULONG ulACLFWPPICount;
* }ACLFW_PPI_TIME_S;
* @endcode 
* 
* @par Description
* This structure notifies ACLFW timer configuration to PPI call back function.
*
* @datastruct stStartTime[ACLFW_PPI_COUNT] Record start time issued
* @datastruct stEndTime[ACLFW_PPI_COUNT]  Record end time issued
* @datastruct ulOprType[ACL_PPI_COUNT] Type of operation issued
* @datastruct ulACLPpiCount Number of times notified
*/
typedef struct tagACLFW_PPI_TIME
{
    ACL_CPUTICK_S stStartTime[ACLFW_PPI_COUNT];/*下发记录的开始时间*/
    ACL_CPUTICK_S stEndTime[ACLFW_PPI_COUNT];  /*下发记录的结束时间*/
    ULONG         ulOprType[ACLFW_PPI_COUNT];  /*下发的操作类型*/
    ULONG         ulACLFWPPICount;             /*下发次数*/
}ACLFW_PPI_TIME_S;

/* 防火墙PPI数据下发统计信息 */
/**
* @defgroup tagACLFW_PPI_COUNT_S ACLFW_PPI_COUNT_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACLFW_PPI_COUNT_S
* {    
*     ULONG ulACLFWUpdateTotal;
*     ULONG ulACLFWUpdateFailure;
*     ULONG ulPPIInUpdateCount;
*     ULONG ulPPIInDeleteCount;
*     ULONG ulPPIOutUpdateCount;
*     ULONG ulPPIOutDeleteCount;
*     ULONG ulPPIMacInUpdateCount;
*     ULONG ulPPIMacInDeleteCount;
*     ULONG ulPPIMacOutUpdateCount;
*     ULONG ulPPIMacOutDeleteCount;
* }ACLFW_PPI_COUNT_S;
* @endcode 
* 
* @par Description
* This structure is used to get the total number of notifications for Inbound and Outbound in IP and MAC layers.
*
* @datastruct ulACLFWUpdateTotal The total number of update notifications to PPI from ACLFW
* @datastruct ulACLFWUpdateFailure The total number of failure notifications to PPI from ACLFW
* @datastruct ulPPIInUpdateCount The total number of update notifications to PPI from ACLFW for inbound in IP layer
* @datastruct ulPPIInDeleteCount The total number of delete notifications to PPI from ACLFW for inbound in IP layer
* @datastruct ulPPIOutUpdateCount The total number of update notifications to PPI from ACLFW for outbound in IP layer
* @datastruct ulPPIOutDeleteCount The total number of delete notifications to PPI from ACLFW for outbound in IP layer
* @datastruct ulPPIMacInUpdateCount The total number of update notifications to PPI from ACLFW for inbound in MAC layer
* @datastruct ulPPIMacInDeleteCount The total number of delete notifications to PPI from ACLFW for inbound in MAC layer
* @datastruct ulPPIMacOutUpdateCount The total number of update notifications to PPI from ACLFW for outbound in MAC layer
* @datastruct ulPPIMacOutDeleteCount The total number of delete notifications to PPI from ACLFW for outbound in MAC layer
*/
typedef struct tagACLFW_PPI_COUNT_S
{    
    ULONG ulACLFWUpdateTotal;     /* ACLFW更新通知总次数 */    
    ULONG ulACLFWUpdateFailure;   /* ACLFW更新通知失败次数 */
    ULONG ulPPIInUpdateCount;         /*IP层过滤接收方向PPI下发次数-添加更新*/
    ULONG ulPPIInDeleteCount;         /*IP层过滤接收方向PPI下发次数-删除*/
    ULONG ulPPIOutUpdateCount;        /*IP层过滤发送方向PPI下发次数-添加更新*/
    ULONG ulPPIOutDeleteCount;        /*IP层过滤发送方向PPI下发次数-删除*/
    ULONG ulPPIMacInUpdateCount;      /*Mac层过滤接收方向PPI下发次数-添加更新*/
    ULONG ulPPIMacInDeleteCount;      /*Mac层过滤接收方向PPI下发次数-删除*/
    ULONG ulPPIMacOutUpdateCount;     /*Mac层过滤发送方向PPI下发次数-添加更新*/
    ULONG ulPPIMacOutDeleteCount;     /*Mac层过滤发送方向PPI下发次数-删除*/
}ACLFW_PPI_COUNT_S;
    
/**
* @defgroup tagACLFW_HWSTAT ACLFW_HWSTAT_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACLFW_HWSTAT
* { 
*     CHAR   stIfName[ACLFW_MAX_INT_NAME_LEN+1];
*     ULONG  ulIPRcvPermitPacket;
*     ULONG  ulIPRcvDenyPacket;
*     ULONG  ulIPSendPermitPacket;
*     ULONG  ulIPSendDenyPacket;
*     ULONG  ulMacRcvPermitPacket;
*     ULONG  ulMacRcvDenyPacket;
*     ULONG  ulMacSendPermitPacket;
*     ULONG  ulMacSendDenyPacket;
* }ACLFW_HWSTAT_S;
* @endcode 
* 
* @par Description
* This structure is used to get ACLFW statistics.
*
* @datastruct stIfName[ACLFW_MAX_INT_NAME_LEN+1] Interface name
* @datastruct ulIPRcvPermitPacket Number of permitted inbound packets in IP layer.
* @datastruct ulIPRcvDenyPacket Number of denied inbound packets in IP layer.
* @datastruct ulIPSendPermitPacket Number of permitted outbound packets in IP layer.
* @datastruct ulIPSendDenyPacket Number of denied outbound packets in IP layer.
* @datastruct ulMacRcvPermitPacket Number of permitted inbound packets in MAC layer.
* @datastruct ulMacRcvDenyPacket Number of denied inbound packets in MAC layer.
* @datastruct ulMacSendPermitPacket Number of permitted outbound packets in MAC layer.
* @datastruct ulMacSendDenyPacket Number of denied outbound packets in MAC layer.
*/
typedef struct tagACLFW_HWSTAT
{ 
    CHAR   stIfName[ACLFW_MAX_INT_NAME_LEN+1];
    ULONG  ulIPRcvPermitPacket;
    ULONG  ulIPRcvDenyPacket;
    ULONG  ulIPSendPermitPacket;
    ULONG  ulIPSendDenyPacket;
    ULONG  ulMacRcvPermitPacket;
    ULONG  ulMacRcvDenyPacket;
    ULONG  ulMacSendPermitPacket;
    ULONG  ulMacSendDenyPacket;
}ACLFW_HWSTAT_S;

/* ACL RULE 下发PPI数据结构 */
/**
* @defgroup tagPPI_ACLBaseRule PPI_ACL_BASE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagPPI_ACLBaseRule
* {
*     ULONG ulGroupID;
*     ULONG ulRuleID;
*     USHORT usAction;
*     USHORT usFrag;
*     ULONG ulSrcAddr;
*     ULONG ulSrcMask;
*     ULONG ulVrfIndex;
*     ULONG ulIfIndex;
*     ULONG ulDirection;
* }PPI_ACL_BASE_S;
* @endcode 
* 
* @par Description
* This is the ACL rule issued PPI data structure.
*
* @datastruct ulGroupID Indicates the Group ID
* @datastruct ulRuleID Indicates the rule ID
* @datastruct usAction Indicates the match action
* @datastruct usFrag Indicates the matched packet fragment
* @datastruct ulSrcAddr Indicates source address
* @datastruct ulSrcMask Indicates source mask
* @datastruct ulVrfIndex Indicates VRF index
* @datastruct ulIfIndex Indicates interface index
* @datastruct ulDirection Indicates the direction of the packets. It can have the following values:
*	- 0 - means inbound packet
*	- 1 - means outbound packet
*/
typedef struct tagPPI_ACLBaseRule
{
    ULONG   ulGroupID;          /* 规则组序号 */
    ULONG   ulRuleID;           /* 规则索引 */
    USHORT  usAction;           /* 匹配动作 */
    
    USHORT  usFrag;             /* 是否匹配分片报文 */
    
    ULONG   ulSrcAddr;          /* 源地址 */
    ULONG   ulSrcMask;          /* 通配符 */
    
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG ulVrfIndex;   /* VRF索引 */
    /* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */    

    /*Begin:VISP V1R8C01 IfIndex Direction eswar 2009-11-03*/
    ULONG   ulIfIndex;     /*interface index*/ 
    ULONG   ulDirection;   /*0:Inbound 1:Outbound*/
    /*End:VISP V1R8C01 IfIndex Direction eswar 2009-11-03*/
}PPI_ACL_BASE_S;


/* ACL RULE 下发PPI数据结构 */
/**
* @defgroup tagPPI_ACLExtendRule PPI_ACL_EXTEND_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagPPI_ACLExtendRule
* {
*     ULONG   ulGroupID;
*     ULONG   ulRuleID;
*     USHORT  usAction;
*     USHORT  usFrag;
*     USHORT  usSPNum;
*     USHORT  usDPNum;
*     USHORT  usSP_Begin1;
*     USHORT  usSP_End1;
*     USHORT  usSP_Begin2;
*     USHORT  usSP_End2;
*     USHORT  usDP_Begin1;
*     USHORT  usDP_End1;
*     USHORT  usDP_Begin2;
*     USHORT  usDP_End2;
*     ULONG   ulSrcAddr;
*     ULONG   ulSrcMask;
*     ULONG   ulDscAddr;
*     ULONG   ulDscMask;
*     UCHAR   ucPID_Begin;
*     UCHAR   ucPID_End;
*     UCHAR   ucPre;
*     UCHAR   ucTos;
*     UCHAR   ucDscp;
*     UCHAR   ucPadding[3];
*     ULONG ulVrfIndex;
*     ULONG ulIfIndex;
*     ULONG   ulDirection;
* }PPI_ACL_EXTEND_S;
* @endcode 
* 
* @par Description
* This is the extended ACL rule issued PPI data structure.
*
* @datastruct ulGroupID Group ID
* @datastruct ulRuleID Rule ID
* @datastruct usAction Indicates match action
* @datastruct usFrag Indicates match packet fragmentation
* @datastruct usSPNum Indicates source port range. If this value is 1, source port 1 will be used.
* For a value other than 1, source port 1 and 2 both will be used.
* @datastruct usDPNum Indicates destination port range. If this value is 1, destination port 1 will 
* be used. For a value other than 1, destination port 1 and 2 both will be used.
* @datastruct usSP_Begin1 Indicates lower limit of the first source port number.
* @datastruct usSP_End1 Indicates upper limit of the first source port number.
* @datastruct usSP_Begin2 Indicates lower limit of the second source port number.
* @datastruct usSP_End2 Indicates upper limit of the second source port number.
* @datastruct usDP_Begin1 Indicates lower limit of the first destination port number.
* @datastruct usDP_End1 Indicates upper limit of the first destination port number.
* @datastruct usDP_Begin2 Indicates lower limit of the second destination port number.
* @datastruct usDP_End2 Indicates upper limit of the second destination port number.
* @datastruct ulSrcAddr Indicates source address.
* @datastruct ulSrcMask Indicates source mask.
* @datastruct ulDscAddr Indicates destination address.
* @datastruct ulDscMask Indicates destination mask.
* @datastruct ucPID_Begin Indicates lower limit of Protocol ID
* @datastruct ucPID_End Indicates upper limit of Protocol ID
* @datastruct ucPre Indicates precedence option.
* @datastruct ucTos Indicates TOS option.
* @datastruct ucDscp Indicates DSCP option.
* @datastruct ucPadding[3] Used for structure padding.
* @datastruct ulVrfIndex Indicates the VRF index.
* @datastruct ulIfIndex Indicates the interface index.
* @datastruct ulDirection Indicates the direction of the packets. It can have the following values: 
*	- 0 - means inbound packets
*	- 1 - means outbound packets
*/
typedef struct tagPPI_ACLExtendRule
{
    ULONG   ulGroupID;          /* 规则组序号 */
    ULONG   ulRuleID;           /* 规则索引 */
    USHORT  usAction;           /* 匹配动作 */
    
    USHORT  usFrag;             /* 是否匹配分片报文 */
    
    USHORT  usSPNum;            /* 该成员值为1，则仅有SP1生效，值为非1，则SP1和SP2都生效 */
    USHORT  usDPNum;            /* 该成员值为1，则仅有DP1生效，值为非1，则DP1和DP2都生效 */
    USHORT  usSP_Begin1;        /* 第一段源端口号下限值 */
    USHORT  usSP_End1;          /* 第一段源端口号上限值 */
    USHORT  usSP_Begin2;        /* 第二段源端口号下限值 */
    USHORT  usSP_End2;          /* 第二段源端口号上限值 */
    USHORT  usDP_Begin1;        /* 第一段目的端口号下限值 */
    USHORT  usDP_End1;          /* 第一段目的端口号上限值 */
    USHORT  usDP_Begin2;        /* 第二段目的端口号下限值 */
    USHORT  usDP_End2;          /* 第二段目的端口号上限值 */    

    ULONG   ulSrcAddr;          /* 源地址 */
    ULONG   ulSrcMask;          /* 通配符 */
    ULONG   ulDscAddr;          /* 目的地址 */
    ULONG   ulDscMask;          /* 通配符 */

    UCHAR   ucPID_Begin;        /* 协议号下限值 */
    UCHAR   ucPID_End;          /* 协议号上限值 */
    
    UCHAR   ucPre;              /* precedence选项 */
    UCHAR   ucTos;              /* TOS选项 */
    UCHAR   ucDscp;             /* Dscp选项 */
    UCHAR   ucPadding[3];
    
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG ulVrfIndex;   /* VRF索引 */
    /* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */    

    /*Begin:VISP V1R8C01 IfIndex Direction eswar 2009-11-03*/
    ULONG ulIfIndex;         /*interface index*/  
    ULONG   ulDirection;     /*0:Inbound 1:Outbound*/
    /*End:VISP V1R8C01 IfIndex Direction eswar 2009-11-03*/
}PPI_ACL_EXTEND_S;


/**
* @defgroup tagPPI_ACLExtendMacRule PPI_ACL_EXTENDMAC_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagPPI_ACLExtendMacRule
* {
*     ULONG  ulGroupID;
*     ULONG  ulRuleID;
*     ULONG  ulAction;
* 
*     UCHAR usSrcMac[6];
*     UCHAR usSrcMask[6];
* 
*     UCHAR usDstMac[6];
*     UCHAR usDstMask[6];
* 
*     ULONG ulFrameType;
*
*     USHORT usCode;
*     USHORT usCodeMask;
* 
*     USHORT usVlanIdStart;
*     USHORT usVlanIdEnd;
* 
*     ULONG ulIfIndex;
*     ULONG ulDirection;
* 
* }PPI_ACL_EXTENDMAC_S;
* @endcode 
* 
* @par Description
* This is the MAC based ACL RULE issued PPI data structure.
*
* @datastruct ulGroupID Group ID
* @datastruct ulRuleID Rule ID
* @datastruct usAction Indicates match action
* @datastruct usSrcMac Indicates source physical address.
* @datastruct usSrcMask Indicates source MAC mask.
* @datastruct usDstMac Indicates destination physical address.
* @datastruct usDstMask Indicates destination MAC mask.
* @datastruct ulFrameType Inidcates frame type. Type can be one of the below things.
* Depending on the ulFrameType the next fields(usCode, usCodeMask) need to be considered.
* 0 - EXTENDEDMACACL_RULEID_NUNE. No need to consider next fields(usCode, usCodeMask).
* 1 - EXTENDEDMACACL_RULEID_TYPE. Next fields(usCode, usCodeMask) contains type code and mask.
* 2 - EXTENDEDMACACL_RULEID_LSAP. Next fields(usCode, usCodeMask) contains lsap code and mask.
* @datastruct usCode Indicates code for given framtype.
* @datastruct usCodeMask Indicates code mask for given framtype.
* @datastruct usVlanIdStart Indicates VLAN ID start configuration.
* @datastruct usVlanIdEnd Indicates VLAN ID end configuration.
* @datastruct ulIfIndex Indicates the interface index.
* @datastruct ulDirection Indicates the direction of the packets. It can have the following values: 
*	- 0 - means inbound packets
*	- 1 - means outbound packets
*/
typedef struct tagPPI_ACLExtendMacRule
{
    ULONG  ulGroupID;
    ULONG  ulRuleID;
    ULONG  ulAction;

    UCHAR usSrcMac[6];
    UCHAR usSrcMask[6];

    UCHAR usDstMac[6];
    UCHAR usDstMask[6];

    ULONG ulFrameType;

    USHORT usCode;
    USHORT usCodeMask;

    USHORT usVlanIdStart;
    USHORT usVlanIdEnd;
    USHORT usVlanPriorityVal; /* s72256: VLAN priority value*/
    USHORT usPadding;         /* s72256: Added 2 bytes to make byte alignment */

    ULONG ulIfIndex;
    ULONG ulDirection;
}PPI_ACL_EXTENDMAC_S;

/* PPI统计信息 */
/**
* @defgroup tagACL_PPI_COUNT_S ACL_PPI_COUNT_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_PPI_COUNT_S
* {
*     ULONG ulAclUpdateTotal; 
*     ULONG ulAclUpdateFailure; 
* }ACL_PPI_COUNT_S;
* @endcode 
* 
* @par Description
* This structure stores the PPI statistics related values.
*
* @datastruct ulAclUpdateTotal The total number of ACL update notifications.
* @datastruct ulAclUpdateFailure Indicates ACL update notification failures.
*/
typedef struct tagACL_PPI_COUNT_S
{
    /* ACL更新通知总次数 */
    ULONG ulAclUpdateTotal; 

    /* ACL更新通知失败次数 */
    ULONG ulAclUpdateFailure; 
}ACL_PPI_COUNT_S;


/* PPI数据面匹配的统计信息 */
/**
* @defgroup tagACL_PPI_MATCH_COUNT_S ACL_PPI_MATCH_COUNT_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagACL_PPI_MATCH_COUNT_S
* {
*     ULONG ulGroupID;
*     ULONG ulRuleID;
*     ULONG ulCount;
* }ACL_PPI_MATCH_COUNT_S;
* @endcode 
* 
* @par Description
* This structure stores the details such as group ID, rule ID, and number of rules matched.
*
* @datastruct ulGroupID Indicates the group ID.
* @datastruct ulRuleID Indicates the rule ID.
* @datastruct ulCount Indicates the number of rules that matched.
*/
typedef struct tagACL_PPI_MATCH_COUNT_S
{
    ULONG ulGroupID;  /* 规则组序号 */
    ULONG ulRuleID;   /* 规则索引 */
    ULONG ulCount;    /* 规则匹配的次数,包括匹配拒绝的次数和匹配允许的次数*/
}ACL_PPI_MATCH_COUNT_S;

/**
* @defgroup ACL_PPI_InfoMsg ACL_PPI_InfoMsg
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_PPI_InfoMsg(ULONG ulRet, ULONG ulOperType, ULONG ulRuleType, VOID *pstPpiAcl);
* @endcode 
* 
* @par Description
* This function is used to store the information based on the type of operation and ACL rule.
* 
* @param[in] ulRet Indicates the error code [] 
* @param[in] ulOperType Indicates the operation type. It can have the following values: 
*	- PPI_ACLRULE_CREATE (0)
*	- PPI_ACLRULE_UPDATE (1)
*	- PPI_ACLRULE_DEL (2)
*	- PPI_ACLRULE_DELALL (3)
*	- PPI_ACLGROUP_CREATE (4)
*	- PPI_ACLGROUP_DEL (5) [PPI_MSG_TYPE_ACL_E]
* @param[in] ulRuleType Indicates the type of ACL rule. It can have the following values: 
*	- ACL_BASIC_RULE_TYPE (1) 
*	- ACL_ADVANCE_RULE_TYPE (2) [] 
*	- ACL_EXTMAC_RULE_TYPE (4) [] 
* @param[in] pstPpiAcl Indicates null pointer. It stores the corresponding structure type [] 
* configuration values, based on the type of the rule; that is PPI_ACL_BASE_S or PPI_ACL_EXTEND_S or PPI_ACL_EXTENDMAC_S[/] 
* @param[out]   []
* 
* @retval VOID This function does not return any value [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_PPI_GROUP_Update
*	- ACL_PPI_RULE_Update
*/ 
extern VOID ACL_PPI_InfoMsg(ULONG ulRet, ULONG ulOperType, ULONG ulRuleType, VOID *pstPpiAcl);

/**
* @defgroup ACL_PPI_GROUP_Update ACL_PPI_GROUP_Update
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_PPI_GROUP_Update(ULONG ulOprType, ULONG ulGroupID);
* @endcode 
* 
* @par Description
* This function is used to update the ACL group information based on the operation type and ACL Group ID.
* 
* @param[in] ulOprType Indicates operation type []
* @param[in] ulGroupID Indicates the group ID []
* @param[out]   []
* 
* @retval VOID This function does not return any value [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_PPI_InfoMsg
*	- ACL_PPI_RULE_Update
*/ 
extern VOID ACL_PPI_GROUP_Update(ULONG ulOprType, ULONG ulGroupID);

/**
* @defgroup ACL_PPI_RULE_Update ACL_PPI_RULE_Update
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_PPI_RULE_Update(ULONG ulOprType, 
*                          ULONG ulGroupID, 
*                          ULONG ulRuleID, 
*                          ULONG ulIfIndex, 
*                          ULONG ulDirection, 
*                          VOID *pstContext);
* @endcode 
* 
* @par Description
* This function is used to update the rule information based on the type of operation, group ID, rule ID, 
* interface index, incoming or outgoing packets.
* 
* @param[in] ulOprType Indicates the type of operation. []
* @param[in] ulGroupID Indicates the group ID. []
* @param[in] ulRuleID Indicates the rule ID. []
* @param[in] ulIfIndex Indicates the interface index. []
* @param[in] ulDirection Indicates the direction of packet transmission. []
* @param[in] pstContext Indicates a null pointer. []
* @param[out]   []
* 
* @retval VOID This function does not return any value [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* pstContext can be NULL, when ulOprType is PPI_ACLRULE_DELALL.
* 
* 
* @par Related Topics
*	- ACL_PPI_InfoMsg
*	- ACL_PPI_GROUP_Update
*/ 
extern VOID ACL_PPI_RULE_Update(ULONG ulOprType, ULONG ulGroupID, ULONG ulRuleID, ULONG ulIfIndex, ULONG ulDirection, VOID *pstContext);

/**
* @defgroup ACLFW_PPI_InfoMsg ACLFW_PPI_InfoMsg
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_PPI_InfoMsg(ULONG ulRet, ULONG ulOprType, ULONG ulMsgType, VOID *pData);
* @endcode 
* 
* @par Description
* This function is used to store PPI notification statistics from ACLFW module.
* 
* @param[in] ulRet Indicates the error code []
* @param[in] ulOprType Indicates the operation type. It can have the following values: 
*	- PPI_ACLFW_ADD (0)
*	- PPI_ACLFW_DEL (1)
*	- PPI_ACLFW_GET (2)
*	- PPI_ACLFW_CLR (3) [E_ACLFW_PPI_OPR]
* @param[in] ulMsgType Indicates the type of message []
* @param[in] pData Indicates configuration data sent to PPI callback function. []
* 
* @retval VOID This function does not return any value [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
extern VOID ACLFW_PPI_InfoMsg(ULONG ulRet, ULONG ulOprType, ULONG ulMsgType, VOID *pData);

/**
* @defgroup ACLFW_PPI_UpdateFW ACLFW_PPI_UpdateFW
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_PPI_UpdateFW(ULONG ulOprType, ULONG ulMsgType , VOID *pData);
* @endcode 
* 
* @par Description
* This function is used to notify about ACL group bindings with interface to external module.
* 
* @param[in] ulOprType Indicates the type of operation []
* @param[in] ulMsgType Indicates the message type []
* @param[in] pData Indicates ACLFW configuration for an interface []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
*
*Return values will be based on registered callback function.
* 
* 
* @par Related Topics
* None
*/ 
extern ULONG ACLFW_PPI_UpdateFW(ULONG ulOprType, ULONG ulMsgType , VOID *pData);


/*ACLFW_PPI_HookRegister        描述:产品注册PPI下发钩子函数*/
/**
* @defgroup ACLFW_PPI_HOOK_FUNC ACLFW_PPI_HOOK_FUNC
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG (*ACLFW_PPI_HOOK_FUNC)(ULONG ulOprType, ULONG ulMsgType, VOID* pData);
* @endcode 
* 
* @par Description
* This function is an ACLFW callback function declaration.
* 
* @param[in] ulOprType Indicates operation type. It will be any value from E_ACLFW_PPI_OPR. []
* @param[in] ulMsgType Indicates message type related to binding operation or statistics. []
* @param[in] pData Indicates configured data if PPI_ACLFW_CFG_S if type is PPI_ACLFW_BIND.  
* Indicates statistics structure if ACLFW_HWSTAT_S if ulMsgType is PPI_ACLFW_STAT. []
* 
* @retval ULONG Depends on registered callback function [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
typedef ULONG (*ACLFW_PPI_HOOK_FUNC)(ULONG ulOprType, ULONG ulMsgType, VOID* pData);

/**
* @defgroup ACLFW_PPI_HookRegister ACLFW_PPI_HookRegister
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_PPI_HookRegister(ACLFW_PPI_HOOK_FUNC pfACLFWPPIHook);
* @endcode 
* 
* @par Description
* This function is used to hook a call back function to get notification for 
* 'bind a group with an interface' and 'unbind a group with an interface'. It is also used to get or clear hardware statistics. 
* 
* @param[in] pfACLFWPPIHook Callback function to be registered. []
* 
* @retval ULONG On success [ACLFW_OK|]
* @retval ULONG Indicates received null pointer as input argument [ACLFW_ERR_NULL|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
extern ULONG ACLFW_PPI_HookRegister(ACLFW_PPI_HOOK_FUNC pfACLFWPPIHook);

/*ACLFW_PPI_SetDebugSwitch      描述:PPI下发Debug开关*/
/**
* @defgroup ACLFW_PPI_SetDebugSwitch ACLFW_PPI_SetDebugSwitch
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_PPI_SetDebugSwitch(ULONG ulSwitch);
* @endcode 
* 
* @par Description
* This function is used to set debug switch for ACLFW PPI operations.
* 
* @param[in] ulSwitch Value of debug switch to be set. []
* 
* @retval ULONG On success [ACLFW_OK|]
* @retval ULONG Indicates wrong value to set debug switch. [ACLFW_ERR_PARA|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
extern ULONG ACLFW_PPI_SetDebugSwitch(ULONG ulSwitch);

/*ACLFW_PPI_GetCount            描述:获取PPI下发统计*/
/**
* @defgroup ACLFW_PPI_GetCount ACLFW_PPI_GetCount
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_PPI_GetCount(ACLFW_PPI_COUNT_S *pstCount);
* @endcode 
* 
* @par Description
* This function is used to get ACLFW PPI notification statistics. 
* 
* @param[out] pstCount Pointer to structure ACLFW_PPI_COUNT_S to which statistics will be copied. []
*
* @retval ULONG On success [ACLFW_OK|]
* @retval ULONG Indicates received null pointer as in put argument [ACLFW_ERR_NULL|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
extern ULONG ACLFW_PPI_GetCount(ACLFW_PPI_COUNT_S *pstCount);

/*ACLFW_PPI_ResetCount          描述:清除PPI下发统计*/
/**
* @defgroup ACLFW_PPI_ResetCount ACLFW_PPI_ResetCount
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_PPI_ResetCount(VOID);
* @endcode 
* 
* @par Description
* This function is used to reset ACLFW PPI notification statistics.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval ULONG On success [ACLFW_OK|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
extern ULONG ACLFW_PPI_ResetCount(VOID);

/*ACLFW_PPI_ShowCount           描述:显示PPI下发统计*/
/**
* @defgroup ACLFW_PPI_ShowCount ACLFW_PPI_ShowCount
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_PPI_ShowCount(VOID);
* @endcode 
* 
* @par Description
* This function is used to show ACLFW PPI notification statistics.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return ant value [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern VOID  ACLFW_PPI_ShowCount(VOID);

/*ACLFW_ClearHWStatByIf         描述:清除硬件防火墙统计*/
/**
* @defgroup ACLFW_ClearHWStatByIf ACLFW_ClearHWStatByIf
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_ClearHWStatByIf(CHAR *pstIfName);
* @endcode 
* 
* @par Description
* This function clears the ACLFW hardware statistics for the given interface.
* 
* @param[in] pstIfName Interface name for which statistics needs to be cleared. []
* 
* @retval ULONG On success. [ACLFW_OK|]
* @retval ULONG Indicates received null pointer as input argument. [ACLFW_ERR_IFNAME|]
* @retval ULONG Indicates interface name length exceeds the limit. [ACLFW_ERR_IFNAME|]
* @retval ULONG Indicates failed to clear statistics. [ACLFW_ERR_PPI_CFG|]
* @retval ULONG Indicates no PPI call back function registered. [ACLFW_ERR_PPI_NOREG|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern ULONG ACLFW_ClearHWStatByIf(CHAR *pstIfName);

/*ACLFW_ClearHWStatByIf         描述:获取硬件防火墙统计*/
/**
* @defgroup ACLFW_GetHWStatByIf ACLFW_GetHWStatByIf
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_GetHWStatByIf(ACLFW_HWSTAT_S *pstStat);
* @endcode 
* 
* @par Description
* This function gets the ACLFW hardware statistics for given interface.
* 
*
* @param[out] pstStat Pointer to a structure ACLFW_HWSTAT_S to which statistics will be copied. []
*
* @retval ULONG On success. [ACLFW_OK|]
* @retval ULONG Indicates received null pointer as input argument [ACLFW_ERR_NULL|]
* @retval ULONG Indicates no PPI call back function registered. [ACLFW_ERR_PPI_NOREG|]
* @retval ULONG Indicates failed to get statistics. [ACLFW_ERR_PPI_CFG|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern ULONG ACLFW_GetHWStatByIf(ACLFW_HWSTAT_S *pstStat);

/*ACLFW_ClearHWStatByIf         描述:显示硬件防火墙统计*/
/**
* @defgroup ACLFW_ShowHWStatByIf
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_ShowHWStatByIf(CHAR *pstIfName);
* @endcode 
* 
* @par Description
* This function gets the ACLFW hardware statistics for the given interface.
* 
* @param[in] pstIfName Interface name for which statistics needs to be shown. []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern VOID  ACLFW_ShowHWStatByIf(CHAR *pstIfName);

/*ACLFW_PPI_SetUpdateCostSwitch 描述:设置ACLFW PPI下发耗时计算开关*/
/**
* @defgroup ACLFW_PPI_SetUpdateCostSwitch ACLFW_PPI_SetUpdateCostSwitch
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_PPI_SetUpdateCostSwitch(ULONG ulSetYes);
* @endcode 
* 
* @par Description
* This function is used to enable or disable calculating CPU ticks for ACLFW PPI updates.
* 
* @param[in] ulSetYes Value to enable/disable the switch. []
* 
* @retval ULONG On success [VOS_OK|]
* @retval ULONG Failed to set the switch [VOS_ERR|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern ULONG ACLFW_PPI_SetUpdateCostSwitch(ULONG ulSetYes);

/*ACLFW_PPI_ShowUpdateCost      描述:ACLFW PPI下发耗时*/
/**
* @defgroup ACLFW_PPI_ShowUpdateCost ACLFW_PPI_ShowUpdateCost
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_PPI_ShowUpdateCost(VOID);
* @endcode 
* 
* @par Description
* This function shows if calculation of CPU ticks for ACLFW PPI update is enabled or disabled.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern VOID ACLFW_PPI_ShowUpdateCost(VOID);

/**
* @defgroup ACL_PPI_HOOK_FUNC ACL_PPI_HOOK_FUNC
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG (*ACL_PPI_HOOK_FUNC) (ULONG ulOprType, ULONG ulRuleType, VOID* pstPpiAcl);
* @endcode 
* 
* @par Description
* This function is an ACL callback function declaration.
* 
* @param[in] ulOprType Indicates operation type. It will be any value from PPI_MSG_TYPE_ACL_E []
* @param[in] ulRuleType Indicates rule for group type (Basic/Advanced/MAC) []
* @param[in] pstPpiAcl Indicates configured data (for rule update) and group number (for group update) []
* @param[out]   []
* 
* @retval ULONG Depends on registered callback function [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
typedef ULONG (*ACL_PPI_HOOK_FUNC) (ULONG ulOprType, ULONG ulRuleType, VOID* pstPpiAcl);

/**
* @defgroup ACL_PPI_HookRegister ACL_PPI_HookRegister
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_PPI_HookRegister(ACL_PPI_HOOK_FUNC pfAclPpiHook);
* @endcode 
* 
* @par Description
* This function is used to hook a call back function to get notification for rule 
* updates, group updates, and rule/group modifications which are bound with an interface.
* 
* @param[in] pfAclPpiHook Callback function to be registered []
* @param[out]   []
*
* @retval ULONG On success [VOS_OK|]
* @retval ULONG Indicates received null pointer as input argument [VOS_ERR|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_PPI_HookRegister(ACL_PPI_HOOK_FUNC pfAclPpiHook);

/**
* @defgroup ACL_SetPpiDebugSwitch ACL_SetPpiDebugSwitch
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_SetPpiDebugSwitch(ULONG ulSwitch);
* @endcode 
* 
* @par Description
* This function is used to set debug switch for ACL PPI operations.
* 
* @param[in] ulSwitch Value of debug switch to be set. []
* @param[out]   []
* 
* @retval ULONG On success [VOS_OK|]
* @retval ULONG Indicates wrong value to set debug switch. [VOS_ERR|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_SetPpiDebugSwitch(ULONG ulSwitch);

/**
* @defgroup ACL_PPI_Count_Get ACL_PPI_Count_Get
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_PPI_Count_Get(ACL_PPI_COUNT_S *pstCount);
* @endcode 
* 
* @par Description
* This function is used to get ACL PPI notification statistics.
* 
* @param[in]   []
* @param[out] pstCount Pointer to structure ACLFW_PPI_COUNT_S to which statistics will be copied. []
* 
* @retval ULONG On success [ACLFW_OK|]
* @retval ULONG Indicates received null pointer as in put argument [VOS_ERR|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_PPI_Count_Get(ACL_PPI_COUNT_S *pstCount);

/**
* @defgroup ACL_PPI_Count_Reset ACL_PPI_Count_Reset
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_PPI_Count_Reset(VOID);
* @endcode 
* 
* @par Description
* This function is used to reset ACL PPI notification statistics.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval ULONG On success [ACLFW_OK|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_PPI_Count_Reset(VOID);

/**
* @defgroup ACL_PPI_ShowCount ACL_PPI_ShowCount
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_PPI_ShowCount(VOID);
* @endcode 
* 
* @par Description
* This function is used to show ACL PPI notification statistics.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern VOID ACL_PPI_ShowCount(VOID);

/**
* @defgroup ACL_ComputeACLPPIUpdateCost ACL_ComputeACLPPIUpdateCost
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ComputeACLPPIUpdateCost(ULONG ulSetYes);
* @endcode 
* 
* @par Description
* This function is used to enable or disable calculating CPU ticks for ACL PPI updates.
* 
* @param[in] ulSetYes Value to enable/disable the switch []
* @param[out]   []

* 
* @retval ULONG On success [VOS_OK|]
* @retval ULONG Failed to set the switch [VOS_ERR|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_ComputeACLPPIUpdateCost(ULONG ulSetYes);

/**
* @defgroup ACL_ShowACLPPIUpdateCost ACL_ShowACLPPIUpdateCost
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_ShowACLPPIUpdateCost(VOID);
* @endcode 
* 
* @par Description
* This function shows if calculation of CPU ticks for ACL PPI update is enabled/disabled.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern VOID ACL_ShowACLPPIUpdateCost(VOID);


/**
* @defgroup ACL_PPI_GetMatchCount ACL_PPI_GetMatchCount
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_PPI_GetMatchCount(ACL_PPI_MATCH_COUNT_S *pstMatchCount);
* @endcode 
* 
* @par Description
* This function gets match count for the given group and rule.
* 
* @param[in] pstMatchCount This structure contains for which group and rule match count is required. []
* @param[out] pstMatchCount The match count for given group and rule will be copied into this structure. []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input argument [Help_ACL_NULL_POINTER|]
* @retval ULONG Indicates there is no callback function registered  [Help_ACL_FUNC_NULL|]
* @retval ULONG Indicates failed to get match count  [Help_ACL_ERR_GETMATCHCOUNT|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_PPI_GetMatchCount(ACL_PPI_MATCH_COUNT_S *pstMatchCount);

/**
* @defgroup ACL_PPI_ShowMatchCountInfo ACL_PPI_ShowMatchCountInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_PPI_ShowMatchCountInfo(ULONG ulGroupID, ULONG ulRuleID);
* @endcode 
* 
* @par Description
* This function displays match count for the given group and rule.
* 
* @param[in] ulGroupID ACL group number for which match count is required. []
* @param[in] ulRuleID ACL rule number for which match count is required. []
* 
* @retval VOID This function does not return any value [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern VOID ACL_PPI_ShowMatchCountInfo(ULONG ulGroupID, ULONG ulRuleID);

/**
* @defgroup ACLFW_NotifyIfDelete ACLFW_NotifyIfDelete
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_NotifyIfDelete(ULONG ulIfIndex);
* @endcode 
* 
* @par Description
* This function deletes the interface configuration for the given interface index.
* 
* @param[in] ulIfIndex Interface index for which configuration has to be deleted. []
* @param[out]   []
* 
* @retval VOID This function does not return any value [|]
* 
* @par Dependency
* fw_acl_ppi.h
* 
* 
* @par Note
* \n
* 
* None
* 
* @par Related Topics
* None
*/ 
extern VOID ACLFW_NotifyIfDelete(ULONG ulIfIndex);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ACL_PPI_H__ */
