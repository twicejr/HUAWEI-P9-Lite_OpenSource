/*************************************************************************
*   版权所有(C) 1987-2011, 深圳华为技术有限公司.
*
*   文 件 名 :  om.h
*
*   作    者 :  yangzhi
*
*   描    述 :  本文件命名为"mdrv.h", 给出V7R1底软和协议栈之间的API接口统计
*
*   修改记录 :  2011年1月18日  v1.00  yangzhi创建
*************************************************************************/
#ifndef _MDRV_OM_H_
#define _MDRV_OM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_om_common.h"

 typedef struct
 {
     unsigned int     ulInfoLen;
     unsigned int     ulErrNo;
     unsigned int     ulBoardTime;
     unsigned int     ulSliceTime;
 }DRV_OM_HEAD_INFO_S;
 
 typedef struct
 {
     DRV_OM_HEAD_INFO_S      stRecordHead;
     unsigned int            ulRebootReason;
     unsigned int            ulModeId;
     unsigned int            ulArg1;
     unsigned int            ulArg2;
     unsigned char           Imsi[9];
     unsigned char           ImsiStatus;
     unsigned char           reserve[2];
 }DRV_OM_SYSTEM_RESET_S;

 /*****************************************************************************
 * 函 数 名  : mdrv_om_get_system_reset_info
 * 功能描述  : 获取系统复位信息
 *
 * 输入参数  : 无
 *
 * 输出参数  : 无
 *
 * 返 回 值  : 0 --- 成功，-1 --- 失败
 *
 *****************************************************************************/
int mdrv_om_get_system_reset_info(DRV_OM_SYSTEM_RESET_S * info);
/**************************************************************************
* 函 数 名  : mdrv_om_set_voicestate
* 功能描述  : 提供给GUNAS用于在进入退出电话时调用
* 输入参数  : flag：进入或退出语音
* 输出参数  :
*             返 回 值  : 0:  操作成功；
*                        -1： 操作失败。
****************************************************************************/
int mdrv_om_set_voicestate(unsigned int flag);

#ifdef __cplusplus
}
#endif
#endif

