

#ifndef _NAT_API_H_
#define _NAT_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif


#define ACL_MAX_GROUP 255  /*Maximum number of ACL groups that the user can configure*/

/*STRUCT< NAT Rule structure > */
typedef struct tagNatRule
{
    UINT32 u32AddrPoolIndex; /*Address pool index*/

    UINT16 u16ACLNumber[ACL_MAX_GROUP]; /*User can configure number of ACL groups here*/
    UINT8  u8ACLCount;         /*ACL Count*/
    UINT8  u8Padding;          /*Padding*/
    
    INTF_HANDLE  intfHandle;    /*Interface handle*/
}NAT_RULE_S;

/*STRUCT< Structure for the getting RULE parameters >*/

typedef struct tagGetRule
{
    UINT32 u32ActvSessnCount; /*Number of active sessions*/
    UINT32 u32AddrPoolIndex;  /*Address pool index*/
    UINT32 u32StartAddress;   /*Start address*/
    UINT32 u32EndAddress;     /*End address*/
    UINT16 u16StartPort;      /*Start Port Number*/
    UINT16 u16EndPort;        /*End Port Number*/

    UINT16 u16ACLNumber[ACL_MAX_GROUP]; /*List of ACL groups*/
    UINT8  u8ACLCount;                  /*Number of ACL groups */
    UINT8  u8Padding;                   /*Byte Alignment*/
    
    INTF_HANDLE  intfHandle;            /*Interface Handle */
}GET_RULE_S;

/*STRUCT< Structure for getting the ALG parameters.>*/
typedef struct tagALGStatus
{
    UINT16 u16Port;               /*Port of the ALG. For example, for F*P it is 21*/
    UINT8  u8Status;              /*Enabled or Disabled*/
}ALG_STATUS_S;

/*STRUCT< Structure that will be used to get the List of ALGs.>*/
typedef struct tagGetAlg
{
    UINT8 u8AlgNames[20][20];
}GET_ALG_S;
/*STRUCT< Structure used for updating FPGA session information > */
typedef struct tagNat_Update_Session
{
    UINT32 u32Index;         /* NAT session index */
    UINT32 u32FatherIndex;   /* Parent index */
    UINT32 u32VPNIndex;      /* VPN index */
    UINT32 u32LocalIP;       /* Local IP, Network order */
    UINT32 u32GlobalIP;      /* Global IP, Network order */
    UINT32 u32DstIp;         /* Destination IP, Network order */
    UINT16 u16LocalPort;     /* Local port, Network order */
    UINT16 u16GlobalPort;    /* Global port, Network order */
    UINT16 u16DstPort;       /* Destination port, Network order */
    UINT8 u8Protocol;        /* Protocol number */
    UINT8 u8ALGFlag;         /* ALG Flag */
    UINT32 u32AppProtocolID; /* ALG protocol ID */
    UINT8 u8ConeMode;        /* Cone mode, IPSAFE_FULL_CONE or IPSAFE_SYMMETRIC_CONE */
    UINT8 u8Pad[3];          /* padding */
}NAT_UPDATE_SESSION_S;

/*STRUCT<Structure used by FPGA to notify NAT structure information > */
typedef struct tagNat_Session_Change
{
    UINT32 u32Index;       /*NAT session index number.*/
}NAT_SESSION_CHANGE_S;

/*STRUCT< NAT ALG MODE structure > */
typedef struct tagNatAlgMode
{
    UINT8 u8TCPMode;  /*Cone mode operation for TCP*/
    UINT8 u8UDPMode;  /*Cone mode operation for UDP*/
    UINT8 u8ICMPMode; /*Cone mode operation for ICMP*/
    UINT8 u8FtpMode;  /*Cone mode operation for F*P*/
    UINT8 u8MsnMode;  /*Cone mode operation for MSN*/
    UINT8 u8DnsMode;  /*Cone mode operation for DNS*/
    UINT8 u8HttpMode; /*Cone mode operation for HTTP*/
    UINT8 u8RtspMode; /*Cone mode operation for RTSP*/
    UINT8 u8SmtpMode; /*Cone mode operation for SMTP*/
    UINT8 u8Pad[2];
}NAT_ALG_MODE;

/*ERRORCODE< Error codes in ALG Frame > */
enum enumNAT_ALG_ErrCode
{
    NAT_ALG_SUCCESS,                                    /*<0> On success*/
    NAT_ALG_BEGIN_CODE = IPSAFE_ALG_BEGIN_RET_CODE,     /*<15000> Beginning of ALG error code*/
    NAT_ALG_INIT_ERR_ALLOC_APP_PRO_OVER_TCP,            /*<15001> ALG TCP protocol table memory allocation failure */
    NAT_ALG_INIT_ERR_ALLOC_APP_PRO_OVER_UDP,            /*<15002> ALG UDP protocol table memory allocation failure */
    NAT_ALG_INIT_ERR_ALLOC_APP_PRO_OVER_ICMP,           /*<15003> ALG ICMP protocol table memory allocation failure */
    NAT_ALG_INIT_ERR_ALLOC_ALG_PROTOCOL_POOL,           /*<15004> ALG protocol table memory initialization failure */
    NAT_ALG_REG_AP_PRO_ERR_ALLOC_PRO_HASH_FROM_POOL,    /*<15005> Failed to get memory from block for ALG Protocol 
                                                             registration */
    NAT_ALG_INIT_ERR_ALLOC_ALG_PROTOCOL_TIME,           /*<15006> Failed to allocate memory for ALG protocol timeout array */
    NAT_ALG_INIT_ERR_ADDNAME_ALG_PROTOCOL_TIME,         /*<15007> Failed to add protocol timeout array to name db */
    NAT_ALG_CHNG_STAT_ERR_INVALID_PROTOCOL,             /*<15008> Invalid ALG protocol number specified */
    NAT_ALG_CHNG_STAT_ERR_PRO_FUNC_NOT_DEFINED,         /*<15009> ALG Protocol status change function not defined */
    NAT_ALG_SET_PROTO_STAT_ERR_PROTOCOL_NOT_FOUND,      /*<15010> ALG protocol not found in the protocol hash table */
    NAT_ALG_REG_AP_PRO_ERR_TRANS_PROTOCOL_FAIL,         /*<15011> ALG Invalid Transport protocol, Internal failure */
    NAT_ALG_SET_PROTO_STAT_ERR_PROTO_ALREADY_ENABLED,   /*<15012> ALG Protocol already enabled */
    NAT_ALG_SET_PROTO_STAT_ERR_PROTO_ALREADY_DISABLED,  /*<15013> ALG Protocol already disabled */    
    NAT_ALG_CHK_IPPKT_INBOUND_ERR_TCP_PKT_LEN,          /*<15014> Invalid inbound TCP Packet Length specified */
    NAT_ALG_CHK_IPPKT_INBOUND_ERR_UDP_PKT_LEN,          /*<15015> Invalid inbound UDP Packet Length specified */
    NAT_ALG_CHK_IPPKT_OUTBOUND_ERR_TCP_PKT_LEN,         /*<15016> Invalid outbound TCP Packet Length specified */
    NAT_ALG_CHK_IPPKT_OUTBOUND_ERR_UDP_PKT_LEN,         /*<15017> Invalid outbound UDP Packet Length specified */
    NAT_ALG_CHK_IPPKT_INBOUND_ERR_ICMP_PKT_LEN,         /*<15018> Invalid inbound ICMP Packet Length specified */
    NAT_ALG_CHK_IPPKT_OUTBOUND_ERR_ICMP_PKT_LEN,        /*<15019> Invalid outbound ICMP Packet Length specified */
    NAT_ALG_VFY_SRV_PARA_INBOUND_ERR_INPUT_PARA_NULL,   /*<15020> Invalid input parameter to inbound ALG*/
    NAT_ALG_VFY_SRV_PARA_OUTBOUND_ERR_INPUT_PARA_NULL,  /*<15021> Invalid input parameter to outbound ALG*/
    NAT_ALG_SET_PROTO_STAT_ERR_TRANS_PROTOCOL_FAIL,     /*<15022> ALG Invalid Transport protocol, Internal failure */
    NAT_ALG_GETALG_CHNG_STAT_ERR_PRO_FUNC_NOT_DEFINED,  /*<15023> status change function is not defined in get alg*/
    NAT_ALG_GETALGFORAll_ERR_GET_STRUCTURE_NULL,        /*<15024> structure passed to the function is NULL i.e. invalid */
    NAT_ALG_GETALGFORAll_ERR_TRNSPRT_PROTOCOL_FAIL,     /*<15025> ALG Invalid Transport protocol, Internal failure in GetALGAll */
    NAT_ALG_GETALG_STATUS_ERR_NULL_POINTER,             /*<15026> NULL structure pointer is passed as Input*/
    NAT_ALG_GETALG_CHNG_STAT_ERR_INVALID_PROTOCOL,      /*<15027> ALG Value Entered is Out of Range*/
    NAT_ALG_GETALG_STATUS_ERR_VCPU_NOINIT,              /*<15028> VCPU is not Initialized*/
    NAT_ALG_GETALLSUPPORTED_ALG_ERR_NULL_POINTER,      /*<15029> NULL Input in get all supported alg*/
    NAT_ALG_GETALLENABLE_ALG_ERR_NULL_POINTER,         /*<15030> NULL Input in get all Enable alg*/
    NAT_ALG_INIT_ERR_FTP_INIT_FAIL,                     /*<15031> Failed to initialize F*P ALG */
    NAT_ALG_INIT_ERR_ICMP_INIT_FAIL,                    /*<15032> Failed to initialize ICMP ALG */
    NAT_ALG_INIT_ERR_DNS_INIT_FAIL,                     /*<15033> Failed to initialize DNS ALG */
    NAT_ALG_INIT_ERR_HTTP_INIT_FAIL,                    /*<15034> Failed to initialize HTTP ALG */
    NAT_ALG_INIT_ERR_RTSP_INIT_FAIL,                    /*<15035> Failed to initialize RTSP ALG */
    NAT_ALG_INIT_ERR_MSN_INIT_FAIL,                     /*<15036> Failed to initialize MSN ALG */    
    NAT_ALG_INIT_ERR_SMTP_INIT_FAIL                     /*<15037> Failed to initialize SMTP ALG */
};


/*ERRORCODE< Error codes in F*P-ALG > */
enum enumNAT_ALG_FTP_ErrCode
{
    NAT_ALG_FTP_SUCCESS,                                     /*<0> On Success*/
    NAT_ALG_FTP_BEGIN_CODE = IPSAFE_FTP_BEGIN_RET_CODE,      /*<7000> Beginning of F*P error code.*/
    
    NAT_ALG_FTP_PKTOUT_ERR_NAT_ACCESS_NULL,                  /*<7001> After identifying the packet as Port Command, 
                                                                  NatAccess was NULL*/
    NAT_ALG_FTP_PKTOUT_ERR_CREATE_NEW_SESSION,               /*<7002> Failed to create new session for Port Command 
                                                                  payload.*/
    NAT_ALG_FTP_PKTOUT_ERR_LOCALFC_DATASESSION,              /*<7003> Failed to fetch session from local FC for duplicate 
                                                                  port packets*/
    NAT_ALG_FTP_PKTOUT_ERR_CREATE_LOCAL_FC,                  /*<7004> Failed to create Local FC for New Data Session */
    NAT_ALG_FTP_PKTOUT_ERR_CREATE_GLOBAL_FC,                 /*<7005> Failed to create Global FC for New Data Session */
    NAT_ALG_FTP_PKTOUT_ERR_MEMALLOC_PROTOCOL_DATA,           /*<7006> Failed to allocate memory for Control Session's 
                                                                  protocol data*/
    NAT_ALG_FTP_PKTOUT_ERR_UNKNOWN_FTP_CMD,                  /*<7007> Unknown F*P Command detected, drop the packet.*/

    
    NAT_ALG_FTP_REPLACEFTPPORT_ERR_PORTLEN,                  /*<7008> Length of Port Command payload incorrect */
    NAT_ALG_FTP_GETPORTFRMTEXT_ERR_INVALID_COMMAND,          /*<7009> Port Command Payload is invalid*/

    NAT_ALG_FTP_PKTOUT_ERR_GLOBALFC_DATASESSION,             /*<7010> Failed to fetch Global FC for duplicate port packets*/
    

        
};

enum enumNAT_ALG_SMTP_ErrCode
{
    NAT_ALG_SMTP_SUCCESS,
    NAT_ALG_SMTP_BEGIN_CODE = IPSAFE_SMTP_BEGIN_RET_CODE,   /*<17000> Beginning of SMTP error code.*/
    NAT_ALG_SMTP_PKTOUT_ERR_ALLOC_PROTOCOL_DATA             /*<17001> Memory allocation failed for SMTP sequence number storage variable*/
};

/*ERRORCODE< Error codes in NAT > */
enum enumNatCode
{
    NAT_SUCCESS,                                        /*<0> Nat process successful */
    NAT_ERR_BEGIN_CODE = IPSAFE_NAT_BEGIN_RET_CODE,     /*<1000> Beginning of NAT error code*/
    NAT_IN_ERR_INBOUND_PKT_CONTEXT_NULL,                /*<1001> Inbound packet context is NULL*/
    NAT_IN_ERR_NO_SESSION,                              /*<1002> Session is absent for the incoming packet*/
    NAT_IN_ERR_SESSION_TIMED_OUT,                       /*<1003> The session has been timed out*/
    NAT_ADJUST_CHKSUM_ERR_UNRECOGNIZED_PROTOCOL,        /*<1004> Checksum for the packet has failed*/
    NAT_FWD_ERR_OUTBOUND_PKT_CONTEXT_NULL,              /*<1005> The outbound packet context is NULL*/
    NAT_FWD_ERR_GET_RULE_HANDLE,                        /*<1006> Failed to fetch the rule handle*/
    NAT_FWD_ERR_NO_RULE_IN_INTERFACE,                   /*<1007> No rule has been configured in the interface*/
    NAT_FWD_ERR_NO_MATCH_RULE,                          /*<1008> No rule has matched to the ACL specified by the user*/
    NAT_FWD_ERR_CREATE_NAT_SESSION,                     /*<1009> Failed to create the session*/
    NAT_DISP_ERR_GET_RULE_HANDLE,                       /*<1010> Unable to fetch rule handle for display*/
    NAT_DISP_ERR_NO_RULE_IN_INTERFACE,                  /*<1011> No rule has been configured in the interface for display*/
    NAT_DISP_ERR_INVALID_OPERTYPE,                      /*<1012> The input operation type is invalid*/
    
    
    NAT_INIT_ERR_ALLOC_GLOBLENATIFNUM,                  /*<1013> GlobalOperNum_Share memory allocation failed*/
    NAT_INIT_ERR_ALLOC_GLOBLEIPPOOLNUM,                 /*<1014> GlobalIpNum_Share memory allocation failed*/
    NAT_INIT_ERR_ADDNAME_GLOBLEIPPOOL,                  /*<1015> Error in adding name to global IP pool*/
    NAT_INIT_ERR_ALLOC_RWLock,                          /*<1016> RWLock_Share memory allocation failed*/
    NAT_INIT_ERR_ADDNAME_RWLock,                        /*<1017> Unable to add g_pstNatRWLock_Share to name db*/
    NAT_INIT_ERR_ALLOC_RULEMEM,                         /*<1018> Unable to initialize NAT address pool*/
    NAT_INIT_ERR_ALLOC_NATSESSION,                      /*<1019> Unable to initialize NAT session pool*/
    NAT_INIT_ERR_CREATE_NOPAT_IPNODE,                   /*<1020> Unable to initialize NAT IP node pool*/
    NAT_INIT_ERR_CREATE_RWLOCK,                         /*<1021> g_pstNatRWLock_Share memory RW Lock create fails*/
    NAT_PRE_CFG_INIT_ERR_ALLOC_MAXSESSIONNUM,           /*<1022> Failed to allocate global memory for MAX Nat Sessions 
                                                             Number*/
    NAT_PRE_CFG_INIT_ERR_ADDNAME_GLOBALMAXSESSION,      /*<1023> Failed to add name to the global shared memory database*/
    NAT_PRE_CFG_INIT_ERR_ALLOC_GLOBALNATACCESSCHAIN,    /*<1024> Failed to allocate global memory for Global NAT access 
                                                            chain*/
    NAT_PRE_CFG_INIT_ERR_ADDNAME_GLOBALNATACCESSCHAIN,  /*<1025> Failed to add name to the global shared memory database*/
    NAT_PRE_CFG_INIT_ERR_ALLOC_MAXVRF,                  /*<1026> Failed to allocate global memory for MAX VRF Number*/
    NAT_PRE_CFG_INIT_ERR_ADDNAME_MAXVRF,                /*<1027> Failed to add name to the global shared memory database*/
    NAT_PRE_CFG_INIT_ERR_ALLOC_CONEMODE,                /*<1028> Failed to allocate memory for the Global Cone Mode*/
    NAT_PRE_CFG_INIT_ERR_ADDNAME_GLOBALCONEMODE,        /*<1029> Failed to add name to the global shared memory database*/
    NAT_PRE_CFG_INIT_ERR_ADDNAME_GLOBALNATMODE,         /*<1030> Failed to add name to the global shared memory database*/
    NAT_PRE_CFG_INIT_ERR_ALLOC_NATMODE,                 /*<1031> Failed to allocate memory for the Global Nat Mode to be 
                                                             supported.*/
    NAT_PRE_CFG_INIT_ERR_ALLOC_ADDRPOOL,                /*<1032> Failed to allocate memory for the Global Address Pool*/
    NAT_PRE_CFG_INIT_ERR_ADDNAME_GLOBALADDRPOOL,        /*<1033> Failed to add name to the global share memory database*/
    NAT_PRE_CFG_INIT_ERR_ALLOC_ADDRPOOLARR,             /*<1034> Failed to allocate memory for the Global Address Pool 
                                                             ARRAY*/
    NAT_PRE_CFG_INIT_ERR_ALLOC_FLOW_STAT_MAX_NUM,       /*<1035> Failed to allocate memory for global flow stat maximum
                                                            number variable*/
    NAT_PRE_CFG_INIT_ERR_ADDNAME_GLOBALFLOWSTAT_MAXNUM,  /*<1036> Failed to add name to the global shared memory 
                                                            database*/
    NAT_PRE_CFG_INIT_ERR_ADDNAME_GLOBALPOOL,            /*<1037> Failed to add name to the global shared memory database*/

    NAT_CHECK_PRECFG_ERR_INVALID_MAX_VRF,               /*<1038> Maximum VRF Value entered is incorrect*/
    NAT_CHECK_PRECFG_ERR_INVALID_MODETYPE,              /*<1039> Mode type is not NAT or PAT*/
    NAT_CHECK_PRECFG_ERR_INVALID_CONEMODE,              /*<1040> Cone Mode entered is not valid*/
    NAT_CHECK_PRECFG_ERR_PRE_CFG_NULL,                  /*<1041> Pointer to Pre-Configuration structure is Null*/


    NAT_OPR_ERR_NULL_POINTER,                           /*<1042> The input rule is NULL*/
    NAT_OPR_ERR_VCPU_NOINIT,                            /*<1043> Global variables not initialized*/
    NAT_OPR_ERR_MODE_TYPE_INVALID,                      /*<1044> Invalid mode type*/
    NAT_OPR_ERR_GET_RULE_HANDLE,                        /*<1045> Failed to fetch the rule handle for rule configuration*/
    NAT_OPR_ERR_OPERTYPE_NOT_SUPPORTED,                 /*<1046> Invalid operation type*/
    NAT_ADDACCRULE_ERR_MAXIMUMRULE_LIMIT_REACHED,       /*<1047> Reached the maximum limit of 128 rules*/
    NAT_ADDACCRULE_ERR_INVALID_ADDR_POOL_INDEX,         /*<1048> Invalid Address Pool index provided in the Rule*/
    NAT_ADDACCRULE_ERR_ADDR_POOL_NOT_EXISTS,            /*<1049> Address Pool index does not exist*/
    NAT_CREATEIPQ_ERR_CREATE_NO_PAT_HASH,               /*<1050> Failed to create the hash table for storing NAT sessions*/
    NAT_CREATEIPQ_ERR_CREATE_IP_QUEUE,                  /*<1051> Failed to create IP queue*/
    NAT_CREATEIPQ_ERR_NO_PAT_GLOBALIP,                  /*<1052> Failed to fetch the memory for holding the global IP's*/
    NAT_CREATEIPQ_ERR_CREATE_NO_PAT_SPINLOCK,           /*<1053> Unable to create lock for the hash structures*/
    NAT_DELACCRULE_ERR_NO_SET_RULE,                     /*<1054> No rule set in the interface*/
    NAT_CHKRULE_ERR_ADDR_POOL_CONFICT,                  /*<1055> Desired Address pool is already in use */
    NAT_CREATENATIF_ERR_ALLOC_NAT_IF,                   /*<1056> Failed to create memory for the interface*/
    NAT_CREATENATIF_ERR_SET_RULE_HANDLE,                /*<1057> Failed to set the rule handle*/
    NAT_CREATEACCNODE_ERR_GET_ACCESS_FROM_BLK,          /*<1058> Block allocation failed*/
    NAT_REM_RULE_FRM_CHAIN_ERR_GET_INTF_ACCESS,         /*<1059> Rule to be deleted does not exist in the interface*/
    NAT_REM_RULE_FRM_GLBL_CHAIN_ERR_GLOBAL_ACCESS,      /*<1060> Rule to be deleted does not exist in the global chain of 
                                                             rules*/
    NAT_CHKPOOL_ERR_ADD_RULE_IP_CONFICT,                /*<1061> Desired IP is conflicting with the already allocated IPs*/
    NAT_SETALGTMOUT_ERR_INVALID_PROTOCOL,               /*<1062> Invaild protocol input*/
    NAT_SETALGTMOUT_ERR_SET_AGING_VCUP_INIT,            /*<1063> Set aging, but VCPU not initialized*/
    NAT_ADDADDRPOOL_ERR_VCPU_NOT_INITIALIZED,           /*<1064> Global variables not initialized*/
    NAT_ADDADDRPOOL_ERR_INVALID_ADDR_POOL_INDEX,        /*<1065> Address pool index is not valid*/
    NAT_ADDADDRPOOL_ERR_POOLALREADY_EXISTS,             /*<1066> Address pool with input index already exists*/
    NAT_ADDADDRPOOL_ERR_INVALID_IP_FORMAT,              /*<1067> Start address is greater than end address */
    NAT_ADDADDRPOOL_ERR_MAXIPLIMIT_PER_RULE,            /*<1068> Cannot configure more than 128 address pool per rule*/
    NAT_ADDADDRPOOL_ERR_INVALID_PORT_RANGE,             /*<1069> Min Port is larger than Max Port*/
    NAT_ADDADDRPOOL_ERR_CREATE_ADDR_POOL,               /*<1070> Unable to create Address Pool at the index*/
    NAT_ADDADDRPOOL_ERR_CREATE_SESSIONARRAY,            /*<1071> Failed to create session array */
    NAT_ADDADDRPOOL_ERR_CREATE_PORTQUEUE,               /*<1072> Failed to create port queue*/
    NAT_DELADDRPOOL_ERR_VCPU_NOT_INITIALIZED,           /*<1073> Global variables not initialized*/
    NAT_DELADDRPOOL_ERR_INVALID_ADDR_POOL_INDEX,        /*<1074> Address pool index is invalid*/
    NAT_DELADDRPOOL_ERR_POOL_NOT_EXISTS,                /*<1075> Address pool is not present*/
    NAT_DELADDRPOOL_ERR_RULES_ATTACHED,                 /*<1076> Address pool has rules attached*/
    NAT_REG_UPDATE_ERR_NULL_HOOK,                       /*<1077> Register hook function is NULL */
    NAT_REG_UPDATE_ERR_VCUP_INIT,                       /*<1078> Register update function, but VCPU needs to be initialized */
    NAT_REG_AGING_ERR_NULL_HOOK,                        /*<1079> Register aging function is NULL */
    NAT_REG_AGING_ERR_VCUP_INIT,                        /*<1080> Register aging function, but VCPU needs to be initialized */
    NAT_NOTIFY_SESS_ERR_NULL_HOOK,                      /*<1081> Notify hook function is NULL */
    NAT_NOTIFY_SESS_ERR_OPER,                           /*<1082> Notify operation type is wrong */
    NAT_NOTIFY_SESS_ERR_NULL_POINTER,                   /*<1083> Notify content is NULL */
    NAT_NOTIFY_SESS_ERR_INDEX_INVALID,                  /*<1084> Notify data index is invalid */
    NAT_NOTIFY_SESS_ERR_NO_HAVE_DOWN,                   /*<1085> Notify data index have download or no download */
    NAT_GET_FC_ERR_NULL_POINTER,                        /*<1086> FC pointer is NULL while getting flow context by session index */
    NAT_GET_FC_ERR_NO_INIT,                             /*<1087> VCPU not initialized while getting Flow context by session index */
    NAT_GET_FC_ERR_INDEX_INVALID,                       /*<1088> Session index is invalid while getting flow context by session index */
    NAT_GET_INDEXBY_FC_ERR_NULL_HOOK,                   /*<1089> Getting session index by flow context failed, because parameter is NULL */
    NAT_GET_INDEXBY_FC_ERR_NO_INIT,                     /*<1090> Getting session index by flow context failed, because VCPU not initialized */
    NAT_GET_INDEXBY_FC_ERR_SESS_NULL,                   /*<1091> Getting session index by flow context failed, because no NAT session in flow context */
    NAT_INIT_ERR_ALLOC_GLOBLADDRPOOLNUM,                /*<1092> AddrPoolNum_Share memory allocation failed*/
    NAT_DISP_GETRULE_ERR_GET_RULE_HANDLE,               /*<1093> Rule handle is not present*/
    NAT_DISP_GETRULE_ERR_NO_RULE_IN_INTERFACE,          /*<1094> No rule is present for this interface */
    NAT_DISP_GETPRECFG_ERR_GET_STRUCTURE_NULL,          /*<1095> Input structure is NULL in GETPRECFG*/
    NAT_DISP_GETPARAMTR_ERR_GET_STRUCTURE_NULL,         /*<1096> Input structure is NULL in GETPARMETER*/
    
    NAT_GET_PRECFG_ERR_NULL_POINTER,                    /*<1097>Input structure for capturing the preCfg parameters is NULL*/
    NAT_GET_PRECFG_ERR_VCPU_NOINIT,                     /*<1098>Vcpu is not initialised*/
    NAT_GET_NXT_RULE_ERR_NULL_POINTER,                  /*<1099>Input structure for capturing the RULE parameters is NULL*/
    NAT_GET_NXT_RULE_ERR_VCPU_NOINIT,                   /*<1100>Vcpu is not initialized*/
    NAT_GET_NXT_RULE_ERR_INVLD_HNDL,                    /*<1101>Input Handle is not valid i.e. NULL*/
    NAT_GET_NXT_RULE_ERR_ALLOC_FAIL,                    /*<1102>Memory Allocation is not successful*/
    NAT_FWD_ERR_CONE_PROTOCOL_NOT_SUPPORTED,            /*<1103>Unrecognized protocol type for the outbound packet*/
    NAT_IN_ERR_CONE_PROTOCOL_NOT_SUPPORTED,             /*<1104>Unrecognized protocol type for the inbound packet*/
    NAT_PRE_CFG_INIT_ERR_ALLOC_GLOBALNATIF_SHARE,       /*<1105>Memory allocation fro Global natif share variable fails*/
    NAT_PRE_CFG_INIT_ERR_ADDNAME_GLOBALNATIF_SHARE,     /*<1106>Unable to add g_pstglobalnatif_share in name data base*/
    NAT_GET_NXT_RULE_ERR_VERSION_CHANGE,                /*<1107>Version No. for this Interface has been changed 
                                                                 i.e. add or del operation has been performed for this */
    NAT_OPENRULELIST_ERR_NULL_VCPU,                     /*<1108>Vcpu is not initialized*/
    NAT_OPENRULELIST_ERR_MCMEMALLOC_FAIL,               /*<1109>Memory Allocation is not successful*/
    NAT_OPENRULELIST_ERR_NO_RULE_DEFINED,               /*<1110>No Rules are Present */
    NAT_OPENRULELIST_ERR_GETHANDLE_FAIL,                /*<1111>get handle for the Rules list is Failed*/
    NAT_OPENRULELIST_ERR_NULL_INTERFACE,                /*<1112>Unable to get the Interface*/
    NAT_SHOWRULEPARAM_ERR_NO_MORE_RULES,                /*<1113>No more Rules are present in this Interface*/
    NAT_GETRULE_PARAMETER_ERR_NO_MORE_RULES,            /*<1114>No more Rules are present in this Interface for Get Function*/
    NAT_CLOSERULELIST_ERR_NULL_HANDLE,                   /*<1115>NULL Handle as Input.*/
    NAT_IN_ERR_INBOUND_FLOW_CONTEXT_NULL,                /*<1116>Inbound packet flow context is null*/
    NAT_DISP_ERR_VCPU_NOINIT,                            /*<1117> VCPU not initialized*/
    NAT_CHECK_PRECFG_ERR_INVALID_ADDRESS_POOL_RANGE,      /*<1118>Invalid range for address pool index*/
    NAT_IN_ERR_INBOUND_PROTOCOL_NULL,                    /*<1119> Protocol of the inbound packet is NULL*/
    NAT_FWD_ERR_OUTBOUND_PROTOCOL_NULL,                 /*<1120>Protocol of the outbound packet is NULL*/
    NAT_FWD_ERR_OUTBOUND_FLOW_CONTEXT_NULL,              /*<1121> Flow context of outbound pkt is NULL*/
    NAT_DEL_SESSIONS_ERR_UNABLE_TOGET_INTRFC,           /*<1122> Unable to fetch the Interface from the Handle*/
    NAT_DEL_SESSIONS_ERR_NO_RULE_IN_INTERFACE,          /*<1123> No Rule is there in the Interface*/
    NAT_ISPOOLADDR_ERR_UNABLE_TOGET_INTRFC,             /*<1124> Unable to fetch the Interface from the Handle in function ISPOOLADDR*/
    NAT_IPOOLADDR_ERR_NO_RULE_IN_INTERFACE,             /*<1125> No Rule is there in the Interface*/
    NAT_ISPOOLADDR_ERR_NULL_HANDLE,                     /*<1126> Null handle as Input*/
    NAT_DEL_SESSIONS_ERR_INVLD_OPER_TYPE,               /*<1127> Invalid operation type as Input*/
    NAT_PRE_CFG_INIT_ERR_ALLOC_ALGMODE,                 /*<1128> Failed to alloc alg mode memory */
    NAT_PRE_CFG_INIT_ERR_ADDNAME_ALGMODE,               /*<1129> Failed to add alg mode name to the global shared memory database*/
    NAT_PRE_CFG_CHECK_ERR_TRANS_TCPALGMODE,             /*<1130> Failed to check transport mode refer TCP cone mode */
    NAT_REG_ALGMODE_ERR_NULL_HOOK,                      /*<1131> Register ALG mode function is NULL */
    NAT_REG_ALGMODE_VCUP_INIT,                          /*<1132> Register ALG mode function, but VCPU needs to be initialized */
    NAT_FWD_ERR_ALG_DISABLED,                           /*<1133> The pkt cannot be processed as the ALG has been disabled*/
    NAT_OPENRULELIST_ERR_NULL_INPUT,                    /*<1134> NULL Input*/
    NAT_INIT_ERR_ALLOC_GLOBL_SESSIONCOUNTNULL,          /*<1135> Memory Allocation for session count fails*/
    NAT_INIT_ERR_ALLOC_TIME_VCPU_NUM,                   /*<1136>*/
    NAT_INIT_ERR_ALLOC_DEL_VCPU_NUM,                    /*<1137>*/
    NAT_INIT_ERR_ALLOC_FPGA_RWLOCK,                     /*<1138> FPGA RWLock_Share memory allocation failed*/
    NAT_INIT_ERR_CREATE_FPGA_RWLOCK,                    /*<1139> g_pstFpgaRWLock_Share memory RW Lock create fails*/
    NAT_INIT_ERR_ADDNAME_FPGA_RWLOCK,                    /*<1140> Unable to add g_pstFpgaRWLock_Share to name db*/
    NAT_INIT_ERR_NULL_INPUT_PARA,
    NAT_INIT_ERR_MEMALLOC_SPINLOCK,
    NAT_INIT_ERR_CREATE_SPINLOCK,
    NAT_INIT_ERR_ADDNAME_SPINLOCK,
    NAT_INIT_ERR_SPIN_LOCK,
    NAT_INIT_ERR_MEMALLOC_AGINGTIMER,
    NAT_INIT_ERR_AGING_TIMER_INIT,
    NAT_INIT_ERR_ADDNAME_AGINGTIMER
}; 


/*ERRORCODE< Error codes in NAT_ALG_ICMP > */
enum enumNat_ALG_ICMP_ERRCode
{              
    NAT_ALG_ICMP_SUCCESS,                                               /*<0> On success*/
    NAT_ALG_ICMP_ERR_BEGIN_CODE = IPSAFE_ICMP_BEGIN_RET_CODE,           /*<8000> Beginning of ICMP error code */
    NAT_ALG_ICMP_SRCHFCFRMPAYLD_ERR_PKT_UNKNOWNICMPPAYLOAD,             /*<8001> Unknown ICMP payload in Error Packet */
    NAT_ALG_ICMP_SRCHFCFRMPAYLD_ERR_PKT_MIN_PAYLOADLEN,                 /*<8002> Payload length is not sufficient for 
                                                                             translation*/
    NAT_ALG_ICMP_SRCHFCFRMPAYLD_ERR_PKT_UNKNOWNPAYLOADTYPE,             /*<8003> Unknown payload type in ICMP Error Packet */
    NAT_ALG_ICMP_SRCHFCFRMPAYLD_ERR_PAYLD_PKT_FC_NOT_FOUND              /*<8004> FC for payload packet is not found*/
    
};


/*ERRORCODE< Error codes in NAT_ALG_RTSP > */
enum enumNat_ALG_RTSP_ERRCode
{              
    NAT_ALG_RTSP_SUCCESS,                                               /*<0> On success*/ 
    NAT_ALG_RTSP_ERR_BEGIN_CODE = IPSAFE_RTSP_BEGIN_RET_CODE,           /*<12000> Beginning of RTSP error code */ 
    NAT_ALG_RTSP_INIT_ERR_ALLOC_DATA_POOL,                              /*<12001> Failed to allocate rtsp data pool */
    NAT_ALG_RTSP_INIT_ERR_ALLOC_SEQ_HASH_TABLE,                         /*<12002> Failed to allocate rtsp sequence hash table */    
    NAT_ALG_RTSP_INIT_ERR_ALLOC_SESSION_HASH_TABLE,                     /*<12003> Failed to allocate rtsp session hash table */
    NAT_ALG_RTSP_INIT_ERR_MEMALLOC_SEQ_SPINLOCK,                        /*<12004> Failed to allocate memory for seq hash table spinlock */
    NAT_ALG_RTSP_INIT_ERR_SEQ_SPINLOCK_CREATE,                          /*<12005> Failed to create sequence hash table spinlock */   
    NAT_ALG_RTSP_INIT_ERR_ADDNAME_SEQ_SPINLOCK,                         /*<12006> Failed to add sequence hash table spinlock to name db */   
    NAT_ALG_RTSP_INIT_ERR_MEMALLOC_SESSION_SPINLOCK,                    /*<12007> Failed to allocate memory for session hash table spinlock */
    NAT_ALG_RTSP_INIT_ERR_SESSION_SPINLOCK_CREATE,                      /*<12008> Failed to create session hash table spinlock */ 
    NAT_ALG_RTSP_INIT_ERR_ADDNAME_SESSION_SPINLOCK,                     /*<12009> Failed to add session hash table spinlock to name db */ 
    NAT_ALG_RTSP_PKTOUT_ERR_DATA_ALLOC,                                 /*<12010> Failed to get new RTSP data from Pool */
    NAT_ALG_RTSP_PKTOUT_ERR_GET_TRANSPORT_PARAM,                        /*<12011> Failed to get Transport Parameter from payload */
    NAT_ALG_RTSP_GET_CMD_ERR_INVALID_REQUEST,                           /*<12012> RTSP Request does not contain EOL */
    NAT_ALG_RTSP_GET_CMD_ERR_INVALID_SETUP_REQUEST,                     /*<12013> Incomplete RTSP SETUP command specified in the payload  */
    NAT_ALG_RTSP_GET_CMD_ERR_INVALID_TEARDOWN_REQUEST,                  /*<12014> Incomplete RTSP TEARDOWN command specified in the payload */
    NAT_ALG_RTSP_GET_CMD_ERR_INVALID_RESONSE,                           /*<12015> Incomplete 200 OK message specified in the payload */
    NAT_ALG_RTSP_GET_CMD_ERR_DATE_TIME,                                 /*<12016> Date-Time information not present in the 200 ok reply message */
    NAT_ALG_RTSP_GET_CMD_ERR_NO_SESSIONID,                              /*<12017> Session number is not present in the 200 ok reply message */
    NAT_ALG_RTSP_GET_TRANS_PARAM_ERR_TRANSPORT_NO_STR,                  /*<12018> "Transport" string is not present in the SETUP request/reply */
    NAT_ALG_RTSP_GET_TRANS_PARAM_ERR_INTERLEAVED,                       /*<12019> Client requests for interleaved data session. translation not needed */
    NAT_ALG_RTSP_GET_TRANS_PARAM_ERR_MULTICAST,                         /*<12020> Client requests for multicast data session. translation not needed */
    NAT_ALG_RTSP_GET_TRANS_PARAM_ERR_TRANSPORT_NO_CRLF,                 /*<12021> Transport information does not end with EOL in SETUP request/reply */
    NAT_ALG_RTSP_GET_TRANS_PARAM_ERR_CLIENT_PORT_NO_STR,                /*<12022> "client_port" string is not specified in the SETUP request/reply */    
    NAT_ALG_RTSP_GET_TRANS_PARAM_ERR_NO_PORT_NUMBER,                    /*<12023> Client port number/s not specified in the SETUP request/reply */
    NAT_ALG_RTSP_PKTOUT_ERR_GET_GLOBAL_PORT1,                           /*<12024> Failed to get new global port from port queue for rtp data connection */
    NAT_ALG_RTSP_PKTOUT_ERR_GET_GLOBAL_PORT2,                           /*<12025> Failed to get new global port from port queue for rtcp data connection */
    NAT_ALG_RTSP_REPLACE_PORT_ERR_NO_CLIENT_PORT,                       /*<12026> "client_port" string is not specified in the SETUP request/reply */
    NAT_ALG_RTSP_REPLACE_PORT_ERR_NO_PORT_NUMBER,                       /*<12027> Client port number/s not specified in the SETUP request/reply */
    NAT_ALG_RTSP_REPLACE_PORT_ERR_CLIENT_PORT_NO_CRLF,                  /*<12028> Client port number/s does not end with EOL in the SETUP request */
    NAT_ALG_RTSP_REPLACE_PORT_ERR_CLIENT_PORT_NO_CRLFCRLF,              /*<12029> Setup Request/reply does not end with \r\n\r\n */
    NAT_ALG_RTSP_PKTOUT_ERR_MEMALLOC_SEQ_ACK_DATA,                      /*<12030> Failed to malloc seq-ack structure */
    NAT_ALG_RTSP_PKTOUT_ERR_MEMALLOC_SEQ_ACK_OUT_DATA,                  /*<12031> Failed to malloc outgoing packet sequence structure */
    NAT_ALG_RTSP_PKTOUT_ERR_TEARDOWN_NO_SEQ,                            /*<12032> Teardown request does not contain sequence number */
    NAT_ALG_RTSP_PKTOUT_ERR_TEARDOWN_NO_SESSIONID,                      /*<12033> Teardown request does not contain session number */
    NAT_ALG_RTSP_PKTOUT_ERR_TEARDOWN_NO_SESSION_HASH,                   /*<12034> Session specified in the TEARDOWN request is not present in the session hash table*/
    NAT_ALG_RTSP_PKTOUT_ERR_NAT_ACCESS_NULL,                            /*<12035> NAT Rule is not present in the session */
    NAT_ALG_RTSP_PKT_IN_ERR_TEARDOWN_SESSION_HASH_NOT_MATCH,            /*<12036> Failed to remove data sessions as session info not present in hash table */
    NAT_ALG_PKT_IN_ERR_CLIENT_PORT_NOT_MATCH,                           /*<12037> Client port number in SETUP reply does not match with the port numbers replaced in the SETUP request */
    NAT_ALG_RTSP_PKT_IN_ERR_NAT_ACCESS_NULL,                            /*<12038> NAT Rule is not present in the session */
    NAT_ALG_PKT_IN_ERR_SETUP_ACK_NO_SESSIONID,                          /*<12039> Session number is not present in the setup 200 ok reply message */
    NAT_ALG_RTSP_PKT_IN_ERR_NAT_RULE_DELETED1,                          /*<12040> Failed to create first rtsp data session as NAT Rule is already deleted */
    NAT_ALG_RTSP_PKT_IN_ERR_NAT_RULE_DELETED2,                          /*<12041> Failed to create second rtsp data session as NAT Rule is already deleted */
    NAT_ALG_RTSP_PKT_IN_ERR_CREATE_NEW_SESSION,                         /*<12042> Failed to create new NAT session */
    NAT_ALG_RTSP_GET_TRANS_PARAM_ERR_SERVER_PORT_NO_STR,                /*<12043> "server_port" string is not specified in the SETUP reply */
    NAT_ALG_RTSP_GET_TRANS_PARAM_ERR_NO_SERVER_PORT_NUMBERS,            /*<12044> server port number/s not specified in the SETUP reply */
    NAT_ALG_RTSP_PKT_IN_ERR_CREATE_Local_FC1,                           /*<12045> Failed to create new local flow context for first rtsp data session */
    NAT_ALG_RTSP_PKT_IN_ERR_CREATE_GLOBAL_FC1,                          /*<12046> Failed to create new global flow context for first rtsp data session  */
    NAT_ALG_RTSP_PKT_IN_ERR_CREATE_Local_FC2,                           /*<12047> Failed to create new local flow context for second rtsp data session */
    NAT_ALG_RTSP_PKT_IN_ERR_CREATE_GLOBAL_FC2,                          /*<12048> Failed to create new global flow context for second rtsp data session */
    NAT_ALG_RTSP_PKT_IN_ERR_MEMALLOC_SEQ_ACK_DATA,                      /*<12049> Failed to malloc new seq-ack data */
    NAT_ALG_RTSP_PKT_IN_ERR_MEMALLOC_SEQ_ACK_IN_DATA,                   /*<12050> Failed to malloc new incoming sequence data */
    NAT_ALG_RTSP_INIT_ERR_PROTO_REG_FOR_TCP_FAIL,                       /*<12051> Failed to register RTSP ALG for tcp */
    NAT_ALG_RTSP_INIT_ERR_PROTO_REG_FOR_UDP_FAIL,                       /*<12052> Failed to register RTSP ALG for udp */
    NAT_ALG_RTSP_PKTOUT_ERR_SEQ_ACK_MALLOC_AGING,                       /*<12053> Failed to malloc seq ack structuring during aging data update */
    NAT_ALG_RTSP_ENBLE_SWITCH_ERR_PROTO_NOT_REGISTERED,                 /*<12054> RTSP ALG is not registered. */
    NAT_ALG_RTSP_GET_ERR_PROTO_NOT_REGISTERED                           /*<12055> RTSP ALG is not registered. */
};  

/*STRUCT< This enum is used to enable or disable protocol, and for updating protocol timeout >*/
typedef enum enumNAT_ALG
{
    NAT_TCP,      /* non specific application protocol. Only for timeout update */
    NAT_UDP,      /* non specific application protocol. Only for timeout update */
    NAT_ALG_FTP,
    NAT_ALG_MSN,
    NAT_ALG_DNS,
    NAT_ALG_ICMP,
    NAT_ALG_HTTP,
    NAT_ALG_RTSP,
    NAT_ALG_SMTP,
    NAT_ALG_ALL,
    NAT_ALG_MAX /* maximum value */
 
    /* Add other ALG protocols */
 
}NAT_ALG_PROTOCOL_E;


#define NAT_ADD_RULE                       0    /*Adds NAT rule*/
#define NAT_DEL_RULE                       1    /*Deletes NAT rule*/

/* for display functions*/
#define NAT_PER_INTERFACE                  0    /*Input for Display Session per Interface*/
#define NAT_ALL_SESSION                    1    /*Input for Display Session for all the sessions */
#define NAT_VRF_SESSION                    2    /*Input for Display Session per VRF*/


#define NAT_NOTIFY_CREATE_SESSION          0    /* Notify FPGA create session */
#define NAT_NOTIFY_DELETE_SESSION          1    /* Notify FPGA delete session */
#define NAT_NOTIFY_SESSION_AGING           2    /* FPGA notify NAT session aging */

#define NAT_DO_ALG                         1    /* Do ALG flag value for FPGA */
#define NAT_NOT_DO_ALG                     0    /* Not do ALG flag value FPGA */

#define NAT_INVALID_SESS_INDEX             0xFFFFFFFF  /* Invalid session index */
#define NAT_ALL_INTERFACE                  0xFFFFFFFF  /*For all the interface(used is_addr_pool api show get APIs)*/
#define NAT_ALL_INTRFC                     0xFFFF  /*For all the interface(used fro show get APIs)*/
#define NAT_DEL_SESS_FOR_INTERFACE                  0    /*Operation type For deleting sessions per Interface.*/
#define NAT_DEL_SESS_FOR_SOURCE_IP                  1    /*Operation type For deleting sessions per source address*/

/*ERRORCODE< ACL action values >*/
typedef enum tagNAT_ACL_Actions 
{ 
    NAT_ACL_DENY = 0,          /*ACL denied*/
    NAT_ACL_PERMIT = 1,        /*ACL permit*/
    NAT_ACL_NOTFOUND = 2       /*ACL not found*/
}NAT_ACL_ACTIONS_E;

#define NAT_ADDRESS_USED     1      /*Indicates that a particular address belongs to the address pool.*/
#define NAT_ADDRESS_NOT_USED 0      /*Indicates that a particular address does not belong to the address pool.*/


extern UINT32 NAT_OperRule(UINT32 u32OperType, NAT_RULE_S *pstRule);


/******************************************************************************
*    Func Name: NAT_SetAlgTimeOut
*    Date Created: 2010-1-13
*       Author: z62474/b71224
*    Description: This API is used to set the aging time for different protocols
*    Input: UINT32 u32Protocol: Protocol number from NAT_ALG_PROTOCOL_E
*           UINT32 u32Timeout: Timeout value in seconds
*    Output: 
*       Return: Success: NAT_SUCCESS
*      Caution: 
*      Since: V200R003C01
*      Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2010-1-13    z62474/b71224     Create the first version.
*
******************************************************************************/
extern UINT32 NAT_SetAlgTimeOut(UINT32 u32Protocol, UINT32 u32SecTimeout);


/*******************************************************************************
*    Func Name: NAT_EnableAlg
* Date Created: 2010-03-29
*       Author: bhaskar(71224)
*      Purpose: This API is used to enable an ALG Protocol for ALG processing
*  Description: This API calls NAT_ChangeStatus function to enable ALG
*        Input: UINT32 u32Protocol: protocol number from enumNAT_ALG <[NAT_ALG_FTP-NAT_ALG_ALL]>
*       Output: 
*       Return: Success:NAT_ALG_SUCCESS
*               Failure:NAT_ALG_SET_PROTO_STAT_ERR_PROTO_ALREADY_ENABLED
*                       NAT_ALG_CHNG_STAT_ERR_INVALID_PROTOCOL
*                       NAT_ALG_CHNG_STAT_ERR_PRO_FUNC_NOT_DEFINED
*                       NAT_ALG_SET_PROTO_STAT_ERR_TRANS_PROTOCOL_FAIL
*                       NAT_ALG_SET_PROTO_STAT_ERR_PROTOCOL_NOT_FOUND
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   bhaskar(71224)          Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_EnableAlg(UINT32 u32Protocol);


/*******************************************************************************
*    Func Name: NAT_DisableAlg
* Date Created: 2010-03-29
*       Author: bhaskar(71224)
*      Purpose: This API is used to disable an ALG Protocol from ALG processing 
*  Description: This API calls NAT_ChangeStatus function to disable ALG
*    Input: UINT32 u32Protocol: Protocol number from enumNAT_ALG <[NAT_ALG_FTP-NAT_ALG_ALL]>
*       Output: 
*       Return: Success:NAT_ALG_SUCCESS
*               Failure:NAT_ALG_SET_PROTO_STAT_ERR_PROTO_ALREADY_DISABLED
*                       NAT_ALG_CHNG_STAT_ERR_INVALID_PROTOCOL
*                       NAT_ALG_CHNG_STAT_ERR_PRO_FUNC_NOT_DEFINED
*                       NAT_ALG_SET_PROTO_STAT_ERR_TRANS_PROTOCOL_FAIL
*                       NAT_ALG_SET_PROTO_STAT_ERR_PROTOCOL_NOT_FOUND
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   bhaskar(71224)          Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_DisableAlg(UINT32 u32Protocol);



extern VOID NAT_DisplaySession(UINT16 u16DispType, UINT32 u32Data);


typedef UINT32 (*NAT_UPDATE_SESSION_FUNC)(UINT32 u32Oper, NAT_UPDATE_SESSION_S *pstNatPpiSession);


/*******************************************************************************
*    Func Name: NAT_RegFunUpdateSessionTable
* Date Created: 2010-04-01
*       Author: zhangchi(00142640)
*      Purpose: This function updates table hook register function.
*  Description: This function is used to update the register table hook.
*        Input: NAT_UPDATE_SESSION_FUNC pfNAT_UpdateSessionTable: NAT update table hook <not null>
*       Output: 
*       Return: Success: NAT_SUCCESS
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-01   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_RegFunUpdateSessionTable(NAT_UPDATE_SESSION_FUNC pfNAT_UpdateSessionTable);

/*******************************************************************************
*    Func Name: NAT_UPDATE_AGINGTIME_FUNC
* Date Created: 2010-04-01
*       Author: zhangchi(00142640)
*      Purpose: Product implement update session aging timeout function prototype
*  Description: Product implement update session aging timeout function prototype
*        Input: UINT32 u32Protocol: Protocol type<NAT_NOTIFY_CREATE_SESSION and NAT_NOTIFY_DELETE_SESSION>
*               UINT32 u32SecTimeOut: Timeout value, uint second<All uint>
*       Output: 
*       Return: Success: NAT_SUCCESS
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-01   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
typedef UINT32 (*NAT_UPDATE_AGINGTIME_FUNC)(UINT32 u32Protocol, UINT32 u32SecTimeOut);

/*******************************************************************************
*    Func Name: NAT_RegFunUpdateAgingTime
* Date Created: 2010-04-06
*       Author: zhangchi(00142640)
*      Purpose: This function updates aging time register function.
*  Description: This function is used to update register aging time hook.
*        Input: NAT_UPDATE_AGINGTIME_FUNC pfNAT_UpdateAgingTime: NAT aging time update hook <not null>
*       Output: 
*       Return: Success: NAT_SUCCESS
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-06   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_RegFunUpdateAgingTime(NAT_UPDATE_AGINGTIME_FUNC pfNAT_UpdateAgingTime);


extern UINT32 NAT_NotifySessionChange(UINT32 u32Oper,NAT_SESSION_CHANGE_S* pstChangeInfo);

/*******************************************************************************
*    Func Name: NAT_GetFCAddrBySessionIndex
* Date Created: 2010-04-14
*       Author: zhangchunyu(62474)
*      Purpose: This function gets the flow context by NAT session index.
*  Description: This function gets the flow context by NAT session index.
*        Input: UINT32 u32SessIndex: Session index <All integers - uint>
*       Output: IPSAFE_FLOW_CONTEXT_S *pstLocalFC: Local flow context <Not null pointer>
*               IPSAFE_FLOW_CONTEXT_S *pstGlobalFC: Global flow context <Not null pointer>
*       Return: Success: NAT_SUCCESS
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-14   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_GetFCAddrBySessionIndex(UINT32 u32SessIndex, 
                                           IPSAFE_FLOW_CONTEXT_S **pstLocalFC,
                                           IPSAFE_FLOW_CONTEXT_S **pstGlobalFC);




UINT32 NAT_AddAddrPool(UINT32 u32StartAddress, 
                        UINT32 u32EndAddress, 
                        UINT16 u16MinPortValue, 
                        UINT16 u16MaxPortValue, 
                        UINT32 u32AddrPoolIndex);



UINT32 NAT_DelAddrPool(UINT32 u32AddrPoolIndex);


UINT32 NAT_IsPoolAddr(INTF_HANDLE intfHandle,UINT32 u32Address);

/*******************************************************************************
*    Func Name: NAT_GetSessionIndexByFlowContext
* Date Created: 2010-04-19
*       Author: zhangchunyu(62474)
*      Purpose: This function gets session index by packet context.
*  Description: This function gets session index by packet context.
*        Input: IPSAFE_FLOW_CONTEXT_S pstFCContext: packet flow context<Not null pointer>
*       Output: UINT32 *pu32SessIndex: Get the session index<Not null pointer>
*       Return: Success: NAT_SUCCESS
*      Caution: This is user for PARC API, and have a restricts:Only Parc call nat forward success
*               then call this API for get session index.Other shouldn't use it
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-19   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 NAT_GetSessionIndexByFlowContext(UINT32 *pu32SessIndex, IPSAFE_FLOW_CONTEXT_S *pstFCContext);



extern VOID NAT_ShowALGStatus(UINT32 u32Protocol);



extern UINT32 NAT_GetALGStatus(UINT32 u32Protocol,ALG_STATUS_S *pstgetAlg);



extern VOID NAT_ShowAllALGStatus(VOID);




extern VOID NAT_ShowNextRule(UINT16 u16Interface,VOID *Handle,UINT32 Number);





extern UINT32 NAT_GetNextRule(UINT16 u16Interface,GET_RULE_S *pstGetRule,VOID *Handle,UINT32 Number);


extern VOID NAT_ShowAllSupportedAlg(VOID);


extern VOID NAT_ShowAllEnabledAlg(VOID);


extern UINT32 NAT_GetAllEnabledAlg(GET_ALG_S *pstAlgNames);


extern UINT32 NAT_GetAllSupportedAlg(GET_ALG_S *pstAlgNames);


extern VOID NAT_ShowPreConfig(VOID);



extern  UINT32 NAT_GetPreConfig(NAT_PRE_CFG_S *pstGetConfig);




extern UINT32 NAT_OpenRuleList(UINT16 u16Interface,VOID ** pHandle);



extern UINT32 NAT_CloseRuleList(VOID *pHandle);





extern UINT32 NAT_DeleteSessions(UINT32 u32operType,UINT32 u32Data);

/*******************************************************************************
*    Func Name: NAT_UPDATE_ALGMODE_FUNC
* Date Created: 2010-06-01
*       Author: zhangchunyu(62474)
*      Purpose: Product implement update alg mode function prototype
*  Description: Product implement update alg mode function prototype
*        Input: UINT32 u32ConeMode: Cone mode type<IPSAFE_CONE_MODE_TRANSPORT and IPSAFE_CONE_MODE_ALG>
*               NAT_ALG_MODE pstAlgMode: Alg mode type pointer<Not null pointer>
*       Output: 
*       Return: Success: NAT_SUCCESS
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-01  zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
typedef UINT32 (*NAT_UPDATE_ALGMODE_FUNC)(UINT32 u32ConeMode, NAT_ALG_MODE *pstAlgMode);

/*******************************************************************************
*    Func Name: NAT_RegFunUpdateAlgMode
* Date Created: 2010-06-02
*       Author: zhangchunyu62474
*      Purpose: Update aging time register function.
*  Description: This function is used to register update aging time hook. 
*        Input: NAT_UPDATE_ALGMODE_FUNC pfNAT_UpdateAlgMode: NAT alg mode update hook<not null>
*       Output: 
*       Return: Successful: NAT_SUCCESS
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-02   zhangchunyu62474        Create the first version.
*
*******************************************************************************/
extern UINT32 NAT_RegFunUpdateAlgMode(NAT_UPDATE_ALGMODE_FUNC pfNAT_UpdateAlgMode);

#ifdef  __cplusplus
}
#endif

#endif

