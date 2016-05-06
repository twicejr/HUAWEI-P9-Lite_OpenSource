/******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : R_ITF_FlowCtrl.h
  Author       : g45205
  Version      : V100R001
  Date         : 2006-05-17
  Description  :
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2006-05-17
     Author: g45205
     Modification:Create
******************************************************************************/
#ifndef __R_ITF_FLOWCTRL_H__
#define __R_ITF_FLOWCTRL_H__

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "vos.h"

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/


/******************************************************************************
   3 私有定义
******************************************************************************/
#define R_ITF_WARNING_LOG(String) \
        (VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(UEPS_PID_FLOWCTRL_C), DIAG_MODE_COMM, PS_PRINT_WARNING), (UEPS_PID_FLOWCTRL_C), __FILE__, __LINE__, "%s \r\n", String)

#define R_ITF_WARNING_LOG1(String, Para1) \
        (VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(UEPS_PID_FLOWCTRL_C), DIAG_MODE_COMM, PS_PRINT_WARNING), (UEPS_PID_FLOWCTRL_C), __FILE__, __LINE__, "%s, %d \r\n", String, Para1)

#define R_ITF_WARNING_LOG2(String, Para1, Para2) \
        (VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(UEPS_PID_FLOWCTRL_C), DIAG_MODE_COMM, PS_PRINT_WARNING), (UEPS_PID_FLOWCTRL_C), __FILE__, __LINE__, "%s, %d, %d \r\n", String, Para1, Para2)

#define R_ITF_WARNING_LOG3(String, Para1, Para2, Para3) \
        (VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(UEPS_PID_FLOWCTRL_C), DIAG_MODE_COMM, PS_PRINT_WARNING), (UEPS_PID_FLOWCTRL_C), __FILE__, __LINE__, "%s, %d, %d, %d \r\n", String, Para1, Para2, Para3)

#define R_ITF_WARNING_LOG4(String, Para1, Para2, Para3, Para4) \
        (VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(UEPS_PID_FLOWCTRL_C), DIAG_MODE_COMM, PS_PRINT_WARNING), (UEPS_PID_FLOWCTRL_C), __FILE__, __LINE__, "%s, %d, %d, %d, %d \r\n", String, Para1, Para2, Para3, Para4)

/* R接口流控掩码 */
#define R_ITF_FLOW_CTRL_MASK_MEM_CNT        (0x00000001)
#define R_ITF_FLOW_CTRL_MASK_MEM_SIZE       (0x00000002)
#define R_ITF_FLOW_CTRL_MASK_CPU_LOAD       (0x00000004)

/*
  把协议栈(主要是NAS)信令面的流控与用户面流控条件统一起来，
  增加类型为R_ITF_FLOW_CTRL_TYPE_PS_CMD的流控，该类型流控水线值是1。
  信令面需要流控时，调用流控接口，类型填R_ITF_FLOW_CTRL_MASK_PS_CMD，
  新水线填R_ITF_FLOW_PS_CMD_START。解除流控类似，新水线填R_ITF_FLOW_PS_CMD_START。
  */
#define R_ITF_FLOW_CTRL_MASK_PS_CMD         (0x00000008)

#define R_ITF_FLOW_PS_CMD_STOP              (0)
#define R_ITF_FLOW_PS_CMD_START             (2)
/******************************************************************************
   4 全局变量定义
******************************************************************************/

/******************************************************************************
   5 枚举变量定义
******************************************************************************/

/* R接口流控类型定义 */
enum R_ITF_FLOW_CTRL_TYPE_ENUM
{
    R_ITF_FLOW_CTRL_TYPE_MEM_CNT        = 0,    /*内存块个数*/
    R_ITF_FLOW_CTRL_TYPE_MEM_SIZE,              /*内存总使用量*/
    R_ITF_FLOW_CTRL_TYPE_BUTT
};
typedef VOS_UINT32 R_ITF_FLOW_CTRL_TYPE_ENUM_UINT32;

/* 流控指示类型枚举 */
enum R_ITF_FLOW_CTR_CMD_ENUM
{
    R_ITF_FLOW_CTRL_START,               /*流控启动指示*/
    R_ITF_FLOW_CTRL_STOP,                /*流控停止指示*/

    R_ITF_FLOW_CTRL_CMD_BUTT
};
typedef VOS_UINT32 R_ITF_FLOW_CTRL_CMD_ENUM_UINT32;

/* R接口流控数据结构定义 */
typedef struct
{
    VOS_UINT32              ulMask;         /* 该流控要素的掩码值 */
    VOS_UINT32              ulCurrLev;
    VOS_UINT32              ulNormalLev;    /* 解除流控阀值 */
    VOS_UINT32              ulWarningLev;   /* 启动流控阀值 */
    VOS_UINT32              ulMaxLev;       /* 最大的情况，供采集数据确定阀值使用 */
} R_ITF_FLOW_LEV_STRU;

typedef struct
{
    VOS_UINT32              ulCtrlMask;
    VOS_UINT32              ulLastOptTick;
    VOS_UINT32              ulCtrlFlag;
    VOS_RATMODE_ENUM_UINT32 enRateMode;
    R_ITF_FLOW_LEV_STRU     astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_BUTT]; /* 0:MemCnt,1:MemSize,2:PppMsgCnt */
} R_ITF_FLOW_CTRL_STRU;

/*可维可测消息*/
typedef struct
{
    VOS_MSG_HEADER                                                               /* 消息头 */        /* _H2ASN_Skip */
    R_ITF_FLOW_CTRL_TYPE_ENUM_UINT32            enFlowCtrlType;                  /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT32                                  ulNewLevel;
    R_ITF_FLOW_CTRL_CMD_ENUM_UINT32             enFlowCtrlCmd;
    VOS_UINT32                                  ulResult;
}R_ITF_FLOW_CTRL_MNTN_INFO_STRU;


extern R_ITF_FLOW_CTRL_STRU             g_stRItfFlowCtrl;

extern VOS_UINT32 R_ITF_SetFlowCtrl
(
    VOS_UINT32                                  ulFlowCtrlType,
    VOS_UINT32                                  ulNewLev
);
extern VOS_UINT32 R_ITF_ClearFlowCtrl(VOS_UINT32 ulFlowCtrlType, VOS_UINT32 ulNewLev);
extern VOS_UINT32 R_ITF_RateDismatchUsbEnable(VOS_VOID);
extern VOS_UINT32 R_ITF_RateDismatchWifiEnable(VOS_VOID);
extern VOS_VOID   R_ITF_ResetFlowCtrl(VOS_VOID);
extern VOS_VOID   R_ITF_SetLFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode);
extern VOS_VOID   R_ITF_Set1XFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode);
extern VOS_VOID   R_ITF_SetHrpdFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode);
extern VOS_VOID   R_ITF_InitFlowCtrl(VOS_VOID);
extern VOS_UINT32 R_ITF_StartFlowCtrl(VOS_RATMODE_ENUM_UINT32 enRateMode);
extern VOS_UINT32 R_ITF_StopFlowCtrl(VOS_RATMODE_ENUM_UINT32 enRateMode);

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


#endif
