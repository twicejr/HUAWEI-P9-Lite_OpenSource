 /******************************************************************************
  文 件 名   : fwd_ppp.h
  版 本 号   : 初稿
  作    者   : zhangnan 68158
  生成日期   : 2007年07月14日
  最近修改   :
  功能描述   : PPP模块头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2007年07月14日
    作    者   : zhangnan 68158
    修改内容   : 创建文件
******************************************************************************/

#ifndef __FWD_PPP_H__
#define __FWD_PPP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "TtfDrvInterface.h"

#define FWD_YES                     0
#define FWD_LITTLE_ENDIAN           FWD_YES

/*PPP头解析返回值定义 */
#define PPP_PARSE_R_DATA            0       /*表示数据报文*/
#define PPP_PARSE_R_LCP_SIG         1       /*表示信令*/
#define PPP_PARSE_R_LCP_ECHO_REQ    2       /*表示ECHO request 报文*/
#define PPP_PARSE_R_ASYN            3       /*异步报文*/
#define PPP_PARSE_R_OTHER_SIG       4       /*ppp其他信令*/
#define PPP_PARSE_R_ERR_SIG         5       /*ppp非法报文*/
#define PPP_PARSE_R_LCP_ECHO_REPLY  6       /*表示ECHO reply 报文*/
#define PPP_PARSE_R_VSCP_DATA       7       /*表示VSCP数据报文*/
#define PPP_PARSE_R_VSNP_SIG        10      /*表示VSCP信令报文*/
/*add:by xsm00201057 2012-3-1 PDSN_C6 IPV6移植_ppp压缩修改*/
#define PPP_PARSE_R_DATA_V4         11      /*ppp IPV4报文*/
#define PPP_PARSE_R_DATA_V6         12      /*ppp IPV6报文*/
/*end:by xsm00201057 2012-3-1 PDSN_C6 IPV6移植_ppp压缩修改*/

/*PPP加/解封装返回值定义*/
#define PPP_R_DATA                   0       /*表示数据报文需转发*/
#define PPP_R_SIG_OK                1       /*表示信令上送成功*/
#define PPP_R_ECHO                   2       /*表示ECHO报文*/
#define PPP_R_ASYN                   3       /*异步报文*/
#define PPP_R_SIG_FAIL            4       /*表示信令上送失败*/
#define PPP_R_ERROR                 5       /*出错报文*/
#define PPP_R_MAGIC_ERROR     6      /*magicnum出错报文*/


/*这两个不是返回值*/
#define PPP_TO_CTRL_OK              0       /*上送控制面成功*/
#define PPP_TO_CTRL_FAIL            1       /*上送控制面失败*/

/*PPP 头定义*/
#define PPP_H_ASYN                  0x7E    /*同异步标志*/
#define PPP_H_ACF                   0xFF03  /*地址控制域*/
#define PPP_H_PF_LCP                0xC021
#define PPP_H_PF_IPV4               0x0021
#define PPP_H_PF_IPV6               0x0057
#define PPP_H_PFC_IPV6              0x57
#define PPP_H_PFC_IPV4              0x21
#define PPP_H_LCP_ECHOREQ           0x09
#define PPP_H_LCP_ECHOREP           0x0a

#define VAS_PCI_REDIRECT_SIZE   1
#define VAS_PCI_L3STAKE_SIZE    3
#define PF_TRACK_FATAL_ERR_LEVEL        0x04
#define PF_TRACK_ERR_LEVEL              0x03
#define PF_TRACK_WARNING_LEVEL          0x02
#define PF_TRACK_INFO_LEVEL             0x01
#define PF_TRACK_INVALID_LEVEL          0

#define IPV4_VERSION 4

#define PPP_H_PF_VSNP               0x005b
#define PPP_H_PFC_VSNP              0x5b

#define PPP_FLAG_SEQ            0x7e
#define PPP_FLAG_SEQ_NO         0xffffffff

#define PPP_REBUILD_ENABLE      1
#define PPP_REBUILD_DISABLE     0

#define PPP_MAX_PKT_LEN_MULTI_2     3600
/*Mod by tianmin at 2013-3-30 for spuf 联调，DPI最多支持分片长度2240(包含576的datablock)*/

#define PPP_MAX_DATA_BLOCK_LENGTH 2000 /*MBUF的限制是2368*/


#define FWD_PPP_FRAG_STAT_TYPE_PPP 1    /*统计类型:一个原始报文被分为多个PPP分片*/
#define FWD_PPP_FRAG_STAT_TYPE_GRE 2    /*统计类型:多个原始报文存于一个PPP分片*/


/*判断序列号a是否是在b之后，在a没有翻转之前，a应该是大于b，如果a翻转后就应该小于b了*/
/*此函数有很大的局限性，a的含义只能是LINKTCB_S结构中的seq_late*/
#define AFollowB(a,b)           (((a) > (b)) || ((a) + 0xFFFF > (b) + 0xFFFF))

#define MAX_LINK_ITEM_NUM       (100)
#define PPP_FREELIST_SIZE       (20000)

/*****************************************************************************
枚举名    : FWD_PKT_TYPE_ENUM_UINT8
结构说明  : 数据包类型定义

  1.日    期   : 2014年10月28日
    作    者   : h00246512
    修改内容   : 定义数据包类型
*****************************************************************************/
enum FWD_PKT_TYPE_ENUM
{
    FWD_PKT_TYPE_IPV4 = 0x00,                                                   /* IPV4 */
    FWD_PKT_TYPE_IPV6 = 0x01,                                                   /* IPV6 */
    FWD_PKT_TYPE_PPP  = 0x02,
    FWD_PKT_TYPE_BUTT
};
typedef VOS_UINT8 FWD_PKT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : ICMP_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : ICMP Type
*****************************************************************************/
enum ICMP_TYPE_ENUM
{
    ICMP_TYPE_ECHO_REPLY    = 0,
    ICMP_TYPE_ECHO_REQUEST  = 8,

    ICMP_TYPE_BUTT
};
typedef VOS_UINT8 ICMP_TYPE_ENUM_UINT8;


typedef struct tagIN4ADDR
{
    PF_ULONG s_ulAddr;
}IN4ADDR_S;


typedef struct tagIP4
{

#if (FWD_LITTLE_ENDIAN == FWD_YES)
    PF_UCHAR   ip_chHLen:4;        /* header length */
    PF_UCHAR   ip_chVer:4;         /* version */
#else
    PF_UCHAR  ip_chVer:4;         /* version */
    PF_UCHAR  ip_chHLen:4;        /* header length */
#endif
    PF_UCHAR   ip_chTOS;           /* type of service */
    PF_USHORT  ip_usLen;       /* total length */

#define ip_sLen     ip_usLen
    PF_USHORT    ip_usId;        /* identification */
    PF_USHORT    ip_usOff;           /* fragment offset field */

#define ip_sOff    ip_usOff
#define    IP_DF 0x4000        /* dont fragment flag */
#define    IP_MF 0x2000        /* more fragments flag */
#define    IP_OFFMASK 0x1fff       /* mask for fragmenting bits */

    PF_UCHAR   ip_chTTL;       /* time to live */

    PF_UCHAR    ip_chPr;            /* protocol */

    PF_USHORT    ip_usSum;            /* checksum */

    IN4ADDR_S ip_stSrc;
    IN4ADDR_S ip_stDst;/* source and dest address */
} IP4_S;

typedef struct
{
    VOS_UINT16  usSrcPort;
    VOS_UINT16  usDstPort;    /* Source and Dest Port */
    VOS_UINT32  ulSeq;        /* Sequence Number */
    VOS_UINT32  ulAck;        /* Acknowledgement Number */

    /* 并未将tcp报文头的所有元素均列出来 */
    VOS_UINT8   aucOthers[4];
} PPP_TRACE_TCP4_STRU;

typedef struct
{
    VOS_UINT16  usSrcPort;
    VOS_UINT16  usDstPort;      /* Source and Dest Port */
    VOS_UINT16  usLen;          /* Length */
    VOS_UINT16  usCheckSum;     /* CRC */

    /* 其余均为data */
    VOS_UINT8   aucData[4];
} PPP_TRACE_UDP4_STRU;

typedef struct
{
    VOS_UINT8   ucType;
    VOS_UINT8   ucCode;
    VOS_UINT16  usCheckSum;     /* CRC */
    VOS_UINT32  ulOtherHd;      /* Other Parts of Header */

    /* 其余均为data */
    VOS_UINT8   aucData[4];
} PPP_TRACE_ICMP_STRU;


/** ****************************************************************************
* Name        : PPP_REBUILD_MNTN_STATISTIC_STRU
*
* Description : PPP分片重组可维可测统计值.
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRebuildStat;                          /* PPP消息队列中待处理的消息个数 */
    VOS_UINT32                          ulGetPppIdFailStat;                     /* 队列锁 */
    VOS_UINT32                          ulGetLinkItemFailStat;
    VOS_UINT32                          ulGetCurrItemStat;
    VOS_UINT32                          ulGetHeadItemStat;
    VOS_UINT32                          ulGetNextItemStat;
    VOS_UINT32                          ulCalcOffsetStat;
    VOS_UINT32                          ulHeadNotFlagSeqStat;
    VOS_UINT32                          ulFindFlagSeqStat;
    VOS_UINT32                          ulNotFindFlagSeqStat;
    VOS_UINT32                          ulHeadIsFlagSeqStat;
    VOS_UINT32                          ulContinueFlagSeqStat;
    VOS_UINT32                          ulNotAllFlagSeqStat;
    VOS_UINT32                          ulFindFlagSeqStat1;
    VOS_UINT32                          ulNotFindFlagSeqStat1;
    VOS_UINT32                          ulAllAreFlagSeqStat;
    VOS_UINT32                          ulDoRebuildStat;
    VOS_UINT32                          ulPktNumErrStat;
    VOS_UINT32                          ulEnterDoRebuildStat;
    VOS_UINT32                          ulNodeNotNullStat;
    VOS_UINT32                          ulNotStartWithSeqStat;
    VOS_UINT32                          ulNoFlagSeqStat;
    VOS_UINT32                          ulWithValidPktStat;
    VOS_UINT32                          ulContinueFlagSeqStat1;
    VOS_UINT32                          ulTailIsFlagSeqStat;
    VOS_UINT32                          ulValidPktInCurrNodeStat;
    VOS_UINT32                          ulNotFindFlagSeqStat2;
    VOS_UINT32                          ulFindFlagSeqStat2;
    VOS_UINT32                          ulFindFlagSeqStat3;
    VOS_UINT32                          ulAllAreFlagSeqStat1;
    VOS_UINT32                          ulNotAllFlagSeqStat1;
    VOS_UINT32                          ulDeleteJumpedNodeStat;
    VOS_UINT32                          ulDeleteHeadNodeStat;
    VOS_UINT32                          ulNodeNotNullStat1;
    VOS_UINT32                          ulRebuildEndFlagStat;
    VOS_UINT32                          ulTNodeNotNullStat;
    VOS_UINT32                          ulFindFlagSeqStat4;
    VOS_UINT32                          ulTNodeIsNullStat;
    VOS_UINT32                          ulCreateMBufStat;
    VOS_UINT32                          ulMBufIsNullStat;
    VOS_UINT32                          ulIsHeadOrNotStartSeqStat;
    VOS_UINT32                          ulLagerThan3600Stat;
    VOS_UINT32                          ulNodeIsNotHeadStat;
    VOS_UINT32                          ulDataIsNotNullStat;
    VOS_UINT32                          ulLargerThan2000Stat;
    VOS_UINT32                          ulCreateDataBlockFailStat;
    VOS_UINT32                          ulRebuildSuccStat;
    VOS_UINT32                          ulNextProcessSliceStat;
    VOS_UINT32                          ulAllAreFlagSeqStat2;
    VOS_UINT32                          ulNoteTmpNodeStat;
    VOS_UINT32                          ulLastSliceStat;
    VOS_UINT32                          ulNotLastSliceStat;
    VOS_UINT32                          ulContinueFlagSeqStat2;
    VOS_UINT32                          ulPktEndsAtEndStat;
    VOS_UINT32                          ulFindNextNodeStat;
    VOS_UINT32                          ulPktEndsNotAtEndStat;
    VOS_UINT32                          ulNotFindFlagSeqStat3;
    VOS_UINT32                          ulFindFlagSeqStat5;
    VOS_UINT32                          ulReleaseSourceStat;
    VOS_UINT32                          ulReleaseMBufStat;
    VOS_UINT32                          ulReleaseMBufStat1;
    VOS_UINT32                          ulReleaseNodesStat;
    VOS_UINT32                          ulReleaseDataStat;
} PPP_REBUILD_MNTN_STATISTIC_STRU;

/** ****************************************************************************
* Name        : PPP_REBUILD_MNTN_STORE_ITEM_STRU
*
* Description : PPP分片重组可维可测存储10个最近的节点.
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHndleSeq;
    VOS_UINT16                          usOffset;
    VOS_UINT16                          usCopy;
    VOS_UINT16                          usLitem;
    VOS_UINT16                          usRsvd[3];                              /*保证后面的指针按8字节对齐*/
    PMBUF_S                             stMbuf;                                 /*用于存储MBUF内容*/
    VOS_UINT8                           aucData[PPP_MAX_DATA_BLOCK_LENGTH];     /*用于存储MBUF数据内容*/
} PPP_REBUILD_MNTN_STORE_ITEM_STRU;

/** ****************************************************************************
* Name        : PPP_REBUILD_INCOMPLETE_SLICE_STRU
*
* Description : PPP分片重组当前状态
*******************************************************************************/
typedef struct
{
	VOS_UINT16								usHasStartFlag;
	VOS_UINT16								usLastByteSeq;
	VOS_UINT16								usStartSeq;
	VOS_UINT16								usEndSeq;
} PPP_REBUILD_INCOMPLETE_SLICE_STRU;


VOS_VOID FWD_PppFillDataInfo
(
    VOS_UINT8                          *pucPppData,
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo
);

VOS_UINT32 FWD_PppParse
(
    VOS_UINT8                          *pcuPppHead,
    VOS_UINT32                         *pulHdLen,
    FWD_PKT_TYPE_ENUM_UINT8            *enIpVersion
);

VOS_VOID FWD_PppDecap
(
    VOS_UINT16                          usStartSeq,
    VOS_UINT16                          usEndSeq,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode,
    VOS_UINT8                           ucPppId
);

VOS_UINT32 FWD_PppGetWantLcpFcFlag
(
    VOS_UINT8                           ucPppId,
    VOS_UINT32                         *pulPppFcFlag
);

VOS_UINT32 FWD_PppGetWantLcpAcfcFlag
(
    VOS_UINT8                           ucPppId,
    VOS_UINT32                         *pulPppAcfcFlag
);

VOS_UINT32 FWD_PppGetHisLcpFcFlag
(
    VOS_UINT8                           ucPppId,
    VOS_UINT32                         *pulPppFcFlag
);

VOS_UINT32 FWD_PppGetHisLcpAcfcFlag
(
    VOS_UINT8                           ucPppId,
    VOS_UINT32                         *pulPppAcfcFlag
);

VOS_UINT32 FWD_PppGetHisAccm
(
    VOS_UINT8                           ucPppId,
    VOS_UINT32                         *pulAccmFlag
);


VOS_UINT32 FWD_PppEncap
(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                          *pucCdsData,
    VOS_UINT16                          usDataLen,
    VOS_UINT32                          ulAccmValue,
    VOS_UINT32                         *pulAsynLen
);

VOS_VOID FWD_PppRebuild
(
    VOS_UINT16                          usSeqNr,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode,
    VOS_UINT8                           ucPppId
);

VOS_VOID FWD_PppHandleCompleteFrame
(
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode,
    VOS_UINT8                           ucPppId
);


#ifdef __cplusplus
}
#endif
#endif    /* end of __FWD_PPP_H__ */
