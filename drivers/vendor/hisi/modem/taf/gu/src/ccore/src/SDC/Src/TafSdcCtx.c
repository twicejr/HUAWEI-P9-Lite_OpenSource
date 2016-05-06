/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSdcCtx.c
  版 本 号   : 初稿
  作    者   : s46746
  生成日期   : 2012年12月25日

  功能描述   : TAF层共享数据中心，包含全局变量管理以及对外提供API接口
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月25日
    作    者   : s46746
    修改内容   : 创建文件

****************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "TafSdcCtx.h"
#include "TafLog.h"

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-10, begin */
#include "TafSdcLib.h"
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-10, begin */

#include "TafNvInterface.h"
#include  "NasNvInterface.h"
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-25, begin */
#if (FEATURE_IMS == FEATURE_ON)
#include  "ImsaNvInterface.h"
#endif

#include  "LNvCommon.h"
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-25, end */


#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
#include  "LNasNvInterface.h"
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */
#if (FEATURE_ON == FEATURE_BASTET)
#include  "TtfNvInterface.h"
#endif

#include  "NasUtranCtrlInterface.h"

#include  "MmaAppLocal.h"
#include "TafStdlib.h"

#include "NasUsimmApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_TAFSDC_CTX_C
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
/* 保存TAF层共用的CTX */
TAF_SDC_CTX_STRU                        g_stTafSdcCtx;

/*默认情况下使用的GSM 7bit to ASCII码转换表*/
LOCAL VOS_UINT8 g_aucTafSdcDef7BitToAsciiTbl[] =
{
 '@', 0xA3, '$', 0xA5, 0xE8, 0xE9, 0xF9, 0xEC, 0xF2, 0xC7,0x0A, 0xD8, 0xF8,0x0D, 0xC5, 0xE5,
 '?', '_', '?', '?', '?', '?', '?', '?', '?', '?', '?',' ', 0xC6, 0xE6, 0xDF, 0xC9,
 ' ', '!',0x22, '#', 0x2A, '%', '&',0x27, '(', ')', '*', '+', ',', '-', '.', '/',
 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
 0xA1, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 0xC4, 0xD6, 0xD1, 0xDC, 0xA7,
 0xBF, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 0xE4, 0xF6, 0xF1, 0xFC, 0xE0
};


/*TME定制使用的GSM 7bit to ASCII码转换表*/
LOCAL VOS_UINT8 g_aucTafSdcTme7BitToAsciiTbl[] =
{
 '@', 0x9C, '$', 0x9D, 0x8A, 0x82, 0x97, 0x8D, 0x95, 0x80,0x0A, '?', '?',0x0D, 0x8F, 0x86,
 '?', '_', 0xE8, 0xE2, '?', 0xEA, 0xE3, '?',0xE4, 0xE9, '?','?', 0x92, 0x91, 0xE1, 0x90,
 ' ', '!',0x22, '#', '?', '%', '&',0x27, '(', ')', '*', '+', ',', '-', '.', '/',
 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
 0xAD, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 0x8E, 0x99, 0xA5, 0x9A, '?',
 0xA8, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 0x84, 0x94, 0xA4, 0x81, 0x85
};

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */

LOCAL VOS_CHAR *g_aucTafSdcCallEmerNumsNoUsim[TAF_SDC_NUMOF_EMER_NUMS_NO_USIM] =
{
"112", "911", "000", "08", "110", "118", "119", "999"
};

LOCAL VOS_CHAR *g_aucTafSdcCallEmerNumsWithUsim[TAF_SDC_NUMOF_EMER_NUMS_WITH_USIM] =
{"112", "911"};

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
LOCAL VOS_CHAR *g_acTafSdcCdmaCallEmcNums[TAF_SDC_NUMOF_CDMA_PRESET_EMC_NUM] =
{
    "110", "112", "911", "999", "119", "120"
};
#endif
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_SDC_GetSdcCtx
 功能描述  : 获取当前SDC的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前SDC的CTX
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_CTX_STRU*  TAF_SDC_GetSdcCtx( VOS_VOID )
{
    return &(g_stTafSdcCtx);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetMsCapInfo
 功能描述  : 获取MS的能力信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MS能力信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整

*****************************************************************************/
TAF_SDC_MS_CAP_INFO_STRU*  TAF_SDC_GetMsCapInfo( VOS_VOID )
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo);
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-16, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetRoamFlag
 功能描述  : 获取当前漫游标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前系统模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月16日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetRoamFlag( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRoamFlag);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetRoamFlag
 功能描述  : 设置当前漫游标记
 输入参数  : 当前驻留的网络的漫游标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月16日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetRoamFlag(VOS_UINT8 ucRoamFlag)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRoamFlag = ucRoamFlag;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCampOnFlag
 功能描述  : 获取当前是否驻留标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前驻留标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月16日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCampOnFlag( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucCampOnFlg);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCampOnFlag
 功能描述  : 设置当前是否驻留标记
 输入参数  : 当前是否驻留标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月16日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCampOnFlag(VOS_UINT8 ucCampOnFlg)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucCampOnFlg = ucCampOnFlg;
    return;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-16, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_Set3GppRfAvailFlag
 功能描述  : 设置当前是否NO RF标记
 输入参数  : 当前是否NO RF标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月13日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2015年05月29日
   作    者   : l00301449
   修改内容   : CDMA Iteration 15
*****************************************************************************/
VOS_VOID TAF_SDC_Set3GppRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.uc3GppRfAvailFlg = ucRfAvailFlg;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get3GppRfAvailFlag
 功能描述  : 获取当前是否NO RF标记
 输入参数  : 无
 输出参数  : VOS_TRUE:  当前NO RF
             VOS_FALSE: 当前非NO RF
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月13日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2015年05月29日
   作    者   : l00301449
   修改内容   : CDMA Iteration 15

*****************************************************************************/
VOS_UINT8 TAF_SDC_Get3GppRfAvailFlag(VOS_VOID)
{
    return (g_stTafSdcCtx.stNetworkInfo.stSysInfo.st3gppSysInfo.uc3GppRfAvailFlg);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Set1xRfAvailFlag
 功能描述  : 设置当前1X的RF标志
 输入参数  : VOS_UINT8                           ucRfAvailFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_Set1xRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.uc1xRfAvailFlg = ucRfAvailFlg;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get1xRfAvailFlag
 功能描述  : 获取当前1X的RF标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_Get1xRfAvailFlag(VOS_VOID)
{
    return (g_stTafSdcCtx.stNetworkInfo.stSysInfo.st1xSysInfo.uc1xRfAvailFlg);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetHrpdRfAvailFlag
 功能描述  : 设置当前HRPD的RF标志
 输入参数  : VOS_UINT8                           ucRfAvailFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetHrpdRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.stHrpdSysInfo.ucHrpdRfAvailFlg = ucRfAvailFlg;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetHrpdRfAvailFlag
 功能描述  : 获取当前HRPD的RF标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetHrpdRfAvailFlag(VOS_VOID)
{
    return (g_stTafSdcCtx.stNetworkInfo.stSysInfo.stHrpdSysInfo.ucHrpdRfAvailFlg);
}




/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-26, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetSysMode
 功能描述  : 获取当前系统模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前系统模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetSysMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysMode);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetSysMode
 功能描述  : 设置当前系统模式
 输入参数  : 当前系统模式接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetSysMode(TAF_SDC_SYS_MODE_ENUM_UINT8 enSysMode)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysMode = enSysMode;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetSysSubMode
 功能描述  : 获取当前系统子模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前系统子模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_SDC_GetSysSubMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysSubMode);
}
/*****************************************************************************
 函 数 名  : TAF_SDC_SetSysSubMode
 功能描述  : 设置当前系统子模式
 输入参数  : 当前系统子模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetSysSubMode(TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysSubMode = enSysSubMode;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get3gppSysInfo
 功能描述  : 获取服务小区系统信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 服务小区系统信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_3GPP_SYS_INFO_STRU* TAF_SDC_Get3gppSysInfo( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get3gppSysInfo
 功能描述  : 获取服务小区系统信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 服务小区系统信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SYS_INFO_STRU* TAF_SDC_GetSysInfo( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo);
}



/*****************************************************************************
 函 数 名  : TAF_SDC_SetCurrCampPlmnId
 功能描述  : 设置当前驻留plmn信息
 输入参数  : pstPlmnId - plmn id信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCurrCampPlmnId(TAF_SDC_PLMN_ID_STRU *pstPlmnId)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.stPlmnId = *pstPlmnId;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurrCampPlmnId
 功能描述  : 获取当前驻留plmn id信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : plmn id信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_PLMN_ID_STRU *TAF_SDC_GetCurrCampPlmnId(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.stPlmnId);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurrCampLac
 功能描述  : 获取当前驻留lac信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : lac信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月2日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 TAF_SDC_GetCurrCampLac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.usLac);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCurrCampLac
 功能描述  : 设置当前驻留lac信息
 输入参数  : usLac - lac信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月2日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCurrCampLac(VOS_UINT16 usLac)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.usLac = usLac;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurrCampRac
 功能描述  : 获取当前驻留rac信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : rac信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月2日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCurrCampRac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRac);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCurrCampRac
 功能描述  : 设置当前驻留rac信息
 输入参数  : ucRac - rac信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月2日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCurrCampRac(VOS_UINT8 ucRac)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRac = ucRac;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurrCampCellId
 功能描述  : 获取当前驻留cell id信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : cell id信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月2日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_GetCurrCampCellId(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulCellId);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCurrCampCellId
 功能描述  : 设置当前驻留cell id信息
 输入参数  : ulCellId - cell id信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月2日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCurrCampCellId(VOS_UINT32 ulCellId)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulCellId = ulCellId;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurrLmmAccessType
 功能描述  : 获取当前驻留的LTE小区是TDD还是FDD,驻留GU小区时该值无效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enAccessType:EUTRAN_TDD/FDD
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年8月15日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8 TAF_SDC_GetCurrLmmAccessType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.enLmmAccessType);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCurrLmmAccessType
 功能描述  : 设置当前驻留的LTE小区是TDD还是FDD,驻留GU小区时该值无效
 输入参数  : enAccessType - EUTRAN_TDD/FDD
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年8月15日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCurrLmmAccessType(TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8 enLmmAccessType)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.enLmmAccessType  = enLmmAccessType;
    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsServiceStatus
 功能描述  : 获取cs域服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : cs域服务状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetCsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsServiceStatus);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCsServiceStatus
 功能描述  : 设置cs域服务状态
 输入参数  : cs域服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsServiceStatus = enCsServiceStatus;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetPsServiceStatus
 功能描述  : 获取ps域服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ps域服务状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetPsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsServiceStatus);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetPsServiceStatus
 功能描述  : 设置ps域服务状态
 输入参数  : ps域服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enPsServiceStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsServiceStatus = enPsServiceStatus;
    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetPsAttachAllowFlg
 功能描述  : 设置ps是否允许注册标识
 输入参数  : ucPsAttachAllowFlg - ps是否允许注册标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年11月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsAttachAllowFlg(VOS_UINT8 ucPsAttachAllowFlg)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucPsAttachAllowFlg = ucPsAttachAllowFlg;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetPsAttachAllowFlg
 功能描述  : 获取ps是否允许注册标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ps是否允许注册标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年11月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetPsAttachAllowFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucPsAttachAllowFlg;
}



/*****************************************************************************
 函 数 名  : TAF_SDC_SetServiceStatus
 功能描述  : 设置UE总服务状态
 输入参数  : enReportSrvsta - 服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enReportSrvsta)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.enReportSrvsta = enReportSrvsta;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetServiceStatus
 功能描述  : 获取UE总服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 服务状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年4月3日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_SDC_GetServiceStatus(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.enReportSrvsta;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppServiceStatus
 功能描述  : 设置AppNetwork中的UE总服务状态
 输入参数  : enReportSrvsta - 服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :

  1.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppServiceStatus(
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enReportSrvsta
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enReportSrvsta = enReportSrvsta;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppServiceStatus
 功能描述  : 获取AppNetwork中的UE总服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 服务状态
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_SDC_GetAppServiceStatus(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enReportSrvsta;
}
/*****************************************************************************
 函 数 名  : TAF_SDC_GetServiceDomain
 功能描述  : 获取服务域
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 服务域
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 TAF_SDC_GetServiceDomain( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.enServiceDomain);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetServiceDomain
 功能描述  : 设置服务域
 输入参数  : 服务域
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 enServiceDomain)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.enServiceDomain = enServiceDomain;
    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppServiceDomain
 功能描述  : 获取AppNetwork中服务域
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 服务域
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII

*****************************************************************************/
TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 TAF_SDC_GetAppServiceDomain( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enServiceDomain);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppServiceDomain
 功能描述  : 设置AppNetwork中服务域
 输入参数  : 服务域
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppServiceDomain(
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 enServiceDomain
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enServiceDomain = enServiceDomain;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsRegStatus
 功能描述  : 获取cs注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : cs注册状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetCsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsRegStatus);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCsRegStatus
 功能描述  : 设置cs注册状态
 输入参数  : cs注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enCsRegStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsRegStatus = enCsRegStatus;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppCsRegStatus
 功能描述  : 获取AppNetworkInfo cs注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : cs注册状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetAppCsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsRegStatus);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppCsRegStatus
 功能描述  : 设置AppNetworkInfo cs注册状态
 输入参数  : cs注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCsRegStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8 enCsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsRegStatus = enCsRegStatus;
    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetPsRegStatus
 功能描述  : 获取ps注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ps注册状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetPsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsRegStatus);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetPsRegStatus
 功能描述  : 设置ps注册状态
 输入参数  : ps注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enPsRegStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsRegStatus = enPsRegStatus;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppPsRegStatus
 功能描述  : 获取AppNetworkInfo ps注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ps注册状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetAppPsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsRegStatus);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppPsRegStatus
 功能描述  : 设置AppNetworkInfo ps注册状态
 输入参数  : ps注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppPsRegStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8 enPsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsRegStatus = enPsRegStatus;
    return;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetSimCsRegStatus
 功能描述  : 获取SIM卡的cs注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SIM卡的cs注册状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年11月20日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetSimCsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucSimCsRegStatus);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetSimCsRegStatus
 功能描述  : 设置SIM卡的cs注册状态
 输入参数  : SIM卡的cs注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年11月20日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetSimCsRegStatus(
    VOS_UINT8       ucSimCsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucSimCsRegStatus = ucSimCsRegStatus;
    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetSimPsRegStatus
 功能描述  : 获取SIM卡的ps注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SIM卡的ps注册状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年11月20日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetSimPsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucSimPsRegStatus);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetSimPsRegStatus
 功能描述  : 设置SIM卡的ps注册状态
 输入参数  : SIM卡的ps注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年11月20日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetSimPsRegStatus(
    VOS_UINT8       ucSimPsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucSimPsRegStatus= ucSimPsRegStatus;
    return;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCsAcRestriction
 功能描述  : 设置cs接入禁止信息
 输入参数  : pstCsAcRetriction - cs接入禁止信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCsAcRestriction(TAF_SDC_ACCESS_RESTRICTION_STRU *pstCsAcRetriction)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction = *pstCsAcRetriction;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsAcRestriction
 功能描述  : 获取cs接入禁止信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : cs接入禁止信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_ACCESS_RESTRICTION_STRU *TAF_SDC_GetCsAcRestriction(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction));
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetPsAcRestriction
 功能描述  : 获取ps接入禁止信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ps接入禁止信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_ACCESS_RESTRICTION_STRU *TAF_SDC_GetPsAcRestriction(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction));
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetPsAcRestriction
 功能描述  : 设置ps接入禁止信息
 输入参数  : pstPsAcRetriction - ps接入禁止信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsAcRestriction(TAF_SDC_ACCESS_RESTRICTION_STRU *pstPsAcRetriction)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction = *pstPsAcRetriction;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetSimImsi
 功能描述  : 获取imsi信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : imsi信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* TAF_SDC_GetSimImsi( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucImsi);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsimImsi
 功能描述  : 获取Csim Imsi信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : imsi信息
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年11月2日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_UINT8* TAF_SDC_GetCsimImsi( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stMsIdentity.aucImsi);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetSimImsi
 功能描述  : 设置imsi信息
 输入参数  : imsi信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整

*****************************************************************************/
VOS_VOID TAF_SDC_SetSimImsi(
    VOS_UINT8                          *pstImsi
)
{
    PS_MEM_CPY(TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucImsi, pstImsi, sizeof(g_stTafSdcCtx.stSimInfo.stUsimInfo.stMsIdentity.aucImsi));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetLastSimImsi
 功能描述  : 获取Last imsi信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : imsi信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年4月26日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整

*****************************************************************************/
VOS_UINT8* TAF_SDC_GetLastSimImsi(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucLastImsi);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetLastSimImsi
 功能描述  : 设置Last imsi信息
 输入参数  : imsi信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年4月26日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整

*****************************************************************************/
VOS_VOID TAF_SDC_SetLastSimImsi(
    VOS_UINT8                          *pstImsi
)
{
    PS_MEM_CPY(TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucLastImsi, pstImsi,
                sizeof(g_stTafSdcCtx.stSimInfo.stUsimInfo.stMsIdentity.aucLastImsi));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetSimStatus
 功能描述  : 获取卡状态,0：sim卡状态无效; 1：sim卡状态有效 2：sim卡在cs下无效
             3：sim卡在ps下无效; 4：sim卡在ps+cs下均无效; 255：sim卡不存在
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 卡状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整

*****************************************************************************/
TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetSimStatus(
    VOS_VOID
)
{
    /* 综合Usim和Csim的CardService获取卡状态 */
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enUsimStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enCsimStatus;

    enUsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus;
    enCsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus;

    if (TAF_SDC_USIM_STATUS_VALID == enUsimStatus)
    {
        return enUsimStatus;
    }
    else if (TAF_SDC_USIM_STATUS_NO_PRESENT != enUsimStatus)
    {
        if (TAF_SDC_USIM_STATUS_VALID == enCsimStatus)
        {
            return enCsimStatus;
        }
        else
        {
            return enUsimStatus;
        }
    }
    else
    {
        if (TAF_SDC_USIM_STATUS_NO_PRESENT != enCsimStatus)
        {
            return enCsimStatus;
        }
        else
        {
            return TAF_SDC_USIM_STATUS_NO_PRESENT;
        }
    }
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetUsimStatus
 功能描述  : 设置Usimm卡状态
 输入参数  : 卡状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月26日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_VOID TAF_SDC_SetUsimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus = enSimStatus;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetUsimStatus
 功能描述  : 获取Usimm卡状态
 输入参数  :
 输出参数  : 无
 返 回 值  : TAF_SDC_USIM_STATUS_ENUM_UINT8: 卡状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetUsimStatus(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsimStatus
 功能描述  : 获取Csimm卡状态
 输入参数  :
 输出参数  : 无
 返 回 值  : TAF_SDC_USIM_STATUS_ENUM_UINT8: 卡状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetCsimStatus(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCsimStatus
 功能描述  : 设置Csimm卡状态
 输入参数  : 卡状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
VOS_VOID TAF_SDC_SetCsimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus = enSimStatus;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetIccIdInfo
 功能描述  : 设置IccId信息
 输入参数  : TAF_SDC_ICCID_INFO_STRU: IccId信息,数据长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年8月26日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
VOS_VOID TAF_SDC_SetIccIdInfo(
    VOS_UINT8                   ucLen,
    VOS_UINT8                  *pucIccId
)
{
    TAF_SDC_ICCID_INFO_STRU    *pstIccIdInfo    = VOS_NULL_PTR;

    pstIccIdInfo                = TAF_SDC_GetIccIdInfo();

    PS_MEM_SET(pstIccIdInfo, 0xFF, sizeof(TAF_SDC_ICCID_INFO_STRU));

    PS_MEM_CPY(pstIccIdInfo->aucIccId, pucIccId, ucLen);

    pstIccIdInfo->ucLen         = ucLen;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetIccIdInfo
 功能描述  : 获取IccId信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : IccId信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年8月26日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
TAF_SDC_ICCID_INFO_STRU *TAF_SDC_GetIccIdInfo( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stSimInfo.stIccIdInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCsimType
 功能描述  : 设置Csimm卡类型
 输入参数  : 卡类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
VOS_VOID TAF_SDC_SetCsimType(
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType = enCsimType;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetUsimType
 功能描述  : 设置Csimm卡类型
 输入参数  : 卡类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
VOS_VOID TAF_SDC_SetUsimType(
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enUsimType
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType = enUsimType;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetUsimType
 功能描述  : 获取SDC Usimm卡状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_SIM_TYPE_ENUM_UINT8: Usim卡类型
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetUsimType(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsimType
 功能描述  : 获取SDC Csimm卡状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_SIM_TYPE_ENUM_UINT8: Csim卡类型
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetCsimType(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType);
}

/* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetSimType
 功能描述  : 获取卡类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 卡类型
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年7月26日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整
*****************************************************************************/
TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetSimType(VOS_VOID)
{
    /* 获取综合的卡类型，下个迭代将改成GetCardType */
    TAF_SDC_USIM_STATUS_ENUM_UINT8      pstUsimStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      pstCsimStatus;

    pstUsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus;
    pstCsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus;

    if (TAF_SDC_USIM_STATUS_VALID == pstUsimStatus)
    {
        return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType);
    }
    else if (TAF_SDC_USIM_STATUS_NO_PRESENT != pstUsimStatus)
    {
        if (TAF_SDC_USIM_STATUS_VALID == pstCsimStatus)
        {
            return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType);
        }
        else
        {
            return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType);
        }
    }
    else
    {
        if (TAF_SDC_USIM_STATUS_NO_PRESENT != pstCsimStatus)
        {
            return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType);
        }
        else
        {
            return TAF_SDC_SIM_TYPE_BUTT;
        }
    }
}
/* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, end */

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-26, end */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetPlatformRatCap
 功能描述  : 获取平台接入技术能力信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前平台接入技术能力信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
*****************************************************************************/
TAF_SDC_PLATFORM_RAT_CAP_STRU*  TAF_SDC_GetPlatformRatCap( VOS_VOID )
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stPlatformRatCap);
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
}
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurcRptCtrl
 功能描述  : 获取CURC控制主动上报标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前CURC控制主动上报标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月1日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_CURC_RPT_CTRL_STRU*  TAF_SDC_GetCurcRptCtrl( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stRptCtrl.stCurcRptCtrl);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetUnsolicitedRptCtrl
 功能描述  : 获取单个命令控制主动上报标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 单个命令控制主动上报标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月1日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_UNSOLICITED_RPT_CTRL_STRU*  TAF_SDC_GetUnsolicitedRptCtrl( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stRptCtrl.stUnsolicitedRptCtrl);
}

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-15, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetGuNwCapInfo
 功能描述  : get GU network capability infomation
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回保存的网络能力参数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月15日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_NETWORK_CAP_INFO_STRU *TAF_SDC_GetGuNwCapInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetLteNwCapInfo
 功能描述  : get LTE network capability infomation
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回保存的网络能力参数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月15日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_NETWORK_CAP_INFO_STRU *TAF_SDC_GetLteNwCapInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetGuNwCapInfo
 功能描述  : set GU network capability infomation
 输入参数  : pstNwCapInfo 网络能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月15日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetGuNwCapInfo(TAF_SDC_NETWORK_CAP_INFO_STRU *pstNwCapInfo)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo.enLteCsCap   = pstNwCapInfo->enLteCsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo.enNwEmcBsCap = pstNwCapInfo->enNwEmcBsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo.enNwImsVoCap = pstNwCapInfo->enNwImsVoCap;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetLteNwCapInfo
 功能描述  : set LTE network capability infomation
 输入参数  : pstNwCapInfo 网络能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月15日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetLteNwCapInfo(TAF_SDC_NETWORK_CAP_INFO_STRU *pstNwCapInfo)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo.enLteCsCap   = pstNwCapInfo->enLteCsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo.enNwEmcBsCap = pstNwCapInfo->enNwEmcBsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo.enNwImsVoCap = pstNwCapInfo->enNwImsVoCap;
}
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-15, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCsAttachAllowFlg
 功能描述  : 设置cs是否允许注册标识
 输入参数  : ucCsAttachAllowFlg - cs是否允许注册标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCsAttachAllowFlg(VOS_UINT8 ucCsAttachAllowFlg)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucCsAttachAllowFlg = ucCsAttachAllowFlg;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsAttachAllowFlg
 功能描述  : 获取cs是否允许注册标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : cs是否允许注册标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCsAttachAllowFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucCsAttachAllowFlg;
}




/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurrNetworkInfo
 功能描述  : 获取stNetworkInfo中的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_NETWORK_INFO_STRU:网络信息，包括驻留信息和信号强度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_NETWORK_INFO_STRU* TAF_SDC_GetCurrNetworkInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppRssiValue
 功能描述  : 设置stAppNetworkInfo 中已转换为等级表示的信号强度
 输入参数  : ucRssiValue - cs已转换为等级表示的信号强度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
     修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppRssiValue(VOS_UINT8 ucRssiValue)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.ucRssiValue = ucRssiValue;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppRssiValue
 功能描述  : 获取stAppNetworkInfo 中已转换为等级表示的信号强度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : stAppNetworkInfo 中已转换为等级表示的信号强度
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetAppRssiValue(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.ucRssiValue;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppCellUlFreq
 功能描述  : 获取stAppNetworkInfo中小区上行频点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : stAppNetworkInfo中小区上行频点
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月14日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_UINT16 TAF_SDC_GetAppCellUlFreq(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.usCellUlFreq;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppCellDlFreq
 功能描述  : 获取stAppNetworkInfo中小区下行频点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : stAppNetworkInfo中小区下行频点
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月14日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_UINT16 TAF_SDC_GetAppCellDlFreq(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.usCellDlFreq;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppLteArfcn
 功能描述  : 获取LTE驻留频点信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : LTE驻留频点信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月24日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SDC_GetAppLteArfcn(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulLteArfcn;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppLteArfcn
 功能描述  : 设置LTE驻留频点信息
 输入参数  : LTE驻留频点信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月14日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppLteArfcn(VOS_UINT32 ulLteArfcn)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulLteArfcn = ulLteArfcn;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppCampPlmnId
 功能描述  : 设置stAppNetworkInfo 中驻留plmn信息
 输入参数  : pstPlmnId - plmn id信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppServicePlmnId(TAF_SDC_PLMN_ID_STRU *pstPlmnId)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.stServicePlmnId = *pstPlmnId;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppCampPlmnId
 功能描述  : 获取 stAppNetworkInfo 中驻留plmn信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : stAppNetworkInfo 中 plmn id信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
TAF_SDC_PLMN_ID_STRU *TAF_SDC_GetAppServicePlmnId(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.stServicePlmnId);
}



/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppSysMode
 功能描述  : 设置 stAppNetworkInfo 中系统模式
 输入参数  : stAppNetworkInfo 中系统模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppSysMode(TAF_SDC_SYS_MODE_ENUM_UINT8 enSysMode)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysMode = enSysMode;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppSysMode
 功能描述  : 获取stAppNetworkInfo系统模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : stAppNetworkInfo系统模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetAppSysMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysMode);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppSysSubMode
 功能描述  : 设置stAppNetworkInfo系统子模式
 输入参数  :stAppNetworkInfo系统子模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppSysSubMode(TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysSubMode = enSysSubMode;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppSysSubMode
 功能描述  : 获取stAppNetworkInfo系统子模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : stAppNetworkInfo系统子模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_SDC_GetAppSysSubMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysSubMode);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppCampLac
 功能描述  : 设置stAppNetworkInfo lac信息
 输入参数  : usLac - lac信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCampLac(VOS_UINT16 usLac)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.usServiceLac = usLac;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppCampLac
 功能描述  : 获取当前stAppNetworkInfo lac信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : lac信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_UINT16 TAF_SDC_GetAppCampLac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.usServiceLac);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppCampRac
 功能描述  : 设置stAppNetworkInfo rac信息
 输入参数  : ucRac - rac信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCampRac(VOS_UINT8 ucRac)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRac = ucRac;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppCampRac
 功能描述  : 获取stAppNetworkInfo rac信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : stAppNetworkInfo rac信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetAppCampRac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRac);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppCampCellId
 功能描述  : 设置stAppNetworkInfo cell id信息
 输入参数  : ulCellId - cell id信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCampCellId(VOS_UINT32 ulServiceCellId)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ulServiceCellId = ulServiceCellId;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppCampCellId
 功能描述  : 获取stAppNetworkInfo cell id信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : cell id信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetAppCampCellId(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ulServiceCellId);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppRoamFlg
 功能描述  : 设置stAppNetworkInfo 漫游信息
 输入参数  : ucServiceRoamFlg - 漫游信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppRoamFlg(VOS_UINT8 ucServiceRoamFlg)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg = ucServiceRoamFlg;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppCampCellId
 功能描述  : 获取stAppNetworkInfo 漫游信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucServiceRoamFlg - 漫游信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetAppRoamFlg(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppNetworkInfo
 功能描述  : 获取stAppNetworkInfo中的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_APPNETWORK_INFO:驻留信息和信号强度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_APPNETWORK_INFO* TAF_SDC_GetAppNetworkInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppUtranMode
 功能描述  : 设置stAppNetworkInfo utran mode信息
 输入参数  : ucServiceUtranMode - utran mode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppUtranMode(VOS_UINT8 ucServiceUtranMode)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceUtranMode = ucServiceUtranMode;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppUtranMode
 功能描述  : 获取stAppNetworkInfo utran mode信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucServiceUtranMode - utran mode
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
 2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetAppUtranMode(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceUtranMode);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppCsServiceStatus
 功能描述  : 获取cs域服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : cs域服务状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : w00281933
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetAppCsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsServiceStatus);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppCsServiceStatus
 功能描述  : 设置cs域服务状态
 输入参数  : cs域服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年2月11日
   作    者   : w00281933
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCsServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsServiceStatus = enCsServiceStatus;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppPsServiceStatus
 功能描述  : 获取ps域服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ps域服务状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年2月11日
   作    者   : w00281933
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetAppPsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsServiceStatus);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppPsServiceStatus
 功能描述  : 设置ps域服务状态
 输入参数  : ps域服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年2月11日
   作    者   : w00281933
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppPsServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enPsServiceStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsServiceStatus = enPsServiceStatus;
    return;
}

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_InitSvlteSupportFlag
 功能描述  : 初始化SVLTE支持标志
 输入参数  : enInitType:INIT类型
             pstMsCapInfo:MS能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitSvlteSupportFlag(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                                  ulLength;
    SVLTE_SUPPORT_FLAG_STRU                     stSvlteFlag;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 初始化为不支持SVLTE */
    pstMsCapInfo->ucSvlteSupportFlag = VOS_FALSE;

    /* SVLTE只有在FEATURE_MULTI_MODEM打开时，才有可能设置为开启 */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_SVLTE_FLAG, &ulLength);

    if (ulLength > sizeof(SVLTE_SUPPORT_FLAG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSvlteSupportFlag():WARNING: en_NV_Item_SVLTE length Error");

        return;
    }

    /* 读NV项en_NV_Item_SVLTE_FLAG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_SVLTE_FLAG,
                         &stSvlteFlag, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSvlteSupportFlag():WARNING: read en_NV_Item_SVLTE Error");

        return;
    }

    /* 赋值到全局变量中 */
    pstMsCapInfo->ucSvlteSupportFlag = stSvlteFlag.ucSvlteSupportFlag;
#endif

    return;
}


/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-25, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitImsRatSupport
 功能描述  : 初始化IMS支持信息
 输入参数  : enInitType:INIT类型
             pstMsCapInfo:MS能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月25日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitImsRatSupport(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    IMSA_NV_IMS_RAT_SUPPORT_STRU                stImsSupport;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* IMS宏关闭时，默认初始化为不支持IMS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stImsRatSupport), 0, sizeof(TAF_SDC_IMS_RAT_SUPPORT_STRU));
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmEmsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranEmsSupportFlag = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag   = VOS_FALSE;

    /* IMS能力只有在FEATURE_IMS打开时，才有可能设置为开启 */
#if (FEATURE_ON == FEATURE_IMS)

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_IMS_RAT_SUPPORT, &ulLength);

    if (ulLength > sizeof(IMSA_NV_IMS_RAT_SUPPORT_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsRatSupport():WARNING: EN_NV_ID_IMS_RAT_SUPPORT length Error");

        return;
    }

    /* 读NV项EN_NV_ID_IMS_RAT_SUPPORT，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_RAT_SUPPORT,
                         &stImsSupport, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsRatSupport():WARNING: read EN_NV_ID_IMS_RAT_SUPPORT Error");

        return;
    }

    /* 赋值到全局变量中 */
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag   = stImsSupport.ucGsmEmsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag = stImsSupport.ucUtranImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag   = stImsSupport.ucLteImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmEmsSupportFlag   = stImsSupport.ucGsmEmsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranEmsSupportFlag = stImsSupport.ucUtranEmsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag   = stImsSupport.ucLteEmsSupportFlag;
#endif

    return;
}

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-25, end */

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitImsCapability
 功能描述  : 初始化IMS支持短信/语音能力
 输入参数  : enInitType:INIT类型
             pstMsCapInfo:MS能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitImsCapability(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    IMS_NV_IMS_CAP_STRU                         stImsCapa;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* IMS宏关闭时，默认初始化为不支持IMS VOICE和IMS SMS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stImsCapability), 0, sizeof(TAF_SDC_IMS_CAPABILITY_STRU));
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag         = VOS_FALSE;

    /* IMS能力只有在FEATURE_IMS打开时，才有可能设置为开启 */
#if (FEATURE_ON == FEATURE_IMS)

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_IMS_CAPABILITY, &ulLength);

    if (ulLength > sizeof(IMS_NV_IMS_CAP_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsCapability():WARNING: EN_NV_ID_IMS_CAPABILITY length Error");

        return;
    }

    /* 读NV项EN_NV_ID_IMS_CAPABILITY，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_CAPABILITY,
                         &stImsCapa, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsCapability():WARNING: read EN_NV_ID_IMS_CAPABILITY Error");

        return;
    }

    /* 赋值到全局变量中 */
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag   = stImsCapa.ucVoiceCallOnImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag   = stImsCapa.ucVideoCallOnImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag         = stImsCapa.ucSmsOnImsSupportFlag;
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitVoiceDomain
 功能描述  : 初始化语音优选域
 输入参数  : enInitType:INIT类型
             pstMsCapInfo:MS能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2014年07月04日
   作    者   : s00217060
   修改内容   : DTS2014070301192:IMS宏打开时，NV默认值为cs only;IMS宏关闭时，NV默认值为ps preferred

*****************************************************************************/
VOS_VOID TAF_SDC_InitVoiceDomain(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    LNAS_LMM_NV_VOICE_DOMAIN_STRU               stVoiceDomain;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* NV关闭时，默认初始化为CS ONLY */
    pstMsCapInfo->stImsConfigPara.enVoiceDomain = TAF_SDC_VOICE_DOMAIN_CS_ONLY;

#if (FEATURE_ON == FEATURE_IMS)

    /* NV打开时，默认初始化为ps preferred */
    pstMsCapInfo->stImsConfigPara.enVoiceDomain = TAF_SDC_VOICE_DOMAIN_IMS_PS_PREFERRED;

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_UE_VOICE_DOMAIN, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_VOICE_DOMAIN_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitVoiceDomain():WARNING: EN_NV_ID_UE_VOICE_DOMAIN length Error");

        return;
    }

    /* 读NV项EN_NV_ID_UE_VOICE_DOMAIN，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_UE_VOICE_DOMAIN,
                         &stVoiceDomain, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitVoiceDomain():WARNING: read EN_NV_ID_UE_VOICE_DOMAIN Error");

        return;
    }

    /* NV项激活，并且取值合法时，赋值到全局变量中 */
    if ( (NV_ITEM_ACTIVE == stVoiceDomain.bitOpVoicDomain)
      && (NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED >= stVoiceDomain.enVoicDomain) )
    {
        pstMsCapInfo->stImsConfigPara.enVoiceDomain = stVoiceDomain.enVoicDomain;
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitSmsDomain
 功能描述  : 初始化短信优选域
 输入参数  : enInitType:INIT类型
             pstMsCapInfo:MS能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitSmsDomain(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NVIM_SMS_DOMAIN_STRU                    stSmsDomain;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 默认初始化为not use sms over ip */
    pstMsCapInfo->stImsConfigPara.enSmsDomain   = TAF_SDC_SMS_DOMAIN_NOT_USE_SMS_OVER_IP;

#if (FEATURE_ON == FEATURE_IMS)
    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_SMS_DOMAIN, &ulLength);

    if (ulLength > sizeof(TAF_NVIM_SMS_DOMAIN_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSmsDomain():WARNING: en_NV_Item_SMS_DOMAIN length Error");

        return;
    }

    /* 读NV项en_NV_Item_SMS_DOMAIN，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_SMS_DOMAIN,
                         &stSmsDomain, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSmsDomain():WARNING: read en_NV_Item_SMS_DOMAIN Error");

        return;
    }

    /* NV项激活，并且取值合法时，赋值到全局变量中 */
    if (TAF_SDC_SMS_DOMAIN_PREFER_TO_USE_SMS_OVER_IP >= stSmsDomain.ucSmsDomain)
    {
        pstMsCapInfo->stImsConfigPara.enSmsDomain = stSmsDomain.ucSmsDomain;
    }
#endif

    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_InitLteCsServiceCfg
 功能描述  : 从NV中获取L支持的cs业务配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月24日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_InitLteCsServiceCfg(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
    NAS_NVIM_LTE_CS_SERVICE_CFG_STRU                        stLteCsServiceCfg;
    VOS_UINT32                                              ulLength;

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    ulLength        = 0;
    PS_MEM_SET(&stLteCsServiceCfg, 0x00, sizeof(NAS_NVIM_LTE_CS_SERVICE_CFG_STRU));

    /* 默认初始化为TAF_SDC_LTE_SUPPORT_BUTT，和MMC初始值保持一致 */
    pstMsCapInfo->stImsConfigPara.enLteCsServiceCfg = TAF_SDC_LTE_SUPPORT_BUTT;

    (VOS_VOID)NV_GetLength(en_NV_Item_Lte_Cs_Service_Config, &ulLength);

    if (ulLength > sizeof(stLteCsServiceCfg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitLteCsServiceCfg():WARNING: en_NV_Item_Lte_Cs_Service_Config length Error");
        return;
    }
    if ( NV_OK != NV_Read(en_NV_Item_Lte_Cs_Service_Config,
                          &stLteCsServiceCfg,
                          ulLength ))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitLteCsServiceCfg(): en_NV_Item_Lte_Cs_Service_Config Error");
        return;
    }

    /* 如果NV项激活并且值有效，则更新全局变量 */
    if ((NV_ITEM_ACTIVE == stLteCsServiceCfg.ucNvimActiveFlg)
     && (stLteCsServiceCfg.ucLteCsServiceCfg < TAF_SDC_LTE_SUPPORT_BUTT))
    {
        pstMsCapInfo->stImsConfigPara.enLteCsServiceCfg = stLteCsServiceCfg.ucLteCsServiceCfg;

    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitRedialConfig
 功能描述  : 初始化重拨配置
 输入参数  : enInitType   －－初始化类型
             pstMsCapInfo －－ 能力参数指针

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月24日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve修改

*****************************************************************************/
VOS_VOID TAF_SDC_InitRedialCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU  stRedialImsToCs;

    PS_MEM_SET(&stRedialImsToCs, 0, sizeof(TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU));
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 默认初始化为FALSE */
    /* IMS to CS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs),
               0,
               sizeof(TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU));

    /* CS to IMS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stRedial.stRedialCsToIms),
               0,
               sizeof(TAF_SDC_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU));

#if (FEATURE_ON == FEATURE_IMS)
    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG, &ulLength);

    if (ulLength > sizeof(TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRedialConfig():WARNING: en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG length Error");

        return;
    }

    /* 读NV项en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG,
                         &stRedialImsToCs, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRedialConfig():WARNING: read en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG Error");

        return;
    }

    /* NV项激活，更新重拨配置 */
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.ucCallRedial = stRedialImsToCs.ucCallRedial;
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.ucSmsRedial  = stRedialImsToCs.ucSmsRedial;
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.ucSsRedial   = stRedialImsToCs.ucSsRedial;

    /* IMS REDIAL NUM */
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum  = TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM;

    if (stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum <= TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM)
    {
        pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum = stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum;
    }



    /* IMSA REDIAL NUM */
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum = TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM;

    if (stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum <= TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM)
    {
        pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum = stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum;
    }



    /* IMS REDIAL CAUSE */
    PS_MEM_CPY(pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ausImsRedialCause,
                stRedialImsToCs.stCallRedialCauseCfg.ausImsRedialCause,
                (stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum)*sizeof(VOS_UINT16));



    /* IMSA REDIAL CAUSE */
    PS_MEM_CPY(pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ausImsaRedialCause,
                stRedialImsToCs.stCallRedialCauseCfg.ausImsaRedialCause,
                (stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum)*sizeof(VOS_UINT16));

    /* CS to IMS方向的换域重拨未来在这儿添加 */
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitImsRoamingCfgInfo
 功能描述  : 初始化重拨配置
 输入参数  : enInitType   －－初始化类型
             pstMsCapInfo －－ 能力参数指针

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月24日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitImsRoamingCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NV_IMS_ROAMING_SUPPORT_STRU             stRoamingFlg;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 默认初始化为FALSE */
    pstMsCapInfo->stImsConfigPara.ucRoamingSupport = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_IMS_ROAMING_SUPPORT_FLG, &ulLength);

    if (ulLength > sizeof(TAF_NV_IMS_ROAMING_SUPPORT_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsRoamingCfgInfo():WARNING: en_NV_Item_IMS_ROAMING_SUPPORT_FLG length Error");

        return;
    }

    /* 读NV项en_NV_Item_IMS_ROAMING_SUPPORT_FLG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_IMS_ROAMING_SUPPORT_FLG,
                         &stRoamingFlg, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsRoamingCfgInfo():WARNING: read en_NV_Item_IMS_ROAMING_SUPPORT_FLG Error");

        return;
    }

    /* NV项激活，更新ims漫游支持配置信息 */
    pstMsCapInfo->stImsConfigPara.ucRoamingSupport = stRoamingFlg.ucImsRoamingFlg;
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitImsUssdCfgInfo
 功能描述  : 初始化重拨配置
 输入参数  : enInitType   －－初始化类型
             pstMsCapInfo －－ 能力参数指针

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2014年04月01日
    作    者   : y00245242
    修改内容   : 为DTS2014040203732修改，增加NV控制USSD业务域选择；USSD业务NV打开，
                 进行正常域选择，否则选择CS域
*****************************************************************************/
VOS_VOID TAF_SDC_InitImsUssdCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NV_IMS_USSD_SUPPORT_STRU                stUssdFlg;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 默认初始化为FALSE */
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_IMS_USSD_SUPPORT_FLG, &ulLength);

    if (ulLength > sizeof(TAF_NV_IMS_USSD_SUPPORT_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsUssdCfgInfo():WARNING: en_NV_Item_IMS_USSD_SUPPORT_FLG length Error");

        return;
    }

    /* 读NV项en_NV_Item_IMS_USSD_SUPPORT_FLG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_IMS_USSD_SUPPORT_FLG,
                         &stUssdFlg, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsUssdCfgInfo():WARNING: read en_NV_Item_IMS_USSD_SUPPORT_FLG Error");

        return;
    }

    /* NV项激活，更新USSD支持配置信息 */
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag = stUssdFlg.ucUssdOnImsSupportFlag;
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitImsConfigPara
 功能描述  : 初始化IMS配置信息
 输入参数  : enInitType:INIT类型
             pstMsCapInfo:MS能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年12月24日
   作    者   : y00245242
   修改内容   : 增加换域重拨与漫游控制功能
 3.日    期   : 2014年04月01日
   作    者   : y00245242
   修改内容   : 为DTS2014040203732修改，增加NV控制USSD业务域选择；USSD业务NV打开，
                进行正常域选择，否则选择CS域
*****************************************************************************/
VOS_VOID TAF_SDC_InitImsConfigPara(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
    /* EN_NV_ID_IMS_RAT_SUPPORT */
    TAF_SDC_InitImsRatSupport(enInitType, pstMsCapInfo);

    /* EN_NV_ID_IMS_CAPABILITY */
    TAF_SDC_InitImsCapability(enInitType, pstMsCapInfo);

    /* EN_NV_ID_UE_VOICE_DOMAIN */
    TAF_SDC_InitVoiceDomain(enInitType, pstMsCapInfo);

    /* en_NV_Item_SMS_DOMAIN */
    TAF_SDC_InitSmsDomain(enInitType, pstMsCapInfo);

    /* en_NV_Item_Lte_Cs_Service_Config */
    TAF_SDC_InitLteCsServiceCfg(enInitType, pstMsCapInfo);

    TAF_SDC_InitRedialCfgInfo(enInitType, pstMsCapInfo);

    TAF_SDC_InitImsRoamingCfgInfo(enInitType, pstMsCapInfo);


    TAF_SDC_InitImsUssdCfgInfo(enInitType, pstMsCapInfo);
}
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

/* Added by w00167002 for L-C互操作项目, 2014-2-15, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitLcConfigPara
 功能描述  : 初始化LC配置信息
 输入参数  : enInitType:INIT类型
             pstLcConfigPara:LC配置能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月15日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitLcConfigPara(
    TAF_SDC_LC_CONFIG_PARA_STRU        *pstLcConfigPara
)
{
    pstLcConfigPara->ucLCEnableFlg  = VOS_FALSE;
    pstLcConfigPara->enRatCombined  = TAF_NVIM_LC_RAT_COMBINED_BUTT;
    pstLcConfigPara->enLCWorkCfg    = TAF_NVIM_LC_WORK_CFG_BUTT;
    pstLcConfigPara->aucReserved[0] = 0;

    return;
}
/* Added by w00167002 for L-C互操作项目, 2014-2-15, end */
#if (FEATURE_ON == FEATURE_BASTET)
/*****************************************************************************
 函 数 名  : TAF_SDC_InitBastetSupportFlag
 功能描述  : 从NV中获取Bastet配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月22日
    作    者   : z00128442
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_InitBastetSupportFlag(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
    VOS_UINT32                                  ulLength;
    BASTET_SUPPORT_FLG_STRU                     stBastetFlag;

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 初始化为不支持bastet*/
    pstMsCapInfo->ucBastetSupportFlag = VOS_FALSE;

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_Bastet_CONFIG, &ulLength);

    if (ulLength > sizeof(BASTET_SUPPORT_FLG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitBastetSupportFlag():WARNING: en_NV_Item_Bastet_CONFIG length Error");

        return;
    }

    /* en_NV_Item_Bastet_CONFIG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_Bastet_CONFIG,
                         &stBastetFlag, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitBastetSupportFlag():WARNING: read en_NV_Item_Bastet_CONFIG Error");

        return;
    }

    /* 赋值到全局变量中 */
    pstMsCapInfo->ucBastetSupportFlag = stBastetFlag.ucActiveFlg;

    return;
}

/*lint -restore */

#endif
/*****************************************************************************
 函 数 名  : TAF_SDC_InitMsCapInfo
 功能描述  : 初始化MS能力信息
 输入参数  : enInitType:INIT类型
             pstMsCapInfo:MS能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2013年06月04日
   作    者   : s00217060
   修改内容   : for V9R1_SVLTE:SVLTE默认关闭
 3.日    期   : 2013年07月25日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseI项目
 4.日    期   : 2013年09月22日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，读取EN_NV_ID_IMS_CAPABILITY、EN_NV_ID_UE_VOICE_DOMAIN
 5.日    期   : 2014年2月14日
   作    者   : w00167002
   修改内容   : L-C互操作项目:LC能力配置初始化
*****************************************************************************/
VOS_VOID TAF_SDC_InitMsCapInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_MS_CAP_INFO_STRU            *pstMsCapInfo
)
{
    TAF_SDC_InitSvlteSupportFlag(enInitType, pstMsCapInfo);

    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
    TAF_SDC_InitImsConfigPara(enInitType, pstMsCapInfo);
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

    /* Added by w00167002 for L-C互操作项目, 2014-2-15, begin */
    TAF_SDC_InitLcConfigPara(&(pstMsCapInfo->stLcConfigPara));
    /* Added by w00167002 for L-C互操作项目, 2014-2-15, end */
#if (FEATURE_ON == FEATURE_BASTET)
    TAF_SDC_InitBastetSupportFlag(enInitType, pstMsCapInfo);
#endif
}

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitRptCtrlInfo
 功能描述  : 初始化主动上报控制全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitRptCtrlInfo(VOS_VOID)
{
    /* 初始化全局变量 */
    TAF_SDC_InitCurcRptCtrlInfo();

    /* 初始化单个命令主动上报标识 */
    TAF_SDC_InitUnsolicitedRptCtrlInfo();
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitUssdCfgInfo
 功能描述  : 初始化USSD的配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_InitUssdCfgInfo(VOS_VOID)
{
    TAF_SDC_ReadUssdTransModeNvim();

    TAF_SDC_ReadUssdTransTableNvim();

    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_ReadUssdTransModeNvim
 功能描述  : 根据NV：(en_NV_Item_CUST_USSD_MODE,，初始USSD的传输模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_ReadUssdTransModeNvim(VOS_VOID)
{
    TAF_USSD_NVIM_TRANS_MODE_STRU       stUssdTranMode;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stUssdTranMode, 0x00, sizeof(TAF_USSD_NVIM_TRANS_MODE_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_CUST_USSD_MODE, &ulLength);

    /* 读取USSD是否透传设置 */
    if (NV_OK == NV_Read(en_NV_Item_CUST_USSD_MODE,
                          &stUssdTranMode,
                          ulLength))
    {
        if (VOS_TRUE != stUssdTranMode.ucStatus)
        {
            stUssdTranMode.ucUssdTransMode = TAF_SDC_USSD_TRAN_MODE;
        }
    }
    else
    {
        stUssdTranMode.ucUssdTransMode = TAF_SDC_USSD_TRAN_MODE;
    }

    TAF_SDC_SetUssdTransMode(stUssdTranMode.ucUssdTransMode);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_ReadUssdTransTableNvim
 功能描述  : 根据NV：(en_NV_Item_USSD_Apha_To_Ascii,，初始USSD的转换表类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_ReadUssdTransTableNvim(VOS_VOID)
{
    SSA_NV_ITEM_ALPHA_to_ASCII_STRU               stUSSDApha;
    VOS_UINT32                                    ulResult;
    VOS_UINT32                                    ulLength;

    ulLength = 0;
    stUSSDApha.ucStatus         = VOS_FALSE;
    stUSSDApha.ucAlphaTransMode = TAF_SDC_USSD_TRAN_MODE_BUTT;

    (VOS_VOID)NV_GetLength(en_NV_Item_USSD_Apha_To_Ascii, &ulLength);

    ulResult = NV_Read(en_NV_Item_USSD_Apha_To_Ascii,
                       &stUSSDApha,
                       ulLength);

    if ((ulResult == NV_OK)
     && (VOS_TRUE == stUSSDApha.ucStatus)
     && (VOS_TRUE == (stUSSDApha.ucAlphaTransMode & 0x01)))
    {
        TAF_SDC_Set7BitToAssicTableType(TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_TME);
    }
    else
    {
        TAF_SDC_Set7BitToAssicTableType(TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_DEF);
    }

    return;
}


/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-05, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitAppCfgSupportType
 功能描述  : 从NV中获取对接的应用类型，并记录到SDC全局变量中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月05日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseI项目新增
*****************************************************************************/
VOS_VOID TAF_SDC_InitAppCfgSupportType(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSysAppConfig;
    VOS_UINT16                          usAppCfgType;

    stSysAppConfig.usSysAppConfigType = SYSTEM_APP_BUTT;
    ulLength                          = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_System_APP_Config, &ulLength);

    if (ulLength > sizeof(stSysAppConfig))
    {
        TAF_SDC_SetAppCfgSupportType(SYSTEM_APP_MP);
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_System_APP_Config,
                         &stSysAppConfig, ulLength))
    {
        TAF_SDC_SetAppCfgSupportType(SYSTEM_APP_MP);

        return;
    }

    if ( SYSTEM_APP_ANDROID < stSysAppConfig.usSysAppConfigType )
    {
        usAppCfgType    = SYSTEM_APP_MP;
    }
    else
    {
        usAppCfgType    = stSysAppConfig.usSysAppConfigType ;
    }

    TAF_SDC_SetAppCfgSupportType(usAppCfgType);

    return;
}
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-05, end */


/*****************************************************************************
 函 数 名  : TAF_SDC_InitPlmnExactlyCompareFlg
 功能描述  : 读取en_NV_Item_PLMN_EXACTLY_COMPARE_FLG nv项内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月26日
    作    者   : c00318887
    修改内容   : AT&T phaseII新增
*****************************************************************************/
VOS_VOID TAF_SDC_InitPlmnExactlyCompareFlg(VOS_VOID)
{
    NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU             stPlmnExactlyCompara;
    VOS_UINT32                                              ulLength;

    PS_MEM_SET(&stPlmnExactlyCompara, 0x00, sizeof(NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU));

    ulLength = 0;
    TAF_SDC_SetPlmnExactlyCompareFlg(VOS_FALSE);

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_PLMN_EXACTLY_COMPARE_FLG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitPlmnExactlyCompareFlg():WARNING: en_NV_Item_PLMN_EXACTLY_COMPARE_FLG length Error");
        return;
    }

    /* 读取NV */
    if (NV_OK != NV_Read (en_NV_Item_PLMN_EXACTLY_COMPARE_FLG, &stPlmnExactlyCompara, ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitPlmnExactlyCompareFlg(): en_NV_Item_PLMN_EXACTLY_COMPARE_FLG Error");
        return;
    }

    /* NV有效性检查 */
    if (VOS_TRUE == stPlmnExactlyCompara.ucPlmnExactlyCompareFlag)
    {
        /* 赋值到全局变量 */
        TAF_SDC_SetPlmnExactlyCompareFlg(stPlmnExactlyCompara.ucPlmnExactlyCompareFlag);
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_InitRefreshAllFileRestartFlag
 功能描述  : 读取en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG nv项内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月26日
    作    者   : z00161729
    修改内容   : AT&T phaseII新增
*****************************************************************************/
VOS_VOID TAF_SDC_InitRefreshAllFileRestartFlag(VOS_VOID)
{
    TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU              stRefreshAllFileRestartFlag;
    VOS_UINT32                                              ulLength;

    PS_MEM_SET(&stRefreshAllFileRestartFlag, 0x00, sizeof(TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU));

    ulLength = 0;
    TAF_SDC_SetRefreshAllFileRestartFlag(VOS_FALSE);

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG, &ulLength);

    if (ulLength > sizeof(TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRefreshAllFileRestartFlag():WARNING: en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG length Error");
        return;
    }

    /* 读取NV */
    if (NV_OK != NV_Read (en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG, &stRefreshAllFileRestartFlag, ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRefreshAllFileRestartFlag(): en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG Error");
        return;
    }

    /* NV有效性检查 */
    if (VOS_TRUE == stRefreshAllFileRestartFlag.ucRefreshAllFileRestartFlag)
    {
        /* 赋值到全局变量 */
        TAF_SDC_SetRefreshAllFileRestartFlag(stRefreshAllFileRestartFlag.ucRefreshAllFileRestartFlag);
    }

    return;
}


/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-11, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitUeUsageSetting
 功能描述  : 从NV中获取对应的UE使用设置，并记录到SDC全局变量中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月11日
    作    者   : y00245242
    修改内容   : VoLTE_PhaseII项目新增
*****************************************************************************/
VOS_VOID TAF_SDC_InitUeUsageSetting(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    LNAS_LMM_NV_UE_CENTER_STRU          stUeCentric;

    ulLength = 0;

    (VOS_VOID)NV_GetLength(EN_NV_ID_UE_CENTER, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_UE_CENTER_STRU))
    {
        /* set data centric same as LNAS operation */
        TAF_SDC_SetUeUsageSetting(EMM_SETTING_DATA_CENTRIC);

        return;
    }

    stUeCentric.enUeCenter = EMM_USAGE_SETTING_BUTT;

    if (NV_OK != NV_Read(EN_NV_ID_UE_CENTER,
                         &stUeCentric, ulLength))
    {
        /* set data centric same as LNAS operation */
        TAF_SDC_SetUeUsageSetting(TAF_SDC_UE_USAGE_DATA_CENTRIC);

        return;
    }

    TAF_SDC_SetUeUsageSetting((TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8)(stUeCentric.enUeCenter));

    return;
}
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-11, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_InitMsSysCfgInfo
 功能描述  : 初始化系统配置信息
 输入参数  : pstMsSysCfgInfo - 系统配置信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : SS FDN&Call Control项目:增加USSD传输模式初始化
 3.日    期   : 2013年08月05日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseI项目
 4.日    期   : 2013年10月15日
   作    者   : y00245242
   修改内容   : VoLTE_PhaseII项目

 5.日    期   : 2013年11月14日
   作    者   : z00161729
   修改内容   : DTS2013111507527:gcf 31.9.2.1不过，网络ussd notify消息应该广播上报，收到网络release complete应该上报cusd:2而不是0
 6.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
 7.日    期   : 2015年2月26日
   作    者   : c00318887
   修改内容   : AT&T phaseII 增加精确比较PLMN表示的处理
*****************************************************************************/
VOS_VOID TAF_SDC_InitMsSysCfgInfo(TAF_SDC_MS_SYS_CFG_INFO_STRU *pstMsSysCfgInfo)
{
    TAF_SDC_InitRptCtrlInfo();

    TAF_SDC_InitUssdCfgInfo();

    /* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-05, begin */
    TAF_SDC_InitAppCfgSupportType();
    /* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-05, end */

    TAF_SDC_InitPlmnExactlyCompareFlg();
    TAF_SDC_InitRefreshAllFileRestartFlag();

    TAF_SDC_InitDsdaPlmnSearchEnhancedCfg();

    /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-11, begin */
    TAF_SDC_InitUeUsageSetting();
    /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-11, end */

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
#if (FEATURE_ON == FEATURE_LTE)
    pstMsSysCfgInfo->stPrioRatList.ucRatNum     = TAF_SDC_MAX_RAT_NUM;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[0]= TAF_SDC_SYS_MODE_LTE;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[1]= TAF_SDC_SYS_MODE_WCDMA;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[2]= TAF_SDC_SYS_MODE_GSM;
#else
    pstMsSysCfgInfo->stPrioRatList.ucRatNum     = TAF_SDC_MAX_RAT_NUM;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[0]= TAF_SDC_SYS_MODE_WCDMA;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[1]= TAF_SDC_SYS_MODE_GSM;
#endif
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    pstMsSysCfgInfo->stNonnormalRegStatusMergeCfg.ucMergeFlg = VOS_TRUE;

    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_InitMsCfgInfo
 功能描述  : 初始化MS能力信息
 输入参数  : enInitType   - INIT类型
             pstMsCapInfo - MS能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitMsCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_MS_CFG_INFO_STRU            *pstMsCfgInfo
)
{
    TAF_SDC_InitMsCapInfo(enInitType, &(pstMsCfgInfo->stMsCapInfo));

    TAF_SDC_InitMsSysCfgInfo(&pstMsCfgInfo->stMsSysCfgInfo);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Init3gppSysInfo
 功能描述  : 初始化驻留plmn信息
 输入参数  : pstCampPlmnInfo - 驻留plmn信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2014年8月14日
   作    者   : s00217060
   修改内容   : DTS2014080700822:初始化accesstype

*****************************************************************************/
VOS_VOID TAF_SDC_Init3gppSysInfo(TAF_SDC_3GPP_SYS_INFO_STRU *pst3gppSysInfo)
{
    pst3gppSysInfo->stPlmnId.ulMcc = TAF_SDC_INVALID_MCC;
    pst3gppSysInfo->stPlmnId.ulMnc = TAF_SDC_INVALID_MNC;
    pst3gppSysInfo->ucRac          = TAF_SDC_RAC_INVALID;
    pst3gppSysInfo->usLac          = TAF_SDC_LAC_INVALID;
    pst3gppSysInfo->ulCellId       = TAF_SDC_CELLID_INVALID;
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-16, begin */
    pst3gppSysInfo->ucRoamFlag     = VOS_FALSE;
    pst3gppSysInfo->ucCampOnFlg    = VOS_FALSE;
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-16, end */

    TAF_SDC_Set3GppRfAvailFlag(VOS_TRUE);

    pst3gppSysInfo->enLmmAccessType   = TAF_SDC_LMM_ACCESS_TYPE_BUTT;

}

/*****************************************************************************
 函 数 名  : TAF_SDC_Init1xSysInfo
 功能描述  : 初始化1X模式下的系统消息上下文
 输入参数  : TAF_SDC_1X_SYS_INFO_STRU           *pst1xSysInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月4日
    作    者   : g00261581
    修改内容   : 新生成函数
  2.日    期   : 2015年3月23日
    作    者   : w00242748
    修改内容   : DTS2015031307387:当网络把SID/NID都配成0时，这时SID/NID便不会
                 主动上报。
  3.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : DTS2015072705348:进入紧急呼回呼模式后，挂起HRPD和LTE；退出紧急呼
                 回呼模式后，再进行搜网，紧急呼回呼模式下，不进行其他任何形式搜网；
*****************************************************************************/
VOS_VOID TAF_SDC_Init1xSysInfo(
    TAF_SDC_1X_SYS_INFO_STRU           *pst1xSysInfo
)
{
    PS_MEM_SET(pst1xSysInfo, 0x0, sizeof(TAF_SDC_1X_SYS_INFO_STRU));

    pst1xSysInfo->lSid                = MMA_INVALID_SID;
    pst1xSysInfo->lNid                = MMA_INVALID_NID;

    pst1xSysInfo->uc1xRfAvailFlg      = VOS_TRUE;

    /* 需要将一些特性的参数，设置成无效值 */
    pst1xSysInfo->stServiceInfo.ulMcc = (VOS_UINT32)MMA_INVALID_MCC;
    pst1xSysInfo->stServiceInfo.usMnc = (VOS_UINT16)MMA_INVALID_MNC;
    pst1xSysInfo->ucRoamingInd        = TAF_SDC_SYS_ROAMING_STATUS_OFF;

    pst1xSysInfo->ulIsInEmcCallBack   = VOS_FALSE;
    pst1xSysInfo->ucIsEmcCallExistFlg = VOS_FALSE;

    pst1xSysInfo->enRegInfoIncl         = PS_FALSE;
    pst1xSysInfo->enBaseStationInfoIncl = PS_FALSE;
    pst1xSysInfo->enServiceInfoIncl     = PS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitHrpdSysInfo
 功能描述  : 初始化HRPD模式下的系统消息上下文
 输入参数  : TAF_SDC_HRPD_SYS_INFO_STRU         *pstHrpdSysInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitHrpdSysInfo(
    TAF_SDC_HRPD_SYS_INFO_STRU         *pstHrpdSysInfo
)
{
    PS_MEM_SET(pstHrpdSysInfo, 0x0, sizeof(TAF_SDC_HRPD_SYS_INFO_STRU));

    pstHrpdSysInfo->ucHrpdRfAvailFlg = VOS_TRUE;


    pstHrpdSysInfo->ucSessionStatus  = HRPD_SESSION_STATUS_CLOSE;

    pstHrpdSysInfo->ulMcc            = (VOS_UINT32)MMA_INVALID_MCC;

}



/*****************************************************************************
 函 数 名  : TAF_SDC_InitCsDomainInfo
 功能描述  : 初始化cs域信息
 输入参数  : pstCsDomainInfo - cs域信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年06月3日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，注册状态初始化为0
 3.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : DTS2014012305088:svlte特性开启卡无效场景mtc无需上报pstransfer:0和1
*****************************************************************************/
VOS_VOID TAF_SDC_InitCsDomainInfo(TAF_SDC_CS_DOMAIN_INFO_STRU *pstCsDomainInfo)
{
    pstCsDomainInfo->enCsRegStatus                         = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstCsDomainInfo->enCsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* 小区受限类型默认需要设置为不受限,否则设置为BUTT时RIL层认为受限 */
    pstCsDomainInfo->stCsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;

    pstCsDomainInfo->stCsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictRegister  = VOS_FALSE;

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    pstCsDomainInfo->ucSimCsRegStatus                      = VOS_FALSE;
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    TAF_SDC_SetCsAttachAllowFlg(VOS_FALSE);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitPsDomainInfo
 功能描述  : 初始化ps域信息
 输入参数  : pstPsDomainInfo - ps域信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年06月3日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，注册状态初始化为0
 3.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改

*****************************************************************************/
VOS_VOID TAF_SDC_InitPsDomainInfo(TAF_SDC_PS_DOMAIN_INFO_STRU *pstPsDomainInfo)
{
    pstPsDomainInfo->enPsRegStatus                         = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstPsDomainInfo->enPsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* 小区受限类型默认需要设置为不受限,否则设置为BUTT时RIL层认为受限 */
    pstPsDomainInfo->stPsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;

    pstPsDomainInfo->stPsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstPsDomainInfo->stPsAcRestriction.ucRestrictRegister  = VOS_FALSE;
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    pstPsDomainInfo->ucSimPsRegStatus                      = VOS_FALSE;
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    TAF_SDC_SetPsAttachAllowFlg(VOS_FALSE);

    return;
}

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-27, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitGuNwCapInfo
 功能描述  : 初始化GU的网络能力相关信息
 输入参数  : pstGuNwCapInfo - GU的网络能力相关信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月29日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_InitGuNwCapInfo(
    TAF_SDC_NETWORK_CAP_INFO_STRU *pstGuNwCapInfo
)
{
    /* 初始化网络的能力信息 */
    PS_MEM_SET(pstGuNwCapInfo, 0, sizeof(TAF_SDC_NETWORK_CAP_INFO_STRU));
    pstGuNwCapInfo->enNwImsVoCap = TAF_SDC_NW_IMS_VOICE_NOT_SUPPORTED;
    pstGuNwCapInfo->enNwEmcBsCap = TAF_SDC_NW_EMC_BS_NOT_SUPPORTED;
    pstGuNwCapInfo->enLteCsCap   = TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitLteNwCapInfo
 功能描述  : 初始化LTE的网络能力相关信息
 输入参数  : pstLteNwCapInfo - LTE的网络能力相关信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月29日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_InitLteNwCapInfo(
    TAF_SDC_NETWORK_CAP_INFO_STRU *pstLteNwCapInfo
)
{
    /* 初始化网络的能力信息 */
    PS_MEM_SET(pstLteNwCapInfo, 0, sizeof(TAF_SDC_NETWORK_CAP_INFO_STRU));
    pstLteNwCapInfo->enNwImsVoCap = TAF_SDC_NW_IMS_VOICE_NOT_SUPPORTED;
    pstLteNwCapInfo->enNwEmcBsCap = TAF_SDC_NW_EMC_BS_NOT_SUPPORTED;
    pstLteNwCapInfo->enLteCsCap   = TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED;

    return;
}

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-27, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_InitNetWorkInfo
 功能描述  : 初始化驻留网络信息
 输入参数  : pstNetworkInfo - 驻留网络信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年07月11日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseI项目
 3.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改
 4.日    期   : 2015年01月28日
   作    者   : y00245242
   修改内容   : iteration 9开发，下移IMSA接口到MSCC模块

*****************************************************************************/
VOS_VOID TAF_SDC_InitNetWorkInfo(TAF_SDC_NETWORK_INFO_STRU *pstNetworkInfo)
{
    pstNetworkInfo->stSysInfo.enSysMode      = TAF_SDC_SYS_MODE_BUTT;
    pstNetworkInfo->stSysInfo.enSysSubMode   = TAF_SDC_SYS_SUBMODE_BUTT;
    pstNetworkInfo->stSysInfo.en1xCallState  = CDMA_1X_CALL_STATE_BUTT;

    TAF_SDC_Init3gppSysInfo(&pstNetworkInfo->stSysInfo.st3gppSysInfo);

    TAF_SDC_Init1xSysInfo(&pstNetworkInfo->stSysInfo.st1xSysInfo);

    TAF_SDC_InitHrpdSysInfo(&pstNetworkInfo->stSysInfo.stHrpdSysInfo);

    TAF_SDC_InitCsDomainInfo(&pstNetworkInfo->stCsDomainInfo);

    TAF_SDC_InitPsDomainInfo(&pstNetworkInfo->stPsDomainInfo);

    pstNetworkInfo->enServiceDomain = TAF_SDC_SERVICE_DOMAIN_BUTT;

    /* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, begin */
    pstNetworkInfo->enReportSrvsta  = TAF_SDC_REPORT_SRVSTA_BUTT;

    TAF_SDC_InitGuNwCapInfo(&pstNetworkInfo->stGuNwCapInfo);
    TAF_SDC_InitLteNwCapInfo(&pstNetworkInfo->stLteNwCapInfo);

    /* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, end */

    PS_MEM_SET(pstNetworkInfo->aucReserved, 0, sizeof(pstNetworkInfo->aucReserved));

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

    TAF_SDC_SetImsNormalRegStatus(TAF_SDC_IMS_NORMAL_REG_STATUS_DEREG);
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

    TAF_SDC_InitNetworkRssiValue(&pstNetworkInfo->stSigQuaInfo);

    pstNetworkInfo->lSid = MMA_INVALID_SID;
    return;
}
/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitCsInfo
 功能描述  : 初始化驻留网络信息
 输入参数  : pstCsInfo - CS域信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月27日
   作    者   : s00217060
   修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_VOID TAF_SDC_InitCsInfo(TAF_SDC_CS_INFO_STRU *pstCsInfo)
{

    PS_MEM_SET(pstCsInfo->aucReserved, 0, sizeof(pstCsInfo->aucReserved));
    pstCsInfo->ucCsServiceConnStatusFlag    = VOS_FALSE;

    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_InitPsInfo
 功能描述  : 初始化驻留网络信息
 输入参数  : pstPsInfo - PS域信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月27日
   作    者   : s00217060
   修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_VOID TAF_SDC_InitPsInfo(TAF_SDC_PS_INFO_STRU *pstPsInfo)
{

    PS_MEM_SET(pstPsInfo->aucReserved, 0, sizeof(pstPsInfo->aucReserved));
    pstPsInfo->ucPsServiceConnStatusFlag    = VOS_FALSE;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_SDC_InitEpsInfo
 功能描述  : 初始化驻留网络信息
 输入参数  : pstEpsInfo - EPS域信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月27日
   作    者   : s00217060
   修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_VOID TAF_SDC_InitEpsInfo(TAF_SDC_EPS_INFO_STRU *pstEpsInfo)
{

    PS_MEM_SET(pstEpsInfo->aucReserved, 0, sizeof(pstEpsInfo->aucReserved));
    pstEpsInfo->ucEpsServiceConnStatusFlag    = VOS_FALSE;

    return;
}
#endif
/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */

/*****************************************************************************
 函 数 名  : TAF_SDC_InitServiceInfo
 功能描述  : 初始化业务信息
 输入参数  : pstServiceInfo - 业务信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年6月17日
   作    者   : s00217060
   修改内容   : 新增SMS和SS业务信息的初始化
 3.日    期   : 2013年09月22日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目
 4.日    期   : 2013年12月16日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII项目
 5.日    期   : 2014年6月30日
   作    者   : z00161729
   修改内容   : DSDS III新增
 6.日    期   : 2014年06月27日
   作    者   : s00217060
   修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_VOID TAF_SDC_InitServiceInfo(
    TAF_SDC_SERVICE_INFO_STRU          *pstServiceInfo
)
{
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
    pstServiceInfo->stSmsInfo.ucCsSmsSrvExistFlg    = VOS_FALSE;
    pstServiceInfo->stSmsInfo.ucPsSmsSrvExistFlg    = VOS_FALSE;
    pstServiceInfo->stSmsInfo.ucImsSmsSrvExistFlg   = VOS_FALSE;
    pstServiceInfo->stSsInfo.ucCsSsSrvExistFlg      = VOS_FALSE;
    pstServiceInfo->stSsInfo.ucImsSsSrvExistFlg     = VOS_FALSE;
    PS_MEM_SET(pstServiceInfo->stSmsInfo.aucReserved, 0, sizeof(pstServiceInfo->stSmsInfo.aucReserved));
    PS_MEM_SET(pstServiceInfo->stSsInfo.aucReserved, 0, sizeof(pstServiceInfo->stSsInfo.aucReserved));

    TAF_SDC_InitCallInfo(&(pstServiceInfo->stCallInfo));
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

    PS_MEM_SET(&pstServiceInfo->stTrigPlmnSrcSrvType, 0, sizeof(pstServiceInfo->stTrigPlmnSrcSrvType));

    /* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
    TAF_SDC_InitCsInfo(&(pstServiceInfo->stCsInfo));
    TAF_SDC_InitPsInfo(&(pstServiceInfo->stPsInfo));
#if (FEATURE_ON == FEATURE_LTE)
    TAF_SDC_InitEpsInfo(&(pstServiceInfo->stEpsInfo));
#endif
    /* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */

    return;
}


/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-26, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : TAF_SDC_InitECallNumber
 功能描述  : 初始化ecall test number或recfg number信息
 输入参数  : pstECallNumber - ecall number信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月26日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitECallNumber(
    TAF_SDC_ECALL_NUM_STRU             *pstECallNumber
)
{
    PS_MEM_SET(pstECallNumber, 0, sizeof(TAF_SDC_ECALL_NUM_STRU));

    pstECallNumber->ucNumType = 0x81;

    return;
}

#endif
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-26, end */

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitCallInfo
 功能描述  : 初始化呼叫相关信息
 输入参数  : pstCallInfo - 呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月16日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年12月23日
   作    者   : y00245242
   修改内容   : 增加SRVCC缓存处理
 3.日    期   : 2014年02月28日
   作    者   : z00161729
   修改内容   : DTS2014022800234:被叫mm收到paging会设置cs业务信令连接存在，
                但查询^usersrvstate时返回无cs业务，syscfgex设置失败回复存在cs业务，不一致
 4.日    期   : 2014-04-15
   作    者   : y00245242
   修改内容   : V3R3C60_eCall项目调整
 5.日    期   : 2014年06月27日
   作    者   : s00217060
   修改内容   : K3V3 多模多天线特性
 6.日    期   : 2014年11月17日
   作    者   : w00176964
   修改内容   : CDMA 1x项目迭代5修改
*****************************************************************************/
VOS_VOID TAF_SDC_InitCallInfo(
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo
)
{
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-17, begin */

    /* 初始化CALL相关标志 */
    pstCallInfo->ucCsCallExistFlg                       = VOS_FALSE;
    pstCallInfo->ucImsCallExistFlg                      = VOS_FALSE;

    /* SRVCC标志管理移到到CALL模块*/

    /* 初始化MM相关紧急呼号码列表 */
    PS_MEM_SET(&(pstCallInfo->stMmCallEmerNumList), 0, sizeof(TAF_SDC_MM_EMERGENCY_LIST_STRU));
    pstCallInfo->stMmCallEmerNumList.ulMcc              = TAF_SDC_INVALID_MCC;
    pstCallInfo->stMmCallEmerNumList.ucEmergencyNumber  = 0;

    /* 根据NV项en_NV_Item_CUSTOM_ECC_NUM_LIST，初始化APP定制紧急呼号码列表 */
    PS_MEM_SET(&(pstCallInfo->stCustomCallEccNumCtx), 0, sizeof(TAF_SDC_CUSTOM_ECC_CTX_STRU));
    TAF_SDC_ReadCustomEccNumListNvim();
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-17, end */

    /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
    /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */

    return;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitPhoneInfo
 功能描述  : 初始化和开关机相关的控制信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年02月03日
    作    者   : f00179208
    修改内容   : IMS动态开关配置项目
*****************************************************************************/
VOS_VOID TAF_SDC_InitPhoneInfo(
    TAF_SDC_PHONE_INFO_STRU            *pstPhInfo
)
{
    PS_MEM_SET(pstPhInfo, 0, sizeof(TAF_SDC_PHONE_INFO_STRU));

    pstPhInfo->enPhMode = TAF_SDC_PHONE_MODE_MINI;

    pstPhInfo->enImsSwitchState = TAF_SDC_IMS_SWITCH_STATE_OFF;

    PS_MEM_SET(pstPhInfo->stHardWareInfo.aucMeId, 0xFF, sizeof(VOS_UINT8) * NAS_OM_MMA_MEID_OCTET_NUM);
    pstPhInfo->stHardWareInfo.ulEsn          = 0xFFFFFFFF;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_InitRegReportStatus
 功能描述  : 初始化和注册状态上报相关的控制信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitRegReportStatus(
    TAF_SDC_REG_REPORT_STATUS_STRU     *pstRegReportStatus
)
{
    PS_MEM_SET(pstRegReportStatus, 0, sizeof(TAF_SDC_REG_REPORT_STATUS_STRU));

    pstRegReportStatus->enCregType  = TAF_SDC_CREG_TYPE_BUTT;
    pstRegReportStatus->enCgregType = TAF_SDC_CGREG_TYPE_BUTT;
    pstRegReportStatus->enCeregType = TAF_SDC_CEREG_TYPE_BUTT;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_ReadCustomEccNumListNvim
 功能描述  : 读取NV中保存的APP定制紧急呼号码
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM新增函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID TAF_SDC_ReadCustomEccNumListNvim(VOS_VOID)
{
    MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU   stCustomEccNumList;
    VOS_UINT8                               i;
    TAF_SDC_CALL_INFO_STRU                 *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();


    PS_MEM_SET(&stCustomEccNumList, 0x00, sizeof(stCustomEccNumList));

    /* 读取APP定制紧急呼列表NV */
    if (NV_OK != NV_Read(en_NV_Item_CUSTOM_ECC_NUM_LIST,
                         &stCustomEccNumList,
                         sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU)))
    {
        return;
    }

    /* 如果列表中保存的个数为无效值 */
    if ( stCustomEccNumList.ucEccNumCount > TAF_SDC_MAX_CUSTOM_ECC_NUM)
    {
        return;
    }


    /* 根据NV项的值赋值到全局变量中 */
    pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.ucEccNumCount
        = stCustomEccNumList.ucEccNumCount;

    /* 将NV读取的内容保存在全局变量中 */
    for (i = 0; i < stCustomEccNumList.ucEccNumCount; i++)
    {
        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ucCategory
            = stCustomEccNumList.astCustomEccNumList[i].ucCategory;

        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent
            = stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent;

        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ulMcc
            = stCustomEccNumList.astCustomEccNumList[i].ulMcc;

        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen
            = stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen;

        (VOS_VOID)VOS_MemCpy(pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                   stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                   stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen);
    }

    return;
}
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */



/*****************************************************************************
 函 数 名  : TAF_SDC_InitMsIdentity
 功能描述  : 初始化sim相关的ms identity信息
 输入参数  : pstMsIdentity - sim相关ms identity信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年07月222日
   作    者   : j00177245
   修改内容   : 清理Coverity
 3.日    期   : 2014年04月28日
   作    者   : s00246516
   修改内容   : 双IMSI切换时,MMA概率不触发关机和开机操作
*****************************************************************************/
VOS_VOID TAF_SDC_InitMsIdentity(TAF_SDC_SIM_MS_IDENTITY_STRU *pstMsIdentity)
{
    VOS_UINT32                          i;

    PS_MEM_SET(pstMsIdentity, 0, sizeof(TAF_SDC_SIM_MS_IDENTITY_STRU));

    for ( i = 0 ; i < TAF_SDC_MAX_IMSI_LEN; i++ )
    {
        pstMsIdentity->aucImsi[i]      = TAF_SDC_IMSI_INVALID;

		pstMsIdentity->aucLastImsi[i]  = TAF_SDC_IMSI_INVALID;
	}

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitSimStatus
 功能描述  : 初始化sim status信息
 输入参数  : pstSimStatus - sim status信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitSimStatus(TAF_SDC_SIM_STATUS_STRU *pstSimStatus)
{
    PS_MEM_SET(pstSimStatus, 0, sizeof(TAF_SDC_SIM_STATUS_STRU));

    pstSimStatus->enSimStatus = TAF_SDC_USIM_STATUS_BUTT;
    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_InitSimInfo
 功能描述  : 初始化sim信息
 输入参数  : pstSimInfo - sim信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年7月30日
   作    者   : w00176964
   修改内容   : 增加SIM卡类型的初始化
 3.日    期   : 2014年4月29日
   作    者   : w00176964
   修改内容   : V3R3C60_eCall项目:增加呼叫模式初始化

*****************************************************************************/
VOS_VOID TAF_SDC_InitSimInfo(TAF_SDC_USIM_INFO_STRU *pstSimInfo)
{
    TAF_SDC_InitSimStatus(&pstSimInfo->stUsimStatus);

    TAF_SDC_InitMsIdentity(&pstSimInfo->stMsIdentity);

    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, begin */
    pstSimInfo->enUsimType = TAF_SDC_SIM_TYPE_BUTT;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, end */

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    TAF_SDC_SetCurCallMode(TAF_SDC_CALL_MODE_BUTT);
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitCsimInfo
 功能描述  : 初始化Csim信息
 输入参数  : TAF_SDC_CSIM_INFO_STRU             *pstCsimInfo - Csim信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月2日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_SDC_InitCsimInfo(
    TAF_SDC_CSIM_INFO_STRU             *pstCsimInfo
)
{
    TAF_SDC_InitSimStatus(&pstCsimInfo->stCsimStatus);

    TAF_SDC_InitMsIdentity(&pstCsimInfo->stMsIdentity);

    pstCsimInfo->enCsimType = TAF_SDC_SIM_TYPE_BUTT;

    PS_MEM_SET(pstCsimInfo->aucRuimid, 0xff, TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT);

    return;
}

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitCtx
 功能描述  : 初始化SDC_CTX
 输入参数  : enInitType:INIT类型
             pstSdcCtx:SDC上下文信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2013年3月29日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
 3.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : SS FDN&Call Control项目:增加业务信息初始化
 4.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : ErrLog&FTM项目
 5.日    期   : 2014年08月18日
   作    者   : w00242748
   修改内容   : DTS2014082204531:CREG=1或CGREG=1设置之后，CREG主动上报和CGREG主动上报
                不断上报。
 6.日    期   : 2015年2月25日
   作    者   : z00161729
   修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_VOID TAF_SDC_InitCtx(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_CTX_STRU                    *pstSdcCtx
)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    TAF_SDC_InitMsCfgInfo(enInitType, &pstSdcCtx->stMsCfgInfo);

    TAF_SDC_InitNetWorkInfo(&pstSdcCtx->stNetworkInfo);

    TAF_SDC_InitSimInfo(&pstSdcCtx->stSimInfo.stUsimInfo);
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    TAF_SDC_InitCsimInfo(&(pstSdcCtx->stSimInfo.stCsimInfo));

    TAF_SDC_InitServiceInfo(&pstSdcCtx->stServiceInfo);

#if (FEATURE_ON == FEATURE_PTM)
    TAF_SDC_InitErrLogInfo(&pstSdcCtx->stErrlogInfo);
#endif

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
    TAF_SDC_InitPhoneInfo(&pstSdcCtx->stPhoneInfo);
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

    TAF_SDC_InitRegReportStatus(&pstSdcCtx->stRegReportStatus);

    TAF_SDC_InitAppNetwork_Info(&pstSdcCtx->stAppNetworkInfo);

    TAF_SDC_InitEnhancedOperatorNameInfo(enInitType, &pstSdcCtx->stEnhancedOperatorNameInfo);

    return;
}

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_InitCurcRptCtrlInfo
 功能描述  : 根据NV：en_NV_Item_PRIVATE_CMD_STATUS_RPT，初始化主动上报能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月4日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID TAF_SDC_InitCurcRptCtrlInfo(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl = VOS_NULL_PTR;
    NVIM_PRIVATE_CMD_STATUS_RPT_STRU        stNvimCmdRptCtrl;
    VOS_UINT32                              ulLength;

    ulLength = 0;

    /* 读取^CURC命令对应的NV项到全局变量 */
    stNvimCmdRptCtrl.ucStatus                     = VOS_FALSE;
    stNvimCmdRptCtrl.ucStatusRptGeneralControl    = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_REPORT;

    pstCurcRptCtrl = TAF_SDC_GetCurcRptCtrl();
    (VOS_VOID)NV_GetLength(en_NV_Item_PRIVATE_CMD_STATUS_RPT, &ulLength);

    if(NV_OK != NV_Read(en_NV_Item_PRIVATE_CMD_STATUS_RPT,
                          &stNvimCmdRptCtrl,
                          ulLength))
    {
        pstCurcRptCtrl->enStatusRptGeneralControl = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_REPORT;
        PS_MEM_SET(pstCurcRptCtrl->aucRptCfg, 0xFF, TAF_SDC_RPT_CFG_MAX_SIZE);
    }
    else
    {
        if( (VOS_TRUE == stNvimCmdRptCtrl.ucStatus)
         && (VOS_FALSE == stNvimCmdRptCtrl.ucStatusRptGeneralControl) )
        {
            pstCurcRptCtrl->enStatusRptGeneralControl = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_NO_REPORT;
            PS_MEM_SET(pstCurcRptCtrl->aucRptCfg, 0x00, TAF_SDC_RPT_CFG_MAX_SIZE);
        }
        else
        {
            pstCurcRptCtrl->enStatusRptGeneralControl = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_REPORT;
            PS_MEM_SET(pstCurcRptCtrl->aucRptCfg, 0xFF, TAF_SDC_RPT_CFG_MAX_SIZE);
        }
    }
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitUnsolicitedRptCtrlInfo
 功能描述  : 初始化单个命令主动上报控制全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年3月29日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2015年11月26日
   作    者   : h00360002
   修改内容   : CTZR新增CTZE上报

*****************************************************************************/
VOS_VOID TAF_SDC_InitUnsolicitedRptCtrlInfo(VOS_VOID)
{
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    /* 默认为主动上报全打开 */
    PS_MEM_SET(pstUnsolicitedRptCtrl->aucRptCfg, 0xFF, TAF_SDC_RPT_CFG_MAX_SIZE);

    /* CREG/CGREG/CEREG关闭 */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CREG, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CGREG, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CEREG, VOS_FALSE);

    /* CTZR关闭 */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZV, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZE, VOS_FALSE);

    /* CUSD关闭 */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUSD, VOS_FALSE);

    /* CUUS1关闭 */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1I, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1U, VOS_FALSE);

    /* CSSN关闭 */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSI, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSU, VOS_FALSE);

    /* 流量上报初始值通过读NV en_NV_Item_DSFLOW_REPORT获取 */

    /* CERSSI上报初始值通过读en_NV_Item_CELL_SIGN_REPORT_CFG获取 */
    TAF_SDC_ReadCellSignReportCfgNV();
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_ReadEnhancedOperNameServiceCfgNvim
 功能描述  : 从NV中获取EONS特性相关配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月13日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_VOID TAF_SDC_ReadEnhancedOperNameServiceCfgNvim( VOS_VOID )
{
    TAF_NVIM_ENHANCED_OPER_NAME_SERVICE_CFG_STRU            stOperNameCfg;
    VOS_UINT32                                              ulLength;
    TAF_SDC_OPER_NAME_TYPE_PRIO_STRU                       *pstOperNamePrio = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;
    VOS_UINT8                                               ucOperNamePrioNum;
    VOS_CHAR                                                cWildCard;

    pstOperNamePrio   = TAF_SDC_GetOperNamePrio();
    PS_MEM_SET(&stOperNameCfg, 0x00, sizeof(stOperNameCfg));
    ulLength          = 0;
    ucOperNamePrioNum = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG, &ulLength);

    if (ulLength > sizeof(TAF_NVIM_ENHANCED_OPER_NAME_SERVICE_CFG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadEnhancedOperNameServiceCfgNvim:read en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG len failed");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG,
                         &stOperNameCfg, ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadEnhancedOperNameServiceCfgNvim:read en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG failed");
        return;
    }

    pstOperNamePrio->ucOperNamePrioNum = stOperNameCfg.ucOperNameServicePrioNum;

    if (pstOperNamePrio->ucOperNamePrioNum > TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM)
    {
        pstOperNamePrio->ucOperNamePrioNum = TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM;
    }

    for (ucIndex = 0; ucIndex < pstOperNamePrio->ucOperNamePrioNum; ucIndex++)
    {
        if (stOperNameCfg.aucOperNameSerivcePrio[ucIndex] >= TAF_SDC_OPER_NAME_TYPE_BUTT)
        {
            continue;
        }

        pstOperNamePrio->aucOperNameTypePrio[ucOperNamePrioNum] = stOperNameCfg.aucOperNameSerivcePrio[ucIndex];
        ucOperNamePrioNum++;
    }

    pstOperNamePrio->ucOperNamePrioNum = ucOperNamePrioNum;

    /* plmn比较支持通配符且通配符为a-f,则更新全局变量 */
    if (VOS_FALSE == stOperNameCfg.ucPlmnCompareSupportWildCardFlag)
    {
        return;
    }

    /* 数字不能做为通配符 */
    if (stOperNameCfg.ucWildCard <= 0x09)
    {
        return;
    }

    /* nv项配置0xA代表字符'A',0xA代表字符'B',0xC代表字符'C',0xD代表字符'D',
       0xE代表字符'E',0xF代表字符'F',其他值认为非法 */
    if ((0x0A == stOperNameCfg.ucWildCard)
     || (0x0B == stOperNameCfg.ucWildCard)
     || (0x0C == stOperNameCfg.ucWildCard)
     || (0x0D == stOperNameCfg.ucWildCard)
     || (0x0E == stOperNameCfg.ucWildCard)
     || (0x0F == stOperNameCfg.ucWildCard))
    {
        cWildCard = (VOS_CHAR)(stOperNameCfg.ucWildCard + 0x37);
        TAF_SDC_SetPlmnCompareWildCard(cWildCard);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_ReadCustomOperNameInfoNvim
 功能描述  : 读取50024 nv项
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月27日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_VOID TAF_SDC_ReadCustomOperNameInfoNvim(VOS_VOID)
{
    VOS_UINT16                          usIndex;
    NAS_MMA_NVIM_OPERATOR_NAME_STRU     stNvCustomOperName;
    VOS_UINT32                          ulNvLen;
    TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU *pstCustomOperNameInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucNvDataIndex = VOS_NULL_PTR;

    pstCustomOperNameInfo = TAF_SDC_GetCustomOperNameInfo();
    ulNvLen               = 0;
    PS_MEM_SET(&stNvCustomOperName, 0x00, sizeof(stNvCustomOperName));

    (VOS_VOID)NV_GetLength(en_NV_Item_HUAWEI_NW_OPL_NAME_CUSTOMIZED, &ulNvLen);

    if ( ulNvLen > sizeof(NAS_MMA_NVIM_OPERATOR_NAME_STRU))
    {
        return;
    }

    if (NV_OK !=  NV_Read(en_NV_Item_HUAWEI_NW_OPL_NAME_CUSTOMIZED,(VOS_VOID *)(&stNvCustomOperName),  ulNvLen))
    {
        return;
    }

    if( NV_ITEM_DEACTIVE == stNvCustomOperName.aucRcvData[0])
    {
        return;
    }

    pucNvDataIndex = stNvCustomOperName.aucRcvData + 4;

    for ( usIndex = 0; usIndex < TAF_NVIM_STORED_OPER_NAME_NUM; usIndex++ )
    {
        PS_MEM_CPY(&pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorPlmnId,
                   pucNvDataIndex, NV_ITEM_PLMN_ID_LEN);

        TAF_SDC_ConvertPlmnId2NasStyle(&pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorPlmnId);
        pucNvDataIndex += NV_ITEM_PLMN_ID_LEN;

        PS_MEM_CPY(pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorNameShort.aucOperatorName,
                   pucNvDataIndex, NV_ITEM_OPER_NAME_SHORT);

        pucNvDataIndex += NV_ITEM_OPER_NAME_SHORT;

        PS_MEM_CPY(pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorNameLong.aucOperatorName,
                   pucNvDataIndex, NV_ITEM_OPER_NAME_LONG);

        pucNvDataIndex += NV_ITEM_OPER_NAME_LONG;
    }

    return;
}



/*****************************************************************************
 函 数 名  : TAF_SDC_ReadCellSignReportCfgNV
 功能描述  : 从NV中读取信号质量上报相关配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年03月06日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID TAF_SDC_ReadCellSignReportCfgNV( VOS_VOID )
{
    TAF_SDC_CELL_SIGN_REPORT_CFG_STRU   stCellSignReportCfg;
    VOS_UINT32                          ulCerssiRptFlg;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stCellSignReportCfg, 0x0, sizeof(stCellSignReportCfg));
    (VOS_VOID)NV_GetLength(en_NV_Item_CELL_SIGN_REPORT_CFG, &ulLength);
    if (ulLength > sizeof(stCellSignReportCfg))
    {
        return;
    }
    if(NV_OK != NV_Read(en_NV_Item_CELL_SIGN_REPORT_CFG,
                          &stCellSignReportCfg,
                          ulLength))
    {
         TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadCellSignReportCfgNV:read en_NV_Item_CELL_SIGN_REPORT_CFG failed");
         return;
    }

    ulCerssiRptFlg  = VOS_TRUE;

    /* 门限值为无效值，不上报 */
    if (TAF_SDC_MAX_SIGN_THRESHOLD < stCellSignReportCfg.ucSignThreshold)
    {
        ulCerssiRptFlg  = VOS_FALSE;
    }

    /* 门限值为0，不上报 */
    if (0 == stCellSignReportCfg.ucSignThreshold)
    {
        ulCerssiRptFlg  = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CERSSI, ulCerssiRptFlg);

    return;
}

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_SetXsmsCallExistFlg
 功能描述  : 设置当前是否处于xsms CALL中
 输入参数  : ucIsXsmsCallExistFlg - 当前是否处于xsms CALL中
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月07日
   作    者   : c00299064
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID    TAF_SDC_SetXsmsCallExistFlg(
    VOS_UINT8                           ucIsXsmsCallExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucIsXsmsCallExistFlg = ucIsXsmsCallExistFlg;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetXsmsCallExistFlg
 功能描述  : 当前是否处于xsms CALL中
 输入参数  :
 输出参数  : 无
 返 回 值  : XSMS CALL STATUS
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月07日
   作    者   : c00299064
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetXsmsCallExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucIsXsmsCallExistFlg;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCsCallExistFlg
 功能描述  : 设置当前是否处于CS CALL中
 输入参数  : ucCsCallExistFlg - 当前是否处于CS CALL中
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目

*****************************************************************************/
VOS_VOID    TAF_SDC_SetCsCallExistFlg(
    VOS_UINT8                           ucCsCallExistFlg
)
{
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsCallExistFlg = ucCsCallExistFlg;
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCsEccExistFlg
 功能描述  : 设置当前是否处于CS 紧急呼中
 输入参数  : ucCsEccExistFlg - 当前是否处于CS 紧急呼中
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月9日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    TAF_SDC_SetCsEccExistFlg(
    VOS_UINT8                           ucCsEccExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsEccExistFlg = ucCsEccExistFlg;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsEccExistFlg
 功能描述  : 获取当前是否处于CS 紧急呼中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前是否处于CS 紧急呼中
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月9日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCsEccExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsEccExistFlg;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCsServiceConnStatusFlag
 功能描述  : 设置cs业务信令连接标识是否存在
 输入参数  : ucCsServiceConnStatusFlag - cs业务信令连接标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年02月28日
   作    者   : z00161729
   修改内容   : DTS2014022800234:被叫mm收到paging会设置cs业务信令连接存在，
                但查询^usersrvstate时返回无cs业务，syscfgex设置失败回复存在cs业务，不一致

*****************************************************************************/
VOS_VOID TAF_SDC_SetCsServiceConnStatusFlag(
    VOS_UINT8                           ucCsServiceConnStatusFlag
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCsInfo.ucCsServiceConnStatusFlag = ucCsServiceConnStatusFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetTrigPlmnSearchSrvType
 功能描述  : 获取业务触发搜网业务类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 业务类型
 调用函数  :
 被调函数  :

 修改历史     :

*****************************************************************************/
TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION *TAF_SDC_GetTrigPlmnSearchSrvType(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stTrigPlmnSrcSrvType);
}



/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsServiceConnStatusFlag
 功能描述  : 获取cs业务信令连接是否存在标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : cs业务信令连接标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年02月28日
   作    者   : z00161729
   修改内容   : DTS2014022800234:被叫mm收到paging会设置cs业务信令连接存在，
                但查询^usersrvstate时返回无cs业务，syscfgex设置失败回复存在cs业务，不一致

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCsServiceConnStatusFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCsInfo.ucCsServiceConnStatusFlag;
}



/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsCallExistFlg
 功能描述  : 获取当前是否处于CS呼叫中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否处于CS呼叫中
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetCsCallExistFlg(VOS_VOID)
{
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsCallExistFlg;
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */
}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_SetImsCallExistFlg
 功能描述  : 设置当前是否处于IMS CALL中
 输入参数  : ucImsCallExistFlg - 当前是否处于IMS CALL中
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目新增

*****************************************************************************/
VOS_VOID    TAF_SDC_SetImsCallExistFlg(
    VOS_UINT8                           ucImsCallExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucImsCallExistFlg = ucImsCallExistFlg;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetImsCallExistFlg
 功能描述  : 获取当前是否处于IMS呼叫中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否处于IMS呼叫中
 调用函数  :
 被调函数  :

 修改历史     :
 2.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目新增

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetImsCallExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucImsCallExistFlg;
}
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

/* SRVCC移到CALL模块自己维护管理*/

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetCallInfo
 功能描述  : 获取呼叫信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_CALL_INFO_STRU:呼叫信息
 调用函数  :
 被调函数  :

 修改历史     :
 2.日    期   : 2013年12月16日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII项目新增

*****************************************************************************/
TAF_SDC_CALL_INFO_STRU* TAF_SDC_GetCallInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetMmCallEmerNumList
 功能描述  : 设置MM相关紧急呼列表
 输入参数  : stMmCallEmerNumList - MM相关紧急呼列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月16日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII项目新增

*****************************************************************************/
VOS_VOID TAF_SDC_SetMmCallEmerNumList(
    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList
)
{
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();

    PS_MEM_CPY(&(pstCallInfo->stMmCallEmerNumList), pstMmCallEmerNumList, sizeof(TAF_SDC_MM_EMERGENCY_LIST_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetMmCallEmerNumList
 功能描述  : 获取MM相关紧急呼列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MM相关紧急呼列表
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月16日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII项目新增

*****************************************************************************/
TAF_SDC_MM_EMERGENCY_LIST_STRU* TAF_SDC_GetMmCallEmerNumList(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stMmCallEmerNumList);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCustomCallEccNumCtx
 功能描述  : 设置运营商定制相关紧急呼列表
 输入参数  : stCustomCallEccNumCtx - 运营商定制相关紧急呼列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月16日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII项目新增

*****************************************************************************/
VOS_VOID TAF_SDC_SetCustomCallEccNumCtx(
    TAF_SDC_CUSTOM_ECC_CTX_STRU        *pstCustomCallEccNumCtx
)
{
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();

    PS_MEM_CPY(&(pstCallInfo->stCustomCallEccNumCtx), pstCustomCallEccNumCtx, sizeof(TAF_SDC_CUSTOM_ECC_CTX_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCustomCallEccNumCtx
 功能描述  : 获取运营商定制相关紧急呼列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 运营商定制相关紧急呼列表
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月16日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII项目新增

*****************************************************************************/
TAF_SDC_CUSTOM_ECC_CTX_STRU* TAF_SDC_GetCustomCallEccNumCtx(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stCustomCallEccNumCtx);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetCallEmerNumsNoUsimTblAddr
 功能描述  : 获取无卡时的紧急呼列表首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无卡时的紧急呼列表首地址
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月16日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_CHAR** TAF_SDC_GetCallEmerNumsNoUsimTblAddr(VOS_VOID)
{
    return g_aucTafSdcCallEmerNumsNoUsim;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCallEmerNumsNoUsimTblAddr
 功能描述  : 获取有卡时的紧急呼列表首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 有卡时的紧急呼列表首地址
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月16日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_CHAR** TAF_SDC_GetCallEmerNumsWithUsimTblAddr(VOS_VOID)
{
    return g_aucTafSdcCallEmerNumsWithUsim;
}

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_SDC_GetCdmaCallEmcNumsAddr
 功能描述  : 获取中国电信预置的紧急呼叫号码列表地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 中国电信预置的紧急呼叫号码列表地址
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2016年02月04日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_CHAR** TAF_SDC_GetCdmaCallEmcNumsAddr(VOS_VOID)
{
    return g_acTafSdcCdmaCallEmcNums;
}
#endif
/*****************************************************************************
 函 数 名  : TAF_SDC_SetUtranSkipWPlmnSearchFlag
 功能描述  : 设置UTRAN搜网状态机在搜T/W状态有副卡gsm中国区信息的前提下，是否需要跳过w搜索的标识
 输入参数  : ucUtranSkipWPlmnSearchFlag - UTRAN搜网状态机在搜T/W状态有副卡gsm中国区信息的前提下是否需要跳过w搜索的标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SDC_SetUtranSkipWPlmnSearchFlag(VOS_UINT8  ucUtranSkipWPlmnSearchFlag)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag = ucUtranSkipWPlmnSearchFlag;
    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetUtranSkipWPlmnSearchFlag
 功能描述  : 获取UTRAN搜网状态机在搜T/W状态有副卡gsm中国区信息的前提下，是否需要跳过w搜索的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : UTRAN搜网状态机在搜T/W状态有副卡gsm中国区信息的前提下是否需要跳过w搜索的标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  TAF_SDC_GetUtranSkipWPlmnSearchFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_InitDsdaPlmnSearchEnhancedCfg
 功能描述  : 控制通过两个Modem的信息交互的增强型的搜索策略；当前支持的策略为：
             通过另一Modem的PLMN信息,控制FDD搜网是否跳过的策略。
             比如GUTL+G的版本，当副卡已经驻留在国内G网的时候，主卡搜网可以跳过FDD的搜索（中移动国内只需要支持TDD模式）
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月23日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_InitDsdaPlmnSearchEnhancedCfg(VOS_VOID)
{
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU                   stDsdaPlmnSearchEnhancedCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stDsdaPlmnSearchEnhancedCfg, 0x00, sizeof(stDsdaPlmnSearchEnhancedCfg));

    TAF_SDC_SetUtranSkipWPlmnSearchFlag(VOS_FALSE);

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG, &ulLength);

    if (ulLength > sizeof(NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU))
    {
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG,
                         &stDsdaPlmnSearchEnhancedCfg, ulLength))
    {
        return;
    }

    if (VOS_TRUE == (stDsdaPlmnSearchEnhancedCfg.usSolutionMask & 0x0001))
    {
         TAF_SDC_SetUtranSkipWPlmnSearchFlag(VOS_TRUE);
    }
#endif

    return;
}



/*****************************************************************************
 函 数 名  : TAF_SDC_SetUssdTransMode
 功能描述  : 设置当前USSD的传输模式
 输入参数  : ucTransMode - 当前USSD的传输模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID    TAF_SDC_SetUssdTransMode(
    VOS_UINT8                           ucTransMode
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucUssdTransMode = ucTransMode;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetUssdTransMode
 功能描述  : 获取当前USSD的传输模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前USSD的传输模式
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetUssdTransMode(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucUssdTransMode;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Set7BitToAssicTableType
 功能描述  : 设置当前ussd的转换表类型
 输入参数  : ucType - ussd的转换表类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID    TAF_SDC_Set7BitToAssicTableType(
    VOS_UINT8                           ucType
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucAlphaTransMode = ucType;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get7BitToAssicTableType
 功能描述  : 获取当前ussd的转换表类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前ussd的转换表类型
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8   TAF_SDC_Get7BitToAssicTableType(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucAlphaTransMode;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurr7BitToAsciiTableAddr
 功能描述  : 获取当前的7BIT到ASCII的转换表指针
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前的7BIT到ASCII的转换表指针
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年5月17日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8*   TAF_SDC_GetCurr7BitToAsciiTableAddr(VOS_VOID)
{
    if (TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_TME == TAF_SDC_Get7BitToAssicTableType())
    {
        return g_aucTafSdcTme7BitToAsciiTbl;
    }
    else
    {
        return g_aucTafSdcDef7BitToAsciiTbl;
    }
}


/*****************************************************************************
 函 数 名  : TAF_SDC_Get3GppCurrentLai
 功能描述  : 获取3GPP服务小区信息并编码
 输入参数  : VOS_UINT8                          *aucLai     服务小区信息
             VOS_UINT32                         *pulLaiLen  服务小区信息长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月16日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数 DTS2011062201273 MO SMS CONTROL
  6.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，
                 MN_GetLaiForMoCtrl->TAF_SDC_GetCurrentLai
*****************************************************************************/
VOS_VOID TAF_SDC_Get3GppCurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
)
{
    VOS_UINT32                          ulPos;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enCsRegStatus;
    TAF_SDC_3GPP_SYS_INFO_STRU         *pst3gppSysInfo = VOS_NULL_PTR;
    TAF_SDC_SYS_INFO_STRU              *pstSysInfo = VOS_NULL_PTR;

    pst3gppSysInfo = TAF_SDC_Get3gppSysInfo();
    pstSysInfo     = TAF_SDC_GetSysInfo();

    ulPos = 0;

    aucLai[ulPos]  = (VOS_UINT8)(0x0000000F & pst3gppSysInfo->stPlmnId.ulMcc);
    aucLai[ulPos] |= (VOS_UINT8)((0x00000F00 & pst3gppSysInfo->stPlmnId.ulMcc) >> 4);
    ulPos++;

    aucLai[ulPos]  = (VOS_UINT8)((0x000F0000 & pst3gppSysInfo->stPlmnId.ulMcc) >> 16);
    aucLai[ulPos] |= (VOS_UINT8)((0x000F0000 & pst3gppSysInfo->stPlmnId.ulMnc) >> 12);
    ulPos++;

    aucLai[ulPos]  = (VOS_UINT8)(0x0000000F & pst3gppSysInfo->stPlmnId.ulMnc);
    aucLai[ulPos] |= (VOS_UINT8)((0x00000F00 & pst3gppSysInfo->stPlmnId.ulMnc) >> 4);
    ulPos++;

    aucLai[ulPos]  = (VOS_UINT8)((pst3gppSysInfo->usLac & 0xff00) >> 8);
    ulPos++;
    aucLai[ulPos]  = (VOS_UINT8)(pst3gppSysInfo->usLac & 0x00ff);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((pst3gppSysInfo->ulCellId >> 8) & 0xff);
    ulPos++;
    aucLai[ulPos] = (VOS_UINT8)(pst3gppSysInfo->ulCellId & 0xff);
    ulPos++;

    if (TAF_SDC_SYS_MODE_GSM != pstSysInfo->enSysMode)
    {
        aucLai[ulPos] = (VOS_UINT8)((pst3gppSysInfo->ulCellId >> 24) & 0xff);
        ulPos++;
        aucLai[ulPos] = (VOS_UINT8)((pst3gppSysInfo->ulCellId >> 16) & 0xff);
        ulPos++;
    }

    *pulLaiLen = ulPos;

    /*获取MM层注册状态*/
    enCsRegStatus = TAF_SDC_GetCsRegStatus();
    if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK != enCsRegStatus)
     && (TAF_SDC_REG_REGISTERED_ROAM != enCsRegStatus))
    {
        PS_MEM_SET(aucLai, (VOS_CHAR)0xff, ulPos);
    }

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_SDC_Get3Gpp2CurrentLai
 功能描述  : 获取3GPP2服务小区信息并编码
 输入参数  : VOS_UINT8                          *aucLai
             VOS_UINT32                         *pulLaiLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月6日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_Get3Gpp2CurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
)
{
    /***********************************************************************
     Description                      Length(Byte)
     MCC                              2
     IMSI_11_12                       1
     SID                              2
     NID                              2
     BASE_ID                          2
     BASE_LAT                         3
     BASE_LONG                        3
     ************************************************************************/
    VOS_UINT32                          ulPos;
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulMcc;
    VOS_UINT8                           ucImsi_11_12;

    ulPos = 0;
    pstSdc1xSysInfo   = TAF_SDC_Get1xSysInfo();

    /* MCC */
    ulMcc = TAF_STD_TransformBcdMccToDeciDigit(pstSdc1xSysInfo->stServiceInfo.ulMcc);
    aucLai[ulPos]  = TAF_SDC_GET_STK_MCC(ulMcc) & 0x00FF;
    ulPos++;

    aucLai[ulPos]  = (TAF_SDC_GET_STK_MCC(ulMcc) & 0xFF00) >> 8;
    ulPos++;

    /* IMSI_11_12*/
    ucImsi_11_12 = TAF_STD_TransformBcdImsi1112ToDeciDigit(pstSdc1xSysInfo->stServiceInfo.usImsi11_12);
    aucLai[ulPos]  = (VOS_UINT8)TAF_SDC_GET_STK_MNC(ucImsi_11_12);
    ulPos++;

    /* SID */
    aucLai[ulPos] = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->lSid);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->lSid) >> 8);
    ulPos++;

    /* NID */
    aucLai[ulPos] = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->lNid);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->lNid) >> 8);
    ulPos++;

    /* BASE_ID */
    aucLai[ulPos] = (VOS_UINT8)(0x00FF & pstSdc1xSysInfo->stBaseStationInfo.usBaseId);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0xFF00 & pstSdc1xSysInfo->stBaseStationInfo.usBaseId) >> 8);
    ulPos++;

    /* BASE_LAI */
    aucLai[ulPos] = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude) >> 8);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x00FF0000 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude) >> 16);
    ulPos++;

    /* BASE_LONG */
    aucLai[ulPos]  = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude) >> 8);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x00FF0000 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude) >> 16);
    ulPos++;

    *pulLaiLen = ulPos;

}
#endif

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurrentLai
 功能描述  : 获取服务小区信息并编码
 输入参数  : VOS_UINT8                          *aucLai
             VOS_UINT32                         *pulLaiLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月6日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_GetCurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* CDMA inside，并且当前是CL模式 */
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        TAF_SDC_Get3Gpp2CurrentLai(aucLai, pulLaiLen);
    }
    else
    {
        TAF_SDC_Get3GppCurrentLai(aucLai, pulLaiLen);
    }
#else
    TAF_SDC_Get3GppCurrentLai(aucLai, pulLaiLen);
#endif
}




/*****************************************************************************
 函 数 名  : TAF_SDC_SetSvlteFlg
 功能描述  : 设置是否支持SVLTE
 输入参数  : ulSvlteFlg - SVLTE标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年6月3日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID    TAF_SDC_SetSvlteSupportFlag(
    VOS_UINT8                          ucSvlteSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.ucSvlteSupportFlag = ucSvlteSupportFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetSvlteFlg
 功能描述  : 获取是否支持SVLTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持SVLTE
             VOS_FALSE:不支持SVLTE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年6月3日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetSvlteSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.ucSvlteSupportFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCsSmsSrvExistFlg
 功能描述  : 设置当前是否有CS域的短信业务
 输入参数  : ucCsSmsSrvExistFlg - 当前是否有CS域的短信业务
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年6月17日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID    TAF_SDC_SetCsSmsSrvExistFlg(
    VOS_UINT8                           ucCsSmsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucCsSmsSrvExistFlg = ucCsSmsSrvExistFlg;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsSmsSrvExistFlg
 功能描述  : 获取当前是否有CS域的短信业务的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否有CS域的短信业务
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年6月17日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetCsSmsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucCsSmsSrvExistFlg;
}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_SetPsSmsSrvExistFlg
 功能描述  : 设置当前是否有PS域的短信业务
 输入参数  : ucPsSmsSrvExistFlg - 当前是否有PS域的短信业务
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsSmsSrvExistFlg(
    VOS_UINT8                           ucPsSmsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucPsSmsSrvExistFlg = ucPsSmsSrvExistFlg;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetPsSmsSrvExistFlg
 功能描述  : 获取当前是否有PS域的短信业务的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否有PS域的短信业务
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetPsSmsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucPsSmsSrvExistFlg;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetImsSmsSrvExistFlg
 功能描述  : 设置当前是否有IMS域的短信业务
 输入参数  : ucImsSmsSrvExistFlg - 当前是否有IMS域的短信业务
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月23日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetImsSmsSrvExistFlg(
    VOS_UINT8                           ucImsSmsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucImsSmsSrvExistFlg = ucImsSmsSrvExistFlg;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetImsSmsSrvExistFlg
 功能描述  : 获取当前是否有IMS域的短信业务的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否有IMS域的短信业务
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetImsSmsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucImsSmsSrvExistFlg;
}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCsSsSrvExistFlg
 功能描述  : 设置当前是否有CS域的补充业务
 输入参数  : ucCsSsSrvExistFlg - 当前是否有CS域的补充业务
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年6月17日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID    TAF_SDC_SetCsSsSrvExistFlg(
    VOS_UINT8                           ucCsSsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucCsSsSrvExistFlg = ucCsSsSrvExistFlg;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCsSsSrvExistFlg
 功能描述  : 获取当前是否有CS域的补充业务的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否有CS域的补充业务
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年6月17日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetCsSsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucCsSsSrvExistFlg;
}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_SetImsSsSrvExistFlg
 功能描述  : 设置当前是否有IMS域的补充业务
 输入参数  : ucImsSsSrvExistFlg - 当前是否有IMS域的补充业务
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月23日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID    TAF_SDC_SetImsSsSrvExistFlg(
    VOS_UINT8                           ucImsSsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucImsSsSrvExistFlg = ucImsSsSrvExistFlg;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetImsSsSrvExistFlg
 功能描述  : 获取当前是否有IMS域的补充业务的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否有IMS域的补充业务
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月23日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetImsSsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucImsSsSrvExistFlg;
}/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */


/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-11, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_SetGsmImsSupportFlag
 功能描述  : 设置是否支持GSM下的IMS
 输入参数  : ucGsmImsSupportFlag - Gsm下的IMS标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年7月11日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetGsmImsSupportFlag(
    VOS_UINT8                          ucGsmImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag = ucGsmImsSupportFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetGsmImsSupportFlag
 功能描述  : 获取是否支持GSM下的IMS标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持GSM下的IMS
             VOS_FALSE:不支持GSM下的IMS
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年7月11日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetGsmImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetUtranImsSupportFlag
 功能描述  : 设置是否支持Utran下的IMS
 输入参数  : ucUtranImsSupportFlag - Utran下的IMS标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年7月11日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetUtranImsSupportFlag(
    VOS_UINT8                          ucUtranImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag = ucUtranImsSupportFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetUtranImsSupportFlag
 功能描述  : 获取是否支持Utran下的IMS标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持Utran下的IMS
             VOS_FALSE:不支持Utran下的IMS
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年7月11日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetUtranImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetLteImsSupportFlag
 功能描述  : 设置是否支持LTE下的IMS
 输入参数  : ucLteImsSupportFlag - LTE下的IMS标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年7月11日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetLteImsSupportFlag(
    VOS_UINT8                          ucLteImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag = ucLteImsSupportFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetLteImsSupportFlag
 功能描述  : 获取是否支持LTE下的IMS标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持LTE下的IMS
             VOS_FALSE:不支持LTE下的IMS
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年7月11日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetLteImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetAppCfgSupportType
 功能描述  : 设置对接的应用类型
 输入参数  : usAppCfgSupportType - 对接的应用类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年7月11日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCfgSupportType(
    VOS_UINT16                          usAppCfgSupportType
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.usAppCfgSupportType = usAppCfgSupportType;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppCfgSupportType
 功能描述  : 获取对接的应用类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : usAppCfgSupportType:对接的应用类型
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年7月11日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 TAF_SDC_GetAppCfgSupportType(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.usAppCfgSupportType;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SaveCsimCardType
 功能描述  : 保存Csim卡类型
 输入参数  : USIMM_CARD_TYPE_ENUM_UINT32 enCardType: Csim卡类型
 输出参数  : 无
 返 回 值  : TRUE -- change
             FALSE-- not change
 修改历史      :
  1.日    期   : 2015年02月07日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SaveCsimCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType
)
{
        VOS_UINT8                           ucSimType;

        switch (enCardType)
        {
            case USIMM_CARD_UIM:
                ucSimType = TAF_SDC_SIM_TYPE_UIM;
                break;

            case USIMM_CARD_CSIM:
                ucSimType = TAF_SDC_SIM_TYPE_CSIM;
                break;

            case USIMM_CARD_NOCARD:
            case USIMM_CARD_ISIM:
            default:

                ucSimType = TAF_SDC_SIM_TYPE_BUTT;
                break;
        }

        TAF_SDC_SetCsimType(ucSimType);

        return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SaveUsimCardType
 功能描述  : 保存Usim卡类型
 输入参数  : USIMM_CARD_TYPE_ENUM_UINT32 enCardType: Usimm卡类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SaveUsimCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType
)
{
    VOS_UINT8                           ucSimType;

    switch (enCardType)
    {
        case USIMM_CARD_SIM:

            ucSimType = TAF_SDC_SIM_TYPE_SIM;
            break;

        case USIMM_CARD_USIM:

            ucSimType = TAF_SDC_SIM_TYPE_USIM;
            break;

        case USIMM_CARD_ROM_SIM:
            ucSimType = TAF_SDC_SIM_TYPE_ROM_SIM;
            break;

        case USIMM_CARD_NOCARD:
        case USIMM_CARD_ISIM:
        default:

            ucSimType = TAF_SDC_SIM_TYPE_BUTT;
            break;
    }

    TAF_SDC_SetUsimType(ucSimType);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SaveUsimCardStatus
 功能描述  : change MMA USIM status
 输入参数  : VOS_UINT32  ulUsimSta
 输出参数  : 无
 返 回 值  : VOS_VOID
 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SaveUsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enUsimStatus
)
{
    switch ( enUsimStatus )
    {
        case USIMM_CARD_SERVIC_ABSENT :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_NO_PRESENT);
             return;

        case USIMM_CARD_SERVIC_UNAVAILABLE :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_UNVALID);
             return;

        case USIMM_CARD_SERVIC_SIM_PIN :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_SIM_PIN);
             return;

        case USIMM_CARD_SERVIC_SIM_PUK :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_SIM_PUK);
             return;

        case USIMM_CARD_SERVIC_NET_LCOK :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_NET_LCOK);
             return;

        case USIMM_CARD_SERVICE_IMSI_LOCK :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_IMSI_LCOK);
             return;

        case USIMM_CARD_SERVIC_AVAILABLE :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_VALID);
             return;

        /* 异常处理 */
        default :
            TAF_WARNING_LOG(WUEPS_PID_MMA, "MMA_ChangeUsimStatus: USIM STATUS INVALID");

            /* 其他情况下认为卡状态有效 */
            TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_VALID);
            return ;
    }
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SaveCsimCardStatus
 功能描述  : 保存Csim卡状态
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   : 2015年02月07日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SaveCsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCsimStatus
)
{
    switch ( enCsimStatus )
    {
        case USIMM_CARD_SERVIC_ABSENT :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_NO_PRESENT);
             return;

        case USIMM_CARD_SERVIC_UNAVAILABLE :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_UNVALID);
             return;

        case USIMM_CARD_SERVIC_SIM_PIN :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_SIM_PIN);
             return;

        case USIMM_CARD_SERVIC_SIM_PUK :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_SIM_PUK);
             return;

        case USIMM_CARD_SERVIC_NET_LCOK :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_NET_LCOK);
             return;

        case USIMM_CARD_SERVICE_IMSI_LOCK :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_IMSI_LCOK);
             return;

        case USIMM_CARD_SERVIC_AVAILABLE :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_VALID);
             return;

        /* 异常处理 */
        default :
            TAF_WARNING_LOG(WUEPS_PID_MMA, "MMA_ChangeUsimStatus: USIM STATUS INVALID");

            /* 其他情况下认为卡状态有效 */
            TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_VALID);
            return ;
    }
}

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-11, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrLogRingBufAddr
 功能描述  : 获取TAF层RING BUFFER的地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF层RING BUFFER的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
OM_RING_ID TAF_SDC_GetErrLogRingBufAddr(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.pstRingBuffer;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrLogRingBufAddr
 功能描述  : 设置TAF层RING BUFFER的地址
 输入参数  : RING BUFFER的地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogRingBufAddr(OM_RING_ID pRingBuffer)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.pstRingBuffer = pRingBuffer;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrlogCtrlFlag
 功能描述  : 获取ERRLOG打开和关闭的标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERRLOG打开和关闭的标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrlogCtrlFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.ucErrLogCtrlFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrlogCtrlFlag
 功能描述  : 设置ERRLOG打开和关闭的标识
 输入参数  : ucFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogCtrlFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.ucErrLogCtrlFlag = ucFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrlogAlmLevel
 功能描述  : 获取ERRLOG打开和关闭的标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERRLOG打开和关闭的标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 TAF_SDC_GetErrlogAlmLevel(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.usAlmLevel;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrlogAlmLevel
 功能描述  : 设置ERRLOG打开和关闭的标识
 输入参数  : usAlmLevel
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogAlmLevel(VOS_UINT16 usAlmLevel)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.usAlmLevel = usAlmLevel;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrlogOverflowCnt
 功能描述  : 获取Ringbuf溢出的次数
 输入参数  : VOS_UINT32
 输出参数  : 无
 返 回 值  : Ringbuf溢出的次数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月19日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetErrlogOverflowCnt(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.ulOverflowCnt;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrlogOverflowCnt
 功能描述  : 设置Ringbuf溢出的次数
 输入参数  : Ringbuf溢出的次数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月19日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogOverflowCnt(VOS_UINT32 ulOverflowCnt)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.ulOverflowCnt = ulOverflowCnt;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrLogCsOosReportToAppFlag
 功能描述  : 获取CS域是否上报过无服务标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否上报过无服务标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月16日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrLogCsOosReportToAppFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucCsOosReportToAppFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrLogCsOosReportToAppFlag
 功能描述  : 设置CS域是否上报过无服务标记
 输入参数  : ucFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月16日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucCsOosReportToAppFlag = ucFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrLogPsOosReportToAppFlag
 功能描述  : 获取PS域是否上报过无服务标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否上报过无服务标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月16日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrLogPsOosReportToAppFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucPsOosReportToAppFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrLogPsOosReportToAppFlag
 功能描述  : 设置PS域是否上报过无服务标记
 输入参数  : ucFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月16日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucPsOosReportToAppFlag = ucFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrLogReportPowerOnBeginFlag
 功能描述  : 获取是否上报过开机CHR
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否上报过开机CHR
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月30日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrLogReportPowerOnBeginFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOnBeginFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrLogReportPowerOnBeginFlag
 功能描述  : 设置是否上报过开机CHR
 输入参数  : ucFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月30日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOnBeginFlag = ucFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrLogReportPowerOffBeginFlag
 功能描述  : 获取是否上报过关机CHR
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否上报过关机CHR
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月30日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrLogReportPowerOffBeginFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOffBeginFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrLogReportPowerOffBeginFlag
 功能描述  : 设置是否上报过关机CHR
 输入参数  : ucFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月30日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOffBeginFlag = ucFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrlogActiveRptFlag
 功能描述  : 获取NV配置的主动上报开关
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrlogActiveRptFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpActiveRptFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrlogActiveRptFlag
 功能描述  : 获取NV配置的主动上报开关
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogActiveRptFlag(VOS_UINT8 ucActiveRptFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpActiveRptFlag = (ucActiveRptFlag & 0x01);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrlogRatSwitchRptFlag
 功能描述  : 获取NV配置的主动上报开关
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrlogRatSwitchRptFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpRatSwitchRptFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrlogRatSwitchRptFlag
 功能描述  : 获取NV配置的主动上报开关
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogRatSwitchRptFlag(VOS_UINT8 ucRatSwitchRptFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpRatSwitchRptFlag = (ucRatSwitchRptFlag & 0x01);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrlogRatSwitchStatisticTime
 功能描述  : 获取NV配置的RAT切换的统计时间
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetErrlogRatSwitchStatisticTime(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvStatisticTime;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrlogRatSwitchStatisticTime
 功能描述  : 设置NV配置的RAT切换的统计时间
 输入参数  : VOS_INT32                  ulStatisticTime
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogRatSwitchStatisticTime(
    VOS_UINT32                           ulStatisticTime
)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvStatisticTime = ulStatisticTime;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrlogRatSwitchStatisticNum
 功能描述  : 获取NV配置的RAT切换的统计次数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetErrlogRatSwitchStatisticNum(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvSwitchNum;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrlogRatSwitchStatisticNum
 功能描述  : 设置NV配置的RAT切换的次数
 输入参数  : VOS_INT32                  ulSwitchNum
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogRatSwitchStatisticNum(
    VOS_UINT32                           ulSwitchNum
)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvSwitchNum = ulSwitchNum;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrLogOldRatType
 功能描述  : 获取最后一次模式切换类型
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 获取最后一次模式切换类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrLogOldRatType(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ucOldRatType;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetErrLogOldRatType
 功能描述  : 设置最后一次模式切换类型
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogOldRatType(VOS_UINT8 ucRatType)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ucOldRatType = ucRatType;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetRatSwitchRingBufAddr
 功能描述  : 获取频繁切换RING BUFFER的地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 频繁切换RING BUFFER的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
OM_RING_ID TAF_SDC_GetRatSwitchRingBufAddr(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.pstRingBuffer;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetRatSwitchRingBufAddr
 功能描述  : 设置频繁切换RING BUFFER的地址
 输入参数  : RING BUFFER的地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetRatSwitchRingBufAddr(OM_RING_ID pRingBuffer)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.pstRingBuffer = pRingBuffer;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim
 功能描述  : 将gutl频繁切换CHR上报NV项配置保存到全局变量中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月27日
    作    者   : n00269697
    修改内容   : CHR优化新增函数
*****************************************************************************/
VOS_VOID TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim(VOS_VOID)
{
    VOS_UINT32                                           ulResult;
    VOS_UINT32                                           ulLength;
    TAF_NV_RAT_FREQUENTLY_SWITCH_CHR_RPT_CFG_STRU        stRatFrequentlySwitchChrRptCfg;

    ulLength = 0;
    PS_MEM_SET(&stRatFrequentlySwitchChrRptCfg,
               0x00, sizeof(TAF_NV_RAT_FREQUENTLY_SWITCH_CHR_RPT_CFG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Rat_Frequently_Switch_Chr_Rpt_Cfg, &ulLength);

    ulResult = NV_Read(en_NV_Item_Rat_Frequently_Switch_Chr_Rpt_Cfg,
                       &stRatFrequentlySwitchChrRptCfg,
                       ulLength);

    if (NV_OK != ulResult)
    {
        TAF_SDC_SetErrlogRatSwitchStatisticTime(0);
        TAF_SDC_SetErrlogRatSwitchStatisticNum(0);
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim: read en_NV_Item_Rat_Frequently_Switch_Chr_Rpt_Cfg failed");

        return;
    }


    /* 从NV读取的频繁切换限定时间大于规定的最大值 */
    if (stRatFrequentlySwitchChrRptCfg.ulStatisticTime > NAS_ERR_LOG_MAX_RAT_SWITCH_STATISTIC_TIME)
    {
        stRatFrequentlySwitchChrRptCfg.ulStatisticTime = NAS_ERR_LOG_MAX_RAT_SWITCH_STATISTIC_TIME;
    }

    TAF_SDC_SetErrlogRatSwitchStatisticTime(stRatFrequentlySwitchChrRptCfg.ulStatisticTime);

    /* 从NV读取的频繁切换限定次数大于规定的最大值 */
    if (stRatFrequentlySwitchChrRptCfg.ulSwitchNum > NAS_ERR_LOG_MAX_RAT_SWITCH_RECORD_MUN)
    {
        stRatFrequentlySwitchChrRptCfg.ulSwitchNum = NAS_ERR_LOG_MAX_RAT_SWITCH_RECORD_MUN;
    }

    TAF_SDC_SetErrlogRatSwitchStatisticNum(stRatFrequentlySwitchChrRptCfg.ulSwitchNum);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_ReadErrlogCtrlInfoNvim
 功能描述  : 根据NV:en_NV_Item_ErrLogCtrlInfo初始化ErrlogInfo
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
  1.日    期   : 2015年4月14日
    作    者   : n00269697
    修改内容   : CHR 优化项目
*****************************************************************************/
VOS_VOID TAF_SDC_ReadErrlogCtrlInfoNvim(VOS_VOID)
{
    VOS_UINT8                           ucActiveRptFlag;
    VOS_UINT8                           ucRatSwitchRptFlag;
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
        TAF_SDC_SetErrlogCtrlFlag(stErrorLogCtrlInfo.ucAlmStatus);
        TAF_SDC_SetErrlogAlmLevel(stErrorLogCtrlInfo.ucAlmLevel);

        ucActiveRptFlag    = (stErrorLogCtrlInfo.aucReportBitMap[0] >> NAS_ERR_LOG_ACTIVE_RPT_FLAG_OFFSET) & 0x01;
        ucRatSwitchRptFlag = (stErrorLogCtrlInfo.aucReportBitMap[1] >> NAS_ERR_LOG_RAT_SWITCH_RPT_FLAG_OFFSET) & 0x01;

        TAF_SDC_SetErrlogActiveRptFlag(ucActiveRptFlag);
        TAF_SDC_SetErrlogRatSwitchRptFlag(ucRatSwitchRptFlag);
    }
    else
    {
        TAF_SDC_SetErrlogCtrlFlag(VOS_FALSE);
        TAF_SDC_SetErrlogAlmLevel(NAS_ERR_LOG_CTRL_LEVEL_CRITICAL);

        TAF_SDC_SetErrlogActiveRptFlag(VOS_FALSE);
        TAF_SDC_SetErrlogRatSwitchRptFlag(VOS_FALSE);

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadErrlogCtrlInfoNvim:read en_NV_Item_ErrLogCtrlInfo failed");
    }

    /* 测试卡，则不开启该功能 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        TAF_SDC_SetErrlogCtrlFlag(VOS_FALSE);
        TAF_SDC_SetErrlogActiveRptFlag(VOS_FALSE);
        TAF_SDC_SetErrlogRatSwitchRptFlag(VOS_FALSE);
    }

    return;
}

/*lint -e593 -e830*/

/*****************************************************************************
 函 数 名  : TAF_SDC_InitErrLogInfo
 功能描述  : 创建RING BUFFER
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_VOID TAF_SDC_InitErrLogInfo(
    TAF_SDC_ERRLOG_INFO_STRU           *pstErrLogInfo
)
{
#if (FEATURE_ON == FEATURE_PTM)
    VOS_CHAR                           *pbuffer;
    OM_RING_ID                          pRingbuffer;
#endif

    TAF_SDC_ReadErrlogCtrlInfoNvim();

    TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim();

#if (FEATURE_ON == FEATURE_PTM)
    TAF_SDC_CreatRatSwitchRingBuf();
#endif

    TAF_SDC_SetErrLogOldRatType(TAF_PH_INFO_NONE_RAT);

    PS_MEM_SET(&pstErrLogInfo->stOosInfo,
               0x0,
               sizeof(TAF_SDC_ERRLOG_OOS_INFO_STRU));

    TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_FALSE);
    TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_FALSE);

#if (FEATURE_ON == FEATURE_PTM)
    /* 申请cache的动态内存 , 长度加1是因为读和写指针之间在写满时会相差一个字节 */
    pbuffer = (char *)PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SDC_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pbuffer)
    {
        pstErrLogInfo->stBuffInfo.pstRingBuffer = VOS_NULL_PTR;
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitErrLogInfo: alloc fail");
        return;
    }

    /* 调用OM的接口，将申请的动态内存创建为RING BUFFER */
    pRingbuffer = OM_RingBufferCreateEx(pbuffer, TAF_SDC_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pRingbuffer)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pbuffer);
    }

    /* 保存ringbuffer指针 */
    pstErrLogInfo->stBuffInfo.pstRingBuffer = pRingbuffer;

    pstErrLogInfo->stBuffInfo.ulOverflowCnt = 0;
#endif

    return;

}
/*lint +e593 +e830*/

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : TAF_SDC_PutRatSwitchRingBuf
 功能描述  : RING BUFFER写操作
 输入参数  : pbuffer:需要写入的内容
             lbytes :写入内容的长度
 输出参数  : 无
 返 回 值  : 实际写入的大小，如果BUFFER空间不够则返回0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_PutRatSwitchRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    OM_RING_ID                          pTafRingBuffer;
    VOS_UINT32                          ulRatRingbufferLength;
    VOS_UINT32                          ulNvSwitchNum;
    VOS_UINT32                          ulLength;

    pTafRingBuffer = TAF_SDC_GetRatSwitchRingBufAddr();
    if (VOS_NULL_PTR == pTafRingBuffer)
    {
        return 0;
    }

    ulNvSwitchNum         = TAF_SDC_GetErrlogRatSwitchStatisticNum();
    ulRatRingbufferLength = ulNvSwitchNum * sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU);

    /* 如果写入比RING BUFFER还大则不写入 */
    if ((ulbytes > ulRatRingbufferLength)
     || (ulbytes != sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU)))
    {
        return 0;
    }

    /* 获取RING BUFFER剩余空间大小 */
    ulFreeSize = TAF_SDC_GetRatSwitchRingBufferFreeBytes();

    /* 如果队列已经满了，则队列头部记录出列 */
    if (0 == ulFreeSize)
    {
        ulLength = TAF_SDC_RatSwitchRingBufRemoveRecord(sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU));

        if (ulLength != sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU))
        {
            return 0;
        }
    }

    /* 写入RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pTafRingBuffer, pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_RatSwitchRingBufRemoveRecord
 功能描述  : RING BUFFER删除操作
 输入参数  : ulbytes: 删除的字节数
 输出参数  : 无
 返 回 值  : 实际删除的字节数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_RatSwitchRingBufRemoveRecord(
    VOS_UINT32                          ulbytes
)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferRemove(TAF_SDC_GetRatSwitchRingBufAddr(), (VOS_INT)ulbytes);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetRecordFromRatSwitchRingBuf
 功能描述  : RING BUFFER读操作操作
 输入参数  : pbuffer: 读出来存放的空间
             ulbytes: 读取的最大值
 输出参数  : 无
 返 回 值  : 实际读取的大小，如果RINGBUFFER为空，则返回0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetRecordFromRatSwitchRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferGetReserve(TAF_SDC_GetRatSwitchRingBufAddr(), pbuffer, (VOS_INT)ulbytes);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetRatSwitchRingBufferFreeBytes
 功能描述  : RING BUFFER中有未使用空间
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 实际RING BUFFER中未使用空间大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetRatSwitchRingBufferFreeBytes(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferFreeBytes(TAF_SDC_GetRatSwitchRingBufAddr());
}

/*****************************************************************************
 函 数 名  : TAF_SDC_CleanRatSwitchRingBuf
 功能描述  : 清空RINGBUFFER中的数据
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_CleanRatSwitchRingBuf(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return;
    }

    OM_RingBufferFlush(TAF_SDC_GetRatSwitchRingBufAddr());

    return;
}

/*lint -e830 -e593*/
/*****************************************************************************
 函 数 名  : TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim
 功能描述  : 将gutl频繁切换CHR上报NV项配置保存到全局变量中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月27日
    作    者   : n00269697
    修改内容   : CHR优化新增函数
*****************************************************************************/
VOS_VOID TAF_SDC_CreatRatSwitchRingBuf(VOS_VOID)
{
    VOS_CHAR                           *pbuffer;
    OM_RING_ID                          pRatRingbuffer;
    VOS_UINT32                          ulNvSwitchNum;                          /* NV配置的gutl切换的统计次数 */
    VOS_INT32                           lRatRingbufferLength;

    ulNvSwitchNum = TAF_SDC_GetErrlogRatSwitchStatisticNum();

    if (0 == ulNvSwitchNum)
    {
        TAF_SDC_SetRatSwitchRingBufAddr(VOS_NULL_PTR);

        return;
    }

    lRatRingbufferLength = (VOS_INT32)ulNvSwitchNum * (VOS_INT32)sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU) + 1;

    pbuffer = (char *)PS_MEM_ALLOC(WUEPS_PID_TAF, (VOS_UINT32)lRatRingbufferLength);
    if (VOS_NULL_PTR == pbuffer)
    {
        TAF_SDC_SetRatSwitchRingBufAddr(VOS_NULL_PTR);
        return;
    }

    PS_MEM_SET(pbuffer, 0, (VOS_UINT32)lRatRingbufferLength);

    /* 调用OM的接口，将申请的动态内存创建为RING BUFFER */
    pRatRingbuffer = OM_RingBufferCreateEx(pbuffer, lRatRingbufferLength);
    if (VOS_NULL_PTR == pRatRingbuffer)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pbuffer);
    }

    TAF_SDC_SetRatSwitchRingBufAddr(pRatRingbuffer);

    return;
}
/*lint +e830 +e593*/

/*****************************************************************************
 函 数 名  : TAF_SDC_PutErrLogRingBuf
 功能描述  : RING BUFFER写操作
 输入参数  : pbuffer:需要写入的内容
             lbytes :写入内容的长度
 输出参数  : 无
 返 回 值  : 实际写入的大小，如果BUFFER空间不够则返回0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    VOS_UINT32                          ulCount;
    OM_RING_ID                          pTafRingBuffer;

    pTafRingBuffer = TAF_SDC_GetErrLogRingBufAddr();
    if (VOS_NULL_PTR == pTafRingBuffer)
    {
        return 0;
    }

    /* 如果写入比RING BUFFER还大则不写入 */
    if (ulbytes > TAF_SDC_RING_BUFFER_SIZE)
    {
        return 0;
    }

    /* 获取RING BUFFER剩余空间大小 */
    ulFreeSize = (VOS_UINT32)OM_RingBufferFreeBytes(pTafRingBuffer);

    ulCount = TAF_SDC_GetErrlogOverflowCnt();
    /* 如果剩余空间不足写入的大小，则清空RING BUFFER */
    if (ulFreeSize < ulbytes)
    {
        ulCount++;
        TAF_SDC_SetErrlogOverflowCnt(ulCount);

        OM_RingBufferFlush(pTafRingBuffer);
    }

    /* 写入RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pTafRingBuffer, pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrLogRingBufContent
 功能描述  : RING BUFFER读操作操作
 输入参数  : pbuffer: 读出来存放的空间
             ulbytes: 读取的最大值
 输出参数  : 无
 返 回 值  : 实际读取的大小，如果RINGBUFFER为空，则返回0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferGet(TAF_SDC_GetErrLogRingBufAddr(), pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetErrLogRingBufferUseBytes
 功能描述  : RING BUFFER中有多少数据
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 实际RING BUFFER中数据大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetErrLogRingBufferUseBytes(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferNBytes(TAF_SDC_GetErrLogRingBufAddr());
}

/*****************************************************************************
 函 数 名  : TAF_SDC_CleanErrLogRingBuf
 功能描述  : 清空RINGBUFFER中的数据
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_VOID TAF_SDC_CleanErrLogRingBuf(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetErrLogRingBufAddr())
    {
        return;
    }

    OM_RingBufferFlush(TAF_SDC_GetErrLogRingBufAddr());

    return;
}

#endif

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_SetVoiceCallOnImsSupportFlag
 功能描述  : 设置是否支持IMS语音呼叫标志
 输入参数  : ucVoiceCallOnImsSupportFlag - IMS语音呼叫是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetVoiceCallOnImsSupportFlag(
    VOS_UINT8                          ucVoiceCallOnImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag = ucVoiceCallOnImsSupportFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetVoiceCallOnImsSupportFlag
 功能描述  : 获取是否支持IMS语音呼叫标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持IMS语音呼叫
             VOS_FALSE:不支持IMS语音呼叫
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetVoiceCallOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetSmsOnImsSupportFlag
 功能描述  : 设置是否支持IMS短信标志
 输入参数  : SmsOnImsSupportFlag - IMS短信是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetSmsOnImsSupportFlag(
    VOS_UINT8                          ucSmsOnImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag = ucSmsOnImsSupportFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetSmsOnImsSupportFlag
 功能描述  : 获取是否支持IMS短信标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持IMS短信
             VOS_FALSE:不支持IMS短信
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetSmsOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetVideoCallOnImsSupportFlag
 功能描述  : 设置是否支持IMS域VIDEO CALL标志
 输入参数  : VideoCallOnImsSupportFlag - IMS域VIDEO CALL是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetVideoCallOnImsSupportFlag(
    VOS_UINT8                          ucVideoCallOnImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag = ucVideoCallOnImsSupportFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetVideoCallOnImsSupportFlag
 功能描述  : 获取是否支持IMS域VIDEO CALL标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持IMS域VIDEO CALL
             VOS_FALSE:不支持IMS域VIDEO CALL
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetVideoCallOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetVoiceDomain
 功能描述  : 设置语音呼叫优选域
 输入参数  : enVoiceDomain - 语音呼叫优选域
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetVoiceDomain(
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enVoiceDomain = enVoiceDomain;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetVoiceDomain
 功能描述  : 获取语音呼叫优选域
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_VOICE_DOMAIN_ENUM_UINT32:语音呼叫优选域
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_VOICE_DOMAIN_ENUM_UINT32 TAF_SDC_GetVoiceDomain(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enVoiceDomain;
}



/*****************************************************************************
 函 数 名  : TAF_SDC_SetSmsDomain
 功能描述  : 设置短信优选域
 输入参数  : enSmsDomain - 短信优选域优选域
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetSmsDomain(
    TAF_SDC_SMS_DOMAIN_ENUM_UINT8      enSmsDomain
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enSmsDomain = enSmsDomain;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetSmsDomain
 功能描述  : 获取短信优选域
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_SMS_DOMAIN_ENUM_UINT32:短信优选域
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SMS_DOMAIN_ENUM_UINT8 TAF_SDC_GetSmsDomain(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enSmsDomain;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetLteEmsSupportFlag
 功能描述  : 设置LTE EMS支持flag
 输入参数  : LTE EMS支持flag:VOS_TRUE -- LTE EMS支持 VOS_FALSE -- LTE EMS不支持
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月24日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetLteEmsSupportFlag(
    VOS_UINT8                           ucLteEmsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag = ucLteEmsSupportFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetLteEmsSupportFlag
 功能描述  : 获取LTE EMS支持flag
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- LTE EMS支持
             VOS_FALSE -- LTE EMS不支持

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年9月24日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetLteEmsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetLteCsServiceCap
 功能描述  : 设置UE支持LTE CS业务能力
 输入参数  : enLteCsServiceCap - UE支持LTE CS业务能力
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年10月08日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetLteCsSeviceCap(
    TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8   enLteCsServiceCap
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enLteCsServiceCfg = enLteCsServiceCap;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetLteCsSeviceCap
 功能描述  : 获取UE支持LTE CS业务能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
             TAF_SDC_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS -- 支持cs fallback和sms over sgs
             TAF_SDC_LTE_SUPPORT_SMS_OVER_SGS_ONLY     -- 支持sms over sgs only
             TAF_SDC_LTE_SUPPORT_1XCSFB                -- 支持1XCSFB
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年10月08日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8 TAF_SDC_GetLteCsSeviceCap(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enLteCsServiceCfg);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetUeUsageSetting
 功能描述  : 获取UE使用设定
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回UE的使用设定
             VOICE_CENTRIC －－ 语音中心
             DATA_CENTRIC  －－ 数据中心
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年10月08日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8 TAF_SDC_GetUeUsageSetting(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.enUeUsageSetting);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetUeUsageSetting
 功能描述  : 设置UE使用设定
 输入参数  : enUeUsageSetting - UE使用设定
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年10月08日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetUeUsageSetting(
    TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8   enUeUsageSetting
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.enUeUsageSetting = enUeUsageSetting;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCampSysMode
 功能描述  : 获取当前驻留时的系统模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前驻留时的系统模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月17日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetCampSysMode( VOS_VOID )
{
    if (VOS_TRUE == TAF_SDC_GetCampOnFlag())
    {
        return TAF_SDC_GetSysMode();
    }

    return TAF_SDC_SYS_MODE_BUTT;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetMsPrioRatList
 功能描述  : 获取SDC中保存当前MS支持的接入模式和接入优先级
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SDC中保存当前MS支持的接入模式和接入优先级
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月20日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_RAT_PRIO_STRU* TAF_SDC_GetMsPrioRatList( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetMsPrioRatList
 功能描述  : 设置SDC中保存SYSCFG的接入优先级列表信息
 输入参数  : pstPrioRatList -SYSCFG的接入优先级列表信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月20日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID TAF_SDC_SetMsPrioRatList(
    TAF_SDC_RAT_PRIO_STRU              *pstPrioRatList
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList = *pstPrioRatList;
}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

/* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetCallRedailFromImsToCsSupportFlag
 功能描述  : 获取呼叫从IMS域到CS域的换域重拨Flag
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE --  重拨支持
             VOS_FALSE -- 重拨不支持

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCallRedailFromImsToCsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial                    \
        .stRedialImsToCs.ucCallRedial;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCallRedailFromImsToCsSupportFlag
 功能描述  : 设置呼叫从IMS域到CS域的换域重拨Flag
 输入参数  : ucCallRedialFromImsToCs -- 支持IMS到CS换域重拨标志
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCallRedailFromImsToCsSupportFlag(VOS_UINT8 ucCallRedialFromImsToCs)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs           \
        .ucCallRedial = ucCallRedialFromImsToCs;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetSmsRedailFromImsToCsSupportFlag
 功能描述  : 获取短信从IMS域到CS域的换域重拨Flag
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE --  重拨支持
             VOS_FALSE -- 重拨不支持

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetSmsRedailFromImsToCsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs    \
        .ucSmsRedial;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetSmsRedailFromImsToCsSupportFlag
 功能描述  : 设置短信从IMS域到CS域的换域重拨Flag
 输入参数  : ucCallRedialFromImsToCs -- 支持IMS到CS换域重拨标志
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetSmsRedailFromImsToCsSupportFlag(VOS_UINT8 ucSmsRedialFromImsToCs)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs           \
        .ucSmsRedial = ucSmsRedialFromImsToCs;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetRoamingSupportFlag
 功能描述  : 获取漫游场景下IMS业务支持标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE --  漫游支持
             VOS_FALSE -- 漫游不支持

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetRoamingSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.ucRoamingSupport;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetRoamingSupportFlag
 功能描述  : 设置漫游支持标记
 输入参数  : ucRoamingSupport －－ 漫游支持标志
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetRoamingSupportFlag(VOS_UINT8 ucRoamingSupport)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.ucRoamingSupport = ucRoamingSupport;
}
/* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, end */

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_SetImsNormalRegStatus
 功能描述  : 设置当前IMS的正常注册状态
 输入参数  : enRegStatus - IMS的注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月14日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目新增

*****************************************************************************/
VOS_VOID    TAF_SDC_SetImsNormalRegStatus(
    TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8    enRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stImsDomainInfo.enImsNormalRegSta = enRegStatus;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetImsNormalRegStatus
 功能描述  : 获取当前IMS的正常注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前IMS的正常注册状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年09月23日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目新增

*****************************************************************************/
TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8   TAF_SDC_GetImsNormalRegStatus(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stImsDomainInfo.enImsNormalRegSta;
}



/*****************************************************************************
 函 数 名  : TAF_SDC_SetCurPhoneMode
 功能描述  : 设置当前的手机模式
 输入参数  : enPhoneMode-当前的手机模式
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SDC_SetCurPhoneMode(
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhoneMode
)
{
    (TAF_SDC_GetSdcCtx()->stPhoneInfo.enPhMode) = enPhoneMode;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurPhoneMode
 功能描述  : 获取当前的手机模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_PHONE_MODE_ENUM_UINT8  TAF_SDC_GetCurPhoneMode(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stPhoneInfo.enPhMode);
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCurImsSwitchState
 功能描述  : 设置当前的IMS协议栈开关机状态
 输入参数  : enState - 当前的IMS协议栈开关机状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : IMS动态开关配置项目
*****************************************************************************/
VOS_VOID  TAF_SDC_SetCurImsSwitchState(
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8       enState
)
{
    (TAF_SDC_GetSdcCtx()->stPhoneInfo.enImsSwitchState) = enState;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurImsSwitchState
 功能描述  : 获取IMS协议栈开关机状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : IMS动态开关配置项目
*****************************************************************************/
TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8  TAF_SDC_GetCurImsSwitchState(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stPhoneInfo.enImsSwitchState);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCregType
 功能描述  : 获取当前设置的Creg类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_CREG_TYPE_ENUM_UINT8  TAF_SDC_GetCregType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stRegReportStatus.enCregType);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCregType
 功能描述  : 设置当前设置的Creg类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SDC_SetCregType(TAF_SDC_CREG_TYPE_ENUM_UINT8 enCregType)
{
    TAF_SDC_GetSdcCtx()->stRegReportStatus.enCregType = enCregType;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCgregType
 功能描述  : 获取当前设置的Cgreg类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_CGREG_TYPE_ENUM_UINT8  TAF_SDC_GetCgregType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stRegReportStatus.enCgregType);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCregType
 功能描述  : 设置当前设置的Creg类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SDC_SetCgregType(TAF_SDC_CGREG_TYPE_ENUM_UINT8 enCgregType)
{
    TAF_SDC_GetSdcCtx()->stRegReportStatus.enCgregType = enCgregType;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCeregType
 功能描述  : 获取当前设置的Cgreg类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_CEREG_TYPE_ENUM_UINT8  TAF_SDC_GetCeregType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stRegReportStatus.enCeregType);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCregType
 功能描述  : 设置当前设置的Creg类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SDC_SetCeregType(TAF_SDC_CEREG_TYPE_ENUM_UINT8 enCeregType)
{
    TAF_SDC_GetSdcCtx()->stRegReportStatus.enCeregType = enCeregType;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetUssdOnImsSupportFlag
 功能描述  : 获取是否支持IMS USSD标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持IMS USSD
             VOS_FALSE:不支持IMS USSD
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年04月01日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetUssdOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetUssdOnImsSupportFlag
 功能描述  : 设置IMS USSD标志
 输入参数  : ucUssdOnImsSupportFlag － IMS USSD标志是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年04月01日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetUssdOnImsSupportFlag(VOS_UINT8 ucUssdOnImsSupportFlag)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag = ucUssdOnImsSupportFlag;
}

#if (FEATURE_ON == FEATURE_ECALL)
/* Added by s00261364 for V3R360_eCall项目, 2014-4-3, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetEcallTestNumber
 功能描述  : 获取TestNumber
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_ECALL_NUM_STRU---当前USIM卡文件中的test号码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月18日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_ECALL_NUM_STRU*                 TAF_SDC_GetEcallTestNumber(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stEcallTestNumber));
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetEcallRecfgNumber
 功能描述  : 获取RecfgNumber
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_ECALL_NUM_STRU---当前USIM卡文件中的recfg号码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月18日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_ECALL_NUM_STRU*                 TAF_SDC_GetEcallRecfgNumber(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stEcallRecfgNumber));
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCurCallMode
 功能描述  : 获取当前的呼叫模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_CALL_MODE_ENUM_UINT8---当前呼叫模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月3日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_CALL_MODE_ENUM_UINT8            TAF_SDC_GetCurCallMode(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enCallMode);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCurCallMode
 功能描述  : 设置当前的呼叫模式
 输入参数  : enCallMode---当前呼叫模式
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月3日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SDC_SetCurCallMode(
    TAF_SDC_CALL_MODE_ENUM_UINT8        enCallMode
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enCallMode = enCallMode;
    return;
}

/* Added by s00261364 for V3R360_eCall项目, 2014-4-3, end */
#endif

/* Added by s00261364 for L-C互操作项目, 2014-2-11, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_SetLCEnableFlg
 功能描述  : 设置L-C模式使能标志
 输入参数  : ucLCEnableFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月10日
   作    者   : s00261364
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetLCEnableFlg(
    VOS_UINT8                           ucLCEnableFlg
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.ucLCEnableFlg = ucLCEnableFlg;
}
/* Added by s00261364 for L-C互操作项目, 2014-2-11, end */


/* Added by s00261364 for L-C互操作项目, 2014-1-27, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetLCEnableFlg
 功能描述  : 获取L-C模式使能标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : L-C模式使能标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年01月23日
   作    者   : s00261364
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetLCEnableFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.ucLCEnableFlg;
}
/* Added by s00261364 for L-C互操作项目, 2014-1-27, end */


/* Added by s00261364 for L-C互操作项目, 2014-2-11, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_SetLCWorkCfg
 功能描述  : 设置L-C模式标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月10日
   作    者   : s00261364
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_SetLCWorkCfg(
    TAF_NVIM_LC_WORK_CFG_ENUM_UINT8     enLCWorkCfg
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.enLCWorkCfg = enLCWorkCfg;
}
/* Added by s00261364 for L-C互操作项目, 2014-2-11, end */


/* Added by s00261364 for L-C互操作项目, 2014-1-27, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetLCWorkCfg
 功能描述  : 获取L-C模式标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : L-C模式标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年01月23日
   作    者   : s00261364
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetLCWorkCfg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.enLCWorkCfg;
}
/* Added by s00261364 for L-C互操作项目, 2014-1-27, end */

/* Added by m00217266 for L-C互操作项目, 2014-2-12, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetLCWorkCfg
 功能描述  : 获取L-C下接入技术组合模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : L-C下接入技术组合模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月12日
   作    者   : m00217266
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetLCRatCombined(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.enRatCombined;
}
/* Added by m00217266 for L-C互操作项目, 2014-2-12, end */

/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_GetLcConfigPara
 功能描述  : 获取L-C下接入技术组合模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : L-C下接入技术组合模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月12日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
TAF_SDC_LC_CONFIG_PARA_STRU* TAF_SDC_GetLcConfigPara(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara);
}
/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */

/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
/*****************************************************************************
 函 数 名  : TAF_SDC_SetPsServiceConnStatusFlag
 功能描述  : 设置ps业务信令连接标识是否存在
 输入参数  : ucPsServiceConnStatusFlag - ps业务信令连接标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : s00217060
   修改内容   : K3V3 多模多天线特性

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsServiceConnStatusFlag(
    VOS_UINT8                           ucPsServiceConnStatusFlag
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stPsInfo.ucPsServiceConnStatusFlag = ucPsServiceConnStatusFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetPsServiceConnStatusFlag
 功能描述  : 获取ps业务信令连接是否存在标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ps业务信令连接标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : s00217060
   修改内容   : K3V3 多模多天线特性

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetPsServiceConnStatusFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stPsInfo.ucPsServiceConnStatusFlag;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_SDC_SetEpsServiceConnStatusFlag
 功能描述  : 设置eps业务信令连接标识是否存在
 输入参数  : ucEpsServiceConnStatusFlag - ps业务信令连接标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : s00217060
   修改内容   : K3V3 多模多天线特性

*****************************************************************************/
VOS_VOID TAF_SDC_SetEpsServiceConnStatusFlag(
    VOS_UINT8                           ucEpsServiceConnStatusFlag
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stEpsInfo.ucEpsServiceConnStatusFlag = ucEpsServiceConnStatusFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetEpsServiceConnStatusFlag
 功能描述  : 获取eps业务信令连接是否存在标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : eps业务信令连接标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : s00217060
   修改内容   : K3V3 多模多天线特性

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetEpsServiceConnStatusFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stEpsInfo.ucEpsServiceConnStatusFlag;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_SDC_InitAppSysMode
 功能描述  : 初始化APP的系统模式和系统子模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月21日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitAppSysMode(VOS_VOID)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysMode      = TAF_SDC_SYS_MODE_BUTT;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitAppSysSubMode
 功能描述  : 初始化APP的系统子模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月21日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_InitAppSysSubMode(VOS_VOID)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysSubMode   = TAF_SDC_SYS_SUBMODE_BUTT;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_InitAppNetworkPlmnInfo
 功能描述  : 初始化服务的plmn信息
 输入参数  : pstCampPlmnInfo - 服务的plmn信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : 新生成函数    Service_State_Optimize_PhaseI项目修改

*****************************************************************************/
VOS_VOID TAF_SDC_InitAppNetworkPlmnInfo(TAF_SDC_SERVICED_PLMN_INFO_STRU  *pstServPlmnInfo)
{
    pstServPlmnInfo->stServicePlmnId.ulMcc = TAF_SDC_INVALID_MCC;
    pstServPlmnInfo->stServicePlmnId.ulMnc = TAF_SDC_INVALID_MNC;
    pstServPlmnInfo->ucServiceUtranMode    = NAS_UTRANCTRL_UTRAN_MODE_BUTT;
    pstServPlmnInfo->ucServiceRac          = TAF_SDC_RAC_INVALID;
    pstServPlmnInfo->usServiceLac          = TAF_SDC_LAC_INVALID;
    pstServPlmnInfo->ulServiceCellId       = TAF_SDC_CELLID_INVALID;
    pstServPlmnInfo->ucServiceRoamFlg      = TAF_PH_INFO_ROAM_UNKNOW;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetEnhancedOperatorNameInfo
 功能描述  : 获取EONS相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU *TAF_SDC_GetEnhancedOperatorNameInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetUsimOplFileInfo
 功能描述  : 获取USIM的OPL文件信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_OPL_FILE_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_OPL_FILE_INFO_STRU* TAF_SDC_GetUsimOplFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimOplFileInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetOperNamePrio
 功能描述  : 获取运营商名称显示优先级
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_OPER_NAME_TYPE_PRIO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_OPER_NAME_TYPE_PRIO_STRU* TAF_SDC_GetOperNamePrio(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stOperNameTypePrio);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCopsFormatType
 功能描述  : 获取cops设置的运营商名称显示格式长名、短名还是数字格式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8 TAF_SDC_GetCopsFormatType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.enCopsFormatType);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitEonsRelatedSimFileInfo
 功能描述  : 初始化EONS卡文件相关信息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月29日
   作    者   : z00359541
   修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_SDC_InitEonsRelatedSimFileInfo(VOS_VOID)
{
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU               *pstEnhancedOperatorNameInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;

    pstEnhancedOperatorNameInfo = &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo);

    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimOplFileInfo), 0, sizeof(TAF_SDC_OPL_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimOplFileInfo), 0, sizeof(TAF_SDC_OPL_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimPnnFileInfo), 0, sizeof(TAF_SDC_PNN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimPnnFileInfo), 0, sizeof(TAF_SDC_PNN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stCphsFileInfo), 0, sizeof(TAF_SDC_CPHS_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimSpnFileInfo), 0, sizeof(TAF_SDC_SPN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimSpnFileInfo), 0, sizeof(TAF_SDC_SPN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimSpdiFileInfo), 0, sizeof(TAF_SDC_SPDI_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimSpdiFileInfo), 0, sizeof(TAF_SDC_SPDI_FILE_INFO_STRU));

    for (ulIndex = 0; ulIndex < TAF_SDC_MAX_SERVICE_PROVIDER_PLMN_NUM; ulIndex++)
    {
        pstEnhancedOperatorNameInfo->stUsimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMcc = TAF_SDC_INVALID_MCC;
        pstEnhancedOperatorNameInfo->stUsimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMnc = TAF_SDC_INVALID_MNC;
        pstEnhancedOperatorNameInfo->stSimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMcc = TAF_SDC_INVALID_MCC;
        pstEnhancedOperatorNameInfo->stSimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMnc = TAF_SDC_INVALID_MNC;
    }

}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitEnhancedOperatorNameInfo
 功能描述  : 初始化EONS信息
 输入参数  : pstEnhancedOperatorNameInfo - EONS信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月25日
   作    者   : z00161729
   修改内容   : AT&T 支持EONS特性修改
 2.日    期   : 2015年12月29日
   作    者   : z00359541
   修改内容   : DTS2015120305849:增加初始化原因值为入参
*****************************************************************************/
VOS_VOID TAF_SDC_InitEnhancedOperatorNameInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8                        enInitType,
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU               *pstEnhancedOperatorNameInfo
)
{
    VOS_UINT32                                              ulIndex;

    if (TAF_MMA_INIT_CTX_STARTUP == enInitType)
    {
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SDC_InitEnhancedOperatorNameInfo: Start up scena, init EONS related SIM file info");
        TAF_SDC_InitEonsRelatedSimFileInfo();
    }

    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stOperNameTypePrio), 0, sizeof(TAF_SDC_OPER_NAME_TYPE_PRIO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stMmInfo), 0, sizeof(TAF_SDC_MM_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stCustomOperNameInfo), 0, sizeof(TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stCustomOperNameInfo), 0, sizeof(TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU));
    pstEnhancedOperatorNameInfo->cWildCard = 0;

    pstEnhancedOperatorNameInfo->enCopsFormatType = TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH;

    for (ulIndex = 0; ulIndex < TAF_SDC_MAX_OPER_NAME_PRIO_NUM; ulIndex++)
    {
        pstEnhancedOperatorNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ulIndex] = TAF_SDC_OPER_NAME_TYPE_BUTT;
    }

    pstEnhancedOperatorNameInfo->stMmInfo.stOperatorPlmnId.ulMcc = TAF_SDC_INVALID_MCC;
    pstEnhancedOperatorNameInfo->stMmInfo.stOperatorPlmnId.ulMnc = TAF_SDC_INVALID_MNC;

    for (ulIndex = 0; ulIndex < TAF_NVIM_STORED_OPER_NAME_NUM; ulIndex++)
    {
        pstEnhancedOperatorNameInfo->stCustomOperNameInfo.astCustomOperName[ulIndex].stOperatorPlmnId.ulMcc = TAF_SDC_INVALID_MCC;
        pstEnhancedOperatorNameInfo->stCustomOperNameInfo.astCustomOperName[ulIndex].stOperatorPlmnId.ulMnc = TAF_SDC_INVALID_MNC;
    }

    TAF_SDC_ReadEnhancedOperNameServiceCfgNvim();
    TAF_SDC_ReadCustomOperNameInfoNvim();
    return;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetCopsFormatType
 功能描述  : 设置cops设置的运营商名称显示格式长名、短名还是数字格式
 输入参数  : enCopsFormatType - 运营商名称显示格式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCopsFormatType(
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8                     enCopsFormatType
)
{
    TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.enCopsFormatType = enCopsFormatType;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetSimOplFileInfo
 功能描述  : 获取SIM的OPL文件信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_OPL_FILE_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_OPL_FILE_INFO_STRU* TAF_SDC_GetSimOplFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimOplFileInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetUsimPnnFileInfo
 功能描述  : 获取usim PNN文件信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_PNN_FILE_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_PNN_FILE_INFO_STRU* TAF_SDC_GetUsimPnnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimPnnFileInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetSimPnnFileInfo
 功能描述  : 获取sim PNN文件信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_PNN_FILE_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_PNN_FILE_INFO_STRU* TAF_SDC_GetSimPnnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimPnnFileInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetUsimSpnFileInfo
 功能描述  : 获取usim SPN文件信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_SPN_FILE_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SPN_FILE_INFO_STRU* TAF_SDC_GetUsimSpnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimSpnFileInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetSimSpnFileInfo
 功能描述  : 获取sim SPN文件信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_SPN_FILE_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SPN_FILE_INFO_STRU* TAF_SDC_GetSimSpnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimSpnFileInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetChpsFileInfo
 功能描述  : 获取CHPS文件信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_CPHS_FILE_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_CPHS_FILE_INFO_STRU* TAF_SDC_GetChpsFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stCphsFileInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetUsimSpdiFileInfo
 功能描述  : 获取usim SPDI文件信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_SPDI_FILE_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetUsimSpdiFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimSpdiFileInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetSimSpdiFileInfo
 功能描述  : 获取sim SPDI文件信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_SPDI_FILE_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetSimSpdiFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimSpdiFileInfo);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetMmInfo
 功能描述  : 获取mm/gmm/emm information信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_MM_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_MM_INFO_STRU* TAF_SDC_GetMmInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stMmInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCustomOperNameInfo
 功能描述  : 获取50024 nv中运营商定制名称
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU* TAF_SDC_GetCustomOperNameInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stCustomOperNameInfo);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetPlmnExactlyCompareFlg
 功能描述  : 获取TAF 中保存的ucPlmnExactlyCompareFlg 信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : c00318887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetPlmnExactlyCompareFlg(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPlmnExactlyCompareInfo.ucPlmnExactlyCompareFlag);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetPlmnExactlyCompareFlg
 功能描述  : 更新TAF 中保存的精确比较标记ucPlmnExactlyCompareFlg
 输入参数  : ucPlmnExactlyComparaFlag :Mnc精确比较标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月26日
   作    者   : c00318887
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SDC_SetPlmnExactlyCompareFlg(VOS_UINT8  ucPlmnExactlyComparaFlag)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPlmnExactlyCompareInfo.ucPlmnExactlyCompareFlag = ucPlmnExactlyComparaFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetRefreshAllFileRestartFlag
 功能描述  : 获取refresh all file时是否需要重启modem标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetRefreshAllFileRestartFlag(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.ucRefreshAllFileRestartFlag);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetRefreshAllFileRestartFlag
 功能描述  : 设置refresh all file时是否需要重启modem标识
 输入参数  : ucRefreshAllFileRestartFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetRefreshAllFileRestartFlag(
    VOS_UINT8                           ucRefreshAllFileRestartFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.ucRefreshAllFileRestartFlag = ucRefreshAllFileRestartFlag;
    return;
}



/*****************************************************************************
 函 数 名  : TAF_SDC_SetPlmnCompareWildCard
 功能描述  : 设置plmn比较时的通配符
 输入参数  : cWildCard - 通配符
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SDC_SetPlmnCompareWildCard(
    VOS_CHAR                            cWildCard
)
{
    TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.cWildCard = cWildCard;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetPlmnCompareWildCard
 功能描述  : 获取plmn比较时的通配符
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_CHAR
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_CHAR  TAF_SDC_GetPlmnCompareWildCard(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.cWildCard;
}



/*****************************************************************************
 函 数 名  : TAF_SDC_InitAppNetworkRssiValue
 功能描述  : 初始化 TAF_SDC_APP_NETWORK_INFO  stAppNetworkInfo中Rssi值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改
  2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID  TAF_SDC_InitNetworkRssiValue(TAF_SDC_SIG_QUALITY_INFO_STRU *pstSigQuaInfo)
{
    /* 3PGG相关制式的信号强度  */
    pstSigQuaInfo->st3GppRssiInfo.sUeRfPower                            = TAF_SDC_UE_RFPOWER_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.ucChannalQual                         = TAF_SDC_BLER_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.ucRssiValue                           = TAF_SDC_RSSI_VALUE_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.usCellDlFreq                          = TAF_SDC_UE_FREQ_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.usCellUlFreq                          = TAF_SDC_UE_FREQ_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRssi              = TAF_SDC_RSSI_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRsd               = 0;   /*填充值*/
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRsrp              = TAF_SDC_RSRP_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRsrq              = TAF_SDC_RSRQ_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.lSINR              = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.usRI         = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.aucRes[0]    = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.aucRes[1]    = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[0]    = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[1]    = 0;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 3GPP2相关制式的信号强度，目前只有1x的 */
    TAF_SDC_Init1xSigQualityRptValue();

    TAF_SDC_InitHrpdSigQualityRptValue();
#endif
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitAppCsDomainInfo
 功能描述  : 初始化cs域信息
 输入参数  : pstCsDomainInfo - cs域信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月11日
   作    者   : w00281933
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_InitAppCsDomainInfo(
    TAF_SDC_CS_DOMAIN_INFO_STRU *pstCsDomainInfo
)
{
    pstCsDomainInfo->enCsRegStatus                         = TAF_SDC_REG_STATUS_BUTT;
    pstCsDomainInfo->enCsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* 小区受限类型默认需要设置为不受限,否则设置为BUTT时RIL层认为受限 */
    pstCsDomainInfo->stCsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictRegister  = VOS_FALSE;
    pstCsDomainInfo->ucSimCsRegStatus                      = VOS_FALSE;
    pstCsDomainInfo->ucCsAttachAllowFlg                    = VOS_FALSE;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitAppPsDomainInfo
 功能描述  : 初始化ps域信息
 输入参数  : pstPsDomainInfo - ps域信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月11日
   作    者   : w00281933
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SDC_InitAppPsDomainInfo(
    TAF_SDC_PS_DOMAIN_INFO_STRU *pstPsDomainInfo
)
{
    pstPsDomainInfo->enPsRegStatus                         = TAF_SDC_REG_STATUS_BUTT;
    pstPsDomainInfo->enPsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* 小区受限类型默认需要设置为不受限,否则设置为BUTT时RIL层认为受限 */
    pstPsDomainInfo->stPsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;

    pstPsDomainInfo->stPsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstPsDomainInfo->stPsAcRestriction.ucRestrictRegister  = VOS_FALSE;
    pstPsDomainInfo->ucSimPsRegStatus                      = VOS_FALSE;
    pstPsDomainInfo->ucPsAttachAllowFlg                    = VOS_FALSE;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitAppNetwork_Info
 功能描述  : 初始化 TAF_SDC_APP_NETWORK_INFO  stAppNetworkInfo
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改
  2.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : Service_State_Optimize_PhaseII 项目修改
  3.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化

*****************************************************************************/
VOS_VOID TAF_SDC_InitAppNetwork_Info(
    TAF_SDC_APPNETWORK_INFO *pstAppNetworkInfo
)
{
    TAF_SDC_InitAppSysMode();
    TAF_SDC_InitAppSysSubMode();

    TAF_SDC_InitAppNetworkPlmnInfo(&pstAppNetworkInfo->stAppSysInfo.stServPlmnInfo);

    TAF_SDC_Init1xSysInfo(&pstAppNetworkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo);

    TAF_SDC_InitNetworkRssiValue(&pstAppNetworkInfo->stAppSigQuaInfo);

    TAF_SDC_InitAppCsDomainInfo(&pstAppNetworkInfo->stCsDomainInfo);
    TAF_SDC_InitAppPsDomainInfo(&pstAppNetworkInfo->stPsDomainInfo);

    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_BUTT);
    TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_BUTT);

}
/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */

/*lint -restore */
#if (FEATURE_ON == FEATURE_BASTET)
/*****************************************************************************
 函 数 名  : TAF_SDC_GetBastetSupportFlag
 功能描述  : 获取是否支持Bastet
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持Bastet
             VOS_FALSE:不支持Bastet
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月22日
   作    者   : z00128442
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetBastetSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.ucBastetSupportFlag;
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_SDC_Set1xCallUcimEmccNumList
 功能描述  : 设置1X下面UIM或CSIM卡中的紧急呼列表
 输入参数  : pstUcimEccNumList - UIM或CSIM中的相关紧急呼列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月18日
   作    者   : w00176964
   修改内容   : 1x项目新增

*****************************************************************************/
VOS_VOID TAF_SDC_Set1xCallUcimEmccNumList(
    TAF_SDC_UCIM_ECC_NUM_LIST_STRU     *pstUcimEccNumList
)
{
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();

    PS_MEM_CPY(&(pstCallInfo->st1xCallUcimEccNumList), pstUcimEccNumList, sizeof(TAF_SDC_UCIM_ECC_NUM_LIST_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get1xCallUcimEmccNumList
 功能描述  : 获取1X下面UIM或CSIM卡中的紧急呼列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 1X下面UIM或CSIM卡中的紧急呼列表
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月18日
   作    者   : w00176964
   修改内容   : 1x项目新增

*****************************************************************************/
TAF_SDC_UCIM_ECC_NUM_LIST_STRU* TAF_SDC_Get1xCallUcimEmccNumList(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.st1xCallUcimEccNumList);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get1xBaseId
 功能描述  : 获取BaseId信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年07月10日
    作    者   : d00212987
    修改内容   : AGPS迭代0新增
*****************************************************************************/
VOS_UINT16 TAF_SDC_Get1xBaseId(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.stBaseStationInfo.usBaseId;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get1xSid
 功能描述  : 获取Sid信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月25日
   作    者   : g00261581
   修改内容   : 1x项目新增
 2.日    期   : 2015年3月23日
   作    者   : w00242748
   修改内容   : DTS2015031307387:当网络把SID/NID都配成0时，这时SID/NID便不会
                主动上报。
*****************************************************************************/
VOS_INT32 TAF_SDC_Get1xSid(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.lSid;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get1xNid
 功能描述  : 获取Nid信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月25日
   作    者   : g00261581
   修改内容   : 1x项目新增
 2.日    期   : 2015年3月23日
   作    者   : w00242748
   修改内容   : DTS2015031307387:当网络把SID/NID都配成0时，这时SID/NID便不会
               主动上报。
*****************************************************************************/
VOS_INT32 TAF_SDC_Get1xNid(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.lNid;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get1xRoamingFlag
 功能描述  : 获取漫游信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月25日
   作    者   : g00261581
   修改内容   : 1x项目新增
*****************************************************************************/
VOS_UINT8 TAF_SDC_Get1xRoamingFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.ucRoamingInd;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Set1xSysInfo
 功能描述  : MMA更新系统消息
 输入参数  : MMA_MSCC_SYS_SRV_INFO_STRU         *pSysInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月25日
   作    者   : g00261581
   修改内容   : 1x项目新增
 2.日    期   : 2015年3月23日
   作    者   : w00242748
   修改内容   : DTS2015031307387:当网络把SID/NID都配成0时，这时SID/NID便不会
                主动上报。
*****************************************************************************/
VOS_VOID TAF_SDC_Set1xSysInfo(
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU         *pSysInfo
)
{
    TAF_SDC_1X_SYS_INFO_STRU           *pSdc1xSysInfo;

    pSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    pSdc1xSysInfo->usBandClass      = pSysInfo->usBandClass;
    pSdc1xSysInfo->ucRoamingInd     = pSysInfo->ucRoamingInd;
    pSdc1xSysInfo->ucPacketZoneId   = pSysInfo->ucPzid;
    pSdc1xSysInfo->lSid             = (0x00000000 | pSysInfo->usSid);
    pSdc1xSysInfo->lNid             = (0x00000000 | pSysInfo->usNid);
    pSdc1xSysInfo->ucPrevInUse      = pSysInfo->ucPrevInUse;
    pSdc1xSysInfo->usFreq           = pSysInfo->usFreq;

    pSdc1xSysInfo->enRegInfoIncl         = pSysInfo->enRegInfoIncl;
    pSdc1xSysInfo->enBaseStationInfoIncl = pSysInfo->enBaseStationInfoIncl;
    pSdc1xSysInfo->enServiceInfoIncl     = pSysInfo->enServiceInfoIncl;

    if (PS_TRUE == pSysInfo->enRegInfoIncl)
    {
        PS_MEM_CPY(&(pSdc1xSysInfo->stRegInfo), &(pSysInfo->stRegInfo), sizeof(NAS_MSCC_PIF_OHM_REG_INFO_STRU));
    }

    if (PS_TRUE == pSysInfo->enBaseStationInfoIncl)
    {
        PS_MEM_CPY(&(pSdc1xSysInfo->stBaseStationInfo), &(pSysInfo->stBaseStationInfo), sizeof(NAS_MSCC_PIF_OHM_BASE_STATION_INFO_STRU));
    }

    if (PS_TRUE == pSysInfo->enServiceInfoIncl)
    {
        PS_MEM_CPY(&(pSdc1xSysInfo->stServiceInfo), &(pSysInfo->stServiceInfo), sizeof(NAS_MSCC_PIF_OHM_SERVICE_INFO_STRU));
    }
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GethrpdSysInfo
 功能描述  : 获取系统消息信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 系统消息信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月25日
   作    者   : y00322978
   修改内容   : iterating 17新增
*****************************************************************************/
TAF_SDC_HRPD_SYS_INFO_STRU* TAF_SDC_GethrpdSysInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.stHrpdSysInfo);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_Get1xSysInfo
 功能描述  : 获取系统消息信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 系统消息信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月25日
   作    者   : g00261581
   修改内容   : 1x项目新增
*****************************************************************************/
TAF_SDC_1X_SYS_INFO_STRU* TAF_SDC_Get1xSysInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_Get1xSigQualityInfo
 功能描述  : 获取1x信号质量信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 1x信号质量信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年01月14日
   作    者   : m00312079
   修改内容   : 1x项目新增
2.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
TAF_SDC_1X_SIG_QUALITY_INFO_STRU* TAF_SDC_Get1xSigQualityInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSigQuaInfo.st3Gpp2SigQuaInfo.st1xSigQualityRptInfo);
}
/*****************************************************************************
 函 数 名  : TAF_SDC_GetHrpdSigQualityInfo
 功能描述  : 获取Hrpd信号质量信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : HRPD信号质量信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月20日
   作    者   : C00299064
   修改内容   : 新增
*****************************************************************************/
TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU* TAF_SDC_GetHrpdSigQualityInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSigQuaInfo.st3Gpp2SigQuaInfo.stHrpdSigQualityRptInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitHrpdSigQualityRptValue;
 功能描述  : 初始化SDC中HDR SigQualityRpt的值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : c00299064
    修改内容   :
*****************************************************************************/
VOS_VOID TAF_SDC_InitHrpdSigQualityRptValue(VOS_VOID)
{
    TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU         *pstSdcHrpdSigQualityInfo;

    pstSdcHrpdSigQualityInfo                     = TAF_SDC_GetHrpdSigQualityInfo();

    pstSdcHrpdSigQualityInfo->enMode             = TAF_SDC_HDR_CSQ_MODE_ENABLE;
    pstSdcHrpdSigQualityInfo->ucTimeInterval     = 0;
    pstSdcHrpdSigQualityInfo->ucRssiThreshold    = 3;
    pstSdcHrpdSigQualityInfo->ucSnrThreshold     = 3;
    pstSdcHrpdSigQualityInfo->ucEcioThreshold    = 10;
    pstSdcHrpdSigQualityInfo->sHdrRssi           = TAF_SDC_HRPD_INVALID_RSSI_VALUE;
    pstSdcHrpdSigQualityInfo->sHdrSnr            = TAF_SDC_HRPD_INVALID_SNR_VALUE;
    pstSdcHrpdSigQualityInfo->sHdrEcio           = TAF_SDC_HRPD_INVALID_ECIO_VALUE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_InitSigQualityRptValue;
 功能描述  : 初始化SDC中SigQualityRpt的值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月27日
    作    者   : m00312079
    修改内容   : 新建

  2.日    期   : 2015年10月16日
    作    者   : m00312079
    修改内容   : DTS2015101505057:添加ec/Io的上报门限

*****************************************************************************/
VOS_VOID TAF_SDC_Init1xSigQualityRptValue(VOS_VOID)
{
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU            *pstSdc1xSigQualityInfo;

    pstSdc1xSigQualityInfo                          = TAF_SDC_Get1xSigQualityInfo();

    pstSdc1xSigQualityInfo->enMode                  = TAF_SDC_CDMACSQ_MODE_ENABLE;
    pstSdc1xSigQualityInfo->ucTimeInterval          = 3;
    pstSdc1xSigQualityInfo->ucRssiRptThreshold      = 3;
    pstSdc1xSigQualityInfo->ucEcIoRptThreshold      = 3;
    pstSdc1xSigQualityInfo->sCdmaRssi               = TAF_SDC_CDMA_INVALID_RSSI_VALUE;
    pstSdc1xSigQualityInfo->sCdmaEcIo               = TAF_SDC_CDMA_INVALID_ECIO_VALUE;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get1xPrevInUse
 功能描述  : 获取当前使用的协议版本信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月16日
   作    者   : z00316370
   修改内容   : 新增
*****************************************************************************/
VOS_UINT8 TAF_SDC_Get1xPrevInUse(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.ucPrevInUse;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_Get1xChan
 功能描述  : 获取当前使用的channel
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月16日
   作    者   : z00316370
   修改内容   : 新增
*****************************************************************************/
VOS_UINT16 TAF_SDC_Get1xChan(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.usFreq;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetXCaLLState
 功能描述  : 设置当前XCALL状态
 输入参数  : enXCallState xcall 状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月9日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetXCaLLState(
    NAS_OM_1X_CALL_STATE_ENUM_UINT8        enXCallState
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.en1xCallState = enXCallState;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetXCallState
 功能描述  : 获取xcall状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月9日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
NAS_OM_1X_CALL_STATE_ENUM_UINT8 TAF_SDC_GetXCallState(
    VOS_VOID
)
{
    return   TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.en1xCallState;

}
/*****************************************************************************
 函 数 名  : TAF_SDC_GetCdmaStatusReportPeriod
 功能描述  : 获取cdma信息主动上报周期
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_SDC_GetCdmaStatusReportPeriod(
    VOS_VOID
)
{
    return TAF_SDC_GetSdcCtx()->stCdmaMntn.ulRptPeriod;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_SetCdmaStatusReportPeriod
 功能描述  : 保存cdma状态信息主动上报周期
 输入参数  : VOS_UINT32               ulRptPeriod
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCdmaStatusReportPeriod(
    VOS_UINT32                          ulRptPeriod
)
{
    TAF_SDC_GetSdcCtx()->stCdmaMntn.ulRptPeriod = ulRptPeriod;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_SetCdmaCurUeState
 功能描述  : 保存cdma当前UE状态
 输入参数  : TAF_SDC_1X_UE_STATUS_ENUM_UINT8    enCasState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月11日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SDC_SetCdmaCurUeState(
    TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8    enCasState
)
{
    TAF_SDC_GetSdcCtx()->enCasState = enCasState;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetCdmaCurUeState
 功能描述  : 获取cdma当前UE状态
 输入参数  :
 输出参数  : 无
 返 回 值  : enCasState
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月11日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCdmaCurUeState(
    VOS_VOID
)
{
    return  TAF_SDC_GetSdcCtx()->enCasState;
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetApp1xSigQualityInfo
 功能描述  : 获取stAppNetworkInfo中的1x信号质量信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 1x信号质量信息
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年9月30日
    作    者   : j00354216
    修改内容   : CDMA Iteration 18 新增
*****************************************************************************/
TAF_SDC_1X_SIG_QUALITY_INFO_STRU* TAF_SDC_GetApp1xSigQualityInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3Gpp2SigQuaInfo.st1xSigQualityRptInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetApp1xSysInfo
 功能描述  : 获取stAppNetworkInfo中的系统消息信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 系统消息信息
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年9月30日
    作    者   : j00354216
    修改内容   : CDMA Iteration 18 新增
*****************************************************************************/
TAF_SDC_1X_SYS_INFO_STRU* TAF_SDC_GetApp1xSysInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetApp1xRoamingFlag
 功能描述  : 获取stAppNetworkInfo漫游信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月30日
   作    者   : j00354216
   修改内容   : CDMA Iteration 18 新增
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetApp1xRoamingFlag(VOS_VOID)
{
   return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.ucRoamingInd;
}


#endif



/*****************************************************************************
 函 数 名  : TAF_SDC_GetImsToCsRedialCauseConfig
 功能描述  : 获取IMS到CS域重播可配置的原因值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月13日
   作    者   : l00289540
   修改内容   : 新增
*****************************************************************************/

TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU * TAF_SDC_GetImsToCsRedialCauseConfig(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg);

}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetNonnormalRegStatusMergeCfg
 功能描述  : 获取非正常服务下是否上报注册服务状态变化配置信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 非正常服务下是否上报注册服务状态变化配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月27日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU* TAF_SDC_GetNonnormalRegStatusMergeCfg(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stNonnormalRegStatusMergeCfg);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetNonnormalRegStatusMergeFlg
 功能描述  : 获取非正常服务下是否上报注册服务状态变化配置信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 非正常服务下是否上报注册服务状态变化配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月27日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetNonnormalRegStatusMergeFlg(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stNonnormalRegStatusMergeCfg.ucMergeFlg);
}


/*****************************************************************************
 函 数 名  : TAF_SDC_GetNetWorkInfoAddr
 功能描述  : 获取NetWorkInfo的地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_SDC_NETWORK_INFO_STRU*     NetWorkInfo的全局变量的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2016年01月15日
   作    者   : l00324781
   修改内容   : 新生成函数
*****************************************************************************/
TAF_SDC_NETWORK_INFO_STRU* TAF_SDC_GetNetWorkInfoAddr(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetAppNetWorkInfoAddr
 功能描述  : 获取AppNetWorkInfo的地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_SDC_APPNETWORK_INFO*     AppNetWorkInfo的全局变量的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2016年01月15日
   作    者   : l00324781
   修改内容   : 新生成函数
*****************************************************************************/
TAF_SDC_APPNETWORK_INFO* TAF_SDC_GetAppNetWorkInfoAddr(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo);
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

