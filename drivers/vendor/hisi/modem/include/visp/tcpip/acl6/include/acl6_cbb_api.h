/***********************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              acl6_cbb_api.h
 *
 *  Project Code: VISP1.8
 *   Module Name: ACL6
 *  Date Created: 
 *        Author: 
 *   Description: ACL6 CBB对外提供的数据结构定义和函数声明
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 ***********************************************************************************/
#ifndef _ACL6_CBB_API_H_
#define _ACL6_CBB_API_H_

#ifdef  __cplusplus
extern "C" 
{
#endif

/* ACL6的错误码 */
enum enumAcl6Help
{
    Help_ACL6_OK = 0,
    Help_ACL6_ERR = MID_COMP_ACL6 + 1,   /* 1 无用 */
    Help_ACL6_NullPoint,                 /* 2 输入指针为空 */
    Help_ACL6_InitErr,                   /* 3 ACL6 CBB已经完成初始化*/
    Help_ACL6_NotInit,                   /* 4 ACL6 CBB未成功初始化*/
    Help_ACL6_CreateSmErr,               /* 5 创建信号量失败 */
    Help_ACL6_TooMuchRulesInSys,         /* 6 规则数超过系统上限 */
    Help_ACL6_TooMuchRulesInGroup,       /* 7 规则数超过规则组上限 */
    Help_ACL6_OperTypeErr,               /* 8 错误的操作类型*/ 
    Help_ACL6_GroupIndexErr,             /* 9 规则组索引错误 */
    Help_ACL6_GroupExist,                /* 10 规则组已经存在 */
    Help_ACL6_GroupNotExist,             /* 11 规则组不存在 */
    Help_ACL6_MatchOrderErr,             /* 12 规则组匹配顺序错误 */
    Help_ACL6_StepErr,                   /* 13 错误的步长 */
    Help_ACL6_DescriptionTooLong,        /* 14 输入规则组描述信息超过128字节 */
    Help_ACL6_NotChangeMatchOrder,       /* 15 规则组配置规则后不可改变匹配顺序 */
    Help_ACL6_RuleNotExist,              /* 16 规则不存在 */
    Help_ACL6_RuleExist,                 /* 17 规则已经存在 */
    Help_ACL6_RuleIndexTooLarge,         /* 18 规则索引用完，无法分配新的规则索引*/
    Help_ACL6_CanNotGiveRuleIndex,       /* 19 规则组配置顺序为自动匹配时，不允许指定规则号 */
    Help_ACL6_DescriptionInvalid,        /* 20 输入规则组描述信息不合法 */
    Help_ACL6_RuleIndexErr,              /* 21 分配规则索引错误 */
    Help_ACL6_CanNotModify,              /* 22 自动匹配时禁止修改规则 */
    Help_ACL6_RuleManageErr,             /* 23 配置规则失败 */
    Help_ACL6_RuleNodeMallocErr,         /* 24 分配规则节点失败 */
    Help_ACL6_CfgOpErr,                  /* 25 规则配置选项错误 */
    Help_ACL6_ActionErr,                 /* 26 规则Action取值错误 */
    Help_ACL6_SrcAddrMaskErr,            /* 27 规则信息源地址掩码长度错误*/
    Help_ACL6_DstAddrMaskErr,            /* 28 规则信息目的地址掩码长度错误*/
    Help_ACL6_HopLmErr,                  /* 29 Hop Limit值取值错误 */
    Help_ACL6_ClassErr,                  /* 30 优先级取值错误 */
    Help_ACL6_FragErr,                   /* 31 分片标记取值错误 */
    Help_ACL6_SrcPortTypeErr,            /* 32 源端口类型错误 */
    Help_ACL6_SrcPortRangeErr,           /* 33 源端口范围错误 */
    Help_ACL6_DstPortTypeErr,            /* 34 目的端口类型错误 */
    Help_ACL6_DstPortRangeErr,           /* 35 目的端口范围错误 */
    Help_ACL6_ProtocalErr,               /* 36 协议号错误 */
    Help_ACL6_GetVrfIndexErr,            /* 37 获取VRF Index失败 */
    Help_ACL6_IfIndexErr,                /* 38 接口索引非法 */
    Help_ACL6_MallocErr,                 /* 39 配置过程中分配内存错误 */
    Help_ACL6_TypeNotExist,              /* 40 规则类型不存在 */
    Help_ACL6_TypeIdErr,                 /* 41 规则类型ID错误 */
    Help_ACL6_ContentNull,               /* 42 规则信息数据结构中的规则内容指针为空*/
    Help_ACL6_ContentSizeZero,           /* 43 注册类型数据结构中的规则内容大小为0*/
    Help_ACL6_FuncNull,                  /* 44 注册类型数据结构中有函数指针为空*/
    Help_ACL6_PortNumErr,                /* 45 端口范围的段数不合法 */
    Help_ACL6_GroupMallocErr,            /* 46 为规则组分配内存失败 */
    Help_ACL6_TypeBasicMallocErr,        /* 47 为基本规则类型分配内存失败 */
    Help_ACL6_TypeAdvMallocErr,          /* 48 为高级规则类型分配内存失败 */
    Help_ACL6_TypeIfMallocErr,           /* 49 为基于接口规则类型分配内存失败 */
    Help_ACL6_GroupBasicMallocErr,       /* 50 为基本规则组分配内存失败 */
    Help_ACL6_GroupAdvMallocErr,         /* 51 为高级规则组分配内存失败 */
    Help_ACL6_GroupIfMallocErr,          /* 52 为基于接口的规则组分配内存失败 */
    Help_ACL6_WaitlistOpenFail,          /* 53 打开waitlist失败 */
    Help_ACL6_WaitlistSetFail,           /* 54 设置waitlist失败 */
    Help_ACL6_WaitlistGetFail,           /* 55 获取waitlist节点失败 */
    Help_ACL6_WaitlistCloseFail,         /* 56 关闭waitlist失败 */
    Help_ACL6_GetMatchCountErr,          /* 57 获取PPI数据面的规则匹配统计信息失败 */
    Help_ACL6_End,                       /* 58 遍历表项时到达最后一条表项 */
    Help_ACL6_DefaultPortErr,            /* 59 Protocal设置为区段时，必须指定将源端口号和目的端口号恢复为默认值 */
    Help_ACL6_SetPortRgWithInvalidPro,   /* 60 设置端口号时，必须协议类型必须为单一值，
                                                                                     且仅支持ICMP6、TCP6、UDP6、SCTP */
    Help_ACL6_Icmp6TypeErr,              /* 61 ICMP6 类型错误 */
    Help_ACL6_Icmp6CodeErr,              /* 62 ICMP6 Code错误 */
    Help_ACL6_PpiFuncNotExist,           /* 63 PPI下发函数未注册 */
    Help_ACL6_PpiUpdateErr,              /* 64 PPI下发函数失败 */
    Help_ACL6_RuleNotFound,              /* 65 没有找到匹配规则 */
    Help_ACL6_MbufOperErr,               /* 66 Mbuf操作失败 */
    Help_ACL6_MbufPktNull,               /* 67 Mbuf数据段为空*/
    Help_ACL6_GetIpv6VTable,             /* 68 获取ipv6组件虚表失败 */
    Help_ACL6_CALLBACK_EXIST,            /* 69 同一模块的回调函数已经注册 */
    Help_ACL6_NoRuleInGroup,             /* 70 规则组下没有任何规则 */
    Help_ACL6_MbufNull,                  /* 71 Mbuf为空 */
    
    Help_ACLFW6_ERR_GET_PRECONFIG,       /* 72 Not able to extract preconfig value */
    Help_ACLFW6_ERR_HASH_INIT,           /* 73 Unable to initailize the hash table */
    Help_ACLFW6_ERR_NULL,                /* 74 Null Input */
    Help_ACLFW6_ERR_INTERFACE_NAME,      /* 75 Interface name length is not valid*/
    Help_ACLFW6_ERR_GET_IFINDEX,         /* 76 Unable to derive IfIndex based on Interface name */    
    Help_ACLFW6_INVALID_FLAG,            /* 77 Invalid operation flag it must be ACLFW6_CFG_DEL/ACLFW6_CFG_ADD */
    Help_ACLFW6_INVALID_DIRECTION,       /* 78 Invalid filter direction.*/
    Help_ACLFW6_INVALID_PERMISSION,      /* 79 Invalid ACL6 permission it must be either ACL6_DENY or ACL6_PERMIT */
    Help_ACLFW6_GROUP_NOT_EXIST,         /* 80 The group does not exist */
    Help_ACLFW6_ERR_CFGSECPOLICY_INIT,   /* 81 ACLFW6 Securiy policy module is not initialized*/
    Help_ACLFW6_ERR_NO_NODE,             /* 82 There is no aclgroup assigned to interface*/
    Help_ACLFW6_ERR_HASH_INVALID_PARA,   /* 83 Unable to initialize the hash table*/
    Help_ACLFW6_ERR_HASH_MALLOC_FAIL,    /* 84 Malloc failure for hash table*/
    Help_ACLFW6_HASH_TABLE_OK,           /* 85 If the hash insertion is successful */
    Help_ACLFW6_HASH_TABLE_ITEM_EXIST,   /* 86 If the hash table already have the entry for a given key*/
    Help_ACLFW6_ERR_HASH_INSERT_TYPE,    /* 87 Invalid hash insertion type is used.*/
    Help_ACLFW6_HASH_TABLE_FULL,         /* 88 Error when hash table is filled */    
    Help_ACLFW6_HASH_ITEM_NOT_EXIST,     /* 89 No entry is present in hash table for a given key*/    
    Help_ACLFW6_ERR_NO_MATCH,            /* 90 The cofig value does not matched with the entry */        
    Help_ACLFW6_ERR_MALLOC,              /* 91 malloc failure*/
    Help_ACLFW6_ERR_IF_TABLE,            /* 92 Unable to open the ifnet table*/    
    Help_ACLFW6_ERR_GET_IF_TABLE,        /* 93 Error to get interface entry from ifnet table*/    
    Help_ACLFW6_END_IF_TABLE,            /* 94 End of ifnet waitlst table */
    Help_ACLFW6_ERR_FILTER_INPUT,        /* 95 Using filter with waitlsit next api is not permited */
    Help_ACLFW6_ERR_IF_TABLE_CLOSE,      /* 96 Unable to close waitlist table of IFNET for a given handle.*/
    Help_ACLFW6_ERR_HASH_TABLE_NULL,     /* 97 Invalid input for hash table delete*/
    Help_ACLFW6_ERR_PPI_CFG_DOWNLOAD,    /* 98 Unable to download the PPI info.*/
    Help_ACLFW6_INVALID_STAT_SWITCH,     /* 99 Invalid flow statistsic switch option.*/

    Help_ACL6_Max   /* 标识枚举字上限,非实际错误码, 请在之前添加新的错误码 */
};

/**********************************************************
*   规则相关宏定义
***********************************************************/
/*规则组操作类型*/
#define ACL6_DEL 0
#define ACL6_ADD 1

/* 规则匹配后操作字 */
#define ACL6_DENY         0 
#define ACL6_PERMIT       1

/*接口过滤类型*/
#define ACL6_IFIN    1    /* 入接口过滤 */
#define ACL6_IFOUT   2    /* 出接口过滤 */
#define ACL6_IFANY   3    /* 入或出接口过滤 */

#define ACL6_CFG_NOOPER  0 /*不配置标记*/
#define ACL6_CFG_SET     1 /*配置标记*/
#define ACL6_CFG_DEFAULT 2 /*恢复默认值标记*/

/* 规则组匹配顺序 */
#define ACL6_MATCHORDER_CONFIG   1
#define ACL6_MATCHORDER_AUTO     2

/* 缺省规则类型ID */
#define ACL6_BASIC_RULE_TYPE     1
#define ACL6_ADVANCE_RULE_TYPE   2
#define ACL6_IFBASED_RULE_TYPE   3

#define ACL6_MAX_VRFNAME_LENGTH  31   /* VRF名字描述信息长度 */    
#define ACL6_DESCRIPTIONSTR_LEN  127  /* 规则组描述信息长度 */

/* 无效规则组序号 */
#define ACL6_INVALID_GROUP_INDEX    0
/* 无效规则索引 */
#define ACL6_INVALID_RULE_INDEX     0xFFFFFFFFL
/* IPv6地址长度 */
#define ACL6_IPV6_ADDR_LEN 16
/* 任意接口索引 */
#define ACL6_IFINDEXANY 0
/* 任意VRF索引 */
#define ACL6_ANY_VRFINDEX     0xFFFFFFFFL

/* 产品需要使用默认步长,所以在API中定义一份,注意该宏定义必须与acl6_def.h中的ACL6_DEFAULT_STEP定义保持一致 */
/* 规则组默认步长 */
#ifndef ACL6_DEFAULT_STEP
#define ACL6_DEFAULT_STEP 5
#endif
/**********************************************************
*   忽略位相关宏定义，在报文匹配时可对指定字段不予比较
***********************************************************/
/* 忽略字段各位的定义 */
#define ACL6_SIPByte     0x0001     
#define ACL6_DIPByte     0x0002
#define ACL6_PROByte     0x0004
#define ACL6_HLMByte     0x0008
#define ACL6_CLSByte     0x0010
#define ACL6_SPORTByte   0x0020
#define ACL6_DPORTByte   0x0040
#define ACL6_VRFByte     0x0080

/* 端口比较类型 */
typedef enum enumAcl6PortOpType
{
    ACL6_PORT_OP_TYPE_IN, /* 0: us*Begin <= IN <= us*End */  
    ACL6_PORT_OP_TYPE_EQ, /* 1: IN == us*Begin */
    ACL6_PORT_OP_TYPE_NEQ,/* 2: IN != us*Begin */  
    ACL6_PORT_OP_TYPE_GE, /* 3: IN >= us*Begin */
    ACL6_PORT_OP_TYPE_LE, /* 4: IN <= us*Begin */
    ACL6_PORT_OP_TYPE_MAX
}ACL6_PORT_OP_TYPE_E;

/**********************************************************
*   对外数据结构
***********************************************************/
/* 存放规则中的IPv6地址和掩码 */
typedef struct tagAcl6Ip6Addr 
{
    UCHAR ucAddr[ACL6_IPV6_ADDR_LEN];    /*IPv6地址信息*/
    ULONG ulMaskLen;     /*IPv6地址掩码长度*/
} ACL6_IP6ADDR_S;

/* ACL6查询过滤器*/
typedef struct tagAcl6Filter
{    
    ULONG  ulGroupIndex; /*规则组索引*/
    ULONG  ulRuleIndex;  /*规则索引*/
}ACL6_FILTER_S;

/* ACL6 规则组配置结构*/
typedef struct tagAcl6CfgManageGroup
{
    ULONG ulOperType;           /*操作类型:ACL6_ADD－创建或更新；ACL6_DEL－删除*/
    ULONG ulGroupIndex;         /*规则组索引*/
    ULONG ulSetMatchOrder;      /*是否设置匹配顺序:
                                  ACL6_CFG_NOOPER － 不配置标记；
                                  ACL6_CFG_SET － 配置标记；
                                  ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulMatchOrder;         /*匹配顺序:(默认为ACL6_MATCHORDER_CONFIG)
                                  ACL6_MATCHORDER_CONFIG － 配置顺序
                                  ACL6_MATCHORDER_AUTO － 自动顺序*/      
    ULONG ulSetStep;            /*是否设置步长:
                                  ACL6_CFG_NOOPER － 不配置标记；
                                  ACL6_CFG_SET － 配置标记；
                                  ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulStep;               /*步长，范围1-20(默认为5)*/
    ULONG ulSetDes;             /*是否设置描述信息:
                                  ACL6_CFG_NOOPER － 不配置标记；
                                  ACL6_CFG_SET － 配置标记；
                                  ACL6_CFG_DEFAULT － 恢复默认值标记*/
    CHAR szDescription[ACL6_DESCRIPTIONSTR_LEN + 1];/*描述信息，1-127个字符*/
}ACL6_CFG_MANAGEGROUP_S;

/* ACL6 基本规则配置结构*/
typedef struct tagAcl6CfgBasicRule
{
    ULONG ulOperType;     /*操作类型:ACL6_ADD－创建或更新；ACL6_DEL－删除*/
    ULONG ulGroupIndex;
    ULONG ulRuleIndex;
    ULONG ulVrfOp;        /*暂不支持该特性
                            是否设置报文VRF域名称:
                            ACL6_CFG_NOOPER － 不配置标记；
                            ACL6_CFG_SET － 配置标记；
                            ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulVrfIndex;
    ULONG ulActionOp;     /*是否设置action的操作类型：
                             ACL6_CFG_NOOPER － 不配置标记；
                             ACL6_CFG_SET － 配置标记；
                             ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulAction;       /*待配置的新的action值:(默认为ACL6_DENY)
                             ACL6_DENY － Deny
                             ACL6_PERMIT － Permit*/
    ULONG ulFragOp;         /*是否设置报文分片标志:
                              ACL6_CFG_NOOPER － 不配置标记；
                              ACL6_CFG_SET － 配置标记；
                              ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulFrag;           /*报文分片(默认为0，不分片)*/
    ULONG ulSrcIpOp;      /*是否设置报文源地址:
                            ACL6_CFG_NOOPER － 不配置标记；
                            ACL6_CFG_SET － 配置标记；
                            ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ACL6_IP6ADDR_S stSrcIp;/*报文源地址(默认为0，掩码默认128)*/
}ACL6_CFG_BASIC_RULE_S;

/* ACL6 端口范围结构*/
typedef struct tagAcl6PortRange
{
    USHORT usBegin;  /*起始端口*/
    USHORT usEnd;    /*终止端口*/
}ACL6_PORT_RANGE_S;

/* ACL6 高级规则配置结构*/
typedef struct tagAcl6CfgAdvRule
{
    ULONG ulOperType;       /*操作类型:ACL6_ADD－创建或更新；ACL6_DEL－删除*/
    ULONG ulGroupIndex;
    ULONG ulRuleIndex;
    ULONG ulVrfOp;          /*暂不支持该特性
                            是否设置报文VRF域名称:
                            ACL6_CFG_NOOPER － 不配置标记；
                            ACL6_CFG_SET － 配置标记；
                            ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulVrfIndex;
    ULONG ulActionOp;       /*是否设置action的操作类型：
                               ACL6_CFG_NOOPER － 不配置标记；
                               ACL6_CFG_SET － 配置标记；
                               ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulAction;         /*待配置的新的action值:(默认为ACL6_DENY)
                               ACL6_DENY － Deny
                               ACL6_PERMIT － Permit*/
    ULONG ulFragOp;         /*是否设置报文分片标志:
                              ACL6_CFG_NOOPER － 不配置标记；
                              ACL6_CFG_SET － 配置标记；
                              ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulFrag;           /*报文分片(默认为0，不分片)*/
    ULONG ulSrcIpOp;        /*是否设置报文源地址:
                              ACL6_CFG_NOOPER － 不配置标记；
                              ACL6_CFG_SET － 配置标记；
                              ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ACL6_IP6ADDR_S stSrcIp; /*报文源地址(默认为0，掩码默认128)*/
    ULONG ulDstIpOp;        /*是否设置报文目的地址:
                              ACL6_CFG_NOOPER － 不配置标记；
                              ACL6_CFG_SET － 配置标记；
                              ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ACL6_IP6ADDR_S stDstIp; /*报文目的地址(默认为0，掩码默认128)*/
    ULONG ulHopLmOp;        /*是否设置报文Hop Limit:
                              ACL6_CFG_NOOPER － 不配置标记；
                              ACL6_CFG_SET － 配置标记；
                              ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulHopLm;          /*报文Hop Limit(默认为255)*/
    ULONG ulClassOp;        /*是否设置报文Traffic Class:
                              ACL6_CFG_NOOPER － 不配置标记；
                              ACL6_CFG_SET － 配置标记；
                              ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulClass;          /*报文Traffic Class(默认为255)*/
    ULONG ulSrcPortOp;      /*是否设置报文源端口标志:
                              ACL6_CFG_NOOPER － 不配置标记；
                              ACL6_CFG_SET － 配置标记；
                              ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulSrcPortOpType;  /*端口比较类型:(默认为ACL6_PORT_OP_TYPE_IN)
                              ACL6_PORT_OP_TYPE_IN - 范围内
                              ACL6_PORT_OP_TYPE_EQ - 等于
                              ACL6_PORT_OP_TYPE_NEQ - 不等于
                              ACL6_PORT_OP_TYPE_GE - 大于
                              ACL6_PORT_OP_TYPE_LE - 小于*/
    ACL6_PORT_RANGE_S stSrcPort;/*报文源端口(默认为Begain:0,End:65535)*/
    ULONG ulDstPortOp;      /*是否设置报文目的端口标志:
                              ACL6_CFG_NOOPER － 不配置标记；
                              ACL6_CFG_SET － 配置标记；
                              ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulDstPortOpType;  /*端口比较类型:(默认为ACL6_PORT_OP_TYPE_IN)
                              ACL6_PORT_OP_TYPE_IN - 范围内
                              ACL6_PORT_OP_TYPE_EQ - 等于
                              ACL6_PORT_OP_TYPE_NEQ - 不等于
                              ACL6_PORT_OP_TYPE_GE - 大于
                              ACL6_PORT_OP_TYPE_LE - 小于*/
    ACL6_PORT_RANGE_S stDstPort;/*报文目的端口(默认为Begain:0,End:65535)*/
    ULONG ulProtoOp;        /*是否设置报文协议类型标志:
                              ACL6_CFG_NOOPER － 不配置标记；
                              ACL6_CFG_SET － 配置标记；
                              ACL6_CFG_DEFAULT － 恢复默认值标记*/
    UCHAR ucProtoBegin;     /*报文协议类型(默认为0)*/
    UCHAR ucProtoEnd;       /*报文协议类型(默认为255)*/
    UCHAR ucPadding[2];
}ACL6_CFG_ADV_RULE_S;

/* ACL6 基于接口规则配置结构*/
typedef struct tagAcl6CfgIfBasedRuleInfo
{
    ULONG ulOperType;       /*操作类型:
                               ACL6_ADD－创建或更新；
                               ACL6_DEL－删除*/
    ULONG ulGroupIndex;
    ULONG ulRuleIndex;
    ULONG ulActionOp;       /*是否设置action的操作类型：
                               ACL6_CFG_NOOPER － 不配置标记；
                               ACL6_CFG_SET － 配置标记；
                               ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulAction;         /*待配置的新的action值:(默认为ACL6_DENY)
                               ACL6_DENY － Deny
                               ACL6_PERMIT － Permit*/
    ULONG ulIfOp;           /*是否设置接口标志：
                               ACL6_CFG_NOOPER － 不配置标记；
                               ACL6_CFG_SET － 配置标记；
                               ACL6_CFG_DEFAULT － 恢复默认值标记*/
    ULONG ulIfIndex;        /*待配置的新的接口索引(默认值为0)*/
} ACL6_CFG_IFBASED_RULEINFO_S;

/*基本规则内容 ContentInfo*/
typedef struct tagAcl6BasicContentInfo
{
    ULONG ulAction;     /* 匹配成功后的动作 */
    ULONG ulFrag;       /* 是否带分片选项 */
    ULONG ulVrfIndex;   /* VRF索引 */
    ACL6_IP6ADDR_S stSrcIp;
} ACL6_BASIC_CONTENT_INFO_S;

/*高级规则内容 ContentInfo*/
typedef struct tagAcl6AdvanceContentInfo 
{
    ULONG ulAction;     /* 匹配成功后的动作 
                           ACL6_DENY － Deny
                           ACL6_PERMIT － Permit*/    
    ULONG ulFrag;       /* 是否带分片选项 */
    ULONG ulVrfIndex;       /* VRF索引 */
    ACL6_IP6ADDR_S stSrcIp;
    ACL6_IP6ADDR_S stDstIp;
    
    ULONG ulSrcPortOpType;
    ACL6_PORT_RANGE_S stSrcPort;/*报文源端口范围*/
    ULONG ulDstPortOpType;
    ACL6_PORT_RANGE_S stDstPort;/*报文目的端口范围*/
    
    UCHAR ucProtoBegin;     /* 协议号范围最小值 */
    UCHAR ucProtoEnd;       /* 协议号范围最大值 */
    UCHAR ucClass;          /* Traffic Class */
    UCHAR ucHopLm;          /* Hop Limit值 */
} ACL6_ADVANCE_CONTENT_INFO_S;

/*基于接口规则内容 ContentInfo*/
typedef struct tagAcl6IfbasedContentInfo
{
    ULONG ulAction;     /* 匹配成功后的动作 */
    ULONG ulIfIndex;    /* 接口索引，0xffffffff为ANY */
} ACL6_IFBASED_CONTENT_INFO_S;

/*规则信息*/
typedef struct tagAcl6RuleInfoOut
{
    ULONG ulTypeID;        /*规则类型ID*/
    ULONG ulGroupIndex;    /*规则组索引*/
    ULONG ulRuleIndex;     /*规则索引*/
    ULONG ulCount;         /*匹配应用计数*/
    union
    {
        ACL6_BASIC_CONTENT_INFO_S stBasicContentInfo;     /*基本规则信息*/
        ACL6_ADVANCE_CONTENT_INFO_S stAdvContentInfo;     /*高级规则信息*/
        ACL6_IFBASED_CONTENT_INFO_S stIfBasedContentInfo; /*基于接口规则信息*/
    } stContent;
} ACL6_RULE_INFO_OUT_S;

/*规则组信息*/
typedef struct tagAcl6GetGroupInfo
{
    ULONG ulGroupIndex;                /* 规则组索引*/
    ULONG ulTypeID;                    /* 规则类型ID 
                                          ACL6_BASIC_RULE_TYPE － 基本规则组
                                          ACL6_ADVANCE_RULE_TYPE － 高级规则组
                                          ACL6_IFBASED_RULE_TYPE － 基于接口的规则组*/
    ULONG ulMatchOrder;                /* 匹配顺序:
                                          ACL6_MATCHORDER_CONFIG － 配置顺序
                                          ACL6_MATCHORDER_AUTO － 自动顺序 */
    ULONG ulStep;                      /* 步长*/
    CHAR  szDescription[ACL6_DESCRIPTIONSTR_LEN + 1];   /* 描述信息 */
    ULONG ulRuleNum;                   /* 规则数目 */
} ACL6_GET_GROUP_INFO_S;

/* ACL6 基于接口过滤输入结构*/
typedef struct tagAcl6ClassifyByIfIn
{
    ULONG ulInIfIndex;
    ULONG ulOutIfIndex;
    ULONG ulIfType;             /*接口过滤类型
                                      ACL6_IFIN － 入接口过滤 
                                      ACL6_IFOUT － 出接口过滤
                                      ACL6_IFANY － 入或出接口过滤*/
    ULONG ulGroupIndex;
} ACL6_CLASSIFY_IF_IN_S;

/* ACL6 基于接口过滤输出结构*/
typedef struct tagAcl6ClassifyByIfOut
{
    ULONG ulAction;     /* 匹配成功后的动作 
                           ACL6_DENY － Deny
                           ACL6_PERMIT － Permit*/
    ULONG ulRuleIndex;  /*规则索引*/
} ACL6_CLASSIFY_IF_OUT_S;


/* ACL6 基于基本/高级规则过滤输入结构*/
typedef struct tagAcl6ClassifyByIpIn
{
    VOID *pPktHdr;
    ULONG ulGroupIndex;
    ULONG ulVrfIndex; 
    ULONG ulIgnoreByte;   /*比较忽略字段
                                ACL6_SIPByte －忽略源地址
                                ACL6_DIPByte －忽略目的地址
                                ACL6_PROByte －忽略协议类型
                                ACL6_HLMByte －忽略Hop Limit
                                ACL6_CLSByte －忽略Traffic Class
                                ACL6_SPORTByte －忽略源端口
                                ACL6_DPORTByte －忽略目的端口
                                ACL6_VRFByte －忽略vrf*/
} ACL6_CLASSIFY_IP_IN_S;

/* ACL6 基于基本/高级规则过滤输出结构*/
typedef struct tagAcl6ClassifyByIpOut
{
    ULONG ulAction;     /* 匹配成功后的动作 
                           ACL6_DENY － Deny
                           ACL6_PERMIT － Permit*/
    ULONG ulRuleIndex;  /*规则索引*/
} ACL6_CLASSIFY_IP_OUT_S;

/* 产品需要使用ACL6_IP6_S,因此在api.h中定义一份,注意结构体必须与acl6_pub.h中的ACL6_IP6_S定义保持一致 */
/*IPv6基本报头*/
#ifndef _ACL6_IP6_S
#define _ACL6_IP6_S
typedef struct tagACL6_Ip6
{
    ULONG ulTclassFlow;      /* 4 bits version, 8 bits traffic class and 20 bits of flow-ID */
    USHORT usPayLen;         /* 16 bits payload length */
    UCHAR ucNextHd;          /* 8 bits next header */
    UCHAR ucHopLm;           /* 8 bits hop limit */
    UCHAR szSrcAddr[ACL6_IPV6_ADDR_LEN];            /* 源IPv6地址 */            
    UCHAR szDstAddr[ACL6_IPV6_ADDR_LEN];            /* 目的IPv6地址 */ 
} ACL6_IP6_S;
#endif

/**********************************************************
*   用户API声明
***********************************************************/
/*******************************************************************************
*    Func Name: ACL6_ManageGroup
* Date Created: 2009-04-08
*       Author: hanna55555
*  Description:添加/删除/修改规则组。
*        Input: ACL6_CFG_MANAGEGROUP_S *pstManageGroup:规则组信息
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
*  2009-04-08   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_ManageGroup(ACL6_CFG_MANAGEGROUP_S *pstManageGroup);
/*************************************************************************
*    Func Name: ACL6_ManageBasicRule
*  Description: 基本ACL6规则配置接口(创建一个新规则或更新一个已存在的规则)
*        Input: ACL6_CFG_BASIC_RULE_S *pstAcl6_BasicRule，基本acl6规则信息
*       Output: 无
*       Return: Help_ACL6_OK,Help_ACL6_ERR,错误码
*      Caution: 无
*------------------------------------------------------------------------*
*  Modification History
*  DATE        NAME             DESCRIPTION
*------------------------------------------------------------------------*
*
*************************************************************************/
extern ULONG ACL6_ManageBasicRule(ACL6_CFG_BASIC_RULE_S* pstAcl6_BasicRule);
/*************************************************************************
*    Func Name: ACL6_ManageAdvRule
*  Description: 高级ACL6规则配置接口(创建一个新规则或更新一个已存在的规则)
*        Input: ACL6_CFG_ADV_RULE_S* pstAcl6_AdvRule，高级规则信息
*       Output: 无
*       Return: Help_ACL6_OK,Help_ACL6_ERR,错误码
*      Caution: 无
*------------------------------------------------------------------------*
*  Modification History
*  DATE        NAME             DESCRIPTION
*------------------------------------------------------------------------*
*
*************************************************************************/
extern ULONG ACL6_ManageAdvRule(ACL6_CFG_ADV_RULE_S* pstAcl6_AdvRule);
/*************************************************************************
*    Func Name: ACL6_ManageIfBasedRule
*  Description: 接口ACL6规则配置接口(创建一个新规则或更新一个已存在的规则)
*        Input: ACL6_CFG_IFBASED_RULEINFO_S* pstAcl6_IfBaseRule，基于接口的acl6规则信息
*       Output: 无
*       Return: Help_ACL6_OK,Help_ACL6_ERR,错误码
*      Caution: 无
*------------------------------------------------------------------------*
*  Modification History
*  DATE        NAME             DESCRIPTION
*------------------------------------------------------------------------*
*
*************************************************************************/
extern ULONG ACL6_ManageIfBasedRule(ACL6_CFG_IFBASED_RULEINFO_S* pstAcl6_IfBaseRule);
/*******************************************************************************
*    Func Name: ACL6_ClassifyByIfInfo
*  Description: 判断接口索引是否满足一个接口ACL6所描述的流,并返回匹配的节点号
*        Input: pstAcl6_ClassifyIn   待匹配信息
*       Output: pstAcl6_ClassifyOut->ulRuleIndex    匹配的ACL6规则的第几个节点
*               pstAcl6_ClassifyOut->ulLog           匹配的ACL6规则的节点的"是否日志"项
*       Return: ACL6_PERMIT      匹配且该匹配节点的动作为"permit"
*               ACL6_DENY        匹配且该匹配节点的动作为"deny"
*               Help_ACL6_RuleNotFound    和该ACL规则的所有节点都不匹配, pulSubitem无意义
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern ULONG ACL6_ClassifyByIfInfo(ACL6_CLASSIFY_IF_IN_S* pstAcl6_ClassifyIn,
                                         ACL6_CLASSIFY_IF_OUT_S* pstAcl6_ClassifyOut);
/*******************************************************************************
*    Func Name: ACL6_ClassifyByIpInfo
*  Description: 判断一个分组是否满足一个ACL6 Group所描述的流,并返回匹配的节点号
*        Input: pstAcl6_ClassifyIn   待匹配信息
*       Output: pstAcl6_ClassifyOut->ulRuleIndex    匹配的ACL6规则的第几个节点
*               pstAcl6_ClassifyOut->ulLog           匹配的ACL6规则的节点的"是否日志"项
*       Return: ACL6_PERMIT      匹配且该匹配节点的动作为"permit"
*               ACL6_DENY        匹配且该匹配节点的动作为"deny"
*               Help_ACL6_RuleNotFound    和该ACL6规则的所有节点都不匹配, pulSubitem无意义
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern ULONG ACL6_ClassifyByIpInfo(ACL6_CLASSIFY_IP_IN_S* pstAcl6_ClassifyIn,
                                          ACL6_CLASSIFY_IP_OUT_S* pstAcl6_ClassifyOut,
                                          ULONG ulFlag);

/* 其他对外接口 */
/*******************************************************************************
*    Func Name: ACL6_Init
* Date Created: 2009-04-08
*       Author: hanna55555
*  Description: 初始化ACL6规则类型与缺省规则组指针
*        Input: ULONG ulMID:模块ID
*       Output: 
*       Return: Help_ACL6_INIT_ERR : ACL CBB已经完成初始化
*                   Help_ACL6_ERR_CreateSm :创建信号量失败
*                   Help_ACL6_TYPE_BASIC_MallocErr : 为基本规则类型分配内存失败 
*                   Help_ACL6_GROUP_BASIC_MallocErr : 为基本规则组分配内存失败
*                   Help_ACL6_TYPE_ADV_MallocErr :  为高级规则类型分配内存失败 
*                   Help_ACL6_GROUP_ADV_MallocErr : 为高级规则组分配内存失败 
*                   Help_ACL6_TYPE_IF_MallocErr : 为基于接口规则类型分配内存失败 
*                   Help_ACL6_GROUP_IF_MallocErr : 为基于接口的规则组分配内存失败 
*                   Help_ACL6_OK : 成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-08   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_Init(ULONG ulMID);
/*******************************************************************************
*    Func Name: ACL6_GetVersion
* Date Created: 2009-04-09
*       Author: hanna55555
*  Description: 获取ACL6的版本号
*        Input: CHAR *pszVerInfo:版本信息
*       Output: 
*       Return: Help_ACL6_NullPoint:输入指针为空 
*                   Help_ACL6_OK: 成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-09   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_GetVersion(CHAR *pszVerInfo);
/*******************************************************************************
*    Func Name: ACL6_ShowVersion
* Date Created: 2009-04-09
*       Author: hanna55555
*  Description: 显示ACL6版本号信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-09   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_ShowVersion(VOID);

/*******************************************************************************
*    Func Name: ACL6_GetGroupInfo
* Date Created: 2009-04-13
*       Author: hanna55555
*  Description: 
*        Input: ACL6_FILTER_S *pstACL6Filter:
*               ACL6_GET_GROUP_INFO_S *pstGroupInfo:
*       Output: 
*       Return: Help_ACL6_NotInit :ACL CBB未成功初始化
*                   Help_ACL6_NullPoint : 输入指针为空
*                   Help_ACL6_GroupIndexError :规则组索引错误 
*                   Help_ACL6_GroupNotExist :规则组不存在
*                   Help_ACL6_OK :成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_GetGroupInfo(ACL6_FILTER_S *pstACL6Filter,ACL6_GET_GROUP_INFO_S *pstGroupInfo);
/*******************************************************************************
*    Func Name: ACL6_GetGroupSum
* Date Created: 2009-04-14
*       Author: hanna55555
*  Description: 获取配置有规则的规则组数量
*        Input: 
*       Output: ULONG *pulGroupSum:规则组数量
*       Return:  Help_ACL6_NotInit : ACL CBB未成功初始化
*                    Help_ACL6_NullPoint : 输入指针为空
*                    Help_ACL6_OK : 成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-14   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_GetGroupSum(ULONG *pulGroupSum);
/*******************************************************************************
*    Func Name: ACL6_ShowGroupSum
* Date Created: 2009-04-09
*       Author: hanna55555
*  Description: 
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-09   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_ShowGroupSum(VOID);
/*******************************************************************************
*    Func Name: ACL6_GetRuleInfo
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 获取指定规则组指定规则的规则信息
*        Input: ACL6_FILTER_S *pstACL6Filter:过滤器
*                  pstACL6Filter->ulGroupIndex:规则组索引，必须指定
*                  pstACL6Filter->ulRuleIndex:规则索引，必须指定
*       Output: ACL6_RULE_INFO_OUT_S *pstRuleInfo:规则信息
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_GetRuleInfo(ACL6_FILTER_S *pstACL6Filter,ACL6_RULE_INFO_OUT_S *pstRuleInfo);
/*******************************************************************************
*    Func Name: ACL6_GetRuleSum
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 获取所有规则数量
*        Input: ULONG *pulRuleSum:规则总量
*       Output: 
*       Return:  Help_ACL6_NotInit : ACL CBB未成功初始化
*                    Help_ACL6_NullPoint : 输入指针为空
*                    Help_ACL6_OK : 成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-23   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_GetRuleSum(ULONG *pulRuleSum);
/*******************************************************************************
*    Func Name: ACL6_ShowRuleSum
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: 显示规则总量
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
extern VOID ACL6_ShowRuleSum(VOID);
/*******************************************************************************
*    Func Name: ACL6_ClearMatchStat
* Date Created: 2009-04-14
*       Author: hanna55555
*  Description: 清除全部或指定规则组下所有或指定规则的匹配统计信息
*        Input: ACL6_FILTER_S *pstACL6Filter:过滤信息
*       Output: 
*       Return: Help_ACL6_NotInit:  ACL CBB未成功初始化
*                   Help_ACL6_GroupIndexError : 规则组索引错误
*                   Help_ACL6_OK:成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-14   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_ClearMatchStat(ACL6_FILTER_S *pstACL6Filter);
/*******************************************************************************
*    Func Name: ACL6_CheckGroupRuleExist
* Date Created: 2009-04-10
*       Author: hanna55555
*  Description: 检查规则组及规则是否已存在
*        Input: ACL6_FILTER_S *pstACL6Filter:过滤信息
*       Output: 
*       Return: Help_ACL6_NotInit: ACL CBB未成功初始化
*                   Help_ACL6_NullPoint:输入指针为空
*                   Help_ACL6_GroupIndexError:规则组索引错误 
*                   Help_ACL6_GroupNotExist:规则组不存在
*                   Help_ACL6_RuleNotExist:规则不存在 
*                   Help_ACL6_OK:成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-10   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_CheckGroupRuleExist(ACL6_FILTER_S *pstACL6Filter);
/*************************************************************************
*    Func Name: ACL6_IFDelete
*  Description: 删除接口时，调用本函数，删除所有基于接口的acl规则
*        Input: ULONG ulIfIndex 要删除的接口索引
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------*
*  Modification History
*  DATE        NAME             DESCRIPTION
*------------------------------------------------------------------------*
*
*************************************************************************/
extern VOID ACL6_IFDelete(ULONG ulIfIndex);

#ifdef  __cplusplus
}
#endif
   
#endif

