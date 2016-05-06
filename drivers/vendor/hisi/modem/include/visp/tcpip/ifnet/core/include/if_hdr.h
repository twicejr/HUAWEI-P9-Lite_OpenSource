/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                                if_hdr.h
*
*  Project Code: VR7C03
*   Module Name: IFNET  
*  Date Created: 2009-02-26
*        Author: wuhailan/zhangchi(00103194/00142640)
*   Description: ifnet体检报告
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-02-26   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/

#ifndef _IF_HDR_H_
#define _IF_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN 47       /* 最大接口名长度 */
#endif

/* IFNET接口体检报告数据结构 */

/* 接口状态 */
typedef struct tagIF_HEALTH_IFSTATUS
{
    UCHAR   szIfName[IF_MAX_INTERFACE_NAME_LEN+1] ;
    ULONG   ulIfIndex ;
    ULONG   ulPhyStatus;       
    ULONG   ulShutdown;       
}IF_HEALTH_IFSTATUS_S ;

/* 接口UP/DOWN统计信息 */
typedef struct tagIF_HEALTH_IFSTATISTIC
{
    ULONG   ulIfIndex ;
    ULONG   ulPhyUpCount;      /* 接口变化到物理UP次数 */
    ULONG   ulPhyDownCount;    /* 接口变化到物理Down次数 */
    ULONG   ulLineUpCount;     /* 接口变化到协议UP次数 */
    ULONG   ulLineDownCount;   /* 接口变化到协议Down次数 */
}IF_HEALTH_IFSTATISTIC_S ;


/* IFNET接口临终遗言数据结构 */
typedef struct tagIF_LASTWORD_IFSTATUS
{
    ULONG   ulIfIndex ;
    UCHAR   ucPhyStatus;       
    UCHAR   ucShutdown;  
    UCHAR   ucResevred[2];
}IF_LASTWORD_IFSTATUS_S ;

/*每次报告的接口个数 */
#define  IFNET_HEALTH_MAXIF_ITEM     20  

/*IFNET体检报告长度*/
#define  IFNET_HEALTH_HEAD_LEN        (sizeof(HDR_MSG_HEAD_S))

extern VOID IF_Health_BatchCheckup();
extern ULONG IF_Health_IfStatusCheckup();
extern ULONG IF_Health_IfStatisticCheckup();
extern ULONG IF_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);

#ifdef  __cplusplus
}
#endif
#endif

