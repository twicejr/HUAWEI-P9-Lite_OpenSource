/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

******************************************************************************
    File name   : ImsaProcAtMsg.h
    Description : ImsaProcAtMsg.c头文件
    History     :
      1.leili 00132387    2013-10-14  Draft Enact

******************************************************************************/

#ifndef __IMSAPROCATMSG_H__
#define __IMSAPROCATMSG_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "AtImsaInterface.h"
#include    "ImsaEntity.h"
#include    "ImsaProcImsCallMsg.h"

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
 结构名  : IMSA_AT_MGMT_DATA_STRU
 结构说明: 查询IMPU时，保存AT命令

 修改历史      :
  1.日    期   : 2013年12月24日
    作    者   : w00209181
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
} IMSA_AT_MGMT_DATA_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID IMSA_ProcMsgCiregSetReq (const AT_IMSA_CIREG_SET_REQ_STRU *pstCiregSetReq);
extern VOS_VOID IMSA_SndMsgAtCireguInd (VOS_UINT32 ulRegInfo);
extern VOS_VOID IMSA_ProcMsgCiregQryReq (const AT_IMSA_CIREG_QRY_REQ_STRU *pstCiregQryReq);
extern VOS_VOID IMSA_ProcMsgCirepSetReq (const AT_IMSA_CIREP_SET_REQ_STRU *pstCirepSetReq);
extern VOS_VOID IMSA_SndMsgAtCirephInd (AT_IMSA_SRVCC_HANDVOER_ENUM_UINT32   enHandover);
extern VOS_VOID IMSA_SndMsgAtCirepiInd (AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32      enImsvops);
extern VOS_VOID IMSA_ProcMsgCirepQryReq (const AT_IMSA_CIREP_QRY_REQ_STRU *pstCiregQryReq);

extern VOS_VOID IMSA_ProcMsgVolteImpuQryReq(const AT_IMSA_VOLTEIMPU_QRY_REQ_STRU *pstVolteImpuQryReq);
extern VOS_VOID IMSA_SndMsgAtQryVolteImpuCnf
(
    VOS_UINT32 ulResult,
    VOS_UINT32 ulImpuLen,
    VOS_CHAR *pucImpu
);

extern VOS_VOID IMSA_ProcMsgCcwaiSetReq(const AT_IMSA_CCWAI_SET_REQ_STRU *pstCcwaiSetReq);
extern VOS_VOID IMSA_SndMsgAtCcwaiSetCnf
(
    VOS_UINT32 ulResult
);
extern VOS_VOID IMSA_SndMsgAtPdpActInd (const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo);
extern VOS_VOID IMSA_SndMsgAtPdpDeactInd (TAF_PDP_TYPE_ENUM_UINT8             enPdpType);

extern VOS_VOID IMSA_SndMsgAtMtStatusInd(const IMSA_MT_STATUS_REPORT_STRU    *pstMtReport);

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

#endif /* end of ImsaProcAtMsg.h */



