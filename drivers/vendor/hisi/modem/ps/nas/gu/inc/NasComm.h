/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : NasComm.h
  Description : NAS内部使用的头文件
  History     :
      1.  张志勇   2003.12.11   新版作成


      2.日    期   : 2010年3月2日
        作    者   : zhoujun /z40661
        修改内容   : NAS R7协议升级

*******************************************************************************/

#ifndef _NAS_COMM_H_
#define _NAS_COMM_H_

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "Nas_Mem.h"

#include "NasCommDef.h"
#include "TafAppMma.h"

#include "NasMntn.h"

#include "Nasrrcinterface.h"
#include "TafMtcApi.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*********************************************************************/
/************** MTF地址宏定义 ****************************************/
/*********************************************************************/
#define              ADDRESS_MTF                            32
#define              ADDRESS_TAF                            100

/*********************************************************************/
/************** PD定义 (27.A02) **************************************/
/*********************************************************************/
#define              PD_ACMP                                1
#define              PD_RSMP                                2
#define              PD_CCP                                 3
#define              PD_PCP                                 4
#define              PD_SSP                                 5
#define              PD_MTMP                                21
#define              PD_DCP                                 22

/*********************************************************************/
/************** PD定义 (24.008) **************************************/
/*********************************************************************/
#define              NAS_PD_GCC                             0x00
#define              NAS_PD_BCC                             0x01
#define              NAS_PD_CC                              0x03
#define              NAS_PD_GTTP                            0x04
#define              NAS_PD_MM                              0x05
#define              NAS_PD_RR                              0x06
#define              NAS_PD_GMM                             0x08
#define              NAS_PD_SMS                             0x09
#define              NAS_PD_SM                              0x0A
#define              NAS_PD_SS                              0x0B
#define              NAS_PD_LS                              0x0C

/* SM发给TAF的消息 */
#define     NAS_SND_TAFMSG_SM2TAF                           0
/* SM接收TAF的原语 */
#define     NAS_RCV_TAFMSG_TAF2SM                           1


/* TAF发给MMC的原语 */
#define     NAS_RCV_TAFMSG_TAF2MMC                          2
/* MMC发给TAF的原语 */
#define     NAS_SND_TAFMSG_MMC2TAF                          3


/* TAF发送给RABM的原语 */
#define     NAS_RCV_TAFMSG_TAF2RABM                         4
/* RABM发送给TAF的原语  */
#define     NAS_SND_TAFMSG_RABM2TAF                         5

/* TAF发给CC的宏定义 */
#define     NAS_RCV_TAFMSG_TAF2CC                           6
/* CC发给TAF的宏定义 */
#define     NAS_SND_TAFMSG_CC2TAF                           7

/* TAF发给SS的宏定义 */
#define     NAS_RCV_TAFMSG_TAF2SS                           8
/* SS发给TAF的宏定义 */
#define     NAS_SND_TAFMSG_SS2TAF                           9

#define PS_PTL_VER_R10                                      (7)
#define PS_PTL_VER_R11                                      (8)

/*********************************************************************/
/************** NAS TIMER ID 定义 ************************************/
/*********************************************************************/
#define NAS_TIMER_ALL                   0xFF

/* SMS TIMER ID */
#define SMC_TIMER_ID_PS_TC1M_MO         0                                             /* TC1M                                     */
#define SMC_TIMER_ID_PS_TC1M_MT         1                                             /* TC1M                                     */
#define SMC_TIMER_ID_CS_TC1M_MO         2                                             /* TC1M                                     */
#define SMC_TIMER_ID_CS_TC1M_MT         3                                             /* TC1M                                     */
#define SMC_TIMER_ID_TR1M               4
#define SMC_TIMER_ID_TR2M               5
#define SMC_TIMER_ID_TRAM               6

/* GMM TIMER ID */
#define     GMM_TIMER_T3302                              0                      /* T3302定时器                              */
#define     GMM_TIMER_T3310                              1                      /* T3310定时器                              */
#define     GMM_TIMER_T3311                              2                      /* T3311定时器                              */
#define     GMM_TIMER_T3312                              3                      /* T3312定时器                              */
#define     GMM_TIMER_T3316                              4                      /* T3316定时器                              */
#define     GMM_TIMER_T3317                              5                      /* T3317定时器                              */
#define     GMM_TIMER_T3318                              6                      /* T3318定时器                              */
#define     GMM_TIMER_T3320                              7                      /* T3320定时器                              */
#define     GMM_TIMER_T3321                              8                      /* T3321定时器                              */
#define     GMM_TIMER_T3330                              9                      /* T3330定时器                              */
#define     GMM_TIMER_1S                                10                      /* 5秒定时器                                */
#define     GMM_TIMER_PROTECT                           11                      /* 保护TIMER(agent)*/
#define     GMM_TIMER_PROTECT_FOR_SIGNALING             12                      /* 保护TIMER(建信令)                        */
#define     GMM_TIMER_SUSPENDED                         13                      /* 保护挂起状态 */
#define     GMM_TIMER_T3314                             14                      /* GPRS READY TIMER定时器 */
#define     GMM_TIMER_RAU_RSP                           15                      /* GMM RAU RSP TIMER定时器 */
#define     GMM_TIMER_PROTECT_FOR_RR_REL                16                      /* 保护TIMER(释放信令连接)                  */
#define     GMM_TIMER_PROTECT_OLD_TLLI                  17
#define     GMM_TIMER_T3319                             18                      /* T3319定时器                              */
#define     GMM_TIMER_T3340                             19                      /* T3340定时器                              */
#define     GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF        20                      /* 等待WRR回复InterRatHoInfoCnf保护定时器   */
#define     GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF      (21)                      /* 等待LMM回复重选安全参数的保护定时器   */
#define     GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF         (22)                      /* 等待LMM回复切换安全参数的保护定时器   */


#define     GMM_TIMER_WAIT_CONNECT_REL                  (23)                    /* 等待连接释放保护定时器   */

#define     GMM_TIMER_TC_DELAY_SUSPEND_RSP              (24)                    /* 在TC的GCF测试中，GMM延迟向MMC回复SUSPEND_RSP定时器 */

#define     GMM_TIMER_T3323                             (25)                    /* ISR去激活定时器 */

#define     GMM_TIMER_HO_WAIT_SYSINFO                   (26)                    /* GMM收到MM的cs信令连接不存在消息时判断如果W下，GS关联不存在，RRC连接存在网络模式I,cs ps mode需要启动等系统消息定时器，D态WAS不会上报系统消息，定时器超时需要做联合rau*/


#define     GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU       (27)                    /* 在TC的GCF测试中，GMM延迟向MMC回复SUSPEND_RSP定时器 */


/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
#define    GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO         (28)                    /* 发rau或attach前判断当前L能力和g_GmmGlobalCtrl.ucMsRadioCapSupportLteFromAs中记录的不一致，启动定时器等接入层上报最新的MS Radio Access capability IE信息*/
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

#define     GMM_TIMER_DETACH_FOR_POWER_OFF              (29)                    /* GMM关机detach定时器 */

#define     GMM_TIMER_PROTECT_PS_DETACH                 (30)                    /* GMMCS域detach保护定时器 */

#define     GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU       (31)                    /* VOICE DOMAIN发生变化时，GMM暂时不能做RAU,启保护定时器 */

#define     GMM_TIMER_DELAY_PS_SMS_CONN_REL             (32)                    /* 延时释放ps域SMS的连接 */

/* 注意:    增加新定时器，请同步更新 GMM_TIMER_NUM */


/* 当对所有的TIMER操作相同时，可以使用下面的宏作为TIMER的种类 */
#define     GMM_REGSTER_AND_SHUTDOWN_TIMER               99                     /* 不支持GPRS时需要停止的定时器 */
#define     GMM_TIMER_ALL                                100

#define     GMM_TIMER_ALL_EXCEPT_T3312_T3323                (101)

/* MM TIMER ID */
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
typedef enum NAS_MM_TIMER_ID
{
    MM_TIMER_T3210                          = 0,
    MM_TIMER_T3211                          = 1,
    MM_TIMER_T3212                          = 2,
    MM_TIMER_T3213                          = 3,
    MM_TIMER_T3214                          = 4,
    MM_TIMER_T3216                          = 5,
    MM_TIMER_T3218                          = 6,
    MM_TIMER_T3220                          = 7,
    MM_TIMER_T3230                          = 8,
    MM_TIMER_T3240                          = 9,
    MM_TIMER_PROTECT_AGENT                  = 10,
    MM_TIMER_PROTECT_DETACH                 = 11,
    MM_TIMER_PROTECT_SIGNALLING             = 12,
    MM_TIMER_PROTECT_CC                     = 13,
    MM_TIMER_PROTECT_CCBS                   = 14,
    MM_TIMER_PROTECT_SUSPEND                = 15,
/* G下，联合注册, CS失败5次后，延迟1秒发起LU*/
    MM_TIMER_DELAY_LU_GSM                   = 16,
/* G下，联合注册成功后，CS需要延迟发起缓存的CS业务，等待GMM RAU过程完全结束,
   暂定延迟1秒 */
    MM_TIMER_DELAY_CS_SERVICE_GSM           = 17,

/* 主动请求底层释放连接后，启动底层连接释放的保护定时器 */
    MM_TIMER_WAIT_CONNECT_REL               = 18,

/* CSFB 流程从L HO到GU后等系统消息时长定时器 */
    MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO    = 19,

/* 紧急呼CSFB 流程从L HO到GU后等系统消息时长定时器 */
    MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO = 20,

/* CSPS 网络模式I的情况下, 关机时由于MM的很多状态都不处理GMMMM_GPRS_DETACH_COMPLETED,
   于是MM不向MMC回复POWER_OFF_CNF. 为规避此问题, 当MM收到POWER_OFF_REQ时启动定时器,
   当定时器超时后, MM向MMC回复POWER_OFF_CNF.
   启动原则:
   1. 收到关机请求时如果已向MMC回复POWER_OFF_CNF, 则不需启动
   2. 收到关机请求时如果有启动其它保护定时器,如MM_TIMER_PROTECT_DETACH, 则不需启动
   3. 其它情况, 如果是CSPS 网络模式I的情况, 则需要启动此定时器
   无需显示停止此定时器, 因为再回复POWER_OFF_CNF时会 Mm_TimerStop(MM_TIMER_STOP_ALL). */
    MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT = 21,

    MM_TIMER_PROTECT_CS_DETACH              = 22,


/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, begin */
    MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF      = 23,
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, end */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-1, begin */
    MM_TIMER_T3242                          = 24,
    MM_TIMER_T3243                          = 25,
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-1, end */

    MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE               = 26,

/* CS HO等系统消息时长定时器，包括ultra Flash CSFB，SRVCC, GU之间电话过程中的HO */
    MM_TIMER_CS_HO_WAIT_SYSINFO             = 27,

    MM_TIMER_MAX
}NAS_MM_TIMER_ID_ENUM;
typedef VOS_UINT8 NAS_MM_TIMER_ID_ENUM_UINT8;
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */


/* MMA TIMER ID List */
#define TAF_USIM_OPPIN                  (80)      /*操作PIN的定时器ID */
#define MMA_INTERNAL_TIMER_ID           (0x82)    /*内部启动定时器，用于ATTACH操作与DETACH操作*/
#define MMA_TIMER_FOR_PC_REPLAY         (40)      /* 新增加定时器，周期性输出MM层回放消息 */
#define TI_MN_PH_RESET                  (41)
#define TI_MN_PH_PIN_OPER               (42)
#define TI_MN_PH_CPHS_SIM_ONS           (43)



/* 6F15文件Refresh触发自动搜网，周期性尝试定时器 */
#define TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU      (45)

#define TI_TAF_MMA_PNN_LIST_MEM_PROTECT_TIMER           (47)     /* 收到AT^PNN查询PNN LIST的请求时启动定时器，时长为15s */


/* 延迟掉电关机定时器: E5掉电关机前需延迟50ms供AT结果回复，将TASKDELAY修改为定时器 */
#define TI_TAF_MMA_DELAY_POWER_DOWN                          (48)

#define TI_TAF_MMA_NET_SCAN_TIMER                           (49)
#define TI_TAF_MMA_ABORT_NET_SCAN_TIMER                     (50)

/******************************************************************************/
/* End of NAS Timer List */
/******************************************************************************/

#define     MAX_DYNAMIC_MSG_LEN                             1024

#ifndef WUEPS_MEM_NO_WAIT
#define     WUEPS_MEM_NO_WAIT                               (VOS_UINT32)1       /* 不等待   */
#endif

#ifndef WUEPS_MEM_WAIT
#define     WUEPS_MEM_WAIT                                  (VOS_UINT32)(-1)    /* 等待     */
#endif

#define NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetfileInfo, enAppTypePara, usEfIdPara, ucRecordNumPara) \
{ \
    (pstGetfileInfo)->usEfId       = usEfIdPara; \
    (pstGetfileInfo)->ucRecordNum  = ucRecordNumPara; \
    (pstGetfileInfo)->enAppType    = enAppTypePara; \
    (pstGetfileInfo)->ucRsv        = 0; \
}

#define NAS_COMM_BUILD_USIM_SET_FILE_INFO(pstSetfileInfo, enAppTypePara, usEfIdPara, ucRecordNumPara, ulEfLenPara, pucEfPara) \
{ \
    (pstSetfileInfo)->enAppType    = enAppTypePara; \
    (pstSetfileInfo)->usEfId       = usEfIdPara; \
    (pstSetfileInfo)->ucRecordNum  = ucRecordNumPara; \
    (pstSetfileInfo)->ucRsv        = 0; \
    (pstSetfileInfo)->ulEfLen      = ulEfLenPara; \
    (pstSetfileInfo)->pucEfContent = pucEfPara; \
}

#define NAS_COMM_MIN(ucValue1, ucValue2) \
   ( (ucValue1) > (ucValue2)) ? (ucValue2) : (ucValue1);


/*****************************************************************************
  3类型定义
*****************************************************************************/
typedef struct
{
    VOS_PID                             ulPid;                    /* 启动Timer的PID */
    VOS_UINT32                          ulTimerName;              /* Timer名 */
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;              /* 定时器精度 */
}NAS_TIMER_PRECISION_STRU;


enum NAS_TIMER_OPERATION_TYPE_ENUM
{
    NAS_TIMER_OPERATION_START,
    NAS_TIMER_OPERATION_STOP
};
typedef VOS_UINT32  NAS_TIMER_OPERATION_TYPE_ENUM_UINT32;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT32                          ulTimeLen;
    NAS_TIMER_OPERATION_TYPE_ENUM_UINT32        ulTimeAction;
}NAS_TIMER_OPERATION_STRU;

/* 巴西TIM拨号错误码结构体 */
typedef struct
{
    VOS_UINT32    ulUsed;                           /* 1: 错误码有效 0：错误码无效 */
    VOS_UINT32    ulErrCode;
}SM_PDP_ACT_ERR_CODE_STRU;

/*****************************************************************************
 结构名    : NAS_CONVERT_MTC_SESSION_STRU
 结构说明  : NAS与MTC的sesson type 转换结构体
 1.日    期   : 2015年09月04日
   作    者   : j00174725
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enNasSessionType;
    MTC_SESSION_TYPE_ENUM_UINT8         enMtcSessionType;
    VOS_UINT8                           aucReserved[2];
}NAS_CONVERT_MTC_SESSION_STRU;




/*****************************************************************************
  4 宏定义
*****************************************************************************/

#define     Cm_MemSet(pBuf,Data,Len)    PS_NAS_MEM_SET((pBuf),(Data),(Len))
#define     Cm_MemCpy(pDst,pSrc,Len)    PS_NAS_MEM_CPY((pDst),(pSrc),(Len))
#define     Cm_Malloc(ulPid, ulSize)    PS_NAS_MEM_ALLOC((ulPid),(ulSize), WUEPS_MEM_NO_WAIT)
#define     Cm_Free(ulPid, pMem)        PS_NAS_MEM_FREE((ulPid),(pMem))

#define     NAS_MEM_FAIL()              PS_NAS_LOG(WUEPS_PID_SS, 0, PS_LOG_LEVEL_ERROR, "NAS Mem Operation Failed!");
#define     NAS_MSG_FAIL()              PS_NAS_LOG(WUEPS_PID_SS, 0, PS_LOG_LEVEL_ERROR, "NAS Msg Opration Failed!");
#define     NAS_TIMER_FAIL()            PS_NAS_LOG(WUEPS_PID_SS, 0, PS_LOG_LEVEL_ERROR, "NAS Timer Opration Failed!");

/* 对PID,MsgName,以及EventType的操作 */
/*
    约束: PID结构 Bit0~Bit11: 模块ID  Bit12~Bit15: 保留 Bit16~Bit19: CPU ID Bit20~Bit31: 保留
    例: PID: 0x000A0BCD  ->  0x0000ABCD  ->  0xABCD0000
        MSG: 0x0000abcd
        EVT: 0xABCDabcd
*/
#define NAS_BuildEventType(ulSndPid, usMsgName) \
    (((VOS_UINT32)(/*lint -e778*/((ulSndPid) & 0xF0000)/*lint +e778*/ \
    | (((ulSndPid) & 0xFFF) << 4)) << 12) | (usMsgName))      /* 根据 Pid以及usMsgName 构建EventType  */

#define NAS_ExtractMsgNameFromEvtType(ulEventType)     ((VOS_UINT16)((ulEventType) & 0x0000FFFF))          /* 从EventType中获取MsgName     */
#define NAS_ExtractSndPidFromEvtType(ulEventType)  \
    ((((ulEventType) & 0xFFF0000) >> 16) | (((ulEventType) & 0xF0000000) >> 12))   /* 从EventType中获取SndPid      */

#define NAS_GetMsgSenderPid(pMsg)                      (((MSG_HEADER_STRU*)pMsg)->ulSenderPid)
#define NAS_GetMsgLength(pMsg)                         (((MSG_HEADER_STRU*)pMsg)->ulLength)
#define NAS_GetMsgName(pMsg)                           (((MSG_HEADER_STRU*)pMsg)->ulMsgName)
#define NAS_GetTimerName(pMsg)                         (PS_GET_REL_TIMER_NAME(pMsg))




/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
extern VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg);

extern VOS_UINT32   NAS_StartRelTimer(
    HTIMER                              *phTm,
    VOS_PID                             Pid,
    VOS_UINT32                          ulLength,
    VOS_UINT32                          ulName,
    VOS_UINT32                          ulParam,
    VOS_UINT8                           ucMode
);

extern VOS_TIMER_PRECISION_ENUM_UINT32 NAS_GetTimerPrecision(
        VOS_PID                             Pid,
        VOS_UINT32                          ulName
    );
extern VOS_UINT32   NAS_StopRelTimer(
    VOS_PID                             Pid,
    VOS_UINT32                          ulName,
    HTIMER                              *phTm
);

/***  All the following functions are defined in MM_CellProc1.c  ***/
extern VOS_VOID NAS_MM_StoreCsUnavailableInfo(
    VOS_UINT16                          usCause,
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU  *pstCsUnavailableInfo
);

/***  All the following functions are defined in GmmAttach.c  ***/
extern VOS_VOID NAS_GMM_StorePsUnavailableInfo(
    VOS_UINT8                           ucCause,
    NAS_MNTN_PS_UNAVAILABLE_INFO_STRU  *pstPsUnavailableInfo
);

extern VOS_BOOL NAS_PreventTestImsiRegFlg(VOS_VOID);

VOS_UINT32 NAS_ConvertSessionTypeToMTCFormat(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enNasSessionType,
    MTC_SESSION_TYPE_ENUM_UINT8        *penMtcSessionType
);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                        /* __cpluscplus         */

#endif
