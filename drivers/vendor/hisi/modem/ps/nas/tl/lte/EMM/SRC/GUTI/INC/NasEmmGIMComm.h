/******************************************************************************


        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmGIMComm.h
    Description :
    History     :
      1.  zangyalan 57968  2008-09-18  Draft Enact
      2.
******************************************************************************/

#ifndef __NASEMMGIMCOMM_H__
#define __NASEMMGIMCOMM_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "PsLogdef.h"

#include "NasLmmPubMInclude.h"
#include "NasLmmPubMOm.h"
#include "LRrcLNasInterface.h"
#include "NasEmmMrrcPubInterface.h"
#include "NasEmmIdenPubInterface.h"
#include "NasEmmPubUMain.h"
#include "NasEmmSecuOm.h"

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
#define NAS_EMM_ERR                     VOS_ERR


/*各种需要用到的长度的宏*/
#define NAS_RRC_PRIORI_LEN              1
#define NAS_RRC_EST_CAUSE_LEN           4
#define NAS_RRC_EST_MSG_TYPE_LEN        4

#define NAS_RRC_MM_REL_REQ_LEN          4


#define NAS_MSG_STRU_MSG_SIZE_LEN       4


/*TaiList的宏*/
#define NAS_EMM_TAI_LIST                (g_stEmmInfo.stNetInfo.stTaiList)

/*bits | 4 | 3 | 2 | 1 |
       | 1 | 0 | 0 | 0 |EPS mobility management messages */

/*bits | 8 | 7 | 6 | 5 |
       | 0 | 0 | 0 | 0 | No security protection*/
#define NAS_EMM_CN_MSG_SE_EMM           0x00
#define NAS_EMM_CN_MSG_PD_EMM           0x07

/*和TAU\ser定义有重复*/
#define NAS_EMM_LEN_CN_MSG_PD_SI        1   /* one byte: Protocol discriminator and Sercurity header type */
#define NAS_EMM_LEN_CN_MSG_MT           1   /* one byte: Message type */
#define NAS_GUTI_COMP_NAS_MSG_LEN       2   /* len of Nas Msg in GUTI REALLOCATION COMPLETE*/

/*关于奇偶校验位的宏*/
#define NAS_EMM_ODD_BIT                 1
#define NAS_EMM_EVEN_BIT                0

/* 打包Emm-RRC消息头 */
#define NAS_EMM_GIM_RRC_MSG_HEADER(pMsg, ulMsgLen) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_ERRC;\
            (pMsg)->ulLength            = ulMsgLen;\
        }


/*封装GIM模块的LOG打印宏*/
#define LOG_SUBMOD_ID_NAS_LMM_GIM                4
#define NAS_EMM_GIM_ERROR_LOG(String)           NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_MRRC, String)
#define NAS_EMM_GIM_WARNING_LOG(String)         NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_MRRC, String)
#define NAS_EMM_GIM_NORMAL_LOG(String)          NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_MRRC, String)
#define NAS_EMM_GIM_INFO_LOG(String)            NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_MRRC, String)
#define NAS_EMM_GIM_INFO_LOG2(String, Para1, Para2)\
                                                NAS_LMM_LOG2_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_MRRC, String, Para1, Para2)

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
/*****************************************************************************
  9 OTHERS
*****************************************************************************/



/****************************************************************************/
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
