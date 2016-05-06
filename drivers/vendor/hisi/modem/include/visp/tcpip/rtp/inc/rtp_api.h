
#ifndef _RTP_API_H_
#define _RTP_API_H_
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* 01 Specification                         
*/
#define MAX_RTP_NUM 32              /*路由策略最大数*/
#define MAX_RTP_NODE_NUM 20         /*路由策略节点最大数*/
#define MAX_IPPREDIX_NUM 32         /*IP前缀最大数*/
#define MAX_IPPREDIX_NODE_NUM 20    /*IP前缀节点最大数*/
#define MAX_MAPBIND_NUM 64          /*策略绑定最大数*/

#define MAX_POLICY_NAME_LEN 47      
#define MAX_PREFIX_NAME_LEN 47      
#define MIN_POLICY_NAME_LEN 1       
#define MIN_PREFIX_NAME_LEN 1  

#define MAX_COST_VALUE 0xffff  
#define MIN_COST_VALUE 1  

#define MIN_INTERFACE_NAME_LEN 1
/* 02 OperationCode                      
*/
#define RTP_FLAG_DO    0            /*配置操作类型-do*/
#define RTP_FLAG_UNDO  1            /*配置操作类型-undo*/
#define RTP_FLAG_DELALL  2          /*配置操作类型-DeleteALL*/

#define RTP_FLAG_UNUSED  0 
#define RTP_FLAG_USED  1            

#define RTP_DENY    0               
#define RTP_PERMIT  1 

/*If-Match*/
#define RTP_MATCH_COST          0x00000001  
#define RTP_MATCH_IF            0x00000002  
#define RTP_MATCH_IPDEST_ACL    0x00000004 
#define RTP_MATCH_IPDEST_PREFIX 0x00000008 
#define RTP_MATCH_IPNHOP_ACL    0x00000010 
#define RTP_MATCH_IPNHOP_PREFIX 0x00000020 
#define RTP_MATCH_TAG           0x00000040
#define RTP_MATCH_ROUTETYPE     0x00000080 

/*Apply*/
#define RTP_APPLY_COST          0x00000001  
#define RTP_APPLY_IP_NHOP       0x00000002 
#define RTP_APPLY_TAG           0x00000004  

/*Entry Type*/ 
#define RTP_ENTRYTYPE_OSPF      1 
#define RTP_ENTRYTYPE_RIP       2 
#define RTP_ENTRYTYPE_RTM       3

/*fiter Type*/ 
#define RTP_FITLERTYPE_IN      1 
#define RTP_FITLERTYPE_OUT     2 


/* 03 ErrCode                      
*/
typedef enum tagRTPERRCODE
{
    RTP_OK = 0,     
    RTP_ERR_NORTPMAP        = 101,   
    RTP_ERR_MAPFULL         = 102,
    RTP_ERR_MAPUNDOFLAG     = 103,
    RTP_ERR_MAPMODE         = 104,
    RTP_ERR_MAPNAME         = 105,
    RTP_ERR_MAPNODENUM      = 106,    
    RTP_ERR_MAPCOST         = 107,
    RTP_ERR_MAPIFNAME       = 108,
    RTP_ERR_MAPACL          = 109,
    RTP_ERR_MAPIPPREFIX     = 110,
    RTP_ERR_MAPTAG          = 111,
    RTP_ERR_MAPTYPE         = 112,
    RTP_ERR_PARANULL        = 113,
    RTP_ERR_MAPBINDFULL     = 114,
    RTP_ERR_NOMAPBIND       = 115,
    RTP_ERR_ENTITYTYPE      = 116,
    RTP_ERR_NOMAPRULE       = 117,
    RTP_ERR_NOIPPREFIX      = 201, 
    RTP_ERR_PREFIXFULL      = 202,
    RTP_ERR_PREFIXUNDOFLAG  = 203,
    RTP_ERR_PREFIXNAME      = 204,
    RTP_ERR_PREFIXSEQ       = 205,
    RTP_ERR_PREFIXMODE      = 206,
    RTP_ERR_PREFIXNET       = 207,
    RTP_ERR_PREFIXLEN       = 208,
    RTP_ERR_PREFIXGE        = 209,
    RTP_ERR_PREFIXLE        = 210,
    RTP_ERR_PREFIXLOGIC     = 211,
    RTP_ERR_NOMORE          = 301,
    RTP_ERR_EXISIT          = 302,
    RTP_ERR_MALLOC          = 303,
    RTP_ERR_INVALIDGROUP    = 304,
    RTP_ERR_INVALIDRULE     = 305,
    RTP_ERR_INVALIDENTRYTYPE     = 306,
    RTP_ERR_INVALIDFILTERTYPE     = 307,
    RTP_ERR_INVALIDINDEX     = 308,
    RTP_ERR_NOBIND          = 401,
    RTP_ERR_REBIND          = 402,
    RTP_ERR_BINDFULL        = 403
}RTPERRCODE_E;

typedef enum tagRTPMATCHERRCODE
{
    RTP_MATCH_DENY          = 0,
    RTP_MATCH_PERMIT        = 1,    
    RTP_MATCH_ERR_NOGROUP   = 2,
    RTP_MATCH_ERR_NORULE    = 3,
    RTP_MATCH_ERR_PARANULL  = 4,
    RTP_MATCH_ERR_RTNULL    = 5
}RTPMATCHERRCODE_E;

/****************************************
@Part 2:Structure
Total= 17
01 MAP Bind Structure  
02 IP Prefix Structure          
03 IP Prefix Config             
04 route policy map structure   
05 route policy config          
06 route policy Match           
****************************************/
/* 1-1  Description :                   */
typedef struct tagRTP_MAPBIND_NODE_S
{ 
    ULONG   ulUsed;
    ULONG   ulEntryType;
    ULONG   ulEntryIndex;
    ULONG   ulFilterType;
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN + 1];    
}RTP_MAPBIND_NODE_S;

/* 1-2  Description :                   */
typedef struct tagRTP_MAPBINDLIST_S
{  
    ULONG       ulCount;   
    RTP_MAPBIND_NODE_S   szMapBind[MAX_MAPBIND_NUM];
}RTP_MAPBINDLIST_S;

/****************************************
02 IP Prefix Structure 
    RTP_IPPREFIX_NODE_S     IP前缀的节点结构
    RTP_IPPREFIX_S          IP前缀结构
    RTP_IPPREFIXLIST_S      IP前缀集合结构
****************************************/
/* 2-1  Description :                   */
typedef struct tagRTP_IPPREFIX_NODE_S
{ 
    ULONG   ulUsed;
    LONG    lMode;
    ULONG   ulNetwork;
    ULONG   ulLen;
    ULONG   ulGe;
    ULONG   ulLe;
    ULONG   ulMatched;
    ULONG   ulDenied;
}RTP_IPPREFIX_NODE_S;

/* 2-2  Description :                   */
typedef struct tagRTP_IPPREFIX_S
{ 
    ULONG   ulUsed;
    ULONG   ulCount;   
    CHAR    szPrefixName[MAX_PREFIX_NAME_LEN+1];
    ULONG   ulMaxSeq;
    RTP_IPPREFIX_NODE_S szPrefixNode[MAX_IPPREDIX_NODE_NUM];
}RTP_IPPREFIX_S;

typedef struct tagRTP_IPPREFIXBASIC_S
{ 
    ULONG   ulUsed;
    ULONG   ulCount;   
    CHAR    szPrefixName[MAX_PREFIX_NAME_LEN+1];
    ULONG   ulMaxSeq;
}RTP_IPPREFIXBASIC_S;

/* 2-3  Description :                   */
typedef struct tagRTP_IPPREFIXLIST_S
{  
    ULONG       ulCount;   
    RTP_IPPREFIX_S   szIpPrefix[MAX_IPPREDIX_NUM];
}RTP_IPPREFIXLIST_S;

/****************************************
03 IP Prefix Config     
    RTP_CFG_IPPREFIX_S  IP前缀的配置参数结构
****************************************/

/* 3-1  Description :                   */
typedef struct tagRTP_CFG_IPPREFIX_S
{ 
    ULONG   ulUndoFlag;
    CHAR    szPrefixName[MAX_PREFIX_NAME_LEN+1];
    ULONG   ulSeq;
    LONG    lMode;
    ULONG   ulNetwork;
    ULONG   ulLen;
    ULONG   ulGe;
    ULONG   ulLe;
}RTP_CFG_IPPREFIX_S;

/****************************************
04 route policy map structure  
    RTP_MAPNODE_S       路由策略节点的结构
    RTP_MAP_S           路由策略结构
    RTP_MAPLIST_S       路由策略集合结构
****************************************/
/* 4-1  Description :                   */
typedef struct tagRTP_MAPNODE_S
{ 
    ULONG   ulUsed;
    LONG    lMode;
    ULONG   ulMatched ;
    ULONG   ulDenied ;
    /*match*/
    ULONG   ulMatchFlag;
    ULONG   ulMatchCost;
    CHAR    szMatchIfName[IF_MAX_INTERFACE_NAME_LEN+1];
    ULONG   ulMatchDestACL;
    CHAR    szMatchDestPrefixName [MAX_PREFIX_NAME_LEN+1];
    ULONG   ulMatchNHopACL;
    CHAR    szMatchNHopPrefixName [MAX_PREFIX_NAME_LEN+1];
    ULONG   ulMatchTag;
    ULONG   ulMatchRouteType; 
    /*apply*/
    ULONG   ulApplyFlag;     
    ULONG   ulApplyCost;
    ULONG   ulApplyNHop;
    ULONG   ulApplyTag;    
}RTP_MAPNODE_S;

/* 4-2  Description :                   */
typedef struct tagRTP_MAP_S
{ 
    ULONG   ulUsed;
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN+1];
    ULONG   ulCount;   
    ULONG   ulMatched;
    
    /*预留*/
    ULONG   ulPRSuccess;   /*该策略策略路由报文成功的总数*/
    ULONG   ulPRFail;      /*该策略策略路由报文失败的总数*/
    RTP_MAPNODE_S   szMapNode[MAX_RTP_NODE_NUM];
}RTP_MAP_S;

typedef struct tagRTP_MAPBASIC_S
{ 
    ULONG   ulUsed;
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN+1];
    ULONG   ulCount;   
    ULONG   ulMatched;
    
    /*预留*/
    ULONG   ulPRSuccess;   /*该策略策略路由报文成功的总数*/
    ULONG   ulPRFail;      /*该策略策略路由报文失败的总数*/
}RTP_MAPBASIC_S;


/* 4-3  Description :                   */
typedef struct tagRTP_MAPLIST_S
{ 
    ULONG       ulCount;   
    RTP_MAP_S   szMap[MAX_RTP_NUM];
}RTP_MAPLIST_S;

/****************************************
05 route policy config  
    RTP_CFG_POLICY_S    路由策略配置的参数结构
    RTP_CFG_P_COST_S    路由策略COST策略配置的参数结构
    RTP_CFG_P_IF_S      路由策略接口策略配置的参数结构
    RTP_CFG_P_ACL_S     路由策略ACL策略配置的参数结构
    RTP_CFG_P_PREFIX_S  路由策略IP前缀策略配置的参数结构
    RTP_CFG_P_NHOP_S    路由策略下一跳策略配置的参数结构
    RTP_CFG_P_TAG_S     路由策略TAG策略配置的参数结构
    RTP_CFG_P_TYPE_S    路由策略COST路由类型策略配置的参数结构
****************************************/
/* 5-1  Description :                   */
typedef struct tagRTP_CFG_POLICY_S
{ 
    ULONG   ulUndoFlag;/* deleteALL Flag */
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN+1];
    LONG    lMode;
    ULONG   ulNodeNum;
}RTP_CFG_POLICY_S;

/* 5-2  Description :                   */
typedef struct tagRTP_CFG_P_COST_S
{ 
    ULONG   ulUndoFlag;
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN+1];
    ULONG   ulNodeNum;
    ULONG   ulCost;
}RTP_CFG_P_COST_S;

/* 5-3  Description :                   */
typedef struct tagRTP_CFG_P_IF_S
{ 
    ULONG   ulUndoFlag;
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN+1];
    ULONG   ulNodeNum;
    CHAR    szIfName[IF_MAX_INTERFACE_NAME_LEN+1];
}RTP_CFG_P_IF_S;

/* 5-4  Description :                   */
typedef struct tagRTP_CFG_P_ACL_S
{ 
    ULONG   ulUndoFlag;
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN+1];
    ULONG   ulNodeNum;
    ULONG   ulIpAcl;
}RTP_CFG_P_ACL_S;

/* 5-5  Description :                   */
typedef struct tagRTP_CFG_P_PREFIX_S
{ 
    ULONG   ulUndoFlag;
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN+1];
    ULONG   ulNodeNum;
    CHAR    szIpPrefixName [MAX_PREFIX_NAME_LEN+1];
}RTP_CFG_P_PREFIX_S;

/* 5-6  Description :                   */
typedef struct tagRTP_CFG_P_NHOP_S
{ 
    ULONG   ulUndoFlag;
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN+1];
    ULONG   ulNodeNum;
    ULONG   ulNHop;
}RTP_CFG_P_NHOP_S;

/* 5-7  Description :                   */
typedef struct tagRTP_CFG_P_TAG_S
{ 
    ULONG   ulUndoFlag;
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN+1];
    ULONG   ulNodeNum;
    ULONG   ulTag;
}RTP_CFG_P_TAG_S;

/* 5-8  Description :                   */
typedef struct tagRTP_CFG_P_TYPE_S
{ 
    ULONG   ulUndoFlag;
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN+1];
    ULONG   ulNodeNum;
    ULONG   ulRouteType;
}RTP_CFG_P_TYPE_S;

/****************************************
06 route policy Match   
    RTPRTENTRY4_S       路由项信息
    RTP_MATCH_S         路由策略匹配结构
    MATCH_RESULTS_S     路由策略匹配结果结构
****************************************/
typedef struct tagRTPRTENTRY4
{
    ULONG   ulDst;      /* Destination address */
    ULONG   ulDstMaskLen;  /* Destination mask */
    ULONG   ulGateway;  /* Next hop */
    ULONG   ulCost;     /* Route Cost*/
    ULONG   ulFlags;    /* route flags,RTF_GATEWAY, RTF_HOST, RTF_INTERFACE, RTF_STATE*/
    ULONG   ulIfIndex;  /* index of outgoing interface */
}RTPRTENTRY4_S;

/* 6-1  Description :                   */
typedef struct tagRTP_MATCH_S
{ 
    CHAR    szPolicyName [MAX_POLICY_NAME_LEN+1];
    RTPRTENTRY4_S *pstRt; 
    ULONG   ulSrcProt;
}RTP_MATCH_S;

/* 6-2  Description :                   */
typedef struct tagMATCH_RESULTS_S 
{
    ULONG ulRstFlag;
    ULONG ulNHop;
    ULONG ulTag;
    ULONG ulCost;
} MATCH_RESULTS_S;

/* 7-1  Description :                   */
typedef struct tagRTP_REFILTER_DATA_S
{ 
    ULONG ulDataType;
    ULONG ulEntryType;
    ULONG ulEntryIndex;
    ULONG ulFilterType;
}RTP_REFILTER_DATA_S;

typedef VOID (*IPPREFIXCHG_HOOK_FUNC )(CHAR*,ULONG,ULONG);
typedef VOID (*RTPCHG_HOOK_FUNC )(CHAR*,ULONG,ULONG);

typedef struct tagIPPREFIX_UPDATE_CALLBACK_NODE
{
    IPPREFIXCHG_HOOK_FUNC pfCallBack;
    ULONG ulModuleId;
    struct tagIPPREFIX_UPDATE_CALLBACK_NODE * pstNext;
}IPPREFIX_UPDATE_CALLBACK_NODE_S;

typedef struct tagRTP_UPDATE_CALLBACK_NODE
{
    RTPCHG_HOOK_FUNC pfCallBack;
    ULONG ulModuleId;
    struct tagRTP_UPDATE_CALLBACK_NODE * pstNext;
}RTP_UPDATE_CALLBACK_NODE_S;

typedef ULONG (*RTPDOFILTER_HOOK_FUNC )(ULONG,ULONG,ULONG,RTPRTENTRY4_S *,MATCH_RESULTS_S *);
typedef ULONG (*RTPOSPFEND_HOOK_FUNC )(ULONG);
typedef ULONG (*RTPRIPEND_HOOK_FUNC )(ULONG);
/****************************************
@Part 3: API    (10)    
****************************************/
/*1-1*/ULONG Rtp_Init();
/*1-2*/ULONG Rtp_UnInit();
/*1-3*/ULONG  Rtp_RegFuncIPPrefixChangeHook(IPPREFIXCHG_HOOK_FUNC pfHookFunc, ULONG ulModId);
/*1-4*/ULONG  Rtp_RegFuncRTPChangeHook(RTPCHG_HOOK_FUNC pfHookFunc, ULONG ulModId);
/*1-5*/ULONG Rtp_RegFuncRTPDoFilterHook(RTPDOFILTER_HOOK_FUNC pfHookFunc);
/*1-6*/ULONG  Rtp_RegFuncRTPRIPEndHook(RTPRIPEND_HOOK_FUNC pfHookFunc);
/*1-6*/ULONG  Rtp_RegFuncRTPOSPFEndHook(RTPOSPFEND_HOOK_FUNC pfHookFunc);
/*1-7*/VOID RTP_UpdatePolicy(CHAR* pcPolicyName, ULONG ulRuleId, ULONG ulEventType);
/*1-8*/VOID RTP_UpdateIPPrefix(CHAR* pcPrefixName, ULONG ulRuleId, ULONG ulEventType);
/*1-9*/VOID Rtp_DoIPPrefixChange(CHAR*  pcPrefixName, ULONG ulRuleId, ULONG ulEventType);
/*1-10*/VOID Rtp_DoACLChange(ULONG ulGroupId, ULONG ulRuleId, ULONG ulEventType);
/*1-11*/VOID Rtp_DoPolicyChange(CHAR*  pcPolicyName, ULONG ulRuleId, ULONG ulEventType);

/*2-1*/ULONG Rtp_SetIpPrefix (RTP_CFG_IPPREFIX_S *pstCfgPrefix);

/*3-1*/ULONG Rtp_SetPolicy(RTP_CFG_POLICY_S *pstCfgPolicy);
/*3-2*/ULONG Rtp_SetMatchCost (RTP_CFG_P_COST_S  *pstCfgCost);
/*3-3*/ULONG Rtp_SetMatchIf (RTP_CFG_P_IF_S *pstCfgIf);
/*3-4*/ULONG Rtp_SetMatchIpDestACL (RTP_CFG_P_ACL_S *pstCfgACL);
/*3-5*/ULONG Rtp_SetMatchIpDestPrefix (RTP_CFG_P_PREFIX_S *pstCfgPrefix);
/*3-6*/ULONG Rtp_SetMatchIpNHopACL (RTP_CFG_P_ACL_S *pstCfgACL);
/*3-7*/ULONG Rtp_SetMatchIpNHopPrefix (RTP_CFG_P_PREFIX_S *pstCfgPrefix);
/*3-8*/ULONG Rtp_SetApplyCost (RTP_CFG_P_COST_S *pstCfgCost);
/*3-9*/ULONG Rtp_BindPolicy(ULONG ulEntryType,ULONG ulEntryIndex, ULONG ulFilterType
    , CHAR *pcPolicyName, ULONG ulUndoFlag);

/*4-1*/ULONG Rtp_GetBindMapName(ULONG ulEntryType, ULONG ulEntryIndex, ULONG ulFilterType
    , CHAR *pMapName);
/*4-2*/ULONG Rtp_ExecRoutemap(RTP_MATCH_S *pstRtpMatch, MATCH_RESULTS_S *pstRe);
/*4-3*/ULONG Rtp_DoFilterForExt(ULONG ulEntryType, ULONG ulEntryIndex, ULONG ulFilterType
                            ,RTPRTENTRY4_S *pstRt, MATCH_RESULTS_S *pstResult);

/*5-1*/ULONG Rtp_RIPProcessEndNotify(ULONG ulEntryIndex);
/*5-2*/ULONG Rtp_OSPFProcessEndNotify(ULONG ulEntryIndex);
/*5-3*/ULONG Rtp_RIPReFiltrateTrigger(ULONG ulEntryIndex, ULONG ulFilterType);
/*5-4*/ULONG Rtp_OSPFReFiltrateTrigger(ULONG ulEntryIndex, ULONG ulFilterType);

/*6-1*/ULONG  Rtp_SetDebugSwitch(ULONG ulDebugFlag);
/*6-2*/ULONG  Rtp_GetDebugSwitch(ULONG* pulDebugFlag);
/*6-3*/VOID Rtp_DebugGetMap(ULONG ulResult, ULONG ulEntryType, ULONG ulEntryIndex
                                  , ULONG ulFilterType, CHAR *pMapName);
/*6-4*/VOID Rtp_DebugExecMap(ULONG ulResult, RTP_MATCH_S *pstRtpMatch, MATCH_RESULTS_S *pstResult);
/*6-5*/VOID Rtp_DebugRefiltrate(ULONG ulEntryType, ULONG ulEntryIndex, ULONG ulFilterType);


/*7-1*/ULONG  Rtp_InitTableVisitIndex(LONG *plCurTblIndex);
/*7-2*/ULONG  Rtp_GetMapEntry(LONG *plCurTblIndex, RTP_MAPBASIC_S *pstMap);
/*7-3*/ULONG  Rtp_GetMapRuleEntry(LONG *plCurTblIndex, RTP_MAPNODE_S *pstMapRule
        , CHAR *pcMapName);
/*7-4*/ULONG  Rtp_GetIpPrefixEntry(LONG *plCurTblIndex, RTP_IPPREFIXBASIC_S *pstPrefix);
/*7-5*/ULONG  Rtp_GetIpPrefixRuleEntry(LONG *plCurTblIndex
    , RTP_IPPREFIX_NODE_S *pstPrefixRule , CHAR *pcIpPrefixName);
/*7-6*/ULONG  Rtp_GetBindEntry(LONG *plCurTblIndex, RTP_MAPBIND_NODE_S *pstBindNode);

/*8-1*/VOID  Rtp_ShowDebugSwitch();
/*8-2*/VOID Rtp_ShowMapBrief();
/*8-3*/VOID Rtp_ShowMapByName(CHAR *pcName);
/*8-4*/VOID Rtp_ShowIpPrefixBrief();
/*8-5*/VOID Rtp_ShowIpPrefixByName(CHAR *pcName);
/*8-6*/VOID  Rtp_ShowMapBind();
/*8-7*/VOID  Rtp_ShowMapBindByMap(CHAR *pcName);
/*8-8*/VOID  Rtp_ShowMapBindByEntryType(ULONG ulEntryType, ULONG ulEntryIndex);

/*9-1*/ULONG Rtp_MatchACLByIP (ULONG ulACLNumber, ULONG ulAddr, ULONG ulMaskLen);
/*9-2*/ULONG Rtp_ExecPrefix(CHAR *pcPrefixName,ULONG ulIpAddr,ULONG ulMaskLen);

/*10-1*/RTP_MAP_S *Rtp_FindRtpMapByName(CHAR *pcName);
/*10-2*/RTP_MAP_S *Rtp_NewRtpMap();
/*10-3*/RTP_IPPREFIX_S *Rtp_FindIpPrefixByName(CHAR *pcName);
/*10-4*/RTP_IPPREFIX_S *Rtp_NewIpPrefix();
/*10-5*/LONG Rtp_CheckPrefix(RTP_IPPREFIX_NODE_S *pstNodeCur,ULONG ulIpAddr,ULONG ulMaskLen);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ROUTE_POLICY_H_ */

