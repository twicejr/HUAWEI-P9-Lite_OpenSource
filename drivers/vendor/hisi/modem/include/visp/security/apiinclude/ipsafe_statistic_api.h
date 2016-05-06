/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsafe_statistic_api.h
*
*  Project Code: DOPRA VISP V200R003C01 NAT
*  Module Name: Statistics Functionality
*  Date Created: 2010
*        Author: Vinay Gudur
*   Description: Statistics functions Interfaces
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-11    Vinay Gudur 71924         Initial version
*
*******************************************************************************/

#ifndef __IPSAFE_STATISTIC_API_H__
#define __IPSAFE_STATISTIC_API_H__

#ifdef  __cplusplus
    extern "C"{
#endif


#define ALG_UNOWN_PROTOCOL 1         /* Number of Unknown Protocols = 1 */

#define ALG_KNOWN_PROTOCOL 255       /* Maximum Number of Protocols */

#define ALG_UNKNOWN_PROTOCL_ID 255   /* Unknown Protocol Id */

#define ALG_MAX_PROTOCOLS (ALG_KNOWN_PROTOCOL + ALG_UNOWN_PROTOCOL)  /* Total Number of Protocols */

#define VCPU_MAX_NUM 32   

#define NAT_STAT_FAIL NAT_FAILED       /* NAT Failure Macro */

#define IPSAFE_FLOWSTAT_SWITCH_OFF 0    /*Flow statistics will be disabled.*/
#define IPSAFE_FLOWSTAT_SWITCH_ON 1     /*Enable flow statistics.*/

#define IPSAFE_FLOWSTAT_VRF_ALL        0xFFFFFFFF   /*Wild card vrf value*/

#define IPSAFE_FLOWSTAT_PROTO_ALL      0xFFFFFFFF /*Wild card protocol number*/

#define IPSAFE_FLOWSTAT_IP_ALL 0        /*any source ip*/

#define IPSAFE_FLOWSTAT_PORT_ALL 0  /*for any port number.*/     


/*STRUCT< Common statistics structure for all modules of NAT>*/
typedef struct tagNATCompleteStatistics
{
    UINT64 u64InDropPackets;  /*Number of Inbound packets which are dropped */
    UINT64 u64InPassPackets;  /*Number of Inbound packets which are passed */
    UINT64 u64InErrPackets;   /*Number of Inbound packets which are found to be error packets */
    UINT64 u64OutDropPackets; /*Number of Outbound packets which are dropped */
    UINT64 u64OutPassPackets; /*Number of Outbound packets which are passed */
    UINT64 u64OutErrPackets;  /*Number of Outbound packets which are found to be error packets */

} NAT_GLOB_STATISTIC_S;



/*ERRORCODE< Error codes in Statistics > */
enum enumNatStat
{
    NAT_STAT_SUCCESS,
    NAT_STAT_BEGIN_RET_CODE = IPSAFE_STAT_BEGIN_RET_CODE, /*<16000> Beginning of stat module error and 
                                                                        return code.*/
    NAT_STAT_INIT_ERR_ALLOC_MANUAL_STAT,                /*<16001> Failed to allocate memory in statistics init for manual 
                                                          stat variable*/
    NAT_STAT_INIT_ERR_ALLOC_ALG_MANUAL_STAT,            /*<16002> Failed to allocate memory in statistics init for manual 
                                                          alg stat variable*/
    NAT_STAT_INIT_ERR_ALLOC_ALG_AUTO_STAT,              /*<16003> Failed to allocate memory in statistics init for auto alg 
                                                          stat variable*/
    NAT_STAT_CLEAR_AUTO_STAT_ERR_NULL_POINTER,          /*<16004> Failed to Clear Auto Statistics*/
    NAT_STAT_CLEAR_MANUAL_STAT_ERR_NULL_POINTER,        /*<16005> Failed to Clear manual statistics*/

    IPSAFE_FLOWSTAT_INIT_ERR_MAX_FLOWSTAT_VAR_NULL,         /* The global max flow stat number variable is NULL*/

    IPSAFE_FLOWSTAT_INIT_ERR_ALLOC_FLOWSTAT_INFO,  /*<16006> Failed to allocate memory for flowstat information in 
                                                     FlowStatInit ()*/

    IPSAFE_FLOWSTAT_INIT_ERR_ADDNAME_FLOWSTAT_INFO, /*<16007> Failed to add name to the shared memory database*/

    IPSAFE_FLOWSTAT_INIT_ERR_ALLOC_FLOWSTAT_RULE,   /*<16008> Failed to allocate memory for flowstat rule in 
                                                      FlowStatInit ()*/

    IPSAFE_FLOWSTAT_INIT_ERR_ADDNAME_FLOWSTAT_RULE, /*<16009> Failed to add name to the shared memory database*/

    IPSAFE_FLOWSTAT_INIT_ERR_ALLOC_MANUAL_FLOWSTAT, /*<16010> Failed to allocate memory for manual statistics in 
                                                      flowstat initialization*/

    IPSAFE_FLOWSTAT_INIT_ERR_ADDNAME_MANUAL_FLOWSTAT, /*<16011> Failed to add name to the shared memory database*/
    
    IPSAFE_FLOWSTAT_INIT_ERR_ALLOC_AUTO_FLOWSTAT, /*<16012> Failed to allocate memory for manual stat in flowstat 
                                                    initialization*/

    IPSAFE_FLOWSTAT_INIT_ERR_ADDNAME_AUTO_FLOWSTAT, /*<16013> Failed to add name to the shared memory database*/

    IPSAFE_FLOWSTAT_SETSWITCH_ERR_SHAREVAR_FLOWSTAT_INFO_NULL,  /*<16014> The global Flowstat_Info variable is null*/

    IPSAFE_FLOWSTAT_SETSWITCH_ERR_FLOWSTATSWITCH_INVALID,   /*<16015> The value provided to set flowstat switch is 
                                                            incorrect*/

    IPSAFE_FLOWSTAT_GETSWITCH_ERR_SHAREVAR_FLOWSTAT_INFO_NULL,  /*<16016> The global Flowstat_Info variable is null*/

    IPSAFE_FLOWSTAT_GETSWITCH_ERR_FLOWSTAT_SWITCH_PTR_NULL, /*<16017> The pointer provided to get the value of flow 
                                                              stat switch is null*/

    IPSAFE_FLOWSTAT_GETRULENUM_ERR_SHAREVAR_FLOWSTAT_INFO_NULL, /*<16018> The global Flowstat_Info variable is null*/

    IPSAFE_FLOWSTAT_GETRULENUM_ERR_RULENUM_PTR_NULL,  /*<16019> The pointer provided to get the value of flow stat rule 
                                                        is null*/

    IPSAFE_FLOWSTAT_CONFIG_RULE_ERR_INPUT_PARA_NULL,  /*<16020> While adding or deleting a rule, the input parameter 
                                                        (rule) was null*/

    IPSAFE_FLOWSTAT_CONFIG_RULE_ERR_INVALID_VRF_INDEX,  /*<16021> The vrf index provided to configure a rule is 
                                                         invalid*/

    IPSAFE_FLOWSTAT_CONFIG_RULE_ERR_INVALID_PROTOCOL_NUM,  /*<16022> The protocol number provided in the rule is 
                                                            invalid */

    IPSAFE_FLOWSTAT_CONFIG_RULE_ERR_INVALID_OPERTYPE,  /*<16023> The opertype passed to the API is invalid.*/

    IPSAFE_FLOWSTAT_DELALL_ERR_SHAREVAR_NULL,  /*<16024> Either the global flowstat_info variable or the flowstat_rule 
                                                 variable is null */

    IPSAFE_FLOWSTAT_ADDRULE_ERR_SHAREVAR_NULL,  /*<16025> Either the global flowstat_info variable or the flowstat_rule 
                                                 variable is null */

    IPSAFE_FLOWSTAT_ADDRULE_TCP_UDP_RULE_ALREADY_EXISTS,  /*<16026> The TCP/UDP rule currently being added already 
                                                           exists.*/

    IPSAFE_FLOWSTAT_ADDRULE_RULE_ALREADY_EXISTS,        /*<16027> The rule currently being added already exists.*/

    IPSAFE_FLOWSTAT_ADDRULE_ERR_EXCEEDED_MAX_FLOWNUM,  /*<16028> Addition of a rule failed because maximum number is of 
                                                        rules have been added */

    IPSAFE_FLOWSTAT_ADDRULE_ERR_NO_FREENODE,  /*<16029> While adding a rule, no node is free. */

    IPSAFE_FLOWSTAT_ADDRULE_ERR_INVALID_FLOWID,  /*<16030> The flow ID for the new rule that is being added is 
                                                  invalid */

    IPSAFE_FLOWSTAT_DELRULE_ERR_SHAREVAR_NULL,  /*<16031> Either the global flowstat_info variable or the flowstat_rule 
                                                 variable is null */

    IPSAFE_FLOWSTAT_DELRULE_NO_RULE_PRESENT,  /*<16032> No rule is configured, so cannot delete any.*/

    IPSAFE_FLOWSTAT_DELRULE_RULE_NOT_PRESENT,  /*<16033> The values for the rule to be deleted donot match with rule*/

    IPSAFE_FLOWSTAT_GET_ALLINFO_ERR_INPUT_PTR_NULL,  /*<16034> The input pointer to get all the information is null*/

    IPSAFE_FLOWSTAT_FILLPKTCONTEXT_ERR_6KEY_MATCHFLOW_EXCEEDMAX, /*<16035> The TCP packet matches a rule but  the rule 
                                            number exceeds its maximum value*/

    IPSAFE_FLOWSTAT_FILLPKTCONTEXT_ERR_4KEY_MATCHFLOW_EXCEEDMAX, /*<16036> The packet matches a rule but  the rule 
                                            number exceeds its maximum value. This is not a TCP packet.*/

    IPSAFE_FLOWSTAT_CLEARALL_ERR_MANUAL_SHAREVAR_NULL,  /*<16037> The global manual flow stat variable is NULL*/

    IPSAFE_FLOWSTAT_CLEARALL_ERR_AUTO_SHAREVAR_NULL, /*<16038> The global variable for auto flow statistics is NULL*/

    IPSAFE_FLOWSTAT_CONFIG_RULE_ERR_VCPU_NOT_INIT,       /*<16039> VCPU has not been initialized while configuring the 
                                                         rule.*/

    IPSAFE_FLOWSTAT_FILLPKTCONTEXT_ERR_INVAILD_PKT,      /*<16040>Either the packet context is null or the protocol is null*/

    NAT_STAT_MAKE_MANUAL_FOR_CPU_STAT_NOT_INIT,     /*<16041>Statistics is not initialized */
    NAT_STAT_MAKE_MANUAL_FOR_CPU_INPUT_NULL,       /*<16042>Input Parameter is NULL */
    NAT_STAT_MAKE_MANUAL_FOR_VRF_INPUT_NULL,       /*<16043>Inpur paramener is NULL*/
    NAT_STAT_MAKE_MANUAL_FOR_VRF_STAT_NOT_INIT,    /*<16044>Statistics is not initialized */
    NAT_STAT_MAKE_MANUAL_INPUT_NULL,               /*<16045>Input Parameter is NULL*/
    NAT_STAT_MAKE_MANUAL_STAT_NOT_INIT,            /*<16045>Statistics is not initialized */ 
    IPSAFE_FLOWSTAT_GET_FLOW_STAT_ALL_ERR_VCPU_NOT_INIT, /*<16046>VCPU is not initialized  */
    NAT_STAT_MAKE_MANUAL_FOR_CPU_INVALID_VCPUNUM    /*<16047>VCPU num is invalid*/
    
};

/*ENUM < This enumeration defines the protocols and protocol ids for statistics.>*/
typedef enum enumALG_STAT_Protocols
{
    NAT_STAT_ALG_ICMP  = 0x01,                      /*Packets dropped or passed are of the type ICMP*/

    NAT_STAT_ALG_FTP_DATA,                          /*Packets dropped or passed are of F*P Data Connection*/

    NAT_STAT_ALG_FTP_CNTRL,                         /*Packets dropped or passed are of F*P Control Connection*/

    NAT_STAT_ALG_SMTP,                              /*Packets dropped or passed are of SMTP*/

    NAT_STAT_ALG_DNS,                               /*Packets dropped or passed are of DNS*/

    NAT_STAT_ALG_HTTP,                              /*Packets dropped or passed are of HTTP*/    

    NAT_STAT_ALG_RTSP,                              /*Packets dropped or passed are of RTSP*/

    NAT_STAT_ALG_MSN,                              /*Packets dropped or passed are of MSN*/
    /* TCP and UDP classification is done when NAT is unaware of the type of ALG protocol */
    NAT_STAT_UNKNOWN_ALG_TYPE_UDP,  /*If the packet is UDP but its ALG is not known to NAT, this could be a valid normal UDP packet*/

    NAT_STAT_UNKNOWN_ALG_TYPE_TCP,   /*If the packet is TCP but its ALG is not known to NAT, this could be a valid normal TCP packet*/

    NAT_STAT_UNKNOWN_ALG_PROTOCOL,   /*When the packet context is NULL, the packet cannot be classified as 
                                            TCP, UDP, ICMP and for any ALG protocol also.*/
    NAT_STAT_UNKNOWN_IPHEADER_PROTO_ID = ALG_UNKNOWN_PROTOCL_ID
    
}ALG_STAT_PROTOCOLS_ID_E;



/*STRUCT< Union to store the type of address. It can either be IPv4 or IPv6.>*/
typedef union unIPSAFE_IPADDR
{
    UINT32 u32IPv4;       /* IPv4 port number*/
    UINT32 u32IPv6[4];    /* If it is a Ipv6 IP number, this union will automatically take care without changing any 
                             code*/
}IPSAFE_IPADDR_UN;

/*STRUCT< This enum stores the operation type of the flow statistics rules.>*/
typedef enum enumIpsafeFlowStatisticRuleOperType
{ 
    IPSAFE_FLOWSTATISTIC_ADD,         /*Use this enum to specify operation type when adding a rule.*/
    IPSAFE_FLOWSTATISTIC_DEL,         /*Use this enum to specify operation type when deleting a rule.*/
    IPSAFE_FLOWSTATISTIC_DELALL,      /*Use this enum to specify operation type to delete all the rules.*/
    
    IPSAFE_FLOWSTATISTIC_OPER_MAX     /*Maximum value for flowstatistic rule operations.*/
}IPSAFE_FLOWSTATISTIC_RULE_OPER_TYPE_E;



/*STRUCT< Common statistics structure for storing VCPU wise statistics>*/
typedef struct  tagNAT_Statistic
{
    UINT32 u32InDropPackets[VCPU_MAX_NUM];   /*Number of Inbound packets which are dropped */
    UINT32 u32InPassPackets[VCPU_MAX_NUM];   /*Number of Inbound packets which are passed */
    UINT32 u32InErrPackets[VCPU_MAX_NUM];    /*Number of Inbound packets which are found to be error packets */
    UINT32 u32OutDropPackets[VCPU_MAX_NUM];  /*Number of Outbound packets which are dropped */
    UINT32 u32OutPassPackets[VCPU_MAX_NUM];  /*Number of Outbound packets which are passed */
    UINT32 u32OutErrPackets[VCPU_MAX_NUM];   /*Number of Outbound packets which are found to be error packets */
} NAT_STATISTIC_S;



/*STRUCT< Common statistics structure for ALG>*/
/* The last one will be have the statistics for unknown protocols */
typedef struct  tagNATALG_Statistic
{
    UINT32 u32InDropPackets[ALG_MAX_PROTOCOLS];   /*Number of Inbound packets which are dropped */
    UINT32 u32InPassPackets[ALG_MAX_PROTOCOLS];   /*Number of Inbound packets which are passed */
    UINT32 u32InErrPackets[ALG_MAX_PROTOCOLS];    /*Number of Inbound packets which are found to be error packets */
    UINT32 u32OutDropPackets[ALG_MAX_PROTOCOLS];  /*Number of Outbound packets which are dropped */
    UINT32 u32OutPassPackets[ALG_MAX_PROTOCOLS];  /*Number of Outbound packets which are passed */
    UINT32 u32OutErrPackets[ALG_MAX_PROTOCOLS];   /*Number of Outbound packets which are found to be error packets */

} NAT_ALG_STATISTIC_S;


/*STRUCT< Structure that defines Statistical rules and also indicates whether the rule is in use or not.
This structure is used by NAT internally while searching for rules and also to return the global shared
variable's value by an exposed API>*/
typedef struct tagIPSAFE_StatRuleInfo
{
    UINT32 u32FlowStatId;        /* Represents the flow statistics ID in host sequence and used only while 
                                    configuration. Starts from 0 to the maximum value for the rule that is configured.*/
    UINT32 u32VrfIndex;          /* VRF index, host order */
    IPSAFE_IPADDR_UN unSrcIp;    /* Source IP, network order */
    IPSAFE_IPADDR_UN unDstIp;    /* Destination IP, network order */
    UINT32 u32ProNo;             /* Protocol number */
    UINT16 u16SrcPort;           /* Source port number, network order */
    UINT16 u16DstPort;           /* Destination port number, network order */
    UINT8  u8IsUsed;             /* This parameter is used to indicate if the flow statistics rule entry exists 
                                    and whether it is used */
    UINT8 Padding[3];            /* Padding */   
                                    
}IPSAFE_STAT_RULE_INFO_S;


/*STRUCT< This structure stores the total number of rules configured and also whether the flow statistics switch 
is on or off. >*/
typedef struct tagIPSAFE_FlowStatisticInfo
{
    UINT32 u32FlowStatNum;      /* Number of current flow statistics*/
    UINT32 u32FlowStatSwitch;   /* This switch determines whether to update flow statistics or not
                                   0 - Flow Statistics is disabled
                                   1 - Flow statistics is enabled */
} IPSAFE_FLOW_STATISTIC_INFO_S;




/*STRUCT< Flow statistics rule structure. While adding, deleting and searching for a specific rule,
the user should make use of this structure.>*/
typedef struct  tagIPSAFE_FlowStatisticRule
{
    UINT32 u32FlowStatId;     /* Flow statistics ID, can be filled up as 0 while deleting.
                                 the beginning of statistics ID is from 0 */
    UINT32 u32VrfIndex;       /* VRF index, host order */
    IPSAFE_IPADDR_UN unSrcIp; /* Source IP, input the value in host order */
    IPSAFE_IPADDR_UN unDstIp; /* Destination IP, input the value in host order*/
    UINT32 u32ProNo;          /* Protocol number, range [0,255] */
    UINT16 u16SrcPort;        /* Source port number, input the value in host order*/
    UINT16 u16DstPort;        /* Destination port number, input the value in host order*/
}IPSAFE_FLOWSTATISTIC_RULE_S;


/*STRUCT< Flow statistics structure that will have pointers to all flowstat global variables.>*/
typedef struct tagIpsafe_FLOWSTATISTIC_ALLINFO
{
    UINT32 u32IpsafeFlowStatMaxNum;      
    IPSAFE_FLOW_STATISTIC_INFO_S *pstIpsafeFlowStatInfo;        
    IPSAFE_STAT_RULE_INFO_S           *pstIpsafeFlowStatRule;        
    NAT_GLOB_STATISTIC_S           *pstIpsafeFlowStatManualInfo;  
    UINT32                          *pu32IpsafeFlowStatAutolInfo;  
}IPSAFE_FLOWSTATISTIC_ALLINFO_S;

/*******************************************************************************
*    Func Name: NAT_ShowAutoStatistic
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function displays the statistics of the dropped packets at 
*               different levels of sub-modules in NAT.
*  Description: This functions displays the number of packets which are dropped
*               in the various sub modules of NAT, NAT_ALG.
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: None
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern VOID NAT_ShowAutoStatistic(VOID);




/*******************************************************************************
*    Func Name: NAT_ClearAutoStatistic
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function clears the Auto Statistics Information.
*  Description: The user should call this function to reset all the statistics 
*               information.
*        Input: 
*       Output: 
*       Return: Success : NAT_STAT_SUCCESS
*               Failure : NAT_STAT_CLEAR_AUTO_STAT_ERR_NULL_POINTER - Statistics 
*                           Initialization failed.
*      Caution: None
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_ClearAutoStatistic(VOID);


/*******************************************************************************
*    Func Name: NAT_ClearManualStatistic
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function clears Manual Statistics Information
*  Description: The user should call this function to reset all the manual statistics 
*               information.
*        Input: 
*       Output: 
*       Return: Success: NAT_STAT_SUCCESS
*               Failure : NAT_STAT_CLEAR_MANUAL_STAT_ERR_NULL_POINTER - Statistics 
*                           Initialization failed
*                         
*      Caution: None
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_ClearManualStatistic(VOID);


/*******************************************************************************
*    Func Name: NAT_ShowAllStatistic
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function displays all the Statistics Information
*  Description: The user should call this function to display all the Statistics Information
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: None
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern VOID NAT_ShowAllStatistic(VOID);


/*******************************************************************************
*    Func Name: NAT_ShowManualStatistic
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function displays the Manual Statistics Information
*  Description: The user should call this function to display the Manual Statistics Information
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: None
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern VOID NAT_ShowManualStatistic(VOID);


/*******************************************************************************
*    Func Name: NAT_ShowManualStatisticByVCPU
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function displays the Manual Statistics for a particular VCPU.
*  Description: The user should call this function to display the Manual Statistics
*               for a particular VCPU.
*        Input: UINT32 u32VCPUID: VCPU ID <The range is 0 - VCPU_MAX_NUM>
*       Output: 
*       Return: VOID
*      Caution: None
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern VOID NAT_ShowManualStatisticByVCPU(UINT32 u32VCPUID);


/*******************************************************************************
*    Func Name: NAT_ClearAllStatistic
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function clears all the statistics information.
*  Description: The user should call this function to reset all the statistics information.
*        Input: 
*       Output: 
*       Return: Success: NAT_STAT_SUCCESS
*               Failure : NAT_STAT_CLEAR_AUTO_STAT_ERR_NULL_POINTER - Statistics Initialization
*                           failed.
*                         NAT_STAT_CLEAR_MANUAL_STAT_ERR_NULL_POINTER - Statistics Initializations
                            failed.
*      Caution: None
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_ClearAllStatistic(VOID);


/*******************************************************************************
*    Func Name: NAT_ShowManualStatisticByVRF
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function displays the Manual Statistics information for a 
*               particular VRF.
*  Description: The user should call this function to displays the Manual Statistics 
*               information for a particular VRF.
*        Input: UINT16 u16VRF: VRF Index <The range is 0 - (VRF_MAX_NUM-1)>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern VOID NAT_ShowManualStatisticByVRF(UINT16 u16VRF);


/*******************************************************************************
*    Func Name: NAT_MakeManualStatistic
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function gets the statistics updated in the 
*               NAT_GLOB_STATISTIC_S structure.
*  Description: The user can call this function by passing a pointer to 
*               NAT_GLOB_STATISTIC_S structure to get the detailed statistics.
*        Input: NAT_GLOB_STATISTIC_S *pstStatistic: Pointer to NAT_GLOB_STATISTIC_S <>
*       Output: NAT_GLOB_STATISTIC_S *pstStatistic: Updated structure containing 
*               statistics information.<>
*       Return: Success - NAT_STAT_SUCCESS
*               Failure - NAT_STAT_MAKE_MANUAL_INPUT_NULL - NULL Input
*                         NAT_STAT_MAKE_MANUAL_STAT_NOT_INIT - Statistics Not Initialized
*      Caution: User has to allocate the structure memory and pass it to the 
*               function.
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_MakeManualStatistic(NAT_GLOB_STATISTIC_S *pstStatistic);



/*******************************************************************************
*    Func Name: NAT_MakeManualStatisticForVRF
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function updates the statistics information in the input 
*               structure for a particular VRF.
*  Description: The user can update the statistics information corresponding to a 
*               particular VRF using this function.
*        Input: NAT_GLOB_STATISTIC_S *pstStatistic: Pointer to the structure 
*               NAT_GLOB_STATISTIC_S. <>
*               UINT16 u16VRF: VRF Index <The range is 0 - (VRF_MAX_NUM-1)>
*       Output: NAT_GLOB_STATISTIC_S pstStatistic : Updated statistics information. <>
*       Return: Success - NAT_STAT_SUCCESS
*               Failure - NAT_STAT_MAKE_MANUAL_FOR_VRF_INPUT_NULL - NULL Input
*                         NAT_STAT_MAKE_MANUAL_FOR_VRF_STAT_NOT_INIT - Statistics Not Initialized

*      Caution: The user should allocate memory for pstStatistic.
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_MakeManualStatisticForVRF(NAT_GLOB_STATISTIC_S *pstStatistic, UINT16 u16VRF);


/*******************************************************************************
*    Func Name: NAT_MakeManualStatisticForVCPU
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function is used to build the Manual Statistics CPU wise 
*               information into the input structure.
*  Description: The user should pass the NAT_GLOB_STATISTIC_S pointer along with VCPU
*               Number in this function to update the manual statistics information.
*        Input: NAT_GLOB_STATISTIC_S *pstStatistic: Pointer to the structure NAT_GLOB_STATISTIC_S. <>
*               UINT32 u32VCPUID: Number of VCPUs <The range is 0-(VCPU_MAX_NUM -1)>
*       Output: NAT_GLOB_STATISTIC_S pstStatistic: It will contain the complete statistics 
*               information. <>
*       Return: Success - NAT_STAT_SUCCESS
*               Failure - NAT_STAT_MAKE_MANUAL_FOR_CPU_INPUT_NULL - NULL Input
*                         NAT_STAT_MAKE_MANUAL_FOR_CPU_STAT_NOT_INIT - Statistics Not Initialized
*      Caution: The user should allocate memory for pstStatistic.
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_MakeManualStatisticForVCPU(NAT_GLOB_STATISTIC_S *pstStatistic, UINT32 u32VCPUID);

/*******************************************************************************
*    Func Name: NAT_ShowManualStatisticByALG
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function displays the manual statistics using the ALG ID.
*  Description: This function is used to display the manual statistics using the 
*               ALG protocol ID.
*        Input: UINT32 u32algProtoID: ALG Protocol ID <ALG_STAT_PROTOCOLS_ID_E>
*       Output: 
*       Return: VOID
*      Caution: None
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern VOID NAT_ShowManualStatisticByALG(UINT32 u32algProtoID);


/*******************************************************************************
*    Func Name: NAT_ShowManualALGStatistic
* Date Created: 2010-04-05
*       Author: Vinay Gudur 71924
*      Purpose: This function displays all the ALG statistics Information 
*  Description: The user should call this function to displays all the ALG 
*               statistics information 
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: None
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-05   Vinay Gudur 71924       Create the first version.
*
*******************************************************************************/
extern VOID NAT_ShowManualALGStatistic(VOID);



extern UINT32 IPSAFE_SetFlowStatisticSwitch(UINT32 u32FlowStatSwitch);


extern UINT32 IPSAFE_GetFlowStatisticSwitch(UINT32 *pu32FlowStatSwitch);




UINT32 IPSAFE_ClearAllFlowStatistic(VOID);



UINT32 IPSAFE_GetFlowStatisticRuleNum(UINT32 *pu32FlowStatRuleNum);




UINT32 IPSAFE_ConfigFlowStatisticRule(UINT32 u32OperType,IPSAFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule);





UINT32 IPSAFE_GetFlowStatisticAllInfo(IPSAFE_FLOWSTATISTIC_ALLINFO_S *pstFlowStatAllInfo);



VOID IPSAFE_ShowFlowStatisticSwitch(VOID);




VOID IPSAFE_ShowAllFlowStatisticRule(VOID);



VOID IPSAFE_ShowFlowStatisticRuleByFlowId(UINT32 u32FlowId);


VOID IPSAFE_ShowAllFlowStatistic(VOID);



VOID IPSAFE_ShowFlowStatisticByFlowRule(IPSAFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule);



VOID IPSAFE_ShowFlowStatisticByFlowId(UINT32 u32FlowId);





#ifdef  __cplusplus
}
#endif

#endif /*__IPSAFE_STATISTIC_API_H__*/


