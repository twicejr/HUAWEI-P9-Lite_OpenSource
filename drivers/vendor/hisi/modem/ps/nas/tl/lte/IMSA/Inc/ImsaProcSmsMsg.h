/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaProcSmsMsg.h
    Description : ImsaProcSmsMsg.c头文件
    History     :
      1.sunbing 00049683    2013-06-19  Draft Enact


******************************************************************************/

#ifndef __IMSAPROCSMSMSG_H__
#define __IMSAPROCSMSMSG_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include "vos.h"
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

/* 消息类型 */
#define IMSA_SMS_NTM_DATA_TYPE_RP_DATA 1
#define IMSA_SMS_NTM_DATA_TYPE_RP_ACK  3
#define IMSA_SMS_NTM_DATA_TYPE_RP_ERR  5

#define IMSA_SMS_MTN_DATA_TYPE_RP_DATA  0
#define IMSA_SMS_MTN_DATA_TYPE_RP_ACK   2
#define IMSA_SMS_MTN_DATA_TYPE_RP_ERR   4
#define IMSA_SMS_MTN_DATA_TYPE_RP_SMMA  6


/* RP ERROR CAUSE */
//#define  IMSA_SMS_ERR_CAUSE_MTI_MO_RP_ERROR                 4
//#define  SMR_ERR_CAUSE_NET_OUT_OF_ORDER                    38
#define  IMSA_SMS_ERR_CAUSE_TEMP_FAILURE                        41
//#define  SMR_ERR_CAUSE_CONGESTION                          42
#define  IMSA_SMS_ERR_CAUSE_RES_UNAVAIL                         47
//#define  IMSA_SMS_ERR_CAUSE_VALUE_INVALID_MR                    81
//#define  SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR              96
//#define  SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST            97
//#define  SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE           98
//#define  SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR                  111



#define IMSA_SMS_TIMER_TR1M_LENGTH     35000
#define IMSA_SMS_TIMER_TR2M_LENGTH     15000
#define IMSA_SMS_TIMER_TRAM_LENGTH     30000

#define IMSA_SMS_WAIT_RESOURCE_APPLY_CNF_LENGTH     5000


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/




/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID IMSA_SMS_SndMsgReportInd(VOS_UINT32 ulErrCode,
                                                  const VOS_UINT8* pucData,
                                                  VOS_UINT32 ulDataLen);
extern VOS_VOID IMSA_SMS_SndImsSmsMsg(const VOS_UINT8 *pucData,
                                                  VOS_UINT32 ulLength,
                                                  VOS_CHAR *pcSmsc);

extern VOS_VOID IMSA_SMS_Init(VOS_VOID );
extern VOS_VOID IMSA_SMS_ClearResource(VOS_VOID);
extern VOS_VOID IMSA_ProcSmsMsg(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_SMS_MemNotifyRetrans( VOS_UINT32 ulErrCode );
extern VOS_VOID IMSA_SMS_ProcTimerMsgTr1m(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_SMS_ProcTimerMsgTr2m(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_SMS_ProcTimerMsgTram(const VOS_VOID *pTimerMsg);


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

#endif /* end of ImsaProcSmsMsg.h */




