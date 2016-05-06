/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmApi.h
  Description : Nas层Gmm对As提供的Api接口头文件
  History     :
      1.  张志勇  2003-12-08: The first version
      2.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
      3.日    期   : 2011年12月29日
        作    者   : l00130025
        修改内容   : DTS2011082201679/DTS2011121504358,切换模式，回退后W/G下注册状态没有与NAS同步
*******************************************************************************/
#ifndef _NAS_API_H_
#define _NAS_API_H_

/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /* __cpluscplus */
#endif  /* __cpluscplus */


#include "Nasrrcinterface.h"
#include "asnasapi.h"

#pragma pack(4)
/* RRC-NAS interface API definition */
typedef VOS_INT32 (*RRMM_DATA_REQ_FUNC)(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority,
                                   VOS_UINT32 ulSize, VOS_INT8 *pData);
typedef VOS_INT32 (*RRMM_EST_REQ_FUNC)(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain,
      VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo, RRC_PLMN_ID_STRU *pstPlmnId, VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg);
typedef VOS_INT32 (*RRMM_REL_REQ_FUNC)(VOS_UINT8 ucCnDomain,RRC_CELL_BAR_ENUM_UINT32  enBarValidFlg);

typedef struct gmm_imported_func_list_stru
{
    RRMM_DATA_REQ_FUNC                      RrmmDataReqFunc;
    RRMM_EST_REQ_FUNC                       RrmmEstReqFunc;
    RRMM_REL_REQ_FUNC                       RrmmRelReqFunc;
}GMM_IMPORTED_FUNC_LIST_STRU;
#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cpluscplus */

#endif /* _NAS_API_H_ */
