/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallProcNvim.c
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2012年3月3日
  最近修改   :
  功能描述   : CALL处理NV项的读写文件
  函数列表   :
  修改历史   :
  1.日    期   :2012年3月3日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"
#include "NVIM_Interface.h"
#include "MnCall.h"

#include "MnCallTimer.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/
#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_MN_CALL_PROC_NIVM_C

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
 函 数 名  : MN_CALL_ReadCustomizeServiceNvim
 功能描述  : 获取NVIM中的en_NV_Item_CustomizeService的内容
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
VOS_VOID  MN_CALL_ReadCustomizeServiceNvim( VOS_VOID )
{
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU               stCustomServ;
    VOS_UINT32                                    ulResult;


    stCustomServ.ulStatus           = VOS_FALSE;
    stCustomServ.ulCustomizeService = VOS_FALSE;

    /* 读取对应的几个NV项，并保存到全局变量中 */
    ulResult = NV_Read(en_NV_Item_CustomizeService,
                       &stCustomServ,
                       sizeof(stCustomServ));

    /* PC工程,回放工程,CC默认打开 */
#if (defined(__PS_WIN32_RECUR__))
        stCustomServ.ulStatus = VOS_TRUE;
        stCustomServ.ulCustomizeService = VOS_TRUE;
#endif
    /* Modified by z00234330 for PCLINT清理, 2014-07-03, begin */
    if((ulResult == NV_OK)
    &&(VOS_TRUE == stCustomServ.ulStatus)
    &&(VOS_TRUE == (stCustomServ.ulCustomizeService&0x01)))
    {
       TAF_CALL_SetCallStatusControl(VOS_TRUE);
    }
    else
    {
        TAF_CALL_SetCallStatusControl(VOS_FALSE);
    }
    /* Modified by z00234330 for PCLINT清理, 2014-07-03, end */
    return;
}

/*****************************************************************************
 函 数 名  : MN_CAL_ReadMultiSimCallConfNvim
 功能描述  : 获取NVIM中的en_NV_Item_MultiSimCallConf的内容
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
*****************************************************************************/
VOS_VOID  MN_CAL_ReadMultiSimCallConfNvim( VOS_VOID )
{
    MN_CALL_NV_ITEM_MULTISIM_CALLCON_STRU         stMultiSimCallCon;
    VOS_UINT32                                    ulResult;


    stMultiSimCallCon.usMultiSimCallConf = VOS_FALSE;

    ulResult = NV_Read(en_NV_Item_MultiSimCallConf,
                      &stMultiSimCallCon,
                      sizeof(stMultiSimCallCon));

    /* Modified by z00234330 for PCLINT清理, 2014-07-03, begin */
    if((ulResult == NV_OK)
    &&(VOS_TRUE == stMultiSimCallCon.usMultiSimCallConf))
    {
        TAF_CALL_SetMultiSimCallStatusControl(VOS_TRUE);
    }
    else
    {
        TAF_CALL_SetMultiSimCallStatusControl(VOS_FALSE);
    }
    /* Modified by z00234330 for PCLINT清理, 2014-07-03, end */

    return;
}

/*****************************************************************************
 函 数 名  : MN_CAL_ReadVideoCallNvim
 功能描述  : 获取NVIM中的en_NV_Item_VIDEO_CALL的内容
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
VOS_VOID  MN_CAL_ReadVideoCallNvim( VOS_VOID )
{
    MN_CALL_NV_ITEM_VIDEO_CALL_STRU               stVideoCall;
    VOS_UINT32                                    ulResult;
    VOS_UINT32                                    ulLength;

    ulLength                 = 0;

    stVideoCall.ucStatus     = VOS_FALSE;
    stVideoCall.ucVpCfgState = MN_CALL_VP_BUTT;

    (VOS_VOID)NV_GetLength(en_NV_Item_VIDEO_CALL, &ulLength);

    ulResult = NV_Read(en_NV_Item_VIDEO_CALL,
                       &stVideoCall,
                       ulLength);

    /* PC工程,回放工程,CC默认打开 */
#if (defined(__PS_WIN32_RECUR__))
        stVideoCall.ucStatus = VOS_TRUE;
        stVideoCall.ucVpCfgState = MN_CALL_VP_MO_MT_BOTH;
#endif
     if((ulResult == NV_OK)
     &&(VOS_TRUE == stVideoCall.ucStatus))
     {
        TAF_CALL_SetVpCfgState(stVideoCall.ucVpCfgState);
     }
     else
     {
        TAF_CALL_SetVpCfgState(MN_CALL_VP_MO_MT_BOTH);
     }

    return;
}


/*****************************************************************************
 函 数 名  : MN_CAL_ReadCcbsNvim
 功能描述  : 获取NVIM中的en_NV_Item_NVIM_CCBS_SUPPORT_FLG的内容
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
VOS_VOID  MN_CAL_ReadCcbsNvim( VOS_VOID )
{
    NAS_NVIM_CCBS_SUPPORT_FLG_STRU                          stCcbsSupportFlg;
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCcbsSupportFlg = VOS_NULL_PTR;


    stCcbsSupportFlg.ucCcbsSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;

    pstCcbsSupportFlg = MN_CALL_GetCustomCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_NVIM_CCBS_SUPPORT_FLG,
                         &stCcbsSupportFlg, sizeof(NAS_NVIM_CCBS_SUPPORT_FLG_STRU)))
    {
        MN_WARN_LOG("MN_CAL_ReadCcbsNvim():WARNING: en_NV_Item_NVIM_CCBS_SUPPORT_FLG Error");

        return;
    }


    if ((MN_CALL_NV_ITEM_ACTIVE != stCcbsSupportFlg.ucCcbsSupportFlg)
     && (MN_CALL_NV_ITEM_DEACTIVE != stCcbsSupportFlg.ucCcbsSupportFlg))
    {
        pstCcbsSupportFlg->ucCcbsSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;
        MN_WARN_LOG("MN_CAL_ReadCcbsNvim():WARNING: NV parameter Error");
        return;
    }

    pstCcbsSupportFlg->ucCcbsSupportFlg = stCcbsSupportFlg.ucCcbsSupportFlg;

    return;
}

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

/*****************************************************************************
 函 数 名  : MN_CAL_ReadCallDeflectionNvim
 功能描述  : 获取NVIM中的en_NV_Item_NVIM_CALL_DEFLECTION_SUPPORT_FLG的内容
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
*****************************************************************************/
VOS_VOID  MN_CAL_ReadCallDeflectionNvim( VOS_VOID )
{
    MN_CALL_NVIM_CALL_DEFLECTION_SUPPORT_FLG_STRU           stCallDeflectionSupportFlg;
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCallDeflectionSupportFlg = VOS_NULL_PTR;


    stCallDeflectionSupportFlg.ucCallDeflectionSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;

    pstCallDeflectionSupportFlg = MN_CALL_GetCustomCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_NVIM_CALL_DEFLECTION_SUPPORT_FLG,
                         &stCallDeflectionSupportFlg, sizeof(MN_CALL_NVIM_CALL_DEFLECTION_SUPPORT_FLG_STRU)))
    {
        MN_WARN_LOG("MN_CAL_ReadCallDeflectionNvim():WARNING: en_NV_Item_NVIM_CALL_DEFLECTION_SUPPORT_FLG Error");

        return;
    }


    if ((MN_CALL_NV_ITEM_ACTIVE != stCallDeflectionSupportFlg.ucCallDeflectionSupportFlg)
     && (MN_CALL_NV_ITEM_DEACTIVE != stCallDeflectionSupportFlg.ucCallDeflectionSupportFlg))
    {
        pstCallDeflectionSupportFlg->ucCallDeflectionSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;
        MN_WARN_LOG("MN_CAL_ReadCallDeflectionNvim():WARNING: NV parameter Error");
        return;
    }

    pstCallDeflectionSupportFlg->ucCallDeflectionSupportFlg = stCallDeflectionSupportFlg.ucCallDeflectionSupportFlg;

    return;
}

/*****************************************************************************
 函 数 名  : MN_CAL_ReadAlsSupportNvim
 功能描述  : 获取NVIM中的en_NV_Item_NVIM_ALS_SUPPORT_FLG的内容
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
VOS_VOID  MN_CAL_ReadAlsSupportNvim( VOS_VOID )
{
    MN_CALL_NVIM_ALS_SUPPORT_FLG_STRU                       stAlsSupportFlg;
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCustomCfg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength                        = 0;

    stAlsSupportFlg.ucAlsSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_ALS_SUPPORT_FLG, &ulLength);
    if (ulLength > sizeof(MN_CALL_NVIM_ALS_SUPPORT_FLG_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_NVIM_ALS_SUPPORT_FLG,
                         &stAlsSupportFlg, ulLength))
    {
        MN_WARN_LOG("MN_CAL_ReadAlsSupportNvim():WARNING: en_NV_Item_NVIM_ALS_SUPPORT_FLG Error");

        return;
    }


    if ((MN_CALL_NV_ITEM_ACTIVE != stAlsSupportFlg.ucAlsSupportFlg)
     && (MN_CALL_NV_ITEM_DEACTIVE != stAlsSupportFlg.ucAlsSupportFlg))
    {
        pstCustomCfg->ucAlsSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;
        MN_WARN_LOG("MN_CAL_ReadAlsSupportNvim():WARNING: NV parameter Error");
        return;
    }

    pstCustomCfg->ucAlsSupportFlg = stAlsSupportFlg.ucAlsSupportFlg;

    return;
}

/*****************************************************************************
 函 数 名  : MN_CAL_ReadReportEccNumSupportNvim
 功能描述  : 获取NVIM中的en_NV_Item_NVIM_ECC_NUM_REPORT_FLG的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID  MN_CALL_ReadReportEccNumSupportNvim( VOS_VOID )
{
    MN_CALL_NVIM_REPORT_ECC_NUM_SUPPORT_FLG_STRU            stCustomSetEcc;
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCustomCfg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;


    ulLength = 0;
    PS_MEM_SET(&stCustomSetEcc, 0x00, sizeof(stCustomSetEcc));

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG, &ulLength);

    if (ulLength > sizeof(MN_CALL_NVIM_REPORT_ECC_NUM_SUPPORT_FLG_STRU))
    {
        MN_WARN_LOG("MN_CALL_ReadReportEccNumSupportNvim():WARNING: en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG length Error");
        pstCustomCfg->ucReportEccNumFlg = VOS_FALSE;

        return;
    }

    (VOS_VOID)NV_GetLength(en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG, &ulLength);
    if (ulLength > sizeof(MN_CALL_NVIM_REPORT_ECC_NUM_SUPPORT_FLG_STRU))
    {
        return;
    }

    /* 如果NV读取失败，则设置为不激活 */
    if (NV_OK != NV_Read(en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG,
                         &stCustomSetEcc, ulLength))
    {
        MN_WARN_LOG("MN_CAL_ReadReportEccNumSupportNvim():WARNING: en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG Error");

        pstCustomCfg->ucReportEccNumFlg = VOS_FALSE;

        return;
    }

    /* NV激活则设置主动上报激活标志为VOS_TRUE */
    if (MN_CALL_NV_ITEM_ACTIVE == stCustomSetEcc.ucReportEccNumFlg)
    {
        pstCustomCfg->ucReportEccNumFlg = VOS_TRUE;
    }
    else
    {
        pstCustomCfg->ucReportEccNumFlg = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_CALL_ReadCallRedialCfgNvim
 功能描述  : 获取NVIM中的en_NV_Item_CS_Call_Redial_CFG的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : 支持呼叫重建新增nv项
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2012年1月4日
    作    者   : w00176964
    修改内容   : DTS2013010403491:GCF测试卡,CC呼叫重建的开关需要关闭
  4.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
  1.日    期   : 2014年04月09日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
*****************************************************************************/
VOS_VOID  MN_CALL_ReadCallRedialCfgNvim( VOS_VOID )
{
    MN_CALL_REDIAL_CFG_STRU             stCallRedialCfg;
    MN_CALL_CUSTOM_CFG_INFO_STRU       *pstCustomCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;


    ulLength = 0;

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
    /* GCF测试,短信重发功能需要关闭 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod     = 0;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval   = 0;


        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD,
                                    pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod);

        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL,
                                    pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval);

        return;
    }

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_CS_Call_Redial_CFG, &ulLength);

    PS_MEM_SET(&stCallRedialCfg, 0x0, sizeof(MN_CALL_REDIAL_CFG_STRU));

    if (ulLength > sizeof(MN_CALL_REDIAL_CFG_STRU))
    {
        MN_WARN_LOG("MN_CALL_ReadCallRedialCfgNvim():WARNING: en_NV_Item_CS_Call_Redial_CFG length Error");
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod     = 0;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval   = 0;

        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod);
        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval);
        return;
    }

    /* 如果NV读取失败，则设置为不激活 */
    if (NV_OK != NV_Read(en_NV_Item_CS_Call_Redial_CFG,
                         &stCallRedialCfg, sizeof(MN_CALL_REDIAL_CFG_STRU)))
    {
        MN_WARN_LOG("MN_CALL_ReadCallRedialCfgNvim():WARNING: en_NV_Item_CS_Call_Redial_CFG Error");
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod     = 0;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval   = 0;

        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod);
        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval);
        return;
    }

    if (MN_CALL_NV_ITEM_ACTIVE == stCallRedialCfg.ucCallRedialSupportFlg)
    {
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialSupportFlg = VOS_TRUE;

        /* nv中存的时长为秒，需要转换为毫秒 */
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod
            = MN_CALL_ONE_THOUSAND_MILLISECOND * stCallRedialCfg.ulCallRedialPeriod;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval
            = MN_CALL_ONE_THOUSAND_MILLISECOND * stCallRedialCfg.ulCallRedialInterval;

    }
    else
    {
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod     = 0;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval   = 0;

    }

    MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod);
    MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval);
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */

    return;
}

/*****************************************************************************
 函 数 名  : MN_CALL_ReadCallRedialCmSrvRejCfgNvim
 功能描述  : 获取NVIM中的en_NV_Item_CALL_REDIAL_CM_SRV_REJ_CAUSE_CFG的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月24日
    作    者   : n00355355
    修改内容   : 支持呼叫重建新增nv项
*****************************************************************************/

VOS_VOID  MN_CALL_ReadCallRedialCmSrvRejCfgNvim( VOS_VOID )
{
    TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU                     stCallRedialCmSrvRejCfg;
    VOS_UINT32                                              ulLength;
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCustomCfg = VOS_NULL_PTR;


    ulLength = 0;

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialCmSrvRejCauseNum = 0;

        return;
    }

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_CALL_REDIAL_CM_SRV_REJ_CAUSE_CFG, &ulLength);

    if (ulLength > sizeof(TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU))
    {
        MN_WARN_LOG("MN_CALL_ReadCallRedialCfgNvim():WARNING: en_NV_Item_CALL_REDIAL_CM_SRV_REJ_CAUSE_CFG length Error");

        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialCmSrvRejCauseNum = 0;

        return;
    }

    PS_MEM_SET(&stCallRedialCmSrvRejCfg, 0x0, sizeof(TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU));

    /* 如果NV读取失败，则设置为不激活 */
    if (NV_OK != NV_Read(en_NV_Item_CALL_REDIAL_CM_SRV_REJ_CAUSE_CFG,
                         &stCallRedialCmSrvRejCfg, sizeof(TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU)))
    {
        MN_WARN_LOG("MN_CALL_ReadCallRedialCmSrvRejCfgNvim():WARNING: TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU Error");

        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialCmSrvRejCauseNum = 0;


        return;
    }

    if (stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum > TAF_NVIM_CALL_REDIAL_CAUSE_MAX_NUM)
    {
        stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum    = TAF_NVIM_CALL_REDIAL_CAUSE_MAX_NUM;
    }

    pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialCmSrvRejCauseNum
        = stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum;

    PS_MEM_CPY(pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.aucCallRedialCmSrvRejCause,
                stCallRedialCmSrvRejCfg.aucCallRedialCmSrvRejCause,
                stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum);

   return;
}



/*****************************************************************************
 函 数 名  : TAF_CALL_ReadCallNotSupportedCause
 功能描述  : 获取CALL模块的终端不支持CALL，回复RELEASE COMPLETE消息原因定制值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月09日
    作    者   : f62575
    修改内容   : DTS2013120411878，终端不支持VOICE/VIDEO CALL，回复RELEASE
COMPLETE消息原因定制值
*****************************************************************************/
VOS_VOID TAF_CALL_ReadCallNotSupportedCause(VOS_VOID)
{
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfg = VOS_NULL_PTR;
    TAF_CALL_NVIM_CALL_NOT_SUPPORTED_CAUSE_STRU             stVoiceCallNotSupportedCause;

    if (NV_OK != NV_Read(en_NV_Item_CALL_CallNotSupportedCause,
                         &stVoiceCallNotSupportedCause,
                         sizeof(stVoiceCallNotSupportedCause)))
    {
        stVoiceCallNotSupportedCause.ucVoiceCallNotSupportedCause = MN_CALL_USER_BUSY;
        stVoiceCallNotSupportedCause.ucVideoCallNotSupportedCause = MN_CALL_INCOMPATIBLE_DESTINATION;
    }

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    pstCustomCfg->ucVoiceCallNotSupportedCause =
                      stVoiceCallNotSupportedCause.ucVoiceCallNotSupportedCause;
    pstCustomCfg->ucVideoCallNotSupportedCause =
                      stVoiceCallNotSupportedCause.ucVideoCallNotSupportedCause;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_ReadAtaReportOkAsyncCfgNvim
 功能描述  : 读取ata 是否异步上报ok配置nv项
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月23日
    作    者   : z00161729
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_CALL_ReadAtaReportOkAsyncCfgNvim(VOS_VOID)
{
    TAF_CALL_NVIM_ATA_REPORT_OK_ASYNC_CFG_STRU              stAtaReportOkAsyncCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_Ata_Report_Ok_Async_Cfg, &ulLength);

    PS_MEM_SET(&stAtaReportOkAsyncCfg, 0x0, sizeof(stAtaReportOkAsyncCfg));

    /* 设置默认值为VOS_FALSE */
    TAF_CALL_SetAtaReportOkAsyncFlag(VOS_FALSE);

    if (ulLength > sizeof(TAF_CALL_NVIM_ATA_REPORT_OK_ASYNC_CFG_STRU))
    {
       return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Ata_Report_Ok_Async_Cfg,
                         &stAtaReportOkAsyncCfg,
                         sizeof(stAtaReportOkAsyncCfg)))
    {
        return;
    }

    if (VOS_TRUE == stAtaReportOkAsyncCfg.ucAtaReportOkAsyncFlag)
    {
        TAF_CALL_SetAtaReportOkAsyncFlag(VOS_TRUE);
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_CALL_ReadCcwaCtrlModeNvim
 功能描述  : 读取ccwa控制模式的NV项
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CALL_ReadCcwaCtrlModeNvim(VOS_VOID)
{
    TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU                       stCcwaCtrlMode;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_Ccwa_Ctrl_Mode, &ulLength);

    PS_MEM_SET(&stCcwaCtrlMode, 0x0, sizeof(stCcwaCtrlMode));

    if (ulLength > sizeof(TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU))
    {
        MN_ERR_LOG("TAF_CALL_ReadCcwaCtrlModeNvim():ERROR: en_NV_Item_Ccwa_Ctrl_Mode length Error");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Ccwa_Ctrl_Mode,
                         &stCcwaCtrlMode,
                         sizeof(stCcwaCtrlMode)))
    {
        MN_ERR_LOG("TAF_CALL_ReadCcwaCtrlModeNvim():ERROR: en_NV_Item_Ccwa_Ctrl_Mode read Error");
        return;
    }


    if (stCcwaCtrlMode.enCcwaCtrlMode >= TAF_CALL_CCWA_CTRL_MODE_BUTT)
    {
        MN_ERR_LOG("TAF_CALL_ReadCcwaCtrlModeNvim():ERROR: en_NV_Item_Ccwa_Ctrl_Mode enCcwaCtrlMode Error");
        return;
    }

    TAF_CALL_SetCcwaCtrlMode(stCcwaCtrlMode.enCcwaCtrlMode);

    return;
}

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : TAF_CALL_ReadEcallCfgNvim
 功能描述  : 获取eCall重拨时长与重拨间隔事件

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月04日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_ReadEcallCfgNvim(VOS_VOID)
{
    TAF_CALL_NVIM_ECALL_CFG_STRU        stEcallCfg;
    MN_CALL_CUSTOM_CFG_INFO_STRU       *pstCustomCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    PS_MEM_SET(&stEcallCfg, 0x0, sizeof(TAF_CALL_NVIM_ECALL_CFG_STRU));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_ECALL_CFG_INFO, &ulLength);

    if (ulLength > sizeof(TAF_CALL_NVIM_ECALL_CFG_STRU))
    {
        MN_WARN_LOG("TAF_CALL_ReadEcallRedialCfgNvim():WARNING: en_NV_Item_ECALL_REDIAL_CFG_INFO length Error");
        /* NV长度非法，默认eCall重拨支持，定时器时长使用hard code中的缺省值 */
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ucCallRedialSupportFlg = VOS_TRUE;

        MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD, TAF_ECALL_REDIAL_PERIOD_TIMER_LENGTH);

        MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL, TAF_ECALL_REDIAL_INTERVAL_TIMER_LENGTH);

        return;
    }

    /* 如果NV读取失败，则设置为不激活 */
    if (NV_OK != NV_Read(en_NV_Item_ECALL_CFG_INFO,
                         &stEcallCfg, sizeof(TAF_CALL_NVIM_ECALL_CFG_STRU)))
    {
        MN_WARN_LOG("TAF_CALL_ReadEcallRedialCfgNvim():WARNING: en_NV_Item_ECALL_REDIAL_CFG_INFO Error");
        /* NV读取失败，默认eCall重拨支持，定时器时长使用hard code中的缺省值 */
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ucCallRedialSupportFlg = VOS_TRUE;

        MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD, TAF_ECALL_REDIAL_PERIOD_TIMER_LENGTH);

        MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL, TAF_ECALL_REDIAL_INTERVAL_TIMER_LENGTH);

        return;
    }

    if (MN_CALL_NV_ITEM_ACTIVE == stEcallCfg.ucEcallRedialSupportFlg)
    {
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ucCallRedialSupportFlg = VOS_TRUE;

        /* nv中存的时长为秒，需要转换为毫秒 */
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialPeriod
            = (VOS_UINT32)(MN_CALL_ONE_THOUSAND_MILLISECOND * stEcallCfg.usEcallRedialPeriod);
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialInterval
            = (VOS_UINT32)(MN_CALL_ONE_THOUSAND_MILLISECOND * stEcallCfg.usEcallRedialInterval);
    }
    else
    {
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ucCallRedialSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialPeriod     = 0;
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialInterval   = 0;
    }

    MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD,
                              pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialPeriod);
    MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL,
                              pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialInterval);

    /* 更新T9时长, 如果不在1~12小时范围，不更新，使用缺省值 */
    if ((stEcallCfg.ucEcallT9Len < TAF_CALL_T9_MIN_TIMER_LENGTH)
     || (stEcallCfg.ucEcallT9Len > TAF_CALL_T9_MAX_TIMER_LENGTH))
    {
        return;
    }

    MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_T9, (stEcallCfg.ucEcallT9Len*TAF_CALL_ONE_HOUR_TIMER_LENGTH));

    return;
}
#endif
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, end */

/*****************************************************************************
 函 数 名  : MN_CALL_ReadNvimInfo
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
  2.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目
  3.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  4.日    期   : 2013年12月09日
    作    者   : f62575
    修改内容   : DTS2013120411878，终端不支持VOICE/VIDEO CALL，回复RELEASE COMPLETE消息原因定制值
  5.日    期   : 2014年04月08日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
  6.日    期   : 2014年6月24日
    作    者   : z00161729
    修改内容   : DSDS III新增
*****************************************************************************/
VOS_VOID MN_CALL_ReadNvimInfo(VOS_VOID)
{
    /* en_NV_Item_CustomizeService */
    MN_CALL_ReadCustomizeServiceNvim();

    /* en_NV_Item_MultiSimCallConf */
    MN_CAL_ReadMultiSimCallConfNvim();

    /* en_NV_Item_VIDEO_CALL */
    MN_CAL_ReadVideoCallNvim();

    /* en_NV_Item_NVIM_CCBS_SUPPORT_FLG */
    MN_CAL_ReadCcbsNvim();

    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

    /* en_NV_Item_NVIM_CALL_DEFLECTION_SUPPORT_FLG */
    MN_CAL_ReadCallDeflectionNvim();

    /* en_NV_Item_NVIM_ALS_SUPPORT_FLG */
    MN_CAL_ReadAlsSupportNvim();

    /* en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG */
    MN_CALL_ReadReportEccNumSupportNvim();

    MN_CALL_ReadCallRedialCfgNvim();

    MN_CALL_ReadCallRedialCmSrvRejCfgNvim();

    TAF_CALL_ReadCallNotSupportedCause();

    TAF_CALL_ReadAtaReportOkAsyncCfgNvim();

    TAF_CALL_ReadCcwaCtrlModeNvim();

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    /* 获取eCall配置参数 */
    TAF_CALL_ReadEcallCfgNvim();
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, end */
    return;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



