/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_query.h
*
*  Project Code: VISPV100R007
*   Module Name: IGMP  
*  Date Created: 2008-03-11
*        Author: zengshaoyang62531
*   Description: 定义igmp query模块的头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-11   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_QUERY_H
#define _IGMPV3_QUERY_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define IGMP_MIN_QUERY_LGENTH       8          /*igmp查询报文的最小长度*/
#define IGMPV3_MIN_QUERY_LENGTH     12         /*igmpv3查询报文的最小长度*/
#define IGMPV3_MIN_REPORT_LENGTH    16         /*igmpv3报告报文的最小长度*/

#define IGMP_INIT_ROBVAR        2          /*Default robustness variable values*/
#define IGMP_INTI_QUERYINT      125        /* Default query query interval */
#define IGMP_DEF_QRYMRT         10         /*Version.1 max response time*/
#define IGMP_TIME_SCALE         1000
#define IGMP_TIME_UNIT          10         /*时间单位,10表示1s*/
#define IGMP_TIME_BASE          100        /*随机值 * IGMP_TIME_BASE后转化为ms*/

#define IGMP_MAXSOURCES(len)    (((len)-12)>>2)

typedef enum tagIGMP_COMPATIBLE_VAR
{
    IGMP_VER1 = 1,         /*igmpv1*/
    IGMP_VER2,             /*igmpv2*/
    IGMP_VER3              /*igmpv3*/
}IGMP_COMPATIBLE_VAR_E;

/*IGMPV3 查询报文首部数据结构*/
typedef struct tagIGMPV3_QUERY
{
    UCHAR  ucType;             /* 类型 */
    UCHAR  ucCode;             /* 最大响应代码 */
    USHORT usChkSum;           /* checksum */
    ULONG  ulGrpAddr;          /* group address */
    
    #if VRP_LITTLE_ENDIAN == VRP_YES
        UCHAR  ucQRV:3;        /* Querier's Robustness Variable */
        UCHAR  ucSFlag:1;      /* Suppress Router-Side Processing flag */
        UCHAR  ucResv:4;       /* resvered */
    #else
        UCHAR  ucResv:4;       /* resvered */
        UCHAR  ucSFlag:1;      /* Suppress Router-Side Processing flag */
        UCHAR  ucQRV:3;        /* Querier's Robustness Variable */
    #endif
    
    UCHAR  ucQQIC;             /* Querier's Query Interval Code */
    USHORT usSrcNums;          /* numbers of sources */ 
    ULONG ulSrcAddr[1];        /* 源地址指针，一定要保证内存连续，防止访问非法内存*/
}IGMPV3_QUERY_S;

/*IGMP报文首部数据结构*/
typedef struct tagIGMPHDR
{
    UCHAR  ucType;             /* 类型 */
    UCHAR  ucCode;             /* code */
    USHORT usChkSum;           /* checksum */
    ULONG  ulGrpAddr;          /* group address */
}IGMPHDR_S;

extern VOID IGMP_CheckIfCompatibleVar(IPIFNET_S *pstIpCtl);
extern ULONG IGMP_CreatOrRefresh_Timer(ULONG *pulTimerID,ULONG ulTime,ULONG ulGrpAddr,
    ULONG ulIfIndex,ULONG ulTimerType);
extern VOID IGMP_Input(MBUF_S *pstMBuf, LONG lHLen);
extern ULONG IGMP_Record_Sources(IPMULTI_S *pstIPMulti,USHORT usSrcNums,INADDR_S *pstSrc);
extern ULONG IGMP_Schedule_Curstate_Reports(MBUF_S *pstMBuf,IPIFNET_S *pstIpctl,
                                                       ULONG ulIgmpLen,ULONG ulMrt);
extern ULONG IGMP_Timer_NeedRefresh(ULONG ulNewRandTime,ULONG ulTimerID);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
