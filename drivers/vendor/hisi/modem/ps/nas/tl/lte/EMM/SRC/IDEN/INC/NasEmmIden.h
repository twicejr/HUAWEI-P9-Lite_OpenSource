/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.
 ******************************************************************************
    File name   : NasEmmIden.h
    Description : 定义EMM_IDEN模块需要的数据结构
    History     :
      1.  zangyalan 57968  2008-09-03  Draft Enact
      2.
******************************************************************************/

#ifndef __NASEMMIDEN_H__
#define __NASEMMIDEN_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "NasEmmGIMComm.h"
#include    "NasEmmPubUCnMsgDecode.h"
#include    "NasEmmIdenPubInterface.h"

#include    "NasEmmAttachEsmMsgProcess.h"

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

#define NAS_EMM_IDEN_IMSI_GLOBAL(i)     g_stEmmInfo.stMmUeId.aucImsi[i]
#define NAS_EMM_IDEN_IMEI_GLOBAL(i)     g_stEmmInfo.stMmUeId.aucImei[i]
#define NAS_EMM_IDEN_IMEISV_GLOBAL(i)   g_stEmmInfo.stMmUeId.aucImeisv[i]

#define EMM_MODILE_ID_IMSI              1 /*001*/
#define EMM_MOBILE_ID_IMEI              2 /*010*/
#define EMM_MOBILE_ID_IMEISV            3 /*011*/
#define EMM_MOBILE_ID_TMSI              4 /*100*/

#define NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN    1
#define NAS_EMM_NO_IDENTITY_LEN         3

#define NAS_EMM_IMSI_LEN                8
#define NAS_EMM_IMEI_LEN                8
#define NAS_EMM_IMEISV_LEN              9
#define NAS_EMM_TMSI_LEN                5

#define RRC_NAS_MSG_HEADER_LEN          2

/*封装GUTI模块的LOG打印宏*/
#define LOG_SUBMOD_ID_NAS_LMM_IDEN               1
#define NAS_EMM_IDEN_ERROR_LOG(String)          NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_IDEN, String)
#define NAS_EMM_IDEN_WARNING_LOG(String)        NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_IDEN, String)
#define NAS_EMM_IDEN_NORMAL_LOG(String)         NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_IDEN, String)
#define NAS_EMM_IDEN_INFO_LOG(String)           NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_IDEN, String)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

extern VOS_VOID NAS_EMM_Info(VOS_VOID);                   /* 获取UEID信息       */

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_EMM_IdenImsi
(
    LRRC_LNAS_MSG_STRU                     *pNasMsg,
    VOS_UINT32                             *ulMsgLen
);
extern VOS_VOID    NAS_EMM_IdenImei(LRRC_LNAS_MSG_STRU *pNasMsg);
extern VOS_VOID    NAS_EMM_IdenImeisv(LRRC_LNAS_MSG_STRU *pNasMsg);
extern VOS_VOID    NAS_EMM_CompCnIdenRsp(LRRC_LNAS_MSG_STRU *pNasMsg);
extern VOS_UINT32  NAS_EMM_IdenCnMsgLen(VOS_UINT8 ucIdenType);
extern VOS_VOID    NAS_EMM_IdenTypeGet(VOS_UINT8 ucIdenType, LRRC_LNAS_MSG_STRU *pNasMsg);
extern VOS_UINT8* NAS_MML_GetUeIdTmsi(VOS_VOID);
extern VOS_VOID  NAS_EMM_EncodeTmsi
(
    LRRC_LNAS_MSG_STRU  *pNasMsg,
    VOS_UINT32  *ulMsgLen
);
extern VOS_UINT32  NAS_EMM_GetTmsiStatus(VOS_VOID);


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

#endif /* end of 发送模块+接收模块+Interface.h */
