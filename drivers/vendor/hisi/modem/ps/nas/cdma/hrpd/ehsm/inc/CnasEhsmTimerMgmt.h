

#ifndef __CNAS_EHSM_TIMER_MGMT_H__
#define __CNAS_EHSM_TIMER_MGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_EHSM_ONE_THOUSAND_MILLISECOND                      (1000)                         /* 1000MS */

#define TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN                      (31*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

#define TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN                (30*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

#define TI_CNAS_EHSM_WAIT_CTTF_PDN_DISC_CNF_LEN                 (10*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

#define TI_CNAS_EHSM_WAIT_DETACH_CNF_LEN                        (10*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

#define TI_CNAS_EHSM_WAIT_HSM_DISC_CNF_LEN                      (16*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

#define TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS_LEN           (4*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


enum CNAS_EHSM_TIMER_ID_ENUM
{
    /* timer for common connection establish confirm from HSM */
    TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF,

    /* Timer to retry the commomn connection establish */
    TI_CNAS_EHSM_WAIT_CONN_RETRY_EST,

    /* Timer for PDN setup confirm and Attach confirm from PPP */
    TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF,

    /* Timer to retry the PDN set up */
    TI_CNAS_EHSM_WAIT_RETRY_PDN_SETUP,

    /* Timer for PDN disconnect confirm from PPP */
    TI_CNAS_EHSM_WAIT_CTTF_PDN_DISC_CNF,

    /* Timer for detach (disc all pdn)*/
    TI_CNAS_EHSM_WAIT_DETACH_CNF,

    /* Timer for disconnect confirm from HSM */
    TI_CNAS_EHSM_WAIT_HSM_DISC_CNF,

    /* Timer for protecting all power off process for EHSM */
    TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS,

    TI_CNAS_EHSM_TIMER_BUTT
};
typedef VOS_UINT32  CNAS_EHSM_TIMER_ID_ENUM_UINT32;



enum CNAS_EHSM_TIMER_STATUS_ENUM
{
    CNAS_EHSM_TIMER_STATUS_STOP,              /* 定时器停止状态 */
    CNAS_EHSM_TIMER_STATUS_RUNING,            /* 定时器运行状态 */
    CNAS_EHSM_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 CNAS_EHSM_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

typedef struct
{
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId;                              /* 定时器的ID */
    CNAS_EHSM_TIMER_STATUS_ENUM_UINT8   enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucReserve[3];
}CNAS_EHSM_TIMER_CTX_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头*/ /*_H2ASN_Skip*/
    CNAS_EHSM_TIMER_STATUS_ENUM_UINT8   enTimerStatus;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulLen;                                  /* 定时器时长 */
}CNAS_EHSM_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID  CNAS_EHSM_SndOmTimerStatus(
    CNAS_EHSM_TIMER_STATUS_ENUM_UINT8   enTimerStatus,
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID  CNAS_EHSM_StartTimer(
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID  CNAS_EHSM_StopTimer(
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId
);

CNAS_EHSM_TIMER_STATUS_ENUM_UINT8  CNAS_EHSM_GetTimerStatus(
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId
);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasEhsmTimerMgmt.h */
