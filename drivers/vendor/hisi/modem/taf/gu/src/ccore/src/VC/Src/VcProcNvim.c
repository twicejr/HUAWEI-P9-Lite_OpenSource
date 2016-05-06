/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : VcProcNvim.c
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2012年3月3日
  最近修改   :
  功能描述   : VC处理NV项的读写文件
  函数列表   :
  修改历史   :
  1.日    期   :2012年3月3日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "VcCtx.h"
#include "VcProcNvim.h"
#include "NVIM_Interface.h"
#include "VcComm.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

#include "VcMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_VC_PROC_NIVM_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*****************************************************************************
   4 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : APP_VC_ReadPcVoiceSupportNvim
 功能描述  : 获取NVIM中的en_NV_Item_PCVOICE_Support_Flg的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID  APP_VC_ReadPcVoiceSupportNvim( VOS_VOID )
{
    APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU                  stPcVoiceSupportFlag;
    APP_VC_MS_CFG_INFO_STRU                                *pstMsCfgInfo;
    VOS_UINT32                                              ulLength;

    pstMsCfgInfo                        = APP_VC_GetCustomCfgInfo();

    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_PCVOICE_Support_Flg, &ulLength);
    if (ulLength > sizeof(stPcVoiceSupportFlag))
    {
        return;
    }
    stPcVoiceSupportFlag.usPcVoiceSupportFlag = APP_VC_NV_ITEM_DEACTIVE;

    if (NV_OK != NV_Read(en_NV_Item_PCVOICE_Support_Flg, &stPcVoiceSupportFlag, ulLength))
    {
        pstMsCfgInfo->usVcPcvoiceSupportFlag = APP_VC_NV_ITEM_DEACTIVE;
        VC_WARN_LOG("APP_VC_ReadAlsSupportNvim: NV Read en_NV_Item_PCVOICE_Support_Flg Fail" );
        return;
    }

    if ( (APP_VC_NV_ITEM_ACTIVE != stPcVoiceSupportFlag.usPcVoiceSupportFlag)
       &&(APP_VC_NV_ITEM_DEACTIVE != stPcVoiceSupportFlag.usPcVoiceSupportFlag))
    {
        pstMsCfgInfo->usVcPcvoiceSupportFlag = APP_VC_NV_ITEM_DEACTIVE;
    }
    else
    {
        pstMsCfgInfo->usVcPcvoiceSupportFlag = stPcVoiceSupportFlag.usPcVoiceSupportFlag;
    }

    return;
}

/*****************************************************************************
 函 数 名  : APP_VC_ReadNvimInfo
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
*****************************************************************************/
VOS_VOID APP_VC_ReadNvimInfo(VOS_VOID)
{
    /* en_NV_Item_PCVOICE_Support_Flg */
    APP_VC_ReadPcVoiceSupportNvim();
    return;
}

/*lint +e958*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



