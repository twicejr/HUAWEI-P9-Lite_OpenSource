/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCsCallCommFunc.c
  版 本 号   : 初稿
  作    者   : l00359089
  生成日期   : 2015年12月22日
  功能描述   : TAF CS CALL 公共接口
  函数列表   :
  修改历史   :
  1.日    期   : 2015年12月22日
    作    者   : l00359089
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafCsCallCommDef.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_CS_CALL_COMM_FUNC_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

VC_TO_TAFCS_CAUSE_STRU                    g_astVcCauseToTafCsCause[] =
{
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_STARTED         ,   TAF_CS_CAUSE_VC_ERR_STARTED         },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_PORT_CFG_FAIL   ,   TAF_CS_CAUSE_VC_ERR_PORT_CFG_FAIL   },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_DEVICE_FAIL ,   TAF_CS_CAUSE_VC_ERR_SET_DEVICE_FAIL },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_START_FAIL  ,   TAF_CS_CAUSE_VC_ERR_SET_START_FAIL  },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_VOLUME_FAIL ,   TAF_CS_CAUSE_VC_ERR_SET_VOLUME_FAIL },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SAMPLE_RATE_FAIL,   TAF_CS_CAUSE_VC_ERR_SAMPLE_RATE_FAIL},
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_TI_START_EXPIRED,   TAF_CS_CAUSE_VC_ERR_TI_START_EXPIRED},
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_CALL_ConvertVcCauseToTafCsCause
 功能描述  : VC的原因值转换为TafCsCause
 输入参数  : enCause   - VC失败原因值
 输出参数  : 无
 返 回 值  : TAF层失败原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :2015年12月22日
    作    者   :l00359089
    修改内容   :新建
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_ConvertVcCauseToTafCsCause(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32 enVcCause
)
{
    TAF_CS_CAUSE_ENUM_UINT32            enTafCause;
    VOS_UINT32                          i;

    enTafCause  = TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING;

    for (i = 0; i < (sizeof(g_astVcCauseToTafCsCause) / sizeof(g_astVcCauseToTafCsCause[0])); i++)
    {
        if (enVcCause == g_astVcCauseToTafCsCause[i].enVcCause)
        {
            enTafCause = g_astVcCauseToTafCsCause[i].enTafCsCasue;
            break;
        }
    }

    return enTafCause;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


