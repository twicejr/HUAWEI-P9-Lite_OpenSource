/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsProcEpdszid.c
  版 本 号   : 初稿
  作    者   : g00261581
  生成日期   : 2014年12月30日
  最近修改   :
  功能描述   : TAF APS Proc EPDSZID function
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月30日
    作    者   : g00261581
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafApsProcEpdszid.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsSndXcc.h"
#include "TafApsMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define THIS_FILE_ID PS_FILE_ID_TAF_APS_PROC_EPDSZID_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_APS_GetEpdszidCtx
 功能描述  : Get Epdszid Ctx Info
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_APS_CDATA_EPDSZID_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_APS_CDATA_EPDSZID_CTX_STRU* TAF_APS_GetEpdszidCtx(VOS_VOID)
{
    return &(g_stTafApsCtx.stCdataCtx.stEpdszidCtx);
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetEpdszidType
 功能描述  : get Epdszid type
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8 TAF_APS_GetEpdszidType(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.stEpdszidCtx.enEpdszidType;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetEpdszidType
 功能描述  : Set Epdszid type
 输入参数  : TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8      enEpdszidType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SetEpdszidType(
    TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8       enEpdszidType
)
{
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.enEpdszidType = enEpdszidType;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetEpdszidHatTimerLen
 功能描述  : Get Hat Timer Len
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_APS_GetEpdszidHatTimerLen(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucHatTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetEpdszidHatTimerLen
 功能描述  : Set Hat Timer Len
 输入参数  : VOS_UINT8                           ucHatTimerLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SetEpdszidHatTimerLen(
    VOS_UINT8                           ucHatTimerLen
)
{
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucHatTimerLen = ucHatTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetEpdszidHtTimerLen
 功能描述  : Get Ht Timer Len
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_APS_GetEpdszidHtTimerLen(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucHtTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetEpdszidHtTimerLen
 功能描述  : Set Ht Timer Len
 输入参数  : VOS_UINT8                           ucHtTimerLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SetEpdszidHtTimerLen(
    VOS_UINT8                           ucHtTimerLen
)
{
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucHtTimerLen = ucHtTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetCurrPacketZoneListLen
 功能描述  : Get Current Packet zone list len
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_APS_GetCurrPacketZoneListLen(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucEpdszidCurrListLen;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetCurrPacketZoneListLen
 功能描述  : Set Current Packet zone list Len
 输入参数  : VOS_UINT8                           ucZoneListLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SetCurrPacketZoneListLen(
    VOS_UINT8                           ucZoneListLen
)
{
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucEpdszidCurrListLen = ucZoneListLen;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ReduceEpdszidInZoneList
 功能描述  : Current Packet Zone List Len is Less than Max Packe Zone List
             Len, So need to reduce some old epdszid record
 输入参数  : VOS_UINT8                           ucMaxZoneListLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ReduceEpdszidInZoneList(
    VOS_UINT8                           ucMaxZoneListLen
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = ucMaxZoneListLen; ucIndex < TAF_APS_CDMA_EPDSZID_LIST_MAX_LEN;  ucIndex++)
    {
        /* Sid/Nid/Pzid Value is set to Invalid Value */
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucIndex].usSid        = TAF_APS_CDMA_EPDSZID_INVAILD_SID;
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucIndex].usNid        = TAF_APS_CDMA_EPDSZID_INVAILD_NID;
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucIndex].ucPzid       = TAF_APS_CDMA_EPDSZID_INVAILD_PZID;
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucIndex].ulBeginSlice = 0;
    }

    TAF_APS_SetCurrPacketZoneListLen(ucMaxZoneListLen);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetMaxPacketZoneListLen
 功能描述  : Get Max Packet zone list len
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_APS_GetMaxPacketZoneListLen(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucEpdszidMaxListLen;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetMaxPacketZoneListLen
 功能描述  : Set Max Packet zone list Len
 输入参数  : VOS_UINT8                           ucMaxZoneListLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SetMaxPacketZoneListLen(
    VOS_UINT8                           ucMaxZoneListLen
)
{
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucEpdszidMaxListLen = ucMaxZoneListLen;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetHysEnableFlg
 功能描述  : Get Hysteresis enable Flg
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_APS_GetHysEnableFlg(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucEpdszidHysEnableFlg;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetHysEnableFlg
 功能描述  : Set Hysteresis enable Flg
 输入参数  : VOS_UINT8                           ucHysEnableFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SetHysEnableFlg(
    VOS_UINT8                           ucHysEnableFlg
)
{
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucEpdszidHysEnableFlg = ucHysEnableFlg;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetHysActivationInd
 功能描述  : Get HAI(HYSTEERESIS ACTIVATION INDICATOR) value
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_APS_GetHysActivationInd(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucEpdszidHai;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetHysActivationInd
 功能描述  : Set HAI(HYSTEERESIS ACTIVATION INDICATOR) value
 输入参数  : VOS_UINT8                           ucHysActivationInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SetHysActivationInd(
    VOS_UINT8                           ucHysActivationInd
)
{
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.ucEpdszidHai = ucHysActivationInd;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetEpdszidChgReOrigScene
 功能描述  : Get Epdszid Chg ReOrig Scene Enum value
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_APS_CDATA_EPDSZID_CHG_REORIG_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_APS_CDATA_EPDSZID_CHG_REORIG_SCENE_ENUM_UINT8 TAF_APS_GetEpdszidChgReOrigScene(VOS_VOID)
{
    return g_stTafApsCtx.stCdataCtx.stEpdszidCtx.enReOrigScene;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetEpdszidChgReOrigScene
 功能描述  : Set Epdszid ReOrig flg after dormant timer expired
 输入参数  : TAF_APS_CDATA_EPDSZID_CHG_REORIG_TYPE_ENUM_UINT8          enReOrigScene
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SetEpdszidChgReOrigScene(
    TAF_APS_CDATA_EPDSZID_CHG_REORIG_SCENE_ENUM_UINT8       enReOrigScene
)
{
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.enReOrigScene = enReOrigScene;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetCurrEpdszidInfo
 功能描述  : Get Current EPDSZID Info
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_APS_CDATA_EPDSZID_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_APS_CDATA_EPDSZID_STRU* TAF_APS_GetCurrEpdszidInfo(VOS_VOID)
{
    return &g_stTafApsCtx.stCdataCtx.stEpdszidCtx.stCurrEpdszid;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetCurrEpdszidInfo
 功能描述  : Update Current EPDSZID Info
 输入参数  : TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SetCurrEpdszidInfo(
    TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
)
{
    PS_MEM_CPY(&g_stTafApsCtx.stCdataCtx.stEpdszidCtx.stCurrEpdszid,
               pstEpdszid,
               sizeof(TAF_APS_CDATA_EPDSZID_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetHrpdEpdszidInfo
 功能描述  : 获取HRPD Pzid Sid Nid信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_APS_CDATA_HRPD_EPDSZID_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_APS_CDATA_HRPD_EPDSZID_CTX_STRU* TAF_APS_GetHrpdEpdszidInfo(VOS_VOID)
{
    return &g_stTafApsCtx.stCdataCtx.stHrpdEpdszidInfo;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetHrpdEpdszidInfo
 功能描述  : 更新Hrpd Pzid Sid Nid信息
 输入参数  : VOS_UINT16                          usSid
             VOS_UINT16                          usNid
             VOS_UINT8                           ucPzid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SetHrpdEpdszidInfo(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT8                           ucPzid
)
{
    g_stTafApsCtx.stCdataCtx.stHrpdEpdszidInfo.usSid  = usSid;
    g_stTafApsCtx.stCdataCtx.stHrpdEpdszidInfo.usNid  = usNid;
    g_stTafApsCtx.stCdataCtx.stHrpdEpdszidInfo.ucPzid = ucPzid;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetOldestEntryInZoneList
 功能描述  : Get the Oldest Epdszid Entry Info
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_APS_CDATA_EPDSZID_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
TAF_APS_CDATA_EPDSZID_STRU* TAF_APS_GetOldestEntryInZoneList(VOS_VOID)
{
    VOS_UINT8                           ucZoneListLen;

    ucZoneListLen = TAF_APS_GetCurrPacketZoneListLen();

    return &g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucZoneListLen - 1];
}

/*****************************************************************************
 函 数 名  : TAF_APS_CheckEpdszidIsTheSame
 功能描述  : Check if Epdszid Info is the same
 输入参数  : TAF_APS_CDATA_EPDSZID_STRU         *pstDesEpdszid
             TAF_APS_CDATA_EPDSZID_STRU         *pstSrcEpdszid
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_CheckEpdszidIsTheSame(
    TAF_APS_CDATA_EPDSZID_STRU         *pstDesEpdszid,
    TAF_APS_CDATA_EPDSZID_STRU         *pstSrcEpdszid
)
{
    switch (TAF_APS_GetEpdszidType())
    {
        case TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID:
            /* Check if Pzid is the same */
            if (pstDesEpdszid->ucPzid ==pstSrcEpdszid->ucPzid)
            {
                return VOS_TRUE;
            }
            break;

        case TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID_SID:
            /* Check if Pzid And Sid is the same */
            if ((pstDesEpdszid->usSid  == pstSrcEpdszid->usSid)
             && (pstDesEpdszid->ucPzid == pstSrcEpdszid->ucPzid))
            {
                return VOS_TRUE;
            }

            break;

        case TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID_SID_NID:
            /* Check if Pzid and Sid Nid is the same */
            if ((pstDesEpdszid->usSid  == pstSrcEpdszid->usSid)
             && (pstDesEpdszid->usNid  == pstSrcEpdszid->usNid)
             && (pstDesEpdszid->ucPzid == pstSrcEpdszid->ucPzid))
            {
                /* Find the EPDSZID in the packet zone list */
                return VOS_TRUE;
            }
            break;

        default:
            break;
    }

    /* Can't Find In The Current Packet Zone List ,Return VOS_FALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_IsEpdszidExistInZoneList
 功能描述  : 判断Epdszid是否在Packet Zone List中存在
 输入参数  : TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_IsEpdszidExistInZoneList(
    TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < TAF_APS_GetCurrPacketZoneListLen(); ucIndex++)
    {
        /* Check if Pzid is the same */
        if (VOS_TRUE == TAF_APS_CheckEpdszidIsTheSame(&g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucIndex], pstEpdszid))
        {
            /* Find the EPDSZID in the packet zone list */
            return VOS_TRUE;
        }
    }

    /* Can't Find In The Current Packet Zone List ,Return VOS_FALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetEpdszidIndexInZoneList
 功能描述  : If Epdszid existed in the Packet Zone List,return the seq num,Else return -1
 输入参数  : TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_APS_GetEpdszidIndexInZoneList(
    TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < TAF_APS_GetCurrPacketZoneListLen(); ucIndex++)
    {
        /* Check if Pzid is the same */
        if (VOS_TRUE == TAF_APS_CheckEpdszidIsTheSame(&g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucIndex], pstEpdszid))
        {
            /* Find the EPDSZID in the packet zone list */
            return ucIndex;
        }
    }

    /* Can't Find In The Current Packet Zone List ,Return INVAILD VAlUE */
    return TAF_APS_CDMA_EPDSZID_INVAILD_SEQ_NUM;
}

/*****************************************************************************
 函 数 名  : TAF_APS_AddEpdszidToZoneList
 功能描述  : Add One EPDSZID to Packet Zone List
 输入参数  : TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_AddEpdszidToZoneList
(
    TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
)
{
    VOS_UINT8                           ucCurrZoneListLen;

    /* If Already existed in the packet zone list ,return */
    if (VOS_TRUE == TAF_APS_IsEpdszidExistInZoneList(pstEpdszid))
    {
        return;
    }

    /* If CurrZoneListLen is Equal to Max Packet zone List ,Need to Delete Last(Oldest) Epdszid in the list */
    if (TAF_APS_GetCurrPacketZoneListLen() == TAF_APS_GetMaxPacketZoneListLen())
    {
        TAF_APS_DeleteOldestEntryInZoneList();

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_EPZID_HT, TAF_APS_INVALID_PDPID))
        {
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_EPZID_HT, TAF_APS_INVALID_PDPID);

            /* start next Epdszid's HT */
            TAF_APS_EpdszidProcHt();
        }
    }

    /* ucCurrZoneListLen <= 14 */
    ucCurrZoneListLen = TAF_APS_GetCurrPacketZoneListLen();

    while (ucCurrZoneListLen > 0)
    {
        PS_MEM_CPY(&g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucCurrZoneListLen],
                   &g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucCurrZoneListLen - 1],
                    sizeof(TAF_APS_CDATA_EPDSZID_STRU));

        ucCurrZoneListLen--;
    }

    /* Add new */
    PS_MEM_CPY(&(g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[0]),
               pstEpdszid,
               sizeof(TAF_APS_CDATA_EPDSZID_STRU));

    ucCurrZoneListLen = TAF_APS_GetCurrPacketZoneListLen();

    TAF_APS_SetCurrPacketZoneListLen(ucCurrZoneListLen + 1);

    if (TAF_APS_GetCurrPacketZoneListLen() >= 2)
    {
        /* Record EPDSZID Begin Slice Timer */
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[1].ulBeginSlice = VOS_GetSlice();
    }

    /* 可维可测 */
    TAF_APS_TraceEpdszidInfo();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_DeleteOldestEntryInZoneList
 功能描述  : Delete The Last Epdszid entry in the packet zone list(The Last is the Oldest)
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_DeleteOldestEntryInZoneList(VOS_VOID)
{
    VOS_UINT8                           ucZoneListLen;

    ucZoneListLen = TAF_APS_GetCurrPacketZoneListLen();

    if (ucZoneListLen > 0)
    {
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucZoneListLen - 1].usSid        = TAF_APS_CDMA_EPDSZID_INVAILD_SID;
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucZoneListLen - 1].usNid        = TAF_APS_CDMA_EPDSZID_INVAILD_NID;
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucZoneListLen - 1].ucPzid       = TAF_APS_CDMA_EPDSZID_INVAILD_PZID;
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucZoneListLen - 1].ulBeginSlice = 0x0;
    }

    TAF_APS_SetCurrPacketZoneListLen(ucZoneListLen - 1);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_DeleteOneEntryInZoneList
 功能描述  : Delete One Epdszid Entry In Zone List
 输入参数  : VOS_UINT8                           ucSeqNum
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_DeleteOneEntryInZoneList(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucCurrZoneListLen;

    ucCurrZoneListLen = TAF_APS_GetCurrPacketZoneListLen();

    if (ucIndex >= ucCurrZoneListLen)
    {
        return;
    }

    for (i = ucIndex; i < ucCurrZoneListLen - 1; i++)
    {
        PS_MEM_CPY(&g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[i],
                   &g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[i + 1],
                    sizeof(TAF_APS_CDATA_EPDSZID_STRU));
    }

    ucCurrZoneListLen--;

    TAF_APS_SetCurrPacketZoneListLen(ucCurrZoneListLen);

    /* 可维可测 */
    TAF_APS_TraceEpdszidInfo();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_MoveEntryToLastPositionInZoneList
 功能描述  : Move One entry to the Last Position In Zone List
 输入参数  : VOS_UINT8                           ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月12日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_MoveEntryToLastPositionInZoneList(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           i;
    TAF_APS_CDATA_EPDSZID_STRU          stTempEpdszidInfo;

    PS_MEM_SET(&stTempEpdszidInfo, 0x0, sizeof(stTempEpdszidInfo));

    PS_MEM_CPY(&stTempEpdszidInfo,
               &g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucIndex],
               sizeof(TAF_APS_CDATA_EPDSZID_STRU));

    i = ucIndex;

    while (i < TAF_APS_GetCurrPacketZoneListLen() - 1)
    {
        PS_MEM_CPY(&g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[i],
                   &g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[i + 1],
                    sizeof(TAF_APS_CDATA_EPDSZID_STRU));

        i++;
    }

    PS_MEM_CPY(&g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[i],
               &stTempEpdszidInfo,
               sizeof(TAF_APS_CDATA_EPDSZID_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_InitPacketZoneList
 功能描述  : Init Packet Zone List
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_InitPacketZoneList(VOS_VOID)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < TAF_APS_CDMA_EPDSZID_LIST_MAX_LEN; ucIndex++)
    {
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucIndex].usSid        = TAF_APS_CDMA_EPDSZID_INVAILD_SID;
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucIndex].usNid        = TAF_APS_CDMA_EPDSZID_INVAILD_NID;
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucIndex].ucPzid       = TAF_APS_CDMA_EPDSZID_INVAILD_PZID;
        g_stTafApsCtx.stCdataCtx.stEpdszidCtx.astEpdszidList[ucIndex].ulBeginSlice = 0;
    }

    TAF_APS_SetCurrPacketZoneListLen(0);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_InitCurrEpdszidInfo
 功能描述  : Init Current Epdszid Info
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月7日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_InitCurrEpdszidInfo(VOS_VOID)
{
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.stCurrEpdszid.usSid        = TAF_APS_CDMA_EPDSZID_INVAILD_SID;
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.stCurrEpdszid.usNid        = TAF_APS_CDMA_EPDSZID_INVAILD_NID;
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.stCurrEpdszid.ucPzid       = TAF_APS_CDMA_EPDSZID_INVAILD_PZID;
    g_stTafApsCtx.stCdataCtx.stEpdszidCtx.stCurrEpdszid.ulBeginSlice = 0x0;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ReadEpdszidFeatureCfgFromNv
 功能描述  : Get Epdszid Feature Cfg From Nv
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ReadEpdszidFeatureCfgFromNv(VOS_VOID)
{
    CNAS_NVIM_1X_EPDSZID_FEATURE_CFG_STRU  stEpdszidFeatureCfg;

    PS_MEM_SET(&stEpdszidFeatureCfg, 0x0, sizeof(CNAS_NVIM_1X_EPDSZID_FEATURE_CFG_STRU));

    if (NV_OK == NV_Read(en_NV_Item_1X_EPDSZID_FEATURE_CFG,
                         &stEpdszidFeatureCfg, sizeof(CNAS_NVIM_1X_EPDSZID_FEATURE_CFG_STRU)))
    {
        TAF_APS_LogReadNVInfo(en_NV_Item_1X_EPDSZID_FEATURE_CFG,
                              sizeof(CNAS_NVIM_1X_EPDSZID_FEATURE_CFG_STRU),
                              WUEPS_PID_TAF,
                              (VOS_UINT8 *)&stEpdszidFeatureCfg);

        TAF_APS_SetEpdszidType(stEpdszidFeatureCfg.ucEpdszidType);

        TAF_APS_SetEpdszidHatTimerLen(stEpdszidFeatureCfg.ucHatLen);

        TAF_APS_SetEpdszidHtTimerLen(stEpdszidFeatureCfg.ucHtLen);
    }
    else
    {
        /* If Read Nv fail, Set Default value */
        TAF_APS_SetEpdszidType(TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID);

        TAF_APS_SetEpdszidHatTimerLen(TAF_APS_CDATA_EPDSZID_HAT_DEFAULT_LEN);

        TAF_APS_SetEpdszidHtTimerLen(TAF_APS_CDATA_EPDSZID_HT_DEFAULT_LEN);
    }
}

/*****************************************************************************
 函 数 名  : TAF_APS_InitEpdszidCtx
 功能描述  : Init EPDSZID Ctx Info
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_InitEpdszidCtx(VOS_VOID)
{
    TAF_APS_CDATA_EPDSZID_CTX_STRU               *pstEpdszidCtx;

    pstEpdszidCtx = TAF_APS_GetEpdszidCtx();

    PS_MEM_SET(pstEpdszidCtx, 0x0, sizeof(TAF_APS_CDATA_EPDSZID_CTX_STRU));

    TAF_APS_SetHysEnableFlg(VOS_TRUE);

    TAF_APS_SetHysActivationInd(VOS_FALSE);

    TAF_APS_ReadEpdszidFeatureCfgFromNv();

    TAF_APS_InitPacketZoneList();

    TAF_APS_InitCurrEpdszidInfo();

    TAF_APS_SetMaxPacketZoneListLen(TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ReleaseEpdszidResource
 功能描述  : Relese Epdszid Resource
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月7日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ReleaseEpdszidResource(VOS_VOID)
{
    TAF_APS_InitEpdszidCtx();

    TAF_APS_EpdszidStopHat();

    TAF_APS_EpdszidStopHt();
}

/*****************************************************************************
 函 数 名  : TAF_APS_EpdszidSocmDisableReconn
 功能描述  : SOCM Msg Disable Epdszid Reconn Feature
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_EpdszidSocmDisableReconn(VOS_VOID)
{
    /* Max Packet Zone List Len si set to 1 */
    TAF_APS_SetMaxPacketZoneListLen(TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN);

    /* Init Zone List */
    TAF_APS_InitPacketZoneList();

    /* Init Curr Zone Info */
    TAF_APS_InitCurrEpdszidInfo();

    /* HAI is set to FALSE */
    TAF_APS_SetHysActivationInd(VOS_FALSE);

    /* Stop Both Hat and Ht */
    TAF_APS_EpdszidStopHat();
    TAF_APS_EpdszidStopHt();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_EpdszidSocmEnableReconn
 功能描述  : SOCM Msg Enable Epdszid Reconn Feature, Also Config Hysteresis Feature
 输入参数  : VOS_UINT8                           ucMaxZoneListLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_EpdszidSocmEnableReconn(
    VOS_UINT8                           ucMaxZoneListLen
)
{
    /* 可维可测 */
    TAF_APS_TraceEpdszidInfo();

    /* Enable Packet Zone Based Reconnect Feature ,Update Max Packet Zone List Len*/
    TAF_APS_SetMaxPacketZoneListLen(ucMaxZoneListLen);

    if (TAF_APS_GetCurrPacketZoneListLen() > ucMaxZoneListLen)
    {
        /* If Max zone List Len is Less than current Len, Need delete some Epdszid entry in the list */
        TAF_APS_ReduceEpdszidInZoneList(ucMaxZoneListLen);
    }

    /* If Max Packet Zone List is set to 1 , Enable Hysteresis Feature, else Disable Hysteresis Feature */
    if (TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN == ucMaxZoneListLen)
    {
        TAF_APS_SetHysEnableFlg(VOS_TRUE);

        /* Stop HT */
        TAF_APS_EpdszidStopHt();
    }
    else
    {
        TAF_APS_SetHysEnableFlg(VOS_FALSE);

        TAF_APS_SetHysActivationInd(VOS_FALSE);

        /* Stop both HAT and HT*/
        TAF_APS_EpdszidStopHt();
        TAF_APS_EpdszidStopHat();
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_EpdszidSocmClearPacketZoneList
 功能描述  : SOCM Msg Clear Packet Zone List
 输入参数  : VOS_UINT8                           ucMaxZoneListLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_EpdszidSocmClearPacketZoneList(
    VOS_UINT8                           ucMaxZoneListLen
)
{
    /* Update Max Packet Zone List Len */
    TAF_APS_SetMaxPacketZoneListLen(ucMaxZoneListLen);

    /* Clear Packet Zone List */
    TAF_APS_InitPacketZoneList();

    TAF_APS_InitCurrEpdszidInfo();

    /* stop ht */
    TAF_APS_EpdszidStopHt();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_EpdszidScomTransferPzid
 功能描述  : SOCM Msg Ntf APS to Transfer Pzid info to BS
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_EpdszidScomTransferPzid(
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
)
{
    /* Transfer pzid info to XCC */
    TAF_APS_SndXccPzidInfoNtf(pstSoCtrlMsgInd);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_EpdszidStopHat
 功能描述  : Stop Hysteresis Activation Timer
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_EpdszidStopHat(VOS_VOID)
{
    /* If HAT is running ,stop it */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_EPZID_HAT, TAF_APS_INVALID_PDPID))
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_EPZID_HAT, TAF_APS_INVALID_PDPID);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_EpdszidProcHt
 功能描述  : Start Hysteresis Timer
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_EpdszidProcHt(VOS_VOID)
{
    TAF_APS_CDATA_EPDSZID_STRU         *pstLastEpdszid;
    VOS_UINT32                          ulEpdszidExistSlice;
    VOS_UINT32                          ulEpdszidExistTimer;
    VOS_UINT32                          ulHtLen;
    VOS_UINT32                          ulCurSlice;

    if (TAF_APS_GetCurrPacketZoneListLen() <= TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN)
    {
        return;
    }

    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_EPZID_HT, TAF_APS_INVALID_PDPID))
    {
        return;
    }

    /* Get Last Epdszid Entry in the Zone List */
    pstLastEpdszid = TAF_APS_GetOldestEntryInZoneList();
    ulCurSlice     = VOS_GetSlice();

    if (ulCurSlice > pstLastEpdszid->ulBeginSlice)
    {
        ulEpdszidExistSlice = ulCurSlice - pstLastEpdszid->ulBeginSlice;
    }
    else
    {
        /* 考虑反转问题 */
        ulEpdszidExistSlice = TAF_APS_MAX_SLICE_VALUE - pstLastEpdszid->ulBeginSlice + ulCurSlice + 1;
    }

    ulEpdszidExistTimer = ulEpdszidExistSlice * 1000 / VOS_GetSliceUnit();

    if (ulEpdszidExistTimer < TAF_APS_GetEpdszidHtTimerLen() * 1000)
    {
        ulHtLen = TAF_APS_GetEpdszidHtTimerLen() * 1000 - ulEpdszidExistTimer;

        /* Start HT */
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_EPZID_HT, ulHtLen, TAF_APS_INVALID_PDPID);
    }
    else
    {
        /* This Epdszid Entry is Expired Already */
        TAF_APS_SndInterHtExpiredInd();
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_EpdszidStopHt
 功能描述  : Stop Hysteresis Timer
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_EpdszidStopHt(VOS_VOID)
{
    /* If HT is running ,stop it */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_EPZID_HT, TAF_APS_INVALID_PDPID))
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_EPZID_HT, TAF_APS_INVALID_PDPID);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcEpdszidEnterDormant
 功能描述  : When enter Dormant State, start HAT/HT
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcEpdszidEnterDormant(VOS_VOID)
{
    TAF_APS_CDATA_EPDSZID_STRU         *pstCurrEpdszid;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCurrZoneListLen;

    /* If HAI Value is TRUE And Hysteresis Feature is Enable, Start HAT */
    if (VOS_TRUE == TAF_APS_GetHysEnableFlg())
    {
        if (VOS_TRUE == TAF_APS_GetHysActivationInd())
        {
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_EPZID_HAT, TAF_APS_GetEpdszidHatTimerLen() * 1000, TAF_APS_INVALID_PDPID);

            TAF_APS_SetHysActivationInd(VOS_FALSE);

            ucCurrZoneListLen = TAF_APS_GetCurrPacketZoneListLen();

            if (ucCurrZoneListLen > TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN)
            {
                /* Get Curr Epdszid Entry in the Zone List */
                pstCurrEpdszid = TAF_APS_GetCurrEpdszidInfo();

                ucIndex        = TAF_APS_GetEpdszidIndexInZoneList(pstCurrEpdszid);

                /* If Curr Epdszid in the Zone list, And not in entry 0 ,Delete the Entry Directly */
                if ((ucIndex > 0) && (ucIndex < ucCurrZoneListLen - 1))
                {
                    TAF_APS_DeleteOneEntryInZoneList(ucIndex);
                }

                /* If Curr Epdszid is the End Entry, Delet the entry ,And stop Ht */
                else if (ucIndex == ucCurrZoneListLen - 1)
                {
                    TAF_APS_DeleteOldestEntryInZoneList();
                    TAF_APS_EpdszidStopHt();
                }
                else
                {
                    /* Curr Epdszid Not in the list ,Do nothing */
                }
            }
        }
    }

    TAF_APS_EpdszidProcHt();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcEpdszidAfterRcvXccOrigDataCallCnf
 功能描述  : After rcv xcc orig data cnf, Add epdszid into Packet
             zone List
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcEpdszidAfterRcvXccOrigDataCallCnf(VOS_VOID)
{
    TAF_APS_CDATA_EPDSZID_STRU         *pstCurrEpdszid;

    pstCurrEpdszid = TAF_APS_GetCurrEpdszidInfo();

    /* Add current Epdszid into Packet Zone List */
    TAF_APS_AddEpdszidToZoneList(pstCurrEpdszid);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcEpdszidHaiChangeInd
 功能描述  : Data Exchange occurs, Hai change from 0 to 1, Stop HAT,HT, updata Max Packet zone List
             len to 1
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcEpdszidHaiChangeInd(VOS_VOID)
{
    /* If HAT is running ,stop it */
    TAF_APS_EpdszidStopHat();

    /* If HT is running ,stop it */
    TAF_APS_EpdszidStopHt();

    /* Max Packet Zone List Len is set to 1 */
    TAF_APS_SetMaxPacketZoneListLen(TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN);

    if (TAF_APS_GetCurrPacketZoneListLen() > TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN)
    {
        /* 可维可测 */
        TAF_APS_TraceEpdszidInfo();

        TAF_APS_ReduceEpdszidInZoneList(TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcEpdszidHatExpired
 功能描述  : When HAT expired , Update Max Packet Zone List Len
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcEpdszidHatExpired(VOS_VOID)
{
    /* Max Packet Zone List Len is set to 4 */
    if (TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN == TAF_APS_GetMaxPacketZoneListLen())
    {
        TAF_APS_SetMaxPacketZoneListLen(TAF_APS_CDMA_EPDSZID_DEFAULT_MAX_LEN);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcEpdszidHtExpired
 功能描述  : When HT expried, Update Packet Zone List, And Decide whether
             begin Re-Conect or not
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcEpdszidHtExpired(VOS_VOID)
{
    TAF_APS_CDATA_EPDSZID_STRU         *pstExpiredEntry;
    TAF_APS_CDATA_EPDSZID_STRU         *pstCurrEntry;

    /* Get the epdszid whose HT expired */
    pstExpiredEntry = TAF_APS_GetOldestEntryInZoneList();

    pstCurrEntry  = TAF_APS_GetCurrEpdszidInfo();

    /* If the Deleted EPDSZID is the same as the Current EPDSZID, Snd Internal Msg to Re_Connect */
    if (TAF_APS_CheckEpdszidIsTheSame(pstCurrEntry, pstExpiredEntry))
    {
        TAF_APS_SndInterEpdszidReOrigReq();
    }

    /* When HT expired ,Delete the Oldest EPDSZID in the packet Zone List */
    TAF_APS_DeleteOldestEntryInZoneList();

    /* Proc HT */
    TAF_APS_EpdszidProcHt();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcMmaEpdszidInfo
 功能描述  : Proc Epdszid Info sent from MMA
 输入参数  : VOS_UINT16                          usSid
             VOS_UINT16                          usNid
             VOS_UINT8                           ucPzid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : g00261581
    修改内容   : 新生成函数

  2.日    期   : 2015年4月24日
    作    者   : Y00213812
    修改内容   : SID改变后需要停止DORMANT定时器
*****************************************************************************/
VOS_VOID TAF_APS_ProcMmaEpdszidInfo(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT8                           ucPzid,
    VOS_UINT8                           ucPdpId
)
{
    TAF_APS_CDATA_EPDSZID_STRU          stCdataEpdszid;
    TAF_APS_CDATA_EPDSZID_STRU         *pstCurrEpdszid;
    VOS_UINT32                          ulReOrigFlag;

    ulReOrigFlag = VOS_FALSE;

    /* Get curr epdszid */
    pstCurrEpdszid = TAF_APS_GetCurrEpdszidInfo();

    PS_MEM_SET(&stCdataEpdszid, 0, sizeof(TAF_APS_CDATA_EPDSZID_STRU));
    stCdataEpdszid.usSid  = usSid;
    stCdataEpdszid.usNid  = usNid;
    stCdataEpdszid.ucPzid = ucPzid;

    /* SID改变后需要停止DORMANT定时器 */
    if (usSid != pstCurrEpdszid->usSid)
    {
        TAF_APS_SetUserCfgDormTiVal(0);

        TAF_APS_SetSocmDormantTiLen(0);

        /* 停止Dormant 定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);
    }

    if (0 == ucPzid)
    {
        TAF_APS_SetHysActivationInd(VOS_FALSE);

        /* Stop both HAT and HT*/
        TAF_APS_EpdszidStopHt();
        TAF_APS_EpdszidStopHat();

        /* Clear Packet Zone List */
        TAF_APS_InitPacketZoneList();

        /* Update Pzid Info */
        TAF_APS_SetCurrEpdszidInfo(&stCdataEpdszid);

        return;
    }

    /* 判断SID/NID/PZID的支持项 */
    switch (TAF_APS_GetEpdszidType())
    {
        case TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID:
            if ((usSid != pstCurrEpdszid->usSid)
             || (usNid != pstCurrEpdszid->usNid))
            {
                ulReOrigFlag = VOS_TRUE;
            }
            break;

        case TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID_SID:
            if (usNid != pstCurrEpdszid->usNid)
            {
                ulReOrigFlag = VOS_TRUE;
            }
            break;

        case TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID_SID_NID:
            break;

        default:
            break;
    }

    /* Update Pzid Info */
    TAF_APS_SetCurrEpdszidInfo(&stCdataEpdszid);

    /* Epdszid是1X的特性，之前数据业务在1X上才会触发重建 */
    /* If New epdsizd not in the list or ulReOrigFlag is TRUE, Start Re-Orig */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        if ((VOS_FALSE == TAF_APS_IsEpdszidExistInZoneList(&stCdataEpdszid))
        ||  (VOS_TRUE  == ulReOrigFlag))
        {
            TAF_APS_SndInterEpdszidReOrigReq();
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcXregEpdszidRegBeginInd
 功能描述  : Proc Xreg Reg Begin Ind msg
 输入参数  : VOS_UINT16                          usSid
             VOS_UINT16                          usNid
             VOS_UINT8                           ucPzid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcXregEpdszidRegBeginInd(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT8                           ucPzid
)
{
    TAF_APS_CDATA_EPDSZID_STRU          stCdataEpdszid;
    VOS_UINT8                           ucIndex;

    /* 可维可测 */
    TAF_APS_TraceEpdszidInfo();

    /* If sid/nid/pzid is 0, return */
    if ((0 == usSid) || (0 == usNid) || (0 == ucPzid))
    {
        return;
    }

    /* If Hysteresis is Disabled, Don't need Reconnect */
    if (VOS_FALSE == TAF_APS_GetHysEnableFlg())
    {
        return;
    }

    PS_MEM_SET(&stCdataEpdszid, 0, sizeof(TAF_APS_CDATA_EPDSZID_STRU));
    stCdataEpdszid.usSid  = usSid;
    stCdataEpdszid.usNid  = usNid;
    stCdataEpdszid.ucPzid = ucPzid;

    /* Current EPDSZID don't exists in the packet zone list */
    if (VOS_FALSE == TAF_APS_IsEpdszidExistInZoneList(&stCdataEpdszid))
    {
        return;
    }

    ucIndex = TAF_APS_GetEpdszidIndexInZoneList(&stCdataEpdszid);

    /* Current EPDSZID is in the first entry in the packet zone list ,return */
    if ((0 == ucIndex) || (TAF_APS_CDMA_EPDSZID_INVAILD_SEQ_NUM == ucIndex))
    {
        return;
    }

    /* Move the entry to last Postion in zone list */
    TAF_APS_MoveEntryToLastPositionInZoneList(ucIndex);

    /* Fake Ht expired msg */
    TAF_APS_SndInterHtExpiredInd();

    /* If Ht running ,stop */
    TAF_APS_EpdszidStopHt();

    /* Updata Current Epdszid Info */
    TAF_APS_SetCurrEpdszidInfo(&stCdataEpdszid);

    /* 可维可测，此处的勾包在测试稳定后删除 */
    TAF_APS_TraceEpdszidInfo();

    return;
}


#endif


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
