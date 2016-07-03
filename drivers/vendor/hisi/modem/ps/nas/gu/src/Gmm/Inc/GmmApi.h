
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
