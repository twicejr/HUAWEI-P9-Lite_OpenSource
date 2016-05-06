/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_hdr.h
*
*  Project Code: V1R6C02
*   Module Name: PP4  
*  Date Created: 2009-07-14
*        Author: zhangchi(00142640)
*   Description: PP4Ìå¼ì±¨¸æ
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-07-14   zhangchi(00142640)      Create
*
*******************************************************************************/

#ifndef _PP4_HDR_H_
#define _PP4_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

typedef struct tagPP4_HEALTH_STATISTIC
{
    ULONG ulIfIndex;
    IPIFSTAT_S stPP4Statistic;
}PP4_HEALTH_STATISTIC_S;

extern VOID IP_PP4_Health_BatchCheckup();
extern ULONG IP_PP4_Health_IFStatisticCheckUp();
extern ULONG IP_PP4_Health_StatisticCheckUp();
extern ULONG IP_PP4_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);

#ifdef  __cplusplus
}
#endif
#endif


