/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSdcLib.c
  版 本 号   : 初稿
  作    者   : s46746
  生成日期   : 2012年12月26日
  最近修改   : 2012年12月26日
  功能描述   : SDC_CTX的对外提供库函数
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月26日
    作    者   : s46746
    修改内容   : 创建文件

****************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "UsimPsInterface.h"
#include "TafSdcLib.h"
#include "zlib.h"
#include "NVIM_Interface.h"

#include "NasUsimmApi.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

#include "TafStdlib.h"
#include "NasMntn.h"
#include "MnComm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_TAF_SDC_LIB_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, begin */
/* 增加AT^REJINFO的主动上报控制，放在一个字节的倒数第三个BIT */
/* 增加AT^PLMNSELERLST的主动上报控制，放在一个字节的倒数第五个BIT */
/* 增加^MIPICLK的主动上报控制，放在第一个字节的最后一个Bit */
/* 增加^CTIME的主动上报控制，放在第六个字节的最后第五个Bit */
/* 增加^CBURSTDTMF的主动上报控制，放在第八个字节的倒数第二个Bit */
/* 增加^CCONTDTMF的主动上报控制，放在第八个字节的最后一个Bit */
/* 增加^SRCHEDPLMNINFO的主动上报控制，放在第二个字节的第二个Bit */
/* 增加^CLOCINFO的主动上报控制，放在第八个字节的倒数第3个Bit */
/* 增加^CSID的主动上报控制，放在第八个字节的倒数第4个Bit */
/* 请重点关注L4A_RPT_CMD_INDEX_ENUM_UINT32，该处使用的bit位，在此处不能再次使用 */
TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            g_aenTafSdcCurcRptCmdTable[] =
{
    TAF_SDC_RPT_CMD_MODE,        TAF_SDC_RPT_CMD_RSSI,        TAF_SDC_RPT_CMD_REJINFO,     TAF_SDC_RPT_CMD_SRVST,
    TAF_SDC_RPT_CMD_PLMNSELEINFO,TAF_SDC_RPT_CMD_SIMST,       TAF_SDC_RPT_CMD_TIME,        TAF_SDC_RPT_CMD_MIPICLK,
    TAF_SDC_RPT_CMD_ANLEVEL,     TAF_SDC_RPT_CMD_SRCHEDPLMNINFO, TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_SMMEMFULL,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_CTZV,
    TAF_SDC_RPT_CMD_CTZE,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_DSFLOWRPT,   TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_ORIG,        TAF_SDC_RPT_CMD_CONF,        TAF_SDC_RPT_CMD_CONN,        TAF_SDC_RPT_CMD_CEND,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_STIN,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_CTIME,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_CERSSI,      TAF_SDC_RPT_CMD_LWCLASH,     TAF_SDC_RPT_CMD_XLEMA,       TAF_SDC_RPT_CMD_ACINFO,
    TAF_SDC_RPT_CMD_PLMN,        TAF_SDC_RPT_CMD_CALLSTATE,   TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_XPASSINFO,
    TAF_SDC_RPT_CMD_CCONTDTMF,   TAF_SDC_RPT_CMD_CBURSTDTMF,  TAF_SDC_RPT_CMD_CLOCINFO,    TAF_SDC_RPT_CMD_CSID,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT
};

/* 增加^CLOCINFO的主动上报控制，放在第八个字节的倒数第3个Bit */
/* 增加^CSID的主动上报控制，放在第八个字节的倒数第4个Bit */
TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            g_aenTafSdcUnsolicitedRptCmdTable[] =
{
    TAF_SDC_RPT_CMD_MODE,        TAF_SDC_RPT_CMD_RSSI,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_SRVST,
    TAF_SDC_RPT_CMD_CREG,        TAF_SDC_RPT_CMD_SIMST,       TAF_SDC_RPT_CMD_TIME,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_ANLEVEL,     TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_CTZV,
    TAF_SDC_RPT_CMD_CTZE,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_DSFLOWRPT,   TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_CUSD,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_CSSI,
    TAF_SDC_RPT_CMD_CSSU,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_CERSSI,      TAF_SDC_RPT_CMD_LWURC,       TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_CUUS1U,
    TAF_SDC_RPT_CMD_CUUS1I,      TAF_SDC_RPT_CMD_CGREG,       TAF_SDC_RPT_CMD_CEREG,       TAF_SDC_RPT_CMD_BUTT,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_CLOCINFO,    TAF_SDC_RPT_CMD_CSID,
    TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT,        TAF_SDC_RPT_CMD_BUTT
};

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, end */

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlatformSupportLte
 功能描述  : 判断平台接入技术能力是否支持LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
             VOS_FALSE:不支持
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_SDC_IsPlatformSupportLte( VOS_VOID )
{
    VOS_UINT32                          i;
    TAF_SDC_PLATFORM_RAT_CAP_STRU      *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();

    /* LTE是否在平台接入技术能力列表中 */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if (TAF_SDC_PLATFORM_RAT_LTE == pstPlatformRatCap->aenRatList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlatformSupportUtran
 功能描述  : 判断平台接入技术能力是否支持Utran FDD或TDD
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
             VOS_FALSE:不支持
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_SDC_IsPlatformSupportUtran( VOS_VOID )
{
    VOS_UINT32                          i;
    TAF_SDC_PLATFORM_RAT_CAP_STRU      *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();

    /* UTRAN是否在平台接入技术能力列表中 */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if ((TAF_SDC_PLATFORM_RAT_WCDMA == pstPlatformRatCap->aenRatList[i])
         || (TAF_SDC_PLATFORM_RAT_TDS == pstPlatformRatCap->aenRatList[i]))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlatformSupportUtranFdd
 功能描述  : 判断平台接入技术能力是否支持Utran FDD
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
             VOS_FALSE:不支持
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月18日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_SDC_IsPlatformSupportUtranFdd( VOS_VOID )
{
    VOS_UINT32                          i;
    TAF_SDC_PLATFORM_RAT_CAP_STRU      *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();

    /* UTRAN是否在平台接入技术能力列表中 */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if (TAF_SDC_PLATFORM_RAT_WCDMA == pstPlatformRatCap->aenRatList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlatformSupportUtranTdd
 功能描述  : 判断平台接入技术能力是否支持Utran TDD
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
             VOS_FALSE:不支持
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月18日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_SDC_IsPlatformSupportUtranTdd( VOS_VOID )
{
    VOS_UINT32                          i;
    TAF_SDC_PLATFORM_RAT_CAP_STRU      *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();

    /* UTRAN是否在平台接入技术能力列表中 */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if (TAF_SDC_PLATFORM_RAT_TDS == pstPlatformRatCap->aenRatList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif


/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlatformSupportGsm
 功能描述  : 判断平台接入技术能力是否支持GSM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
             VOS_FALSE:不支持
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_SDC_IsPlatformSupportGsm( VOS_VOID )
{
    VOS_UINT32                          i;
    TAF_SDC_PLATFORM_RAT_CAP_STRU      *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();

    /* GSM是否在平台接入技术能力列表中 */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if (TAF_SDC_PLATFORM_RAT_GSM == pstPlatformRatCap->aenRatList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlatformSupport3Gpp2
 功能描述  : 判断平台接入技术能力是否支持CDMA
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 支持
             VOS_FALSE -- 不支持
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月08日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsPlatformSupport3Gpp2(VOS_VOID)
{
    VOS_UINT32                          i;
    TAF_SDC_PLATFORM_RAT_CAP_STRU      *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();

    /* CDMA是否在平台接入技术能力列表中 */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if ((TAF_SDC_PLATFORM_RAT_1X   == pstPlatformRatCap->aenRatList[i])
         || (TAF_SDC_PLATFORM_RAT_HRPD == pstPlatformRatCap->aenRatList[i]))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlatformSupport1x
 功能描述  : 判断平台接入技术能力是否支持1x
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 支持
             VOS_FALSE -- 不支持
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月24日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsPlatformSupport1x(VOS_VOID)
{
    VOS_UINT32                          i;
    TAF_SDC_PLATFORM_RAT_CAP_STRU      *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();

    /* CDMA是否在平台接入技术能力列表中 */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if (TAF_SDC_PLATFORM_RAT_1X == pstPlatformRatCap->aenRatList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlatformSupportHrpd
 功能描述  : 判断平台接入技术能力是否支持HRPD
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 支持
             VOS_FALSE -- 不支持
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月24日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsPlatformSupportHrpd(VOS_VOID)
{
    VOS_UINT32                          i;
    TAF_SDC_PLATFORM_RAT_CAP_STRU      *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();

    /* CDMA是否在平台接入技术能力列表中 */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if (TAF_SDC_PLATFORM_RAT_HRPD == pstPlatformRatCap->aenRatList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlatformSupportHybrid
 功能描述  : 判断当前modem是否支持HYBRID模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月5日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsPlatformSupportHybrid(VOS_VOID)
{
    VOS_UINT32                          ulSupport1X;
    VOS_UINT32                          ulSupportEVDO;

    ulSupport1X     = TAF_SDC_IsPlatformSupport1x();
    ulSupportEVDO   = TAF_SDC_IsPlatformSupportHrpd();

    if ((VOS_TRUE == ulSupport1X)
     && (VOS_TRUE == ulSupportEVDO))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlatformSupport3Gpp
 功能描述  : 判断平台接入技术能力是否支持G或U或L
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 支持
             VOS_FALSE -- 不支持
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月08日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsPlatformSupport3Gpp(VOS_VOID)
{
    VOS_UINT32                                              i;
    TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8                    enRatType         = TAF_SDC_PLATFORM_RAT_BUTT;
    TAF_SDC_PLATFORM_RAT_CAP_STRU                          *pstPlatformRatCap = VOS_NULL_PTR;


    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();

    /* 在平台接入技术能力列表中是否由G、U或L */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        enRatType = pstPlatformRatCap->aenRatList[i];

        if ((TAF_SDC_PLATFORM_RAT_GSM   == enRatType)
         || (TAF_SDC_PLATFORM_RAT_WCDMA == enRatType)
         || (TAF_SDC_PLATFORM_RAT_TDS   == enRatType)
         || (TAF_SDC_PLATFORM_RAT_LTE   == enRatType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-11, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_LogUnsolicitedRptInfo
 功能描述  : 勾主动上报相关信息
 输入参数  : enRptCmdIndex         - CURC主动上报命令枚举
             pstCurcRptCtrl        - CURC控制主动上报的结构体
             pstUnsolicitedRptCtrl - 单个命令控制主动上报的结构体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月11日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SDC_LogUnsolicitedRptInfo(
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex,
    TAF_SDC_CURC_RPT_CTRL_STRU                 *pstCurcRptCtrl,
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU          *pstUnsolicitedRptCtrl
)
{
    TAF_OAM_UNSOLICITED_RPT_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_OAM_UNSOLICITED_RPT_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                         sizeof(TAF_OAM_UNSOLICITED_RPT_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(TAF_OAM_UNSOLICITED_RPT_INFO_STRU));

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->ulLength        = sizeof(TAF_OAM_UNSOLICITED_RPT_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId         = TAF_OAM_UNSOLICITED_RPT_INFO_IND;
    pstMsg->ulRptCmdIndex   = enRptCmdIndex;
    PS_MEM_CPY(pstMsg->aucCurcRptCfg, pstCurcRptCtrl->aucRptCfg, sizeof(pstMsg->aucCurcRptCfg));
    PS_MEM_CPY(pstMsg->aucUnsolicitedRptCfg, pstUnsolicitedRptCtrl->aucRptCfg, sizeof(pstMsg->aucUnsolicitedRptCfg));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-11, end */
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_CheckRptCmdStatus
 功能描述  : 检查主动上报命令启用状态
 输入参数  : VOS_UINT8                          *pucRptCfg,
             TAF_SDC_CMD_RPT_CTRL_TYPE_ENUM_UINT8     enRptCtrlType,
             TAF_SDC_RPT_CMD_INDEX_ENUM_UINT32        enRptCmdIndex
 输出参数  : 无
 返 回 值  :  VOS_TRUE        -- 启用主动上报
              VOS_FALSE       -- 关闭主动上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月10日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32 TAF_SDC_CheckRptCmdStatus(
    VOS_UINT8                                  *pucRptCfg,
    TAF_SDC_CMD_RPT_CTRL_TYPE_ENUM_UINT8        enRptCtrlType,
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex
)
{
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8   *pulRptCmdTblPtr       = VOS_NULL_PTR;
    VOS_UINT32                          ulRptCmdTblSize;
    VOS_UINT8                           ucTableIndex;
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucBit;

    /* 主动上报命令索引错误，默认主动上报 */
    if (enRptCmdIndex >= TAF_SDC_RPT_CMD_BUTT)
    {
        return VOS_TRUE;
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-11, begin */
    TAF_SDC_LogUnsolicitedRptInfo(enRptCmdIndex, TAF_SDC_GetCurcRptCtrl(), TAF_SDC_GetUnsolicitedRptCtrl());
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-11, end */

    /* 主动上报受控类型填写错误，默认主动上报 */
    if (TAF_SDC_CMD_RPT_CTRL_BUTT == enRptCtrlType)
    {
        return VOS_TRUE;
    }

    if (TAF_SDC_CMD_RPT_CTRL_BY_CURC == enRptCtrlType)
    {
        pulRptCmdTblPtr = TAF_SDC_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_PTR();
        ulRptCmdTblSize = TAF_SDC_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_SIZE();
    }
    else
    {
        pulRptCmdTblPtr = TAF_SDC_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_PTR();
        ulRptCmdTblSize = TAF_SDC_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_SIZE();
    }

    for (ucTableIndex = 0; ucTableIndex < ulRptCmdTblSize; ucTableIndex++)
    {
        if (enRptCmdIndex == pulRptCmdTblPtr[ucTableIndex])
        {
            break;
        }
    }

    /* 与全局变量中的Bit位对比 */
    if (ulRptCmdTblSize != ucTableIndex)
    {
        /* 由于用户设置的字节序与Bit映射表序相反, 首先反转Bit位 */
        /*lint -e961*/
        ulOffset        = TAF_SDC_RPT_CFG_MAX_SIZE - (ucTableIndex / 8) - 1;
        /*lint +e961*/
        ucBit           = (VOS_UINT8)(ucTableIndex % 8);

        return (VOS_UINT32)((pucRptCfg[ulOffset] >> ucBit) & 0x1);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_UpdateRptCmdStatus
 功能描述  : 更新主动上报命令启用状态
 输入参数  : TAF_SDC_RPT_CMD_INDEX_ENUM_UINT32        enRptCmdIndex
             VOS_UINT8                                ucRptCmdStatus
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月10日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID TAF_SDC_UpdateRptCmdStatus(
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex,
    VOS_UINT32                                  ulRptCmdStatus
)
{
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8   *pulRptCmdTblPtr     = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRpt   = VOS_NULL_PTR;
    VOS_UINT32                          ulRptCmdTblSize;
    VOS_UINT8                           ucTableIndex;
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucBit;
    VOS_UINT8                           ucRptFlg;

    ucRptFlg    = 0x01;

    /* 主动上报命令索引错误，默认主动上报 */
    if (enRptCmdIndex >= TAF_SDC_RPT_CMD_BUTT)
    {
        return;
    }

    pulRptCmdTblPtr     = TAF_SDC_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_PTR();
    ulRptCmdTblSize     = TAF_SDC_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_SIZE();
    pstUnsolicitedRpt   = TAF_SDC_GetUnsolicitedRptCtrl();

    for (ucTableIndex = 0; ucTableIndex < ulRptCmdTblSize; ucTableIndex++)
    {
        if (enRptCmdIndex == pulRptCmdTblPtr[ucTableIndex])
        {
            break;
        }
    }

    /* 与全局变量中的Bit位对比 */
    if (ulRptCmdTblSize != ucTableIndex)
    {
        /* 由于用户设置的字节序与Bit映射表序相反, 首先反转Bit位 */
        /*lint -e961*/
        ulOffset        = TAF_SDC_RPT_CFG_MAX_SIZE - (ucTableIndex / 8) - 1;
        /*lint +e961*/
        ucBit           = (VOS_UINT8)(ucTableIndex % 8);

        /*lint -e701*/
        ucRptFlg = (VOS_UINT8)(ucRptFlg << ucBit);
        /*lint +e701*/

        /* 关闭主动上报时 */
        if (VOS_FALSE == ulRptCmdStatus)
        {
            (pstUnsolicitedRpt->aucRptCfg[ulOffset]) &= (~ucRptFlg);
        }
        else
        {
            (pstUnsolicitedRpt->aucRptCfg[ulOffset]) |= ucRptFlg;
        }

    }

    return;
}

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_ConvertOamSendPid
 功能描述  : svlte特性开启时，modem1可能收到usim0的消息，需要将消息中send pid进行转换
 输入参数  : ulConvertedSendPid - 消息中原始的send pid
 输出参数  : 无
 返 回 值  : 转换后的pid
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月5日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改

  2.日    期   : 2015年6月25日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT32 TAF_SDC_ConvertOamSendPid(
    VOS_UINT32                          ulConvertedSendPid
)
{

    if ((I0_WUEPS_PID_USIM == ulConvertedSendPid)
     || (I1_WUEPS_PID_USIM == ulConvertedSendPid)
     || (I2_WUEPS_PID_USIM == ulConvertedSendPid))
    {
        return WUEPS_PID_USIM;
    }

    if ((I0_MAPS_STK_PID == ulConvertedSendPid)
     || (I1_MAPS_STK_PID == ulConvertedSendPid)
     || (I2_MAPS_STK_PID == ulConvertedSendPid))
    {
        return MAPS_STK_PID;
    }

    if ((I0_MAPS_PB_PID == ulConvertedSendPid)
     || (I1_MAPS_PB_PID == ulConvertedSendPid)
     || (I2_MAPS_PB_PID == ulConvertedSendPid))
    {
        return MAPS_PB_PID;
    }


    if ((I0_MAPS_PIH_PID == ulConvertedSendPid)
     || (I1_MAPS_PIH_PID == ulConvertedSendPid)
     || (I2_MAPS_PIH_PID == ulConvertedSendPid))
    {
        return MAPS_PIH_PID;
    }

    return ulConvertedSendPid;
}

/* Deleted by l00208543 for STK升级, 2013-07-24, begin */
/* Deleted by l00208543 for STK升级, 2013-07-24, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsSrvExistFlg
 功能描述  : 获取当前是否有CS业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前是否有CS业务
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月17日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_GetCsSrvExistFlg(VOS_VOID)
{
    /* 如果有电话业务存在，认为当前有CS业务 */
     /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    if (VOS_TRUE == TAF_SDC_GetCsCallExistFlg())
     /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */
    {
        return VOS_TRUE;
    }

    /* 如果有CS域短信业务存在，认为当前有CS业务 */
    if (VOS_TRUE == TAF_SDC_GetCsSmsSrvExistFlg())
    {
        return VOS_TRUE;
    }

    /* 如果有CS域补充业务存在，认为当前有CS业务 */
    if (VOS_TRUE == TAF_SDC_GetCsSsSrvExistFlg())
    {
        return VOS_TRUE;
    }

    /* 其他情况下认为没有CS业务 */
    return VOS_FALSE;

}


/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-29, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetImsSupportFlag
 功能描述  : 获取当前是否支持IMS标志,GSM,UTRAN,LTE IMS其中有一个支持IMS就认为支持IMS
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前是否支持IMS标志
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月17日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_GetImsSupportFlag(VOS_VOID)
{
    /* 如果支持GSM IMS，认为当前支持IMS */
    if (VOS_TRUE == TAF_SDC_GetGsmImsSupportFlag())
    {
        return VOS_TRUE;
    }

    /* 如果支持UTRAN IMS，认为当前支持IMS */
    if (VOS_TRUE == TAF_SDC_GetUtranImsSupportFlag())
    {
        return VOS_TRUE;
    }

    /* 如果支持LTE IMS，认为当前支持IMS */
    if (VOS_TRUE == TAF_SDC_GetLteImsSupportFlag())
    {
        return VOS_TRUE;
    }

    /* 其他情况下认为当前不支持IMS */
    return VOS_FALSE;

}

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-29, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_IsImsiAvailableInCurrSimStatus
 功能描述  : 判断哪些卡状态可以取到卡的IMSI
 输入参数  : TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月18日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsImsiAvailableInCurrSimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
)
{
    switch(enSimStatus)
    {
        /* 这些状态时可以取到IMSI */
        case TAF_SDC_USIM_STATUS_VALID:
        case TAF_SDC_USIM_STATUS_CS_UNVALID:
        case TAF_SDC_USIM_STATUS_PS_UNVALID:
        case TAF_SDC_USIM_STATUS_CS_PS_UNVALID:
        case TAF_SDC_USIM_STATUS_NET_LCOK:
        case TAF_SDC_USIM_STATUS_ROMSIM:
        case TAF_SDC_USIM_STATUS_IMSI_LCOK:

            return VOS_TRUE;

        default:

            return VOS_FALSE;
    }
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : TAF_SDC_IsErrLogNeedRecord
 功能描述  : 查询usLevel级别的异常是否需要记录
 输入参数  : VOS_UINT16 usLevel
 输出参数  : 无
 返 回 值  : VOS_TRUE:   需要上报
             VOS_FALSE:  不需要上报

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月23日
    作    者   : s00190137
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsErrLogNeedRecord(VOS_UINT16 usLevel)
{
    /* Log开关关闭，不需要上报 */
    if (0 == TAF_SDC_GetErrlogCtrlFlag())
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* 模块log级别usLevel大于用户设置的log上报级别或usLevel无效，不需要上报 */
    if ((TAF_SDC_GetErrlogAlmLevel() < usLevel)
     || (NAS_ERR_LOG_CTRL_LEVEL_NULL == usLevel))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCardImsiFailRecord
 功能描述  : 记录CS呼叫异常事件
 输入参数  : VOS_UINT32                        ulGetCardImsiRslt,
             VOS_UINT8                         pucImsi
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月18日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_GetCardImsiFailRecord(
    VOS_UINT32                          ulGetCardImsiRslt,
    VOS_UINT8                          *pucImsi
)
{
    NAS_ERR_LOG_GET_CARD_IMSI_FAIL_STRU                     stGetCardImsiFail;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_GET_CARD_IMSI_FAIL);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* 不需要记录或没有异常时，不保存异常信息 */
    if ((VOS_FALSE == ulIsLogRecord)
     || (USIMM_API_SUCCESS == ulGetCardImsiRslt))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_GET_CARD_IMSI_FAIL_STRU);

    /* 填充Cs呼叫失败异常信息 */
    PS_MEM_SET(&stGetCardImsiFail, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stGetCardImsiFail.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_TAF),
                                      NAS_ERR_LOG_ALM_GET_CARD_IMSI_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));



    /* 调用API返回的结果 */
    stGetCardImsiFail.ulGetCardImsiRslt = ulGetCardImsiRslt;

    /* 调用API返回的IMSI */
    if (VOS_NULL_PTR != pucImsi)
    {
        PS_MEM_CPY(stGetCardImsiFail.aucImsi, pucImsi, NAS_MNTN_IMSI_LENGTH_IN_USIM);
    }

    /* USIM信息 */
    stGetCardImsiFail.stUsimInfo.enSimType      = TAF_SDC_GetUsimType();
    stGetCardImsiFail.stUsimInfo.enSimStatus    = TAF_SDC_GetUsimStatus();

    /* CSIM信息 */
    stGetCardImsiFail.stCsimInfo.enSimType      = TAF_SDC_GetCsimType();
    stGetCardImsiFail.stCsimInfo.enSimStatus    = TAF_SDC_GetCsimStatus();

    /* 主动上报NAS_ERR_LOG_ALM_GET_CARD_IMSI_FAIL */
    TAF_SndAcpuOmFaultErrLogInd(&stGetCardImsiFail, ulLength, NAS_ERR_LOG_ALM_GET_CARD_IMSI_FAIL);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stGetCardImsiFail, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_GetCardImsiFailRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_GET_CARD_IMSI_FAIL,
                           WUEPS_PID_TAF,
                           (VOS_UINT8 *)&stGetCardImsiFail,
                           sizeof(stGetCardImsiFail));
    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_CalcTime
 功能描述  : 计算时长
 输入参数  : ulFirTime -- 起始计时
             ulSecTime -- 结束计时
 输出参数  : pulTotalTime -- 时长
 返 回 值  : 成功返回VOS_OK; 失败返回VOS_ERR;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月21日
    作    者   : j00174725
    修改内容   : V3R3 ROTS项目
*****************************************************************************/
VOS_UINT32  TAF_CalcTime(
                VOS_UINT32  ulFirTime,
                VOS_UINT32  ulSecTime,
                VOS_UINT32 *pulTotalTime
)
{
    if (ulFirTime > ulSecTime)
    {
        *pulTotalTime = 0;
        return VOS_ERR;
    }

    *pulTotalTime = ulSecTime - ulFirTime;

    return VOS_OK;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
/*****************************************************************************
 函 数 名  :TAF_SDC_IsLteOnlyMode
 功能描述  :判断当前接入模式是否为Lte only
 输入参数  :pstRatOrder - 接入模式和优先级信息
 输出参数  :无
 返 回 值  :VOS_TRUE  - 当前为L单模
            VOS_FALSE - 当前不为L单模
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月20日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsLteOnlyMode(
    TAF_SDC_RAT_PRIO_STRU              *pstRatOrder
)
{
    if ( (1                        == pstRatOrder->ucRatNum)
      && (TAF_SDC_SYS_MODE_LTE     == pstRatOrder->aenRatPrio[0]) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*******************************************************************************
  函 数 名  : TAF_SDC_IsUsimStausValid
  功能描述  : 判断SIM卡是否有效
  输入参数  : 无
  输出参数  : 无
  返 回 值  : VOS_FALSE:SIM卡无效
              VOS_TRUE:SIM卡有效
  调用函数  :
  被调函数  :

  修改历史      :
  1.日    期   : 2013年11月20日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性开启卡无效场景mtc无需上报pstransfer:0和1
  3.日    期   : 2013年05月14日
    作    者   : w00176964
    修改内容   : eCall特性开发
*******************************************************************************/
VOS_UINT32 TAF_SDC_IsUsimStausValid(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucSimPsRegStatus;
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-14, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    TAF_SDC_CALL_MODE_ENUM_UINT8        enCallMode;
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-14, end */
#if (FEATURE_ON == FEATURE_LTE)
    TAF_SDC_RAT_PRIO_STRU              *pstRatPrio = VOS_NULL_PTR;

    pstRatPrio       = TAF_SDC_GetMsPrioRatList();
#endif

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-14, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    enCallMode = TAF_SDC_GetCurCallMode();
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-14, end */

    ucSimCsRegStatus = TAF_SDC_GetSimCsRegStatus();
    ucSimPsRegStatus = TAF_SDC_GetSimPsRegStatus();

    if ((VOS_FALSE == ucSimPsRegStatus)
     && (VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    /* 无卡时返回VOS_FALSE卡无效 */
    if (TAF_SDC_USIM_STATUS_NO_PRESENT == TAF_SDC_GetSimStatus())
    {
        return VOS_FALSE;
    }

    if (( VOS_FALSE == TAF_SDC_GetPsAttachAllowFlg())
     && ( VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-14, begin */
    if (( VOS_FALSE == TAF_SDC_GetCsAttachAllowFlg())
     && ( VOS_FALSE == ucSimPsRegStatus)
#if (FEATURE_ON == FEATURE_ECALL)
     && (TAF_SDC_ECALL_ONLY != enCallMode)
#endif
       )
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-14, end */
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* LTE单模的情况PS卡无效的时候也认为此时卡无效 */
    if ((VOS_TRUE == TAF_SDC_IsLteOnlyMode(pstRatPrio))
     && (VOS_FALSE == ucSimPsRegStatus))
    {
        return VOS_FALSE;
    }
#endif
    return VOS_TRUE;

}
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_SDC_IsImsVoiceSupportedInUE
 功能描述  : 判断UE是否支持IMS VOICE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:IMS VOICE不支持
             VOS_TRUE: IMS VOICE支持
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月31日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_IsImsVoiceSupportedInUE(VOS_VOID)
{
    VOS_UINT32                          ulImsSupportFlag;

    ulImsSupportFlag    = TAF_SDC_GetImsSupportFlag();

    /* 当前IMS的RAT NV不支持或语音优选域为CS ONLY或网络不支持IMS时 认为IMS VOICE不可用*/
    if ((TAF_SDC_VOICE_DOMAIN_CS_ONLY       == TAF_SDC_GetVoiceDomain())
     || (VOS_FALSE                          == ulImsSupportFlag))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_IsImsVoiceSupportedInNW
 功能描述  : 判断网络是否支持IMS VOICE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:IMS VOICE不支持
             VOS_TRUE: IMS VOICE支持
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月31日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_IsImsVoiceSupportedInNW(VOS_VOID)
{
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstCurNwCapInfo   = VOS_NULL_PTR;

    if (TAF_SDC_SYS_MODE_LTE == TAF_SDC_GetSysMode())
    {
        pstCurNwCapInfo = TAF_SDC_GetLteNwCapInfo();
    }
    else
    {
        pstCurNwCapInfo = TAF_SDC_GetGuNwCapInfo();
    }

    if (TAF_SDC_NW_IMS_VOICE_NOT_SUPPORTED == pstCurNwCapInfo->enNwImsVoCap)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



#endif
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, end */

/* Added by l00198894 for 新增+ECID命令, 2013-12-10, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_PlmnId2Bcd
 功能描述  : 将原PLMNid转化为BCD格式记录
             例如:MCC为460,MNC为01时,
             pstPlmnId->Mcc = 0x000604      pstPlmnId->Mcc = 0x00000460
                                        ---->
             pstPlmnId->Mnc = 0x0F0100      pstPlmnId->Mnc = 0x00000F01
 输入参数  : TAF_SDC_PLMN_ID_STRU *pstPlmnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : l00198894
    修改内容   : 新增+ECID命令
*****************************************************************************/
VOS_VOID TAF_SDC_PlmnId2Bcd(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
)
{
    VOS_UINT8                           ucI;
    VOS_UINT32                          ulTmp;
    VOS_UINT8                           aucTmp[4];

    ulTmp            = pstPlmnId->ulMcc;
    pstPlmnId->ulMcc = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }
    pstPlmnId->ulMcc = ((VOS_UINT32)aucTmp[0] << 8)
                      |((VOS_UINT32)aucTmp[1] << 4)
                      | aucTmp[2];

    ulTmp            = pstPlmnId->ulMnc;
    pstPlmnId->ulMnc = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }

    if(0xf == aucTmp[2])
    {
        pstPlmnId->ulMnc = ((VOS_UINT32)aucTmp[0] << 4)
                          |((VOS_UINT32)aucTmp[1] )
                          |0xf00;
    }
    else
    {
        pstPlmnId->ulMnc = ((VOS_UINT32)aucTmp[0] << 8)
                          |((VOS_UINT32)aucTmp[1] << 4)
                          | aucTmp[2];
    }
    return;
}
/* Added by l00198894 for 新增+ECID命令, 2013-12-10, end */

/* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
/*******************************************************************************
  函 数 名  : TAF_SDC_IsConfigCLInterWorkCOutside
  功能描述  : 判断是否CL互操作方案
  输入参数  : 无
  输出参数  : 无
  返 回 值  : VOS_FALSE:不是
              VOS_TRUE:是
  调用函数  :
  被调函数  :

  修改历史      :
  1.日    期   : 2014年2月15日
    作    者   : s00246516
    修改内容   : 新生成函数
*******************************************************************************/
VOS_UINT32 TAF_SDC_IsConfigCLInterWorkCOutside(VOS_VOID)
{
    if (VOS_FALSE == TAF_SDC_GetLCEnableFlg())
    {
        return VOS_FALSE;
    }

    if ( TAF_NVIM_LC_RAT_COMBINED_CL != TAF_SDC_GetLCRatCombined() )
    {
        return VOS_FALSE;
    }

    /* 当前配置为CL互操作模式，BALONG的modem不支持CDMA */
    if (TAF_NVIM_LC_INTER_WORK == TAF_SDC_GetLCWorkCfg())
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_FALSE == TAF_SDC_IsPlatformSupport3Gpp2())
#endif
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_SDC_IsConfigCLMode
 功能描述  : C Inside并且用户设置了C模
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsConfigCLMode(VOS_VOID)
{
    TAF_SDC_RAT_PRIO_STRU              *pstRatPrio = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstRatPrio = TAF_SDC_GetMsPrioRatList();

    for (i = 0; i < pstRatPrio->ucRatNum; i++)
    {
        if ((TAF_SDC_SYS_MODE_CDMA_1X == pstRatPrio->aenRatPrio[i])
         || (TAF_SDC_SYS_MODE_EVDO == pstRatPrio->aenRatPrio[i]))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Is1xOnlyMode
 功能描述  : 判断只支持1X模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月24日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_Is1xOnlyMode(VOS_VOID)
{
    TAF_SDC_RAT_PRIO_STRU              *pstRatPrio      = VOS_NULL_PTR;
    pstRatPrio                          = TAF_SDC_GetMsPrioRatList();

    if ( (1                        == pstRatPrio->ucRatNum)
      && (TAF_SDC_SYS_MODE_CDMA_1X == pstRatPrio->aenRatPrio[0]) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get1xConcurrentSupportedFlag
 功能描述  : 判断1X是否支持并发业务
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_Get1xConcurrentSupportedFlag(VOS_VOID)
{
    TAF_SDC_1X_SYS_INFO_STRU           *pst1xSysInfo;

    pst1xSysInfo = TAF_SDC_Get1xSysInfo();

    if ((VOS_TRUE             == pst1xSysInfo->stServiceInfo.ucConcurrentSupported)
     && (TAF_SDC_REV_IN_USE_7 <= pst1xSysInfo->ucPrevInUse))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#endif





/*lint -restore */

/*****************************************************************************
 函 数 名  : TAF_SDC_CheckDtmfKey
 功能描述  : 检查DTMF key的合法性
 输入参数  : VOS_CHAR  *pckey
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   : g00261581
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32 TAF_SDC_CheckDtmfKey(
    VOS_CHAR                           *pckey
)
{
    /* 转换为大写字符 */
    if ( (*pckey >= 'a') && (*pckey <= 'z'))
    {
        *pckey = *pckey - 0x20;
    }

    if (!((('0' <= *pckey) && ('9' >= *pckey))
         || ('*' == *pckey) || ('#' == *pckey)
         || ('A' == *pckey) || ('B' == *pckey)
         || ('C' == *pckey) || ('D' == *pckey)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_IsCsNormalService
 功能描述  : 判断CS域是否正常服务
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : l00198894
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32 TAF_SDC_IsCsNormalService(VOS_VOID)
{
    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetCsServiceStatus())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_IsBcchPlmnIdInDestSimPlmnList
 功能描述  : 判断PLMN ID是否在列表中(卡类型的网络ID)
 输入参数  : pstBcchPlmnId    -  需要判断的PLMN ID
             ucSimPlmnNum     -  列表中plmn id的个数
             pstSimPlmnIdList - plmn列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在列表中
             VOS_FALSE : PLMN ID不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年2月27日
   作    者   : z00161729
   修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 TAF_SDC_IsBcchPlmnIdInDestSimPlmnList (
    TAF_SDC_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT8                           ucSimPlmnNum,
    TAF_SDC_PLMN_ID_STRU               *pstSimPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ucSimPlmnNum; i++ )
    {
        if ( VOS_TRUE == TAF_SDC_CompareBcchPlmnwithSimPlmn(pstBcchPlmnId,
                                                            pstSimPlmnIdList + i))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}





/*****************************************************************************
 函 数 名  : TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn
 功能描述  : 精确比较SIM卡中存储PLMN与系统消息广播中PLMN是否相等,MNC完全相同才为相等，PLMN 属于 NA PCS1900 除外
             1)一个plmn是Bcch格式的，一个plmn是Sim格式的进行比较时，
               Bcch格式的plmn必须作为第一个入参，sim格式的必须作为第二个入参
             2)两个Bcch格式的plmn比较时，入参顺序没关系
             3)两个Sim格式的plmn比较时，入参顺序没关系
 输入参数  : TAF_SDC_PLMN_ID_STRU    *pstBccPlmnId
             TAF_SDC_PLMN_ID_STRU    *pstSimPlmnId
 输出参数  : 无
 返 回 值  : VOS_TRUE: PLMN ID相同
             VOS_FALSE: PLMN ID不相同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月26日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId
)
{
    VOS_UINT32                          ulCmpRlst;

    if (pstBccPlmnId->ulMcc == pstSimPlmnId->ulMcc)
    {
        if (pstBccPlmnId->ulMnc == pstSimPlmnId->ulMnc)
        {
            return VOS_TRUE;
        }
        else if ((pstBccPlmnId->ulMnc & TAF_SDC_MCC_LOW_TWO_BYTE_VALUE_MASK)
              == (pstSimPlmnId->ulMnc & TAF_SDC_MCC_LOW_TWO_BYTE_VALUE_MASK))
        {
            /* 取MNC的最高位 ,若最高位是0或F，低2位Mnc相同则认为Plmn相等 */
            ulCmpRlst = TAF_SDC_CompareBcchMnc3BytewithSimMnc3Byte(
                                    pstBccPlmnId,
                                    pstSimPlmnId,
                                    VOS_TRUE);

            return ulCmpRlst;
        }
        else
        {
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_CompareBcchPlmnwithSimPlmn
 功能描述  : 比较系统消息广播中PLMN与SIM卡中存储PLMN是否相等,
             1)一个plmn是Bcch格式的，一个plmn是Sim格式的进行比较时，
               Bcch格式的plmn必须作为第一个入参，sim格式的必须作为第二个入参
             2)两个Bcch格式的plmn比较时，入参顺序没关系
             3)两个Sim格式的plmn比较时，入参顺序没关系
 输入参数  : TAF_SDC_PLMN_ID_STRU    *pstBccPlmnId
             TAF_SDC_PLMN_ID_STRU    *pstSimPlmnId
 输出参数  : 无
 返 回 值  : VOS_TRUE: PLMN ID相同
             VOS_FALSE: PLMN ID不相同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月26日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_CompareBcchPlmnwithSimPlmn(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId
)
{
    VOS_UINT32                          ulCmpRlst;

    ulCmpRlst   = VOS_FALSE;

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-14, begin */
    /* 如果需要精确比较MNC*/
    if (VOS_TRUE == TAF_SDC_GetPlmnExactlyCompareFlg())
    {
        ulCmpRlst = TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn(pstBccPlmnId, pstSimPlmnId);

        return ulCmpRlst;
    }
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-14, end */

    /* HPLMN Matching Criteria for mobiles which support PCS1900 for NA:
    1) The MS shall compare using all 3 digits the SIM-MCC with the BCCH-MCC.
    If the values do not match, then the HPLMN match fails*/
    if (pstBccPlmnId->ulMcc == pstSimPlmnId->ulMcc)
    {
        /*The MS shall compare using all 3 digits the SIM-MNC with the BCCH-MNC.
          If the values match, then the HPLMN match succeeds*/
        if (pstBccPlmnId->ulMnc == pstSimPlmnId->ulMnc)
        {
            ulCmpRlst = VOS_TRUE;
        }
        else if ((pstBccPlmnId->ulMnc & TAF_SDC_MCC_LOW_TWO_BYTE_VALUE_MASK)
              == (pstSimPlmnId->ulMnc & TAF_SDC_MCC_LOW_TWO_BYTE_VALUE_MASK))
        {
            /* 取MNC的最高位 ,若最高位是0或F，低2位Mnc相同则认为Plmn相等 */
            ulCmpRlst = TAF_SDC_CompareBcchMnc3BytewithSimMnc3Byte(
                                        pstBccPlmnId,
                                        pstSimPlmnId,
                                        VOS_FALSE);
        }
        else
        {
        }

    }

    return ulCmpRlst;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_CompareBcchPlmnBytewithSimPlmnByte_WithWildcard
 功能描述  : 比较系统消息广播中PLMN中的某个字节与SIM卡中存储PLMN中的对应字节是否相等,
             通配符可以匹配0~9的任何数字.
 输入参数  : VOS_UINT32    ucHexBcchByte --16进制表示的某字节，可能是通配符
             VOS_UINT32    ucHexSimByte  --16进制表示的某字节，可能是通配符
             VOS_CHAR      cWildcard    --ASCII 表示的通配符
 输出参数  : 无
 返 回 值  : VOS_TRUE: 字节相同
             VOS_FALSE: 字节不相同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年3月2日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_CompareBcchPlmnBytewithSimPlmnByte_WithWildcard(
    VOS_UINT8                           ucHexBcchByte,
    VOS_UINT8                           ucHexSimByte,
    VOS_CHAR                            cWildcard
)
{
    VOS_UINT8                           ucAsciiBcchByte;
    VOS_UINT8                           ucAsciiSimByte;
    VOS_CHAR                            cUpperWildCard;

    /* 下列情况认为两个字节是相同的:
     * 1.两个字节相等
     * 2.某字节是通配符而被比较字节是数字，但字节中的通配符是16进制数而ucWildcard是ASCII码，
     *   比如: 0x0D 需要转换成'D',0x02--'2', 0X12是错误格式
     */
    TAF_SDC_HexToAsciiOfPlmnByte(ucHexBcchByte, &ucAsciiBcchByte);
    TAF_SDC_HexToAsciiOfPlmnByte(ucHexSimByte, &ucAsciiSimByte);

    cUpperWildCard = VOS_CharToUpper(cWildcard);

    if ( (ucHexBcchByte == ucHexSimByte)
       || ((cUpperWildCard == ucAsciiBcchByte)
        && (isdigit(ucAsciiSimByte)))
       || ((cUpperWildCard == ucAsciiSimByte)
        && (isdigit(ucAsciiBcchByte))))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_CompareBcchMncwithSimMnc_WithWildcard
 功能描述  : 比较系统消息广播中PLMN中的MCC与SIM卡中存储PLMN中的MCC是否相等,
             通配符可以匹配0~9的任何数字，且非精确比较时，通配符不区分大小写
 输入参数  : VOS_UINT32    ulBcchMcc
             VOS_UINT32    ulSimMcc
             VOS_UINT8     ucWildcard
             VOS_UINT8     ucExactlyCmpFlg
 输出参数  : 无
 返 回 值  : VOS_TRUE: MCC相同
             VOS_FALSE: MCC不相同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年3月2日
   作    者   : c00318887
   修改内容   : 新生成函数
 2.日    期   : 2015年6月26日
   作    者   : w00316404
   修改内容   : 清理pc-lint告警
*****************************************************************************/
VOS_UINT32 TAF_SDC_CompareBcchMccwithSimMcc_WithWildcard(
    VOS_UINT32                          ulBcchMcc,
    VOS_UINT32                          ulSimMcc,
    VOS_CHAR                            cWildcard,
    VOS_UINT8                           ucExactlyCmpFlg
)
{
    VOS_UINT8                           ucBcchByte;
    VOS_UINT8                           ucSimByte;
    VOS_UINT32                          ulCmpRlst;
    VOS_UINT32                          ulIdx;
    VOS_UINT32                          ulShiftNum;

    /* 检查MCC是否相同 */
    for (ulIdx = 0; ulIdx < TAF_SDC_PLMN_MCC_LEN; ulIdx++)
    {
        ulShiftNum = ulIdx * 8;
        ucBcchByte = (VOS_UINT8)((ulBcchMcc & ((VOS_UINT32)TAF_SDC_MCC_MNC_BYTE_VALUE_MASK << ulShiftNum)) >> ulShiftNum);
        ucSimByte  = (VOS_UINT8)((ulSimMcc & ((VOS_UINT32)TAF_SDC_MCC_MNC_BYTE_VALUE_MASK << ulShiftNum)) >> ulShiftNum);

        ulCmpRlst  = TAF_SDC_CompareBcchPlmnBytewithSimPlmnByte_WithWildcard(
                                        ucBcchByte,
                                        ucSimByte,
                                        cWildcard);

        /* 如果某字节不等，则MCC不相同 */
        if (VOS_FALSE == ulCmpRlst)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_SDC_CompareBcchMnc3BytewithSimMnc3Byte
 功能描述  : 比较系统消息广播中PLMN中的MNC和SIM卡中存储PLMN中的MNC是否相等时,
             MNC的最高位是否需要特殊处理:
             1. 北美的国家码在310和316之间，比较最高位是否是0或F，则判为相同
             2. 如果是非精确比较，BCCH的MNC最高位是F时，则也判为相同
             注意参数顺序:
             1)一个plmn是Bcch格式的，一个plmn是Sim格式的进行比较时，
               Bcch格式的plmn必须作为第一个入参，sim格式的必须作为第二个入参
             2)两个Bcch格式的plmn比较时，入参顺序没关系
             3)两个Sim格式的plmn比较时，入参顺序没关系
 输入参数  : TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
             TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId,
             VOS_UINT8                           ucExactlyCmpFlg
 输出参数  : 无
 返 回 值  : VOS_TRUE: MNC最高位相同
             VOS_FALSE: MNC最高位不相同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年3月2日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_CompareBcchMnc3BytewithSimMnc3Byte(
    TAF_SDC_PLMN_ID_STRU               *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU               *pstSimPlmnId,
    VOS_UINT8                           ucExactlyCmpFlg
)
{
    VOS_UINT8                           ucBcchMnc3Byte;
    VOS_UINT8                           ucSimMnc3Byte;

    ucBcchMnc3Byte = (VOS_UINT8)((pstBccPlmnId->ulMnc & TAF_SDC_MCC_THIRD_BYTE_VALUE_MASK) >> 16);
    ucSimMnc3Byte  = (VOS_UINT8)((pstSimPlmnId->ulMnc & TAF_SDC_MCC_THIRD_BYTE_VALUE_MASK) >> 16);

    /* PLMN 属于 NA PCS1900,北美的国家码在310和316之间，要进行特殊处理 */
    if ((TAF_SDC_PCS1900_MCC_LOW_VALUE == (pstBccPlmnId->ulMcc & TAF_SDC_MCC_LOW_TWO_BYTE_VALUE_MASK))
     && (TAF_SDC_PCS1900_MCC_HIGH_VALUE_RANGE >= (pstSimPlmnId->ulMcc & TAF_SDC_MCC_THIRD_BYTE_VALUE_MASK)))
    {
        if ( ((TAF_SDC_PCS1900_MNC_THIRD_BYTE_VALUE_F == ucBcchMnc3Byte)
            && (TAF_SDC_PCS1900_MNC_THIRD_BYTE_VALUE_0 == ucSimMnc3Byte))
          || ((TAF_SDC_PCS1900_MNC_THIRD_BYTE_VALUE_0 == ucBcchMnc3Byte)
           && (TAF_SDC_PCS1900_MNC_THIRD_BYTE_VALUE_F == ucSimMnc3Byte)) )
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /* The MS shall compare using just the 1st 2 digits of the SIM-MNC
        with the BCCH-MNC. If the values match, then the HPLMN match succeeds,
        otherwise the HPLMN match fails.*/
        if ( (VOS_FALSE == ucExactlyCmpFlg)
          && (TAF_SDC_LOW_BYTE_INVALID == ucBcchMnc3Byte) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : TAF_SDC_CompareBcchMncwithSimMnc_WithWildcard
 功能描述  : 比较系统消息广播中PLMN中的MNC的低2个字节与SIM卡中存储PLMN中的MNC的低2个字节是否相等,
             通配符可以匹配0~9的任何数字，且非精确比较时，通配符不区分大小写
 输入参数  : VOS_UINT32    ulBcchMnc
             VOS_UINT32    ulSimMnc
             VOS_UINT8     ucWildcard
             VOS_UINT8     ucExactlyCmpFlg
 输出参数  : 无
 返 回 值  : VOS_TRUE: MCC的低2个字节相同
             VOS_FALSE: MCC的低2个字节不相同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年3月2日
   作    者   : c00318887
   修改内容   : 新生成函数
 2.日    期   : 2015年6月26日
   作    者   : w00316404
   修改内容   : 清理pc-lint告警
*****************************************************************************/
VOS_UINT32 TAF_SDC_CompareBcchMncLow2ByteWithSimMnclowLow2Byte_WithWildcard(
    VOS_UINT32                          ulBcchMnc,
    VOS_UINT32                          ulSimMnc,
    VOS_CHAR                            cWildcard,
    VOS_UINT8                           ucExactlyCmpFlg
)
{
    VOS_UINT8                           ucBcchByte;
    VOS_UINT8                           ucSimByte;
    VOS_UINT32                          ulCmpRlst;
    VOS_UINT32                          ulIdx;
    VOS_UINT32                          ulShiftNum;

    /*检查MCC是否相同*/
    for (ulIdx = 0; ulIdx < TAF_SDC_PLMN_MNC_LEN-1; ulIdx++)
    {
        ulShiftNum = ulIdx * 8;
        ucBcchByte = (VOS_UINT8)((ulBcchMnc & ((VOS_UINT32)TAF_SDC_MCC_MNC_BYTE_VALUE_MASK<<ulShiftNum)) >> ulShiftNum);
        ucSimByte  = (VOS_UINT8)((ulSimMnc & ((VOS_UINT32)TAF_SDC_MCC_MNC_BYTE_VALUE_MASK<<ulShiftNum)) >> ulShiftNum);

        ulCmpRlst  = TAF_SDC_CompareBcchPlmnBytewithSimPlmnByte_WithWildcard(
                                        ucBcchByte,
                                        ucSimByte,
                                        cWildcard);

        /*如果某字节不等，则MNC低2个字节不相同*/
        if (VOS_FALSE == ulCmpRlst)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_SDC_ConvertSimPlmnToNasPLMN
 功能描述  : 将SIM卡中的3字节格式PLMN转换为MCC和MNC分开的格式
            (10.5.1.3 Location Area Identification)
             8 7 6 5     4 3 2 1
            Location Area Identification IEI       octet 1
            MCC digit 2     MCC digit 1            octet 2
            MNC digit 3     MCC digit 3            octet 3
            MNC digit 2     MNC digit 1            octet 4

            例如: 32f020(mcc:0x000302,mnc:0x0f0200) --> 230,02f
 输入参数  : pstSimPlmn - sim卡格式plmn id
 输出参数  : pstNasPlmn - 转换后plmn id
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月16日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SDC_ConvertSimPlmnToNasPLMN(
    TAF_SDC_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    TAF_SDC_PLMN_ID_STRU                *pstNasPlmn
)
{
    VOS_UINT32                          ulTempData;
    TAF_SDC_PLMN_ID_STRU                stPlmn;

    /*
       PLMN BCD 编码 方式

       MCC digit 2,  MCC digit 1, ----OCTET 1
       MNC digit 3,  MCC digit 3, ----OCTET 2
       MNC digit 2,  MNC digit 1, ----OCTET 3
    */
    ulTempData = TAF_SDC_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[0]);
    stPlmn.ulMcc = ulTempData;
    ulTempData = (TAF_SDC_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[0])) >> TAF_SDC_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMcc |= ulTempData << TAF_SDC_OCTET_MOVE_EIGHT_BITS;

    ulTempData = TAF_SDC_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[1]);
    stPlmn.ulMcc |= ulTempData << TAF_SDC_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = (TAF_SDC_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[1])) >> TAF_SDC_OCTET_MOVE_FOUR_BITS;

    stPlmn.ulMnc = ulTempData << TAF_SDC_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = TAF_SDC_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[2]);
    stPlmn.ulMnc |= ulTempData;
    ulTempData = (TAF_SDC_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[2])) >> TAF_SDC_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMnc |= ulTempData << TAF_SDC_OCTET_MOVE_EIGHT_BITS;

    *pstNasPlmn = stPlmn;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_CompareBcchMncwithSimMnc_WithWildcard
 功能描述  : 比较系统消息广播中PLMN中的MNC与SIM卡中存储PLMN中的MNC是否相等,
             通配符可以匹配0~9的任何数字，且非精确比较时，通配符不区分大小写,
             PLMN 属于 NA PCS1900 特殊处理
             1)一个plmn是Bcch格式的，一个plmn是Sim格式的进行比较时，
               Bcch格式的plmn必须作为第一个入参，sim格式的必须作为第二个入参
             2)两个Bcch格式的plmn比较时，入参顺序没关系
             3)两个Sim格式的plmn比较时，入参顺序没关系
 输入参数  : TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
             TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId,
             VOS_UINT8                           ucWildcard
             VOS_UINT8                           ucExactlyCmpFlg
 输出参数  : 无
 返 回 值  : VOS_TRUE: MNC相同
             VOS_FALSE: MNC不相同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年3月2日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_CompareBcchMncwithSimMnc_WithWildcard(
    TAF_SDC_PLMN_ID_STRU               *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU               *pstSimPlmnId,
    VOS_CHAR                            cWildcard,
    VOS_UINT8                           ucExactlyCmpFlg
)
{
    VOS_UINT8                           ucBcchMnc3Byte;
    VOS_UINT8                           ucSimMnc3Byte;
    VOS_UINT32                          ulMncLow2ByteCmpRlst;
    VOS_UINT32                          ulMnc3ByteCmpRlst;

    /* 检查MNC的低2个字节是否相同 */
    ulMncLow2ByteCmpRlst = TAF_SDC_CompareBcchMncLow2ByteWithSimMnclowLow2Byte_WithWildcard(
                                        pstBccPlmnId->ulMnc,
                                        pstSimPlmnId->ulMnc,
                                        cWildcard,
                                        ucExactlyCmpFlg);

    /* MNC的低2个字节不同，则MNC不同 */
    if (VOS_FALSE == ulMncLow2ByteCmpRlst)
    {
        return VOS_FALSE;
    }

    /* MNC的低2个字节相同，再检查MNC的第3个字节是否相同 */
    ucBcchMnc3Byte = (VOS_UINT8)((pstBccPlmnId->ulMnc & TAF_SDC_MCC_THIRD_BYTE_VALUE_MASK) >> 16);
    ucSimMnc3Byte  = (VOS_UINT8)((pstSimPlmnId->ulMnc & TAF_SDC_MCC_THIRD_BYTE_VALUE_MASK) >> 16);

    ulMnc3ByteCmpRlst = TAF_SDC_CompareBcchPlmnBytewithSimPlmnByte_WithWildcard(
                                    ucBcchMnc3Byte,
                                    ucSimMnc3Byte,
                                    cWildcard);

    /* MNC的第3个字节也相等，则MNC相同 */
    if (VOS_TRUE == ulMnc3ByteCmpRlst)
    {
        return VOS_TRUE;
    }
    else
    {
        /* MNC最高位不相同，需要判断是否需要特殊处理*/
        ulMnc3ByteCmpRlst = TAF_SDC_CompareBcchMnc3BytewithSimMnc3Byte(
                                        pstBccPlmnId,
                                        pstSimPlmnId,
                                        ucExactlyCmpFlg);

        return ulMnc3ByteCmpRlst;
    }


}


/*****************************************************************************
 函 数 名  : TAF_SDC_IsValidWildcard
 功能描述  : 判断PLMN中的通配符是否是有效的通配符
 输入参数  : VOS_CHAR    ucWildcard  --- 通配符
 输出参数  : 无
 返 回 值  : VOS_TRUE: 有效通配符
             VOS_FALSE: 无效通配符
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年3月18日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_IsValidWildcard(
    VOS_CHAR                            cWildcard
)
{
    VOS_CHAR                            cUpperWildCard;

    cUpperWildCard = VOS_CharToUpper(cWildcard);

    /* 通配符只能在 'A-F','a-f',取值 */
    if ( ('A' <= cUpperWildCard)
      && (cUpperWildCard <= 'F'))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}
/*****************************************************************************
 函 数 名  : TAF_SDC_HexToAsciiOfPlmnByte
 功能描述  : 将PLMN中的某字节十六进制表示的通配符转换成ASCII字符
             比如: 0xA ---'A'; 0x2 ---'2', 不在0x0- -0x9,0xA--0xF范围则不变
 输入参数  : VOS_UINT8    ucSrc  ---  通配符0-F的十六进制表示
 输出参数  : VOS_UINT8   *pucDst ---  转换后的ASCII字符
 返 回 值  : VOS_FALSE           --- 不合格式
             VOS_TRUE            --- 格式正确，转换正确
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年3月18日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_HexToAsciiOfPlmnByte(
    VOS_UINT8                            ucSrc,
    VOS_UINT8                           *pucDst
)
{
    if (10 > ucSrc)
    {
        /* 0x0-0x9 ---'0'-'9' */
        *pucDst = ucSrc + 0x30;
    }
    else if (16 > ucSrc)
    {
        /* 0xA-0xF ---'A'-'F' */
        *pucDst = ucSrc + 'A' - 10;
    }
    else
    {
        *pucDst = ucSrc;
    }

}


/*****************************************************************************
 函 数 名  : TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn_WithWildcard
 功能描述  : 比较系统消息广播中PLMN与SIM卡中存储PLMN是否相等,
              但PLMN 中MCC 和/或MNC 可能带有通配符，通配符可以和0~9 中的任何值匹配
             1)一个plmn是Bcch格式的，一个plmn是Sim格式的进行比较时，
               Bcch格式的plmn必须作为第一个入参，sim格式的必须作为第二个入参
             2)两个Bcch格式的plmn比较时，入参顺序没关系
             3)两个Sim格式的plmn比较时，入参顺序没关系
 输入参数  : TAF_SDC_PLMN_ID_STRU    *pstBccPlmnId
             TAF_SDC_PLMN_ID_STRU    *pstSimPlmnId
             VOS_UINT8                        ucWildcard
 输出参数  : 无
 返 回 值  : VOS_TRUE: PLMN ID相同
             VOS_FALSE: PLMN ID不相同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月26日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn_WithWildcard(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId,
    VOS_CHAR                             cWildcard
)
{
    VOS_UINT32                          ulMccCmpRlst;
    VOS_UINT32                          ulMncCmpRlst;

    /* 通配符是否有效 */
    if (VOS_FALSE == TAF_SDC_IsValidWildcard(cWildcard))
    {
        return VOS_FALSE;
    }

    /* 检查MCC是否相同 */
    ulMccCmpRlst = TAF_SDC_CompareBcchMccwithSimMcc_WithWildcard(
                                        pstBccPlmnId->ulMcc,
                                        pstSimPlmnId->ulMcc,
                                        cWildcard,
                                        VOS_TRUE);
    if (VOS_FALSE == ulMccCmpRlst)
    {
        return VOS_FALSE;
    }



    /* MCC相等，再检查MNC是否相同 */
    ulMncCmpRlst = TAF_SDC_CompareBcchMncwithSimMnc_WithWildcard(
                                        pstBccPlmnId,
                                        pstSimPlmnId,
                                        cWildcard,
                                        VOS_TRUE);

    return ulMncCmpRlst;


}

/*****************************************************************************
 函 数 名  : TAF_SDC_ConvertPlmnId2NasStyle
 功能描述  : 将原PLMNid转化为NAS内部使用格式记录
             例如:MCC为460,MNC为01时,
             pstPlmnId->Mcc = 0x000604      pstPlmnId->Mcc = 0x00000460
                                        <----
             pstPlmnId->Mnc = 0x000100      pstPlmnId->Mnc = 0x00000001
 输入参数  : TAF_PLMN_ID_STRU *pstPlmnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月25日
   作    者   : z00161729
   修改内容   : AT&T 支持EONS特性修改

*****************************************************************************/
VOS_VOID TAF_SDC_ConvertPlmnId2NasStyle(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
)
{
    VOS_UINT8                           ucI;
    VOS_UINT8                           aucTmp[4];
    VOS_UINT32                          ulTmp;

    ulTmp           = pstPlmnId->ulMcc;
    pstPlmnId->ulMcc  = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }
    pstPlmnId->ulMcc  =  aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);

    ulTmp           = pstPlmnId->ulMnc;
    pstPlmnId->ulMnc  = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }

    if(0xf == aucTmp[2])
    {
        pstPlmnId->ulMnc =  aucTmp[1]
                         |((VOS_UINT32)aucTmp[0] << 8)
                         |0x0f0000;
    }
    else
    {
        pstPlmnId->ulMnc =   aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);
    }
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetOplFileType
 功能描述  : 获取的OPL文件类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_FILE_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月2日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_FILE_TYPE_ENUM_UINT8  TAF_SDC_GetOplFileType(VOS_VOID)
{
    VOS_UINT8                           ucSimType;
    TAF_SDC_OPL_FILE_INFO_STRU         *pstUsimOplInfo = VOS_NULL_PTR;
    TAF_SDC_OPL_FILE_INFO_STRU         *pstSimOplInfo = VOS_NULL_PTR;

    pstUsimOplInfo = TAF_SDC_GetUsimOplFileInfo();
    pstSimOplInfo  = TAF_SDC_GetSimOplFileInfo();
    ucSimType      = 0;

    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

    if ((USIMM_CARD_SIM == ucSimType)
     && (0 != pstSimOplInfo->ulOplRecordNum))
    {
        return TAF_SDC_FILE_TYPE_SIM;
    }

    if (USIMM_CARD_USIM == ucSimType)
    {
        if (0 != pstUsimOplInfo->ulOplRecordNum)
        {
            return TAF_SDC_FILE_TYPE_USIM;
        }

        if (0 != pstSimOplInfo->ulOplRecordNum)
        {
            return TAF_SDC_FILE_TYPE_SIM;
        }
    }

    return TAF_SDC_FILE_TYPE_BUTT;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetPnnFileType
 功能描述  : 获取的PNN文件类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_FILE_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月2日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_FILE_TYPE_ENUM_UINT8  TAF_SDC_GetPnnFileType(VOS_VOID)
{
    VOS_UINT8                           ucSimType;
    TAF_SDC_PNN_FILE_INFO_STRU         *pstUsimPnnInfo = VOS_NULL_PTR;
    TAF_SDC_PNN_FILE_INFO_STRU         *pstSimPnnInfo = VOS_NULL_PTR;

    ucSimType      = 0;
    pstUsimPnnInfo = TAF_SDC_GetUsimPnnFileInfo();
    pstSimPnnInfo  = TAF_SDC_GetSimPnnFileInfo();

    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

    if ((USIMM_CARD_SIM == ucSimType)
     && (0 != pstSimPnnInfo->ulPnnRecordNum))
    {
        return TAF_SDC_FILE_TYPE_SIM;
    }

    if (USIMM_CARD_USIM == ucSimType)
    {
        if (0 != pstUsimPnnInfo->ulPnnRecordNum)
        {
            return TAF_SDC_FILE_TYPE_USIM;
        }

        if (0 != pstSimPnnInfo->ulPnnRecordNum)
        {
            return TAF_SDC_FILE_TYPE_SIM;
        }
    }

    return TAF_SDC_FILE_TYPE_BUTT;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetSpdiFileInfo
 功能描述  : 获取的SPDI文件信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_SPDI_FILE_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月2日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetSpdiFileInfo(VOS_VOID)
{
    VOS_UINT8                           ucSimType;
    TAF_SDC_SPDI_FILE_INFO_STRU        *pstUsimSpdiInfo = VOS_NULL_PTR;
    TAF_SDC_SPDI_FILE_INFO_STRU        *pstSimSpdiInfo = VOS_NULL_PTR;

    ucSimType       = 0;
    pstUsimSpdiInfo = TAF_SDC_GetUsimSpdiFileInfo();
    pstSimSpdiInfo  = TAF_SDC_GetSimSpdiFileInfo();

    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

    if (USIMM_CARD_SIM == ucSimType)
    {
        return pstSimSpdiInfo;
    }

    if (USIMM_CARD_USIM == ucSimType)
    {
        if (0 != pstUsimSpdiInfo->ucServiceProviderPlmnNum)
        {
            return pstUsimSpdiInfo;
        }

        if (0 != pstSimSpdiInfo->ucServiceProviderPlmnNum)
        {
            return pstSimSpdiInfo;
        }
    }

    return pstUsimSpdiInfo;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_IsOperNameTypeSupport
 功能描述  : 判断pnn或spn或mm info或cphs是否支持
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
             VOS_FALSE:不支持
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_SDC_IsOperNameTypeSupport(
    TAF_SDC_OPER_NAME_TYPE_ENUM_UINT8   enOperNameType
)
{
    TAF_SDC_OPER_NAME_TYPE_PRIO_STRU   *pstOperNamePrio = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstOperNamePrio = TAF_SDC_GetOperNamePrio();

    for (ucIndex = 0; ucIndex < pstOperNamePrio->ucOperNamePrioNum; ucIndex++)
    {
        if (enOperNameType == pstOperNamePrio->aucOperNameTypePrio[ucIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_CompareBcchPlmnwithSimPlmn_WithWildValue
 功能描述  : 比较系统消息广播中PLMN与SIM卡中存储PLMN是否相等,
             但PLMN 中MCC 和/或MNC 可能带有通配符，通配符可以和0~9 中的任何值匹配
             1)一个plmn是Bcch格式的，一个plmn是Sim格式的进行比较时，
               Bcch格式的plmn必须作为第一个入参，sim格式的必须作为第二个入参
             2)两个Bcch格式的plmn比较时，入参顺序没关系
             3)两个Sim格式的plmn比较时，入参顺序没关系
 输入参数  : TAF_SDC_PLMN_ID_STRU    *pstBccPlmnId
             TAF_SDC_PLMN_ID_STRU    *pstSimPlmnId
             VOS_UINT8               ucWildcard
 输出参数  : 无
 返 回 值  : VOS_TRUE: PLMN ID相同
             VOS_FALSE: PLMN ID不相同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月26日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_CompareBcchPlmnwithSimPlmn_WithWildcard(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId,
    VOS_CHAR                             cWildcard
)
{
    VOS_UINT32                          ulCmpRlst;
    VOS_UINT32                          ulMccCmpRlst;
    VOS_UINT32                          ulMncCmpRlst;

    /* 如果需要精确比较*/
    if (VOS_TRUE == TAF_SDC_GetPlmnExactlyCompareFlg())
    {
        ulCmpRlst = TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn_WithWildcard(pstBccPlmnId, pstSimPlmnId, cWildcard);

        return ulCmpRlst;
    }

    /* 通配符是否有效 */
    if (VOS_FALSE == TAF_SDC_IsValidWildcard(cWildcard))
    {
        return VOS_FALSE;
    }

    /* 检查MCC是否相同 */
    ulMccCmpRlst = TAF_SDC_CompareBcchMccwithSimMcc_WithWildcard(
                                        pstBccPlmnId->ulMcc,
                                        pstSimPlmnId->ulMcc,
                                        cWildcard,
                                        VOS_FALSE);
    if (VOS_FALSE == ulMccCmpRlst)
    {
        return VOS_FALSE;
    }



    /* MCC相等，再检查MNC是否相同 */
    ulMncCmpRlst = TAF_SDC_CompareBcchMncwithSimMnc_WithWildcard(
                                        pstBccPlmnId,
                                        pstSimPlmnId,
                                        cWildcard,
                                        VOS_FALSE);

    return ulMncCmpRlst;

}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetImsiHomePlmn
 功能描述  : 根据IMSI和MNC长度得到HPLMN
 输入参数  : VOS_UINT8                          *pucImsi
             VOS_UINT8                           ucUsimMncLenth
 输出参数  : 无
 返 回 值  : TAF_SDC_PLMN_ID_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_PLMN_ID_STRU  TAF_SDC_GetImsiHomePlmn(
    VOS_UINT8                          *pucImsi,
    VOS_UINT8                           ucUsimMncLenth
)
{
    TAF_SDC_PLMN_ID_STRU                stHplmn;

    PS_MEM_SET(&stHplmn, 0, sizeof(TAF_SDC_PLMN_ID_STRU));

    stHplmn.ulMcc |= (pucImsi[1] & TAF_SDC_OCTET_HIGH_FOUR_BITS) >> TAF_SDC_OCTET_MOVE_FOUR_BITS;
    stHplmn.ulMcc |= (pucImsi[2] & TAF_SDC_OCTET_LOW_FOUR_BITS) << TAF_SDC_OCTET_MOVE_EIGHT_BITS;
    stHplmn.ulMcc |= (pucImsi[2] & TAF_SDC_OCTET_HIGH_FOUR_BITS) << TAF_SDC_OCTET_MOVE_TWELVE_BITS;
    stHplmn.ulMnc |= (pucImsi[3] & TAF_SDC_OCTET_LOW_FOUR_BITS);
    stHplmn.ulMnc |= (pucImsi[3] & TAF_SDC_OCTET_HIGH_FOUR_BITS) << TAF_SDC_OCTET_MOVE_FOUR_BITS;

    if ((TAF_SDC_MNC_LENGTH_TWO_BYTES_IN_IMSI == ucUsimMncLenth))
    {
        stHplmn.ulMnc |= (TAF_SDC_LOW_BYTE_INVALID) << TAF_SDC_OCTET_MOVE_SIXTEEN_BITS;
    }
    else
    {
        stHplmn.ulMnc |= (pucImsi[4] & TAF_SDC_OCTET_LOW_FOUR_BITS) << TAF_SDC_OCTET_MOVE_SIXTEEN_BITS;
    }

    /* 对于中移动卡的特殊处理需要保留,添加2位MNC的HPLMN到Hplmn列表中,
      移动MCC=460,MNC=02和07中国移动卡特殊处理
    */
    if (( 0x000604 == stHplmn.ulMcc )
     && ( (0x200   == (stHplmn.ulMnc & 0xFFFF ) )
       || (0x700   == (stHplmn.ulMnc & 0xFFFF))))
    {
        stHplmn.ulMnc &= 0xFF0000;
    }

    return stHplmn;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_IsImsSrvExist
 功能描述  : 当前是否存在IMS业务
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_TRUE:  存在
             VOS_FALSE: 不存在
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : IMS动态开关配置项目
*****************************************************************************/
VOS_UINT32 TAF_SDC_IsImsSrvExist(VOID)
{
    VOS_UINT8                           ucImsVoiceFlag;
    VOS_UINT8                           ucImsSmsFlag;
    VOS_UINT8                           ucImsSsFlag;

    ucImsVoiceFlag  = TAF_SDC_GetImsCallExistFlg();
    ucImsSmsFlag    = TAF_SDC_GetImsSmsSrvExistFlg();
    ucImsSsFlag     = TAF_SDC_GetImsSsSrvExistFlg();

    if ((VOS_TRUE == ucImsVoiceFlag)
     || (VOS_TRUE == ucImsSmsFlag)
     || (VOS_TRUE == ucImsSsFlag))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}



VOS_UINT32 TAF_SDC_IsSysCfgRatSupportHrpdAndLte(VOS_VOID)
{
    /* syscfg set both support HRPD and LTE, we consider it's CL mode */
    VOS_UINT32                          ulLteSupport;

    ulLteSupport = TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_LTE);

    if ((VOS_TRUE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_EVDO))
     && (VOS_TRUE == ulLteSupport))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlmnIdValid
 功能描述  : 判断PLMN ID是否有效
 输出参数  : VOS_VOID
 返 回 值  : VOS_FALSE  : PLMN ID是无效值
             VOS_TRUE : PLMN ID是有效值
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年05月29日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_IsPlmnIdValid(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
)
{
    VOS_UINT32                          ulResult;

    /*
    The coding of this field is the responsibility of each administration but
    BCD coding shall be used. The MNC shall consist of 2 or 3 digits.
    If a network operator decides to use only two digits in the MNC,
    bits 5 to 8 of octet 7 shall be coded as "1111".
    MCC digit 2     MCC digit 1
    MNC digit 3     MCC digit 3
    MNC digit 2     MNC digit 1
    */

    ulResult = VOS_TRUE;

    if ( ((pstPlmnId->ulMcc & TAF_SDC_MCC_MNC_BYTE_VALUE_MASK) > TAF_SDC_MAX_DIGIT_VALUE)
      || (((pstPlmnId->ulMcc >> 8) & TAF_SDC_MCC_MNC_BYTE_VALUE_MASK) > TAF_SDC_MAX_DIGIT_VALUE)
      || (((pstPlmnId->ulMcc >> 16) & TAF_SDC_MCC_MNC_BYTE_VALUE_MASK) > TAF_SDC_MAX_DIGIT_VALUE))
    {
        ulResult = VOS_FALSE;
    }

    if ((((pstPlmnId->ulMnc) & TAF_SDC_MCC_MNC_BYTE_VALUE_MASK) > TAF_SDC_MAX_DIGIT_VALUE)
     || (((pstPlmnId->ulMnc >> 8) & TAF_SDC_MCC_MNC_BYTE_VALUE_MASK) > TAF_SDC_MAX_DIGIT_VALUE))
    {
        ulResult = VOS_FALSE;
    }

    if ((((pstPlmnId->ulMnc >> 16) & TAF_SDC_MCC_MNC_BYTE_VALUE_MASK) > TAF_SDC_MAX_DIGIT_VALUE)
     && (((pstPlmnId->ulMnc >> 16) & TAF_SDC_MCC_MNC_BYTE_VALUE_MASK) != TAF_SDC_LOW_BYTE_INVALID))
    {
        ulResult = VOS_FALSE;
    }

    return ulResult;
}



/*****************************************************************************
 函 数 名  : TAF_SDC_IsPlatformRatCapNvimValid
 功能描述  : 检查从NV中读取平台接入技术能力是否有效
 输入参数  : pstNvPlatformRatCap 平台接入技术能力的NV项结构体指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:平台接入技术能力NV项有效
             VOS_FALSE:平台接入技术能力NV项无效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : s46746
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsPlatformRatCapNvimValid(
    PLATAFORM_RAT_CAPABILITY_STRU      *pstNvPlatformRatCap
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* 如果平台支持的接入技术个数为0，返回无效 */
    if (0 == pstNvPlatformRatCap->usRatNum)
    {
        return VOS_FALSE;
    }

    for (i = 0; i < pstNvPlatformRatCap->usRatNum; i++)
    {
        /* 如果平台支持的接入技术有重复，返回无效  */
        for (j = i + 1 ; j < pstNvPlatformRatCap->usRatNum; j++)
        {
            if (pstNvPlatformRatCap->aenRatList[i] == pstNvPlatformRatCap->aenRatList[j])
            {
                return VOS_FALSE;
            }
        }

        /* 如果平台支持的接入技术大于或等于BUTT，返回无效 */
        if (pstNvPlatformRatCap->aenRatList[i] >= PLATFORM_RAT_BUTT)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_ConvertNvPlatformRatToTafType
 功能描述  : 把NV类型的平台接入技术能力转换成TAF类型的
 输入参数  : enNvPlatformRatCap:NV类型的平台接入技术能力
 输出参数  : 无
 返 回 值  : TAF类型的平台接入技术能力
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : s46746
    修改内容   : 新增函数

  2.日    期   : 2014年07月18日
    作    者   : y00213812
    修改内容   : 新增CDMA的1X和EVDO模式

*****************************************************************************/
TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8 TAF_SDC_ConvertNvPlatformRatToTafType(
    PLATFORM_RAT_TYPE_ENUM_UINT16       enNvPlatformRatCap
)
{
    TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8                    enTafSdcPlatformRat;

    switch (enNvPlatformRatCap)
    {
        case PLATFORM_RAT_GSM:
            enTafSdcPlatformRat = TAF_SDC_PLATFORM_RAT_GSM;
            break;

        case PLATFORM_RAT_WCDMA:
            enTafSdcPlatformRat = TAF_SDC_PLATFORM_RAT_WCDMA;
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        case PLATFORM_RAT_TDS:
            enTafSdcPlatformRat = TAF_SDC_PLATFORM_RAT_TDS;
            break;
#endif

#if   (FEATURE_ON == FEATURE_LTE)
        case PLATFORM_RAT_LTE:
            enTafSdcPlatformRat = TAF_SDC_PLATFORM_RAT_LTE;
            break;
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case PLATFORM_RAT_1X:
            enTafSdcPlatformRat = TAF_SDC_PLATFORM_RAT_1X;
            break;

        case PLATFORM_RAT_HRPD:
            enTafSdcPlatformRat = TAF_SDC_PLATFORM_RAT_HRPD;
            break;

#endif
        default:
            enTafSdcPlatformRat = TAF_SDC_PLATFORM_RAT_BUTT;
            break;
    }

    return enTafSdcPlatformRat;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_IsSyscfgSupportSpecRat
 功能描述  : 判断当前SYSCFG是否支持特定的接入技术
 输入参数  : TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月30日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsSyscfgSupportSpecRat(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
)
{
    VOS_UINT8                           i;
    TAF_SDC_RAT_PRIO_STRU              *pstRatPrioList;

    pstRatPrioList = TAF_SDC_GetMsPrioRatList();

    for (i = 0; i < pstRatPrioList->ucRatNum; i++)
    {
        if (enSysMode == pstRatPrioList->aenRatPrio[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_IsCurrentNormalServiceStatus
 功能描述  : 判断当前是只是单域的服务状态处于非normal service
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:仅单个域非normal service，
             VOS_FALSE:CS/PS域都不能提供正常服务
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 TAF_SDC_IsCurrentNormalServiceStatus(void)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulPsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulCsServiceStatus;

    ulCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    ulPsServiceStatus = TAF_SDC_GetPsServiceStatus();

    /* 更新总的服务状态 */
    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulCsServiceStatus)
     || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulPsServiceStatus))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}

/*****************************************************************************
 函 数 名  : TAF_SDC_IsCurrentNormalRegStatus
 功能描述  : 判断当前是只是单域的注册状态处于非normal service
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:仅单个域非normal service，
             VOS_FALSE:CS/PS域都不能提供正常服务
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月11日
    作    者   : w00281933
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 TAF_SDC_IsCurrentNormalRegStatus(void)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8   ucPsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8   ulCsRegStatus;

    ulCsRegStatus = TAF_SDC_GetCsRegStatus();
    ucPsRegStatus = TAF_SDC_GetPsRegStatus();

    /* 更新总的服务状态 */
    if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK == ulCsRegStatus)
     || (TAF_SDC_REG_REGISTERED_ROAM == ulCsRegStatus))
    {
        return VOS_TRUE;
    }
    else if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK == ucPsRegStatus)
          || (TAF_SDC_REG_REGISTERED_ROAM == ucPsRegStatus))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}


/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateRoamFlag
 功能描述  : 更新MMA保存的RoamFlag标示
 输入参数  : enRegState       --MMC上报的注册状态消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月11日
   作    者   : w00281933
   修改内容   : 新生成函数(服务状态优化Phase II  合入时,把这个函数移到 TFA_MMA_COMM_FUNC.C)
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateRoamFlag(
    TAF_SDC_REG_STATUS_ENUM_UINT8      enRegState
)
{
    switch (enRegState)
    {
        case TAF_SDC_REG_REGISTERED_HOME_NETWORK:
            TAF_SDC_SetRoamFlag(VOS_FALSE);
            break;

        case TAF_SDC_REG_REGISTERED_ROAM:
            TAF_SDC_SetRoamFlag(VOS_TRUE);
            break;

        default:
            break;
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedReportRegStatus_RegStatusInd
 功能描述  : 收到注册状态时，是否需要上报注册状态
 输入参数  : 服务域，旧的注册状态，新的注册状态
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要上报
             VOS_FALSE: 不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月11日
    作    者   : w00281933
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsAppSepcDomainRegStaChg(
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enCnDomainId,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState
)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppCsRegState;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppPsRegState;

    enAppCsRegState = TAF_SDC_GetAppCsRegStatus();
    enAppPsRegState = TAF_SDC_GetAppPsRegStatus();


    if (TAF_SDC_SERVICE_DOMAIN_CS== enCnDomainId)
    {
        /* cs域注册状态变化时上报 */
        if (enAppCsRegState != enRegState)
        {
            return VOS_TRUE;
        }
    }
    else if (TAF_SDC_SERVICE_DOMAIN_PS == enCnDomainId)
    {
        /* ps域注册状态变化时上报 */
        if (enAppPsRegState != enRegState)
        {
            return VOS_TRUE;
        }
    }
    else
    {
        return VOS_FALSE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedReportRegStatusWhenNonnormalService_RegStatusInd
 功能描述  : 非正常服务时是否需要上报注册状态改变
 输入参数  : 服务域，旧的注册状态，新的注册状态
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要上报
             VOS_FALSE: 不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月28日
    作    者   : z00359541
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_IsNeedReportRegStatusWhenNonnormalService(
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enCnDomainId,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState
)
{
    TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU            *pstNonnormalRegStatusMergeCfg = VOS_NULL_PTR;
    TAF_SDC_REG_STATUS_ENUM_UINT8                           enAppCsRegState;
    TAF_SDC_REG_STATUS_ENUM_UINT8                           enAppPsRegState;

    enAppCsRegState                 = TAF_SDC_GetAppCsRegStatus();
    enAppPsRegState                 = TAF_SDC_GetAppPsRegStatus();
    pstNonnormalRegStatusMergeCfg   = TAF_SDC_GetNonnormalRegStatusMergeCfg();

    if (VOS_TRUE == pstNonnormalRegStatusMergeCfg->ucMergeFlg)
    {
        if (TAF_SDC_CREG_TYPE_BREVITE == TAF_SDC_GetCregType())
        {
            /* CS域下的判断 */
            if (TAF_SDC_SERVICE_DOMAIN_CS == enCnDomainId)
            {
                if (((NAS_MSCC_PIF_REG_NOT_REGISTERED_NOT_SEARCH == enAppCsRegState )
                  || (NAS_MSCC_PIF_REG_NOT_REGISTERED_SEARCHING == enAppCsRegState))
                && ((NAS_MSCC_PIF_REG_NOT_REGISTERED_SEARCHING == enRegState)
                 || (NAS_MSCC_PIF_REG_NOT_REGISTERED_NOT_SEARCH == enRegState)))
                {
                    return VOS_FALSE;
                }
            }
        }

        if (TAF_SDC_CREG_TYPE_BREVITE == TAF_SDC_GetCgregType())
        {

            /* PS域下的判断 */
            if (TAF_SDC_SERVICE_DOMAIN_PS == enCnDomainId)
            {
                if (((NAS_MSCC_PIF_REG_NOT_REGISTERED_NOT_SEARCH == enAppPsRegState )
                  || (NAS_MSCC_PIF_REG_NOT_REGISTERED_SEARCHING == enAppPsRegState))
                && ((NAS_MSCC_PIF_REG_NOT_REGISTERED_SEARCHING == enRegState)
                 || (NAS_MSCC_PIF_REG_NOT_REGISTERED_NOT_SEARCH == enRegState)))
                {
                    return VOS_FALSE;
                }
            }
        }
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_IsSpecRatInRatList
 功能描述  : 判断特定的接入技术是否在接入技术列表中
 输入参数  : TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType,
             TAF_MMA_RAT_ORDER_STRU             *pstRatList
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月30日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_IsSpecRatInRatList(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType,
    TAF_MMA_RAT_ORDER_STRU             *pstRatList
)
{
    VOS_UINT8                           i;

    if (VOS_NULL_PTR == pstRatList)
    {
        return VOS_FALSE;
    }

    for (i = 0; i < TAF_SDC_MIN(pstRatList->ucRatOrderNum, TAF_PH_MAX_GUL_RAT_NUM); i++)
    {
        if (enRatType == pstRatList->aenRatOrder[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_SDC_CovertCimisNumToBcd
 功能描述  : 转换号码为十进制
 输入参数  : ulSrcValude  -- BCD码长度
             ulCodeMode   -- BCD码存放的位置

 输出参数  : 无
 返 回 值  : VOS_UINT32 -按照协议还原计算值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : y00245242
    修改内容   : Create
*****************************************************************************/
VOS_UINT32 TAF_SDC_CovertCimisNumToBcd(VOS_UINT32 ulSrcValude, VOS_UINT32 ulCodeMode)
{
    VOS_UINT32                          ulTempl   = 0;
    VOS_UINT32                          ulDstValue = 0;

    if (ulCodeMode >= 3)
    {
        ulTempl = ulSrcValude / 100;        /*百位*/
        if (ulTempl + 1 <= 9)
        {
            ulDstValue += (ulTempl + 1) * 100;
        }
    }

    if (ulCodeMode >= 2)
    {
        ulTempl = (ulSrcValude / 10)  % 10; /*十位*/
        if ( ulTempl+1 <= 9)
        {
            ulDstValue += (ulTempl+1 ) * 10;
        }
    }

    if (ulCodeMode >= 1)
    {
        ulTempl = ulSrcValude % 10;         /*个位*/
        if (ulTempl +1 <= 9)
        {
            ulDstValue += ulTempl +1;
        }
    }

    return ulDstValue;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_ConvertCImsiBcdCode
 功能描述  : 转换CIMSI格式到BCD码
 输入参数  : VOS_UINT8 *pucCIMSI       -- BCD码存放的位置
             VOS_UINT8 *pucAsciiStr  -- 字符串写入位置

 输出参数  : pucStrCIMSI 存放转换后字符

 返 回 值  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : y00245242
    修改内容   : 新建
*****************************************************************************/
VOS_UINT32 TAF_SDC_ConvertCImsiBcdCode(
    VOS_UINT8                           *pucCIMSI,
    VOS_UINT8                           *pucStrCIMSI)
{
    VOS_UINT32                          ulMCC     = 0; /* 国家代号 */
    VOS_UINT32                          ulMNC     = 0; /* 网络代号 */
    VOS_UINT32                          ulMSIN_A  = 0; /* 移动用户身份第0 - 3位*/
    VOS_UINT32                          ulMSIN_B  = 0; /* 移动用户身份第4 - 10位*/
    VOS_UINT32                          ulMSIN_B1 = 0; /* 移动用户身份第4 - 6位*/
    VOS_UINT32                          ulMSIN_B2 = 0; /* 移动用户身份第7位*/
    VOS_UINT32                          ulMSIN_B3 = 0; /* 移动用户身份第8 - 10位*/
/*
    6F22格式：
    00 AA AA BB BB BB CC 80 DD DD

    00代表CLASS=0
    AA AA根据MIN前3位计算
    BB BB BB根据MIN后7位计算
    CC根据MNC计算
    80代表IMSI_M_PROGRAMMED=1、IMSI_M_ADD_NUM=0

    DD DD根据MCC计算
    参照CDMA2000协议中6F22的格式，第1个字节和第7个字节都好搞定，基本就是标志位的设置。

    计算AA AA步骤
    1、以MIN的前3位为计算数据，分割成3个个位数，分别命名为D1、D2、D3
    2、计算数字NUM = D1 * 100 + D2 * 10 + D3 - 111（如D1、D2、D3中出现0，则当作10计算）
    3、将NUM转换为2字节小端格式16进制，位数不足在前面用0补。AA AA计算完毕

    计算BB BB BB步骤
    1、以MIN第4-6位为数据，按照AA AA的计算步骤1、2算出NUM，将NUM转换为10bit的2进制，不足用0补
    2、将MIN第7位单独取出来，按照标准10进制转2进制的计算方法，计算出4bit的2进制，不足用0补(修正：如果是0，按照10计算)
    3、以MIN第8-10位为数据，按照AA AA的计算步骤1、2算出NUM，将NUM转换为10bit的2进制，不足用0补
    4、将前3步的计算出来的共24bit的2进制数拼起来，转换成3字节小端格式16进制数。BB BB BB计算完毕

    计算CC步骤
    1、将MNC分割成2个个位数，分别命名为D1、D2
    2、计算数字NUM = D1 * 10 + D2 - 11（如D1、D2中出现0，则当作10计算）
    3、将NUM转换为1字节16进制。CC计算完毕

    计算DD DD步骤
    1、以MCC为数据，按照AA AA的计算方法，计算出2字节小端格式16进制，即为DD DD

    例子：
    已知IMSI号：460036591141482
    此IMSI中：
    MCC是460
    MNC是03
    MIN是6591141482

    计算AA AA
    MIN前3位659，NUM = 6 * 100 + 5 * 10 + 9 - 111 = 548 转换成2字节小端格式16进制为：24 02

    计算BB BB BB
    MIN第4-6位114，NUM = 1 * 100 + 1 * 10 + 4 - 111 = 3 转换成10bit的2进制为：0000000011
    MIN第7位1，转换为4bit的2进制为：0001
    MIN第8-10位482，NUM = 4 * 100 + 8 * 10 + 2 - 111 = 371 转换成10bit的2进制为：0101110011
    24bit的2进制数为：000000001100010101110011，转换成3字节小端格式16进制为：73 C5 00

    计算CC
    MNC为03，NUM = 10 * 10 + 3 - 11 = 92，转换成1字节16进制为5C

    计算DD DD
    MCC为460，NUM = 4 * 100 + 6 * 10 + 10 - 111 = 359 转换成2字节小端格式16进制为：67 01

    至此得到6F22文件内容应为
    00 24 02 73 C5 00 5C 80 67 01
    460036591141482
*/
    pucStrCIMSI[0] = 0x08;

    ulMCC     = pucCIMSI[8];
    ulMCC     = 0x0000FFFF & ( ulMCC | (pucCIMSI[9] << 8));
    ulMCC     = TAF_SDC_CovertCimisNumToBcd(ulMCC,3);       /* 国家代号 */
    pucStrCIMSI[1] = 0x09 | TAF_STD_ConvertDeciDigitToBcd((VOS_UINT8)(ulMCC/100), VOS_TRUE);
    pucStrCIMSI[2] = TAF_STD_ConvertDeciDigitToBcd((VOS_UINT8)(ulMCC%100), VOS_TRUE);

    ulMNC     = pucCIMSI[6];
    ulMNC     = TAF_SDC_CovertCimisNumToBcd(ulMNC,2);       /* 网络代号 */
    pucStrCIMSI[3] = TAF_STD_ConvertDeciDigitToBcd((VOS_UINT8)(ulMNC), VOS_TRUE);

    ulMSIN_A  = pucCIMSI[1];
    ulMSIN_A  = 0x0000FFFF & ( ulMSIN_A | (pucCIMSI[2] << 8));
    ulMSIN_A  = TAF_SDC_CovertCimisNumToBcd(ulMSIN_A, 3);   /* 移动用户身份第1 - 3位*/
    pucStrCIMSI[4] = TAF_STD_ConvertDeciDigitToBcd((VOS_UINT8)(ulMSIN_A/10), VOS_TRUE);
    pucStrCIMSI[5] = TAF_STD_ConvertDeciDigitToBcd((VOS_UINT8)(ulMSIN_A%10), VOS_FALSE);

    ulMSIN_B  = pucCIMSI[3];
    ulMSIN_B  = 0x0000FFFF & (ulMSIN_B | (pucCIMSI[4] << 8));
    ulMSIN_B  = 0x00FFFFFF & (ulMSIN_B | (pucCIMSI[5] << 16));

    ulMSIN_B1 = ulMSIN_B >> 14;
    ulMSIN_B1 = TAF_SDC_CovertCimisNumToBcd(ulMSIN_B1, 3); /* 移动用户身份第4 - 6位 */
    pucStrCIMSI[5] |= (TAF_STD_ConvertDeciDigitToBcd((VOS_UINT8)(ulMSIN_B1/100), VOS_TRUE) & 0xF0);
    pucStrCIMSI[6]  = TAF_STD_ConvertDeciDigitToBcd((VOS_UINT8)(ulMSIN_B1%100), VOS_TRUE);

    ulMSIN_B2 = (ulMSIN_B & 0x3c00)>>10;         /* 移动用户身份第7位 */
    ulMSIN_B2 = ulMSIN_B2 % 10;

    pucStrCIMSI[7]  = (ulMSIN_B2 & 0x0F);

    ulMSIN_B3 = ulMSIN_B & 0x3FF;
    ulMSIN_B3 = TAF_SDC_CovertCimisNumToBcd(ulMSIN_B3, 3);  /* 移动用户身份第8 - 10位 */
    pucStrCIMSI[7]|= TAF_STD_ConvertDeciDigitToBcd((VOS_UINT8)(ulMSIN_B3/100), VOS_TRUE) & 0xF0;
    pucStrCIMSI[8] = TAF_STD_ConvertDeciDigitToBcd((VOS_UINT8)(ulMSIN_B3%100), VOS_TRUE);

    return VOS_OK;
}
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

