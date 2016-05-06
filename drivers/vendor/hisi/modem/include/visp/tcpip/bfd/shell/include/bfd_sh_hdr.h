/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_sh_hdr.h
*
*  Project Code: VISP V1R6C02
*   Module Name:   
*  Date Created: 2009-07-14
*        Author: mafeng(59090)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-07-14   zhangchi(00142640)/mafeng(59090)           Create
*
*******************************************************************************/

#ifndef _BFD_SH_HDR_H_
#define _BFD_SH_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* BFD会话基本信息 */
typedef struct tagBFD_HEALTH_BASEINFO_S
{
    ULONG ulVrfIndex;         /* VRF索引值 */
    ULONG ulSessionID;
    ULONG ulDstIPAddress;     /* 会话的目的地址，主机序 */
    ULONG ulSrcIPAddress;     /* 会话的源地址，主机序 */
    ULONG ulIfIndex;
    USHORT usActDetectMode;
    USHORT usSessionStatus;   /* 会话状态 */
    ULONG ulUpToDown;         /* 会话自创建之后，状态由Up变Down的总次数 */
    ULONG ulLastDownTime;     /* 最后一次Down的时间 */
}BFD_HEALTH_BASEINFO_S;

/* BFD NP下发统计信息 */
typedef struct tagBFD_HEALTH_NPINFO_S
{
    /* BFD更新通知总次数 */
    ULONG ulBFDUpdateTotal; 
    /* BFD更新通知失败次数 */
    ULONG ulBFDUpdateFailure;
}BFD_HEALTH_NPINFO_S;

extern VOID BFD_Health_BatchCheckup(VOID);
extern ULONG BFD_Health_SessionCheckup(VOID);
extern ULONG BFD_Health_NpCheckup(VOID);
extern ULONG BFD_LastWord_LastWordCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);
    
#ifdef  __cplusplus
}
#endif
#endif


