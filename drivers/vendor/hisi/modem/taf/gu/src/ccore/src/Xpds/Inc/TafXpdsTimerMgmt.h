/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsTimerMgmt.h
  版 本 号   : 初稿
  作    者   : 谷传征
  生成日期   : 2015年8月21日
  最近修改   :
  功能描述   : XPDS模块
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月21日
    作    者   : g00261581
    修改内容   : CDMA A-GPS项目新增

******************************************************************************/

#ifndef __TAFXPDSTIMERMGMT_H__
#define __TAFXPDSTIMERMGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MnComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_XPDS_CTX_MAX_TIMER_NUM                          (10)

/*将定时器的秒转换成DOPRA定时器所需的毫秒，需要乘以1000 */
#define TIMER_S_TO_MS_1000                                  (1000)

#define TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND_TIMER_LEN         (20  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_AT_BINDUP_IND_TIMER_LEN            (40  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_MPC_START_POS_RSP_TIMER_LEN        (8  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_MPC_POS_REPORT_RSP_TIMER_LEN       (8  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN                  (35 * TIMER_S_TO_MS_1000)

#define TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF_TIMER_LEN    (25 * TIMER_S_TO_MS_1000)

#define TI_TAF_XPDS_WAIT_XCC_DATA_CAll_CONNECT_CNF_TIMER_LEN (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_XCC_DATA_CAll_STATUS_IND_TIMER_LEN (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_XCC_ANSWER_CAll_CNF_TIMER_LEN      (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_XCC_CALL_CONN_IND_TIMER_LEN        (5  * TIMER_S_TO_MS_1000)

#define TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS_TIMER_LEN      (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_CAS_CNF_TIMER_LEN        (13 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_ALM_EPHI_RESP_TIMER_LEN  (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_GPS_LOC_RESP_TIMER_LEN   (5  * TIMER_S_TO_MS_1000)

#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM_TIMER_LEN          (13 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP_TIMER_LEN  (13 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PDE_ASSIST_DATA_CNF_TIMER_LEN        (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_AQU_ASSI_TIMER_LEN     (13 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_REQ_AFTER_PPM_TIMER_LEN          (5  * TIMER_S_TO_MS_1000)

#define TI_TAF_XPDS_IS801_SESSION_TIMER_LEN                     (32 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_PDE_MSB_DATA_TIMER_LEN                 (25 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO_DEFAULT_TIMER_LEN  0
#define TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF_TIMER_LEN_SI       (20 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF_TIMER_LEN_NI       (7 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_AT_GPS_STOP_TIMER_LEN    (5 * TIMER_S_TO_MS_1000)


#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_MS_INFO_TIMER_LEN          (13 * TIMER_S_TO_MS_1000)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_XPDS_TIMER_ID_ENUM
 枚举说明  : XPDS定时器的ID
 1.日    期   : 2015年8月21日
   作    者   : G00261581
   修改内容   : CDMA A-GPS项目新增
*****************************************************************************/
enum TAF_XPDS_TIMER_ID_ENUM
{
    TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND   = 0,
    TI_TAF_XPDS_WAIT_AT_BINDUP_IND,

    TI_TAF_XPDS_WAIT_MPC_START_POS_RSP,
    TI_TAF_XPDS_WAIT_MPC_POS_REPORT_RSP,

    TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF,

    TI_TAF_XPDS_NI_POS_REPORT_INTERNAL,
    TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY,
    TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO,  /* 用于精度测试定时器 */
    TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF,             /* 等候GPS伪距定时器 */

    TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF,
    TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF,
    TI_TAF_XPDS_WAIT_PDE_MSB_DATA,

    TI_TAF_XPDS_IS801_SESSION,  /* 中国电信需求: T8 IS 801会话定时器 */

    TI_TAF_XPDS_WAIT_XCC_DATA_CAll_CONNECT_CNF,
    TI_TAF_XPDS_WAIT_XCC_DATA_CAll_STATUS_IND,
    TI_TAF_XPDS_WAIT_XCC_ANSWER_CAll_CNF,
    TI_TAF_XPDS_WAIT_XCC_CALL_CONN_IND,
    TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS,
    TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_CAS_CNF,
    TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_ALM_EPHI_RESP,
    TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_GPS_LOC_RESP,

    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PDE_ASSIST_DATA_CNF,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_MS_INFO,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSI,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_REQ_AFTER_PPM,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_COMPLETE_NI_QUALITY,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PPM_COMPLETE_NI_QUALITY,
    TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_AT_GPS_STOP,

    TI_TAF_XPDS_TIMER_BUTT
};
typedef VOS_UINT32  TAF_XPDS_TIMER_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_XPDS_TIMER_STATUS_ENUM
 结构说明  : XPDS定时器状态,停止或运行
 1.日    期   : 2015年8月21日
   作    者   : G00261581
   修改内容   : CDMA A-GPS项目新增
*****************************************************************************/
enum TAF_XPDS_TIMER_STATUS_ENUM
{
    TAF_XPDS_TIMER_STATUS_STOP          = 0,                /* 定时器停止状态 */
    TAF_XPDS_TIMER_STATUS_RUNING,                           /* 定时器运行状态 */
    TAF_XPDS_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_XPDS_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_XPDS_TIMER_START_RESULT_ENUM
 结构说明  : XPDS定时器启动结果返回值
 1.日    期   : 2015年8月21日
   作    者   : G00261581
   修改内容   : CDMA A-GPS项目新增
*****************************************************************************/
enum TAF_XPDS_TIMER_START_RESULT_ENUM
{
    TAF_XPDS_TIMER_START_SUCCEE         = 0,                /* 定时器启动成功 */
    TAF_XPDS_TIMER_START_FAILURE,                           /* 定时器启动失败 */

    TAF_XPDS_TIMER_START_BUTT
};
typedef VOS_UINT8 TAF_XPDS_TIMER_START_RESULT_ENUM_UINT8;
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
/*****************************************************************************
 结构名    : TAF_XPDS_TIMER_CXT_STRU
 结构说明  : XPDS定时器运行上下文
  1.日    期   : 2015年8月21日
    作    者   : G00261581
    修改内容   : CDMA A-GPS项目新增

*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;             /* 定时器的运行指针 */
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId;          /* 定时器的ID */
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus;      /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucReserve[3];      /* 保留位 */
} TAF_XPDS_TIMER_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_TIMER_INFO_STRU
 结构说明  : log出XPDS定时器运行情况
  1.日    期   : 2015年8月21日
    作    者   : G00261581
    修改内容   : CDMA A-GPS项目新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus;      /* 定时器状态 */
    VOS_UINT8                           aucReserve[3];      /* 保留位 */
    VOS_UINT32                          ulLen;              /* 定时器时长 */
}TAF_XPDS_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enMsgId;
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus;      /* 定时器状态 */
    VOS_UINT8                           aucReserve[3];      /* 保留位 */
    VOS_UINT32                          ulLen;              /* 定时器时长 */

}TAF_XPDS_TIMER_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_XPDS_TIMER_MSG_DATA             stMsgData;
}TafXpdsTimerMgmt_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID TAF_XPDS_SndOmTimerStatus(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen,
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus
);

VOS_VOID TAF_XPDS_InitAllTimers(
    TAF_XPDS_TIMER_CTX_STRU            *pstXPDSTimerCtx
);

TAF_XPDS_TIMER_START_RESULT_ENUM_UINT8  TAF_XPDS_StartTimer(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID TAF_XPDS_StopTimer(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId
);

TAF_XPDS_TIMER_STATUS_ENUM_UINT8  TAF_XPDS_GetTimerStatus(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId
);

VOS_VOID TAF_XPDS_StopAllTimer(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif



