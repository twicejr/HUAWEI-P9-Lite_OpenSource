

#ifndef __NASEMMSSMSGPROC_H__
#define __NASEMMSSMSGPROC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LmmLcsInterface.h"
#include    "NasEmmPubUCnMsgDecode.h"

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
/* 打包LCS消息头 */
/* LCS模块PID变更为WUEPS_PID_LCS */
#define NAS_EMM_LCS_MSG_HEADER(pMsg, MsgLenthNoHeader)\
            {\
                (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
                (pMsg)->ulSenderPid         = PS_PID_MM;\
                (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
                (pMsg)->ulReceiverPid       = WUEPS_PID_LCS;\
                (pMsg)->ulLength            = (MsgLenthNoHeader);\
            }



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
extern VOS_VOID NAS_LMM_SndLcsDataInd
(
    NAS_EMM_GENERIC_MESSAGE_CONTAINER_STRU     *pstContainer
);

extern VOS_VOID NAS_EMM_SndLcsDataCnf
(
    LMM_LCS_SEND_RSLT_ENUM_UINT32        enDataCnfRst,
    VOS_UINT32                          ulOpId
);

extern VOS_VOID  NAS_LMM_SndLmmLcsEstCnf
(
    LMM_LCS_EST_RESULT_ENUM_UINT32       ulEstRst,
    VOS_UINT32                          ulOpid
);


extern VOS_UINT32 NAS_EMM_RcvLcsMsgEstReq
(
    MsgBlock                           *pMsg
);

extern VOS_UINT32 NAS_EMM_RcvLcsMsgDataReq
(
    MsgBlock                           *pMsg
);
extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLcsEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_VOID    NAS_EMM_SndLcsPosCapInfoInd( VOS_VOID );
extern VOS_UINT32 NAS_EMM_CheckLcsOrLppMsgNeedHighPrioStore( VOS_VOID );
extern VOS_UINT32 NAS_EMM_CheckLcsOrLppMsgNeedLowPrioStore( VOS_VOID );
extern VOS_VOID NAS_LMM_SndLcsRelInd( VOS_VOID );



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


#endif /* end of NasEmmSsMsgProc.h */
