/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaPublic.h
    Description : ImsaPublic.c头文件
    History     :
      1.sunbing 00049683    2013-06-19  Draft Enact


******************************************************************************/

#ifndef __IMSADSDSPUBLIC_H__
#define __IMSADSDSPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include "PsCommonDef.h"
#include "LPSCommon.h"
#include "ImsaEntity.h"
#include "LPsOm.h"
#include "ImsaImsEvent.h"
#include "ImsParm.h"
#include "ImsaLrrcInterface.h"
#include "NasFileId.h"
#include "PsRrmInterface.h"
#include "SpmImsaInterface.h"
#include "ImsaImsInterface.h"
#include "MsgImsaInterface.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define TI_IMSA_GET_SERVICE_WAIT_RF_RESOURCE_TIMER_LEN  (5000)
#define TI_IMSA_DEREG_WAIT_RF_RESOURCE_TIMER_LEN        (1000)
#define TI_IMSA_MO_CALL_WAIT_RF_RESOURCE_TIMER_LEN      (30000)
#define TI_IMSA_MT_CALL_WAIT_RF_RESOURCE_TIMER_LEN      (30000)
#define TI_IMSA_EMC_CALL_WAIT_RF_RESOURCE_TIMER_LEN     (30000)
#define TI_IMSA_MO_SMS_WAIT_RF_RESOURCE_TIMER_LEN       (30000)
#define TI_IMSA_MT_SMS_WAIT_RF_RESOURCE_TIMER_LEN       (30000)
#define TI_IMSA_RF_OCCUPIED_DELAY_PROC_TIMER_LEN        (1000)
#define TI_IMSA_POWER_OFF_WAIT_RF_RESOURCE_TIMER_LEN    (1000)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
 枚举名    : IMSA_DSDS_ENABLE_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : ST测试使用
*****************************************************************************/
enum IMSA_DSDS_ENABLE_FLAG_ENUM
{
    IMSA_DSDS_INIT = 0,            /*初始dsds*/
    IMSA_DSDS_ENABLE,               /*打开dsds*/
    IMSA_DSDS_DISABLE,                 /*关闭dsds*/
    IMSA_DSDS_BUTT,
};
typedef VOS_UINT8 IMSA_DSDS_ENABLE_FLAG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : IMSA_TASKTYPE_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : DSDS TASK Type状态枚举
*****************************************************************************/
enum IMSA_DSDS_MODEMID_ENUM
{
    IMSA_DSDS_MODEM0 = 0,                  /*MODEM0*/
    IMSA_DSDS_MODEM1,                      /*MODEM1*/
    IMSA_DSDS_MODEM_BUTT
};
typedef VOS_UINT8 IMSA_DSDS_MODEMID_ENUM_UINT8;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : IMSA_DSDS_TASKTYPE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存已发送的REQ对应的CNF信息
*****************************************************************************/
typedef struct
{
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType;
    IMSA_TASKTYPE_STATUS_ENUM_UINT8         enStatus;
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc;
    VOS_UINT32                              ulPara;
    VOS_UINT8                               ucHasBuffer;    /* 1:表示存在，0:表示不存在 */
    VOS_UINT8                               aucRsv[3];
}IMSA_DSDS_TASKTYPE_INFO_STRU;

/*****************************************************************************
 结构名    : IMSA_DSDS_BUFFER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA DSDS相关的缓存结构
*****************************************************************************/
typedef struct
{
    SPM_IMSA_CALL_ORIG_REQ_STRU             stMoCall;
    SPM_IMSA_CALL_ORIG_REQ_STRU             stEmcCall;
    SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU       stEnhancedConferrence;
    MSG_IMSA_RP_DATA_REQ_STRU               stMoSms;
    IMSA_IMS_OUTPUT_SMS_EVENT_STRU          stMtSms;
    MSG_IMSA_SMMA_REQ_STRU                  stSmma;
}IMSA_DSDS_BUFFER_INFO_STRU;

/*****************************************************************************
 结构名    : IMSA_DSDS_BUFFER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA DSDS相关的缓存结构
*****************************************************************************/
typedef struct
{
    IMSA_DSDS_BUFFER_INFO_STRU              stBufferInfo;

    IMSA_TIMER_STRU                         stWaitRegRFTimer;
    IMSA_TIMER_STRU                         stWaitDeRegRFTimer;
    IMSA_TIMER_STRU                         stWaitMoCallRFTimer;
    IMSA_TIMER_STRU                         stWaitMtCallRFTimer;
    IMSA_TIMER_STRU                         stWaitEmcCallRFTimer;
    IMSA_TIMER_STRU                         stWaitMoSmsRFTimer;
    IMSA_TIMER_STRU                         stWaitMtSmsRFTimer;
    IMSA_TIMER_STRU                         stDelayProcOccupiedTimer;
    IMSA_TIMER_STRU                         stWaitPowerOffRfTimer;
}IMSA_DSDS_PUBLIC_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/

/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern IMSA_DSDS_TASKTYPE_INFO_STRU     g_stImsaDsdsTaskTypeInfo[];
extern IMSA_DSDS_PUBLIC_INFO_STRU       g_stDsdsPubilcInfo;
#define IMSA_DSDS_ABNORMAL_IDX  0xff

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID  IMSA_DsdsProcRegResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcMoCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcEmcCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcMtCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcMoSmsResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcMtSmsResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcOccupyDelayTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsStartApplyReqTimer
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc
);

extern VOS_VOID  IMSA_DsdsStopApplyReqTimer
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc
);


extern VOS_UINT32  IMSA_DsdsIsHasActiveResource
(
    VOS_VOID
);

extern VOS_VOID IMSA_DsdsInit( VOS_VOID );
extern VOS_VOID IMSA_DsdsClearResource(VOS_VOID);
extern VOS_VOID IMSA_RrmMsgDistr(const VOS_VOID *pRcvMsg);
extern VOS_UINT32 IMSA_DsdsGetIndexByTaskType (RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType);
extern VOS_VOID IMSA_ProcMsgResourceApplyCnf
(
    const RRM_PS_RADIO_RESOURCE_APPLY_CNF_STRU *pstApplyCnf
);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaPublic.h */




