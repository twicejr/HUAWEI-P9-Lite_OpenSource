

#ifndef _3AH_HDR_H_
#define _3AH_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif



/* 3ah接口体检报告数据结构 */

/* 接口统计信息 */
typedef struct tagOAM3AH_HEALTH_IFSTATISTIC
{
    ULONG ulIfIndex;
    OAM3AH_PDUSTAT_S stPduStat;
}OAM3AH_HEALTH_IFSTATISTIC_S ;

/* 3ah状态机状态 */
typedef struct tagOAM3AH_HEALTH_FSMSTATE
{
    ULONG ulIfIndex;
    ULONG ulFsmState;                   /* 接口3AH状态机状态            */
    UCHAR aucPeerMacAddr[MACADDRLEN];   /* 对端physical地址              */
    UCHAR ucReserve[2];
}OAM3AH_HEALTH_FSMSTATE_S;


extern VOID OAM_3AH_Health_BatchCheckup(VOID);
extern ULONG OAM_3AH_Health_IfStatisticCheckup(VOID);
extern ULONG OAM_3AH_Health_FsmStateCheckup(VOID);

#ifdef  __cplusplus
}
#endif
#endif

