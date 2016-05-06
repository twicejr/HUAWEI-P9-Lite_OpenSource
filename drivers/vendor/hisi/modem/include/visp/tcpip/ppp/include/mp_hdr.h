/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                               mp_hdr.h
*
*  Project Code: VISPV100R007C03
*   Module Name: MP  
*  Date Created: 2009-02-28
*        Author: wuhailan
*   Description: VISP 健康体检头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-02-28   zhangchi                Create
*******************************************************************************/
#ifndef _MP_HDR_H_
#define _MP_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

#define  MP_HEALTH_MAX_ITEM     20  

#ifndef MP_SUPPORT_MAX_BIND
#define MP_SUPPORT_MAX_BIND     128
#endif


/* 接口UP/DOWN统计信息 */
typedef struct tagMP_HEALTH_STATISTIC
{
    ULONG ulMpIfIndex;
    ULONG ulLostFragments;          /* 接收方向丢弃的分片 */
    ULONG ulReorderedPkts;          /* 接收方向重组报文数 */
    ULONG ulUnassignedPkts;         /* 接收方向等待重组的分片数 */
    ULONG ulInterleavedPkts;        /* 发送方向LFI的分片个数 */
    
    ULONG ulWindowMatchPkts;        /* 匹配重组窗口报文个数 */
    ULONG ulWindowInPkts;           /* 落在重组窗口中报文个数 */
    ULONG ulWindowBehindPkts;       /* 落后重组窗口报文个数 */
    ULONG ulWindowSurpassPkts;      /* 超过重组窗口报文个数 */
}MP_HEALTH_STATISTIC_S;

typedef struct tagMP_HDR_MPBIND
{
    ULONG ulFatherIfIndex;
    ULONG ulMpBindNum;                          /* 捆绑链路数, 即已生效的子链路数 */
    ULONG ulSubLinkNum;                         /* 配置的子链路数 */  
}MP_HDR_MPBIND_S;

typedef struct tagMP_HDR_MPSUBLINK
{
    ULONG ulFatherIfIndex;
    ULONG ulSubLinkIfIndex;
    ULONG ulSubLinkStatus;
}MP_HDR_MPSUBLINK_S;

extern VOID MP_Health_BatchCheckup();
extern ULONG MP_Health_StatisticCheckup();
extern ULONG MP_Health_MpInfoCheckup();
extern ULONG MP_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);
extern ULONG MP_LastWord_StatisticCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);
    
#ifdef  __cplusplus 
}
#endif
#endif /* _MP_HDR_H_ */

