/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_report.h
*
*  Project Code: VISPV100R007
*   Module Name: igmp  
*  Date Created: 2008-04-11
*        Author: zengshaoyang62531
*   Description: igmp report头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-11   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_REPORT_H_
#define _IGMPV3_REPORT_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

typedef VOID (*IGMP_HOOK_FOR_SEND)();

    
/*定时器超时后的回调函数的输入参数*/
typedef struct tagIGMPCALLBACK
{
    ULONG ulIfIndex;             /* 接口索引 */
    ULONG ulGrpAddr;             /* 组地址 */
    ULONG ulTimerType;           /* 定时器类型 */
}IGMPCALLBACK_S;

/*igmp报文创建mbuf时,给链路层预留的长度*/
#define IGMP_MBUF_LINKHDR 40

#define IGMP_REPORT_MODE_IN 1         /*is_in*/
#define IGMP_REPORT_MODE_EX 2         /*is_ex*/
#define IGMP_REPORT_TO_IN   3         /*to_in*/
#define IGMP_REPORT_TO_EX   4         /*to_ex*/
#define IGMP_REPORT_ALLOW_NEW 5       /*allow_new*/
#define IGMP_REPORT_BLOCK_OLD 6       /*block_old*/

#define IGMP_TIMERTYPE_IF       1       /*定时器类型：接口定时器*/
#define IGMP_TIMERTYPE_GRP      2       /*定时器类型：组定时器1*/
#define IGMP_TIMERTYPE_GRPSRC   3       /*定时器类型：组定时器2*/
#define IGMP_TIMERTYPE_STATACHG 4       /*定时器类型：状态改变定时器*/
#define IGMP_TIMERTYPE_VER1     5       /*定时器类型：IGMPV1版本定时器*/
#define IGMP_TIMERTYPE_VER2     6       /*定时器类型：IGMPV2版本定时器*/

#define IGMP_MASK_NULL         0x0     /* 空标记 */
#define IGMP_MASK_CUR_STATE    0x01    /* report current-state */
#define IGMP_MASK_ALLOW_NEW    0x02    /* report source as allow-new */
#define IGMP_MASK_BLOCK_OLD    0x04    /* report source as block-old */
#define IGMP_MASK_TO_IN        0x08    /* report source as to_in */
#define IGMP_MASK_TO_EX        0x10    /* report source as to_ex */
#define IGMP_MASK_STATE_TAG1   0x20    /* TAG1标记，状态改变时，用于标记多播组EX或IN列表，结合TAG2状态来发送成
                                        * 员报告，如对于IncludeList，如果源地址A既打了TAG1又打了TAG2，则源地址
                                        * A不用发送成员报告，如果只打了TAG1，则要对A发送BLOCK_OLD报告，如果只
                                        * 打了TAG2，则要发送ALLOW_NEW报告，对于ExcludeList，则正好是相反的情况
                                        */
#define IGMP_MASK_STATE_TAG2   0x40    /* TAG2标记 */

#define IGMP_MASK_IF_STATE     0x80    /* report current-state per interface */
#define IGMP_MASK_SNDRPT_IMMEDIATELY    0x100   /* 立即发送报告标记 */

#define IGMP_MASK_STATE_TX   (IGMP_MASK_STATE_TAG1 | IGMP_MASK_STATE_TAG2)
#define IGMP_MASK_PENDING    (IGMP_MASK_CUR_STATE | IGMP_MASK_ALLOW_NEW | IGMP_MASK_BLOCK_OLD)

/*知名多播地址*/
#define IGMP_ALL_HOSTS      0xE0000001L  /*224.0.0.1*/
#define IGMP_ALL_ROUTER     0xE0000002L /*224.0.0.2*/
#define IGMPV3_ALL_ROUTER   0xe0000016L /*224.0.0.22*/

#define IGMP_HDRLEN        8      /*igmp成员报告的最小的头长度，对于IGMPv3，不包括组记录*/
#define IGMP_GRPREC_HDRLEN 8      /*igmpv3最小的组记录长度，不包括源地址*/

#define IPADDRSPACE 2
#define IGMPPKTSPACE(ulCount) ((ulCount) << 2)

#define IGMP_CLEARTAG(start,srclist,mask)\
{\
    for ((srclist) = (start);(srclist) != NULL;(srclist) = (srclist)->pstNextSourceAddr)\
    {\
        (srclist)->ulReportTag &= ~(mask);\
    }\
}

/*IGMPV3报告组记录*/
typedef struct tagIgmpv3_Report_GrpRec
{
    UCHAR ucType;                     /*type*/
    UCHAR ucAux_data_len;             /*附加数据长度*/
    USHORT usNum_srcs;                /*源地址数目*/ 
    ULONG ulGrp_addr;                 /*组地址*/
    ULONG ulSrcs[1];                  /*源地址,基本类型可以定义0个元素的数组，实现变长功能*/
}Igmpv3_Report_GrpRec_S;

/*IGMPV3报告首部*/
typedef struct tagIgmpv3_Report_Hdr
{
    UCHAR ucType;                      /*类型*/
    UCHAR ucResv;                      /*reserved*/
    USHORT usChkSum;                   /*checksum*/
    USHORT usReserved;                 /*reserved*/
    USHORT usNum_Grp_rec;              /*numbers of group records*/
    Igmpv3_Report_GrpRec_S stGrpRec[1];/*组装报文时，保证内存连续，此处定义一个元素即可*/
}Igmpv3_Report_Hdr_S;

typedef struct tagROUTEALERTOPTION
{
    ULONG ulIpAddr;              /*取为空值*/
    UCHAR ucOptName;             /*选项名*/
    UCHAR ucOptLen;              /*选项长度*/
    USHORT usOptVar;             /*选项名字*/
}ROUTEALERTOPTION_S;

#define IGMP_ROUTE_ALERT 148

extern ULONG IGMPV1V2_Send_Report(IPMULTI_S *pstIPM, UCHAR ucType);
extern ULONG IGMPV3_Send_CurrentStateReport(IPMULTI_S *pstIPM,ULONG ulUseRecord);
extern ULONG IGMPV3_Send_Report(IPMULTI_S *pstIPM, IPMULTI_SOURCELIST_S *pstTagList,
            ULONG ulCount, ULONG ulMask, ULONG ulType, ULONG ulIpAddr);
extern VOID IGMPV3_Send_StateChgReport(IPMULTI_S *pstIPM,ULONG *pulRet);
extern VOID IGMP_Cancel_All_Reports(IPIFNET_S *pstIPCtl,ULONG ulCancel_StaChg);
extern VOID Igmp_Clean_Recorded_Sources(IPMULTI_S *pstIPM);
extern ULONG IGMP_Compute_Chksum(UCHAR *pucBuff,LONG llength,USHORT *usChksum);
extern VOID IGMP_FillInIPHead(IP_S *pstIPHead,ULONG ulDst,ULONG ulSrc,USHORT usTotLen);
extern IPMULTI_SOURCELIST_S* Igmp_Get_Sources(Igmpv3_Report_GrpRec_S *pstGrp, 
            IPMULTI_SOURCELIST_S *pstSrcList, ULONG ulMask, ULONG ulMax, ULONG ulStart, 
            ULONG *ulCnt);
extern IPMULTI_S* IGMP_SearchGroupOnIpIfnet(IPIFNET_S *pstIpCtl,ULONG ulGrpAddr);
extern VOID IGMP_Send_SrcListChg_Report(IPMULTI_S *pstIPMulti, ULONG ulPlusTag);
extern ULONG IGMP_SourceListIsEmpty(IPMULTI_SOURCELIST_S *pstSrcList);
extern VOID IGMP_TimeOutCallBack(VOID *pstTimerArg,ULONG *ulReTransFlg);
extern VOID IGMP_Delete_MultiGrp(IPMULTI_S *pstGrp);
extern VOID IGMP_Free_MultiList(IPMULTI_LIST_S *pstMultiList,IPIFNET_S *pstIpctl);

#ifdef __cplusplus
}
#endif /* __cplusplus */
    
#endif /* _IGMPV3_REPORT_H_ */

