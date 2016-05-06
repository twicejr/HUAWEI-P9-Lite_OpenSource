/*************************************************************************************
*
*                       dhcpv6c_pkt.h
*
*  项目代码：           UGW9811 V900R010C00
*  创建日期：           2012-06-28
*  作者：               Y00170683
*  修改历史列表：
*  参考文档：       
*  功能：               DHCPV6C模块消息处理头文件                 
*  其他：                  
*
*-----------------------------------------------------------------------------------
*
*  Copyright  Beijing Institute HuaWei Tech, Inc.
*                     ALL RIGHTS RESERVED
*
*************************************************************************************/
#ifndef __DHCPV6C_PKT_H__
#define __DHCPV6C_PKT_H__

#ifdef    __cplusplus
extern "C" {
#endif


/*******************************************************************************************************/
/********************                          宏定义                           ************************/
/*******************************************************************************************************/

#define DHCPV6C_SEND_MSG_MAXLEN 1024  /* 发送消息最大长度 */

#define DHCPV6C_HUNDRED 100

/* transaction-id组成 */
/* DE板：TID为token(13bit)+sc id(2bit)+sequence(9bit)*/
/* F板： TID为token(14bit)+Sequence(10bit)*/
#define DHCPV6C_MAX_SEQUENCE_ID_DE       0x1ff  /* DE板 sequenceNum 最大ID */
#define DHCPV6C_MAX_SEQUENCE_ID_F       0x3ff   /* F板 sequenceNum 最大ID */
#define DHCPV6C_TOKEN_BIT11       11   /* DE板 TOKEN占用比特数--13BIT */
#define DHCPV6C_TOKEN_BIT10       10   /* F板 TOKEN占用比特数--14BIT */
#define DHCPV6C_SCID_BIT9       9   /* DE板 SC占用比特数--2BIT */
#define DHCPV6C_MAX_SEQUENCE_NUM_DE       512  /* DE板 sequenceNum 最大规格 */
#define DHCPV6C_MAX_SEQUENCE_NUM_F       1024  /* F板 sequenceNum 最大规格 */
#define DHCPV6C_MAX_SEQUENCE_NUM      g_usDhcpv6cMaxSeqNum 
#define DHCPV6C_MAX_DNS_NUM      2 

#define DHCPV6C_GET_MSG_TYPE(pucDhcpv6Msg) (((DHCPV6C_MSG_S *)(pucDhcpv6Msg))->ulMsgTypeBit8)

/* 根据teidc获取token */
#ifdef __LINUX_PLATFORM__
#define DHCPC_GET_TOKEN_BY_TEIDC(teid) ((teid) >> 18)
#else
#define DHCPC_GET_TOKEN_BY_TEIDC(teid) ((teid) >> 19)
#endif

/* 根据token获取teidc */
#define DHCPC_GET_TEIDC_BY_TOKEN(token) ((token) << 19)

/* DUID-type 不是1,2,3 */
#define DHCPC_CHECK_DUIDTYPE_INCORRECT(usDuidType) \
(                                                 \
    ((DHCPV6_MSG_OPTION_DUID_LLT != (usDuidType)) \
    && (DHCPV6_MSG_OPTION_DUID_EN != (usDuidType)) \
    && (DHCPV6_MSG_OPTION_DUID_LL != (usDuidType))) ? \
    VOS_TRUE : VOS_FALSE \
)

#define DHCPV6C_SET_V6ADDR_NULL(aulV6Addr) \
{ \
    (aulV6Addr)[0] = DHCP_INVALID_ULONG; \
    (aulV6Addr)[1] = DHCP_INVALID_ULONG; \
    (aulV6Addr)[2] = DHCP_INVALID_ULONG; \
    (aulV6Addr)[3] = DHCP_INVALID_ULONG; \
}

/* V6地址不存在  */
#define DHCPC_CHECK_V6ADDR_IS_NULL(aulV6Addr) \
(                                                 \
    ((DHCP_INVALID_ULONG == ((aulV6Addr)[0])) \
    && (DHCP_INVALID_ULONG == ((aulV6Addr)[1])) \
    && (DHCP_INVALID_ULONG == ((aulV6Addr)[2])) \
    && (DHCP_INVALID_ULONG == ((aulV6Addr)[3]))) ? \
    VOS_TRUE : VOS_FALSE \
)

/*******************************************************************************************************/
/********************                        结构定义                           ************************/
/*******************************************************************************************************/

/***************************************************************/
/**************         DHCPV6 Option结构体      ***************/
/***************************************************************/

/*信令和全部扩展定义 1字节对齐*/
#pragma pack(1)

/* 基本TLV格式的OPTION */
typedef struct tagDHCPV6C_TLV_OPTION_S
{
    VOS_UINT16 usType;    /* Type */
    VOS_UINT16 usLen;     /* Length */
    UCHAR ucData[0];  /* value */
}DHCPV6C_TLV_OPTION_S;

/* DUID-LLT */
typedef struct tagDHCPV6C_DUID_LLT_OPTION_S
{
    USHORT usType;    /* Type */
    USHORT usHardWare;     /* HardWare */
    ULONG  ulTime;     /* Time */
    UCHAR ucData[0];  /* value */
}DHCPV6C_DUID_LLT_OPTION_S;

/* DUID-EN */
typedef struct tagDHCPV6C_DUID_EN_OPTION_S
{
    VOS_UINT16 usType;    /* Type */
    VOS_UINT32  ulEnterpriseNum;     /* EnterpriseNum */
    UCHAR ucData[0];  /* value */
}DHCPV6C_DUID_EN_OPTION_S;

/* DUID-LL */
typedef struct tagDHCPV6C_DUID_LL_OPTION_S
{
    USHORT usType;    /* Type */
    USHORT  usHardWare;     /* HardWare */
    UCHAR ucData[0];  /* value */
}DHCPV6C_DUID_LL_OPTION_S;

/* IANA_OPTION */
typedef struct tagDHCPV6C_IANA_OPTION_S
{
    USHORT usType;    /* Type */
    VOS_UINT16 usLen;     /* Length */
    VOS_UINT32 ulId;     /* IA-ID */
    VOS_UINT32 ulT1;       /* t1 */
    VOS_UINT32 ulT2;       /* t2 */
    UCHAR ucData[0];  /* IA_NA-options */
}DHCPV6C_IANA_OPTION_S;

/* IAADDR_OPTION */
typedef struct tagDHCPV6C_IAADDR_OPTION_S
{
    USHORT usType;             /* Type */
    VOS_UINT16 usLen;              /* Length */
    in6_addr stIpv6Addr;      /* IPv6 address */
    VOS_UINT32 ulPreTime;          /* preferred-lifetime */
    VOS_UINT32 ulValidTime;        /* valid-lifetime */
    UCHAR ucData[0];  /* IA_NA-options */
}DHCPV6C_IAADDR_OPTION_S;

/* STATUS_CODE_OPTION */
typedef struct tagDHCPV6C_STATUS_CODE_OPTION_S
{
    USHORT usType;      /* Type */
    VOS_UINT16 usLen;       /* Length */
    VOS_UINT16 usCode;      /* status-code */
    UCHAR ucData[0];   /* status-message */
}DHCPV6C_STATUS_CODE_OPTION_S;

#pragma pack()

/* DHCPV6C消息option部分 */
typedef struct tagDHCPV6C_OPTION_INFO_S
{
    DHCPV6C_TLV_OPTION_S *pstClientIdOption;
    DHCPV6C_DUID_EN_OPTION_S *pstCiDuidEn;    
    DHCPV6C_TLV_OPTION_S *pstServerIdOption;
    DHCPV6C_IANA_OPTION_S *pstIaNaOption;
    DHCPV6C_IAADDR_OPTION_S *pstIaAddrOption;
    DHCPV6C_TLV_OPTION_S *pstDnsOption; /* DNS */
    DHCPV6C_STATUS_CODE_OPTION_S *pstMsgStatusCodeOption; /* 消息中携带的 */
    DHCPV6C_STATUS_CODE_OPTION_S *pstIaNaStatusCodeOption; /* IA-NA-option中携带的 */
    DHCPV6C_STATUS_CODE_OPTION_S *pstIaAddrStatusCodeOption; /* IA-addr-option中携带的 */   
    UCHAR ucMainDnsFlg;
    UCHAR ucSecdDnsFlg;
    UCHAR aucRev6[6];    
 } DHCPV6C_OPTION_INFO_S; 

/* DHCPV6C消息 */
typedef struct tagDHCPV6C_MSG_INFO_S
{    
    UCHAR *pucMsg;          /* 消息体指针 */
    VOS_UINT32 ulMsgLen;        /* 消息长度 */
    USHORT usSeqNum;    
    UCHAR aucResed[2];        
    DHCPV6C_OPTION_INFO_S stDhcpv6cOptionInfo;  /* 消息扩展头信息 */
} DHCPV6C_MSG_INFO_S;

/********************************************************************/
/************************数据相关************************************/
/********************************************************************/
/* SequenceNum空闲资源管理结构 */
typedef struct tagDHCPV6C_SEQNUM_FREELINK_S
{
    USHORT* pusNextNode;                /* 空闲链表下一个节点的索引 */
    USHORT usUsedNum;                   /* 占用节点数 */
    USHORT usFreeHead;                  /* 空闲节点链表头 */
    USHORT usFreeTail;                  /* 空闲节点链表尾 */
    USHORT usReseved;                  
}DHCPV6C_SEQNUM_FREELINK_S;

/* SequenceNum与DHCP控制块对应关系结构 */
typedef struct tagDHCPV6C_SEQNUM_CONTEXT_S
{
    ULONG ulTeidc;    /* teidc */
    UCHAR ucbit2IpAddrType : 2;   /* 地址类型 */
    UCHAR ucbit2UsedFlg : 2;      /* 使用标记 */
    UCHAR ucbit4AgeingCnt : 4;    /* 老化计数----申请和释放时清零,定时器到时累加 */    
                                   /* 大于DHCPC_AGEING_SEQNUM_MAX_CNT时说明seqnum残留,需要释放 */
    UCHAR aucResed[3];            
}DHCPV6C_SEQNUM_CONTEXT_S;

/*******************************************************************************************************/
/********************                        全局变量                           ************************/
/*******************************************************************************************************/
extern UCHAR* g_pucDhcpv6cSendBuff;        /*发送消息缓存*/
extern UCHAR* g_pucDhcpv6cRevBuff;         /*接收消息缓存*/

extern USHORT g_usDhcpv6cMaxSeqNum; /* SequencNum规格,DE512,F1024*/
extern DHCPV6C_SEQNUM_FREELINK_S g_stDhcpv6cSeqNumLink; /* SequencNum后向空闲链 */
extern DHCPV6C_SEQNUM_CONTEXT_S *g_pstDhcpv6cSeqContext; /*  SequenceNum与DHCP控制块对应关系 */


/*******************************************************************************************************/
/********************                        外部接口                           ************************/
/*******************************************************************************************************/

extern ULONG DHCPV6C_InitFreeLink(DHCPV6C_SEQNUM_FREELINK_S* pstFreeLink, VOS_UINT16 usTotalNum);
extern ULONG DHCPV6C_AllocSeqNum(USHORT *pusSeqNum, ULONG ulTeidc, UCHAR ucIpAddrType);
extern ULONG DHCPV6C_QuryTeidcBySeqNum(USHORT usSeqNum, ULONG *pulTeidc, UCHAR *pucIpAddrType);
extern VOID DHCPV6C_FreeSeqNum(USHORT usSeqNum);

extern USHORT LAP_IPv6GetAddrType( in6_addr *addr );
/*m00221573 全文件pclint 2012-10-16 start*/
extern ULONG DHCPV6C_MsgDecode(DHCPV6C_MSG_INFO_S *pstMsgInfo);
extern ULONG DHCPV6C_CheckOption(DHCPV6C_OPTION_INFO_S *pstDhcpv6cOptionInfo,
                                      DHCPC_CTRLBLK *pstDhcpcContext);
extern ULONG DHCPV6C_SendPacket(DHCPC_CTRLBLK *pstDhcpcContext, ULONG ulDhpcv6MsgType);
extern VOID DHCPV6C_SaveOptionToContext(DHCPC_CTRLBLK *pstDhcpcContext, 
                                                 DHCPV6C_OPTION_INFO_S *pstDhcpv6Option);
extern ULONG DHCPM_GetDhcpSrvVpnByIndex(ULONG ulDhcpIndex, ULONG *pulVpnIndex);
extern ULONG DHCPC_SelectAndGetServerCfg(DHCPC_CTRLBLK *pstDhcpcContext, ULONG aulServerIp[LAP_IP_ULONG_NUM]);
extern VOID DHCPCv6_OmMsgTrc(UCHAR *pucDhcpv6Msg,DHCPC_CTRLBLK *pstDhcpcContext, UCHAR ucMsgType,ULONG ulMsgLen, UCHAR MsgDirection);
/*m00221573 全文件pclint 2012-10-16 end*/
extern VOID DHCPV6C_GetSeqNumByMsg(USHORT *pusSeqNum, UCHAR *pucMsg);
#ifdef    __cplusplus
}
#endif

#endif


