/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         iphc_def.h
 *
 *  Project Code: VISP
 *   Module Name: IPHC
 *  Date Created: 2002/06/25
 *        Author: wangyue
 *   Description: 本头文件包含iphc模块的宏定义；   
 *
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2006-03-30      xiehuaguo       Adjust for D00647
 *
 ************************************************************************/
 
#ifndef _IPHC_DEF_H_
#define _IPHC_DEF_H_


#ifdef  __cplusplus
extern "C"{
#endif

/* 报文压缩类型定义 */
#define IPHC_COMPRESS_ALL           0   /* 对TCP/non-TCP报文都压缩 */
#define IPHC_ONLY_COMPRESS_NON_TCP  1   /* 仅压缩no-TCP报文 */
#define IPHC_ONLY_COMPRESS_TCP      2   /* 仅压缩TCP报文*/
#define IPHC_NOT_COMPRESS_ALL       3   /* 禁止压缩TCP、non-TCP报文 */

/* 报文类型 */
#define IPHC_IP_TCP_PACKETTYPE      1   /* IP+TCP报文 */
#define IPHC_IP_UDP_PACKETTYPE      2   /* IP+UDP报文 */
#define IPHC_IP_UDP_RTP_PACKETTYPE  3   /* IP+UDP+RTP报文 */

/* TCP_SPACE常量定义*/
#define IPHC_DEF_TCP_SPACE       15      /* 默认值 */
#define IPHC_MIN_TCP_SPACE       3       /* 下限 */
#define IPHC_MAX_TCP_SPACE       255     /* 上限 */

/* NON_TCP_SPACE常量定义 */
#define IPHC_DEF_NON_TCP_SPACE   15      /* 默认值 */
#define IPHC_MIN_NON_TCP_SPACE   3       /* 下限 */
#define IPHC_MAX_NON_TCP_SPACE   999   /* 上限 */

#define IPHC_MAX_NON_TCP_SPACE_NP 65535  /*IPHC 在NP模式下的上限*/

/* F_MAX_PERIOD常量定义 */
#define IPHC_DEF_F_MAX_PERIOD    256     /* 默认值 */
#define IPHC_MIN_F_MAX_PERIOD    1       /* 下限 */
#define IPHC_MAX_F_MAX_PERIOD    65535   /* 上限 */

/* F_MAX_TIME常量定义 */
#define IPHC_DEF_F_MAX_TIME      5       /* 默认值 */
#define IPHC_MIN_F_MAX_TIME      1       /* 下限 */
#define IPHC_MAX_F_MAX_TIME      255     /* 上限 */

/* MAX_HEADER常量定义 */
#define IPHC_DEF_MAX_HEADER      168     /* 默认值 */
#define IPHC_MIN_MAX_HEADER      60      /* 下限 */
#define IPHC_MAX_MAX_HEADER      168     /* 上限 */

/* 协商(Enhanced) RTP Compression子选项设置 */
#define IPHC_NONE_RTP_COMPRESSION       0   /* 不协商RTP Compression和Enhanced RTP Compression子选项 */
#define IPHC_RTP_COMPRESSION            1   /* 协商RTP Compression子选项 */
#define IPHC_ENHANCED_RTP_COMPRESSION   2   /* 协商Enhanced RTP Compression子选项 */

/*子选项类型定义*/
#define IPHC_ONLY_COMPRESS_PART         3   /*仅压缩TCP/非TCP报文子选项*/

/*子选项长度定义*/
#define IPHC_LEN_RTP_COMPRESSION     2   /*RTP Compression子选项*/
#define IPHC_LEN_ENHANCED_RTP_COMPRESSION  2   /*Enhanced RTP Compression子选项*/
#define IPHC_LEN_ONLY_COMPRESS_PART       3   /*仅压缩TCP/非TCP报文子选项*/

/*上下文类型定义*/
#define IPHC_CONTEXT_TYPE_ALL       0   /*TCP报文格式和非TCP报文格式*/
#define IPHC_CONTEXT_TYPE_TCP       1   /*TCP报文格式*/
#define IPHC_CONTEXT_TYPE_NONTCP    2   /*非TCP报文格式*/

/*上下文位置定义*/
#define IPHC_CONTEXT_SIDE_ALL       0   /*压缩和解压缩上下文*/
#define IPHC_CONTEXT_SIDE_COMP      1   /*压缩方上下文*/
#define IPHC_CONTEXT_SIDE_DECOMP    2   /*解压方上下文*/

/********************* IPHC模块相关SID相关宏(BEGIN)********************/
#define SID_COMP_IPHC_CONTEXT_S         1
#define SID_COMP_IPHC_MBUF_S            2 
#define SID_COMP_IPHC_COMP_CONTEXT_S    3       
#define SID_COMP_IPHC_DECOMP_CONTEXT_S  4    
/********************* IPHC模块相关SID相关宏(END)**********************/
#ifndef MIN
#define MIN(a, b)       ((a)>(b) ? (b):(a)) 
#endif

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif

