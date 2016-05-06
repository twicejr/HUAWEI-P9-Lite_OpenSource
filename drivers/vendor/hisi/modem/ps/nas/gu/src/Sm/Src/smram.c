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


/*****************************************************************************
 函 数 名  : NAS_SM_GetTiMapToNsapi
 功能描述  : 获取TI和NSAPI的映射关系表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TI和NSAPI的映射关系表头指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月18日
    作    者   : l00198894
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT8 * NAS_SM_GetTiMapToNsapi(VOS_VOID)
{
    return &g_TiMapToNsapi[0];
}

/*****************************************************************************
 函 数 名  : NAS_SM_GetCrMapToNsapi
 功能描述  : 获取CR和NSAPI的映射关系表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CR和NSAPI的映射关系表头指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月18日
    作    者   : l00198894
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT8 * NAS_SM_GetCrMapToNsapi(VOS_VOID)
{
    return &g_CrMapToNsapi[0];
}

/*****************************************************************************
 函 数 名  : NAS_SM_GetTiExt
 功能描述  : 获取ti是否有扩展位
 输入参数  : 无
 输出参数  : 无
 返 回 值  : Ti是否为扩展为的标识
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月18日
    作    者   : l00198894
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT8 NAS_SM_GetTiExt(VOS_VOID)
{
    return g_ucTiExt;
}

/*****************************************************************************
 函 数 名  : NAS_SM_SetTiExt
 功能描述  : 设置ti是否有扩展位
 输入参数  : Ti是否为扩展为的标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月18日
    作    者   : l00198894
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID NAS_SM_SetTiExt(VOS_UINT8 ucTiExt)
{
    g_ucTiExt = ucTiExt;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_GetSmEntity
 功能描述  : 获取SM实体
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SM实体指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月18日
    作    者   : l00198894
    修改内容   : 新增函数

*****************************************************************************/
SM_ENTITY_STRU * NAS_SM_GetSmEntity(VOS_VOID)
{
    return &g_SmEntity;
}

/*****************************************************************************
 函 数 名  : NAS_SM_GetSmPdpAddrApn
 功能描述  : 获取SM保存的PDP地址与APN
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SM保存的PDP地址与APN指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月18日
    作    者   : l00198894
    修改内容   : 新增函数

*****************************************************************************/
SM_PDP_ADDR_AND_APN_STRU * NAS_SM_GetSmPdpAddrApn(VOS_VOID)
{
    return &g_SmPdpAddrApn;
}

/*****************************************************************************
 函 数 名  : NAS_SM_GetSapi
 功能描述  : 获取Sapi数组指针
 输入参数  : VOS_UINT8  ucIndex -- 索引
 输出参数  : 无
 返 回 值  : Sapi数组指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月18日
    作    者   : l00198894
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT8 * NAS_SM_GetSapi(VOS_UINT8 ucIndex)
{
    return &(g_aucSapi[ucIndex][0]);
}

/*****************************************************************************
 函 数 名  : NAS_SM_GetSmSgsnVersion
 功能描述  : 获取SM Sgsn的版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SM Sgsn的版本
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月18日
    作    者   : l00198894
    修改内容   : 新增函数

*****************************************************************************/
GMMSM_SGSN_REL_VER_ENUM NAS_SM_GetSmSgsnVersion(VOS_VOID)
{
    return g_SmSgsnVersion;
}

/*****************************************************************************
 函 数 名  : NAS_SM_SetSmSgsnVersion
 功能描述  : 设置SM Sgsn的版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SM Sgsn的版本
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月18日
    作    者   : l00198894
    修改内容   : 新增函数

*****************************************************************************/
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

