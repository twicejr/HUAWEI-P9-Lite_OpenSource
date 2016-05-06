/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CfdNvId.h
  版 本 号   :
  作    者   : 
  生成日期   : 2010年12月24日
  最近修改   :
  功能描述   : 定义了机要数据NV项ID枚举定义
  函数列表   :
  修改历史   :
  1.日    期   : 2010年12月24日
    作    者   : y00163779
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CFDNVID_H__
#define __CFDNVID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "NvIddef.h"

enum CFD_NV_ID_ENUM
{
/* 8267  */      en_NV_Item_CustomizeSimLockPlmnInfo = GU_PS_NV_ID_MIN + 74,
/* 8268  */      en_NV_Item_CardlockStatus,
/* 8269  */      en_NV_Item_CustomizeSimLockMaxTimes,
/* 8481  */      en_NV_Item_OperLock_Plmn_Info = 8481,
/* 8494  */      en_NV_Item_OPERLOCK_PLMN_INFO_WHITE = 8494,
                 en_NV_Item_BUTT
};

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* __CFDNVID_H__ */
