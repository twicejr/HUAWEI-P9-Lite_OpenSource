/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MmGsmDifMsg.h
  Author      : ---
  Version     : V200R001
  Date        : 2005-09-08
  Description : 该头文件定义了子模块 GsmDifMsgProc 的接口定义
  History     :
  1. Date:2005-04-19
     Author: ---
     Modification:Create
  2. s46746 2006-03-39  根据问题单A32D02486修改
  3.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  4.日    期   : 2006年11月22日
    作    者   : s46746
    修改内容   : 问题单号:A32D07372
************************************************************************/

#ifndef _MM_GSMDIFMSG_H_
#define _MM_GSMDIFMSG_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MM_T3212_UNIT_TRANSFORM         360000/*(6 * 60 * 1000)*/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/*模块名＋意义＋HEADER
 */


/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */
VOS_UINT8 MM_RcvGsmRrcPagingInd(VOS_VOID *pRcvMsg);

VOS_UINT8 MM_RcvGsmRrcSyncInd(VOS_VOID *pRcvMsg);

VOS_INT32 MM_GasRrDataReq(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority,
                          VOS_UINT32 ulSize, VOS_INT8 *pData);

VOS_UINT32  MM_SupplementNsdInfo(VOS_UINT8 *pData);

VOS_INT32 MM_WasRrDataReq(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority,
                          VOS_UINT32 ulSize, VOS_INT8 *pData);

VOS_INT32 MM_GasRrEstReq(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain,
                         VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo, RRC_PLMN_ID_STRU *pstPlmnId,
                         VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg);

VOS_INT32 MM_WasRrEstReq(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain,
                         VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo, RRC_PLMN_ID_STRU *pstPlmnId,
                         VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg);


VOS_INT32 MM_GasRrRelReq(VOS_UINT8 ucCnDomain,RRC_CELL_BAR_ENUM_UINT32 enBarValidFlg);

/*VOS_INT32 MM_GasRrAbortReq(VOS_UINT32 ulAbortType);*/

VOS_INT32 MM_GasAttachReq(ATTACH_INFO_STRU *pAttachInfo);

VOS_INT32 MM_GasUsimStatusReq(USIM_VALID_INFO_STRU *pUsimValidInfo);

VOS_INT32 MM_GasSecurityKeyChgReq(SECURITY_KEY_INFO_STRU *pSecurityKeyInfo);

VOS_INT32 MM_GasTmsiLaiChgReq(NAS_INFO_TMSI_LAI_STRU *pTmsiLai);

VOS_INT32 MM_GasDelKeyReq(VOS_UINT8 ucCnDomain);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MmGsmDifMsg.h */
