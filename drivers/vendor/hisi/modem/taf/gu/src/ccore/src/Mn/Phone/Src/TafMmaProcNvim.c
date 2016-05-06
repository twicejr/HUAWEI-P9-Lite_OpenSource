/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaProcNvim.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年7月9日
  最近修改   :
  功能描述   : MMa处理NV项的读写文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年07月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "pscfg.h"
#if (FEATURE_LTE == FEATURE_ON)
#include "msp_nvim.h"
#endif
#include "ScInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

#include "TafAppMma.h"
#include "MmaAppLocal.h"
#include "GasNvInterface.h"

#include "TafLog.h"

#if ( FEATURE_ON == FEATURE_LTE )
#include "LPsNvInterface.h"
#include "LNvCommon.h"
#endif

#if (FEATURE_ON == FEATURE_IMS)
#include "ImsaNvInterface.h"
#endif

#include "NasMntn.h"
#include "TafLog.h"
#include "TafMmaMntn.h"
#include "TafMmaComFunc.h"

#include "NasUsimmApi.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_PROC_NVIM_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/
extern NAS_MMA_NEW_ADD_GLABAL_VARIABLE_FOR_PC_REPLAY_ST g_MmaNewValue;
extern MMA_DEACT_SIM_WHEN_POWEROFF_ENUM_UINT8           g_ucMmaDeactSimWhenPoweroff;
extern TAF_MMA_GLOBAL_VALUE_ST                          gstMmaValue;
extern VOS_UINT8                                        g_ucMmaOmConnectFlg;                           /* 是否已与PC工具连接, VOS_TRUE: 已连接; VOS_FALSE: 未连接.                                                                                   默认未连接 */
extern VOS_UINT8                                        g_ucMmaOmPcRecurEnableFlg;                     /* 当前PC工具是否使能了NAS的PC回放消息的发送, VOS_TRUE: 使能; VOS_FASLE: 未使能
                                                                                   默认使能PC回放 */
extern VOS_UINT32                                       g_ucUsimHotOutFlag;
extern VOS_UINT32                                       g_ucUsimHotInFlag;
extern MMA_UE_FORB_BAND_ST                              gstMmaForbBand;
extern ENUM_SYSTEM_APP_CONFIG_TYPE_U16                  g_usMmaAppConfigSupportType;
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-12, begin */
extern VOS_UINT8                                        g_aucMmaImei[TAF_PH_IMEI_LEN-1];
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-12, end */


/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadUeSupporttedGuBandNvim
 功能描述  : 从NV项中获取当前UE支持的GU的频段值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月23日
    作    者   : likelai
    修改内容   : 新生成函数
  2.日    期   : 2012年3月5日
    作    者   : w00176964
    修改内容   : DTS2012121802573:band6,BAND19支持
  3.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID TAF_MMA_ReadUeSupporttedGuBandNvim(VOS_VOID)
{
    /* 修改硬件频段的读取为32位格式 */
    VOS_UINT32                          aulSptBand[3];
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stUeBand;
    TAF_MMA_USER_BAND_SET_UN            uUserSetBand;
    VOS_UINT32                          ulDataLen;
    TAF_MMA_UE_BAND_CAPA_ST            *pstUeBandCap = VOS_NULL_PTR;

    ulDataLen = 0;

    /*获取 UE支持的 Band */
    PS_MEM_SET(&stUeBand,0x00,sizeof(stUeBand));
    PS_MEM_SET(&uUserSetBand,0x00,sizeof(uUserSetBand));


    PS_MEM_SET(aulSptBand, 0x00, sizeof(aulSptBand));

    (VOS_VOID)NV_GetLength(en_NV_Item_WG_RF_MAIN_BAND, &ulDataLen);

    if (NV_OK != NV_Read(en_NV_Item_WG_RF_MAIN_BAND,aulSptBand,ulDataLen))
    {
        /*打印未成功初始化值，原值保留*/
        MMA_WARNINGLOG("MMA_InitMeInfo():Read en_NV_Item_WG_RF_MAIN_BAND Failed!");
    }
    else
    {
        pstUeBandCap = TAF_MMA_GetUeSupportBandAddr();

        stUeBand.unWcdmaBand.ulBand = aulSptBand[0];
        pstUeBandCap->unWRFSptBand.ulBand = aulSptBand[0];
        MMA_SwitchUESupportBand2UserSetBand(stUeBand,&uUserSetBand);
        pstUeBandCap->ulUeWSptBand = uUserSetBand.ulPrefBand;

        PS_MEM_SET(&stUeBand,0x00,sizeof(stUeBand));
        PS_MEM_SET(&uUserSetBand,0x00,sizeof(uUserSetBand));
        /*V9R1 NV数据结构扩展为32位 */
        stUeBand.unGsmBand.ulBand = aulSptBand[2];
        pstUeBandCap->unGRFSptBand.ulBand = aulSptBand[2];
        /*V9R1 NV数据结构扩展为32位 */
        MMA_SwitchUESupportBand2UserSetBand(stUeBand,&uUserSetBand);
        pstUeBandCap->ulUeGSptBand = uUserSetBand.ulPrefBand;

        pstUeBandCap->ulAllUeBand = (pstUeBandCap->ulUeGSptBand | pstUeBandCap->ulUeWSptBand);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadForbBandNvim
 功能描述  : 从NV项中获取ForbBand的值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月23日
    作    者   : likelai
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
  4.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID TAF_MMA_ReadForbBandNvim(VOS_VOID)
{
    VOS_UINT32                          ulLen;
    NAS_MMA_NVIM_FORBAND_STRU           stForband;
    VOS_UINT8                           ucOffSet;


    ulLen = 0;
    PS_MEM_SET(&stForband, 0x00, sizeof(stForband));

    (VOS_VOID)NV_GetLength(en_NV_Item_Forbidden_Band, &ulLen);

    if (ulLen > MMA_FORB_BAND_NV_MAX_SIZE)
    {
        return;
    }

    PS_MEM_SET(&stForband, 0, ulLen);

    if (NV_OK != NV_Read(en_NV_Item_Forbidden_Band,&stForband, ulLen))
    {
        MMA_WARNINGLOG("MMA_GetForbBandFromNV():WARNING: en_NV_Item_Forbbiden_Band Error");
        return;
    }

    /*
    gstMmaForbBand定义与NV中的值不一致，需要按下述字节进行转换
    VOS_UINT8    ucActiveFlag  - NV项第1个字节
    VOS_UINT8    ucForbStatus  - NV项第2个字节
    TAF_UINT32   ulBandLow     - NV项第3-6个字节
    TAF_UINT32   ulBandHigh    - NV项第7-10个字节
    */
    ucOffSet = 0;
    /*lint -e961*/
    gstMmaForbBand.ucActiveFlag = stForband.aucForband[ucOffSet++];
    /*lint +e961*/

    if (NV_ITEM_DEACTIVE == gstMmaForbBand.ucActiveFlag)
    {
        return;
    }
    /*lint -e961*/
    gstMmaForbBand.ucForbStatus = stForband.aucForband[ucOffSet++];
    /*lint +e961*/

    PS_MEM_CPY(&(gstMmaForbBand.stForbBand.ulBandLow),stForband.aucForband+ucOffSet,
                                sizeof(gstMmaForbBand.stForbBand.ulBandLow));

    ucOffSet += sizeof(gstMmaForbBand.stForbBand.ulBandLow);

    PS_MEM_CPY(&(gstMmaForbBand.stForbBand.ulBandHigh),stForband.aucForband+ucOffSet,
                                sizeof(gstMmaForbBand.stForbBand.ulBandHigh));


    if ( (0 != gstMmaForbBand.stForbBand.ulBandHigh)
      || (TAF_PH_BAND_ANY != gstMmaForbBand.stForbBand.ulBandLow))
    {
        gstMmaForbBand.ulForbBand = gstMmaForbBand.stForbBand.ulBandHigh |
            (gstMmaForbBand.stForbBand.ulBandLow & ~TAF_PH_BAND_NEED_CHANGE_TO_64BIT);
    }
    else
    {
        gstMmaForbBand.ulForbBand = gstMmaForbBand.stForbBand.ulBandLow;
    }

    /* 容错处理 */
    if (TAF_PH_BAND_ANY == gstMmaForbBand.ulForbBand)
    {
        gstMmaForbBand.ulForbBand = 0;
    }

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_MMA_ReadNvimUeSupporttedLteBand
 功能描述  : 读单板支持的LTE Band范围
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : z00161729
   修改内容   : 新生成函数

 2.日    期   : 2011年11月21日
   作    者   : w00167002
   修改内容   : DTS2011112102720:从NV en_NV_Item_EUTRA_CAPA_COMM_INFO中获取的结构体
                为类型NVIM_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU，而不是
                TAF_USER_SET_PREF_BAND64类型。
                修改内容:从en_NV_Item_EUTRA_CAPA_COMM_INFO中读取内容后，转换为NAS
                格式，即ulBandLow的最低bit对应band1，最高bit对应band32
                ulBandHigh的最低bit对应band33，最高bit对应band64。

 3.日    期   : 2011年12月3日
   作    者   : w00167002
   修改内容   : DTS2011120300373:DTS2011112102720修改时，对于获取NV中的频段信息
                 通过指数算法来实现，效率低下，现修改为通过移位来实现。
 4.日    期   : 2012年12月11日
   作    者   : L00171473
   修改内容   : DTS2012121802573, TQE清理
 5.日    期   : 2013年8月9日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseI项目:修改函数名
 6.日    期   : 2013年11月25日
   作    者   : w00242748
   修改内容   : DTS2013112602236,废弃NVID 9005后，读取LNVID 53804修改
*****************************************************************************/
VOS_VOID TAF_MMA_ReadNvimUeSupporttedLteBand(VOS_VOID)
{
    TAF_USER_SET_PREF_BAND64                   *pstUeSupportLteBand = VOS_NULL_PTR;

    VOS_UINT32                                  ulRslt;
    LRRC_NV_UE_EUTRA_CAP_STRU                  *pstUECapability     = VOS_NULL_PTR;
    RRC_UE_CAP_RF_PARA_STRU                    *pstRfPara           = VOS_NULL_PTR;
    VOS_UINT32                                  i;
    VOS_UINT8                                   ucBandNo;

    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();

    PS_MEM_SET(pstUeSupportLteBand, 0X0, sizeof(TAF_USER_SET_PREF_BAND64));



    pstUECapability =(LRRC_NV_UE_EUTRA_CAP_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                            sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));

    if(VOS_NULL_PTR == pstUECapability)
    {
        MN_ERR_LOG("TAF_MMA_ReadNvimUeSupporttedLteBand():PS_MEM_ALLOC failed!");
        return ;
    }

    PS_MEM_SET(pstUECapability, 0x00, sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));


    /* LTE NV项长度 */
    ulRslt = NVM_Read(EN_NV_ID_UE_CAPABILITY, pstUECapability, sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));


    if ( (NV_OK != ulRslt)
      || (NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM < pstUECapability->stRfPara.usCnt) )
    {
        /* 读NV失败,打印未成功初始化值，默认赋值为支持所有频段 */
        MN_ERR_LOG("TAF_MMA_ReadNvimUeSupporttedLteBand():read en_NV_Item_EUTRA_CAPA_COMM_INFO error");
        pstUeSupportLteBand->ulBandHigh = MN_MMA_LTE_HIGH_BAND_ALL;
        pstUeSupportLteBand->ulBandLow  = MN_MMA_LTE_LOW_BAND_ALL;

        PS_MEM_FREE(WUEPS_PID_MMA, pstUECapability);

        return;
    }

    /* 获取NV中的频段信息:
       ulBandLow的最低bit对应band1，最高bit对应band32
       ulBandHigh的最低bit对应band33，最高bit对应band64 */
    pstRfPara = &(pstUECapability->stRfPara);

    for ( i = 0; i < pstRfPara->usCnt; i++ )
    {
        ucBandNo = (pstRfPara->astSuppEutraBandList[i]).ucEutraBand;

        /* NV中的频段信息指示为低32,即对应band1到band32*/
        if ( ucBandNo <= (NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM / 2) )
        {
            /*lint -e701*/
            pstUeSupportLteBand->ulBandLow  |= (VOS_UINT32)( 0x00000001 << (ucBandNo - 1) );
            /*lint +e701*/

        }

        /* NV中的频段信息指示为高32,即对应band33到band64 */
        else if ( ucBandNo <= NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM  )
        {
            /*lint -e961 -e701*/
            pstUeSupportLteBand->ulBandHigh |= (VOS_UINT32)( 0x00000001 << (ucBandNo - 32 - 1) );
            /*lint +e961 +e701*/
        }
        else
        {
            /* band号异常 */
            MN_ERR_LOG("TAF_MMA_ReadNvimUeSupporttedLteBand():LTE BAND NO IS BIG THAN 64, error");
        }
    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstUECapability);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadUserSetLteBands
 功能描述  : 读用户设置的LTE Band范围
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年8月8日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadUserSetLteBands(VOS_VOID)
{
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    /* 读用户设置的LTE频段 NV项 */
    if (NV_OK != NV_Read(en_NV_Item_USER_SET_LTEBANDS,
                         &(pstUserSetBand->stUserSetLteBand), sizeof(TAF_USER_SET_PREF_BAND64)))
    {
        /* 读NV失败,打印未成功初始化值，默认赋值为支持所有频段 */
        pstUserSetBand->stUserSetLteBand.ulBandLow  = MN_MMA_LTE_LOW_BAND_ANY;
        pstUserSetBand->stUserSetLteBand.ulBandHigh = MN_MMA_LTE_HIGH_BAND_ANY;
    }

    return;
}


#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadFreqBandNvim
 功能描述  : 从NV项en_NV_Item_Support_Freqbands中获取当前系统设置的频段值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月23日
    作    者   : likelai
    修改内容   : 新生成函数
  2.日    期   : 2014年8月1日
    作    者   : b00269685
    修改内容   : DTS2014071803206:拆分nv8229

*****************************************************************************/
VOS_VOID  TAF_MMA_ReadFreqBandNvim(VOS_VOID)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-8-14, begin */
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand = VOS_NULL_PTR;
    NVIM_UE_SUPPORT_FREQ_BAND_STRU      stUserSetFreqBand;

    PS_MEM_SET(&stUserSetFreqBand, 0x00, sizeof(stUserSetFreqBand));

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    if (NV_OK != NV_Read(en_NV_Item_Support_Freqbands,
                         &stUserSetFreqBand, sizeof(NVIM_UE_SUPPORT_FREQ_BAND_STRU)))
    {
        /* 打印未成功初始化值，原值保留 */
        MN_WARN_LOG("TAF_MMA_ReadFreqBandNvim():Read Support_Freqbands Failed!");

        return;
    }

    pstUserSetBand->uUserSetUeFormatGuBand.unWcdmaBand.ulBand = stUserSetFreqBand.ulWcdmaBand;
    pstUserSetBand->uUserSetUeFormatGuBand.unGsmBand.ulBand   = stUserSetFreqBand.ulGsmBand;

    PS_MEM_SET(pstUserSetBand->uUserSetUeFormatGuBand.aucReserved1,
               0,
               sizeof(pstUserSetBand->uUserSetUeFormatGuBand.aucReserved1));
    PS_MEM_SET(pstUserSetBand->uUserSetUeFormatGuBand.aucReserved2,
               0,
               sizeof(pstUserSetBand->uUserSetUeFormatGuBand.aucReserved2));
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-8-14, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadUserSettedBandNvim
 功能描述  : 从NV中读取用户设置的G/W/L频段
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月11日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID TAF_MMA_ReadUserSettedBandNvim(VOS_VOID)
{
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    /* 获取用户设置的GU频段 */
    if (NV_OK != NV_Read(en_NV_Item_User_Set_Freqbands,
                         &(pstUserSetBand->stOrigUserSetGuBand),
                         sizeof(TAF_USER_SET_PREF_BAND64)))
    {
        /*打印未成功初始化值，原值保留*/
        pstUserSetBand->uUserSetGuBand.ulPrefBand      = TAF_PH_BAND_ANY;
        pstUserSetBand->stOrigUserSetGuBand.ulBandHigh = 0;
        pstUserSetBand->stOrigUserSetGuBand.ulBandLow  = TAF_PH_BAND_ANY;
        MMA_WARNINGLOG("TAF_MMA_ReadUserSettedBandNvim():Read UserSet_Freqbands Failed!");
    }
    else
    {
        if ( (0 != pstUserSetBand->stOrigUserSetGuBand.ulBandHigh )
          || ( TAF_PH_BAND_ANY != pstUserSetBand->stOrigUserSetGuBand.ulBandLow) )
        {
            pstUserSetBand->uUserSetGuBand.ulPrefBand = pstUserSetBand->stOrigUserSetGuBand.ulBandHigh |
                                        (pstUserSetBand->stOrigUserSetGuBand.ulBandLow & ~TAF_PH_BAND_NEED_CHANGE_TO_64BIT);
            /* 过滤无效频段 */
            pstUserSetBand->uUserSetGuBand.ulPrefBand &= (TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand);
        }
        else
        {
            /* 当前频段为TAF_PH_BAND_ANY时，赋值为单板支持的所有频段 */
            pstUserSetBand->uUserSetGuBand.ulPrefBand = TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;
        }
    }

    MN_INFO_LOG1("TAF_MMA_ReadUserSettedBandNvim():Support_Freqbands:",(VOS_INT32)pstUserSetBand->uUserSetGuBand.ulPrefBand);


    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateBandCapa
 功能描述  : 读取ForbBand的NV项之后，更新gstMmaBandCapa
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_UpdateBandCapa(VOS_VOID)
{
    TAF_MMA_GetUeSupportBandAddr()->ulUeWSptBand &= ~(gstMmaForbBand.ulForbBand);
    TAF_MMA_GetUeSupportBandAddr()->ulUeGSptBand &= ~(gstMmaForbBand.ulForbBand);
    TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand = (TAF_MMA_GetUeSupportBandAddr()->ulUeGSptBand \
                                                 | TAF_MMA_GetUeSupportBandAddr()->ulUeWSptBand);


    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateUserSetFreqBand
 功能描述  : 读取ForbBand的NV项之后，更新gstMmaBandCapa
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_UpdateUserSetFreqBand(VOS_VOID)
{
    TAF_USER_SET_PREF_BAND64            stUserSetBandAny;  /*64位原始频带*/
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    stUserSetBandAny.ulBandHigh = 0;
    stUserSetBandAny.ulBandLow = TAF_PH_BAND_ANY;

    /* 更新用户设置频段的NV为3fffffff */
    if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_User_Set_Freqbands,
                                           &stUserSetBandAny,
                                           sizeof(stUserSetBandAny)))
    {
        MMA_WARNINGLOG("MMA_UpdateBandNvRefForbBand():WARNING:NVIM_Write en_NV_Item_User_Set_Freqbands failed");
    }

    /* 当前频段为TAF_PH_BAND_ANY时，赋值为单板支持的所有频段 */
    /* 写完en_NV_Item_User_Set_Freqbands之后，直接更新全局变量，后续不用再重新读该NV */
    pstUserSetBand->uUserSetGuBand.ulPrefBand = TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateSupportFreqBand
 功能描述  : 读取ForbBand的NV项之后，更新gstMmaBandCapa
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_UpdateSupportFreqBand(
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU  *pstOrigFreqBand
)
{
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    /* 更新频段NV */
    if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_Support_Freqbands,
                                           pstOrigFreqBand,
                                           sizeof(pstOrigFreqBand->unWcdmaBand)+sizeof(pstOrigFreqBand->unGsmBand)))
    {
        MMA_WARNINGLOG("MMA_UpdateBandNvRefForbBand():WARNING:NVIM_Write en_NV_Item_Support_Freqbands failed");
    }

    /* 写完en_NV_Item_Support_Freqbands之后，直接更新全局变量，后续不用再重新读该NV */
    PS_MEM_CPY(&(pstUserSetBand->uUserSetUeFormatGuBand),
                pstOrigFreqBand,
                sizeof(TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : MMA_UpdateFreqBandRefForbBand
 功能描述  : 根据禁止频段的信息更新FreqBandNV和UsersetBandNV
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月23日
    作    者   : likelai
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  4.日    期   : 2013年7月16日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改
*****************************************************************************/
VOS_VOID MMA_UpdateBandNvRefForbBand(VOS_VOID)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-16, begin */
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU    stOrigFreqBand;
    TAF_MMA_USER_BAND_SET_UN             uOrigFreqBand;
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU   *pstUserSetBand = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();


    PS_MEM_SET(&uOrigFreqBand, 0, sizeof(TAF_MMA_USER_BAND_SET_UN));

    PS_MEM_SET(&stOrigFreqBand, 0x00, sizeof(stOrigFreqBand));

    stOrigFreqBand  = pstUserSetBand->uUserSetUeFormatGuBand;

    /*将当前系统设置的频段转换为用户设置的格式*/
    MMA_SwitchUESupportBand2UserSetBand(stOrigFreqBand,&uOrigFreqBand);
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-16, end */

    /* 当前系统设置的频段与ulForbBand是否有交集 */
    if (0 != (uOrigFreqBand.ulPrefBand & gstMmaForbBand.ulForbBand))
    {
        /*过滤掉当前禁止的频段*/
        uOrigFreqBand.ulPrefBand &= ~(gstMmaForbBand.ulForbBand);

        MMA_SwitchUserSetBand2UESupportBand(uOrigFreqBand, &stOrigFreqBand);

        /* 写NV:en_NV_Item_User_Set_Freqbands,更新全局变量 */
        TAF_MMA_UpdateUserSetFreqBand();

        /* 写NV:en_NV_Item_Support_Freqbands,更新全局变量 */
        TAF_MMA_UpdateSupportFreqBand(&stOrigFreqBand);
    }

}
/*****************************************************************************
 函 数 名  : MMA_UpdateForbBandStatusToNV
 功能描述  : 将ForbBand的NV的状态更新为VOS_TRUE
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月23日
    作    者   : likelai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MMA_UpdateForbBandStatusToNV(VOS_VOID)
{
    VOS_UINT32                           ulRslt;

    gstMmaForbBand.ucForbStatus = VOS_TRUE;

    ulRslt = MMA_WriteValue2Nvim(en_NV_Item_Forbidden_Band,
                   &gstMmaForbBand,
                   sizeof(gstMmaForbBand.ucActiveFlag)+sizeof(gstMmaForbBand.ucForbStatus));

    if (MMA_SUCCESS != ulRslt)
    {
        MMA_WARNINGLOG("MMA_UpdateForbBandStatusToNV():WARNING:NVIM_Write en_NV_Item_Forbbiden_Band failed");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateUeAllowedBandRange
 功能描述  : 获取UE当前能够设置的频段范围
 输入参数  : VOS_VOIS
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月23日
    作    者   : likelai
    修改内容   : 新生成函数
  2.日    期   : 2010年7月20日
    作    者   : z00161729
    修改内容   : V7R1 phase II 支持syscfgex修改
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateUeAllowedBandRange(VOS_VOID)
{
    /* 频段相关的NV操作:
    1.读en_NV_Item_WG_RF_MAIN_BAND
    2.读en_NV_Item_Forbidden_Band
    3.读en_NV_Item_EUTRA_CAPA_COMM_INFO
    4.读en_NV_Item_Support_Freqbands
    5.写en_NV_Item_User_Set_Freqbands，
      同时更新gstMmaValue.stLastSyscfgSet.stUserSetBand.uUserSetGuBand.ulPrefBand
    6.写en_NV_Item_Support_Freqbands
      同时更新gstMmaValue.stLastSyscfgSet.stUserSetBand.uUserSetUeFormatGuBand
    7.写en_NV_Item_Forbidden_Band
    8.读en_NV_Item_USER_SET_LTEBANDS
    */

    /* en_NV_Item_WG_RF_MAIN_BAND */
    /*获取硬件支持的频段范围*/
    TAF_MMA_ReadUeSupporttedGuBandNvim();

    /* en_NV_Item_Forbidden_Band */
    /*获取禁止频段的状态和范围*/
    TAF_MMA_ReadForbBandNvim();

#if (FEATURE_ON == FEATURE_LTE)
    /* en_NV_Item_EUTRA_CAPA_COMM_INFO */
    /* 获取配件支持的LTE的频段范围 */
    TAF_MMA_ReadNvimUeSupporttedLteBand();

    /* en_NV_Item_USER_SET_LTEBANDS */
    /* 获取用户设置的LTE的频段范围 */
    TAF_MMA_ReadUserSetLteBands();
#endif

    /* en_NV_Item_Support_Freqbands */
    TAF_MMA_ReadFreqBandNvim();

    /* 读取en_NV_Item_User_Set_Freqbands*/
    TAF_MMA_ReadUserSettedBandNvim();

    if (NV_ITEM_ACTIVE == gstMmaForbBand.ucActiveFlag)
    {
        /* 更新gstMmaBandCapa */
        TAF_MMA_UpdateBandCapa();
    }


    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ReadPlmnSelectionModeNvim
 功能描述  : 从NV项en_NV_Item_SelPlmn_Mode中获取搜网模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID TAF_MMA_ReadPlmnSelectionModeNvim(VOS_VOID)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
    NAS_NVIM_SELPLMN_MODE_STRU          stPlmnSelMode;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_SelPlmn_Mode, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_SELPLMN_MODE_STRU))
    {
        return;
    }


    stPlmnSelMode.usSelPlmnMode = NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO;

    if (NV_OK != NV_Read(en_NV_Item_SelPlmn_Mode, &stPlmnSelMode, ulLength))
    {
        MMA_ERRORLOG("TAF_MMA_ReadPlmnSelectionModeNvim(): Read NV Fail");
        return;
    }

    if ((stPlmnSelMode.usSelPlmnMode != NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO)
     && (stPlmnSelMode.usSelPlmnMode != NAS_MSCC_PIF_PLMN_SEL_MODE_MANUAL))
    {
        MMA_ERRORLOG("TAF_MMA_ReadPlmnSelectionModeNvim(): ucPlmnSelMode is invalid");
        return;
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

    TAF_MMA_SetPlmnSelectionMode((VOS_UINT8)stPlmnSelMode.usSelPlmnMode);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadRatPrioListNvim
 功能描述  : 初始化接入技术
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月15日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，读取用户设置接入技术NV进行平台能力检查
*****************************************************************************/
VOS_VOID TAF_MMA_ReadRatPrioListNvim(VOS_VOID)
{
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList = VOS_NULL_PTR;

    /* 接入技术平衡特性未使能，接入技术从NV项en_NV_Item_RAT_PRIO_LIST中取 */
    if (VOS_TRUE != TAF_MMA_GetRatBalancingEnableFlg())
    {
        /* 获取当前的接入模式优先级 */
        pstRatPrioList = TAF_MMA_GetRatPrioListAddr();
        TAF_MMA_ReadNvimRatPrioList(pstRatPrioList);
        PS_MEM_CPY(&(gstMmaValue.pg_StatusContext->stRatPrioList),
                   pstRatPrioList, sizeof(TAF_MMA_RAT_ORDER_STRU));

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
        TAF_SDC_SetMsPrioRatList((TAF_SDC_RAT_PRIO_STRU *)pstRatPrioList);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */
    }
    /* 接入技术平衡特性使能，收到卡状态并且卡在位时，再从4F36文件中取 */
    else
    {
        MMA_NORMAILLOG("TAF_MMA_InitRatPrioList(): WAIT FOR READING 4F36.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadMsClassNvim
 功能描述  : 读取手机模式NV
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年4月9日
    作    者   : h00313353
    修改内容   : SysCfg宏定义转为枚举
*****************************************************************************/
VOS_VOID TAF_MMA_ReadMsClassNvim(VOS_VOID)
{
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    VOS_UINT32                          ulLength;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;

    PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));
    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();
    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_MsClass, &ulLength);
    if (NV_OK != NV_Read(en_NV_Item_MMA_MsClass,
                         &stMsClass,
                         ulLength))
    {
        pstLastSyscfgSet->enSrvDomain = TAF_MMA_SERVICE_DOMAIN_CS_PS;
    }
    else
    {
        pstLastSyscfgSet->enSrvDomain = stMsClass.ucMsClass;
    }

    MMA_ChangeSrv2Class(pstLastSyscfgSet->enSrvDomain, &gstMmaValue.stSetMsClass.MsClassType);

    gstMmaValue.stSetMsClass.NewMsClassType             = gstMmaValue.stSetMsClass.MsClassType;
    /*同步该参数位于STA子模块中的值*/
    gstMmaValue.pg_StatusContext->ucModeService         = gstMmaValue.stSetMsClass.MsClassType;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadRoamCapaNvim
 功能描述  : 读取漫游能力NV
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadRoamCapaNvim(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;

    PS_MEM_SET(&stRoamFeature, 0x00, sizeof(stRoamFeature));
    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();
    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Capa, &ulLength);

    if ( NV_OK != NV_Read(en_NV_Item_Roam_Capa,
                          &stRoamFeature,
                          ulLength))
    {
        MMA_WARNINGLOG("TAF_MMA_ReadRoamCapaNvim():Read en_NV_Item_Roam_Capa Failed!");
        stRoamFeature.ucRoamFeatureFlg = NAS_MSCC_PIF_ROAM_FEATURE_OFF;
        stRoamFeature.ucRoamCapability = NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF;
    }
    else
    {
        if (stRoamFeature.ucRoamFeatureFlg >= NAS_MSCC_PIF_ROAM_FEATURE_BUTT)
        {
            stRoamFeature.ucRoamFeatureFlg = NAS_MSCC_PIF_ROAM_FEATURE_OFF;
        }
        if (stRoamFeature.ucRoamCapability >= NAS_MSCC_PIF_ROAM_BUTT)
        {
            stRoamFeature.ucRoamCapability = NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF;
        }
    }

    gstMmaValue.ucRoamFeatureStatus = stRoamFeature.ucRoamFeatureFlg;
    pstLastSyscfgSet->enRoam        = stRoamFeature.ucRoamCapability;
    return;
}

/*****************************************************************************
 函 数 名  : MN_MMA_ReadRoamingBrokerInfoNvim
 功能描述  : 从NV中读取RoamingBroker的使能标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : L00171473
   修改内容   : 新生成函数
  2.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID TAF_MMA_ReadRoamingBrokerInfoNvim(VOS_VOID)
{
    NAS_MMA_NVIM_ROAMING_BROKER_STRU    stRoamingBroker;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stRoamingBroker, 0, sizeof(NAS_MMA_NVIM_ROAMING_BROKER_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_Roaming_Broker, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_Roaming_Broker, &stRoamingBroker, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadRoamingBrokerInfoNvim: Read NV Fail ");
        gstMmaValue.ucRoamBrokerSwitch = VOS_FALSE;
    }
    else
    {
        gstMmaValue.ucRoamBrokerSwitch = (stRoamingBroker.aucRoamingBroker)[0];

        /* 如果NV中的值无效，则设置RoamBroker功能关闭 */
        if ( (VOS_FALSE != (stRoamingBroker.aucRoamingBroker)[0]) && (VOS_TRUE != (stRoamingBroker.aucRoamingBroker)[0]) )
        {
            gstMmaValue.ucRoamBrokerSwitch = VOS_FALSE;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadReportPlmnSupportFlgNvim
 功能描述  : 从NV中读取en_NV_Item_REPORT_PLMN_SUPPORT_FLAG
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID TAF_MMA_ReadReportPlmnSupportFlgNvim(VOS_VOID)
{
    TAF_MMA_NVIM_REPORT_PLMN_SUPPORT_FLG_STRU   stReportPlmn;
    VOS_UINT32                                  ulLength;


    PS_MEM_SET(&stReportPlmn, 0x00, sizeof(stReportPlmn));
    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_REPORT_PLMN_SUPPORT_FLAG, &ulLength);

    if (ulLength > sizeof(TAF_MMA_NVIM_REPORT_PLMN_SUPPORT_FLG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_ReadNvimReportPlmnSupportFlg():WARNING: en_NV_Item_REPORT_PLMN_SUPPORT_FLAG length Error");
        gstMmaValue.ucReportPlmnFlg = VOS_FALSE;
        return;
    }

    if (NV_OK != NV_Read (en_NV_Item_REPORT_PLMN_SUPPORT_FLAG, &stReportPlmn, ulLength))
    {
        gstMmaValue.ucReportPlmnFlg = VOS_FALSE;
        return;
    }

    if ((VOS_TRUE  != stReportPlmn.ucNvimActiveFlg)
     && (VOS_FALSE != stReportPlmn.ucNvimActiveFlg))
    {
        gstMmaValue.ucReportPlmnFlg = VOS_FALSE;
        return;
    }

    /* 将NV值赋值到全局变量 */
    gstMmaValue.ucReportPlmnFlg = stReportPlmn.ucNvimActiveFlg;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadAccessModeNvim
 功能描述  : 读取接入模式NV
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadAccessModeNvim(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    NAS_MMA_NVIM_ACCESS_MODE_STRU       stAccessMode;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;

    PS_MEM_SET(&stAccessMode, 0x00, sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU));
    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();
    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_AccessMode, &ulLength);
    if (ulLength > sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_MMA_AccessMode ,
                         &stAccessMode,
                         ulLength))

    {
        MN_WARN_LOG("TAF_MMA_ReadAccessModeNvim:Read:NV_Read runs failed");
        return ;
    }
    pstLastSyscfgSet->enPrioRat = (stAccessMode.aucAccessMode)[1];
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadFollowonOpenSpeedFlagNvim
 功能描述  : 从NV中读取快速开机标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadFollowonOpenSpeedFlagNvim(VOS_VOID)
{
    VOS_UINT32                              ulLength;
    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU   stQuickStartFlg;

    PS_MEM_SET(&stQuickStartFlg, 0x00, sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU));
    ulLength = sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU);

    if (NV_OK != NV_Read(en_NV_Item_FollowOn_OpenSpeed_Flag,
                          (VOS_VOID*)(&(stQuickStartFlg.ulQuickStartSta)),
                          ulLength))
    {
       gstMmaValue.ulQuickStartFlg = MMA_QUICK_START_DISABLE;

       return;
    }

    gstMmaValue.ulQuickStartFlg = stQuickStartFlg.ulQuickStartSta;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadRfAutoTestFlagNvim
 功能描述  : 从NV中读取上电自动开机标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadRfAutoTestFlagNvim(VOS_VOID)
{
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulAutoSwitchOnFlg;

    ulAutoSwitchOnFlg   = MMA_RF_AUTO_TEST_DISABLE;
    ulDataLen           = sizeof(VOS_UINT16);

    if (NV_OK != NV_Read(en_NV_Item_RF_Auto_Test_Flag,
                          (VOS_VOID*)(&(ulAutoSwitchOnFlg)),
                           ulDataLen))
    {
       TAF_MMA_SetAutoSwitchOnFlg(MMA_RF_AUTO_TEST_ENABLE);

       return;
    }

    TAF_MMA_SetAutoSwitchOnFlg(ulAutoSwitchOnFlg);

#if 0
#ifdef NAS_STUB
    TAF_MMA_SetAutoSwitchOnFlg(MMA_RF_AUTO_TEST_DISABLE);
#endif
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadEFustServiceCfgNvim
 功能描述  : 从en_NV_Item_EFust_Service_Cfg NV中获取GSM是否禁止接入信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadEFustServiceCfgNvim(VOS_VOID)
{
    VOS_UINT32                          ulDataLen;

    ulDataLen = sizeof(MMA_EFUST_SERVICE_CFG_STRU);

    if (NV_OK != NV_Read(en_NV_Item_EFust_Service_Cfg,
                          (VOS_VOID*)(&(gstMmaValue.stEfustServiceCfg)),
                           ulDataLen))
    {
         /*打印未成功初始化值，原值保留*/
        MMA_WARNINGLOG("TAF_MMA_ReadEFustServiceCfgNvim():Read EFust_Service_Cfg Failed!");
    }

    if (NV_ITEM_DEACTIVE == gstMmaValue.stEfustServiceCfg.ucEnableFlag)
    {
        gstMmaValue.stEfustServiceCfg.ucForbidSndMsg = 0;
        gstMmaValue.stEfustServiceCfg.ucForbidReg2GNetWork = 0;
    }

    return;
}

/* TAF_MMA_ReadDisplaySpnFlagNvim*/


/*****************************************************************************
 函 数 名  : TAF_MMA_ReadNotDisplayLocalNetworkNameNvim
 功能描述  : 从NV中获取用户配置的是否显示本地的全球运营商信息标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadNotDisplayLocalNetworkNameNvim(VOS_VOID)
{
    VOS_UINT32                                              ulLength;
    TAF_MMA_NOT_DISPLAY_LOCAL_NETWORKNAME_NVIM_STRU         stNotDisplayLocalNetworkNameStru;

    ulLength = 0;

    PS_MEM_SET(&stNotDisplayLocalNetworkNameStru, 0x00, sizeof(TAF_MMA_NOT_DISPLAY_LOCAL_NETWORKNAME_NVIM_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_NotDisplayLocalNetworkName, &ulLength);

    /* 从NV中获取用户配置的是否显示本地的全球运营商信息标志 */
    if (NV_OK == NV_Read(en_NV_Item_NotDisplayLocalNetworkName,
                         &stNotDisplayLocalNetworkNameStru,
                         ulLength))
    {
       gstMmaValue.ucNotDisplayLocalNetworkNameFlg = stNotDisplayLocalNetworkNameStru.ucNotDisplayLocalNetworkNameFlg;
    }


    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadSystemAppCofigNvim
 功能描述  : 读取en_NV_Item_System_APP_Config，获取对接的上层应用
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadSystemAppCofigNvim(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSysAppConfig;

    ulLength = 0;
    PS_MEM_SET(&stSysAppConfig, 0x00, sizeof(NAS_NVIM_SYSTEM_APP_CONFIG_STRU));

    /* 读取en_NV_Item_System_APP_Config，获取对接的上层应用 */
    (VOS_VOID)NV_GetLength(en_NV_Item_System_APP_Config, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_System_APP_Config,
                         &stSysAppConfig, ulLength))
    {
        stSysAppConfig.usSysAppConfigType = SYSTEM_APP_MP;
        MMA_WARNINGLOG("TAF_MMA_ReadSystemAppCofigNvim():Read en_NV_Item_System_APP_Config Failed!");
    }

    if ( SYSTEM_APP_ANDROID < stSysAppConfig.usSysAppConfigType)
    {
        g_usMmaAppConfigSupportType = SYSTEM_APP_MP;
        MMA_WARNINGLOG("TAF_MMA_ReadSystemAppCofigNvim():en_NV_Item_System_APP_Config error!");
    }
    else
    {
        g_usMmaAppConfigSupportType = stSysAppConfig.usSysAppConfigType;
    }


    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ReadImeiNvim
 功能描述  : 从NV中获取IMEI
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadImeiNvim(VOS_VOID)
{
    TAF_PH_MEINFO_STRU                 *pstMeInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucBuf[TAF_PH_IMEI_LEN + 1];
    VOS_UINT8                           ucCheckData;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          i;
    MODEM_ID_ENUM_UINT16                enModemId;

    ulDataLen   = TAF_PH_IMEI_LEN;
    ucCheckData = 0;
    pstMeInfo   = &(gstMmaValue.stMeInfo);
    PS_MEM_SET(aucBuf, 0x00, sizeof(aucBuf));

    /* 由PID获取MODEMID */
    enModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMA);

    /* 调用SC接口读取IMEI号码 */
    (VOS_VOID)SC_PERS_VerifyNvReadImei(enModemId, en_NV_Item_IMEI, aucBuf, NV_ITEM_IMEI_SIZE);

    for (i = 0; i < (TAF_PH_IMEI_LEN-2); i += 2)
    {
        ucCheckData += aucBuf[i]
                      +((aucBuf[i+1] + aucBuf[i+1])/10)
                      +((aucBuf[i+1] + aucBuf[i+1])%10);
    }

    ucCheckData = (10 - (ucCheckData%10))%10;

    MMA_ImeiBcd2Ascii((VOS_UINT8)ulDataLen, aucBuf, (pstMeInfo->ImeisV.aucImei));

    (pstMeInfo->ImeisV.aucImei)[TAF_PH_IMEI_LEN-2] = (VOS_UINT8)(ucCheckData + 0x30);
    (pstMeInfo->ImeisV.aucImei)[TAF_PH_IMEI_LEN-1] = 0;

    PS_MEM_CPY(g_MmaNewValue.aucImeiBcd, aucBuf, ulDataLen);

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-18, begin */
    PS_MEM_CPY(g_aucMmaImei, pstMeInfo->ImeisV.aucImei, TAF_PH_IMEI_LEN - 1);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-18, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadFmridNvim
 功能描述  : 从NV中获取厂商名字
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadFmridNvim(VOS_VOID)
{
    VOS_UINT32                          ulDataLen;
    TAF_PH_MEINFO_STRU                 *pstMeInfo = VOS_NULL_PTR;

    pstMeInfo = &(gstMmaValue.stMeInfo);
    ulDataLen = TAF_MAX_MFR_ID_LEN + 1;

    /*获取厂商名字*/
    if (NV_OK != NV_Read(en_NV_Item_FMRID,
                         pstMeInfo->FmrId.aucMfrId,
                         ulDataLen))
    {
        /*打印未成功初始化值，原值保留*/
        MMA_WARNINGLOG("TAF_MMA_ReadFmridNvim():Read FMRID Failed!");
    }


    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ReadProductNameNvim
 功能描述  : 从NV中获取产品名字
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadProductNameNvim(VOS_VOID)
{
    VOS_UINT32                          ulDataLen;
    TAF_PH_MEINFO_STRU                 *pstMeInfo = VOS_NULL_PTR;

    pstMeInfo = &(gstMmaValue.stMeInfo);
    ulDataLen = TAF_PH_PRODUCT_NAME_LEN + 1;

    /*获取产品名字*/
    if (NV_OK != NV_Read(en_NV_Item_ProductName,
                         pstMeInfo->ProductName.aucProductName,
                         ulDataLen))
    {
        /*打印未成功初始化值，原值保留*/
       MMA_WARNINGLOG("TAF_MMA_ReadProductNameNvim():Read ProductName Failed!");
    }


    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadAttEnsCustomNvim
 功能描述  : 从NV项en_NV_Item_Att_Ens_Ctrl_Para中读取是否支持网络技术平衡控制和接入技术平衡控制
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月14日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID TAF_MMA_ReadAttEnsCustomNvim(VOS_VOID)
{
    NVIM_ATT_ENS_CTRL_STRU              stNvAttEns;


    PS_MEM_SET(&stNvAttEns, 0x00, sizeof(stNvAttEns));

    /* 读NV项en_NV_Item_Att_Ens_Ctrl_Para失败 */
    if (NV_OK != NV_Read(en_NV_Item_Att_Ens_Ctrl_Para,
                         &stNvAttEns,
                         sizeof(NVIM_ATT_ENS_CTRL_STRU)))
    {
        MMA_ERRORLOG("TAF_MMA_ReadATTCustomNvim(): Read NV Fail");
        return;
    }

    /* 置网络选择菜单控制标识 */
    if (VOS_TRUE == stNvAttEns.ucNetSelMenuFlg)
    {
        TAF_MMA_SetNetworkSelectionMenuEnableFlg(VOS_TRUE);
    }

    /* 置接入技术平衡控制标识 */
    if (VOS_TRUE == stNvAttEns.ucRatBalancingFlg)
    {
        TAF_MMA_SetRatBalancingEnableFlg(VOS_TRUE);
    }

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_MMA_ReadLastTinInfoNvim
 功能描述  : 从NV中获取上一次的TIN信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_MMA_ReadLastTinInfoNvim(
    NAS_NVIM_TIN_INFO_STRU             *pstTinInfo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    (VOS_VOID)NV_GetLength(en_NV_Item_TIN_INFO, &ulLength);

    ulResult = NV_Read(en_NV_Item_TIN_INFO, pstTinInfo, sizeof(NAS_NVIM_TIN_INFO_STRU));

    if (NV_OK != ulResult)
    {
        return MMA_FAILURE;
    }

    return MMA_SUCCESS;
}

#endif

/*VOS_VOID TAF_MMA_ReadUeSupporttedCPHSFlagNvim(VOS_VOID)*/

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadDeactUsimWhenPoweroffNvim
 功能描述  : 开机上电读取en_NV_Item_DEACT_USIM_WHEN_POWEROFF项
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月3日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目修改

*****************************************************************************/
VOS_VOID TAF_MMA_ReadDeactUsimWhenPoweroffNvim(VOS_VOID)
{
    TAF_NVIM_DEACT_SIM_WHEN_POWEROFF_STRU                   stNvDeactSimWhenPoweroff;

    PS_MEM_SET(&stNvDeactSimWhenPoweroff, 0, sizeof(TAF_NVIM_DEACT_SIM_WHEN_POWEROFF_STRU));

    if (NV_OK != NV_Read(en_NV_Item_DEACT_USIM_WHEN_POWEROFF,
                         &stNvDeactSimWhenPoweroff,
                         sizeof(TAF_NVIM_DEACT_SIM_WHEN_POWEROFF_STRU)))
    {
        /* 读取NV项失败，默认该特性关闭 */
        g_ucMmaDeactSimWhenPoweroff = MMA_DEACT_SIM_WHEN_POWEROFF_DISABLE;

        return;
    }

    /* NV读取成功，若值为1，则特性打开，否则都认为特性关闭 */
    if (VOS_TRUE == stNvDeactSimWhenPoweroff.ucEnableFlag)
    {
        g_ucMmaDeactSimWhenPoweroff = MMA_DEACT_SIM_WHEN_POWEROFF_ENABLE;
    }
    else
    {
        g_ucMmaDeactSimWhenPoweroff = MMA_DEACT_SIM_WHEN_POWEROFF_DISABLE;
    }

    return;
}

/* TAF_MMA_ReadAlphanumericNameByPlmnIdNvim*/


/*****************************************************************************
 函 数 名  : TAF_MMA_ReadPsStartNvim
 功能描述  : 从NV中获取是否自动开机的消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月24日
    作    者   : luokaihui / l00167671
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012030105247,开机时NV项RfAutoTestCtrl不生效
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID  TAF_MMA_ReadPsStartNvim( VOS_VOID )
{
    NAS_MMA_NVIM_AUTO_START_STRU        stNvAutoStart;

    stNvAutoStart.ulAutoStart   = NAS_MMA_AUTOMATIC_START;

    if ( NV_OK != NV_Read(en_NV_Item_PS_START,
                          &stNvAutoStart,
                          sizeof(stNvAutoStart) ))
    {
        (VOS_VOID)vos_printf("read auto start nv fail\r\n");
    }

    if ((stNvAutoStart.ulAutoStart) > NAS_MMA_MANUAL_START)
    {
        TAF_MMA_SetAutoInitPsFlg(VOS_TRUE);
        return;
    }

    if (NAS_MMA_MANUAL_START == stNvAutoStart.ulAutoStart)
    {
        TAF_MMA_SetAutoInitPsFlg(VOS_FALSE);
    }
    else
    {
        TAF_MMA_SetAutoInitPsFlg(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadCardLockStatusNvim
 功能描述  : 从NV中获取是否锁卡的消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_ReadCardLockStatusNvim( VOS_VOID )
{
    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stCardLockStatus, 0x00, sizeof(stCardLockStatus));

    ulResult = NV_Read(en_NV_Item_CardlockStatus,
                       &stCardLockStatus,
                       (VOS_UINT32)(sizeof(stCardLockStatus)));

    if (NV_OK != ulResult)
    {
        MN_WARN_LOG("TAF_MMA_ReadCardLockStatusNvim:WARNING:  read sim lock status fail");
    }

    g_MmaNewValue.stCardLockStatus = stCardLockStatus;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadSimLockMaxTimesNvim
 功能描述  : 从NV中获取SIM卡被锁的最大次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_ReadSimLockMaxTimesNvim( VOS_VOID )
{
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU  stSimLockMaxTimes;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    PS_MEM_SET(&stSimLockMaxTimes, 0x00, sizeof(stSimLockMaxTimes));
    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_CustomizeSimLockMaxTimes, &ulLength);

    if (ulLength > sizeof(TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_ReadNvimCustomizeSimLockMaxTimes():WARNING: en_NV_Item_CustomizeSimLockMaxTimes length Error");
        g_MmaNewValue.stSimLockMaxTimes.ulStatus = VOS_FALSE;
        g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
        return;
    }

    ulResult = NV_Read(en_NV_Item_CustomizeSimLockMaxTimes,
                               &stSimLockMaxTimes,
                               sizeof(stSimLockMaxTimes));

    if (NV_OK != ulResult)
    {
        g_MmaNewValue.stSimLockMaxTimes.ulStatus        = VOS_FALSE;
        g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes  = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
    }
    else
    {
        if (VOS_FALSE == stSimLockMaxTimes.ulStatus)
        {
            g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
        }
        else
        {
            g_MmaNewValue.stSimLockMaxTimes = stSimLockMaxTimes;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadSimLockPlmnNvim
 功能描述  : 从NV中获取SIM卡锁网信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_ReadSimLockPlmnNvim( VOS_VOID )
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU          stSimLockPlmnInfo;
    VOS_UINT32                                  ulResult;

    PS_MEM_SET(&stSimLockPlmnInfo, 0x00, sizeof(stSimLockPlmnInfo));

    ulResult = NV_Read(en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo));
    if (NV_OK != ulResult)
    {
        g_MmaNewValue.stSimLockPlmnInfo.ulStatus = VOS_FALSE;
        PS_MEM_SET(g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange, (VOS_CHAR)0xaa,
                       sizeof(g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange));
    }
    else
    {
        g_MmaNewValue.stSimLockPlmnInfo = stSimLockPlmnInfo;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadLastImsiNvim
 功能描述  : 从NV中获取上一次的IMSI信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_MMA_ReadLastImsiNvim(
    NAS_MMC_NVIM_LAST_IMSI_STRU        *pstLastImsi
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Last_Imsi, &ulLength);

    ulResult = NV_Read(en_NV_Item_Last_Imsi, pstLastImsi, ulLength);

    if (NV_OK != ulResult)
    {
        return MMA_FAILURE;
    }

    return MMA_SUCCESS;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadSimPersonalisationPwdNvim
 功能描述  : 从NV中获取SIM中PWD信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadSimPersonalisationPwdNvim( VOS_VOID )
{
    VOS_UINT8                           aucPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(aucPwd, 0x00, sizeof(aucPwd));
    (VOS_VOID)NV_GetLength(en_NV_Item_Sim_Personalisation_Pwd, &ulLength);

    ulResult = NV_Read(en_NV_Item_Sim_Personalisation_Pwd,
                     aucPwd,
                     ulLength);

    if (NV_OK != ulResult)
    {
        return;
    }

    PS_MEM_CPY(g_MmaNewValue.aucPwd, aucPwd, TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);

    return;
}



/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_ReadLcCtrlNvim
 功能描述  : 从NV中获取LC互操作配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月15日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadLcCtrlNvim( VOS_VOID )
{
    TAF_SDC_LC_CONFIG_PARA_STRU        *pstLcConfigInfo = VOS_NULL_PTR;
    TAF_NV_LC_CTRL_PARA_STRU            stLcCtrlInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    ulLength        = 0;
    pstLcConfigInfo = TAF_SDC_GetLcConfigPara();

    PS_MEM_SET(&stLcCtrlInfo, 0x00, sizeof(TAF_NV_LC_CTRL_PARA_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_LC_Ctrl_PARA, &ulLength);

    ulResult = NV_Read(en_NV_Item_LC_Ctrl_PARA,
                       &stLcCtrlInfo,
                       ulLength);

    if (NV_OK != ulResult)
    {
        return;
    }

    /* NV 内容异常检测,如果内容异常，则不修改当前LC值 */
    if ( (VOS_TRUE                      != stLcCtrlInfo.ucLCEnableFlg)
      && (VOS_FALSE                     != stLcCtrlInfo.ucLCEnableFlg) )
    {
        return;
    }

    if ( (TAF_NVIM_LC_RAT_COMBINED_GUL  != stLcCtrlInfo.enRatCombined)
      && (TAF_NVIM_LC_RAT_COMBINED_CL   != stLcCtrlInfo.enRatCombined)
      && (TAF_NVIM_LC_RAT_COMBINED_BUTT != stLcCtrlInfo.enRatCombined))
    {
        return;
    }

    if ( (TAF_NVIM_LC_INDEPENT_WORK     != stLcCtrlInfo.enLCWorkCfg)
      && (TAF_NVIM_LC_INTER_WORK        != stLcCtrlInfo.enLCWorkCfg)
      && (TAF_NVIM_LC_WORK_CFG_BUTT     != stLcCtrlInfo.enLCWorkCfg) )
    {
        return;
    }

    pstLcConfigInfo->ucLCEnableFlg = stLcCtrlInfo.ucLCEnableFlg;
    pstLcConfigInfo->enRatCombined = stLcCtrlInfo.enRatCombined;
    pstLcConfigInfo->enLCWorkCfg   = stLcCtrlInfo.enLCWorkCfg;

    return;
}

/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */

/*****************************************************************************
 函 数 名  : TAF_MMA_WritePlmnSelectionModeNvim
 功能描述  : 写NV项: en_NV_Item_SelPlmn_Mode
 输入参数  : ucReselMode - 选网模式自动或手动
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年11月1日
    作    者   : z00161729
    修改内容   : DTS2013111103301:svlte需要关机状态支持cops设置，更新nv项搜网模式

*****************************************************************************/
VOS_VOID TAF_MMA_WritePlmnSelectionModeNvim(VOS_UINT8 ucReselMode)
{
    NAS_NVIM_SELPLMN_MODE_STRU          stPlmnSelMode;
    VOS_UINT32                          ulNvLength;

    ulNvLength                  = 0;
    stPlmnSelMode.usSelPlmnMode = ucReselMode;

    (VOS_VOID)NV_GetLength(en_NV_Item_SelPlmn_Mode, &ulNvLength);

    if (NV_OK != NV_Write(en_NV_Item_SelPlmn_Mode,
                      &stPlmnSelMode,
                      ulNvLength))
    {
        MN_WARN_LOG("TAF_MMA_WritePlmnSelectionModeNvim:WARNING:  read en_NV_Item_SelPlmn_Mode fail");
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMA_UpdateUESupportBandNvim
 功能描述  : 将写NV操作迁移到PID初始化之后
             更新NV 8229，PID初始化时将8229与10000取交集，写到8229中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月16日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2014年8月1日
    作    者   : b00269685
    修改内容   : nv拆分
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateUeBandNvim()
{
    TAF_USER_SET_PREF_BAND64            stOrigUserSetGuBand;
    VOS_UINT32                          ulBand;
    TAF_MMA_USER_BAND_SET_UN            uUserSetBand;
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stSetBand;
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stUeOrigSupportFreqBand;
    TAF_MMA_USER_BAND_SET_UN            uUeOrigSupportFreqBand;

    PS_MEM_SET(&stOrigUserSetGuBand, 0x00, sizeof(stOrigUserSetGuBand));
    PS_MEM_SET(&ulBand, 0x00, sizeof(ulBand));
    PS_MEM_SET(&uUserSetBand, 0x00, sizeof(uUserSetBand));
    PS_MEM_SET(&stSetBand, 0x00, sizeof(stSetBand));
    PS_MEM_SET(&stUeOrigSupportFreqBand, 0x00, sizeof(stUeOrigSupportFreqBand));
    PS_MEM_SET(&uUeOrigSupportFreqBand, 0x00, sizeof(uUeOrigSupportFreqBand));


    /* 读NV8265到stOrigUserSetGuBand中 */
    TAF_MMA_ReadUserSettedBandNvim();

    MN_MMA_Convert64BitBandTo32Bit(&(TAF_MMA_GetLastSyscfgSetAddr()->stUserSetBand.stOrigUserSetGuBand),
                                   &ulBand);

    MN_MMA_ConvertGUFrequencyBand(&ulBand);
    uUserSetBand.ulPrefBand = ulBand;

    /* 读NV8229到stUeOrigSupportFreqBand中 */
    TAF_MMA_ReadFreqBandNvim();

    /*将当前系统设置的频段转换为用户设置的格式*/
    MMA_SwitchUESupportBand2UserSetBand(TAF_MMA_GetLastSyscfgSetAddr()->stUserSetBand.uUserSetUeFormatGuBand,
                                        &uUeOrigSupportFreqBand);

    /* 如果用户设置频段、射频频段交集与NV 8229值相同，则直接返回不需要写NV */
    if (uUserSetBand.ulPrefBand != uUeOrigSupportFreqBand.ulPrefBand)
    {
        MMA_SwitchUserSetBand2UESupportBand(uUserSetBand, &stSetBand);

        /* 写NV:en_NV_Item_Support_Freqbands,更新全局变量 */
        TAF_MMA_UpdateSupportFreqBand(&stSetBand);
    }

    /*若ForbBandNV激活,进行频段检查和 更新NV项*/
    if (NV_ITEM_ACTIVE == gstMmaForbBand.ucActiveFlag)
    {
        if (VOS_FALSE == gstMmaForbBand.ucForbStatus)
        {
            /*根据禁止频段的信息更新FreqBandNV和UsersetBandNV*/
            MMA_UpdateBandNvRefForbBand();

            /*更新禁止频段的Status为TRUE 1*/
            MMA_UpdateForbBandStatusToNV();
        }
    }

    return;
}



#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateUserSetLteBands
 功能描述  : 将写NV操作迁移到PID初始化之后
             更新NV 9017，PID初始化时将9017与D22C取交集，写到9017中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月6日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateUserSetLteBands()
{
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;
    TAF_USER_SET_PREF_BAND64           *pstUserSetLteBand   = VOS_NULL_PTR;
    TAF_USER_SET_PREF_BAND64            stDestUserSetLteBand;

    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();
    pstUserSetLteBand   = TAF_MMA_GetUserSetLteBandAddr();

    /* 用户设置的NV取9017与NV:D22C中单板支持的频段交集 */
    stDestUserSetLteBand.ulBandLow  = (pstUeSupportLteBand->ulBandLow)  & (pstUserSetLteBand->ulBandLow);
    stDestUserSetLteBand.ulBandHigh = (pstUeSupportLteBand->ulBandHigh) & (pstUserSetLteBand->ulBandHigh);

    TAF_MMA_UpdateLteBandToNvim(&stDestUserSetLteBand, pstUserSetLteBand);

    return;
}

#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadCFreqLockNvim
 功能描述  : 读取1X/EVDO的锁频信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月27日
    作    者   : y00307564
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReadCFreqLockNvim(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstTafMmaCFreqLockPara;

    pstTafMmaCFreqLockPara = TAF_MMA_GetCFreqLockSetPara();

    ulResult = NV_Read(en_NV_Item_CFreqLock_CFG,
                       pstTafMmaCFreqLockPara,
                       sizeof(TAF_NVIM_CFREQ_LOCK_CFG_STRU));

    TAF_MMA_LogReadNVInfo(en_NV_Item_CFreqLock_CFG,
                          sizeof(TAF_NVIM_CFREQ_LOCK_CFG_STRU),
                          WUEPS_PID_MMA,
                          (VOS_UINT8 *)pstTafMmaCFreqLockPara);

    if (NV_OK != ulResult)
    {
        /* 读取NV失败，按不锁频处理 */
        PS_MEM_SET(pstTafMmaCFreqLockPara, 0x0, sizeof(TAF_NVIM_CFREQ_LOCK_CFG_STRU));
        pstTafMmaCFreqLockPara->enFreqLockMode = TAF_MMA_CFREQ_LOCK_MODE_OFF;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadCcpuResetRecordNvim
 功能描述  : 读取C核单独复位标记的NV项(en_NV_Item_Ccpu_Reset_Record)
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ReadCcpuResetRecordNvim(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    TAF_NVIM_CCPU_RESET_RECORD_STRU     stCcpuResetRecord;

    ulLength = 0;
    PS_MEM_SET(&stCcpuResetRecord, 0x00, sizeof(TAF_NVIM_CCPU_RESET_RECORD_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Ccpu_Reset_Record, &ulLength);
    if (ulLength > sizeof(TAF_NVIM_CCPU_RESET_RECORD_STRU))
    {
        return;
    }

    /* NV读取失败，则按默认值处理 */
    if (NV_OK != NV_Read(en_NV_Item_Ccpu_Reset_Record, &stCcpuResetRecord, ulLength))
    {
        MMA_WARNINGLOG("TAF_MMA_ReadCcpuResetRecordNvim():WARNING:NV Read failed.");

        return;
    }

    if (VOS_TRUE == stCcpuResetRecord.ucCcpuResetFlag)
    {
        NAS_TRACE_HIGH("Ccpu Reseting! ");

        TAF_MMA_SetCcpuResetFlag(VOS_TRUE);
    }

    if (0 == stCcpuResetRecord.ucReserved1)
    {
        TAF_MMA_SetTestRoamFlag(VOS_FALSE);
    }
    else
    {
        TAF_MMA_SetTestRoamFlag(VOS_TRUE);

        if (0 != stCcpuResetRecord.ucReserved2)
        {
            TAF_MMA_SetWaitExtTimerLen(stCcpuResetRecord.ucReserved2);
        }
    }


    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadGetGeoCfgInfoNvim
 功能描述  : 读取获取国家码的配置信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月30日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ReadGetGeoCfgInfoNvim(VOS_VOID)
{
    TAF_MMA_GET_GEO_CTX_STRU                               *pstGetGeoCtx = VOS_NULL_PTR;
    NAS_NVIM_GET_GEO_CFG_INFO_STRU                          stGetGeoCfgInfo;
    VOS_UINT32                                              ulLength;

    ulLength     = 0;
    pstGetGeoCtx = TAF_MMA_GetGeoCtxAddr();
    PS_MEM_SET(&stGetGeoCfgInfo, 0x00, sizeof(NAS_NVIM_GET_GEO_CFG_INFO_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Get_Geo_Cfg_Info, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_GET_GEO_CFG_INFO_STRU))
    {
        return;
    }

    /* 读取获取国家码配置信息的NV */
    if (NV_OK != NV_Read(en_NV_Item_Get_Geo_Cfg_Info, &stGetGeoCfgInfo, ulLength))
    {
        return;
    }

    /* 如果该功能关闭，则都按默认值处理 */
    if (VOS_TRUE != stGetGeoCfgInfo.ucActiveFlag)
    {
        return;
    }

    /* AUSTIN C10虚拟卡则不开启GET GEO功能:CSS没有实现DSDS,会抢占RF，导致底层RF异常 */
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag = VOS_FALSE;
        MMA_WARNINGLOG("TAF_MMA_ReadGetGeoCfgInfoNvim: Is virtual sim!");

        return;
    }

    pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag = VOS_TRUE;

    /* 如果NV配置的时长为0，则按默认值处理 */
    /* NV配置的获取国家码定时器时长单位是秒，全局变量存的获取国家码定时器时长单位是毫秒 */
    if (0 != stGetGeoCfgInfo.ucGetGeoTimerlen)
    {
        /* 秒转换成毫秒后，存入全局变量 */
        pstGetGeoCtx->stGetGeoNvCfg.ulGetGeoTimerLen = stGetGeoCfgInfo.ucGetGeoTimerlen * NAS_SDC_ONE_THOUSAND_MILLISECOND;
    }

    /* 如果NV配置的时长为0，则按默认值处理 */
    /* NV配置的国家码有效时长单位是分钟，全局变量存的国家码有效时长单位是秒 */
    if (0 != stGetGeoCfgInfo.ulGeoEffectiveTimeLen)
    {
        /* 分钟转换成秒后，存入全局变量 */
        pstGetGeoCtx->stGetGeoNvCfg.ulGeoEffectiveTimeLen = stGetGeoCfgInfo.ulGeoEffectiveTimeLen * NAS_MML_SIXTY_SECOND;
    }

    return;
}


#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_MMA_UpdataVoiceDomainNv
 功能描述  : 更新语音优选域的NV
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : IMS动态开关配置项目
*****************************************************************************/
VOS_UINT32 TAF_MMA_UpdataVoiceDomainNv(
    VOS_UINT32                          ulVoiceDomain
)
{
    VOS_UINT32                          ulLength;
    LNAS_LMM_NV_VOICE_DOMAIN_STRU       stVoiceDomain;

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_UE_VOICE_DOMAIN, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_VOICE_DOMAIN_STRU))
    {
        return VOS_FALSE;
    }

    /* 读NV项EN_NV_ID_UE_VOICE_DOMAIN，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_UE_VOICE_DOMAIN,
                         &stVoiceDomain, ulLength))
    {
        return VOS_FALSE;
    }

    stVoiceDomain.enVoicDomain  = (NAS_LMM_VOICE_DOMAIN_ENUM_UINT32)ulVoiceDomain;

    if (NV_OK != NV_Write(EN_NV_ID_UE_VOICE_DOMAIN,
                          &stVoiceDomain, ulLength))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateLteImsSupportNv
 功能描述  : 更新LTE IMS使能NV
 输入参数  : ucFlag 标识
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月04日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_UpdateLteImsSupportNv(
    VOS_UINT8                           ucFlag
)
{
    VOS_UINT32                          ulLength;
    IMSA_NV_IMS_RAT_SUPPORT_STRU        stImsSupport;

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_IMS_RAT_SUPPORT, &ulLength);

    if (ulLength > sizeof(IMSA_NV_IMS_RAT_SUPPORT_STRU))
    {
        return VOS_FALSE;
    }

    /* 读NV项EN_NV_ID_IMS_RAT_SUPPORT，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_RAT_SUPPORT,
                         &stImsSupport, ulLength))
    {
        return VOS_FALSE;
    }

    stImsSupport.ucLteImsSupportFlag    = ucFlag;
    stImsSupport.ucLteEmsSupportFlag    = ucFlag;

    if (NV_OK != NV_Write(EN_NV_ID_IMS_RAT_SUPPORT,
                          &stImsSupport, ulLength))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadPlatformRatCap
 功能描述  : 初始化平台接入技术能力
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月23日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID TAF_MMA_ReadPlatformRatCap(VOS_VOID)
{
    TAF_SDC_PLATFORM_RAT_CAP_STRU                          *pstPlatformRatCap = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    PLATAFORM_RAT_CAPABILITY_STRU                           stNvPlatformRatCap;
    TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8                    enTafSdcPlatformRat;

    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 初始化为CDMA 1X + GSM ONLY */
    pstPlatformRatCap->ucRatNum      = 2;
    pstPlatformRatCap->aenRatList[0] = TAF_SDC_PLATFORM_RAT_1X;
    pstPlatformRatCap->aenRatList[1] = TAF_SDC_PLATFORM_RAT_GSM;
    for (i = 2; i < TAF_SDC_PLATFORM_MAX_RAT_NUM; i++)
    {
        pstPlatformRatCap->aenRatList[i] = TAF_SDC_PLATFORM_RAT_BUTT;
    }
#else
    /* 初始化为GSM ONLY */
    pstPlatformRatCap->ucRatNum      = 1;
    pstPlatformRatCap->aenRatList[0] = TAF_SDC_PLATFORM_RAT_GSM;
    for (i = 1; i < TAF_SDC_PLATFORM_MAX_RAT_NUM; i++)
    {
        pstPlatformRatCap->aenRatList[i] = TAF_SDC_PLATFORM_RAT_BUTT;
    }
#endif

    /* 读取NV, 如果读取失败，直接返回，默认值保留为仅支持GSM */
    PS_MEM_SET(&stNvPlatformRatCap, 0x0, sizeof(stNvPlatformRatCap));
    if (NV_OK != NV_Read(en_NV_Item_Platform_RAT_CAP,
                         &stNvPlatformRatCap, sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMC, "TAF_MMA_ReadPlatformRatCap():ERROR: read en_NV_Item_PLATFORM_RAT_CAP Error");

        return;
    }

    if (stNvPlatformRatCap.usRatNum >= PLATFORM_MAX_RAT_NUM)
    {
        stNvPlatformRatCap.usRatNum = PLATFORM_MAX_RAT_NUM;
    }

    /* 有效性检查：无效，直接返回，默认值保留为仅支持GSM */
    if (VOS_FALSE == TAF_SDC_IsPlatformRatCapNvimValid(&stNvPlatformRatCap))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMC, "TAF_MMA_ReadPlatformRatCap():ERROR: en_NV_Item_PLATFORM_RAT_CAP Invalid");

        return;
    }

    j = 0;

    /* 读取成功，将NV中读取值赋值到pstPlatformRatCap */
    for (i = 0; i < stNvPlatformRatCap.usRatNum; i++)
    {
        enTafSdcPlatformRat = TAF_SDC_ConvertNvPlatformRatToTafType(stNvPlatformRatCap.aenRatList[i]);
        if (TAF_SDC_PLATFORM_RAT_BUTT != enTafSdcPlatformRat)
        {
            pstPlatformRatCap->aenRatList[j] = enTafSdcPlatformRat;
            j ++;
        }
    }

    /* 如果有从NV中获取平台支持接入技术，需要更新支持的个数，否则不更新，仍然按照初始值1 */
    if (j > 0)
    {
        pstPlatformRatCap->ucRatNum      = (VOS_UINT8)j;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadDelayReportServiceStatusCfgNvim
 功能描述  : 从NV中获取短暂掉网显示优化的配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
VOS_VOID TAF_MMA_ReadDelayReportServiceStatusCfgNvim(VOS_VOID)
{
    TAF_MMA_NVIM_DELAY_REPORT_SERVICE_STATUS_STRU                 stDelayReportServiceStatusCfg;

    PS_MEM_SET(&stDelayReportServiceStatusCfg, 0x00, sizeof(TAF_MMA_NVIM_DELAY_REPORT_SERVICE_STATUS_STRU));

    TAF_MMA_SetDelayReportServiceStatusFlg(VOS_FALSE);
    TAF_MMA_SetDelayReportServiceStatusTimerLen(0);

    if (NV_OK != NV_Read(en_NV_Item_DELAY_REPORT_SERVICE_STATUS_CFG,
                        (VOS_VOID *)&stDelayReportServiceStatusCfg,
                        sizeof(TAF_MMA_NVIM_DELAY_REPORT_SERVICE_STATUS_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_ReadDelayReportServiceStatusCfgNvim: return error");
        return;
    }

    if (VOS_TRUE == stDelayReportServiceStatusCfg.ucEnable)
    {
        TAF_MMA_SetDelayReportServiceStatusFlg(VOS_TRUE);
        TAF_MMA_SetDelayReportServiceStatusTimerLen(stDelayReportServiceStatusCfg.ulRptSrvStaDelayTimerValue*NAS_SDC_ONE_THOUSAND_MILLISECOND);
        return;
    }
    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ReadUserCfgExtEhplmnInfoNvim
 功能描述  : 读取NV en_NV_Item_User_Cfg_Ehplmn_Info
 输入参数  : NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU             *pstNvimCfgExtEhplmnInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ReadUserCfgExtEhplmnInfoNvim(
    NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU             *pstNvimCfgExtEhplmnInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulNvimEhplmnNum;
    TAF_SDC_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    TAF_SDC_PLMN_ID_STRU                                    stPlmn;
    NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU              stNvimCfgExtEhplmnInfo;

    PS_MEM_SET(&stNvimCfgExtEhplmnInfo, 0x00, sizeof(stNvimCfgExtEhplmnInfo));

    /*循环变量初始化*/
    ulNvimEhplmnNum = 0;

    if (NV_OK != NV_Read( en_NV_Item_User_Cfg_Ext_Ehplmn_Info,
                            &stNvimCfgExtEhplmnInfo, sizeof(NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadUserCfgExtEhplmnInfoNvim:Read NV Failed");
        return;
    }

    ulNvimEhplmnNum = stNvimCfgExtEhplmnInfo.ulNvimEhplmnNum;

    if (ulNvimEhplmnNum > NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM)
    {
        ulNvimEhplmnNum = NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM;
    }

    pstNvimCfgExtEhplmnInfo->ulNvimEhplmnNum    = ulNvimEhplmnNum;

    for (j = 0; j < ulNvimEhplmnNum; j++)
    {

        /* 读取NV中的IMSI信息 */

        /* 初始化内存中存放PLMN网络列表个数 */
        pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucImsiPlmnListNum = 0;

        /* 防止数组越界 */
        if (stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucImsiPlmnListNum > NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM)
        {
            stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucImsiPlmnListNum = NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM;
        }

        for (i = 0; i < stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucImsiPlmnListNum; i++)
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].astImsiPlmnList[i].aucSimPlmn, TAF_SDC_SIM_FORMAT_PLMN_LEN);
            TAF_SDC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

            if (VOS_TRUE == TAF_SDC_IsPlmnIdValid(&stPlmn))
            {
                PS_MEM_CPY(pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].astImsiPlmnList[pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucImsiPlmnListNum].aucSimPlmn,
                           stSimPlmn.aucSimPlmn,
                           TAF_SDC_SIM_FORMAT_PLMN_LEN);
                pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucImsiPlmnListNum++;
            }
        }


        /* 读取NV中的EHplmn信息 */

        /* 初始化内存中存放PLMN网络列表个数 */
        pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucEhplmnListNum   = 0;

        /* 防止数组越界 */
        if (stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucEhplmnListNum > NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM)
        {
            stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucEhplmnListNum = NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM;
        }

        for (i = 0; i < stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucEhplmnListNum; i++)
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].astEhPlmnList[i].aucSimPlmn, TAF_SDC_SIM_FORMAT_PLMN_LEN);
            TAF_SDC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

            if (VOS_TRUE == TAF_SDC_IsPlmnIdValid(&stPlmn))
            {
                PS_MEM_CPY(pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].astEhPlmnList[pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucEhplmnListNum].aucSimPlmn,
                           stSimPlmn.aucSimPlmn,
                           TAF_SDC_SIM_FORMAT_PLMN_LEN);
                pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucEhplmnListNum++;
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadDplmnNplmnCfgNvim
 功能描述  : 读en_NV_Item_Dplmn_Nplmn_Cfg
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : 新生成函数
  2.日    期   : 2015年12月2日
    作    者   : s00217060
    修改内容   : DTS2015070103821修改:coverity

*****************************************************************************/
VOS_VOID TAF_MMA_ReadDplmnNplmnCfgNvim(
    NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU                      *pstNvimDPlmnNPlmnCfg
)
{
    VOS_UINT32                                              ulLen;

    /* 读en_NV_Item_Dplmn_Nplmn_Cfg */
    PS_MEM_SET(pstNvimDPlmnNPlmnCfg, 0x00, sizeof(NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU));
    ulLen       = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Dplmn_Nplmn_Cfg, &ulLen);

    if (ulLen > sizeof(NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "ERROR:TAF_MMA_ReadDplmnNplmnCfgNvim : read en_NV_Item_Dplmn_Nplmn_Cfg len error");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Dplmn_Nplmn_Cfg, pstNvimDPlmnNPlmnCfg, ulLen))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "ERROR:TAF_MMA_ReadDplmnNplmnCfgNvim : read en_NV_Item_Dplmn_Nplmn_Cfg Failed");
        return;
    }

    return;
}



#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadEsnFromNvim
 功能描述  : 可维可测读取nv上报 esn信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月22日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ReadEsnFromNvim( VOS_VOID )
{
    VOS_INT32                           lIndex;
    NV_PESN_STRU                        stPesn;

    if (NV_OK != NV_Read(en_NV_Item_PESN, &stPesn, sizeof(NV_PESN_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadEsnAndMeidNvim:Read Nvim Failed");
        return;
    }

    if (VOS_FALSE == TAF_MMA_IsPesnValid(&stPesn))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadEsnAndMeidNvim: read Nvim succ, but nvim is invalid");
        return;
    }

    TAF_MMA_LogReadNVInfo(en_NV_Item_PESN,
                          sizeof(NV_PESN_STRU),
                          WUEPS_PID_MMA,
                          (VOS_UINT8 *)&stPesn);

    PS_MEM_SET(&(TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.ulEsn), 0x00, sizeof(VOS_UINT32));

    /* Read from high to low */
    for (lIndex = (PESN_NV_DATA_LEN - 1); lIndex >= 0; lIndex--)
    {
        /* Update the current value */
        TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.ulEsn <<= sizeof(stPesn.aucPEsn[0]) * 8;

        /* Add lower bits */
        TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.ulEsn |= stPesn.aucPEsn[lIndex];
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadMeidFromNvim
 功能描述  : 可维可测读取nv上报 meid信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月22日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ReadMeidFromNvim( VOS_VOID )
{
    NV_MEID_STRU                        stMeid;

    if (NV_OK != NV_Read(en_NV_Item_MEID, &stMeid, sizeof(NV_MEID_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadEsnAndMeidNvim:Read Nvim Failed");
        return;
    }

    if (VOS_FALSE == TAF_MMA_IsMeidValid(&stMeid))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadEsnAndMeidNvim: read Nvim succ, but nvim is invalid");
        return;
    }

    TAF_MMA_LogReadNVInfo(en_NV_Item_MEID,
                          sizeof(NV_MEID_STRU),
                          WUEPS_PID_MMA,
                          (VOS_UINT8 *)&stMeid);

    PS_MEM_CPY(TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.aucMeId, stMeid.aucMeID, MEID_NV_DATA_LEN_NEW);
}

#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim
 功能描述  : 从NV读取非正常服务上报注册状态改变配置
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月28日
    作    者   : z00359541
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim( VOS_VOID )
{
    TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU            *pstNonnormalRegStatusMergeCfg = VOS_NULL_PTR;
    TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU            stNonnormalRegStatusMergeCfg;

    pstNonnormalRegStatusMergeCfg = TAF_SDC_GetNonnormalRegStatusMergeCfg();

    PS_MEM_SET(&stNonnormalRegStatusMergeCfg, 0X00, sizeof(TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU));

    /* 测试卡不生效 */
    if (VOS_TRUE  == NAS_USIMMAPI_IsTestCard())
    {
        TAF_NORMAL_LOG(WUEPS_PID_MMC, "TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim():Test SIM, Config Invalid");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_NONNORMAL_REG_STATUS_MERGE_CFG, &stNonnormalRegStatusMergeCfg, sizeof(TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim:Read Nvim Failed");
        return;
    }

    TAF_MMA_LogReadNVInfo(en_NV_Item_NONNORMAL_REG_STATUS_MERGE_CFG,
                          sizeof(TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU),
                          WUEPS_PID_MMA,
                          (VOS_UINT8 *)&stNonnormalRegStatusMergeCfg);

    if (VOS_FALSE == stNonnormalRegStatusMergeCfg.ucMergeFlg)
    {
        pstNonnormalRegStatusMergeCfg->ucMergeFlg = VOS_FALSE;

        TAF_NORMAL_LOG(WUEPS_PID_MMC, "TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim():ucMergeFlg = false");
        return;
    }

    pstNonnormalRegStatusMergeCfg->ucMergeFlg = VOS_TRUE;
    TAF_NORMAL_LOG(WUEPS_PID_MMC, "TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim():ucMergeFlg = true");

    return;
}
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_MMA_ReadDelaySndCLServiceStatusTimeLenNvim
 功能描述  : 从NV中获取CL服务状态延迟上报时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : h00313353
    修改内容   : DTS2016010508602
*****************************************************************************/
VOS_VOID TAF_MMA_ReadDelaySndCLServiceStatusTimeLenNvim(
    VOS_VOID
)
{
    TAF_MMA_NVIM_DELAY_RPT_CLNOSERVICE_STRU                 stDelayCLSrvStatusLen;
    TAF_MMA_CL_NO_SERVICE_DELAY_RPT_STRU                   *pstClNoServiceDelayRpt  = VOS_NULL_PTR;

    pstClNoServiceDelayRpt              = TAF_MMA_GetCLNoServiceDelayRptInfo();
    PS_MEM_SET(&stDelayCLSrvStatusLen, 0x00, sizeof(TAF_MMA_NVIM_DELAY_RPT_CLNOSERVICE_STRU));

    if (NV_OK != NV_Read(en_NV_Item_CL_NO_SERVICE_DELAY_RPT_CFG,
                         &stDelayCLSrvStatusLen,
                         sizeof(TAF_MMA_NVIM_DELAY_RPT_CLNOSERVICE_STRU)))
    {
        pstClNoServiceDelayRpt->ucCLNoServiceDelayRptLen    = 0;
        pstClNoServiceDelayRpt->ucDoNoServiceDelayRptLen    = 0;

        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadDelaySndCLServiceStatusTimeLenNvim: Nv Read error Set To 0");

        return;
    }

    pstClNoServiceDelayRpt->ucCLNoServiceDelayRptLen = stDelayCLSrvStatusLen.ucCLDelayTimerLen;
    pstClNoServiceDelayRpt->ucDoNoServiceDelayRptLen = stDelayCLSrvStatusLen.ucDoDelayTimerLen;

#ifdef DMT
    pstClNoServiceDelayRpt->ucCLNoServiceDelayRptLen = 0;
    pstClNoServiceDelayRpt->ucDoNoServiceDelayRptLen = 0;
#endif

    TAF_INFO_LOG1(WUEPS_PID_MMA, "TAF_MMA_ReadDelaySndCLServiceStatusTimeLenNvim: CL TIMER LEN(s):", pstClNoServiceDelayRpt->ucCLNoServiceDelayRptLen);
    TAF_INFO_LOG1(WUEPS_PID_MMA, "TAF_MMA_ReadDelaySndCLServiceStatusTimeLenNvim: DO TIMER LEN(s):", pstClNoServiceDelayRpt->ucDoNoServiceDelayRptLen);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadCLDelayReportSrvCfgNvim
 功能描述  : 读取CL延迟上报定时器NV项
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月30日
    作    者   : j00354216
    修改内容   : CDMA Iteration_18新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ReadCLDelayReportSrvCfgNvim(VOS_VOID)
{
    TAF_MMA_NVIM_CL_DELAY_REPORT_SERVICE_STATUS_STRU        stCLDealyReptSrvCfg;

    PS_MEM_SET(&stCLDealyReptSrvCfg, 0x00, sizeof(TAF_MMA_NVIM_CL_DELAY_REPORT_SERVICE_STATUS_STRU));

    if (NV_OK != NV_Read(en_NV_Item_CL_DELAY_REPORT_SERVICE_STATUS_CFG,
                        (VOS_VOID *)&stCLDealyReptSrvCfg,
                        sizeof(TAF_MMA_NVIM_CL_DELAY_REPORT_SERVICE_STATUS_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_ReadCLDelayReportServiceStatusCfgNvim: return error");
        /* 读取nv失败，CL模延时上报功能为关闭 */
        return;
    }

    /* 勾包，可维可测 */
    TAF_MMA_LogReadNVInfo(en_NV_Item_CL_DELAY_REPORT_SERVICE_STATUS_CFG,
                          sizeof(TAF_MMA_NVIM_CL_DELAY_REPORT_SERVICE_STATUS_STRU),
                          WUEPS_PID_MMA,
                          (VOS_UINT8 *)&stCLDealyReptSrvCfg);

    /* 延时上报开关ucClDelayRptEnable为开，定时器时长才有意义 */
    if (VOS_FALSE != stCLDealyReptSrvCfg.ucCLDelayRptEnable)
    {
        TAF_MMA_SetCLDelayReptSrvStatusFlg(VOS_TRUE);
        /* ulClRptSrvStaDelayTimerLen 单位为秒，转换为毫秒 */
        TAF_MMA_SetCLDelayReptSrvStatusTimerLen(stCLDealyReptSrvCfg.ulCLRptSrvStaDelayTimerLen * NAS_SDC_ONE_THOUSAND_MILLISECOND);
    }
    else
    {
        TAF_MMA_SetCLDelayReptSrvStatusFlg(VOS_FALSE);
        TAF_MMA_SetCLDelayReptSrvStatusTimerLen(0);
    }

    return;
}
#endif

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



