/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_hdr_trans.c
*
*  Project Code: VISPV100R007C03
*   Module Name: PUBLIC  
*  Date Created: 2009-02-27
*        Author: VISPV100R007C03项目组
*   Description: VISP 健康体检报告与临终遗言解析翻译模块
*                要求不能使用任何协议相关的数据结构，可以支持脱离协议栈独立编译。
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-02-27   VISPV100R007C03项目组   Create
*******************************************************************************/
#ifndef _HDR_TRANS_H_
#define _HDR_TRANS_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define HDR_TYPE_ULONG  1
#define HDR_TYPE_USHORT 2
#define HDR_TYPE_BOOL   3
#define HDR_TYPE_UCHAR  4

#ifndef VOS_OK
#define VOS_OK  0
#endif
#ifndef VOS_ERR
#define VOS_ERR 1
#endif

/* 内存空间大小 */
#ifndef LEN_16
#define LEN_16 16
#endif
#ifndef LEN_32
#define LEN_32 32
#endif
#ifndef LEN_64
#define LEN_64 64
#endif
#ifndef LEN_128
#define LEN_128 128
#endif
#ifndef LEN_256
#define LEN_256 256
#endif
#ifndef LEN_512
#define LEN_512 512
#endif
#ifndef LEN_1024
#define LEN_1024 1024
#endif
#ifndef LEN_2048
#define LEN_2048 2048
#endif
#ifndef LEN_4096
#define LEN_4096 4096
#endif

/* 大小头序标志 */
#define HDR_BIG_ENDIAN    0
#define HDR_LITTLE_ENDIAN 1

/* 消息类型 */
#define TYPE_HEALTH_CHECKUP       1
#define TYPE_LASTWORD_CHECKUP     2

#define IF_MAX_INTERFACE_NAME_LEN 47       /* 最大接口名长度 */

/* 类型定义 */
#ifndef VOID
#define VOID   void
#endif
#ifndef CHAR
#define CHAR   char
#endif
#ifdef TCPIP_DOPRA_V2    /*如用户需要使用Doprav2,则VISP与Dopra版本保持强依赖关系,需要包含Dopra头文件*/
#ifndef LONG
#define LONG   int
#endif
#ifndef ULONG
#define ULONG  unsigned int
#endif
#else
#ifndef LONG
#define LONG   long
#endif
#ifndef ULONG
#define ULONG  unsigned long
#endif
#endif

#ifndef UCHAR
#define UCHAR  unsigned char
#endif

#ifndef USHORT
#define USHORT unsigned short
#endif

/* 系统时间结构 */
typedef struct tagTCPIP_TIME
{
    USHORT usYear;       /* 1970-... */
    UCHAR  ucMonth;      /* 1-12     */
    UCHAR  ucDate;       /* 1-31     */

    UCHAR  ucHour;       /* 0-23 */
    UCHAR  ucMinute;     /* 0-59 */
    UCHAR  ucSecond;     /* 0-59 */
    UCHAR  ucReseved; 
}TCPIP_TIME_S;

typedef struct tagHealthMsgHead
{
    ULONG         ulMsgType;
    ULONG         ulSeq ; 
    TCPIP_TIME_S    stTime;
    USHORT        usModID;
    USHORT        usMsgLen;
    ULONG         ulMsgNum;
}HDR_MSG_HEAD_S;

typedef struct tagHDR_TLVHEAD
{
    USHORT   usType;
    USHORT   usLen;       
}HDR_TLVHEAD_S;

/* 接口索引 与 接口名对应关系表 */
typedef struct tagHDR_IFNAMEANDINDEX
{
    struct tagHDR_IFNAMEANDINDEX *pstNext;
    UCHAR   szIfName[IF_MAX_INTERFACE_NAME_LEN+1] ;
    ULONG   ulIfIndex; 
}HDR_IFNAMEANDINDEX_S;


extern VOID   HDR_GetLineByFile(FILE *fp, UCHAR *pucLine, ULONG *pulLineLen);
extern ULONG  HDR_GetBeginLineByType(FILE *fp,ULONG ulSubType,ULONG *pulSubLen,UCHAR *uszInfo);
extern CHAR  *Hdr_IpAddrToStr(ULONG ulAddr, CHAR *szStr);
extern VOID   HDR_LastWord_Translate(UCHAR* pHDRMsg, ULONG ulMsgLen);
extern ULONG  HDR_toHL(ULONG ulX);
extern USHORT HDR_toHS(USHORT usX);
extern VOID   HDR_Translate(UCHAR* pHDRMsg, ULONG ulMsgLen, ULONG ulScanId);
extern VOID   HDR_TranslateByCfg(HDR_MSG_HEAD_S *pstHdrComHead, FILE *fpHdrFile, FILE *fpCfgFile, ULONG ulScanId);
extern VOID   HDR_WriteBinaryFile(UCHAR* pHDRMsg, ULONG ulMsgLen, ULONG ulMsgType, ULONG ulScanId);
/*extern VOID   main(VOID);*/
extern int main(VOID);/* Modify by shuxieliu00176784, at 2011-05-20. 修改原因: 消除Coverity告警 */
extern ULONG  TCPIP_TranslatHdrByConfig(CHAR szHdrFile[LEN_128],CHAR szCfgFile[LEN_128],ULONG ulScanId);

#ifdef  __cplusplus
}
#endif

#endif

