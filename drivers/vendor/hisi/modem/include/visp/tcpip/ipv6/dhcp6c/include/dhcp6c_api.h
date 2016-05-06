/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp6c_api.h
*
*  Project Code: VISPV100R008C03
*   Module Name: DHCPv6
*  Date Created: 2009-12-8
*        Author: wujie 61195
*   Description: DHCPv6模块用户API头文件，定义用户需要使用的数据结构、宏和API原型
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2009-12-8   wujie 61195      Create the first version.
*
*******************************************************************************/

#ifndef _DHCP6C_API_H_
#define _DHCP6C_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/* Bit Fields */
#define DHCP6C_BIT0   (1<<0)
#define DHCP6C_BIT1   (1<<1)
#define DHCP6C_BIT2   (1<<2)
#define DHCP6C_BIT3   (1<<3)
#define DHCP6C_BIT4   (1<<4)
#define DHCP6C_BIT5   (1<<5)
#define DHCP6C_BIT6   (1<<6)
#define DHCP6C_BIT7   (1<<7)
#define DHCP6C_BIT8   (1<<8)
#define DHCP6C_BIT9   (1<<9)
#define DHCP6C_BIT10  (1<<10)
#define DHCP6C_BIT11  (1<<11)
#define DHCP6C_BIT12  (1<<12)
#define DHCP6C_BIT13  (1<<13)
#define DHCP6C_BIT14  (1<<14)
#define DHCP6C_BIT15  (1<<15)
#define DHCP6C_BIT16  (1<<16)
#define DHCP6C_BIT17  (1<<17)
#define DHCP6C_BIT18  (1<<18)
#define DHCP6C_BIT19  (1<<19)
#define DHCP6C_BIT20  (1<<20)
#define DHCP6C_BIT21  (1<<21)
#define DHCP6C_BIT22  (1<<22)
#define DHCP6C_BIT23  (1<<23)
#define DHCP6C_BIT24  (1<<24)
#define DHCP6C_BIT25  (1<<25)
#define DHCP6C_BIT26  (1<<26)
#define DHCP6C_BIT27  (1<<27)
#define DHCP6C_BIT28  (1<<28)
#define DHCP6C_BIT29  (1<<29)
#define DHCP6C_BIT30  (1<<30)
#define DHCP6C_BIT31  (1<<31)

/*MACRO< DHCP6C Define >*/
#define DHCP6C_MAX_ENUM_VALUE           0xFFFFFFFF
#define DHCP6C_MAX_DUID_VALUE_LENGTH    (128 + 1 + 3) /* 3-Bytes-Arm CPU */

#define DHCP6C_MAX_LINK_LAYER_ADDR_LEN      126  /*DHCP6C链路层地址最大长度*/

/*ERRORCODE<Error codes - Notified to the Application >*/
typedef enum tagDHCP6C_ERRCODE
{
    DHCP6C_OK = 0,                          /* <0>No Error - Ok */
    DHCP6C_ERR = 1,                         /* <1>Error */
    DHCP6C_ERRCODE_COMPONENT_NOT_REGISTER,  /* 2  Component not register */

    /* ---------------------- Input Parameter Validation -------------------- */
    DHCP6C_ERRCODE_INVALID_INPUT,                       /* 3  Invalid input parameter */
    DHCP6C_ERRCODE_INPUT_NULL,                          /* 4  Input parameter is NULL */
    DHCP6C_ERRCODE_ADDRLEN_ZERO,                        /* 5  Input Link Layer Address Len is Zero */
    DHCP6C_ERRCODE_ADDRLEN_REACHMAX,                    /* 6  Input Link Layer Address Len Reach MAX */
    DHCP6C_ERRCODE_TMSTAMP_ZERO,                        /* 7  Input Link time stamp is zero */    
    DHCP6C_ERRCODE_ENNUMBER_ZERO,                       /* 8  Input EntrNumber is zero */    
    DHCP6C_ERRCODE_ENIDLEN_ZERO,                        /* 9  Input Entr ID Len is zero */    
    DHCP6C_ERRCODE_ENIDLEN_REACHMAX,                    /* 10 Input Entr Len Reach MAX */    
    DHCP6C_ERRCODE_NULLINPUT_GETUTIL_FSTNODE,           /* 11 Input Null pointer in Util_GetFirstNode */
    DHCP6C_ERRCODE_NULLNODE_GETUTIL_FSTNODE,            /* 12 Get Null Node in Util_GetFirstNode */
    DHCP6C_ERRCODE_NULLINPUT_GETUTIL_NODECNT,           /* 13 Input Null pointer in Util_GetNodeCount */
    DHCP6C_ERRCODE_NULLINPUT_UTIL_INTF_NOTSTART,        /* 14 Input Null pointer in Util_IsInterfaceNotStarted */ 
    DHCP6C_ERRCODE_NULLINPUT_GETUTIL_NEXTNODE,          /* 15 Input Null pointer in Util_GetNextNode */ 
    DHCP6C_ERRCODE_NULLINPUT_GETUTIL_TRANSNODE,         /* 16 Input Null pointer in Util_GetTranscationMsgNode */
    DHCP6C_ERRCODE_MSG_ERR_UTIL_INTF_NOTSTART,          /* 17 Msg is Err in Util_GetTranscationMsgNode */
    DHCP6C_ERRCODE_MSG_NOTPRESENT_UTIL_INTF_NOTSTART,   /* 18 Msg is not present in Util_GetTranscationMsgNode */
    DHCP6C_ERRCODE_DUID_INUSE_UTIL_INTF_NOTSTART,       /* 19 DUID is in use in  Util_GetTranscationMsgNode */
    DHCP6C_ERRCODE_NULLINPUT_UTIL_VALIDATE_ADDR,        /* 20 Input Null pointer in Util_ValidateAddressesWithTime */
    DHCP6C_ERRCODE_INVALID_LIFETIME_NOTMATCH,           /* 21 Input lifetime is not match in Util_ValidateAddressesWithTime */
    DHCP6C_ERRCODE_INVALID_IA_PREFIX_LEN,               /* 22 Input invalid prefix len in Util_ValidateAddressesWithTime */
    DHCP6C_ERRCODE_INVALID__IAOTHER_PREFIX_LEN,         /* 23 Input invalid IA-NA and IA-TA in Util_ValidateAddressesWithTime */
    DHCP6C_ERRCODE_INPUT_ZERO_ADDRCNT,                  /* 24 Input zero addr cnt in Util_ValidateAddressesWithTime */
    DHCP6C_ERRCODE_DUPLICATE_ADDR,                      /* 25 Input duplicate addr in Util_ValidateAddressesWithTime */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_ISDUPLICATE,          /* 26 Input Null point in Util_IsIAIDDuplicate */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_MATCHNODE,            /* 27 Input Null point in Util_IsIAIDDuplicate */
    DHCP6C_NULLPOINT_UTIL_GETINTFNODE,                  /* 28 Input Null point in Util_GetInterfaceNode */
    DHCP6C_NULLPOINT_UTIL_GET_IACFGNODE,                /* 29 Input Null point in Util_GetIACfgNode */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_ADDIANODE,            /* 30 Input Null point in Util_AddIACfgNode */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_START,                /* 31 Input Null point in Util_IsConfigValidToStart */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_NOIARUN,              /* 32 Input Null point in Util_IsConfigValidToStart*/   
    DHCP6C_ERRCODE_NULLPOINT_UTIL_VALIDATEADDR,         /* 33 Input Null point in Util_VALIDATEADDR       */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_VALIDATE_RAWOPT,      /* 34 Input Null point in Util_VALIDATE_RAWOPT    */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_VALIDATE_AUTHINFO,    /* 35 Input Null point in Util_VALIDATE_AUTHINFO  */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_VALIDATE_KEYINFO,     /* 36 Input Null point in UTIL_VALIDATE_KEYINFO   */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_RANDGEN,              /* 37 Input Null point in UTIL_RANDGEN            */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_FREELIST,             /* 38 Input Null point in UTIL_FREELIST           */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_ADDNODE,              /* 39 Input Null point in UTIL_ADDNODE            */
    DHCP6C_ERRCODE_NULLPOINT_CREATNODE,                 /* 40 Input Null point in CREATNODE               */
    DHCP6C_ERRCODE_NULLPOINT_ADDNODE,                   /* 41 Input Null point in ADDNODE                 */
    DHCP6C_ERRCODE_NULLPOINT_DELNODE,                   /* 42 Input Null point in DELNODE                 */
    DHCP6C_ERRCODE_NULLPOINT_MATCHNODE,                 /* 43 Input Null point in MATCHNODE               */
    DHCP6C_ERRCODE_NULLPOINT_INITNODE,                  /* 44 Input Null point in INITNODE                */
    DHCP6C_ERRCODE_NULLPOINT_ISDEFNODE,                 /* 45 Input Null point in ISDEFNODE               */
    DHCP6C_ERRCODE_NULLPOINT_ADDKEYINF,                 /* 46 Input Null point in ADDKEYINF               */
    DHCP6C_ERRCODE_NULLPOINT_DELKEYINF,                 /* 47 Input Null point in DELKEYINF               */
    DHCP6C_ERRCODE_NULLPOINT_GETKEYINF,                 /* 48 Input Null point in GETKEYINF               */
    DHCP6C_ERRCODE_NULLPOINT_ISDAPKEY,                  /* 49 Input Null point in ISDAPKEY                */
    DHCP6C_ERRCODE_NULLPOINT_MATCH_PRIMNODE,            /* 50 Input Null point in MATCH_PRIMNODE          */
    DHCP6C_ERRCODE_NULLPOINT_INITKEYINF,                /* 51 Input Null point in INITKEYINF              */
    DHCP6C_ERRCODE_NULLPOINT_DELSERNODE,                /* 52 Input Null point in DELSERNODE              */
    DHCP6C_ERRCODE_NULLPOINT_GETSERNODE,                /* 53 Input Null point in GETSERNODE              */
    DHCP6C_ERRCODE_NULLPOINT_MATCHSERNODE,              /* 54 Input Null point in MATCHSERNODE            */
    DHCP6C_ERRCODE_NULLPOINT_INIT_DNSSERNODE,           /* 55 Input Null point in INIT_DNSSERNODE         */
    DHCP6C_ERRCODE_NULLPOINT_ADD_RAWNODE,               /* 56 Input Null point in ADD_RAWNODE             */
    DHCP6C_ERRCODE_NULLPOINT_DEL_RAWNODE,               /* 57 Input Null point in DEL_RAWNODE             */
    DHCP6C_ERRCODE_NULLPOINT_FREE_RAWNODE,              /* 58 Input Null point in FREE_RAWNODE            */
    DHCP6C_ERRCODE_NULLPOINT_GET_RAWNODE,               /* 59 Input Null point in GET_RAWNODE             */
    DHCP6C_ERRCODE_NULLPOINT_MATCH_RAWNODE,             /* 60 Input Null point in MATCH_RAWNODE           */
    DHCP6C_ERRCODE_NULLPOINT_INIT_RAWNODE,              /* 61 Input Null point in INIT_RAWNODE            */
    DHCP6C_ERRCODE_NULLPOINT_DEL_IANODE,                /* 62 Input Null point in DEL_IANODE              */
    DHCP6C_ERRCODE_NULLPOINT_MATCH_IANODE,              /* 63 Input Null point in MATCH_IANODE            */
    DHCP6C_ERRCODE_NULLPOINT_INIT_IANODE,               /* 64 Input Null point in INIT_IANODE             */
    DHCP6C_ERRCODE_NULLPOINT_ISDEF_IANODE,              /* 65 Input Null point in ISDEF_IANODE            */
    DHCP6C_ERRCODE_NULLPOINT_DEL_PRENODE,               /* 66 Input Null point in DEL_PRENODE             */
    DHCP6C_ERRCODE_NULLPOINT_GET_PRENODE,               /* 67 Input Null point in GET_PRENODE             */
    DHCP6C_ERRCODE_NULLPOINT_MATCH_PRENODE,             /* 68 Input Null point in MATCH_PRENODE           */
    DHCP6C_ERRCODE_NULLPOINT_INIT_PRENODE,              /* 69 Input Null point in INIT_PRENODE            */
    DHCP6C_ERRCODE_NULLPOINT_ADD_TRANSNODE,             /* 70 Input Null point in ADD_TRANSNODE           */
    DHCP6C_ERRCODE_NULLPOINT_DEL_TRANSNODE,             /* 71 Input Null point in DEL_TRANSNODE           */
    DHCP6C_ERRCODE_NULLPOINT_INIT_TRANSNODE,            /* 72 Input Null point in INIT_TRANSNODE          */
    DHCP6C_ERRCODE_NULLPOINT_MATCH_TRANSNODE,           /* 73 Input Null point in MATCH_TRANSNODE         */
    DHCP6C_ERRCODE_NULLPOINT_ADD_PARSENODE,             /* 74 Input Null point in ADD_PARSENODE           */
    DHCP6C_ERRCODE_NULLPOINT_FREE_PARSENODE,            /* 75 Input Null point in FREE_PARSENODE          */
    DHCP6C_ERRCODE_NULLPOINT_GET_SENTMSG,               /* 76 Input Null point in GET_SENTMSG             */
    DHCP6C_ERRCODE_NULLPOINT_GET_RCVMSG,                /* 77 Input Null point in GET_RCVMSG              */
    DHCP6C_ERRCODE_NULLPOINT_GET_STATEOFF,              /* 78 Input Null point in GET_STATEOFF            */
    DHCP6C_ERRCODE_NULLPOINT_GET_RCVOFF,                /* 79 Input Null point in GET_RCVOFF              */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_RECSTATS,             /* 80 Input Null point in UTIL_RECSTATS           */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_STOREINTF,            /* 81 Input Null point in UTIL_STOREINTF          */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_DELINTF,              /* 82 Input Null point in UTIL_DELINTF            */
    DHCP6C_ERRCODE_NULLPOINT_UTIL_FLUSHINTF,            /* 83 Input Null point in UTIL_FLUSHINTF          */
    DHCP6C_ERRCODE_UTIL_GETNULLNODE,                    /* 84 Get Null Node in add addr                   */
    DHCP6C_ERRCODE_UTIL_GETNULLIANODE,                  /* 85 Get Null IA Node in add addr                */
    DHCP6C_ERRCODE_UTIL_GETNULL_OUTINTF,                /* 86 Get Null out interface in add addr          */
    DHCP6C_ERRCODE_UTIL_GETNULL_CFGNODE,                /* 87 Get Null cfg Node in add addr               */
    DHCP6C_ERRCODE_UTIL_GETNULL_INTF_OUTNODE,           /* 88 Get Null out interface in add addr               */
    DHCP6C_ERRCODE_MORE_ADDR,                           /* 89 One or More Requested Address Configuration present */
    DHCP6C_ERRCODE_INVALID_TCONF,                       /* 90 Invalid for T1/T2 configuration */
    DHCP6C_ERRCODE_INVALID_LSCONF,                      /* 91 Invalid Leased configuration */
    DHCP6C_ERRCODE_ZERO_ADDRCNT,                        /* 92 Addr count is zero in ProcDNSServersRequest */    
    DHCP6C_ERRCODE_TYPEANDCNT_NOMATCH,                  /* 93 Addr count is not 1 can not del in ProcDNSServersRequest */    
    DHCP6C_ERRCODE_INPUT_EXCEED_DNS_ADDR_MAX_VAL,       /* 94 Address given is greater than MAX value */
    DHCP6C_ERRCODE_DUID_NOT_CFG_TO_START,               /* 95 Accept Enabled, But DUID not Configured */
    DHCP6C_ERRCODE_AUTH_DISABLE_TO_START,               /* 96 Reconfigure Accept Enabled, But Authentication is Disabled */
    DHCP6C_ERRCODE_DUID_NOT_CFG_TO_ENABLEOPT,           /* 97 Authentication is Enabled, But DUID is not configured */
    DHCP6C_ERRCODE_RAPID_CFG_TO_ENABLEOPT,              /* 98 Authentication Enabled with Delayed Authentication Protocol */
    DHCP6C_ERRCODE_PROKEY_CFG_TO_ENABLEOPT,             /* 99 Authentication is Enabled, But No Delayed Authentication */
    DHCP6C_ERRCODE_RECFG_DISABLE_TO_ENABLEOPT,          /* 100 Authentication Enabled with Reconfigure Key Authentication */
    DHCP6C_ERRCODE_NOTIA_PRESENT,                       /* 101 Address is not present in this IA */
    DHCP6C_ERRCODE_NO_DUPLICATE,                        /* 102 Only one Address is being declined */
    DHCP6C_ERRCODE_INPUT_NULL_RLSIA,                    /* 103 Input Null in ReleaseIA_Updation */
    DHCP6C_ERRCODE_INVALID_TRANS_TYPE,                  /* 104 Invalid Trans para type */
    DHCP6C_ERRCODE_INVALID_PARA_MR,                     /* 105 Invalid MRC or MRD value */
    DHCP6C_ERRCODE_ACTVALUE_EXCEED,                     /* 106 New value value exceed area */
    DHCP6C_ERRCODE_INVALID_INPUT_MSGTYPE,               /* 107 Invalid Msg type */
    DHCP6C_ERRCODE_INPUT_NULL_VALUE,                    /* 108 Value is null */
    DHCP6C_ERRCODE_INTF_NOT_PRESENT_UTIL_GETINTFNODE,   /* 109 Interface is Null in Util_GetInterfaceNode */
    
    /* ------------------------ General Error Codes ------------------------- */
    DHCP6C_ERRCODE_INVALID_CFG_OPT,         /* 110 Config Operation */
    DHCP6C_ERRCODE_NO_SERVER_INFO,          /* 111 No server information */
    DHCP6C_ERRCODE_NO_CFG_TO_FETCH,         /* 112 No configuration is present */
    DHCP6C_ERRCODE_NO_LEASED_CFG_PRESENT,   /* 113 No Leased Cfg is present */
    DHCP6C_ERRCODE_RANDOM_GENERATOR_FAIL,   /* 114 Random No generation failed */
    DHCP6C_ERRCODE_END_OF_LIST,             /* 115 Get Next failed */
    DHCP6C_ERRCODE_NOT_FOUND,               /* 116 Searched item not found */
    DHCP6C_ERRCODE_NOT_ALLOWED,             /* 117 Operation not allowed */
    /* ----------------------- DUID Related Error codes --------------------- */
    DHCP6C_ERRCODE_SAME_DUID_PRESENT,       /* 118 DUID being configured is same */
    DHCP6C_ERRCODE_DUID_NOT_PRESENT,        /* 119 DUID is not configured */

    /* -------------- System State Machine Errors --------------------------- */
    DHCP6C_ERRCODE_ALREADY_RUNNING,         /* 120 Client is Running */
    DHCP6C_ERRCODE_SYS_NOT_INITIALISED,     /* 121 Client is not Initialized */
    DHCP6C_ERRCODE_INVALID_SYSTEM_STATE,    /* 122 System state is invalid */
    DHCP6C_ERRCODE_SYS_NOT_IN_RUNNING,      /* 123 System is not in running state */

    /* ---------------- Interfaces Related Error codes ---------------------- */
    DHCP6C_ERRCODE_INTERFACE_NOT_PRESENT,   /* 124 Interface does not exist */
    DHCP6C_ERRCODE_MAX_INTF_REACHED,        /* 125 MAX number of interface reached*/
    DHCP6C_ERRCODE_INTERFACE_NOT_STARTED,   /* 126 No On Going transaction  */
    DHCP6C_ERRCODE_NO_INTERFACE_PRESENT,    /* 127 No Interface present */

    /* --------------------- IA Related Error Codes ------------------------- */
    DHCP6C_ERRCODE_INVALID_IATYPE,          /* 128 Invalid IA type */
    DHCP6C_ERRCODE_INVALID_IATIMERTYPE,     /* 129 Invalid IA timer type T1/T2 */
    DHCP6C_ERRCODE_IA_NOT_PRESENT,          /* 130 IA does not exist */
    DHCP6C_ERRCODE_MAX_IA_REACHED,          /* 131 MAX number of IA list reached */
    DHCP6C_ERRCODE_NO_IA_REQ_CONFIG,        /* 132 No IA Requested config present */
    DHCP6C_ERRCODE_NO_IA_OBTAINED,          /* 133 No IA in Obtained state */
    DHCP6C_ERRCODE_IA_NOT_OBTAINED,         /* 134 Specified IA is not Obtained */
    DHCP6C_ERRCODE_IA_OPTION_NOT_PRESENT,   /* 135 IA Option not found */
    DHCP6C_ERRCODE_IAID_DUPLICATE,          /* 136 IAID Duplicate */

    /* ------------------- Address Related Error codes ---------------------- */
    DHCP6C_ERRCODE_INVALID_ADDR_TYPE,       /* 137 Multicast/Link local address */
    DHCP6C_ERRCODE_ADDRESS_LEASED,          /* 138 Address is already Leased */
    DHCP6C_ERRCODE_MAX_ADDR_REACHED,        /* 139 MAX Addresses per IA reached */
    DHCP6C_ERRCODE_EXCEED_ADDR_PAF_VAL,     /* 140 Address exceed */
    DHCP6C_ERRCODE_EXCEED_DNS_ADDR_MAX_VAL, /* 141 MAX DNS Address Reached */
    DHCP6C_ERRCODE_IAADDR_NOT_PRESENT,      /* 142 Address not present in IA */
    DHCP6C_ERRCODE_INVALID_LIFETIME,        /* 143 Valid/Pref life time is invalid*/
    DHCP6C_ERRCODE_ADDRPREF_NOT_PRESENT,    /* 144 Addr/Prefix not found */
    DHCP6C_ERRCODE_NO_ADDR_PRESENT,         /* 145 No Address present */
    DHCP6C_ERRCODE_INVALID_PREFIX_LEN,      /* 146 Invalid prefix length */

    /* --------------------- Other Config Error Codes ----------------------- */
    DHCP6C_ERRCODE_DNSADDR_NOT_PRESENT,     /* 147 DNS server address does't exist*/
    DHCP6C_ERRCODE_NO_DNS_REQ_CONFIG,       /* 148 No DNS COnfiguration Requested */

    /* ------------------------- Key Error Codes ---------------------------- */
    DHCP6C_ERRCODE_KEY_NOT_CONFIGURED,      /* 149 No Key Configured */
    DHCP6C_ERRCODE_KEY_IN_USE,              /* 150 Key is alreay in use */
    DHCP6C_ERRCODE_DUPLICATE_KEY,           /* 151 Duplicate Key */
    DHCP6C_ERRCODE_MAX_KEY_REACHED,         /* 152 Max number of keyconfig reached*/
    DHCP6C_ERRCODE_INVALID_KEYINFO,         /* 153 Invalid Key info */
    DHCP6C_ERRCODE_INVALID_AUTHPARAMS,      /* 154 Invalid Auth params */

    /* ------------------------ Message Error Codes ------------------------- */
    DHCP6C_ERRCODE_INVALID_MESSAGE,         /* 155 Invalid Message */
    DHCP6C_ERRCODE_INVALID_MESSAGE_TYPE,    /* 156 Invalid Message Type */
    DHCP6C_ERRCODE_INVALID_MESSAGE_LEN,     /* 157 Invalid Message Length */
    DHCP6C_ERRCODE_SOLICIT_TRANS_FAILED,    /* 158 Solicit transmission failed */
    DHCP6C_ERRCODE_INFREQ_TRANS_FAILED,     /* 159 Info-Req transmission failed */
    DHCP6C_ERRCODE_RENEW_TRANS_FAILED,      /* 160 Renew transmission failed */
    DHCP6C_ERRCODE_REBIND_TRANS_FAILED,     /* 161 Rebind transmission failed */

    /* ------------------------- Option Error Codes ------------------------- */
    DHCP6C_ERRCODE_MAX_RAW_OPT_REACHED,      /* 162 MAX Raw option reached */
    DHCP6C_ERRCODE_EXCEED_RAW_OPT_MAX_VAL,   /* 163 Max Raw Options Reached */
    DHCP6C_ERRCODE_NO_RAW_OPT_CONFIG,        /* 164 No Raw option Requested */
    DHCP6C_ERRCODE_EXCEED_DUID_MAX_LEN,      /* 165 MAX DUID length         */
    DHCP6C_ERRCODE_INVALID_OPT_CODE,         /* 166 Invalid Option Code     */
    DHCP6C_ERRCODE_MSG_SIZE_EXCEEDED,        /* 167 Message size exceed     */
    DHCP6C_ERRCODE_INVALID_STATUSCODE,       /* 168 Invalid Status code     */
    DHCP6C_ERRCODE_OPT_LEN_MISMATCH,         /* 169 Option Length mismatch */
    DHCP6C_ERRCODE_OPT_MIN_LEN_ERROR,        /* 170 Option length - Underrun */
    DHCP6C_ERRCODE_OPT_MAX_LEN_ERROR,        /* 171 Option length - OverRun */
    DHCP6C_ERRCODE_NATIVE_OPTION,            /* 172 Native Option(Not raw option) */
    DHCP6C_ERRCODE_RELAY_SPECIFIC_OPTION,    /* 173 Relay specific Option */
    DHCP6C_ERRCODE_RAWOPT_NOT_PRESENT,       /* 174 Raw option not present */
    DHCP6C_ERRCODE_NO_DNSADDR_PROVIDED,      /* 175 DNS address not provided */
    DHCP6C_ERRCODE_DUPLICATE_OPTION,         /* 176 Duplicate Option in recv msg */
    DHCP6C_ERRCODE_INVALID_OPT_LENGTH,       /* 177 Invalid Option length */

    /* ------------------------ Debug Error Codes --------------------------- */
    DHCP6C_ERRCODE_INVALID_DBGLEVEL,         /* 178 Invalid debug level */
    DHCP6C_ERRCODE_INVALID_DBGENTY,          /* 179 Invalid debug entity type*/
    DHCP6C_ERRCODE_IC_CB_NOT_REGISTERED,     /* 180 IC Callbacks - Not Registed */

    /* ---------------------- Transaction Errors----------------------------- */
    DHCP6C_ERRCODE_RETRANSMISSION_FAIL_BY_MRD,  /* 181 MRD failed */
    DHCP6C_ERRCODE_RETRANSMISSION_FAIL_BY_MRC,  /* 182 MRC failed */
    DHCP6C_ERRCODE_MESSAGE_REVD_IS_NULL,        /* 183 Message received is NULL */
    DHCP6C_ERRCODE_TRANS_NOT_DELETED,           /* 184 Transaction Not deleted */
    DHCP6C_ERRCODE_INVALID_TRANS_ID,            /* 185 Transaction ID not matched */
    DHCP6C_ERRCODE_INVALID_INTERFACE_ID,        /* 186 Interface ID Not exist */
    DHCP6C_ERRCODE_INVALID_TIMER_ID,            /* 187 Timer ID not matched */
    DHCP6C_ERRCODE_TRANSMSG_NOT_PRESENT,        /* 188 Trans message not found */
    DHCP6C_ERRCODE_INVALID_REVD_MSG_LENGTH,     /* 189 Invalid received msg length*/

    /* ---------------------- Control Module Errors------------------------- */
    DHCP6C_ERRCODE_DECLINE_CTRL_MSG_FAIL,       /* 190 Decline Control Msg fail */
    DHCP6C_ERRCODE_RELEASE_CTRL_MSG_FAIL,       /* 191 Release Control Msg fail */
    DHCP6C_ERRCODE_IA_EXTENDING_LEASE,          /* 192 Already IA is extending lease */
    DHCP6C_ERRCODE_INVALID_T2_TIMEOUT,          /* 193 Invalid T2 timeout */
    DHCP6C_ERRCODE_INVALID_T3_TIMEOUT,          /* 194 Invalid T3 timeout */
    DHCP6C_ERRCODE_NO_SERVER_DUID,              /* 195 Server ID not present */

    /* ------------------------ System Errors ------------------------------- */
    DHCP6C_ERRCODE_MALLOC_FAILED,           /* 196 Memory allocation failed */
    DHCP6C_ERRCODE_EVENT_MALLOC_FAIL,       /* 197 Event Memory allocation Failed */
    DHCP6C_ERRCODE_EVENT_RT_TMR_MALLOC_FAIL,/* 198 Event RT Timer Malloc Failed */
    DHCP6C_ERRCODE_EVENT_TX_TMR_MALLOC_FAIL,/* 199 Event TX Timer Malloc Failed */
    DHCP6C_ERRCODE_WRITE_TO_QUEUE_FAILED,   /* 200 Writing Msg into Queue Failed */
    DHCP6C_ERRCODE_WRITE_EVENT_FAILED,      /* 201 Writing Event Failed */
    DHCP6C_ERRCODE_TMRCREATE_FAILED,        /* 202 Error in Creating timer */
    DHCP6C_ERRCODE_TMRDEL_FAILED,           /* 203 Error in Deleting timer */
    DHCP6C_ERRCODE_GETTMRINFO_FAILED,       /* 204 Get Timer Info Failed */
    DHCP6C_ERRCODE_FAILED_TO_OBTAIN_SEMAPHORE_LOCK,/* 205 Semaphore Lock Failed */

    /* ------------------ Socket Related Error  ----------------------------- */
    DHCP6C_SOCK_CREATION_FAILED,            /* 206 Socket creation failed */
    DHCP6C_SOCK_BIND_FAILED,                /* 207 Socket bind failed */
    DHCP6C_SOCK_SEND_FAILED,                /* 208 Socket send failed */
    DHCP6C_ERRCODE_INVALID_SOCK_EVENT,      /* 209 Invalid Socket event */

    /* ------------------- PAF  Related Error --------------------------------*/
    DHCP6C_ERRCODE_PAFVALUE_INVALID,        /* 210 Invalid PAF value     */
    DHCP6C_ERRCODE_PAF_KEY_NOT_FOUND,       /* 211 PAF key not matched   */

    /* ----------------------Init Module Errors-------------------------- */
    DHCP6C_ERRCODE_ALREADY_INIT_FAILED,     /* 212 Initialization already failed */
    DHCP6C_ERRCODE_ALREADY_INVOKED,         /* 213 Init already invoked */
    DHCP6C_ERRCODE_OUT_OF_SEQUENCE,         /* 214 Init out of sequense */
    DHCP6C_ERRCODE_NO_APPCFG_CALLBACKS_REG, /* 215 No ACPM callbacks registerd */
    DHCP6C_ERRCODE_NO_AUTH_CALLBACK_REG,    /* 216 HMACMD5 Callback not registered*/
    DHCP6C_ERRCODE_NO_DNSADDR_CALLBACK_REG, /* 217 DNS Addr Cfg CB not registered */
    DHCP6C_ERRCODE_NO_RAWOPT_CALLBACK_REG,  /* 218 Rawoption Cfg CB not registered*/

    /* ----------------------Error Codes added later--------------------- */
    DHCP6C_ERRCODE_INVALID_T1_GT_T2,        /* 219 T1 Greater than T2 */
    DHCP6C_ERRCODE_INVALID_T2_LT_T1,        /* 220 T2 is Less than T1*/
    DHCP6C_ERRCODE_INVALID_CFG_TO_START,    /* 221 Invalid configuration to start */
    DHCP6C_ERRCODE_INVALID_DST_ADDR,        /* 222 Dest. address is invalid */
    DHCP6C_ERRCODE_INFO_REQ_CREATION,       /* 223 Invalid Info-Req creation */
    DHCP6C_ERRCODE_INVALID_TRANS_OPERATION, /* 224 Invalid Post operation code */
    DHCP6C_ERRCODE_ADDRESS_ALREADY_PRESENT, /* 225 Address Already present */
    DHCP6C_ERRCODE_TIMER_ALREADY_EXPIRED,   /* 226 Timer already expired */
    DHCP6C_ERRCODE_TRANSACTION_IN_PROGRESS, /* 227 Transaction is in Progress */
    DHCP6C_ERRCODE_NO_T1_T2_FOR_IA_TA,      /* 228 No T1 and T2 for IA TA */
    DHCP6C_ERRCODE_UNSUPPORTED_TMR_RANGE,   /* 229 Unsupported Timer value range */
    DHCP6C_ERRCODE_NO_UCVCVSIO_CFG,         /* 230 No User/Vendor Class, VSO */
    DHCP6C_ERRCODE_NO_UC_CFG,               /* 231 No User Class Cfg */
    DHCP6C_ERRCODE_NO_VC_CFG,               /* 232 No Vendor Class Cfg */
    DHCP6C_ERRCODE_NO_VSIO_CFG,             /* 233 No Vendor Specific Opt Cfg */
    DHCP6C_ERRCODE_DUPLICATE_ENTERNUM,      /* 234 Duplicate Enterprise Number */
    DHCP6C_ERRCODE_VSIO_NOT_FOUND,          /* 235 VSIO Not found - Undo Failed */
    DHCP6C_ERRCODE_NO_UCVCVSIO_CALLBACK_REG,/* 236 UC VC VSIO CB not registered */
    DHCP6C_ERRCODE_EXCEED_MAX_VSIO,         /* 237 Max VSIO Already Present */

    /* ----------------------Error Codes - Authentication ------------------- */
    DHCP6C_ERRCODE_AUTH_KEY_NOT_NEGO,       /* 238 Auth Key not Nego */
    DHCP6C_ERRCODE_AUTH_HMAC_MD5_FAIL,      /* 239 HMAC_MD5 - Verfication Fail */

    /*------------------------------------------------------------------------*/
    DHCP6C_ERRCODE_PRODUCT_HOOK_TELL_DROP,  /* 240 Product receive packet process hook function tell us drop packet */

    DHCP6C_ERRCODE_MALLOC_DELETE_ADDR_FAIL, /* 241 malloc addr fail when delete an address */
    DHCP6C_ERRCODE_NOT_EXIST_SERVERINFO,    /* 242 Not exist server info */
    DHCP6C_ERRCODE_IPV6_NOT_ENABLE_ONINTF,  /* 243 Ipv6 not enable on interface */
    
    /*------------------------------------------------------------------------*/
    DHCP6C_ERRCODE_MAX,
    DHCP6C_ERRCODE_MAX_ULONG = DHCP6C_MAX_ENUM_VALUE
}DHCP6C_ERRCODE_E;

/*STRUCT< IA type >*/
typedef enum tagDHCP6C_IAType
{
    DHCP6C_IA_TYPE_NA = 0,                  /* Non Temporary IA */
    DHCP6C_IA_TYPE_TA,                      /* Temporary IA */
    DHCP6C_IA_TYPE_PD,                      /* Prefix */
    DHCP6C_IA_TYPE_MAX,                     /* The max value */
    DHCP6C_IA_TYPE_MAX_ULONG = DHCP6C_MAX_ENUM_VALUE  /* The max value */
}DHCP6C_IATYPE_E;

/*STRUCT< DHCP6 client send message type >*/
typedef enum tagDHCP6C_SENDMsgType
{
    DHCP6C_SEND_MSG_TYPE_SOLICIT = 0, /* 0<Solicit>*/
    DHCP6C_SEND_MSG_TYPE_REQUEST,     /* 1<Request>*/
    DHCP6C_SEND_MSG_TYPE_INF_REQUEST, /* 2<Information-Request>*/
    DHCP6C_SEND_MSG_TYPE_RENEW,       /* 3<Renew>*/
    DHCP6C_SEND_MSG_TYPE_REBIND,      /* 4<Rebind>*/
    DHCP6C_SEND_MSG_TYPE_CONFIRM,     /* 5<Confirm>*/
    DHCP6C_SEND_MSG_TYPE_RELEASE,     /* 6<Release>*/
    DHCP6C_SEND_MSG_TYPE_DECLINE,     /* 7<Decline>*/
    DHCP6C_SEND_MSG_TYPE_MAX,         /* 8<Decline>*/
    DHCP6C_SEND_MSG_TYPE_MAX_ULONG = DHCP6C_MAX_ENUM_VALUE /* DHCP6C_MAX_ENUM_VALUE<Max Value>*/
}DHCP6C_SENDMSGTYPE_E;

/*STRUCT< DHCP6 client receive message type >*/
typedef enum tagDHCP6C_Stat_RcvdMsgType
{
    DHCP6C_STAT_RCVD_MSG_TYPE_ADVERTISE = 0,    /* Advertise */
    DHCP6C_STAT_RCVD_MSG_TYPE_REPLY,            /* Reply */
    DHCP6C_STAT_RCVD_MSG_TYPE_RECONFIGURE,      /* Reconfigure */
    DHCP6C_STAT_RCVD_MSG_TYPE_MAX,
    DHCP6C_STAT_RCVD_MSG_TYPE_MAX_ULONG = DHCP6C_MAX_ENUM_VALUE
}DHCP6C_STAT_RECEIVEDMSGTYPE_E;

/*STRUCT< Status Code >*/
typedef enum tagDHCP6C_Stat_StatusCode
{
    DHCP6C_STAT_STATUS_CODE_SUCCESS = 0,        /* Success */
    DHCP6C_STAT_STATUS_CODE_UNSPEC_FAIL,        /* UnspecFail */
    DHCP6C_STAT_STATUS_CODE_NO_ADDRESS_AVAIL,   /* NoAddrsAvail */
    DHCP6C_STAT_STATUS_CODE_NO_BINDING,         /* NoBinding */
    DHCP6C_STAT_STATUS_CODE_NOT_ON_LINK,        /* NotOnLink */
    DHCP6C_STAT_STATUS_CODE_USE_MULTICAST,      /* UseMulticast */
    DHCP6C_STAT_STATUS_CODE_NO_PREFIX_AVAIL,    /* NoPrefixAvail */
    DHCP6C_STAT_STATUS_CODE_MAX,
    DHCP6C_STAT_STATUS_CODE_MAX_ULONG = DHCP6C_MAX_ENUM_VALUE
}DHCP6C_STAT_STATUSCODE_E;

/*STRUCT< DHCP6 client receive option statistic item >*/
typedef enum tagDHCP6C_Stat_RcvdOptionType
{
    DHCP6C_STAT_RCVD_OPTION_CLIENTID = 0,   /* Client DUID option */
    DHCP6C_STAT_RCVD_OPTION_SERVERID,       /* Server DUID option */
    DHCP6C_STAT_RCVD_OPTION_IA_NA,          /* IA NA option */
    DHCP6C_STAT_RCVD_OPTION_IA_TA,          /* IA TA option */
    DHCP6C_STAT_RCVD_OPTION_IA_PD,          /* IA PD option */
    DHCP6C_STAT_RCVD_OPTION_IAADDR,         /* IA address option */
    DHCP6C_STAT_RCVD_OPTION_IAPREFIX,       /* IA prefix option */
    DHCP6C_STAT_RCVD_OPTION_ORO,            /* Option request option */
    DHCP6C_STAT_RCVD_OPTION_PREFERENCE,     /* Preference option */
    DHCP6C_STAT_RCVD_OPTION_ELAPSED_TIME,   /* Elapsed time option */
    DHCP6C_STAT_RCVD_OPTION_UNICAST,        /* Unicast option */
    DHCP6C_STAT_RCVD_OPTION_STATUS_CODE,    /* Status code option */
    DHCP6C_STAT_RCVD_OPTION_RAPID_COMMIT,   /* Rapid commit option */
    DHCP6C_STAT_RCVD_OPTION_USER_CLASS,     /* User class option */
    DHCP6C_STAT_RCVD_OPTION_VENDOR_CLASS,   /* Vendor class option */
    DHCP6C_STAT_RCVD_OPTION_VENDOR_OPTS,    /* Vendor Specific Info. option */
    DHCP6C_STAT_RCVD_OPTION_RECONF_MSG,     /* Reconfigure message option */
    DHCP6C_STAT_RCVD_OPTION_RECONF_ACCEPT,  /* Reconfigure accept option */
    DHCP6C_STAT_RCVD_OPTION_DNS_SERVERS,    /* DNS option */
    DHCP6C_STAT_RCVD_OPTION_AUTH,           /* Authentication option */
    DHCP6C_STAT_RCVD_OPTION_RAW,            /* Raw Option */
    DHCP6C_STAT_RCVD_OPTION_MAX,
    DHCP6C_STAT_RCVD_OPTION_MAX_ULONG = DHCP6C_MAX_ENUM_VALUE
}DHCP6C_STAT_RCVDOPTIONTYPE_E;

/*STRUCT< DHCP6 client transmission parameter >*/
typedef enum tagDHCP6C_TransParamType
{
    DHCP6C_TRANS_PARAM_TYPE_IRT = 0, /* Initial Retransmission Time        */
    DHCP6C_TRANS_PARAM_TYPE_MRC,     /* Maximum Retransmission Count       */
    DHCP6C_TRANS_PARAM_TYPE_MRT,     /* Maximum Retransmission Time        */
    DHCP6C_TRANS_PARAM_TYPE_MRD,     /* Maximum Retransmission Duration    */
    DHCP6C_TRANS_PARAM_TYPE_MAX,
    DHCP6C_TRANS_PARAM_TYPE_MAX_ULONG = DHCP6C_MAX_ENUM_VALUE
}DHCP6C_TRANSPARAM_TYPE_E;

/*STRUCT< Configuration operation type >*/
typedef enum tagDHCP6C_CFG_OPT
{
    DHCP6C_CFG_OPT_DISABLE = 0, /* Disable Operation */
    DHCP6C_CFG_OPT_ENABLE,      /* Enable Operation */
    DHCP6C_CFG_OPT_ADD,         /* Add Operation */
    DHCP6C_CFG_OPT_DELETE,      /* Delete Operation */
    DHCP6C_CFG_OPT_SET,         /* Set Operation */
    DHCP6C_CFG_OPT_UNDO_SET,    /* Undo Set Operation */
    DHCP6C_CFG_OPT_MAX,
    DHCP6C_CFG_OPT_MAX_ULONG = DHCP6C_MAX_ENUM_VALUE
}DHCP6C_CFG_OPT_E;

/*STRUCT< Debug level >*/
typedef enum tagDHCP6C_DBG_LEVEL
{
    DHCP6C_DBG_LEVEL_DISABLED = 0,      /* Disabled */
    DHCP6C_DBG_LEVEL_OUTLINE,           /* Outline */
    DHCP6C_DBG_LEVEL_DETAILED,          /* Detailed */
    DHCP6C_DBG_LEVEL_MORE_DETAILED,     /* More Detailed */
    DHCP6C_DBG_LEVEL_MAX,
    DHCP6C_DBG_LEVEL_MAX_ULONG = DHCP6C_MAX_ENUM_VALUE
}DHCP6C_DBG_LEVEL_E;

/*STRUCT< Debug type >*/
typedef enum tagDHCP6C_DBG_ENTITY
{
    DHCP6C_DBG_ENTITY_ALL           = 0,            /* All */
    DHCP6C_DBG_ENTITY_MSG           = DHCP6C_BIT0,  /* Messages */
    DHCP6C_DBG_ENTITY_EVENT         = DHCP6C_BIT1,  /* Event */
    DHCP6C_DBG_ENTITY_TIMEOUT       = DHCP6C_BIT2,  /* Timeout */
    DHCP6C_DBG_ENTITY_CFG_REQUESTED = DHCP6C_BIT3,  /* Configuration Requested*/
    DHCP6C_DBG_ENTITY_CFG_LEASED    = DHCP6C_BIT4,  /* Configuration Leased */
    DHCP6C_DBG_ENTITY_CFG_AUTH      = DHCP6C_BIT5,  /* Configuration Auth */
    DHCP6C_DBG_ENTITY_SYS_SM        = DHCP6C_BIT6,  /* System State Machine */
    DHCP6C_DBG_ENTITY_REQ_SM        = DHCP6C_BIT7,  /* Request State Machine */
    DHCP6C_DBG_ENTITY_LES_SM        = DHCP6C_BIT8,  /* Leased State Machine */
    DHCP6C_DBG_ENTITY_AUTH          = DHCP6C_BIT9,  /* Authentication */
    DHCP6C_DBG_MEMORY               = DHCP6C_BIT10, /* Memory */
    DHCP6C_DBG_PACKET_VERBOSE       = DHCP6C_BIT11, /* packet verbose */
    DHCP6C_DBG_ENTITY_MAX           = DHCP6C_BIT12,
    DHCP6C_DBG_ENTITY_MAX_ULONG     = 0xFFFFFFFF
}DHCP6C_DBG_ENTITY_E;

/*STRUCT<Link layer address >*/
typedef struct tagDHCP6C_LinkLayerAddress
{
    USHORT usHardwareType;      /* Hardware type */
    USHORT usLinkLyrAddrLength; /* Link Layer address length*/    
    UCHAR ucapLinkLyrAddr[DHCP6C_MAX_LINK_LAYER_ADDR_LEN + 2];  /* Link Layer Address, ARM CPU */
}DHCP6C_LINKLAYERADDRESS_S;

#ifndef _IN6ADDR_S
#define _IN6ADDR_S
/*STRUCT<Ipv6 address>*/
typedef struct tagIN6Addr
{
    union
    {
        UCHAR     u6_ucaddr[16];
        USHORT    u6_usaddr[8];
        ULONG     u6_uladdr[4];
    } u6_addr;    /* 128-bit IP6 address */
} IN6ADDR_S;
#endif

/*STRUCT<Ipv6 address with life time>*/
typedef struct tagDHCP6C_IN6ADDRWITHTIME
{
    IN6ADDR_S stAddresss;               /* Address in IA */
    ULONG ulPreferedLifeTimeValue;      /* Prefered life time of address */
    ULONG ulValidLifeTimeValue;         /* Valid life time of address */
    UCHAR ucPrefixLength;               /* Prefix Length */
    UCHAR ucReserved1;                  /* Reserved */
    USHORT usReserved2;                 /* Reserved */
}DHCP6C_IN6ADDRWITHTIME_S;

/*STRUCT<DHCP6 client IA information>*/
typedef struct tagDHCP6C_IADESC
{
    ULONG           ulIfindex;  /* IFNET index */
    DHCP6C_IATYPE_E enIAType;   /* IA type */
    ULONG           ulIAID;     /* IAID */
}DHCP6C_IADESC_S;

/*STRUCT<DHCP6 client raw option>*/
typedef struct tagDHCP6C_RawOption
{
    USHORT usType;              /* Host byte order */
    USHORT usOptLength;         /* Host byte order */
    UCHAR *pucData;             /* Opaque - Array */
}DHCP6C_RAWOPTION_S;

/*STRUCT<DHCP6 client statistics information>*/
typedef struct tagDHCP6C_Statistics
{
    /* ---------------------------------------------------------------------- */
    /* Message Sent - Statistics */
    /* Message Sent - Total */
    ULONG ulMsgTotalSentCnt;

    /* Message Sent - New */
    ULONG ulMsgSentMsg[DHCP6C_SEND_MSG_TYPE_MAX];

    /* Message Sent - Unicasted */
    ULONG ulMsgSentUnicasted[DHCP6C_SEND_MSG_TYPE_MAX];

    /* Message Sent - Multicasted */
    ULONG ulMsgSentMulticasted[DHCP6C_SEND_MSG_TYPE_MAX];

    /* ---------------------------------------------------------------------- */
    /* Message Sent - Errors */

    /* Message Sent - ReTransmission */
    ULONG ulMsgReSent[DHCP6C_SEND_MSG_TYPE_MAX];

    /* Message Sent - Aborted */
    ULONG ulMsgSentAborted[DHCP6C_SEND_MSG_TYPE_MAX];

    /* Message Sent - Unicasted But, Multicasted */
    ULONG ulMsgSentUcastButMcasted[DHCP6C_SEND_MSG_TYPE_MAX];

    /* Message Sent - Failed (Socket send fail) */
    ULONG ulMsgSentFailed[DHCP6C_SEND_MSG_TYPE_MAX];

    /* Message Sent - Failed (Retransmission Failure) */
    ULONG ulMsgSentReTxFailed[DHCP6C_SEND_MSG_TYPE_MAX];

    /* ---------------------------------------------------------------------- */
    /* Message Received */
    /* Message Received - Total */
    ULONG ulMsgTotalRcvdCnt;

    /* Message Received */
    ULONG ulMsgRcvdMsg[DHCP6C_STAT_RCVD_MSG_TYPE_MAX];

    /* Message Received - Along with Status code*/
    ULONG ulMsgRcvdMsgSC[DHCP6C_STAT_RCVD_MSG_TYPE_MAX][DHCP6C_STAT_STATUS_CODE_MAX];

                    /* HCC Error - Line more than 80 chars It is obvious */
    /* ---------------------------------------------------------------------- */

    /* Message Received - Errors */
    /* Unknown message Received count */
    ULONG ulUnKnownMsgRcvdCnt;


    /* Message Received - Expected as Unicast Response, But Mulicast Response */
    ULONG ulMsgRcvdExpUnicastButMulticasted[DHCP6C_STAT_RCVD_MSG_TYPE_MAX];

    /* Message Received - Expected as Mulicast Response, But Unicast Response */
    ULONG ulMsgRcvdExpMulicastButUnicasted[DHCP6C_STAT_RCVD_MSG_TYPE_MAX];

    /* Message Received - In different Interface */
    ULONG ulMsgRcvdInDifferentInf[DHCP6C_STAT_RCVD_MSG_TYPE_MAX];

    /* ---------------------------------------------------------------------- */
    /* Message Received - Dropped - Malformed/Invalid Message */
    /* Message Received - Dropped - Transcation ID Not found */
    ULONG ulMsgRcvdDroppedTransIDNotFound;

    /* Message Received - Advertise Dropped - Invalid Response */
    ULONG ulMsgRcvdAdvDroppedInvalidResponse;

    /* Message Received - Reply Dropped - Invalid Response */
    ULONG ulMsgRcvdReplyDroppedInvalidResponse;

    /* Message Received - Reconfigure Dropped - Already in Progress */
    ULONG ulMsgRcvdDroppedReconfigureInProgress;

    /* Message Received - Reconfigure Dropped - Not Negotiated */
    ULONG ulMsgRcvdDroppedReconfigureNotNegotiated;

    /* Message Received - Reconfigure Dropped - Not Accepted by Client */
    ULONG ulMsgRcvdDroppedReconfigureNotAccepted;

    /* Message Received - Dropped - Parse Error */
    ULONG ulMsgRcvdDroppedParseError[DHCP6C_STAT_RCVD_MSG_TYPE_MAX];

    /* ---------------------------------------------------------------------- */
    /* Message Received - Dropped - No Data present */
    ULONG ulMsgRcvdDroppedNoData[DHCP6C_STAT_RCVD_MSG_TYPE_MAX];

    /* ---------------------------------------------------------------------- */
    /* Message Received - Dropped - Invalid Message Errors */
    /* Message Received - Dropped as Msg Type is Client send msg */
    ULONG ulMsgRcvdDroppedClientMsg[DHCP6C_SEND_MSG_TYPE_MAX];

    /* ---------------------------------------------------------------------- */
    /* Message Received - Dropped due to Errors Option */
    /* Message Received - Dropped as Option expected is not present */
    ULONG ulMsgRcvdDropOptNotPresent[DHCP6C_STAT_RCVD_MSG_TYPE_MAX][DHCP6C_STAT_RCVD_OPTION_MAX];

                    /* HCC Error - Line more than 80 chars It is obvious */

    /* Message Received - Dropped as invalid Option is present */
    ULONG ulMsgRcvdDropOptPresent[DHCP6C_STAT_RCVD_MSG_TYPE_MAX][DHCP6C_STAT_RCVD_OPTION_MAX];

                    /* HCC Error - Line more than 80 chars It is obvious */

    /* Message Received - Dropped as Option value is not matching */
    ULONG ulMsgRcvdDropOptMisMatch[DHCP6C_STAT_RCVD_MSG_TYPE_MAX][DHCP6C_STAT_RCVD_OPTION_MAX];

                    /* HCC Error - Line more than 80 chars It is obvious */
    /* Message Received - Dropped as Option is malformed */
    ULONG ulMsgRcvdDropOptError[DHCP6C_STAT_RCVD_MSG_TYPE_MAX][DHCP6C_STAT_RCVD_OPTION_MAX];

                    /* HCC Error - Line more than 80 chars It is obvious */

    /* ---------------------------------------------------------------------- */
    /* Message Received - Dropped - Authentication Errors */
    /* Message Received - Authentication - Dropped - Reply Detected */
    ULONG ulDroppedReplayDetected[DHCP6C_STAT_RCVD_MSG_TYPE_MAX];

    /* Message Received - Authentication - Accepted - Reply Detected */
    ULONG ulAcceptedReplayDetected[DHCP6C_STAT_RCVD_MSG_TYPE_MAX];

    /* ---------------------------------------------------------------------- */
    /* Message Received - Authentication Errors */

    /* Message Received - Dropped - Authentication failed */
    ULONG ulMsgDropAuthFailed[DHCP6C_STAT_RCVD_MSG_TYPE_MAX];

    /* Message Received - Dropped - No Authentication */
    ULONG ulMsgDropNoAuth[DHCP6C_STAT_RCVD_MSG_TYPE_MAX];

    /* Message Received - Accepted - Authentication failed */
    ULONG ulAcceptMsgOnAuthFailed[DHCP6C_STAT_RCVD_MSG_TYPE_MAX];

    /* Message Received - Accepted - No Authentication Option */
    ULONG ulAcceptAdvertiseAuthOptNotPresent;

    /* Message Received - Accepted - No Authentication Information */
    ULONG ulAcceptAdvertiseAuthInfoNotPresent;

    /* Message Received - Accepted - No Authentication Option */
    ULONG ulAcceptReplyAuthOptNotPresent;

    /* Message Received - Accepted - No Authentication Information*/
    ULONG ulAcceptReplyAuthInfoNotPresent;

    /* Authentication Key not found */
    ULONG ulAuthKeyNotFound;

    /* IA Dropped because of Extra addresses given by Server */
    ULONG aulIADiscardedMoreAddressPrefix[DHCP6C_IA_TYPE_MAX];

}DHCP6C_STATISTICS_S;

/*STRUCT< DUID: DHCP6 client unique Identifier >*/
typedef struct tagDHCP6C_DUID_Info
{
    ULONG ulDUID_len;                              /* DUID length */
    UCHAR aucDUID_ID[DHCP6C_MAX_DUID_VALUE_LENGTH];/* DUID Value */

}DHCP6C_DUID_INFO_S;

/*STRUCT<DHCP6 client server information>*/
typedef struct tagDHCP6C_ServerInfo
{
    DHCP6C_DUID_INFO_S  stServerDUID;          /* Servers DUID */
    DHCP6C_CFG_OPT_E    enServerUnicastEnable; /* server是否使能了单播发送 */
    IN6ADDR_S           stServerIPAddress;     /* server 地址 */
    UCHAR               ucPreference;          /* preference value */
    UCHAR               ucPadding;
    USHORT              usPadding;
}DHCP6C_SERVER_INFO_S;

/*******************************************************************************
*    Func Name: TCPIP_GenerateDUIDLLT
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 利用链路层地址+时间戳的方式生成DUID.
*        Input: DHCP6C_LINKLAYERADDRESS_S *pstLnkLyrAddr:系统中任意一个端口的链路层地址<非空>
*               ULONG ulTimeStamp:从2000年1月1日午夜至今经过的秒数模0xFFFFFFFF<[0, 0xFFFFFFFF]>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码 
*      Caution: 系统仅有一个DUID，有三种配置方式，任选其一即可:
*               1、链路层地址+时间戳
*               2、设备商自行分配
*               3、链路层地址
*               DUID作为DHCPv6 client的唯一标识，在server端会将其同client的配置参数关联起来，
*               故应该尽一切可能保证它不发生变化
*    Reference: TCPIP_GenerateDUIDEN
*               TCPIP_GenerateDUIDLL
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GenerateDUIDLLT(const DHCP6C_LINKLAYERADDRESS_S *pstLnkLyrAddr, ULONG ulTimeStamp);

/*******************************************************************************
*    Func Name: TCPIP_GenerateDUIDEN
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 通过设备商自行分配的方式来生成DUID
*        Input: ULONG ulEntrNumber:  主机序，设备商的企业编号，由IANA统一分配<ULONG>
*               UCHAR ucEntrIDLength:设备编码长度<(0, 124]>
*               UCHAR *pucEntrID:     设备编码，由该设备商自行分配<非空>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码 
*      Caution: 系统仅有一个DUID，有三种配置方式，任选其一即可:
*               1、链路层地址+时间戳
*               2、设备商自行分配
*               3、链路层地址
*               DUID作为DHCPv6 client的唯一标识，在server端会将其同client的配置参数关联起来，
*               故应该尽一切可能保证它不发生变化.
*               DUID 在START 使能接口前,添加新的DUID 将覆盖先前的DUID;
*               DUID 在START 使能接口后,添加新的DUID 将返回失败。
*    Reference: TCPIP_GenerateDUIDLLT
*               TCPIP_GenerateDUIDLL
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GenerateDUIDEN(ULONG ulEntrNumber, UCHAR ucEntrIDLength, const UCHAR *pucEntrID);

/*******************************************************************************
*    Func Name: TCPIP_GenerateDUIDLL
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 利用链路层地址生成DUID
*        Input: DHCP6C_LINKLAYERADDRESS_S *pstLnkLyrAddr:系统中任意一个端口的链路层地址<非空>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码 
*      Caution: 系统仅有一个DUID，有三种配置方式，任选其一即可:
*               1、链路层地址+时间戳
*               2、设备商自行分配
*               3、链路层地址
*               DUID作为DHCPv6 client的唯一标识，在server端会将其同client的配置参数关联起来，
*               故应该尽一切可能保证它不发生变化
*    Reference: TCPIP_GenerateDUIDEN
*               TCPIP_GenerateDUIDLLT
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GenerateDUIDLL(const DHCP6C_LINKLAYERADDRESS_S *pstLnkLyrAddr);

/*
*  Description: DHCPv6消息接收处理钩子函数
*        Input: ulRcvIFIndex: dhcpv6消息入接口索引
*               pucMsg:       dhcpv6消息(UDP报文净荷，不含UDP首部)起始地址
*               ulMsgLen:     dhcpv6消息长度，单位字节
*       Output: 
*       Return: 返回0则VISP继续处理报文，返回非0则VISP丢弃报文
*/
typedef ULONG (*TCPIP_RCV_DHCP6MSG_HOOK_FUNC)(ULONG ulRcvIFIndex, UCHAR *pucMsg, ULONG ulMsgLen);

/*******************************************************************************
*    Func Name: TCPIP_RegHookRcvDhcp6Msg
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 产品注册钩子，处理所有收到的dhcpv6消息
*        Input: TCPIP_RCV_DHCP6MSG_HOOK_FUNC pfFunc:钩子函数指针<非空>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_RegHookRcvDhcp6Msg(TCPIP_RCV_DHCP6MSG_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_AddAddrsToIA
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 配置一条IA，同时指定用户期望server为该IA分配的地址或前缀信息
*        Input: DHCP6C_IADESC_S *pstIADesc:IA结构体<非空>
*               DHCP6C_IN6ADDRWITHTIME_S *pstAddrWithTime:地址或前缀结构体指针，如果用户不清楚则设置为空指针，
*                                表示用户不指定地址，由server分配地址<非空>
*               ULONG ulAddrCnt:期望的地址或前缀个数<不能为0>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 1、每个接口的(IA type, IA ID)二元组必须在系统内部唯一，并且在系统重启后不发生变化
*               2、DHCP6C_IA_TYPE_PD(前缀列表)为路由器专用，无线的应用场景下可以不考虑
*               3、对于同一个IA，可以多次调用本接口添加多个地址或前缀
*               4、对于NA 和TA,前缀只能为0, 对于PD，前缀为大于0小于129
*    Reference: TCPIP_DelAddrFromIA
*               TCPIP_GetCfgAddrsFromIA
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_AddAddrsToIA(const DHCP6C_IADESC_S *pstIADesc, const DHCP6C_IN6ADDRWITHTIME_S *pstAddrWithTime, ULONG ulAddrCnt);

/*******************************************************************************
*    Func Name: TCPIP_DelAddrFromIA
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 删除用户期望的属于该IA的一个地址或前缀
*        Input: DHCP6C_IADESC_S *pstIADesc:  IA结构体<非空>
*               IN6ADDR_S *pstAddresss:地址或前缀结构体指针<非空>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_AddAddrsToIA
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_DelAddrFromIA(const DHCP6C_IADESC_S *pstIADesc, const IN6ADDR_S *pstAddresss);

/*******************************************************************************
*    Func Name: TCPIP_GetCfgAddrsFromIA
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 获取用户期望的属于该IA的所有地址或前缀
*        Input: DHCP6C_IADESC_S *pstIADesc:       IA结构体<非空>
*       Output: DHCP6C_IN6ADDRWITHTIME_S **ppstAddrWithTime:地址或前缀结构体，*ppstAddrWithTime指向的内存由VISP申请，调用者释放<非空>
*               ULONG *pulAddrCnt:      期望的地址或前缀个数<非空>
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_AddAddrsToIA
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GetCfgAddrsFromIA(const DHCP6C_IADESC_S *pstIADesc, DHCP6C_IN6ADDRWITHTIME_S **ppstAddrWithTime, ULONG *pulAddrCnt);

/*******************************************************************************
*    Func Name: TCPIP_GetObtainedAddrsFromIA
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 获取SERVER分配的属于该IA的所有地址或前缀
*        Input: DHCP6C_IADESC_S *pstIADesc:       IA结构体<非空>
*       Output: DHCP6C_IN6ADDRWITHTIME_S **ppstAddrWithTime:地址或前缀结构体，*ppstAddrWithTime指向的内存由VISP申请，调用者释放<非空>
*               ULONG *pulAddrCnt:      地址或前缀个数<非空>
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 目前只有NA可以从SERVER分配地址;TA和PD暂不支持。
*    Reference: TCPIP_GetCfgAddrsFromIA
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GetObtainedAddrsFromIA(const DHCP6C_IADESC_S *pstIADesc, DHCP6C_IN6ADDRWITHTIME_S **ppstAddrWithTime, ULONG *pulAddrCnt);

/*******************************************************************************
*    Func Name: TCPIP_SetRapidCommit
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 设置是否使能快速DHCP过程
*        Input: ULONG ulIfIndex:      接口索引<非0>
*               DHCP6C_CFG_OPT_E ulOperationType:操作类型<DHCP6C_CFG_OPT_DISABLE:0或DHCP6C_CFG_OPT_ENABLE:1>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_GetRapidCommit
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_SetRapidCommit(ULONG ulIfIndex, DHCP6C_CFG_OPT_E ulOperationType);

/*******************************************************************************
*    Func Name: TCPIP_GetRapidCommit
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 获取是否使能快速DHCP过程的开关
*        Input: ULONG ulIfIndex:       接口索引<非0>
*       Output: DHCP6C_CFG_OPT_E *pulOperationType:操作类型<enable或disable>
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_SetRapidCommit
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GetRapidCommit(ULONG ulIfIndex, DHCP6C_CFG_OPT_E *pulOperationType);

/*******************************************************************************
*    Func Name: TCPIP_SetDNS6ServerRequest
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 用户配置DNS Server选项
*        Input: ULONG ulIfIndex:      接口索引<非0>
*               IN6ADDR_S *pstAddress:     用户期望的DNS Server 地址数组，如果用户不清楚则设置为空指针，
*                                此时完全由DHCPv6 Server负责分配
*               ULONG *ulAddressCnt:   DNS Server 地址个数，对于删除操作该值必须为1
*               DHCP6C_CFG_OPT_E ulOperationType:操作类型<add或delete>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_GetCfgDNS6ServerAddrs
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_SetDNS6ServerRequest(ULONG ulIfIndex, const IN6ADDR_S *pstAddress, 
                              ULONG ulAddressCnt, DHCP6C_CFG_OPT_E ulOperationType); 

/*******************************************************************************
*    Func Name: TCPIP_GetCfgDNS6ServerAddrs
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 获取用户配置的DNS Server 地址列表
*        Input: ULONG ulIfIndex:      接口索引<非0>
*       Output: IN6ADDR_S **ppstAddress:    DNS Server 地址数组，*ppstAddress指向的内存由VISP申请，调用者释放<非空>
*               ULONG *pulAddressCount:地址个数，pulAddressCount指向的内存由调用者申请和释放<非空>
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_SetDNS6ServerRequest
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GetCfgDNS6ServerAddrs(ULONG ulIfIndex, IN6ADDR_S **ppstAddress, ULONG *pulAddressCount);

/*******************************************************************************
*    Func Name: TCPIP_SetRawOption
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 用户直接以tlv方式指定option，VISP不解释这些option的具体内容，直接编码在dhcp报文里
*        Input: ULONG ulIfIndex:          接口索引<非0>
*               DHCP6C_RAWOPTION_S *pstRawOptionRequest:option数据区<非空>
*               DHCP6C_CFG_OPT_E ulOperationType:    操作类型<add或delete>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 不能设置如下选项类型:
*               1~9、11~14、18、19、20、23、25、26、37、38 
*    Reference: TCPIP_GetCfgRawOptions
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_SetRawOption(ULONG ulIfIndex, const DHCP6C_RAWOPTION_S *pstRawOptionRequest, DHCP6C_CFG_OPT_E ulOperationType);

/*******************************************************************************
*    Func Name: TCPIP_GetCfgRawOptions
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 获取用户设置的所有raw option
*        Input: ULONG ulIfIndex:接口索引<非0>
*       Output: DHCP6C_RAWOPTION_S **ppstRawOptionRequest:raw option数据区，*ppstRawOptionRequest指向的内存由VISP申请，调用者释放<非空>
*               ULONG *pulRawOptCnt:raw option个数<非空>
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_SetRawOption
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GetCfgRawOptions(ULONG ulIfIndex, DHCP6C_RAWOPTION_S **ppstRawOptionRequest, ULONG *pulRawOptCnt);

/*******************************************************************************
*    Func Name: TCPIP_StartDhcpOnIF
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 在一个接口上使能dhcpv6 client功能
*        Input: ULONG ulIfIndex:接口索引<非0>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 必须保证该接口上的DHCP参数配置完毕，然后再执行start操作
*    Reference: TCPIP_StopDhcpOnIF
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_StartDhcpOnIF(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_StopDhcpOnIF
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 去使能接口的dhcpv6 client功能
*        Input: ULONG ulIfIndex:接口索引<非0>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_StartDhcpOnIF
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_StopDhcpOnIF(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetDhcp6ServerInfo
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 获取指定接口的dhcpv6 server信息
*        Input: ULONG ulIfIndex:    接口索引<非0>
*       Output: pDHCP6C_SERVER_INFO_S *stServerInfo: server信息<非空>
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 1. DHCP6 client使能并获取信息成功时获取server信息成功;
*               2. DHCP6 client未使能,或者使能获取信息失败时不存在server信息,获取server信息会失败;
*               3. DHCP6 client当前不存在从server获取的信息时,获取server信息会失败;
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GetDhcp6ServerInfo(ULONG ulIfIndex, DHCP6C_SERVER_INFO_S *pstServerInfo);

/*******************************************************************************
*    Func Name: TCPIP_ReleaseAddrs
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 释放IA里的某些地址或前缀
*        Input: DHCP6C_IADESC_S *pstIADesc: IA结构体<非0>
*               DHCP6C_IN6ADDRWITHTIME_S *pstAddress:地址或前缀结构体<非空>
*               ULONG ulAddrCnt: 地址或前缀个数<非0>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 1、释放地址,可以不指定前缀,也可以指定前缀;
*               2、释放前缀,一定要指明哪个地址的前缀。
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_ReleaseAddrs(const DHCP6C_IADESC_S *pstIADesc, const DHCP6C_IN6ADDRWITHTIME_S *pstAddress, ULONG ulAddrCnt);

/*******************************************************************************
*    Func Name: TCPIP_ReleaseIA
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 释放IA里的所有地址或前缀
*        Input: DHCP6C_IADESC_S *pstIADesc:IA结构体<非空>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_ReleaseIA(const DHCP6C_IADESC_S *pstIADesc);

/*******************************************************************************
*    Func Name: TCPIP_ReleaseByIF
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 释放指定接口上指定类型的所有IA
*        Input: ULONG ulIfIndex:接口索引<非0>
*               DHCP6C_IATYPE_E enIAType: IA类型
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_ReleaseByIF(ULONG ulIfIndex, DHCP6C_IATYPE_E enIAType);

/*******************************************************************************
*    Func Name: TCPIP_ReleaseAll
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 释放系统里的所有IA
*        Input: 
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_ReleaseAll(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ConfirmCfg
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 向server发送confirm报文，以确认一个接口上的dhcpv6配置是否仍然有效。
*               如果某个接口连接到的网络发生了变化，但系统尚未掉电，可以使用本接口进行确认。
*        Input: ULONG ulIfIndex: 接口索引<非空>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_ConfirmCfg(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcp6TranParams
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 设置dhcp6的各项重传参数
*        Input: DHCP6C_SENDMSGTYPE_E enMsgType:       dhcp6消息类型
*               DHCP6C_TRANSPARAM_TYPE_E enTransParamType:重传参数类型
*               ULONG ulParamValue:    重传参数取值
*               DHCP6C_CFG_OPT_E ulOperationType: 操作类型<set或undo set，undo set即恢复默认值>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_GetDhcp6TransParams
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_SetDhcp6TranParams(DHCP6C_SENDMSGTYPE_E enMsgType, DHCP6C_TRANSPARAM_TYPE_E enTransParamType, ULONG ulParamValue, DHCP6C_CFG_OPT_E ulOperationType);

/*******************************************************************************
*    Func Name: TCPIP_GetDhcp6TransParams
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 获取dhcp6的各项重传参数
*        Input: DHCP6C_SENDMSGTYPE_E enMsgType:       dhcp6消息类型
*               DHCP6C_TRANSPARAM_TYPE_E enTransParamType:重传参数类型
*       Output: ULONG *pulParamValue:   重传参数取值<非空>
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_SetDhcp6TranParams
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GetDhcp6TransParams(DHCP6C_SENDMSGTYPE_E enMsgType, DHCP6C_TRANSPARAM_TYPE_E enTransParamType, ULONG *pulParamValue);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpMaxRetryTimes
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 设置dhcp6在配置失败之后的重新尝试次数
*        Input: ULONG ulMaxRetries:   重新尝试次数<[0, 16]>
                DHCP6C_CFG_OPT_E ulOperationType:操作类型<set或undo set，undo set即恢复默认值3>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_GetDhcpMaxRetryTimes
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_SetDhcpMaxRetryTimes(ULONG ulMaxRetries, DHCP6C_CFG_OPT_E ulOperationType);

/*******************************************************************************
*    Func Name: TCPIP_GetDhcpMaxRetryTimes
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 获取dhcp6在配置失败之后的重新尝试次数
*        Input: 
*       Output: ULONG *pulMaxRetries:重新尝试次数<非空>
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_SetDhcpMaxRetryTimes
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GetDhcpMaxRetryTimes(ULONG *pulMaxRetries);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcp6DbgLevel
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 设置dhcp6的debug等级
*        Input: DHCP6C_DBG_LEVEL_E enDbgLevel: 调试等级
                DHCP6C_DBG_ENTITY_E enDbgEntity:调试对象
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_SetDhcp6DbgLevel(DHCP6C_DBG_LEVEL_E enDbgLevel, DHCP6C_DBG_ENTITY_E enDbgEntity);

/*******************************************************************************
*    Func Name: TCPIP_GetDhcp6Stat
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 获取dhcp6的接口统计信息
*        Input: ULONG ulIfIndex:    接口索引<非0>
*               DHCP6C_STATISTICS_S *pstStatistics:统计信息结构体，指向的内存由调用者负责申请和释放<非空>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_ResetDhcp6Stat
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_GetDhcp6Stat(ULONG ulIfIndex, DHCP6C_STATISTICS_S *pstStatistics);

/*******************************************************************************
*    Func Name: TCPIP_ResetDhcp6Stat
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 清空dhcp6的接口统计信息
*        Input: ULONG ulIfIndex:接口索引<非0>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: TCPIP_GetDhcp6Stat
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_ResetDhcp6Stat(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ShowDhcp6Stat
* Date Created: 2009-12-17
*       Author: wujie 61195
*      Purpose: 
*  Description: 显示dhcp6的接口统计信息
*        Input: ULONG ulIfIndex:接口索引<非0>
*       Output: 
*       Return: 成功返回DHCP6C_OK
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-17   wujie 61195             Create
*
*******************************************************************************/
ULONG TCPIP_ShowDhcp6Stat(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ShowDhcp6InfoOnIF
* Date Created: 2010-01-30
*       Author: 60786
*      Purpose: 
*  Description: 显示指定接口的dhcp6 client配置信息及部分重要信息,用于调试定位
*        Input: ULONG ulIfIndex:接口索引<非0>
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: TCPIP_ShowAllDhcp6Info
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-30   W60786                  Create
*
*******************************************************************************/
VOID TCPIP_ShowDhcp6InfoOnIF(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ShowAllDhcp6Info
* Date Created: 2009-12-17
*       Author: 60786
*      Purpose: 
*  Description: 显示系统中所有dhcp6 client信息,用于调试定位
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: TCPIP_ShowDhcp6InfoOnIF
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-30   W60786                  Create
*
*******************************************************************************/
VOID TCPIP_ShowAllDhcp6Info(VOID);


#ifdef __cplusplus
}
#endif

#endif

