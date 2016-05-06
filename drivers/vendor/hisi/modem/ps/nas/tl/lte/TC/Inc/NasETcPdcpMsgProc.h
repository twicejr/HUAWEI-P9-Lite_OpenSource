/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasTcPdcpMsgProc.h
  Description     : NasTcPdcpMsgProc.c header file
  History         :
      1.李洪 00150010       2009-10-13  Draft Enact

******************************************************************************/

#ifndef __NASTCPDCPMSGPROC_H__
#define __NASTCPDCPMSGPROC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasETcPublic.h"
#include  "LTcPdcpInterface.h"

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


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_ETC_RESULT_TYPE_ENUM
 枚举说明  : 结果枚举
 ***************************************************************************/
enum NAS_ETC_RESULT_TYPE_ENUM
{
    NAS_ETC_RESULT_TYPE_SUCCESS                                   = 0,
    NAS_ETC_RESULT_TYPE_FAIL                                      = 1,

    NAS_ETC_RESULT_TYPE_BUTT
};
typedef VOS_UINT32   NAS_ETC_RESULT_TYPE_ENUM_UINT32;

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
extern VOS_VOID  NAS_ETC_PdcpUlMsgDistr
       (
           VOS_VOID                           *pRcvMsg
       );
extern VOS_VOID  NAS_ETC_RcvTcPdcpUlActTestModeCnf
       (
           const LTC_LPDCP_ACTIVATE_TEST_MODE_CNF_STRU *pRcvMsg
       );
extern VOS_VOID  NAS_ETC_RcvTcPdcpUlDeactTestModeCnf
       (
           const LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF_STRU *pRcvMsg
       );
extern VOS_VOID  NAS_ETC_RcvTcPdcpUlStartTestLoopCnf
       (
           const LTC_LPDCP_START_TEST_LOOP_CNF_STRU *pRcvMsg
       );
extern VOS_VOID  NAS_ETC_RcvTcPdcpUlStopTestLoopCnf
       (
           const LTC_LPDCP_STOP_TEST_LOOP_CNF_STRU *pRcvMsg
       );
extern VOS_VOID  NAS_ETC_SndTcPdcpActTestModeMsg
       (
           const NAS_ETC_NW_MSG_STRU                 *pstTcNwMsgIE
       );
extern VOS_VOID  NAS_ETC_SndTcPdcpDeactTestModeMsg(VOS_VOID);
extern VOS_VOID  NAS_ETC_SndTcPdcpStartTestLoopMsg
       (
           const NAS_ETC_NW_MSG_STRU                 *pstTcNwMsgIE
       );
extern VOS_VOID  NAS_ETC_SndTcPdcpStopTestLoopMsg
       (
           const NAS_ETC_NW_MSG_STRU                 *pstTcNwMsgIE
       );
extern VOS_VOID  NAS_ETC_SndTcCdsActTestModeMsg(VOS_VOID);
extern VOS_VOID  NAS_ETC_SndTcCdsDeactTestModeMsg(VOS_VOID);
extern VOS_VOID  NAS_ETC_SndTcCdsStartTestLoopMsg
       (
            const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
       );

extern VOS_VOID  NAS_ETC_SndTcCdsStopTestLoopMsg(VOS_VOID);


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

#endif /* end of NasTcPdcpMsgProc.h */
