/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasDynLoadApi.c
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2015年8月11日
  最近修改   :
  功能描述   : NasDynLoadApi.c文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月11日
    作    者   : w00242748
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasDynLoadApi.h"
#include "mdrv.h"
#include "NasDynLoad.h"
#include "NasMntn.h"
#include "NasDynLoadMntn.h"
#include "NVIM_Interface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_DYNLOAD_API_C

NAS_DYNLOAD_CB_RAT_INFO_STRU            g_astNasDynloadCbRatInfo[VOS_RATMODE_BUTT];
VOS_RATMODE_ENUM_UINT32                 g_enCurRatModeInCached[NAS_DYNLOAD_LOAD_RATCOMB_TYPE_BUTT] = {VOS_RATMODE_BUTT};
NAS_DYNLOAD_CTRL_STRU                   g_stNasDynloadCtrl;
WAS_QueryCSNR                           g_pfTafQueryCsnrCb = VOS_NULL_PTR;


/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/


/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*****************************************************************************
  6 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : TAF_RegQueryCSNR
 功能描述  : 加载回调函数WAS_MNTN_QUERYCSNR的注册函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_RegQueryCsnrCallBack(
    WAS_QueryCSNR                      pfQueryCsnr
)
{
    g_pfTafQueryCsnrCb = pfQueryCsnr;
}

/*****************************************************************************
 函 数 名  : TAF_GetTafQueryCsnrAddr
 功能描述  : 加载回调函数WAS_MNTN_QUERYCSNR的注册函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : WAS_QueryCSNR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
WAS_QueryCSNR TAF_GetWasQueryCsnrAddr(VOS_VOID)
{
    return g_pfTafQueryCsnrCb;
}


#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_ReadDynloadExceptionCtrlNvim
 功能描述  : 从NVIM中获取动态加载次数控制信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_DYNLOAD_ReadDynloadExceptionCtrlNvim(VOS_VOID)
{
    NAS_NVIM_DYNLOAD_EXCEPTION_CTRL_STRU                    stDynloadExceptionCtrl;
    VOS_UINT32                                              ulLength;

    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Dynload_Exception_CTRL, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_DYNLOAD_EXCEPTION_CTRL_STRU))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_ReadDynloadExceptionCtrlNvim(): en_NV_Item_Dynload_Exception_CTRL length Error");

        NAS_DYNLOAD_SetTWMaxAttemptCount(0);

        return;
    }

    PS_MEM_SET(&stDynloadExceptionCtrl, 0x00, sizeof(stDynloadExceptionCtrl));

    if (NV_OK != NV_Read(en_NV_Item_Dynload_Exception_CTRL,
                        (VOS_VOID *)&stDynloadExceptionCtrl,
                        ulLength))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                     "NAS_DYNLOAD_ReadDynloadExceptionCtrlNvim():en_NV_Item_Dynload_Exception_CTRL Error");

        NAS_DYNLOAD_SetTWMaxAttemptCount(0);

        return;
    }

    if (stDynloadExceptionCtrl.ucTWMaxAttemptCount > NAS_DYNLOAD_MAX_ATTEMPT_COUNT)
    {
        NAS_DYNLOAD_SetTWMaxAttemptCount(NAS_DYNLOAD_MAX_ATTEMPT_COUNT);
    }
    else
    {
        NAS_DYNLOAD_SetTWMaxAttemptCount(stDynloadExceptionCtrl.ucTWMaxAttemptCount);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_ReadDynloadCtrlNvim
 功能描述  : 从NVIM中获取动态加载控制信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_DYNLOAD_ReadDynloadCtrlNvim(VOS_VOID)
{
    NAS_NVIM_DYNLOAD_CTRL_STRU          stDynloadCtrl;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Dynload_CTRL, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_DYNLOAD_CTRL_STRU))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_ReadDynloadCtrlNvim(): en_NV_Item_Dynload_CTRL length Error");

        if (MODEM_ID_0 == VOS_GetModemIDFromPid(UEPS_PID_MSCC))
        {
            NAS_DYNLOAD_SetEnableDynloadTWFlg(VOS_TRUE);
        }
        else
        {
            NAS_DYNLOAD_SetEnableDynloadTWFlg(VOS_FALSE);
        }

        return;
    }

    PS_MEM_SET(&stDynloadCtrl, 0x00, sizeof(stDynloadCtrl));

    if (NV_OK != NV_Read(en_NV_Item_Dynload_CTRL,
                        (VOS_VOID *)&stDynloadCtrl,
                        ulLength))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                     "NAS_DYNLOAD_ReadDynloadCtrlNvim():en_NV_Item_Dynload_CTRL Error");

        if (MODEM_ID_0 == VOS_GetModemIDFromPid(UEPS_PID_MSCC))
        {
            NAS_DYNLOAD_SetEnableDynloadTWFlg(VOS_TRUE);
        }
        else
        {
            NAS_DYNLOAD_SetEnableDynloadTWFlg(VOS_FALSE);
        }

        return;
    }

    NAS_DYNLOAD_SetEnableDynloadTWFlg(stDynloadCtrl.ucEnableDynloadTW);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_ConvertVosRatTypeToDrvType
 功能描述  : RAT TYPE类型转换
 输入参数  : VOS_RATMODE_ENUM_UINT32    enVosRatType
 输出参数  : 无
 返 回 值  : NAS_DYNLOAD_RAT_TYPE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
DRV_RAT_MODE_ENUM NAS_DYNLOAD_ConvertVosRatTypeToDrvType(
    VOS_RATMODE_ENUM_UINT32             enVosRatType
)
{
    DRV_RAT_MODE_ENUM                   enRatType;

    switch (enVosRatType)
    {
        case VOS_RATMODE_WCDMA :
            enRatType = DRV_RAT_MODE_UMTS_FDD;
            break;
        case VOS_RATMODE_TDS :
            enRatType = DRV_RAT_MODE_UMTS_TDD;
            break;
        default:
            NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_ConvertVosRatTypeToDrvType enRatType InValid!\r\n");
            enRatType = DRV_RAT_MODE_BUTT;
            break;
    }

    return enRatType;
}


/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_SaveCbRatInfo
 功能描述  : 保存特定模块的加载回调函数
 输入参数  : NAS_DYNLOAD_RAT_TYPE_ENUM_UINT32 enRatMode
             VOS_UINT32 ulPID
             NAS_DYNLOAD_INIT_CB pfInit
             NAS_DYNLOAD_UNLOAD_CB pfUnload
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_SaveCbRatInfo(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    VOS_UINT32                          ulPID,
    NAS_DYNLOAD_INIT_CB                 pfInit,
    NAS_DYNLOAD_UNLOAD_CB               pfUnload
)
{
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstCbRatInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstCbRatInfo = NAS_DYNLOAD_GetSpecCbRatInfo(enRatMode);

    if (VOS_NULL_PTR == pstCbRatInfo)
    {
        return VOS_FALSE;
    }

    /* 获取当前PID在相应接入技术的模块中得索引 */
    for (i = 0; i < pstCbRatInfo->ulNum; i++)
    {
        if (ulPID == pstCbRatInfo->astModule[i].ulPid)
        {
            break;
        }
    }

    /* 如果未找到PID的索引，则需新增一条记录 */
    if (i == pstCbRatInfo->ulNum)
    {
        if (pstCbRatInfo->ulNum == NAS_DYNLOAD_CB_MODULE_NUM)
        {
            NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_SaveCbRatInfo module num is max!\r\n");
            return VOS_FALSE;
        }

        pstCbRatInfo->astModule[i].ulPid      = ulPID;
        pstCbRatInfo->astModule[i].pfInitCb   = pfInit;
        pstCbRatInfo->astModule[i].pfUnloadCb = pfUnload;
        pstCbRatInfo->ulNum++;
    }
    else
    {
        pstCbRatInfo->astModule[i].pfInitCb   = pfInit;
        pstCbRatInfo->astModule[i].pfUnloadCb = pfUnload;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_ClearCbRatInfo
 功能描述  : 清除特定模块的加载回调函数
 输入参数  : VOS_RATMODE_ENUM_UINT32 enRatMode
             VOS_UINT32 ulPID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_ClearCbRatInfo(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    VOS_UINT32                          ulPID
)
{
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstCbRatInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstCbRatInfo = NAS_DYNLOAD_GetSpecCbRatInfo(enRatMode);

    if (VOS_NULL_PTR == pstCbRatInfo)
    {
        return VOS_FALSE;
    }

    /* 获取当前PID在相应接入技术的模块中得索引 */
    for (i = 0; i < pstCbRatInfo->ulNum; i++)
    {
        if (ulPID == pstCbRatInfo->astModule[i].ulPid)
        {
            break;
        }
    }

    if (i < pstCbRatInfo->ulNum)
    {
        /* 删除一条记录 */
        PS_MEM_MOVE(&(pstCbRatInfo->astModule[i]),
                    &(pstCbRatInfo->astModule[i+1]),
                    (pstCbRatInfo->ulNum-i-1)*sizeof(NAS_DYNLOAD_CB_MODULE_INFO_STRU));

        pstCbRatInfo->ulNum--;

        PS_MEM_SET(&pstCbRatInfo->astModule[pstCbRatInfo->ulNum], 0x00, sizeof(NAS_DYNLOAD_CB_MODULE_INFO_STRU));
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_RegLoadCallBack
 功能描述  : 加载回调函数的注册函数
 输入参数  : VOS_RATMODE_ENUM_UINT32 enRatMode
             VOS_UINT32 ulPID
             NAS_DYNLOAD_INIT_CB pfInit
             NAS_DYNLOAD_UNLOAD_CB pfUnload
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_RegLoadCallBack(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    VOS_UINT32                          ulPID,
    NAS_DYNLOAD_INIT_CB                 pfInit,
    NAS_DYNLOAD_UNLOAD_CB               pfUnload
)
{
    NAS_TRACE_HIGH("NAS_DYNLOAD_RegLoadCallBack enRatMode=%d, ulPid=%d, pfInit=%d, pfUnload=%d\r\n",
                    enRatMode, ulPID, pfInit, pfUnload);

    NAS_DYNLOAD_LogRegisterInfo(enRatMode, ulPID, (VOS_UINT32)pfInit, (VOS_UINT32)pfUnload);

    (VOS_VOID)NAS_DYNLOAD_SaveCbRatInfo(enRatMode, ulPID, pfInit, pfUnload);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_DeRegLoadCallBack
 功能描述  : 去注册回调函数
 输入参数  : VOS_RATMODE_ENUM_UINT32             enRatMode
             VOS_UINT32                          ulPID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月1日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_DeRegLoadCallBack(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    VOS_UINT32                          ulPID
)
{
    NAS_TRACE_HIGH("NAS_DYNLOAD_DeRegLoadCallBack enRatMode=%d, ulPid=%d\r\n", enRatMode, ulPID);

    NAS_DYNLOAD_LogDeregisterInfo(enRatMode, ulPID);

    (VOS_VOID)NAS_DYNLOAD_ClearCbRatInfo(enRatMode, ulPID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_UnloadAS
 功能描述  : 卸载接入层的API函数
 输入参数  : VOS_RATMODE_ENUM_UINT32                                 enRatType
             NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月1日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_UnloadAS(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType,
    VOS_RATMODE_ENUM_UINT32                                 enRatType
)
{
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstCbRatInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstCbRatInfo = NAS_DYNLOAD_GetSpecCbRatInfo(enRatType);

    /* 参数有效性检查 */
    if ( (VOS_RATMODE_BUTT <= enRatType)
      || (NAS_DYNLOAD_LOAD_RATCOMB_TYPE_BUTT <= enRatCombType) )
    {
        return VOS_FALSE;
    }

    /* 如果需要卸载的接入模式已被卸载，则直接返回卸载成功 */
    if (enRatType != NAS_DYNLOAD_GetCurRatInCached(enRatCombType))
    {
        return VOS_TRUE;
    }

     /* 调用相应模块的加载函数 */
    for ( i = 0; i < pstCbRatInfo->ulNum; i++ )
    {
        NAS_DYNLOAD_LogExcuteUnloadInfo(g_astNasDynloadCbRatInfo,
                                        enRatType,
                                        pstCbRatInfo->astModule[i].ulPid,
                                        (VOS_UINT32)pstCbRatInfo->astModule[i].pfUnloadCb);

        pstCbRatInfo->astModule[i].pfUnloadCb();
    }

    NAS_DYNLOAD_SetCurRatInCached(enRatCombType, VOS_RATMODE_BUTT);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_LoadAS
 功能描述  : 加载接入层的API函数
 输入参数  : VOS_RATMODE_ENUM_UINT32                                 enRatType
             NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月1日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_LoadAS(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType,
    VOS_RATMODE_ENUM_UINT32                                 enRatType
)
{
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstCbRatInfo = VOS_NULL_PTR;
    NAS_DYNLOAD_REBOOT_INFO_STRU        stRebootInfo;
    VOS_UINT32                          i;
    VOS_INT32                           lIsAsLoaded;
    DRV_RAT_MODE_ENUM                   enDrvRatMode;
    VOS_UINT32                          ulTime;

    pstCbRatInfo = NAS_DYNLOAD_GetSpecCbRatInfo(enRatType);

    lIsAsLoaded = MDRV_ERROR;

    PS_MEM_SET(&stRebootInfo, 0x00, sizeof(stRebootInfo));

    /* 将当前需要加载的接入技术，转换成内部类型 */

    /* 参数有效性检查 */
    if ( (VOS_RATMODE_BUTT <= enRatType)
      || (NAS_DYNLOAD_LOAD_RATCOMB_TYPE_BUTT <= enRatCombType) )
    {
        return VOS_FALSE;
    }

    /* 如果需要加载的接入模式已被加载，则直接返回加载成功 */
    if (enRatType == NAS_DYNLOAD_GetCurRatInCached(enRatCombType))
    {
        return VOS_TRUE;
    }

    /* 将执行当前接入模式的卸载操作 */
    (VOS_VOID)NAS_DYNLOAD_UnloadAS(enRatCombType, NAS_DYNLOAD_GetCurRatInCached(enRatCombType));

    for ( ulTime = 0; ulTime < (NAS_DYNLOAD_GetTWMaxAttemptCount() + 1); ulTime++)
    {
        NAS_DYNLOAD_LogStartDrvLoadInfo(enRatType);

        enDrvRatMode = NAS_DYNLOAD_ConvertVosRatTypeToDrvType(enRatType);

        lIsAsLoaded = mdrv_loadas(enDrvRatMode);

        NAS_DYNLOAD_LogFinishDrvLoadInfo(g_astNasDynloadCbRatInfo, lIsAsLoaded);

        if (MDRV_OK == lIsAsLoaded)
        {
            break;
        }
    }

    if (MDRV_ERROR == lIsAsLoaded)
    {
        stRebootInfo.ulPid    = UEPS_PID_MSCC;
        stRebootInfo.enRatMode = enRatType;

        /* 复位 */
        NAS_DYNLOAD_SoftReboot(&stRebootInfo);

        return VOS_FALSE;
    }

    /* 调用相应模块的加载函数 */
    for ( i = 0; i < pstCbRatInfo->ulNum; i++ )
    {
        NAS_DYNLOAD_LogExcuteInitInfo(g_astNasDynloadCbRatInfo,
                                      enRatType,
                                      pstCbRatInfo->astModule[i].ulPid,
                                      (VOS_UINT32)pstCbRatInfo->astModule[i].pfInitCb);

        pstCbRatInfo->astModule[i].pfInitCb();
    }

    NAS_DYNLOAD_SetCurRatInCached(enRatCombType, enRatType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_GetCurRatInCached
 功能描述  : 获取当前cache中的接入技术
 输入参数  : NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType
 输出参数  : 无
 返 回 值  : VOS_RATMODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月31日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_RATMODE_ENUM_UINT32 NAS_DYNLOAD_GetCurRatInCached(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType
)
{
    return g_enCurRatModeInCached[enRatCombType];
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_SetCurRatInCached
 功能描述  : 设置cache中的接入技术
 输入参数  : NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType
             VOS_RATMODE_ENUM_UINT32                                 enRatMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月31日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_DYNLOAD_SetCurRatInCached(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType,
    VOS_RATMODE_ENUM_UINT32                                 enRatMode
)
{
    g_enCurRatModeInCached[enRatCombType] = enRatMode;
}


/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_GetEnableDynloadTWFlg
 功能描述  : 获取TW是否动态加载的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月27日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
NAS_DYNLOAD_CTRL_STRU* NAS_DYNLOAD_GetDynloadCtrl(VOS_VOID)
{
    return &g_stNasDynloadCtrl;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_GetEnableDynloadTWFlg
 功能描述  : 获取TW是否动态加载的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月27日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_DYNLOAD_GetEnableDynloadTWFlg(VOS_VOID)
{
    return NAS_DYNLOAD_GetDynloadCtrl()->ucEnableDynloadTW;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_SetEnableDynloadTWFlg
 功能描述  : 获取TW是否动态加载的标记
 输入参数  : VOS_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月27日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_DYNLOAD_SetEnableDynloadTWFlg(
    VOS_UINT8                           ucEnableFlg
)
{
    NAS_DYNLOAD_GetDynloadCtrl()->ucEnableDynloadTW = ucEnableFlg;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_GetEnableDynloadTWFlg
 功能描述  : 获取TW是否动态加载的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月27日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_DYNLOAD_GetTWMaxAttemptCount(VOS_VOID)
{
    return NAS_DYNLOAD_GetDynloadCtrl()->ucTWMaxAttemptCount;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_SetEnableDynloadTWFlg
 功能描述  : 获取TW是否动态加载的标记
 输入参数  : VOS_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月27日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_DYNLOAD_SetTWMaxAttemptCount(
    VOS_UINT8                           ucTWMaxAttemptCount
)
{
    NAS_DYNLOAD_GetDynloadCtrl()->ucTWMaxAttemptCount = ucTWMaxAttemptCount;
}


/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_GetEnableDynloadTWFlg
 功能描述  : 获取TW是否动态加载的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月27日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
NAS_DYNLOAD_CB_RAT_INFO_STRU* NAS_DYNLOAD_GetSpecCbRatInfo(
    VOS_RATMODE_ENUM_UINT32             enRatMode
)
{
    if (enRatMode >= VOS_RATMODE_BUTT)
    {
        return VOS_NULL_PTR;
    }

    return &g_astNasDynloadCbRatInfo[enRatMode];
}
#endif



/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


