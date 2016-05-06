

#ifndef __NASEMMLPPGPROC_H__
#define __NASEMMLPPGPROC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
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

#include    "NasEmmPubUCnMsgDecode.h"
#include    "LRrcLNasInterface.h"
#include    "EmmLppInterface.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_EMM_LPP_MSG_HEADER(pMsg, MsgLenthNoHeader)\
                {\
                    (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
                    (pMsg)->ulSenderPid         = PS_PID_MM;\
                    (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
                    (pMsg)->ulReceiverPid       = PS_PID_LPP;\
                    (pMsg)->ulLength            = (MsgLenthNoHeader);\
                }

#define NAS_LPP_LMM_OPID_INVALID        0XFFFFFFFF


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
结构名    : NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU
结构说明  : NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU信息
1.日    期   : 2015年07月16日
作    者   : lifuxin 00253982
修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpAdditionalInfo :1;
    VOS_UINT32                          bitRsv              :31;

    VOS_UINT8                           ucContainerType;
    VOS_UINT8                           aucRsv[3];
    NAS_EMM_GENERIC_MESSAGE_CONTAINER_STRU stContainer;
    NAS_EMM_ADDITIONAL_INFOR_STRU       stAdditionalInfo;
} NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_VOID NAS_EMM_SendLppDataCnf
(
    LMM_LPP_SEND_RSLT_ENUM_UINT32   enDataCnfRst,
    VOS_UINT32                      ulOpId
);

extern VOS_VOID NAS_EMM_SendLppEstCnf
(
   LMM_LPP_EST_RESULT_ENUM_UINT32      enEstCnfRst
);

extern VOS_VOID NAS_EMM_CompUplinkGenericNasTransportMsg(VOS_UINT8 *pMsgBuf,
                                                         VOS_UINT32 *pulIndex,
                                                         const NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU *pMsgStruct);
extern VOS_UINT32 NAS_EMM_SndUplinkGenericTransportFailProc(VOS_VOID* pMsg, VOS_UINT32 *pulIsDelBuff);
extern VOS_UINT32 NAS_EMM_SndUplinkGenericTransportSuccProc(VOS_VOID* pMsg);

extern VOS_VOID NAS_EMM_SendMrrcDataReq_UplinkGenericNasTransport
(
    const NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU    *pstUplinkMsg,
    VOS_UINT32                                          ulEmmLppOrSsOpId,
    VOS_UINT32                                          ulLppSsFlag
);

extern VOS_UINT32 NAS_EMM_RevLppMsgDataReq(MsgBlock *  pMsg);
extern VOS_UINT32 NAS_EMM_RevLppMsgEstReq(MsgBlock *  pMsg);
extern VOS_UINT32 NAS_EMM_SndUplinkGenericTransportSuccProc(VOS_VOID* pMsg);
extern VOS_UINT32 NAS_EMM_SndUplinkGenericTransportFailProc(VOS_VOID* pMsg, VOS_UINT32 *pulIsDelBuff);
extern VOS_VOID NAS_EMM_SndLppStartInd(  VOS_VOID );
extern VOS_VOID NAS_EMM_SndLppCnf
(
    VOS_UINT32                          ulMsgId,
    LMM_LPP_EST_RESULT_ENUM_UINT32      ulEstRst,
    LMM_LPP_SEND_RSLT_ENUM_UINT32       enDataCnfRst,
    VOS_UINT32                          ulOpId
);
extern VOS_UINT32 NAS_EMM_CheckLcsOrLppMsgNeedHighPrioStore( VOS_VOID );
extern VOS_UINT32 NAS_EMM_CheckLcsOrLppMsgNeedLowPrioStore( VOS_VOID );
extern VOS_VOID NAS_EMM_SendLppRelInd();
extern VOS_VOID NAS_EMM_SendLppCellChangeInd
(
    VOS_UINT32          ulCellId,
    VOS_UINT32          ulEarfcn,
    VOS_UINT16          usPhyCellId,
    VOS_UINT8          *pucPlmnId
);
extern VOS_VOID NAS_EMM_SndLppStopInd(  VOS_VOID );
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


#endif /* end of NasEmmLppMsgProc.h */
