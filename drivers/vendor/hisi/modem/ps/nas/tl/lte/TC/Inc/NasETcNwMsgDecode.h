/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasTcNwMsgDecode.h
  Description     : NasTcNwMsgDecode.c header file
  History         :
      1.李洪 00150010       2009-10-13  Draft Enact

******************************************************************************/

#ifndef __NASTCNWMSGDECODE_H__
#define __NASTCNWMSGDECODE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasETcPublic.h"

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
  2 Macro
*****************************************************************************/
#define NAS_ETC_MSG_MIN_LEN                      (2)
#define NAS_ETC_MIN_ACT_TEST_MODE_MSG_LEN        (3)
#define NAS_ETC_MIN_CLOSE_UE_TEST_LOOP_MSG_LEN   (4)
#define NAS_ETC_SUM_LEN_OF_PD_MSGTYPE            (2)
#define NAS_ETC_MAX_DRB_NUM                      (8)
#define NAS_ETC_MAX_SDU_SIZE                     (1520)          /* 单位:字节*/
#define NAS_ETC_LB_SETUP_DRB_IE_LEN              (3)

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
extern NAS_ETC_CAUSE_ENUM_UINT8  NAS_ETC_DecodeNwActTestModeMsg
       (
           const VOS_UINT8                    *pucMsg,
           VOS_UINT32                         *pulTcMsgLen,
           NAS_ETC_NW_MSG_STRU                 *pstMsgIE
       );
extern NAS_ETC_CAUSE_ENUM_UINT8  NAS_ETC_DecodeNwCloseUeTestLoopMsg
       (
           const VOS_UINT8                    *pucMsg,
           VOS_UINT32                         *pulTcMsgLen,
           NAS_ETC_NW_MSG_STRU                 *pstMsgIE
       );
extern NAS_ETC_CAUSE_ENUM_UINT8 NAS_ETC_DecodeNwMsg(VOS_UINT8 *pucMsg,
                                                VOS_UINT32 *pulMsgLen,
                                                NAS_ETC_NW_MSG_STRU *pstMsgIE);

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

#endif /* end of NasTcNwMsgDecode.h */
