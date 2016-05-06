/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                                trunk_hdr.h
*
*  Project Code: VR7C03
*   Module Name: trunk  
*  Date Created: 2009-03-03
*        Author: h00121208/l57500
*   Description: trunk体检报告
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-03-03   h00121208/l57500        Create
*
*******************************************************************************/

#ifndef _TRUNK_HDR_H_
#define _TRUNK_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* 体检报告TRUNK信息 */
typedef struct tagTRUNK_HEALTH_INFO
{
    TRUNK_INFO_S stTkInfo;
}TRUNK_HEALTH_INFO_S;

/* 体检报告trunk 成员端口信息 */
typedef struct tagLACP_HEALTH_INFO
{
    ULONG ulTkId;                        /* 端口所在trunk的id*/
    ULONG ulPortIndex;                  /* 端口索引          */
    LACP_FSM_INFO_S   stLacpFsmInfo;    /* 成员端口状态机信息 */
    LACP_NEGO_INFO_S  stLacpNegoInfo;   /* 成员端口协商信息 */
    PORT_STAT_INFO_S  stPortStat;       /* 成员端口报文统计信息 */
}LACP_HEALTH_INFO_S;


/* trunk临终遗言绑定信息 */
typedef struct tagTRUNK_LASTWORD_BINDINFO
{
    ULONG  ulIfIndex;                           /* Trunk接口索引 */
    ULONG  ulEnableLacp;                            /* 是否使能LACP */
    ULONG  ulPortIfIndex[TRUNK_PORT_MAX_NUM];       /* 成员端口接口索引数组 */
    ULONG  ulUpPortIfIndex[TRUNK_PORT_MAX_NUM];     /* UP的成员端口接口索引数组 */
}TRUNK_LASTWORD_BINDINFO_S;


#ifdef  __cplusplus
}
#endif
#endif


