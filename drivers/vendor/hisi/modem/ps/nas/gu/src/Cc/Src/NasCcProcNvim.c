/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcProcNvim.c
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2012年3月3日
  最近修改   :
  功能描述   : CC处理NV项的读写文件
  函数列表   :
  修改历史   :
  1.日    期   :2012年3月3日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasCcCtx.h"
#include "NasCcProcNvim.h"
#include "NVIM_Interface.h"
#include "NasCcCommon.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

#include "NasUsimmApi.h"
#include "NasCcTimer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_CC_PROC_NIVM_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
   4 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NAS_CC_ReadCcTimerLenNvim
 功能描述  : 获取NVIM中的en_NV_Item_CC_TimerLen的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月30日
    作    者   : l00208543
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ReadCcTimerLenNvim( VOS_VOID )
{
    NAS_CC_NVIM_TIMER_LEN_STRU          stNasCcTimerLen;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulTimerLength;

    ulLength = 0;

    ulTimerLength = 0;

    PS_MEM_SET(&stNasCcTimerLen, 0, sizeof(NAS_CC_NVIM_TIMER_LEN_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_CC_TimerLen, &ulLength);
    if (ulLength > sizeof(NAS_CC_NVIM_TIMER_LEN_STRU))
    {
        return;
    }

    if (VOS_OK != NV_Read(en_NV_Item_CC_TimerLen,
                         &stNasCcTimerLen, ulLength))
    {
        NAS_CC_WARN_LOG("NAS_CC_ReadCcTimerLenNvim():WARNING: en_NV_Item_CC_TimerLen Error");

        return;
    }

    /* 如果NV中设置的值为0或者大于等于30s，则按照协议默认值30s处理，否则视为有效值，需要进行设置 */
    if ((stNasCcTimerLen.ucT305Len > 0)
      &&(stNasCcTimerLen.ucT305Len < 30))
    {
        /* 更新T305的时长 */
        ulTimerLength = NAS_CC_ONE_THOUSAND_MILLISECOND * ((VOS_UINT32)stNasCcTimerLen.ucT305Len);
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T305, ulTimerLength);
    }
    else
    {
        /* 更新T305的时长 */
        ulTimerLength = 30000;
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T305, ulTimerLength);
    }

    if ((stNasCcTimerLen.ucT308Len > 0)
      &&(stNasCcTimerLen.ucT308Len < 30))
    {
        /* 更新T308的时长 */
        ulTimerLength = NAS_CC_ONE_THOUSAND_MILLISECOND * ((VOS_UINT32)stNasCcTimerLen.ucT308Len);
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T308, ulTimerLength);
    }
    else
    {
        /* 更新T308的时长 */
        ulTimerLength = 30000;
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T308, ulTimerLength);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ReadCcT303LenNvim
 功能描述  : 获取NVIM中的en_NV_Item_CC_TimerLen的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月20日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ReadCcT303LenNvim( VOS_VOID )
{
    NAS_CC_NVIM_T303_LEN_CFG_STRU       stNasCcT303Len;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulTimerLength;

    ulLength                          = 0;
    ulTimerLength                     = 0;
    PS_MEM_SET(&stNasCcT303Len, 0, sizeof(NAS_CC_NVIM_T303_LEN_CFG_STRU));

    /* 获取NV项长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_CC_T303_Len_Cfg, &ulLength);
    if (ulLength > sizeof(NAS_CC_NVIM_T303_LEN_CFG_STRU))
    {
        return;
    }

    /* 读取NV */
    if (VOS_OK != NV_Read(en_NV_Item_CC_T303_Len_Cfg, &stNasCcT303Len, ulLength))
    {
        NAS_CC_WARN_LOG("NAS_CC_ReadCcT303LenNvim():WARNING: en_NV_Item_CC_T303Len Error");

        return;
    }

    /* 未开启T303定时器时取默认时长 */
    if (VOS_TRUE != stNasCcT303Len.ucT303ActiveFlag)
    {
        return;
    }

    if (stNasCcT303Len.ucT303Len < TI_NAS_CC_T303_DEFAULT_LEN)
    {
        /* 时长小于30秒取30秒 */
        ulTimerLength = NAS_CC_ONE_THOUSAND_MILLISECOND * TI_NAS_CC_T303_DEFAULT_LEN;
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T303, ulTimerLength);
    }
    else
    {
        /* 更新T303时长 */
        ulTimerLength = NAS_CC_ONE_THOUSAND_MILLISECOND * ((VOS_UINT32)stNasCcT303Len.ucT303Len);
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T303, ulTimerLength);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ReadCcbsNvim
 功能描述  : 获取NVIM中的en_NV_Item_NVIM_CCBS_FLG的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID  NAS_CC_ReadCcbsNvim( VOS_VOID )
{
    NAS_NVIM_CCBS_SUPPORT_FLG_STRU   stCcbsSupportFlg;
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCcbsSupportFlg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength = 0;


    stCcbsSupportFlg.ucCcbsSupportFlg = NAS_CC_NV_ITEM_DEACTIVE;

    pstCcbsSupportFlg = NAS_CC_GetCustomCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_CCBS_SUPPORT_FLG, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_CCBS_SUPPORT_FLG_STRU))
    {
        return;
    }

    if (VOS_OK != NV_Read(en_NV_Item_NVIM_CCBS_SUPPORT_FLG,
                         &stCcbsSupportFlg, ulLength))
    {
        NAS_CC_WARN_LOG("NAS_CC_ReadCcbsNvim():WARNING: en_NV_Item_NVIM_CCBS_SUPPORT_FLG Error");

        return;
    }


    if ((NAS_CC_NV_ITEM_ACTIVE != stCcbsSupportFlg.ucCcbsSupportFlg)
     && (NAS_CC_NV_ITEM_DEACTIVE != stCcbsSupportFlg.ucCcbsSupportFlg))
    {
        pstCcbsSupportFlg->ucCcbsSupportFlg = NAS_CC_NV_ITEM_DEACTIVE;
        NAS_CC_WARN_LOG("NAS_CC_ReadCcbsNvim():WARNING: NV parameter Error");
        return;
    }

    pstCcbsSupportFlg->ucCcbsSupportFlg = stCcbsSupportFlg.ucCcbsSupportFlg;

    return;
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : NAS_CC_ReadErrlogCtrlInfoNvim
 功能描述  : 根据NV:en_NV_Item_ErrLogCtrlInfo初始化ErrlogInfo
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_CC_ReadErrlogCtrlInfoNvim(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;
    NV_ID_ERR_LOG_CTRL_INFO_STRU        stErrorLogCtrlInfo;

    ulLength = 0;
    PS_MEM_SET(&stErrorLogCtrlInfo, 0x00, sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_ErrLogCtrlInfo, &ulLength);

    ulResult = NV_Read(en_NV_Item_ErrLogCtrlInfo,
                       &stErrorLogCtrlInfo,
                       ulLength);

    if (ulResult == NV_OK)
    {
        NAS_CC_SetErrlogCtrlFlag(stErrorLogCtrlInfo.ucAlmStatus);
        NAS_CC_SetErrlogAlmLevel(stErrorLogCtrlInfo.ucAlmLevel);
    }
    else
    {
        NAS_CC_SetErrlogCtrlFlag(VOS_FALSE);
        NAS_CC_SetErrlogAlmLevel(NAS_ERR_LOG_CTRL_LEVEL_CRITICAL);
    }

    return;
}
#endif



/*****************************************************************************
 函 数 名  : NAS_CC_ReadNvimInfo
 功能描述  : 从NV中读取信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月18日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2013年8月30日
    作    者   : l00208543
    修改内容   : DTS2013082902121
  3.日    期   : 2015年3月20日
	作    者   : wx270776
	修改内容   : DTS2015030301449: 增加读取T303时长
*****************************************************************************/
VOS_VOID NAS_CC_ReadNvimInfo(VOS_VOID)
{
    /* en_NV_Item_NVIM_CCBS_SUPPORT_FLG */
    NAS_CC_ReadCcbsNvim();

    /* en_NV_Item_CC_TimerLen */
    NAS_CC_ReadCcTimerLenNvim();

    NAS_CC_ReadCcT303LenNvim();

    NAS_CC_ReadProceedingStartT310Nvim();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ReadProceedingStartT310Nvim
 功能描述  : 获取NVIM中的en_NV_Item_PROGRESS_INDICATOR_START_T310_INFO的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ReadProceedingStartT310Nvim( VOS_VOID )
{
    NAS_NVIM_PROGRESS_INDICATOR_START_T310_INFO_STRU    stProceedingT310;

    PS_MEM_SET(&stProceedingT310, 0, sizeof(NAS_NVIM_PROGRESS_INDICATOR_START_T310_INFO_STRU));

    /* 设置默认值 */
    NAS_CC_SetProceedingStartT310Flag(VOS_FALSE);

    /* 读取NV */
    if (VOS_OK != NV_Read(en_NV_Item_PROGRESS_INDICATOR_START_T310_INFO, &stProceedingT310, sizeof(stProceedingT310)))
    {
        NAS_CC_WARN_LOG("NAS_CC_ReadProceedingStartT310Nvim():WARNING: en_NV_Item_PROGRESS_INDICATOR_START_T310_INFO Error");

        return;
    }

    if (VOS_TRUE  == stProceedingT310.ucIsStartT310AccordWith3GPP)
    {
        NAS_CC_SetProceedingStartT310Flag(VOS_TRUE);
    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



