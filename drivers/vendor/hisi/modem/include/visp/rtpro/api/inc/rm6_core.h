/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              rm6_core.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2009-09-08
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-09-08   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _RM6_CORE_H
#define _RM6_CORE_H
#ifdef  __cplusplus
    extern "C"{
#endif

#ifndef BOOL_T
#define BOOL_T  short   /* boolean */  
#endif 


#define RTM6_ADDRESS_NTOH(x) \
{\
    (x)[0] = VOS_NTOHL((x)[0]);\
    (x)[1] = VOS_NTOHL((x)[1]);\
    (x)[2] = VOS_NTOHL((x)[2]);\
    (x)[3] = VOS_NTOHL((x)[3]);\
}

#define RTM6_ADDRESS_HTON(x) \
{\
    (x)[0] = VOS_HTONL((x)[0]);\
    (x)[1] = VOS_HTONL((x)[1]);\
    (x)[2] = VOS_HTONL((x)[2]);\
    (x)[3] = VOS_HTONL((x)[3]);\
}

#define RM6_RPM_MTYPE_TYPE1     1
#define RM6_RPM_MTYPE_TYPE2     2

extern ULONG g_ulIpv6PolicyId[];
extern NBB_LLQE_ROOT  g_ipv6RpmPlyCfgList;

extern ULONG g_ulSemForRm6Policy;

typedef struct tagRM6_RPM_PLCYREDIS
{
    UCHAR   ucRPAID; /*引入协议类型*/
    UCHAR   ucPad;    /*填充字段*/
    USHORT  usRPAProcessID;/*引入协议的*/
    ULONG   ulMetricType;/*metric 类型*/
    ULONG   ulMetricVal;/*metric 值*/
} RM6_RPM_PLCYREDIS_S;  


typedef struct tagRM6_CFGREDISTRIBUTE
{
    BOOL_T bNoFlag;
    USHORT usProcessId; 
    RM6_RPM_PLCYREDIS_S stPolicyRedist;
}RM6_CFGREDISTRIBUTE_S;


#define RM6_NOFLAG_ADD 0
#define RM6_NOFLAG_DEL 1


/*比RTM4 多了新的变量，
分开定义是为了后续可以对RTM4 进行优化
*/
typedef struct tagRM6_Rpm_Plcy_Id_s
{
    USHORT usSrcType;   /*源协议类型*/
    USHORT usSrcProcId; /*源协议ID*/
    ULONG  ulDirection; /*过滤的方向:入或者出*/
    USHORT usDstType;   /*目的协议ID*/
    USHORT usDstProcId; /*目的实例号*/
    ULONG  ulPolicyId; /*策略ID*/
    ULONG ulAclGroupNum; /*ACL 规则组号*/
    ULONG ulRtmInstance; /*RTM 的instance*/
    NBB_LLQE  stListNode;/*链表*/
} RM6_RPM_PLCY_ID_S;

/*发送IPS消息后返回的判断操作*/
#define  RM6_IPS_Ret_Opt(ulRet, ips)\
{\
    if (RM_OK != ulRet)\
    {\
        ulRet  += MID_COMP_RTM;\
        goto EXIT_LABEL;\
    }\
    \
    if (NULL == ips)\
    {\
        ulRet = RM_ERR_RETURN_IPS_IS_NULL;\
        goto EXIT_LABEL;\
    }\
    \
    ulRet = ((AMB_SET *)ips)->ret_code;\
    if (ulRet == AMB_RC_NO_ERROR)\
    {\
        ulRet = RM_OK;\
    }\
    else\
    {\
        ulRet += MID_COMP_RTM;\
        goto EXIT_LABEL;\
    }\
}

#define RM6_POLICY_LOCK           (VOID)TCPIP_SmP(g_ulSemForRm6Policy)
#define RM6_POLICY_UNLOCK         (VOID)TCPIP_SmV(g_ulSemForRm6Policy)


extern ULONG RM6_Import_Protocol_Check(RM6_CFGREDISTRIBUTE_S* pstRedistIn,ULONG ulProType);
extern ULONG RM6_Metric_Check(ULONG ulProType,ULONG ulVrfIndex, RM6_CFGREDISTRIBUTE_S* pstRedistIn);
extern ULONG RM6_PolicyCheck(ULONG ulProType,ULONG ulVrfIndex, RM6_CFGREDISTRIBUTE_S* pstRedistIn);
extern ULONG RM6_CfgRouteRedist(RM_CFG_REDIST_S *pstRedistPolicy);
extern ULONG RM6_MetricPolicy_Check(ULONG ulProType,RM_CFG_REDIST_FLAG_S *pstRtmRedistFlag);


extern ULONG RM6_CreatePolicyId(ULONG ulRtm6Instace,ULONG ulPolicyId, ULONG ulDirectFlag);
extern ULONG RM6_CfgDesPolicy(ULONG ulProType,ULONG ulProcessId,ULONG ulRtm6Instace,ULONG ulPolicyId);
extern ULONG RM6_CfgSrcPolicy(RM6_CFGREDISTRIBUTE_S* pstRedistIn,ULONG ulRtm6Instace,ULONG ulPolicyId);
extern ULONG RM6_CfgMetricPolicy(ULONG ulProType,RM6_CFGREDISTRIBUTE_S* pstRedistIn,ULONG ulRtm6Instace,ULONG ulPolicyId);
extern ULONG RM6_ApplyPolicy(ULONG ulInstance,ULONG ulPolicyId,LONG lEnableType);
extern ULONG RM6_DelRoutePolicy(ULONG ulDirection, ULONG ulProType,RM6_CFGREDISTRIBUTE_S* pstRedistIn,ULONG ulRtm6Instace);

extern ULONG RM6_CFG_CmdRtRedistPolicy(ULONG ulProType,ULONG ulVrfIndex, RM6_CFGREDISTRIBUTE_S* pstRedistIn );

extern ULONG RM6_get_redist_mib(MIB_RTM_REDIST_KEY_INDEX_S *pstIndex, 
                        RM_DSP_REDIST_S *pstConfigInfo);

extern ULONG RM6_cmm_redist_open(UINTPTR *pulSessionID,RM_REDIST_FILTER_S *pstRedistFilter);
extern ULONG RM6_cmm_redist_get_first(UINTPTR ulSessionID, RM_DSP_REDIST_S * pstConfigInfo);
extern ULONG RM6_cmm_redist_get_next(UINTPTR ulSessionID, RM_DSP_REDIST_S * pstConfigInfo);
extern LONG RM6_ProType_DclToApi(LONG ulSrcPro);

extern ULONG RM6_DelAllPolicyByRpmId(ULONG ulSrcType, ULONG ulDestProcId,ULONG ulRtm6Instace);
extern ULONG RM6_RouteToRPMProc (ULONG ulProType ,ULONG ulVrfIndex, RM_CFGDISTRIBUTE_S*  pstDistImpIn );
extern ULONG RM6_CfgAcl6PolicyFilter(ULONG ulUndoFlag, ULONG ulRtmInstance, 
                                              ULONG ulPolicyId, ULONG ulAclNum);

extern ULONG RM6_GetFreePlyId(ULONG ulAddrFamily);
extern ULONG RM6_AllocPolicyId(USHORT usDstType, USHORT usDstProcId ,
                USHORT usSrcType,  USHORT usSrcProcId, ULONG ulDirection, 
                ULONG *pulPolicyId, ULONG ulAddrFamily,ULONG ulRtmInstance);
extern ULONG RM6_FreePolicyId(ULONG ulPolicyId , ULONG ulAddrFamily);
extern ULONG RM6_GetPolicyId(USHORT usDstType, USHORT usDstProcId ,USHORT usSrcType, USHORT usSrcProcId,
                        ULONG ulAddrFamily);
extern ULONG RM6_IsPolicyExist(USHORT usDestType, USHORT usDestProcId , ULONG ulAddrFamily);
extern ULONG RM6_SetAclGroupByPolicyInfo(ULONG usDstType, RM_CFGDISTRIBUTE_S*  pstDistImpIn, 
                                                        ULONG ulRtmInstance, ULONG ulPolicyId);
extern ULONG RM6_Acl6ChangeNotify(ULONG ulAclGroupNum, ULONG ulReserve1, ULONG ulReserve2);
extern VOID  RM6_PolicyIdListSort(RM6_RPM_PLCY_ID_S *pstStores);
extern ULONG RM6_RouteFromRPMProc (ULONG ulProType ,ULONG ulVrfIndex, RM_CFGDISTRIBUTE_S*  pstDistImpIn);
extern ULONG RM6_CFG_CmdRtRecvPolicy(ULONG ulProType,ULONG ulVrfIndex, RM6_CFGREDISTRIBUTE_S* pstRedistIn);
extern ULONG RM6_FilterProcFromRpm(ULONG ulPolicyId, UCHAR  ucDestAddr[]);
extern ULONG RM6_GetPolicyInfoByPolicyId(ULONG ulPolicyId, ULONG *pulRtmInstance, ULONG *pulAcl6GroupNum);
extern ULONG RM6_CfgSrcPolicy_RpmToRtm(ULONG ulProType , ULONG ulSrcProcessId,ULONG ulRtm6Instace, ULONG ulPolicyId);
extern ULONG RM6_RouteFromRPMRfresh(ULONG ulProType , ULONG ulProcessId);
extern ULONG RM6_RouteFromRPMProcCheck (ULONG ulProType ,ULONG ulVrfIndex, RM_CFGDISTRIBUTE_S*  pstDistImpIn);
extern ULONG RM6_CheckAndGetAclnum(RM_CFGDISTRIBUTE_S*  pstDistImpIn, ULONG  *pulAcl6GroupNum);
extern BOOL_T RM6_RouteToRPMAclIsExist(ULONG ulPolicyId, ULONG ulAclNum, BOOL_T bMatchFlag);
extern LONG RM6_MetricType_DclToApi(LONG lPathType);
extern BOOL_T  IsRpm_still_has_policy(ULONG ulProType, ULONG ulProcId, ULONG ulDirection);
extern ULONG RPM_Acl6MatchByDestIp (ULONG ulACLNumber, UCHAR ucAddr[LEN_16], ULONG ulPrfixLen);
extern ULONG RM6_GetAclByRpmId(ULONG ulDestType, ULONG  ulDestId, ULONG *pulAcl6GroupNum);

/*************************************************************/
/* Modified by jijianhua00169178, 消除coverity告警, 2011/8/12*/
/* 延时不能使用for,           问题单号:DTS2011081606263 */
/*************************************************************/
extern VOS_VOID VOS_T_Delay( VOS_UINT32 ulMillisecond );
/*End of Modified by jijianhua00169178, 2011/8/12   问题单号:DTS2011081606263 */

#ifdef  __cplusplus
}
#endif

#endif 
