/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hsgw_apn_adpt_api.c
  版 本 号   : 初稿
  作    者   : honglei 50774
  生成日期   : 2013年5月17日
  最近修改   :
  功能描述   : HSGW产品APN/DOMAIN适配接口
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月17日
    作    者   : honglei 50774
    修改内容   : 创建文件

******************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "srv_common_inc.h"

#include "am_public.h"
#include "apn_adpt_api.h"
#include "a11_spu_sru_pub.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

S_CFG_DOMAINNODE *g_pstApnByIndex = NULL;
extern VOS_UINT32 A11_GetDomainByIndex( VOS_UINT16 usAPNIndex, S_CFG_DOMAINNODE **pstAPN);
extern VOS_UINT32 USM_GetApnCfgByApnIndex(VOS_UINT16 usApnIndex, HSGW_APN_INFO_S **ppstHsgwApn);

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : AM_ApnApiGetL2tpGroup
 功能描述  : APN的L2TP group配置
 输入参数  : VOS_UINT16 usApnIdx
 输出参数  : VOS_UINT16 *pusL2tpGroup
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetL2tpGroup(VOS_UINT16 usApnIdx, VOS_UINT16 *pusL2tpGroup)
{
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL;
    VOS_UINT32 ulRet = VOS_OK;

    ulRet = A11_GetDomainByIndex(usApnIdx, &pstDomain);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /* 未使能L2TP */
    if (VOS_TRUE != pstDomain->ucL2tp)
    {
        return VOS_ERR;
    }

    *pusL2tpGroup = pstDomain->usGroupNum;
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AM_ApnApiGetApnIdx
 功能描述  : 根据APN结构返回APN索引，主要用于各组的APN回调函数
 输入参数  : UCHAR *pucApnInfo
 输出参数  : VOS_UINT16 *pusApnIdx
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetApnIdx(UCHAR *pucApnInfo, VOS_UINT16 *pusApnIdx)
{
    S_CFG_DOMAINNODE *pstDomain = (S_CFG_DOMAINNODE*)pucApnInfo;

    if (VOS_NULL == pstDomain)
    {
        return VOS_ERR;
    }

    *pusApnIdx = pstDomain->usApnIndex;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AM_ApnApiGetApnIdxByName
 功能描述  : 根据APN名返回APN索引，注意该接口效率较低，需谨慎使用!
 输入参数  : UCHAR *pucApnInfo
 输出参数  : VOS_UINT16 *pusApnIdx
 返 回 值  : APN/Domain索引
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetApnIdxByName(UCHAR *pucApnName, VOS_UINT16 *pusApnIdx)
{
    VOS_UINT32 ulRet = VOS_OK;
    S_CFG_CDB_CONDITION sCondition = {0};
    S_CFG_DOMAINNODE tmpApn = {0};

    if ((NULL == pusApnIdx) || (NULL == pucApnName))
    {
        return VOS_ERR;
    }

    sCondition.ucOper = M_CFG_CDB_EQUAL;
    sCondition.udwFieldId = M_HSGW_APN_COMMOM_TBL_APN_FLD_ID;

    VOS_StrCpy((CHAR*)sCondition.aValue, (CHAR*)pucApnName);

    /*  查询CDB 中的APN信息配置表 */
    ulRet = DBApiQuerySingle(M_HSGW_APN_COMMOM_TBL_ID, 1, &sCondition, (CHAR *)&tmpApn);
    if (ulRet == CDB_EC_SUCCESS)
    {
        *pusApnIdx = tmpApn.usApnIndex;
        return VOS_OK;
    }

    return VOS_ERR;
}


/*****************************************************************************
 函 数 名  : AM_ApnApiGetApnIdxByName
 功能描述  : 根据CDB的APN配置内容，获取APN索引和RadiusGroupID
 输入参数  : UCHAR *pucApnInfo
 输出参数  : VOS_UINT16 *pusApnIdx
             VOS_UINT16 *pusServerGroupID
 返 回 值  : APN/Domain索引
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 AM_ApnApiGetRadiusInfo(UCHAR *pucApnNodeAddr, VOS_UINT16 *pusApnIdx, VOS_UINT16 *pusServerGroupID)
{
    S_CFG_DOMAINNODE *pstApn = (S_CFG_DOMAINNODE*)pucApnNodeAddr;

    if ((NULL == pstApn) || (NULL == pusApnIdx) || (NULL == pusServerGroupID))
    {
        return VOS_ERR;
    }

    *pusApnIdx = pstApn->usApnIndex;
    *pusServerGroupID = pstApn->usServerGroupID;
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AM_ApnApiGetAcctInfo
 功能描述  : 根据APN/Domain索引获取计费信息
 输入参数  : VOS_UINT16 usApnIdx
 输出参数  : APN_ACCT_INFO *pstAcctInfo
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetAcctInfo(VOS_UINT16 usApnIdx, APN_ACCT_INFO *pstAcctInfo)
{
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL;
    VOS_UINT32 ulRet = VOS_OK;

    if (NULL == pstAcctInfo)
    {
        return VOS_ERR;
    }

    ulRet = A11_GetDomainByIndex(usApnIdx, &pstDomain);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    pstAcctInfo->pucAPN         = &pstDomain->aucAPN[0];
    pstAcctInfo->ucTransAccess  = pstDomain->ucTransAccess;
    pstAcctInfo->usServerGroupID = pstDomain->usServerGroupID;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AM_ApnApiGetAcctInfo
 功能描述  : 根据APN/Domain索引获取计费类型
 输入参数  : VOS_UINT16 usApnIdx
 输出参数  : APN_CM_TYPE_S *pstApnType
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetCmApnType(VOS_UINT16 usApnIdx, APN_CM_TYPE_S *pstApnType)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AM_ApnApiGetAcctInfo
 功能描述  : 根据APN/Domain索引获取Idle开关
 输入参数  : VOS_UINT16 usApnIdx
 输出参数  : UCHAR *pucIdleSwitch
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetIdleSwitch(VOS_UINT16 usApnIdx, UCHAR *pucIdleSwitch, UCHAR *pucUpdateSwitch)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AM_ApnApiGetApnName
 功能描述  : 根据APN/Domain索引获取Idle开关
 输入参数  : VOS_UINT16 usApnIdx
 输出参数  :
 返 回 值  : APN/DOMAIN名，当不存在时返回NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
UCHAR* AM_ApnApiGetApnName(VOS_UINT16 usApnIdx)
{
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL;
    VOS_UINT32 ulRet = VOS_OK;

    ulRet = A11_GetDomainByIndex(usApnIdx, &pstDomain);
    if (VOS_OK != ulRet)
    {
        return VOS_NULL;
    }

    return &pstDomain->aucAPN[0];
}

/*****************************************************************************
 函 数 名  : AM_ApnApiGetAliasApnName
 功能描述  : 获取别名APN/Domain名字
 输入参数  : VOS_UINT16 usApnIdx
 输出参数  :
 返 回 值  : APN/DOMAIN名，当不存在时返回NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetAliasApnName(VOS_UINT16 usAliasApnIdx, UCHAR *pucAliasApnName)
{
    UCHAR *pucApnName = NULL;

    pucApnName = AM_ApnApiGetApnName(usAliasApnIdx);

    if (NULL != pucApnName)
    {
        VOS_StrNCpy(pucAliasApnName, pucApnName, M_CFG_MAX_APN_STRING_LEN - 1);
        pucAliasApnName[M_CFG_MAX_APN_STRING_LEN - 1] = '\0';
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
 函 数 名  : AM_ApnApiGetMultiServiceMod
 功能描述  : 获取APN配置的MultiServiceMod
 输入参数  : VOS_UINT16 usApnIdx
 输出参数  : pucMultiServiceMod
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月22日
    作    者   : Z66908
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetMultiServiceMod(VOS_UINT16 usApnIdx, UCHAR *pucMultiServiceMod)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AM_ApnApiGetApnNameForHsgw
 功能描述  : hsgw 根据apn index 获取apn name
 输入参数  : VOS_UINT16 usApnIndex
             UCHAR *pucApnName
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月28日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetApnNameForHsgw(VOS_UINT16 usApnIndex, UCHAR *pucApnName)
{
    VOS_UINT32 ulRet = VOS_OK;
    HSGW_APN_INFO_S *pstApn = VOS_NULL;

    if ( NULL == pucApnName )
    {
        return VOS_ERR;
    }

    ulRet = USM_GetApnCfgByApnIndex(usApnIndex, &pstApn);
    if ( VOS_OK != ulRet )
    {
        return ulRet;
    }

    VOS_StrCpy(pucApnName, pstApn->aucApnInfoName);
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AM_ApnApiGetApnSoftParaVaule
 功能描述  : 根据APN的软参索引获取软参值
 输入参数  : APN索引：usAPNIndex, ucSoftParaIndex(1-8)
 输出参数  : 软参值： *pucSoftParaValue
 返 回 值  : VOS_OK－成功 VOS_ERR－失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月6日
    作    者   : xuchao 00249899
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 AM_ApnApiGetApnSoftParaVaule(VOS_UINT16 usAPNIndex , UCHAR ucSoftParaIndex, UCHAR *pucSoftParaValue)
{
    if ((NULL == g_pstApnByIndex) || (NULL == pucSoftParaValue))
    {
        VOS_ASSERT(0);
        return VOS_ERR;
    }

    *pucSoftParaValue = 0;
    return VOS_OK;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
