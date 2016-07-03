/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : smram.c
  Description  : sm的全局变量定义
  Function List:
  History:
      1.   张志勇      2004.04.01   新规作成
*******************************************************************************/
#include "SmInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif



VOS_UINT8                  g_TiMapToNsapi[256];                                     /* TI和NSAPI的映射关系                      */

VOS_UINT8                  g_CrMapToNsapi[256];                                     /* CR和NSAPI的映射关系                      */

VOS_UINT8                  g_ucTiExt;                                               /* 记录ti是否有扩展位                       */

SM_ENTITY_STRU             g_SmEntity;                                              /* sm实体定义                               */

SM_PDP_ADDR_AND_APN_STRU   g_SmPdpAddrApn;                                    /* 保存pdp address和apn                     */

/*                           该数组以NSAPI为索引:
                             第0行,即ucSapi[0][1]用来暂存SAPI,在填状态机时再读到SAPI数组具体位置;
                             第1行到第4行不使用;
                             第5行到第15行为NSAPI的索引.
                             第一列为有效标识,0-无效,1-有效;
                             第二列为SAPI,即ucSapi[i][1]的值为NSAPI i 的 SAPI.*/
VOS_UINT8                       g_aucSapi[SM_MAX_NSAPI_NUM + SM_NSAPI_OFFSET][2];

GMMSM_SGSN_REL_VER_ENUM    g_SmSgsnVersion; /* 保存GMM上报的当前SGSN版本信息 */



VOS_UINT8 * NAS_SM_GetTiMapToNsapi(VOS_VOID)
{
    return &g_TiMapToNsapi[0];
}


VOS_UINT8 * NAS_SM_GetCrMapToNsapi(VOS_VOID)
{
    return &g_CrMapToNsapi[0];
}


VOS_UINT8 NAS_SM_GetTiExt(VOS_VOID)
{
    return g_ucTiExt;
}


VOS_VOID NAS_SM_SetTiExt(VOS_UINT8 ucTiExt)
{
    g_ucTiExt = ucTiExt;
    return;
}


SM_ENTITY_STRU * NAS_SM_GetSmEntity(VOS_VOID)
{
    return &g_SmEntity;
}


SM_PDP_ADDR_AND_APN_STRU * NAS_SM_GetSmPdpAddrApn(VOS_VOID)
{
    return &g_SmPdpAddrApn;
}


VOS_UINT8 * NAS_SM_GetSapi(VOS_UINT8 ucIndex)
{
    return &(g_aucSapi[ucIndex][0]);
}


GMMSM_SGSN_REL_VER_ENUM NAS_SM_GetSmSgsnVersion(VOS_VOID)
{
    return g_SmSgsnVersion;
}


VOS_VOID NAS_SM_SetSmSgsnVersion(GMMSM_SGSN_REL_VER_ENUM enSmSgsnVersion)
{
    g_SmSgsnVersion = enSmSgsnVersion;
    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

